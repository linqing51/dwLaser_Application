#include "shareddata.h"

// ---------------- 静态成员初始化 ----------------
// 静态常量初始化（运行时常量必须在类外初始化）
const QString SharedData::APP_VERSION = "1.0.0";

// 静态变量初始化（必须在类外初始化）
int SharedData::globalRequestCount = 0;
QString SharedData::currentUser = "";
double SharedData::systemLoad = 0.0;


// ---------------- 构造函数实现 ----------------
SharedData::SharedData(QObject *parent)
    : QObject(parent)
{
    // 构造函数逻辑（如初始化非静态成员）
}

// ---------------- 静态方法实现 ----------------
void SharedData::resetStaticData()
{
    // 重置所有静态变量为初始值
    globalRequestCount = 0;
    currentUser = "";
    systemLoad = 0.0;
}


