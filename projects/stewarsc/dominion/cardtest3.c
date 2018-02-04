/* Salvager card test */

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
	int cardsAdded = 2;
	int i = 0;
	int j = 0;

	int k[10] = {smithy, adventurer, salvager, remodel, baron, great_hall, ambassador, tribute, outpost, minion};

	//calling initializeGame to set up game state
	initializeGame(players, k, seed, &game);

	printf("************ cardtest3 ************\n");
	printf("\n************Testing Salvager card.************\n");

	// copy the game state to a test case
	memcpy(&testGame, &game, sizeof(struct gameState));

	cardEffect(salvager, choice1, choice2, choice3, &testGame, handpos, &bonus);

	//Test 1: No state change for other players
	printf("\n*****Test 1: No state change for other players*****\n\n");

	char* name = "Test 1";
	int newPlayer = 1;

	assertTrue(name, testGame.handCount[newPlayer], game.handCount[newPlayer]);
	assertTrue(name, testGame.deckCount[newPlayer], game.deckCount[newPlayer]);
	assertTrue(name, testGame.discardCount[newPlayer], game.discardCount[newPlayer]);
	assertTrue(name, testGame.playedCards[newPlayer], game.playedCards[newPlayer]);

	//Test 2: +1 Buys
	printf("\n*****Test 2: +1 Buys*****\n\n");

	//number of buys in test should be + 1 in regular game
	assertTrue("Test 2", testGame.numBuys, game.numBuys + 1);

	//Test 3: Cost of trashed card should be equal to coins added
	printf("\n*****Test 3: Cost of cards = coins added*****\n\n");

	//resetting testGame and setting trashed card to be estate (2 coins)	
	choice1 = estate;
	memcpy(&testGame, &game, sizeof(struct gameState));

	cardEffect(salvager, choice1, choice2, choice3, &testGame, handpos, &bonus);

	assertTrue("Test 3: Non-Zero Value Card", testGame.coins, game.coins + getCost(choice1));

	//resetting testGame and setting trashed card to be copper (0 coins)
	choice1 = copper;
	memcpy(&testGame, &game, sizeof(struct gameState));

	cardEffect(salvager, choice1, choice2, choice3, &testGame, handpos, &bonus);

	assertTrue("Test 3: Zero Value Card", testGame.coins, game.coins + getCost(choice1));

	//Test 4: hand count should be - 2
	printf("\n*****Test 4: Hand Count should be - 2 from original*****\n\n");

	//resetting testGame and setting trashed card to be estate (2 coins)	
	choice1 = estate;
	memcpy(&testGame, &game, sizeof(struct gameState));

	cardEffect(salvager, choice1, choice2, choice3, &testGame, handpos, &bonus);

	assertTrue("Test 4-Hand Count", testGame.handCount[currentPlayer], game.handCount[currentPlayer] - 2);

	//Test 5: Card trashed shouldn't be in deck at end
	printf("\n*****Test 5: Trashed card shouldn't be in deck at end*****\n\n");

	//using estate from above test as trash card

	int countInGame = fullDeckCount(currentPlayer, choice1, &game) - 1;
	int countInTestGame = fullDeckCount(currentPlayer, choice1, &testGame);

	assertTrue("Test 5: Numbers should be equal - means card was trashed", countInGame, countInTestGame);

	//Test 6: Card trashed should be in deck at first
	printf("\n*****Test 6: Trashed card should have been in deck at beginning*****\n\n");
	
	//chose treasure_map because it is not in deck
	choice1 = treasure_map;
	memcpy(&testGame, &game, sizeof(struct gameState));

	int r = cardEffect(salvager, choice1, choice2, choice3, &testGame, handpos, &bonus);

	assertTrue("Test 6: Should have return of -1 since card isn't in deck", r, -1);

	printf("\n********SALVAGER TESTING COMPLETE*********\n\n");

	return 0;
}