#include <stdio.h>
#include <stdbool.h>

typedef struct list
{
    struct list* next; 
    int val;
}list;

list insert(list lista, int val)
{
    list* root = lista;

}

bool** list_to_matrix(list* graph, int n)
{
    bool** temp = (bool**)malloc(n*sizeof(bool*));
    for(int i = 0; i < n; i++)
    {
        temp[i] = (bool*)malloc(n*sizeof(bool));
    }
    for(int i = 0; i < n; i++)
    {
        while(graph[i]->next != NULL)
        {
            temp[i][graph[i]->val] = true;
            temp[graph[i]->val][i] = true;
            graph[i] = graph[i]->next;
        }
        temp[i][graph[i]->val] = true;
        temp[graph[i]->val][i] = true;
    }
    return temp;
}

list* matrix_to_list(bool** matrix, int n)
{
    list* graph = (list*)malloc(n*sizeof(list));
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(matrix[i][j] == true)
            {
                graph[i] = insert(graph[i], j);
            }
        }
    }
}

int main()
{

}