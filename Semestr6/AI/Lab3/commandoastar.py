from heapq import heappop, heappush

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

def bfs_goal_distances(goal_positions, board, rows, cols):
  goal_distance = [[float('inf')] * cols for _ in range(rows)]
  queue = [(y, x, 0) for y, x in goal_positions]
  
  for y, x in goal_positions:
    goal_distance[y][x] = 0
  
  while queue:
    y, x, d = queue.pop(0)
    for dy, dx in moves.values():
      ny, nx = y + dy, x + dx
      if is_move_safe((ny, nx)) and goal_distance[ny][nx] == float('inf'):
        goal_distance[ny][nx] = d + 1
        queue.append((ny, nx, d + 1))
  
  return goal_distance

def heuristic(positions, goal_distance, alpha=1):
  return max(goal_distance[y][x] for y, x in positions) / alpha

def a_star(starting_positions, goal_positions, board, rows, cols):
  goal_distance = bfs_goal_distances(goal_positions, board, rows, cols)
  
  pq = [(heuristic(starting_positions, goal_distance), "", starting_positions)]
  visited = {frozenset(starting_positions)}
  
  while pq:
    _, path, positions = heappop(pq)
    
    if all(pos in goal_positions for pos in positions):
      return path
    
    for direction in moves:
      new_positions = make_move(positions, direction)
      if frozenset(new_positions) not in visited:
        visited.add(frozenset(new_positions))
        heappush(pq, (len(path) + 1 + heuristic(new_positions, goal_distance), path + direction, new_positions))


def main():
  board, starting_positions, goal_positions, rows, cols = read_input()
  path, new_state = make_random_moves(starting_positions, 10)
  path = path + a_star(new_state, goal_positions, board, rows, cols)
  with open("zad_output.txt", "w") as f:
    f.write(path)

if __name__ == "__main__":
  main()