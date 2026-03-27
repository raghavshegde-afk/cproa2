#ifndef PLAYLIST_H
#define PLAYLIST_H
#include"song.h"

void merge_playlists(music** head1, music** tail1, music** head2, music** tail2);

    

void delete_playlist(music** head_point, music** tail_point);

void delete_song_from_playlist(music** head_point, music** tail_point, music** current, const char* filename,int sl);





#endif