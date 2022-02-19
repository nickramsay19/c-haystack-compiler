#include "include/SourceFile.h"

#include <stdio.h>
#include <stdlib.h>

struct SourceFileStruct {
    char *filename;
    char *content;
};

SourceFile InitSourceFile(char* filename) {

    // allocate space for the struct
    SourceFile sf = (SourceFile) malloc(sizeof(struct SourceFileStruct));

    // allocate space for the strings
    sf->filename = (char*) calloc(DEFAULT_SOURCEFILE_NAME_LEN, sizeof(char));
    sf->content = (char*) calloc(DEFAULT_SOURCEFILE_CONTENT_LEN, sizeof(char));

    int src_cap = DEFAULT_SOURCEFILE_CONTENT_LEN;
    int src_pos = 0;

    // read the contents of the file
    FILE *fp = fopen(filename, "r");
    char c;
    while (fscanf(fp, "%c", &c)) {
        // check if there is capacity to add the next char
        if (src_pos == src_cap) {
            src_cap *= 2; // double the capacity
            sf->content = (char*) realloc(sf->content, src_cap * sizeof(char));
        }

        // write the char and increment src_pos
        sf->content[src_pos++] = c;
    }

    // close the file
    fclose(fp);

    return sf;
}