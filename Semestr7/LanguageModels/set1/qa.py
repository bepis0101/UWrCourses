from transformers import AutoTokenizer, AutoModelForCausalLM
import torch
from torch.nn import functional as F
import re
import random
from tqdm import tqdm

def load_questions(path):
    with open(path, 'r', encoding='utf-8') as f:
        qs = [x.strip() for x in f if x.strip()]
        return qs
        
QNA_SAMPLE = 0.1
PATH = './task4_questions.txt'
q_pref = "Pytanie:"
a_pref = "Odpowiedź:"
categories = {
    "tak_nie": f""""
    {q_pref} Czy ziemia jest płaska?
    {a_pref} Nie.
    {q_pref} Czy ptaki znoszą jajka?
    {a_pref} Tak.
    """,
    "osoby": f"""
    {q_pref} Kto napisał "Folwark zwierzęcy"?
    {a_pref} George Orwell.
    {q_pref} Kto ma rekord olimpijski w sprincie na 100 metrów?
    {a_pref} Usain Bolt.
    """,
    "miejsca": f"""
    {q_pref} W jakim kraju jest Taj Mahal?
    {a_pref} Indie.
    {q_pref} W jakim mieście mieszkał Alzheimer?
    {a_pref} Wrocław. 
    """,
    "cytaty": f"""
    {q_pref}: Kto powiedział: "Być albo nie być?"
    {a_pref}: William Shakespeare.
    {q_pref}: Kto powiedział: "Miej serce i patrzaj w serce"?
    {a_pref}: Adam Mickiewicz.
    """,
    "definicja": f"""
    {q_pref}: Co to jest komputer?
    {a_pref}: Urządzenie elektroniczne do przetwarzania danych.
    {q_pref}: Co to jest stolica?
    {a_pref}: Główne miasto kraju.
    """,
    "fakt": f"""
    {q_pref} Ile to 13 odjąć 2?
    {a_pref} 11
    {q_pref} Która planeta jest najbliżej słońca?
    {a_pref} Merkury.
    """
}

model_name = 'eryk-mazus/polka-1.1b-chat'
device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
tokenizer = AutoTokenizer.from_pretrained(model_name)
model = AutoModelForCausalLM.from_pretrained(model_name)
model.to(device)  # type: ignore
print("Model loaded on", device)

def log_probs_from_logits(logits, labels):
    logp = F.log_softmax(logits, dim=-1)
    logp_label = torch.gather(logp, 2, labels.unsqueeze(2)).squeeze(-1)
    return logp_label

def sentence_prob(sentence_txt):
    input_ids = tokenizer(sentence_txt, return_tensors='pt')['input_ids'].to(device)
    with torch.no_grad():
        output = model(input_ids=input_ids)
        log_probs = log_probs_from_logits(output.logits[:, :-1, :], input_ids[:, 1:])
        seq_log_probs = torch.sum(log_probs)
    return seq_log_probs.cpu().numpy()  

def ask_model(question, shots=None):
    base_prompt = ""
    if shots:
        base_prompt = shots.strip() + "\n\n"
    prompt = f"{base_prompt}{q_pref} {question}\n{a_pref}"
    inputs = tokenizer(prompt, return_tensors="pt").to(device)

    max_new_tokens = 20
    pad_token_id = tokenizer.eos_token_id
    do_sample = True
    temperature = 0.7
    top_p = 0.9
    repetition_penalty = 1.2
    num_beams = None

    # If shots supplied and seem factual, force deterministic decoding
    if shots and len(shots) > 0:
        do_sample = False
        num_beams = 5
        temperature = 0.0

    # Pass tokenized inputs as explicit tensors on the model device
    input_ids = inputs['input_ids'].to(device)
    attention_mask = inputs.get('attention_mask')
    if attention_mask is not None:
        attention_mask = attention_mask.to(device)

    # Call generate with explicit named params
    if num_beams is not None:
        output = model.generate(
            input_ids=input_ids,
            attention_mask=attention_mask,
            max_new_tokens=max_new_tokens,
            pad_token_id=pad_token_id,
            do_sample=do_sample,
            temperature=temperature,
            top_p=top_p,
            repetition_penalty=repetition_penalty,
            num_beams=num_beams,
        )
    else:
        output = model.generate(
            input_ids=input_ids,
            attention_mask=attention_mask,
            max_new_tokens=max_new_tokens,
            pad_token_id=pad_token_id,
            do_sample=do_sample,
            temperature=temperature,
            top_p=top_p,
            repetition_penalty=repetition_penalty,
        )
    text = tokenizer.decode(output[0], skip_special_tokens=True)
    ans = text.split("Odpowiedź:")[-1].strip().split('\n')[0]
    ans = ans.strip()
    # remove leading punctuation/quotes
    ans = re.sub(r'^["\'"`\\s:.–—\-]+', '', ans)
    return ans

