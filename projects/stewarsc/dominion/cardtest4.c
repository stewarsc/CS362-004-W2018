/* Remodel card test */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(){

	int seed = 10;
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int players = 2;
	int currentPlayer = 0;
	struct gameState game, testGame;
	int i = 0;
	int j = 0;

	int k[10] = {smithy, adventurer, salvager, remodel, baron, great_hall, ambassador, tribute, outpost, minion};

	//calling initializeGame to set up game state
	initializeGame(players, k, seed, &game);

	printf("************ cardtest4 ************\n");
	printf("\n************Testing Remodel card.************\n");

	// copy the game state to a test case
	memcpy(&testGame, &game, sizeof(struct gameState));

	cardEffect(remodel, choice1, choice2, choice3, &testGame, handpos, &bonus);

	//Test 1: No state change for other players
	printf("\n*****Test 1: No state change for other players*****\n\n");

	char* name = "Test 1";
	int newPlayer = 1;

	assertTrue(name, testGame.handCount[newPlayer], game.handCount[newPlayer]);
	assertTrue(name, testGame.deckCount[newPlayer], game.deckCount[newPlayer]);
	assertTrue(name, testGame.discardCount[newPlayer], game.discardCount[newPlayer]);
	assertTrue(name, testGame.playedCards[newPlayer], game.playedCards[newPlayer]);

	//Test 2: Card trashed shouldn't be in deck at end
	printf("\n*****Test 2: Trashed card shouldn't be in deck at end*****\n\n");

	///resetting testGame and setting trashed card to be copper and gained card to be estate	
	choice1 = copper;
	choice2 = estate;
	memcpy(&testGame, &game, sizeof(struct gameState));

	cardEffect(remodel, choice1, choice2, choice3, &testGame, handpos, &bonus);

	int countInGame = fullDeckCount(currentPlayer, choice1, &game) - 1;
	int countInTestGame = fullDeckCount(currentPlayer, choice1, &testGame);

	assertTrue("Test 2: Numbers should be equal - means card was trashed", countInGame, countInTestGame);

	//Test 3: Card trashed should be in deck at first
	printf("\n*****Test 3: Trashed card should have been in deck at beginning*****\n\n");
	
	//chose cutpurse because it isn't in deck: gold is two more than cutpurse
	choice1 = cutpurse;
	choice2 = gold;
	memcpy(&testGame, &game, sizeof(struct gameState));

	int r = cardEffect(remodel, choice1, choice2, choice3, &testGame, handpos, &bonus);

	assertTrue("Test 3: Should have return of -1 since card isn't in deck", r, -1);

	//Test 4: Cards in hand and deck should be same after card
	printf("\n*****Test 4: Cards in hand and deck should be same after card*****\n\n");

	assertTrue("Test 4: Cards in Hand", testGame.handCount[currentPlayer], game.handCount[currentPlayer] -1);
	assertTrue("Test 4: Cards in Deck", testGame.deckCount[currentPlayer], game.deckCount[currentPlayer]);

	//Test 5: Card trashed should be <= 2 coins above exchanged card
	printf("\n*****Test 5: Trashed card value must be <= 2 from exchanged card*****\n\n");

	//case 1 - Two above it
	choice1 = remodel;
	choice2 = gold;
	memcpy(&testGame, &game, sizeof(struct gameState));

	r = cardEffect(remodel, choice1, choice2, choice3, &testGame, handpos, &bonus);

	assertTrue("Test 5: Should have return of 0 since it is <= 2", r, 0);

	//case 2 - Below cost - Example: Remodel costs less than gold
	choice1 = remodel;
	choice2 = gold;
	memcpy(&testGame, &game, sizeof(struct gameState));

	r = cardEffect(remodel, choice1, choice2, choice3, &testGame, handpos, &bonus);

	assertTrue("Test 5: Should have return of 0 since it is <= 2", r, 0);

	//case 3 - Card wanted costs more than two above trashed card
	choice1 = copper;
	choice2 = gold;
	memcpy(&testGame, &game, sizeof(struct gameState));

	r = cardEffect(remodel, choice1, choice2, choice3, &testGame, handpos, &bonus);

	assertTrue("Test 5: Should have return of -1 since it is > 2", r, -1);

	printf("\n********REMODEL TESTING COMPLETE*********\n\n");

	return 0;
}
