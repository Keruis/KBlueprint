#include "ChatMessageBubble.h"
#include "Markdown.h"
#include <QPainter>
#include <QFontMetrics>
#include <QStyleOption>

ChatBubble::ChatBubble(const QString& message, bool fromSelf, QWidget* parent)
        : QWidget(parent), m_message(message), m_fromSelf(fromSelf) {
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    setAttribute(Qt::WA_TranslucentBackground);
}

QSize ChatBubble::sizeHint() const {
    QFontMetrics fm(font());
    const int fullCharWidth = fm.horizontalAdvance("你");
    const int padding = 24;
    const double maxUnitsPerLine = 20.0;
    const int spacingBetweenSegments = 6;

    auto segments = parseMarkdownSegments(m_message);
    qDebug() << "共分段:" << segments.size();
    for (int i = 0; i < segments.size(); ++i) {
        qDebug() << QString("段 %1 (%2):").arg(i).arg(segments[i].type == SegmentType::Markdown ? "Markdown" : "PlainText");
        qDebug() << segments[i].content;
    }
    double units = 0;
    for (QChar ch : m_message) {
        units += (ch.unicode() < 128) ? 0.5 : 1.0;
    }

    int textWidth = (units <= maxUnitsPerLine) ?
                    static_cast<int>(units * fullCharWidth) :
                    static_cast<int>(maxUnitsPerLine * fullCharWidth);

    double totalHeight = 0;
    double maxWidth = 0;

    for (const auto& seg : segments) {
        QTextDocument doc;
        doc.setDefaultFont(font());
        QTextOption opt;
        opt.setWrapMode(QTextOption::WordWrap);
        doc.setDefaultTextOption(opt);

        if (seg.type == SegmentType::Markdown) {
            doc.setMarkdown(seg.content);
        } else {
            QString htmlText = seg.content.toHtmlEscaped();
            QRegularExpression urlRegex(R"((https?://[^\s]+))");
            htmlText.replace(urlRegex, R"(<a href="\1" style="color:#3399ff;">\1</a>)");
            doc.setHtml(htmlText);
        }

        doc.setTextWidth(textWidth);
        QSizeF size = doc.size();
        totalHeight += size.height() + spacingBetweenSegments;
        maxWidth = std::max(maxWidth, size.width());
    }

    return QSize(static_cast<int>(maxWidth) + padding,
                 static_cast<int>(totalHeight) + 12);
}

void ChatBubble::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QFontMetrics fm(font());
    const int fullCharWidth = fm.horizontalAdvance("你");
    const double maxUnitsPerLine = 20.0;
    const int bubblePaddingH = 10;
    const int bubblePaddingV = 4;
    const int spacingBetweenSegments = 6;

    double units = 0;
    for (QChar ch : m_message) {
        units += (ch.unicode() < 128) ? 0.5 : 1.0;
    }

    int textWidth = (units <= maxUnitsPerLine) ?
                    static_cast<int>(units * fullCharWidth) :
                    static_cast<int>(maxUnitsPerLine * fullCharWidth);

    auto segments = parseMarkdownSegments(m_message);
    QVector<QTextDocument*> docs;
    double totalHeight = 0;
    double maxWidth = 0;

    for (const auto& seg : segments) {
        auto* doc = new QTextDocument;
        doc->setDefaultFont(font());
        QTextOption opt;
        opt.setWrapMode(QTextOption::WordWrap);
        doc->setDefaultTextOption(opt);

        if (seg.type == SegmentType::Markdown) {
            doc->setMarkdown(seg.content);
        } else {
            QString htmlText = seg.content.toHtmlEscaped();
            QRegularExpression urlRegex(R"((https?://[^\s]+))");
            htmlText.replace(urlRegex, R"(<a href="\1" style="color:#3399ff;">\1</a>)");
            doc->setHtml(htmlText);
        }

        doc->setTextWidth(textWidth);
        QSizeF size = doc->size();
        totalHeight += size.height() + spacingBetweenSegments;
        maxWidth = std::max(maxWidth, size.width());
        docs.append(doc);
    }

    int bubbleWidth = static_cast<int>(maxWidth) + bubblePaddingH * 2;
    int bubbleHeight = static_cast<int>(totalHeight) + bubblePaddingV * 2;

    QRect bubbleRect = m_fromSelf
                       ? QRect(width() - bubbleWidth - 4, 4, bubbleWidth, bubbleHeight)
                       : QRect(4, 4, bubbleWidth, bubbleHeight);

    QColor bgColor = m_fromSelf ? QColor("#0078D7") : QColor("#3a3a3a");
    painter.setBrush(bgColor);
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(bubbleRect, 10, 10);

    painter.save();
    painter.translate(bubbleRect.left() + bubblePaddingH, bubbleRect.top() + bubblePaddingV);

    for (auto* doc : docs) {
        doc->drawContents(&painter);
        painter.translate(0, doc->size().height() + spacingBetweenSegments);
    }

    painter.restore();

    qDeleteAll(docs);
}

void ChatBubble::mouseReleaseEvent(QMouseEvent* event) {
    int bubblePaddingH = 10;
    int bubblePaddingV = 4;

    QFontMetrics fm(font());
    const int fullCharWidth = fm.horizontalAdvance("你");
    const double maxUnitsPerLine = 20.0;
    double units = 0;
    for (QChar ch : m_message) {
        units += (ch.unicode() < 128) ? 0.5 : 1.0;
    }
    int textWidth = (units <= maxUnitsPerLine) ? static_cast<int>(units * fullCharWidth)
                                               : static_cast<int>(maxUnitsPerLine * fullCharWidth);
    m_cachedDoc.setTextWidth(textWidth);
    QSizeF docSize = m_cachedDoc.size();

    int bubbleWidth = static_cast<int>(docSize.width()) + bubblePaddingH * 2;
    int bubbleHeight = static_cast<int>(docSize.height()) + bubblePaddingV * 2;

    QRect bubbleRect = m_fromSelf
                       ? QRect(width() - bubbleWidth - 4, 4, bubbleWidth, bubbleHeight)
                       : QRect(4, 4, bubbleWidth, bubbleHeight);

    QPointF docPoint = event->pos() - QPointF(bubbleRect.topLeft()) - QPointF(bubblePaddingH, bubblePaddingV);
    QString anchor = m_cachedDoc.documentLayout()->anchorAt(docPoint);
    if (!anchor.isEmpty()) {
        QDesktopServices::openUrl(QUrl(anchor));
    }
}