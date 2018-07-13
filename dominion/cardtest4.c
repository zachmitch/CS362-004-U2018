#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <math.h>




void testRemodel() {

	printf("Testing Remodel card:\n");

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
	gs1->hand[0][0] = remodel;
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

	//Try to get a card that's too expensive ( > +2 ) copper for smithy
	int result = cardEffect(remodel, 2, smithy, neg1, gs1, 0, &neg1);

	if (result == -1 ) {
		printf("Remodel PASS user can't trade for card of cost > 2\n");
	} else {
		printf("Remodel FAIL user can't trade for card of cost > 2\n");
		testSuccess = 0;
	}

	//Setup hand
	gs1->hand[0][0] = remodel;
	gs1->hand[0][1] = gardens;
	gs1->hand[0][2] = copper;
	gs1->hand[0][3] = copper;
	gs1->hand[0][4] = copper;
	gs1->handCount[0] = 5;
	gs1->discardCount[0] = 0;

	//Confirm that newcard added to hand
	result = cardEffect(remodel, 1, smithy, neg1, gs1, 0, &neg1);

	int i;
	int inHand = 0;
	
	for(i = 0; i < gs1->handCount[0]; i++) { if ( gs1->hand[0][i] == smithy) inHand = 1;}

	if ( inHand ) {
		printf("Remodel PASS card successfully added to user hand\n");
	} else {
		printf("Remodel FAIL card successfully added to user hand\n");
		testSuccess = 0;
	}


	//Confirm that trashed card is not added to discard

	if (gs1->discardCount[0] == 1 ) {
		printf("Remodel PASS trashed card disposed of properly\n");
	} else {
		printf("Remodel FAIL trashed card disposed of properly\n");
		testSuccess = 0;
	}

	//Confirm exit of 0 for mine
	if (result == 0) {
		printf("Remodel PASS card returns 0\n");
	} else {
		printf("Remodel FAIL card returns 0, returns %d\n", result);
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

	testRemodel();
	return 0;

}
