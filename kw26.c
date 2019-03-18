#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>
#include <time.h>
#include "kw26.h"
#define ONLYHEX 0
#define PATTERN_SIZE 5

Int40 *kw26Add(Int40 *p, Int40 *q){
    int i, carry=0;
    Int40 *r=NULL;
    r = (Int40*)malloc(sizeof(Int40));
    r->digits = (int*)malloc(MAX40 * sizeof(int));
    memset(r->digits,0,sizeof(int) * MAX40);
    if ((NULL==r)||(NULL==p)||(NULL==q)||(NULL==r->digits)){
        return NULL;
    }
    for(i=0;i<MAX40;i++){
        r->digits[i]= p->digits[i] + q->digits[i] + carry;
        if(r->digits[i]>15){
            carry=1;
            r->digits[i]-=16;
        }
        else{
            carry=0;
        }
    }
    return r;
}

Int40 *kw26Destroyer(Int40 *p){
    if(NULL!=p){
        if(NULL!=p->digits){
            free(p->digits);
        }
        free(p);
    }
    return NULL;
}

Int40 *Int40Copy(Int40 *original){
    int i;
    Int40 *ogCopy =NULL;
    ogCopy = (Int40*)malloc(sizeof(Int40));
    ogCopy->digits = (int*)malloc(MAX40 * sizeof(int));
    if((ogCopy==NULL)||(ogCopy->digits==NULL)){
        return NULL;
    }
    for(i=0; i<MAX40; i++){
        ogCopy->digits[i]=original->digits[i];
    }
    return ogCopy;
}

Int40 *parseString(char *str){
    int i, len;
    Int40 *p=NULL;
    if(NULL==str){
        return NULL;
    }
    len=strlen(str);
    p = (Int40*)malloc(sizeof(Int40));
    p->digits = (int*)malloc(MAX40 * sizeof(int));
    memset(p->digits,0,sizeof(int) * MAX40);
    if((NULL==p)||(NULL==p->digits)){
        return NULL;
    }

    if(strlen(str)>MAX40){
        len=MAX40;
    }

    for(i=0, len=len; i<MAX40 && len>0; i++, len--){
        if(isdigit(str[len-1])){ //if its a number between 0 and 9
            p->digits[i]=str[len-1]-'0';//subtract value of '0' to get a digit from 0 to 9
        }
        else if(islower(str[len-1])){
            p->digits[i]=10 + str[len-1]-'a';//subtract value of 'a' to get a letter from a to z and add 10 to go back to A
            #if ONLYHEX
            if(p->digits[i]>'f'){//Not in hex
                p->digits[i]=0;
            }
            #endif // ONLYHEX
        }
        else if(isupper(str[len-1])){//check upper case
            p->digits[i]=10 + str[len-1]-'A';//subtract value of 'A' to get a letter from A to Z and add 10 to go back to A
            #if ONLYHEX
            if(p->digits[i]>'F'){//Not in hex
                p->digits[i]=0;
            }
            #endif // ONLYHEX
        }
        else{
            p->digits[i]=str[len-1];
        }
    }
    return p;
}

Int40 *fibKw26(int n, Int40 *first, Int40 *second){
    int i;
    Int40 *fib0, *fib1, *fibN=NULL;
    if(n==0){
        return Int40Copy(first);
    }
    else if(n==1){
        return Int40Copy(second);
    }
    else{
        fib0=Int40Copy(first);
        fib1=Int40Copy(second);
        for(i=2; i<=n ; i++){
            fibN=kw26Add(fib0,fib1);
            kw26Destroyer(fib0);
            fib0=Int40Copy(fib1);
            kw26Destroyer(fib1);
            fib1=Int40Copy(fibN);
        }
        kw26Destroyer(fib0);
        kw26Destroyer(fib1);
        return fibN;
    }
}

Int40 *loadHWConfigVariable(int seed){
    Int40* p = NULL;
    int i, j, numPattern = MAX40/5;//=8
    p = (Int40*)malloc(sizeof(Int40));
    p->digits = (int*)malloc(sizeof(int)*MAX40);
    memset(p->digits, 0, sizeof(int)*MAX40);
    if((p==NULL)||(p->digits==NULL)){
        return NULL;
    }
    srand(time(NULL));
    if(seed == 0){ //unseeded

        for(i=0; i<MAX40 ; i++){//fill array with 1's
            p->digits[i]=1;
        }
    }
    else{
        for(i=0; i<PATTERN_SIZE;i++){
            p->digits[i]=rand()%16;//5 random numbers
        }
        for(i=1; i<numPattern;i++){//repeating the pattern
            for(j=0; j<PATTERN_SIZE;j++){//filling the array with repeated 5 digits
                p->digits[i * PATTERN_SIZE + j]=p->digits[j];
            }
        }
    }
    return p;
}

Int40* loadCryptoVariable(char *cryptoVariableFilename){
    int i;
    char string[41]={0}, ch;
    FILE *fp=fopen(cryptoVariableFilename, "r");
    if(NULL == fp){
        return NULL;
    }
    for(i=0; i<MAX40;i++){
        ch=getc(fp);
        if(ch==EOF){
            break;
        }
        string[i]=ch;
    }
    return parseString(string);
}

Int40* loadPlainText(char *plainTextFilename){
    char *str=NULL;
    long f_size;
    int i, len=0;
    Int40 *p=NULL;
    FILE *fp=fopen(plainTextFilename, "r");
    if(NULL==fp){
        return NULL;
    }
    fseek(fp, 0, SEEK_END);//find the end of the file
    f_size = ftell(fp);//where is the end is the length of the file
    fseek(fp, 0, SEEK_SET);//go back to the beginning of the file
    str = malloc(f_size);//allocate the exact size of the file
    if(NULL==str){
        return NULL;
    }
    for(i=0; i<f_size;i++){
        str[i]=(char)fgetc(fp);
        len++;
    }
    /*
    do
    {
        *str++ = (char)fgetc(fp);
    } while(*str != EOF);
    */
    p = (Int40*)malloc(sizeof(Int40));
    p->digits = (int*)malloc(MAX40 * sizeof(int));

    if((NULL==p)||(NULL==p->digits)){
        return NULL;
    }
    memset(p->digits,0,sizeof(int) * MAX40);
    if(len>MAX40){
        len=MAX40;
    }
    for(i=0, len=len; i<MAX40 && len>0; i++, len--){
            p->digits[i]=(int)str[len-1];
        }
    return p;
}

Int40 *encrypt(Int40 *key, Int40 *inputText){
    Int40 *encryptText=NULL;
    int i;
    encryptText= (Int40*)malloc(sizeof(Int40));
    encryptText->digits = (int*)malloc(MAX40 * sizeof(int));
    memset(encryptText->digits,0,sizeof(int) * MAX40);
    if((NULL==encryptText)||(NULL==encryptText->digits)||(NULL==key)||(NULL==key->digits)){ //multy line if statement
        return 0;
    }
    //encryptText=parseString(inputText);
    if((NULL==encryptText)||(NULL==encryptText->digits)){ //multy line if statement
        return 0;
    }
    for(i=0; i<MAX40; i++){
        encryptText->digits[i]=key->digits[i]^inputText->digits[i];
    }
    return encryptText;
}

void kw26Rating(){
    char myNID[]= "fe961882";
    fprintf(stderr, "%s;%f;%f\n", myNID, 2.50, 10.0);
}
