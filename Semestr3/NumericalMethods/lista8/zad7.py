import matplotlib.pyplot as plt

def lambdak(x, k):
    hk = x[k] - x[k - 1]
    hk1 = x[k + 1] - x[k]
    return hk / (hk + hk1)

def dk(x, y, k):
    # difference quotient f[xk-1, xk, xk+1]
    t1 = (y[k + 1] - y[k]) / (x[k + 1] - x[k])
    t2 = (y[k] - y[k - 1]) / (x[k] - x[k - 1])
    return 6 * (t1 - t2) / (x[k + 1] - x[k - 1])

def moments(t, x, y):
    n = len(t) - 1
    q = [0]
    p = [0]
    ux = [0]
    uy = [0]
    for i in range(1, n):
        lk = lambdak(t, i)
        p.append(lk * q[i - 1] + 2)
        q.append((lk - 1) / p[i])
        dk_ = dk(t, x, i)
        ux.append((dk_ - lk * ux[i - 1])/p[i]) 
        dk_ = dk(t, y, i)
        uy.append((dk_ - lk * uy[i - 1])/p[i])

    Mx, My = [0]*(n+1), [0]*(n+1)
    Mx[n], My[n] = 0, 0
    Mx[n-1], My[n-1] = ux[n-1], uy[n-1]
    for i in range(n-2, -1, -1):
        Mx[i] = ux[i] - q[i] * Mx[i + 1]
        My[i] = uy[i] - q[i] * My[i + 1]

    return Mx, My

def nifs3(X, x0, y0, M):
    k = 1
    while x0[k] < X:
        # print(x0[k], X)
        k += 1

    return (1/(x0[k]-x0[k-1])) * (M[k-1]*pow(x0[k] - X, 3)/6. +  M[k] * pow(X - x0[k-1], 3)/6. + (y0[k-1] - M[k-1]*pow(x0[k]-x0[k-1], 2)/6.)*(x0[k]-X) + (y0[k] - M[k]*pow(x0[k]-x0[k-1], 2)/6.)*(X-x0[k-1]))

def ts(n):
    n-=1
    t = []
    for k in range(n+1):
        t.append(k/n)
    return t

x = [5.5, 8.5, 10.5, 13, 17, 20.5, 24.5, 28, 32.5, 37.5, 40.5, 42.5, 45, 47,
49.5, 50.5, 51, 51.5, 52.5, 53, 52.8, 52, 51.5, 53, 54, 55, 56, 55.5, 54.5, 54, 55, 57, 58.5,
59, 61.5, 62.5, 63.5, 63, 61.5, 59, 55, 53.5, 52.5, 50.5, 49.5, 50, 51, 50.5, 49, 47.5, 46,
45.5, 45.5, 45.5, 46, 47.5, 47.5, 46, 43, 41, 41.5, 41.5, 41, 39.5, 37.5, 34.5, 31.5, 28, 24,
21, 18.5, 17.5, 16.5, 15, 13, 10, 8, 6, 6, 6, 5.5, 3.5, 1, 0, 0, 0.5, 1.5, 3.5, 5, 5, 4.5, 4.5, 5.5,
6.5, 6.5, 5.5]

y =  [41, 40.5, 40, 40.5, 41.5, 41.5, 42, 42.5, 43.5, 45, 47, 49.5, 53, 57, 59,
59.5, 61.5, 63, 64, 64.5, 63, 61.5, 60.5, 61, 62, 63, 62.5, 61.5, 60.5, 60, 59.5, 59, 58.5,
57.5, 55.5, 54, 53, 51.5, 50, 50, 50.5, 51, 50.5, 47.5, 44, 40.5, 36, 30.5, 28, 25.5, 21.5,
18, 14.5, 10.5, 7.50, 4, 2.50, 1.50, 2, 3.50, 7, 12.5, 17.5, 22.5, 25, 25, 25, 25.5, 26.5,
27.5, 27.5, 26.5, 23.5, 21, 19, 17, 14.5, 11.5, 8, 4, 1, 0, 0.5, 3, 6.50, 10, 13, 16.5, 20.5,
25.5, 29, 33, 35, 36.5, 39, 41]

t = ts(len(x))
# print(len(t), len(x), len(y))
# print(t)
Mx, My = moments(t, x, y)

M = 1000

nifsx = []
nifsy = []
for k in range(M+1):
    nifsx.append(nifs3(k/M, t, x, Mx))
    nifsy.append(nifs3(k/M, t, y, My)) 



plt.cla()
plt.plot(nifsx, nifsy)
ax = plt.gca()
ax.set_aspect('equal', adjustable='box')
plt.show()
