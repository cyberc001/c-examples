#include <stdio.h>

enum card_suit
{
	CLUBS,
	DIAMONDS,
	HEARTS,
	SPADES
};

enum card_value
{
	CARD_FOUR = 4,
	CARD_FIVE,
	CARD_SIX,
	CARD_SEVEN,
	CARD_EIGHT,
	CARD_NINE,
	CARD_TEN,
	CARD_JACK = 15,
	CARD_QUEEN = 25,
	CARD_KING = 50
};


struct card
{
	enum card_suit suit;
	enum card_value value;
};

void display_card(struct card* c)
{
	const char* card_suit_names[] = {"clubs", "diamonds", "hearts", "spades"};
	const char* card_value_names[] = {"four", "five", "six", "seven", "eight", "nine", "ten", "jack", "queen", "king"};
	enum card_value val = c->value;
	switch(val){
		case 15: val = 11; break;
		case 25: val = 12; break;
		case 50: val = 13; break;
	}

	printf("%s of %s\n", card_suit_names[c->suit], card_value_names[c->value - 4]);
}

int main()
{
	struct card c = {CLUBS, CARD_FOUR};
	display_card(&c);
}
