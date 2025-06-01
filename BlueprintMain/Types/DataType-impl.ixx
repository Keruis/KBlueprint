module;
#include <string>
#include "../../utils/xml/xml.h"
module DataType;

namespace Types {
    DataTypeManager::DataTypeManager() {
        idToName[(int)BaseDataType::IMAGE] = "IMAGE";

        for (const auto& [id, name] : idToName) {
            nameToId[name] = id;
        }

        nextDynamicId = (int)BaseDataType::MAX_BASE_TYPE;
    }

    DataTypeManager& DataTypeManager::instance() {
        static DataTypeManager inst;
        return inst;
    }

    bool DataTypeManager::loadFromXml(const std::string& path) {
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

    std::string DataTypeManager::getTypeName(int id) const {
        auto it = idToName.find(id);
        return it != idToName.end() ? it->second : "UNKNOWN";
    }

    int DataTypeManager::getTypeId(const std::string& name) const {
        auto it = nameToId.find(name);
        return it != nameToId.end() ? it->second : -1;
    }

    bool DataTypeManager::isBaseType(int id) const {
        return id < (int)BaseDataType::MAX_BASE_TYPE;
    }
}