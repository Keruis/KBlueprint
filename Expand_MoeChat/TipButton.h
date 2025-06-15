#ifndef BLUEPRINT_TIPBUTTON_H
#define BLUEPRINT_TIPBUTTON_H

#include <QToolTip>
#include <QHelpEvent>
#include <QPushButton>

class TipButton : public QPushButton {
    Q_OBJECT
public:
    explicit TipButton(const QString& text, const QString& tip, QWidget* parent = nullptr)
            : QPushButton(text, parent), m_tip(tip) {}

protected:
    bool event(QEvent* event) override ;

private:
    QString m_tip;
};


#endif //BLUEPRINT_TIPBUTTON_H
