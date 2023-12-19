#ifndef CARDCONTAINER_H
#define CARDCONTAINER_H


#include "card.h"
#include <QVector>
#include <QLabel>

namespace gm
{

class CardInterface {
public:
    virtual QString toString() = 0;

    virtual ~CardInterface() = 0;
};

class CardContainer : public CardInterface
{
public:
    CardContainer();
    CardContainer(const QVector<Card>&);

    QVector<Card> getCards() const;

    void setCards(const QVector<Card>&);

    void addCard(const Card&);
    void addCards(const QVector<Card>&);

    void removeCard();
    void removeCards(qsizetype);

    void sort();

    void clear();

    qsizetype size() const;
    bool empty() const;

    QString toString() override;

protected:
    QVector<Card> m_vecCards;

};



}



#endif // CARDCONTAINER_H
