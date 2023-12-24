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
int playerTotalNum[4];
char cardFace[10] = "jack", king[10] = "King", queen[10] = "Queen", jack[10] = "Jack", ace[10] = "Ace";
int cardNum = 51;
int playerCards[4][10];
int whichplayerGoneBust[3];
int playerTrun = 0, Trun = 1, howManyPlayers = -1, bust = 0;

// display the deck
void DisplayDeck(int deck[52])
{
	for (int i = 0; i < 52; i++)
	{
		printf("%d\n", deck[i]);
	}
}

// which face card is it
int whichFaceCard (int i, int player) {
	int CardNum = 0;
	// what card is it e.g. is it a king, queen, jack or ace
	if (playerCards[player][i] == 1) {
		strcpy(cardFace, ace);
		CardNum = 11;
	}
	else if (playerCards[player][i] == 11) {
		strcpy(cardFace, jack);
		CardNum = 10;
	}
	else if (playerCards[player][i] == 12) {
		strcpy(cardFace, queen);
		CardNum = 10;
	}
	else if (playerCards[player][i] == 13) {
		strcpy(cardFace, king);
		CardNum = 10;
	}
	else {
		sprintf(cardFace, "%d", playerCards[player][i]);
		CardNum = playerCards[player][i];
	}
	return CardNum;
}

// is Ace 11 or 1
int isAce(int player, int i, int totalCardNum) {
	// if hand is over 21 and they have a ace
	int CardNum = 0;
	if (playerCards[player][i] == 1)
	{	
		for (int i = 0; i < playerTrun; i++) {
			CardNum = 0;
			if (totalCardNum > 21) {
				totalCardNum = totalCardNum - 11;
				CardNum = 1;
			}
			totalCardNum = totalCardNum + CardNum;

			return totalCardNum;
		}
	}
	else
	{
		return totalCardNum;
	}
	return 0;
}

int playerTotalPoints(int player) {
	int totalCardNum = 0, CardNum = 0;
	for (int i = 0; i < playerTrun; i++) {
		CardNum = 0;

		CardNum = whichFaceCard(i, player);

		totalCardNum = totalCardNum + CardNum;
	}

	for (int i = 0; i < playerTrun; i++) {
		totalCardNum = isAce(player, i, totalCardNum);
	}

	playerTotalNum[player] = totalCardNum;
	return totalCardNum;
}

// who won
void whoWon(int player) {
	if (playerTotalNum[player] == 21) {
		printf("Player %d has Won\n", player);

	}

}

// swap the players around as the last ones are busted and don't what to display their cards any more
void swapRow(int player, int rowA, int rowB) {
	int temp = 0;
	for (int i = 0; i < 10; i++)
	{
		temp = playerCards[rowA][i];
		playerCards[rowA][i] = playerCards[rowB][i];
		playerCards[rowB][i] = temp;
	}
}

// did the play go bust or lose
void goneBust(int player) {
	playerTotalPoints(player);
	if (playerTotalNum[player] > 21) {
		printf("Player %d gone Bust\n", player);
		howManyPlayers = howManyPlayers - 1;
 		swapRow(player, player, 3);
		whichplayerGoneBust[bust] = player;
		bust++;
	}
	if (howManyPlayers < 1) {
		printf("House Wins");
	}
}


// display the dealer hand
void displayDealerHand(int player) {
	playerTotalPoints(player);
	printf("Dealer hand -");
	int totalCardNum = 0;
	for (int i = 0; i < playerTrun; i++) {
		whichFaceCard(i, player);
		if (i == 1)
		{
			printf(" 'card'");
		}
		else
			printf(" %s", cardFace);
	}
	
	for (int i = 0; i < playerTrun; i++) {
		totalCardNum = isAce(player, i, totalCardNum);
	}
	totalCardNum = playerTotalNum[player];

	//printf(" = %d", totalCardNum);
	printf("\n");
}

// display the player hand
void displayPlayerHand(int player) {
	
	int totalCardNum = 0;

	// if player one is the dealer
	if (player == 0)
		displayDealerHand(player);
	else {
		printf("Player %d hand -", player);

		for (int i = 0; i < playerTrun; i++) {

			whichFaceCard(i, player);

			printf(" %s", cardFace);
		}

		for (int i = 0; i < playerTrun; i++) {
			isAce(player, i, totalCardNum);
		}
		
		totalCardNum = playerTotalPoints(player);

		printf(" = %d", totalCardNum);
		printf("\n");		
	}
}

