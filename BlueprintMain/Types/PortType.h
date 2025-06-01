#ifndef BLUEPRINT_PORTTYPE_H
#define BLUEPRINT_PORTTYPE_H

enum PortType {
    Input,              // 普通输入端口
    Output,             // 普通输出端口
    EVENT_OUTPUT,       // 事件的输出端口（触发下一节点）
    EVENT_INPUT,        // 事件的输入端口（接收上一个事件）
    EVENT_TRUE_RETURN,  // 条件为真时的返回路径
    EVENT_FALSE_RETURN, // 条件为假时的返回路径
    EVENT_CONDITION     // 条件本身（用于判断的连接）
};

#endif //BLUEPRINT_PORTTYPE_H
