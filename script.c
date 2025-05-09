#ifndef SCRIPT_H__
#define SCRIPT_H__
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/unistd.h>
#define ct int _ct(int args, char ** argv) {
#define cte return 0; }

#ifndef SCRIPT
#  define SCRIPT "main.c"
#endif
#ifndef SRC_BUILD
#  define SRC_BUILD "./main"
#endif
#ifndef __CT_REBUILD
#  define __CT_REBUILD ctmd((char *[]){"cc", SCRIPT, "-o", SRC_BUILD, "-I.", "-g", 0})
#endif

#define ctr(...) int \
main (int args, char ** argv) \
{ \
  __VA_ARGS__ \
}

int _ctmd(char ** args) {
  pid_t pid = fork();
  if (pid < 0) {
    puts("SCRIPTS: Can't fork");
    return 1;
  } else if (!pid) {
    execvp(args[0], args);
    puts("SCRIPTS: Error during this command");
    printf("args[0] == %s\n", args[0]);
    exit(1);
  } else {
    int stat=0;
    waitpid(pid, &stat, 0);

    if (WIFEXITED(stat) && WEXITSTATUS(stat)) {
      printf("SCRIPTS: Error: %d\n", WEXITSTATUS(stat));
      exit(1);
    }
  }

  return 0;
}

#define ctmd(...) _ctmd(__VA_ARGS__);
#define echo(x) ctmd((char *[]){"echo", x, 0})
#define ctfn(x) x: 
#define ctfne(x) goto x##_end;
#define ctrfn(x) goto x;\
x##_end:
#define ctrs(...) ctmd(__VA_ARGS__) exit(0);

#ifdef build
int main() {
  __CT_REBUILD;
  ctmd((char *[]){SRC_BUILD, 0})
  return 0;
}
#endif


#ifndef build
int _ct(int args, char ** argv);
ctr(_ct(args,argv);)
#endif

#endif // SCRIPT_H__
