/*----------------------------------------------------------------------------
 * 文件编码约定: 本文件为 UTF-8 编码(带BOM)。
 * 本工程源码统一使用 UTF-8(带BOM) 保存: 新建或修改任何源文件时,
 * 请以 UTF-8 编码保存, 并在文件头保留本注释。
 *----------------------------------------------------------------------------*/
#ifndef __DCHMIAPP_H__
#define __DCHMIAPP_H__
/*****************************************************************************/
#include "sPlc.h"
/*****************************************************************************/
#include "dcHmiApp.h"
#include "preScheme.h"
#include "dcHmiLanguage.h"
#include "dcHmiNotifyButton.h"
#include "dcHmiNotifyProgress.h"
#include "dcHmiNotifyReadRTC.h"
#include "dcHmiNotifyText.h"
#include "tempCtrLoop.h"
/*****************************************************************************/
#include "hmiLib.h"
#include "dcHmiRes.h"
#include "MainAppLib.h"
#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************/
#define LANGUAGE_CODE_EN														01
#define LANGUAGE_CODE_GB														02
/*****************************************************************************/
#define FSMSTEP_HIBERNATE														0//休眠->软关机
#define FSMSTEP_IDLE																1//待机
#define FSMSTEP_POWERUP															10//上电
//HMI初始操作	
#define FSMSTEP_RESTORE_HMI													100//HMI 恢复储存数据
#define FSMSTEP_CHECK_FAIL_DISPLAY									200//失败自检
//密码输入状态
#define FSMSTEP_WAIT_ENTER_PASSCODE									300
#define FSMSTEP_PASSCODE_INPUT											301//密码输入状态
#define FSMSTEP_PASSCODE_NEW0												302//密码更改状态第一次输入
#define FSMSTEP_PASSCODE_NEW1												303//密码更改状态第二次输入
//STNADBY状态
#define FSMSTEP_STANDBY															400//等待状态
#define FSMSTEP_READY_LOAD_PARA											401//载入参数
#define FSMSTEP_READY_LOAD_DONE											402//载入参数完毕
#define FSMSTEP_LASER_WAIT_TRIGGER									403//激光触发
#define FSMSTEP_LASER_EMITING												404//激光发射中
#define FSMSTEP_READY_ERROR													405//脚踏踩下错误

//储存病例
#define FSMSTEP_LIST_TREATMENT											450//显示编辑导入导出EPROM储存的病历
#define FSMSTEP_EDIT_TREATMENT                      460//编辑选择的病历
//选项状态
#define FSMSTEP_OPTION															500//选项菜单
#define FSMSTEP_INFORMATION													600
#define FSMSTEP_SCHEME															700//方案菜单第页

