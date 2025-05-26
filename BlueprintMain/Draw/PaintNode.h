#ifndef _PAINTNODE_H_
#define _PAINTNODE_H_

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <QPainter>
#include <QString>
#include <QStyleOptionGraphicsItem>
#include "../../utils/xml/xml.h"
#include "StyleType.h"

namespace Paint {
    class NodeStyle {
    public:
        NodeStyle() = default;
        NodeStyle(const std::string& filePath) noexcept ;

        void printNodeStyle() const noexcept ;

        void load() noexcept ;

        void paintNode(QPainter* painter, QRectF& rect, int type, QString name) noexcept ;

        std::map<std::string,
                std::pair<
                        std::string,
                        std::vector<
                                std::map<std::string, std::string>
                        >
                >
        > GetNodeStyle() noexcept {return m_NodeStyle;}

        Utils::Xml& Getxml() {return m_xml;}

    private:
        Utils::Xml m_xml;
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