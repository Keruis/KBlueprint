#ifndef BLUEPRINT_RADIALMENU_H
#define BLUEPRINT_RADIALMENU_H

#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QPointF>
#include <QTimer>
#include <QPaintEvent>
#include <QSvgRenderer>

class RadialMenu : public QWidget {
    Q_OBJECT

public:
    explicit RadialMenu(QWidget* parent = nullptr) ;

private:
    //void showAt(const QPoint& globalPos) ;
    void updateHoveredByDirection() ;
    [[nodiscard]] int getHoveredSegmentFromAngle(double angle) const ;

protected:
    void paintEvent(QPaintEvent *) override ;
    void mousePressEvent(QMouseEvent *event) override ;
    void mouseMoveEvent(QMouseEvent *event) override ;
    void closeEvent(QCloseEvent *event) override ;


signals:
    void segmentClicked(int index);

private:
    int m_radius;
    int m_innerRadius;
    int m_segmentCount;

    int m_hoveredIndex = -1;
    QPoint m_screenCenter;

    QSvgRenderer* m_svgRenderer0;
    QSvgRenderer* m_svgRenderer1;
};


#endif //BLUEPRINT_RADIALMENU_H
