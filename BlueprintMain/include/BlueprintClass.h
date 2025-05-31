#ifndef BLUEPRINT_BLUEPRINTCLASS_H
#define BLUEPRINT_BLUEPRINTCLASS_H

#include <QGraphicsView>
#include <QOpenGLWidget>
#include <QGraphicsScene>
#include <QFile>
#include <QMenu>
#include <QWheelEvent>
#include <QScrollBar>
#include <QMap>
#include <QPropertyAnimation>
#include <QGraphicsBlurEffect>
#include <QTransform>
#include <QInputDialog>

#include <memory>
#include <vector>
#include "BlueprintNode.h"
#include "BlueprintConnection.h"
#include "BlueprintPort.h"
#include "../../Container/Vec/Vector.h"
#include "../Draw/Background.h"
#include "RegionItem.h"

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

        void SaveNodePush(BlueprintNode* node) noexcept ;

        void PlaceNodeInScene(BlueprintNode* originalNode, const QPointF& mousePos) noexcept ;
        void removeConnection(BlueprintConnection* connection) noexcept ;

        void updateConnectionsForPort(BlueprintPort *port);

        Vector<BlueprintConnection*> GetConnections() noexcept ;

        void propagateDataFromInitialNode(BlueprintPort* init) noexcept ;
        bool areTypesCompatible(const QString& type1, const QString& type2) noexcept ;

        void ensureSceneRectCoversViewport() {
            QRectF viewRect = mapToScene(viewport()->rect()).boundingRect();
            QRectF sceneRect = scene()->sceneRect();

            QRectF expanded = sceneRect;
            constexpr qreal margin = 100.0;
            constexpr qreal extendSize = 1000.0;

            // 向右扩展
            if (viewRect.right() > sceneRect.right() - margin) {
                expanded.setRight(sceneRect.right() + extendSize);
            }

            // 向左扩展
            if (viewRect.left() < sceneRect.left() + margin) {
                expanded.setLeft(sceneRect.left() - extendSize);
            }

            // 向下扩展
            if (viewRect.bottom() > sceneRect.bottom() - margin) {
                expanded.setBottom(sceneRect.bottom() + extendSize);
            }

            // 向上扩展
            if (viewRect.top() < sceneRect.top() + margin) {
                expanded.setTop(sceneRect.top() - extendSize);
            }

            // 如果扩展了，就更新 sceneRect
            if (expanded != sceneRect) {
                scene()->setSceneRect(expanded);
                qDebug() << "Scene rect expanded to:" << expanded;
            }
        }

    protected:
        void drawBackground(QPainter *painter, const QRectF &rect) override;
        void wheelEvent(QWheelEvent *event) override;
        void mousePressEvent(QMouseEvent *event) override;
        void mouseMoveEvent(QMouseEvent *event) override;
        void mouseReleaseEvent(QMouseEvent *event) override;

    private:
        void setupRendering() noexcept;
        void setupInteraction() noexcept;
        void setupAppearance() noexcept;

        void updateAllConnections() noexcept ;

        void addConnection(BlueprintConnection* connection) noexcept ;
        void startConnectionDrag(const QPointF &startPos) noexcept ;

        void smoothZoom() noexcept ;
    protected:
        void contextMenuEvent(QContextMenuEvent *event) override;

    private:
        BlueprintBackground m_background;

        bool m_panning = false;

        double m_zoomLevel = 1.0;
        double m_targetZoomLevel = 1.0;
        double m_velocity = 0.0;
        bool m_isDashing = false;

        double m_blurLevel = 0.0;
        double m_targetBlurLevel = 0.0;

        QTimer *m_animationTimer = nullptr;
        QGraphicsBlurEffect *m_blurEffect = nullptr;

        BlueprintPort *m_draggingPort = nullptr;
        BlueprintConnection *m_currentConnection = nullptr;

        std::unique_ptr<Ui::BlueprintClass> m_ui;
        std::unique_ptr<QGraphicsScene> m_scene;

        Vector<BlueprintNode*> m_saveNodes; // 用于存储所有节点
        Vector<BlueprintNode*> m_sceneNodes; // 用于存储场景中的节点

        Vector<BlueprintConnection*> m_connections;
    };
}

#endif //BLUEPRINT_BLUEPRINTCLASS_H
