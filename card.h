#ifndef CARD_H
#define CARD_H

#include <QtGlobal>
#include <QString>

#include "cardwidget.h"

namespace gm
{

class Card final
{
public:
    enum class Rank {
        UndefinedRank = 0,
        TWO,
        THREE,
        FOUR,
        FIVE,
        SIX,
        SEVEN,
        EIGHT,
        NINE,
        TEN,
        JACK,
        QUEEN,
        KING,
        ACE
    };

    enum class Suit {
        UndefinedSuit = 0,
        SPADES,
        HEARTS,
        DIAMONDS,
        CLUBS
    };

    static const qsizetype RANK_LENGTH = 13;
    static const qsizetype SUIT_LENGTH = 4;

public:
    Card();
    Card(Rank, Suit);

    Rank getRank() const;
    Suit getSuit() const;

    void setRank(Rank rank);
    void setSuit(Suit suit);

    QString toString() const;

    bool operator==(const Card&) const;
    bool operator!=(const Card&) const;
    bool operator<(const Card&) const;
    bool operator>(const Card&) const;
    bool operator<=(const Card&) const;
    bool operator>=(const Card&) const;

private:
    Rank _rank;
    Suit _suit;
};

}



#endif // CARD_H
