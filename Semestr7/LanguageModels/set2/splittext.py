import torch
from transformers import AutoTokenizer, AutoModelForCausalLM

prompt = "wprost|wyprosty|wyprostu|wyprost uwielbiała|wielbił|wielbiła|uwielbił|wielbiło|uwielbiał|uwielbiało|uwielbiały słuchać|osłuchać|słychać|usłuchać o|i|e|a|ó|ę|y|ą|u wartościach własnych|owłosionych macierzy|mocarz|macierzą|macierze|mocarza|mocarze|mocarzy|macierz"

def split_prompt(prompt):
  words = prompt.split(" ")
  return list(map(lambda x: x.split("|"), words))

class TextDisambiguator:
  def __init__(self, model_name='flax-community/papuGaPT2'):
    print(f"Ładowanie modelu {model_name}...")
    self.tokenizer = AutoTokenizer.from_pretrained(model_name)
    self.model = AutoModelForCausalLM.from_pretrained(model_name)
    self.model.eval()
    print("Model załadowany.")

  def score_sequence(self, text):
    inputs = self.tokenizer(text, return_tensors='pt')
    
    with torch.no_grad():
      outputs = self.model(**inputs, labels=inputs['input_ids'])
    loss = outputs.loss.item()
    n_tokens = inputs['input_ids'].shape[1]
    return -loss * n_tokens

  def disambiguate(self, encoded_text_list, beam_width=3):
    beams = [("", 0.0)]

    for group_idx, variants_str in enumerate(encoded_text_list):
      variants = variants_str.split('|')
      candidates = []

      for sequence, current_score in beams:
        for variant in variants:
          prefix = sequence + " " if sequence else ""
          new_sequence = prefix + variant
          # print(current_score)
          score = self.score_sequence(new_sequence)
          candidates.append((new_sequence, score))

      candidates.sort(key=lambda x: x[1], reverse=True)
      beams = candidates[:beam_width]

    return beams[0][0]

if __name__ == "__main__":
  variant_groups = prompt.split(" ")
  
  disambiguator = TextDisambiguator()
  result = disambiguator.disambiguate(variant_groups, beam_width=3)
  
  print("-" * 30)
  print("WYNIK KOŃCOWY:")
  print(result)