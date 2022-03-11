/*
Nick Chesi
CS2060 T-Th
OS: Windows 10
HW05 Pass by reference 
Due: 03/15/22
Description: Pass by reference practice
*/

#include<stdio.h> 
#include<ctype.h> 
#include<math.h>  

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996) //  had to have this idk why but my ide just started being poopy and wouldnt just let me have the above define
#define ADMIN_PIN 4932
#define MAX_TICKETS_NUM 4
#define SEAT_SECTIONS 3 

const float courtsidePriceMinMax[2] = {500,200};
const float middleCourtPriceMinMax[2] = {200,75};
const float upperCourtPriceMinMax[2] = {75,10};
const float charityMinMax[2] = {25,5};

int promptAdminPin();
double * setUpValues();
double adminPromptForCharityPercent();
double * getCustomerTickets();

int main(void) {

	double * priceHolder;
	double * ticketHolder;
	double charityPercent = 0;
	double totalPrice = 0;

	priceHolder = setUpValues(); 
	charityPercent = adminPromptForCharityPercent();

	for (int i = 0; i < SEAT_SECTIONS; i++) {
		printf("Price %d: %.2lf\n", i, *(priceHolder + i));
	}

	printf("Entering Customer mode: \n");
	ticketHolder = getCustomerTickets();
	printf("ARE YOU SUPPOSED TO BE HERE??\n");
	printf("Tickets 0: %.2lf\n", *(ticketHolder + 0));
	printf("Tickets 1: %.2lf\n", *(ticketHolder + 1));
	printf("Tickets 2: %.2lf\n", *(ticketHolder + 2));
	return 0;
}

/*
	Prompts the user for their adminsitrator pin and confirms that its correct
*/

int promptAdminPin() {
	
	unsigned int counter = 3;
	unsigned int boolIsAdminPinValid = 0;
	unsigned int userInput = 0;

	while (counter > 0) {

		printf("Enter Admin Pin to continute(Attempt: %d): \n", counter);
		scanf("%d", &userInput);

		if (userInput != ADMIN_PIN) {
			printf("PIN INVALID, ATTEMPTS REMAINING: %d\n\n", counter - 1);
			counter--;
			boolIsAdminPinValid = 0;

			if (!isdigit(userInput)) {
				while ((getchar()) != '\n');
			}
		}
		else if (userInput == ADMIN_PIN) {
			printf("Pin Accepted\n");
			boolIsAdminPinValid = 1;
			counter = 0;
		}
	}

	if (counter == 0 && userInput != ADMIN_PIN) {
		printf("Too many failed attempts, program will now exit!\n");
	}

	return boolIsAdminPinValid;
}

/*
	Uses pointers to pass an array through a function and then sends it to main
*/

double * setUpValues() {

	static double prices[SEAT_SECTIONS];

	double userPriceInputCourt = 0;
	double courtsidePrice = 0;

	double userPriceInputMiddle = 0;
	double midPrice = 0;

	double userPriceInputUpper = 0;
	double upper = 0;

	int verifyPrices = 1;
	int boolIsValidPin = promptAdminPin();

	if (boolIsValidPin == 1) {
		while (verifyPrices == 1) {
			for (size_t i = 0; i < SEAT_SECTIONS; i++) {
				if (i == 0) {
					do {
						printf("Enter Ticket Price for Courtside (Between %.2f - %.2f): ", courtsidePriceMinMax[0], courtsidePriceMinMax[1]);
						scanf("%lf", &userPriceInputCourt);

						courtsidePrice = userPriceInputCourt;

						if (courtsidePrice > courtsidePriceMinMax[0] || courtsidePrice < courtsidePriceMinMax[1]) {
							printf("ERROR INPUT GREATER THAN %.2f OR LOWER THAN %.2f: %.2lf \n", courtsidePriceMinMax[0], courtsidePriceMinMax[1], courtsidePrice);
							while ((getchar()) != '\n');
						}
					} while (courtsidePrice > courtsidePriceMinMax[0] || courtsidePrice < courtsidePriceMinMax[1]);
					prices[i] = courtsidePrice;
					printf("Ticket price for Court section set to: %.2lf\n", courtsidePrice);
				}
				if (i == 1) {
					do {
						printf("Enter Ticket Price for Middle section (Between %.2f - %.2f): ", middleCourtPriceMinMax[0], middleCourtPriceMinMax[1]);
						scanf("%lf", &userPriceInputMiddle);

						midPrice = userPriceInputMiddle;

						if (midPrice > middleCourtPriceMinMax[0] || midPrice < middleCourtPriceMinMax[1]) {
							printf("ERROR INPUT GREATER THAN %.2f OR LOWER THAN %.2f: %.2lf \n", middleCourtPriceMinMax[0], middleCourtPriceMinMax[1], userPriceInputMiddle);
							while ((getchar()) != '\n');
						}
					} while (midPrice > middleCourtPriceMinMax[0] || midPrice < middleCourtPriceMinMax[1]);
					prices[i] = midPrice;
					printf("Ticket price for Middle section set to: %.2lf\n", midPrice);
				}
				if (i == 2) {
					do {
						printf("Enter Ticket Price for Upper section (Between %.2f - %.2f): ", upperCourtPriceMinMax[0], upperCourtPriceMinMax[1]);
						scanf("%lf", &userPriceInputUpper);

						upper = userPriceInputUpper;

						if (upper > upperCourtPriceMinMax[0] || upper < upperCourtPriceMinMax[1]) {
							printf("ERROR INPUT GREATER THAN %f OR LOWER THAN %.2f: %.2lf \n", upperCourtPriceMinMax[0], upperCourtPriceMinMax[1], userPriceInputUpper);
							while ((getchar()) != '\n');
						}
					} while (upper > upperCourtPriceMinMax[0] || upper < upperCourtPriceMinMax[1]);
					prices[i] = upper;
					printf("Ticket price for Upper section set to: %.2lf\n", upper);
				}
			}

			while ((getchar()) != '\n');
			char isCorrect = 'a';
			while (!(toupper(isCorrect) == 'Y')) {
				printf("Are prices entered correctly? (Y/N) \n");
				for (int j = 0; j < SEAT_SECTIONS; j++) {
					printf("Prices %d: %.2lf\n", j, prices[j]);
				}
				scanf("%c", &isCorrect);
				if (toupper(isCorrect) == 'Y') {
					isCorrect = 'Y';
					verifyPrices = 0;
				}
				if (toupper(isCorrect) == 'N') {
					isCorrect = 'Y';
					verifyPrices = 1;
				}
				else if(!(toupper(isCorrect) == 'Y') && !(toupper(isCorrect) == 'N')) {
					printf("ERROR INVALID INPUT\n");
					while ((getchar()) != '\n');
				}
			}
		}
	}
	else if (boolIsValidPin == 0) {
		printf("ERROR INVALID PIN PROGRAM WILL NOW EXIT\n");
	}

	return prices;
}

