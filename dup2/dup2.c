#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() 
{
  int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
  if (fd < 0) 
  {
    perror("open");
    exit(EXIT_FAILURE);
  }
  
  if (dup2(fd, STDOUT_FILENO) == -1) 
  {
    perror("dup2");
    close(fd);
    exit(EXIT_FAILURE);
  }

  close(fd); 
  printf("Hello, World!\n");
}
