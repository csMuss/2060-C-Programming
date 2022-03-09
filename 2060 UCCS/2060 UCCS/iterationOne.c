/*
Nick Chesi
CS2060 T-Th
OS: Windows
HW03 part B
Due: 02/24/22
Description: LA07

*/

#include<stdio.h> 
#include<ctype.h> 
#include<math.h>  

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
// constants
#define PIN 4932
#define LOWERPRICECOURT 200
#define UPPERPRICECOURT 500
#define LOWERPRICEMID 75
#define UPPERPRICEMID 200
#define LOWERPRICEUPPER 10
#define UPPERPRICEUPPER 75
#define CHARITYLOWER 5
#define CHARITYUPPER 25
#define MAXNUMBEROFTICKETSALLOWED 1000

// globals used for calculating the final price
int courtGlobalSold = 0;
int middleGlobalSold = 0;
int upperGlobalSold = 0;
double charityGlobalPercent = 0;

// pre processors 
int promptAdminPin();
int promptAdminSetupCourt();
int promptAdminSetupMid();
int promptAdminSetupUpper();
double adminPromptForCharityPercent();
void getZipCode();
int promptUserForTicket();
int validateUserInputNumber(int userInput);
void printSummary(int court, int middle, int upper);

// main
int main(void) {

	if (promptAdminPin() == 1) {

		courtGlobalSold = promptAdminSetupCourt();
		middleGlobalSold = promptAdminSetupMid();
		upperGlobalSold = promptAdminSetupUpper();
		charityGlobalPercent = adminPromptForCharityPercent();
		printf("NOW ENTERING CUSTOMER MODE:\n");
		while ((getchar()) != '\n');
		promptUserForTicket();
	}
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

		if (userInput != PIN) {
			printf("PIN INVALID, ATTEMPTS REMAINING: %d\n\n", counter - 1);
			counter--;
			boolIsAdminPinValid = 0;

			if (!isdigit(userInput)) {
				while ((getchar()) != '\n');
			}
		}
		else if (userInput == PIN) {
			printf("Pin Accepted\n");
			boolIsAdminPinValid = 1;
			counter = 0;
		}
	}

	if (counter == 0 && userInput != PIN) {
		printf("Too many failed attempts, program will now exit!\n");
	}

	return boolIsAdminPinValid;

}

/*
	Prompts the admin for the court setup and validates that its in range of the pre defined constants
*/

int promptAdminSetupCourt() {

	unsigned int userPriceInput = 0;
	unsigned int courtsidePrice = 0; 

	do {
		printf("Enter Ticket Price for Courtside (Between %d - %d): ", UPPERPRICECOURT, LOWERPRICECOURT);
		scanf("%d", &courtsidePrice);

		userPriceInput = courtsidePrice; 

		if (userPriceInput > UPPERPRICECOURT || userPriceInput < LOWERPRICECOURT) {
			printf("ERROR INPUT GREATER THAN %d OR LOWER THAN %d: %d \n", UPPERPRICECOURT, LOWERPRICECOURT, userPriceInput);
			while ((getchar()) != '\n');
		}
	} while (userPriceInput > UPPERPRICECOURT || userPriceInput < LOWERPRICECOURT);


	printf("Ticket price for courtside set to: %d\n", userPriceInput);
	return userPriceInput; 
}

/*
	Prompts the admin for the middle court set up with in the range of the pre defined constants
*/

int promptAdminSetupMid() {

	unsigned int userPriceInput = 0;
	unsigned int midPrice = 0;

	do {
		printf("Enter Ticket Price for Middle section (Between %d - %d): ", UPPERPRICEMID, LOWERPRICEMID);
		scanf("%d", &userPriceInput);

		midPrice = userPriceInput;

		if (midPrice > UPPERPRICEMID || midPrice < LOWERPRICEMID) {
			printf("ERROR INPUT GREATER THAN %d OR LOWER THAN %d: %d \n", UPPERPRICEMID, LOWERPRICEMID, userPriceInput);
			while ((getchar()) != '\n');
		}
	} while (midPrice > UPPERPRICEMID || midPrice < LOWERPRICEMID);


	printf("Ticket price for Middle section set to: %d\n", midPrice);
	return midPrice;
}

/*
	Prompts the admin for the upper court set up with in the range of the pre defined constants
*/

