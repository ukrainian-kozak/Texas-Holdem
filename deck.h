#ifndef DECK_H
#define DECK_H

#include <QVector>
#include <random>
#include "cardcontainer.h"

namespace gm
{

class Deck final : public CardContainer
{
public:
    static const int DECK_LENGTH = 52;

    Deck();

public:
    Card getCard() const;
    QVector<Card> getCards(qsizetype) const;

    void shuffle();
};


}

#endif // DECK_H
