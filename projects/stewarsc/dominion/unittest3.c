/* Unit test for endTurn function */

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
	int nextPlayer, currentPlayer;
	int count;
	int coinAmount = 1012;
	int r;
	struct gameState game, testGame;

	int k[10] = {smithy, adventurer, salvager, remodel, baron, great_hall, ambassador, tribute, outpost, minion};

	//initializing game for testing
	initializeGame(players, k, seed, &game);

	//copy the game state to a test case
	memcpy(&testGame, &game, sizeof(struct gameState));

	printf("************ unittest3 ************\n");
	printf("\n************Testing endTurn function.************\n");

	//Test 1: make sure it returns 0
	printf("\n*****Test 1: return 0 on completion.*****\n");
	r = endTurn(&testGame);

	assertTrue("Test 2: Should return 0 if called correctly.", r, 0);

	//Test 2: Make sure it goes to next player from player 0
	printf("\n*****Test 2: Goes to next player.*****\n");

	//resetting game state
	memcpy(&testGame, &game, sizeof(struct gameState));

	nextPlayer = whoseTurn(&testGame) + 1;

	printf("Current Player is %d, next is %d\n", whoseTurn(&testGame), nextPlayer);

	endTurn(&testGame);

	assertTrue("Test 2: Switched current player.", whoseTurn(&testGame), nextPlayer);

	//test 3: Make sure next player loops around to zero
	printf("\n*****Test 3: Goes to first player after end.*****\n");

	printf("Current Player is %d, next is %d\n", whoseTurn(&testGame), firstPlayer);

	//player should loop around to zero
	endTurn(&testGame);

	assertTrue("Test 3: Should be at player 0.", whoseTurn(&testGame), firstPlayer);

	//Test 4: Hand count of previous player should be zero and current Player 5
	printf("\n*****Test 4: Hand count reset.*****\n");

	//resetting game state
	memcpy(&testGame, &game, sizeof(struct gameState));

	//saving count of current players cards in hand and player number
	count = numHandCards(&testGame);
	currentPlayer = whoseTurn(&testGame);

	//switching turns
	endTurn(&testGame);
	assertTrue("Test 4: Current Player should have hand count of 5.", numHandCards(&testGame), 5);

	//switching back to current player
	testGame.whoseTurn = currentPlayer;

	assertTrue("Test 4: Previous player should have 0 cards in hand.", numHandCards(&testGame), 0);

	//Test 5: reset coin count
	printf("\n*****Test 5: Reset coin count *****\n");

	//resetting game state
	memcpy(&testGame, &game, sizeof(struct gameState));

	//setting coins to coinAmount(1112 is arbitrary to account for accidental matching)
	testGame.coins = coinAmount;

	endTurn(&testGame);

	//checking if coins is reset from coinAmount
	if (testGame.coins != coinAmount){
		printf("Test 5: Coin amount reset. TEST PASSED!\n");
	}

	else{
		printf("Test 5: Coin amount not reset. TEST FAILED!\n");
	}

	//Test 6: Game state reset
	printf("\n*****Test 6: Game state reset *****\n");	

	//resetting game state
	memcpy(&testGame, &game, sizeof(struct gameState));

	//making game state all 73's for ease 
	testGame.outpostPlayed = 73;
	testGame.phase = 73;
	testGame.numActions = 73;
	testGame.numBuys = 73;
	testGame.playedCardCount = 73;

	//switching turn
	endTurn(&testGame);

	//checking values against what they are supposed to be at reset
	assertTrue("Test 6: outpostPlayed", testGame.outpostPlayed, 0);
	assertTrue("Test 6: phase", testGame.phase, 0);
	assertTrue("Test 6: numActions", testGame.numActions, 1);
	assertTrue("Test 6: numBuys", testGame.numBuys, 1);
	assertTrue("Test 6: playedCardCount", testGame.playedCardCount, 0);

	//Test 7: Discard count is correct
	printf("\n*****Test 7: Discard count correct *****\n");

	//resetting game state
	memcpy(&testGame, &game, sizeof(struct gameState));

	endTurn(&testGame);

	assertTrue("Test 6: Discard count should be 5.", testGame.discardCount[firstPlayer], game.discardCount[firstPlayer] + 5);

	printf("\n************ endTurn Testing Complete. ************\n");
	
	return 0;
}