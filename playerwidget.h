#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include <QLabel>
#include <QVBoxLayout>
#include <QHboxLayout>

class PlayerWidget : public QWidget
{
    Q_OBJECT
public:
    PlayerWidget(const QString&, QWidget* pwgt = nullptr);

private:
    std::unique_ptr<QLabel> _name;
    std::unique_ptr<QLabel> _stack;
    std::unique_ptr<QLabel> _potContribution;
};

#endif // PLAYERWIDGET_H
