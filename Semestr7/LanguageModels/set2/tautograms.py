import torch
import torch.nn.functional as F
from transformers import AutoTokenizer, AutoModelForCausalLM, LogitsProcessor, LogitsProcessorList

model_name = "sdadas/polish-gpt2-medium"
tokenizer = AutoTokenizer.from_pretrained(model_name)
model = AutoModelForCausalLM.from_pretrained(model_name)

if tokenizer.pad_token is None:
  tokenizer.pad_token = tokenizer.eos_token
  model.config.pad_token_id = model.config.eos_token_id

class TautogramLogitsProcessor(LogitsProcessor):
  def __init__(self, letter, tokenizer):
    self.letter = letter.lower()
    self.tokenizer = tokenizer
    self.vocab_size = tokenizer.vocab_size
    self.suppress_mask = torch.zeros(self.vocab_size, dtype=torch.bool)
    
    for i in range(self.vocab_size):
      token_text = tokenizer.decode([i])
      if token_text.startswith(" "):
        clean_word = token_text.strip().lower()
        if not clean_word:
          continue
        if not clean_word.startswith(self.letter) and clean_word[0].isalnum():
          self.suppress_mask[i] = True

  def __call__(self, input_ids, scores):
    scores[:, self.suppress_mask] = -float('inf')
    return scores

def score_sequence(input_ids, model):
  attention_mask = torch.ones_like(input_ids)
  with torch.no_grad():
    outputs = model(input_ids, attention_mask=attention_mask)
    logits = outputs.logits[:, :-1, :]
    target_ids = input_ids[:, 1:]
    
    probs = F.softmax(logits, dim=-1)
    token_probs = torch.gather(probs, 2, target_ids.unsqueeze(-1)).squeeze(-1)
    
    min_prob = token_probs.min().item()
    mean_prob = token_probs.mean().item()
    
    return mean_prob * min_prob

def generate_best_tautogram(prefix, variants=5):
  letter = prefix.split()[0][0].lower()
  input_ids = tokenizer.encode(prefix, return_tensors='pt')
  attention_mask = torch.ones_like(input_ids)
  
  logits_processor = LogitsProcessorList([
    TautogramLogitsProcessor(letter, tokenizer)
  ])
  
  best_text = ""
  best_score = -1.0
  
  for _ in range(variants):
    try:
      output = model.generate(
        input_ids,
        attention_mask=attention_mask,
        max_new_tokens=50,
        do_sample=True,
        top_k=50,
        top_p=0.95,
        repetition_penalty=1.5,
        logits_processor=logits_processor,
        pad_token_id=tokenizer.eos_token_id,
        eos_token_id=tokenizer.eos_token_id,
        num_return_sequences=1
      )
      
      score = score_sequence(output, model)
      decoded = tokenizer.decode(output[0], skip_special_tokens=True).strip()
      
      if not decoded.endswith(('.', '!', '?')):
        decoded += "."
      
      if score > best_score:
        best_score = score
        best_text = decoded
        
    except Exception:
      continue
            
  return best_text

prefix = "Prawdziwy piekarz przyprawia pieczywo pieprzem"
result = generate_best_tautogram(prefix)
print(result)