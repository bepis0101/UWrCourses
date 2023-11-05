class ListItem:
    def __init__(self, val):
        self.value = val
        self.next = None

def insert_end(list, value):
    while list.next != None:
        list = list.next
    list.next = ListItem(value)
def print_list(list):
    while list.next != None:
        print(list.val, end=" ")
        list = list.next
    print(list.val)
    
def matrix_to_list(matrix, list, n):
    for i in range(n):
        root = list[i]
        for j in range(n):
            if matrix[i][j] == 1:
                list[i] = insert_end(list[i], j)
        list[i] = root
    return list

def list_to_matrix(matrix, list, n):
    for i in range(n):
        while list[i].next != None:
            matrix[i][list[i].val] = 1
            matrix[list[i].val][i] = 1
            list[i] = list[i].next
        matrix[i][list[i].val] = 1
        matrix[list[i].val][i] = 1
        

            