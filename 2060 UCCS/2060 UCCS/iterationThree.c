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
#define MAX_TICKETS_NUM 10000
#define SEAT_SECTIONS 3 

const float courtsidePriceMinMax[2] = {500,200};
const float middleCourtPriceMinMax[2] = {200,75};
const float upperCourtPriceMinMax[2] = {75,10};
const float charityMinMax[2] = {25,5};

int promptAdminPin();
double * setUpValues();
double adminPromptForCharityPercent();
double * getCustomerTickets();
void getZipCode();
double * printSummary(double courtSideTicketNum, double middleTicketNum, double upperTicketNum, double courtsidePrice, double middlePrice, double upperPrice, double charityPercent);

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
	printSummary(*(ticketHolder + 0), *(ticketHolder + 1), *(ticketHolder + 2), *(priceHolder + 0), *(priceHolder + 1), *(priceHolder + 2), charityPercent);

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

	int verifyPrices = 1;
	double charityValue = 0;

	while (verifyPrices == 1) {
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

		while ((getchar()) != '\n');
		char isCorrect = 'a';
		while (!(toupper(isCorrect) == 'Y')) {
			printf("Is The Charity Percent Entered Correctly? (Y/N) \n");
			printf("Charity Percent: %.2lf\n", charityValue);

			scanf("%c", &isCorrect);

			if (toupper(isCorrect) == 'Y') {
				isCorrect = 'Y';
				verifyPrices = 0;
			}
			if (toupper(isCorrect) == 'N') {
				isCorrect = 'Y';
				verifyPrices = 1;
			}
			else if (!(toupper(isCorrect) == 'Y') && !(toupper(isCorrect) == 'N')) {
				printf("ERROR INVALID INPUT\n");
				while ((getchar()) != '\n');
			}
		}
	}

	printf("Charity Percent set to: %.2lf\n", charityValue);
	return charityValue;
}

/*
	Prompts the users for tickets and gets the amount of tickets
*/

double * getCustomerTickets() {

	static double numOfTickets[SEAT_SECTIONS];
	char charInput = 'a';

	int ticket = 0;

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

			if (tolower(charInput) == 'c') {

				printf("Courtside selected, Please select number of tickets(1-4): \n");
				scanf("%d", &ticket);

				if (ticket < 0 || ticket > MAX_TICKETS_NUM) {
					printf("ERROR %d NOT ACCEPTED ONLY 1-%d ACCEPTED \n", ticket, MAX_TICKETS_NUM);
					printf("Courtside selected, Please select number of tickets(1-4): \n");
					do {
						scanf("%d", &ticket);

						if (ticket < 0 || ticket > MAX_TICKETS_NUM || isalpha(ticket)) {
							printf("ERROR %d NOT ACCEPTED ONLY 1-%d ACCEPTED \n", ticket, MAX_TICKETS_NUM);
							ticket = 0;
							while ((getchar()) != '\n');
						}

					} while ((ticket < 0 || ticket > MAX_TICKETS_NUM) && isalpha(ticket));
				}
				if (ticket > 0 || ticket < MAX_TICKETS_NUM && isdigit(ticket)) {
					courtSideTicketNum += ticket;
					ticket = 0;
					getZipCode();
				}
			}

			if (tolower(charInput) == 'm') {

				printf("Middle Section selected, Please select number of tickets(1-4): \n");
				scanf("%d", &ticket);

				if (ticket < 0 || ticket > MAX_TICKETS_NUM) {
					printf("ERROR %d NOT ACCEPTED ONLY 1-%d ACCEPTED \n", ticket, MAX_TICKETS_NUM);
					printf("Courtside selected, Please select number of tickets(1-4): \n");
					do {
						scanf("%d", &ticket);

						if (ticket < 0 || ticket > MAX_TICKETS_NUM || isalpha(ticket)) {
							printf("ERROR %d NOT ACCEPTED ONLY 1-%d ACCEPTED \n", ticket, MAX_TICKETS_NUM);
							ticket = 0;
							while ((getchar()) != '\n');
						}

					} while ((ticket < 0 || ticket > MAX_TICKETS_NUM) && isalpha(ticket));
				}
				if (ticket > 0 || ticket < MAX_TICKETS_NUM && isdigit(ticket)) {
					middleSectionTicketNum += ticket;
					ticket = 0;
					getZipCode();
				}
			}

			if (tolower(charInput) == 'u') {

				printf("Upper Section selected, Please select number of tickets(1-4): \n");
				scanf("%d", &ticket);

				if (ticket < 0 || ticket > MAX_TICKETS_NUM) {
					printf("ERROR %d NOT ACCEPTED ONLY 1-%d ACCEPTED \n", ticket, MAX_TICKETS_NUM);
					printf("Upper Section selected, Please select number of tickets(1-4): \n");
					do {
						scanf("%d", &ticket);

						if (ticket < 0 || ticket > MAX_TICKETS_NUM || isalpha(ticket)) {
							printf("ERROR %d NOT ACCEPTED ONLY 1-%d ACCEPTED \n", ticket, MAX_TICKETS_NUM);
							ticket = 0;
							while ((getchar()) != '\n');
						}

					} while ((ticket < 0 || ticket > MAX_TICKETS_NUM) && isalpha(ticket));
				}
				if (ticket > 0 || ticket < MAX_TICKETS_NUM && isdigit(ticket)) {
					upperSectionTicketNum += ticket;
					ticket = 0;
					getZipCode();
				}
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

			numOfTickets[0] = courtSideTicketNum;
			numOfTickets[1] = middleSectionTicketNum;
			numOfTickets[2] = upperSectionTicketNum;

			printf("COURTSIDE TICKETS: %d\n", courtSideTicketNum);// DEBUG
			printf("MIDDLE TICKETS: %d\n", middleSectionTicketNum);// DEBUG
			printf("UPPER TICKETS: %d\n", upperSectionTicketNum);// DEBUG

		} while (!toupper(charInput) == 'Q');
	}
	return numOfTickets;
}

