module;
#include <string>
#include "../../utils/xml/xml.h"
module DataType;

namespace Types {
    DataTypeManager::DataTypeManager() {
        idToName[(int)BaseDataType::FOR_FUNCTION] = "FOR_FUNCTION";
        idToName[(int)BaseDataType::INT] = "INT";
        idToName[(int)BaseDataType::FLOAT] = "FLOAT";
        idToName[(int)BaseDataType::DOUBLE] = "DOUBLE";
        idToName[(int)BaseDataType::CHAR] = "CHAR";
        idToName[(int)BaseDataType::STRING] = "STRING";
        idToName[(int)BaseDataType::BOOL] = "BOOL";
        idToName[(int)BaseDataType::LONG] = "LONG";
        idToName[(int)BaseDataType::SHORT] = "SHORT";
        idToName[(int)BaseDataType::UNSIGNED_INT] = "UNSIGNED_INT";
        idToName[(int)BaseDataType::VARIANT] = "VARIANT";

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