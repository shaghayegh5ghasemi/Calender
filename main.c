#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct program{
    int day;
    char name[40];
    int start;
    int end;
    struct program *next;
};
void options(){
    printf("[1] new task\n");
    printf("[2] show tasks\n");
    printf("[3] save\n");
    printf("[4] load\n");
    printf("[5] quit\n");
}
struct program* create_program(int d, char n[40], int s, int e){
    struct program *np;
    np = (struct program *)malloc(sizeof(struct program));
    if(np != NULL){
        np->day = d;
        strcpy(np->name, n);
        np->start = s;
        np->end = e;
        np->next = NULL;
    }
    return np;
}
void add_front(struct program **plist, struct program *new_program){
    new_program->next = *plist;
    *plist = new_program;
}
void add_end(struct program *list, struct program new_program){
    struct program *current;
    for(current  = list;current->next != NULL; current = current->next);
    current->next = new_program;
    new_program->next = NULL;
}

void insert_task(struct program **plist, struct program *nt){
    struct program *current;
    struct program *previous;
    current = *plist;
    previous = NULL;
    while((current != NULL) && (nt->day == current->day) && ((nt->start) > (current->start))){
        previous = current;
        current = current->next;
    }
    //insert new task at the beginning of list
    if(previous == NULL)
        add_front(plist, nt);
    else{
        //insert new task between previous and current
        previous->next = nt;
        nt->next = current;
    }
}

struct program* new_task(){
    int dy;
    char nm[40];
    int st;
    int ed;
    printf("Enter the day: ");
    scanf("%d", &dy);
    printf("Enter the name: ");
    scanf("%s", nm);
    printf("Enter the start time: ");
    scanf("%d", &st);
    printf("Enter the end time: ");
    scanf("%d", &ed);
    //check kon esme va saate barname to ye rooz tekrari nabashe!
    struct program *nt;
    nt = create_program(dy, nm, st, ed);
    return nt;
}
void print_tasks(struct program *list){
    struct program *current;
    printf("0 (Saturday): ");
    for(current = list; current != NULL; current = current->name){
        if(current->day == 0){
            printf("%s (from: %d, to: %d)\n", current->name
                   , current->start, current->end);
        }
    }
    printf("\n");
    printf("1 (Sunday): ");
    for(current = list; current != NULL; current = current->name){
        if(current->day == 1){
            printf("%s (from: %d, to: %d)\n", current->name
                   , current->start, current->end);
        }
    }
    printf("\n");
    printf("2 (Monday): ");
    for(current = list; current != NULL; current = current->name){
        if(current->day == 2){
            printf("%s (from: %d, to: %d)\n", current->name
                   , current->start, current->end);
        }
    }
    printf("\n");
    printf("3 (Tuesday): ");
    for(current = list; current != NULL; current = current->name){
        if(current->day == 3){
            printf("%s (from: %d, to: %d)\n", current->name
                   , current->start, current->end);
        }
    }
    printf("\n");
    printf("4 (Wednesday): ");
    for(current = list; current != NULL; current = current->name){
        if(current->day == 4){
            printf("%s (from: %d, to: %d)\n", current->name
                   , current->start, current->end);
        }
    }
    printf("\n");
    printf("5 (Thursday): ");
    for(current = list; current != NULL; current = current->name){
        if(current->day == 5){
            printf("%s (from: %d, to: %d)\n", current->name
                   , current->start, current->end);
        }
    }
    printf("\n");
    printf("6 (Friday): ");
    for(current = list; current != NULL; current = current->name){
        if(current->day == 6){
            printf("%s (from: %d, to: %d)\n", current->name
                   , current->start, current->end);
        }
    }
    printf("\n");
}

int main()
{
    char name[30];
    int choice;
    struct program *list = NULL;
    printf("Enter your name: ");
    scanf("%s", name);
    printf("Welcome %s!", name);
    options();
    scanf("%d", &choice);
    struct program *nt;
    FILE *fp;
    while(choice != 5){
        switch(choice){
        case 1:
            nt = new_task();
            if(nt == NULL)
                printf("there is no space to add your task!");
            else
                insert_task(&(list), nt);

        case 2:
            print_tasks(list);
        case 3:
            fp = fopen(name, "w");
            if(fp == NULL)
                printf("Can not open a file to save your data!");
            else{
                fprint_tasks(list, fp);
            }
            fclose(fp);
        case 4:
            fopen(name, "r+");
            //??
    }
    if(choice == 5){
        printf("Bye %s", name);
        return 0;
    }
    }
    return 0;
}



/*
bara save kardan bayad code ro to file zakhire konam ke bad az etmame arname va vorode dobare age load ro zad bara chap kardan kar ha ya wzafe kardane kare jadid be moshkel nakhorim! */
