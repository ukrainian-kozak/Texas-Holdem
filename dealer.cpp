#include "dealer.h"

namespace gm
{


//===================Constructors start============================

Dealer::Dealer()
{
}

Dealer::Dealer(qsizetype ante, qsizetype blind, const QVector<Player>& players) :
    m_Deck({}),
    m_PokerTable(ante, blind, players),
    m_Street(Dealer::UndefinedStreet),
    m_nCurrPosition(0),
    m_nActionCount(0)
{
}


//===================Constructors end============================







//==============Get/Set functions start===================================

QVector<Card> Dealer::getCards() const
{
    return m_vecCommunityCards.getCards();
}


//==============Get/Set functions end===================================






//==========Start/End Hand functions start===========================

void Dealer::startHand()
{
    for (auto& player : m_PokerTable.m_vecPlayers)
        player.setDecision(Player::UndefinedDecision);

    m_Deck.shuffle();
    postAnte();
    postBlinds();
    updateGameStage();
}

void Dealer::endHand()
{
    passPotToWinner();
    m_PokerTable.clearPot();
    passCardsToDeck();

    m_PokerTable.m_vecPlayers.erase(std::remove_if(m_PokerTable.m_vecPlayers.begin(), m_PokerTable.m_vecPlayers.end(),
                              [&] (const Player& player) { return player.getStack() == 0; }), m_PokerTable.m_vecPlayers.end());
}

void Dealer::passCardsToDeck()
{
    m_Deck.addCards(m_vecMuckedCards.getCards());
    m_Deck.addCards(m_vecCommunityCards.getCards());
    m_vecCommunityCards.clear();
    m_vecMuckedCards.clear();
}


//==========Start/End Hand functions end===========================






//===========Deal preflop, flop, turn, river functions start========================


void Dealer::dealPreflop()
{
    for (auto & player : m_PokerTable.m_vecPlayers) {
        player.setCards(m_Deck.getCards(2));
        m_Deck.removeCards(2);
    }
}

void Dealer::dealFlop()
{
    m_vecCommunityCards.addCards(m_Deck.getCards(3));
    m_Deck.removeCards(3);
}

void Dealer::dealTurn()
{
    m_vecCommunityCards.addCard(m_Deck.getCard());
    m_Deck.removeCard();
}

void Dealer::dealRiver()
{
    m_vecCommunityCards.addCard(m_Deck.getCard());
    m_Deck.removeCard();
}


//===========Deal preflop, flop, turn, river functions end========================



//========Action functions start======================================


#if 1
void Dealer::makeFold(qsizetype pos)
{
    m_vecMuckedCards.addCards(m_PokerTable.m_vecPlayers[pos].getCards());
    m_PokerTable.m_vecPlayers[pos].setDecision(Player::Decision::Fold);
    m_PokerTable.m_vecPlayers[pos].throwOutCards();
}

void Dealer::makeCall(qsizetype pos)
{
    m_PokerTable.m_vecPlayers[pos].setDecision(Player::Decision::Call);
    m_PokerTable.m_vecPlayers[pos].addToPotContribution(maxContribution() - m_PokerTable.m_vecPlayers[pos].getPotContribution());
}

void Dealer::makeBet(qsizetype pos, qsizetype val)
{
    m_PokerTable.m_vecPlayers[pos].setDecision(Player::Decision::Bet);
    m_PokerTable.m_vecPlayers[pos].addToPotContribution(val);
}
#endif



//========Action functions end======================================


//=========Update Game Stage Functions start============================


void Dealer::updateGameStage()
{

    switch (m_Street) {
    case UndefinedStreet:
        m_nCurrPosition = m_PokerTable.m_vecPlayers.size() > 2 ? 2 : 0;
        m_Street = Street::Preflop;
        dealPreflop();
        moveCurrentPosition();
        break;
    case Preflop:
        dealFlop();
        m_Street = Street::Flop;
        moveCurrentPosition();
        break;
    case Flop:
        dealTurn();
        m_Street = Street::Turn;
        moveCurrentPosition();
        break;
    case Turn:
        dealRiver();
        m_Street = Street::River;
        moveCurrentPosition();
        break;
    case River:
        endHand();
        m_Street = Street::UndefinedStreet;
        startHand();
        break;
    }
}


//=========Update Game Stage Functions start============================








//=============Post ante and blinds functions start===============================

void Dealer::postAnte()
{
    for (auto& player : m_PokerTable.m_vecPlayers) {
        player.setPotContribution(m_PokerTable.getAnte());
    }
    m_PokerTable.setPot(m_PokerTable.getAnte() * m_PokerTable.m_vecPlayers.size());
    emit antePosted(m_PokerTable.getPot());
}


void Dealer::postBlinds()
{
    m_PokerTable.m_vecPlayers[0].setPotContribution(m_PokerTable.getBigBlind() / 2);
    m_PokerTable.m_vecPlayers[1].setPotContribution(m_PokerTable.getBigBlind());
    m_PokerTable.setPot(m_PokerTable.getPot() + m_PokerTable.getBigBlind() / 2 + m_PokerTable.getBigBlind());
    //emit blindsPosted();
}



//=============Post ante and blinds functions end===============================







//============payout functions start=========================================


void Dealer::passPotToWinner()
{
    qsizetype activePlayers = std::count_if(m_PokerTable.m_vecPlayers.begin(),
                                            m_PokerTable.m_vecPlayers.end(),
                                            [&] (const Player& player) { return player.getPotContribution() > 0; } );

    if (activePlayers == 1) {
        qsizetype pos = std::distance(m_PokerTable.m_vecPlayers.begin(),
                                      std::find_if(m_PokerTable.m_vecPlayers.begin(),
                                      m_PokerTable.m_vecPlayers.end(),
                                      [&](const Player& player) {return player.isActive();}));

        m_PokerTable.m_vecPlayers[pos].addToStack(m_PokerTable.getPot());
    }
    else {
        auto ranks = classifyRanks();

        while (activePlayers > 1) {
            qsizetype contribution = minContribution();

            for (auto& player : m_PokerTable.m_vecPlayers)
                player.removeFromPotContribution(contribution);

            qsizetype payout = contribution * activePlayers + m_PokerTable.getPot();

            qsizetype winners = std::count_if(m_PokerTable.m_vecPlayers.begin(), m_PokerTable.m_vecPlayers.end(),
                                                       [&](const Player& player) { return PokerHand(player.getCards(), getCards()) == ranks.back();});

            for (auto& player : m_PokerTable.m_vecPlayers) {
                if (player.isActive() && PokerHand(player.getCards(), getCards()) == ranks.back()) {
                    player.addToStack(payout / winners);
                }
            }

            for (qsizetype i = 0; i <m_PokerTable.m_vecPlayers.size(); ++i) {
                if (m_PokerTable.m_vecPlayers[i].isActive() && m_PokerTable.m_vecPlayers[i].getPotContribution() == 0) {
                    makeFold(i);
                }
            }

            ranks.erase(ranks.end() - winners, ranks.end());

            activePlayers = std::count_if(m_PokerTable.m_vecPlayers.begin(), m_PokerTable.m_vecPlayers.end(),
                                          [&](const Player& player) { return player.getPotContribution() > 0;});
        }
    }
}

QVector<PokerHand> Dealer::classifyRanks()
{
    QVector<PokerHand> ranks;

    for (const auto& player : m_PokerTable.m_vecPlayers) {
        if (player.isActive())
            ranks.push_back(PokerHand(player.getCards(), getCards()));
    }

    std::sort(ranks.begin(), ranks.end());

    return ranks;
}

void Dealer::passChipsToPot()
{
    qsizetype sum = 0;

    for (auto& player : m_PokerTable.m_vecPlayers) {
        sum += player.getPotContribution();
        player.setPotContribution(0);
    }

    m_PokerTable.addToPot(sum);
}


//============payout functions end=========================================








//============Min/Max Contribution functions start===========================


qsizetype Dealer::minContribution()
{
    qsizetype val = LONG_LONG_MAX;

    for (const auto& player : m_PokerTable.m_vecPlayers)
        if (player.isActive())
            val = std::min(val, player.getPotContribution());

    return val;
}

qsizetype Dealer::maxContribution()
{
    qsizetype val = 0;

    for (const auto& player : m_PokerTable.m_vecPlayers)
        if (player.isActive())
            val = std::max(val, player.getPotContribution());

    return val;
}


//============Min/Max Contribution functions end===========================







//============Move position function start====================================


void Dealer::changePositions()
{
    m_PokerTable.changePositions();
}

void Dealer::moveCurrentPosition()
{
    for (qsizetype i = m_nCurrPosition + 1; i != m_nCurrPosition; ++i) {
        if (i == m_PokerTable.m_vecPlayers.size())
            i = 0;
        if (m_PokerTable.m_vecPlayers[i].isActive() && m_PokerTable.m_vecPlayers[i].getStack() > 0) {
            m_nCurrPosition = i;
            break;
        }
    }
}


//============Move position function end====================================
}

