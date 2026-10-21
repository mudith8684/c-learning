#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

typedef struct Song {
    int id;
    char title[MAX];
    char artist[MAX];
    int duration;
    struct Song *prev;
    struct Song *next;
} Song;

Song *createSong(int id, const char *title, const char *artist, int duration) {
    Song *newSong = malloc(sizeof(Song));
    if(newSong == NULL) {
        printf("Failed to allocate memory for a new song.\n");
        return NULL;
    }
    newSong->id = id;
    snprintf(newSong->title, MAX, "%s", title);
    snprintf(newSong->artist, MAX, "%s", artist);
    newSong->duration = duration;
    newSong->prev = NULL;
    newSong->next = NULL;
    return newSong;
}

void insertBeginning(Song **head, Song **tail, Song *newSong) {
    if(newSong == NULL) {
        return;
    }
    if(*head == NULL) {
        *head = *tail = newSong;
    } else {
        newSong->next = *head;
        (*head)->prev = newSong;
        *head = newSong;
    }
}

void insertEnd(Song **head, Song **tail, Song *newSong) {
    if(newSong == NULL) {
        return;
    }
    if(*tail == NULL) {
        *head = *tail = newSong;
    } else {
        newSong->prev = *tail;
        (*tail)->next = newSong;
        *tail = newSong;
    }
}

int insertAtPosition(Song **head, Song **tail, Song **current, Song *newSong, int position) {
    if(newSong == NULL || position < 1) {
        return 0;
    }
    Song *nextNode = *head;
    Song *prevNode = NULL;
    int i = 1;
    while(i < position && nextNode != NULL) {
        prevNode = nextNode;
        nextNode = nextNode->next;
        i++;
    }
    if(i != position) {
        return 0;
    }
    newSong->prev = prevNode;
    newSong->next = nextNode;
    if(prevNode != NULL) {
        prevNode->next = newSong;
    } else {
        *head = newSong;
    }
    if(nextNode != NULL) {
        nextNode->prev = newSong;
    } else {
        *tail = newSong;
    }
    *current = newSong;
    return 1;
}

int deleteById(Song **head, Song **tail, Song **current, int id) {
    Song *temp = *head;

    while(temp != NULL && temp->id != id) {
        temp = temp->next;
    } // Find song with given ID

    if(temp == NULL) {
        return 0;
    } // Song not found

    if(*current == temp) {
        if(temp->next != NULL) {
            *current = temp->next;
        } else {
            *current = temp->prev;
        }
    } // If deleting current song, update current to prev or next node

    if(temp->prev != NULL) {
        temp->prev->next = temp->next;
    } else {
        *head = temp->next;
    } // Update prev node or head

    if(temp->next != NULL) {
        temp->next->prev = temp->next;
    } else {
        *tail = temp->prev;
    } // Update next node or tail

    free(temp);
    return 1;
}

// Helper function for searchByTitle and searchByArtist for partial matches, and is case-insensitive
int containsIgnoreCase(const char *text, const char *query) {
    if(*query == '\0') {
        return 1;
    }
    for(; *text != '\0'; text++) {
        const char *t = text;
        const char *q = query;
        while(*t != '\0' && *q != '\0' && tolower((unsigned char)*t) == tolower((unsigned char)*q)) {
            t++;
            q++;
        }
        if(*q == '\0') {
            return 1;
        }
    }
    return 0;
}

void searchByTitle(Song *head, const char *title) {
    Song *temp = head;
    int found = 0;
    while(temp != NULL) {
        if(containsIgnoreCase(temp->title, title)) {
            printf("ID: %d\n", temp->id);
            printf("Title: %s\n", temp->title);
            printf("Artist: %s\n", temp->artist);
            printf("Duration: %d\n", temp->duration);
            found = 1;
        }
        temp = temp->next;
    }
    if(!found) {
        printf("No songs found with title: %s\n", title);
    }
}

void searchByArtist(Song *head, const char *artist) {
    Song *temp = head;
    int found = 0;
    while(temp != NULL) {
        if(containsIgnoreCase(temp->artist, artist)) {
            printf("ID: %d\n", temp->id);
            printf("Title: %s\n", temp->title);
            printf("Artist: %s\n", temp->artist);
            printf("Duration: %d\n", temp->duration);
            found = 1;
        }
        temp = temp->next;
    }
    if(!found) {
        printf("No songs found by artist: %s\n", artist);
    }
}

