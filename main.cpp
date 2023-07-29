#include"sea_fight_game.h"
#include"ship.h"
using namespace std;
int main()
{
	const int allowed_strikes = 40;
	Deck** one_deck, ** two_deck, ** three_deck;
	one_deck = new Deck * [3];
	two_deck = new Deck * [2];
	three_deck = new Deck * [1];
	int i;
	for (i = 0; i < 3; i++) one_deck[i] = new Deck[1];
	for (i = 0; i < 2; i++) two_deck[i] = new Deck[2];
	three_deck[0] = new Deck[3];
	one_deck[0][0].row = 0;
	one_deck[0][0].column = 4;
	one_deck[1][0].row = 3;
	one_deck[1][0].column = 0;
	one_deck[2][0].row = 7;
	one_deck[2][0].column = 4;
	two_deck[0][0].row = 5;
	two_deck[0][0].column = 1;
	two_deck[0][1].row = 5;
	two_deck[0][1].column = 2;
	two_deck[1][0].row = 3;
	two_deck[1][0].column = 6;
	two_deck[1][1].row = 4;
	two_deck[1][1].column = 6;
	three_deck[0][0].row = 3;
	three_deck[0][0].column = 4;
	three_deck[0][1].row = 4;
	three_deck[0][1].column = 4;
	three_deck[0][2].row = 5;
	three_deck[0][2].column = 4;
	SeaFightGame game(allowed_strikes, one_deck, two_deck, three_deck);
	game.Start();
	return 0;
}