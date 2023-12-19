#include "playerwidget.h"

PlayerWidget::PlayerWidget(const QString& name, QWidget* pwgt) :
    QWidget(pwgt),
    _name(std::make_unique<QLabel>(name)),
    _stack(std::make_unique<QLabel>("1000")),
    _potContribution(std::make_unique<QLabel>("0"))
{
    QVBoxLayout* pvbxLayout = new QVBoxLayout;
    pvbxLayout->addWidget(_potContribution.get());
    pvbxLayout->addWidget(_name.get());
    pvbxLayout->addWidget(_stack.get());
    setLayout(pvbxLayout);

    resize(50, 80);
}
