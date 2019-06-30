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
struct programs{
    int day;
    char name[40];
    int start;
    int end;
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
void add_end(struct program *list, struct program *new_program){
    struct program *current;
    for(current  = list;current->next != NULL; current = current->next);
    current->next = new_program;
    new_program->next = NULL;
}
void delete_front(struct program **list){
        struct program *temp;
        temp=*list;
        *list = temp->next;
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
    struct program *nt;
    nt = create_program(dy, nm, st, ed);
    return nt;
}
int check_new_task(struct program *list, struct program *new_program){
    struct program *current;
    for(current = list; current != NULL; current = current->next){
        if((current->day == new_program->day) && (strcmp(current->name, new_program->name) == 0))
            return 1;
        if((current->day == new_program->day) && (((new_program->start > current->start) && (new_program->start < current->end)) || ((new_program->end < current->end) && (new_program->end > current->start))))
            return 2;
    }
    return 0;
}
void print_tasks(struct program *list){
    struct program *current;
    printf("0 (Saturday): \n");
    for(current = list; current != NULL; current = current->next){
        if(current->day == 0){
            printf("%s (from: %d, to: %d)\n", current->name
                   , current->start, current->end);

        }
    }

    printf("\n");
    printf("1 (Sunday): \n");
    for(current = list; current != NULL; current = current->next){
        if(current->day == 1){
            printf("%s (from: %d, to: %d)\n", current->name
                   , current->start, current->end);
        }
    }
    printf("\n");
    printf("2 (Monday): \n");
    for(current = list; current != NULL; current = current->next){
        if(current->day == 2){
            printf("%s (from: %d, to: %d)\n", current->name
                   , current->start, current->end);
        }
    }
    printf("\n");
    printf("3 (Tuesday): \n");
    for(current = list; current != NULL; current = current->next){
        if(current->day == 3){
            printf("%s (from: %d, to: %d)\n", current->name
                   , current->start, current->end);
        }
    }
    printf("\n");
    printf("4 (Wednesday): \n");
    for(current = list; current != NULL; current = current->next){
        if(current->day == 4){
            printf("%s (from: %d, to: %d)\n", current->name
                   , current->start, current->end);
        }
    }
    printf("\n");
    printf("5 (Thursday): \n");
    for(current = list; current != NULL; current = current->next){
        if(current->day == 5){
            printf("%s (from: %d, to: %d)\n", current->name
                   , current->start, current->end);
        }
    }
    printf("\n");
    printf("6 (Friday): \n");
    for(current = list; current != NULL; current = current->next){
        if(current->day == 6){
            printf("%s (from: %d, to: %d)\n", current->name
                   , current->start, current->end);
        }
    }
    printf("\n");
}
    void save_file(struct program *list,char name[30]){
        FILE *fp;
        strcat(name,".bin");
        fp = fopen(name, "wb");
        if(fp == NULL){
            printf("Can not open a file to save your data!");
            return;
        }
        struct programs temp;
        struct program *current;
        for(current = list; current != NULL; current = current->next){
            temp.day = current->day;
            strcpy(temp.name, current->name);
            temp.start = current->start;
            temp.end = current->end;
            fwrite(&temp, sizeof(struct programs), 1, fp);
        }
        fclose(fp);
    }

    void load_file(struct program **list, char name[30]){
        strcat(name,".bin");
        FILE *fp;
        fp = fopen(name, "rb");
        if(fp == NULL){
            printf("File not found!");
            return;
        }
        struct programs temp;
        struct program *current;
        while(!feof(fp)){
            fread(&temp, sizeof(struct programs), 1, fp);
            current = create_program(temp.day, temp.name, temp.start, temp.end);
            add_front(list, current);
        }
        fclose(fp);
    }

int main()
{
    char name[30];
    char copyname[30];
    int choice;
    struct program *list = NULL;
    printf("Enter your name: ");
    scanf("%s", name);
    strcpy(copyname, name);
    printf("Welcome %s!\n", name);
    struct program *nt;
    while(1){
        options();
        scanf("%d", &choice);
        switch(choice){
            case 1:
                nt = new_task();
                if(nt == NULL)
                    printf("there is no space to add your task!");
                else{
                    if(check_new_task(list, nt) == 1){
                        printf("conflict with name!\n");
                    }
                    if(check_new_task(list, nt) == 2){
                        printf("conflict with time!\n");
                    }
                    if(check_new_task(list, nt) == 0){
                        insert_task(&(list), nt);
                        printf("There is no error and new task is created!\n");
                    }
                }
                break;
            case 2:
                print_tasks(list);
                break;
            case 3:
                save_file(list, copyname);
                break;
            case 4:
                load_file(&list, copyname);
                delete_front(&list);
                break;
            case 5:
                printf("Bye %s", name);
                return 0;
        }
    }
    return 0;
}



/*
bara save kardan bayad code ro to file zakhire konam ke bad az etmame arname va vorode dobare age load ro zad bara chap kardan kar ha ya wzafe kardane kare jadid be moshkel nakhorim! */
