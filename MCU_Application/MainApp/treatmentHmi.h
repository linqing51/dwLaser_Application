// ----------------------------------------------------------------------------
// 文件编码约定: 本文件为 UTF-8 编码(带BOM)。
// 本工程源码统一使用 UTF-8(带BOM) 保存, 以 UTF-8 编码保存并在文件头保留本注释。
// ----------------------------------------------------------------------------
// 病历HMI交互层: 仅声明病历相关页面/弹窗的全部HMI入口, 由treatmentHmi.c实现。
// 本头文件不依赖dcHmiApp.h, 只经sPlc.h取得基础类型; 病历存储见treatment.h,
// 病历U盘CSV数据层见treatmentCsv.h。通知层与主状态机经本头调用病历HMI。
#ifndef __TREATMENTHMI_H__
#define __TREATMENTHMI_H__
#include "sPlc.h"
#ifdef __cplusplus
extern "C" {
#endif

// ***************************************************************************
// 病历列表页(GDDC_PAGE_LIST_TREATMENT)
void listTreatmentSetFindText(const char *text);
void enterListTreatmentPage(void);
void updateListTreatmentDisplay(void);
void refreshListTreatmentDisplay(void);
void listTreatmentPageKey(uint8_t dir);
void listTreatmentMoveUp(void);
void listTreatmentMoveDown(void);
void listTreatmentSelect(uint8_t slot);
void listTreatmentDelete(void);
void listTreatmentDeleteStart(uint8_t slot);
void listTreatmentDeleteConfirm(void);
void listTreatmentDeleteCancel(void);
void dcHmiShowTreatmentRecord(uint16_t index, const treatmentLog_t *log);

// ***************************************************************************
// 新建/注册患者(GDDC_PAGE_EDIT_PATIENT / GDDC_PAGE_REGISTER_PATIENT)
void listTreatmentCreateStart(void);
void listTreatmentCreateConfirm(void);
void listTreatmentCreateCancel(void);
void listTreatmentRegisterNewPatient(void);
void listTreatmentRegisterConfirm(void);
void listTreatmentRegisterCancel(void);

// ***************************************************************************
// 发射后核对/丢弃(GDDC_PAGE_VERIFY_TREATMENT / GDDC_PAGE_DISCARD_TREATMENT)
void listTreatmentVerifyAfterLaser(void);
void listTreatmentVerifySaveRecord(void);
void listTreatmentVerifySelect(void);
void listTreatmentVerifySelectCancel(void);
void listTreatmentVerifyDiscard(void);
void listTreatmentDiscardReturn(void);
void listTreatmentDiscardCancel(void);
uint8_t listTreatmentExitReadyVerify(void);

// ***************************************************************************
// 病历记录列表(GDDC_PAGE_LIST_RECORD / GDDC_PAGE_DELETE_RECORD)
void listTreatmentRecordEnter(uint8_t slot);
void refreshListRecordDisplay(void);
void listTreatmentRecordPageKey(uint8_t dir);
void listTreatmentRecordPageUp(void);
void listTreatmentRecordPageDown(void);
void listTreatmentRecordClose(void);
void listTreatmentRecordDeleteKey(uint8_t slot);
void listTreatmentRecordDeleteStart(uint8_t slot);
void listTreatmentDeleteRecordConfirm(void);
void listTreatmentDeleteRecordCancel(void);
void listTreatmentRecordEditPatient(void);
void listTreatmentEditPatientConfirm(void);
void listTreatmentEditPatientCancel(void);
uint8_t listTreatmentIsEditPatientMode(void);
uint8_t listTreatmentIsVerifySelectMode(void);

// ***************************************************************************
// U盘导入导出页(GDDC_PAGE_OPERATOR_USB 系列)
void enterOperatorUsbPage(void);
void listTreatmentOperatorUsbBack(void);
void refreshOperatorUsbDisplay(void);
void listTreatmentSaveUsbStart(void);
void listTreatmentLoadUsbStart(void);
void listTreatmentUsbConfirm(void);
void listTreatmentUsbCancel(void);
void listTreatmentUsbLoop(void);
uint8_t listTreatmentUsbBusy(void);
uint8_t listTreatmentUsbButtonAllowed(uint16_t screen_id, uint16_t control_id);

// ***************************************************************************
// 病历按键锁定/释放
uint8_t treatmentButtonLockAllowed(uint16_t screen, uint16_t control, uint8_t state);
void treatmentReleaseButton(uint16_t screen, uint16_t control);
void treatmentHmiResetLockIfPageMoved(uint16_t screen_id);

// ***************************************************************************
// 跨文件内部刷新入口: 供dcHmiApp.c的屏幕冷加载回调NotifyScreen与待机页刷新调用
void listTreatmentWriteStandbyPatientName(void);
void listTreatmentRenderRegisterDisplay(void);
void listTreatmentRefreshVerifyDisplay(void);
void listTreatmentReleaseVerifyKeys(void);
void listTreatmentRecordEnumerate(void);
void listTreatmentRecordUpdatePageKeys(void);

#ifdef __cplusplus
}
#endif
#endif
