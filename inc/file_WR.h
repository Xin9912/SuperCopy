#ifndef _FILE_WR_H
  #define _FILE_ER_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>

#define BLKSIZE 1024

typedef int INT32;
typedef short int INT16;
typedef unsigned short int UINT16;
typedef unsigned char UINT8;
typedef char INT8;
typedef unsigned int UINT32;
typedef long int INT64;

typedef struct
{
	UINT16 len;
	UINT32 numblk;
	char buffer[0];
}FILE_DATA_S;

typedef enum
{
	rd = 0,
	wt = 1
}opt_code_t;

typedef enum
{
	OCTET = 0,
	ASCII = 1
}opt_mode_t;

typedef struct
{
	char* filename;
	FILE_DATA_S *data;	
	FILE* fd;
	opt_mode_t mode;
	opt_code_t code;
}FILE_OPT_S;

INT8 file_Process(FILE_OPT_S* read,FILE_OPT_S* write);
static INT16 file_Write(FILE_OPT_S* opt);
static INT16 file_Read(FILE_OPT_S* opt);
INT8 check_File(const char* rdfile,const char* wtfile);

#endif