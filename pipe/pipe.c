/*
===============================================================================
Title       : Quote Through Pipe (LINUS Torvalds)
File        : pipe_quote.c
Author      : Monish Kumar.k
Description :
    This C program demonstrates inter-process communication using pipes.

    - It creates a unidirectional pipe using `pipe()`.
    - It writes a famous quote by Linus Torvalds to the write end of the pipe.
    - The same process reads the content from the read end of the pipe and
      writes it to standard output (STDOUT).
    - The program uses `getpid()` to print its process ID, and `getchar()` 
      is used to pause execution, allowing observation of the behavior.

    Quote Used:
        "Talk is cheap. Show me the code" — Linus Torvalds

Compilation :
    gcc pipe_quote.c -o pipe_quote

Execution :
    ./pipe_quote

Notes :
    - This program uses blocking `read()` and `write()` system calls.
    - Only one process is involved; no fork is used. It's a self-contained
      example of how pipes can be used within a single process.
    - Ensure proper buffer size is maintained while reading from the pipe.
===============================================================================
*/

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
