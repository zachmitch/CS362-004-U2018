#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <math.h>




void testSmithy() {

	printf("Testing Smithy card:\n");

	int testSuccess = 1;

	//Setup player 0 gamestate with:
	//	 a 5-card hand of 1 smithy and 4 coppers
	//	 a 5-card deck of only silvers
	//       a 0 card discard 

	struct gameState * gs1;
	gs1 = newGame();
	gs1->whoseTurn = 0;
	gs1->numActions = 1;
	gs1->handCount[0] = 5;
	gs1->deckCount[0] = 5;
	gs1->discardCount[0] = 0;	

	//Setup hand
	gs1->hand[0][0] = smithy;
	gs1->hand[0][1] = copper;
	gs1->hand[0][2] = copper;
	gs1->hand[0][3] = copper;
	gs1->hand[0][4] = copper;

	//Setup deck
	gs1->deck[0][0] = silver;
	gs1->deck[0][1] = silver;
	gs1->deck[0][2] = silver;
	gs1->deck[0][3] = silver;
	gs1->deck[0][4] = silver;


	//Call Smithy card
	//No use for choice(1-3) or card bonus pointer
	int neg1 = -1;
	int result = cardEffect(smithy, neg1, neg1, neg1, gs1, 0, &neg1);

	//Confirm that net gain of cards is +2 (added 3, discarded 1)
	if(gs1->handCount[0] == 7) {
		printf("Smithy:  PASS net +2 cards added to hand (added 3, discard 1)\n");
	} else {
		printf("Smithy:  FAIL net +2 cards added to hand (added 3, discard 1)\n");
		testSuccess = 0;
	}
	
	//Confirm that three cards were removed from deck
	if(gs1->deckCount[0] == 2) {
		printf("Smithy:  PASS 3 cards removed from player's deck\n");
	} else {
		printf("Smithy:  FAIL 3 cards removed from player's deck\n");
		testSuccess = 0;
	}

	//Confirm that smithy was removed from hand
	if(gs1->deck[0][0] != smithy) {
		printf("Smithy:  PASS Smithy was removed from player's hand\n");
	} else {
		printf("Smithy:  FAIL Smithy was removed from player's hand\n");
		testSuccess = 0;
	}

	//Confirm that smithy was added to discard pile
	if(gs1->discardCount[0] == 1 ) {
		printf("Smithy:  PASS Smithy added to discard pile\n");
	} else {
		printf("Smithy:  FAIL Smithy added to discard pile\n");
		testSuccess = 0;
	}

	//Confirm exit status of 0
	if(result == 0) {
		printf("Smithy:  PASS Smithy exited with result of 0\n");
	} else {
		printf("Smithy:  FAIL Smithy exited with result of 0\n");
		testSuccess = 0;
	}


	if(testSuccess) {
		printf("TEST SUCCESSFUL\n");
	} else {
		printf("TEST FAILURE\n");
		testSuccess = 0;
	}





}



int main() {

	testSmithy();
	return 0;

}
