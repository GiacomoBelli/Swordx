#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <getopt.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include "Structure.h"
#define MAXW 500
#define MAXC 32

int get_word_freq(wfstruct *words, size_t *idx, FILE *file)
{
    char word[MAXC] = {0};
    size_t i;

    /* read first word into array, update index 'idx' */
    if (*idx == 0)
    {

        if (fscanf(file, " %32[^ ,.\t\n]%*c%*[!?-_'><@#*:;°]", word) == 1)
        {

            strcpy(words[*idx].seen, word);
            words[*idx].freq++;
            (*idx)++;
        }
        else
        {
            fprintf(stderr, "error: file read error.\n");
            return 1;
        }
    }

    /* read each word in file */
    while (fscanf(file, " %32[^ ,.\t\n]%*c%*[!?-_'><@#*:;°]", word) == 1)
    {
        /* check against all words in struct */
        for (i = 0; i < *idx; i++)
        {
            /* if word already 'seen', update 'words[i]. freq' count */

            if (strcmp(words[i].seen, word) == 0)
            {
                words[i].freq++;
                goto skipdup; /* skip adding word to 'words[i].seen' */
            }

        } /* add to 'words[*idx].seen', update words[*idx].freq & '*idx' */
        strcpy(words[*idx].seen, word);
        words[*idx].freq++;
        (*idx)++;

    skipdup:

        if (*idx == MAXW)
        { /* check 'idx' against MAXW */
            fprintf(stderr, "warning: MAXW words exceeded.\n");
            break;
        }
    }
    fclose(file);
    return 0;
    
}

int compare(const void *a, const void *b)
{
    wfstruct *ap = (wfstruct *)a;
    wfstruct *bp = (wfstruct *)b;
    return (strcmp(ap->seen, bp->seen));
}
/* qsort compare funciton by frequency */
int compare_by_frequency(wfstruct *a, wfstruct *b)
{
    if (a->freq < b->freq)
        return +1;
    if (a->freq > b->freq)
        return -1;
    return 0;
}
int get_word_freq_alpha(wfstruct *words, size_t *idx, FILE *file)
{
    char word[MAXC] = {0};
    size_t i;

    /* read first word into array, update index 'idx' */
    if (*idx == 0)
    {

        if (fscanf(file, " %32[^ ,.!?1234567890\t\n]%*c", word) == 1)
        {

            strcpy(words[*idx].seen, word);
            words[*idx].freq++;
            (*idx)++;
        }
        else
        {
            fprintf(stderr, "error: file read error.\n");
            return 1;
        }
    }

    /* read each word in file */
    while (fscanf(file, " %32[^ ,.!?1234567890\t\n]%*c", word) == 1)
    {
        /* check against all words in struct */
        for (i = 0; i < *idx; i++)
        {
            /* if word already 'seen', update 'words[i]. freq' count */

            if (strcmp(words[i].seen, word) == 0)
            {
                words[i].freq++;
                goto skipdup; /* skip adding word to 'words[i].seen' */
            }

        } /* add to 'words[*idx].seen', update words[*idx].freq & '*idx' */
        strcpy(words[*idx].seen, word);
        words[*idx].freq++;
        (*idx)++;

    skipdup:

        if (*idx == MAXW)
        { /* check 'idx' against MAXW */
            fprintf(stderr, "warning: MAXW words exceeded.\n");
            break;
        }
    }
    fclose(file);
    return 0;
}
