from collections import deque

def max_sublist_sum(ls):
    global_max = float('-inf')
    max_curr = 0
    start = 0
    end = 0
    s = 0
    for i in range(0, len(ls)):
        max_curr += ls[i]

        if global_max < max_curr:
            global_max = max_curr
            start = s
            end = i
        if max_curr < 0:
            max_curr = 0
            s = i + 1
    return (global_max, start, end)
    
print(max_sublist_sum([-2, -3, 4, -1, -2, 1, 5, -3]))