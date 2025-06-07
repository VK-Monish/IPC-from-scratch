#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdlib.h>

int main()
{
  int pipe_fd[2];
  int df;
  char buf[52];
  df = pipe(pipe_fd);
  if(df == -1)
  {
    perror("pipe()");
  }
  write(pipe_fd[1],"Talk is cheap Show me the code said by\n",38);
  write(pipe_fd[1],"\nLINUS Torvalds",14);
  printf("%d\n",getpid());
  getchar();
  read(pipe_fd[0],buf,52);
  write(STDOUT_FILENO,buf,52);
  close(pipe_fd[0]);
  close(pipe_fd[1]);
  getchar();
  return 0;
}
