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
    for i in range(1, n - 1):
        lk = lambdak(x, i)
        p.append(lk * q[i - 1] + 2)
        q.append((lk - 1) / p[i])
        dk_ = dk(x, y, i)
        ux.append((dk_ - lk * ux[i - 1])/p[i]) 
        uy.append((dk_ - lk * uy[i - 1])/p[i])

    Mx, My = [], []
    Mx[n], My[n] = 0, 0
    Mx[n-1], My[n-1] = ux[n-1], uy[n-1]
    for i in range(n-2, 0, -1):
        Mx[i] = ux[i] - q[i] * Mx[i + 1]
        My[i] = uy[i] - q[i] * My[i + 1]

    return (Mx, My)

def nifs3(X, x0, y0, M):
    k = 1
    while X[k] < x0:
        k += 1
    return (1/(x0[k]-x0[k-1])) * M[k-1] * (x0[k] - X)**3/6 +  M[k] * (X - x0[k-1])**3/6+ (y0[k-1] - M[k-1]*(x0[k]-x0[k-1])**2/6)*(x0[k]-X) + (y0[k] - M[k]*(x0[k]-x0[k-1])**2/6)*(X-x0[k-1])


