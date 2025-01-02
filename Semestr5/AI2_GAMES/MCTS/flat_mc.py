import sys
from math import inf
from datetime import datetime
from copy import deepcopy
from random import choice


def calc_miliseconds(start, end):
  return (end-start).microseconds / 1000


# Constants
WIDTH = 8
HEIGHT = 8
DEAD_TILE = 'x'
EMPTY_TILE = '-'

MOVES = {
  'UP': [-1, 0],
  'RIGHT': [0, 1],
  'DOWN': [1, 0],
  'LEFT': [0, -1],
}

def grid_preprocessing(lines):
  grid = [[EMPTY_TILE for j in range(WIDTH)] for i in range(HEIGHT)]
  for y, line in enumerate(lines):
      for x, character in enumerate(line.split(' ')):
        if character <= '1' and character >= '0':
          grid[y][x] = int(character)
        else:
          grid[y][x] = character
  return grid

def grid_to_string(grid):
  return '\n'.join([''.join([str(cell) for cell in row]) for row in grid])


class State:
  def __init__(self, my_id, width, height, grid=[[EMPTY_TILE for j in range(WIDTH)] for i in range(HEIGHT)]):
    self.my_id = my_id
    self.most_left = 0
    self.most_up = 0
    self.width = width
    self.height = height
    self.opp_id = 1 - my_id
    self.grid = grid
    self.my_entities = 32
    self.opp_entities = 32
  
  def move(self, direction):
    if direction == 'UP':
        return self.move_up()
    elif direction == 'RIGHT':
        return self.move_right()
    elif direction == 'DOWN':
        return self.move_down()
    elif direction == 'LEFT':
        return self.move_left()
  
  def cleanup(self):
    self.my_entities = 0
    self.opp_entities = 0
    for y in range(self.most_up, self.height):
      empty_row = True
      for x in range(self.most_left, self.width):
        if self.grid[y][x] == self.my_id:
          empty_row = False
          self.my_entities += 1
        elif self.grid[y][x] == self.opp_id:
          empty_row = False
          self.opp_entities += 1
      if empty_row and (y == self.most_up or self.grid[y-1][0] == DEAD_TILE):
        for x in range(self.most_left, self.width):
          self.grid[y][x] = DEAD_TILE
        self.most_up += 1
    for y in range(self.height-1, self.most_up-1, -1):
      empty_row = True
      for x in range(self.most_left, self.width):
        if self.grid[y][x] == self.my_id or self.grid[y][x] == self.opp_id:
          empty_row = False
      if empty_row and (y == self.height-1 or self.grid[y+1][0] == DEAD_TILE):
        for x in range(self.most_left, self.width):
          self.grid[y][x] = DEAD_TILE
        self.height -= 1
    
    for x in range(self.most_left, self.width):
      empty_col = True
      for y in range(self.most_up, self.height):
        if self.grid[y][x] == self.my_id or self.grid[y][x] == self.opp_id:
          empty_col = False
      if empty_col and (x == self.most_left or self.grid[0][x-1] == DEAD_TILE):
        for y in range(self.most_up, self.height):
          self.grid[y][x] = DEAD_TILE
        self.most_left += 1
    for x in range(self.width-1, self.most_left-1, -1):
      empty_col = True
      for y in range(self.most_up, self.height):
        if self.grid[y][x] == self.my_id or self.grid[y][x] == self.opp_id:
          empty_col = False
      if empty_col and (x == self.width-1 or self.grid[0][x+1] == DEAD_TILE):
        for y in range(self.most_up, self.height):
          self.grid[y][x] = DEAD_TILE
        self.width -= 1
        
    
    
  def move_up(self):
    grid_cp = [[DEAD_TILE for j in range(WIDTH)] for i in range(HEIGHT)]
    for x in range(self.most_left, self.width):
      is_pushing = False
      for y in range(self.height-1, self.most_up-1, -1):
        if not is_pushing and self.grid[y][x] == self.my_id:
          is_pushing = True
          grid_cp[y][x] = EMPTY_TILE
        elif not is_pushing and self.grid[y][x] != self.my_id:
          grid_cp[y][x] = self.grid[y][x]
        elif is_pushing and self.grid[y][x] == EMPTY_TILE:
          is_pushing = False
          grid_cp[y][x] = self.grid[y+1][x]
        else:
          grid_cp[y][x] = self.grid[y+1][x]
    self.grid = deepcopy(grid_cp)
    self.cleanup()


  def move_down(self):
    grid_cp = [[DEAD_TILE for j in range(WIDTH)] for i in range(HEIGHT)]
    for x in range(self.most_left, self.width):
      is_pushing = False
      for y in range(self.most_up, self.height):
        if not is_pushing and self.grid[y][x] == self.my_id:
          is_pushing = True
          grid_cp[y][x] = EMPTY_TILE
        elif not is_pushing and self.grid[y][x] != self.my_id:
          grid_cp[y][x] = self.grid[y][x]
        elif is_pushing and self.grid[y][x] == EMPTY_TILE:
          is_pushing = False
          grid_cp[y][x] = self.grid[y-1][x]
        else:
          grid_cp[y][x] = self.grid[y-1][x]
    self.grid = deepcopy(grid_cp)
    self.cleanup()

  def move_right(self):
    grid_cp = [[DEAD_TILE for j in range(WIDTH)] for i in range(HEIGHT)]
    for y in range(self.most_up, self.height):
      is_pushing = False
      for x in range(self.most_left, self.width):
        if not is_pushing and self.grid[y][x] == self.my_id:
          is_pushing = True
          grid_cp[y][x] = EMPTY_TILE
        elif not is_pushing and self.grid[y][x] != self.my_id:
          grid_cp[y][x] = self.grid[y][x]
        elif is_pushing and self.grid[y][x] == EMPTY_TILE:
          is_pushing = False
          grid_cp[y][x] = self.grid[y][x-1]
        else:
          grid_cp[y][x] = self.grid[y][x-1]
    self.grid = deepcopy(grid_cp)
    self.cleanup()

  def move_left(self):
    grid_cp = [[DEAD_TILE for j in range(WIDTH)] for i in range(HEIGHT)]
    for y in range(HEIGHT):
      is_pushing = False
      for x in range(self.width-1, self.most_left-1, -1):
        if not is_pushing and self.grid[y][x] == self.my_id:
          is_pushing = True
          grid_cp[y][x] = EMPTY_TILE
        elif not is_pushing and self.grid[y][x] != self.my_id:
          grid_cp[y][x] = self.grid[y][x]
        elif is_pushing and self.grid[y][x] == EMPTY_TILE:
          is_pushing = False
          grid_cp[y][x] = self.grid[y][x+1]
        else:
          grid_cp[y][x] = self.grid[y][x+1]
    self.grid = deepcopy(grid_cp)
    self.cleanup()

  def play_opp(self):
    action = choice(['UP', 'RIGHT', 'DOWN', 'LEFT'])
    self.my_id, self.opp_id = self.opp_id, self.my_id
    self.my_entities, self.opp_entities = self.opp_entities, self.my_entities
    self.move(action)
    self.my_id, self.opp_id = self.opp_id, self.my_id
    self.my_entities, self.opp_entities = self.opp_entities, self.my_entities

  def is_terminal(self):
    return self.my_entities == 0 or self.opp_entities == 0
  

