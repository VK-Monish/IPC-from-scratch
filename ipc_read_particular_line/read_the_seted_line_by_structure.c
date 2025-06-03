#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

#define max 1024

struct filedata
{
  char content[max];
  ssize_t size;
};

int main()
{
  struct flock lock;
  int fd;
  char *filename = "file.txt";
  struct filedata con;
  
  lock.l_type   = F_RDLCK;
  lock.l_whence = SEEK_SET;
  lock.l_start  = 0;
  lock.l_len    = 122;
  lock.l_pid    = getpid();
  
  fd = open(filename, O_RDONLY);
  
  if((fcntl(fd,F_SETLK,&lock)) < 0)
  {
    perror("fcntl()");
    exit(-1);
  }

  con.size = read(fd, con.content, lock.l_len);
  
  if(con.size == -1)
  {
    perror("read()");
    exit(-1);
  }
  con.content[con.size] = '\0';
  printf("The sizeof file is : %ld\nThe the readed file data is : %s\n",con.size,con.content);

  lock.l_type = F_UNLCK;

  if((fcntl(fd,F_SETLK,&lock)) < 0)
  {
    perror("fcntl()");
    exit(-1);
  }
  close(fd);
}
