#include <cassert>
#include <iostream>

#include "PokerHand.h"

namespace {

	// Higher card
	void testCaseOne() 
	{
		poker::PokerHand hand    ("AC KH 4S 3D 7H");
		poker::PokerHand opponent("TH QS KC 2D JC");
		assert(hand.compareWith(opponent) == poker::PokerHand::Comparison::WIN);
	}

	// One pair vs high card
	void testCaseTwo() 
	{
		poker::PokerHand hand    ("AC AH 3D 4S 7H");
		poker::PokerHand opponent("TH QS KC 2D JC");
		assert(hand.compareWith(opponent) == poker::PokerHand::Comparison::WIN);
	}

	// One pair vs one pair
	void testCaseThree() 
	{
	 	poker::PokerHand hand    ("AC AH 3D 4S 7H");
	 	poker::PokerHand opponent("TH QS KC 2D QC");
	 	assert(hand.compareWith(opponent) == poker::PokerHand::Comparison::WIN);
	}

	// One pair vs two pair
	void testCaseFour() 
	{
		poker::PokerHand hand    ("AC AH 3D 4S 7H");
		poker::PokerHand opponent("TH QS TC 2D QD");
		assert(hand.compareWith(opponent) == poker::PokerHand::Comparison::LOSS);
	}

	// two pair vs three of kind
	void testCaseFive() 
	{
		poker::PokerHand hand    ("TH QS TC 2D QD");
		poker::PokerHand opponent("KD KH KS 5H 8S");
		assert(hand.compareWith(opponent) == poker::PokerHand::Comparison::LOSS);
	}

	// three of kind vs straight
	void testCaseSix() 
	{
		poker::PokerHand hand    ("KD KH KS 5H 8S");
		poker::PokerHand opponent("6S 7H 8C 9S TD");
		assert(hand.compareWith(opponent) == poker::PokerHand::Comparison::LOSS);
	}

	// one pair vs one pair tie upto last card
	void testCaseSeven() 
	{
		poker::PokerHand hand    ("AC AH 3D 4S 7H");
		poker::PokerHand opponent("AD AS 3H 4C 6D");
		assert(hand.compareWith(opponent) == poker::PokerHand::Comparison::WIN);
	}

	// flush vs straight
	void testCaseEight() 
	{
		poker::PokerHand hand    ("KD TD 8D 5D 8D");
		poker::PokerHand opponent("6S 7H 8C 9S TD");
		assert(hand.compareWith(opponent) == poker::PokerHand::Comparison::WIN);
	}

	// Full house vs flush
	void testCaseNine() 
	{
		poker::PokerHand hand    ("KD KH KS 5H 5S");
		poker::PokerHand opponent("6D 7D 8D TD QD");
		assert(hand.compareWith(opponent) == poker::PokerHand::Comparison::WIN);
	}

	// full house vs four of kind
	void testCaseTen() 
	{
		poker::PokerHand hand    ("KD KH KS 5H 5S");
		poker::PokerHand opponent("6D 6S 6C 6H 7H");
		assert(hand.compareWith(opponent) == poker::PokerHand::Comparison::LOSS);
	}

	// four of kind vs straight flush
	void testCaseEleven()
	{
		poker::PokerHand hand    ("KD KH KS KC 2S");
		poker::PokerHand opponent("6S 7S 8S 9S TS");
		assert(hand.compareWith(opponent) == poker::PokerHand::Comparison::LOSS);
	}

	// perfect tie
	void testCaseTwelve() 
	{
		poker::PokerHand hand    ("AC AH 3D 4S 7H");
		poker::PokerHand opponent("AD AS 3H 4C 7D");
		assert(hand.compareWith(opponent) == poker::PokerHand::Comparison::TIE);
	}
}

int main() {

	testCaseOne();
	testCaseTwo();
	testCaseThree();
	testCaseFour();
	testCaseFive();
	testCaseSix();
	testCaseSeven();
	testCaseEight();
	testCaseNine();
	testCaseTen();
	testCaseEleven();
	testCaseTwelve();

	std::cout << "All tests passed\n";

	return EXIT_SUCCESS;
}

