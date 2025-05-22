#ifndef BLUEPRINT_BLUEPRINTCLASS_H
#define BLUEPRINT_BLUEPRINTCLASS_H

#include <QGraphicsView>
#include <QGraphicsScene>

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

private:
    Ui::BlueprintClass *m_ui;
    QGraphicsScene* m_scene;
};


#endif //BLUEPRINT_BLUEPRINTCLASS_H
