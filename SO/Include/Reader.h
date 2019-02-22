#include <stdio.h>
#include <ctype.h>
#include <dirent.h>

FILE *open_file(char *path);
FILE *create_file(char *path);
DIR *open_dir(char *path);
FILE *open_file_w_mode(char *path);