int promptAdminSetupUpper() {

	unsigned int userPriceInput = 0;
	unsigned int upper = 0;

	do {
		printf("Enter Ticket Price for Upper section (Between %d - %d): ", UPPERPRICEUPPER, LOWERPRICEUPPER);
		scanf("%d", &userPriceInput);

		upper = userPriceInput;

		if (upper > UPPERPRICEUPPER || upper < LOWERPRICEUPPER) {
			printf("ERROR INPUT GREATER THAN %d OR LOWER THAN %d: %d \n", UPPERPRICEUPPER, LOWERPRICEUPPER, userPriceInput);
			while ((getchar()) != '\n');
		}
	} while (upper > UPPERPRICEUPPER || upper < LOWERPRICEUPPER);


	printf("Ticket price for Upper section set to: %d\n", upper);
	return upper;
}

/*
	Prompts the admin for the charity percentage with in the range of the pre defined constants
*/

double adminPromptForCharityPercent() {

	double charityValue = 0;

	do {
		printf("Enter Charity percent: \n");
		scanf("%lf", &charityValue);

		if (charityValue < CHARITYLOWER) {
			printf("ERROR INVALID INPUT %.2lf IS LOWER THAN %d\n", charityValue, CHARITYLOWER);
			while ((getchar()) != '\n');
		}
		else if (charityValue > CHARITYUPPER) {
			printf("ERROR INVALID INPUT %.2lf IS GREATER THAN %d\n", charityValue, CHARITYUPPER);
			while ((getchar()) != '\n');
		}
	} while (charityValue < CHARITYLOWER || charityValue > CHARITYUPPER);

	printf("Charity Percent set to: %.2lf\n", charityValue);
	return charityValue;
}

/*
	Prompts the user for their ticket selection and does several computations to reach the final calculations, counts tickets for each row etc...
*/

