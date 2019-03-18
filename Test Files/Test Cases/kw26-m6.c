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

// print an Int40 with TWO hex chars for all 40 ints
void kw26PrintBy2X(Int40 *p)
{
  int i;

  if (p == NULL)
    {
      printf("(null pointer)\n");
      return;
    }

  for (i = MAX40 - 1; i >= 0; i--)
    printf("%02X", p->digits[i]);
  printf("\n");
}

int main(int argc, char *argv[])
{
  Int40 *p; //F[0]
  Int40 *q; //F[1]
  Int40 *r; //F[x]
  Int40 *t; // used for plain text
  Int40 *encryptedText; // crypto data
  Int40 *decryptedText; // un-crypto data  
  int seed = 0;
  int fNum = 0;
  char *cryptoFilename;
  char *inputPlainTextFilename;
    

  // Check if command line parms entered
  // IF none ->EXIT but leave a message
  if (argc == 1)
    {
      printf("\n\t usage:\n");
      printf("\t kw26-m6 cryptoFilename inputPlainTextFilename F[N] seedType\n\n");
      exit(1);
    }
  cryptoFilename = argv[1];
  inputPlainTextFilename = argv[2];
  fNum = atoi(argv[3]);
  seed = atoi(argv[4]);

  // Load crypto variable from the file named cryptoFilename

  // Load the HW config variable F[0]
  p = loadHWConfigVariable(seed);
  kw26Print(p); //print HW config variable F[0]

  // Load the Crypto Variable F[1]
  q = loadCryptoVariable(cryptoFilename);
  kw26Print(q); //print crypto variable F[1]

  printf("F(%d)\n", fNum);
  r = fibKw26(fNum, p, q);
  kw26Print(r); //print F[fNum] one hex digit at a time
  kw26PrintBy2X(r); //print F[fNum] two hex digits per each input digit

  // load the plain text 
  t = loadPlainText(inputPlainTextFilename);
  kw26PrintBy2X(t); //print two hex digits per each input character

  //encrypt the plain text, t, with the key, r
  encryptedText = encrypt(r, t);
  kw26PrintBy2X(encryptedText); //print two hex digits per each input character

  //decrypt the encrypted text, encryptedText, with the key, r
  decryptedText = encrypt( encryptedText, r);
  kw26PrintBy2X(decryptedText); //print two hex digits per each input character
  
  return 0;
}
