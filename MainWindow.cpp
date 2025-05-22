#include "MainWindow.h"
#include "./ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_ui(new Ui::MainWindow),                    //NOLINT
      m_blueprint(new BlueprintClass)
{
    m_ui->setupUi(this);
    setCentralWidget(m_blueprint);
}

MainWindow::~MainWindow() {
    delete m_ui;
    m_ui = nullptr;
}
