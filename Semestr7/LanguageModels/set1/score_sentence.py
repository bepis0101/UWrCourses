import itertools
import torch
from transformers import AutoModelForCausalLM, AutoTokenizer

@torch.no_grad()
def score_sentence(sentence, device='cpu'):
  tokenizer = AutoTokenizer.from_pretrained("flax-community/papuGaPT2")
  inputs = tokenizer(sentence, return_tensors='pt', add_special_tokens=True)
  input_ids = inputs['input_ids'].to(device)
  attention_mask = inputs['attention_mask'].to(device)
  model = AutoModelForCausalLM.from_pretrained("flax-community/papuGaPT2").to(device)
  outputs = model(input_ids, attention_mask=attention_mask)
  logits = outputs.logits # logit => 1 — batch size (jedno zdanie), długość sekwencji (liczba tokenów w zdaniu), rozmiar słownika modelu 
  log_probs = torch.nn.functional.log_softmax(logits, dim=-1)
  target_ids = input_ids[0]
  seq_len = target_ids.size(0)
  if seq_len <= 1:
    return float('-inf')  # nieocenia się jedno-tokenowych zdań sensownie
  # wybierz logp(token_{t} | tokens_{<t}) = log_probs[0, t-1, token_t]
  chosen = []
  for t in range(1, seq_len):
    lp = log_probs[0, t-1, target_ids[t]].item()
    chosen.append(lp)
  sum_logp = float(sum(chosen))
  return sum_logp

def unique_permutations(iterable):
  """Generates unique permutations of an iterable, even if it contains duplicates."""
  previous = None
  for p in itertools.permutations(sorted(iterable)):
    if p != previous:
      previous = p
      yield p

def normalize_sentence(sentence: str) -> list[str]:
  return list(map(lambda x: x.lower().strip('., '), sentence.strip().split()))

test = "Babuleńka miała dwa rogate koziołki."
tokens = normalize_sentence(test)
perms = list(unique_permutations(tokens))
print(f"Liczba unikalnych permutacji: {len(perms)}")
scored = []
for p in perms:
  s = ' '.join(p)
  score = score_sentence(s, device='cpu')
  print(f"{score:.2f}: {s}")
  scored.append((s, score))
scored = sorted(scored, key=lambda x: x[1], reverse=True)
print(scored[:10])