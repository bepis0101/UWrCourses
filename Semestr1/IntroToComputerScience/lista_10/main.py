class ListItem:
    def __init__(self, value):
        self.val = value
        self.next = None

def insert_end(list, value):        #zadanie 1
    while list.next != None:
        list = list.next
    list.next = ListItem(value)

def delete_last(list):
    prev = None
    while list.next != None:
        prev = list
        list = list.next
    prev.next = None
    del list

def merge(list1, list2):
    while list1.next != None:
        list1 = list1.next
    list1.next = list2

def delete_val(list, val):
    prev = None
    while list.next != None:
        prev = list
        list = list.next
        if list.val == val:
            prev.next = list.next

def print_list(list):
    while list.next != None:
        print(list.val, end=" ")
        list = list.next
    print(list.val)

def print_inverse_list(list):
    if list.next != None:
        print_inverse_list(list.next)
    print(list.val, end=" ")



lista = ListItem(15)
insert_end(lista, 12)
insert_end(lista, 4)
insert_end(lista, 5)
lista1 = ListItem(10)
insert_end(lista1, 3)
merge(lista, lista1)
print_list(lista)
delete_last(lista)
print_list(lista)
print_inverse_list(lista)