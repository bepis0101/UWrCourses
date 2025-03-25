text = open('pan_tadeusz.txt', encoding='utf-8').read().split('\n')
# print(text[:10])
words = open('words_for_ai1.txt', encoding='utf-8').read().split('\n')
# print(words[:10])
words = set(words)

longest_word = max(words, key=len)


### Korzystamy z algorytmu programowania dynamicznego do znalezienia najwiekszej wartosci dp.
### dp[i] to maksymalna suma kwadratow dlugosci słów w linii od indeksu 0 do i
### split[i] to indeks poczatku slowa
### liczac dp sprawdzamy jednoczesnie czy slowo w ogóle istnieje w słowniku


def split_line(line):
  dp = [-1] * (len(line)+1)
  split = [-1] * (len(line)+1)
  dp[0] = 0
  for i in range(1, len(line)+1):
    for j in range(max(0, i-len(longest_word)), i):
      word = line[j:i]
      if word in words:
        score = len(word)**2 + dp[j]
        if score > dp[i]:
          dp[i] = score
          split[i] = j
  if dp[-1] == -1:
    return None
  return split

def get_words(line):
  result = []
  split = split_line(line)
  if split is None:
    return "Błąd"
  i = len(line)
  while i > 0:
    j = split[i]
    result.append(line[j:i])
    i = j
  return result[::-1]

output = open("zad2_output.txt", "w", encoding='utf-8')
for line in text:
  curr = get_words(line)
  if curr != "Błąd":
    output.write(" ".join(curr) + "\n")
  else:
    output.write("Błąd\n")