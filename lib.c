

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"lib.h"



void listsongs()
{
    FILE* lib = fopen("library.txt", "r");
    if (lib == NULL) {
        printf("No songs in library.\n");
        return;
    }
    int ch;
    printf("Songs in library:\n");
    while ((ch = fgetc(lib)) != EOF) {
        putchar(ch);
    }
    fclose(lib);
}
void addlibrary(const char* filename)
{//making sure each song is added just once to library
    FILE* lib = fopen("library.txt", "r+");
    if (lib == NULL) {
        printf("Error opening library file.\n");
        return;
    }

    char line[256];
    int found = 0;
    while (fgets(line, sizeof(line), lib)) {
        line[strcspn(line, "\n")] = '\0';  // Remove newline character else we will add same song again, replace with end of string(at least that is what I understand)
        if (strcmp(line, filename) == 0) {
            found = 1;
            break;
        }
    }

    if (!found) {
        fseek(lib, 0, SEEK_END);
        fprintf(lib, "%s\n", filename);
    }

    fclose(lib);
}



