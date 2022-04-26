/*
Nick Chesi
CS2060 T-Th
OS: Windows 10
HW05 Pass by reference
Due: 03/15/22
Description: Pass by reference practice
*/

#include <stdio.h> 
#include <math.h>  
#include <stdlib.h>
#include <ctype.h>

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996) //  had to have this idk why but my ide just started being poopy and wouldnt just let me have the above define
#define MAX_TICKETS_NUM 4
#define SEAT_SECTIONS 4
#define ADMIN_PIN_MAX_ENTRY 4

const int ADMIN_PIN = 4932;
	              						 // Court     //box      // middle   // upper
const float ticketMinMaxPrices[4][2] = { { 500,375 },{ 330,225 }, { 200,100 }, { 75,10 } };
const float charityMinMax[2] = { 30,10 };

// Pre customer setup
int promptAdminPin();
double* setUpValues();
double adminPromptForCharityPercent();
// Customer ticket counter
double* getCustomerTickets(double charityPercent, double courtSideCost, double boxCost, double middleCost, double upperCost);
// Ticket regrestration functions
double getCourtsideTicket(double charityPercent, double courtSideCost);
double getBoxTicket(double charityPercent, double boxCost);
double getMiddleSectionTicket(double charityPercent, double middleCost);
double getUpperSectionTicket(double charityPercent, double upperCost);
// Verification and reciept functions
double returnValidDoubleInput();
char returnValidCharInput();
void getZipCode();
void printReciept(int level, double numOfTickets, double charityAmout, double totalCost);
int verifyYesNo(int receipt);
double* printSummary(double courtSideTicketNum, double boxTicketNum, double middleTicketNum, double upperTicketNum, 
	double courtsidePrice, double boxPrice, double middlePrice, double upperPrice, double charityPercent);
// File output to save transactions

/*
(10 pts) Do not use scanf to get the seat prices and percentage for charity. 
Implement a function to validate a double or float (depending on what you are using in your Ticket Sales iteration). 
Use the same secure C approach that was used for integers in lecture 21. The function prototype should pass the string that was entered, 
the double value by reference and return a boolean. You can use <= and >= for all max and min bounds checking.
*/

int main(void) {

	double* priceHolder;
	double* ticketHolder;
	double charityPercent = 0;
	double totalPrice = 0;

	if (promptAdminPin() == 1) {
		priceHolder = setUpValues();
		charityPercent = adminPromptForCharityPercent();

		for (int i = 0; i < SEAT_SECTIONS; i++) {
			printf("Price %d: %.2lf\n", i, *(priceHolder + i));

		}
		printf("Entering Customer mode: \n");

		ticketHolder = getCustomerTickets(charityPercent, *(priceHolder + 0), *(priceHolder + 1), *(priceHolder + 2), *(priceHolder + 3));
		printSummary(*(ticketHolder + 0), *(ticketHolder + 1), *(ticketHolder + 2), *(ticketHolder + 3), *(priceHolder + 0), 
			*(priceHolder + 1), *(priceHolder + 2), *(priceHolder + 3), charityPercent);

	}

	return 0;
}

/*
	Prompts the user for their adminsitrator pin and confirms that its correct
*/