#define FSMSTEP_DIAGNOSIS  													800//诊断菜单
#define FSMSTEP_DIAGNOSIS_RAW												801//诊断菜单-RAW数据
#define FSMSTEP_RENAME															900
//关机状态
#define FSMSTEP_POWEROFF_CONFIRM										1000
//功率校准状态
#define FSMSTEP_CORRECTION													1100//功率校正
/*****************************************************************************/
#define HMI_FLASH_DATA_VERSION  										0XAABB0000
#define HMI_FLASH_DATA_ADDR     										0X00000000
/*****************************************************************************/
void dcHmiLoop(void);//HMI轮训程序
void dcHmiLoopInit(void);
void statusLoop(void);
void tempControlLoop(void);//温度风扇控制循环
void updateStandbyDisplay(void);
void standbyTouchEnable(int8_t enable);
void updatePowerDisplay(void);
void updatePosWidthDisplay(void);
void updateNegWidthDisplay(void );
void updateTimesDisplay(void);
void updateGroupOffDisplay(void);
void updateOptionDisplay(void);
void updateInformationDisplay(void);
void updateAcousticDisplay(void);
uint8_t isLegalUsbDev(USBH_HandleTypeDef *phost);
void wfswLoop(USBH_HandleTypeDef *phost);
/*****************************************************************************/
void loadSelectScheme(int16_t classify, int16_t index);
void updateSchemeDetail(int16_t classify, int16_t index);
void unselectSchemeAll(void);
void seletcSchemeNum(int16_t classify, int16_t index);
void unselectSchemeNum(int16_t index);
/*****************************************************************************/
void clearReleaseTimeEnergy(void);
void updateReleaseTimeEnergy(void);
void updateListTreatmentDisplay(void);//病历储存页面:显示当前治疗记录(待保存)
void refreshListTreatmentDisplay(void);//病历列表页:按当前窗口刷新姓名/ID/病历数与选中按钮状态
void enterListTreatmentPage(void);//病历列表页:重建患者视图并显示第一页
void refreshOperatorUsbDisplay(void);//USB操作页:刷新机内病历摘要与U盘在位状态
void enterOperatorUsbPage(void);//列表页"操作USB"按键:进入USB导入导出操作页
void listTreatmentOperatorUsbBack(void);//USB操作页返回:回到病历列表页
void listTreatmentMoveUp(void);//病历列表页:PAGE_UP键向前翻一整页(到第一页停止)
void listTreatmentMoveDown(void);//病历列表页:PAGE_DOWN键向后翻一整页(到最后一页停止)
void listTreatmentPageKey(uint8_t dir);//病历列表页翻页键统一去抖入口: 0=PAGE_UP 1=PAGE_DOWN, 动作期禁用+完成后清零恢复(释放由notify幂等兜底)
void listTreatmentSelect(uint8_t slot);//病历列表页:选择当前页第slot个患者(0-4)
void listTreatmentSetFindText(const char *text);//病历列表页:SEARCH_NAME输入查找字母, 实时过滤患者姓名
void listTreatmentDelete(void);//旧记录式删除逻辑(暂保留, 新UI的DELETE_0-4走listTreatmentDeleteStart确认页)
void listTreatmentDeleteStart(uint8_t slot);//列表页DELETE_0-4: 进入删除确认页(不立即删除), 缓存待删除患者
void listTreatmentDeleteConfirm(void);//删除确认页DELETE: 级联删除患者及其全部病历后返回列表页
void listTreatmentDeleteCancel(void);//删除确认页CANCEL: 不删除并返回列表页

