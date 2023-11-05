class ListItem:
    def __init__(self, value):
        self.val = value
        self.next = None
        self.prev = None
def insert(list, val):
    while list.next != None:
        list = list.next
    new = ListItem(val)
    new.prev = list
    list.next = new

def pop_front(list):
    list.val = list.next.val
    list.prev = None
    list.next = list.next.next

def pop_back(list):
    while list.next.next != None:
        list = list.next
    list.next = None


def print_list(list):
    while list.next != None:
        print(list.val, end=" ")
        list = list.next
    print(list.val)

L = ListItem(5)
insert(L, 2)
insert(L, 7)
print_list(L)
pop_front(L)
print_list(L)
pop_back(L)
print_list(L)

    