def heura(q):
    clean_q = q.lower().strip()
    if clean_q.startswith("czy ") or clean_q.startswith("czyż ") or clean_q.startswith("czy też "):
        few_shots = categories["tak_nie"]
        prob_yes = sentence_prob(f"{few_shots}\n\n{q_pref} {q}\n{a_pref} Tak.")
        prob_no = sentence_prob(f"{few_shots}\n\n{q_pref} {q}\n{a_pref} Nie.")
        return "Tak." if prob_yes > prob_no else "Nie."
    if any(tok in q for tok in ["ile", "ile wynosi", "ile jest", "którym roku", "kiedy"]):
        ans = ask_model(q, shots=categories["fakt"])
        nums = re.findall(r'\d+', ans)
        if nums:
            return nums[0] + "."
        word_to_digit = {"jeden": "1", "dwa": "2", "trzy": "3", "cztery": "4", "pięć": "5", 
                         "sześć": "6", "siedem": "7", "osiem": "8", "dziewięć": "9", "zero": "0"}
        for w, d in word_to_digit.items():
            if re.search(rf"\b{w}\b", ans.lower()):
                return d
        return ans
    if q.startswith("co") or "oznacza" in q or q.startswith("jak nazywa się"):
        few_shots = categories["definicja"]
        return ask_model(q, shots=few_shots)
    if any(tok in q for tok in ["kto", "która osoba", "który człowiek"]):
        few_shots = categories["osoby"]
        return ask_model(q, shots=few_shots)
    if any(tok in q for tok in ["gdzie", "w jakim kraju", "w jakim mieście"]):
        few_shots = categories["miejsca"]
        return ask_model(q, shots=few_shots)
    if any(tok in q for tok in ["kto powiedział", "cytował", "cytat"]):
        few_shots = categories["cytaty"]
        return ask_model(q, shots=few_shots)
    few_shots = categories["fakt"]
    return ask_model(q, shots=few_shots)

def main():
    questions = load_questions(PATH)
    with open("task4_questions.txt", encoding="utf-8") as f:
        questions = [x.strip() for x in f if x.strip()]
        questions_idx = random.sample(range(len(questions)), int(len(questions) * QNA_SAMPLE))
        questions = [questions[i] for i in questions_idx]

    with open("task4_answers.txt", "r", encoding="utf-8") as f:
        real_answers = [x.strip() for x in f if x.strip()]
        real_answers = [real_answers[i] for i in questions_idx]

    with open("correct_answers.txt", "w", encoding="utf-8") as f:
        for a in real_answers:
            f.write(a + "\n")
    with open("task4_questions_sampled.txt", "w", encoding="utf-8") as f:
        for q in questions:
            f.write(q + "\n")

    answers = []
    for q in tqdm(questions, desc="Odpowiadanie na pytania"):
        ans = heura(q)
        answers.append(ans)

    with open("found_answers.txt", "w", encoding="utf-8") as f:
        for a in answers:
            f.write(a.strip() + "\n")

main()