#include "cardcontainer.h"

namespace gm
{

//==============Constructors begin================================


CardContainer::CardContainer()
{
}

CardContainer::CardContainer(const QVector<Card>& cards) :
    m_vecCards(cards)
{
}


CardInterface::~CardInterface()
{
}

//==============Constructors end================================






//==============Get/Set functions begin================================


QVector<Card> CardContainer::getCards() const
{
    return m_vecCards;
}

void CardContainer::setCards(const QVector<Card>& cards)
{
    m_vecCards = cards;
}


//==============Get/Set functions end================================





//==============Add/Remove functions begin================================


void CardContainer::addCard(const Card& card)
{
    m_vecCards.push_back(card);
}

void CardContainer::addCards(const QVector<Card>& cards)
{
    m_vecCards += cards;
}

void CardContainer::removeCard()
{
    m_vecCards.pop_back();
}

void CardContainer::removeCards(qsizetype count)
{
    m_vecCards.erase(m_vecCards.end() - count, m_vecCards.end());
}


//==============Get/Set functions end================================





//==============Sort Function begin================================


void CardContainer::sort()
{
    std::sort(m_vecCards.rbegin(), m_vecCards.rend());
}


//==============Sort Function end================================





//==============Cler/Size/Empty Functions begin================================


void CardContainer::clear()
{
    m_vecCards.clear();
}

qsizetype CardContainer::size() const
{
    return m_vecCards.size();
}

bool CardContainer::empty() const
{
    return m_vecCards.empty();
}


//==============Cler/Size/Empty Functions end================================






//==============To String Function begin================================

QString CardContainer::toString()
{
    return m_vecCards.size() > 2 ? "" : m_vecCards[0].toString() + " and " + m_vecCards[1].toString();
}


//==============To String Function end================================
}

