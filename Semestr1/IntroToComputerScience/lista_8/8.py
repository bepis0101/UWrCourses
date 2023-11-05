def hanoi(n, a, c, b):
    if(n == 1):
        s = a + ' ' + c
        print(s)
        return
    hanoi(n-1, a, b, c)
    s = a + ' ' + c
    print(s)
    hanoi(n-1, b, c, a)


n = int(input())
a = '1'
b = '2'
c = '3'
hanoi(n, a, c, b)