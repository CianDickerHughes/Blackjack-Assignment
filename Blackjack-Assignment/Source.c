#include<stdio.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>

// variables
int cardDeck[52] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
					1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 
					1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 
					1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
int deck[52];

// shuffle cards
void shuffleCards() {
	// variables
	int shuffleCardsDeck[52];
	srand(time(NULL));


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

	//



}