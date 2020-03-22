#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <math.h>

void Print_List1(void){
    printf("[1]Load\n\n");
    printf("[2]New single  game\n\n");
    printf("[3]New Multiplayer game\n\n");
    printf("[4]New Multiplayer game with computer\n\n");
    printf("[5]Exit\n\n");
}

struct node{                            //struct of cells.
    char name[50];
    int x;
    int y;
    int energy;
    int size_name;
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
    nn->size_name = strlen(name_of_cell);
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
    F->type = find(a, n-b-1, f);
    if(F->type == '1')
        F->Energy = 100;
    else
        F->Energy = 0;


}

void Print_map_one_player(int n, struct node* list, char c_list){
    struct node* current = NULL;

    for (int i = 0; i < n + 1; i++) {
        if (i == n && n % 2 == 0)
            break;
        if (i % 2 == 0)
            printf(" .....");
        if (i % 2 == 1)
            printf("      ");
    }
    printf("\n");
    for(int i=3*n; i>0; i--) {
        for (int j = 0 ; j < n ; ++j) {
            int p = 0;
            for(current = list; current != NULL; current = current->next) {
                if (current->y == i/3 && current->x == j) {
                    p++;
                    break;
                }
            }

            if(i % 3 == 0 && j % 2 == 0)
                printf("|     ");
            if(i % 3 == 1 && j % 2 == 0)
                printf("|.....");
            if(i % 3 == 2 && j % 2 == 0 && p == 1)
                printf("|  %c  ", c_list);
            if(i % 3 == 2 && j % 2 == 0 && p == 0)
                printf("|     ");

            if(i % 3 == 0  && j % 2 == 1)
                printf("|.....");
            if(i % 3 == 2 && j % 2 == 1)
                printf("|     ");
            if(i % 3 == 1 && j % 2 == 1 && p == 1)
                printf("|  %c  ", c_list);
            if(i % 3 == 1 && j % 2 == 1 && p == 0)
                printf("|     ");
        }
        printf("|\n");
    }
    printf(" ");
    for(int i=0; i<n; i++){
        if(i % 2 == 1)
            printf(".....|");
        if(i == n-1 && i%2 == 0)
            break;
        if(i % 2 == 0)
            printf("     |");
    }
    printf("\n");
}

void Print_map_two_players(int n, struct node* list1, struct node* list2) {
    struct node* current1 = list1;
    struct node* current2 = list2;
    for (int i = 0; i < n + 1; i++) {
        if (i == n && n % 2 == 0)
            break;
        if (i % 2 == 0)
            printf(" .....");
        if (i % 2 == 1)
            printf("      ");
    }
    printf("\n");
    for(int i=3*n; i>0; --i){
        for(int j=0; j<n; j++){
            bool q = false;
            bool p = false;
            for (current1 = list1; current1 != NULL; current1 = current1->next) {
                if (current1->x == i/3 && current1->y == j) {
                    q = true;
                    //break;
                }
            }
            for (current2 = list2; current2 != NULL; current2 = current2->next) {
                if (current2->x == i/3 && current2->y == j) {
                    p = true;
                   // break;
                }
            }
            if(i % 3 == 0 && j % 2 == 0)
                printf("|     ");
            if(i % 3 == 1 && j % 2 == 0)
                printf("|.....");
            if(i % 3 == 2 && j % 2 == 0 && p == true && q == false)
                printf("|  X  ");
            if(i % 3 == 2 && j % 2 == 0 && p == false && q == false)
                printf("|     ");
            if(i % 3 == 2 && j % 2 == 0 && q == true && p == false)
                printf("|  Y  ");


            if(i % 3 == 0  && j % 2 == 1)
                printf("|.....");
            if(i % 3 == 2 && j % 2 == 1)
                printf("|     ");
            if(i % 3 == 1 && j % 2 == 1 && p == false && q == false)
                printf("|     ");
            if(i % 3 == 1 && j % 2 == 1 && p == true && q == false)
                printf("|  X  ");
            if(i % 3 == 1 && j % 2 == 1 && q == true && p == false)
                printf("|  Y  ");

        }

        printf("|\n");
    }
    printf(" ");
    for(int i=0; i<n; i++){
        if(i % 2 == 1)
            printf(".....|");
        if(i == n-1 && i%2 == 0)
            break;
        if(i % 2 == 0)
            printf("     |");


    }
    printf("\n");
}

void Print_list_cells(struct node* list){
    struct node* current = list;
    int cnt = 1;
    while(current != NULL){
        printf("[%d] %s ", cnt, current->name);
        printf("(%d, %d)\n", current->x, current->y);
        current = current->next;
        cnt++;
    }
}

void  Main_menu(void){
    printf("[1] Move\n\n");
    printf("[2] Split a cell\n\n");
    printf("[3] Boost energy\n\n");
    printf("[4] Save\n\n");
    printf("[5] Exit\n\n");
}

void Move_menu(void){
    printf("[1] North\n\n");
    printf("[2] South\n\n");
    printf("[3] Northeast\n\n");
    printf("[4] Northwest\n\n");
    printf("[5] Southeast\n\n");
    printf("[6] Southwest\n\n");
}

void Moving_cell(int number_cell, int number_move, struct node* current, int n, FILE *f ){
    struct node* list = current;
    // struct node* head = NULL;
    for(int i = 1 ; i < number_cell ; i++){
        current = current->next;
    }
    if(number_move == 1 && current->y != n-1 && find(current->x, current->y+1, f) != '3' && found(current->x, current->y+1, list) == 0){
        current->y++;
    }
    if(number_move == 2 && current->y != 0 && find(current->x, current->y-1, f) != '3' && found(current->x, current->y-1, list) == 0){
        current->y--;
    }
    if(number_move == 3 && current->x != n-1  ){
        if((current->x % 2 == 0) && find(current->x+1, current->y+1, f) != '3' && current->y != n-1 && found(current->x+1, current->y+1, list) == 0) {
            current->y++;
            current->x++;
        }
        if((current->x % 2 == 1) && find(current->x+1, current->y, f) != '3' && found(current->x+1, current->y, list) == 0) {
            current->x++;
        }
    }
    if(number_move == 4 && current->x != 0){
        if((current->x % 2 == 0) && find(current->x-1, current->y+1, f) != '3' && current->y != n-1 && found(current->x-1, current->y+1, list) == 0) {
            current->y++;
            current->x--;
        }
        if((current->x % 2 != 0) && find(current->x-1, current->y, f) != '3' && found(current->x-1, current->y, list) == 0) {
            current->x--;
        }
    }
    if(number_move == 5 && current->x != n-1){
        if((current->x % 2 != 0) && find(current->x+1, current->y-1, f) != '3' && current->y != 0 && found(current->x+1, current->y-1, list) == 0) {
            current->y--;
            current->x++;
        }
        if((current->x % 2 == 0) && find(current->x+1, current->y, f) != '3' && found(current->x+1, current->y, list) == 0) {
            current->x++;
        }
    }
    if(number_move == 6 && current->x != 0){
        if(current->x % 2 == 1 && find(current->x-1, current->y-1, f) != '3' && current->y != 0 && found(current->x-1, current->y-1, list) == 0) {
            current->y--;
            current->x--;
        }
        if(current->x % 2 == 0 && find(current->x-1, current->y, f) != '3' && found(current->x-1, current->y, list) == 0) {
            current->x--;
        }
    }

    //return current;
}

