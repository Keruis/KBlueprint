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

    void NodeStyle::paintNode(QPainter* painter, QRectF& rect, int type, const QString& name) noexcept {
        auto& nodeManager = Types::NodeTypeManager::instance();

        painter->setBrush(
                m_xml[StyleID]["Background"].text().empty()
                ? Qt::gray
                : ColorQtStyle[m_xml[StyleID]["Background"].text()]
        );

        int BorderWidth = m_xml[StyleID]["BorderWidth"].text().empty()
                ? 1
                : std::stoi(m_xml[StyleID]["BorderWidth"].text());

        painter->setPen(QPen(m_xml[StyleID]["BorderColor"].text().empty()
                ? Qt::black
                : ColorQtStyle[m_xml[StyleID]["BorderColor"].text()]
                , BorderWidth));

        painter->drawRoundedRect(rect, m_xml[StyleID]["xRadius"].text().empty()
                ? m_xml[StyleID]["Radius"].text().empty()
                ? 10 : std::stoi(m_xml[StyleID]["Radius"].text())
                : std::stoi(m_xml[StyleID]["xRadius"].text()), m_xml[StyleID]["yRadius"].text().empty()
                        ? m_xml[StyleID]["Radius"].text().empty()
                        ? 10 : std::stoi(m_xml[StyleID]["Radius"].text())
                        : std::stoi(m_xml[StyleID]["yRadius"].text()));

        // 绘制内边框
        QRectF innerRect = rect.adjusted(2, 2, -2, -2);
        painter->setBrush(m_xml[StyleID]["BorderStyle"].text().empty()
                          ? Qt::NoBrush
                          : BrushQtStyle[m_xml[StyleID]["BorderStyle"].text()]);

        painter->setPen(QPen(
                ColorQtStyle[m_xml[StyleID][nodeManager.getTypeName(type)]["InnerBorderColor"].text().empty() ? "Qt::blue" : m_xml[StyleID][nodeManager.getTypeName(type)]["InnerBorderColor"].text()]
                , m_xml[StyleID][nodeManager.getTypeName(type)]["InnerBorderWidth"].text().empty()
                ? 2
                : std::stoi(m_xml[StyleID][nodeManager.getTypeName(type)]["InnerBorderWidth"].text())));

        painter->drawRoundedRect(innerRect, 8, 8);

        // 设置字体大小并绘制标题
        QFont font = painter->font();
        font.setPointSize(m_xml[StyleID]["FontSize"].text().empty()
                          ? 10
                          : std::stoi(m_xml[StyleID]["FontSize"].text()));  // 设置字体大小
        painter->setFont(font);
        painter->setPen(m_xml[StyleID]["FontColor"].text().empty()
                        ? Qt::black
                        : ColorQtStyle[m_xml[StyleID]["FontColor"].text()]);

        // 设置标题区域
        QRectF titleRect = QRectF(rect.left(), rect.top(), rect.width(), 30);  // 标题区域高度为30
        painter->drawText(titleRect, Qt::AlignCenter, name);  // 居中绘制标题

        // 在标题和端口区域之间绘制一条分割线
        painter->setPen(QPen(m_xml[StyleID]["DividerColor"].text().empty()
                             ? Qt::black
                             : ColorQtStyle[m_xml[StyleID]["DividerColor"].text()],
                             m_xml[StyleID]["DividerWidth"].text().empty()
                             ? 1
                             : std::stoi(m_xml[StyleID]["DividerWidth"].text())));  // 设置线条颜色和宽度
        painter->drawLine(rect.left(), titleRect.bottom(), rect.right(), titleRect.bottom());
    }
}
