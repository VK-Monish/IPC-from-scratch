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
