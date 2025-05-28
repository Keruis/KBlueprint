#ifndef _PAINTNODE_H_
#define _PAINTNODE_H_

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <QPainter>
#include <QString>
#include <QTime>
#include <random>
#include <chrono>
#include <QStyleOptionGraphicsItem>
#include "../../utils/xml/xml.h"
#include "StyleType.h"

namespace Paint {
    class NodeStyle {
    public:
        NodeStyle() = default;
        NodeStyle(const std::string& filePath) noexcept ;

        void paintNode(QPainter* painter, QRectF& rect, int type, const QString& name) noexcept ;

        void updateNodeStyle() noexcept ;

        std::map<std::string,
                std::pair<
                        std::string,
                        std::vector<
                                std::map<std::string, std::string>
                        >
                >
        > GetNodeStyle() noexcept {return m_NodeStyle;}

        Utils::Xml& Getxml() {return m_xml;}

        void SetStyleID(const std::string& id) noexcept {StyleID = id;}

    private:
        std::vector<int> parseStringToIntVector(const std::string& input) ;
        QColor GetXmlStyleColor(const std::string& style, QColor defaultColor) noexcept ;
        Qt::BrushStyle GetXmlStyleBrush(const std::string& style, Qt::BrushStyle defaultBrush) noexcept ;
        Qt::AlignmentFlag GetXmlStyleAlignmentFlag(const std::string& style, Qt::AlignmentFlag defaultAlignmentFlag) noexcept ;
        int GetXmlStyleSum(const std::string& style, int defaultSum) ;

    private:
        QColor m_BackgroundColor;
        QColor m_BackgroundBorderColor;
        int m_BackgroundBorderWidth;
        int m_BackgroundRadiusX;
        int m_BackgroundRadiusY;
        Qt::BrushStyle m_BackgroundBorderStyle;
        int m_FontSize;
        QColor m_FontColor;
        QColor m_TitleBackgroundColor;
        Qt::AlignmentFlag m_FontFlagStyle;
        QColor m_DividerColor;
        int m_DividerWidth;

    private:
        Utils::Xml m_xml;
        std::string StyleID = "Style-1";
        std::map<std::string,
            std::pair<
                std::string,
                std::vector<
                    std::map<std::string, std::string>
                >
            >
        > m_NodeStyle;
    };
}

#endif