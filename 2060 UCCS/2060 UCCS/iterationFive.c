/*
Nick Chesi
CS2060 T-Th
OS: Windows 10
HW05 Pass by reference
Due: 03/15/22
Description: Pass by reference practice
*/

#include<stdio.h> 
#include<math.h>  

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996) //  had to have this idk why but my ide just started being poopy and wouldnt just let me have the above define
#define MAX_TICKETS_NUM 4
#define SEAT_SECTIONS 3 

const int ADMIN_PIN = 4932;
const float courtsidePriceMinMax[2] = { 500,200 };
const float middleCourtPriceMinMax[2] = { 200,75 };
const float upperCourtPriceMinMax[2] = { 75,10 };
const float charityMinMax[2] = { 25,5 };

int promptAdminPin();
double* setUpValues();
double adminPromptForCharityPercent();
double* getCustomerTickets(double charityPercent, double courtSideCost, double middleCost, double upperCost);
double getCourtsideTicket(double charityPercent, double courtSideCost);
double getMiddleSectionTicket(double charityPercent, double middleCost);
double getUpperSectionTicket(double charityPercent, double upperCost);
void getZipCode();
void printReciept(int level, double numOfTickets, double charityAmout, double totalCost);
int verifyYesNo(int receipt);
double* printSummary(double courtSideTicketNum, double middleTicketNum, double upperTicketNum, double courtsidePrice, double middlePrice, double upperPrice, double charityPercent);

int main(void) {

	double* priceHolder;
	double* ticketHolder;
	double* cost;
	double charityPercent = 0;
	double totalPrice = 0;

	if (promptAdminPin() == 1) {
		priceHolder = setUpValues();
		charityPercent = adminPromptForCharityPercent();

		for (int i = 0; i < SEAT_SECTIONS; i++) {
			printf("Price %d: %.2lf\n", i, *(priceHolder + i));

		}
		printf("Entering Customer mode: \n");
		ticketHolder = getCustomerTickets(charityPercent, *(priceHolder + 0), *(priceHolder + 1), *(priceHolder + 2));
		printSummary(*(ticketHolder + 0), *(ticketHolder + 1), *(ticketHolder + 2), *(priceHolder + 0), *(priceHolder + 1), *(priceHolder + 2), charityPercent);
	}

	return 0;
}

/*
	Prompts the user for their adminsitrator pin and confirms that its correct
*/

