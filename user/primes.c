#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int p_left[2];
  pipe(p_left);

  if (fork() == 0) {
    close(p_left[1]);
    char buffer[sizeof(int)];

    while (read(p_left[0], buffer, sizeof(int)) > 0) {
      int seed = (int) buffer[0];
      printf("prime %d\n", seed);

      int p_right[2];
      pipe(p_right);

      if (fork() == 0) {
        close(p_left[0]);
        p_left[0] = p_right[0];
        close(p_right[1]);
      } else {
        while (read(p_left[0], buffer, sizeof(int)) > 0) {
          int i = (int) buffer[0];
          if (i % seed != 0)
            write(p_right[1], &i, sizeof(int));
        }
        close(p_right[0]);
        close(p_right[1]);
        wait(0);
        exit(0);
      }
    }
  } else {
    close(p_left[0]);
    for (int i = 2; i <= 35; i++) {
      write(p_left[1], &i, sizeof(int));
    }
    close(p_left[1]);
    wait(0);
  }

  exit(0);
}
