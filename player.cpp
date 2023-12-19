#include "player.h"

namespace gm
{

Player::Player() :
    m_Hand(),
    m_Decision(Player::UndefinedDecision),
    m_nStack(0),
    m_nPotContribution(0),
    m_bActive(false)
{
}

Player::Player(qsizetype stack) :
    m_Hand(),
    m_Decision(Player::UndefinedDecision),
    m_nStack(stack),
    m_nPotContribution(0),
    m_bActive(true)
{
}

Player::Decision Player::getDecision() const
{
    return m_Decision;
}

void Player::throwOutCards()
{
    m_Hand.clear();
}

void Player::setDecision(Player::Decision decision)
{
    m_Decision = decision;
}

QVector<Card> Player::getCards() const
{
    return m_Hand.getCards();
}

void Player::setCards(const QVector<Card>& cards)
{
    m_Hand.setCards(cards);
}

void Player::setCard(const Card& card)
{
    m_Hand.addCard(card);
}

qsizetype Player::getStack() const
{
    return m_nStack;
}

void Player::setStack(qsizetype stack)
{
    m_nStack = stack;
}

void Player::addToStack(qsizetype chips)
{
    m_nStack += chips;
}





//==========Pot Functions begin===========================


qsizetype Player::getPotContribution() const
{
    return m_nPotContribution;
}

void Player::setPotContribution(qsizetype val)
{
    m_nPotContribution = val;
}

void Player::addToPotContribution(qsizetype value)
{
    m_nPotContribution += value;
    m_nStack -= value;
}

void Player::removeFromPotContribution(qsizetype val)
{
    val > m_nPotContribution ? m_nPotContribution = 0 : m_nPotContribution -= val;
}


//==========Pot Functions end===========================






bool Player::isActive() const
{
    return m_bActive;
}

}

