/* Unit test for numHandCards function */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(){

	int seed = 10;
	int choice1 = 0, choice2 = 0, choice3 = 0;
	int players = 2;
	int firstPlayer = 0;
	int secondPlayer = 1;
	struct gameState game;

	int k[10] = {smithy, adventurer, salvager, remodel, baron, great_hall, ambassador, tribute, outpost, minion};

	//initializing game for testing
	initializeGame(players, k, seed, &game);

	printf("************ unittest1 ************\n");
	printf("\n************Testing numHandCards function.************\n");

	//Test 1: Making sure 5 cards in hand at beginning, per game rules

	printf("\n*****Test 1: 5 cards in player 1's hands, 0 in player 2.*****\n");
	//player 1
	game.whoseTurn = firstPlayer;
	assertTrue("Test 1, Player 1: 5 cards in hand. Should be equal.", numHandCards(&game), 5);

	//player 2
	game.whoseTurn = secondPlayer;
	assertTrue("Test 1, Player 2: 0 cards in hand, should be equal.", numHandCards(&game), 0);

	//Test 2: set hand to MAX_HAND 

	printf("\n*****Test 2: set hand to MAX_HAND.*****\n");
	game.handCount[whoseTurn(&game)] = MAX_HAND;

	assertTrue("Test 2: hand should be MAX_HAND number.", numHandCards(&game), MAX_HAND);

	//Test 3: set hand to 0

	printf("\n*****Test 3: set hand to 0.*****\n");
	game.handCount[whoseTurn(&game)] = 0;

	assertTrue("Test 3: hand should be 0.", numHandCards(&game), 0);

	//Test 4: set hand to negative number - should fail

	printf("\n*****Test 4: set hand to negative number.*****\n");
	game.handCount[whoseTurn(&game)] = -100;

	if (numHandCards(&game) == -100){
		printf("TEST FAILED! Returned a negative handCount.\n");
	}
	
	else{
		printf("TEST PASSED! Did not allow a negative handCount.\n");
	}		

	//Test 5: set hand count to greater than MAX_HAND

	printf("\n*****Test 5: set handCount to > MAX_HAND.*****\n");
	game.handCount[whoseTurn(&game)] = MAX_HAND + 1;

	if (numHandCards(&game) == MAX_HAND + 1){
		printf("TEST FAILED! Returned more than MAX_HAND.\n");
	}
	
	else{
		printf("TEST PASSED! Did not allow more than MAX_HAND.\n");
	}

	printf("\n************ numHandCards Testing Complete. ************\n");

	return 0;
}

