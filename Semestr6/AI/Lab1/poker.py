import random

class Card:
  def __init__(self, suit, rank):
    self.suit = suit # [0, 1, 2, 3] -> [♠, ♣, ♥, ♦]
    self.rank = rank 
  def __repr__(self):
    return f'[{self.rank} of {self.suit}]'

# below we check the power of the hand

def check_color(cards: list):
  return all(card.suit == cards[0].suit for card in cards)

def check_sequence(cards: list):
  return all(cards[i].rank == cards[i+1].rank+1 for i in range(len(cards)-1))

def check_poker(cards: list):
  return check_color(cards) and check_sequence(cards)

def check_four_of_a_kind(cards: list):
  count = {}
  for card in cards:
    count[card.rank] = count.get(card.rank, 0) + 1
  return 4 in count.values()

def check_full_house(cards: list):
  count = {}
  for card in cards:
    count[card.rank] = count.get(card.rank, 0) + 1
  return 3 in count.values() and 2 in count.values()

def check_three_of_a_kind(cards: list):
  count = {}
  for card in cards:
    count[card.rank] = count.get(card.rank, 0) + 1
  return 3 in count.values()

def check_two_pairs(cards: list):
  count = {}
  for card in cards:
    count[card.rank] = count.get(card.rank, 0) + 1
  return list(count.values()).count(2) == 2

def check_pair(cards: list):
  count = {}
  for card in cards:
    count[card.rank] = count.get(card.rank, 0) + 1
  return 2 in count.values()

def power(cards):
  if check_poker(cards):
    return 9
  if check_four_of_a_kind(cards):
    return 8
  if check_full_house(cards):
    return 7
  if check_color(cards):
    return 6
  if check_sequence(cards):
    return 5
  if check_three_of_a_kind(cards):
    return 4
  if check_two_pairs(cards):
    return 3
  if check_pair(cards):
    return 2
  return 1

# wysoką kartę zawsze wygrywa figurant

def draw_cards(deck):
  return random.sample(deck, 5)

# dodajemy karty kazdego koloru z wybranych figur

def generate_deck(ranks):
  res = []
  for rank in ranks:
    for suit in range(4):
      res.append(Card(suit, rank))
  return res

# symulacja gry i statystyki wygranych

def sim(deck_figurant, deck_blotkarz):
  iterations = 1000
  wins = 0
  for _ in range(iterations):
    figurant = draw_cards(deck_figurant)
    blotkarz = draw_cards(deck_blotkarz)
    if power(figurant) < power(blotkarz):
      wins += 1
  return wins/iterations

# eksperyment z usuwaniem losowych kart z talii

def fully_random_experiment():
  init_figurant = [i for i in range(11, 16)]
  init_blotkarz = [i for i in range(2, 11)]
  number_of_cards = 32
  for i in range(number_of_cards-5):
    sum_ = 0 
    for j in range(100):
      deck_figurant = generate_deck(init_figurant)
      deck_blotkarz = random.sample(generate_deck(init_blotkarz), number_of_cards-i)
      sum_ += sim(deck_figurant, deck_blotkarz)
    print(f'for {number_of_cards-i} cards in deck the avg is: {sum_/100}')

# eksperyment z usuwaniem kart o okreslonych rangach

def removing_rank_experiment():
  init_figurant = [i for i in range(11, 16)]
  init_blotkarz = [i for i in range(2, 11)]
  for i in range(7):
    sum_ = 0
    for j in range(100):
      deck_figurant = generate_deck(init_figurant)
      deck_blotkarz = generate_deck(random.sample(init_blotkarz, 8-i))
      sum_ += sim(deck_figurant, deck_blotkarz)
    print(f'for {i} removed the avg is: {sum_/100}')

def main():
  for i in range(100):
    init_figurant = [i for i in range(11, 16)]
    init_blotkarz = [i for i in range(2, 11)]
    deck_figurant = generate_deck(init_figurant)
    deck_blotkarz = generate_deck(random.sample(init_blotkarz, 3))
    print(deck_blotkarz)
    print(deck_figurant)
    print(sim(deck_figurant, deck_blotkarz))
    print('------------------------------------------\n')


# fully_random_experiment()
removing_rank_experiment()
# main()