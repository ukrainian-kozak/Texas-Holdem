#ifndef POKERHAND_H
#define POKERHAND_H

#include "cardcontainer.h"
#include <QVarLengthArray>

namespace gm
{

class PokerHand final : public CardContainer
{
public:
    enum class HandStrength : quint8 {
        UndefinedHand = 0,
        HighCard,
        Pair,
        TwoPairs,
        ThreeOfKind,
        Straight,
        Flush,
        FullHouse,
        Poker,
        StraightFlush,
        RoyalFlush
    };

    PokerHand(const QVector<Card>&);
    PokerHand(const QVector<Card>&, const QVector<Card>&);

public:
    void classifyHand();

    HandStrength getHandStrength() const;

    qsizetype findHighCard(qsizetype);
    qsizetype findPair();
    qsizetype findTwoPair();
    qsizetype findThreeOfkind();
    qsizetype findStraight();
    qsizetype findFlush();
    qsizetype findFullHouse();
    qsizetype findPoker();
    qsizetype findStraightFlush();
    qsizetype findRoyalFlush();

    QString toString() override;
    QString rankToString(Card::Rank) const;


    bool operator==(const PokerHand&) const;
    bool operator!=(const PokerHand&) const;
    bool operator<(const PokerHand&) const;
    bool operator>(const PokerHand&) const;
    bool operator<=(const PokerHand&) const;
    bool operator>=(const PokerHand&) const;

private:
    HandStrength m_eHandStrength;
    qsizetype m_nKicker;
    QVarLengthArray<qsizetype, 13> m_arrRankTotal;

    void initializeRankTotal();
};


}


#endif // POKERHAND_H
