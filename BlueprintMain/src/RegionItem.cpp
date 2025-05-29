#include <iostream>
#include "../Draw/StyleType.h"
#include "../include/RegionItem.h"

RegionItem::RegionItem(QGraphicsItem *parent, const QString& name)
    : QGraphicsRectItem(parent), m_resizeDirection(NoResize), m_name(name)
    {


}

void RegionItem::Initialize() noexcept {
    setFlag(ItemIsMovable, true);
    setFlag(ItemIsSelectable, true);
    setAcceptHoverEvents(true);
    Utils::Xml root;
    root.load("Region.xml");
    std::vector<int> rectSize = parseStringToIntVector(root["RectSize"].text());
    if (rectSize.size() < 4) {
        rectSize = std::vector<int>{0, 0, 150, 200};
    }
    setRect(rectSize[0], rectSize[1], rectSize[2], rectSize[3]);
    setBrush(GetXmlStyleColor(root["RectBackgroundColor"].text(), QColor(255, 255, 255, 120)));
    m_font.SetFont(QFont("Arial"));
}

QString RegionItem::GetName() noexcept {
    return m_name;
}

void RegionItem::SetName(const QString& name) noexcept {
    m_name = name;
}

void RegionItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    setCursor(Qt::ArrowCursor);
    QGraphicsRectItem::hoverEnterEvent(event);
}

void RegionItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event) {
    ResizeDirection direction = calculateResizeDirection(event->pos());
    switch (direction) {
        case ResizeLeft:    setCursor(Qt::SizeHorCursor); break;
        case ResizeRight:   setCursor(Qt::SizeHorCursor); break;
        case ResizeTop:     setCursor(Qt::SizeVerCursor); break;
        case ResizeBottom:  setCursor(Qt::SizeVerCursor); break;
        case ResizeLeftTop:
        case ResizeRightBottom:
            setCursor(Qt::SizeFDiagCursor); break;
        case ResizeRightTop:
        case ResizeLeftBottom:
            setCursor(Qt::SizeBDiagCursor); break;
        default:            setCursor(Qt::ArrowCursor); break;
    }
    QGraphicsRectItem::hoverMoveEvent(event);
}

void RegionItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        m_resizeDirection = calculateResizeDirection(event->pos());
        if (m_resizeDirection == NoResize) {
            QGraphicsRectItem::mousePressEvent(event);
        } else {
            m_dragStartPos = event->pos(); // 记录本地坐标
        }
    }
}

void RegionItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (m_resizeDirection != NoResize) {
        adjustSize(event->pos());
    } else {
        QGraphicsRectItem::mouseMoveEvent(event);
    }
}

void RegionItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    if (scene()) {
        QPointF scenePos = this->scenePos();
        QGraphicsItem* newParent = nullptr;

        QList<QGraphicsItem*> itemsAtPos = scene()->items(scenePos, Qt::IntersectsItemShape, Qt::DescendingOrder);
        for (QGraphicsItem* item : itemsAtPos) {
            // 排除自己
            if (item == this) continue;

            if (auto region = dynamic_cast<RegionItem*>(item)) {
                newParent = region;
                break;
            }
        }

        // 如果父节点不同，更新 parent
        if (newParent != parentItem()) {
            QPointF oldScenePos = this->scenePos();
            setParentItem(newParent); // 重新设置父区域
            QPointF newPos = newParent ? newParent->mapFromScene(oldScenePos) : oldScenePos;
            setPos(newPos); // 让区域在视觉上不跳动
        }
    }
    m_resizeDirection = NoResize;
    QGraphicsRectItem::mouseReleaseEvent(event);
}

void RegionItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) {
    // 判断是否点击在文字区域
    if (m_textRect.contains(event->pos())) {
        bool ok = false;
        QString newName = QInputDialog::getText(
                nullptr,
                QObject::tr("Edit Region Name"),
                QObject::tr("New name:"),
                QLineEdit::Normal,
                m_name,
                &ok
        );

        if (ok && !newName.isEmpty()) {
            m_name = newName;
            update();  // 重新绘制
        }
    }

    // 保持可拖动逻辑
    QGraphicsRectItem::mouseDoubleClickEvent(event);
}

RegionItem::ResizeDirection RegionItem::calculateResizeDirection(const QPointF &pos) noexcept {
    QRectF rect = this->rect();
    qreal edgeSize = 15.0; // 边缘检测阈值

    bool left = qAbs(pos.x() - rect.left()) <= edgeSize;
    bool right = qAbs(pos.x() - rect.right()) <= edgeSize;
    bool top = qAbs(pos.y() - rect.top()) <= edgeSize;
    bool bottom = qAbs(pos.y() - rect.bottom()) <= edgeSize;

    if (left && top) return ResizeLeftTop;
    if (right && top) return ResizeRightTop;
    if (left && bottom) return ResizeLeftBottom;
    if (right && bottom) return ResizeRightBottom;
    if (left) return ResizeLeft;
    if (right) return ResizeRight;
    if (top) return ResizeTop;
    if (bottom) return ResizeBottom;
    return NoResize;
}

