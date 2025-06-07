#ifndef BLUEPRINT_PLACEHOLDERPAGE_H
#define BLUEPRINT_PLACEHOLDERPAGE_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QFont>
#include <QPalette>

class PlaceholderPage : public QWidget {
public:
    explicit PlaceholderPage(QWidget* parent = nullptr) : QWidget(parent) {
        setMinimumWidth(600);
        setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);

        auto* layout = new QVBoxLayout(this);
        layout->setContentsMargins(0, 0, 0, 0);

        auto* label = new QLabel("未选择任何页面", this);

        QFont font("Segoe UI", 20, QFont::Medium);
        font.setStyleHint(QFont::SansSerif);
        label->setFont(font);

        QPalette palette = label->palette();
        palette.setColor(QPalette::WindowText, QColor("#444"));
        label->setPalette(palette);

        label->setAlignment(Qt::AlignCenter);
        layout->addWidget(label);
    }
};

#endif // BLUEPRINT_PLACEHOLDERPAGE_H