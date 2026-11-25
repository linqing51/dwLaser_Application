//----------------------------------------------------------------------------
// 文件编码约定: 本文件为 UTF-8 编码(带BOM)。
// 本工程源码统一使用 UTF-8(带BOM) 保存: 新建或修改任何源文件时,
// 请以 UTF-8 编码保存, 并在文件头保留本注释。
//----------------------------------------------------------------------------
#ifndef __DCHMIRES_H__
#define __DCHMIRES_H__
/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/
#define HMI_BLACK                                        0x0000 //黑色
#define HMI_NAVY                                         0x000F //深蓝色
#define HMI_DGREEN                                       0x03E0 //深绿色
#define HMI_DCYAN                                        0x03EF //深青色
#define HMI_MAROON                                       0x7800 //深红色
#define HMI_PURPLE                                       0x780F //紫色
#define HMI_OLIVE                                        0x7BE0 //橄榄绿
#define HMI_LGRAY                                        0xC618 //灰白色
#define HMI_DGRAY                                        0x7BEF //深灰色
#define HMI_BLUE                                         0x001F //蓝色
#define HMI_GREEN                                        0x07E0 //绿色
#define HMI_CYAN                                         0x07FF //青色
#define HMI_RED                                          0xF800 //红色
#define HMI_MAGENTA                                      0xF81F //品红
#define HMI_YELLOW                                       0xFFE0 //黄色
#define HMI_WHITE                                        0xFFFF //白色
/*****************************************************************************/
//HMI页面编号
#define GDDC_PAGE_START                                  0  //开始页面
#define GDDC_PAGE_POWERUP_DUAL_1470_635                  1  //启动页面
#define GDDC_PAGE_POWERUP_DUAL_1940_636                  2  //启动页面
#define GDDC_PAGE_POWERUP_DUAL_450_980                   3  //启动页面
#define GDDC_PAGE_POWERUP_TRI_1470_980_635               4  //启动页面
#define GDDC_PAGE_POWERUP_TRI_1940_1470_635              5  //启动页面
#define GDDC_PAGE_PASSCODE                               6  //密码输入页面
#define GDDC_PAGE_NEW_PASSCODE                           7  //新密码输入页面
#define GDDC_PAGE_STANDBY_DUAL_1470_635                  8  //待机页面
#define GDDC_PAGE_STANDBY_DUAL_1940_635                  9  //待机页面
#define GDDC_PAGE_STANDBY_DUAL_450_980                   10 //待机页面
#define GDDC_PAGE_STANDBY_TRI_1470_980_635               11 //待机页面
#define GDDC_PAGE_STANDBY_TRI_1940_1470_635              12 //待机页面
#define GDDC_PAGE_LIST_TREATMENT                         13 //显示病历列表
#define GDDC_PAGE_DELETE_TREATMENT                       14 //删除病历确认
#define GDDC_PAGE_LIST_RECORD                            15 //‌治疗记录页面
#define GDDC_PAGE_DELETE_RECORD							             16 //治疗记录删除页面
#define GDDC_PAGE_EDIT_PATIENT                           17 //编辑病人
#define GDDC_PAGE_REGISTER_PATIENT                       18 //添加病人
#define GDDC_PAGE_OPERATOR_USB                           19 //USB导入导出操作页面
#define GDDC_PAGE_OPERATOR_USB_SAVE                      20 //USB储存操作确认页面
#define GDDC_PAGE_OPERATOR_USB_LOAD        				       21 //USB载入操作确认页面
#define GDDC_PAGE_VERIFY_TREATMENT                       22 //核对治疗记录
#define GDDC_PAGE_DISCARD_TREATMENT                      23 //放弃本次治疗记录
#define GDDC_PAGE_READY                                  24 //准备页面
#define GDDC_PAGE_OPTION                                 25 //选项页面
#define GDDC_PAGE_SCHEME_CLASSIFY_DUAL                   26 //方案分类页 双波长
#define GDDC_PAGE_SCHEME_CLASSIFY_TRI                    27 //方案分类页 三波长
#define GDDC_PAGE_SCHEME_DETAIL                          28 //方案分类页 自定义
#define GDDC_PAGE_INFORMATION                            29 //信息页面
#define GDDC_PAGE_DIAGNOSIS                              30 //诊断页面
#define GDDC_PAGE_DIAGNOSIS_RAW                          31 //诊断页面-原始寄存器
#define GDDC_PAGE_DIAGNOSIS_CALI                         32 //诊断页面-功率校准
#define GDDC_PAGE_RENAME                                 33 //SCHEME更名
#define GDDC_PAGE_RESTORE                                34 //弹出菜单 确认恢复默认值
#define GDDC_PAGE_WEAR_SAFETY                            35 //脚踏安全警告
#define GDDC_PAGE_POWEROFF_CONFIRM                       36 //弹出菜单 确认关机
//GDDC页面控件编号
#define GDDC_PAGE_PASSCODE_KEY_NUM1                      1
#define GDDC_PAGE_PASSCODE_KEY_NUM2                      2
#define GDDC_PAGE_PASSCODE_KEY_NUM3                      3
#define GDDC_PAGE_PASSCODE_KEY_NUM4                      4
#define GDDC_PAGE_PASSCODE_KEY_NUM5                      5
#define GDDC_PAGE_PASSCODE_KEY_NUM6                      6
#define GDDC_PAGE_PASSCODE_KEY_NUM7                      7
#define GDDC_PAGE_PASSCODE_KEY_NUM8                      8
#define GDDC_PAGE_PASSCODE_KEY_NUM9                      9
#define GDDC_PAGE_PASSCODE_KEY_NUM0                      10
#define GDDC_PAGE_PASSCODE_KEY_CANCEL                    11
#define GDDC_PAGE_PASSCODE_KEY_BACKSPACE                 12
#define GDDC_PAGE_PASSCODE_KEY_CHANGEPASSCODE            13
#define GDDC_PAGE_PASSCODE_KEY_ENTER                     14
#define GDDC_PAGE_PASSCODE_TEXT_CODE                     15
/*****************************************************************************/
#define GDDC_PAGE_NEW_PASSCODE_KEY_NUM1                  1
#define GDDC_PAGE_NEW_PASSCODE_KEY_NUM2                  2
#define GDDC_PAGE_NEW_PASSCODE_KEY_NUM3                  3
#define GDDC_PAGE_NEW_PASSCODE_KEY_NUM4                  4
#define GDDC_PAGE_NEW_PASSCODE_KEY_NUM5                  5
#define GDDC_PAGE_NEW_PASSCODE_KEY_NUM6                  6
#define GDDC_PAGE_NEW_PASSCODE_KEY_NUM7                  7
#define GDDC_PAGE_NEW_PASSCODE_KEY_NUM8                  8
#define GDDC_PAGE_NEW_PASSCODE_KEY_NUM9                  9
#define GDDC_PAGE_NEW_PASSCODE_KEY_NUM0                  10
#define GDDC_PAGE_NEW_PASSCODE_KEY_CANCEL                11
#define GDDC_PAGE_NEW_PASSCODE_KEY_BACKSPACE             12
#define GDDC_PAGE_NEW_PASSCODE_KEY_SAVE                  13
#define GDDC_PAGE_NEW_PASSCODE_KEY_BACK                  14
#define GDDC_PAGE_NEW_PASSCODE_TEXT_CODE                 15
/*****************************************************************************/
#define GDDC_PAGE_STANDBY_KEY_POWER_SEL_ADD              1 //当前选择功率增加
#define GDDC_PAGE_STANDBY_KEY_POWER_SEL_INC              2 //当前选择功率减小
#define GDDC_PAGE_STANDBY_KEY_POWER_CH0_ADD              3 //功率增加
#define GDDC_PAGE_STANDBY_KEY_POWER_CH0_INC              4 //功率减小
#define GDDC_PAGE_STANDBY_KEY_POWER_CH1_ADD              5 //通道1功率增加
#define GDDC_PAGE_STANDBY_KEY_POWER_CH1_INC              6 //通道1功率减小
#define GDDC_PAGE_STANDBY_KEY_POWER_CH2_ADD              7 //通道2功率增加
#define GDDC_PAGE_STANDBY_KEY_POWER_CH2_INC              8 //公道2功率减小
#define GDDC_PAGE_STANDBY_KEY_POWER_AIM_ADD              9 //指示光亮度加
#define GDDC_PAGE_STANDBY_KEY_POWER_AIM_INC              10 //指示光亮度减
#define GDDC_PAGE_STANDBY_KEY_STANDBY                    11 //进入准备
#define GDDC_PAGE_STANDBY_KEY_MODE_CW                    12 //连续模式
#define GDDC_PAGE_STANDBY_KEY_MODE_MP                    13 //脉冲模式
#define GDDC_PAGE_STANDBY_KEY_ENTER_OPTION               14 //
#define GDDC_PAGE_STANDBY_KEY_ENTER_SCHEME               15 //
#define GDDC_PAGE_STANDBY_KEY_SCHEME_SAVE                16 //
#define GDDC_PAGE_STANDBY_KEY_SCHEME_NEXT                17 //
#define GDDC_PAGE_STANDBY_KEY_SCHEME_LAST                18 //
#define GDDC_PAGE_STANDBY_KEY_POSWIDTH_ADD               19 //
#define GDDC_PAGE_STANDBY_KEY_POSWIDTH_INC               20 //
#define GDDC_PAGE_STANDBY_KEY_NEGWIDTH_ADD               21 //
#define GDDC_PAGE_STANDBY_KEY_NEGWIDTH_INC               22 //
#define GDDC_PAGE_STANDBY_KEY_SELECT_CH0                 23 //激光通道0选择
#define GDDC_PAGE_STANDBY_KEY_SELECT_CH1                 24 //激光通道1选择
#define GDDC_PAGE_STANDBY_KEY_SELECT_CH2                 25 //激光通道2选择
#define GDDC_PAGE_STANDBY_TEXT_NAME                      26 //方案名称显示
#define GDDC_PAGE_STANDBY_TEXT_SET_POWER_SEL             27 //当前设定功率
#define GDDC_PAGE_STANDBY_TEXT_SET_POWER_CH0             28 //设定功率 1470 / 1940
#define GDDC_PAGE_STANDBY_TEXT_SET_POWER_CH1             29 //设定功率 980
#define GDDC_PAGE_STANDBY_TEXT_SET_POWER_RED             30 //设定功率 635(工作激光)
#define GDDC_PAGE_STANDBY_TEXT_SET_POWER_AIM             31 //设定功率 650(指示激光)
#define GDDC_PAGE_STANDBY_TEXT_WARN                      32 //报警显示
#define GDDC_PAGE_STANDBY_TEXT_AVERAGE_POWER             33 //平均功率显示
#define GDDC_PAGE_STANDBY_TEXT_FREQUENCY                 34 //频率显示
#define GDDC_PAGE_STANDBY_TEXT_DUTYCYCLE                 35 //占空比显示
#define GDDC_PAGE_STANDBY_TEXT_POSWIDTH                  36 //正脉宽显示
#define GDDC_PAGE_STANDBY_TEXT_NEGWIDTH                  37 //负脉宽显示
#define GDDC_PAGE_STANDBY_TEXT_TOTAL_POWER               38 //总功率显示
#define GDDC_PAGE_STANDBY_TEXT_PATIENT_NAME              39 //患者名字显示
#define GDDC_PAGE_STANDBY_PROGRESS_SET_POWER_SEL         40 //当前功率设定拖动条
#define GDDC_PAGE_STANDBY_PROGRESS_SET_POWER_CH0         41 //功率设定拖动条 1470 /1940
#define GDDC_PAGE_STANDBY_PROGRESS_SET_POWER_CH1         42 //功率设定拖动条 980
#define GDDC_PAGE_STANDBY_PROGRESS_SET_POWER_CH2         43 //功率设定拖动条 635(工作激光)
#define GDDC_PAGE_STANDBY_PROGRESS_SET_POWER_AIM         44 //功率设定拖动条 650(指示激光)
#define GDDC_PAGE_STANDBY_ICON_MPKEY                     45 //脉冲模式背景图
#define GDDC_PAGE_STANDBY_KEY_ENTER_TREATMENT            46 //储存手术记录
#define GDDC_PAGE_STANDBY_TEXT_DEBUG              99 //显示调试信息
/*****************************************************************************/
#define GDDC_PAGE_LIST_TREATMENT_TEXT_NAME_0             1 //患者名字
#define GDDC_PAGE_LIST_TREATMENT_TEXT_NAME_1             2 //患者名字
#define GDDC_PAGE_LIST_TREATMENT_TEXT_NAME_2             3 //患者名字
#define GDDC_PAGE_LIST_TREATMENT_TEXT_NAME_3             4 //患者名字
#define GDDC_PAGE_LIST_TREATMENT_TEXT_NAME_4             5 //患者名字
#define GDDC_PAGE_LIST_TREATMENT_TEXT_ID_0               6 //患者ID
#define GDDC_PAGE_LIST_TREATMENT_TEXT_ID_1               7 //患者ID
#define GDDC_PAGE_LIST_TREATMENT_TEXT_ID_2               8 //患者ID
#define GDDC_PAGE_LIST_TREATMENT_TEXT_ID_3               9 //患者ID
#define GDDC_PAGE_LIST_TREATMENT_TEXT_ID_4               10 //患者ID
#define GDDC_PAGE_LIST_TREATMENT_TEXT_RECORD_COUNT_0     11 //治疗记录数量
#define GDDC_PAGE_LIST_TREATMENT_TEXT_RECORD_COUNT_1     12 //治疗记录数量
#define GDDC_PAGE_LIST_TREATMENT_TEXT_RECORD_COUNT_2     13 //治疗记录数量
#define GDDC_PAGE_LIST_TREATMENT_TEXT_RECORD_COUNT_3     14 //治疗记录数量
#define GDDC_PAGE_LIST_TREATMENT_TEXT_RECORD_COUNT_4     15 //治疗记录数量
#define GDDC_PAGE_LIST_TREATMENT_TEXT_CAPACITY           16 //病历容量
#define GDDC_PAGE_LIST_TREATMENT_TEXT_SEARCH_NAME        17 //按姓名或患者编号搜索
#define GDDC_PAGE_LIST_TREATMENT_TEXT_PAGE_NUM           18 //病历页数

