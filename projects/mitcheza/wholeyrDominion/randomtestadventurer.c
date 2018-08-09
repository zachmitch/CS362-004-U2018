#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <math.h>
#include <assert.h>
#include <time.h>



// Test Adventurer Random
// Purpose:  Randomly tests the adventurer card across dependencies
// Parameters : test - number of random tests to run
// Returns:   0 if successfully completed


int testAdventurerRandom(int tests){

	//Adventurer card draws cards from deck until you get +2 treasure cards, then
	//        it discards all non-treasure cards drawn and the adventurer card itself
	//Adventurer dependencies:  currentPlayer, gameState, handPosition, 
	//      gameState (expanded):  deckCOunt, deck, handCount, hand, discardCount, discard
	

	int i, j;  //iterators
	int b4_handCount, b4_deckCount, b4_discard;  //Counts before execute card
	int success; //1 == success, 0 == failure
	int passed = 0;

	//Create random environments tests amount of times and print results

	for (i = 0; i < tests; i++) {

		printf("\n\n*********** RANDOM ADVENTURER TEST %d ***************\n", i + 1);

		success = 1;		

		//Create an empty new game
		struct gameState * gs = newGame();
		assert(gs != NULL);

		gs->phase = 0;
		gs->numActions = 1;
		gs->playedCardCount = 0;

		//Random number of players between 2-MAX_PLAYERS
		gs->numPlayers = (rand() % (MAX_PLAYERS - 1)) + 2;

		//Random players turn
		gs->whoseTurn = rand() % gs->numPlayers;

		//Create a random hand of cards between 2-5 (no treasures)
		gs->handCount[gs->whoseTurn] = b4_handCount = (rand() % 4) + 2;

		//Fill that hand with non treasure cards
		int randomCard, randomCards[] = {curse, duchy, council_room, feast, 
			adventurer,copper, silver, gold};

		//Randomly fill hand with cards from the dominion deck in randomCards
		//  from position 0-3 only (avoid having treasure cards in hand for 
		//  easier validation)
		for(j = 0; j < gs->handCount[gs->whoseTurn]; j++) {
			randomCard = randomCards[rand() % 4];
			gs->hand[gs->whoseTurn][j] = randomCard;
		}

		//Randomly place adventurer card in hand
		int advPos;
		advPos = rand() % gs->handCount[gs->whoseTurn];
		gs->hand[gs->whoseTurn][advPos] = 7;



		//Randomly generate deck and size, between 20 - 30
		//Then randomly fill in cards from dominion
		gs->deckCount[gs->whoseTurn] = b4_deckCount = (rand() % 21) + 10;
		for(j = 0; j < gs->deckCount[gs->whoseTurn]; j++) {
			randomCard = randomCards[rand() % 8];	
			gs->deck[gs->whoseTurn][j] = randomCard;
		}
	
		//Set discard as empty	
		gs->discardCount[gs->whoseTurn] = b4_discard = 0;


		//Let user know the card totals before and after playcard
		printf("SETUP - PLYRS: %d, WHZTRN: %d\n",
			gs->numPlayers, gs->whoseTurn);
		
		//prints hand counts	
		printf("\nBEFORE - HANDCT: %d, ADVPOS: %d, DECKCT: %d, DSCDCT: %d\n",
			gs->handCount[gs->whoseTurn], advPos, gs->deckCount[gs->whoseTurn],
			gs->discardCount[gs->whoseTurn]);

		//prints hand
		printf("HAND: ");
		for(j = 0; j < gs->handCount[gs->whoseTurn]; j++) {
			printf("[%d] %d ",j, gs->hand[gs->whoseTurn][j]);
		}


		//Play the adventurer card
		printf("\n\n                 * Play Adventurer *                  \n\n");
	
		int neg1 = -1;
		cardEffect(adventurer, neg1, neg1, neg1, gs, 0, &neg1);
	


		//Count how many treasures added to hand
		int treasureCount = 0;
		for(j = 0; j < gs->handCount[gs->whoseTurn]; j++) {
			if ( gs->hand[gs->whoseTurn][j] == copper ||
			     gs->hand[gs->whoseTurn][j] == silver ||
			     gs->hand[gs->whoseTurn][j] == gold) { 
					treasureCount++;
			}
		}

		//prints handcounts
		printf("AFTER  - HANDCT: %d, DECKCT: %d, DSCDCT: %d, TREASURE_CT: %d\n",
			gs->handCount[gs->whoseTurn], gs->deckCount[gs->whoseTurn],
			gs->discardCount[gs->whoseTurn], treasureCount);

		

		//Check hand
		printf("HAND: ");
		for(j = 0; j < gs->handCount[gs->whoseTurn]; j++) {
			printf("[%d] %d ",j, gs->hand[gs->whoseTurn][j]);
		}

		//Test to run
		// 1. +2 treasure in hand
		// 2. adventurer placed in played cards pile
		// 3. non-treasure cards discarded
		// 4. handcount net +1


		// 1. +2 treasure
		if (treasureCount == 2) {
			printf("\n\nTEST SUCCESS:  +2 TREASURES TO HAND\n");
		} else {
			printf("\n\nTEST FAILURE:  +2 TREASURES TO HAND\n");
			success = 0;
		}

		//2.  adventurer in played cards pile
		if (gs->playedCardCount == 1 && gs->playedCards[0] == adventurer) {
			printf("TEST SUCCESS:  ADVENTURER PLACED IN PLAYED CARDS\n");
		} else {
			printf("TEST FAILURE:  ADVENTURER PLACED IN PLAYED CARDS\n");
			success = 0;
		}

		// 3. non treasure discarded
		if ( gs->deckCount[gs->whoseTurn] == ((b4_deckCount - 2) - gs->discardCount[gs->whoseTurn])) {
			printf("TEST SUCCESS:  CORRECT # OF CARDS DISCARDED\n");
		} else {
			printf("TEST FAILURE:  CORRECT # OF CARDS DISCARDED\n");
			success = 0;
		}

		// 4. handcount += 1
		if ( b4_handCount + 1 == gs->handCount[gs->whoseTurn]) {
			printf("TEST SUCCESS:  CORRECT # OF CARDS IN HAND\n");
		} else { 
			printf("TEST FAILURE:  CORRECT # OF CARDS IN HAND\n");
			success = 0;
		}



		//Check for overall test success
		if(success) {
			printf("\n         TEST %d PASSED\n", i + 1);
			passed++;
		} else {
			printf("\n         TEST %d FAILED\n", i + 1);
		}

		//cleanup test environment
		free(gs);

		}


		printf("\n   *** PASSED %d/%d TESTS ATTEMPTED ***\n", passed, tests);

	return 0;

}






int main() {


	srand(time(0));

	//Number passed is # of tests
	testAdventurerRandom(100);


	return 0;

}




