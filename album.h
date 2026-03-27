#ifndef ALBUM_H
#define ALBUM_H
#include "song.h"
#include"playlist.h"

typedef struct album {
    char* name;
    int id;
    music* song1;
    struct album* na;
} album;

extern int n;

typedef struct albumset {
    album* a;
} albumset;

extern albumset album_library;

void appendsongalbum(album* a, music* m);
void addsongtoalbum(album* a, const char* filename);
void appendalbum(albumset* as, album* al);
void deletefromalbum(album* a, const char* filename);
void addalbumtoplaylist(album* a, music** head_point, music** tail_point) ;
void listalbums(albumset* as);
void listsongsofalbum(album* a);
void saveplaylistasalbum(music* head, const char* albumname);
void deletealbum(album* a);
void save_album_state(albumset* as);
void load_album_state(albumset* as);


#endif