#include "ChatMessageBubble.h"
#include <QPainter>
#include <QTextDocument>
#include <QFontMetrics>
#include <QStyleOption>

ChatBubble::ChatBubble(const QString& message, bool fromSelf, QWidget* parent)
        : QWidget(parent), m_message(message), m_fromSelf(fromSelf) {
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    setAttribute(Qt::WA_TranslucentBackground);
}

QSize ChatBubble::sizeHint() const {
    QFontMetrics fm(font());
    QTextDocument doc;
    doc.setDefaultFont(font());

    QString wrappedMessage = QString("<div style='white-space: pre-wrap; word-break: break-all;'>%1</div>")
            .arg(m_message.toHtmlEscaped());
    doc.setHtml(wrappedMessage);

    const int fullCharWidth = fm.horizontalAdvance("你");
    const int padding = 24;
    const double maxUnitsPerLine = 20.0;

    double units = 0;
    for (QChar ch : m_message) {
        units += (ch.unicode() < 128) ? 0.5 : 1.0;
    }

    int textWidth;
    if (units <= maxUnitsPerLine) {
        textWidth = static_cast<int>(units * fullCharWidth);
    } else {
        textWidth = static_cast<int>(maxUnitsPerLine * fullCharWidth);
    }

    doc.setTextWidth(textWidth);
    QSizeF docSize = doc.size();

    return QSize(static_cast<int>(docSize.width()) + padding,
                 static_cast<int>(docSize.height()) + 16);
}

void ChatBubble::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QFontMetrics fm(font());
    QTextDocument doc;
    doc.setDefaultFont(font());

    QString wrappedMessage = QString("<div style='white-space: pre-wrap; word-break: break-all;'>%1</div>")
            .arg(m_message.toHtmlEscaped());
    doc.setHtml(wrappedMessage);

    const int fullCharWidth = fm.horizontalAdvance("你");
    const int padding = 24;
    const double maxUnitsPerLine = 20.0;

    double units = 0;
    for (QChar ch : m_message) {
        units += (ch.unicode() < 128) ? 0.5 : 1.0;
    }

    int textWidth;
    if (units <= maxUnitsPerLine) {
        textWidth = static_cast<int>(units * fullCharWidth);
    } else {
        textWidth = static_cast<int>(maxUnitsPerLine * fullCharWidth);
    }

    doc.setTextWidth(textWidth);
    QSizeF docSize = doc.size();

    int bubblePaddingH = 10;
    int bubblePaddingV = 6;

    int bubbleWidth = static_cast<int>(docSize.width()) + bubblePaddingH * 2;
    int bubbleHeight = static_cast<int>(docSize.height()) + bubblePaddingV * 2;

    QRect bubbleRect;
    if (m_fromSelf)
        bubbleRect = QRect(width() - bubbleWidth - 4, 4, bubbleWidth, bubbleHeight);
    else
        bubbleRect = QRect(4, 4, bubbleWidth, bubbleHeight);

    QColor bgColor = m_fromSelf ? QColor("#0078D7") : QColor("#3a3a3a");
    painter.setBrush(bgColor);
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(bubbleRect, 10, 10);

    painter.translate(bubbleRect.left() + bubblePaddingH, bubbleRect.top() + bubblePaddingV);
    doc.drawContents(&painter);
}