def sim(root, action):
  s = deepcopy(root)
  while not s.is_terminal():
    s.move(action)
    s.play_opp()
    action = choice(['UP', 'RIGHT', 'DOWN', 'LEFT'])
  if s.my_entities == 0 and s.opp_entities == 0:
    return 50
  if s.my_entities == 0:
    return 100
  return 0



def flat_mc(root):
  start = datetime.now()
  score = {}
  visits = {}
  s = deepcopy(root)
  while calc_miliseconds(start, datetime.now()) < 100:
    action = choice(['UP', 'RIGHT', 'DOWN', 'LEFT'])
    if action not in score:
      score[action] = 0
    if action not in visits:
      visits[action] = 0
    visits[action] += 1
    score[action] += sim(s, action)
  best_avg = -inf
  best_action = None
  for action in score:
    avg = score[action] / visits[action]
    if avg > best_avg:
      best_avg = avg
      best_action = action
  return best_action
    
    



# # Try to survive by not falling off

my_id = int(input())  # Your id, 0 or 1
height = int(input())  # height of the grid
width = int(input())  # width of the grid

state = State(my_id, width, height)

# # game loop
while True:
  lines = []
  for i in range(height):
    line = input()  # string describing tiles of a line of the grid containing values: 0 or 1: player with this id, '-': empty, 'x': hole
    lines.append(line)
  state.grid = grid_preprocessing(lines)

  # Write an action using print
  # To debug: print("Debug messages...", file=sys.stderr, flush=True)

  # UP | RIGHT | DOWN | LEFT

  print(flat_mc(state))
