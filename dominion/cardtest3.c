#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <math.h>




void testMine() {

	printf("Testing Mine card:\n");

	int testSuccess = 1;

	//Setup player 0 gamestate with:
	//	 a 5-card hand of 1 mine, 3 coppers, and gardens
	//	 a 5-card deck of smithy, gardens,council_room, silver, and gold
	//       a 0 card discard 

	struct gameState * gs1;
	gs1 = newGame();
	gs1->whoseTurn = 0;
	gs1->numActions = 1;
	gs1->handCount[0] = 5;
	gs1->deckCount[0] = 5;
	gs1->discardCount[0] = 0;	

	//Setup hand
	gs1->hand[0][0] = mine;
	gs1->hand[0][1] = gardens;
	gs1->hand[0][2] = copper;
	gs1->hand[0][3] = copper;
	gs1->hand[0][4] = copper;

	//Setup deck
	gs1->deck[0][0] = smithy;
	gs1->deck[0][1] = gardens;
	gs1->deck[0][2] = council_room;
	gs1->deck[0][3] = silver;
	gs1->deck[0][4] = gold;

	//Call Mine card
	//No use for choice(1-3) or card bonus pointer
	int neg1 = -1;

	//Check that user chooses to trash a non-treasure card
	int result = cardEffect(mine, 1, silver, neg1, gs1, 0, &neg1);

	if (result == -1 ) {
		printf("Mine PASS user tried to trash a non-treasure card\n");
	} else {
		printf("Mine FAIL user tried to trash a non-treasure card\n");
		testSuccess = 0;
	}

	//Check that user chooses to pickup a non-treasure card
	result = cardEffect(mine, 2, smithy, neg1, gs1, 0, &neg1);

	if (result == -1 ) {
		printf("Mine PASS tried to pick up a non-treasure card\n");
	} else {
		printf("Mine FAIL tried to pick up a non-treasure card\n");
		testSuccess = 0;
	}

	//Setup hand
	gs1->whoseTurn = 0;
	gs1->numActions = 1;
	gs1->hand[0][0] = mine;
	gs1->hand[0][1] = gardens;
	gs1->hand[0][2] = copper;
	gs1->hand[0][3] = copper;
	gs1->hand[0][4] = copper;
	gs1->handCount[0] = 5;

	//Check that user picks up treasure card that is > +3 cost of what is trashed
	result = cardEffect(mine, 2, gold, neg1, gs1, 0, &neg1);

	if (result == -1 ) {
		printf("Mine PASS tried to purchase treasure card too expensive\n");
	} else {
		printf("Mine FAIL tried to purchase treasure card too expensive\n");
		testSuccess = 0;
	}

	//Setup hand again
	gs1->hand[0][0] = mine;
	gs1->hand[0][1] = gardens;
	gs1->hand[0][2] = copper;
	gs1->hand[0][3] = copper;
	gs1->hand[0][4] = copper;
	gs1->handCount[0] = 5;
	gs1->discardCount[0] = 0;
	gs1->whoseTurn = 0;

	//Run function as expected now...will serve for all future tests
	int result2 = cardEffect(mine, 2, silver, neg1, gs1, 0, &neg1);

	//Confirm that card is added to players hand
	int i;
	int inHand = 0;
	for(i = 0; i < gs1->handCount[0]; i++) { 
		if (gs1->hand[0][i] == silver) inHand = 1;
	}

	if ( inHand ) {
		printf("Mine PASS added treasure card successfully to hand\n");
	} else {
		printf("Mine FAIL added treasure card successfully to hand\n");
		testSuccess = 0;
	}

	//COnfirm that Mine card is discarded
	if ( gs1->discardCount[0] == 1) {
		printf("Mine PASS added card successfully to discard\n");
	} else {
		printf("Mine FAIL added card successfully to discard\n");
		testSuccess = 0;
	}

	//Confirm exit of 0 for mine
	if (result2 == 0) {
		printf("Mine PASS Mine card returns 0\n");
	} else {
		printf("Mine FAIL Mine card returns 0, return %d\n", result2);
		testSuccess = 0;
	}


	if(testSuccess) {
		printf("TEST SUCCESSFUL\n");
	} else {
		printf("TEST FAILURE\n");
	}





}



int main() {

	testMine();
	return 0;

}
