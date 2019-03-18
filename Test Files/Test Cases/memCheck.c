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
		printf("%d", p->digits[i]);
	printf("\n");
}

int main(void)
{
    Int40 *p;
    Int40 *q;

    // Infinite loop. 
    while(1)
    {
	p = parseString("1010101010101");

// Use this block of code if your parseString function is broken
/*
       	p = malloc(sizeof(Int40));
        p->digits = malloc(40*sizeof(int));
        for (int j=0; j<40; j++)
        {
            p->digits[j] = j%16;
        }
*/
	// If your add function is broken then comment out both
	// q = kw26Add(p,p) & kw26Destroyer(q)
        q = kw26Add(p,p);
        kw26Destroyer(p);
        kw26Destroyer(q);
    }

    return 0;
}

