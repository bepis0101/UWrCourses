class ListItemImproved:
    def __init__(self, value):
        self.val = value
        self.next = None
        self.last = self

def insert_front(list, value):
    L = ListItemImproved(list.val)
    list.val = value
    L.next = list.next
    list.next = L

def insert_back(list, value):
    L = ListItemImproved(value)
    list.last.next = L
    list.last = L

#def merge(list1, list2):

def pop_front(list):
    list.val = list.next.val
    list.next = list.next.next

def print_list(list):
    while list.next != None:
        print(list.val, end=" ")
        list = list.next
    print(list.val)

L = ListItemImproved(5)
insert_front(L, 4)
insert_front(L, 7)
insert_front(L, 1)
print_list(L)