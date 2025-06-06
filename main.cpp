#include <QApplication>
#include <QThread>
#include <QTimer>
#include "MainWindow.h"
#include "BlueprintMain/include/BlueprintNode.h"
#include "SplashWindow/SplashWindow.h"

#include <iostream>

import NodeType;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    SplashWindow* splash = new SplashWindow();
    splash->Initialize();
    splash->show();

    MainWindow* window = new MainWindow();
    auto& manager = Types::NodeTypeManager::instance();

    Blueprint::BlueprintNode* tmp1 = new Blueprint::BlueprintNode(0, 1, nullptr);
    tmp1->SetNodeName("A");
    tmp1->SetClassName(QString::fromStdString(manager.getTypeName(tmp1->GetNodeType())));
    tmp1->Initialize(0);

    Blueprint::BlueprintNode* tmp2 = new Blueprint::BlueprintNode(1, 1, nullptr);
    tmp2->SetNodeName("B");
    tmp2->SetClassName(QString::fromStdString(manager.getTypeName(tmp2->GetNodeType())));
    tmp2->Initialize(1);

    auto& blueprint = window->GetBlueprint();
    blueprint->SaveNodePush(tmp1);
    blueprint->SaveNodePush(tmp2);

    QObject::connect(splash, &SplashWindow::animationFinished, [&]() {
        //splash->close();
        window->show();
    });

    window->Initialization();

    return a.exec();
}