#define GDDC_PAGE_LIST_TREATMENT_KEY_SELECT_PATIENT_0    20 //选择患者
#define GDDC_PAGE_LIST_TREATMENT_KEY_SELECT_PATIENT_1    21 //选择患者
#define GDDC_PAGE_LIST_TREATMENT_KEY_SELECT_PATIENT_2    22 //选择患者
#define GDDC_PAGE_LIST_TREATMENT_KEY_SELECT_PATIENT_3    23 //选择患者
#define GDDC_PAGE_LIST_TREATMENT_KEY_SELECT_PATIENT_4    24 //选择患者
#define GDDC_PAGE_LIST_TREATMENT_KEY_DELETE_0            25 //删除患者
#define GDDC_PAGE_LIST_TREATMENT_KEY_DELETE_1            26 //删除患者
#define GDDC_PAGE_LIST_TREATMENT_KEY_DELETE_2            27 //删除患者
#define GDDC_PAGE_LIST_TREATMENT_KEY_DELETE_3            28 //删除患者
#define GDDC_PAGE_LIST_TREATMENT_KEY_DELETE_4            29 //删除患者
#define GDDC_PAGE_LIST_TREATMENT_KEY_EDIT_RECORD_0       31 //编辑患者记录
#define GDDC_PAGE_LIST_TREATMENT_KEY_EDIT_RECORD_1       32 //编辑患者记录
#define GDDC_PAGE_LIST_TREATMENT_KEY_EDIT_RECORD_2       33 //编辑患者记录
#define GDDC_PAGE_LIST_TREATMENT_KEY_EDIT_RECORD_3       34 //编辑患者记录
#define GDDC_PAGE_LIST_TREATMENT_KEY_EDIT_RECORD_4       35 //编辑患者记录
#define GDDC_PAGE_LIST_TREATMENT_KEY_PAGE_UP             36 //上一页
#define GDDC_PAGE_LIST_TREATMENT_KEY_PAGE_DOWN           37 //下一页
#define GDDC_PAGE_LIST_TREATMENT_KEY_CLOSE               38 //关闭
#define GDDC_PAGE_LIST_TREATMENT_KEY_CREATE_NEW          39 //新建患者
#define GDDC_PAGE_LIST_TREATMENT_KEY_OPERATOR_USB        40 //操作USB
#define GDDC_PAGE_LIST_TREATMENT_TEXT_DEBUG       99 //显示调试信息
//***************************************************************************
#define GDDC_PAGE_DELETE_TREATMENT_KEY_OK                1  //确认删除
#define GDDC_PAGE_DELETE_TREATMENT_KEY_CANCEL            2  //取消
#define GDDC_PAGE_DELETE_TREATMENT_TEXT_NAME_ID        3 //名字-ID
#define GDDC_PAGE_DELETE_TREATMENT_TEXT_SUMMARY_0      4
#define GDDC_PAGE_DELETE_TREATMENT_TEXT_SUMMARY_1       5
#define GDDC_PAGE_DELETE_TREATMENT_TEXT_SUMMARY_2        6
//***************************************************************************
#define GDDC_PAGE_LIST_RECORD_TEXT_NAME					  1//患者名字-ID
#define GDDC_PAGE_LIST_RECORD_TEXT_TIME_ENERGY_0    2//第1行治疗记录-显示日期-发射能量-发射时间-功率-波长显示
#define GDDC_PAGE_LIST_RECORD_TEXT_TIME_ENERGY_1          3//第2行治疗记录-显示日期-发射能量-发射时间-功率-波长显示
#define GDDC_PAGE_LIST_RECORD_TEXT_TIME_ENERGY_2       4//第3行治疗记录-显示日期-发射能量-发射时间-功率-波长显示
#define GDDC_PAGE_LIST_RECORD_TEXT_TIME_ENERGY_3          5//第4行治疗记录-显示日期-发射能量-发射时间-功率-波长显示
#define GDDC_PAGE_LIST_RECORD_TEXT_TIME_ENERGY_4       6//第5行治疗记录-显示日期-发射能量-发射时间-功率-波长显示
#define GDDC_PAGE_LIST_RECORD_TEXT_SCHEME_WIDTH_0         7//第1行治疗记录-显示治疗方案-激光模式-正脉冲宽度-负脉冲宽度
#define GDDC_PAGE_LIST_RECORD_TEXT_SCHEME_WIDTH_1         8//第2行治疗记录-显示治疗方案-激光模式-正脉冲宽度-负脉冲宽度
#define GDDC_PAGE_LIST_RECORD_TEXT_SCHEME_WIDTH_2         9//第3行治疗记录-显示治疗方案-激光模式-正脉冲宽度-负脉冲宽度
#define GDDC_PAGE_LIST_RECORD_TEXT_SCHEME_WIDTH_3         10//第4行治疗记录-显示治疗方案-激光模式-正脉冲宽度-负脉冲宽度
#define GDDC_PAGE_LIST_RECORD_TEXT_SCHEME_WIDTH_4         11//第5行治疗记录-显示治疗方案-激光模式-正脉冲宽度-负脉冲宽度
#define GDDC_PAGE_LIST_RECORD_TEXT_PAGE					  12//显示页数
#define GDDC_PAGE_LIST_RECORD_KEY_DELETE_0                20//删除第1行治疗记录
#define GDDC_PAGE_LIST_RECORD_KEY_DELETE_1                21//删除第2行治疗记录
#define GDDC_PAGE_LIST_RECORD_KEY_DELETE_2                22//删除第3行治疗记录
#define GDDC_PAGE_LIST_RECORD_KEY_DELETE_3                23//删除第4行治疗记录
#define GDDC_PAGE_LIST_RECORD_KEY_DELETE_4                24//删除第5行治疗记录
#define GDDC_PAGE_LIST_RECORD_KEY_PAGE_UP			      25//上一页按键
#define GDDC_PAGE_LIST_RECORD_KEY_PAGE_DOWN               26//下一页按键
#define GDDC_PAGE_LIST_RECORD_KEY_CLOSE                   27//关闭按键
#define GDDC_PAGE_LIST_RECORD_KEY_EDIT_PATIENT		      28//编辑患者
//***************************************************************************
#define GDDC_PAGE_DELETE_RECORD_TEXT_NAME                 1//显示患者名字-ID
#define GDDC_PAGE_DELETE_RECORD_TEXT_SUMMARY_0            2//显示治疗日期-发射能量-发射时间-发射功率
#define GDDC_PAGE_DELETE_RECORD_KEY_CANCEL                10//取消返回上级菜单
#define GDDC_PAGE_DELETE_RECORD_KEY_OK                    11//确认删除治疗记录
//***************************************************************************
#define GDDC_PAGE_EDIT_PATIENT_TEXT_ID                    1 //患者ID
#define GDDC_PAGE_EDIT_PATIENT_TEXT_NAME                  2 //患者姓名
#define GDDC_PAGE_EDIT_PATIENT_TEXT_AGE                   3 //患者年龄
#define GDDC_PAGE_EDIT_PATIENT_TEXT_GENDER                4 //性别显示
#define GDDC_PAGE_EDIT_PATIENT_MENU_GENDER                10 //性别下来菜单
#define GDDC_PAGE_EDIT_PATIENT_KEY_OK                     20 //保存修改
#define GDDC_PAGE_EDIT_PATIENT_KEY_CANCEL                 21 //取消
#define GDDC_PAGE_EDIT_PATIENT_KEY_GENDER                 22 //性别选择菜单按键
//***************************************************************************
#define GDDC_PAGE_REGISTER_PATIENT_TEXT_ID                    1 //患者ID
#define GDDC_PAGE_REGISTER_PATIENT_TEXT_NAME                  2 //患者姓名
#define GDDC_PAGE_REGISTER_PATIENT_TEXT_AGE                   3 //患者年龄
#define GDDC_PAGE_REGISTER_PATIENT_TEXT_GENDER                4 //性别显示
#define GDDC_PAGE_REGISTER_PATIENT_TEXT_SUMMARY_0             5 //提示信息
#define GDDC_PAGE_REGISTER_PATIENT_MENU_GENDER                10 //性别下来菜单
#define GDDC_PAGE_REGISTER_PATIENT_KEY_OK                     20 //保存修改
#define GDDC_PAGE_REGISTER_PATIENT_KEY_CANCEL                 21 //取消
#define GDDC_PAGE_REGISTER_PATIENT_KEY_GENDER                 22 //性别选择菜单按键
//***************************************************************************
#define GDDC_PAGE_OPERATOR_USB_TEXT_SUMMARY                 1 //患者数-治疗记录数
#define GDDC_PAGE_OPERATOR_USB_TEXT_SUMMARY_USB             2 //UDISK 信息
#define GDDC_PAGE_OPERATOR_USB_KEY_SAVE_UDISK               3 //存储到U盘
#define GDDC_PAGE_OPERATOR_USB_KEY_LOAD_UDISK               4 //从U盘载入
#define GDDC_PAGE_OPERATOR_USB_KEY_CLOSE                    5 //返回病历列表
//***************************************************************************
#define GDDC_PAGE_OPERATOR_USB_SAVE_TEXT_SUMMARY_0     1 //信息栏
#define GDDC_PAGE_OPERATOR_USB_SAVE_TEXT_SUMMARY_1     2 //信息栏
#define GDDC_PAGE_OPERATOR_USB_SAVE_TEXT_SUMMARY_2     3 //信息栏
#define GDDC_PAGE_OPERATOR_USB_SAVE_TEXT_SUMMARY_3     4 //信息栏
#define GDDC_PAGE_OPERATOR_USB_SAVE_KEY_CANCEL         10 //取消按键
#define GDDC_PAGE_OPERATOR_USB_SAVE_KEY_OK        11 //确认按键
//***************************************************************************
#define GDDC_PAGE_OPERATOR_USB_LOAD_TEXT_SUMMARY_0     1//信息栏
#define GDDC_PAGE_OPERATOR_USB_LOAD_TEXT_SUMMARY_1      2//信息栏
#define GDDC_PAGE_OPERATOR_USB_LOAD_TEXT_SUMMARY_2      3//信息栏
#define GDDC_PAGE_OPERATOR_USB_LOAD_TEXT_SUMMARY_3      4//信息栏
#define GDDC_PAGE_OPERATOR_USB_LOAD_KEY_CANCEL          10//取消按键
#define GDDC_PAGE_OPERATOR_USB_LOAD_KEY_OK              11//确认按键
//***************************************************************************
#define GDDC_PAGE_VERIFY_TREATMENT_TEXT_ID               1 //患者编号
#define GDDC_PAGE_VERIFY_TREATMENT_TEXT_NAME             2 //患者姓名
#define GDDC_PAGE_VERIFY_TREATMENT_TEXT_AGE              3 //患者年龄
#define GDDC_PAGE_VERIFY_TREATMENT_TEXT_SUMMARY_TIME     4 //治疗摘要-日期
#define GDDC_PAGE_VERIFY_TREATMENT_TEXT_SUMMARY_ENERGY   5 //治疗摘要-能量
#define GDDC_PAGE_VERIFY_TREATMENT_TEXT_SUMMARY_OUT_TIME   6 //治疗摘要-输出时长
#define GDDC_PAGE_VERIFY_TREATMENT_TEXT_SUMMARY_POWER    7 //治疗摘要-功率
#define GDDC_PAGE_VERIFY_TREATMENT_TEXT_SUMMARY_SCHEME   8 //治疗摘要-方案
#define GDDC_PAGE_VERIFY_TREATMENT_TEXT_GENDER                  9//性别显示
#define GDDC_PAGE_VERIFY_TREATMENT_MENU_GENDER              20 //性别下来菜单
#define GDDC_PAGE_VERIFY_TREATMENT_KEY_SAVE_RECORD       30 //保存记录 
#define GDDC_PAGE_VERIFY_TREATMENT_KEY_DISCARD_RECORD    31 //放弃本次记录
#define GDDC_PAGE_VERIFY_TREATMENT_KEY_SELECT_TREATMENT    32 //选择患者
#define GDDC_PAGE_VERIFY_TREATMENT_KEY_GENDER               33 //性别选择菜单按键
//***************************************************************************
#define GDDC_PAGE_DISCARD_TREATMENT_TEXT_NAME            1 //名字与ID
#define GDDC_PAGE_DISCARD_TREATMENT_TEXT_ENERGY          2 //能量时间功率
#define GDDC_PAGE_DISCARD_TREATMENT_KEY_RETURN           10 //返回核对
#define GDDC_PAGE_DISCARD_TREATMENT_KEY_CANCEL           11 //放弃本次记录
//***************************************************************************
#define GDDC_PAGE_READY_TEXT_NAME                        1 //方案名称显示
#define GDDC_PAGE_READY_TEXT_POWER_CH0                   2 //发射功率显示 1470 /1940
#define GDDC_PAGE_READY_TEXT_POWER_CH1                   3 //发射功率显示 980
#define GDDC_PAGE_READY_TEXT_POWER_RED                   4 //发射功率显示 635
#define GDDC_PAGE_READY_TEXT_POWER_AIM                   5 //发射功率显示 650
#define GDDC_PAGE_READY_TEXT_POWER_TOTAL                 6 //总发射功率显示
#define GDDC_PAGE_READY_TEXT_ENERGY                      7 //发射能量显示
#define GDDC_PAGE_READY_TEXT_TREATMENT_TIME              8 //发射时间显示
#define GDDC_PAGE_READY_TEXT_ACOUSTIC_ENERGY             9 //提示音能量
#define GDDC_PAGE_READY_TEXT_ACOUSTIC_TIME               10 //提示音时间
#define GDDC_PAGE_READY_TEXT_ACOUSTIC_CYCLE              11 //提示音周期
#define GDDC_PAGE_READY_TEXT_SHOW_WAVE                   12 //选择波长显示
#define GDDC_PAGE_READY_KEY_ACOUSTIC_ENERGY_ADD          13 //提示音能量增加
#define GDDC_PAGE_READY_KEY_ACOUSTIC_ENERGY_INC          14 //提示音能量减小
#define GDDC_PAGE_READY_KEY_ACOUSTIC_TIME_ADD            15 //提示音时间增加
#define GDDC_PAGE_READY_KEY_ACOUSTIC_TIME_INC            16 //提示音时间减小
#define GDDC_PAGE_READY_KEY_READY                        17 //切换待机按键
#define GDDC_PAGE_READY_KEY_EMULATOR_FSW                 98 //模拟脚踏
#define GDDC_PAGE_READY_TEXT_DEBUG                       99 //显示调试信息
//***************************************************************************
#define GDDC_PAGE_OPTION_KEY_TONE                        1 //蜂鸣器声光同步
#define GDDC_PAGE_OPTION_KEY_BEEP_VOLUME_ADD             2 //蜂鸣器音量加
#define GDDC_PAGE_OPTION_KEY_BEEP_VOLUME_INC             3 //蜂鸣器音量减
#define GDDC_PAGE_OPTION_KEY_LCD_BRG_ADD                 4 //液晶屏亮度增加
#define GDDC_PAGE_OPTION_KEY_LCD_BRG_INC                 5 //液晶屏亮度减少
#define GDDC_PAGE_OPTION_KEY_ENTER_OK                    6 //返回待机页面
#define GDDC_PAGE_OPTION_KEY_ENTER_INFORMATION           7 //进入信息菜单
#define GDDC_PAGE_OPTION_KEY_HAND_SWITCH_ON              8 //常开-脉冲 脚踏模式选择
#define GDDC_PAGE_OPTION_KEY_ENTER_ENGINEER              9 //进入工程师模式。
#define GDDC_PAGE_OPTION_TEXT_BEEP_VOLUME                10 //蜂鸣器音量显示
#define GDDC_PAGE_OPTION_TEXT_LCD_BRG                    11 //屏幕亮度显示
#define GDDC_PAGE_OPTION_PROGRESS_BEEP_VOLUME            12 //蜂鸣器音量调节
#define GDDC_PAGE_OPTION_PROGRESS_LCD_BRG                13 //屏幕亮度调节
#define GDDC_PAGE_OPTION_KEY_RESTORE                     14 //恢复默认设置
/*****************************************************************************/
#define GDDC_PAGE_RESTORE_KEY_CANCEL                     1 //取消恢复默认值
#define GDDC_PAGE_RESTORE_KEY_YES                        2 //确认恢复默认值
/*****************************************************************************/
#define GDDC_PAGE_LOAD_UDISK_KEY_COVER                   1 //覆盖
#define GDDC_PAGE_LOAD_UDISK_KEY_CANCEL                  2 //取消
/*****************************************************************************/
#define GDDC_PAGE_SCHEME_CLASSIFY_KEY_PHLEBOLOGY         1
#define GDDC_PAGE_SCHEME_CLASSIFY_KEY_PROCTOLOGY         2
#define GDDC_PAGE_SCHEME_CLASSIFY_KEY_GTNECOLOGY         3
#define GDDC_PAGE_SCHEME_CLASSIFY_KEY_ENT                4
#define GDDC_PAGE_SCHEME_CLASSIFY_KEY_NEUROSURGERY       5
#define GDDC_PAGE_SCHEME_CLASSIFY_KEY_DERMATOLOGY        6
#define GDDC_PAGE_SCHEME_CLASSIFY_KEY_LIPOSUCTION        7
#define GDDC_PAGE_SCHEME_CLASSIFY_KEY_DENTISTRY          8
#define GDDC_PAGE_SCHEME_CLASSIFY_KEY_THERAPY            9
#define GDDC_PAGE_SCHEME_CLASSIFY_KEY_CUSTOM             10
#define GDDC_PAGE_SCHEME_CLASSIFY_KEY_RETURN             11
#define GDDC_PAGE_SCHEME_CLASSIFY_KEY_ENDOLIFT           12
/*****************************************************************************/
#define GDDC_PAGE_SCHEME_DETAIL_KEY_RENAME               1 //更名按键
#define GDDC_PAGE_SCHEME_DETAIL_KEY_OK                   2 //确定
#define GDDC_PAGE_SCHEME_DETAIL_KEY_CANCEL               3 //取消
#define GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_0             4
#define GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_1             5
#define GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_2             6
#define GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_3             7
#define GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_4             8
#define GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_5             9
#define GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_6             10
#define GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_7             11
#define GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_8             12
#define GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_9             13
#define GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_10            14
#define GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_11            15
#define GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_12            16
#define GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_13            17
#define GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_14            18
#define GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_15            19
#define GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_0     20
#define GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_1     21
#define GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_2     22
#define GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_3     23
#define GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_4     24
#define GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_5     25
#define GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_6     26
#define GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_7     27
#define GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_8     28
#define GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_9     29
#define GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_10    30
#define GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_11    31
#define GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_12    32
#define GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_13    33
#define GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_14    34
#define GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_15    35
#define GDDC_PAGE_SCHEME_DETAIL_TEXT_DETAIL0      36
#define GDDC_PAGE_SCHEME_DETAIL_TEXT_DETAIL1      37
#define GDDC_PAGE_SCHEME_DETAIL_TEXT_CLASSIFY     38
#define GDDC_PAGE_SCHEME_DETAIL_KEY_LAST_PAGE            39
#define GDDC_PAGE_SCHEME_DETAIL_KEY_NEXT_PAGE            40
/*****************************************************************************/
#define GDDC_PAGE_INFORMATION_KEY_ENTER_OK               1
#define GDDC_PAGE_INFORMATION_TEXT_TYPE           2
#define GDDC_PAGE_INFORMATION_TEXT_SN             3
#define GDDC_PAGE_INFORMATION_TEXT_LASER_WAVELENGTH 4
#define GDDC_PAGE_INFORMATION_TEXT_MAX_LASER_POWER 5
#define GDDC_PAGE_INFORMATION_TEXT_HARDWARE_VERSION 6
#define GDDC_PAGE_INFORMATION_TEXT_SOFTWARE_VERSION 7
#define GDDC_PAGE_INFORMATION_TEXT_MANUFACTURE_DATE 8
#define GDDC_PAGE_INFORMATION_TEXT_UUID           9
#define GDDC_PAGE_INFORMATION_TEXT_RTC            10
/*****************************************************************************/
#define GDDC_PAGE_DIAGNOSIS_TEXT_INFO0            1
#define GDDC_PAGE_DIAGNOSIS_TEXT_INFO1            2
#define GDDC_PAGE_DIAGNOSIS_TEXT_INFO2            3
#define GDDC_PAGE_DIAGNOSIS_TEXT_INFO3            4
#define GDDC_PAGE_DIAGNOSIS_TEXT_INFO4            17
#define GDDC_PAGE_DIAGNOSIS_TEXT_INFO5            22
#define GDDC_PAGE_DIAGNOSIS_TEXT_INFO6            23
#define GDDC_PAGE_DIAGNOSIS_TEXT_INFO7            24
#define GDDC_PAGE_DIAGNOSIS_TEXT_INFO8            25
#define GDDC_PAGE_DIAGNOSIS_TEXT_YEAR             140
#define GDDC_PAGE_DIAGNOSIS_TEXT_MONTH            141
#define GDDC_PAGE_DIAGNOSIS_TEXT_DAY              142
#define GDDC_PAGE_DIAGNOSIS_TEXT_SN               143
#define GDDC_PAGE_DIAGNOSIS_TEXT_RED_LED_DC       144
#define GDDC_PAGE_DIAGNOSIS_TEXT_GREEN_LED_DC     145
#define GDDC_PAGE_DIAGNOSIS_TEXT_BLUE_LED_DC      146
#define GDDC_PAGE_DIAGNOSIS_TEXT_FIRMWARE_INFO    147
#define GDDC_PAGE_DIAGNOSIS_TEXT_SET_AIM_GAIN     148
#define GDDC_PAGE_DIAGNOSIS_TEXT_FIBER_DETECT     149
#define GDDC_PAGE_DIAGNOSIS_TEXT_DIODE_A_TEMP     150
#define GDDC_PAGE_DIAGNOSIS_TEXT_DIODE_B_TEMP     151
#define GDDC_PAGE_DIAGNOSIS_TEXT_RTC_YEAR         26
#define GDDC_PAGE_DIAGNOSIS_TEXT_RTC_MONTH        27
#define GDDC_PAGE_DIAGNOSIS_TEXT_RTC_DAY          28
#define GDDC_PAGE_DIAGNOSIS_TEXT_RTC_HOURS        24
#define GDDC_PAGE_DIAGNOSIS_TEXT_RTC_MINUTES      30
#define GDDC_PAGE_DIAGNOSIS_TEXT_RTC_SECONDS      31
//
#define GDDC_PAGE_DIAGNOSIS_KEY_DISABLE_TEMPERATURE      300 //屏蔽温度检测
#define GDDC_PAGE_DIAGNOSIS_KEY_DISABLE_FIBER_PROBE      301 //屏蔽光纤探测
#define GDDC_PAGE_DIAGNOSIS_KEY_DISABLE_RFID             302 //屏蔽RFID
#define GDDC_PAGE_DIAGNOSIS_KEY_DISABLE_ESTOP            303 //屏蔽急停检测
#define GDDC_PAGE_DIAGNOSIS_KEY_DISABLE_FOOTSWITCH       304 //屏蔽脚踏检测
#define GDDC_PAGE_DIAGNOSIS_KEY_DISABLE_INTERLOCK        305 //屏蔽安全连锁
#define GDDC_PAGE_DIAGNOSIS_KEY_DISABLE_FLOW             6 //屏蔽流量检测
#define GDDC_PAGE_DIAGNOSIS_KEY_DISABLE_HUMIDITY         7 //屏蔽湿度检测
#define GDDC_PAGE_DIAGNOSIS_KEY_DISABLE_AUTO_FAN         306 //屏蔽风扇
#define GDDC_PAGE_DIAGNOSIS_KEY_CALIBRATION              307 //切换正常和校正模式
#define GDDC_PAGE_DIAGNOSIS_KEY_SAVE_EPROM               308 //储存参数到 ERPOM
#define GDDC_PAGE_DIAGNOSIS_KEY_CLEAR_EPROM              309 //恢复默认参数 EPROM
#define GDDC_PAGE_DIAGNOSIS_KEY_CLEAR_CRC                310 //清除固件CRC信息
#define GDDC_PAGE_DIAGNOSIS_KEY_UPDATE_BOOTLOAD_REQ      311 //更新引导固件请求
#define GDDC_PAGE_DIAGNOSIS_KEY_UPDATE_BOOTLOAD_YES      312 //确认更新固件
#define GDDC_PAGE_DIAGNOSIS_KEY_UPDATE_BOOTLOAD_NO       313 //确认不更新固件
#define GDDC_PAGE_DIAGNOSIS_KEY_OPEN_ILOCK               314 //默认常开安全连锁
#define GDDC_PAGE_DIAGNOSIS_KEY_RAW_DATE                 315 //进去RAW数据信息
#define GDDC_PAGE_DIAGNOSIS_KEY_AUTOFILL                 316 //病历自动填充测试
#define GDDC_PAGE_DIAGNOSIS_KEY_ENTER_OK                 99
/*****************************************************************************/
#define GDDC_PAGE_DIAGNOSIS_RAW_TEXT_INFO0        1
#define GDDC_PAGE_DIAGNOSIS_RAW_TEXT_INFO1        2
#define GDDC_PAGE_DIAGNOSIS_RAW_TEXT_INFO2        3
#define GDDC_PAGE_DIAGNOSIS_RAW_TEXT_INFO3        4
#define GDDC_PAGE_DIAGNOSIS_RAW_TEXT_INFO4        5
#define GDDC_PAGE_DIAGNOSIS_RAW_TEXT_INFO5        6
#define GDDC_PAGE_DIAGNOSIS_RAW_TEXT_INFO6        7
#define GDDC_PAGE_DIAGNOSIS_RAW_TEXT_INFO7        8
#define GDDC_PAGE_DIAGNOSIS_RAW_TEXT_INFO8        9
#define GDDC_PAGE_DIAGNOSIS_RAW_TEXT_INFO9        10
#define GDDC_PAGE_DIAGNOSIS_RAW_TEXT_INFO10       11
#define GDDC_PAGE_DIAGNOSIS_RAW_TEXT_INFO11       12
#define GDDC_PAGE_DIAGNOSIS_RAW_TEXT_INFO12       13
#define GDDC_PAGE_DIAGNOSIS_RAW_TEXT_INFO13       14
#define GDDC_PAGE_DIAGNOSIS_RAW_TEXT_INFO14       15
#define GDDC_PAGE_DIAGNOSIS_RAW_KEY_ENTER_OK             99
/*****************************************************************************/
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_CSET_CH0    10
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_CSET_CH1    11
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_CSET_CH2    12
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_CSET_CH3    13
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_CSET_CH4    14
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_CSET_CH5    15
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_CSET_CH6    16
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_CSET_CH7    17