/*
	Prompts the admin for the charity percentage with in the range of the pre defined constants
*/

double adminPromptForCharityPercent() {

	double charityValue = 0;

	do {
		printf("Enter Charity percent: \n");
		scanf("%lf", &charityValue);

		if (charityValue < charityMinMax[1]) {
			printf("ERROR INVALID INPUT %.2lf IS LOWER THAN %.2f\n", charityValue, charityMinMax[1]);
			while ((getchar()) != '\n');
		}
		else if (charityValue > charityMinMax[0]) {
			printf("ERROR INVALID INPUT %.2lf IS GREATER THAN %.2f\n", charityValue, charityMinMax[0]);
			while ((getchar()) != '\n');
		}
	} while (charityValue < charityMinMax[1] || charityValue > charityMinMax[0]);

	printf("Charity Percent set to: %.2lf\n", charityValue);
	return charityValue;
}

double * getCustomerTickets() {

	static double numOfTickets[SEAT_SECTIONS];
	char charInput = 'a';

	int courtSideTicketNum = 0;
	int middleSectionTicketNum = 0;
	int upperSectionTicketNum = 0;

	int breaker = 0;
	int boolIsValidPin = 0;

	while ((getchar()) != '\n');

	while (breaker == 0) {
		do {
			printf("Please Enter Seat Selection Courtside, Middle, Upper (C,M,U): \n");
			scanf("%c", &charInput);

			if (toupper(charInput) == 'C') {
				do {
					printf("Please Enter Number of tickets to purchase Courtside Section: \n");
					scanf("%d", &courtSideTicketNum);
					if (courtSideTicketNum > MAX_TICKETS_NUM && courtSideTicketNum < MAX_TICKETS_NUM) {
						printf("ERROR NUMBER ENTERED IS GREATER THAN ALLOWED TICKETS: %d\n", courtSideTicketNum);
						while ((getchar()) != '\n');
					}
				} while (courtSideTicketNum > MAX_TICKETS_NUM && courtSideTicketNum < MAX_TICKETS_NUM);
				numOfTickets[0] = numOfTickets[0] + courtSideTicketNum;
				printf("Tickets Selected: %d\n", courtSideTicketNum);
			}

			if (toupper(charInput) == 'M') {
				do {
					printf("Please Enter Number of tickets to purchase Middle Section: \n");
					scanf("%d", &middleSectionTicketNum);
					if (middleSectionTicketNum > MAX_TICKETS_NUM && middleSectionTicketNum < MAX_TICKETS_NUM) {
						printf("ERROR NUMBER ENTERED IS GREATER THAN ALLOWED TICKETS: %d\n", middleSectionTicketNum);
						while ((getchar()) != '\n');
					}
				} while (middleSectionTicketNum < MAX_TICKETS_NUM && middleSectionTicketNum > MAX_TICKETS_NUM);
				numOfTickets[1] = numOfTickets[1] + middleSectionTicketNum;
				printf("Tickets Selected: %d\n", middleSectionTicketNum);
			}

			if (toupper(charInput) == 'U') {
				do {
					printf("Please Enter Number of tickets to purchase Upper Section: \n");
					scanf("%d", &upperSectionTicketNum);
					if (upperSectionTicketNum > MAX_TICKETS_NUM && upperSectionTicketNum < MAX_TICKETS_NUM) {
						printf("ERROR NUMBER ENTERED IS GREATER THAN ALLOWED TICKETS: %d\n", upperSectionTicketNum);
						while ((getchar()) != '\n');
					}
				} while (upperSectionTicketNum > MAX_TICKETS_NUM && upperSectionTicketNum < MAX_TICKETS_NUM);
				numOfTickets[2] = numOfTickets[2] + upperSectionTicketNum;
				printf("Tickets Selected: %d\n", upperSectionTicketNum);
			}

			if (toupper(charInput) == 'Q') {
				boolIsValidPin = promptAdminPin();
				if (boolIsValidPin == 1) {
					breaker = 1;
				}
				else {
					printf("ERROR INVALID PIN\n");
				}
			}
			else {
				while ((getchar()) != '\n');
			}

			printf("COURTSIDE TICKETS: %d\n", courtSideTicketNum);// DEBUG
			printf("MIDDLE TICKETS: %d\n", middleSectionTicketNum);// DEBUG
			printf("UPPER TICKETS: %d\n", upperSectionTicketNum);// DEBUG

		} while (!toupper(charInput) == 'Q');
	}
	return numOfTickets;
}
