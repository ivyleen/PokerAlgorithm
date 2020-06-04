#include "PokerHand.h"
#include <ctype.h>
#include <iostream>
#include <algorithm>
#include <sstream>

// constructor
poker::PokerHand::PokerHand(std::string_view hand)
			:	hand(hand), 
				m_straightFlush(false),
				m_fourOfKind(false),
				m_fullHouse(false),
				m_flush(false),
				m_straight(false),
				m_threeOfKind(false),
				m_twoPair(false),
				m_onePair(false)
{
	m_cards.reserve(5);
	m_countOfRanks.clear();
	parseHand();
}

poker::PokerHand::Comparison poker::PokerHand::compareWith(const PokerHand& opponent) 
{
	// if we both have nothing we check the highest card
	if (!m_haveCombination && !opponent.haveCombinations()) 
	{
		return checkForResultForNonCombinationCards(opponent);
	}
	// if we don't have combination and the opponent have we lose
	else if (!m_haveCombination && opponent.haveCombinations()) {	return Comparison::LOSS; }
	// if we have combination and the opponent doesn't we win
	else if (m_haveCombination && !opponent.haveCombinations()) { return Comparison::WIN;	}
	// we both have combinations
	else if (m_haveCombination && opponent.haveCombinations() )
	{
		// check which combination is higher
		if ( static_cast<int>(getHighestCombination()) > static_cast<int>(opponent.getHighestCombination()))
		{
			// if we have the higher combination
			return Comparison::WIN;
		}
		else if ( static_cast<int>(getHighestCombination()) < static_cast<int>(opponent.getHighestCombination()) )
		{
			// if we have the lower combination
			return Comparison::LOSS;
		}
		else if (static_cast<int>(getHighestCombination()) == static_cast<int>(opponent.getHighestCombination()) )
		{
			// if we have the same combination check the higher card of combination
			if ( getHighestCardOfCombinationValue() > opponent.getHighestCardOfCombinationValue())
			{
				return Comparison::WIN;		
			}
			else if ( getHighestCardOfCombinationValue() < opponent.getHighestCardOfCombinationValue())
			{
				return Comparison::LOSS;
			}
			else if ( getHighestCardOfCombinationValue() == opponent.getHighestCardOfCombinationValue())
			{
				return checkForResultForNonCombinationCards(opponent);
			}
		}
	}
}

poker::PokerHand::Comparison poker::PokerHand::checkForResultForNonCombinationCards(const PokerHand& opponent)
{
	// if there are equal you need to loop through every card to check if they are the same
	std::vector<PokerCard> opponentHand = opponent.getHand();
	bool tie = true;
	bool win = false;

	for (int i = 0; i < m_cards.size(); ++i)
	{
		if( m_cards.at(i).getRank() != opponentHand.at(i).getRank())
		{
			if (m_cards.at(i).getValueOfRank() > opponentHand.at(i).getValueOfRank())
			{
				win = true;
			}

			tie = false;
			break;
		}
	}

	if (tie)  { return Comparison::TIE; }
	if (win)  { return Comparison::WIN; }
	if (!win) { return Comparison::LOSS;}
}

int poker::PokerHand::getHighestCardOfCombinationValue() const
{
	// get the highest card in hand
	for ( int i = m_cards.size() -1; i > 0; --i)
	{
		char card = m_cards.at(i).getRank();
		// check if the card is in the combination
		if (m_countOfRanks.find(card)->second > 1)
		{
			return m_cards.at(i).getValueOfRank();
		}
	}
}

poker::PokerHand::Combination poker::PokerHand::getHighestCombination() const
{
	// check for straight flush
	if(m_straightFlush) { return poker::PokerHand::Combination::StraightFlush; }
	// check for four of kind
	if(m_fourOfKind)    { return poker::PokerHand::Combination::FourOfKind;	}
	// check for full house
	if ( m_fullHouse)   { return poker::PokerHand::Combination::FullHouse; }
	// check for flush
	if(m_flush) 		{ return poker::PokerHand::Combination::Flush; }
	// check for straight
	if (m_straight) 	{ return poker::PokerHand::Combination::Straight; }
	// check for three of kind 
	if ( m_threeOfKind)	{ return poker::PokerHand::Combination::ThreeOfKind; }
	// check for pairs
	if (m_twoPair)		{ return poker::PokerHand::Combination::TwoPair; }
	if (m_onePair)		{ return poker::PokerHand::Combination::OnePair; }
}


void poker::PokerHand::parseHand()
{
	// do not take the spaces
	for ( int i = 0; i < hand.size()-1; i+=3)
	{
		m_cards.emplace_back(hand.substr(i,2));
	}

	// sort the vector in order to have the highest card in the back
	// and to be easier for checking for sequence
	std::sort(m_cards.begin(), m_cards.end(),[&](auto& first, auto& second)
										{
											return first.getValueOfRank() < second.getValueOfRank();
										});

	initCombinations();
}


void poker::PokerHand::initCombinations()
{
	// count the ranks
	for ( int i = 0; i < m_cards.size(); ++i)
	{
		++m_countOfRanks[m_cards.at(i).getRank()];
	}

	std::map<char,int> countOfSuits;

	// count the suits
	for ( int i = 0; i < m_cards.size(); ++i)
	{
		++countOfSuits[m_cards.at(i).getSuit()];
	}

	// if we have 5 cards with same suit we have flush
	if (countOfSuits.size() == 1) { m_flush = true;}

	// if we have 5 cards with different rank we have three options:
	// high card, straight and straight flush
	if (m_countOfRanks.size() == 5) 
	{
		// check if the cards are sequencial: if we have difference between the first and the last element
		// equals to the size -1 of the container then we have a sequence of element +1 when iterating
		// note: the vector is already sorted
		if (m_cards.at(m_cards.size()-1).getValueOfRank() - m_cards.at(0).getValueOfRank() == m_cards.size() -1)
		{
			// if they are, we have two options: straight or straight flush
			if ( m_flush) { m_flush = false; m_straightFlush = true;} else {m_straight = true;}
		}
		else
		{
			// if not we only have highCard
			m_highCard = true; 
		}
	}

	// check for combinations
	m_haveCombination = m_flush || m_straightFlush || m_straight;

	// if we already have the combination no need of looping anymore
	if (!m_haveCombination)
	{
		for ( std::pair<char,int> c : m_countOfRanks)
		{		
			char card = c.first;
			int count = c.second;
	
			// check if we have four of rank
			if ( count == 4) { m_fourOfKind = true; break;}

			// check if we have one pair, two pair or full house
			if ( count == 2) { if (!m_onePair) { if(!m_threeOfKind) {m_onePair = true;} 
												 else { m_threeOfKind = false; m_fullHouse = true;} }
							   else { m_onePair = false; m_twoPair = true; } }
			
			//check if we have three of kind or full house
			if ( count == 3) { if (!m_onePair) {m_threeOfKind = true;} 
							   else { m_onePair = false; m_fullHouse = true; } }
		}

		// check for combination
		m_haveCombination = m_onePair || m_twoPair || m_threeOfKind || m_fullHouse || m_fourOfKind;
	}
}

int poker::PokerHand::PokerCard::getValueOfRank() const
{
	if (std::isdigit(rank))
	{
		return (rank - '0');
	}

	int value;

	switch(rank)
	{
		case 'T' : value = 10; break;
		case 'J' : value = 11; break;
		case 'Q' : value = 12; break;
		case 'K' : value = 13; break;
		case 'A' : value = 14; break;
		default : std::cout << "Something broke!\n"; break;
	}

	return value;
}