void Moving_cell_two(int number_cell, int number_move, struct node* current1, struct node* current2, int n, FILE *f){
    struct node* list1 = current1;
    struct node* list2 = current2;
    for(int i = 1 ; i < number_cell ; i++){
        current1 = current1->next;
    }
    if(number_move == 1 && current1->y != n-1 && find(current1->x, current1->y+1, f) != '3' && found(list1->x, list1->y+1, list1) == 0){
        if(found(current1->x, current1->y+1, list2) == 0)
            current1->y++;
    }
    if(number_move == 2 && current1->y != 0 && find(current1->x, current1->y-1, f) != '3' && found(list1->x, list1->y-1, list1) == 0){
        if(found(current1->x, current1->y-1, list2) == 0)
            current1->y--;
    }
    if(number_move == 3 && current1->x != n-1  ){
        if((current1->x % 2 == 0) && find(current1->x+1, current1->y+1, f) != '3' && current1->y != n-1 && found(list1->x+1, list1->y+1, list1) == 0) {
            if(found(current1->x+1, current1->y+1, list2) == 0){
                current1->y++;
                current1->x++;
            }
        }
        if((current1->x % 2 != 0) && find(current1->x+1, current1->y, f) != '3' && found(list1->x+1, list1->y, list1) == 0) {
            if(found(current1->x+1, current1->y, list2) == 0)
                current1->x++;
        }
    }
    if(number_move == 4 && current1->x != 0){
        if((current1->x % 2 == 0) && find(current1->x-1, current1->y+1, f) != '3' && current1->y != n-1 && found(list1->x-1, list1->y+1, list1) == 0) {
            if(found(current1->x-1, current1->y+1, list2) == 0){
                current1->y++;
                current1->x--;
            }

        }
        if((current1->x % 2 != 0) && find(current1->x-1, current1->y, f) != '3' && found(list1->x-1, list1->y, list1) == 0) {
            if(found(current1->x-1, current1->y, list2) == 0)
                current1->x--;
        }
    }
    if(number_move == 5 && current1->x != n-1){
        if((current1->x % 2 != 0) && find(current1->x+1, current1->y-1, f) != '3' && current1->y != 0 && found(list1->x+1, list1->y-1, list1) == 0) {
            if(found(current1->x+1, current1->y-1, list2) == 0){
                current1->y--;
                current1->x++;
            }

        }
        if((current1->x % 2 == 0) && find(current1->x+1, current1->y, f) != '3' && found(list1->x+1, list1->y, list1) == 0) {
            if(found(current1->x+1, current1->y, list2) == 0)
                current1->x++;
        }
    }
    if(number_move == 6 && current1->x != 0){
        if(current1->x % 2 != 0 && find(current1->x-1, current1->y-1, f) != '3' && current1->y != 0 && found(list1->x-1, list1->y-1, list1) == 0) {
            if(found(current1->x-1, current1->y-1, list2) == 0){
                current1->y--;
                current1->x--;
            }
        }
        if(current1->x % 2 == 0 && find(current1->x-1, current1->y, f) != '3' && found(list1->x-1, list1->y, list1) == 0) {
            if(found(current1->x-1, current1->y, list2) == 0)
                current1->x--;
        }
    }

}

int Define_X(struct node* list, int number_cell){             //define X of choose cell.
    struct node* current = list;
    for(int i = 1 ; i < number_cell ; i++)
        current = current->next;
    return current->x;
}

int Define_Y(struct node* list, int number_cell){             //define Y of choose cell.
    struct node* current = list;
    for(int i = 1 ; i < number_cell ; i++)
        current = current->next;
    return current->y;
}

