#ifndef SONG_H
#define SONG_H
#include"action.h"

void delete_song(music** head_point, music** tail_point, music** current) ;


void appendSong(music** head_point, music** tail_point, const char* filename) ;

void create_song_file(char* filename) ;


#endif
