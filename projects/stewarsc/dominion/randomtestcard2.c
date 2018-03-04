/*Village random test*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include<stdlib.h>
#include<time.h>

//holds bools for specific tests to stop repeating errors
struct errorControl{
  int handCountBool;
  int deckCountBool;
  int discardCountBool;
  int ownCardBool;
  int nextHandCountBool;
  int nextDeckCountBool;
  int nextDiscardCountBool;
  int actionsBool;
  int valueBool;
};

//initializing errorControl struct
struct errorControl initError(struct errorControl error){
  error.handCountBool = 0;
  error.deckCountBool = 0;
  error.discardCountBool = 0;
  error.ownCardBool = 0;
  error.nextHandCountBool = 0;
  error.nextDeckCountBool = 0;
  error.nextDiscardCountBool = 0;
  error.actionsBool = 0;
  error.valueBool = 0;

  return error;
}

void checkVillage(int player, struct gameState *post, struct errorControl* error, int* testCheck){

  struct gameState pre;
  memcpy (&pre, post, sizeof(struct gameState));

  int r, handPos = 0;
  
  r = callVillage(player, post, handPos);

  //changing values manually

  //Accounting for empty deck scenario - I don't want to accidentally break 
  //function because of manually adjusting for deck count
  if (pre.deckCount[player] > 1) {
    pre.deckCount[player] = pre.deckCount[player] - 1;
  }

  //updating deck count with discard pile
  else{
    pre.deckCount[player] = (pre.discardCount[player] - 1) ;
  }

  pre.numActions = pre.numActions + 2;

  //*****checking that r = 0
  if (r != 0){
    printf("TEST FAILED: r did not return 0\n");
    printGameState(&pre, player);
    *testCheck = 1;
    error->valueBool = 1;
  }

  //*****checking that hand count is same as before to account for added card and played card
  if (post->handCount[player] != pre.handCount[player] && error->handCountBool == 0){
    printf("TEST FAILED: handCount not equal.\n");
    printGameState(&pre, player);
    *testCheck = 1;
    error->handCountBool = 1;
  }

  //*****checking that deck count is - 1
  if (post->deckCount[player] != pre.deckCount[player] && error->deckCountBool == 0){
    printf("TEST FAILED: deckCount not equal.\n");
    printGameState(&pre, player);
    *testCheck = 1;
    error->deckCountBool = 1;
  }

  //*****no state change for other players
  if (post->handCount[1] != pre.handCount[1] && error->nextHandCountBool == 0){
    printf("TEST FAILED: handCount changed for next player.\n");
    printGameState(&pre, player);
    *testCheck = 1;
    error->nextHandCountBool = 1;
  }

  if (post->deckCount[1] != pre.deckCount[1] && error->nextDeckCountBool == 0){
    printf("TEST FAILED: deckCount changed for next player.\n");
    printGameState(&pre, player);
    *testCheck = 1;
    error->nextDeckCountBool = 1;
  }

  if (post->discardCount[1] != pre.discardCount[1] && error->nextDiscardCountBool == 0){
    printf("TEST FAILED: discardCount changed for next player.\n");
    printGameState(&pre, player);
    *testCheck = 1;
    error->nextDiscardCountBool = 1;
  }

  //checking that number of actions is + 2
  if (post->numActions != pre.numActions && error->actionsBool == 0){
    printf("TEST FAILED: numActions not equal.\n");
    printGameState(&pre, player);
    *testCheck = 1;
    error->actionsBool = 1;
  }  

}

int main(){
  int i, j, player, n, allTestsGood = 0;
  struct errorControl errorCatcher;

  //random cards to choose from, including treasure cards
  int kCards[13] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall, copper, silver, gold};

  struct gameState G;

  printf ("Testing Village.\n");

  printf ("RANDOM TESTS.\n");

  srand(time(NULL));

  errorCatcher = initError(errorCatcher);

  for (n = 0; n < 50000; n++) {
    for (i = 0; i < sizeof(struct gameState); i++) {
      ((char*)&G)[i] = rand() % 256;
    }
    G.numPlayers = 2;
    player = 0;
    G.deckCount[player] = rand() % MAX_DECK;
    G.discardCount[player] = rand() % MAX_DECK;
    G.handCount[player] = rand() % MAX_HAND;
    G.playedCardCount = rand() % MAX_DECK;
    G.numActions = rand() % 100; //chose 100 actions since it is not likely to have more
    G.numBuys = rand() % 100; //chose 100 buys since it is not likely to have more
    G.coins = rand() % 1000; //randomly chose 1000 for coin value choice

    //filling deck with random cards from kCards (size of 13)
    for (j = 0; j < G.deckCount[player]; j++){
      G.deck[player][j] = kCards[rand() % 13];
    }

    //filling hand with random cards
    for (j = 0; j < G.handCount[player]; j++){
      G.hand[player][j] = kCards[rand() % 13];
    }  

    for (j = 0; j < G.discardCount[player]; j++){
      G.discard[player][j] = kCards[rand() % 13];
    } 

    for (j = 0; j < G.playedCardCount; j++){
      G.playedCards[j] = kCards[rand() % 13];
    } 
    
    checkVillage(player, &G, &errorCatcher, &allTestsGood);
  }

  //checks if any tests failed using bool value
  if(allTestsGood == 0)
    printf ("ALL TESTS OK\n");

  else
    printf("TEST(S) FAILED\n");

  return 0;

}