#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_CDISP_CH0   20
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_CDISP_CH1   21
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_CDISP_CH2   22
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_CDISP_CH3   23
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_CDISP_CH4   24
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_CDISP_CH5   25
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_CDISP_CH6   26
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_CDISP_CH7   27

#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_DIODE_TEMP  30
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_HWATER_TEMP 31
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_CWATER_TEMP 32
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_PID0        33
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_PID1        34
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_HT0         29
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_HT1         35

#define GDDC_PAGE_DIAGNOSIS_CALI_KEY_AUTOTUNE         36

#define GDDC_PAGE_DIAGNOSIS_CALI_KEY_UPDATE_CH0       40
#define GDDC_PAGE_DIAGNOSIS_CALI_KEY_UPDATE_CH1       41
#define GDDC_PAGE_DIAGNOSIS_CALI_KEY_UPDATE_CH2       42
#define GDDC_PAGE_DIAGNOSIS_CALI_KEY_UPDATE_CH3       43
#define GDDC_PAGE_DIAGNOSIS_CALI_KEY_UPDATE_CH4       44
#define GDDC_PAGE_DIAGNOSIS_CALI_KEY_UPDATE_CH5       45
#define GDDC_PAGE_DIAGNOSIS_CALI_KEY_UPDATE_CH6       46
#define GDDC_PAGE_DIAGNOSIS_CALI_KEY_UPDATE_CH7       47

