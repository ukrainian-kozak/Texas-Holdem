#include "card.h"

namespace gm
{

//==============Constructors begin================================


Card::Card() :
    _rank(Rank::UndefinedRank),
    _suit(Suit::UndefinedSuit)
{
}

Card::Card(Rank rank, Suit suit) :
    _rank(rank),
    _suit(suit)
{
}


//==============Constructors end================================


QString Card::toString() const
{
    QString res;

    switch (_rank) {
    case Rank::TWO:
        res += " 2_of_ ";
        break;
    case Rank::THREE:
        res += " 3_of_";
        break;
    case Rank::FOUR:
        res += " 4_of_";
        break;
    case Rank::FIVE:
        res += " 5_of_";
        break;
    case Rank::SIX:
        res += " 6_of_";
        break;
    case Rank::SEVEN:
        res += " 7_of_";
        break;
    case Rank::EIGHT:
        res += " 8_of_";
        break;
    case Rank::NINE:
        res += " 9_of_";
        break;
    case Rank::TEN:
        res += " 10_of_";
        break;
    case Rank::JACK:
        res += " jack_of_";
        break;
    case Rank::QUEEN:
        res += " queen_of_";
        break;
    case Rank::KING:
        res += " king_of_";
        break;
    case Rank::ACE:
        res += " ace_of_";
        break;
    default:
        res += " undefined_rank_of_";
        break;
    }

    switch (_suit) {
    case Suit::SPADES:
        res += "spades";
        break;
    case Suit::HEARTS:
        res += "hearts";
        break;
    case Suit::DIAMONDS:
        res += "diamonds";
        break;
    case Suit::CLUBS:
        res += "clubs";
        break;
    default:
        res += "undefined_suit";
        break;
    }

    return res;
}



//================Get/Set Functions begin=========================


Card::Rank Card::getRank() const
{
    return _rank;
}

Card::Suit Card::getSuit() const
{
    return _suit;
}

void Card::setRank(Card::Rank rank)
{
    _rank = rank;
}

void Card::setSuit(Card::Suit suit)
{
    _suit = suit;
}


//================Get/Set Functions end=========================





//===================Operator <=> begin==========================


bool Card::operator==(const Card& other) const
{
    return _rank == other._rank && _suit == other._suit;
}

bool Card::operator!=(const Card& other) const
{
    return !(*this == other);
}

bool Card::operator<(const Card& other) const
{
    return _rank < other._rank;
}

bool Card::operator>(const Card& other) const
{
    return other < *this;
}

bool Card::operator<=(const Card& other) const
{
    return !(other < *this);
}

bool Card::operator>=(const Card& other) const
{
    return !(*this < other);
}


//===================Operator <=> end==========================

}
























