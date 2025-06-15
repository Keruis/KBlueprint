#ifndef BLUEPRINT_FLOATINGSIDEBAR_H
#define BLUEPRINT_FLOATINGSIDEBAR_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

class FloatingSidebar : public QWidget {
Q_OBJECT
public:
    explicit FloatingSidebar(QWidget* parent = nullptr);

private:
    void setupLayout();
    void setupTitle();
    void setupButtons();
    QPushButton* createFlatButton(const QString& text);

private:
    QVBoxLayout* m_layout = nullptr;
};

#endif //BLUEPRINT_FLOATINGSIDEBAR_H
