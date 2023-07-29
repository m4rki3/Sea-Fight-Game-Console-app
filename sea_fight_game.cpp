#include "sea_fight_game.h"
#include<iostream>
using namespace std;
SeaFightGame::SeaFightGame(const int& allowed_strikes, Deck** one_deck_positions, Deck** two_deck_positions, Deck** three_deck_positions)
{
	allowed_strikes_ = allowed_strikes;
	strikes_count_ = 0;
	ship_decks_destroyed_ = 0;
	game_status_ = kContinues;
	strikes_positions_ = new Deck[allowed_strikes];
	battle_field_ = new FieldStatus * [kHeight_];
	int i, j;
	for (i = 0; i < kHeight_; i++)
	{
		battle_field_[i] = new FieldStatus[kWeight_];
		for (j = 0; j < kWeight_; j++)
			battle_field_[i][j] = kNull;
	}
	for (i = 0; i < kOne_deck_ships_count_; i++)
	{
		one_deck_ships_[i] = Ship(kOneDeck, one_deck_positions[i]);
		battle_field_[one_deck_positions[i][0].row][one_deck_positions[i][0].column] = kDeck;
	}
	for (i = 0; i < kTwo_deck_ships_count_; i++)
	{
		two_deck_ships_[i] = Ship(kTwoDeck, two_deck_positions[i]);
		for (j = 0; j < 2; j++)
			battle_field_[two_deck_positions[i][j].row][two_deck_positions[i][j].column] = kDeck;
	}
	for (i = 0; i < kThree_deck_ships_count_; i++)
	{
		three_deck_ships_[i] = Ship(kThreeDeck, three_deck_positions[i]);
		for (j = 0; j < 3; j++)
			battle_field_[three_deck_positions[i][j].row][three_deck_positions[i][j].column] = kDeck;
	}
}
void SeaFightGame::OpenMenu()
{
	cout << '\n' << '\n' << '\n' << '\n';
	cout << '\t' << '\t' << "SEA FIGHT GAME" << '\n' << '\n';
	cout << '\t' << '\t' << "1 - START GAME" << '\n';
	cout << '\t' << '\t' << "2 - EXIT" << '\n';
}
void SeaFightGame::ShowBattleField()
{
	cout << '\n' << '\n' << '\n' << '\n';
	cout << '\t' << '\t' << "  A B C D E F G H" << '\n';
	cout << '\t' << '\t' << " * * * * * * * * *" << '\n';
	int i, j;
	for (i = 0; i < kHeight_; i++)
	{
		cout << '\t' << '\t' << i + 1 << '*';
		for (j = 0; j < kWeight_; j++)
		{
			switch (battle_field_[i][j])
			{
			case kDeck:
				cout << '+';
				break;
			case kDestroyed:
				cout << '#';
				break;
			case kWreck:
				cout << '@';
				break;
			default:
				cout << ' ';
				break;
			}
			if (j != kWeight_ - 1)cout << ' ';
		}
		cout << '*' << '\n';
	}
	cout << '\t' << '\t' << " * * * * * * * * *" << '\n';
}
char SeaFightGame::SwitchKey()
{
	while (true)
	{
		switch (getchar())
		{
		case '1':
			return '1';
		case '2':
			return '2';
		default: continue;
		}
	}
}
bool SeaFightGame::TryExit()
{
	system("cls");
	cout << '\n' << '\n' << '\n' << '\n';
	cout << '\t' << '\t' << "Are you sure to exit?" << '\n';
	cout << '\t' << '\t' << "1 - YES" << '\n';
	cout << '\t' << '\t' << "2 - CANCEL" << '\n';
	if (SwitchKey() == '1') return true;
	return false;
}
void SeaFightGame::StrikeTo(const int& row, const int& column)
{
	if (battle_field_[row][column] == kDeck)
	{
		int i;
		battle_field_[row][column] = kDestroyed;
		ship_decks_destroyed_++;
	}
	else  battle_field_[row][column] = kWreck;
	strikes_positions_[strikes_count_].row = row;
	strikes_positions_[strikes_count_].column = column;
	strikes_count_++;
}
void SeaFightGame::AIStrikes()
{
	int i, j;
	for (i = 0; i < kHeight_; i++)
	{
		for (j = 0; j < kWeight_; j++)
			if (battle_field_[i][j] == kDestroyed)
				if (i > 0 && battle_field_[i - 1][j] != kDestroyed && battle_field_[i - 1][j] != kWreck)
				{
					StrikeTo(i - 1, j);
					return;
				}
				else if (i < kHeight_ - 1 && battle_field_[i + 1][j] != kDestroyed && battle_field_[i + 1][j] != kWreck)
				{
					StrikeTo(i + 1, j);
					return;
				}
				else if (j > 0 && battle_field_[i][j - 1] != kDestroyed && battle_field_[i][j - 1] != kWreck)
				{
					StrikeTo(i, j - 1);
					return;
				}
				else if (j < kWeight_ - 1 && battle_field_[i][j + 1] != kDestroyed && battle_field_[i][j + 1] != kWreck)
				{
					StrikeTo(i, j + 1);
					return;
				}
	}
	int random_row = rand() % kHeight_;
	int random_column = rand() % kWeight_;
	while (battle_field_[random_row][random_column] == kWreck ||
		   battle_field_[random_row][random_column] == kDestroyed)
	{
		random_row = rand() % kHeight_;
		random_column = rand() % kWeight_;
	}
	StrikeTo(random_row, random_column);
}
void SeaFightGame::SwitchGameStatus()
{
	cout << '\n' << '\n' << '\n' << '\n' << '\t' << '\t' << '\t';
	switch (game_status_)
	{
	case kAIWon:
		cout << "AI WON" << '\n';
		getchar();
		break;
	default:
		cout << "AI LOST" << '\n';
		getchar();
		break;
	}
}
void SeaFightGame::ShowSummary()
{
	cout << '\n' << '\n' << '\t' << '\t' << "SUMMARY:" << '\n';
	cout << '\t' << '\t' << "Number of ship decks destroyed: " << ship_decks_destroyed_ << '\n';
	cout << '\t' << '\t' << "Number of strikes were dealed: " << strikes_count_ << '\n';
	for (int i = 0; i < strikes_count_; i++)
	{
		cout << '\t' << '\t' << i + 1 << " strike: ";
		if (battle_field_[strikes_positions_[i].row][strikes_positions_[i].column] == kDestroyed)
			cout << "ship deck was successfully destroyed.";
		else cout << "missile strike has missed.";
		cout << '\n';
	}
}
bool SeaFightGame::ShipIsDestroyed(const Ship& ship)
{
	for (int i = 0; i < ship.length_; i++)
		if (battle_field_[ship.positions_[i].row][ship.positions_[i].column] == kDeck)
			return false;
	return true;
}
void SeaFightGame::CheckShipStatuses()
{
	int i;
	bool ships_are_destroyed = true;
	for (i = 0; i < kOne_deck_ships_count_ && ships_are_destroyed; i++)
	{
		if (!ShipIsDestroyed(one_deck_ships_[i]))
			ships_are_destroyed = false;
	}
	for (i = 0; i < kTwo_deck_ships_count_ && ships_are_destroyed; i++)
	{
		if (!ShipIsDestroyed(two_deck_ships_[i]))
			ships_are_destroyed = false;
	}
	for (i = 0; i < kThree_deck_ships_count_ && ships_are_destroyed; i++)
	{
		if (!ShipIsDestroyed(three_deck_ships_[i]))
			ships_are_destroyed = false;
	}
	if (ships_are_destroyed) game_status_ = kAIWon;
}
void SeaFightGame::CheckShipsWereDestroyed()
{
	int i;
	for (i = 0; i < kOne_deck_ships_count_; i++)
	{
		if (ShipIsDestroyed(one_deck_ships_[i]) && !one_deck_ships_[i].marked_as_destroyed_)
		{ 
			MarkDestroyedShip(one_deck_ships_[i]);
			return;
		}
	}
	for (i = 0; i < kTwo_deck_ships_count_; i++)
	{
		if (ShipIsDestroyed(two_deck_ships_[i]) && !two_deck_ships_[i].marked_as_destroyed_)
		{
			MarkDestroyedShip(two_deck_ships_[i]);
			return;
		}
	}
	for (i = 0; i < kThree_deck_ships_count_; i++)
	{
		if (ShipIsDestroyed(three_deck_ships_[i]) && !three_deck_ships_[i].marked_as_destroyed_)
		{
			MarkDestroyedShip(three_deck_ships_[i]);
			return;
		}
	}
}
void SeaFightGame::MarkDestroyedShip(Ship& ship)
{
	for (int i = 0; i < ship.length_; i++)
	{
		if (ship.positions_[i].row > 0 && battle_field_[ship.positions_[i].row - 1][ship.positions_[i].column] != kDestroyed)
			battle_field_[ship.positions_[i].row - 1][ship.positions_[i].column] = kWreck;
		if (ship.positions_[i].row < kHeight_ - 1 && battle_field_[ship.positions_[i].row + 1][ship.positions_[i].column] != kDestroyed)
			battle_field_[ship.positions_[i].row + 1][ship.positions_[i].column] = kWreck;
		if (ship.positions_[i].column > 0 && battle_field_[ship.positions_[i].row][ship.positions_[i].column - 1] != kDestroyed)
			battle_field_[ship.positions_[i].row][ship.positions_[i].column - 1] = kWreck;
		if (ship.positions_[i].column < kWeight_ - 1 && battle_field_[ship.positions_[i].row][ship.positions_[i].column + 1] != kDestroyed)
			battle_field_[ship.positions_[i].row][ship.positions_[i].column + 1] = kWreck;
		if (ship.positions_[i].row > 0 && ship.positions_[i].column > 0 && battle_field_[ship.positions_[i].row - 1][ship.positions_[i].column - 1] != kDestroyed)
			battle_field_[ship.positions_[i].row - 1][ship.positions_[i].column - 1] = kWreck;
		if (ship.positions_[i].row > 0 && ship.positions_[i].column < kWeight_ - 1 && battle_field_[ship.positions_[i].row - 1][ship.positions_[i].column + 1] != kDestroyed)
			battle_field_[ship.positions_[i].row - 1][ship.positions_[i].column + 1] = kWreck;
		if (ship.positions_[i].row < kHeight_ - 1 && ship.positions_[i].column > 0 && battle_field_[ship.positions_[i].row + 1][ship.positions_[i].column - 1] != kDestroyed)
			battle_field_[ship.positions_[i].row + 1][ship.positions_[i].column - 1] = kWreck;
		if (ship.positions_[i].row < kHeight_ - 1 && ship.positions_[i].column < kWeight_ - 1 && battle_field_[ship.positions_[i].row + 1][ship.positions_[i].column + 1] != kDestroyed)
			battle_field_[ship.positions_[i].row + 1][ship.positions_[i].column + 1] = kWreck;
	}
	ship.marked_as_destroyed_ = true;
}
void SeaFightGame::StartFight()
{
	getchar();
	while (game_status_ == kContinues && strikes_count_ < allowed_strikes_)
	{
		system("cls");
		ShowBattleField();
		getchar();
		AIStrikes();
		CheckShipStatuses();
		CheckShipsWereDestroyed();
	}
	system("cls");
	ShowBattleField();
	SwitchGameStatus();
	ShowSummary();
}
void SeaFightGame::Start()
{
	srand(time(nullptr));
	while (true)
	{
		OpenMenu();
		if (SwitchKey() == '1')
		{
			StartFight();
			return;
		}
		else if (TryExit()) return;
		system("cls");
	}
}