from collections import deque as Queue
import random


def read_input():
  PATH = 'zad_input.txt'
  with open(PATH, 'r') as f:
    lines = f.read().splitlines()
    ROWS = len(lines)
    COLS = len(lines[0])
  mapa = [['#' for _ in range(COLS)] for _ in range(ROWS)]
  starting_positions = set()
  goal_positions = set()
  for i, line in enumerate(lines):
    for j, char in enumerate(line):
      match char:
        case ' ':
          mapa[i][j] = 1
        case '#':
          mapa[i][j] = 0
        case 'B':
          starting_positions.add((i, j))
          goal_positions.add((i, j))
        case 'G':
          goal_positions.add((i, j))
        case 'S':
          starting_positions.add((i, j))

  return mapa, starting_positions, goal_positions, ROWS, COLS


mapa, starting_positions, goal_positions, ROWS, COLS = read_input()

moves = {
  'U': (-1, 0),
  'D': (1, 0),
  'L': (0, -1),
  'R': (0, 1),
}

def is_move_safe(move):
  y, x = move
  if y < 0 or y >= ROWS or x < 0 or x >= COLS:
    return False
  if mapa[y][x] == 0:
    return False
  return True

def make_move(state, dir):
  new_state = set()
  for agent in state:
    y, x = agent
    dy, dx = moves[dir]
    new_agent = (y + dy, x + dx)
    if is_move_safe(new_agent):
      new_state.add(new_agent)
    else:
      new_state.add(agent)
  return new_state

def is_goal(state):
  return sorted(state) == sorted(goal_positions)

def make_random_moves(start_state, count_moves):
  path = ""
  for i in range(count_moves):
    move = random.choice(list(moves.keys()))
    path += move
    start_state = make_move(start_state, move)
  return path, start_state

def bfs(start_state):
  q = Queue()
  visited = set()
  q.append((start_state, ""))
  visited.add(tuple(start_state))
  while q:
    state, path = q.popleft()
    if is_goal(state):
      return state, path
    for move in moves.keys():
      new_state = make_move(state, move)
      if tuple(new_state) not in visited:
        visited.add(tuple(new_state))
        q.append((new_state, path + move))
  return False, ""

res = False
path1 = ""
path2 = ""
while not res:
  state = starting_positions.copy()
  max_agents = 2
  iterations = 0
  while len(state) > max_agents:
    path1, state = make_random_moves(starting_positions, 80)
    iterations += 1
    if iterations > 100: max_agents = 3
  res, path2 = bfs(state)
  if res:
    break

output_path = "zad_output.txt"
with open(output_path, "w") as output:
  output.write(path1 + path2)