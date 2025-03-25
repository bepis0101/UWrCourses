import re
import random
PATH = "pan_tadeusz.txt"
FILE = open(PATH, encoding='utf-8',mode="r")
TEXT = FILE.read().split('\n')
data = []
for line in TEXT:
  if line == '':
    continue
  cleaned = re.sub(r'[^\w\s]', '', line)
  cleaned = cleaned.replace('    ', '')
  cleaned = cleaned.lower()
  data.append(cleaned)


PATH2 = "pan_tadeusz_algo.txt"
FILE2 = open(PATH2, encoding='utf-8',mode="r")
TEXT2 = FILE2.read().split('\n')
data2 = []
for line in TEXT2:
  data2.append(line)

print(len(data2) == len(data))

correct_lines = 0

for i in range(len(data)):
  if data[i] == data2[i]:
    correct_lines += 1

print(correct_lines / len(data))

PATH3 = "pan_tadeusz_compressed.txt"
FILE3 = open(PATH3, encoding='utf-8',mode="r")
TEXT3 = FILE3.read().split('\n')
data3 = TEXT3

PATH4 = "words_for_ai1.txt"
FILE4 = open(PATH4, encoding='utf-8',mode="r")
TEXT4 = FILE4.read().split('\n')
data4 = TEXT4


def split_line(line):
  parts = []
  while not all(part in data4 for part in parts) or len(parts) == 0:
    indices = sorted(random.sample(range(0, len(line)), random.randint(0, min(50, len(line)))))
    parts = []
    start = 0
    for i in indices:
      parts.append(line[start:i])
      start = i
    parts.append(line[start:])
  return parts

correct_lines = 0
for i in range(len(data3)):
  parts = split_line(data3[i])
  print(i)
  if ''.join(parts) == data3[i]:
    correct_lines += 1

print(correct_lines / len(data3))

