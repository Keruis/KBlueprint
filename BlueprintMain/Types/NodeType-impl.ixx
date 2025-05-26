module;
#include <string>
#include "../../utils/xml/xml.h"
module NodeType;

namespace Types {
    NodeTypeManager::NodeTypeManager() {
        idToName[(int)BaseNodeType::FUNCTION] = "FUNCTION";
        idToName[(int)BaseNodeType::INPUT] = "INPUT";
        idToName[(int)BaseNodeType::OUTPUT] = "OUTPUT";
        idToName[(int)BaseNodeType::BRANCH] = "BRANCH";
        idToName[(int)BaseNodeType::CONDITION] = "CONDITION";
        idToName[(int)BaseNodeType::FORLOOP] = "FORLOOP";

        for (const auto& [id, name] : idToName) {
            nameToId[name] = id;
        }

        nextDynamicId = (int)BaseNodeType::MAX_BASE_TYPE;
    }

    NodeTypeManager& NodeTypeManager::instance() {
        static NodeTypeManager inst;
        return inst;
    }

    bool NodeTypeManager::loadFromXml(const std::string& path) {
        Utils::Xml root;
        root.load(path);

        for (Utils::Xml::iterator it = root.begin(); it != root.end(); it++) {
            std::string name = it->attr("name");
            if (!nameToId.contains(name)) {
                idToName[nextDynamicId] = name;
                nameToId[name] = nextDynamicId++;
            }
        }
        return true;
    }

    std::string NodeTypeManager::getTypeName(int id) const {
        auto it = idToName.find(id);
        return it != idToName.end() ? it->second : "UNKNOWN";
    }

    int NodeTypeManager::getTypeId(const std::string& name) const {
        auto it = nameToId.find(name);
        return it != nameToId.end() ? it->second : -1;
    }

    bool NodeTypeManager::isBaseType(int id) const {
        return id < (int)BaseNodeType::MAX_BASE_TYPE;
    }
}