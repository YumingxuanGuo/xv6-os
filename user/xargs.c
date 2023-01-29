#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

int 
main(int argc, char *argv[]) 
{
    char buf[512], *argv2[MAXARG];
    memcpy(argv2, argv + 1, (argc - 1) * 8);
    while (strlen(gets(buf, 512)) != 0) {
      buf[strlen(buf) - 1] = 0;
        if (fork() == 0) {
            argv2[argc - 1] = buf;
            exec(argv2[0], argv2);
            exit(0);
        }
        else wait(0);
    }
    exit(0);
}