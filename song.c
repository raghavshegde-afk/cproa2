


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"song.h"
void create_song_file(char* filename){
    FILE* fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error creating file %s\n", filename);
        return;
    }
    else {
        printf("File %s created successfully.\n", filename);
        printf("give contents for the song file:(end your input with END)\n");
        char line[256];
        while (1) {
            fgets(line, sizeof(line), stdin);
            if (strcmp(line, "END\n") == 0) {
                break;
            }
            fputs(line, fp);
        }
    }
    fclose(fp);
}
void appendSong(music** head_point, music** tail_point, const char* filename) {
    music* node = malloc(sizeof(music));
    if (!node) return;

    node->fp = fopen(filename, "r");
    if (!node->fp) {
        printf("Warning: Could not open %s\n", filename);
        free(node);
        return;
    }

    node->filename = strdup(filename);
    node->next = NULL;

    if (*head_point == NULL) {
        node->prev = NULL;
        *head_point = node;
        *tail_point = node;
        node->slno = 1;
        play(node);
    } else {
        node->prev = *tail_point;
        (*tail_point)->next = node;
        *tail_point = node;
        node->slno = node->prev->slno + 1;
    }
}
void delete_song(music** head_point, music** tail_point, music** current) {
    if (*current == NULL) return;
    music* node = *current;

    if (node == *head_point) *head_point = node->next;
    if (node == *tail_point) *tail_point = node->prev;
    if (node->prev) node->prev->next = node->next;
    if (node->next) node->next->prev = node->prev;

    *current = node->prev ? node->prev : node->next;
    while(node->next!=NULL){
        node->slno--;
        node=node->next;
    }

    fclose(node->fp);
    free(node->filename);
    free(node);

    if (*current) printf("Now playing: %s\n", (*current)->filename);
}




