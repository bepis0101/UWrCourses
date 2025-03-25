
def opt_dist(bit_list, D):
  n = len(bit_list)
  bit_list = [int(b) for b in bit_list]
  if D == 0:
    return sum(bit_list)

  # zliczamy ile zmian zeby pierwsze okno bylo poprawne    
  changes = sum(1 for i in range(D) if bit_list[i] == 0) + sum(1 for i in range(D, n) if bit_list[i] == 1)
  min_changes = changes
  # updatujemy po drodze
  for i in range(1, n - D + 1):
    if bit_list[i - 1] == 0:
      changes -= 1
    if bit_list[i + D - 1] == 0:
      changes += 1
    if bit_list[i - 1] == 1:
      changes += 1
    if i + D - 1 < n and bit_list[i + D - 1] == 1:
      changes -= 1
    
    # patrzymy czy to jest najlepszy wynik
    min_changes = min(min_changes, changes)
  
  return min_changes


file_in = open("zad4_input.txt", "r")
file_out = open("zad4_output.txt", "w")

input_ = file_in.read().splitlines()
for line in input_:
  bit_list, D = line.split()
  file_out.write(str(opt_dist(bit_list, int(D)))+ "\n")