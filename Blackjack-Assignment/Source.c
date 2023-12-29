#include<stdio.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>
#include <stdbool.h>
#include "Source.h"

// Cian Dicker-Hughes
// G00415413@ATU.IE

// public variables
int cardDeck[52] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
					1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 
					1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 
					1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
int playerTotalNum[4];
char cardFace[10] = "Joker", king[10] = "King", queen[10] = "Queen", jack[10] = "Jack", ace[10] = "Ace";
char dealerBust[10], busts[10] = " = Bust";
int cardNum = 51;
int playerCards[4][10];
int playerCardSplit[4][10];
int whichplayerGoneBust[3];
int playerNumofCards[4] = { 0,0,0,0 };
int playerTrun = 0, Trun = 1, howManyPlayers = -1, bust = 0, dealerTrun = 0, dealerTruns = 0, highStore = 0, 
wonPlayer = 0, splits[4] = { 0,0,0,0 };

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

// who won the game
void whoWon(int player, int end) {
	for (int i = 0; i < playerTrun; i++) {
		if (playerCards[player][i] > 0) {
			playerNumofCards[player]++;
		}
	}

	if (playerTotalNum[player] == 21) {
		if (player == 0) {
			printf("Dealer has Won\n");
		}
		else {
			printf("Player %d has Won\n", player);
		}
	}
	// when the the game end how show who won
	else if(end == true) {
		if (playerTotalNum[player] > highStore){
			highStore = playerTotalNum[player];
			wonPlayer = player;	
		} 
		else if (playerTotalNum[player] == highStore) {
			printf("There is a Tie\n");
			if (playerNumofCards[player] > playerNumofCards[wonPlayer]) {
				wonPlayer = player;
			}
			else if (playerNumofCards[player] < playerNumofCards[wonPlayer]) {
				wonPlayer = wonPlayer;
			}
			else{
				printf("they are Tie with player %d and %d\n", wonPlayer, player);
			}
		}

		if ((player + 1) >= howManyPlayers) {
			if (player == 0) {
				printf("Dealer has Won\n");
			}
			else {
				printf("Player %d has Won\n", wonPlayer);
			}
		}
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
		if (player == 0)
			printf("Dealer gone Bust\n");
		else {
			printf("Player %d gone Bust\n", player);
		}
		if (player == 0) {
			strcpy(dealerBust, busts);
		}
		else if (player >= 1){
			swapRow(player, player, 3);
			howManyPlayers = howManyPlayers - 1;
		}
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
		if (dealerTrun == 0)
		{
			if (i == 1)
			{
				printf(" 'card'");
			}
			else
				printf(" %s", cardFace);
		}
		else
			printf(" %s", cardFace);
	}
	
	for (int i = 0; i < playerTrun; i++) {
		totalCardNum = isAce(player, i, totalCardNum);
	}
	
	if (dealerTrun == 1)
	{
		totalCardNum = playerTotalPoints(player);
		printf(" = %d", totalCardNum);
	}

	printf("%s", dealerBust);
	printf("\n");
}

int whichFaceCardSplitHand(int i, int player) {
	int CardNum = 0;
	// what card is it e.g. is it a king, queen, jack or ace
	if (playerCardSplit[player][i] == 1) {
		strcpy(cardFace, ace);
		CardNum = 11;
	}
	else if (playerCardSplit[player][i] == 11) {
		strcpy(cardFace, jack);
		CardNum = 10;
	}
	else if (playerCardSplit[player][i] == 12) {
		strcpy(cardFace, queen);
		CardNum = 10;
	}
	else if (playerCardSplit[player][i] == 13) {
		strcpy(cardFace, king);
		CardNum = 10;
	}
	else {
		sprintf(cardFace, "%d", playerCardSplit[player][i]);
		CardNum = playerCardSplit[player][i];
	}
	return CardNum;
}

// is Ace 11 or 1
int isAceSplitHand(int player, int i, int totalCardNum) {
	// if hand is over 21 and they have a ace
	int CardNum = 0;
	if (playerCardSplit[player][i] == 1)
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

void displayPlayerSplitHand(int player) {

	int totalCardNum = 0;

	printf("Player %d (2) hand -", player);

	for (int i = 0; i < playerTrun; i++) {

		whichFaceCardSplitHand(i, player);

		printf(" %s", cardFace);
	}

	for (int i = 0; i < playerTrun; i++) {
		isAceSplitHand(player, i, totalCardNum);
	}

	totalCardNum = playerTotalPoints(player);

	printf(" = %d", totalCardNum);
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

		if (splits[player] == 1) {
			displayPlayerSplitHand(player);
		}
	}
}


