#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <math.h>
#include <assert.h>
#include <time.h>

// Test Smithy Random
// Purpose:  Randomly tests the smithy card across dependencies
// Parameters : test - number of random tests to run
// Returns:   0 if successfully completed

int testSmithyRandom(int tests){

	//Smithy is supposed to add 3 cards to hand, and then discard smithy card to playedcard
	//Smithy dependencies:  currentPlayer, gameState, handPosition
	//	gameState (expanded):  played cards, playedCardCount, deckCount, 
	//             handCount, deck, hand 

	
	int i, j;  //iterators
	int b4_handCount, b4_deckCount, b4_playedCardCount, b4_discard;  //Counts before execute card
	int success; //1 == success, 0 == failure
	int passed = 0;

	//Create random environments tests amount of times and print results

	for (i = 0; i < tests; i++) {

		printf("\n\n*********** RANDOM SMITHY TEST %d ***************\n", i + 1);

		success = 1;		

		//Create an empty new game
		struct gameState * gs = newGame();
		assert(gs != NULL);

		gs->phase = 0;
		gs->numActions = 1;

		//Random number of players between 2-MAX_PLAYERS
		gs->numPlayers = (rand() % (MAX_PLAYERS - 1)) + 2;

		//Random players turn
		gs->whoseTurn = rand() % gs->numPlayers;

		//Create a random hand of cards between 1-8
		gs->handCount[gs->whoseTurn] = b4_handCount = (rand() % 8) + 1;

		//Randomly fill hand with cards from the dominion deck
		for(j = 0; j < gs->handCount[gs->whoseTurn]; j++) {
			int randCard = 13;  //Make sure only smithy card in deck
			while (randCard == 13) { randCard = rand() % 27;}
			gs->hand[gs->whoseTurn][j] = randCard;
		}

		//Randomly place smithy card in hand
		int smithyLoc;
		smithyLoc = rand() % gs->handCount[gs->whoseTurn];
		gs->hand[gs->whoseTurn][smithyLoc] = 13;

		//Randomly generate deck and size, between 0 - 20
		//Then randomly fill in cards from dominion
		gs->deckCount[gs->whoseTurn] = b4_deckCount = rand() % 21;
		for(j = 0; j < gs->deckCount[gs->whoseTurn]; j++) {
			int randCard = 13;  //Make sure only smithy card in deck
			while (randCard == 13) { randCard = rand() % 27;}
			gs->deck[gs->whoseTurn][j] = randCard;
		}
		
		//Randomly generate played card count for this players turn (0-3)
		// Then randomly fill in cards from dominion
		gs->playedCardCount = b4_playedCardCount = rand() % 4;
		for(j = 0; j < gs->playedCardCount; j++) {
			int randCard = 13;  //Make sure only smithy card in deck
			while (randCard == 13) { randCard = rand() % 27;}
			gs->playedCards[j] = randCard;
		}


		//Randomly generate discard card count for this players turn (3-6)
		// Then randomly fill in cards from dominion
		gs->discardCount[gs->whoseTurn] = b4_discard = 3;
		for(j = 0; j < gs->discardCount[gs->whoseTurn]; j++) {
			int randCard = 13;  //Make sure only smithy card in deck
			while (randCard == 13) { randCard = rand() % 27;}
			gs->discard[gs->whoseTurn][j] = randCard;
		}


		//Let user know the card totals before and after playcard
		printf("SETUP - PLYRS: %d, WHZTRN: %d, SMITHYHANDPOS: %d\n",
			gs->numPlayers, gs->whoseTurn, smithyLoc);
		
		//prints hand counts	
		printf("\nBEFORE SMITHY - HANDCT: %d, DECKCT: %d, PLYDCRDCT: %d\n",
			gs->handCount[gs->whoseTurn], gs->deckCount[gs->whoseTurn],
			gs->playedCardCount);

		//prints hand
		printf("HAND: ");
		for(j = 0; j < gs->handCount[gs->whoseTurn]; j++) {
			printf("[%d] %d ",j, gs->hand[gs->whoseTurn][j]);
		}


		//Play the smithy card
		printf("\n\n                 * Play Smithy *                  \n\n");
//		playCard(smithyLoc, 1, 1, 1, gs);
		int neg1 = -1;
		cardEffect(smithy, neg1, neg1, neg1, gs, 0, &neg1);
		
		//prints handcounts
		printf("AFTER SMITHY - HANDCT: %d, DECKCT: %d, PLYDCRDCT: %d\n",
			gs->handCount[gs->whoseTurn], gs->deckCount[gs->whoseTurn],
			gs->playedCardCount);




		

		//Check hand, hand count, deck count, and played card counts to confirm correct
		printf("HAND: ");
		for(j = 0; j < gs->handCount[gs->whoseTurn]; j++) {
			printf("[%d] %d ",j, gs->hand[gs->whoseTurn][j]);
		}

		//hand should be net +2 cards
		if( (b4_handCount + 2) == gs->handCount[gs->whoseTurn]) {
			printf("\n\nTEST SUCCESS: HANDCOUNT\n");
		} else {
			printf("\nTEST FAILURE: HANDCOUNT\n");
			success = 0;
		}

		//Make sure that smithy is no longer in hand
		if (gs->hand[gs->whoseTurn][smithyLoc] != smithy) {
			printf("TEST SUCCESS: CARD REMOVED\n");
		} else {
			printf("TEST FAILURE: CARD REMOVED\n");
			success = 0;
		}

	
		//Deck count should be net -3 cards, put 3 cards in discard 
		// in case deck was empty
		if (b4_deckCount >= 3) {
			if ((b4_deckCount - 3) == gs->deckCount[gs->whoseTurn]) {
				printf("TEST SUCCESS: DECKCOUNT\n");
			} else {
				printf("TEST FAILURE: DECKCOUNT\n");
				success = 0;
			}
		} else {
			if(b4_deckCount == gs->deckCount[gs->whoseTurn]) {
				printf("TEST SUCCESS: DECKCOUNT\n");
			} else {
				printf("TEST FAILURE: DECKCOUNT\n");
				success = 0;
			}
		}



		//played card count should be net +1
		if ((b4_playedCardCount + 1) == gs->playedCardCount) {
			printf("TEST SUCCESS: PLYD CARD COUNT\n");
		} else {
			printf("TEST FAILURE: PLYD CARD COUNT\n");
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


	testSmithyRandom(100);



	return 0;

}




