#include "catch.hpp"

#include "../client/game/Card.h"
#include "../client/game/Deck.h"
#include "../client/game/Dealer.h"
#include "../client/game/Strategy.h"

// CARD TESTS
TEST_CASE("Cards store state internally") {
	Card card(Card::Rank::JACK, Card::Suit::DIAMONDS);
	REQUIRE(card.getRank() == Card::Rank::JACK);
	REQUIRE(card.getSuit() == Card::Suit::DIAMONDS);
}

TEST_CASE("Number cards have value") {
	Card card(Card::Rank::FIVE, Card::Suit::CLUBS);
	REQUIRE(card.getValue() == 5);
}

TEST_CASE("Face cards have value") {
	Card card(Card::Rank::KING, Card::Suit::SPADES);
	REQUIRE(card.getValue() == 10);
}

TEST_CASE("Cards have a card code") {
	Card card(Card::Rank::TWO, Card::Suit::HEARTS);
	REQUIRE(card.getCode() == "05");
}

// DECK TESTS
TEST_CASE("A deck can be made up of multiple decks") {
	Deck deck(6);
	REQUIRE(deck.size() == 52 * 6);
}

// DEALER TESTS
TEST_CASE("Dealer hits if total is under 17") {
	Dealer dealer;
	Card card0(Card::Rank::QUEEN, Card::Suit::CLUBS);
	Card card1(Card::Rank::THREE, Card::Suit::CLUBS);

	dealer.dealCard(card0);
	dealer.dealCard(card1);

	REQUIRE(dealer.wantsToHit());
}

TEST_CASE("Dealer stands if total is at or above 17") {
	Dealer dealer;
	Card card0(Card::Rank::QUEEN, Card::Suit::CLUBS);
	Card card1(Card::Rank::SEVEN, Card::Suit::CLUBS);

	dealer.dealCard(card0);
	dealer.dealCard(card1);

	REQUIRE(!dealer.wantsToHit());
	REQUIRE(dealer.playerIsDealer());
}

// Strategy Tests
TEST_CASE("Strategies compute the value of hands with numbers") {
	Dealer strategy;
	Card card0(Card::Rank::FIVE, Card::Suit::CLUBS);
	Card card1(Card::Rank::SEVEN, Card::Suit::CLUBS);

	strategy.dealCard(card0);
	strategy.dealCard(card1);

	REQUIRE(strategy.getHandValue() == 12);
	REQUIRE(!strategy.isBust());
}

TEST_CASE("Strategies compute the value of hands with faces") {
	Dealer strategy;
	Card card0(Card::Rank::FIVE, Card::Suit::CLUBS);
	Card card1(Card::Rank::KING, Card::Suit::CLUBS);
	Card card2(Card::Rank::QUEEN, Card::Suit::CLUBS);

	strategy.dealCard(card0);
	strategy.dealCard(card1);
	strategy.dealCard(card2);

	REQUIRE(strategy.getHandValue() == 25);
	REQUIRE(strategy.isBust());
}

TEST_CASE("Aces can be ones or elevens") {
	Dealer strategy;
	Card card0(Card::Rank::ACE, Card::Suit::CLUBS);
	Card card1(Card::Rank::ACE, Card::Suit::CLUBS);
	Card card2(Card::Rank::FIVE, Card::Suit::CLUBS);

	strategy.dealCard(card0);
	strategy.dealCard(card1);
	strategy.dealCard(card2);

	REQUIRE(strategy.getHandValue() == 17);
	REQUIRE(!strategy.isBust());
}

TEST_CASE("Strategies can have natural blackjack") {
	Dealer strategy;
	Card card0(Card::Rank::ACE, Card::Suit::CLUBS);
	Card card1(Card::Rank::KING, Card::Suit::CLUBS);

	strategy.dealCard(card0);
	strategy.dealCard(card1);
	
	REQUIRE(strategy.hasNaturalBlackjack());
	REQUIRE(strategy.getHandValue() == 21);
	REQUIRE(!strategy.isBust());
}