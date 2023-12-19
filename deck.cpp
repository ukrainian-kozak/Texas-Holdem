#include "deck.h"


namespace gm
{


Deck::Deck() :
    CardContainer()
{
    m_vecCards.reserve(DECK_LENGTH);

    for (qsizetype i = 0; i < Card::SUIT_LENGTH; ++i) {
        for (qsizetype j = 0; j < Card::RANK_LENGTH; ++j) {
            m_vecCards.push_back(Card(static_cast<Card::Rank>(i + 1), static_cast<Card::Suit>(j + 1)));
        }
    }
}

Card Deck::getCard() const
{
    return m_vecCards.back();
}

QVector<Card> Deck::getCards(qsizetype count) const
{
    if (count > 0 && count < m_vecCards.size()) {
        return QVector<Card>(m_vecCards.end() - count, m_vecCards.end());
    }
}

void Deck::shuffle()
{
    std::random_device rd;
    std::mt19937 m(rd());

    std::shuffle(m_vecCards.begin(), m_vecCards.end(), m);
}



}
