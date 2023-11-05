## zadanie 4 lista 1
## Borys Adamiak

import decimal
from math import pi
from math import isclose
import random

def ifHit(x, y):
    if x*x + y*y <= decimal.Decimal(1):
        return True
    return False

numberOfHits = 100000000
hitsOnTarget = 0

for i in range(1, numberOfHits+1):
    x = decimal.Decimal(random.uniform(-1, 1))
    y = decimal.Decimal(random.uniform(-1, 1))
    if ifHit(x, y):
        # print('Pi = ', 4*hitsOnTarget/i)
        hitsOnTarget += 1
    if isclose(pi, 4*hitsOnTarget/i, rel_tol=1e-7):
        print('Number of hits: ', i)
        print('Pi = ', 4*hitsOnTarget/i)
        print('Built in Pi = ', pi)
        break
