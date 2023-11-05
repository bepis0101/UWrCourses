def sudan(n, x, y):
    if n == 0:
        return x + y
    if y == 0:
        return x
    else:
        return sudan(n - 1, sudan(n, x, y - 1), sudan(n, x, y - 1) + y)
    

memo = {}

def sudan_memo(n, x, y):
    if n == 0:
        return x + y
    if (n, x, y) in memo:
        return memo[(n, x, y)]
    
    if y == 0:
        memo[(n, x, y)] = x
        return x
    else:
        result = sudan(n - 1, sudan(n, x, y - 1), sudan(n, x, y - 1) + y)
    
    memo[(n, x, y)] = result
    return result


print(f'{sudan(0, 1, 1)}')
print(f'{sudan(1, 1, 1)}')
print(f'{sudan(2, 1, 1)}')
print(f'{sudan(2, 1, 2)}')

print(f'{sudan_memo(0, 1, 1)}')
print(f'{sudan_memo(1, 1, 1)}')
print(f'{sudan_memo(2, 1, 1)}')
print(f'{sudan_memo(2, 1, 2)}')
print(f'{sudan_memo(2, 2, 2)}')
# print(f'{sudan_memo(3, 1, 2)}') tego juz nie wylicza