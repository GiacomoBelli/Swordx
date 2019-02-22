#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <getopt.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include "Structure.h"
#include "Reader.h"
#define MAXW 500
#define MAXC 32

int main(int argc,char *argv[])
{
clock_t start = clock();
char array[1000][1000];
char filename[1000];
struct dirent *in_file;
wfstruct words[MAXW] = {{{0}, 0}};
size_t i, idx = 0;
int c;
int j;
int num;
char *filename_to_exclude;
DIR *dir;
FILE *file;
const char *short_options = "hr:f:e:a:m:i:l:s:u";
const struct option long_options[] =
    {
        {"help", no_argument, 0, 'h'},
        {"recursive", required_argument, 0, 'r'},
        {"follow", no_argument, 0, 'f'},
        {"alpha", no_argument, 0, 'a'},
        {"exclude", required_argument, 0, 'e'},
        {"min", required_argument, 0, 'm'},
        {"ignore", required_argument, 0, 'i'},
        {"sortbyoccurences", no_argument, 0, 's'},
        {"log", no_argument, 0, 'm'},
        {"upgrade", required_argument, 0, 'u'},
        {NULL, 0, NULL, 0},
};
while((c = getopt_long(argc, argv, short_options, long_options, NULL)) != -1)
{
    switch (c)
    {
    case 'h':
    printf("%s\n", "Usage: swordx [OPTION]... [INPUT]...");
    printf("\n");
    printf("%s\n", " 'swordx' reads a file/folder,counts its occourencies and it saves it in a file.");
    printf("\n");
    printf(" [INPUT]		file or directory to be processed\n");
    printf(" [OPTION]  :\n");
    printf("\n");
    printf("  -h, --help                     print this help\n");
    printf("  --output [FILENAME]           write output in [FILE]\n");
    printf("                                (default output file is  /swordx.out)  \n");
    printf("  -r, --recursive                processes directories recursively     \n");
    printf("  -f, --follow                    follow links\n");
    printf("  -e [FILE], --explude [FILE]    [FILE] not processed                \n");
    printf("                                           (only works with -r)\n");
    printf("  -a, --alpha                    only process alphanumeric characters\n");
    printf("  -m[NUM], --min [NUM]           process words with more than [NUM] characters           \n");
    printf("  -i[FILE], --ignore[FILE]       [FILE] is a list of words to ignore      \n");
    printf("                                               (one word per line)      \n");
    printf("  -s, --sortbyoccurency           output file ordered by occurencies   \n");
    printf("  -l [FILE], --log [FILE]        create a log file with timing and stored/ignored words \n");
    printf("                                                                       \n");


        return 0;

    case 'r':
        dir = open_dir(argv[2]);
        while ((in_file = readdir(dir)) != NULL)
        {
            printf("%s\n", in_file->d_name);
            sprintf(filename, "%s/%s", argv[2], in_file->d_name);
            file = open_file(filename);
            get_word_freq(words, &idx, file);
            qsort(words, idx, sizeof *words, compare);
            printf("\nthe occurrence of words are:\n\n");
            for (i = 0; i < idx; i++)
            {
                printf("  %-28s : %zu\n", words[i].seen, words[i].freq);
            }
            
        }
        closedir(dir);
        return 0;
    case 'm':
        num = atoi(argv[2]);
        file = open_file(argv[3]);
        get_word_freq(words, &idx, file);
        qsort(words, idx, sizeof *words, compare);
        printf("\nthe occurrence of words are:\n\n");
        for (i = 0; i < idx; i++)
        {
            if (strlen(words[i].seen) >= num)
                printf("  %s : %zu\n", words[i].seen, words[i].freq);
        }
        return 0;
    case 's':
        file = open_file(argv[2]);
        get_word_freq(words, &idx, file);
        qsort(words, idx, sizeof *words, (int (*)(const void *, const void *))compare_by_frequency);
        printf("\nthe occurrence of words are:\n\n");
        for (i = 0; i < idx; i++)
            printf("  %s : %zu\n", words[i].seen, words[i].freq);

        return 0;
    case 'e':

        filename_to_exclude = (argv[5]);
        break;
    case 'a':
        file = open_file(argv[2]);
        get_word_freq_alpha(words, &idx, file);
        qsort(words, idx, sizeof *words, compare);
        printf("\nthe occurrence of words are:\n\n");
        for (i = 0; i < idx; i++)
        {
            printf("  %s : %zu\n", words[i].seen, words[i].freq);
        }
        return 0;
    case 'i':
        file = open_file(argv[2]);
        while (fscanf(file, "%1000c", array[j]) != EOF)
        {
            j++;
        }
        for (int p = 0; p < j; p++)
        {
            printf("%s\n", array[p]);
        }
        fclose(file);
        file = open_file(argv[3]);
        get_word_freq_alpha(words, &idx, file);
        qsort(words, idx, sizeof *words, compare);
        printf("\nthe occurrence of words are:\n\n");
        for (i = 0; i < idx; i++)
        {
            for (int p = 0; p < j; p++)
                if (strcmp(words[i].seen, array[p]) == 0)
                    words[i].seen == "\0";
        }
        for (i = 0; i < idx; i++)
        {
            printf("  %s : %zu\n", words[i].seen, words[i].freq);
        }
        return 0;
    case 'l':

        file = open_file(argv[2]);
        get_word_freq_alpha(words, &idx, file);
        qsort(words, idx, sizeof *words, compare);
        file = open_file_w_mode("logFile.log");
        clock_t end = clock();
        double cpu_timing = (double)(end - start) / CLOCKS_PER_SEC;
        fprintf(file, "%f\n%s\n%ld\n%d", cpu_timing, argv[2], idx, j);
        fclose(file);
        return 0;
    case 'u':
        file = open_file(argv[2]);
        get_word_freq_alpha(words, &idx, file);
        qsort(words, idx, sizeof *words, compare);
        file = open_file(argv[3]);
        for (i = 0; i < idx; i++)
        {
            fprintf(file, "%s:%zu\n", words[i].seen, words[i].freq);
            fclose(file);
        }
        return 0;
    }

}

if (argc < 2)
{
    get_word_freq(words, &idx, stdin);
}
else
{
    //read each file given on command line
    for (i = 1; i < (size_t)argc; i++)
    {

        // open file for reading
        if (!(file = open_file(argv[i])))
        {
            fprintf(stderr, "error: file open failed '%s'.\n", argv[i]);
            continue;
        }
        // check 'idx' against MAXW
        if (idx == MAXW)
            break;

        get_word_freq(words, &idx, file);
    }
}

//sort words alphabetically
qsort(words, idx, sizeof *words, compare);
printf("\nthe occurrence of words are:\n\n");
for (i = 0; i < idx; i++) {
    printf("  %-28s : %zu\n", words[i].seen, words[i].freq);

}
return 0;
}


    