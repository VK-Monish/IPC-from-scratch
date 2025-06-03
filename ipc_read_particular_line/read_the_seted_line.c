#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>

#define buffer_size 1024

int main()
{
  char *filename = "file.txt";
  char buf[1024];
  struct flock lock;
  int fd, len_read;

  lock.l_type = F_RDLCK;
  lock.l_whence = SEEK_SET;
  lock.l_start = 0;
  lock.l_len = 30;
  lock.l_pid = getpid();

  fd = open(filename, O_RDONLY);

  if((fcntl(fd,F_SETLK,&lock)) < 0)
  {
    perror("fcntl()");
    exit(-1);
  }
  len_read = read(fd,buf,lock.l_len);
  
  if(len_read == -1)
  {
    perror("read()");
    exit(-1);
  }
  buf[len_read]='\0';
  printf("The readed data : %s\n",buf);

  lock.l_type = F_UNLCK;

  if((fcntl(fd,F_SETLK,&lock)) > 0)
  {
    perror("fcntl()");
    exit(-1);
  }
  close(fd);
}
