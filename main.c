#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"action.h"
#include"song.h"
#include"playlist.h"
#include"album.h"
#include"lib.h"

/* ASSUMPTIONS:
all details reelated to a specific song are in a specific text file and if you want to add a song you must add the file  and the file must exist so if you  wish to add any more songs you must first add the file and once you have added the song to a playlist or album it will be added to the library as it is now accessible to the program
playlist is analogous to queue in spotify
albums are analogous to playlists on spotify
library file stores names of all songs*/

int n=0;



int main() {
    music* heads[MAX_playlists] = {NULL};//Misunderstood the question when I first wrote the code was too lazy to change this so I just set maximum number of playlists to 1 in another file
    music* tails[MAX_playlists] = {NULL};
    music* currents[MAX_playlists] = {NULL};

    int active = 0; 

    load_album_state(&album_library);//Retain albums and songs from previous iteration of program as structs
    printf("when inputting name please make it lower case with no spaces so it matches with filename(assuming you have inputted an available song) or you can add the file for the song if you  have it and once you have added the song to a playlist or album it will be added to the library as it is now accessible to the program.If the song is not listed in the listsongs option then you will have to add the song to playlist or album in order to play it.Note that you must add song to playlist if you wish to play it and cannot directly play the song.\n"); 
    printf("Available commands:\n");
    printf("addtoplaylist <songid>\n");
    printf("play\n");
    printf("next\n");
    printf("previous\n");
    printf("deletefromplaylist\n");
    printf("resetplaylist\n");
    printf("remove\n");
    printf("log\n");
    printf("exit\n");
    printf("saveplaylistasalbum <albumname>\n");
    printf("listalbums\n");
    printf("listsongsofalbum <albumid>\n");
    printf("addalbumtoplaylist <albumid>\n");
    printf("addtoalbum <albumid> <songid>\n");
    printf("deletefromalbum <albumid> <songid>\n");
    printf("listsongs\n");
    printf("newalbum <albumname>\n");
    printf("deleteplaylist\n");
    // printf("createsongfile <filename>\n");
    printf("deletesongfromplaylist <songid>\n");
    while (1) {
        char command[30];
        printf("\n Enter command: ", active);
        scanf("%s", command);

        add_log(command);

        if (!strcmp(command, "addtoplaylist")) {
            int id;
            scanf("%d", &id);
            char filename[30];
            if(id==1) strcpy(filename,"weatherman");
            else if(id==2) strcpy(filename,"vivalavida");
            else if(id==3) strcpy(filename,"mrbrightside");
            else if(id==4) strcpy(filename,"photograph");
            else if(id==5) strcpy(filename,"numb");
            else if(id==6) strcpy(filename,"theemptinessmachine");
            else if(id==7) strcpy(filename,"rise");
            else if (id==8) strcpy(filename,"blindinglights");
            else printf("Invalid song ID.\n");
            // addlibrary(filename);
            appendSong(&heads[active], &tails[active], filename);
            if (currents[active] == NULL) currents[active] = heads[active];
        }
        else if (!strcmp(command, "play")){
            play(currents[active]);
        }
        else if (!strcmp(command, "next")) {
            play_next(&currents[active], heads[active]);
            play(currents[active]);

        }
        else if (!strcmp(command, "previous")) {
            play_prev(&currents[active], tails[active]);
            play(currents[active]);
            
        }
        else if (!strcmp(command, "deletefromplaylist")) {
            delete_song(&heads[active], &tails[active], &currents[active]);
        }
        else if (!strcmp(command, "deletesongfromplaylist")) {
            // char filename[20];
            // scanf("%s", filename);
            int id;
            scanf("%d", &id);
            char filename[30];
            if(id==1) strcpy(filename,"weatherman");
            else if(id==2) strcpy(filename,"vivalavida");
            else if(id==3) strcpy(filename,"mrbrightside");
            else if(id==4) strcpy(filename,"photograph");
            else if(id==5) strcpy(filename,"numb");
            else if(id==6) strcpy(filename,"theemptinessmachine");
            else if(id==7) strcpy(filename,"rise");
            else if (id==8) strcpy(filename,"blindinglights");
            else printf("Invalid song ID.\n");
            int s;
            scanf("%d",&s);
            delete_song_from_playlist(&heads[active], &tails[active], &currents[active], filename,s);
        }
        else if (!strcmp(command, "resetplaylist")) {
            for (int i = 0; i < MAX_playlists; i++)
                close_all(heads[i]);
            
        }
        else if(!strcmp(command,"remove")){
            delete_playlist(&heads[active], &tails[active]);
            currents[active] = NULL;
        }
        else if (!strcmp(command,"log")){
            FILE* logfile = fopen("log.txt", "r"); 
            if (logfile == NULL) {
                printf("No history found.\n");
            } else {
                char c;
                while ((c = fgetc(logfile)) != EOF) {
                    putchar(c);
                }
                fclose(logfile);
            }
        }
        else if(!strcmp(command,"exit")){
            //exit program ,store the albums to file so we can retain them for next time
            save_album_state(&album_library);
            printf(" Program exit complete.\n");


            break;
        }
        else if(!strcmp(command,"saveplaylistasalbum")){
            char albumname[50];
            scanf("%s",albumname);
            saveplaylistasalbum(heads[active],albumname);
        }
        else if(!strcmp(command,"listalbums")){
            listalbums(&album_library);
        }
        else if(!strcmp(command,"listsongsofalbum")){
            int z;
            scanf("%d",&z);
            album* current=album_library.a;
            while(current!=NULL){
                if(current->id==z){
                    listsongsofalbum(current);
                    break;
                }
                current=current->na;
            }
            if(current==NULL){
                printf("Album not found.\n");
            }
        }
        else if(!strcmp(command,"addalbumtoplaylist")){
            int z;
            scanf("%d",&z);
            album* current=album_library.a;
            while(current!=NULL){
                if(current->id==z){
                    addalbumtoplaylist(current,&heads[active],&tails[active]);
                    if(currents[active]==NULL) currents[active]=heads[active];
                    break;
                }
                current=current->na;
            }
            if(current==NULL){
                printf("Album not found.\n");
            }
        }
        else if (!strcmp(command,"addtoalbum")){
            int z;
            int i;
            scanf("%d", &i);
            char filename[30];
            if(i==1) strcpy(filename,"weatherman");
            else if(i==2) strcpy(filename,"vivalavida");
            else if(i==3) strcpy(filename,"mrbrightside");
            else if(i==4) strcpy(filename,"photograph");
            else if(i==5) strcpy(filename,"numb");
            else if(i==6) strcpy(filename,"theemptinessmachine");
            else if(i==7) strcpy(filename,"rise");
            else if (i==8) strcpy(filename,"blindinglights");
            else printf("Invalid song ID.\n");
            scanf("%d",&z);
            // addlibrary(filename);
            album* current=album_library.a;
            while(current!=NULL){
                if(current->id==z){
                    addsongtoalbum(current,filename);
                    break;
                }
                current=current->na;
            }
            if(current==NULL){
                printf("Album not found.\n");
            }
        }
        else if (!strcmp(command,"deletefromalbum")){
            int z;
            int i;
            scanf("%d", &i);
            char filename[30];
            if(i==1) strcpy(filename,"weatherman");
            else if(i==2) strcpy(filename,"vivalavida");
            else if(i==3) strcpy(filename,"mrbrightside");
            else if(i==4) strcpy(filename,"photograph");
            else if(i==5) strcpy(filename,"numb");
            else if(i==6) strcpy(filename,"theemptinessmachine");
            else if(i==7) strcpy(filename,"rise");
            else if(i==8) strcpy(filename,"blindinglights");
            else printf("Invalid song ID.\n");
            scanf("%d",&z);
            album* current=album_library.a;
            while(current!=NULL){
                if(current->id==z){
                    deletefromalbum(current,filename);
                    break;
                }
                current=current->na;
            }
            if(current==NULL){
                printf("Album not found.\n");
            }
        }
        else if (!strcmp(command, "listsongs")) {
            listsongs();
        }
        else if(!strcmp(command,"newalbum")){
            char albumname[50];
            scanf("%s",albumname);
            album* newAlbum=malloc(sizeof(album));
            if(!newAlbum) continue;
            newAlbum->name=strdup(albumname);
            newAlbum->song1=NULL;
            newAlbum->na=NULL;
            appendalbum(&album_library,newAlbum);
        }
        else if (!strcmp(command,"deleteplaylist")){
            delete_playlist(&heads[active],&tails[active]);
            currents[active]=NULL;
        }
        // else if(!strcmp(command,"createsongfile")){
        //     char filename[50];
        //     scanf("%s",filename);
        //     create_song_file(filename);
        // }
        else {
            printf("Unknown command.\n");
        }
    }

    return 0;
}
