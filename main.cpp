#include <QApplication>
#include "MainWindow.h"
#include "BlueprintMain/include/BlueprintNode.h"


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow window;

    Blueprint::BlueprintNode* tmp1 = new Blueprint::BlueprintNode(0, 1, nullptr);
    tmp1->SetNodeName("A");
    tmp1->SetClassName("Other");
    tmp1->Initialize(0);

    Blueprint::BlueprintNode* tmp2 = new Blueprint::BlueprintNode(1, 1, nullptr);
    tmp2->SetNodeName("B");
    tmp2->SetClassName("Other");
    tmp2->Initialize(1);

    auto& blueprint = window.GetBlueprint();
    blueprint->SaveNodePush(tmp1);
    blueprint->SaveNodePush(tmp2);

    window.Initialization();
    window.show();
    window.Shutdown();

    return a.exec();
}

