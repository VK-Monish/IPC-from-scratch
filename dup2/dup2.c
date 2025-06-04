/*
 * Program Name: redirect_stdout_to_file.c
 * Description:
 *   This program demonstrates how to redirect the standard output (stdout)
 *   to a file using the `dup2()` system call in a Linux environment.
 * 
 *   Steps performed:
 *   1. Opens (or creates) a file named "output.txt" with write-only permission.
 *   2. Uses `dup2()` to duplicate the file descriptor to STDOUT_FILENO,
 *      which redirects all `printf()` output to the file.
 *   3. Closes the original file descriptor as it's no longer needed.
 *   4. Prints "Hello, World!" — this will be written to "output.txt" instead of the terminal.
 *
 * File Permissions:
 *   - The file is created with 0644 permissions: 
 *     Owner: read/write, Group: read, Others: read.
 *
 * Compilation:
 *   gcc redirect_stdout_to_file.c -o redirect
 *
 * Execution:
 *   ./redirect
 *
 * After running, check the contents of "output.txt":
 *   cat output.txt
 *   => Hello, World!
 */

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
