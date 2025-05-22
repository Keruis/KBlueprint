#ifndef BLUEPRINT_MAINWINDOW_H
#define BLUEPRINT_MAINWINDOW_H

#include <QMainWindow>
#include "BlueprintMain/include/BlueprintClass.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    void Initialization() noexcept ;
    void Shutdown() noexcept ;

private:
    Ui::MainWindow *m_ui;
    BlueprintClass* m_blueprint;
};


#endif
