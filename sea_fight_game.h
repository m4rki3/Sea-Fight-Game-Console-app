#pragma once
#include"ship.h"
enum GameStatus
{
	kContinues,
	kAIWon,
	kAILost
};
class SeaFightGame
{
private:
#pragma region Fields
	int allowed_strikes_;
	int strikes_count_;
	int ship_decks_destroyed_;
	const int kWeight_ = 8;
	const int kHeight_ = 8;
	static const int kOne_deck_ships_count_ = 3;
	static const int kTwo_deck_ships_count_ = 2;
	static const int kThree_deck_ships_count_ = 1;
	Ship one_deck_ships_[kOne_deck_ships_count_];
	Ship two_deck_ships_[kTwo_deck_ships_count_];
	Ship three_deck_ships_[kThree_deck_ships_count_];
	FieldStatus** battle_field_;
	Deck* strikes_positions_;
	GameStatus game_status_;
#pragma endregion
#pragma region Methods
	void OpenMenu();
	void ShowBattleField();
	char SwitchKey();
	void StartFight();
	bool TryExit();
	void SwitchGameStatus();
	void StrikeTo(const int&, const int&);
	void AIStrikes();
	void CheckShipStatuses();
	void CheckShipsWereDestroyed();
	void MarkDestroyedShip(Ship&);
	bool ShipIsDestroyed(const Ship&);
	void ShowSummary();
#pragma endregion
public:
	SeaFightGame(const int&, Deck**, Deck**, Deck**);
	void Start();
};