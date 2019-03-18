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

  // Load crypto variable from the file named cryptoVarFile
  kw26Print(p = loadCryptoVariable("cryptoVarFile"));
  kw26Destroyer(p);

  // Load the unseeded HW config variable

  // NB The seeded variable should have a repeating
  //    pattern of 5 random digits - 8 times.
  // NB The unseeded variable should have the digit "1"
  //    40 times. The 0 parameter below is unseeded.
  kw26Print(p = loadHWConfigVariable(0));
  kw26Destroyer(p);

  // Load the SEEDED HW config variable

  // SEEDED random number generator should generate
  // a different sequence of numbers in every run
  // Remember the number should be 5 random digits that 
  // repeat 8 times for 40 digits.

  kw26Print(p = loadHWConfigVariable(1));
  kw26Destroyer(p);

  return 0;
}