void RegionItem::adjustSize(const QPointF &currentPos) noexcept {
    qreal dx = currentPos.x() - m_dragStartPos.x();
    qreal dy = currentPos.y() - m_dragStartPos.y();

    QRectF newRect = rect();
    prepareGeometryChange();

    switch (m_resizeDirection) {
        case ResizeLeft:
            newRect.setLeft(newRect.left() + dx);
            break;
        case ResizeRight:
            newRect.setWidth(newRect.width() + dx);
            break;
        case ResizeTop:
            newRect.setTop(newRect.top() + dy);
            break;
        case ResizeBottom:
            newRect.setHeight(newRect.height() + dy);
            break;
        case ResizeLeftTop:
            newRect.setLeft(newRect.left() + dx);
            newRect.setTop(newRect.top() + dy);
            break;
        case ResizeRightTop:
            newRect.setTop(newRect.top() + dy);
            newRect.setWidth(newRect.width() + dx);
            break;
        case ResizeLeftBottom:
            newRect.setLeft(newRect.left() + dx);
            newRect.setHeight(newRect.height() + dy);
            break;
        case ResizeRightBottom:
            newRect.setWidth(newRect.width() + dx);
            newRect.setHeight(newRect.height() + dy);
            break;
        default: return;
    }

    // 防止尺寸过小
    newRect.setWidth(qMax(50.0, newRect.width()));
    newRect.setHeight(qMax(50.0, newRect.height()));
    prepareGeometryChange();
    setRect(newRect);
    update();
    m_dragStartPos = currentPos;
}

void RegionItem::addChildRegion(RegionItem* child) noexcept {
    child->setParentItem(this);
    child->setZValue(this->zValue() + 1);
}

void RegionItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    if (rect().width() > 1000 || rect().height() > 1000) {
        // 超大块就不渲染文字或特殊效果，提升速度
        painter->setBrush(brush());
        painter->setPen(Qt::NoPen);
        painter->drawRect(rect());  // 无圆角
        return;
    }

    QRectF r = rect();
    constexpr const qreal radius = 10.0;  // 圆角半径

    // 设置填充颜色
    painter->setBrush(brush());
    painter->setPen(Qt::NoPen);

    // 启用抗锯齿
    painter->setRenderHint(QPainter::Antialiasing);

    // 绘制圆角矩形
    painter->drawRoundedRect(r, radius, radius);

    // 动态调整字体大小
    qreal availableWidth = rect().width() - 2;
    qreal textWidth = painter->fontMetrics().horizontalAdvance(m_name);
    qreal fontSize = 5 * (availableWidth / textWidth);
    m_font.SetSize(fontSize);

    // 设置文字样式
    painter->setPen(QColor(255, 255, 255, 130));
    painter->setFont(m_font.GetFont());
    painter->setRenderHint(QPainter::TextAntialiasing);

    // 计算文本位置（右上角）
    qreal textHeight = painter->fontMetrics().height();
    m_textRect.setRect(
            rect().right() - painter->fontMetrics().horizontalAdvance(m_name) - 10,
            rect().top() + 2,
            painter->fontMetrics().horizontalAdvance(m_name),
            textHeight
    );

    // 绘制文本
    painter->drawText(m_textRect, Qt::AlignRight | Qt::AlignTop, m_name);
}

std::vector<int> RegionItem::parseStringToIntVector(const std::string &input) {
    std::vector<int> result;
    std::stringstream ss(input);
    std::string item;

    while (std::getline(ss, item, ',')) {
        item.erase(item.begin(), std::find_if(item.begin(), item.end(), [](unsigned char ch) {
            return !std::isspace(ch);
        }));
        item.erase(std::find_if(item.rbegin(), item.rend(), [](unsigned char ch) {
            return !std::isspace(ch);
        }).base(), item.end());

        try {
            int num = std::stoi(item);
            result.push_back(num);
        } catch (const std::invalid_argument& e) {
            std::cerr << "警告: 无法将 '" << item << "' 转换为整数，已跳过" << std::endl;
        } catch (const std::out_of_range& e) {
            std::cerr << "警告: 数字 '" << item << "' 超出范围，已跳过" << std::endl;
        }
    }

    return result;
}

QColor RegionItem::GetXmlStyleColor(const std::string& style, QColor defaultColor) noexcept {
    if (style.empty()) {
        return defaultColor;
    } else if (
            [&]() -> bool{
                size_t start = style.find_first_not_of(" \t\n\r\f\v");
                if (start == std::string::npos) {
                    return false; // 全是空格
                }

                // 检查剩余部分是否至少有4个字符
                if (style.size() - start < 4) {
                    return false;
                }

                // 比较前4个字符是否为 "Qt::"
                return style.substr(start, 4) == "Qt::";
            }()
            ) {
        return Paint::ColorQtStyle[style];
    }
    std::vector<int> colorTmp = parseStringToIntVector(style);
    while (colorTmp.size() < 4) {
        colorTmp.push_back(255);
    }
    return QColor(colorTmp[0], colorTmp[1], colorTmp[2], colorTmp[3]);
}

