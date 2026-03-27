
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"playlist.h"



void delete_playlist(music** head_point, music** tail_point) {
    music* current = *head_point;
    while (current != NULL) {
        music* temp = current;
        current = current->next;
        fclose(temp->fp);
        free(temp->filename);
        free(temp);
    }
    *head_point = NULL;
    *tail_point = NULL;
    printf("Playlist deleted successfully.\n");
}

void delete_song_from_playlist(music** head_point, music** tail_point, music** current, const char* filename,int sl) {
    if (*head_point == NULL) return;
    music* node = *head_point;

    while (node != NULL) {
        if (!strcmp(node->filename, filename) && node->slno == sl) {
            // if (node == *head_point) *head_point = node->next;
            // if (node == *tail_point) *tail_point = node->prev;
            // if (node->prev) node->prev->next = node->next;
            // if (node->next) node->next->prev = node->prev;
            // if (*current == node) *current = node->next ? node->next : node->prev;
            // fclose(node->fp);
            // free(node->filename);
            // free(node);
            delete_song(head_point, tail_point, current);
            printf("Song %s deleted from playlist.\n", filename);
            return;
        }
        node = node->next;
    }
    printf("Song %s not found in playlist or wrong serial number provided\n", filename);
}




