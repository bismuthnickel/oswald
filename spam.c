#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void print_usage(char* program_name) {
    printf("usage: %s <SPAM>... [FLAGS]...\n", program_name);
    printf("flags:\n");
    printf("  -l, -c, --limit, --count     (amount of times to spam, default: 5)\n");
    printf("  -d, --disable-new-lines      (disable new lines)\n");
    printf("  -s, --separator              (print in between each spam, default: ' ')\n");
}

int parse_arguments(int argc, char* argv[], int* limit, int* disable_new_lines, char** separator, int* spam_start_index) {
    *limit = 5;
    *disable_new_lines = 0;
    *separator = " ";
    *spam_start_index = 1;
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            if (strcmp(argv[i], "-l") == 0 || strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--limit") == 0 || strcmp(argv[i], "--count") == 0) {
                if (i + 1 < argc) {
                    sscanf(argv[i + 1], "%d", limit);
                    i++;
                } else {
                    fprintf(stderr, "Error: Missing value for -l / --limit flag\n");
                    return 1;
                }
            } else if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--disable-new-lines") == 0) {
                *disable_new_lines = 1;
            } else if (strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--separator") == 0) {
                if (i + 1 < argc) {
                    *separator = argv[i + 1];
                    i++;
                } else {
                    fprintf(stderr, "Error: Missing value for -s / --separator flag\n");
                    return 1;
                }
            }
        } else {
            *spam_start_index = i;
            break;
        }
    }
    if (*spam_start_index >= argc) {
        print_usage(argv[0]);
        return 1;
    }
    return 0;
}

int main(int argc, char* argv[]) {
    int limit, disable_new_lines, spam_start_index;
    char* separator;
    if (parse_arguments(argc, argv, &limit, &disable_new_lines, &separator, &spam_start_index)) {
        return 1;
    }
    for (int i = 0; i < limit; i++) {
        printf("%s", argv[spam_start_index]);
        if (i < limit - 1) {
            printf("%s", separator);
        }
    }
    if (!disable_new_lines) {
        printf("\n");
    }
    return 0;
}
