#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main() 
{
  int fd = open("file.txt", O_RDONLY);
  if (fd < 0) 
  {
    perror("open()");
    return 1;
  }

  struct flock lock;
  lock.l_type = F_RDLCK;
  lock.l_whence = SEEK_SET;
  lock.l_start = 0;     // Read from byte 50
  lock.l_len = 30;       // Lock 30 bytes
  lock.l_pid = getpid();

    // Try to acquire read lock
  if (fcntl(fd, F_SETLK, &lock) == -1) 
  {
    perror("fcntl() - read lock failed");
    close(fd);
    return 1;
  }

    // Move the file pointer to byte 50
  if (lseek(fd, lock.l_start, SEEK_SET) == -1) 
  {
    perror("lseek()");
    close(fd);
    return 1;
  }

    
  char buffer[100];
  ssize_t len = read(fd, buffer, lock.l_len);
  if (len > 0) 
  {
    buffer[len] = '\0';
    printf("Reader: Read data = %s\n", buffer);
    
  } 
  else 
  {
    perror("read()");
  }

    // Unlock the region
  lock.l_type = F_UNLCK;
  fcntl(fd, F_SETLK, &lock);
  close(fd);
  return 0;
}