int move_of_split_cell(int n, int x, int y, FILE *f, struct node* list){
    int cnt = 0;
    if(x != 0 && y != 0 && x != n-1 && y != n-1){
        if(find(x, y+1, f) == '3' || found(x, y+1, list) == 1)
            cnt++;
        if(find(x, y-1, f) == '3' || found(x, y-1, list) == 1)
            cnt++;
        if(find(x+1, y, f) == '3' || found(x+1, y, list) == 1)
            cnt++;
        if(find(x-1, y, f) == '3' || found(x-1, y, list) == 1)
            cnt++;
        if(x % 2 == 0){
            if(find(x+1, y+1, f) == '3' || found(x+1, y+1, list) == 1)
                cnt++;
            if(find(x-1, y+1, f) == '3' || found(x-1, y+1, list) == 1)
                cnt++;
        }
        if(x % 2 != 0){
            if(find(x+1, y-1, f) == '3' || found(x+1, y-1, list) == 1)
                cnt++;
            if(find(x-1, y-1, f) == '3' || found(x-1, y-1, list) == 1)
                cnt++;
        }
        if(cnt == 6)
            return 0;
    }

    if(x == 0 && y != 0 && y != n-1){
        cnt = 0;
        if(find(x, y-1, f) == '3' || found(x, y-1, list) == 1)
            cnt++;
        if(find(x, y+1, f) == '3' || found(x, y+1, list) == 1)
            cnt++;
        if(find(x+1, y+1, f) == '3' || found(x+1, y+1, list) == 1)
            cnt++;
        if(find(x+1, y, f) == '3' || found(x+1, y, list) == 1)
            cnt++;
        if(cnt == 4)
            return  0;
    }
    if(x == n-1 && y != 0 && y != n-1){
        cnt = 0;
        if(x % 2 == 0){
            if(find(x-1, y+1, f) == '3' || found(x-1, y+1, list) == 1)
                cnt++;
        }
        if(cnt % 2 != 0){
            if(find(x-1, y-1, f) == '3' || found(x-1, y-1, list) == 1)
                cnt++;
        }
        if(find(x-1, y, f) == '3' || found(x-1, y, list) == 1)
            cnt++;
        if(find(x, y+1, f) == '3' || found(x, y+1, list) == 1)
            cnt++;
        if(find(x, y-1, f) == '3' || found(x, y-1, list) == 1)
            cnt++;
        if(cnt == 4)
            return 0;
    }

    if(x != 0 && x != n-1 && y == 0 && x % 2 == 1){
        cnt = 0;
        if(find(x, y+1, f) == '3' || found(x, y+1, list) == 1)
            cnt++;
        if(find(x+1, y, f) == '3' || found(x+1, y, list) == 1)
            cnt++;
        if(find(x-1, y, f) == '3' || found(x-1, y, list) == 1)
            cnt++;
        if(cnt == 3)
            return 0;
    }

    if(x != 0 && x != n-1 && y == 0 && x % 2 == 0){
        cnt = 0;
        if(find(x+1, y+1, f) == '3' || found(x+1, y+1, list) == 1)
            cnt++;
        if(find(x-1, y+1, f) == '3' || found(x-1, y+1, list) == 1)
            cnt++;
        if(find(x+1, y, f) == '3' || found(x+1, y, list) == 1)
            cnt++;
        if(find(x-1, y, f) == '3' || found(x-1, y, list) == 1)
            cnt++;
        if(find(x, y+1, f) == '3' || found(x, y+1, list) == 1)
            cnt++;
        if(cnt == 5)
            return 0;
    }

    if(x != 0 && x != n-1 && y == n-1 && x % 2 == 0) {
        cnt = 0;
        if(find(x, y-1, f) == '3' || found(x, y-1, list) == 1)
            cnt++;
        if(find(x+1, y, f) == '3' || found(x+1, y, list) == 1)
            cnt++;
        if(find(x-1, y, f) == '3' || found(x-1, y, list) == 1)
            cnt++;
        if(cnt == 3)
            return 0;
    }

    if(x != 0 && x != n-1 && y == n-1 && x % 2 != 0){
        cnt = 0;
        if(find(x, y-1, f) == '3' || found(x, y-1, list) == 1)
            cnt++;
        if(find(x+1, y, f) == '3' || found(x+1, y, list) == 1)
            cnt++;
        if(find(x-1, y, f) == '3' || found(x-1, y, list) == 1)
            cnt++;
        if(find(x+1, y-1, f) == '3' || found(x+1, y-1, list) == 1)
            cnt++;
        if(find(x-1, y-1, f) == '3' || found(x-1, y-1, list) == 1)
            cnt++;
        if(cnt == 5)
            return 0;
    }

    if(x == 0 && y == 0){
        cnt = 0;
        if(find(x+1, y, f) == '3' || found(x+1, y, list) == 1)
            cnt++;
        if(find(x, y+1, f) == '3' || found(x, y+1, list) == 1)
            cnt++;
        if(find(x+1, y+1, f) == '3' || found(x+1, y+1, list) == 1)
            cnt++;
        if(cnt == 3)
            return 0;
    }

    if(x == 0 && y == n-1){
        cnt = 0;
        if(find(x, y-1, f) == '3' || found(x, y-1, list) == 1)
            cnt++;
        if(find(x+1, y, f) == '3' || found(x+1, y, list) == 1)
            cnt++;
        if(cnt == 2)
            return 0;
    }

    if(x == n-1 && y == 0){
        cnt =0;
        if(find(x, y+1, f) == '3' || found(x, y+1, list) == 1)
            cnt++;
        if(find(x-1, y, f) == '3' || found(x-1, y, list) == 1)
            cnt++;
        if(cnt == 2)
            return 0;
    }

    if(x == n-1 && y == n-1){
        cnt = 0;
        if(find(x-1, y-1, f) == '3' || found(x-1, y-1, list) == 1)
            cnt++;
        if(find(x, y-1, f) == '3' || found(x, y-1, list) == 1)
            cnt++;
        if(find(x-1, y, f) == '3' || found(x-1, y, list) == 1)
            cnt++;
        if(cnt == 3)
            return 0;
    }
    return 1;
}

int Define_energy(struct node* list, int number_cell){
    struct node* current = list;
    for(int i = 1 ; i < number_cell ; i++)
        current = current->next;
    return current->energy;
}

void initial_new_cell(struct node* list, int number_cell, char name_new[], int size){
    struct node* current = list;
    for(int i = 1 ; i < number_cell ; i++)
        current = current->next;
    current->energy = 40;
    for(int i = 0 ; i < size ; i++){
        current->name[i] = name_new[i];
    }
    current->name[strlen(name_new)] = '\0';
    //return current;
}

int Define_random_move(struct node* list, int number_cell, int x1, int y1){
    struct node* current = list;
    for(int i = 1 ; i < number_cell ; i++)
        current = current->next;
    if(current->x == x1 && current->y == y1)
        return 0;
    return 1;
}

struct node* Increase_energy(struct node* list, int number_cell, int sum){          //sum = energy that want to increase.
    struct node* current = list;
    for(int i = 1 ; i < number_cell ; i++)
        current = current->next;
    current->energy += sum;
    if(current->energy > 100)
        current->energy = 100;
    return current;
}

void Save_state_cells(FILE *f, struct node* list, int i){
    struct node* current = list;
    fwrite(&i, sizeof(int), 1, f);
    while (current != NULL){
        fwrite(&current->x, sizeof(int), 1, f);
        fwrite(&current->y, sizeof(int), 1, f);
        fwrite(&current->energy, sizeof(int), 1, f);
        fwrite(&current->size_name, sizeof(int), 1, f);
        fwrite(current->name, sizeof(char), current->size_name, f);
        current = current->next;
    }
}

struct node* Read_cell(FILE *f){
    struct node* current = NULL;
    int i ;
    int x, y, en, s;
    char name[50];

    fread(&i, sizeof(int), 1, f);
    fread(&x, sizeof(int), 1, f);
    fread(&y, sizeof(int), 1, f);
    fread(&en, sizeof(int), 1, f);
    fread(&s, sizeof(int), 1, f);
    fread(name, sizeof(char), s, f);
    name[s] = '\0';
    current = create_node(x, y, en, name, s);

    while (i > 1){
        fread(&x, sizeof(int), 1, f);
        fread(&y, sizeof(int), 1, f);
        fread(&en, sizeof(int), 1, f);
        fread(&s, sizeof(int), 1, f);
        fread(name, sizeof(char), s, f);
        name[s] = '\0';
        add_end(current, create_node(x, y, en, name, s));
        i--;
    }
    fclose(f);
    return current;
}


char *rand_string(size_t size) {
    char *str = malloc((size + 1) * sizeof(char));
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (size_t i = 0; i < size; i++) {
        int key = rand() % (sizeof(charset) / sizeof(char) - 1);
        str[i] = charset[key];
    }
    str[size] = '\0';
    return str;
}


