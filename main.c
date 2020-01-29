#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

void Print_List1(void){
    printf("[1]Load\n");
    printf("[2]New single  game\n");
    printf("[3]New Multi game\n");
    printf("[4]Exit\n");
}

struct node{                            //struct of cells.
    char name[50];
    int x;
    int y;
    int energy;
    struct node* next;
};

struct node* create_node(int i, int j, int sum, char name_of_cell[],int size){              //sum = energy of cell;
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
    nn->energy = sum;
    nn->next = NULL;
    return nn;
};

void add_end(struct node* list, struct node* new_node){
    struct node* current;
    for(current = list; current->next != NULL; current = current->next);
    current->next = new_node;
    new_node->next = NULL;
}

int found(int a, int b, struct node* list){                     //understand that block is empty.
    struct node* current;
    for(current = list; current != NULL; current = current->next){
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
        printf("%d\n", current->energy);
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
    //sscanf(c, "%d", a);
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

struct blocks_of_map{                               //struct of block.
    int x;
    int y;
    int num;
    char type;
    int Energy;
};

void initial(struct blocks_of_map* F, int n, int i, FILE *f){
    int a = i % n;
    int b = i / n;
    F->y = n-b-1;
    F->x = a;
    F->num = 0;
    F->type = find(a, n-i-1, f);
    if(F->type == '1')
        F->Energy = 100;
    else
        F->Energy = 0;


}

void Print_map_one_player(int n, struct node* list, char c_list){
    struct node* current = NULL;

    for(int i = 0 ; i < n ; ++i) {

        printf("|");
        for (int j = n-1 ; j > -1 ; --j) {
            int p = 0;
            for(current = list; current != NULL; current = current->next) {
                if (current->x == n-1-i && current->y == n-1-j) {
                    p++;
                    break;
                }
            }
            if(p == 1 )
                printf(" %c |", c_list);
            if(p == 0 )
                printf("...|");
        }
        printf("\n");
    }
}

void Print_map_tow_players(int n, struct node* list1, struct node* list2, char c_list1, char c_list2){
    struct node* current1 = NULL;
    struct node* current2 = NULL;
    for(int i = 0 ; i < n ; ++i) {

        printf("|");
        for (int j = n-1 ; j > -1 ; --j) {
            int q = 0;
            int p = 0;
            for(current1 = list1; current1 != NULL; current1 = current1->next) {
                if (current1->x == n-1-i && current1->y == n-1-j) {
                    p++;
                    break;
                }
            }
            for(current2 = list2; current2 != NULL; current2 = current2->next) {
                if (current2->x == n-1-i && current2->y == n-1-j) {
                    q++;
                    break;
                }
            }

            if(p == 1 )
                printf(" %c |", c_list1);
            if(q == 1 )
                printf(" %c |", c_list2);
            if(q == 0 && p == 0)
                printf("...|");
        }
        printf("\n");
    }
}


int main(){
    int number_of_choice;
    FILE *f;
    int n = number_of_map(f);

    struct blocks_of_map Block[n*n];

    for(int i=0; i<n*n; i++){
        initial(&(Block[i]), n, i, f);
    }

    Print_List1();

    printf("\n\ninter the number of choice:\n\n");
    scanf("%d", &number_of_choice);
    struct node* cell = NULL;
    struct node* cell1 = NULL;
    struct node* cell2 = NULL;

    if(number_of_choice == 2){
        int number_of_cells;
        printf("inter the number of cells:\n\n");
        scanf("%d", &number_of_cells);
        srand(time(NULL));
        int x ;
        int y ;
        char name[50];
        getchar();


        while (1){
            x = rand() % n;
            y = rand() % n;
            if(find(x, y, f) != '3') {
                printf("inter the name of 1 cell:\n");
                gets(name);
                cell = create_node(x, y, 0, name, strlen(name));
                Block[n * (n - 1 - y) + x].num = 1;

                break;
            }
        }

        for(int i = 1 ; i < number_of_cells ; i++){
            while(1){
                x = rand() % n;
                y = rand() % n;
                if(found(x, y, cell) == 0 && find(x, y, f) != '3'){
                    printf("inter inter the name of %d cell:\n", i+1);
                    gets(name);
                    add_end(cell, create_node(x, y, 0, name, strlen(name)));
                    Block[n * (n - 1 - y) + x].num = 1;
                    break;
                }
            }
        }
    }

    if(number_of_choice == 3){
        int number_of_cells1;
        printf("inter number of cells1:\n");
        scanf("%d", &number_of_cells1);
        srand(time(NULL));
        int x ;
        int y ;
        getchar();
        char name[50];
        printf("inter the name of 1 cell1:\n");
        gets(name);
        while(1){
            x = rand() % n;
            y = rand() % n;
            if(find(x, y, f) != '3'){
                cell1 = create_node(x, y, 0, name, strlen(name));
                Block[n * (n - 1 - y) + x].num = 1;
                break;
            }
        }

        for(int i = 1 ; i < number_of_cells1 ; i++){
            while(1){
                x = rand() % n;
                y = rand() % n;
                if(found(x, y, cell1) == 0  &&  find(x, y, f) != '3'){
                    printf("inter the name of %d cell1:\n", i+1);
                    gets(name);
                    add_end(cell1, create_node(x, y, 0, name, strlen(name)));
                    Block[n * (n - 1 - y) + x].num = 1;
                    break;
                }
            }
        }

        int number_of_cells2;
        printf("inter number of cell2:\n");
        scanf("%d", &number_of_cells2);
        srand(time(NULL));
        getchar();
        printf("inter the name of 1 cell2:\n");
        gets(name);
        while(1){
            x = rand() % n;
            y = rand() % n;
            if(found(x, y, cell1) == 0  &&  find(x, y, f) != '3'){
                cell2 = create_node(x, y, 0, name, strlen(name));
                Block[n * (n - 1 - y) + x].num = 2;
                break;
            }
        }

        for(int i = 1 ; i < number_of_cells2 ; i++){

            while(1){

                x = rand() % n;
                y = rand() % n;
                if(found(x, y, cell1) == 0  &&  find(x, y, f) != '3' && found(x, y, cell2) == 0){
                    printf("inter the name of %d cell2:\n", i+1);
                    gets(name);
                    add_end(cell2, create_node(x, y, 0, name, strlen(name)));
                    Block[n * (n - 1 - y) + x].num = 2;
                    break;
                }
            }
        }
    }

    //Print_map(n, cell1, cell2, 'X', 'Y');

    Print_map_tow_players(n, cell1, cell2, 'X', 'Y');
    printf("\n\n");
    print_List(cell1);
    printf("\n\n");
    print_List(cell2);

    return 0;


}
