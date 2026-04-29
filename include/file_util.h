#ifndef  LR_FILE_UTIL
# define LR_FILE_UTIL // I don't think this needs any update

#include <stdio.h>
#include <stdlib.h>

char* lr_file_read(const char* path) {
    FILE* file = fopen(path, "rb");
    if (!file) {
        fprintf(stderr, "Could not open file: %s\n", path);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* buffer = (char*)malloc(length + 1);
    if (!buffer) {
        fclose(file);
        return NULL;
    }

    size_t read_size = fread(buffer, 1, length, file);
    buffer[read_size] = '\0'; // Use the actual read size!

    fclose(file);
    return buffer;
}

#endif