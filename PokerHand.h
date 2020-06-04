#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <map>

namespace poker {


	class PokerHand {

		struct PokerCard
		{
			PokerCard( std::string card)
			{
				rank = card.at(0);
				suit = card.at(1);
			}

			~PokerCard() {}

			bool operator==( const PokerCard& c1) const
			{
				return this->getRank() == c1.getRank() && this->getSuit() == c1.getSuit() ;
			}

			int getValueOfRank() const;
			int getRank() const { return rank; }
			int getSuit() const { return suit; }

		private:
			// from 2 to 14
			char rank;
			// from 1 to 4
			char suit;
		};


	public:
		// all the results from the comparison
		enum class Comparison : char {
			TIE = 0,
			WIN = 1,
			LOSS = 2
		};

		// all combinations possible for a hand
		enum class Combination
		{	
			HighCard = 0, 
			OnePair = 1, 
			TwoPair = 2, 
			ThreeOfKind = 3, 
			Straight = 4, 
			Flush = 5, 
			FullHouse = 6, 
			FourOfKind = 7,
			StraightFlush = 8
		};

		// constructor
		PokerHand(std::string_view hand);
		// destructor
		~PokerHand() {}

		// functions
		Comparison compareWith(const PokerHand& opponent);
		int getHighestCardOfCombinationValue() const;

		inline int getHighestCard() const 			{ return m_cards.rbegin()->getRank();}
		inline int getHighestCardValue() const			{ return m_cards.rbegin()->getValueOfRank();}
		inline std::vector<PokerCard> const getHand() const	{ return m_cards;}
		inline bool haveCombinations() const 			{ return m_haveCombination;}

	private:
		std::string hand;
		// no point in storing as pointers in the vec for this task
		std::vector<PokerCard> m_cards;
		std::map<char,int> m_countOfRanks;

		// keep track of all possible combinations
		bool m_straightFlush;
		bool m_fourOfKind;
		bool m_fullHouse;
		bool m_flush;
		bool m_straight;
		bool m_threeOfKind;
		bool m_twoPair;
		bool m_onePair;
		bool m_highCard;

		bool m_haveCombination;

		// check all combinations and init their values to the correct ones
		void initCombinations();

		// helper functions
		void parseHand();
		Combination getHighestCombination() const;
		Comparison checkForResultForNonCombinationCards(const PokerHand& opponent);
	};
}

