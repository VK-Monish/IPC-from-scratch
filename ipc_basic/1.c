/*
===============================================================================
Project Title : File Locking using fcntl()
File Name     : file_lock_writer.c
Description   : 
    This program demonstrates how to apply a write lock on a file using 
    System-level file locking with `fcntl()` in C. It creates or opens a 
    file named "file.txt", applies a write lock to ensure exclusive access, 
    writes a message containing the process ID (PID), holds the lock for 5 
    seconds (simulating processing), and then unlocks the file before exiting.

Key Concepts  :
    - File descriptors using `open()`
    - Record/file locking with `fcntl()` and `struct flock`
    - Exclusive write locking (F_WRLCK)
    - Lock releasing (F_UNLCK)
    - Basic file I/O and process management in Unix/Linux

Usage         :
    1. Compile: `gcc file_lock_writer.c -o writer`
    2. Run: `./writer`
    3. Observe the lock behavior by running this with another process 
       trying to access the same file (e.g., another writer/reader).
===============================================================================
*/

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

