import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np
from random import randint

height = 30
width = 30
numOfFrames = 100
numOfObstacles = height//3

# Inicjalizacja planszy
board = [[0 for _ in range(width)] for _ in range(height)]
fig, ax = plt.subplots()
ax.set_xlim(0, width)
ax.set_ylim(0, height)

# Inicjalizacja węża
snake = [((width//2)+i, height//2) for i in range(3)]
print(snake)
snake_direction = (-1, 0)  # Początkowy kierunek ruchu węża

# Dodanie losowych kwadratów na planszę
for _ in range(numOfObstacles):
    obstacle = (randint(0, width-1), randint(0, height-1))
    board[obstacle[0]][obstacle[1]] = 2
    square = plt.Rectangle(obstacle, 1, 1, fc='red')
    ax.add_patch(square)

# Inicjalizacja głowy węża
for i in range(len(snake)):
    board[snake[i][0]][snake[i][1]] = 1
    body = plt.Rectangle(snake[i], 1, 1, fc='green')
    ax.add_patch(body)

# Funkcja do aktualizacji animacji
def update(frame):
    global snake, snake_direction
    
    # Usunięcie ogona węża
    tail = plt.Rectangle(snake[-1], 1, 1, fc='white')
    board[snake[-1][0]][snake[-1][1]] = 0
    ax.add_patch(tail)
    snake.pop()
    # Dodanie nowej głowy węża
    new_head = (snake[0][0]+snake_direction[0], snake[0][1]+snake_direction[1])
    
    if new_head[0] < 0 or new_head[0] >= width or new_head[1] < 0 or new_head[1] >= height:
        print("Game over you hit the wall")
        plt.close()
        return
    
    board[new_head[0]][new_head[1]] = 1
    snake.insert(0, new_head)
    head = plt.Rectangle(snake[0], 1, 1, fc='green')
    ax.add_patch(head)
    
    # Sprawdzenie czy wąż nie zjadł przeszkody
    
    if ax.patches[0].get_xy() == snake[0] or board[snake[0][0]][snake[0][1]] == 2:
        print("Game over you hit the obstacle")
        plt.close()
        return

    # Sprawdzenie czy wąż nie zjadł samego siebie
    if new_head in snake[1:]:
        print("Game over you hit yourself")
        plt.close()
        return

    dx = randint(-1, 1)
    dy = randint(-1, 1)
    while (dx*dy != 0) or (snake_direction[0] == -dx and dx != 0) or (snake_direction[1] == -dy and dy != 0):
        print(snake_direction, dx, dy)
        if (snake_direction[1] == -dy and dy != 0):
            dy = randint(-1, 1)
        else:
            dx = randint(-1, 1)

    snake_direction = (dx, dy)
    

# Uruchomienie animacji
ani = animation.FuncAnimation(fig, update, frames=numOfFrames, interval=200, repeat=False)
plt.show()
