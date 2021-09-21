# SuperCopy
## Description <br>
It could copy file in ASCII/OCTET format between windows and Linux. It will perform by reading/writing one and one packet whose size is BLKSIZE(defined macro). BLKSIZE could be changed to other values, default is 1024 bytes. <br>

## Build<br>
linux and gcc is necessary.
<br>
`make -j[n]`<br>
The target will be placed in the out directory.
## Usage<br>
```linux
Usage: ./spcp srcfile dstfile -t/o[t/o] [-f]
       srcfile：source filename
       dstfile：destination filename
       -t/o:  the mode you will read the source file. -t is for ASCII while -o is for OCTET
       [t/o]:  the mode you will write the destination file. -t is for ASCII while -o is for OCTET. o is default
       [-f]: will overwrite the existing destination file
   eg: ./spcp file.c file1.c -tt [-f]
```
