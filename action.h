#ifndef ACTION_H
#define ACTION_H

#define MAX_playlists 1
typedef struct music {
    FILE* fp;
    int slno;
    struct music* next;
    struct music* prev;
    char* filename;
} music;
typedef struct lib{
    FILE* fip;
    int id;
    struct lib* next;
}lib;
void close_all(music* head);

void play(music* current);

    
    

music* play_next(music** current, music* head);


music* play_prev(music** current, music* tail);

void add_log(const char* command);




#endif