#define GDDC_PAGE_DIAGNOSIS_CALI_KEY_LAS_PWM_CH0      1
#define GDDC_PAGE_DIAGNOSIS_CALI_KEY_LAS_PWM_CH1      2
#define GDDC_PAGE_DIAGNOSIS_CALI_KEY_LAS_PWM_CH2      3
#define GDDC_PAGE_DIAGNOSIS_CALI_KEY_LAS_PWM_CH3      4
#define GDDC_PAGE_DIAGNOSIS_CALI_KEY_LAS_PWM_CH4      5
#define GDDC_PAGE_DIAGNOSIS_CALI_KEY_LAS_PWM_CH5      6
#define GDDC_PAGE_DIAGNOSIS_CALI_KEY_LAS_PWM_CH6      7
#define GDDC_PAGE_DIAGNOSIS_CALI_KEY_LAS_PWM_CH7      8
	
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_0P5         50
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_0P10        51
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_0P15        52
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_0P20        53
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_0P25        54
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_0P30        55
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_0P35        56
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_0P40        57
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_0P45        58
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_0P50        59
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_0P55        60
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_0P60        61
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_0P65        62
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_0P70        63
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_0P75        64
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_0P80        65
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_0P85        66
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_0P90        67
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_0P95        68
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_0P100       69

