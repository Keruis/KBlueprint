#ifndef BLUEPRINT_CHATMESSAGEBUBBLE_H
#define BLUEPRINT_CHATMESSAGEBUBBLE_H


#include <QWidget>
#include <QString>

class ChatBubble : public QWidget {
    Q_OBJECT
public:
    explicit ChatBubble(const QString& message, bool fromSelf, QWidget* parent = nullptr);
    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    QString m_message;
    bool m_fromSelf;
    QRect m_textRect;
};

#endif //BLUEPRINT_CHATMESSAGEBUBBLE_H
