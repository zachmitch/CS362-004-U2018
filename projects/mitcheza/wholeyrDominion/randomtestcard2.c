#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <math.h>
#include <assert.h>
#include <time.h>

// Test Mine Random
// Purpose:  Randomly tests the mine card across dependencies
// Parameters : test - number of random tests to run
// Returns:   0 if successfully completed

int testMineRandom(int tests){

	//Mine card trashes a treasure card from your hand and gains a treasure card
	//   up to +3 more than its cost.  Discards the mine card thereafter
	// Mine dependencies:  currentPlayer, handPos, gameState, choice1 (trashed treasure), 
	//	choice2 (gained treasure),  
	//	
	//	gamestate (expanded):  hand, handCOunt, 


	
	int i, j;  //iterators
	int b4_handCount, b4_trashCard;  //Counts before execute card
	int success; //1 == success, 0 == failure
	int passed = 0;

	//Create random environments tests amount of times and print results

	for (i = 0; i < tests; i++) {

		printf("\n\n*********** RANDOM MINE TEST %d ***************\n", i + 1);

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

		//Create a random hand of cards between 2-5
		gs->handCount[gs->whoseTurn] = b4_handCount = (rand() % 4) + 2;

		//Randomly fill hand with some treasure and non-treasure cards from deck
		int randomCard, randomCards[] = {4,5,6,8};
//copper, silv, gold, cncl room, feast, gardn
		for(j = 0; j < gs->handCount[gs->whoseTurn]; j++) {
			randomCard = rand() % 4;
			gs->hand[gs->whoseTurn][j] = randomCards[randomCard];
		}

		//Randomly place mine card in hand
		int minePos;
		minePos = rand() % gs->handCount[gs->whoseTurn];
		gs->hand[gs->whoseTurn][minePos] = 11;


		//Let user know the setup of random test
		printf("\nSETUP - PLYRS: %d, WHZTRN: %d\n",
			gs->numPlayers, gs->whoseTurn);
		
		//Randomly choose card in hand to be trashed that's not the mine card
		//We'll test for execution for trashing treasure and non-treasure cards
		int trashPos;
		do {
			trashPos = rand() % gs->handCount[gs->whoseTurn];
		} while ( mine == gs->hand[gs->whoseTurn][trashPos] );

		//Randomly choose treasure/non-treasure card to pick up
		int pickup, pickups[] = {4,5,6,7,8};
		pickup = pickups[rand() % 5];

		//assign supply to pickups (sometimes will be empty)
		int supplyLeft = rand() % 5;
		for (j = 0; j < 5; j++) { gs->supplyCount[pickups[j]] = supplyLeft;}

		//Section here is only for printout so I can see what cards we are 
		//trashing and picking up instead of enums
		char * trashCard, * pickupCard;

		char * cards[] = {"copper", "silver", "gold", "adventurer", 
			"cncl room", "feast", "gardens"};
	
		//Assign pickup card
		switch(pickup) {
			case 4:
				pickupCard = cards[0];
				break;
			case 5:
				pickupCard = cards[1];
				break;
			case 6:	
				pickupCard = cards[2];
				break;	
			case 7:
				pickupCard = cards[3];
				break;
			case 8:
				pickupCard = cards[4];
				break;
		}

		//Assign trash card
		b4_trashCard = gs->hand[gs->whoseTurn][trashPos];
		switch(b4_trashCard) {

			case 4:
				trashCard = cards[0];
				break;
			case 5:
				trashCard = cards[1];
				break;
			case 6:
				trashCard = cards[2];
				break;
			case 8:
				trashCard = cards[4];
				break;
	

		}

		//Print the gist of this attempt (ex:  "Trash x, pickup y")
		printf("\nATTEMPT TRASH '%s', PICKUP '%s'\n", trashCard, pickupCard);


		//prints hand counts	
		printf("\nBEFORE - HANDCT: %d, MINE POS: %d, TRSHD POS: %d, SPPLYCT: %d\n"
			,gs->handCount[gs->whoseTurn], minePos, trashPos, supplyLeft);

		//prints hand
		printf("HAND BEFORE: ");
		for(j = 0; j < gs->handCount[gs->whoseTurn]; j++) {
			printf("[%d] %d ",j, gs->hand[gs->whoseTurn][j]);
		}

		

		//Play the mine card
		printf("\n\n                 * Play Mine *                  \n\n");
		int neg1 = -1;
	
		//choice1 - trashed treasure ->trashPos
		//choice2 - picked up treasure ->pickup

		int testResult;  //Tracks if error

		testResult = cardEffect(mine, trashPos, pickup, neg1, gs, 0, &neg1);
		
		//prints hand
		printf("HAND AFTER : ");
		for(j = 0; j < gs->handCount[gs->whoseTurn]; j++) {
			printf("[%d] %d ",j, gs->hand[gs->whoseTurn][j]);
		}
		
		printf("\n\nTEST RESULT: %d\n", testResult); 


		//Tests I want to conduct:
		// 1.  Empty supply count
		// 2.  Trashing a non-treasure card
		// 3.  Picking up a non-treasure card
		// 4.  Picking up card that is > 3 cost
		// 5.  Discard mine (played card)
		// 6.  Hand count -= 1	

		
		// 1.  empty supply
		if (supplyLeft == 0) {

			if (testResult == -1) {
				printf("TEST SUCCESS: EMPTY SUPPLY COUNT, CAN'T PICKUP\n");
			} else {
				printf("TEST FAILURE: EMPTY SUPPLY COUNT, CAN'T PICKUP\n");
				success = 0;
			}
		}


		//2.  trash non-treasure
		if ( (b4_trashCard > gold || b4_trashCard < copper)) {

			if( testResult < 0)
				printf("TEST SUCCESS:  TRASHING NON-TREASURE CARD ILLEGAL\n");
			else {
				printf("TEST FAILURE:  TRASHING NON-TREASURE CARD ILLEGAL\n");
				success = 0;
			}
	
		} 


		//3  pickup non-treasure
		if ( (pickup > gold || pickup < copper)) {

			if( testResult < 0)
				printf("TEST SUCCESS:  PICKUP NON-TREASURE CARD ILLEGAL\n");
			else {
				printf("TEST FAILURE:  PICKUP NON-TREASURE CARD ILLEGAL\n");
				success = 0;
			}
	
		} 

		//4. Pickup card > 3 cost

		if ( getCost(pickup) > (getCost(b4_trashCard) + 3) ) {

			if( testResult < 0)
				printf("TEST SUCCESS:  CAN'T PICKUP CARD >3 COST\n");
			else {
				printf("TEST FAILURE:  CAN'T PICKUP CARD >3 COST\n");
				success = 0;
			}
	
		} 

		// 5, 6
		if ( testResult == 0 ) {
			//5.  check that mine was put in played cards
			if ( gs->playedCardCount == 1 && gs->playedCards[0] == mine) {
				printf("TEST SUCCESS:  MINE DISCARDED INTO PLAYEDCARDS\n");
			} else {
				printf("TEST FAILURE:  MINE DISCARDED INTO PLAYEDCARDS\n");			
				success = 0;
			}

			//6.  handCount =- 1 (discard mine, trash a card, gain a card == [net -1])
			if ( b4_handCount - 1 == (gs->handCount[gs->whoseTurn])) {
				printf("TEST SUCCESS:  CORRECT # OF CARDS IN HAND AFTER PLAY\n");
			} else {
				printf("TEST FAILURE:  CORRECT # OF CARDS IN HAND AFTER PLAY\n");
				success = 0;
			}
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


	testMineRandom(100);



	return 0;

}




