#ifndef BLUEPRINT_TERMINALUI_H
#define BLUEPRINT_TERMINALUI_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPlainTextEdit>
#include <QHBoxLayout>
#include <QTimer>
#include <QProcess>
#include <QLineEdit>
#include <QString>
#include <QRegularExpression>

#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <sys/wait.h>
#include <pty.h>
#include <QSocketNotifier>

#include "CPUUsage.h"

class Terminal : public QWidget {
    Q_OBJECT

public:
    explicit Terminal(QWidget* parent = nullptr) ;

    void Initialize() noexcept ;

private:
    void setupLayout();
    void setupStatusBar();
    bool setupPty();
    void setupShell();
    void setupInputHandling();
    void setupResourceMonitor();

protected:
    bool eventFilter(QObject* obj, QEvent* event) override ;

private:
    CPUUsage m_cpuUsage;

    QPlainTextEdit* m_terminalOutput = nullptr;
    QLineEdit* m_commandInput = nullptr;

    QLabel* m_pathLabel = nullptr;
    QLabel* m_cpuLabel = nullptr;
    QLabel* m_memLabel = nullptr;


    int m_ptyMasterFd = -1;  // 伪终端 master 文件描述符
    int m_ptySlaveFd  = -1;
    pid_t m_childPid  = -1;   // 子进程 PID
    QSocketNotifier* m_ptyNotifier = nullptr;

    QStringList m_commandHistory;
    int m_historyIndex = -1;

    QString stripAnsi(const QString& text) {
        static QRegularExpression ansiEscapePattern(R"(\x1B(?:[@-Z\\-_]|\[[0-?]*[ -/]*[@-~]))");
        QString copy = text;
        return copy.replace(ansiEscapePattern, "");
    }

    void onPtyReadyRead() {
        char buf[4096];
        ssize_t bytesRead = ::read(m_ptyMasterFd, buf, sizeof(buf));
        if (bytesRead > 0) {
            QString rawText = QString::fromLocal8Bit(buf, bytesRead);
            QString cleanText = stripAnsi(rawText);

            m_terminalOutput->moveCursor(QTextCursor::End);
            m_terminalOutput->insertPlainText(cleanText);
            m_terminalOutput->moveCursor(QTextCursor::End);
        }
    }
};


#endif //BLUEPRINT_TERMINALUI_H
