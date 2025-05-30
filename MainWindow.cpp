#include "MainWindow.h"
#include "./ui_MainWindow.h"
#include <QDockWidget>
#include <QPushButton>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_ui(std::make_unique<Ui::MainWindow>()),                    //NOLINT
      m_blueprint(std::make_unique<Blueprint::BlueprintClass>())
{
    m_ui->setupUi(this);
}

MainWindow::~MainWindow() = default;

void MainWindow::Initialization() noexcept {
    //setCentralWidget(m_blueprint.get());
    this->setWindowFlags(Qt::FramelessWindowHint);
    auto titleBar = new QWidget(this);
    titleBar->setFixedHeight(30);
    titleBar->setStyleSheet("background-color: #2e2e2e; color: white;");

    auto layout = new QHBoxLayout(titleBar);
    layout->setContentsMargins(5, 0, 5, 0);

    auto titleLabel = new QLabel("蓝图编辑器");
    auto minimizeBtn = new QPushButton("-");
    auto maximizeBtn = new QPushButton("口");
    auto closeBtn = new QPushButton("X");

    layout->addWidget(titleLabel);
    layout->addStretch();
    layout->addWidget(minimizeBtn);
    layout->addWidget(maximizeBtn);
    layout->addWidget(closeBtn);

    auto central = new QWidget;
    auto mainLayout = new QVBoxLayout(central);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(titleBar);
    mainLayout->addWidget(m_blueprint.get());
    setCentralWidget(central);

    connect(minimizeBtn, &QPushButton::clicked, this, &QMainWindow::showMinimized);
    connect(maximizeBtn, &QPushButton::clicked, [this]() {
        isMaximized() ? showNormal() : showMaximized();
    });
    connect(closeBtn, &QPushButton::clicked, this, &QMainWindow::close);

    m_blueprint->Initialization();
}

void MainWindow::Shutdown() noexcept { }

std::unique_ptr<Blueprint::BlueprintClass> &MainWindow::GetBlueprint() noexcept {
    return m_blueprint;
}

