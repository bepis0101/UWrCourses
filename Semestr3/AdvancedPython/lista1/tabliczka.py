## zadanie 1 lista 1
## Borys Adamiak


import decimal

def digits_count(x):
    count = 0
    while x >= 1:
        count += 1
        x /= 10
    return count


def drange(x, y, jump):
  while x <= y:
    yield x
    x += jump

def arr(x1, x2, y1, y2, jump):
    cnt = 3
    cnt += max(digits_count(x2), digits_count(y2))
    after_punctuation = 2
    c = ' '
    print("{0:{1}}".format(c, cnt+2), end="")
    for i in drange(decimal.Decimal(x1), decimal.Decimal(x2), decimal.Decimal(jump)):
        print("{0:{1}.{2}f} ".format(i, cnt, after_punctuation), end="")
    print()
    for i in drange(decimal.Decimal(y1), decimal.Decimal(y2), decimal.Decimal(jump)):
        print("{0:{1}.{2}f}: ".format(i, cnt, after_punctuation), end="")
        for j in drange(decimal.Decimal(x1), decimal.Decimal(x2), decimal.Decimal(jump)):
            print("{0:{1}.{2}f} ".format(i*j, cnt, after_punctuation), end="")
        print()

arr(0.2, 15.3, 0.2, 3.14, 0.7)
print()
arr(1, 10, 1, 10.9, 1)
print()
arr(3.0, 5.0, 2.0, 4.0, 1.0)