/* Smithy card test */

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

	printf("************ cardtest1 ************\n");
	printf("\n************Testing Smithy card.************\n");

	// copy the game state to a test case
	memcpy(&testGame, &game, sizeof(struct gameState));

	cardEffect(smithy, choice1, choice2, choice3, &testGame, handpos, &bonus);

	//Test 1: current player receives exactly 3 cards
	printf("\n*****Test 1: Testing for 3 cards added to players hand.*****\n\n");

	//cards in hand: should be + 2 because smithy card was played
	printf("Cards in hand(handCount) actual = %d, expected = %d\n", testGame.handCount[currentPlayer], game.handCount[currentPlayer] + cardsAdded);
	assertTrue("Test 1", testGame.handCount[currentPlayer], game.handCount[currentPlayer] + cardsAdded);
	
	printf("\n");
	//cards in deck: should be - 3
	printf("Cards in deck(deckCount) actual = %d, expected = %d\n", testGame.deckCount[currentPlayer], game.deckCount[currentPlayer] - cardsAdded);
	assertTrue("Test 1", testGame.deckCount[currentPlayer], game.deckCount[currentPlayer] - cardsAdded);

	//Test 2: cards come from own players pile

	printf("\n*****Test 2: Testing that cards drawn are from players pile.*****\n\n");

	i = 0;
	j = 0;

	//comparing cards in hand to current cards in deck
	for (i; i < testGame.handCount[currentPlayer]; i++){

		//determines if card is in hand or not (bool value)
		int inHand = 0;
		
		for (j; j < game.deckCount[currentPlayer]; j++){
			
			//comparing cards in testGame's hand to original games deck
			if(testGame.hand[0][i] == game.deck[currentPlayer][j]){
				printf("Card %d is from own hand. TEST PASSED!\n", testGame.hand[currentPlayer][i]);
				inHand = 1;
				break;
			}
		}

		if (!inHand) printf("Card %d not in hand. TEST FAILED.\n", testGame.hand[currentPlayer][i]);
	}

	//Test 3: No state change for other players
	printf("\n*****Test 3: No state change for other players*****\n\n");

	char* name = "Test 3";
	int newPlayer = 1;

	assertTrue(name, testGame.handCount[newPlayer], game.handCount[newPlayer]);
	assertTrue(name, testGame.deckCount[newPlayer], game.deckCount[newPlayer]);
	assertTrue(name, testGame.discardCount[newPlayer], game.discardCount[newPlayer]);
	assertTrue(name, testGame.playedCards[newPlayer], game.playedCards[newPlayer]);

	//Test 4: No state change for victory or kingdom cards
	printf("\n*****Test 4: No state change for victory and kingdom cards.*****\n");

	char* name1 = "Test 4";

	printf("\nVictory Card Test\n\n");

	assertTrue(name1, testGame.supplyCount[estate], game.supplyCount[estate]);
	assertTrue(name1, testGame.supplyCount[duchy], game.supplyCount[duchy]);
	assertTrue(name1, testGame.supplyCount[province], game.supplyCount[province]);

	printf("\nKingdom Card Test\n\n");

	i = adventurer;

	for(i; i < treasure_map; i++){
		assertTrue(name1, testGame.supplyCount[i], game.supplyCount[i]);
	}

	printf("\n\n********SMITHY TESTING COMPLETE*********\n\n");

	return 0;
}