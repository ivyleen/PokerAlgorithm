## 1. Requirements

A poker hand has a constructor that accepts a `std::string_view` containing 
exactly 5 cards, for example: 

```cpp
  PokerHand hand("KS 2H 5C JD TD");
```

Further, a poker hand has a member function to compare itself to another hand:

```cpp
  PokerHand::Comparison PokerHand::compareWith(const PokerHand& opponent);
```

The characteristics of the string of cards are:

  * A space is used as card seperator
  * Each card consists of two characters
  * The first character is the value of the card, valid characters are: `2`,
    `3`, `4`, `5`, `6`, `7`, `8`, `9`, `T`(en), `J`(ack), `Q`(ueen), `K`(ing),
    `A`(ce)
  * The second character represents the suit, valid characters are: `S`(pades),
    `H`(earts), `D`(iamonds), `C`(lubs)

The result of your poker hand compare can be one of the 3 options:

  * `PokerHand::Comparison::TIE`
  * `PokerHand::Comparison::WIN`
  * `PokerHand::Comparison::LOSS`

The ranking of the hands should follow the [Texas Hold'em rules](https://en.wikipedia.org/wiki/List_of_poker_hands).

You can run with the following command:
g++ -std=c++17 -o poker PokerHand.cpp PokerHand_UnitTest.cpp
