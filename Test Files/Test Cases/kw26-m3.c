#include <stdio.h>
#include <stdlib.h>

#include "kw26.h"

// print an Int40 (followed by a newline character)
void kw26Print(Int40 *p)
{
  int i;

  if (p == NULL)
    {
      printf("(null pointer)\n");
      return;
    }

  for (i = MAX40 - 1; i >= 0; i--)
    printf("%x", p->digits[i]);
  printf("\n");
}

int main(void)
{
  Int40 *p;
  Int40 *q;
  Int40 *r;

  // Load crypto variable from the file named cryptoVarFile

  // Load the unseeded HW config variable

  // Unseeded random number generator should generate
  // the same sequence of numbers in every run

  // NB The unseeded variable should have a repeating
  //    pattern of 5 "random" digits - 8 times.


  p = loadCryptoVariable("cryptoVarFile");
  q = loadHWConfigVariable(0);
  /*
    p = parseString("7656362109723093382194813785549032874959");
    q = parseString("1942719427194271942719427194271942719427");
  */
  r = kw26Add( p, q);
  kw26Print(p);
  kw26Print(q);
  kw26Print(r);

  return 0;
}
