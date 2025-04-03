from heapq import heappop, heappush

def read_input():
  with open("zad_input.txt", "r") as f:
    lines = f.read().splitlines()
  
  rows = len(lines)
  cols = len(lines[0])
  board = [[False for _ in range(cols)] for _ in range(rows)]
  starting_positions = set()
  goal_positions = set()

  for y, line in enumerate(lines):
    for x, char in enumerate(line):
      match char:
        case 'B':
          starting_positions.add((y, x))
          goal_positions.add((y, x))
        case 'G':
          goal_positions.add((y, x))
        case 'S':
          starting_positions.add((y, x))
        case '#':
          board[y][x] = True
  
  return board, starting_positions, goal_positions, rows, cols

def is_safe(y, x, rows, cols):
  return 0 <= y < rows and 0 <= x < cols

def is_available(y, x, board):
  return is_safe(y, x, len(board), len(board[0])) and not board[y][x]

moves = {
  'L': (0, -1),
  'R': (0, 1),
  'U': (-1, 0),
  'D': (1, 0),
}

def move(position, direction, board):
  y, x = position
  dy, dx = moves[direction]
  new_y, new_x = y + dy, x + dx
  return (new_y, new_x) if is_available(new_y, new_x, board) else (y, x)

def make_move(positions, direction, board):
  return {move(pos, direction, board) for pos in positions}

def bfs_goal_distances(goal_positions, board, rows, cols):
  goal_distance = [[float('inf')] * cols for _ in range(rows)]
  queue = [(y, x, 0) for y, x in goal_positions]
  
  for y, x in goal_positions:
    goal_distance[y][x] = 0
  
  while queue:
    y, x, d = queue.pop(0)
    for dy, dx in moves.values():
      ny, nx = y + dy, x + dx
      if is_available(ny, nx, board) and goal_distance[ny][nx] == float('inf'):
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
      with open("zad_output.txt", "w") as f:
        f.write(path)
      return
    
    for direction in moves:
      new_positions = make_move(positions, direction, board)
      if frozenset(new_positions) not in visited:
        visited.add(frozenset(new_positions))
        heappush(pq, (len(path) + 1 + heuristic(new_positions, goal_distance), path + direction, new_positions))

def main():
  board, starting_positions, goal_positions, rows, cols = read_input()
  a_star(starting_positions, goal_positions, board, rows, cols)

if __name__ == "__main__":
  main()