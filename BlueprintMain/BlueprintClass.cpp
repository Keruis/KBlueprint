#include "BlueprintClass.h"
#include "./ui_BlueprintClass.h"

BlueprintClass::BlueprintClass(QWidget *parent)
    : QGraphicsView(parent),
    m_ui(new Ui::BlueprintClass),
    m_scene(new QGraphicsScene(this))
{
    m_ui->setupUi(this);
    setScene(m_scene);  // 将场景设置为QGraphicsView的场景
}

BlueprintClass::~BlueprintClass() {
    delete m_ui;
    m_ui = nullptr;
}

void BlueprintClass::Initialization() noexcept {
    setRenderHint(QPainter::Antialiasing);  // 抗锯齿
    setDragMode(QGraphicsView::ScrollHandDrag);  // 设置拖拽模式

    // 初始视图缩放
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    setBackgroundBrush(QColor(30, 30, 30));  // 设置深色背景
}