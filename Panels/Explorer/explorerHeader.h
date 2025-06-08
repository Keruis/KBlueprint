#ifndef BLUEPRINT_EXPLORERHEADER_H
#define BLUEPRINT_EXPLORERHEADER_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QFrame>
#include <QHBoxLayout>
#include <QPushButton>
#include <QPropertyAnimation>

class ExplorerHeader : public QWidget {
Q_OBJECT
public:
    explicit ExplorerHeader(QWidget* parent = nullptr);
    void setButtonsVisible(bool visible);

signals:
    void addRequested();
    void expandRequested();
    void collapseRequested();

private:
    QPushButton* m_addBtn = nullptr;
    QFrame* m_line = nullptr;
    QPushButton* m_expandBtn = nullptr;
    QPushButton* m_collapseBtn = nullptr;

    QPropertyAnimation* m_addAnim = nullptr;
    QPropertyAnimation* m_lineAnim = nullptr;
    QPropertyAnimation* m_expandAnim = nullptr;
    QPropertyAnimation* m_collapseAnim = nullptr;

    void setupUi();
    void setupConnections();
    void setupAnimations();
    void animateOpacity(QPropertyAnimation* animation, qreal endValue);
    QPushButton* createIconButton(const QString& iconPath, const QString& tooltip);
};


#endif //BLUEPRINT_EXPLORERHEADER_H
