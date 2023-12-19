#include "pokertable.h"

namespace gm
{

PokerTable::PokerTable()
    : m_nPot(0),
    m_nAnte(0),
    m_nBigBlind(0)
{
    m_vecPlayers.reserve(9);
    for (qsizetype i = 0; i < 9; ++i) {
        m_vecPlayers.push_back(Player(1000));
    }
}

PokerTable::PokerTable(qsizetype ante, qsizetype bigBlind, const QVector<Player>& players)
    : m_nPot(0),
    m_nAnte(ante),
    m_nBigBlind(bigBlind),
    m_vecPlayers(players)
{
}

void PokerTable::changePositions()
{
    std::rotate(m_vecPlayers.rbegin(), m_vecPlayers.rbegin() + 1, m_vecPlayers.rend());
}

qsizetype PokerTable::getAnte() const
{
    return m_nAnte;
}

void PokerTable::setAnte(qsizetype ante)
{
    m_nAnte = ante;
}

qsizetype PokerTable::getBigBlind() const
{
    return m_nBigBlind;
}

void PokerTable::setBigBlind(qsizetype val)
{
    m_nBigBlind = val;
}

qsizetype PokerTable::getPot() const
{
    return m_nPot;
}

void PokerTable::setPot(qsizetype val)
{
    m_nPot = val;
}

void PokerTable::addToPot(qsizetype val)
{
    m_nPot += val;
}

void PokerTable::clearPot()
{
    m_nPot = 0;
}

void PokerTable::passChipsFromPotToPlayer(qsizetype pos, qsizetype chips)
{
    m_vecPlayers[pos].addToStack(chips);
}

void PokerTable::addPlayer(const Player& player)
{
    m_vecPlayers.push_back(player);
}

void PokerTable::removePlayer(qsizetype pos)
{
    m_vecPlayers.remove(pos);
}

qsizetype PokerTable::activeCount() const
{
    return std::count_if(m_vecPlayers.begin(), m_vecPlayers.end(),
                                  [&](const Player& player) { return player.isActive(); });
}

qsizetype PokerTable::allInCount() const
{
    return std::count_if(m_vecPlayers.begin(), m_vecPlayers.end(),
                         [&](const Player& player) { return player.getStack() == 0;});
}


}

