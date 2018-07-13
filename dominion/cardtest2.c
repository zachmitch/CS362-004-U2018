#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <math.h>




void testAdventurer() {

	printf("Testing Adventurer card:\n");

	int testSuccess = 1;

	//Setup player 0 gamestate with:
	//	 a 5-card hand of 1 Adventurer and 4 coppers
	//	 a 5-card deck of smithy, gardens,council_room and 2 silver
	//       a 0 card discard 

	struct gameState * gs1;
	gs1 = newGame();
	gs1->whoseTurn = 0;
	gs1->numActions = 1;
	gs1->handCount[0] = 5;
	gs1->deckCount[0] = 5;
	gs1->discardCount[0] = 0;	

	//Setup hand
	gs1->hand[0][0] = adventurer;
	gs1->hand[0][1] = copper;
	gs1->hand[0][2] = copper;
	gs1->hand[0][3] = copper;
	gs1->hand[0][4] = copper;

	//Setup deck
	gs1->deck[0][0] = smithy;
	gs1->deck[0][1] = gardens;
	gs1->deck[0][2] = council_room;
	gs1->deck[0][3] = silver;
	gs1->deck[0][4] = silver;

	//Call adventurer card
	//No use for choice(1-3) or card bonus pointer
	int neg1 = -1;
	int result = cardEffect(adventurer, neg1, neg1, neg1, gs1, 0, &neg1);

	//Check that net 1 card added to hand (+2 treasure, -1 adenturer)
	if ( gs1->handCount[0] == 6) {
		printf("PASS Adventurer card added correct amount of cards to hand\n");
	} else {
		printf("FAIL Adventurer card added correct amount of cards to hand\n");
		testSuccess = 0;
	}

	//Check that two treasure added to hand
	if ( gs1->hand[0][4] == silver && gs1->hand[0][5] == silver ) {
		printf("PASS Adventurer card added two treasure cards to hand\n");
	} else {
		printf("FAIL Adventurer card added two treasure cards to hand\n");
		testSuccess = 0;
	}

	//Check that all non-treasure drawn cards added to discard
	//  Should be total 4 (adventurer + 3 non treasure cards)
	if (gs1->discardCount[0] == 4) {
		printf("PASS Adventurer card discarded correct amt of cards\n");
	} else {
		printf("FAIL Adventurer card discarded correct amt of cards\n");
		testSuccess = 0;
	}


	//Check that function returns 0
	if (result == 0) {
		printf("PASS Adventurer card returns 0\n");
	} else {
		printf("FAIL Adventurer card returns 0\n");
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

	testAdventurer();
	return 0;

}