#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_1P5         70
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_1P10        71
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_1P15        72
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_1P20        73
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_1P25        74
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_1P30        75
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_1P35        76
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_1P40        77
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_1P45        78
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_1P50        79
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_1P55        80
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_1P60        81
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_1P65        82
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_1P70        83
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_1P75        84
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_1P80        85
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_1P85        86
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_1P90        87
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_1P95        88
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_1P100       89

#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_2P5         90
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_2P10        91
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_2P15        92
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_2P20        93
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_2P25        94
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_2P30        95
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_2P35        96
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_2P40        97
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_2P45        98
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_2P50        99
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_2P55        100
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_2P60        101
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_2P65        102
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_2P70        103
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_2P75        104
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_2P80        105
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_2P85        106
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_2P90        107
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_2P95        108
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_2P100       109

#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_3P5         110
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_3P10        111
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_3P15        112
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_3P20        113
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_3P25        114
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_3P30        115
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_3P35        116
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_3P40        117
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_3P45        118
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_3P50        119
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_3P55        120
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_3P60        121
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_3P65        122
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_3P70        123
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_3P75        124
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_3P80        125
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_3P85        126
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_3P90        127
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_3P95        128
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_3P100       129

#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_4P5         130
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_4P10        131
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_4P15        132
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_4P20        133
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_4P25        134
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_4P30        135
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_4P35        136
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_4P40        137
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_4P45        138
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_4P50        139
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_4P55        140
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_4P60        141
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_4P65        142
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_4P70        143
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_4P75        144
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_4P80        145
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_4P85        146
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_4P90        147
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_4P95        148
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_4P100       149

