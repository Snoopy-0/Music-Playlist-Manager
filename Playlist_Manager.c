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
    //char artist[50];
    struct node *p;
    struct node *prev;

    p = *head;
    prev = *head; 

    printf("enter the name of the song you want to delete: ");
    fgets(name, 50, stdin);
    name[strcspn(name, "\n")] = 0;

    printf("\n");

    if(p != NULL && strcmp(p->title, name) == 0){
        *head = p->next; 
        free(p);
        return;
    }

    while(p != NULL && strcmp(p->title, name) != 0){
        prev = p; 
        p = p->next;
    }

    if(p == NULL){
        printf("song could not be found. Returning to menu\n");
        return;
    }

    prev->next = p->next; 

    free(p);

    printf("%s has successfully been deleted. Returning to menu. \n", name);
}

void searchSong(struct node *head){
    char name[50];
    struct node *p;

    p = head;
    
    printf("enter the name of the song you would like to find: ");
    fgets(name, 50, stdin);
    name[strcspn(name, "\n")] = 0; 

    while(p != NULL){
        if(p != NULL && strcmp(p->title, name) == 0){
            printf("Song title: %s \n", p->title);
            printf("Song artist: %s \n", p->artist);
            printf("song duration: %d \n", p->duration);
            printf("\n");
            return;
        }else if(p != NULL && strcmp(p->title, name) != 0){
            p = p->next;
        }
    }
    printf("song could not be found. Returning to menu.\n");
    return;
}

void searchByArtist(struct node *head){
    char artistName[50];
    struct node *p;

    p = head;

    printf("Please enter the artist you would like to search by: ");
    fgets(artistName, 50, stdin);
    artistName[strcspn(artistName, "\n")] = 0;
    printf("\n");

    printf("Showing songs by %s: \n", artistName);
    printf("\n");

    while(p != NULL){
        if(strcmp(p->artist, artistName) == 0){
            printf("Song title: %s \n", p->title);
            printf("Song artist: %s \n", p->artist);
            printf("song duration: %d \n", p->duration);
            printf("\n");
            p = p->next;
        }else{
            p = p->next;
        }
    }
    return;
}

void listDuration(struct node *head){
    int count;
    int seconds;
    int minutes;
    struct node *p;
    p = head; 

    while(p != NULL){
        count = count + p->duration;
        p = p->next;
    }

    minutes = count/60; 
    seconds = count % 60;

    printf("playlist duration is %d:%d minutes long.\n", minutes, seconds);
    return;
}
/*
void shuffleList(struct node *head){
    struct node *p;
    struct node *temp;
    p = head;
    temp = head;

    while(p != NULL){
        
    }
}*/

void savePlaylist(struct node *head){
    FILE *fptr;
    fptr = fopen("savedPlaylist.txt", "w");
    struct node *p;
    p = head;

    if(fptr != NULL){
        while(p != NULL){
            fprintf(fptr, "--------------------------------------------\n");
            fprintf(fptr, "Song Title: %s\n", p->title);
            fprintf(fptr, "Song artist: %s\n",p->artist);
            fprintf(fptr, "Song Duration: %d\n", p->duration);

            p = p->next;
        }
    }else{
        printf("could not save playlist to a file. Returning to menu");
        return;
    }
    printf("Done! playlist has been successfully saved to a file. Returning to menu.\n");
    fclose(fptr);
    return;
}

void loadPlaylist(struct node *head){
    char filename[50];
    char fData[100];

    printf("Please enter the file name to open: ");
    fgets(filename, 50, stdin);
    filename[strcspn(filename, "\n")] = 0;

    FILE *fptr = fopen(filename,"r");
    if(fptr != NULL){
        while(fgets(fData, 100, fptr)){
            if(strncmp(fData, "Song Title:", 11) == 0){
                char *title = fData + 11;
                title += strspn(title, " ");
            }else{

            } 
            if(strncmp(fData, "Song artist:", 12) == 0){
                char *artist = fData + 12;
                artist += strspn(artist, " ");
            }else{

            } 
            if(strncmp(fData, "Song Duration:", 14) == 0){
                char *durationStr = fData + 14;
                int duration = atoi(durationStr);
            }
        }
    }else{
        printf("could not open %s. Returning to menu.", filename);
        return;
    }
}

void createList(char title[50], char artist[50], int duration){
    struct node *head = NULL, *tail = NULL, *cnode;
    while(1){
        cnode = (struct node *)malloc(sizeof(struct node));
        strcpy(cnode->title, title);
        strcpy(cnode->artist, artist);
        cnode->duration = duration; 
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
        printf("4. Search for songs by a particular artist: \n");
        printf("5. Print the entire song list: \n");
        printf("6. Total list duration: \n");
        printf("7. Shuffle the playlist randomly: \n");
        printf("8. Save the playlist to a text file: \n");
        printf("9. Open a saved playlist text file: \n");
        printf("0. To exit\n");
        scanf("%d", &choice);
        printf("\n");

        while(getchar() != '\n');

        switch(choice){
            case 1:
                addSong(head, tail);
                break;
            case 2:
               deleteSong(head, tail);
                break;
            case 3:
               searchSong(*head);
                break;
            case 4:
                searchByArtist(*head);
                break;
            case 5:
                printList(*head);
                break;
            case 6:
                listDuration(*head);
                break;
            case 7:
                //shuffleList(*head);
                break;
            case 8:
                savePlaylist(*head);
                break;
            case 9:
                loadPlaylist(*head);
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