// give next card out to players
void handCardOut(int whichPlayer) {
		
		playerCards[whichPlayer][playerTrun] = cardDeck[cardNum];
		cardNum--;
}

// if dealer got a blackjack
void dealerBlackjack() {
	int cardnum = whichFaceCard(0, 0), totalNum;
	if (cardnum == 10 || cardnum == 11)
	{
		totalNum = cardnum;
		cardnum = whichFaceCard(0, 1);
		totalNum = totalNum + cardnum;
		if (totalNum == 21) {
			printf("Dealer has got a blackJack\n");
			exit(0);
		}
	}
}

// hand out the cards to players for frist two card
void fristHandCardOut(int players) {
	
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < players; j++)
		{
			playerCards[j][i] = cardDeck[cardNum];
			cardNum--;
		}
		playerTrun++; dealerTruns++;
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

// split the player hand
void split(int player) {
	int playerOptions, j = 0, CardNum1, CardNum2;
	CardNum1 = whichFaceCard(0, player);
	CardNum2 = whichFaceCard(1, player);
	if (CardNum1 == CardNum2)
	{
		if (player > 0) {
			do {

				printf("does Player %d what to Splits their cards? (1 for yes and 2 for no)\n", player);
				scanf_s("%d", &playerOptions);
				if (playerOptions == 1 || playerOptions == 2) {
					j = 1;
				}
				else {
					printf("Enter 1 to Split your hand or 2 to not Split your hand\n\n");
					j = 0;
				}
			} while (j == 0);
			if (playerOptions == 1) {
				printf("You Split\n");
				playerCardSplit[player][0] = playerCards[player][1];
				playerTrun--;
				handCardOut(player);
				playerCardSplit[player][playerTrun] = cardDeck[cardNum];
				cardNum--;
				playerTrun++;
				splits[player] = 1;
			}
			else {
				return 0;
			}
		}
		else {
			return 0;
		}
	}

}

// loading game from .txt file from a saved game
void loadGame() {
	FILE* game;

	game = fopen("GameSave.txt", "r");

	// variables
	int cardDeck1[52], playerCards1[4][10];
	int cardNum1 = 0, howManyPlayers1 = 0, playerTrun1 = 0;

	for (int i = 0; i < 51; i++)
	{
		fscanf(game, "%2d", &cardDeck1[i]);
		cardDeck[i] = cardDeck1[i];
	}

	fscanf(game, "%2d", &cardNum1);
	cardNum = cardNum1;

	fscanf(game, "%2d", &howManyPlayers1);
	howManyPlayers = howManyPlayers1;

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < howManyPlayers; j++) {
			fscanf(game, "%2d", &playerCards1[j][i]);
			playerCards[j][i] = playerCards1[j][i];
		}
	}

	fscanf(game, "%2d", &playerTrun1);
	playerTrun = playerTrun1;

	fclose(game);
}

// save the game to a .txt
void saveGame() {
	FILE* game;
	game = fopen("GameSave.txt", "w");

	for (int i = 51; i > 0; i--) {
		fprintf(game, "%d\n", cardDeck[i]);
	} fprintf(game, "\n");

	fprintf(game, "%d\n\n", cardNum);

	fprintf(game, "%d\n\n", howManyPlayers);

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < howManyPlayers; j++) {
			fprintf(game, "%d\n", playerCards[j][i]);
		}
	} fprintf(game, "\n");

	fprintf(game, "%d\n\n", playerTrun);

	//fprintf(game, "Debug\n");

	fclose(game);
}

