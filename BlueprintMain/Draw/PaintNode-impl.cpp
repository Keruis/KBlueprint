#include "PaintNode.h"

import NodeType;
#include <QPainterPath>

namespace Paint {
    NodeStyle::NodeStyle(const std::string &filePath) noexcept {
        m_xml.load(filePath);
        updateNodeStyle();
    }

    std::vector<int> NodeStyle::parseStringToIntVector(const std::string &input) {
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

    QColor NodeStyle::GetXmlStyleColor(const std::string& style, QColor defaultColor) noexcept {
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
            return ColorQtStyle[style];
        }
        std::vector<int> colorTmp = parseStringToIntVector(style);
        while (colorTmp.size() < 4) {
            colorTmp.push_back(255);
        }
        return QColor(colorTmp[0], colorTmp[1], colorTmp[2], colorTmp[3]);
    }

    Qt::BrushStyle NodeStyle::GetXmlStyleBrush(const std::string& style, Qt::BrushStyle defaultBrush) noexcept {
        if (style.empty()) {
            return defaultBrush;
        }
        if ([&]() -> bool{
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
        }()) {
            return BrushQtStyle[style];
        }
        return defaultBrush;
    }

    int NodeStyle::GetXmlStyleSum(const std::string &style, int defaultSum) {
        if (style.empty()) {
            return defaultSum;
        }

        std::vector<int> tmpSum = parseStringToIntVector(style);

        return tmpSum[0];
    }

    Qt::AlignmentFlag
    NodeStyle::GetXmlStyleAlignmentFlag(const std::string &style, Qt::AlignmentFlag defaultAlignmentFlag) noexcept {
        if (style.empty()) {
            return defaultAlignmentFlag;
        }
        if ([&]() -> bool{
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
        }()) {
            return AlignmentFlagQtStyle[style];
        }
        return defaultAlignmentFlag;
    }

    void NodeStyle::updateNodeStyle() noexcept {
        m_BackgroundColor = GetXmlStyleColor(m_xml[StyleID]["Background"]["Color"].text(), Qt::gray);
        m_BackgroundBorderWidth = GetXmlStyleSum(m_xml[StyleID]["Background"]["BorderWidth"].text(), 1);
        m_BackgroundBorderColor = GetXmlStyleColor(m_xml[StyleID]["Background"]["BorderColor"].text(), Qt::black);
        int TmpRadius = GetXmlStyleSum(m_xml[StyleID]["Background"]["Radius"].text(), 10);
        m_BackgroundRadiusX = GetXmlStyleSum(m_xml[StyleID]["Background"]["xRadius"].text(), TmpRadius);
        m_BackgroundRadiusY = GetXmlStyleSum(m_xml[StyleID]["Background"]["yRadius"].text(), TmpRadius);
        m_BackgroundBorderStyle = GetXmlStyleBrush(m_xml[StyleID]["Background"]["BorderStyle"].text(), Qt::NoBrush);
        m_FontSize = GetXmlStyleSum(m_xml[StyleID]["FontSize"].text(), 10);
        m_FontColor = GetXmlStyleColor(m_xml[StyleID]["FontColor"].text(), Qt::black);
        m_TitleBackgroundColor = GetXmlStyleColor(m_xml[StyleID]["TitleBackgroundColor"].text(), QColor(128, 128, 128, 220));
        m_FontFlagStyle = GetXmlStyleAlignmentFlag(m_xml[StyleID]["FontFlagStyle"].text(), Qt::AlignCenter);
        m_DividerColor = GetXmlStyleColor(m_xml[StyleID]["DividerColor"].text(), Qt::black);
        m_DividerWidth = GetXmlStyleSum(m_xml[StyleID]["DividerWidth"].text(), 1);
    }

