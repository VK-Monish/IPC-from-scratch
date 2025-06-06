/*
 * File: file_copy_with_dup.c
 * Description:
 *   This program demonstrates file copying using the `dup()` system call.
 *   It reads data from a source file named "a.txt" and writes it to a
 *   destination file named "b.txt" using a duplicated file descriptor.
 *
 *   Steps:
 *   1. Opens "a.txt" in read-only mode.
 *   2. Opens (or creates) "b.txt" in write-only mode, truncating it if it exists.
 *   3. Uses `dup()` to duplicate the destination file descriptor.
 *   4. Reads chunks of data from "a.txt" into a buffer.
 *   5. Writes the buffer contents to "b.txt" using the duplicated descriptor.
 *   6. Closes all file descriptors properly.
 *
 * Notes:
 *   - The `dup()` system call creates a copy of the file descriptor that refers
 *     to the same open file description.
 *   - File permissions for the created "b.txt" are set to 0644 (rw-r--r--).
 *
 * Compilation:
 *   gcc file_copy_with_dup.c -o file_copy_with_dup
 *
 * Usage:
 *   Ensure "a.txt" exists in the current directory before running.
 *   ./file_copy_with_dup
 */

#include <fcntl.h>
#include <unistd.h>

int main() 
{
  int src = open("a.txt", O_RDONLY);
  int dst = open("b.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
  
  int dup_dst = dup(dst);  // Duplicate the destination file descriptor

  char buf[100];
  int n;

  while ((n = read(src, buf, sizeof(buf))) > 0)
  {
    write(dup_dst, buf, n);  // Use the duplicated descriptor
  }

  close(src);
  close(dst);
  close(dup_dst);
}