void displayForward(Song *head) {
    if(head == NULL) {
        printf("Playlist is empty.\n");
        return;
    }
    Song *temp = head;
    while(temp != NULL) {
        printf("ID: %d\n", temp->id);
        printf("Title: %s\n", temp->title);
        printf("Artist: %s\n", temp->artist);
        printf("Duration: %d\n", temp->duration);
        temp = temp->next;
    }
}

void displayReverse(Song *tail) {
    if(tail == NULL) {
        printf("Playlist is empty.\n");
        return;
    }
    Song *temp = tail;
    while(temp != NULL) {
        printf("ID: %d\n", temp->id);
        printf("Title: %s\n", temp->title);
        printf("Artist: %s\n", temp->artist);
        printf("Duration: %d\n", temp->duration);
        temp = temp->prev;
    }
}

void displayFunctions() {
    printf("\nMUSIC PLAYLIST MANAGER\n");
    printf("1. Insert at beginning\n");
    printf("2. Insert at end\n");
    printf("3. Insert at position\n");
    printf("4. Delete song by ID\n");
    printf("5. Search by title\n");
    printf("6. Search by artist\n");
    printf("7. Display forward\n");
    printf("8. Display reverse\n");
    printf("9. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    Song *head = NULL, *tail = NULL, *current = NULL;
    int choice, id, duration, position;
    char title[MAX], artist[MAX];
    while(1) {
        displayFunctions();
        if(scanf("%d", &choice) != 1) {
            printf("Invalid input. Exiting...\n");
            break;
        }
        getchar();
        switch(choice) {
            case 1:
            case 2:
            case 3: {
                printf("Enter song ID: ");
                if(scanf("%d", &id) != 1) {
                    printf("Invalid ID.\n");
                    goto cleanup;
                }
                getchar();
                printf("Enter song title: ");
                if(fgets(title, MAX, stdin) == NULL) {
                    goto cleanup;
                }
                title[strcspn(title, "\n")] = '\0';
                printf("Enter artist name: ");
                if(fgets(artist, MAX, stdin) == NULL) {
                    goto cleanup;
                }
                artist[strcspn(artist, "\n")] = '\0';
                printf("Enter duration in seconds: ");
                if(scanf("%d", &duration) != 1) {
                    printf("Invalid duration.\n");
                    goto cleanup;
                }
                getchar();
                Song *newSong = createSong(id, title, artist, duration);
                if(newSong == NULL) {
                    printf("Could not create song.\n");
                    break;
                }
                if(choice == 1) {
                    insertBeginning(&head, &tail, newSong);
                    current = newSong;
                    printf("Song inserted at beginning.\n");
                } else if(choice == 2) {
                    insertEnd(&head, &tail, newSong);
                    current = newSong;
                    printf("Song inserted at end.\n");
                } else {
                    printf("Enter position (1-based): ");
                    if(scanf("%d", &position) != 1) {
                        printf("Invalid position.\n");
                        free(newSong);
                        getchar();
                        break;
                    }
                    getchar();
                    if(insertAtPosition(&head, &tail, &current, newSong, position)) {
                        printf("Song inserted successfully.\n");
                    } else {
                        printf("Invalid position.\n");
                        free(newSong);
                    }
                }
                break;
            }
            case 4: {
                printf("Enter song ID to delete from playlist: ");
                if(scanf("%d", &id) != 1) {
                    printf("Invalid ID.\n");
                    goto cleanup;
                }
                getchar();
                if(deleteById(&head, &tail, &current, id)) {
                    printf("Song deleted successfully.\n");
                } else {
                    printf("Song ID not found.\n");
                }
                break;
            }
            case 5: {
                printf("Enter title (or part of it): ");
                if(fgets(title, MAX, stdin) == NULL) {
                    goto cleanup;
                }
                title[strcspn(title, "\n")] = '\0';
                searchByTitle(head, title);
                break;
            }
            case 6: {
                printf("Enter artist (or part of the name): ");
                if(fgets(artist, MAX, stdin) == NULL) {
                    goto cleanup;
                }
                artist[strcspn(artist, "\n")] = '\0';
                searchByArtist(head, artist);
                break;
            }
            case 7: {
                displayForward(head);
                break;
            }
            case 8: {
                displayReverse(head);
                break;
            }
            case 9: {
                goto cleanup;
            }
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
cleanup:
    while(head != NULL) {
        Song *temp = head;
        head = head->next;
        free(temp);
    }
    tail = NULL;
    current = NULL;
    printf("Playlist memory freed. Goodbye!\n");
    return 0;
}