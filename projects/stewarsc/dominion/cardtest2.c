/* Adventurer card test */

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

	printf("************ cardtest2 ************\n");
	printf("\n************Testing Adventurer card.************\n");

	// copy the game state to a test case
	memcpy(&testGame, &game, sizeof(struct gameState));

	cardEffect(adventurer, choice1, choice2, choice3, &testGame, handpos, &bonus);

	//Test 1: No state change for other players
	printf("\n*****Test 1: No state change for other players*****\n\n");

	char* name = "Test 1";
	int newPlayer = 1;

	assertTrue(name, testGame.handCount[newPlayer], game.handCount[newPlayer]);
	assertTrue(name, testGame.deckCount[newPlayer], game.deckCount[newPlayer]);
	assertTrue(name, testGame.discardCount[newPlayer], game.discardCount[newPlayer]);
	assertTrue(name, testGame.playedCards[newPlayer], game.playedCards[newPlayer]);

	//Test 2: No state change for victory or kingdom cards
	printf("\n*****Test 2: No state change for victory and kingdom cards.*****\n");

	char* name1 = "Test 2";

	printf("\nVictory Card Test\n\n");

	assertTrue(name1, testGame.supplyCount[estate], game.supplyCount[estate]);
	assertTrue(name1, testGame.supplyCount[duchy], game.supplyCount[duchy]);
	assertTrue(name1, testGame.supplyCount[province], game.supplyCount[province]);

	printf("\nKingdom Card Test\n\n");

	i = adventurer;

	for(i; i < treasure_map; i++){
		assertTrue(name1, testGame.supplyCount[i], game.supplyCount[i]);
	}

	//Test 3: current player receives exactly 2 cards
	printf("\n*****Test 3: Testing for 2 cards added to players hand.*****\n\n");

	//cards in hand: should be + 2
	printf("Cards in hand(handCount) actual = %d, expected = %d\n", testGame.handCount[currentPlayer], game.handCount[currentPlayer] + cardsAdded);
	assertTrue("Test 3", testGame.handCount[currentPlayer], game.handCount[currentPlayer] + cardsAdded);

	//Test 4: Coin count increased by >= 2
	printf("\n*****Test 4: Testing that coin count increased by at least 2.*****\n\n");

	if (testGame.coins >= game.coins + 2){
		printf("Gained at least two coins. TEST PASSED!\n");	
	} 

	else{
		printf("Did not gain at least two coins. TEST FAILED!\n");
	}

	//Test 5: cards come from own players pile

	printf("\n*****Test 5: Testing that cards drawn are from players pile.*****\n\n");

	i = 0;
	j = 0;

	if (testGame.deckCount[currentPlayer] < 1)
			printf("No cards in deck. TEST FAILED!\n");

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

	//Test 6: Making sure two extra cards are treasure cards

	printf("\n*****Test 6: Making sure that two extra cards are treasures.*****\n\n");

	//if hand counts are equal, run test. Else, don't run because it will fail
	if(testGame.handCount[currentPlayer] == game.handCount[currentPlayer] + 2){
		i = 0;
		int treasureCount = 0;
		int compareCount = 0;

		//counting # of treasures in game and comparing to # of treasure in testGame
		for (i; i < game.handCount[currentPlayer]; i++){
			if (game.hand[currentPlayer][i] == copper || game.hand[currentPlayer][i] == silver 
				|| game.hand[currentPlayer][i] == gold){
				treasureCount++;
			}
		}

		i = 0;
		for (i; i < testGame.handCount[currentPlayer]; i++){
			if (testGame.hand[currentPlayer][i] == copper || testGame.hand[currentPlayer][i] == silver 
				|| testGame.hand[currentPlayer][i] == gold){
				compareCount++;
			}
		}

		int finalCount = compareCount - treasureCount;

		//making sure there are two more treasure cards in hand from original hand
		if (finalCount == 2){
			printf("There are two more treasure cards. TEST PASSED!\n");
		}

		else{
			printf("There are NOT two more treasure cards. TEST FAILED!\n");
		}
	}

	else{
		printf("Wrong amount of cards in hand to check. TEST FAILED!\n");
	}

	printf("\n********ADVENTURER TESTING COMPLETE*********\n\n");
	return 0;
}