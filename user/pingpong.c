#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int p[2];
  pipe(p);

  char *byte = "_";

  if (fork() == 0) {
    char buffer[2];
    read(p[0], buffer, 1);
    printf("%d: received ping\n", getpid());
    write(p[1], byte, 1);
  } else {
    char buffer[2];
    write(p[1], byte, 1);
    read(p[0], buffer, 1);
    printf("%d: received pong\n", getpid());
  }

  exit(0);
}
