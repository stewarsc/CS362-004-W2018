/* Unit test for isGameOver function */

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
	struct gameState game, testGame;

	int k[10] = {smithy, adventurer, salvager, remodel, baron, great_hall, ambassador, tribute, outpost, minion};

	//initializing game for testing
	initializeGame(players, k, seed, &game);

	//copying game state to testGame
	memcpy(&testGame, &game, sizeof(struct gameState));

	printf("************ unittest4 ************\n");
	printf("\n********** Testing isGameOver Function **********\n");

	//test1: does it return 0 in normal circumstances
	printf("\n***** Test 1: Return 0 for normal *****\n");

	assertTrue("Test 1", isGameOver(&game), 0);

	//Test 2: Province pile empty
	printf("\n***** Test 2: Province pile empty *****\n");

	//resetting game state
	memcpy(&testGame, &game, sizeof(struct gameState));

	//emptying supply count of province
	testGame.supplyCount[province] = 0;

	assertTrue("Test 2: No Province cards - game should end", isGameOver(&testGame), 1);

	//Test 3: 3 Supply Piles empty using cards from k
	printf("\n***** Test 3: One Supply Pile empty *****\n");

	//resetting game state
	memcpy(&testGame, &game, sizeof(struct gameState));

	//emptying smithy supplly count
	testGame.supplyCount[smithy] = 0;

	assertTrue("Test 3: One supply pile empty (smithy).", isGameOver(&testGame), 0);

	//test 4: 2 supply piles empty - game shouldn't end
	printf("\n***** Test 4: Two Supply Piles empty *****\n");

	//emptying adventurer to go with smithy
	testGame.supplyCount[adventurer] = 0;

	assertTrue("Test 4: Two supply piles empty.", isGameOver(&testGame), 0);

	//test 5: 3 supply piles empty - game shouldn't end
	printf("\n***** Test 5: Three Supply Piles empty - should end *****\n");

	//emptying great_hall to go with smithy and adventurer
	testGame.supplyCount[great_hall] = 0;

	assertTrue("Test 5: Three supply piles empty. Should end.", isGameOver(&testGame), 1);

	printf("\n************ isGameOver Testing Complete. ************\n");

	return 0;

}