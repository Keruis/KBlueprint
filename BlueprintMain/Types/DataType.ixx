module;
#include <string>
#include <map>
export module DataType;

namespace Types {
    export enum class BaseDataType {
        IMAGE = 0,
        MAX_BASE_TYPE
    };

    export class DataTypeManager {
    public:
        static DataTypeManager &instance();

        bool loadFromXml(const std::string &path);

        std::string getTypeName(int id) const;

        int getTypeId(const std::string &name) const;

        bool isBaseType(int id) const;

    private:
        DataTypeManager();

        std::map<int, std::string> idToName;
        std::map<std::string, int> nameToId;
        int nextDynamicId;
    };
}