uint8_t listTreatmentUsbButtonAllowed(uint16_t screen_id, uint16_t control_id);//触摸放行判断(写入中屏蔽触摸, 确认页只放行确认/取消)
uint8_t treatmentButtonLockAllowed(uint16_t screen_id, uint16_t control_id, uint8_t state);//按键互锁门(在途期间锁定其他按键)
void treatmentReleaseButton(uint16_t screen_id, uint16_t control_id);//在途按键清零并解除互锁
void treatmentPopupReleaseArm(uint16_t screen, uint16_t first, uint16_t last);//弹出层返回后延迟重新确认按键弹起
uint8_t listTreatmentUsbBusy(void);//确认页/写入中(usbState非0)
void listTreatmentSaveUsbStart(void);//USB操作页: SAVE_UDISK按键, 进入确认页(不立即写盘, 确认后才CSV导出)
void listTreatmentLoadUsbStart(void);//USB操作页: LOAD_UDISK按键, 进入确认页(不立即读盘, 确认后才CSV导入覆盖机内病历)
void listTreatmentUsbConfirm(void);//确认页: CONFIRM按键, 授权执行导出/导入(读写在轮询中完成)
void listTreatmentUsbCancel(void);//确认页: CANCEL按键, 不读写并返回USB操作页
void listTreatmentCreateStart(void);//列表页CREATE按键: 本次治疗确实发射过激光后进入编辑页新建病历
void listTreatmentCreateConfirm(void);//编辑页OK按键: 校验患者信息后把当前治疗记录追加到EPROM末尾
void listTreatmentCreateCancel(void);//编辑页CANCEL按键: 放弃新建并返回病历列表页
//历史治疗记录页(15)与单条删除确认页(16)
void listTreatmentRecordEnter(uint8_t slot);//列表页KEY_EDIT_RECORD: 进入该患者历史治疗记录页
void refreshListRecordDisplay(void);//记录页: 刷新姓名行/5个记录槽(空槽隐藏)/页码
void listTreatmentRecordPageUp(void);//记录页PAGE_UP: 记录窗口向前翻5条
void listTreatmentRecordPageDown(void);//记录页PAGE_DOWN: 记录窗口向后翻5条
void listTreatmentRecordPageKey(uint8_t dir);//翻页键软件去抖入口: 0=PAGE_UP 1=PAGE_DOWN, 快速连按只生效一次(释放由notify统一做)
void listTreatmentRecordClose(void);//记录页CLOSE: 返回病历列表页
void listTreatmentRecordDeleteStart(uint8_t slot);//记录页DELETE: 进入单条删除确认页(16)
void listTreatmentRecordDeleteKey(uint8_t slot);//记录页DELETE统一入口: 先禁用DELETE键关闭触摸窗口再进确认页, 并解除本页互锁(防卡按下)
void listTreatmentDeleteRecordConfirm(void);//删除确认页OK: 删除该条记录后回记录页
void listTreatmentDeleteRecordCancel(void);//删除确认页CANCEL: 不删除回记录页
void listTreatmentRecordEditPatient(void);//记录页EDIT_PATIENT: 进入患者信息编辑页(17)
void listTreatmentEditPatientConfirm(void);//患者信息编辑页OK: 原地更新患者信息后回记录页
void listTreatmentEditPatientCancel(void);//患者信息编辑页CANCEL: 不更新回记录页
uint8_t listTreatmentIsEditPatientMode(void);//当前编辑页是否为患者信息更新模式
//新建患者注册页(18)/激光核对页(22)/放弃页(23), 见规格第十七节
void listTreatmentRegisterNewPatient(void);//列表页CREATE_NEW: 手动新建患者(不要求激光), 进入注册页
void listTreatmentRegisterConfirm(void);//注册页OK: 校验后新建患者(激光流程同时落记录)
void listTreatmentRegisterCancel(void);//注册页CANCEL: 按来源页返回, EPROM不变
void listTreatmentVerifyAfterLaser(void);//激光停光后自动进入核对页
void listTreatmentVerifySaveRecord(void);//核对页SAVE_RECORD: 新患者进注册页, 已有患者直接落记录
void listTreatmentVerifySelect(void);//核对页SELECT_TREATMENT: 列表页选择已有患者
void listTreatmentVerifyDiscard(void);//核对页DISCARD_RECORD: 进入放弃页
void listTreatmentDiscardReturn(void);//放弃页RETURN: 回核对页
void listTreatmentDiscardCancel(void);//放弃页CANCEL: 确认放弃, 回待机页
uint8_t listTreatmentIsVerifySelectMode(void);//列表页是否处于核对选择模式
void listTreatmentVerifySelectCancel(void);//核对选择模式关闭列表: 回核对页
void listTreatmentUsbLoop(void);//USB确认页轮询(确认页等待按键, 确认后执行一次导出/导入, 完成回操作页)
void dcHmiShowTreatmentRecord(uint16_t index, const treatmentLog_t *log);//病历储存页面:显示EPROM历史病历
void updateSchemeInfo(int16_t classify, int16_t cn);
void updateWarnMsgDisplay(uint8_t id);
void returnStandbyDisplay(void);
void standbyKeyValue(uint8_t value);//设置Standby键值
void standbyKeyTouchEnable(int8_t enable);//Standby key触摸
/*****************************************************************************/
void updateExtralDisplay(void);//更新额外显示
void standbyDebugInfoVisiable(int8_t enable);
void emulatorFswApplyMode(void);//按工程模式设置仿真脚踏可见性/使能(正常模式隐藏禁用并清零)
void optionKeyEnable(uint8_t enable);
/*****************************************************************************/
extern void PmuPowerUp(void);//开机函数
extern void PmuPowerDown(void);//关机函数

#ifdef __cplusplus
}
#endif
#endif