#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_5P5         150
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_5P10        151
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_5P15        152
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_5P20        153
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_5P25        154
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_5P30        155
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_5P35        156
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_5P40        157
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_5P45        158
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_5P50        159
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_5P55        160
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_5P60        161
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_5P65        162
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_5P70        163
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_5P75        164
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_5P80        165
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_5P85        166
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_5P90        167
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_5P95        168
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_5P100       169

#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_6P5         170
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_6P10        171
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_6P15        172
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_6P20        173
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_6P25        174
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_6P30        175
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_6P35        176
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_6P40        177
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_6P45        178
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_6P50        179
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_6P55        180
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_6P60        181
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_6P65        182
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_6P70        183
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_6P75        184
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_6P80        185
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_6P85        186
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_6P90        187
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_6P95        188
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_6P100       189

#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_7P5         190
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_7P10        191
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_7P15        192
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_7P20        193
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_7P25        194
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_7P30        195
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_7P35        196
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_7P40        197
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_7P45        198
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_7P50        199
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_7P55        200
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_7P60        201
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_7P65        202
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_7P70        203
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_7P75        204
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_7P80        205
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_7P85        206
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_7P90        207
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_7P95        208
#define GDDC_PAGE_DIAGNOSIS_CALI_TEXT_7P100       209

