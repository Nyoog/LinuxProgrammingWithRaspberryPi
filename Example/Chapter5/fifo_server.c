#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFOFILE    "fifo"

int main(int argc, char** argv)
{
   int n, fd;
   char buf[BUFSIZ];

   unlink(FIFOFILE);                                            /* 기존의 FIFO파일을 삭제한다. */

   if(mkfifo(FIFOFILE, 0666) < 0) {                      /* 새로운 FIFO 파일을 생성한다. */
      perror("mkfifo( )");
      return -1;
   }

   if((fd = open(FIFOFILE, O_RDONLY)) < 0) {   /* FIFO를 오픈한다. */
      perror("open( )");
      return -1;
   }

   while((n = read(fd, buf, sizeof(buf))) > 0)          /* FIFO로 부터 데이터를 받아온다. */
     printf("%s", buf);                                              /* 읽어온 데이터를 화면으로 출력한다. */
                                 
   close(fd);

   return 0;
}

