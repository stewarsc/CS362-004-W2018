/*Adventurer random test*/

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
  int ownCardBool;
  int treasureBool;
  int nextHandCountBool;
  int nextDeckCountBool;
  int nextDiscardCountBool;
  int coinBool;
  int valueBool;
};

//initializing errorControl struct
struct errorControl initError(struct errorControl error){
  error.handCountBool = 0;
  error.deckCountBool = 0;
  error.ownCardBool = 0;
  error.treasureBool = 0;
  error.nextHandCountBool = 0;
  error.nextDeckCountBool = 0;
  error.nextDiscardCountBool = 0;
  error.coinBool = 0;
  error.valueBool = 0;
  return error;
}
void checkAdventurer(int player, struct gameState *post, struct errorControl* error, int* testCheck){

  struct gameState pre;
  memcpy (&pre, post, sizeof(struct gameState));

  int r, z = 0, drawntreasure = 0, cardDrawn = 0, i, j;
  int temphand[MAX_HAND];
  
  r = callAdventurer(drawntreasure, post, player, cardDrawn, temphand, z);

  //changing values manually
  pre.handCount[player] = pre.handCount[player] + 1;

  //Accounting for empty deck scenario - I don't want to accidentally break 
  //function because of manually adjusting for deck count
  if (pre.deckCount[player] > 2){ 
    pre.deckCount[player] = pre.deckCount[player] - 2;
  }

  //updating deck count with discard pile
  else{
    pre.deckCount[player] = (pre.discardCount[player]) - 2;
  }

  pre.coins = pre.coins + 2;

  //*****checking that r = 0
  if (r != 0){
    printf("TEST FAILED: r did not return 0\n");
    printGameState(&pre, player);
    *testCheck = 1;
    error->valueBool = 1;
  }
  
  //*****checking that hand count is increased by 1 to account for played adventurer
  if (post->handCount[player] != pre.handCount[player] && error->handCountBool == 0){
    printf("TEST FAILED: handCount not equal.\n");
    printGameState(&pre, player);
    *testCheck = 1;
    error->handCountBool = 1;
  }

  //*****checking that deck count is decreased by 2
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

  //*****making sure cards came from own deck

  //comparing cards in hand to current cards in deck
  for (i = 0; i < post->handCount[player]; i++){

    //determines if card is in hand or not (bool value)
    int inHand = 0;

    for (j = 0; j < pre.deckCount[player]; j++){
      
      //comparing cards in testGame's hand to original games deck
      if(post->hand[0][i] == pre.deck[player][j]){
        inHand = 1;
        break;
      }
    }

    if (!inHand && error->ownCardBool == 0){
      printf("TEST FAILED: Card in hand that isn't from original deck.\n");
      printGameState(&pre, player);
      error->ownCardBool = 1;
      *testCheck = 1;
   }
  }

  //*****checking that two extra cards are treasure cards
  i = 0;
  int treasureCount = 0;
  int compareCount = 0;

  //counting # of treasures in pre and comparing to # of treasure in post
  for (i; i < pre.handCount[player]; i++){
    if (pre.hand[player][i] == copper || pre.hand[player][i] == silver 
      || pre.hand[player][i] == gold){
      treasureCount++;
    }
  }

  i = 0;
  for (i; i < post->handCount[player]; i++){
    if (post->hand[player][i] == copper || post->hand[player][i] == silver 
      || post->hand[player][i] == gold){
      compareCount++;
    }
  }

  int finalCount = compareCount - treasureCount;

  //making sure there are two more treasure cards in hand from original hand
  if (finalCount < 2 && error->treasureBool == 0){
    printf("TEST FAILED: The two extra cards aren't treasure cards.\n");
    printGameState(&pre, player);
    error->treasureBool = 1;
    *testCheck = 1;
  }

  //*****checking that coin count was increased by 2
  if (post->coins != pre.coins && error->coinBool == 0){
    printf("TEST FAILED: coin count not updated.\n");
    printGameState(&pre, player);
    error->coinBool = 1;
    *testCheck = 1;
  }


}

int main(){
  int i, j, player, n, allTestsGood = 0;
  struct errorControl errorCatcher;

  //random cards to choose from, including treasure cards
  int kCards[13] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall, copper, silver, gold};

  struct gameState G;

  printf ("Testing Adventurer.\n");

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
    
    checkAdventurer(player, &G, &errorCatcher, &allTestsGood);
  }

  //checks if any tests failed using bool value
  if(allTestsGood == 0)
    printf ("ALL TESTS OK\n");

  else
    printf("TEST(S) FAILED\n");

  return 0;

}