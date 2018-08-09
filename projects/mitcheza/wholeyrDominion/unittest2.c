
#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <math.h>

//Unit test for getCost() in dominion.c

void testGetCost() {

	printf("Testing getCost() function:\n");

	int i; //Iterator
	int testSuccess = 1; // Bool whether test passed or not
	
	//Card names and their position is the corresponding ENUM
	char * card[] = {"curse", "estate", "duchy", "province", "copper", "silver", "gold",
	"adventurer", "council_room", "feast", "gardens", "mine", "remodel", "smithy",
	"village", "baron", "great_hall", "minion", "steward", "tribute", "ambassador",
	"cutpurse", "embargo", "outpost", "salvager", "sea_hag", "treasure_map"};

	//Got the cost from:
	//  http://wiki.dominionstrategy.com/index.php/List_of_cards
	int card_cost[] = {0, 2, 5, 8, 0, 3, 6, 6, 5, 4, 4, 5, 4, 4, 3, 4, 3, 5,
	3, 5, 3, 4, 2, 5, 4, 4, 4};

	
	//Iterate over cards and confirm correct cost
	for (i = 0; i < 27; i++) {

		if ( getCost(i) == card_cost[i] ) {

			printf("getCost(): PASS when testing %s == %d.\n", card[i], card_cost[i]);

		} else {

			printf("getCost(): FAIL when testing %s == %d.\n", card[i], card_cost[i]);
			testSuccess = 0;
		}
	
	}

	if (testSuccess) {
		printf("TEST SUCCESSFUL\n");
	} else {
		printf("TEST FAILED\n");
	}

}



int main() {

	testGetCost();
	return 0;

}


