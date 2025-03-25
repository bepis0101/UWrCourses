import random

ROWS = 7
COLS = 7

iters = 10000

pic = [[random.choice([0, 1]) for _ in range(COLS)] for _ in range(ROWS)]
rows = []
cols = []


def check_row(row):
  col = 0
  sum = 0
  while col < COLS and not pic[row][col]:
    col += 1
  while col < COLS and pic[row][col]:
    col += 1
    sum += 1
  while col < COLS and not pic[row][col]:
    col += 1
  if col < COLS:
    return False
  if sum != rows[row]:
    return False
  return True

def check_col(col):
  row = 0
  sum = 0
  while row < ROWS and not pic[row][col]:
    row += 1
  while row < ROWS and pic[row][col]:
    row += 1
    sum += 1
  while row < ROWS and not pic[row][col]:
    row += 1
  if row < ROWS:
    return False
  if sum != cols[col]:
    return False
  return True

def check_rows():
  for row in range(ROWS):
    if not check_row(row):
      return False
  return True

def check_cols():
  for col in range(COLS):
    if not check_col(col):
      return False
  return True

def draw_incorrect_row():
  inc_rows = [row for row in range(ROWS) if not check_row(row)]
  if inc_rows:
    return random.choice(inc_rows)
  return -1

def draw_incorrect_col():
  inc_cols = [col for col in range(COLS) if not check_col(col)]
  if inc_cols:
    return random.choice(inc_cols)
  return -1

def fix_row(row):
  # znajdujemy w którym bloku o chcianej długości jest najwiecej jedynek
  prefix = [0]*ROWS
  len = rows[row]
  maxx = 0
  ptr = 0

  if pic[row][0]: 
    prefix[0] = 1
  for i in range(1, len):
    prefix[i] = prefix[i-1]
    if pic[row][i]: prefix[i] += 1
  maxx = prefix[len-1]
  ptr = len-1

  for i in range(len, ROWS):
    if i > 0: prefix[i] = prefix[i-1]
    if pic[row][i-len]: prefix[i] -= 1
    if pic[row][i]: prefix[i] += 1

    if prefix[i] > maxx:
      maxx = prefix[i]
      ptr = i
  
  for i in range(0, ptr-len+1): pic[row][i] = 0
  for i in range(ptr-len+1, ptr+1): pic[row][i] = 1
  for i in range(ptr+1, ROWS): pic[row][i] = 0
  

def fix_col(col):
  # znajdujemy blok o danej długości, w którym jest najwiecej jedynek
  prefix = [0]*COLS
  len = cols[col]
  maxx = 0
  ptr = 0

  if pic[col][0]: 
    prefix[0] = 1
  for i in range(1, len):
    prefix[i] = prefix[i-1]
    if pic[col][i]: prefix[i] += 1
  maxx = prefix[len-1]
  ptr = len-1

  for i in range(len, COLS):
    if i > 0: prefix[i] = prefix[i-1]
    if pic[col][i-len]: prefix[i] -= 1
    if pic[col][i]: prefix[i] += 1

    if prefix[i] > maxx:
      maxx = prefix[i]
      ptr = i
  
  for i in range(0, ptr-len+1): pic[col][i] = 0
  for i in range(ptr-len+1, ptr+1): pic[col][i] = 1
  for i in range(ptr+1, COLS): pic[col][i] = 0

def try_solve():
  for t in range(iters):
    row = draw_incorrect_row()
    if row != -1:
      fix_row(row)
    
    col = draw_incorrect_col()
    if col != -1:
      fix_col(col)
    
    if check_rows() and check_cols():
      return True, pic
  return False, pic


def print_pic():
  for row in pic:
    for cell in row:
      if cell:
        file_out.write('#')
      else:
        file_out.write('.')
    file_out.write('\n')

file_in = open("zad5_input.txt", "r")
file_out = open("zad5_output.txt", "w")

data = file_in.read().split("\n")

ROWS, COLS = data[0].split()
ROWS, COLS = int(ROWS), int(COLS)

for i in range(1, ROWS+1):
  rows.append(int(data[i]))
for i in range(ROWS+1, ROWS+COLS+1):
  cols.append(int(data[i]))


solved = False
while not solved:
  pic = [[random.choice([0, 1]) for _ in range(COLS)] for _ in range(ROWS)]
  solved, pic = try_solve()

print_pic()