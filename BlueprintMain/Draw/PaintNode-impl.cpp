#include "PaintNode.h"

import NodeType;

namespace Paint {
    NodeStyle::NodeStyle(const std::string &filePath) noexcept {
        m_xml.load(filePath);
    }

    void NodeStyle::printNodeStyle() const noexcept {
        std::cout << "=== NodeStyle Data ===\n";
        for (const auto& [nodeName, nodeEntry] : m_NodeStyle) {
            std::cout << "Node: " << nodeName << "\n";
            std::cout << "  NodeType: " << nodeEntry.first << "\n";
            std::cout << "  Children:\n";

            for (const auto& childMap : nodeEntry.second) {
                std::cout << "    [";
                bool first = true;
                for (const auto& [childName, childText] : childMap) {
                    if (!first) std::cout << ", ";
                    std::cout << childName << "=" << childText;
                    first = false;
                }
                std::cout << "]\n";
            }
            std::cout << "\n"; // 分隔不同节点
        }
    }

    void NodeStyle::load() noexcept {
        for (auto& it : m_xml) {
            // 获取当前节点的NodeType属性
            const std::string nodeType = it.attr("NodeType");
            // 获取或创建当前节点的条目
            auto& nodeEntry = m_NodeStyle[it.name()];
            nodeEntry.first = nodeType;  // 设置NodeType

            // 遍历当前节点的所有子节点
            if (!it.empty()) {
                for (auto &ss: it) {
                    // 将子节点的name和text存入map
                    std::map<std::string, std::string> attrMap;
                    attrMap[ss.name()] = ss.text();

                    // 将map添加到vector中
                    nodeEntry.second.emplace_back(std::move(attrMap));
                }
            }
        }
        printNodeStyle();
    }

    void NodeStyle::paintNode(QPainter* painter, QRectF& rect, int type, QString name) noexcept {
        auto& nodeManager = Types::NodeTypeManager::instance();

        std::string NodeType = nodeManager.getTypeName(type);

        painter->setBrush(ColorQtStyle[m_xml["Style-1"]["Brush"].text()]);

        painter->setPen(Qt::black);
        painter->drawRoundedRect(rect, 10, 10);

        // 绘制内边框
        QRectF innerRect = rect.adjusted(2, 2, -2, -2);  // 调整rect以绘制一个稍小的矩形，形成内边框效果
        painter->setBrush(Qt::NoBrush);  // 内边框不填充
        // 根据 nodeType 设置不同的内边框颜色
        if (type == nodeManager.getTypeId("FUNCTION"))
            painter->setPen(QPen(QColor(0, 128, 255), 2));  // 设置内边框颜色为蓝色，宽度为2像素
        else if (type == nodeManager.getTypeId("INPUT"))
            painter->setPen(QPen(QColor(0, 255, 0), 2));  // 设置内边框颜色为绿色，宽度为2像素
        else if (type == nodeManager.getTypeId("OUTPUT"))
            painter->setPen(QPen(QColor(255, 0, 0), 2));  // 设置内边框颜色为红色，宽度为2像素
        painter->drawRoundedRect(innerRect, 8, 8);  // 绘制内边框，圆角稍微小一点

        // 设置字体大小并绘制标题
        QFont font = painter->font();
        font.setPointSize(10);  // 设置字体大小
        painter->setFont(font);
        painter->setPen(Qt::black);

        // 设置标题区域
        QRectF titleRect = QRectF(rect.left(), rect.top(), rect.width(), 30);  // 标题区域高度为30
        painter->drawText(titleRect, Qt::AlignCenter, name);  // 居中绘制标题

        // 在标题和端口区域之间绘制一条分割线
        painter->setPen(QPen(Qt::black, 1));  // 设置线条颜色和宽度
        painter->drawLine(rect.left(), titleRect.bottom(), rect.right(), titleRect.bottom());
    }
}
