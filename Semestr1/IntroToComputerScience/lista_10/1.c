#include "/home/bepis0101/all.h"
typedef struct lista
{
    int value;
    struct lista* next;
    //struct lista* prev;
}lista;

lista* create(int val)
{
    lista* temp = (lista*)malloc(sizeof(lista));
    temp->value = val;
    temp->next = NULL;
    //temp->prev = NULL;
    return temp;
}

lista* insert_begin(lista* list, int val)
{
    lista* new;
    new = create(val);
    new->next = list;
    return new;
}

lista* insert_end(lista* list, int val)
{
    lista* new;
    new = create(val);
    while(list->next != NULL)
    {
        list = list->next;
    }
    list->next = new;
    return list;
}
void delete_last(lista* list)
{
    while(list->next != NULL)
    {
        list = list->next;
    }


}

lista* find_val(lista* list, int val)
{
    while(list != NULL)
    {
        if(list->value == val)
        {
            return list;
        }
        list = list->next;
    }
    return NULL;
}
void write(lista* list)
{
    while(list != NULL)
    {
        printf("%d ", list->value);
        list = list->next;
    }
}
int main()
{
    int x; 
    scanf("%d", &x);
    lista* list = create(x);
    while(x != -1)
    {        
        scanf("%d", &x);
        list = insert_end(list, x);
        write(list);
        printf("\n");
    }
    
}