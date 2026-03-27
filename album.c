


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"album.h"

albumset album_library = {NULL};



void appendsongalbum(album* a, music* m) {
    if (a->song1 == NULL) {
        a->song1 = m;
        m->next = NULL;
        m->prev = NULL;
    } else {
        music* temp = a->song1;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = m;
        m->prev = temp;
        m->next = NULL;
    }
}
void addsongtoalbum(album* a, const char* filename) {
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
    node->prev = NULL;

    appendsongalbum(a, node);
}
void appendalbum(albumset* as, album* al) {
    if (as->a == NULL) {
        as->a = al;
        al->na = NULL;
        n+=1;
        al->id=n;
    } else {
        album* temp = as->a;
        while (temp->na != NULL) {
            temp = temp->na;
        }
        temp->na = al;
        al->na = NULL;
        n+=1;
        al->id=n;
    }
    return;
}
void deletefromalbum(album* a, const char* filename) {
    music* current = a->song1;
    while (current != NULL) {
        if (!strcmp(current->filename, filename)) {
            if (current->prev) current->prev->next = current->next;
            if (current->next) current->next->prev = current->prev;
            fclose(current->fp);
            free(current->filename);
            free(current);
            return;
        }
        current = current->next;
    }
}

void addalbumtoplaylist(album* a, music** head_point, music** tail_point) {
    music* current = a->song1;
    while (current != NULL) {
        appendSong(head_point, tail_point, current->filename);
        current = current->next;
    }
}
void listalbums(albumset* as) {
    album* current = as->a;
    while (current != NULL) {
        printf("Album: %s,ID= %d\n", current->name,current->id);
        current = current->na;
    }
}
void listsongsofalbum(album* a) {
    music* current = a->song1;
    printf("Songs in album %s:\n", a->name);
    while (current != NULL) {
        printf("%s\n", current->filename);
        current = current->next;
    }
}


void saveplaylistasalbum(music* head, const char* albumname) {
    if (head == NULL || albumname == NULL) {
        printf("Error: Playlist is empty or album name is invalid.\n");
        return;
    }

    // Avoid duplicate album name
    album* exist = album_library.a;
    while (exist != NULL) {
        if (strcmp(exist->name, albumname) == 0) {
            printf("Album '%s' already exists.\n", albumname);
            return;
        }
        exist = exist->na;
    }

    // Create new album
    album* newAlbum = malloc(sizeof(album));
    if (!newAlbum) {
        printf("Failure to make album from playlist\n");
        return;
    }

    newAlbum->name = strdup(albumname);
    newAlbum->song1 = NULL;
    newAlbum->na = NULL;

    // Add the new album to the global album library
    appendalbum(&album_library, newAlbum);

    // Copy all songs from the playlist into the new album
    music* current = head;
    while (current != NULL) {
        addsongtoalbum(newAlbum, current->filename);
        current = current->next;
    }

    printf("Album '%s' created.", albumname);
}


void save_album_state(albumset* as) {
    if (as == NULL || as->a == NULL) {
        printf("No albums to save.\n");
        return;
    }

    FILE* file = fopen("albumdata.txt", "w");

    album* current_album = as->a;
    while (current_album != NULL) {
        fprintf(file, "ALBUM %s\n", current_album->name);

        music* current_song = current_album->song1;
        while (current_song != NULL) {
            fprintf(file, "SONG %s\n", current_song->filename );
            current_song = current_song->next;
        }

        current_album = current_album->na;
    }

    fclose(file);
    printf("Album library saved.\n");
}


void load_album_state(albumset* as) {
    FILE* file = fopen("albumdata.txt", "r");
    if (file == NULL) {
        printf("No saved album library found. Starting fresh.\n");
        return;
    }

    char line_type[20];
    char name[100]; //
    
    album* last_album_loaded = NULL;

    while (fscanf(file, "%s %s", line_type, name) == 2) {
        if (!strcmp(line_type, "ALBUM")) {
            // Create a new album
            album* new_album = (album*)malloc(sizeof(album));
            if (new_album == NULL) {
                printf("Error: Malloc failed.\n"); 
                return;
            }
            new_album->name = strdup(name);
            new_album->song1 = NULL;
            new_album->na = NULL;

            // Add it to the albumset
            appendalbum(as, new_album);

            // Keep track of it so we can add songs to it
            last_album_loaded = new_album;
        }
        else if (!strcmp(line_type, "SONG")) {
            if (last_album_loaded != NULL) {
                addsongtoalbum(last_album_loaded, name);
            }
        }
    }

    fclose(file);
    printf("Album library loaded.\n");
}



