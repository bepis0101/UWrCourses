from transformers import AutoTokenizer, AutoModelForCausalLM
import torch


# model polski GPT-2
model_name = "flax-community/papugapt2"
tokenizer = AutoTokenizer.from_pretrained(model_name)
model = AutoModelForCausalLM.from_pretrained(model_name)

opinie = [
    # pozytywne
    ("Parking monitorowany w cenie.", "pozytywna"),
    ("Hotel czysty, pokoje były sprzątane bardzo dokładnie.", "pozytywna"),
    ("Fajny klimat pofabrykanckich kamienic.", "pozytywna"),
    ("Sala zabaw dla dzieci, plac zabaw na zewnątrz, kominek, tenis stołowy.", "pozytywna"),
    # negatywne
    ("W wielu pokojach niedziałająca klimatyzacja.", "negatywna"),
    ("Jedzenie monotonne.", "negatywna"),
    ("Drożej niż u konkurencji w podobnym standardzie.", "negatywna"),
    ("Omijaj to miejsce!", "negatywna"),
]

# kilka wariantów promptów
prompty = [
    "To była opinia pozytywna: {o}",
    "To była opinia negatywna: {o}",
]

@torch.no_grad()
def log_likelihood(text):
    """Zwraca sumę logp(tokenów) dla całego tekstu."""
    inputs = tokenizer(text, return_tensors="pt")
    outputs = model(**inputs, labels=inputs["input_ids"])
    # outputs.loss = średni cross-entropy, więc mnożymy przez długość
    nll = outputs.loss.item() * inputs["input_ids"].size(1)
    return -nll  # logp = -nll

correct = 0
for opinia, gold in opinie:
    pos_score = log_likelihood(prompty[0].format(o=opinia))
    neg_score = log_likelihood(prompty[1].format(o=opinia))
    wynik = "pozytywna" if pos_score > neg_score else "negatywna"
    print(f"„{opinia}” → {wynik} (prawidłowa: {gold})")
    if wynik == gold:
        correct += 1

accuracy = correct / len(opinie)
print(f"\nSkuteczność: {accuracy:.2%}")