/*
	Gets the zipcode and verifys its correct
*/

void getZipCode() {

	int zip = 0;

	do {
		printf("Enter zip code for payment: \n");
		scanf("%d", &zip);
		if (zip < 10000 || zip > 99999) {
			printf("INVALID ZIP CODE\n");
			while ((getchar()) != '\n');
		}
	} while (zip < 10000 || zip > 99999);

}

/*
	Gets the inputs and prints the summary
*/

double * printSummary(double courtSideTicketNum, double middleTicketNum, double upperTicketNum, double courtsidePrice, double middlePrice, double upperPrice, double charityPercent) {

	static double totalPrices[SEAT_SECTIONS];

	double charityTotal = 0;
	double totalTickets = 0;
	double totalPrice = 0;

	for (int i = 0; i < SEAT_SECTIONS; i++) {
		if (i == 0) {
			totalPrices[i] = courtSideTicketNum * courtsidePrice;
		}
		if (i == 1) {
			totalPrices[i] = middleTicketNum * middlePrice;
		}
		if (i == 2) {
			totalPrices[i] = upperTicketNum * upperPrice;
		}
	}

	totalPrice = totalPrices[0] + totalPrices[1] + totalPrices[2];
	charityTotal = totalPrice * (charityPercent / 100);
	totalTickets = courtSideTicketNum + middleTicketNum + upperTicketNum;
		
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n========== Summary ==========\n");

	printf("Courtside Tickets Sold: %.2lf\n", courtSideTicketNum);
	printf("Middle Tickets Sold: %.2lf\n", middleTicketNum);
	printf("Upper Tickets Sold: %.2lf\n\n", upperTicketNum);

	printf("Courtside Tickets Prices: $%.2lf\n", totalPrices[0]);
	printf("Middle Tickets Prices: $%.2lf\n", totalPrices[1]);
	printf("Upper Tickets Prices: $%.2lf\n\n", totalPrices[2]);

	printf("Total Tickest Sold: %.2lf\n", totalTickets);
	printf("Total Amount Sold: $%.2lf\n\n", totalPrice);
	printf("Total Donated To Charity: $%.2lf\n", charityTotal);

	printf("======= End of Summary ======\n\n\n\n\n\n\n\n\n\n\n");

	return totalPrices;
}
