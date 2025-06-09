#include "terminal.h"

Terminal::Terminal(QWidget *parent)
    : QWidget(parent)
{

}

void Terminal::Initialize() noexcept {
    setupLayout();
    if (!setupPty()) {
        m_terminalOutput->appendPlainText("Failed to initialize PTY");
        return;
    }
    setupShell();
    setupInputHandling();
    update();
}

void Terminal::setupLayout() {
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 12, 0);
    layout->setSpacing(0);

    m_title = new QLabel("Terminal");
    m_title->setFixedHeight(24);
    layout->addWidget(m_title);

    // 中间部分：输出和右边面板
    QHBoxLayout* centerLayout = new QHBoxLayout;

    // 左侧输出区域
    m_terminalOutput = new QPlainTextEdit;
    m_terminalOutput->setReadOnly(true);
    m_terminalOutput->setStyleSheet(R"(
        QPlainTextEdit {
            background-color: rgba(0, 0, 0, 60);
            color: white;
            font-family: Consolas;
        }
    )");
    m_terminalOutput->setMinimumHeight(40);

    // 右侧信息面板
    QWidget* rightInfoPanel = new QWidget;
    QVBoxLayout* infoLayout = new QVBoxLayout(rightInfoPanel);

    setupLabel();

    infoLayout->addWidget(m_topInfo);
    infoLayout->addWidget(m_middleInfo);
    infoLayout->addWidget(m_bottomInfo);
    rightInfoPanel->setFixedWidth(50);
    centerLayout->addWidget(rightInfoPanel, /*stretch=*/1);
    centerLayout->addWidget(m_terminalOutput, /*stretch=*/3);

    layout->addLayout(centerLayout);

    QHBoxLayout* inputLayout = new QHBoxLayout;

    inputLayout->setContentsMargins(50, 0, 0, 0);
    m_commandInput = new QLineEdit;
    m_commandInput->setPlaceholderText("Enter command...");
    m_commandInput->setStyleSheet("background-color: rgba(0, 0, 0, 80);"
                                  "color: white; "
                                  "font-family: Consolas;");
    inputLayout->addWidget(m_commandInput);

    setupButton();
    inputLayout->addWidget(m_firstRightButton);
    inputLayout->addWidget(m_secondRightButton);
    inputLayout->addWidget(m_thirdRightButton);

    layout->addLayout(inputLayout);
}

void Terminal::setupButton() {
    m_firstRightButton  = new QPushButton("1");
    m_secondRightButton = new QPushButton("2");
    m_thirdRightButton  = new QPushButton("3");
}

QWidget *Terminal::createIconLabelWithText(const QString &icon, const QString &text) noexcept {
    QWidget* container = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout(container);
    layout->setSpacing(2);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setAlignment(Qt::AlignCenter);

    QLabel* iconLabel = new QLabel;
    iconLabel->setAlignment(Qt::AlignCenter);

    if (QFileInfo(icon).exists() && icon.endsWith(".svg", Qt::CaseInsensitive)) {
        // 加载 SVG 图标
        QSvgRenderer svg(icon);
        QPixmap pixmap(24, 24);
        pixmap.fill(Qt::transparent);
        QPainter painter(&pixmap);
        svg.render(&painter);
        iconLabel->setPixmap(pixmap);
    } else {
        // 显示 Emoji 或字符
        iconLabel->setText(icon);
        iconLabel->setStyleSheet(R"(
            font-size: 20px;
            font-family: "Segoe UI Emoji", "Noto Color Emoji", "Apple Color Emoji", sans-serif;
        )");
    }

    QLabel* textLabel = new QLabel(text);
    textLabel->setStyleSheet(R"(
        color: lightgray;
        font-family: Consolas;
        font-size: 12px;
        border: 1px solid gray;
        border-radius: 6px;
        padding: 2px 4px;
    )");
    textLabel->setAlignment(Qt::AlignCenter);

    layout->addWidget(iconLabel);
    layout->addWidget(textLabel);

    return container;
}

void Terminal::setupLabel() {
    m_topInfo = createIconLabelWithText(":icons/terminal/error.svg", QString::number(m_errorNum));
    m_middleInfo = createIconLabelWithText(":icons/terminal/warning.svg", QString::number(m_warning));
    m_bottomInfo = createIconLabelWithText(":icons/terminal/Info.svg", QString::number(m_Info));
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

QString Terminal::stripAnsi(const QString& text) {
    static QRegularExpression ansiEscapePattern(R"(\x1B(?:[@-Z\\-_]|\[[0-?]*[ -/]*[@-~]))");
    QString copy = text;
    return copy.replace(ansiEscapePattern, "");
}

void Terminal::onPtyReadyRead() {
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