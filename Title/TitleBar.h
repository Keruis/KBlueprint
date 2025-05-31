#ifndef BLUEPRINT_TITLEBAR_H
#define BLUEPRINT_TITLEBAR_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMouseEvent>

class TitleBar : public QWidget {
    Q_OBJECT
public:
    explicit TitleBar(QWidget* parent);
    void Initialize() noexcept ;

private:
    QLabel* createIconLabel() noexcept ;
    QPushButton* createSettingBtn() noexcept ;
    QPushButton* createMinimizeBtn() noexcept ;
    QPushButton* createMaximizeBtn() noexcept ;
    QPushButton* createCloseBtn() noexcept ;

signals:
    void requestSetting();
    void requestMinimize();
    void requestClose();

private:
    QPushButton* m_maximizeBtn;
    void toggleMaximizeRestore() noexcept ;
};


#endif //BLUEPRINT_TITLEBAR_H
