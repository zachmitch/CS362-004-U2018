#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <math.h>


//Unit test for shuffle() in dominion.c

void testShuffle() {

	printf("Testing function shuffle():\n");

	int testSuccess = 1;
	struct gameState * gs1;
	gs1 = newGame();

	//Test for empty deck shuffle
	gs1->deckCount[0] = 0;

	if ( shuffle(0, gs1) == -1 ) {
		printf("shuffle():  PASS cannot shuffle an empty deck\n");
	} else { 
		printf("shuffle():  FAIL cannot shuffle an empty deck\n");
		testSuccess = 0;
	}

	//Assert that shuffle works as advertised
	// 1/8! chance that it will still be in this order
	gs1->deckCount[0] = 8;
	gs1->deck[0][0] = 0;
	gs1->deck[0][1] = 1;
	gs1->deck[0][2] = 2;
	gs1->deck[0][3] = 3;
	gs1->deck[0][4] = 4;
	gs1->deck[0][5] = 5;
	gs1->deck[0][6] = 6;
	gs1->deck[0][7] = 7;
	int i; //iter
	int shuffled = 0;

	shuffle(0, gs1);

	for ( i = 0; i < 8; i++) {

		if (gs1->deck[0][i] != i) {
			shuffled = 1;
			break;
		}
	}
		
	if (shuffled) {
		printf("shuffle():  PASS cards were shuffled into a different order\n");
	} else { 
		printf("shuffle():  FAIL cards were shuffled into a different order\n");
		testSuccess = 0;
	}

	//Confirm that deckCount[player] remains unchanged as function tampers with it
	if ( gs1->deckCount[0] == 8) {
		printf("shuffle():  PASS deckCount was not affected by shuffle\n");
	} else { 
		printf("shuffle():  FAIL deckCount was not affected by shuffle\n");
		testSuccess = 0;
	}
	

	if (testSuccess) {
		printf("TEST SUCCESSFUL\n");
	} else { 
		printf("TEST FAILURE\n");
		testSuccess = 0;
	}

}



int main() {

	testShuffle();
	return 0;

}
