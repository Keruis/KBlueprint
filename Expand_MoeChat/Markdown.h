#ifndef BLUEPRINT_MARKDOWN_H
#define BLUEPRINT_MARKDOWN_H

#include <QVector>
#include <QList>
#include <QString>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

enum class SegmentType {
    PlainText,
    Markdown
};

struct TextSegment {
    QString content;
    SegmentType type;
};

QVector<TextSegment> parseMarkdownSegments(const QString& raw) {
    QVector<TextSegment> segments;

    QRegularExpression re(R"([（(]keruis[）)]\[markdown\]\{([\s\S]*?)\})", QRegularExpression::CaseInsensitiveOption);
    int lastPos = 0;

    auto it = re.globalMatch(raw);
    while (it.hasNext()) {
        QRegularExpressionMatch match = it.next();

        int start = match.capturedStart();
        int end = match.capturedEnd();

        if (start > lastPos) {
            segments.append({
                raw.mid(lastPos, start - lastPos).trimmed(),
                SegmentType::PlainText
            });
        }

        QString markdown = match.captured(1).trimmed();
        segments.append({ markdown, SegmentType::Markdown });

        lastPos = end;
    }

    if (lastPos < raw.length()) {
        segments.append({
            raw.mid(lastPos).trimmed(),
            SegmentType::PlainText
        });
    }

    return segments;
}

#endif //BLUEPRINT_MARKDOWN_H
