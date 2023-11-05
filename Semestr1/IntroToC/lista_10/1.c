#include "/home/bepis0101/all.h"
FILE *input;
#define R 6371000
typedef struct element
{
    float x;
    float y;
    float z;
    char* name;
    element *next;
}element;

element *tworzenie()
{
    element *pom;
    pom = (element*)malloc(sizeof(element));
    return pom;
}

element* dodaj_element(element *aktualny)
{
    element *nastepny = tworzenie();
    aktualny->next = nastepny;
    aktualny->next->next = NULL;
    return aktualny->next;
}


void read(element* lista)
{
    float x, y, z;
    if(fscanf(input, " %f %f %f", &z, &x, &y) != 3) return false;
    element* nastepny = dodaj_element(lista);
    (nastepny->z) = z; (nastepny->x) = x; (nastepny->y) = y;
    char in = fgetc(input);
    while(in == ' ') in = fgetc(input);
    int pointer = 0;
    while(in != '\n')
    {
        *(nastepny->name + pointer) = in;
        pointer++;
        in = fgetc(input);
    }
    *(nastepny->name + pointer) = '\0';

    return 0;
}

void usun_liste(element *lista)
{
    if(lista->next != NULL) lista->next;
    free(lista);
}

int cnt_wierszy()
{
    int wiersze = 0;
    char in = ' ';
    while(!feof(input))
    {
        in = fgetc(input);
        if(in == '\n') wiersze++;
    }
    rewind(input);
    return wiersze;
}
void wypisz(element *lista)
{
    printf("%f %f %f %s\n", lista->z, lista->x, lista->y, lista->name);
}

float dist(element *from, element *to)
{
    float x = R*cos(from->x*M_PI/180.0)*cos(from->y*M_PI/180.0);
    float xd = R*cos(to->x*M_PI/180.0)*cos(to->y*M_PI/180.0);
    float y = R*cos(from->x*M_PI/180.0)*sin(from->y*M_PI/180.0);
    float yd = R*cos(to->x*M_PI/180.0)*sin(to->y*M_PI/180.0);
    float z = R*sin(from->x*M_PI/180.0) + from->z;
    float zd = R*sin(to->x*M_PI/180.0) + to->z;

    return sqrt((x-xd)*(x-xd)+(y-yd)*(y-yd)+(z-zd)*(z-zd));

}

int main(int argc, char** argv)
{
    input = fopen(argv[1], "r");
    int wiersze = cnt_wierszy();
    element *lista = (element*)malloc(sizeof(element));
    element *pointer = lista;
    int count = 0;
    for(int i = 0 i < wiersze; i++)
    {
        if(!read(pointer))
        {
            fscanf(input, "%s", &(pointer->name));
            if(strstr(pointer->name, "KONIEC") != NULL) break;
            else
            {
                char c = fgetc(input);
                while(c != '\n') c = fgetc(input);
                goto loop;
            }
        }

        pointer = pointer->next;
        count++;
        loop:;
    }
    printf("ilosc wczytanych elementow: %d\n", wiersze);

    pointer = lista;
    if(argc == 2)
    {
        while(pointer->next != NULL)
        {
            wypisz(pointer);
            pointer = pointer->next;
        }
    }
    else if(argc == 3)
    {
        while(pointer->next != NULL)
        {
            if(strstr(pointer->name, argv[2]) != NULL)
            {
                wypisz(pointer);   
            }
            pointer = pointer->next;      
        }
    }
    else if(argc == 4 && strcmp(argv[3], "dist") == 0)
    {
        element *pierwszy;
        while(pointer->next != NULL)
        {
            if(strstr(pointer->name, argv[2]) != NULL)
            {
                pierwszy = pointer;
                break;
            }
            pointer = pointer->next;
        }

        printf("distance from ");
        wypisz(pierwszy);
        pointer = lista;
        while(pointer->next != NULL)
        {
            if(pointer == pierwszy)
            {
                pointer = pointer->next;
                continue;
            }
            wypisz(pointer);
            printf(" distance: %f meters\n", dist(pierwszy, pointer));
            pointer = pointer->next;
        }
    }
    
    usun_liste(lista);
    fclose(input);
    
}