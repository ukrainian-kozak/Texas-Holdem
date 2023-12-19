#ifndef PLAYER_H
#define PLAYER_H

#include "pokerhand.h"

namespace gm {

class Player {
public:
    enum Decision { UndefinedDecision = 0, Fold, Call, Bet };

    Player();
    Player(qsizetype);

public:
    Decision getDecision() const;
    void setDecision(Decision);

    QVector<Card> getCards() const;
    void setCards(const QVector<Card>&);
    void setCard(const Card&);

    qsizetype getStack() const;
    void setStack(qsizetype);
    void addToStack(qsizetype);

    qsizetype getPotContribution() const;
    void setPotContribution(qsizetype);
    void addToPotContribution(qsizetype);
    void removeFromPotContribution(qsizetype);

    void throwOutCards();

    bool isActive() const;


private:
    CardContainer m_Hand;
    Decision m_Decision;

    qsizetype m_nStack;
    qsizetype m_nPotContribution;

    bool m_bActive;
};




}



#endif // PLAYER_H