void main(){

	// variables
	int game, j, save, usersave, playerOptions = 0, playerStand = -1, allPlayerStand = 0, dealerStand = 0, temp = 0;
	bool end = false;
	// do player what to start new game or play a previous game
	do
	{
		printf("Do you want to start a new game or a previous game? (Enter 1 to start new game or Enter 2 to start save game)\n");
		scanf_s("%d", &game);
		if (game == 1 || game == 2) {
			j = 1;
		}
		else {
			printf("Enter 1 to start new game or 2 to start save game\n\n");
			j = 0;
		}
	} while (j == 0);

	if (game == 2) {
		loadGame();
	}
	else
	{
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
	}
	
	// display hand
	for (int i = 0; i < howManyPlayers; i++)
	{
		displayPlayerHand(i);
	}
	for (int i = 0; i < howManyPlayers; i++) {
		whoWon(i, end);
	}printf("\n");
	
	dealerBlackjack();

	for (int i = 0; i < howManyPlayers; i++)
	{
		split(i);
	} printf("\n");
	
	for (int i = 0; i < howManyPlayers; i++)
	{
		displayPlayerHand(i);
	}

	// asking the user if they want to save game
	do 
	{
		printf("Do you want to save the Game? (1 for yes or 2 for no)\n");
		scanf_s("%d", &save);
		if (save == 1)
		{
			printf("Game has been save");
			saveGame();
		}
		else {
			printf("Game has not been save");
		}

		if (save == 1 || save == 2)
		{
			usersave = 1;
		}
		else
		{
			printf("Enter 1 to save game or 2 to not save game\n");
			usersave = 0;
		}
	} while (usersave == 0); printf("\n");

	// if all player stand
	do {
		allPlayerStand = 0;
		// do player whats a new card 
		for (int i = 1; i < howManyPlayers; i++) {
			do {
				printf("Do player %d what to Hit or Stand? (enter 1 to Hit or enter 2 to Stand)\n", i);
				scanf_s("%d", &playerOptions);
				if (playerOptions == 1)
				{
					printf("You Hit\n");
					handCardOut(i);
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
			playerTrun--;
		}
		else{
			j = 0;
		}
		playerTrun++;
	
		//display the the players and see who gone bust or won
		for (int i = 0; i < howManyPlayers; i++) {
			goneBust(i);
		}printf("\n");

		for (int i = 0; i < howManyPlayers; i++) {
			displayPlayerHand(i);
		}printf("\n");

		for (int i = 0; i < howManyPlayers; i++) {
			whoWon(i, end);
		}printf("\n"); printf("\n");

		// asking the user if they want to save game
		do
		{
			printf("Do you want to save the Game? (1 for yes or 2 for no)\n");
			scanf_s("%d", &save);
			if (save == 1)
			{
				printf("Game has been save");
				saveGame();
			}
			else {
				printf("Game has not been save");
			}
			if (save == 1 || save == 2)
			{
				usersave = 1;
			}
			else
			{
				printf("Enter 1 to save game or 2 to not save game\n");
				usersave = 0;
			}
		} while (usersave == 0); printf("\n");

	} while(j == 0);

	// dealer turn
	printf("The Dealer turn\n\n");
	dealerTrun = 1;
	for (int i = 0; i < howManyPlayers; i++) {
		displayPlayerHand(i);
	}printf("\n");
	do {
		dealerStand = 0;
		// do dealer whats a new card 
		do {
			printf("Do you what to Hit or Stand? (enter 1 to Hit or enter 2 to Stand)\n");
			scanf_s("%d", &playerOptions);
			if (playerOptions == 1)
			{
				if (playerTrun == dealerTruns)
				{
					playerTrun++;
				}
				temp = playerTrun;
				playerTrun = dealerTruns;
				printf("You Hit\n");
				handCardOut(0);
				playerTrun = temp;
			}
			else
			{
				printf("You Stand\n");
				dealerStand = 1;
			}
			if (playerOptions == 1 || playerOptions == 2) {
	
			}
			else {
				printf("Enter 1 to Hit or 2 to Stand\n\n");
				dealerStand = 3;
			}
		} while (dealerStand == 3); printf("\n");
		dealerTruns++;
		if (dealerStand == 1) {
			j = 1;
		}
		else {
			j = 0;
		}

		// display the the dealer and players and see who gone bust or won
		for (int i = 0; i < howManyPlayers; i++) {
			goneBust(i);
		}printf("\n");

		for (int i = 0; i < howManyPlayers; i++) {
			displayPlayerHand(i);
		}printf("\n");
		end = true;
		for (int i = 0; i < howManyPlayers; i++) {
			whoWon(i, end);
		}printf("\n");

		// asking the user if they want to save game
		do
		{
			printf("Do you want to save the Game? (1 for yes or 2 for no)\n");
			scanf_s("%d", &save);
			if (save == 1)
			{
				printf("Game has been save");
				saveGame();
			}
			else {
				printf("Game has not been save");
			}
			if (save == 1 || save == 2)
			{
				usersave = 1;
			}
			else
			{
				printf("Enter 1 to save game or 2 to not save game\n");
				usersave = 0;
			}
		} while (usersave == 0); printf("\n");

	} while (j == 0);

	printf("Game has ended\n");

}