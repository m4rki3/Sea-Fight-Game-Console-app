#pragma once
struct Deck
{
	int row;
	int column;
};
enum ShipType
{
	kOneDeck,
	kTwoDeck,
	kThreeDeck
};
enum FieldStatus
{
	kDestroyed,
	kDeck,
	kNull,
	kWreck
};
class Ship
{
private:
	int length_;
	bool marked_as_destroyed_;
	Deck* positions_;
public:
	friend class SeaFightGame;
	Ship();
	Ship(const ShipType&, Deck*);
	void operator = (const Ship&);
};