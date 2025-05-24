#include "../include/BlueprintClass.h"
#include "../ui/ui_BlueprintClass.h"

import EventHelpers;

using namespace Blueprint;

BlueprintClass::BlueprintClass(QWidget *parent)
    : QGraphicsView(parent),
    m_ui(std::make_unique<Ui::BlueprintClass>()),
    m_scene(std::make_unique<QGraphicsScene>(this))
{
    m_ui->setupUi(this);
    setScene(m_scene.get());
}

BlueprintClass::~BlueprintClass() = default;

void BlueprintClass::setupRendering() noexcept {
    setRenderHint(QPainter::Antialiasing);  // 抗锯齿
    setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
}

void BlueprintClass::setupInteraction() noexcept {
    setDragMode(QGraphicsView::ScrollHandDrag);  // 设置拖拽模式
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
}

void BlueprintClass::setupAppearance() noexcept {
    setFrameShape(QFrame::NoFrame);
    setBackgroundBrush(QColor(30, 30, 30));  // 设置深色背景
}

void BlueprintClass::Initialization() noexcept {
    setupRendering();
    setupInteraction();
    setupAppearance();
}

void BlueprintClass::Shutdown() noexcept {}

// TEST
void BlueprintClass::contextMenuEvent(QContextMenuEvent* event) {
    Blueprint::EventHelpers::showStandardContextMenu(this, event);
}