#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{   
    FILE *file_ptr;
    char ch;

    for (int i = 1; i < argc; i++) {
        file_ptr = fopen(argv[i],"r");

        if (NULL == file_ptr) {
            printf("fail.\r\n");
            return EXIT_FAILURE;
        }

        // printf("Contents of file %s:\r\n",argv[i]);

        while ((ch=fgetc(file_ptr)) != EOF) {
            printf("%c", ch);
        }

        printf("\r\n");
        fclose(file_ptr);
    }
    return 0;
}
