#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>


int main()
{
  char *filename = "file.txt";
  char buf[1024];
  struct flock lock;
  int fd, len;

  lock.l_type = F_WRLCK;
  lock.l_whence = SEEK_SET;
  lock.l_start = 0;
  lock.l_len = 0;
  lock.l_pid = getpid();

  len = snprintf(buf, 1024, "Data: process1 PID : %d",getpid());
  fd = open(filename, O_RDWR | O_CREAT, 0666);
  if(fd < 0)
  {
    perror("open() failed !!");
    exit(EXIT_FAILURE);
  }

  if( fcntl(fd, F_SETLK, &lock) < 0 )
  {
    perror("fcntl() failed !!");
    exit(EXIT_FAILURE);
  }
  else
  {
    write(fd, buf, len);
    printf("Process %d write data \n",lock.l_pid);
    sleep(5);
  }

  lock.l_type = F_UNLCK;
  if(fcntl(fd, F_SETLK, &lock) < 0)
  {
    perror("fcntl() unlocking failed !!");
    exit(EXIT_FAILURE);
  }

  close(fd);
  exit(EXIT_SUCCESS);
}