int main() {
    int number_of_choice;

    FILE *f;
    FILE *save_cell_state;
    FILE *save_block_state;
    FILE *save_cell1_state;
    FILE *save_block1_state;
    FILE *save_cell2_state;
    FILE *save_block2_state;

    int n = number_of_map(f);

    struct blocks_of_map Block[n * n];



    Print_List1();

    printf("\n\nEnter the number of choice:\n\n");
    scanf("%d", &number_of_choice);

    struct node *cell = NULL;
    struct node *cell1 = NULL;
    struct node *cell2 = NULL;

    int number_of_cells;
    int number_of_cells1;
    int number_of_cells2;
    char name[50];

    if (number_of_choice == 2) {
        for (int i = 0; i < n * n; i++) {
            initial(&(Block[i]), n, i, f);
        }
        printf("inter the number of cells:\n\n");
        scanf("%d", &number_of_cells);
        srand(time(NULL));
        int x;
        int y;

        getchar();

        while (1) {
            x = rand() % n;
            y = rand() % n;
            if (find(x, y, f) != '3') {
                printf("inter the name of 1 cell:\n");
                gets(name);
                cell = create_node(x, y, 80, name, strlen(name));
                Block[n * (n - 1 - y) + x].num = 1;

                break;
            }
        }

        for (int i = 1; i < number_of_cells; i++) {
            while (1) {
                x = rand() % n;
                y = rand() % n;
                if (found(x, y, cell) == 0 && find(x, y, f) != '3') {
                    printf("inter inter the name of %d cell:\n", i + 1);
                    gets(name);
                    add_end(cell, create_node(x, y, 80, name, strlen(name)));
                    Block[n * (n - 1 - y) + x].num = 1;
                    break;
                }
            }
        }


        Print_map_one_player(n, cell, 'X');
        printf("Please choose one of your cells:\n");
        Print_list_cells(cell);
        int Number;
        scanf("%d", &Number);                           //number of cell in linked_list.
        bool flag = true;
        while (flag) {
            Main_menu();
            printf("Please inter a number of menu:\n");
            int number_menu;
            scanf("%d", &number_menu);
            if (number_menu == 1) {
                Move_menu();
                int number_move;
                printf("Please inter a number of move:\n");
                scanf("%d", &number_move);
                Moving_cell(Number, number_move, cell, n, f);
                Print_map_one_player(n, cell, 'X');
                print_List(cell);
            }

            if (number_menu == 2) {

                int x1 = Define_X(cell, Number);
                int y1 = Define_Y(cell, Number);
                int en = Define_energy(cell, Number);

                if (Block[n * (n - 1 - y1) + x1].type == '2' && move_of_split_cell(n, x1, y1, f, cell) == 1) {

                    if (en > 79) {
                        printf("Please inter the name of new first_cell:\n");
                        getchar();
                        gets(name);
                        initial_new_cell(cell, Number, name, strlen(name));
                        printf("Please inter the name of new second_cell:\n");
                        gets(name);
                        srand(time(NULL));
                        int random_move;
                        add_end(cell, create_node(x1, y1, 40, name, strlen(name)));
                        while (1) {
                            random_move = (rand() % 6) + 1;
                            Moving_cell(Number, random_move, cell, n, f);
                            if (Define_random_move(cell, Number, x1, y1) == 1)
                                break;
                        }
                        Print_map_one_player(n, cell, 'X');
                        print_List(cell);
                    }
                }
            }

            if (number_menu == 3) {
                int x1 = Define_X(cell, Number);
                int y1 = Define_Y(cell, Number);
                if (Block[n * (n - 1 - y1) + x1].type == '1') {
                    if (Block[n * (n - 1 - y1) + x1].Energy >= 15) {
                        Block[n * (n - 1 - y1) + x1].Energy -= 15;
                        cell = Increase_energy(cell, Number, 15);
                    }
                    if (Block[n * (n - 1 - y1) + x1].Energy < 15) {
                        int energy_min = Block[n * (n - 1 - y1) + x1].Energy;
                        Block[n * (n - 1 - y1) + x1].Energy -= energy_min;
                        cell = Increase_energy(cell, Number, energy_min);
                    }
                }
            }
            if (number_menu == 4) {

                save_cell_state = fopen("save_cell_state.bin", "wb");
                save_block_state = fopen("save_block_state.bin", "wb");
                int cnt = 0;
                struct node* list = cell;
                for(list = cell ; list != NULL ; list = list->next)
                    cnt++;
                Save_state_cells(save_cell_state, cell, cnt);
                struct blocks_of_map save_block;
                for(int i=0; i<n*n; i++){
                    initial(&save_block, n, i, f);
                    fwrite(&save_block, sizeof(save_block), 1, save_block_state);
                }
                fclose(save_cell_state);
                fclose(save_block_state);
            }

            if (number_menu == 5) {
                flag = false;

            }
        }

    }


    if (number_of_choice == 3) {
        for (int i = 0; i < n * n; i++) {
            initial(&(Block[i]), n, i, f);
        }
        printf("inter number of cells1:\n");
        scanf("%d", &number_of_cells1);
        srand(time(NULL));
        int x;
        int y;
        getchar();

        printf("inter the name of 1 cell1:\n");
        gets(name);
        while (1) {
            x = rand() % n;
            y = rand() % n;
            if (find(x, y, f) != '3') {
                cell1 = create_node(x, y, 0, name, strlen(name));
                Block[n * (n - 1 - y) + x].num = 1;
                break;
            }
        }

        for (int i = 1; i < number_of_cells1; i++) {
            while (1) {
                x = rand() % n;
                y = rand() % n;
                if (found(x, y, cell1) == 0 && find(x, y, f) != '3') {
                    printf("inter the name of %d cell1:\n", i + 1);
                    gets(name);
                    add_end(cell1, create_node(x, y, 0, name, strlen(name)));
                    Block[n * (n - 1 - y) + x].num = 1;
                    break;
                }
            }
        }


        printf("inter number of cell2:\n");
        scanf("%d", &number_of_cells2);
        srand(time(NULL));
        getchar();
        printf("inter the name of 1 cell2:\n");
        gets(name);
        while (1) {
            x = rand() % n;
            y = rand() % n;
            if (found(x, y, cell1) == 0 && find(x, y, f) != '3') {
                cell2 = create_node(x, y, 0, name, strlen(name));
                Block[n * (n - 1 - y) + x].num = 2;
                break;
            }
        }

        for (int i = 1; i < number_of_cells2; i++) {
            while (1) {
                x = rand() % n;
                y = rand() % n;
                if (found(x, y, cell1) == 0 && find(x, y, f) != '3' && found(x, y, cell2) == 0) {
                    printf("inter the name of %d cell2:\n", i + 1);
                    gets(name);
                    add_end(cell2, create_node(x, y, 0, name, strlen(name)));
                    Block[n * (n - 1 - y) + x].num = 2;
                    break;
                }
            }
        }

        printf("player1\n");
        Print_map_one_player(n, cell1, 'X');
        printf("player2\n");
        Print_map_one_player(n, cell2, ' Y');
        print_List(cell1);
        print_List(cell1);

        bool flag = true;
        while (flag) {
            printf("Please choose one of your cells (player1):\n");
            Print_list_cells(cell1);
            int Number;
            scanf("%d", &Number);
            Main_menu();
            printf("Please inter a number of menu:\n");
            int number_menu;
            scanf("%d", &number_menu);
            if (number_menu == 1) {
                Move_menu();
                int number_move;
                printf("Please inter a number of move:\n");
                scanf("%d", &number_move);
                Moving_cell_two(Number, number_move, cell1, cell2, n, f);
               //Moving_cell(Number, number_move, cell1, n, f);
               printf("player1\n");
                Print_map_one_player(n, cell1, 'X');
                printf("player2\n");
                Print_map_one_player(n, cell2, ' Y');
                print_List(cell1);
            }

            if (number_menu == 2) {

                int x1 = Define_X(cell1, Number);
                int y1 = Define_Y(cell1, Number);
                int en = Define_energy(cell1, Number);

                if (Block[n * (n - 1 - y1) + x1].type == '2' && move_of_split_cell(n, x1, y1, f, cell1) == 1) {

                    if (en > 79) {
                        printf("Please inter the name of new first_cell1:\n");
                        getchar();
                        gets(name);
                        initial_new_cell(cell1, Number, name, strlen(name));

                        printf("Please inter the name of new second_cell1:\n");
                        gets(name);
                        int random_move;
                        add_end(cell1, create_node(x1, y1, 40, name, strlen(name)));
                        while (1) {
                            random_move = (rand() % 6) + 1;
                            Moving_cell_two(number_of_cells1, random_move, cell1, cell2, n, f);
                            if (Define_random_move(cell1, number_of_cells1, x1, y1) == 1)
                                break;
                        }
                        printf("player1\n");
                        Print_map_one_player(n, cell1, 'X');
                        printf("player2\n");
                        Print_map_one_player(n, cell2, ' Y');
                        print_List(cell1);
                    }
                }
            }

            if (number_menu == 3) {
                int x1 = Define_X(cell1, Number);
                int y1 = Define_Y(cell1, Number);
                if (Block[n * (n - 1 - y1) + x1].type == '1') {
                    if (Block[n * (n - 1 - y1) + x1].Energy >= 15) {
                        Block[n * (n - 1 - y1) + x1].Energy -= 15;
                        cell1 = Increase_energy(cell1, Number, 15);
                    }
                    if (Block[n * (n - 1 - y1) + x1].Energy < 15) {
                        int energy_min = Block[n * (n - 1 - y1) + x1].Energy;
                        Block[n * (n - 1 - y1) + x1].Energy -= energy_min;
                        cell1 = Increase_energy(cell1, Number, energy_min);
                    }
                }
            }

            if (number_menu == 4) {

                save_cell1_state = fopen("save_cell1_state.bin", "wb");
                if(save_cell1_state == NULL){
                    printf("cannot open the save_cell1_state.");
                    return NULL;
                }
                save_block1_state = fopen("save_block1_state.bin", "wb");

                int cnt1 = 0;
                struct node* list1 ;
                for(list1 = cell1 ; list1 != NULL ; list1 = list1->next)
                    cnt1++;

                Save_state_cells(save_cell1_state, cell1, cnt1);
                struct blocks_of_map save_block;
                for(int i=0; i<n*n; i++){
                    initial(&save_block, n, i, f);
                    fwrite(&save_block, sizeof(save_block), 1, save_block1_state);
                }
                fclose(save_cell1_state);
                fclose(save_block1_state);
            }

            if (number_menu == 5) {
                flag = false;

            }


            printf("Please choose one of your cells (player2):\n");
            Print_list_cells(cell2);
            scanf("%d", &Number);
            Main_menu();
            printf("Please inter a number of menu:\n");
            scanf("%d", &number_menu);

            if (number_menu == 1) {
                Move_menu();
                int number_move;
                printf("Please inter a number of move:\n");
                scanf("%d", &number_move);
                Moving_cell_two(Number, number_move, cell2, cell1, n, f);
                printf("player1\n");
                Print_map_one_player(n, cell1, 'X');
                printf("player2\n");
                Print_map_one_player(n, cell2, ' Y');
                print_List(cell1);
            }

            if (number_menu == 2) {

                int x1 = Define_X(cell2, Number);
                int y1 = Define_Y(cell2, Number);
                int en = Define_energy(cell2, Number);

                if (Block[n * (n - 1 - y1) + x1].type == '2' && move_of_split_cell(n, x1, y1, f, cell2) == 1) {

                    if (en > 79) {
                        printf("Please inter the name of new first_cell2:\n");
                        getchar();
                        gets(name);
                        initial_new_cell(cell2, Number, name, strlen(name));
                        printf("Please inter the name of new second_cell2:\n");
                        gets(name);
                        int random_move;
                        add_end(cell2, create_node(x1, y1, 40, name, strlen(name)));
                        while (1) {
                            random_move = (rand() % 6) + 1;
                            Moving_cell_two(number_of_cells2, random_move, cell2, cell1, n, f);
                            if (Define_random_move(cell2, number_of_cells2, x1, y1) == 1)
                                break;
                        }
                        printf("player1\n");
                        Print_map_one_player(n, cell1, 'X');
                        printf("player2\n");
                        Print_map_one_player(n, cell2, ' Y');
                        print_List(cell1);
                    }
                }
            }

            if (number_menu == 3) {
                int x1 = Define_X(cell2, Number);
                int y1 = Define_Y(cell2, Number);
                if (Block[n * (n - 1 - y1) + x1].type == '1') {
                    if (Block[n * (n - 1 - y1) + x1].Energy >= 15) {
                        Block[n * (n - 1 - y1) + x1].Energy -= 15;
                        cell2 = Increase_energy(cell2, Number, 15);
                    }
                    if (Block[n * (n - 1 - y1) + x1].Energy < 15) {
                        int energy_min = Block[n * (n - 1 - y1) + x1].Energy;
                        Block[n * (n - 1 - y1) + x1].Energy -= energy_min;
                        cell2 = Increase_energy(cell2, Number, energy_min);
                    }
                }
            }

            if (number_menu == 4) {

                save_cell2_state = fopen("save_cell2_state.bin", "wb");
                save_block2_state = fopen("save_block2_state.bin", "wb");
                int cnt2 = 0;
                struct node* list2 ;
                for(list2 = cell2 ; list2 != NULL ; list2 = list2->next)
                    cnt2++;
                Save_state_cells(save_cell2_state, cell2, cnt2);
                struct blocks_of_map save_block;
                for (int i = 0; i < n * n; i++) {
                    initial(&save_block, n, i, f);
                    fwrite(&save_block, sizeof(save_block), 1, save_block2_state);
                }
                fclose(save_cell2_state);
                fclose(save_block2_state);
            }


            if (number_menu == 5){
                flag = false;

            }
        }
    }

    if(number_of_choice == 4){
        for (int i = 0; i < n * n; i++) {
            initial(&(Block[i]), n, i, f);
        }
        printf("Enter number of cells1:\n");
        scanf("%d", &number_of_cells1);
        srand(time(NULL));
        int x;
        int y;
        getchar();

        printf("Enter the name of 1 cell1:\n");
        gets(name);
        while (1) {
            x = rand() % n;
            y = rand() % n;
            if (find(x, y, f) != '3') {
                cell1 = create_node(x, y, 0, name, strlen(name));
                Block[n * (n - 1 - y) + x].num = 1;
                break;
            }
        }

        for (int i = 1; i < number_of_cells1; i++) {
            while (1) {
                x = rand() % n;
                y = rand() % n;
                if (found(x, y, cell1) == 0 && find(x, y, f) != '3') {
                    printf("inter the name of %d cell1:\n", i + 1);
                    gets(name);
                    add_end(cell1, create_node(x, y, 0, name, strlen(name)));
                    Block[n * (n - 1 - y) + x].num = 1;
                    break;
                }
            }
        }

        srand(time(NULL));
        number_of_cells2 = rand() % n*n;
        int cnt = 0;
        for(int i=0; i<n*n; i++){
            if(Block[i].type == '3')
                cnt++;
        }

        while(number_of_cells2 + number_of_cells1 + cnt > n*n)
            number_of_cells2--;

        printf("number_of_cells2: %d\n", number_of_cells2);

        char *str = rand_string(5);
        printf("rand name[5] cell2: %s\n", str);


        while (1) {
            x = rand() % n;
            y = rand() % n;
            if (found(x, y, cell1) == 0 && find(x, y, f) != '3') {
                cell2 = create_node(x, y, 0, str, strlen(str));
                Block[n * (n - 1 - y) + x].num = 2;
                break;
            }
        }

        for (int i = 1 ; i < number_of_cells2 ; i++) {
            while (1) {
                x = rand() % n;
                y = rand() % n;
                if (found(x, y, cell1) == 0 && find(x, y, f) != '3' && found(x, y, cell2) == 0) {
                    str = rand_string(5);
                    printf("rand name[5] cell2: %s\n", str);
                    add_end(cell2, create_node(x, y, 0, str, strlen(str)));
                    Block[n * (n - 1 - y) + x].num = 2;
                    break;
                }
            }
        }

        printf("player1\n");
        Print_map_one_player(n, cell1, 'X');
        printf("player2\n");
        Print_map_one_player(n, cell2, ' Y');
        print_List(cell1);

        bool flag = true;
        while (flag) {
            printf("Please choose one of your cells (player1):\n");
            Print_list_cells(cell1);
            int Number;
            scanf("%d", &Number);
            Main_menu();
            printf("Please inter a number of menu:\n");
            int number_menu;
            scanf("%d", &number_menu);
            if (number_menu == 1) {
                Move_menu();
                int number_move;
                printf("Please inter a number of move:\n");
                scanf("%d", &number_move);
                Moving_cell(Number, number_move, cell1, n, f);
                printf("player1\n");
                Print_map_one_player(n, cell1, 'X');
                printf("player2\n");
                Print_map_one_player(n, cell2, ' Y');
                print_List(cell1);
            }

            if (number_menu == 2) {

                int x1 = Define_X(cell1, Number);
                int y1 = Define_Y(cell1, Number);
                int en = Define_energy(cell1, Number);

                if (Block[n * (n - 1 - y1) + x1].type == '2' && move_of_split_cell(n, x1, y1, f, cell1) == 1) {

                    if (en > 79) {
                        printf("Please inter the name of new first_cell1:\n");
                        getchar();
                        gets(name);
                        initial_new_cell(cell1, Number, name, strlen(name));
                        printf("Please inter the name of new second_cell1:\n");
                        gets(name);
                        int random_move;
                        add_end(cell1, create_node(x1, y1, 40, name, strlen(name)));
                        while (1) {
                            random_move = (rand() % 6) + 1;
                            Moving_cell(number_of_cells1, random_move, cell1, n, f);
                            if (Define_random_move(cell1, number_of_cells1, x1, y1) == 1)
                                break;
                        }
                        printf("player1\n");
                        Print_map_one_player(n, cell1, 'X');
                        printf("player2\n");
                        Print_map_one_player(n, cell2, ' Y');
                        print_List(cell1);
                    }
                }
            }

            if (number_menu == 3) {
                int x1 = Define_X(cell1, Number);
                int y1 = Define_Y(cell1, Number);
                if (Block[n * (n - 1 - y1) + x1].type == '1') {
                    if (Block[n * (n - 1 - y1) + x1].Energy >= 15) {
                        Block[n * (n - 1 - y1) + x1].Energy -= 15;
                        cell1 = Increase_energy(cell1, Number, 15);
                    }
                    if (Block[n * (n - 1 - y1) + x1].Energy < 15) {
                        int energy_min = Block[n * (n - 1 - y1) + x1].Energy;
                        Block[n * (n - 1 - y1) + x1].Energy -= energy_min;
                        cell1 = Increase_energy(cell1, Number, energy_min);
                    }
                }
            }

            if (number_menu == 4) {

                save_cell1_state = fopen("save_cell1_state.bin", "wb");
                if(save_cell1_state == NULL){
                    printf("cannot open the save_cell1_state.");
                    return NULL;
                }
                save_block1_state = fopen("save_block1_state.bin", "wb");

                int cnt1 = 0;
                struct node* list1 ;
                for(list1 = cell1 ; list1 != NULL ; list1 = list1->next)
                    cnt1++;

                Save_state_cells(save_cell1_state, cell1, cnt1);
                struct blocks_of_map save_block;
                for(int i=0; i<n*n; i++){
                    initial(&save_block, n, i, f);
                    fwrite(&save_block, sizeof(save_block), 1, save_block1_state);
                }
                fclose(save_cell1_state);
                fclose(save_block1_state);
            }

            if (number_menu == 5) {
                flag = false;

            }



            Print_list_cells(cell2);
            printf("Please press Enter (for player2):\n");
            getchar();
            srand(time(NULL));
            Number = (rand() % number_of_cells2) + 1;
            Main_menu();
            printf("Please Enter a number of menu:\n");
            printf("Please press Enter (for player2):\n");
            getchar();
            srand(time(NULL));
            number_menu = (rand() % 5) + 1;

            if (number_menu == 1) {
                Move_menu();
                int number_move;
                printf("Please inter a number of move:\n\n");
                printf("Please press Enter (for player2):\n\n");
                getchar();
                number_move = (rand() % 6) + 1;
                Moving_cell(Number, number_move, cell2, n, f);
                printf("player1\n");
                Print_map_one_player(n, cell1, 'X');
                printf("player2\n");
                Print_map_one_player(n, cell2, ' Y');
                print_List(cell1);

            }

            if (number_menu == 2) {

                int x1 = Define_X(cell2, Number);
                int y1 = Define_Y(cell2, Number);
                int en = Define_energy(cell2, Number);

                if (Block[n * (n - 1 - y1) + x1].type == '2' && move_of_split_cell(n, x1, y1, f, cell2) == 1) {

                    if (en > 79) {
                        str = rand_string(5);
                        printf("rand name[5] new1_cell2: %s\n", str);

                        initial_new_cell(cell2, Number, str, strlen(str));
                        str = rand_string(5);
                        printf("rand name[5] new2_cell2: %s\n", str);


                        int random_move;
                        add_end(cell2, create_node(x1, y1, 40, str, strlen(str)));
                        while (1) {
                            random_move = (rand() % 6) + 1;
                            Moving_cell(number_of_cells2, random_move, cell2, n, f);
                            if (Define_random_move(cell2, number_of_cells2, x1, y1) == 1)
                                break;
                        }
                        printf("player1\n");
                        Print_map_one_player(n, cell1, 'X');
                        printf("player2\n");
                        Print_map_one_player(n, cell2, ' Y');
                        print_List(cell1);
                    }
                }
            }

            if (number_menu == 3) {
                int x1 = Define_X(cell2, Number);
                int y1 = Define_Y(cell2, Number);
                if (Block[n * (n - 1 - y1) + x1].type == '1' ) {
                    if (Block[n * (n - 1 - y1) + x1].Energy >= 15) {
                        Block[n * (n - 1 - y1) + x1].Energy -= 15;
                        cell2 = Increase_energy(cell2, Number, 15);
                    }
                    if (Block[n * (n - 1 - y1) + x1].Energy < 15) {
                        int energy_min = Block[n * (n - 1 - y1) + x1].Energy;
                        Block[n * (n - 1 - y1) + x1].Energy -= energy_min;
                        cell2 = Increase_energy(cell2, Number, energy_min);
                    }
                }
            }

            if (number_menu == 4) {

                save_cell2_state = fopen("save_cell2_state.bin", "wb");
                save_block2_state = fopen("save_block2_state.bin", "wb");
                int cnt2 = 0;
                struct node* list2 ;
                for(list2 = cell2 ; list2 != NULL ; list2 = list2->next)
                    cnt2++;
                Save_state_cells(save_cell2_state, cell2, cnt2);
                struct blocks_of_map save_block;
                for (int i = 0; i < n * n; i++) {
                    initial(&save_block, n, i, f);
                    fwrite(&save_block, sizeof(save_block), 1, save_block2_state);
                }
                fclose(save_cell2_state);
                fclose(save_block2_state);
            }


            if (number_menu == 5){
                flag = false;

            }
        }

    }

    if(number_of_choice == 5){
        return 0;
    }

    if(number_of_choice == 1){
        printf("[1] single player game load:\n\n[2] Multiplayer game load:\n\n\n");
        printf("Please enter the number of player:\n");


        int number_of_player_load;
        scanf("%d", &number_of_player_load);

        if(number_of_player_load == 1){
            save_cell_state = fopen("save_cell_state.bin", "rb");
            cell = Read_cell(save_cell_state);
            fclose(save_cell_state);
            save_block_state = fopen("save_block_state.bin", "rb");
            struct blocks_of_map p;
            for(int i=0; i<n*n; i++){
                fread(&p, sizeof(p), 1, save_block_state);
                Block[i] = p;
            }
            fclose(save_block_state);

            Print_map_one_player(n, cell, 'X');
            printf("Please choose one of your cells:\n");
            Print_list_cells(cell);
            int Number;
            scanf("%d", &Number);                           //number of cell in linked_list.
            bool flag = true;
            while (flag) {
                Main_menu();
                printf("Please inter a number of menu:\n");
                int number_menu;
                scanf("%d", &number_menu);
                if (number_menu == 1) {
                    Move_menu();
                    int number_move;
                    printf("Please inter a number of move:\n");
                    scanf("%d", &number_move);
                    Moving_cell(Number, number_move, cell, n, f);
                    Print_map_one_player(n, cell, 'X');
                }

                if (number_menu == 2) {

                    int x1 = Define_X(cell, Number);
                    int y1 = Define_Y(cell, Number);
                    int en = Define_energy(cell, Number);

                    if (Block[n * (n - 1 - y1) + x1].type == '2' && move_of_split_cell(n, x1, y1, f, cell) == 1) {

                        if (en > 79) {
                            printf("Please inter the name of new first_cell:\n");
                            getchar();
                            gets(name);
                            initial_new_cell(cell, Number, name, strlen(name));
                            printf("Please inter the name of new second_cell:\n");
                            gets(name);
                            int random_move;
                            add_end(cell, create_node(x1, y1, 40, name, strlen(name)));
                            while (1) {
                                random_move = (rand() % 6) + 1;
                                Moving_cell(number_of_cells, random_move, cell, n, f);
                                if (Define_random_move(cell, number_of_cells, x1, y1) == 1)
                                    break;
                            }
                            Print_map_one_player(n, cell, 'X');
                        }
                    }
                }

                if (number_menu == 3) {
                    int x1 = Define_X(cell, Number);
                    int y1 = Define_Y(cell, Number);
                    if (Block[n * (n - 1 - y1) + x1].type == '1') {
                        if (Block[n * (n - 1 - y1) + x1].Energy >= 15) {
                            Block[n * (n - 1 - y1) + x1].Energy -= 15;
                            cell = Increase_energy(cell, Number, 15);
                        }
                        if (Block[n * (n - 1 - y1) + x1].Energy < 15) {
                            int energy_min = Block[n * (n - 1 - y1) + x1].Energy;
                            Block[n * (n - 1 - y1) + x1].Energy -= energy_min;
                            cell = Increase_energy(cell, Number, energy_min);
                        }
                    }
                }
                if (number_menu == 4) {

                    save_cell_state = fopen("save_cell_state.bin", "wb");
                    save_block_state = fopen("save_block_state.bin", "wb");
                    int cnt = 0;
                    struct node* list = cell;
                    for(list = cell ; list != NULL ; list = list->next)
                        cnt++;
                    Save_state_cells(save_cell_state, cell, cnt);
                    struct blocks_of_map save_block;
                    for(int i=0; i<n*n; i++){
                        initial(&save_block, n, i, f);
                        fwrite(&save_block, sizeof(save_block), 1, save_block_state);
                    }
                    fclose(save_cell_state);
                    fclose(save_block_state);
                }

                if (number_menu == 5) {
                    flag = false;

                }
            }
        }

        if(number_of_player_load == 2){
            save_cell1_state = fopen("save_cell1_state.bin", "rb");
            cell1 = Read_cell(save_cell1_state);
            fclose(save_cell1_state);
            save_cell2_state = fopen("save_cell2_state.bin", "rb");
            cell2 = Read_cell(save_cell2_state);
            fclose(save_cell2_state);

            save_block1_state = fopen("save_block1_state.bin", "rb");
            struct blocks_of_map p;
            for(int i=0; i<n*n; i++){
                fread(&p, sizeof(p), 1, save_block1_state);
                Block[i] = p;
            }
            fclose(save_block1_state);

            printf("player1\n");
            Print_map_one_player(n, cell1, 'X');
            printf("player2\n");
            Print_map_one_player(n, cell2, ' Y');
            print_List(cell1);

            bool flag = true;
            while (flag) {
                printf("Please choose one of your cells (player1):\n");
                Print_list_cells(cell1);
                int Number;
                scanf("%d", &Number);
                Main_menu();
                printf("Please inter a number of menu:\n");
                int number_menu;
                scanf("%d", &number_menu);
                if (number_menu == 1) {
                    Move_menu();
                    int number_move;
                    printf("Please inter a number of move:\n");
                    scanf("%d", &number_move);
                    Moving_cell_two(Number, number_move, cell1, cell2, n, f);
                    printf("player1\n");
                    Print_map_one_player(n, cell1, 'X');
                    printf("player2\n");
                    Print_map_one_player(n, cell2, ' Y');
                    print_List(cell1);
                }

                if (number_menu == 2) {

                    int x1 = Define_X(cell1, Number);
                    int y1 = Define_Y(cell1, Number);
                    int en = Define_energy(cell1, Number);

                    if (Block[n * (n - 1 - y1) + x1].type == '2' && move_of_split_cell(n, x1, y1, f, cell1) == 1) {

                        if (en > 79) {
                            printf("Please inter the name of new first_cell1:\n");
                            getchar();
                            gets(name);
                            initial_new_cell(cell1, Number, name, strlen(name));
                            printf("Please inter the name of new second_cell1:\n");
                            gets(name);
                            int random_move;
                            add_end(cell1, create_node(x1, y1, 40, name, strlen(name)));
                            while (1) {
                                random_move = (rand() % 6) + 1;
                                Moving_cell_two(number_of_cells1, random_move, cell1, cell2, n, f);
                                if (Define_random_move(cell1, number_of_cells1, x1, y1) == 1)
                                    break;
                            }
                            printf("player1\n");
                            Print_map_one_player(n, cell1, 'X');
                            printf("player2\n");
                            Print_map_one_player(n, cell2, ' Y');
                            print_List(cell1);
                        }
                    }
                }

                if (number_menu == 3) {
                    int x1 = Define_X(cell1, Number);
                    int y1 = Define_Y(cell1, Number);
                    if (Block[n * (n - 1 - y1) + x1].type == '1') {
                        if (Block[n * (n - 1 - y1) + x1].Energy >= 15) {
                            Block[n * (n - 1 - y1) + x1].Energy -= 15;
                            cell1 = Increase_energy(cell1, Number, 15);
                        }
                        if (Block[n * (n - 1 - y1) + x1].Energy < 15) {
                            int energy_min = Block[n * (n - 1 - y1) + x1].Energy;
                            Block[n * (n - 1 - y1) + x1].Energy -= energy_min;
                            cell1 = Increase_energy(cell1, Number, energy_min);
                        }
                    }
                }

                if (number_menu == 4) {

                    save_cell1_state = fopen("save_cell1_state.bin", "wb");
                    save_block1_state = fopen("save_block1_state.bin", "wb");

                    int cnt1 = 0;
                    struct node* list1 ;
                    for(list1 = cell1 ; list1 != NULL ; list1 = list1->next)
                        cnt1++;

                    Save_state_cells(save_cell1_state, cell1, cnt1);
                    struct blocks_of_map save_block;
                    for(int i=0; i<n*n; i++){
                        initial(&save_block, n, i, f);
                        fwrite(&save_block, sizeof(save_block), 1, save_block1_state);
                    }
                    fclose(save_cell1_state);
                    fclose(save_block1_state);
                }

                if (number_menu == 5) {
                    flag = false;

                }


                printf("Please choose one of your cells (player2):\n");
                Print_list_cells(cell2);
                scanf("%d", &Number);
                Main_menu();
                printf("Please inter a number of menu:\n");
                scanf("%d", &number_menu);

                if (number_menu == 1) {
                    Move_menu();
                    int number_move;
                    printf("Please inter a number of move:\n");
                    scanf("%d", &number_move);
                    Moving_cell_two(Number, number_move, cell2, cell1, n, f);
                    Print_map_one_player(n, cell1, 'X');
                    Print_map_one_player(n, cell2, ' Y');
                }

                if (number_menu == 2) {

                    int x1 = Define_X(cell2, Number);
                    int y1 = Define_Y(cell2, Number);
                    int en = Define_energy(cell2, Number);

                    if (Block[n * (n - 1 - y1) + x1].type == '2' && move_of_split_cell(n, x1, y1, f, cell2) == 1) {

                        if (en > 79) {
                            printf("Please inter the name of new first_cell2:\n");
                            getchar();
                            gets(name);

                            initial_new_cell(cell2, Number, name, strlen(name));
                            printf("Please inter the name of new second_cell2:\n");
                            gets(name);
                            int random_move;
                            add_end(cell2, create_node(x1, y1, 40, name, strlen(name)));
                            while (1) {
                                random_move = (rand() % 6) + 1;
                                Moving_cell_two(number_of_cells2, random_move, cell2, cell1, n, f);
                                if (Define_random_move(cell2, number_of_cells2, x1, y1) == 1)
                                    break;
                            }
                            printf("player1\n");
                            Print_map_one_player(n, cell1, 'X');
                            printf("player2\n");
                            Print_map_one_player(n, cell2, ' Y');
                            print_List(cell1);
                        }
                    }
                }

                if (number_menu == 3) {
                    int x1 = Define_X(cell2, Number);
                    int y1 = Define_Y(cell2, Number);
                    if (Block[n * (n - 1 - y1) + x1].type == '1') {
                        if (Block[n * (n - 1 - y1) + x1].Energy >= 15) {
                            Block[n * (n - 1 - y1) + x1].Energy -= 15;
                            cell2 = Increase_energy(cell2, Number, 15);
                        }
                        if (Block[n * (n - 1 - y1) + x1].Energy < 15) {
                            int energy_min = Block[n * (n - 1 - y1) + x1].Energy;
                            Block[n * (n - 1 - y1) + x1].Energy -= energy_min;
                            cell2 = Increase_energy(cell2, Number, energy_min);
                        }
                    }
                }

                if (number_menu == 4) {

                    save_cell2_state = fopen("save_cell2_state.bin", "wb");
                    save_block2_state = fopen("save_block2_state.bin", "wb");
                    int cnt2 = 0;
                    struct node* list2 ;
                    for(list2 = cell2 ; list2 != NULL ; list2 = list2->next)
                        cnt2++;
                    Save_state_cells(save_cell2_state, cell2, cnt2);
                    struct blocks_of_map save_block;
                    for (int i = 0; i < n * n; i++) {
                        initial(&save_block, n, i, f);
                        fwrite(&save_block, sizeof(save_block), 1, save_block2_state);
                    }
                    fclose(save_cell2_state);
                    fclose(save_block2_state);
                }


                if (number_menu == 5){
                    flag = false;

                }
            }
        }
    }

    if(cell != NULL){
        struct node* current = cell;
        int Sum_of_energy_cell = 0;
        for (current = cell; current != NULL; current = current->next) {
            Sum_of_energy_cell += current->energy;
        }
        printf("sum of energy cell: %d\n", Sum_of_energy_cell);
    }

    if(cell1 != NULL){
        struct node* current = cell1;
        int Sum_of_energy_cell1 = 0;
        for (current = cell1; current != NULL; current = current->next) {
            Sum_of_energy_cell1 += current->energy;
        }
        printf("sum of energy cell1: %d\n", Sum_of_energy_cell1);


        struct node* current2 = cell2;
        int Sum_of_energy_cell2 = 0;
        for (current2 = cell2; current2 != NULL; current2 = current2->next) {
            Sum_of_energy_cell2 += current2->energy;
        }
        printf("sum of energy cell2: %d\n", Sum_of_energy_cell2);
    }



    return 0;
}