int promptAdminPin() {

	unsigned int counter = ADMIN_PIN_MAX_ENTRY;
	unsigned int boolIsAdminPinValid = 0;
	char buffer[] = "1111";
	char* ptr;
	int userInput = NULL;

	while (counter > 0) {

		printf("Enter Admin Pin to continute(Attempt: %d): \n", counter);
		userInput = returnValidDoubleInput();

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

char promptForCharityName(char name) {

}

/*
	Uses pointers to pass an array through a function and then sends it to main
*/

double* setUpValues() {

	static double prices[SEAT_SECTIONS];

	double userPriceInputCourt = 0;
	double courtsidePrice = 0;

	double userPriceInputBox = 0;
	double boxPrice = 0;

	double userPriceInputMiddle = 0;
	double midPrice = 0;

	double userPriceInputUpper = 0;
	double upper = 0;

	int verifyPrices = 1;
	int boolIsValidPin = 0;

	boolIsValidPin = 1;
	char buffer[] = "1111";

	
	if (boolIsValidPin == 1) {
		while ((getchar()) != '\n');
		while (verifyPrices == 1) {
			for (size_t i = 0; i < SEAT_SECTIONS; i++) {
				if (i == 0) {
					do {
						printf("Enter Ticket Price for Courtside (Between %.2f - %.2f): ", ticketMinMaxPrices[0][0], ticketMinMaxPrices[0][1]);
						userPriceInputCourt = returnValidDoubleInput();
						courtsidePrice = userPriceInputCourt;

						if (courtsidePrice > ticketMinMaxPrices[0][0] || courtsidePrice < ticketMinMaxPrices[0][1]) {
							printf("ERROR INPUT GREATER THAN %.2f OR LOWER THAN %.2f: %.2lf \n", ticketMinMaxPrices[0][0], ticketMinMaxPrices[0][1], courtsidePrice);
							while ((getchar()) != '\n');
						}
					} while (courtsidePrice > ticketMinMaxPrices[0][0] || courtsidePrice < ticketMinMaxPrices[0][1]);
					prices[i] = courtsidePrice;
					printf("Ticket price for Court section set to: %.2lf\n", courtsidePrice);
				}
				else if (i == 1) {
					do {
						printf("Enter Ticket Price for Box section (Between %.2f - %.2f): ", ticketMinMaxPrices[1][0], ticketMinMaxPrices[1][1]);
						userPriceInputBox = returnValidDoubleInput();
						boxPrice = userPriceInputBox;

						if (boxPrice > ticketMinMaxPrices[1][0] || boxPrice < ticketMinMaxPrices[1][1]) {
							printf("ERROR INPUT GREATER THAN %.2f OR LOWER THAN %.2f: %.2lf \n", ticketMinMaxPrices[1][0], ticketMinMaxPrices[1][1], userPriceInputBox);
							while ((getchar()) != '\n');
						}
					} while (boxPrice > ticketMinMaxPrices[1][0] || boxPrice < ticketMinMaxPrices[1][1]);
					prices[i] = boxPrice;
					printf("Ticket price for Box section set to: %.2lf\n", boxPrice);
				}
				else if (i == 2) {
					do {
						printf("Enter Ticket Price for Middle section (Between %.2f - %.2f): ", ticketMinMaxPrices[2][0], ticketMinMaxPrices[2][1]);
						userPriceInputMiddle = returnValidDoubleInput();
						midPrice = userPriceInputMiddle;

						if (midPrice > ticketMinMaxPrices[2][0] || midPrice < ticketMinMaxPrices[2][1]) {
							printf("ERROR INPUT GREATER THAN %.2f OR LOWER THAN %.2f: %.2lf \n", ticketMinMaxPrices[2][0], ticketMinMaxPrices[2][1], userPriceInputMiddle);
							while ((getchar()) != '\n');
						}
					} while (midPrice > ticketMinMaxPrices[2][0] || midPrice < ticketMinMaxPrices[2][1]);
					prices[i] = midPrice;
					printf("Ticket price for Middle section set to: %.2lf\n", midPrice);
				}
				else if (i == 3) {
					do {
						printf("Enter Ticket Price for Upper section (Between %.2f - %.2f): ", ticketMinMaxPrices[3][0], ticketMinMaxPrices[3][1]);
						userPriceInputUpper = returnValidDoubleInput();
						upper = userPriceInputUpper;

						if (upper > ticketMinMaxPrices[3][0] || upper < ticketMinMaxPrices[3][1]) {
							printf("ERROR INPUT GREATER THAN %f OR LOWER THAN %.2f: %.2lf \n", ticketMinMaxPrices[3][0], ticketMinMaxPrices[3][1], userPriceInputUpper);
							while ((getchar()) != '\n');
						}
					} while (upper > ticketMinMaxPrices[3][0] || upper < ticketMinMaxPrices[3][1]);
					prices[i] = upper;
					printf("Ticket price for Upper section set to: %.2lf\n", upper);
				}
			}
			int isCorrect = 0;
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
	char buffer[] = "1111";

	while (verifyPrices == 1) {
		while ((getchar()) != '\n');
		do {
			printf("Enter Charity percent: \n");
			charityValue = returnValidDoubleInput();

			if (charityValue < charityMinMax[1]) {
				printf("ERROR INVALID INPUT %.2lf IS LOWER THAN %.2f\n", charityValue, charityMinMax[1]);
				while ((getchar()) != '\n');
			}
			else if (charityValue > charityMinMax[0]) {
				printf("ERROR INVALID INPUT %.2lf IS GREATER THAN %.2f\n", charityValue, charityMinMax[0]);
				while ((getchar()) != '\n');
			}
		} while (charityValue < charityMinMax[1] || charityValue > charityMinMax[0]);

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

double* getCustomerTickets(double charityPercent, double courtSideCost, double boxCost, double middleCost, double upperCost) {

	static double numOfTickets[SEAT_SECTIONS];
	char charInput = 'a';
	char buffer[1];

	double courtSideTicketNum = 0;
	double boxSectionNum = 0;
	double middleSectionTicketNum = 0;
	double upperSectionTicketNum = 0;

	int ynBreaker = 0;
	int breaker = 0;
	int boolIsValidPin = 0;

	while ((getchar()) != '\n');

	while (breaker == 0) {
		do {
			printf("Please Enter Seat Selection Courtside, Middle, Upper (C,B,M,U): \n");
			fgets(buffer, 5, stdin);
			charInput = atol(buffer); // make this wordk

			if (tolower(charInput) == 'c') {
				courtSideTicketNum += getCourtsideTicket(charityPercent, courtSideCost);
			}

			if (tolower(charInput) == 'b') {
				boxSectionNum += getBoxTicket(charityPercent, boxCost);
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
			numOfTickets[1] = boxSectionNum;
			numOfTickets[2] = middleSectionTicketNum;
			numOfTickets[3] = upperSectionTicketNum;

			printf("COURTSIDE TICKETS: %lf\n", courtSideTicketNum);// DEBUG
			printf("BOX TICKETS: %lf\n", boxSectionNum);// DEBUG
			printf("MIDDLE TICKETS: %lf\n", middleSectionTicketNum);// DEBUG
			printf("UPPER TICKETS: %lf\n", upperSectionTicketNum);// DEBUG

		} while (!toupper(charInput) == 'Q');
	}
	return numOfTickets;
}

/*
	Gets the number of courtside tickets from customers
*/

double getCourtsideTicket(double charityPercent, double courtSideCost) {

	double numberOfTickets = 0;
	double courtsideTicketNum = 0;
	double ynBreaker = 0;

	printf("Courtside selected, Please select number of tickets(1-4): \n");
	numberOfTickets = returnValidDoubleInput();

	if (numberOfTickets < 0 || numberOfTickets > MAX_TICKETS_NUM) {
		printf("ERROR %lf NOT ACCEPTED ONLY 1-%d ACCEPTED \n", numberOfTickets, MAX_TICKETS_NUM);
		printf("Courtside selected, Please select number of tickets(1-4): \n");
		do {
			numberOfTickets = returnValidDoubleInput();

			if (numberOfTickets < 0 || numberOfTickets > MAX_TICKETS_NUM || isalpha(numberOfTickets)) {
				printf("ERROR %lf NOT ACCEPTED ONLY 1-%d ACCEPTED \n", numberOfTickets, MAX_TICKETS_NUM);
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
				printReciept(1, numberOfTickets, charityPercent, courtSideCost);
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
Gets the number of courtside tickets from customers
*/

double getBoxTicket(double charityPercent, double boxCost) {

	double numberOfTickets = 0;
	double boxTicketNum = 0;
	double ynBreaker = 0;

	printf("Box selected, Please select number of tickets(1-4): \n");
	numberOfTickets = returnValidDoubleInput();

	if (numberOfTickets < 0 || numberOfTickets > MAX_TICKETS_NUM) {
		printf("ERROR %d NOT ACCEPTED ONLY 1-%lf ACCEPTED \n", numberOfTickets, MAX_TICKETS_NUM);
		printf("Box selected, Please select number of tickets(1-4): \n");
		do {
			numberOfTickets = returnValidDoubleInput();

			if (numberOfTickets < 0 || numberOfTickets > MAX_TICKETS_NUM || isalpha(numberOfTickets)) {
				printf("ERROR %d NOT ACCEPTED ONLY 1-%lf ACCEPTED \n", numberOfTickets, MAX_TICKETS_NUM);
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
				boxTicketNum += numberOfTickets;
				getZipCode();
				while ((getchar()) != '\n');
				printReciept(2, numberOfTickets, charityPercent, boxCost);
				numberOfTickets = 0;
			}
			if (ynBreaker == 0) {
				ynBreaker = 1;
				numberOfTickets = 0;
			}
		}
		ynBreaker = 0;
	}

	return boxTicketNum;

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
	numberOfTickets = returnValidDoubleInput();

	if (numberOfTickets < 0 || numberOfTickets > MAX_TICKETS_NUM) {
		printf("ERROR %d NOT ACCEPTED ONLY 1-%d ACCEPTED \n", numberOfTickets, MAX_TICKETS_NUM);
		printf("Courtside selected, Please select number of tickets(1-4): \n");
		do {
			numberOfTickets = returnValidDoubleInput();

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
				printReciept(3, numberOfTickets, charityPercent, middleCost);
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
	numberOfTickets = returnValidDoubleInput();

	if (numberOfTickets < 0 || numberOfTickets > MAX_TICKETS_NUM) {
		printf("ERROR %d NOT ACCEPTED ONLY 1-%d ACCEPTED \n", numberOfTickets, MAX_TICKETS_NUM);
		printf("Upper Section selected, Please select number of tickets(1-4): \n");
		do {
			numberOfTickets = returnValidDoubleInput();

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
				printReciept(4, numberOfTickets, charityPercent, upperCost);
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
	    zip = returnValidDoubleInput();
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
			printf("\nLevel: Box Section ");
			printf("Package: %.2lf ", numOfTickets);
			printf("Total Cost: %.2lf ", totalCost * numOfTickets);
			printf("Total Donated To Charity: %.2lf \n\n", (totalCost * numOfTickets) * (charityAmout / 100));
			breakrer = 1;
		}
		if (level == 3) {
			printf("\nLevel: Middle Section ");
			printf("Package: %.2lf ", numOfTickets);
			printf("Total Cost: %.2lf ", totalCost * numOfTickets);
			printf("Total Donated To Charity: %.2lf \n\n", (totalCost * numOfTickets) * (charityAmout / 100));
			breakrer = 1;
		}
		if (level == 4) {
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
			userInput = returnValidCharInput();
		}
		if (receipt == 0) {
			printf("Are entered values correctly? (Y/N)");
			userInput = returnValidCharInput();
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

double* printSummary(double courtSideTicketNum, double boxTicketNum, double middleTicketNum, double upperTicketNum, double courtsidePrice, double boxPrice, double middlePrice, double upperPrice, double charityPercent) {

	static double totalPrices[SEAT_SECTIONS];

	double charityTotal = 0;
	double totalTickets = 0;
	double totalPrice = 0;

	for (int i = 0; i < SEAT_SECTIONS; i++) {
		if (i == 0) {
			totalPrices[i] = courtSideTicketNum * courtsidePrice;
		}
		if (i == 1) {
			totalPrices[i] = boxTicketNum * boxPrice;
		}
		if (i == 2) {
			totalPrices[i] = middleTicketNum * middlePrice;
		}
		if (i == 3) {
			totalPrices[i] = upperTicketNum * upperPrice;
		}
	}

	totalPrice = totalPrices[0] + totalPrices[1] + totalPrices[2];
	charityTotal = totalPrice * (charityPercent / 100);
	totalTickets = courtSideTicketNum + middleTicketNum + upperTicketNum;

	printf("========== Summary ==========\n");

	printf("Courtside Tickets Sold: %.2lf       Ticket Price: $%.2lf  Sales Total: $%.2lf  Total Charity: $%.2lf\n", courtSideTicketNum, courtsidePrice, totalPrices[0], totalPrices[0] * (charityPercent / 100));
	printf("Box Tickets Sold: %.2lf             Ticket Price: $%.2lf  Sales Total: $%.2lf  Total Charity: $%.2lf\n", boxTicketNum, boxPrice, totalPrices[1], totalPrices[1] * (charityPercent / 100));
	printf("Middle Section Tickets Sold: %.2lf  Ticket Price: $%.2lf  Sales Total: $%.2lf  Total Charity: $%.2lf\n", middleTicketNum, middlePrice, totalPrices[2], totalPrices[2] * (charityPercent / 100));
	printf("Upper Section Tickets Sold: %.2lf   Ticket Price: $%.2lf  Sales Total: $%.2lf  Total Charity: $%.2lf\n", upperTicketNum, upperPrice, totalPrices[3], totalPrices[3] * (charityPercent / 100));
	printf("Total Tickest Sold: %.2lf\n", totalTickets);
	printf("Total Amount Sold: $%.2lf\n", totalPrice);
	printf("Total Donated To Charity: $%.2lf\n", charityTotal);

	printf("======= End of Summary ======\n");

	return totalPrices;
}

/*
	Returns / gets a valid double data type input
*/
double returnValidDoubleInput() {

	double userInput = 0;
	char buffer[5] = {NULL};
	char* ptr;

	fgets(buffer, 5, stdin);
	userInput = strtol(buffer, &ptr, 10);

	printf("Test: %lf\n", userInput);

	return userInput;
}

/*
	Returns / gets a valid char data type input
*/
char returnValidCharInput() {

	double userInput = 0;
	char buffer[5] = { NULL };

	fgets(buffer, 5, stdin);
	printf("Test: %s!\n", buffer);

	return userInput;
}

// Print records to a file
void printToFileReciept(double courtSideTicketNum, double boxTicketNum, double middleTicketNum, double upperTicketNum, double courtsidePrice, double boxPrice, double middlePrice, double upperPrice, double charityPercent) {

	FILE* fp;

	fp = fopen("receiptFile.txt", "a");
	fprintf(fp, "This is being written in the file. This is an int variable");
	fclose(fp);



}

void printToFileSummary(double courtSideTicketNum, double boxTicketNum, double middleTicketNum, double upperTicketNum, double courtsidePrice, double boxPrice, double middlePrice, double upperPrice, double charityPercent) {

	FILE* fp;

	static double totalPrices[SEAT_SECTIONS];

	double charityTotal = 0;
	double totalTickets = 0;
	double totalPrice = 0;

	for (int i = 0; i < SEAT_SECTIONS; i++) {
		if (i == 0) {
			totalPrices[i] = courtSideTicketNum * courtsidePrice;
		}
		if (i == 1) {
			totalPrices[i] = boxTicketNum * boxPrice;
		}
		if (i == 2) {
			totalPrices[i] = middleTicketNum * middlePrice;
		}
		if (i == 3) {
			totalPrices[i] = upperTicketNum * upperPrice;
		}
	}

	totalPrice = totalPrices[0] + totalPrices[1] + totalPrices[2];
	charityTotal = totalPrice * (charityPercent / 100);
	totalTickets = courtSideTicketNum + middleTicketNum + upperTicketNum;


	fp = fopen("summaryFile.txt", "a");
	
	fprintf(fp, "========== Summary ==========\n");

	fprintf(fp,"Courtside Tickets Sold: %.2lf       Ticket Price: $%.2lf  Sales Total: $%.2lf  Total Charity: $%.2lf\n", courtSideTicketNum, courtsidePrice, totalPrices[0], totalPrices[0] * (charityPercent / 100));
	fprintf(fp,"Box Tickets Sold: %.2lf             Ticket Price: $%.2lf  Sales Total: $%.2lf  Total Charity: $%.2lf\n", boxTicketNum, boxPrice, totalPrices[1], totalPrices[1] * (charityPercent / 100));
	fprintf(fp,"Middle Section Tickets Sold: %.2lf  Ticket Price: $%.2lf  Sales Total: $%.2lf  Total Charity: $%.2lf\n", middleTicketNum, middlePrice, totalPrices[2], totalPrices[2] * (charityPercent / 100));
	fprintf(fp,"Upper Section Tickets Sold: %.2lf   Ticket Price: $%.2lf  Sales Total: $%.2lf  Total Charity: $%.2lf\n", upperTicketNum, upperPrice, totalPrices[3], totalPrices[3] * (charityPercent / 100));
	fprintf(fp,"Total Tickest Sold: %.2lf\n", totalTickets);
	fprintf(fp,"Total Amount Sold: $%.2lf\n", totalPrice);
	fprintf(fp,"Total Donated To Charity: $%.2lf\n", charityTotal);

	fprintf(fp, "======= End of Summary ======\n");

	fclose(fp);
}