int promptUserForTicket() {

	char getUserInput = 'a';

	int ticket = 0;

	int courtTickets = 0;
	int middleTickets = 0;
	int upperTickets = 0;
	int boolIsValidPin = 0;
	//int getZip = 0;
	//int ticketArray[3]; // HOLDS three variables, pos 0 all the tickets for court, pos 1 all the tickets for middle, pos 2 all the tickets for upper.

	while (!(tolower(getUserInput) == 'q') && boolIsValidPin == 0) {

		printf("Hello, Please select seating arrangment Courtside, Middle, or Upper (C,M,U): \n");
		scanf("%c", &getUserInput);

		if (tolower(getUserInput) == 'c') {

			printf("Courtside selected, Please select number of tickets(1-4): \n");
			scanf("%d", &ticket);

			if (ticket < 0 || ticket > MAXNUMBEROFTICKETSALLOWED) {
				printf("ERROR %d NOT ACCEPTED ONLY 1-%d ACCEPTED \n", ticket, MAXNUMBEROFTICKETSALLOWED);
				printf("Courtside selected, Please select number of tickets(1-4): \n");
				do {
					scanf("%d", &ticket);

					if (ticket < 0 || ticket > MAXNUMBEROFTICKETSALLOWED || isalpha(ticket)) {
						printf("ERROR %d NOT ACCEPTED ONLY 1-%d ACCEPTED \n", ticket, MAXNUMBEROFTICKETSALLOWED);
						ticket = 0;
						while ((getchar()) != '\n');
					}

				} while ((ticket < 0 || ticket > MAXNUMBEROFTICKETSALLOWED) && isalpha(ticket));
			}
			if(ticket > 0 || ticket < MAXNUMBEROFTICKETSALLOWED && isdigit(ticket)) {
				courtTickets += ticket;
				ticket = 0;
				getZipCode();
			}
		}

		if (tolower(getUserInput) == 'm') {

			printf("Middle Section selected, Please select number of tickets(1-4): \n");
			scanf("%d", &ticket);

			if (ticket < 0 || ticket > MAXNUMBEROFTICKETSALLOWED) {
				printf("ERROR %d NOT ACCEPTED ONLY 1-%d ACCEPTED \n", ticket, MAXNUMBEROFTICKETSALLOWED);
				printf("Courtside selected, Please select number of tickets(1-4): \n");
				do {
					scanf("%d", &ticket);

					if (ticket < 0 || ticket > MAXNUMBEROFTICKETSALLOWED || isalpha(ticket)) {
						printf("ERROR %d NOT ACCEPTED ONLY 1-%d ACCEPTED \n", ticket, MAXNUMBEROFTICKETSALLOWED);
						ticket = 0;
						while ((getchar()) != '\n');
					}

				} while ((ticket < 0 || ticket > MAXNUMBEROFTICKETSALLOWED) && isalpha(ticket));
			}
			if (ticket > 0 || ticket < MAXNUMBEROFTICKETSALLOWED && isdigit(ticket)) {
				middleTickets += ticket;
				ticket = 0;
				getZipCode();
			}
		}

		if (tolower(getUserInput) == 'u') {

			printf("Upper Section selected, Please select number of tickets(1-4): \n");
			scanf("%d", &ticket);

			if (ticket < 0 || ticket > MAXNUMBEROFTICKETSALLOWED) {
				printf("ERROR %d NOT ACCEPTED ONLY 1-%d ACCEPTED \n", ticket, MAXNUMBEROFTICKETSALLOWED);
				printf("Upper Section selected, Please select number of tickets(1-4): \n");
				do {
					scanf("%d", &ticket);

					if (ticket < 0 || ticket > MAXNUMBEROFTICKETSALLOWED || isalpha(ticket)) {
						printf("ERROR %d NOT ACCEPTED ONLY 1-%d ACCEPTED \n", ticket, MAXNUMBEROFTICKETSALLOWED);
						ticket = 0;
						while ((getchar()) != '\n');
					}

				} while ((ticket < 0 || ticket > MAXNUMBEROFTICKETSALLOWED) && isalpha(ticket));
			}
			if (ticket > 0 || ticket < MAXNUMBEROFTICKETSALLOWED && isdigit(ticket)) {
				upperTickets += ticket;
				ticket = 0;

				getZipCode();
			}
		}
		if (tolower(getUserInput) == 'q') {
			printf("ADMIN HAS QUIT, PRINTING SUMMARY...\n");
			if (promptAdminPin() == 1) {
				boolIsValidPin = 1;
				printSummary(courtTickets, middleTickets, upperTickets);
			}
			else {
				boolIsValidPin = 0;
				ticket = 0;
				getUserInput = 'a';
				printf("ERROR BAD PIN\n");
				while ((getchar()) != '\n');
			}
		}
		else {
			while ((getchar()) != '\n');
			ticket = 0;
			boolIsValidPin = 0;
		}
		printf("COURTSIDE TICKETS: %d\n", courtTickets);// DEBUG
		printf("MIDDLE TICKETS: %d\n", middleTickets);// DEBUG
		printf("UPPER TICKETS: %d\n", upperTickets);// DEBUG
		// ADD FUNCTIONS TO COMPUTE THE PREVIOUS VALUES takes courtickets, middle tickets and upper then multiplies them by the respective prices
	} 
	if (tolower(getUserInput) == 'q' && boolIsValidPin == 1) {
			printSummary(courtTickets, middleTickets, upperTickets);
	}

	return ticket;
}

/*
	Prompts the user for their zipcode for payment and verifys that it is correct
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
	Validates the correct input from the user
*/

int validateUserInputNumber(int userInput) {

	int holder = 0;

	if (scanf("%d", &userInput) == 1) {
		printf("VALID");
	}
	else {
		while((getchar()) != '\n');
		printf("ERROR");
	}

	return userInput;

}

/*
	Prints a summary of the purchased tickets 
*/

void printSummary(int court, int middle, int upper) {

	int courtTotal = courtGlobalSold * court;
	int middleTotal = middleGlobalSold * middle;
	int upperTotal = upperGlobalSold * upper;

	printf("\n\n\n\n\n\n\n\n\n============== Summary ==============\n");
	
	printf("Courtside Tickets sold: %d\nCourtside Sales: $%d\n",court, courtTotal);
	printf("=====================================\n");
	printf("Middle Section Tickets sold: %d\nMiddle Section Sales: $%d\n", middle, middleTotal);
	printf("=====================================\n");
	printf("Upper Section Tickets sold: %d\nUpper Section Sales: $%d\n", upper, upperTotal);
	printf("=====================================\n");

	int total = courtTotal + middleTotal + upperTotal;

	printf("Total tickets sold: %d\n", court + middle + upper);
	printf("Total Money Raised: $%d\n", total);
	printf("=====================================\n");

	double charityTotal = courtTotal * (charityGlobalPercent / 100) + middleTotal * (charityGlobalPercent / 100) + upperTotal * (charityGlobalPercent / 100);

	printf("Total Raised For Charity: $%.2lf", charityTotal);

	printf("\n=========== End of Summary ==========\n\n\n\n\n");
}
