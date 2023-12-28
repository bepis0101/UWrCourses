import matplotlib.pyplot as plt
import points as p 

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
        Mx[i] = ux[i] + q[i] * Mx[i + 1]
        My[i] = uy[i] + q[i] * My[i + 1]

    return Mx, My

def nifs3(X, x0, y0, M):
    k = 1
    while x0[k] < X:
        k += 1

    return (1/(x0[k]-x0[k-1])) * (M[k-1]*pow(x0[k] - X, 3)/6. +  M[k] * pow(X - x0[k-1], 3)/6. + (y0[k-1] - M[k-1]*pow(x0[k]-x0[k-1], 2)/6.)*(x0[k]-X) + (y0[k] - M[k]*pow(x0[k]-x0[k-1], 2)/6.)*(X-x0[k-1]))

def ts(n):
    n-=1
    t = []
    for k in range(n+1):
        t.append(k/n)
    return t

def _unzip(l):
    return [x[0] for x in l], [x[1] for x in l], ts(len(l))

def nifss(t, x, y, M):
    Mx, My = moments(t, x, y)
    nifs3x = []
    nifs3y = []
    for k in range(M+1):
        nifs3x.append(nifs3(k/M, t, x, Mx))
        nifs3y.append(nifs3(k/M, t, y, My))
    return nifs3x, nifs3y


x, y, t = _unzip(p.N)
nifs3x, nifs3y = nifss(t, x, y, 500)
plt.plot(x, y, 'o', nifs3x, nifs3y)


x, y, t = _unzip(p.u)
nifs3x, nifs3y = nifss(t, x, y, 500)
plt.plot(x, y, 'o', nifs3x, nifs3y)

x, y, t = _unzip(p.m)
nifs3x, nifs3y = nifss(t, x, y, 500)
plt.plot(x, y, 'o', nifs3x, nifs3y)

x, y, t = _unzip(p.er)
nifs3x, nifs3y = nifss(t, x, y, 1000)
plt.plot(x, y, 'o', nifs3x, nifs3y)

x, y, t = _unzip(p.ki)
nifs3x, nifs3y = nifss(t, x, y, 1000)
plt.plot(x, y, 'o', nifs3x, nifs3y)

x, y, t = _unzip(p.i)
nifs3x, nifs3y = nifss(t, x, y, 2)
plt.plot(x, y, 'o', nifs3x, nifs3y)

x, y, t = _unzip(p.s)
nifs3x, nifs3y = nifss(t, x, y, 300)
plt.plot(x, y, 'o', nifs3x, nifs3y)

x, y, t = _unzip(p.a)
nifs3x, nifs3y = nifss(t, x, y, 500)
plt.plot(x, y, 'o', nifs3x, nifs3y)

x,y,t = _unzip(p.su)
nifs3x, nifs3y = nifss(t, x, y, 1000)
plt.plot(x, y, 'o', nifs3x, nifs3y)

x,y,t = _unzip(p.p)
nifs3x, nifs3y = nifss(t, x, y, 500)
plt.plot(x, y, 'o', nifs3x, nifs3y)

x,y,t = _unzip(p.er1)
nifs3x, nifs3y = nifss(t, x, y, 1000)
plt.plot(x, y, 'o', nifs3x, nifs3y)

x, y, t = _unzip(p.dotup)
nifs3x, nifs3y = nifss(t, x, y, 4)
plt.plot(x, y, 'o', nifs3x, nifs3y)

x, y, t = _unzip(p.dotdown)
nifs3x, nifs3y = nifss(t, x, y, 4)
plt.plot(x, y, 'o', nifs3x, nifs3y)

x, y, t = _unzip(p.nose)
nifs3x, nifs3y = nifss(t, x, y, 2)
plt.plot(x, y, 'o', nifs3x, nifs3y)

x, y, t = _unzip(p.smile)
nifs3x, nifs3y = nifss(t, x, y, 300)
plt.plot(x, y, 'o', nifs3x, nifs3y)

im = plt.imread('C:/Users/borys/Desktop/UWr/Semestr3/NumericalMethods/konkurs/napis.png')
plt.imshow(im)
plt.show()