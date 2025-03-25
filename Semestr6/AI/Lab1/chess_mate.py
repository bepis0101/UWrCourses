from collections import deque


file_in = open('zad1_input.txt', 'r', encoding='utf-8')
file_out = open('zad1_output.txt', 'w', encoding='utf-8')

text = file_in.read().split('\n')

board = [['.' for __ in range (8)] for _  in range(8)]

def get_params(line):
  move, white_king, white_rook, black_king = line.split()
  return move, white_king, white_rook, black_king

def get_pos(pos):
  return [ord(pos[0])-ord('a'), 8-int(pos[1])]

def get_pos_rev(pos):
  x, y = pos
  return chr(x+ord('a')) + str(8-y)

def get_board(white_king, white_rook, black_king):
  board = [['.' for _ in range(8)] for _ in range(8)] 
  white_king = get_pos(white_king)
  white_rook = get_pos(white_rook)
  black_king = get_pos(black_king)
  board[white_king[1]][white_king[0]] = 'K'
  board[black_king[1]][black_king[0]] = 'k'
  board[white_rook[1]][white_rook[0]] = 'R'
  return board

def print_board(board):
  for row in board:
    print(' '.join(row))

def get_legal_king(king):
  king = get_pos(king)
  x, y = king
  legal = [[x+dx, y+dy] for dx in range(-1, 2) for dy in range(-1, 2) if dx or dy]
  return [[nx, ny] for nx, ny in legal if nx >= 0 and nx < 8 and ny >= 0 and ny < 8]

def get_legal_rook(rook):
  rook = get_pos(rook)
  x, y = rook
  legal = []
  for i in range(x+1, 8):
    if board[y][i] == '.':
      legal.append([i, y])
    else:
      break
  for i in range(x-1, -1, -1):
    if board[y][i] == '.':
      legal.append([i, y])
    else:
      break
  for i in range(y+1, 8):
    if board[i][x] == '.':
      legal.append([x, i])
    else:
      break
  for i in range(y-1, -1, -1):
    if board[i][x] == '.':
      legal.append([x, i])
    else:
      break
  return legal


def is_checkmate(wk, wr, bk):
  legal_king = get_legal_king(bk)
  legal_rook = get_legal_rook(wr)
  return all(move in legal_rook or move == get_pos(wk) for move in legal_king)


parents = {}

def register_transition(previous, current, move_desc):
  parents[current] = (previous, move_desc)

def reconstruct_moves(state):
  moves = []
  while state in parents:
    state, description = parents[state]
    moves.append(description)
  moves.reverse()
  return moves

def bfs(move, wk, wr, bk):
  q = deque()
  q.append((move, wk, wr, bk, 0))
  visited = set()
  while q:
    move, wk, wr, bk, moves = q.popleft()
    if is_checkmate(wk, wr, bk):
      return moves
    if (wk,wr,bk) in visited:
      continue
    visited.add((wk,wr,bk))
    if move == 'white':
      legal_king = get_legal_king(wk)
      legal_rook = get_legal_rook(wr)
      for move in legal_king:
        if move not in legal_rook:
          q.append(('black', get_pos_rev(move), wr, bk, moves+1))
      for move in legal_rook:
        if move != wk:
          q.append(('black', wk, get_pos_rev(move), bk, moves+1))
    else:
      legal_king = get_legal_king(bk)
      for move in legal_king:
        if move != wr:
          q.append(('white', wk, wr, get_pos_rev(move), moves+1))    
  return -1

file_in = open('zad1_input.txt', 'r', encoding='utf-8')
file_out = open('zad1_output.txt', 'w', encoding='utf-8')

text = file_in.read().split('\n')

for line in text:
  if not line:
    continue
  move, white_king, white_rook, black_king = get_params(line)
  board = get_board(white_king, white_rook, black_king)
  result = bfs(move, white_king, white_rook, black_king)
  file_out.write(str(result) + '\n')