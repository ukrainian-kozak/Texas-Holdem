#include "pokerhand.h"

namespace gm
{

PokerHand::PokerHand(const QVector<Card>& cards) :
    PokerHand(cards, {})
{
}

PokerHand::PokerHand(const QVector<Card>& holeCards, const QVector<Card>& communityCards) :
    CardContainer(communityCards),
    m_eHandStrength(HandStrength::UndefinedHand),
    m_nKicker(0),
    m_arrRankTotal({})
{
    addCards(holeCards);
    sort();
    initializeRankTotal();
    classifyHand();
}

PokerHand::HandStrength PokerHand::getHandStrength() const
{
    return m_eHandStrength;
}

void PokerHand::classifyHand()
{
    if ((m_nKicker = findRoyalFlush())) {
        m_eHandStrength = HandStrength::RoyalFlush;
    }
    else if ((m_nKicker = findStraightFlush())) {
        m_eHandStrength = HandStrength::StraightFlush;
    }
    else if ((m_nKicker = findPoker())) {
        m_eHandStrength = HandStrength::Poker;
        m_nKicker *= 100 + findHighCard(1);
    }
    else if ((m_nKicker = findFullHouse())) {
        m_eHandStrength = HandStrength::FullHouse;
        m_nKicker *= 100 + findPair();
    }
    else if ((m_nKicker = findFlush())) {
        m_eHandStrength = HandStrength::Flush;
    }
    else if ((m_nKicker = findStraight())) {
        m_eHandStrength = HandStrength::Straight;
    }
    else if ((m_nKicker = findThreeOfkind())) {
        m_eHandStrength = HandStrength::ThreeOfKind;
        m_nKicker *= 1000 + findHighCard(1) * 100 + findHighCard(2) * 10;
    }
    else if ((m_nKicker = findTwoPair())) {
        m_eHandStrength = HandStrength::TwoPairs;
        m_nKicker *= 100 + findHighCard(1) * 10;
    }
    else if ((m_nKicker = findPair())) {
        m_eHandStrength = HandStrength::Pair;
        m_nKicker *= 1000 + findHighCard(1) * 100 + findHighCard(2) * 10 + findHighCard(3);
    }
    else if ((m_nKicker = findHighCard(5))) {
        m_eHandStrength = HandStrength::HighCard;
        m_nKicker += findHighCard(1) * 10000 + findHighCard(2) + 1000 + findHighCard(3) * 100 + findHighCard(4) * 10;
    }
    else {
        m_eHandStrength = HandStrength::UndefinedHand;
    }
}

qsizetype PokerHand::findHighCard(qsizetype count)
{
    auto it = m_arrRankTotal.begin();

    for (qsizetype i = 0; i < count; ++i) {
        it = std::find(it, m_arrRankTotal.end(), 1);

        if (it == m_arrRankTotal.end())
            break;
        if (i == count - 1)
            return Card::RANK_LENGTH - std::distance(m_arrRankTotal.begin(), it);

        ++it;
    }

    return 0;
}

qsizetype PokerHand::findPair()
{
    return Card::RANK_LENGTH - std::distance(m_arrRankTotal.begin(), std::find(m_arrRankTotal.begin(), m_arrRankTotal.end(), 2));
}

qsizetype PokerHand::findTwoPair()
{
    if (std::count(m_arrRankTotal.begin(), m_arrRankTotal.end(), 2) > 1) {
        return Card::RANK_LENGTH - std::distance(m_arrRankTotal.begin(), std::find(m_arrRankTotal.begin(), std::next(m_arrRankTotal.begin(), Card::RANK_LENGTH - findPair() + 1), 2));
    }

    return 0;
}

qsizetype PokerHand::findThreeOfkind()
{
    return Card::RANK_LENGTH - std::distance(m_arrRankTotal.begin(), std::find(m_arrRankTotal.begin(), m_arrRankTotal.end(), 3));
}

qsizetype PokerHand::findStraight()
{
    for (qsizetype i = 0; i < Card::RANK_LENGTH - 5; ++i) {
        if (m_arrRankTotal[i] > 0 && m_arrRankTotal[i - 1] > 0
            && m_arrRankTotal[i - 2] > 0 && m_arrRankTotal[i - 3] > 0
            && m_arrRankTotal[i - 4] > 0) {
            return Card::RANK_LENGTH - i;
        }
    }

    if (m_arrRankTotal[0] > 0 && m_arrRankTotal[12] > 0
        && m_arrRankTotal[11] > 0 && m_arrRankTotal[10] > 0
        && m_arrRankTotal[9] > 0) {
        return 4;
    }

    return 0;
}

qsizetype PokerHand::findFlush()
{
    for (qsizetype i = 0; i < Card::SUIT_LENGTH; ++i) {
        if (std::count_if(m_vecCards.begin(), m_vecCards.end(),
             [&](const Card& card) { return card.getSuit() == static_cast<Card::Suit>(i + 1);}) >= 5) {
            return static_cast<qsizetype>(m_vecCards[std::distance(m_vecCards.begin(), std::find_if(m_vecCards.begin(), m_vecCards.end(),
                                                                                                    [&](const Card& card) { return card.getSuit() == static_cast<Card::Suit>(i + 1); }))].getRank());
        }
    }

    return 0;
}

qsizetype PokerHand::findFullHouse()
{
    return findPair() ? Card::RANK_LENGTH - findThreeOfkind() : 0;
}

qsizetype PokerHand::findPoker()
{
    return Card::RANK_LENGTH - std::distance(m_arrRankTotal.begin(), std::find(m_arrRankTotal.begin(), m_arrRankTotal.end(), 4));
}

qsizetype PokerHand::findStraightFlush()
{
    return findFlush() ? Card::RANK_LENGTH - findStraight() : 0;
}

qsizetype PokerHand::findRoyalFlush()
{
    return findStraightFlush() == 1 ? 1 : 0;
}

QString PokerHand::toString()
{
    QString res;

    switch (m_eHandStrength) {
    case HandStrength::HighCard:
        res = " High Card " + rankToString(static_cast<Card::Rank>(findHighCard(1)));
        break;
    case HandStrength::Pair:
        res = "Pair of " + rankToString(static_cast<Card::Rank>(findPair()));
        break;
    case HandStrength::TwoPairs:
        res = "Two Pairs of " + rankToString(static_cast<Card::Rank>(findTwoPair()));
        break;
    case HandStrength::ThreeOfKind:
        res = "Set of " + rankToString(static_cast<Card::Rank>(findThreeOfkind()));
        break;
    case HandStrength::Straight:
        res = "Straight of " + rankToString(static_cast<Card::Rank>(findStraight()));
        break;
    case HandStrength::Flush:
        res = "Flush";
        break;
    case HandStrength::FullHouse:
        res = "Full House of " + rankToString(static_cast<Card::Rank>(findThreeOfkind()));
        break;
    case HandStrength::Poker:
        res = "Poker of " + rankToString(static_cast<Card::Rank>(findPoker()));
        break;
    case HandStrength::StraightFlush:
        res = "Straight Flush";
        break;
    case HandStrength::RoyalFlush:
        res = "Royal Flush";
        break;
    default:
        res = "Undefined Hand";
        break;
    }

    return res;
}

QString PokerHand::rankToString(Card::Rank rank) const
{
    QString res;

    switch (rank) {
    case Card::Rank::TWO:
        res = "Two";
        break;
    case Card::Rank::THREE:
        res = "Three";
        break;
    case Card::Rank::FOUR:
        res = "Four";
        break;
    case Card::Rank::FIVE:
        res = "Five";
        break;
    case Card::Rank::SIX:
        res = "Six";
        break;
    case Card::Rank::SEVEN:
        res = "Seven";
        break;
    case Card::Rank::EIGHT:
        res = "Eight";
        break;
    case Card::Rank::NINE:
        res = "Nine";
        break;
    case Card::Rank::TEN:
        res = "Ten";
        break;
    case Card::Rank::JACK:
        res = "Jack";
        break;
    case Card::Rank::QUEEN:
        res = "Queen";
        break;
    case Card::Rank::KING:
        res = "King";
        break;
    case Card::Rank::ACE:
        res = "Ace";
        break;
    default:
        res = "Undefined Rank";
        break;
    }

    return res;
}

bool PokerHand::operator==(const PokerHand& other) const
{
    return m_eHandStrength == other.m_eHandStrength && m_nKicker == other.m_nKicker;
}

bool PokerHand::operator!=(const PokerHand& other) const
{
    return !(*this == other);
}

bool PokerHand::operator<(const PokerHand& other) const
{
    return std::tie(m_eHandStrength, m_nKicker) < std::tie(other.m_eHandStrength, other.m_nKicker);
}

bool PokerHand::operator>(const PokerHand& other) const
{
    return other < *this;
}

bool PokerHand::operator<=(const PokerHand& other) const
{
    return !(*this > other);
}

bool PokerHand::operator>=(const PokerHand& other) const
{
    return !(*this < other);
}

void PokerHand::initializeRankTotal()
{
    std::size_t arrayIndex = 0;
    for (std::size_t i = m_arrRankTotal.size(); i > 0; --i, arrayIndex++) {
        m_arrRankTotal[arrayIndex] = std::count_if(m_vecCards.begin(), m_vecCards.end(),
                                              [&](const Card& card) { return card.getRank() == static_cast<Card::Rank>(i); });
    }
}

}
