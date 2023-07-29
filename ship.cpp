#include"ship.h"
#include"sea_fight_game.h"
Ship::Ship()
{
	length_ = 1;
	positions_ = new Deck[length_];
	marked_as_destroyed_ = false;
}
Ship::Ship(const ShipType& type, Deck* positions)
{
	switch (type)
	{
	case kOneDeck:
		length_ = 1;
		break;
	case kTwoDeck:
		length_ = 2;
		break;
	case kThreeDeck:
		length_ = 3;
		break;
	}
	positions_ = new Deck[length_];
	for (int i = 0; i < length_; i++)
		positions_[i] = positions[i];
}
void Ship::operator = (const Ship& other)
{
	length_ = other.length_;
	if (positions_ != nullptr) delete[] positions_;
	positions_ = new Deck[length_];
	for (int i = 0; i < length_; i++)
		positions_[i] = other.positions_[i];
}