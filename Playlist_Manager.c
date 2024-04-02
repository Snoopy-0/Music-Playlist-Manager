#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
    char title[50];
    char artist[50];
    int duration;
    struct node *next; 
};

void printList(struct node *head){
    
    printf("--------------------------------------------------------------------\n");
    while(head != NULL){
        printf("Song title: %s \n", head->title);
        printf("Song artist: %s \n", head->artist);
        printf("song duration: %d \n", head->duration);
        printf("\n");
        head = head->next;
    }
}

void addSong(struct node **head, struct node **tail) {
    char choice;
    char temp[50];

    do {
        struct node *cnode = (struct node *)malloc(sizeof(struct node));

        printf("New song title: ");
        fgets(temp, 50, stdin);
        temp[strcspn(temp, "\n")] = 0;
        strcpy(cnode->title, temp);

        printf("New song artist: ");
        fgets(temp, 50, stdin);
        temp[strcspn(temp, "\n")] = 0;
        strcpy(cnode->artist, temp);

        printf("New song duration: ");
        scanf("%d", &(cnode->duration));
        while (getchar() != '\n');

        cnode->next = NULL;

        if (*head == NULL) {
            *head = cnode;
        } else {
            (*tail)->next = cnode;
        }
        *tail = cnode;

        printf("\nWould you like to enter another (y/n)? ");
        choice = getchar();
        printf("\n");
        while (getchar() != '\n');
    }
    while (choice == 'y' || choice == 'Y');
}


void deleteSong(struct node **head, struct node **tail){
    char name[50];
    char artist[50];
    int duration;
    struct node *p;

    p = *head;

    printf("enter the name of the song you want to delete: ");
    fgets(name, 50, stdin);
    name[strcspn(name, "\n")] = 0;

    printf("enter the name of the artist: ");
    fgets(artist, 50, stdin);
    artist[strcspn(artist, "\n")] = 0;

    while(p != NULL){
        if(name != p->title || artist != p->artist){
            p = p->next;
        }else{
            p = p->next->next;
        }
    }
}

void menu(struct node **head, struct node **tail){
    while(1){
        int choice;

        printf("--------------------------------------------------------------------\n");
        printf("Welcome to the music playlist menu, what would you like to do?\n");
        printf("1. to add a new song to the list: \n");
        printf("2. Delete a song from the list: \n");
        printf("3. Search for a song on the list: \n");
        printf("4. Print the entire song list: \n");
        printf("5. Total list duration: \n");
        printf("0. To exit\n");
        scanf("%d", &choice);
        printf("\n");

        while(getchar() != '\n');

        switch(choice){
            case 1:
                addSong(head, tail);
                break;
            case 2:
               // deleteSong();
                break;
            case 3:
               // searchSong();
                break;
            case 4:
                printList(*head);
                break;
            case 5:
               // totalTime();
                break;
            case 0:
                return;
        }
    }
}

int main(){
    struct node *head = NULL, *tail = NULL, *cnode;
    char temp[50];

    while(1){
        cnode = (struct node *)malloc(sizeof(struct node));
        printf("enter song(exit to stop): ");
        fgets(temp, 50, stdin);
        temp[strcspn(temp, "\n")] = 0;

        if(strcmp(temp, "exit") == 0){
            free(cnode);
            break;
        }
        strcpy(cnode->title, temp); 

        printf("Artist: ");
        fgets(cnode->artist, 50, stdin);
        cnode->artist[strcspn(cnode->artist, "\n")] = 0; 

        printf("Duration (in seconds): ");
        scanf("%d", &(cnode->duration));
        while (getchar() != '\n');
        
        cnode->next = NULL;

        if(head == NULL){
            head = cnode;
        }

        if(tail != NULL){
            tail->next = cnode;
        }

        tail = cnode;
    }
    menu(&head, &tail);
}