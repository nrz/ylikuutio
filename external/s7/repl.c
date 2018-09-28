#include <stdio.h>
#include <stdlib.h>

#include "s7.h"

int main(int argc, char **argv)
{
  s7_scheme *sc;
  sc = s7_init();

  if (argc == 2)
    {
      fprintf(stderr, "load %s\n", argv[1]);
      s7_load(sc, argv[1]);
    }
  else 
    {
      s7_load(sc, "repl.scm");
      s7_eval_c_string(sc, "((*repl* 'run))");
    }
  return(0);
}

/* gcc -o repl repl.c s7.o -Wl,-export-dynamic -lm -I. -ldl
 */
