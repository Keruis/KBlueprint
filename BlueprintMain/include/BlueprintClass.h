#ifndef BLUEPRINT_BLUEPRINTCLASS_H
#define BLUEPRINT_BLUEPRINTCLASS_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QFile>
#include <QMenu>
#include <QWheelEvent>
#include <QScrollBar>
#include <QMap>
#include <QPropertyAnimation>
#include <QGraphicsBlurEffect>
#include <QTransform>

#include <memory>
#include <vector>
#include "BlueprintNode.h"
#include "BlueprintConnection.h"
#include "BlueprintPort.h"
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
        void removeConnection(BlueprintConnection* connection) noexcept ;
        // 更新与指定端口相关的所有连接
        void updateConnectionsForPort(BlueprintPort *port);

        Vector<BlueprintConnection*> GetConnections() noexcept ;

        void propagateDataFromInitialNode(BlueprintPort* init) noexcept ;
        bool areTypesCompatible(const QString& type1, const QString& type2) noexcept ;

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
        bool m_panning = false;
        QPoint m_lastMousePos;

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
