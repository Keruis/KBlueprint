module;
#include <QGraphicsView>
#include <QContextMenuEvent>
#include <QFile>
#include <QMenu>
#include <QDebug>
module EventHelpers;

namespace Blueprint::EventHelpers {
    void showStandardContextMenu(void* viewPtr, void* eventPtr) {
        auto* view = reinterpret_cast<QGraphicsView*>(viewPtr);
        auto* event = reinterpret_cast<QContextMenuEvent*>(eventPtr);
        QPointF scenePos = view->mapToScene(event->pos());

        QMenu contextMenu;
        QFile styleFile(":/qss/ContextMenu.qss");
        if (styleFile.open(QFile::ReadOnly)) {
            QString styleSheet = QLatin1String(styleFile.readAll());
            contextMenu.setStyleSheet(styleSheet);
        }

        QMap<QString, QStringList> classNodeMap = {
                {"Input", {"Input A", "Input B", "Input C"}},
                {"Output", {"Output X", "Output Y"}},
                {"Logic", {"AND", "OR", "NOT"}},
                {"Math", {"Add", "Subtract", "Multiply"}}
        };

        for (auto it = classNodeMap.begin(); it != classNodeMap.end(); ++it) {
            QMenu* classMenu = contextMenu.addMenu(it.key());
            classMenu->setObjectName(
                    it.key() == "Input" ? "InputMenu" :
                    it.key() == "Output" ? "OutputMenu" : "OtherMenu"
            );

            for (const QString& nodeName : it.value()) {
                QAction* action = classMenu->addAction(nodeName);
                QObject::connect(action, &QAction::triggered, [nodeName, scenePos]() {
                    qDebug() << "Clicked:" << nodeName << "at position:" << scenePos;
                });
            }
        }

        contextMenu.exec(event->globalPos());
    }
}