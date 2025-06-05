#ifndef BLUEPRINT_LEFTTOOLBAR_H
#define BLUEPRINT_LEFTTOOLBAR_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QToolButton>
#include <QButtonGroup>

class LeftToolBar : public QWidget {
    Q_OBJECT

public:
    explicit LeftToolBar(QWidget* parent = nullptr) ;
    ~LeftToolBar() ;

    void Initialize() noexcept ;

private:
    QToolButton* createSvgButton(const QString& svgPath) noexcept ;
    QToolButton* createSvgButton(const QString& svgPath, const QString& text) noexcept ;

signals:
    void buttonClicked(int index);

private:
    QButtonGroup* m_buttonGroup = nullptr;
};


#endif //BLUEPRINT_LEFTTOOLBAR_H