    void NodeStyle::paintNode(QPainter* painter, QRectF& rect, int type, const QString& name) noexcept {
        auto& nodeManager = Types::NodeTypeManager::instance();

        QLinearGradient bgGradient(rect.topLeft(), rect.bottomLeft());
        bgGradient.setColorAt(0, m_BackgroundColor.lighter(110));
        bgGradient.setColorAt(1, m_BackgroundColor.darker(90));

        painter->setBrush(bgGradient);

        painter->setPen(QPen(m_BackgroundBorderColor, m_BackgroundBorderWidth));

        qreal titleRadiusX = m_BackgroundRadiusX;
        qreal titleRadiusY = m_BackgroundRadiusY;

        painter->drawRoundedRect(rect, titleRadiusX, titleRadiusY);

        // 绘制内边框
        QRectF innerRect = rect.adjusted(2, 2, -2, -2);
        painter->setBrush(m_BackgroundBorderStyle);

        painter->setPen(QPen(
                ColorQtStyle[m_xml[StyleID][nodeManager.getTypeName(type)]["InnerBorderColor"].text().empty()
                ? "Qt::black" : m_xml[StyleID][nodeManager.getTypeName(type)]["InnerBorderColor"].text()]
                , m_xml[StyleID][nodeManager.getTypeName(type)]["InnerBorderWidth"].text().empty()
                ? 2
                : std::stoi(m_xml[StyleID][nodeManager.getTypeName(type)]["InnerBorderWidth"].text())));

        painter->drawRoundedRect(innerRect, 8, 8);

        // 设置标题背景色
        QColor titleBgColor = m_TitleBackgroundColor;
        painter->setBrush(titleBgColor);
        painter->setPen(Qt::NoPen);

        QRectF titleRect = QRectF(rect.left(), rect.top(), rect.width(), 20);

        QPointF center = titleRect.center();
        QRadialGradient diffusionGradient(center, 60);  // 半径60px的扩散范围
        diffusionGradient.setColorAt(0, QColor(255, 0, 200, 180));  // 中心颜色（半透明红）
        diffusionGradient.setColorAt(0.7, QColor(255, 0, 200, 60)); // 中间过渡
        diffusionGradient.setColorAt(1, Qt::transparent);             // 边缘透明

        QPainterPath path;
        path.moveTo(titleRect.left() + titleRadiusX, titleRect.top());
        path.arcTo(titleRect.left(), titleRect.top(), titleRadiusX*2, titleRadiusX*2, 90, 90);
        path.lineTo(titleRect.left(), titleRect.bottom());
        path.lineTo(titleRect.right(), titleRect.bottom());
        path.lineTo(titleRect.right(), titleRect.top() - titleRadiusY);
        path.arcTo(titleRect.right() - titleRadiusY*2, titleRect.top(), titleRadiusY*2, titleRadiusY*2, 0, 90);
        path.closeSubpath();

        painter->setBrush(titleBgColor);
        painter->drawPath(path);

        QRectF diffusionRect = titleRect.adjusted(0, 1, 0, -1);  // 扩大绘制区域
        painter->save();  // 保存当前状态
        painter->setBrush(diffusionGradient);
        painter->setPen(Qt::NoPen);
        painter->drawRoundedRect(diffusionRect, 15, 15);  // 使用更大圆角
        painter->restore();  // 恢复状态（避免影响后续绘制）


        QPainterPath overlayPath = path;
        painter->setBrush(QColor(0, 0, 0, 30)); // 半透明黑色
        painter->setCompositionMode(QPainter::CompositionMode::CompositionMode_Multiply); // 混合模式
        painter->drawPath(overlayPath);
        painter->setCompositionMode(QPainter::CompositionMode::CompositionMode_SourceOver); // 恢复默认模式

        QFont font = painter->font();
        font.setPointSize(m_FontSize);  // 设置字体大小
        painter->setFont(font);
        painter->setPen(m_FontColor);   // 设置文字颜色

        // 绘制标题文本
        painter->drawText(titleRect, m_FontFlagStyle, name);

        // 在标题和端口区域之间绘制一条分割线
        painter->setPen(QPen(m_DividerColor, m_DividerWidth));  // 设置线条颜色和宽度

        painter->drawLine(rect.left(), titleRect.bottom(), rect.right(), titleRect.bottom());
    }
}