// give next card out to players
void handCardOut(int players, int whichPlayer) {
		
		playerCards[whichPlayer][playerTrun] = cardDeck[cardNum];
		cardNum--;
}

// hand out the cards to players for frist two card
void fristHandCardOut(int players) {
	
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < players; j++)
		{
			playerCards[j][i] = cardDeck[cardNum];
			cardNum--;
			printf("%d - %d\n", playerCards[j][i], (j + 1));
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
	// DisplayDeck(cardDeck);
}

void main(){

	// variables
	int game, j, playerOptions = 0, playerStand = -1, allPlayerStand = 0;
	/* do player what to start new game or play a previous game
	printf("Do you want to start a new game or a previous game? (Enter 1 to start new game or Enter 2 to start save game)\n");
	scanf_s("%d", &game);*/

	// get how many players to play
	do
	{
		printf("How Many player are there to play (player one is the Dealer and you need 2 or 4 player to start playing)\n");
		scanf_s("%d", &howManyPlayers);

		if (howManyPlayers >= 2 && howManyPlayers <= 4)
		{
			j = 1;
		}
		else
		{
			printf("There isn't enough players or to many players\n");
			j = 0;
		}
	} while (j == 0);

	// shuffling cards
	printf("Dealer is shuffling the Cards and handing them out\n");
	shuffleCards();

	fristHandCardOut(howManyPlayers);
	
	// display hand
	for (int i = 0; i < howManyPlayers; i++)
	{
		displayPlayerHand(i);
	}
	for (int i = 0; i < howManyPlayers; i++) {
		whoWon(i);
	}printf("\n");

	// if all player stand
	do {
		allPlayerStand = 0;
		// do player whats a new card 
		for (int i = 1; i < howManyPlayers; i++) {
			do {
				printf("Do you what to Hit or Stand? (enter 1 to Hit or enter 2 to Stand)\n");
				scanf_s("%d", &playerOptions);
				if (playerOptions == 1)
				{
					printf("You Hit\n");
					handCardOut(howManyPlayers, i);
				}
				else
				{
					printf("You Stand\n");
					allPlayerStand++;
				}

				if (playerOptions == 1 || playerOptions == 2) {
					playerStand = 1;
				}
				else {
					printf("Enter 1 to Hit or 2 to Stand\n\n");
					playerStand = 0;
				}
				
			} while (playerStand == 0); printf("\n");
		} 
		if ((allPlayerStand + 1) == howManyPlayers) {
			j = 1;
		}
		else{
			j = 0;
		}
		playerTrun++;
	
		//
		for (int i = 0; i < howManyPlayers; i++) {
			goneBust(i);
		}printf("\n");

		for (int i = 0; i < howManyPlayers; i++) {
			displayPlayerHand(i);
		}printf("\n");

		for (int i = 0; i < howManyPlayers; i++) {
			whoWon(i);
		}printf("\n");

	} while(j == 0);

	printf("The Dealer turn");

}



/* 

printf("debug\n");

whichPlayer = 0

for (int i = 0; i < howManyPlayers; i++)
	{
		displayPlayerHand(i);
	}printf("\n");

ask user if they want ace to be 1 or 11
	for (int i = 0; i < playerTrun; i++) {
		CardNum = 0;
		if (playerCards[player][i] == 1) {
			do {
				printf("\nDo you what the Ace to be a 1 or 11 (Enter 1 or 11)");
				scanf_s("%d", &ace);
				if (ace == 1)
					CardNum = 1;
				else if (ace == 11)
					CardNum = 11;
				else {
					printf("Enter 1 or 11 for your ace");
					ace = 0;
				}
			} while (ace == 0);
		}

		totalCardNum = totalCardNum + CardNum;


		if (j == 0) {
				if (playerCards[j][i] == 1 || playerCards[j][i] == 11 || playerCards[j][i] == 12 || playerCards[j][i] == 13)
				{
					printf("debug\n");
				}
			}

	}*/