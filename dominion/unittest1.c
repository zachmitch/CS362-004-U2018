#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <math.h>


//Unit test for scoreFor() in dominion.c
//  Parameters player and gameState
//  Returns player score


void testScoreFor() {

	printf("Testing scoreFor() function:\n");

	int testSuccess = 1;
	struct gameState * gs1;

	gs1 = newGame();

	//Total cards 18 for Player 1, one of each card that affects score in each
	gs1->handCount[0] = 6;
	gs1->discardCount[0] = 6;
	gs1->deckCount[0] = 6;
	
	gs1->hand[0][0] = 0;  //Curse
	gs1->hand[0][1] = 1;  //Estate
	gs1->hand[0][2] = 2;  //Duchy
	gs1->hand[0][3] = 3;  //Province
	gs1->hand[0][4] = 16; //Great hall
	gs1->hand[0][5] = 10; //Gardens

	gs1->discard[0][0] = 0;  //Curse
	gs1->discard[0][1] = 1;  //Estate
	gs1->discard[0][2] = 2;  //Duchy
	gs1->discard[0][3] = 3;  //Province
	gs1->discard[0][4] = 16; //Great hall
	gs1->discard[0][5] = 10; //Gardens

	gs1->deck[0][0] = 0;  //Curse
	gs1->deck[0][1] = 1;  //Estate
	gs1->deck[0][2] = 2;  //Duchy
	gs1->deck[0][3] = 3;  //Province
	gs1->deck[0][4] = 16; //Great hall
	gs1->deck[0][5] = 10; //Gardens



	//Total cards 9 for Player 2
	gs1->handCount[1] = 3;
	gs1->discardCount[1] = 3;
	gs1->deckCount[1] = 3;
	
	gs1->hand[1][0] = 0;  //Curse
	gs1->hand[1][1] = 1;  //Estate
	gs1->hand[1][2] = 2;  //Duchy

	gs1->discard[1][0] = 0;  //Curse
	gs1->discard[1][1] = 16;  //Great Hall
	gs1->discard[1][2] = 10;  //Gardens

	gs1->deck[1][0] = 0;  //Curse
	gs1->deck[1][1] = 1;  //Estate
	gs1->deck[1][2] = 2;  //Duchy


	//Total cards for 10 for Player 3
	gs1->handCount[2] = 4;
	gs1->discardCount[2] = 3;
	gs1->deckCount[2] = 3;
	
	gs1->hand[2][0] = 0;  //Curse
	gs1->hand[2][1] = 0;  //Curse
	gs1->hand[2][2] = 0;  //Curse
	gs1->hand[2][3] = 0;  //Curse

	gs1->discard[2][0] = 0;  //Curse
	gs1->discard[2][1] = 0;  
	gs1->discard[2][2] = 0;  

	gs1->deck[2][0] = 0;  //Curse
	gs1->deck[2][1] = 0;  
	gs1->deck[2][2] = 0; 

	//Total cards for 9 for Player 4
	gs1->handCount[3] = 3;
	gs1->discardCount[3] = 3;
	gs1->deckCount[3] = 3;
	
	gs1->hand[3][0] = 0;  //Curse
	gs1->hand[3][1] = 1;  //Estate
	gs1->hand[3][2] = 2;  //Duchy

	gs1->discard[3][0] = 16;  //Council Room
	gs1->discard[3][1] = 10;  //Gardens  
	gs1->discard[3][2] = 3; //Province 

	gs1->deck[3][0] = 0;  //Curse
	gs1->deck[3][1] = 1;  //Estate
	gs1->deck[3][2] = 2;  //Duchy

	if ( scoreFor(0, gs1) == 33 ) {
		printf("scoreFor(): PASS when testing 1 of each scoring card in deck, hand, discard == 33\n");		
	} else {
		printf("scoreFor(): FAIL when testing 1 of each scoring card in deck, hand, discard == 33\n");		
		testSuccess = 0;
	}

	if ( scoreFor(1, gs1) == 6) {
		printf("scoreFor(): PASS when testing 3 x (curse), 2 x (duchy, estate), great hall, gardens  == 6\n");		
	} else {
		printf("scoreFor(): FAIL when testing 3 x (curse), 2 x (duchy, estate), great hall, gardens  == 6\n");		
		testSuccess = 0;
	}

	if ( scoreFor(2, gs1) == -10) {
		printf("scoreFor(): PASS when testing 10 curses  == -10\n");		
	} else {
		printf("scoreFor(): FAIL when testing 10 curses  == -10\n");		
		testSuccess = 0;
	}

	if ( scoreFor(3, gs1) == 13) {
		printf("scoreFor(): PASS when testing hand  == 13\n");		
	} else {
		printf("scoreFor(): FAIL when testing hand  == 13\n");		
		testSuccess = 0;
	}


	if(testSuccess) {
		printf("TEST SUCCESS\n");
	} else {
		printf("TEST FAILED\n");
	}



	free(gs1);

}



int main() {

	testScoreFor();
	return 0;

}
