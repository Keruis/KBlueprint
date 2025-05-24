module;
#include <string>
#include <map>
export module NodeType;

namespace Types {
    export enum class BaseNodeType {
        FUNCTION = 0,   // 函数节点：表示一个可执行的函数操作，一般包含逻辑处理
        INPUT,          // 输入节点：表示外部输入的数据、信号或变量进入系统的入口
        OUTPUT,         // 输出节点：表示系统输出数据或结果的出口
        BRANCH,         // 分支节点：用于流程控制，根据条件决定下一步执行路径
        CONDITION,      // 条件节点：表示布尔判断条件，通常配合 BRANCH 控制流程走向
        FORLOOP,        // 循环节点：表示一个 for 循环结构，用于重复执行某段逻辑
        MAX_BASE_TYPE
    };

    export class NodeTypeManager {
    public:
        static NodeTypeManager &instance();

        bool loadFromXml(const std::string &path);

        std::string getTypeName(int id) const;

        int getTypeId(const std::string &name) const;

        bool isBaseType(int id) const;

    private:
        NodeTypeManager();

        std::map<int, std::string> idToName;
        std::map<std::string, int> nameToId;
        int nextDynamicId;
    };
}