# zad 1
Modele będą automatycznie wybierać teksty które są bardziej prawdopodobne. Rozwiązanie nie jest idealne, bo modele w różny sposób generują tekst więc sprawdzanie musiałoby się odbywać dla konkretnego modelu. Dodatkowo ludzkie teksty często są równie proste co te generowane przez modele więc może pojawić się wiele false positive.
Perplexity można kontrolować za pomocą temperatury - im wyższa temperatura tym bardziej zróżnicowane (i mniej przewidywalne) teksty będą generowane przez model, co może obniżyć skuteczność detekcji. Można także próbować różnych top_p lub top_k aby zwiększyć różnorodność generowanych tekstów.

# zad 2
Dlaczego losowanie od lewej do prawej się nie sprawdzi:
jeśli na przykład pozycja k jest duża to tracimy dużo czasu na losowanie poprzednich tokenów

a) Losujemy $k-1$ słów i forcujemy żeby k-te słowo było ustalone. Następnie sprawdzamy czy prawdopodobieństwo wygenerowania k-tego słowa jest większe niż pewien próg. Możemy również użyć beam search żeby było kilka korpusów.

b) Przyjmujemy model 3-gramowy. Dla każdego k nieparzystego po kolei tworzymy zbiory kandydatów na słowo k-te które jest prawdopobne biorąc pod uwagę k-1 i k+1. W ten sposób losujemy słowa które na pewno będą sensowne.

c) Tworzymy dwa korpusy od przodu i od tyłu. Rozszerzamy od przodu a następnie od tyłu sprawdzamy overlap na każdym kroku.

d) Na każdym kroku tworzymy zbiory kandydatów dla sufiksu i wybieramy spośród nich.

# zad 3
Można wykorzystać argument wartości naukowej i R&D albo określić to jako eksperyment badawczy

# zad 4
Ustalamy wspólny korpus początkowy i seed.
Następnie generujemy po słowie. Jeśli chcemy zakodować 1 to wybieramy najbardziej prawdopdobne słowo, jeśli 0 inne słowo.
Dekodując robimy na odwrót.

# zad 5
Jeśli kluczem jest model językowy to możemy zgadnąć ręcznie najbardziej prawdopodobne słowo ale nie będziemy mieć stu procentowej pewności

# zad 6
Zapisujemy jako liczbę porządkową słowa w liście prawdopodobieństw.

# zad 7

# zad 8
Cechy charakterystyczne wierszyka:
- stały układ rymów (na przykład AABB lub ABAB)
- rytm (stała liczba sylab w wersie)
- spójnośc tematyczna
- poprawność gramatyczna i składniowa

algo:
1. Generujemy 1 linijkę zaczynajac od tematu i prosimy o wygenerowanie kilku wersów ale zatrzymujemy tylko te które zachowują nasze założone metryki. Identyfikujemy słowo do rymowania.
2. Potrzebny nam słownik rymów do zidentyfikowanego wcześniej słowa. Generujemy linijke słowo po słowie trzymając k najlepzych kandydatów. Liczymy sylaby, jeśli przekroczymy ustaloną metrykę to odrzycamy daną wiązkę. Gdy zbliżamy się do końca linijki wyszukujemy najbardziej prawdopodobne słowo ze słownika do najleszych kandydatów. 
3. Bierzemy dwie pierwsze linijki jako kontekst i generujemy 3. jeśli chcemy żeby wiersz był AABB to nie może się rymować z L1 i L2.

# zad 9
Generowanie UI. Jako korpus podajemy na przykład początek formularza czy jakiś nagłówek. Generujemy po komponencie.
Model musi być nauczony na konkretnej składni którą sami mozemy zdefiniować (np. DOM tree)