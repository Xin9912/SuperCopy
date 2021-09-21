#include "file_WR.h"

static char* fopen_type[][2] = 
{
    "rb","r","wb","w"
};

INT8 file_Process(FILE_OPT_S* read,FILE_OPT_S* write)
{
    FILE_DATA_S* data = NULL;

    if((NULL == read) || (NULL == write))
    {
        perror("file_process inputs failed!!!\n");
        return -1;
    }

    if(NULL == (data = (FILE_DATA_S *)calloc(1,sizeof(FILE_DATA_S) + BLKSIZE + 1)))
    {
        perror("Fail to calloc data!!!\n");
        return -1;
    }
    
    read->data = data;
    read->code = rd;
    write->data = data;
    write->code = wt;

    if((read->fd = fopen(read->filename,fopen_type[read->code][read->mode])) == NULL)
    {
        perror("Fail to fopen read file!!!\n");
        goto fail;
    }
    if((write->fd = fopen(write->filename,fopen_type[write->code][write->mode])) == NULL)
    {
        perror("Fail to fopen write file!!!\n");
        goto fail;
    }

    data->numblk = 1;

    do
    {
        data->len = file_Read(read);
        file_Write(write);
    }while(data->len == BLKSIZE);

    printf("Successful!!! Blknums: %d\n",data->numblk - 1);
    free(data);
    fclose(write->fd);
    fclose(read->fd);   
    return 0;

fail:
    free(data);
    fclose(write->fd);
    fclose(read->fd);   
    return  -1;
}

static INT16 file_Write(FILE_OPT_S* opt)
{
    FILE_DATA_S* data = NULL;
    char *temp = NULL;
    UINT16 i = 0;
    UINT16 total_size = 0;
    if(NULL == opt)
    {
        perror("Maybe last write failed/n");
        return -1;
    }

    data = opt->data;
    temp = data->buffer;
    if(!data->len)
        return 0;
    
    if(opt->mode == ASCII)
    {
        while(i < data->len)
        {
            i++;
            if(*temp == '\r')
            {
                if(*(temp + 1) == '\n')
                {
                    i++;
                    /*      读写缓冲区共用导致        */
                    if(i > data->len)
                        {
                            i--;
                            break;
                        }                       
                    temp++;                  
                    fwrite(temp,1,1,opt->fd);
                }
                else
                    fwrite(temp,1,1,opt->fd);
                temp++;
            }
            else
            {
                fwrite(temp,1,1,opt->fd);
                temp++;
            }
            total_size++;
        }
    }
    else
        i = fwrite(temp,1,data->len,opt->fd);

    if(i == data->len)
    {
        data->numblk++;
        return i;
    }
    else 
        return -1;
}

static INT16 file_Read(FILE_OPT_S* opt)
{
    static UINT16 rd_num = 0;
    char *temp = NULL;
    UINT16 tota_size = 0;
    int size = 0;
    FILE_DATA_S *data = opt->data;

    if(rd_num < data->numblk)
        rd_num++;
    else
    {
        perror("Maybe last write failed\n");
        return -1;
    }

    temp = data->buffer;

    if(opt->mode == ASCII)
    {
        if(temp[BLKSIZE] == '\n')
        {
            temp[BLKSIZE] = 0;
            *temp = '\n';
            temp++;
            tota_size++;
        }
        while(tota_size < BLKSIZE)
        {
            size = fread(temp,1,1,opt->fd);
            if(size == 0)
                return tota_size;
            if(*temp == '\n')
            {
                *temp = '\r';
                temp++;
                *temp = '\n';
                temp++;   
                tota_size += 2;
            }
            else
            {
                tota_size++;
                temp++;
            }
        }
        if(data->buffer[BLKSIZE] == '\n')
            return tota_size - 1;
    }
    else 
    {
        tota_size = fread(temp,1,BLKSIZE,opt->fd);      
    }
    return tota_size;
}

INT8 check_File(const char* rdfile,const char* wtfile)
{
    if(access(rdfile,F_OK) != 0)
    {
        printf("%s is not exist!!!\n",rdfile);
        return -1;
    }

    if(access(wtfile,F_OK) == 0)
        return 1;

    return 0;
}