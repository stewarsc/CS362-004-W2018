/* Unit test for whoseTurn function */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(){

	int seed = 10;
	int choice1 = 0, choice2 = 0, choice3 = 0;
	int players = MAX_PLAYERS;
	int firstPlayer = 0;
	int secondPlayer = 1;
	struct gameState game;

	int k[10] = {smithy, adventurer, salvager, remodel, baron, great_hall, ambassador, tribute, outpost, minion};

	//initializing game for testing
	initializeGame(players, k, seed, &game);

	printf("************ unittest2 ************\n");
	printf("\n************Testing whoseTurn function.************\n");

	//test 1: player 1's turn at beginning

	printf("\n*****Test 1: Player 1's turn at beginning.*****\n");
	
	assertTrue("Test 1: Should return 0.", whoseTurn(&game), firstPlayer);

	//test 2: switch to player 2's turn

	game.whoseTurn = secondPlayer;

	printf("\n*****Test 2: Player 2's turn after switching.*****\n");
	
	assertTrue("Test 2: Should return 1.", whoseTurn(&game), secondPlayer);

	//test 3: Test last player (MAX_PLAYERS)

	printf("\n*****Test 3: Test last player(MAX_PLAYERS).*****\n");

	game.whoseTurn = MAX_PLAYERS;

	assertTrue("Test 3: returns should be equal.", whoseTurn(&game), MAX_PLAYERS);

	//test 4: Test too many players (MAX_PLAYERS + 1)

	printf("\n*****Test 4: Test too many players (MAX_PLAYERS + 1).*****\n");

	game.whoseTurn = MAX_PLAYERS + 1;

	if (whoseTurn(&game) == MAX_PLAYERS + 1){
		printf("TEST FAILED! Returned more than MAX_PLAYERS.\n");
	}
	
	else{
		printf("TEST PASSED! Did not allow more than MAX_PLAYERS.\n");
	}


	//test 5: test negative player

	printf("\n*****Test 5: Test negative player.*****\n");

	game.whoseTurn = -100;

	if (whoseTurn(&game) == -100){
		printf("TEST FAILED! Returned a negative player.\n");
	}
	
	else{
		printf("TEST PASSED! Did not allow a negative player.\n");
	}

	printf("\n************ whoseTurn Testing Complete. ************\n");

	return 0;

}

