import collections

def infixToOnp(infix):
    stack = collections.deque()
    onp = []
    for i in infix:
        i = str(i)
        if i == '(':
            stack.append(i)
        elif i == ')':
            while stack[-1] != '(':
                onp.append(stack.pop())
            stack.pop()
        elif i in '+-':
            while stack and stack[-1] != '(':
                onp.append(stack.pop())
            stack.append(i)
        elif i in '*/':
            while stack and stack[-1] in '*/':
                onp.append(stack.pop())
            stack.append(i)
        else:
            onp.append(i)
    while stack:
        onp.append(stack.pop())
    return onp

def calcONP(onp):
    stack = collections.deque()
    for i in onp:
        if i in '+-*/':
            a = int(stack.pop())
            b = int(stack.pop())
            if i == '+':
                stack.append(b + a)
            elif i == '-':
                stack.append(b - a)
            elif i == '*':
                stack.append(b * a)
            elif i == '/':
                stack.append(b / a)
        else:
            stack.append(i)
    return stack.pop()

print(infixToOnp(['(', 2, '+', 3, ')', '*', 4]))
print(calcONP(infixToOnp(['(', 2, '+', 3, ')', '*', 4])))