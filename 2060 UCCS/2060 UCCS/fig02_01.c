// Fig. 2.1: fig02_01.c
// A first program in c.
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// function main begins program excution
int main(void) {

	// variables
	int length = 1;
	int width = 1;
	int area = 1;
	int divisionlw = 1; // This is the integer variable that holds the result of leght / width

	printf("Enter length: \n");
	scanf("%d", &length); // length input
	//printf("Length: %d", length); Used for testing 

	printf("Enter width: \n");
	scanf("%d", &width); // width input
	//printf("Width: %d", Width); Used for testing

	area = width * length; // area computation
	printf("Area: %d\n", area); // area output

	divisionlw = length / width; // division computation
	printf("Division result is %s\n ", divisionlw); 
	
	return 0;

} // end function main
