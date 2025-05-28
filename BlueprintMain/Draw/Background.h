#ifndef BLUEPRINT_BACKGROUND_H
#define BLUEPRINT_BACKGROUND_H

#include <QPainter>
#include <QRectF>

class BlueprintBackground {
public:
    void DrawBackground(QPainter *painter, const QRectF &rect) noexcept ;

    int GetGridSize() noexcept ;
    void SetGridSize(int gridSize) noexcept ;

private:
    int m_gridSize = 20;

};

#endif //BLUEPRINT_BACKGROUND_H
