#include "terminal.h"

Terminal::Terminal(QWidget *parent)
    : QWidget(parent)
{

}

void Terminal::Initialize() noexcept {
    setupLayout();
    setupStatusBar();
    if (!setupPty()) {
        m_terminalOutput->appendPlainText("Failed to initialize PTY");
        return;
    }
    setupShell();
    setupInputHandling();
    setupResourceMonitor();
    update();
}

void Terminal::setupLayout() {
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);

    QLabel* title = new QLabel("Terminal");
    title->setFixedHeight(24);
    layout->addWidget(title);

    m_terminalOutput = new QPlainTextEdit;
    m_terminalOutput->setReadOnly(true);
    m_terminalOutput->setStyleSheet("color: white; font-family: Consolas;");
    m_terminalOutput->setMinimumHeight(80);
    layout->addWidget(m_terminalOutput);

    m_commandInput = new QLineEdit;
    m_commandInput->setPlaceholderText("Enter command...");
    m_commandInput->setStyleSheet("color: white; font-family: Consolas;");
    layout->addWidget(m_commandInput);
}

void Terminal::setupStatusBar() {
    QWidget* statusBar = new QWidget;
    QHBoxLayout* statusLayout = new QHBoxLayout(statusBar);
    statusLayout->setContentsMargins(4, 2, 4, 2);
    statusLayout->setSpacing(8);

    m_pathLabel = new QLabel("Path: /your/project/path");
    m_cpuLabel = new QLabel("CPU: 0%");
    m_memLabel = new QLabel("Memory: 0 MB");

    statusLayout->addWidget(m_pathLabel);
    statusLayout->addStretch();
    statusLayout->addWidget(m_cpuLabel);
    statusLayout->addWidget(m_memLabel);
    layout()->addWidget(statusBar);
}

bool Terminal::setupPty() {
    int masterFd, slaveFd;
    struct termios termSettings{};
    struct winsize winSize{};

    winSize.ws_row = 24;
    winSize.ws_col = 80;

    if (openpty(&masterFd, &slaveFd, nullptr, &termSettings, &winSize) == -1) {
        return false;
    }

    m_ptyMasterFd = masterFd;
    m_ptySlaveFd = slaveFd;
    return true;
}

void Terminal::setupShell() {
    m_childPid = fork();
    if (m_childPid == -1) {
        m_terminalOutput->appendPlainText("Failed to fork");
        ::close(m_ptyMasterFd);
        ::close(m_ptySlaveFd);
        return;
    }

    if (m_childPid == 0) {
        // child process
        ::close(m_ptyMasterFd);
        setsid();
        ioctl(m_ptySlaveFd, TIOCSCTTY, 0);
        dup2(m_ptySlaveFd, STDIN_FILENO);
        dup2(m_ptySlaveFd, STDOUT_FILENO);
        dup2(m_ptySlaveFd, STDERR_FILENO);

        if (m_ptySlaveFd > STDERR_FILENO) {
            ::close(m_ptySlaveFd);
        }

        execl("/bin/bash", "bash", nullptr);
        _exit(1);
    } else {
        ::close(m_ptySlaveFd);
        connect(m_commandInput, &QLineEdit::returnPressed, this, [=]() {
            QString command = m_commandInput->text().trimmed();
            if (command.isEmpty()) return;

            m_terminalOutput->appendPlainText(QString("> %1").arg(command));

            if (command == "clear") {
                m_terminalOutput->clear();
            } else {
                QByteArray cmdBytes = command.toLocal8Bit() + "\n";
                ::write(m_ptyMasterFd, cmdBytes.constData(), cmdBytes.size());
            }

            m_commandHistory.prepend(command);
            m_historyIndex = -1;
            m_commandInput->clear();
        });
        m_ptyNotifier = new QSocketNotifier(m_ptyMasterFd, QSocketNotifier::Read, this);
        connect(m_ptyNotifier, &QSocketNotifier::activated, this, &Terminal::onPtyReadyRead);
    }
}

void Terminal::setupInputHandling() {
    connect(m_commandInput, &QLineEdit::returnPressed, this, [=]() {
        QString command = m_commandInput->text().trimmed();
        if (command.isEmpty()) return;

        m_terminalOutput->appendPlainText(QString("> %1").arg(command));
        QByteArray cmdBytes = command.toLocal8Bit() + "\n";
        ::write(m_ptyMasterFd, cmdBytes.constData(), cmdBytes.size());

        m_commandHistory.prepend(command);
        m_historyIndex = -1;
        m_commandInput->clear();
    });

    m_commandInput->installEventFilter(this);
}

void Terminal::setupResourceMonitor() {
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=]() {
        double cpuUsage = m_cpuUsage.GetCPUUsage();
        double memUsage = m_cpuUsage.GetMemoryUsageMB();
        m_cpuLabel->setText(QString("CPU: %1%").arg(cpuUsage, 0, 'f', 1));
        m_memLabel->setText(QString("Memory: %1 MB").arg(memUsage, 0, 'f', 1));
    });
    timer->start(1000);
}

bool Terminal::eventFilter(QObject* obj, QEvent* event) {
    if (obj == m_commandInput && event->type() == QEvent::KeyPress) {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        if (keyEvent->key() == Qt::Key_Up) {
            if (m_historyIndex + 1 < m_commandHistory.size()) {
                m_historyIndex++;
                m_commandInput->setText(m_commandHistory[m_historyIndex]);
            }
            return true;
        }
        if (keyEvent->key() == Qt::Key_Down) {
            if (m_historyIndex > 0) {
                m_historyIndex--;
                m_commandInput->setText(m_commandHistory[m_historyIndex]);
            } else {
                m_historyIndex = -1;
                m_commandInput->clear();
            }
            return true;
        }
    }
    return QWidget::eventFilter(obj, event);
}