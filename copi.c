#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{   
    FILE *file_ptr;
    FILE *stream;
    char ch;

    stream = fopen(argv[2], "w");

    file_ptr = fopen(argv[1],"r");

    if (NULL == file_ptr) {
        printf("fail.\r\n");
        return EXIT_FAILURE;
    }

    // printf("Contents of file %s:\r\n",argv[i]);

    while ((ch=fgetc(file_ptr)) != EOF) {
        fputc(ch, stream);
    }

    printf("\r\n");
    fclose(file_ptr);
    fclose(stream);
    return 0;
}
