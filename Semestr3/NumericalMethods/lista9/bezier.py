import matplotlib.pyplot as plt

controlPoints = [
    (0, 0), (3.5, 36), (25, 25), (25, 1.5), (-5, 3), (-5, 33),
    (15, 11), (-0.5, 35), (19.5, 15.5), (7, 0), (1.5, 10.5)
]

weights = [
    1, 6, 4, 2, 3, 4, 2, 1, 5, 4, 1
]

def factorial(n):
    if n == 0:
        return 1
    return n * factorial(n - 1)

def bezier(n, t, W):
    binom = 1
    mult = 1
    res = binom*W[n]
    for i in range(1, n+1):
        binom *= (n-i+1)/i
        mult *= (1-t)
        res *= t
        res += binom*mult*W[n-i]

    return res

def bezierReal(n, t, W, weights):
    return bezier(n, t, [weights[i]*W[i] for i in range(n+1)])/bezier(n, t, weights)

xs = [x[0] for x in controlPoints]
ys = [y[1] for y in controlPoints]

fig, ax = plt.subplots()
ax.set_aspect('equal')

plt.scatter(xs, ys, color='red')
for i, _ in enumerate(weights):
    ax.annotate(i, (xs[i], ys[i]))

xRes = []
yRes = []
t = 0
precision = 0.001
while t <= 1:
    xRes.append(bezierReal(len(controlPoints)-1, t, xs, weights))
    yRes.append(bezierReal(len(controlPoints)-1, t, ys, weights))
    t += precision

ax.plot(xRes, yRes, color='blue')
plt.show()