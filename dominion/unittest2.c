#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <math.h>

//Unit test for scoreFor() in dominion.c

void testScoreFor() {

	printf("Testing getCost() function:\n");

	int testSuccess = 1;
	
	//Card names and their corresponding ENUM
	int curse = 0;
	int estate = 1;
	int duchy = 2;
	int province = 3;
	int copper = 4;
	int silver = 5;
	int gold = 6;
	int adventurer = 7;
	int smithy = 13;


	//Got the cost from:
	//  http://wiki.dominionstrategy.com/index.php/List_of_cards

	if ( getCost(curse) == 0)
		printf("getCost():  PASS curse cost == 0\n");
	else {
		printf("getCost():  FAIL curse cost != 0\n");
		testSuccess = 0;
	}


	if ( getCost(estate) == 2)
		printf("getCost():  PASS estate cost == 2\n");
	else {
		printf("getCost():  FAIL estate cost != 2\n");
		testSuccess = 0;
	}


	if ( getCost(duchy) == 5)
		printf("getCost():  PASS duchy cost == 5\n");
	else {
		printf("getCost():  FAIL duchy cost != 5\n");
		testSuccess = 0;
	}

	if ( getCost(province) == 8)
		printf("getCost():  PASS province cost == 8\n");
	else {
		printf("getCost():  FAIL province cost != 8\n");
		testSuccess = 0;
	}

	if ( getCost(copper) == 0)
		printf("getCost():  PASS copper cost == 0\n");
	else {
		printf("getCost():  FAIL copper cost != 0\n");
		testSuccess = 0;
	}

	if ( getCost(silver) == 3)
		printf("getCost():  PASS silver cost == 3\n");
	else {
		printf("getCost():  FAIL silver cost != 3\n");
		testSuccess = 0;
	}

	if ( getCost(gold) == 6)
		printf("getCost():  PASS gold cost == 6\n");
	else {
		printf("getCost():  FAIL gold cost != 6\n");
		testSuccess = 0;
	}

	if ( getCost(adventurer) == 6)
		printf("getCost():  PASS adventurer cost == 6\n");
	else {
		printf("getCost():  FAIL adventurer cost != 6\n");
		testSuccess = 0;
	}


	if ( getCost(smithy) == 4)
		printf("getCost():  PASS smithy cost == 4\n");
	else {
		printf("getCost():  FAIL smithy cost != 4\n");
		testSuccess = 0;
	}


	if (testSuccess)
		printf("TEST SUCCESSFULLY COMPLETED");
	else 
		printf("TEST FAILED");


}



int main() {

	testScoreFor();
	return 0;

}
