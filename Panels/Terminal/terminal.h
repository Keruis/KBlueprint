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
#include <QPainter>
#include <QPushButton>
#include <QFileInfo>
#include <QSvgRenderer>

#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <sys/wait.h>
#include <pty.h>
#include <QSocketNotifier>

class Terminal : public QWidget {
    Q_OBJECT

public:
    explicit Terminal(QWidget* parent = nullptr) ;

    void Initialize() noexcept ;

    QPlainTextEdit* GetTerminalOutput() noexcept {
        return m_terminalOutput;
    }

private:
    void setupLayout();
    bool setupPty();
    void setupShell();
    void setupInputHandling();
    void setupButton();
    void setupLabel();

    QString stripAnsi(const QString& text) ;
    void onPtyReadyRead();

    QWidget* createIconLabelWithText(const QString& icon, const QString& text) noexcept ;

protected:
    bool eventFilter(QObject* obj, QEvent* event) override ;

private:
    QLabel* m_title = nullptr;

    QPlainTextEdit* m_terminalOutput = nullptr;
    QLineEdit* m_commandInput = nullptr;

    int m_ptyMasterFd = -1;
    int m_ptySlaveFd  = -1;
    pid_t m_childPid  = -1;
    QSocketNotifier* m_ptyNotifier = nullptr;

    QStringList m_commandHistory;
    int m_historyIndex = -1;

    QPushButton* m_firstRightButton = nullptr;
    QPushButton* m_secondRightButton = nullptr;
    QPushButton* m_thirdRightButton = nullptr;

    QWidget* m_topInfo;
    QWidget* m_middleInfo;
    QWidget* m_bottomInfo;

    std::size_t m_errorNum = 0;
    std::size_t m_warning = 0;
    std::size_t m_Info = 0;
};


#endif //BLUEPRINT_TERMINALUI_H
