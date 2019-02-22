#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <getopt.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#define MAXW 500
#define MAXC 32

typedef struct
{
    char seen[MAXC];
    size_t freq;

}wfstruct;
int get_word_freq(wfstruct *words, size_t *idx, FILE *file);
int compare(const void *a, const void *b);
int compare_by_frequency(wfstruct *a, wfstruct *b);
int get_word_freq_alpha(wfstruct *words, size_t *idx, FILE *file);