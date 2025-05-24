#include "MainWindow.h"
#include "./ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_ui(std::make_unique<Ui::MainWindow>()),                    //NOLINT
      m_blueprint(std::make_unique<Blueprint::BlueprintClass>())
{
    m_ui->setupUi(this);
    setCentralWidget(m_blueprint.get());
}

MainWindow::~MainWindow() = default;

void MainWindow::Initialization() noexcept {
    m_blueprint->Initialization();
}

void MainWindow::Shutdown() noexcept { }