#include <stdlib.h>
#include <ctype.h>
#include <dirent.h>
#include "Reader.h"

FILE *open_file(char *path)
{
    FILE *file = fopen(path, "r");
    return file;
}

FILE *create_file(char *path)
{
    FILE *file = fopen(path, "ab+");
    return file;
}

FILE *open_file_w_mode(char *path)
{
    FILE *file = fopen(path, "w+");
    return file;
}

DIR *open_dir(char *path)
{
    DIR *dir = open_dir(path);
    return dir;
}




