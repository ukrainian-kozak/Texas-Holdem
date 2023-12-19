#ifndef DEALER_H
#define DEALER_H

#include "deck.h"
#include "pokertable.h"
#include <QObject>

namespace gm
{

class Dealer : public QObject
{
    Q_OBJECT
public:
    enum Street { UndefinedStreet, Preflop, Flop, Turn, River };

    Dealer();
    Dealer(qsizetype, qsizetype, const QVector<Player>&);

public:
    QVector<Card> getCards() const;

    void startHand();
    void dealPreflop();
    void dealFlop();
    void dealTurn();
    void dealRiver();
    void endHand();

#if 1
    //public slots:
    void makeFold(qsizetype);
    void makeCall(qsizetype);
    void makeBet(qsizetype, qsizetype);
#endif

signals:
    void antePosted(qsizetype);
    //void blindsPosted();

private:
    Deck m_Deck;
    PokerTable m_PokerTable;
    CardContainer m_vecCommunityCards;
    CardContainer m_vecMuckedCards;
    Street m_Street = UndefinedStreet;
    qsizetype m_nCurrPosition = 0;
    qsizetype m_nActionCount = 0;

    void updateGameStage();

    void changePositions();
    void moveCurrentPosition();

    void postBlinds();
    void postAnte();

    void passPotToWinner();
    void passChipsToPot();
    void passCardsToDeck();

    qsizetype minContribution();
    qsizetype maxContribution();

    QVector< PokerHand> classifyRanks();
};

}


#endif // DEALER_H
