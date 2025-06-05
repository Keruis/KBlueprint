#ifndef BLUEPRINT_BOTTOMBAR_H
#define BLUEPRINT_BOTTOMBAR_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QTimer>
#include <QTime>
#include "../SystemMonitor/CPUUsage.h"

class BottomBar : public QWidget {
    Q_OBJECT

public:
    explicit BottomBar(QWidget* parent = nullptr) ;
    ~BottomBar() ;

    void Initialize() noexcept ;

    void SetPath(const QString& path) noexcept ;

private:
    void setupStatusBar() noexcept ;
    void setupResourceMonitor() noexcept ;

private:
    CPUUsage m_cpuUsage;

    QLabel* m_pathLabel = nullptr;
    QLabel* m_cpuLabel = nullptr;
    QLabel* m_memLabel = nullptr;
};


#endif //BLUEPRINT_BOTTOMBAR_H