int promptAdminPin() {

	unsigned int counter = 3;
	unsigned int boolIsAdminPinValid = 0;
	int userInput = 0;

	while (counter > 0) {

		printf("Enter Admin Pin to continute(Attempt: %d): \n", counter);
		scanf("%d", &userInput);

		if (userInput != ADMIN_PIN) {
			printf("PIN INVALID, ATTEMPTS REMAINING: %d\n\n", counter - 1);
			counter--;
			boolIsAdminPinValid = 0;
			while ((getchar()) != '\n');
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

double* setUpValues() {

	static double prices[SEAT_SECTIONS];

	double userPriceInputCourt = 0;
	double courtsidePrice = 0;

	double userPriceInputMiddle = 0;
	double midPrice = 0;

	double userPriceInputUpper = 0;
	double upper = 0;

	int verifyPrices = 1;
	int boolIsValidPin = 0;

	boolIsValidPin = 1;

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
			int isCorrect = 0;
			while ((getchar()) != '\n');
			for (int j = 0; j < SEAT_SECTIONS; j++) {
				printf("Prices %d: %.2lf\n", j, prices[j]);
			}

			isCorrect = verifyYesNo(0);

			if (isCorrect == 1) {
				verifyPrices = 0;
			}
			if (isCorrect == 0) {
				verifyPrices = 1;
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
		int isCorrect = 0;
		isCorrect = verifyYesNo(0);

		if (isCorrect == 1) {
			verifyPrices = 0;
		}
		if (isCorrect == 0) {
			verifyPrices = 1;
		}
	}

	printf("Charity Percent set to: %.2lf\n", charityValue);
	return charityValue;
}

/*
	Prompts the users for tickets and gets the amount of tickets
*/

double* getCustomerTickets(double charityPercent, double courtSideCost, double middleCost, double upperCost) {

	static double numOfTickets[SEAT_SECTIONS];
	char charInput = 'a';
	char isCorrect = 'a';

	int courtSideTicketNum = 0;
	int middleSectionTicketNum = 0;
	int upperSectionTicketNum = 0;
	int ynBreaker = 0;
	int breaker = 0;
	int boolIsValidPin = 0;

	while ((getchar()) != '\n');

	while (breaker == 0) {
		do {
			printf("Please Enter Seat Selection Courtside, Middle, Upper (C,M,U): \n");
			scanf("%c", &charInput);

			if (tolower(charInput) == 'c') {
				courtSideTicketNum += getCourtsideTicket(charityPercent, courtSideCost);
			}

			if (tolower(charInput) == 'm') {
				middleSectionTicketNum += getMiddleSectionTicket(charityPercent, middleCost);
			}

			if (tolower(charInput) == 'u') {
				upperSectionTicketNum += getUpperSectionTicket(charityPercent, middleCost);
				
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
	Gets the number of courtside tickets from customers
*/

double getCourtsideTicket(double charityPercent, double courtSideCost) {

	int numberOfTickets = 0;
	int courtsideTicketNum = 0;
	int ynBreaker = 0;

	printf("Courtside selected, Please select number of tickets(1-4): \n");
	scanf("%d", &numberOfTickets);

	if (numberOfTickets < 0 || numberOfTickets > MAX_TICKETS_NUM) {
		printf("ERROR %d NOT ACCEPTED ONLY 1-%d ACCEPTED \n", numberOfTickets, MAX_TICKETS_NUM);
		printf("Courtside selected, Please select number of tickets(1-4): \n");
		do {
			scanf("%d", &numberOfTickets);

			if (numberOfTickets < 0 || numberOfTickets > MAX_TICKETS_NUM || isalpha(numberOfTickets)) {
				printf("ERROR %d NOT ACCEPTED ONLY 1-%d ACCEPTED \n", numberOfTickets, MAX_TICKETS_NUM);
				numberOfTickets = 0;
				while ((getchar()) != '\n');
			}

		} while ((numberOfTickets < 0 || numberOfTickets > MAX_TICKETS_NUM) && isalpha(numberOfTickets));
	}
	if (numberOfTickets > 0 || numberOfTickets < MAX_TICKETS_NUM && isdigit(numberOfTickets)) {

		while (ynBreaker == 0) {
			while ((getchar()) != '\n');
			ynBreaker = verifyYesNo(0);

			if (ynBreaker == 1) {
				courtsideTicketNum += numberOfTickets;
				getZipCode();
				while ((getchar()) != '\n');
				printReciept(2, numberOfTickets, charityPercent, courtSideCost);
				numberOfTickets = 0;
			}
			if (ynBreaker == 0) {
				ynBreaker = 1;
				numberOfTickets = 0;
			}
		}
		ynBreaker = 0;
	}

	return courtsideTicketNum;

}

/*
	Gets the number of middlesection tickets from customers
*/

double getMiddleSectionTicket(double charityPercent, double middleCost) {

	int numberOfTickets = 0;
	int courtsideTicketNum = 0;
	int middleSectionTicketNum = 0;
	int ynBreaker = 0;

	printf("Middle Section selected, Please select number of tickets(1-4): \n");
	scanf("%d", &numberOfTickets);

	if (numberOfTickets < 0 || numberOfTickets > MAX_TICKETS_NUM) {
		printf("ERROR %d NOT ACCEPTED ONLY 1-%d ACCEPTED \n", numberOfTickets, MAX_TICKETS_NUM);
		printf("Courtside selected, Please select number of tickets(1-4): \n");
		do {
			scanf("%d", &numberOfTickets);

			if (numberOfTickets < 0 || numberOfTickets > MAX_TICKETS_NUM || isalpha(numberOfTickets)) {
				printf("ERROR %d NOT ACCEPTED ONLY 1-%d ACCEPTED \n", numberOfTickets, MAX_TICKETS_NUM);
				numberOfTickets = 0;
				while ((getchar()) != '\n');
			}

		} while ((numberOfTickets < 0 || numberOfTickets > MAX_TICKETS_NUM) && isalpha(numberOfTickets));
	}
	if (numberOfTickets > 0 || numberOfTickets < MAX_TICKETS_NUM && isdigit(numberOfTickets)) {

		while (ynBreaker == 0) {
			while ((getchar()) != '\n');
			ynBreaker = verifyYesNo(0);

			if (ynBreaker == 1) {
				middleSectionTicketNum += numberOfTickets;
				getZipCode();
				while ((getchar()) != '\n');
				printReciept(2, numberOfTickets, charityPercent, middleCost);
				numberOfTickets = 0;
			}
			if (ynBreaker == 0) {
				ynBreaker = 1;
				numberOfTickets = 0;
			}
		}
		ynBreaker = 0;
	}

	return middleSectionTicketNum;
}

/*
	Gets the number of upper section tickets from customers
*/

double getUpperSectionTicket(double charityPercent, double upperCost) {

	int numberOfTickets = 0;
	int upperSectionTicketNum = 0;
	int ynBreaker = 0;

	printf("Upper Section selected, Please select number of tickets(1-4): \n");
	scanf("%d", &numberOfTickets);

	if (numberOfTickets < 0 || numberOfTickets > MAX_TICKETS_NUM) {
		printf("ERROR %d NOT ACCEPTED ONLY 1-%d ACCEPTED \n", numberOfTickets, MAX_TICKETS_NUM);
		printf("Upper Section selected, Please select number of tickets(1-4): \n");
		do {
			scanf("%d", &numberOfTickets);

			if (numberOfTickets < 0 || numberOfTickets > MAX_TICKETS_NUM || isalpha(numberOfTickets)) {
				printf("ERROR %d NOT ACCEPTED ONLY 1-%d ACCEPTED \n", numberOfTickets, MAX_TICKETS_NUM);
				numberOfTickets = 0;
				while ((getchar()) != '\n');
			}

		} while ((numberOfTickets < 0 || numberOfTickets > MAX_TICKETS_NUM) && isalpha(numberOfTickets));
	}
	if (numberOfTickets > 0 || numberOfTickets < MAX_TICKETS_NUM && isdigit(numberOfTickets)) {

		while (ynBreaker == 0) {
			while ((getchar()) != '\n');
			ynBreaker = verifyYesNo(0);

			if (ynBreaker == 1) {
				upperSectionTicketNum += numberOfTickets;
				getZipCode();
				while ((getchar()) != '\n');
				printReciept(3, numberOfTickets, charityPercent, upperCost);
				numberOfTickets = 0;
			}
			if (ynBreaker == 0) {
				ynBreaker = 1;
				numberOfTickets = 0;
			}
		}
		ynBreaker = 0;
	}

	return upperSectionTicketNum;
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
	Prints the reciept to the customer
*/

void printReciept(int level, double numOfTickets, double charityAmout, double totalCost) {

	int breakrer = 0;
	int isCorrect = 0;

	isCorrect = verifyYesNo(1);

	if (isCorrect == 1) {

		if (level == 1) {
			printf("\nLevel: Courtside ");
			printf("Package: %.2lf ", numOfTickets);
			printf("Total Cost: %.2lf ", totalCost * numOfTickets);
			printf("Total Donated To Charity: %.2lf \n\n", (totalCost * numOfTickets) * (charityAmout / 100));
			breakrer = 1;
		}
		if (level == 2) {
			printf("\nLevel: Middle Section ");
			printf("Package: %.2lf ", numOfTickets);
			printf("Total Cost: %.2lf ", totalCost * numOfTickets);
			printf("Total Donated To Charity: %.2lf \n\n", (totalCost * numOfTickets) * (charityAmout / 100));
			breakrer = 1;
		}
		if (level == 3) {
			printf("\nLevel: Upper Section ");
			printf("Package: %.2lf ", numOfTickets);
			printf("Total Cost: %.2lf ", totalCost * numOfTickets);
			printf("Total Donated To Charity: %.2lf \n\n", (totalCost * numOfTickets) * (charityAmout / 100));
			breakrer = 1;
		}
	}
	if (isCorrect == 0) {
		breakrer = 1;
	}
}

/*
	Used to veryify if the answer is correct, the parameter receipt is for the customer input
*/

int verifyYesNo(int receipt) {

	int breaker = 0;
	int isCorrect = 0;

	char userInput = 'a';
	while (breaker == 0) {
		if (receipt == 1) {
			printf("Would you like a receipt?(Y/N)");
			scanf("%c", &userInput);
		}
		if (receipt == 0) {
			printf("Are entered values correctly? (Y/N)");
			scanf("%c", &userInput);
		}

		if (tolower(userInput) == 'y') {
			isCorrect = 1;
			breaker = 1;
		}

		if (tolower(userInput) == 'n') {
			isCorrect = 0;
			breaker = 1;
		}

		else if (!(toupper(userInput) == 'Y') && !(toupper(userInput) == 'N')) {
			printf("ERROR INVALID INPUT\n");
			while ((getchar()) != '\n');
		}

	}

	return isCorrect;
}


/*
	Gets the inputs and prints the summary
*/

double* printSummary(double courtSideTicketNum, double middleTicketNum, double upperTicketNum, double courtsidePrice, double middlePrice, double upperPrice, double charityPercent) {

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

	printf("========== Summary ==========\n");

	printf("Courtside Tickets Sold: %.2lf       Ticket Price: $%.2lf  Sales Total: $%.2lf  Total Charity: $%.2lf\n", courtSideTicketNum, courtsidePrice, totalPrices[0], totalPrices[0] * (charityPercent / 100));
	printf("Middle Section Tickets Sold: %.2lf  Ticket Price: $%.2lf  Sales Total: $%.2lf  Total Charity: $%.2lf\n", middleTicketNum, middlePrice, totalPrices[1], totalPrices[1] * (charityPercent / 100));
	printf("Upper Section Tickets Sold: %.2lf   Ticket Price: $%.2lf  Sales Total: $%.2lf  Total Charity: $%.2lf\n", upperTicketNum, upperPrice, totalPrices[2], totalPrices[2] * (charityPercent / 100));
	printf("Total Tickest Sold: %.2lf\n", totalTickets);
	printf("Total Amount Sold: $%.2lf\n", totalPrice);
	printf("Total Donated To Charity: $%.2lf\n", charityTotal);

	printf("======= End of Summary ======\n");

	return totalPrices;
}
