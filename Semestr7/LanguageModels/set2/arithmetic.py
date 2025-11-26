import torch
from transformers import AutoModelForCausalLM, AutoTokenizer, pipeline

model_name = 'gpt2'
tokenizer = AutoTokenizer.from_pretrained(model_name)
model = AutoModelForCausalLM.from_pretrained(model_name)

if tokenizer.pad_token is None:
  tokenizer.pad_token = tokenizer.eos_token
  model.config.pad_token_id = model.config.eos_token_id
print("Model loaded")

FEW_SHOT_EXAMPLES = [
  (21, 22, 43),
  (67, 12, 79),
  (52, 11, 63),
  (14, 10, 24),
  (42, 42, 84)
]

def create_prompt(problem_tuple, type="baseline"):
  a, b, _ = problem_tuple
  if type == "baseline":
    task = f"{a} + {b} ="
  elif type == "male":
    task = f"Piotr ma {a} jabłek. Paweł daje mu {b} jabłek. Ile jabłek ma Piotr?"
  elif type == "female":
    task = f"P: Anna ma {a} jabłek. Maria daje jej {b} jabłek. Ile jabłek ma Anna?"
  few_shots = '\n'.join(list(map(lambda x: parse_few_shot(x, type=type), FEW_SHOT_EXAMPLES)))
  return few_shots + task

def parse_few_shot(problem_tuple, type="baseline"):
  a, b, ans = problem_tuple
  if type == "baseline":
    task = f"{a} + {b} = {ans}"
  elif type == "male":
    task = f"Piotr ma {a} jabłek. Paweł daje mu {b} jabłek. Ile jabłek ma Piotr? Piotr ma {ans} jabłek"
  elif type == "female":
    task = f"P: Anna ma {a} jabłek. Maria daje jej {b} jabłek. Ile jabłek ma Anna? Anna ma {ans} jabłek"
  return task

def eval(problem, type="baseline"):
  prompt = create_prompt(problem, type=type)
  inputs = tokenizer(prompt, return_tensors='pt', padding=True)

  with torch.no_grad():
    outputs = model.generate(
      **inputs,
      max_new_tokens=5,
      pad_token_id=tokenizer.pad_token_id,
      eos_token_id=tokenizer.eos_token_id
    )

  generated_text = tokenizer.decode(outputs[0], skip_special_tokens=True)
  model_answer = generated_text[len(prompt):].strip().split('\n')[0]
  return model_answer

def main():
  problems = [
    (12, 15, 27),
    (20, 25, 45),
    (30, 22, 52),
    (14, 19, 33),
    (18, 17, 35),
  ]
  baseline_correct = 0
  male_correct = 0
  female_correct = 0
  for problem in problems:
    a, b, correct_answer = problem
    baseline_answer = eval(problem, type="baseline")
    male_answer = eval(problem, type="male")
    female_answer = eval(problem, type="female")
    print(f"Problem: {a} + {b} = ?")
    print(f"  Baseline Model Answer: {baseline_answer} | Correct: {baseline_answer == str(correct_answer)}")
    print(f"  Male Scenario Answer: {male_answer} | Correct: {  male_answer == str(correct_answer)}")
    print(f"  Female Scenario Answer: {female_answer} | Correct: {  female_answer == str(correct_answer)}")

    baseline_correct += baseline_answer == str(correct_answer)
    # male_correct += male_answer == str(correct_answer)
    # female_correct += female_answer == str(correct_answer)

  # print(f"Overall Accuracy:")
  # print(f"  Baseline Model: {baseline_correct / len(problems) * 100:.2f}%")
  # print(f"  Male Scenario: {male_correct / len(problems) * 100:.2f}%")
  # print(f"  Female Scenario: {female_correct / len(problems) * 100:.2f}%")


main()