#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>




void Print_List1(void){
    printf("[1]Load\n");
    printf("[2]New single player game\n");
    printf("[3]New Multiplayer game\n");
    printf("[4]Exit\n");
}

struct node{
    char name[50];
    int x;
    int y;
    struct node* next;
};

struct node* create_node(int i, int j,  char name_of_cell[],int size){
    struct node* nn;
    nn = (struct node*) malloc(sizeof(struct node));
    if(nn == NULL){
        printf("cannot allocate memory.");
        return NULL;
    }

    for(int k=0; k<strlen(name_of_cell); k++){
        nn->name[k] = name_of_cell[k];
    }
    nn->name[strlen(name_of_cell)] = '\0';
    nn->x = i;
    nn->y = j;
    nn->next = NULL;
    return nn;
};

void add_end(struct node* list, struct node* new_node){
    struct node* current;
    for(current = list; current->next != NULL; current = current->next);
    current->next = new_node;
    new_node->next = NULL;
}

int found(int a, int b, struct node* list){
    struct node* current;
    for(current = list; current->next != NULL; current = current->next){
        if(current->x == a && current->y == b)
            return 1;
    }

    return 0;
}


void print_List(struct node* list){
    struct node* current = list;
    while(current != NULL){
        printf("%s\n", current->name);
        printf("%d  ", current->x);
        printf("%d\n", current->y);
        current = current->next;
    }
}

char find(int x, int y, FILE *f) {
    unsigned int n;
    unsigned char c;
    f = fopen("c:\\mapp.bin", "rb");
    if (f == NULL) {
        printf("cannot open the file.");
        return NULL;
    }
    fread(&n, sizeof(n), 1, f);
    for (int i = 1; i < n - y; i++) {
        for (int j = 0; j < n; j++) {
            fread(&c, sizeof(c), 1, f);
        }
    }
    for (int i = 0; i < x; i++) {
        fread(&c, sizeof(c), 1, f);
    }
    fread(&c, sizeof(c), 1, f);
    fclose(f);
    return c;
}

int number_of_map(FILE *f){
    unsigned int n;
    f = fopen("c:\\mapp.bin", "rb");
    fread(&n, sizeof(n), 1, f);
    fclose(f);
    return  n;
}

struct blocks_of_map{
    int x;
    int y;
    int num;
    char type;
    int Energy;
};


int main(){
    bool flag = true;
    int number_of_choice;
    FILE *f;
    int n = number_of_map(f);
    struct blocks_of_map Block[n*n];
    int cnt = 0;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            Block[cnt].y = n-i-1;
            Block[cnt].x = n-j-1;
            Block[cnt].num = 0;
            Block[cnt].type = find(n-j-1, n-i-1, f);
            if(Block[cnt].type == '1')
                Block[cnt].Energy = 100;
            else
                Block[cnt].Energy = 0;
        }
    }

    Print_List1();
    scanf("%d", &number_of_choice);
    struct node* cell;
    struct node* cell1;
    struct node* cell2;

    if(number_of_choice == 2){
        int number_of_cells;
        scanf("%d", &number_of_cells);
        srand(time(NULL));
        int x = rand() % n;
        int y = rand() % n;
        char name[50];
        getchar();
        gets(name);
        if(find(x, y, f) == '3'){
            cell = create_node(x, y, name, strlen(name));
         }
        for(int i=0; i<number_of_cells-1; i++){
            x = rand() % n;
            y = rand() % n;

            if(found(x, y, cell) == 1 ){
                i--;
                continue;
            }
            gets(name);
            add_end(cell, create_node(x, y, name, strlen(name)));
        }
    }

    if(number_of_choice == 3){
        int number_of_cells1;
        scanf("%d", &number_of_cells1);
        srand(time(NULL));
        int x = rand() % n;
        int y = rand() % n;
        getchar();
        char name[50];
        gets(name);
        //if(){
        cell1 = create_node(x, y, name, sizeof(name));
        //}
        for(int i=0; i<number_of_cells1-1; i++){
            x = rand() % n;
            y = rand() % n;
            gets(name);
            if(found(x, y, cell1) == 1  ){
                i--;
                continue;
            }
            add_end(cell1, create_node(x, y, name, sizeof(name)));

        }

        int number_of_cells2;
        scanf("%d", &number_of_cells2);
        srand(time(NULL));
        x = rand() % n;
        y = rand() % n;

        getchar();
        gets(name);
        //if(){
        cell2 = create_node(x, y, name, sizeof(name));
        //}
        for(int i=0; i<number_of_cells2-1; i++){
            x = rand() % n;
            y = rand() % n;
            gets(name);
            if(found(x, y, cell2) == 1 ){
                i--;
                continue;
            }
            add_end(cell2, create_node(x, y, name, sizeof(name)));
        }
    }

    print_List(cell1);
    printf("\n\n");
    print_List(cell2);

    return 0;

}
