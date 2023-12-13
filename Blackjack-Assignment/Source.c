#include<stdio.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>
#include "Source.h"

// public variables
int cardDeck[52] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
					1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 
					1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 
					1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
int cardNum = 51;
int playerCards[4][10];
int playerTrun= 0;

// display the deck
void DisplayDeck(int deck[52])
{
	for (int i = 0; i < 52; i++)
	{
		printf("%d\n", deck[i]);
	}
}

// show player hand
void displayPlayerHand(int player) {
	printf("Player %d -", (player + 1));
	for (int i = 0; i < playerTrun; i++) {
		printf(" %d", playerCards[player][i]);
	}
	printf("\n");
}

// hand out the cards to players
void fristHandCardOut(int players) {
	
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < players; j++)
		{
			playerCards[i][j] = cardDeck[cardNum];
			cardNum--;
			printf("%d - %d\n", playerCards[i][j], (j + 1));
		}
		playerTrun++;
	}
}

// shuffle cards
void shuffleCards() {
	// variables
	int temp, drawnCard;
	srand(time(NULL));

	// shuffling
	for (int i = 51; i > 0; i--)
	{
		drawnCard = rand() % i;
		temp = cardDeck[i];
		cardDeck[i] = cardDeck[drawnCard];
		cardDeck[drawnCard] = temp;
	}
	DisplayDeck(cardDeck);
}

void main()
{
	// variables

	int game, howManyPlayers = -1, i;

	/* do player what to start new game or play a previous game
	printf("Do you want to start a new game or a previous game? (Enter 1 to start new game or Enter 2 to start save game)\n");
	scanf_s("%d", &game);*/

	// get how many players to play
	do
	{
		printf("How Many player are there to play (player one is the Dealer and you need 2 or 4 player to start playing)\n");
		scanf("%d", &howManyPlayers);

		if (howManyPlayers >= 2 && howManyPlayers <= 4)
		{
			i = 1;
		}
		else
		{
			printf("there isn't enough players or to many players\n");
			i = 0;
		}
	} while (i == 0);

	// shuffling cards
	printf("Dealer is shuffling the Cards and handing them out\n");
	shuffleCards();

	fristHandCardOut(howManyPlayers);
	
	for (int i = 0; i < howManyPlayers; i++)
	{
		displayPlayerHand(i);
	}
	




}