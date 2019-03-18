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

	//40 digits
	kw26Print(p = parseString("0123456789abcdef0123456789abcdef01234567"));
	kw26Destroyer(p);

	//<40 digits
	kw26Print(p = parseString("354913546879519843519843548943513179"));
	kw26Destroyer(p);


	//>40 digits
	kw26Print(p = parseString("012345678901234567890123456789012345678901234567899999"));
	kw26Destroyer(p);

	//Null digits
	kw26Print(p = parseString(NULL));
	kw26Destroyer(p);

	//40 digit add
	p = parseString("ffffffffffffffffffffffffffffffffffffffff"); //40 fs
	q = parseString("1"); //just a single 1
	r = kw26Add( p, q);
	kw26Print(p); 
	kw26Print(q);
	kw26Print(r);

	//40 digit add
	p = parseString("7777777777777777777777777777777777777777"); //40 7s
	q = parseString("5555555555555555555555555555555555555555"); //40 5s
	r = kw26Add( p, q);
	kw26Print(p); 
	kw26Print(q);
	kw26Print(r);

		    

	return 0;
}

