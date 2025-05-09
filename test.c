#include "script.c"
#include <string.h>

ct
if (args > 1 && 0!=strcmp(argv[1], "--ct-no-rebuild")) {
  ctmd((char *[]){"tcc", SCRIPT, "-o", SRC_BUILD, "-I.", "-g", 0})
  ctrs((char *[]){SRC_BUILD, "--ct-no-rebuild", 0})
}
ctfn(hz)
  echo("hello world")
ctfne(hz)

ctfn(fn2)
  echo("this is 2nd fn")
ctfne(fn2)

ctrfn(hz)
ctrfn(fn2)
cte

