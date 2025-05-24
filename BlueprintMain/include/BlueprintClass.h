#ifndef BLUEPRINT_BLUEPRINTCLASS_H
#define BLUEPRINT_BLUEPRINTCLASS_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QFile>
#include <QMenu>
#include <QWheelEvent>
#include <memory>

#include "BlueprintNode.h"
#include "../../Container/Vec/Vector.h"

QT_BEGIN_NAMESPACE
namespace Ui { class BlueprintClass; }
QT_END_NAMESPACE

namespace Blueprint {
    class BlueprintClass : public QGraphicsView {
    Q_OBJECT

    public:
        explicit BlueprintClass(QWidget *parent = nullptr);
        ~BlueprintClass() override;

        void Initialization() noexcept;
        void Shutdown() noexcept;

        void PlaceNodeInScene(BlueprintNode* originalNode, const QPointF& mousePos) noexcept ;

    private:
        void setupRendering() noexcept;
        void setupInteraction() noexcept;
        void setupAppearance() noexcept;

    protected:
        void contextMenuEvent(QContextMenuEvent *event) override;

    private:
        std::unique_ptr<Ui::BlueprintClass> m_ui;
        std::unique_ptr<QGraphicsScene> m_scene;

        Vector<BlueprintNode*> m_saveNodes; // 用于存储所有节点
        Vector<BlueprintNode*> m_sceneNodes; // 用于存储场景中的节点
    };
}

#endif //BLUEPRINT_BLUEPRINTCLASS_H
