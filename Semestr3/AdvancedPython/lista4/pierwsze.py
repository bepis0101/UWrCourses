import timeit

def primaryImperative(n: int) -> list:
    primary = []
    for i in range(2, n+1):
        isPrimary = True
        for j in range(2, i):
            if i % j == 0:
                isPrimary = False
                break
        if isPrimary:
            primary.append(i)
    return primary

def primaryComprehension(n: int) -> list:
    return [i for i in range(2, n+1) if all(i % j != 0 for j in range(2, i))]

def primaryFunctional(n: int) -> list:
    return list(filter(lambda x: all(x % i != 0 for i in range(2, x)), range(2, n+1)))


def measureFunction(func, n):
    start = timeit.default_timer()
    func(n)
    end = timeit.default_timer()
    return end - start

def makeTable():
    print('{:<5} {:<15} {:<15} {:<15}'.format('n', 'Imperative', 'Comprehension', 'Functional'))
    for i in range(0, 101, 10):
        print('{:<5} {:<15} {:<15} {:<15}'.format(i, round(measureFunction(primaryImperative, i), 6), round(measureFunction(primaryComprehension, i), 6), round(measureFunction(primaryFunctional, i), 6)))

makeTable()