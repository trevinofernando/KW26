#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
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

int main(int argc, char *argv[])
{
  Int40 *p;
  Int40 *q;
  Int40 *r;
  int seed = 0;
  int fNum = 0;
  char *cryptoFilename;

  // Check if command line parms entered
  // IF none ->EXIT but leave a message
  if (argc == 1)
    {
      printf("\n\t usage:\n");
      printf("\t kw26-m5 cryptoFilename seedType\n\n");
      exit(1);
    }
  cryptoFilename = argv[1];
  seed = atoi(argv[2]);

  // Load crypto variable from the file named cryptoFilename

  // Load the HW config variable F[0]
  p = loadHWConfigVariable(seed);
  kw26Print(p); //print HW config variable F[0]

  // Load the Crypto Variable F[1]
  q = loadCryptoVariable(cryptoFilename);
  kw26Print(q); //print crypto variable F[1]

  printf("F(5)\n");
  r = fibKw26(5, p, q);
  kw26Print(r); //print F[n]

  printf("F(10)\n");
  r = fibKw26(10, p, q);
  kw26Print(r); //print F[n]

  printf("F(20)\n");
  r = fibKw26(20, p, q);
  kw26Print(r); //print F[n]


  return 0;
}