#define GDDC_PAGE_DIAGNOSIS_CALI_KEY_SAVE_CH0         224
#define GDDC_PAGE_DIAGNOSIS_CALI_KEY_SAVE_CH1         225
#define GDDC_PAGE_DIAGNOSIS_CALI_KEY_SAVE_CH2         226
#define GDDC_PAGE_DIAGNOSIS_CALI_KEY_SAVE_CH3         227
#define GDDC_PAGE_DIAGNOSIS_CALI_KEY_SAVE_CH4         228
#define GDDC_PAGE_DIAGNOSIS_CALI_KEY_SAVE_CH5         229
#define GDDC_PAGE_DIAGNOSIS_CALI_KEY_SAVE_CH6         230
#define GDDC_PAGE_DIAGNOSIS_CALI_KEY_SAVE_CH7         231

#define GDDC_PAGE_DIAGNOSIS_CALI_KEY_ENTER_OK            900
/*****************************************************************************/
#define GDDC_PAGE_RENAME_TEXT_NEWNAME             1
#define GDDC_PAGE_RENAME_KEY_ENTER                       2
#define GDDC_PAGE_RENAME_KEY_EXIT                        3
/*****************************************************************************/
#define GDDC_PAGE_POWEROFF_CONFIRM_KEY_YES            10
#define GDDC_PAGE_POWEROFF_CONFIRM_KEY_CANCEL         11
/*****************************************************************************/
#ifdef __cplusplus
}
#endif
/*****************************************************************************/
#endif



