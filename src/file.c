#include "file_WR.h"

int main(int argc,char* argv[])
{
    FILE_OPT_S *read,*write = NULL;
    int val = 0;

    if(argc < 3)
    {
        goto param_error;
        exit(1);
    }
    
    if(NULL == (read = (FILE_OPT_S*)calloc(1,sizeof(FILE_OPT_S))))
    {
        perror("Fail to calloc memory for read!!!/n");
        exit(1);
    }

    if(NULL == (write = (FILE_OPT_S*)calloc(1,sizeof(FILE_OPT_S))))
    {
        perror("Fail to calloc memory for write!!!/n");
        exit(1);
    }
    
    if((val = check_File(argv[1],argv[2])) != 0)
    {
        if(val == -1)
            goto fail;
        if(strcmp(argv[argc - 1],"-f") != 0)
        {
            printf("%s is existed!!!\n",argv[2]);
            goto fail;         
        }
    }
        
    read->mode = (*(argv[3] + 1) == 't') ? ASCII : OCTET;
    write->mode = (*(argv[3] + 2) == 't') ? ASCII : OCTET;

    read->filename = argv[1];
    write->filename = argv[2];

    val = file_Process(read,write);

    if(val == -1)
        goto fail;
    else 
        return 0;

param_error:
    printf("Usage: ./spcp srcfile dstfile [-t/o][t/o] [-f]\n");
    printf("       srcfile：source filename\n");
    printf("       dstfile：destination filename\n");
    printf("       [-t/o]:  the mode you will read the source file. -t is for ASCII while -o is for OCTET. -o is default\n");
    printf("       [t/o]:  the mode you will write the destination file. -t is for ASCII while -o is for OCTET. o is default\n");
    printf("       [-f]: will overwrite the existing destination file\n");
    printf("   eg: ./spcp file.c file1.c -tt [-f]\n");
    return -1;

fail:
    free(read);
    free(write);
    printf("Super cp failed!!!\n");
    return -1;
}
