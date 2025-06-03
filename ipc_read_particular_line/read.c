#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main() 
{
  int fd = open("file.txt", O_WRONLY | O_CREAT, 0666);
  if (fd < 0) 
  {
    perror("open()");
    return 1;
  }
  
  struct flock lock;
  lock.l_type = F_WRLCK;
  lock.l_whence = SEEK_SET;
  lock.l_start = 0;       // Lock first 50 bytes
  lock.l_len = 50;
  lock.l_pid = getpid();

  if (fcntl(fd, F_SETLK, &lock) == -1) 
  {
    perror("fcntl() - write lock failed");
    close(fd);
    return 1;
  }

  char *data = "This is some important data being written.";
  write(fd, data, strlen(data));
  printf("Writer: Data written and region locked.\n");

  sleep(10);  // Keep lock for 10 seconds to simulate writing
  lock.l_type = F_UNLCK;
  fcntl(fd, F_SETLK, &lock);
  printf("Writer: Lock released.\n");

  close(fd);
  return 0;
}
