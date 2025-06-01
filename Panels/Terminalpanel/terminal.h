#ifndef BLUEPRINT_TERMINALUI_H
#define BLUEPRINT_TERMINALUI_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPlainTextEdit>
#include <QHBoxLayout>
#include "CPUUsage.h"
#include <QTimer>

class Terminal : public QWidget {
    Q_OBJECT

public:
    explicit Terminal(QWidget* parent = nullptr) ;

    void Initialize() noexcept ;

private:
    CPUUsage m_cpuUsage;
    QPlainTextEdit* m_terminalOutput = nullptr;
    QLabel* m_pathLabel = nullptr;
    QLabel* m_cpuLabel = nullptr;
    QLabel* m_memLabel = nullptr;
};


#endif //BLUEPRINT_TERMINALUI_H
