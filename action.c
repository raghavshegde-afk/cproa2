

#include<stdio.h>
#include<stdlib.h>
#include"action.h"

void close_all(music* head) {
    while (head) {
        music* temp = head;
        head = head->next;
        fclose(temp->fp);
        free(temp->filename);
        free(temp);
    }
}
void play(music* current) {
    if (current == NULL || current->fp == NULL) { // Added check for fp because it won't work otherwise(nothing to read)
        printf("No song is currently selected or playlist is empty.\n");
        return;
    }

    printf("Now playing: %s\n", current->filename);

     

    int ch;
    while ((ch = fgetc(current->fp)) != EOF) {
        putchar(ch);
    }

    // You don't want to close the file here,or you won't be able to play it again.
    // Rewind the file pointer to the beginning so we can replay it later
    rewind(current->fp);
    
    
}
music* play_next(music** current, music* head) {
    if (*current == NULL) return NULL;
    *current = ((*current)->next != NULL) ? (*current)->next : head;
    // play(*current);
    return *current;
}

music* play_prev(music** current, music* tail) {
    if (*current == NULL) return NULL;
    *current = ((*current)->prev != NULL) ? (*current)->prev : tail;
    // play(*current);
    return *current;
}
void add_log(const char* command) {
    FILE* log = fopen("log.txt", "a");
    fprintf(log, "%s\n", command);
    fclose(log);
}

