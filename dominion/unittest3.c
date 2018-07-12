#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <math.h>


//Unit test for scoreFor() in dominion.c

void testbuyCard() {

	printf("Testing buyCard() function:\n");

	int testSucces = 1;	

	struct gameState * gs1;
	gs1 = newGame();

	gs1->whoseTurn = 0;

	//Test no buys avail
	gs1->numBuys = 0;

	if ( buyCard(smithy, gs1) == -1) {
		printf("buyCard():  PASS no buys available\n");
	} else {
		printf("buyCard():  FAIL no buys available\n");
		testSucces = 0;
	}

	//Test card not available for purch	
	gs1->numBuys = 1;
	gs1->supplyCount[smithy] = 0;
	
	if ( buyCard(smithy, gs1) == -1) {
		printf("buyCard():  PASS supplyCount == 0, cannot buy\n");
	} else {
		printf("buyCard():  FAIL supplyCount == 0, cannot buy\n");
		testSucces = 0;
	}

	//Test not enough money
	gs1->coins = 0;

	if ( buyCard(smithy, gs1) == -1) {
		printf("buyCard():  PASS not enough coins to buy, cannot buy\n");
	} else {
		printf("buyCard():  FAIL not enough coins to buy, cannot buy\n");
		testSucces = 0;
	}

	//Test card bought added to discard pile
	int coinpurse = 10;
	gs1->coins = coinpurse;
	gs1->supplyCount[smithy] = 100;
	gs1->discardCount[gs1->whoseTurn] = 0;

	buyCard(smithy, gs1);

	if ( gs1->discard[0][0] == smithy) {
		printf("buyCard():  PASS bought smithy and successfully added to discard\n");
	} else {
		printf("buyCard():  FAIL bought smithy and successfully added to discard\n");
		testSucces = 0;
	}

	//Test that coins are subtracted correctly for purchase
	if ( gs1->coins == (coinpurse - getCost(smithy))) {
		printf("buyCard():  PASS coins deducted correctly from available amt\n");
	} else {
		printf("buyCard():  FAIL coins deducted correctly from available amt\n");
		testSucces = 0;
	}

	//Test that user is out of buys
	if ( buyCard(curse, gs1) == -1) {
		printf("buyCard():  PASS user buys deducted correctly\n");
	} else {
		printf("buyCard():  FAIL user buys deducted correctly\n");
		testSucces = 0;
	}

	if ( testSucces) {
		printf("TEST SUCCESSFUL\n");
	} else {
		printf("TEST FAILED");
	}

}



int main() {

	testbuyCard();
	return 0;

}
