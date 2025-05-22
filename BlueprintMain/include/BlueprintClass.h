#ifndef BLUEPRINT_BLUEPRINTCLASS_H
#define BLUEPRINT_BLUEPRINTCLASS_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QFile>
#include <QMenu>
#include <QWheelEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class BlueprintClass; }
QT_END_NAMESPACE

class BlueprintClass : public QGraphicsView {
    Q_OBJECT

public:
    explicit BlueprintClass(QWidget *parent = nullptr);
    ~BlueprintClass() override;

    void Initialization() noexcept ;
    void Shutdown() noexcept ;

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;

private:
    Ui::BlueprintClass *m_ui;
    QGraphicsScene* m_scene;
};


#endif //BLUEPRINT_BLUEPRINTCLASS_H
