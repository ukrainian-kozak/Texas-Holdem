#ifndef POKERTABLE_H
#define POKERTABLE_H

#include "player.h"

namespace gm
{

class PokerTable
{
    friend class Dealer;

public:
    PokerTable();
    PokerTable(qsizetype, qsizetype, const QVector<Player>&);

    void changePositions();

    qsizetype getAnte() const;
    void setAnte(qsizetype);

    qsizetype getBigBlind() const;
    void setBigBlind(qsizetype);

    qsizetype getPot() const;
    void setPot(qsizetype);
    void addToPot(qsizetype);
    void clearPot();

    void passChipsFromPotToPlayer(qsizetype, qsizetype);

    void addPlayer(const Player&);

    void removePlayer(qsizetype);

    qsizetype activeCount() const;
    qsizetype allInCount() const;

private:
    qsizetype m_nPot;
    qsizetype m_nAnte;
    qsizetype m_nBigBlind;
    QVector<Player> m_vecPlayers;
};


}


#endif // POKERTABLE_H
