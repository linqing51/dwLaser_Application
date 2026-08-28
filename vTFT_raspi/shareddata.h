#ifndef SHAREDDATA_H
#define SHAREDDATA_H

#include <QObject>
#include <QString>


struct SpiBuf {
    int cpuUsage;
    int memoryUsage;
};
union DataUnion {
    SpiBuf SpiData;
    unsigned char byteData[4];
};

// 共享数据类
class SharedData : public QObject
{
    Q_OBJECT // 若需要Qt元对象系统支持则添加，纯数据类可省略

public:
    // 构造函数（私有化以实现单例，或公开供普通使用）
    explicit SharedData(QObject *parent = nullptr);

    // ---------------- 静态常量 ----------------
    // 编译期常量（推荐使用constexpr，C++11及以上）
    static constexpr int MAX_CONNECT_COUNT = 100;      // 最大连接数
    static constexpr double DEFAULT_TIMEOUT = 3.5;     // 默认超时时间
    static const QString APP_VERSION;                  // 应用版本（运行时常量）

    // ---------------- 静态变量 ----------------
    static int globalRequestCount;                     // 全局请求计数
    static QString currentUser;                        // 当前登录用户
    static double systemLoad;                          // 系统负载
    static DataUnion globalSpiBuf;
    // ---------------- 静态方法 ----------------
    // 静态变量初始化/重置方法
    static void resetStaticData();


private:

};

#endif // SHAREDDATA_H
