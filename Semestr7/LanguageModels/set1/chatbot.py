from transformers import pipeline, AutoModelForCausalLM, AutoTokenizer

model_name = "flax-community/papuGaPT2"

tokenizer = AutoTokenizer.from_pretrained(model_name)
model = AutoModelForCausalLM.from_pretrained(model_name)

generator = pipeline("text-generation", model=model, tokenizer=tokenizer, device=-1)

history = []

print('Witaj w chatbocie Gwiezdno wojennym! Odpowiadam na pytania dotyczące uniwersum Star Wars.\n'
      'Aby uzyskać listę komend wpisz "__help", aby zakończyć rozmowę wpisz "__exit".')

COMMAND_LIST = {
    '__help': 'Wyświetla listę dostępnych komend.',
    '__exit': 'Kończy rozmowę z chatbotem.',
    '__clear': 'Czyści historię rozmowy.',
    '__history': 'Wyświetla historię rozmowy.'
}

PREFIX_BOT = 'Największy fan Gwiezdnych Wojen: '
PREFIX_USER = 'Nowy fan uniwersum Gwiezdnych Wojen: '

def execute_command(command):
    global history
    match command:
        case '__help':
            print('Lista dostępnych komend:')
            for cmd, desc in COMMAND_LIST.items():
                print(f'{cmd}: {desc}')
        case '__exit':
            print('Niech moc będzie z tobą!')
            return True
        case '__clear':
            history = []
            print('Historia wyczyszczona.')
        case '__history':
            if not history:
                print('Brak historii rozmowy.')
                return
            print('Historia rozmowy:')
            for q, a in history:
                print(f'Użytkownik: {q}')
                print(f'Bot: {a}\n')
    return False

def build_prompt(user_input):
    # Używamy tylko ostatnich 3 wypowiedzi dla kontekstu
    dialogue_context = ""
    for (q, a) in history[-3:]:
        dialogue_context += f"{PREFIX_USER}{q}\n{PREFIX_BOT}{a}\n"
    dialogue_context += f"{PREFIX_USER}{user_input}\n{PREFIX_BOT}"
    return dialogue_context

def clean_response(text):
    # Wytnij część po ostatnim promptcie
    text = text.strip()
    text = text.split('\n')[0]  # tylko pierwsza linia
    # usuń niedokończone zdania
    if '.' in text:
        text = '.'.join(text.split('.')[:-1]) + '.'
    return text.strip()

while True:
    user_input = input("> ").strip()
    if any(user_input.startswith(cmd) for cmd in COMMAND_LIST.keys()):
        if execute_command(user_input.split()[0]):
            break
        continue

    # Generujemy kilka odpowiedzi
    prompt = build_prompt(user_input)
    responses = generator(
        prompt,
        pad_token_id=tokenizer.eos_token_id,
        do_sample=True,
        top_p=0.9,
        top_k=20,
        temperature=0.8,
        num_return_sequences=3,
        max_new_tokens=60,
        repetition_penalty=1.2
    )
    # Wybieramy najlepszą
    cleaned = [clean_response(r["generated_text"][len(prompt):]) for r in responses]
    candidates = [r for r in cleaned if len(r.split()) > 2]
    print("Candidates before filtering:" )
    for c in candidates:
      print(f"- {c}")
    candidates = filter(lambda x: any(char.isalpha() for char in x), candidates)
    candidates = list(candidates)
    if not candidates:
      candidates = ["Hmm, nie jestem pewien..."]
    best = max(candidates, key=lambda x: filter(str.isalpha, x).__sizeof__())

    print(best)
    history.append((user_input, best))
