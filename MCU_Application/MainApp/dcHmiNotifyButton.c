// ----------------------------------------------------------------------------
 // 文件编码约定: 本文件为 UTF-8 编码(带BOM)。
 // 本工程源码统一使用 UTF-8(带BOM) 保存: 新建或修改任何源文件时,
 // 请以 UTF-8 编码保存, 并在文件头保留本注释。
 // ----------------------------------------------------------------------------
#include "dcHmiNotifyButton.h"
#include "treatment.h"
#include "minicsvApp.h"//U盘CSV导入导出(治疗记录)
// ***************************************************************************
//诊断页全部按键ID(与GDDC_PAGE_DIAGNOSIS.tft枚举一致), 共19个, 自动填充期间用于整页锁键
static const uint16_t diagnosisKeyList[] = {
  GDDC_PAGE_DIAGNOSIS_KEY_DISABLE_FLOW,         //6
  GDDC_PAGE_DIAGNOSIS_KEY_DISABLE_HUMIDITY,     //7
  GDDC_PAGE_DIAGNOSIS_KEY_ENTER_OK,             //99
  GDDC_PAGE_DIAGNOSIS_KEY_DISABLE_TEMPERATURE,  //300
  GDDC_PAGE_DIAGNOSIS_KEY_DISABLE_FIBER_PROBE,  //301
  GDDC_PAGE_DIAGNOSIS_KEY_DISABLE_RFID,         //302
  GDDC_PAGE_DIAGNOSIS_KEY_DISABLE_ESTOP,        //303
  GDDC_PAGE_DIAGNOSIS_KEY_DISABLE_FOOTSWITCH,   //304
  GDDC_PAGE_DIAGNOSIS_KEY_DISABLE_INTERLOCK,    //305
  GDDC_PAGE_DIAGNOSIS_KEY_DISABLE_AUTO_FAN,     //306
  GDDC_PAGE_DIAGNOSIS_KEY_CALIBRATION,          //307
  GDDC_PAGE_DIAGNOSIS_KEY_SAVE_EPROM,           //308
  GDDC_PAGE_DIAGNOSIS_KEY_CLEAR_EPROM,          //309
  GDDC_PAGE_DIAGNOSIS_KEY_CLEAR_CRC,            //310
  GDDC_PAGE_DIAGNOSIS_KEY_UPDATE_BOOTLOAD_REQ,  //311
  GDDC_PAGE_DIAGNOSIS_KEY_UPDATE_BOOTLOAD_YES,  //312
  GDDC_PAGE_DIAGNOSIS_KEY_UPDATE_BOOTLOAD_NO,   //313
  GDDC_PAGE_DIAGNOSIS_KEY_OPEN_ILOCK,           //314
  GDDC_PAGE_DIAGNOSIS_KEY_RAW_DATE,             //315
  GDDC_PAGE_DIAGNOSIS_KEY_AUTOFILL              //316
};

//诊断页按键锁定: enable=0禁用本页按键(自动填充期间防误触), enable=1恢复
//AUTOFILL(316)自身跳过: 保持可点按状态, 结束后由SetButtonValue复位;
//UPDATE_BOOTLOAD_YES/NO(312/313)页面初始化时默认隐藏且禁用, 恢复时跳过以保持禁用原状
static void diagnosisKeysSetEnable(uint8_t enable) {
  uint16_t i;
  for(i = 0U; i < (uint16_t)(sizeof(diagnosisKeyList) / sizeof(diagnosisKeyList[0])); i++) {
    uint16_t key = diagnosisKeyList[i];
    if(key == GDDC_PAGE_DIAGNOSIS_KEY_AUTOFILL) {
      continue;
    }
    if((enable != 0U) &&
       ((key == GDDC_PAGE_DIAGNOSIS_KEY_UPDATE_BOOTLOAD_YES) ||
        (key == GDDC_PAGE_DIAGNOSIS_KEY_UPDATE_BOOTLOAD_NO))) {
      continue;
    }
    SetControlEnable(GDDC_PAGE_DIAGNOSIS, key, enable);
    softDelayMs(1);
  }
}
// ***************************************************************************
//按钮控件通知当按钮状态改变(或调用GetControlValue)时，执行此函数
//screen_id 画面ID;control_id 控件ID;state 按钮状态：0弹起，1按下
void NotifyButton(uint16_t screen_id, uint16_t control_id, uint8_t state){
  char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
  //按键互锁: 某按键在途(按下到清零)期间, 其他按键一律拒绝
  if(!treatmentButtonLockAllowed(screen_id, control_id, state)){
    return;
  }
  if(!listTreatmentUsbButtonAllowed(screen_id, control_id)){//提示页显示期间屏蔽触摸, 载入确认页只放行"覆盖/取消"
    return;
  }
  //PASSCODE 密码输入页面
  switch(screen_id){
    case GDDC_PAGE_PASSCODE:{//等待密码输入
      dispBuf[4] = 0;
      switch(control_id){
        case GDDC_PAGE_PASSCODE_KEY_NUM1:{//按键1
          if(NVRAM0[EM_DC_PASSCODE_INDEX] == 0){
            NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x0031;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 1;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
            NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x3100;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 2;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
            NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x0031;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 3;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
            NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x3100;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 4;
          }
          *(int16_t*)(dispBuf + 0) = NVRAM0[EM_DC_NEW_PASSCODE0];
          *(int16_t*)(dispBuf + 2) = NVRAM0[EM_DC_NEW_PASSCODE1];
          SetTextValue(screen_id, GDDC_PAGE_PASSCODE_TEXT_CODE, (uint8_t*)(dispBuf));
          break;
        }
        case GDDC_PAGE_PASSCODE_KEY_NUM2:{//按键2
          if(NVRAM0[EM_DC_PASSCODE_INDEX] == 0){
            NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x0032;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 1;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
            NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x3200;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 2;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
            NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x0032;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 3;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
            NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x3200;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 4;
          }
          *(int16_t*)(dispBuf + 0) = NVRAM0[EM_DC_NEW_PASSCODE0];
          *(int16_t*)(dispBuf + 2) = NVRAM0[EM_DC_NEW_PASSCODE1];
          SetTextValue(screen_id, GDDC_PAGE_PASSCODE_TEXT_CODE, (uint8_t*)(dispBuf));
          break;
        }
        case GDDC_PAGE_PASSCODE_KEY_NUM3:{//按键3
          if(NVRAM0[EM_DC_PASSCODE_INDEX] == 0){
            NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x0033;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 1;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
            NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x3300;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 2;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
            NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x0033;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 3;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
            NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x3300;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 4;
          }
          *(int16_t*)(dispBuf + 0) = NVRAM0[EM_DC_NEW_PASSCODE0];
          *(int16_t*)(dispBuf + 2) = NVRAM0[EM_DC_NEW_PASSCODE1];
          dispBuf[4] = 0x0;
          SetTextValue(screen_id, GDDC_PAGE_PASSCODE_TEXT_CODE, (uint8_t*)(dispBuf));
          break;
        }
        case GDDC_PAGE_PASSCODE_KEY_NUM4:{//按键4
          if(NVRAM0[EM_DC_PASSCODE_INDEX] == 0){
            NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x0034;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 1;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
            NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x3400;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 2;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
            NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x0034;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 3;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
            NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x3400;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 4;
          }
          *(int16_t*)(dispBuf + 0) = NVRAM0[EM_DC_NEW_PASSCODE0];
          *(int16_t*)(dispBuf + 2) = NVRAM0[EM_DC_NEW_PASSCODE1];
          SetTextValue(screen_id, GDDC_PAGE_PASSCODE_TEXT_CODE, (uint8_t*)(dispBuf));
          break;
        }
        case GDDC_PAGE_PASSCODE_KEY_NUM5:{//按键5
          if(NVRAM0[EM_DC_PASSCODE_INDEX] == 0){
            NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x0035;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 1;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
            NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x3500;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 2;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
            NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x0035;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 3;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
            NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x3500;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 4;
          }
          *(int16_t*)(dispBuf + 0) = NVRAM0[EM_DC_NEW_PASSCODE0];
          *(int16_t*)(dispBuf + 2) = NVRAM0[EM_DC_NEW_PASSCODE1];
          SetTextValue(screen_id, GDDC_PAGE_PASSCODE_TEXT_CODE, (uint8_t*)(dispBuf));
          break;
        }
        case GDDC_PAGE_PASSCODE_KEY_NUM6:{//按键6
          if(NVRAM0[EM_DC_PASSCODE_INDEX] == 0){
            NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x0036;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 1;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
            NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x3600;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 2;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
            NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x0036;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 3;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
            NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x3600;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 4;
          }
          *(int16_t*)(dispBuf + 0) = NVRAM0[EM_DC_NEW_PASSCODE0];
          *(int16_t*)(dispBuf + 2) = NVRAM0[EM_DC_NEW_PASSCODE1];
          SetTextValue(screen_id, GDDC_PAGE_PASSCODE_TEXT_CODE, (uint8_t*)(dispBuf));
          break;
        }
        case GDDC_PAGE_PASSCODE_KEY_NUM7:{//按键7
          if(NVRAM0[EM_DC_PASSCODE_INDEX] == 0){
            NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x0037;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 1;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
            NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x3700;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 2;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
            NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x0037;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 3;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
            NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x3700;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 4;
          }
          *(int16_t*)(dispBuf + 0) = NVRAM0[EM_DC_NEW_PASSCODE0];
          *(int16_t*)(dispBuf + 2) = NVRAM0[EM_DC_NEW_PASSCODE1];
          SetTextValue(screen_id, GDDC_PAGE_PASSCODE_TEXT_CODE, (uint8_t*)(dispBuf));
          break;
        }
        case GDDC_PAGE_PASSCODE_KEY_NUM8:{//按键8
            if(NVRAM0[EM_DC_PASSCODE_INDEX] == 0){
            NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x0038;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 1;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
            NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x3800;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 2;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
            NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x0038;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 3;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
            NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x3800;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 4;
          }
          *(int16_t*)(dispBuf + 0) = NVRAM0[EM_DC_NEW_PASSCODE0];
          *(int16_t*)(dispBuf + 2) = NVRAM0[EM_DC_NEW_PASSCODE1];
          SetTextValue(screen_id, GDDC_PAGE_PASSCODE_TEXT_CODE, (uint8_t*)(dispBuf));
          break;
        }
        case GDDC_PAGE_PASSCODE_KEY_NUM9:{//按键9
          if(NVRAM0[EM_DC_PASSCODE_INDEX] == 0){
            NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x0039;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 1;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
            NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x3900;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 2;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
            NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x0039;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 3;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
            NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x3900;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 4;
          }
          *(int16_t*)(dispBuf + 0) = NVRAM0[EM_DC_NEW_PASSCODE0];
          *(int16_t*)(dispBuf + 2) = NVRAM0[EM_DC_NEW_PASSCODE1];
          dispBuf[4] = 0x0;
          SetTextValue(screen_id, GDDC_PAGE_PASSCODE_TEXT_CODE, (uint8_t*)(dispBuf));
          break;
        }
        case GDDC_PAGE_PASSCODE_KEY_NUM0:{//按键0
          if(NVRAM0[EM_DC_PASSCODE_INDEX] == 0){
            NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x0030;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 1;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
            NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x3000;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 2;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
            NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x0030;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 3;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
            NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x3000;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 4;
          }
          *(int16_t*)(dispBuf + 0) = NVRAM0[EM_DC_NEW_PASSCODE0];
          *(int16_t*)(dispBuf + 2) = NVRAM0[EM_DC_NEW_PASSCODE1];
          SetTextValue(screen_id, GDDC_PAGE_PASSCODE_TEXT_CODE, (uint8_t*)(dispBuf));
          break;
        }
        case GDDC_PAGE_PASSCODE_KEY_CANCEL:{//按键CANCEL
          CLR(EM_DC_NEW_PASSCODE0);//清空已输入密码
          CLR(EM_DC_NEW_PASSCODE1);
          CLR(EM_DC_PASSCODE_INDEX);//清空密码显示位索引
          NVRAM0[EM_DC_PAGE] = GDDC_PAGE_PASSCODE;
          SetTextValue(screen_id, GDDC_PAGE_PASSCODE_TEXT_CODE, (uint8_t*)(dispBuf));
          break;
        }
        case GDDC_PAGE_PASSCODE_KEY_BACKSPACE:{//按键BACKSPACE
          if(NVRAM0[EM_DC_PASSCODE_INDEX] == 4){
            NVRAM0[EM_DC_NEW_PASSCODE1] &= 0x00FF;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 0x3;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
            NVRAM0[EM_DC_NEW_PASSCODE1] &= 0xFF00;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 0x2;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
            NVRAM0[EM_DC_NEW_PASSCODE0] &= 0x00FF;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 0x1;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
            NVRAM0[EM_DC_NEW_PASSCODE0] &= 0xFF00;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 0x0;
          }
          *(int16_t*)(dispBuf + 0) = NVRAM0[EM_DC_NEW_PASSCODE0];
          *(int16_t*)(dispBuf + 2) = NVRAM0[EM_DC_NEW_PASSCODE1];
          SetTextValue(screen_id, GDDC_PAGE_PASSCODE_TEXT_CODE, (uint8_t*)(dispBuf));
          break;
        }
        case GDDC_PAGE_PASSCODE_KEY_CHANGEPASSCODE:{//按键CHANGEPASSCODE
          if((NVRAM0[EM_DC_NEW_PASSCODE0] == NVRAM0[DM_DC_OLD_PASSCODE0]) && (NVRAM0[EM_DC_NEW_PASSCODE1] == NVRAM0[DM_DC_OLD_PASSCODE1])){
            NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_PASSCODE_NEW0;
            NVRAM0[EM_DC_PAGE] = GDDC_PAGE_NEW_PASSCODE;
            SetScreen(NVRAM0[EM_DC_PAGE]);
          }
          else if((NVRAM0[EM_DC_NEW_PASSCODE0] == CONFIG_HMI_ADMIN_PASSWORD0) && (NVRAM0[EM_DC_NEW_PASSCODE1] == CONFIG_HMI_ADMIN_PASSWORD1)){
            NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_PASSCODE_NEW0;
            NVRAM0[EM_DC_PAGE] = GDDC_PAGE_NEW_PASSCODE;
            SetScreen(NVRAM0[EM_DC_PAGE]);
          }
          CLR(EM_DC_NEW_PASSCODE0);//清空已输入密码
          CLR(EM_DC_NEW_PASSCODE1);
          CLR(EM_DC_PASSCODE_INDEX);//清空密码显示位索引
          *(int16_t*)(dispBuf + 0) = NVRAM0[EM_DC_NEW_PASSCODE0];
          *(int16_t*)(dispBuf + 2) = NVRAM0[EM_DC_NEW_PASSCODE1];
          dispBuf[4] = 0x0;
          SetTextValue(screen_id, GDDC_PAGE_PASSCODE_TEXT_CODE, (uint8_t*)(dispBuf));
          break;
        }
        case GDDC_PAGE_PASSCODE_KEY_ENTER:{//按键ENTER
          if((NVRAM0[EM_DC_NEW_PASSCODE0] == CONFIG_HMI_ADMIN_PASSWORD0) && (NVRAM0[EM_DC_NEW_PASSCODE1] == CONFIG_HMI_ADMIN_PASSWORD1)){
            NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_STANDBY;
            SSET(R_ENGINEER_MODE);
            standbyDebugInfoVisiable(true);
            emulatorFswApplyMode();//工程模式: 仿真脚踏可见并使能
          }else if((NVRAM0[EM_DC_NEW_PASSCODE0] == NVRAM0[DM_DC_OLD_PASSCODE0]) && (NVRAM0[EM_DC_NEW_PASSCODE1] == NVRAM0[DM_DC_OLD_PASSCODE1])){
            NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_STANDBY;
            RRES(R_ENGINEER_MODE);
            standbyDebugInfoVisiable(false);
            emulatorFswApplyMode();//正常模式: 仿真脚踏隐藏禁用并清零
          }
          else{
            break;
          }
          CLR(EM_DC_NEW_PASSCODE0);//清空已输入密码
          CLR(EM_DC_NEW_PASSCODE1);
          CLR(EM_DC_PASSCODE_INDEX);//清空密码显示位索引
          *(int16_t*)(dispBuf + 0) = NVRAM0[EM_DC_NEW_PASSCODE0];
          *(int16_t*)(dispBuf + 2) = NVRAM0[EM_DC_NEW_PASSCODE1];
          dispBuf[4] = 0x0;

          SetButtonValue( GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH0, false);
          SetControlVisiable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH0, true);
          SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH0, true);
          
          SetButtonValue( GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH1, false);
          SetControlVisiable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH1, true);
          SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH1, true);

          SetButtonValue( GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH2, false);
          SetControlVisiable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH2, true);
          SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH2, true);

          NVRAM0[EM_DC_PAGE] = GDDC_PAGE_STANDBY;//切换待机页面
          SetTextValue(screen_id, GDDC_PAGE_PASSCODE_TEXT_CODE, (uint8_t*)(dispBuf));
                    
          updateStandbyDisplay();
          SetScreen(NVRAM0[EM_DC_PAGE]);
          break;
        }
        default:break;
      }
      break;
    }
    case GDDC_PAGE_NEW_PASSCODE:{//新密码输入页面
      dispBuf[4] = 0x0;
      switch(control_id){
        case GDDC_PAGE_NEW_PASSCODE_KEY_NUM1:{//按键1
          if(NVRAM0[EM_DC_PASSCODE_INDEX] == 0){
            NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x0031;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 1;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
            NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x3100;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 2;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
            NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x0031;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 3;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
            NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x3100;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 4;
          }
          *(int16_t*)(dispBuf + 0) = NVRAM0[EM_DC_NEW_PASSCODE0];
          *(int16_t*)(dispBuf + 2) = NVRAM0[EM_DC_NEW_PASSCODE1];
          SetTextValue(screen_id, GDDC_PAGE_PASSCODE_TEXT_CODE, (uint8_t*)(dispBuf));
          break;
        }
        case GDDC_PAGE_NEW_PASSCODE_KEY_NUM2:{//按键2
          if(NVRAM0[EM_DC_PASSCODE_INDEX] == 0){
            NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x0032;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 1;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
            NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x3200;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 2;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
            NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x0032;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 3;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
            NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x3200;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 4;
          }
          *(int16_t*)(dispBuf + 0) = NVRAM0[EM_DC_NEW_PASSCODE0];
          *(int16_t*)(dispBuf + 2) = NVRAM0[EM_DC_NEW_PASSCODE1];
          SetTextValue(screen_id, GDDC_PAGE_PASSCODE_TEXT_CODE, (uint8_t*)(dispBuf));
          break;
        }
        case GDDC_PAGE_NEW_PASSCODE_KEY_NUM3:{//按键3
          if(NVRAM0[EM_DC_PASSCODE_INDEX] == 0){
            NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x0033;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 1;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
            NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x3300;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 2;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
            NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x0033;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 3;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
            NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x3300;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 4;
          }
          *(int16_t*)(dispBuf + 0) = NVRAM0[EM_DC_NEW_PASSCODE0];
          *(int16_t*)(dispBuf + 2) = NVRAM0[EM_DC_NEW_PASSCODE1];
          SetTextValue(screen_id, GDDC_PAGE_PASSCODE_TEXT_CODE, (uint8_t*)(dispBuf));
          break;
        }
        case GDDC_PAGE_NEW_PASSCODE_KEY_NUM4:{//按键4
          if(NVRAM0[EM_DC_PASSCODE_INDEX] == 0){
            NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x0034;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 1;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
            NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x3400;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 2;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
            NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x0034;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 3;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
            NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x3400;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 4;
          }
          *(int16_t*)(dispBuf + 0) = NVRAM0[EM_DC_NEW_PASSCODE0];
          *(int16_t*)(dispBuf + 2) = NVRAM0[EM_DC_NEW_PASSCODE1];
          SetTextValue(screen_id, GDDC_PAGE_PASSCODE_TEXT_CODE, (uint8_t*)(dispBuf));
          break;
        }
        case GDDC_PAGE_NEW_PASSCODE_KEY_NUM5:{//按键5
          if(NVRAM0[EM_DC_PASSCODE_INDEX] == 0){
            NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x0035;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 1;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
            NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x3500;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 2;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
            NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x0035;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 3;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
            NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x3500;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 4;
          }
          *(int16_t*)(dispBuf + 0) = NVRAM0[EM_DC_NEW_PASSCODE0];
          *(int16_t*)(dispBuf + 2) = NVRAM0[EM_DC_NEW_PASSCODE1];
          SetTextValue(screen_id, GDDC_PAGE_PASSCODE_TEXT_CODE, (uint8_t*)(dispBuf));
          break;
        }
        case GDDC_PAGE_NEW_PASSCODE_KEY_NUM6:{//按键6
          if(NVRAM0[EM_DC_PASSCODE_INDEX] == 0){
            NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x0036;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 1;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
            NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x3600;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 2;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
            NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x0036;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 3;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
            NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x3600;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 4;
          }
          *(int16_t*)(dispBuf + 0) = NVRAM0[EM_DC_NEW_PASSCODE0];
          *(int16_t*)(dispBuf + 2) = NVRAM0[EM_DC_NEW_PASSCODE1];
          SetTextValue(screen_id, GDDC_PAGE_PASSCODE_TEXT_CODE, (uint8_t*)(dispBuf));
          break;
        }
        case GDDC_PAGE_NEW_PASSCODE_KEY_NUM7:{//按键7
          if(NVRAM0[EM_DC_PASSCODE_INDEX] == 0){
            NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x0037;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 1;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
            NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x3700;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 2;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
            NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x0037;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 3;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
            NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x3700;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 4;
          }
          *(int16_t*)(dispBuf + 0) = NVRAM0[EM_DC_NEW_PASSCODE0];
          *(int16_t*)(dispBuf + 2) = NVRAM0[EM_DC_NEW_PASSCODE1];
          SetTextValue(screen_id, GDDC_PAGE_PASSCODE_TEXT_CODE, (uint8_t*)(dispBuf));
          break;
        }
        case GDDC_PAGE_NEW_PASSCODE_KEY_NUM8:{//按键8
          if(NVRAM0[EM_DC_PASSCODE_INDEX] == 0){
            NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x0038;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 1;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
            NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x3800;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 2;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
            NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x0038;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 3;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
            NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x3800;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 4;
          }
          *(int16_t*)(dispBuf + 0) = NVRAM0[EM_DC_NEW_PASSCODE0];
          *(int16_t*)(dispBuf + 2) = NVRAM0[EM_DC_NEW_PASSCODE1];
          SetTextValue(screen_id, GDDC_PAGE_PASSCODE_TEXT_CODE, (uint8_t*)(dispBuf));
          break;
        }
        case GDDC_PAGE_NEW_PASSCODE_KEY_NUM9:{//按键9
          if(NVRAM0[EM_DC_PASSCODE_INDEX] == 0){
            NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x0039;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 1;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
            NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x3900;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 2;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
            NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x0039;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 3;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
            NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x3900;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 4;
          }
          *(int16_t*)(dispBuf + 0) = NVRAM0[EM_DC_NEW_PASSCODE0];
          *(int16_t*)(dispBuf + 2) = NVRAM0[EM_DC_NEW_PASSCODE1];
          SetTextValue(screen_id, GDDC_PAGE_PASSCODE_TEXT_CODE, (uint8_t*)(dispBuf));
          break;
        }
        case GDDC_PAGE_NEW_PASSCODE_KEY_NUM0:{//按键0
          if(NVRAM0[EM_DC_PASSCODE_INDEX] == 0){
            NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x0030;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 1;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
            NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x3000;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 2;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
            NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x0030;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 3;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
            NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x3000;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 4;
          }
          *(int16_t*)(dispBuf + 0) = NVRAM0[EM_DC_NEW_PASSCODE0];
          *(int16_t*)(dispBuf + 2) = NVRAM0[EM_DC_NEW_PASSCODE1];
          SetTextValue(screen_id, GDDC_PAGE_PASSCODE_TEXT_CODE, (uint8_t*)(dispBuf));
          break;
        }
        case GDDC_PAGE_NEW_PASSCODE_KEY_CANCEL:{
          CLR(EM_DC_NEW_PASSCODE0);
          CLR(EM_DC_NEW_PASSCODE1);
          CLR(EM_DC_PASSCODE_INDEX);//清空密码显示位索引
          *(int16_t*)(dispBuf + 0) = NVRAM0[EM_DC_NEW_PASSCODE0];
          *(int16_t*)(dispBuf + 2) = NVRAM0[EM_DC_NEW_PASSCODE1];
          SetTextValue(screen_id, GDDC_PAGE_PASSCODE_TEXT_CODE, (uint8_t*)(dispBuf));
          break;
        }
        case GDDC_PAGE_NEW_PASSCODE_KEY_BACKSPACE:{
          if(NVRAM0[EM_DC_PASSCODE_INDEX] == 4){
            NVRAM0[EM_DC_NEW_PASSCODE1] &= 0x00FF;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 0x3;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
            NVRAM0[EM_DC_NEW_PASSCODE1] &= 0xFF00;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 0x2;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
            NVRAM0[EM_DC_NEW_PASSCODE0] &= 0x00FF;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 0x1;
          }
          else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
            NVRAM0[EM_DC_NEW_PASSCODE0] &= 0xFF00;
            NVRAM0[EM_DC_PASSCODE_INDEX] = 0x0;
          }
          *(int16_t*)(dispBuf + 0) = NVRAM0[EM_DC_NEW_PASSCODE0];
          *(int16_t*)(dispBuf + 2) = NVRAM0[EM_DC_NEW_PASSCODE1];
          SetTextValue(screen_id, GDDC_PAGE_PASSCODE_TEXT_CODE, (uint8_t*)(dispBuf));
          break;
        }
        case GDDC_PAGE_NEW_PASSCODE_KEY_SAVE:{
          if((NVRAM0[EM_DC_PASSCODE_INDEX] >= 4) && (NVRAM0[EM_DC_NEW_PASSCODE0] != 0x0000) && (NVRAM0[EM_DC_NEW_PASSCODE0] != 0x0000)){
            NVRAM0[DM_DC_OLD_PASSCODE0] = NVRAM0[EM_DC_NEW_PASSCODE0];
            NVRAM0[DM_DC_OLD_PASSCODE1] = NVRAM0[EM_DC_NEW_PASSCODE1];
            NVSAVE();
            CLR(EM_DC_PASSCODE_INDEX);//清空密码显示位索引
            CLR(EM_DC_NEW_PASSCODE0);
            CLR(EM_DC_NEW_PASSCODE1);
            NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_PASSCODE_INPUT;
            NVRAM0[EM_DC_PAGE] = GDDC_PAGE_PASSCODE;
            SetScreen(NVRAM0[EM_DC_PAGE]);
          }
          else{
            CLR(EM_DC_PASSCODE_INDEX);//清空密码显示位索引
            CLR(EM_DC_NEW_PASSCODE0);
            CLR(EM_DC_NEW_PASSCODE1);
            NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_PASSCODE_NEW0;
            NVRAM0[EM_DC_PAGE] = GDDC_PAGE_NEW_PASSCODE;
          }
          *(int16_t*)(dispBuf + 0) = NVRAM0[EM_DC_NEW_PASSCODE0];
          *(int16_t*)(dispBuf + 2) = NVRAM0[EM_DC_NEW_PASSCODE1];
          SetTextValue(screen_id, GDDC_PAGE_PASSCODE_TEXT_CODE, (uint8_t*)(dispBuf));
          break;
        }
        case GDDC_PAGE_NEW_PASSCODE_KEY_BACK:{//放弃新密码修改
          CLR(EM_DC_NEW_PASSCODE0);
          CLR(EM_DC_NEW_PASSCODE1);
          CLR(EM_DC_PASSCODE_INDEX);//清空密码显示位索引
          NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_PASSCODE_INPUT;
          *(int16_t*)(dispBuf + 0) = NVRAM0[EM_DC_NEW_PASSCODE0];
          *(int16_t*)(dispBuf + 2) = NVRAM0[EM_DC_NEW_PASSCODE1];
          SetTextValue(screen_id, GDDC_PAGE_PASSCODE_TEXT_CODE, (uint8_t*)(dispBuf));
          NVRAM0[EM_DC_PAGE] = GDDC_PAGE_PASSCODE;
          SetScreen(NVRAM0[EM_DC_PAGE]);
          break;
        }
        default:break;
      }
      break;
    }
    case GDDC_PAGE_STANDBY:{//主界面STANDBY CW
      switch(control_id){
        case GDDC_PAGE_STANDBY_KEY_POWER_SEL_ADD:{
          if(state){
            if(NVRAM0[EM_LASER_CHANNEL_SELECT] == LASER_CHANNEL_CH0){//选中1470nm
              if(NVRAM0[EM_LASER_POWER_CH0] < CONFIG_MAX_LASER_POWER_CH0){
                ADDS1(EM_LASER_POWER_CH0);
              }
            }
            if(NVRAM0[EM_LASER_CHANNEL_SELECT] == LASER_CHANNEL_CH1){//选中980nm
              if(NVRAM0[EM_LASER_POWER_CH1] < CONFIG_MAX_LASER_POWER_CH1){
                ADDS1(EM_LASER_POWER_CH1);
              }
            }
            if(NVRAM0[EM_LASER_CHANNEL_SELECT] == LASER_CHANNEL_CH2){//选中635nm
              if(NVRAM0[EM_LASER_POWER_CH2] < CONFIG_MAX_LASER_POWER_CH2){
                ADDS1(EM_LASER_POWER_CH2);
              }
            }
            NVRAM0[EM_LASER_POWER_TOTAL] = NVRAM0[EM_LASER_POWER_CH0] + NVRAM0[EM_LASER_POWER_CH1] + NVRAM0[EM_LASER_POWER_CH2];
            updateStandbyDisplay();
          }
          break;
        }
        case GDDC_PAGE_STANDBY_KEY_POWER_SEL_INC:{
          if(state){

            if(NVRAM0[EM_LASER_CHANNEL_SELECT] == LASER_CHANNEL_CH0){//选中1470nm
              if(NVRAM0[EM_LASER_POWER_CH0] > CONFIG_MIN_LASER_POWER_CH0){
                DECS1(EM_LASER_POWER_CH0);
              }
            }

            if(NVRAM0[EM_LASER_CHANNEL_SELECT] == LASER_CHANNEL_CH1){//选中980nm
              if(NVRAM0[EM_LASER_POWER_CH1] > CONFIG_MIN_LASER_POWER_CH1){
                DECS1(EM_LASER_POWER_CH1);
              }
            }
            if(NVRAM0[EM_LASER_CHANNEL_SELECT] == LASER_CHANNEL_CH2){//选中635nm
              if(NVRAM0[EM_LASER_POWER_CH2] > CONFIG_MIN_LASER_POWER_CH2){
                DECS1(EM_LASER_POWER_CH2);
              }
            }
            NVRAM0[EM_LASER_POWER_TOTAL] = NVRAM0[EM_LASER_POWER_CH0] + NVRAM0[EM_LASER_POWER_CH1] + NVRAM0[EM_LASER_POWER_CH2];
            updateStandbyDisplay();
          }
          break;
        }
        case GDDC_PAGE_STANDBY_KEY_SELECT_CH0:{
          if(state){
            NVRAM0[EM_LASER_CHANNEL_SELECT] = LASER_CHANNEL_CH0;
            updateStandbyDisplay();
          }
          break;
        }
        case GDDC_PAGE_STANDBY_KEY_SELECT_CH1:{
          if(state){
            NVRAM0[EM_LASER_CHANNEL_SELECT] = LASER_CHANNEL_CH1;
            updateStandbyDisplay();
          }
          break;
        }
        case GDDC_PAGE_STANDBY_KEY_SELECT_CH2:{
          if(state){
            NVRAM0[EM_LASER_CHANNEL_SELECT] = LASER_CHANNEL_CH2;
            updateStandbyDisplay();
          }
          break;
        }
        case GDDC_PAGE_STANDBY_KEY_POWER_CH0_ADD:{
          if(state){
            if(NVRAM0[EM_LASER_POWER_CH0] < CONFIG_MAX_LASER_POWER_CH0){
              ADDS1(EM_LASER_POWER_CH0);
              NVRAM0[EM_LASER_POWER_TOTAL] = NVRAM0[EM_LASER_POWER_CH0] + NVRAM0[EM_LASER_POWER_CH1] + NVRAM0[EM_LASER_POWER_CH2];
              updateStandbyDisplay();
            }
          }
          break;
        }
        case GDDC_PAGE_STANDBY_KEY_POWER_CH0_INC:{
          if(state){
            if(NVRAM0[EM_LASER_POWER_CH0] > CONFIG_MIN_LASER_POWER_CH0){
              DECS1(EM_LASER_POWER_CH0);
              NVRAM0[EM_LASER_POWER_TOTAL] = NVRAM0[EM_LASER_POWER_CH0] + NVRAM0[EM_LASER_POWER_CH1] + NVRAM0[EM_LASER_POWER_CH2];
              updateStandbyDisplay();
            }
          }
          break;
        }
        case GDDC_PAGE_STANDBY_KEY_POWER_CH1_ADD:{
          if(state){
            if(NVRAM0[EM_LASER_POWER_CH1] < CONFIG_MAX_LASER_POWER_CH1){
              ADDS1(EM_LASER_POWER_CH1);
              NVRAM0[EM_LASER_POWER_TOTAL] = NVRAM0[EM_LASER_POWER_CH0] + NVRAM0[EM_LASER_POWER_CH1] + NVRAM0[EM_LASER_POWER_CH2];
              updateStandbyDisplay();
            }
          }
          break;
        }
        case GDDC_PAGE_STANDBY_KEY_POWER_CH1_INC:{
          if(state){
            if(NVRAM0[EM_LASER_POWER_CH1] > CONFIG_MIN_LASER_POWER_CH1){
              DECS1(EM_LASER_POWER_CH1);
              NVRAM0[EM_LASER_POWER_TOTAL] = NVRAM0[EM_LASER_POWER_CH0] + NVRAM0[EM_LASER_POWER_CH1] + NVRAM0[EM_LASER_POWER_CH2];
              updateStandbyDisplay();
            }
          }
          break;
        }
        case GDDC_PAGE_STANDBY_KEY_POWER_CH2_ADD:{
          if(state){
            if(NVRAM0[EM_LASER_POWER_CH2] < CONFIG_MIN_LASER_POWER_CH2){
              ADDS1(EM_LASER_POWER_CH2);
              NVRAM0[EM_LASER_POWER_TOTAL] = NVRAM0[EM_LASER_POWER_CH0] + NVRAM0[EM_LASER_POWER_CH1] + NVRAM0[EM_LASER_POWER_CH2];
              updateStandbyDisplay();
            }
          }
          break;
        }
        case GDDC_PAGE_STANDBY_KEY_POWER_CH2_INC:{
          if(state){
            if(NVRAM0[EM_LASER_POWER_CH2] > CONFIG_MIN_LASER_POWER_CH2){
              DECS1(EM_LASER_POWER_CH2);
              NVRAM0[EM_LASER_POWER_TOTAL] = NVRAM0[EM_LASER_POWER_CH0] + NVRAM0[EM_LASER_POWER_CH1] + NVRAM0[EM_LASER_POWER_CH2];
              updateStandbyDisplay();
            }
          }
          break;
        }
        case GDDC_PAGE_STANDBY_KEY_POWER_AIM_ADD:{
          if(state){
            if(NVRAM0[DM_RAIM_BRG] < CONFIG_MAX_LASER_POWER_RAIM){
              ADDS1(DM_RAIM_BRG);
              updateStandbyDisplay();
            }
          }
          break;
        }
        case GDDC_PAGE_STANDBY_KEY_POWER_AIM_INC:{
          if(state){
            if(NVRAM0[DM_RAIM_BRG] > CONFIG_MIN_LASER_POWER_RAIM){
              DECS1(DM_RAIM_BRG);
              updateStandbyDisplay();
            }
          }
          break;
        }
        case GDDC_PAGE_STANDBY_KEY_POSWIDTH_ADD:{
          if(state){//DOWN
            SSET(R_STANDBY_KEY_POSWIDTH_ADD_DOWN);
          }
          else{
            SSET(R_STANDBY_KEY_POSWIDTH_ADD_UP);
          }
          break;
        }
        case GDDC_PAGE_STANDBY_KEY_POSWIDTH_INC:{
          if(state){//DOWN
            SSET(R_STANDBY_KEY_POSWIDTH_DEC_DOWN);
          }
          else{
            SSET(R_STANDBY_KEY_POSWIDTH_DEC_UP);
          }
          break;
        }
        case GDDC_PAGE_STANDBY_KEY_NEGWIDTH_ADD:{
          if(state){//DOWN
            SSET(R_STANDBY_KEY_NEGWIDTH_ADD_DOWN);
          }
          else{
            SSET(R_STANDBY_KEY_NEGWIDTH_ADD_UP);
          }
          break;
        }
        case GDDC_PAGE_STANDBY_KEY_NEGWIDTH_INC:{
          if(state){//DOWN
            SSET(R_STANDBY_KEY_NEGWIDTH_DEC_DOWN);
          }
          else{
            SSET(R_STANDBY_KEY_NEGWIDTH_DEC_UP);
          }
          break;
        }
        case GDDC_PAGE_STANDBY_KEY_SCHEME_SAVE:{
          if(state){
            if (NVRAM0[DM_SCHEME_CLASSIFY] == SCHEME_CUSTIOM){
              updateCustomScheme(NVRAM0[DM_SCHEME_INDEX]);//EM->FD
              if(NVRAM0[DM_SCHEME_INDEX] <= (CONFIG_HMI_SCHEME_NUM - 1)){
                FDSAV_ONE(NVRAM0[DM_SCHEME_INDEX]);//FDRAM->EPROM
              }
            }
          }
          break;
        }
        case GDDC_PAGE_STANDBY_KEY_SCHEME_LAST:{//选择上一个方案
          if(state){
            SSET(R_STANDBY_KEY_SCHEME_LAST_DOWN);
          }
          break;
        }
        case GDDC_PAGE_STANDBY_KEY_SCHEME_NEXT:{//选择下一个方案
          if(state){
            SSET(R_STANDBY_KEY_SCHEME_NEXT_DOWN);
          }
          break;
        }
        case GDDC_PAGE_STANDBY_KEY_STANDBY:{
          if(state){
            SSET(R_STANDBY_KEY_STNADBY_DOWN);
          }
          break;
        }
        case GDDC_PAGE_STANDBY_KEY_MODE_CW:{
          if(state){
            NVRAM0[EM_LASER_PULSE_MODE] = LASER_MODE_CW;
            //隐藏MP模式按键
            updateExtralDisplay();
            updateStandbyDisplay();
          }
          break;
        }
        case GDDC_PAGE_STANDBY_KEY_MODE_MP:{
          if(state){
            NVRAM0[EM_LASER_PULSE_MODE] = LASER_MODE_MP;
            //显示MP模式按键
            updatePosWidthDisplay();
            updateNegWidthDisplay();
            updateExtralDisplay();
            updateStandbyDisplay();
          }
          break;
        }
        case GDDC_PAGE_STANDBY_KEY_ENTER_OPTION:{
          if(state){
            SSET(R_STANDBY_KEY_ENTER_OPTION_DOWN);
          }
          break;
        }
        case GDDC_PAGE_STANDBY_KEY_ENTER_SCHEME:{//按键SCHEME
          if(state){
            NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_SCHEME;
#if defined(APP_CONFIG_WAVE_1470_635)
            NVRAM0[EM_DC_PAGE] = GDDC_PAGE_SCHEME_CLASSIFY_DUAL;
            SetScreen(NVRAM0[EM_DC_PAGE]);
#endif

#if defined(APP_CONFIG_WAVE_1470_980_635)
            NVRAM0[EM_DC_PAGE] = GDDC_PAGE_SCHEME_CLASSIFY_TRI;
            SetScreen(NVRAM0[EM_DC_PAGE]);
#endif

#if defined(APP_CONFIG_WAVE_1940_635)
          memcpy((char*)FDRAM1, (char*)FDRAM0, (CONFIG_FDRAM_SIZE * 2));
          NVRAM0[EM_SCHEME_CLASSIFY_TMP] = SCHEME_CUSTIOM;
          NVRAM0[EM_SCHEME_NUM_TMP] = NVRAM0[DM_SCHEME_INDEX];
          NVRAM0[EM_DC_PAGE] = GDDC_PAGE_SCHEME_DETAIL;
          updateSchemeDetail(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
          seletcSchemeNum(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
          SetScreen(NVRAM0[EM_DC_PAGE]);
#endif

#if defined(APP_CONFIG_WAVE_450_980)
          memcpy((char*)FDRAM1, (char*)FDRAM0, (CONFIG_FDRAM_SIZE * 2));
          NVRAM0[EM_SCHEME_CLASSIFY_TMP] = SCHEME_CUSTIOM;
          NVRAM0[EM_SCHEME_NUM_TMP] = NVRAM0[DM_SCHEME_INDEX];
          NVRAM0[EM_DC_PAGE] = GDDC_PAGE_SCHEME_DETAIL;
          updateSchemeDetail(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
          seletcSchemeNum(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
          SetScreen(NVRAM0[EM_DC_PAGE]);
#endif

#if defined(APP_CONFIG_WAVE_1940_1470_635)
          NVRAM0[EM_DC_PAGE] = GDDC_PAGE_SCHEME_CLASSIFY_DUAL;
          SetScreen(NVRAM0[EM_DC_PAGE]);
#endif
          }
          break;
        }
        case GDDC_PAGE_STANDBY_KEY_ENTER_TREATMENT:{
          if(state){
            SSET(R_STANDBY_KEY_ENTER_LIST_TREATMENT_DOWN);
          }
          break;
        }
        default:break;
      }
      break;
    }

    case GDDC_PAGE_LIST_TREATMENT:{//显示病历列表
      switch(control_id){
        case GDDC_PAGE_LIST_TREATMENT_KEY_PAGE_UP:{//向前翻一整页: 动作期禁用+去抖, 清零/使能/解锁由延迟释放轮询在手指抬起后处理
          if(state){
            listTreatmentPageKey(0U);
          }
          break;
        }
        case GDDC_PAGE_LIST_TREATMENT_KEY_PAGE_DOWN:{//向后翻一整页: 动作期禁用+去抖, 清零/使能/解锁由延迟释放轮询在手指抬起后处理
          if(state){
            listTreatmentPageKey(1U);
          }
          break;
        }
        case GDDC_PAGE_LIST_TREATMENT_KEY_CLOSE:{//返回STANDBY状态
          if(state){
            if(listTreatmentIsVerifySelectMode()){//核对选择模式: 不回待机, 回核对页
              listTreatmentVerifySelectCancel();
            }
            else{
              returnStandbyDisplay();//统一返回待机页面
            }
            treatmentReleaseButton(GDDC_PAGE_LIST_TREATMENT, GDDC_PAGE_LIST_TREATMENT_KEY_CLOSE);//切页后释放源按键
          }
          break;
        }
        case GDDC_PAGE_LIST_TREATMENT_KEY_CREATE_NEW:{//手动新建患者: 直接进入注册页(不要求本次发射激光)
          if(state){
            listTreatmentRegisterNewPatient();
            treatmentReleaseButton(GDDC_PAGE_LIST_TREATMENT, GDDC_PAGE_LIST_TREATMENT_KEY_CREATE_NEW);//复位自锁按钮并解除互锁
          }
          break;
        }
        case GDDC_PAGE_LIST_TREATMENT_KEY_OPERATOR_USB:{//操作USB: 进入USB导入导出操作页
          if(state){
            treatmentReleaseButton(GDDC_PAGE_LIST_TREATMENT, GDDC_PAGE_LIST_TREATMENT_KEY_OPERATOR_USB);//先释放再切页: 当前页仍在时下发清零
            enterOperatorUsbPage();
          }
          break;
        }
        default:{
          //KEY_SELECT_PATIENT_0-4:选择当前页对应位置的患者
          if(state && (control_id >= GDDC_PAGE_LIST_TREATMENT_KEY_SELECT_PATIENT_0)
             && (control_id <= GDDC_PAGE_LIST_TREATMENT_KEY_SELECT_PATIENT_4)){
            listTreatmentSelect((uint8_t)(control_id - GDDC_PAGE_LIST_TREATMENT_KEY_SELECT_PATIENT_0));
            treatmentReleaseButton(GDDC_PAGE_LIST_TREATMENT, control_id);//切页后释放源按键(选中高亮在重新进入时由refresh恢复)
          }
          //KEY_DELETE_0-4:进入删除确认页(不立即删除), 确认后才级联删除该患者
          else if(state && (control_id >= GDDC_PAGE_LIST_TREATMENT_KEY_DELETE_0)
             && (control_id <= GDDC_PAGE_LIST_TREATMENT_KEY_DELETE_4)){
            listTreatmentDeleteStart((uint8_t)(control_id - GDDC_PAGE_LIST_TREATMENT_KEY_DELETE_0));
            treatmentReleaseButton(GDDC_PAGE_LIST_TREATMENT, control_id);//切页后释放源按键
          }
          //KEY_EDIT_RECORD_0-4:进入该患者的历史治疗记录页(15)
          else if(state && (control_id >= GDDC_PAGE_LIST_TREATMENT_KEY_EDIT_RECORD_0)
             && (control_id <= GDDC_PAGE_LIST_TREATMENT_KEY_EDIT_RECORD_4)){
            listTreatmentRecordEnter((uint8_t)(control_id - GDDC_PAGE_LIST_TREATMENT_KEY_EDIT_RECORD_0));
            treatmentReleaseButton(GDDC_PAGE_LIST_TREATMENT, control_id);//切页后释放源按键
          }
          break;
        }
      }
      break;
    }
    case GDDC_PAGE_LIST_RECORD:{//患者历史治疗记录页: 浏览/翻页/删除/编辑患者
      switch(control_id){
        case GDDC_PAGE_LIST_RECORD_KEY_PAGE_UP:{//记录窗口向前翻页(经软件去抖, 快速连按只生效一次)
          if(state){
            listTreatmentRecordPageKey(0U);
            treatmentReleaseButton(GDDC_PAGE_LIST_RECORD, GDDC_PAGE_LIST_RECORD_KEY_PAGE_UP);//复位自锁按钮并解除互锁
          }
          break;
        }
        case GDDC_PAGE_LIST_RECORD_KEY_PAGE_DOWN:{//记录窗口向后翻页(经软件去抖, 快速连按只生效一次)
          if(state){
            listTreatmentRecordPageKey(1U);
            treatmentReleaseButton(GDDC_PAGE_LIST_RECORD, GDDC_PAGE_LIST_RECORD_KEY_PAGE_DOWN);//复位自锁按钮并解除互锁
          }
          break;
        }
        case GDDC_PAGE_LIST_RECORD_KEY_CLOSE:{//返回病历列表页(13)
          if(state){
            treatmentReleaseButton(GDDC_PAGE_LIST_RECORD, GDDC_PAGE_LIST_RECORD_KEY_CLOSE);//先释放再切页: 当前页仍在时下发清零
            listTreatmentRecordClose();
          }
          break;
        }
        case GDDC_PAGE_LIST_RECORD_KEY_EDIT_PATIENT:{//进入患者信息编辑页(17)
          if(state){
            //源按钮释放已纳入RecordEditPatient的画面冻结事务, 避免在当前页可见弹起过程
            listTreatmentRecordEditPatient();
          }
          break;
        }
        default:{
          //KEY_DELETE_0-4:进入单条记录删除确认页(16), 确认后才删除
          if(state && (control_id >= GDDC_PAGE_LIST_RECORD_KEY_DELETE_0)
             && (control_id <= GDDC_PAGE_LIST_RECORD_KEY_DELETE_4)){
            //禁用DELETE键关闭触摸窗口后再切页, 不在手指仍触摸时清零(避免卡按下); 锁与视觉由确认页返回路径统一处理
            listTreatmentRecordDeleteKey((uint8_t)(control_id - GDDC_PAGE_LIST_RECORD_KEY_DELETE_0));
          }
          break;
        }
      }
      break;
    }
    case GDDC_PAGE_DELETE_RECORD:{//单条治疗记录删除确认页: 确认删除或取消返回记录页
      switch(control_id){
        case GDDC_PAGE_DELETE_RECORD_KEY_OK:{
          if(state){
            listTreatmentDeleteRecordConfirm();
            treatmentReleaseButton(GDDC_PAGE_DELETE_RECORD, GDDC_PAGE_DELETE_RECORD_KEY_OK);//复位自锁按钮并解除互锁
          }
          break;
        }
        case GDDC_PAGE_DELETE_RECORD_KEY_CANCEL:{
          if(state){
            listTreatmentDeleteRecordCancel();
            treatmentReleaseButton(GDDC_PAGE_DELETE_RECORD, GDDC_PAGE_DELETE_RECORD_KEY_CANCEL);//复位自锁按钮并解除互锁
          }
          break;
        }
        default:break;
      }
      break;
    }
    case GDDC_PAGE_DELETE_TREATMENT:{//删除患者确认页: 确认删除或取消返回列表页
      switch(control_id){
        case GDDC_PAGE_DELETE_TREATMENT_KEY_OK:{
          if(state){
            listTreatmentDeleteConfirm();
            treatmentReleaseButton(GDDC_PAGE_DELETE_TREATMENT, GDDC_PAGE_DELETE_TREATMENT_KEY_OK);//notify无条件释放: 含守卫空操作也弹起
          }
          break;
        }
        case GDDC_PAGE_DELETE_TREATMENT_KEY_CANCEL:{
          if(state){
            listTreatmentDeleteCancel();
            treatmentReleaseButton(GDDC_PAGE_DELETE_TREATMENT, GDDC_PAGE_DELETE_TREATMENT_KEY_CANCEL);//notify无条件释放
          }
          break;
        }
        default:break;
      }
      break;
    }
    case GDDC_PAGE_OPERATOR_USB:{//USB导入导出操作页
      switch(control_id){
        case GDDC_PAGE_OPERATOR_USB_KEY_CLOSE:{//返回病历列表页
          if(state){
            treatmentReleaseButton(GDDC_PAGE_OPERATOR_USB, GDDC_PAGE_OPERATOR_USB_KEY_CLOSE);//先释放再切页: 当前页仍在时下发清零
            listTreatmentOperatorUsbBack();
          }
          break;
        }
        case GDDC_PAGE_OPERATOR_USB_KEY_SAVE_UDISK:{//存储到U盘: 检测U盘后弹保存提示页(写入在轮询中完成)
          if(state){
            treatmentReleaseButton(GDDC_PAGE_OPERATOR_USB, GDDC_PAGE_OPERATOR_USB_KEY_SAVE_UDISK);//先释放再切页: 当前页仍在时下发清零
            listTreatmentSaveUsbStart();
          }
          break;
        }
        case GDDC_PAGE_OPERATOR_USB_KEY_LOAD_UDISK:{//从U盘载入: 检测U盘后弹载入确认页(不直接覆盖机内病历)
          if(state){
            treatmentReleaseButton(GDDC_PAGE_OPERATOR_USB, GDDC_PAGE_OPERATOR_USB_KEY_LOAD_UDISK);//先释放再切页: 当前页仍在时下发清零
            listTreatmentLoadUsbStart();
          }
          break;
        }
        default:{
          break;
        }
      }
      break;
    }
    case GDDC_PAGE_OPERATOR_USB_SAVE:{//USB导出确认页
      switch(control_id){
        case GDDC_PAGE_OPERATOR_USB_SAVE_KEY_CANCEL:{//取消: 不读写, 返回USB操作页
          if(state){
            treatmentReleaseButton(GDDC_PAGE_OPERATOR_USB_SAVE, GDDC_PAGE_OPERATOR_USB_SAVE_KEY_CANCEL);//先释放再切页: 当前页仍在时下发清零
            listTreatmentUsbCancel();
          }
          break;
        }
        case GDDC_PAGE_OPERATOR_USB_SAVE_KEY_OK:{//确认: 授权导出(在轮询中完成)
          if(state){
            listTreatmentUsbConfirm();
          }
          break;
        }
        default:{
          break;
        }
      }
      break;
    }
    case GDDC_PAGE_OPERATOR_USB_LOAD:{//USB导入确认页
      switch(control_id){
        case GDDC_PAGE_OPERATOR_USB_LOAD_KEY_CANCEL:{//取消: 不读写, 返回USB操作页
          if(state){
            treatmentReleaseButton(GDDC_PAGE_OPERATOR_USB_LOAD, GDDC_PAGE_OPERATOR_USB_LOAD_KEY_CANCEL);//先释放再切页: 当前页仍在时下发清零
            listTreatmentUsbCancel();
          }
          break;
        }
        case GDDC_PAGE_OPERATOR_USB_LOAD_KEY_OK:{//确认: 授权导入(在轮询中完成)
          if(state){
            listTreatmentUsbConfirm();
          }
          break;
        }
        default:{
          break;
        }
      }
      break;
    }
    case GDDC_PAGE_EDIT_PATIENT:{//老患者编辑页(性别为下拉菜单, 经NotifyMenu处理)
      switch(control_id){
        case GDDC_PAGE_EDIT_PATIENT_KEY_OK:{//保存: 记录页进入=更新患者信息; 正常流程=校验后追加到EPROM
          if(state){
            if(listTreatmentIsEditPatientMode()){
              //edit模式: Confirm内部画面冻结事务已释放源按钮, 此处不再重复
              listTreatmentEditPatientConfirm();
            }
            else{
              listTreatmentCreateConfirm();
              treatmentReleaseButton(GDDC_PAGE_EDIT_PATIENT, GDDC_PAGE_EDIT_PATIENT_KEY_OK);//create模式: 复位自锁按钮并解除互锁
            }
          }
          break;
        }
        case GDDC_PAGE_EDIT_PATIENT_KEY_CANCEL:{//取消: 记录页进入=回记录页; 正常流程=返回病历列表页, EPROM不变
          if(state){
            if(listTreatmentIsEditPatientMode()){
              //edit模式: Cancel内部画面冻结事务已释放源按钮, 此处不再重复
              listTreatmentEditPatientCancel();
            }
            else{
              listTreatmentCreateCancel();
              treatmentReleaseButton(GDDC_PAGE_EDIT_PATIENT, GDDC_PAGE_EDIT_PATIENT_KEY_CANCEL);//create模式: 复位自锁按钮并解除互锁
            }
          }
          break;
        }
        default:break;
      }
      break;
    }
    case GDDC_PAGE_VERIFY_TREATMENT:{//激光核对页
      switch(control_id){
        case GDDC_PAGE_VERIFY_TREATMENT_KEY_SAVE_RECORD:{
          if(state){
            //瞬变按钮: 按下执行落盘, 松开屏幕自动弹起; 校验失败停留本页也不卡按下
            listTreatmentVerifySaveRecord();
          }
          break;
        }
        case GDDC_PAGE_VERIFY_TREATMENT_KEY_DISCARD_RECORD:{
          if(state){
            treatmentReleaseButton(GDDC_PAGE_VERIFY_TREATMENT, GDDC_PAGE_VERIFY_TREATMENT_KEY_DISCARD_RECORD);
            listTreatmentVerifyDiscard();
          }
          break;
        }
        case GDDC_PAGE_VERIFY_TREATMENT_KEY_SELECT_TREATMENT:{
          if(state){
            treatmentReleaseButton(GDDC_PAGE_VERIFY_TREATMENT, GDDC_PAGE_VERIFY_TREATMENT_KEY_SELECT_TREATMENT);
            listTreatmentVerifySelect();
          }
          break;
        }
        default:break;
      }
    }
    case GDDC_PAGE_DISCARD_TREATMENT:{//放弃本次记录页
      switch(control_id){
        case GDDC_PAGE_DISCARD_TREATMENT_KEY_RETURN:{
          if(state){
            treatmentReleaseButton(GDDC_PAGE_DISCARD_TREATMENT, GDDC_PAGE_DISCARD_TREATMENT_KEY_RETURN);
            listTreatmentDiscardReturn();
          }
          break;
        }
        case GDDC_PAGE_DISCARD_TREATMENT_KEY_CANCEL:{
          if(state){
            treatmentReleaseButton(GDDC_PAGE_DISCARD_TREATMENT, GDDC_PAGE_DISCARD_TREATMENT_KEY_CANCEL);
            listTreatmentDiscardCancel();
          }
          break;
        }
        default:break;
      }
    }
    case GDDC_PAGE_REGISTER_PATIENT:{//新患者注册页
      switch(control_id){
        case GDDC_PAGE_REGISTER_PATIENT_KEY_OK:{//保存: 校验后新建患者(激光流程同时落记录)
          if(state){
            //瞬变按钮: 按下执行校验, 松开屏幕自动弹起; 校验失败停留本页也不卡按下
            listTreatmentRegisterConfirm();
          }
          break;
        }
        case GDDC_PAGE_REGISTER_PATIENT_KEY_CANCEL:{//取消: 按来源页返回, EPROM不变
          if(state){
            treatmentReleaseButton(GDDC_PAGE_REGISTER_PATIENT, GDDC_PAGE_REGISTER_PATIENT_KEY_CANCEL);//复位自锁按钮并解除互锁
            listTreatmentRegisterCancel();
          }
          break;
        }
        default:break;
      }
    }
    case GDDC_PAGE_READY:{
      switch(control_id){
        case GDDC_PAGE_READY_KEY_READY:{
          if(!state){
            SSET(R_STANDBY_KEY_STNADBY_UP);
          }
          break;
        }
        case GDDC_PAGE_READY_KEY_EMULATOR_FSW:{//工程模式瞬态按键: 按下=脚踏踩下, 弹起=脚踏松开
          if(state){
            SSET(R_EMULATOR_FSW_PRESS);
          }
          else{
            RRES(R_EMULATOR_FSW_PRESS);
          }
          break;
        }
        case GDDC_PAGE_READY_KEY_ACOUSTIC_ENERGY_ADD:{
          if(state){//DOWN
            SSET(R_READY_KEY_ACOUSTIC_ENERGY_ADD_DOWN);
          }
          else{//UP
            SSET(R_READY_KEY_ACOUSTIC_ENERGY_ADD_UP);
          }
          break;
        }
        case GDDC_PAGE_READY_KEY_ACOUSTIC_ENERGY_INC:{
          if(state){//DOWN
            SSET(R_READY_KEY_ACOUSTIC_ENERGY_DEC_DOWN);
          }
          else{//UP
            SSET(R_READY_KEY_ACOUSTIC_ENERGY_DEC_UP);
          }
          break;
        }
        case GDDC_PAGE_READY_KEY_ACOUSTIC_TIME_ADD:{
          if(state){//DOWN
            SSET(R_READY_KEY_ACOUSTIC_TIME_ADD_DOWN);
          }
          else{//UP
            SSET(R_READY_KEY_ACOUSTIC_TIME_ADD_UP);
          }
          break;
        }
        case GDDC_PAGE_READY_KEY_ACOUSTIC_TIME_INC:{
          if(state){//DOWN
            SSET(R_READY_KEY_ACOUSTIC_TIME_DEC_DOWN);
          }
          else{//UP
            SSET(R_READY_KEY_ACOUSTIC_TIME_DEC_UP);
          }
          break;
        }
        default:break;
      }
      break;
    }
    case GDDC_PAGE_OPTION:{//选项页面
      switch(control_id){
        case GDDC_PAGE_OPTION_KEY_TONE:{
          if(state){
            SSET(MR_BEEP_TONE);
          }
          else{
            RRES(MR_BEEP_TONE);
          }
          break;
        }
        case GDDC_PAGE_OPTION_KEY_BEEP_VOLUME_ADD:{
          if(state){
            SSET(R_OPTION_KEY_BEEM_VOLUME_ADD_DOWN);
          }
          break;
        }
        case GDDC_PAGE_OPTION_KEY_BEEP_VOLUME_INC:{
          if(state){
            SSET(R_OPTION_KEY_BEEM_VOLUME_DEC_DOWN);
          }
          break;
        }
        case GDDC_PAGE_OPTION_KEY_LCD_BRG_ADD:{
          if(state){
            SSET(R_OPTION_KEY_LCD_BRG_ADD_DOWN);
          }
          break;
        }
        case GDDC_PAGE_OPTION_KEY_LCD_BRG_INC:{
          if(state){
            SSET(R_OPTION_KEY_LCD_BRG_DEC_DOWN);
          }
          break;
        }
        case GDDC_PAGE_OPTION_KEY_ENTER_INFORMATION:{//信息
          if(state){
            SSET(R_OPTION_KEY_ENTER_INFORMATION_DOWN);
          }
          break;
        }
        case GDDC_PAGE_OPTION_KEY_ENTER_OK:{//OK
          if(state){
            returnStandbyDisplay();//统一返回待机页面
          }
          break;
        }
        case GDDC_PAGE_OPTION_KEY_HAND_SWITCH_ON:{
          if(state){
            SSET(MR_FOOSWITCH_HAND_SWITCH);
            updateOptionDisplay();
          }
          else{
            RRES(MR_FOOSWITCH_HAND_SWITCH);
            updateOptionDisplay();
          }
          break;
        }
        case GDDC_PAGE_OPTION_KEY_ENTER_ENGINEER:{
          if(state){
            SSET(R_OPTION_KEY_ENTER_DIAGNOSIS_DOWN);
          }
          break;
        }
        default:break;
      }
      break;
    }
    case GDDC_PAGE_RESTORE:{
      switch(control_id){
        case GDDC_PAGE_RESTORE_KEY_YES:{
          if(state){
            restoreDefault();
            restoreScheme(true);
            REBOOT();
          }
          break;
        }
        case GDDC_PAGE_RESTORE_KEY_CANCEL:{
          if(state){
            updateOptionDisplay();
            
          }
          break;
        }
        default:break;
      }
    }
    case GDDC_PAGE_INFORMATION:{
      switch(control_id){
        case GDDC_PAGE_INFORMATION_KEY_ENTER_OK:{
          if(state){
            SSET(R_INFORMATION_KEY_OK_DOWN);
          }
          else{
            SSET(R_INFORMATION_KEY_OK_UP);
          }
          break;
        }
        default:break;
      }
      break;
    }
    case GDDC_PAGE_SCHEME_CLASSIFY_TRI:{
      switch(control_id){
        case  GDDC_PAGE_SCHEME_CLASSIFY_KEY_PHLEBOLOGY:{
          if(state){
            NVRAM0[EM_SCHEME_CLASSIFY_TMP] = SCHEME_PHLEBOLOGY;
            NVRAM0[EM_SCHEME_NUM_TMP] = 0;
            NVRAM0[EM_DC_PAGE] = GDDC_PAGE_SCHEME_DETAIL;
            updateSchemeDetail(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
            seletcSchemeNum(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
            SetScreen(NVRAM0[EM_DC_PAGE]);
          }
          break;
        }
        case GDDC_PAGE_SCHEME_CLASSIFY_KEY_PROCTOLOGY:{
          if(state){
            NVRAM0[EM_SCHEME_CLASSIFY_TMP] = SCHEME_PROCTOLOGY;
            NVRAM0[EM_SCHEME_NUM_TMP] = 0;
            NVRAM0[EM_DC_PAGE] = GDDC_PAGE_SCHEME_DETAIL;
            updateSchemeDetail(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
            seletcSchemeNum(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
            SetScreen(NVRAM0[EM_DC_PAGE]);
          }
          break;
        }
        case GDDC_PAGE_SCHEME_CLASSIFY_KEY_GTNECOLOGY:{
          if(state){
            NVRAM0[EM_SCHEME_CLASSIFY_TMP] = SCHEME_GYNECOLOGY;
            NVRAM0[EM_SCHEME_NUM_TMP] = 0;
            NVRAM0[EM_DC_PAGE] = GDDC_PAGE_SCHEME_DETAIL;
            updateSchemeDetail(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
            seletcSchemeNum(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
            SetScreen(NVRAM0[EM_DC_PAGE]);
          }
          break;
        }
        case GDDC_PAGE_SCHEME_CLASSIFY_KEY_ENT:{
          if(state){
            NVRAM0[EM_SCHEME_CLASSIFY_TMP] = SCHEME_ENT;
            NVRAM0[EM_SCHEME_NUM_TMP] = 0;
            NVRAM0[EM_DC_PAGE] = GDDC_PAGE_SCHEME_DETAIL;
            updateSchemeDetail(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
            seletcSchemeNum(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
            SetScreen(NVRAM0[EM_DC_PAGE]);
          }
          break;
        }
        case GDDC_PAGE_SCHEME_CLASSIFY_KEY_NEUROSURGERY:{
          if(state){
            NVRAM0[EM_SCHEME_CLASSIFY_TMP] = SCHEME_NEUROSURGERY;
            NVRAM0[EM_SCHEME_NUM_TMP] = 0;
            NVRAM0[EM_DC_PAGE] = GDDC_PAGE_SCHEME_DETAIL;
            updateSchemeDetail(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
            seletcSchemeNum(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
            SetScreen(NVRAM0[EM_DC_PAGE]);
          }
          break;
        }
        case GDDC_PAGE_SCHEME_CLASSIFY_KEY_DERMATOLOGY:{
          if(state){
            NVRAM0[EM_SCHEME_CLASSIFY_TMP] = SCHEME_DERMATOLOGY;
            NVRAM0[EM_SCHEME_NUM_TMP] = 0;
            NVRAM0[EM_DC_PAGE] = GDDC_PAGE_SCHEME_DETAIL;
            updateSchemeDetail(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
            seletcSchemeNum(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
            SetScreen(NVRAM0[EM_DC_PAGE]);
          }
          break;
        }
        case GDDC_PAGE_SCHEME_CLASSIFY_KEY_LIPOSUCTION:{
          if(state){
            NVRAM0[EM_SCHEME_CLASSIFY_TMP] = SCHEME_LIPOSUCTION;
            NVRAM0[EM_SCHEME_NUM_TMP] = 0;
            NVRAM0[EM_DC_PAGE] = GDDC_PAGE_SCHEME_DETAIL;
            updateSchemeDetail(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
            seletcSchemeNum(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
            SetScreen(NVRAM0[EM_DC_PAGE]);
          }
          break;
        }
        case GDDC_PAGE_SCHEME_CLASSIFY_KEY_DENTISTRY:{
          if(state){
            NVRAM0[EM_SCHEME_CLASSIFY_TMP] = SCHEME_DENTISTRY;
            NVRAM0[EM_SCHEME_NUM_TMP] = 0;
            NVRAM0[EM_DC_PAGE] = GDDC_PAGE_SCHEME_DETAIL;
            updateSchemeDetail(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
            seletcSchemeNum(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
            SetScreen(NVRAM0[EM_DC_PAGE]);
          }
          break;
        }
        case GDDC_PAGE_SCHEME_CLASSIFY_KEY_THERAPY:{
          if(state){
            NVRAM0[EM_SCHEME_CLASSIFY_TMP] = SCHMEM_THERAPY;
            NVRAM0[EM_SCHEME_NUM_TMP] = 0;
            NVRAM0[EM_DC_PAGE] = GDDC_PAGE_SCHEME_DETAIL;
            updateSchemeDetail(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
            seletcSchemeNum(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
            SetScreen(NVRAM0[EM_DC_PAGE]);
          }
          break;
        }
        case GDDC_PAGE_SCHEME_CLASSIFY_KEY_CUSTOM:{
          if(state){
            memcpy((char*)FDRAM1, (char*)FDRAM0, (CONFIG_FDRAM_SIZE * 2));
            NVRAM0[EM_SCHEME_CLASSIFY_TMP] = SCHEME_CUSTIOM;
            NVRAM0[EM_SCHEME_NUM_TMP] = 0;
            NVRAM0[EM_DC_PAGE] = GDDC_PAGE_SCHEME_DETAIL;
            updateSchemeDetail(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
            seletcSchemeNum(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
            SetScreen(NVRAM0[EM_DC_PAGE]);
          }
          break;
        }
        case GDDC_PAGE_SCHEME_CLASSIFY_KEY_RETURN:{
            returnStandbyDisplay();//统一返回待机页面
          break;
        }
        default:break;
      }
      break;
    }
    case GDDC_PAGE_SCHEME_CLASSIFY_DUAL:{
      switch(control_id){
        case  GDDC_PAGE_SCHEME_CLASSIFY_KEY_PHLEBOLOGY:{
          if(state){
            NVRAM0[EM_SCHEME_CLASSIFY_TMP] = SCHEME_PHLEBOLOGY;
            NVRAM0[EM_SCHEME_NUM_TMP] = 0;
            NVRAM0[EM_DC_PAGE] = GDDC_PAGE_SCHEME_DETAIL;
            updateSchemeDetail(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
            seletcSchemeNum(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
            SetScreen(NVRAM0[EM_DC_PAGE]);
          }
          break;
        }
        case GDDC_PAGE_SCHEME_CLASSIFY_KEY_PROCTOLOGY:{
          if(state){
            NVRAM0[EM_SCHEME_CLASSIFY_TMP] = SCHEME_PROCTOLOGY;
            NVRAM0[EM_SCHEME_NUM_TMP] = 0;
            NVRAM0[EM_DC_PAGE] = GDDC_PAGE_SCHEME_DETAIL;
            updateSchemeDetail(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
            seletcSchemeNum(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
            SetScreen(NVRAM0[EM_DC_PAGE]);
          }
          break;
        }
        case GDDC_PAGE_SCHEME_CLASSIFY_KEY_GTNECOLOGY:{
          if(state){
            NVRAM0[EM_SCHEME_CLASSIFY_TMP] = SCHEME_GYNECOLOGY;
            NVRAM0[EM_SCHEME_NUM_TMP] = 0;
            NVRAM0[EM_DC_PAGE] = GDDC_PAGE_SCHEME_DETAIL;
            updateSchemeDetail(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
            seletcSchemeNum(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
            SetScreen(NVRAM0[EM_DC_PAGE]);
          }
          break;
        }
        case GDDC_PAGE_SCHEME_CLASSIFY_KEY_NEUROSURGERY:{
          if(state){
            NVRAM0[EM_SCHEME_CLASSIFY_TMP] = SCHEME_NEUROSURGERY;
            NVRAM0[EM_SCHEME_NUM_TMP] = 0;
            NVRAM0[EM_DC_PAGE] = GDDC_PAGE_SCHEME_DETAIL;
            updateSchemeDetail(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
            seletcSchemeNum(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
            SetScreen(NVRAM0[EM_DC_PAGE]);
          }
          break;
        }
        case GDDC_PAGE_SCHEME_CLASSIFY_KEY_LIPOSUCTION:{
          if(state){
            NVRAM0[EM_SCHEME_CLASSIFY_TMP] = SCHEME_LIPOSUCTION;
            NVRAM0[EM_SCHEME_NUM_TMP] = 0;
            NVRAM0[EM_DC_PAGE] = GDDC_PAGE_SCHEME_DETAIL;
            updateSchemeDetail(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
            seletcSchemeNum(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
            SetScreen(NVRAM0[EM_DC_PAGE]);
          }
          break;
        }
        case GDDC_PAGE_SCHEME_CLASSIFY_KEY_THERAPY:{
          if(state){
            NVRAM0[EM_SCHEME_CLASSIFY_TMP] = SCHMEM_THERAPY;
            NVRAM0[EM_SCHEME_NUM_TMP] = 0;
            NVRAM0[EM_DC_PAGE] = GDDC_PAGE_SCHEME_DETAIL;
            updateSchemeDetail(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
            seletcSchemeNum(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
            SetScreen(NVRAM0[EM_DC_PAGE]);
          }
          break;
        }
        case GDDC_PAGE_SCHEME_CLASSIFY_KEY_ENDOLIFT:{
          if(state){
            NVRAM0[EM_SCHEME_CLASSIFY_TMP] = SCHEME_ENDOLIFT;
            NVRAM0[EM_SCHEME_NUM_TMP] = 0;
            NVRAM0[EM_DC_PAGE] = GDDC_PAGE_SCHEME_DETAIL;
            updateSchemeDetail(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
            seletcSchemeNum(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
            SetScreen(NVRAM0[EM_DC_PAGE]);
          }
          break;
        }
        case GDDC_PAGE_SCHEME_CLASSIFY_KEY_CUSTOM:{
          if(state){
            memcpy((char*)FDRAM1, (char*)FDRAM0, (CONFIG_FDRAM_SIZE * 2));
            NVRAM0[EM_SCHEME_CLASSIFY_TMP] = SCHEME_CUSTIOM;
            NVRAM0[EM_SCHEME_NUM_TMP] = 0;
            NVRAM0[EM_DC_PAGE] = GDDC_PAGE_SCHEME_DETAIL;
            updateSchemeDetail(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
            seletcSchemeNum(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
            SetScreen(NVRAM0[EM_DC_PAGE]);
          }
          break;
        }
        case GDDC_PAGE_SCHEME_CLASSIFY_KEY_RETURN:{
            returnStandbyDisplay();//统一返回待机页面
          break;
        }
        default:break;
      }
      break;
    }
    case GDDC_PAGE_SCHEME_DETAIL:{
      switch(control_id){
        case GDDC_PAGE_SCHEME_DETAIL_KEY_RENAME:{
          if(state){
            SSET(R_SCHEME_KEY_RENAME_DOWN);
          }
          break;
        }
        case GDDC_PAGE_SCHEME_DETAIL_KEY_OK:{
          if(state){
            if(NVRAM0[EM_SCHEME_CLASSIFY_TMP] == SCHEME_CUSTIOM){
              memcpy((char*)FDRAM0, (char*)FDRAM1, (CONFIG_FDRAM_SIZE * 2));
            }
            NVRAM0[DM_SCHEME_INDEX] = NVRAM0[EM_SCHEME_NUM_TMP];//选定方案生效
            NVRAM0[DM_SCHEME_CLASSIFY] = NVRAM0[EM_SCHEME_CLASSIFY_TMP];
            loadSelectScheme(NVRAM0[DM_SCHEME_CLASSIFY], NVRAM0[DM_SCHEME_INDEX]);
            returnStandbyDisplay();//统一返回待机页面
          }
          break;
        }
        case GDDC_PAGE_SCHEME_DETAIL_KEY_CANCEL:{
          if(state){
#if defined(APP_CONFIG_WAVE_1470_980_635)
            NVRAM0[EM_DC_PAGE] = GDDC_PAGE_SCHEME_CLASSIFY_TRI;
            SetScreen(NVRAM0[EM_DC_PAGE]);
#endif
#if defined(APP_CONFIG_WAVE_1470_635)
            NVRAM0[EM_DC_PAGE] = GDDC_PAGE_SCHEME_CLASSIFY_DUAL;
            SetScreen(NVRAM0[EM_DC_PAGE]);
#endif
#if defined(APP_CONFIG_WAVE_1940_635)
            returnStandbyDisplay();//统一返回待机页面
#endif
#if defined(APP_CONFIG_WAVE_450_980)
            returnStandbyDisplay();//统一返回待机页面
#endif
#if defined(APP_CONFIG_WAVE_1940_1470_635)
            NVRAM0[EM_DC_PAGE] = GDDC_PAGE_SCHEME_CLASSIFY_DUAL;
            SetScreen(NVRAM0[EM_DC_PAGE]);
#endif
          }
          break;
        }
        case GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_0:{
          if(state){
            SSET(R_SCHEME_KEY_SCHEME_SELECT_0_DOWN);
          }
          break;
        }
        case GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_1:{
          if(state){
            SSET(R_SCHEME_KEY_SCHEME_SELECT_1_DOWN);
          }
          break;
        }
        case GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_2:{
          if(state){
            SSET(R_SCHEME_KEY_SCHEME_SELECT_2_DOWN);
          }
          break;
        }
        case GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_3:{
          if(state){
            SSET(R_SCHEME_KEY_SCHEME_SELECT_3_DOWN);
          }
          break;
        }
        case GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_4:{
          if(state){
            SSET(R_SCHEME_KEY_SCHEME_SELECT_4_DOWN);
          }
          break;
        }
        case GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_5:{
          if(state){
            SSET(R_SCHEME_KEY_SCHEME_SELECT_5_DOWN);
          }
          break;
        }
        case GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_6:{
          if(state){
            SSET(R_SCHEME_KEY_SCHEME_SELECT_6_DOWN);
          }
          break;
        }
        case GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_7:{
          if(state){
            SSET(R_SCHEME_KEY_SCHEME_SELECT_7_DOWN);
          }
          break;
        }
        case GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_8:{
          if(state){
            SSET(R_SCHEME_KEY_SCHEME_SELECT_8_DOWN);
          }
          break;
        }
        case GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_9:{
          if(state){
            SSET(R_SCHEME_KEY_SCHEME_SELECT_9_DOWN);
          }
          break;
        }
        case GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_10:{
          if(state){
            SSET(R_SCHEME_KEY_SCHEME_SELECT_10_DOWN);
          }
          break;
        }
        case GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_11:{
          if(state){
            SSET(R_SCHEME_KEY_SCHEME_SELECT_11_DOWN);
          }
          break;
        }
        case GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_12:{
          if(state){
            SSET(R_SCHEME_KEY_SCHEME_SELECT_12_DOWN);
          }
          break;
        }
        case GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_13:{
          if(state){
            SSET(R_SCHEME_KEY_SCHEME_SELECT_13_DOWN);
          }
          break;
        }
        case GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_14:{
          if(state){
            SSET(R_SCHEME_KEY_SCHEME_SELECT_14_DOWN);
          }
          break;
        }
        case GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_15:{
          if(state){
            SSET(R_SCHEME_KEY_SCHEME_SELECT_15_DOWN);
          }
          break;
        }
        case GDDC_PAGE_SCHEME_DETAIL_KEY_NEXT_PAGE:{
          if(state){
            NVRAM0[EM_SCHEME_NUM_TMP] = 16;
            updateSchemeDetail(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
            SetButtonValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_0, 1);
            updateSchemeInfo(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
          }
          break;
        }
        case GDDC_PAGE_SCHEME_DETAIL_KEY_LAST_PAGE:{
          if(state){
            NVRAM0[EM_SCHEME_NUM_TMP] = 0;
            updateSchemeDetail(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
            SetButtonValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_0, 1);
            updateSchemeInfo(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
          }
          break;
        }
        default:break;
      }
      break;
    }
    
    case GDDC_PAGE_DIAGNOSIS:{
      switch(control_id){
        case GDDC_PAGE_DIAGNOSIS_KEY_ENTER_OK:{
          if(state){
            SSET(R_DIAGNOSIS_OK_DOWN);
          }
          break;
        }
        case GDDC_PAGE_DIAGNOSIS_KEY_DISABLE_FOOTSWITCH:{
          if(state){
            SSET(R_DISABLE_FOOTSWITCH_CHECK);
          }
          else{
            RRES(R_DISABLE_FOOTSWITCH_CHECK);
          }
          break;
        }
        case GDDC_PAGE_DIAGNOSIS_KEY_DISABLE_TEMPERATURE:{
          if(state){
            SSET(R_DISABLE_TEMPERATURE_CHECK);
          }
          else{
            RRES(R_DISABLE_TEMPERATURE_CHECK);
          }
          break;
        }
        case GDDC_PAGE_DIAGNOSIS_KEY_DISABLE_ESTOP:{
          if(state){
            SSET(R_DISABLE_ESTOP_CHECK);
          }
          else{
            RRES(R_DISABLE_ESTOP_CHECK);
          }
          break;
        }
        case GDDC_PAGE_DIAGNOSIS_KEY_DISABLE_INTERLOCK:{
          if(state){
            SSET(R_DISABLE_INTERLOCK_CHECK);
          }
          else{
            RRES(R_DISABLE_INTERLOCK_CHECK);
          }
          break;
        }
        case GDDC_PAGE_DIAGNOSIS_KEY_DISABLE_RFID:{
          if(state){
            SSET(R_DISABLE_RFID_CHECK);
          }
          else{
            RRES(R_DISABLE_RFID_CHECK);
          }
          break;
        }
        case GDDC_PAGE_DIAGNOSIS_KEY_DISABLE_FIBER_PROBE:{
          if(state){
            SSET(R_DISABLE_FIBER_PROBE_CHECK);
          }
          else{
            RRES(R_DISABLE_FIBER_PROBE_CHECK);
          }
          break;
        }
        case GDDC_PAGE_DIAGNOSIS_KEY_DISABLE_HUMIDITY:{
          if(state){
            SSET(R_DISABLE_HUMIDITY_CHECK);
          }
          else{
            RRES(R_DISABLE_HUMIDITY_CHECK);
          }
          break;
        }
        case GDDC_PAGE_DIAGNOSIS_KEY_DISABLE_AUTO_FAN:{
          if(state){
            SSET(R_DISABLE_AUTO_FAN);
          }
          else{
            RRES(R_DISABLE_AUTO_FAN);
          }
          break;
        }
        case GDDC_PAGE_DIAGNOSIS_KEY_DISABLE_FLOW:{
          if(state){
            SSET(R_DISABLE_FLOW_CHECK);
          }
          else{
            RRES(R_DISABLE_FLOW_CHECK);
          }
          break;
        }
        case GDDC_PAGE_DIAGNOSIS_KEY_CALIBRATION:{//切换入功率校正页面
          if(state){
            SSET(R_DIAGNOSIS_GOTO_CORRECTION_DOWN);
          }
          break;
        }
        case GDDC_PAGE_DIAGNOSIS_KEY_CLEAR_EPROM:{//清空EPROM
          if(state){
            SSET(R_CLEAR_EPROM);
          }
          break;
        }
        case GDDC_PAGE_DIAGNOSIS_KEY_CLEAR_CRC:{//清空固件CRC
          if(state){
            SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_ENTER_OK, false);
            SSET(R_CLEAR_CRC);
          }
          break;
        }
        case GDDC_PAGE_DIAGNOSIS_KEY_SAVE_EPROM:{//储存EPROM
          if(state){
            SSET(R_SAVE_EPROM);
          }
          break;
        }
        case GDDC_PAGE_DIAGNOSIS_KEY_UPDATE_BOOTLOAD_REQ:{//更新BOOTLOAD请求
          if(state){
            SSET(R_UPDATE_BOOTLOAD_REQ);
          }
          break;
        }
        case GDDC_PAGE_DIAGNOSIS_KEY_UPDATE_BOOTLOAD_YES:{//计算U盘BOOTLOAD文件CRC值
          if(state){
            SSET(R_UPDATE_BOOTLOAD_YES);
          }
          break;
        }
        case GDDC_PAGE_DIAGNOSIS_KEY_UPDATE_BOOTLOAD_NO:{
          if(state){
            SSET(R_UPDATE_BOOTLOAD_NO);
          }
          break;
        }
        case GDDC_PAGE_DIAGNOSIS_KEY_OPEN_ILOCK:{
          if(state){
            deviceConfig.normalOpenInterLock = 0;//按下设置为联锁常闭
          }
          else{
            deviceConfig.normalOpenInterLock = 1;//弹起设置为连锁常开
          }
          break;
        }
        case GDDC_PAGE_DIAGNOSIS_KEY_RAW_DATE:{
          if(state){
            SSET(R_DIAGNOSIS_GOTO_RAW_DOWN);
          }
          break;
        }
        case GDDC_PAGE_DIAGNOSIS_KEY_AUTOFILL:{//病历自动填充: 按键触发, 先清空再持续新建患者直到区块写满, 每患者随机5-19条记录
          if(state){
            uint16_t demoPatients = 0U, demoRecords = 0U;
            uint8_t demoErr;
            //种子固定传0: 每次按键按运行时刻(滴答+芯片UID+上次PRNG状态)取新种子,
            //保证姓名/性别/年龄/治疗方案/治疗参数均随机; 患者数无上限, 完全由剩余空间决定
            //记录数范围传 0,0 = 默认 5..19; 双重越界保险(FreeBytesPR+InRegion)在填充函数内部保证
            diagnosisKeysSetEnable(0U);//生成期间先禁用本页其他按键, 防止阻塞期间排队触摸误触
            demoErr = (uint8_t)treatmentDemoGenerate(0U,
                                                     0U, 0U, 1U,
                                                     &demoPatients, &demoRecords);
            memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
            if(demoErr == (uint8_t)TREATMENT_DEMO_OK){
              sprintf(dispBuf, "FILL P:%u R:%u OK", demoPatients, demoRecords);
            }
            else{
              sprintf(dispBuf, "DEMO FILL ERR:%d", (int)demoErr);
            }
            SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXT_INFO4, (uint8_t*)dispBuf);
            diagnosisKeysSetEnable(1U);//生成结束恢复按键(312/313保持默认隐藏禁用, 不随恢复开放)
            SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_AUTOFILL, 0);//按钮为自锁型, 填充完成后复位为弹起, 文字回到Fill Demo
          }
          break;
        }
        default:break;
      }
    }
    case GDDC_PAGE_DIAGNOSIS_RAW:{
      switch(control_id){
        case GDDC_PAGE_DIAGNOSIS_RAW_KEY_ENTER_OK:{
          if(state){//退回上级菜单
            SSET(R_DIAGNOSIS_RAW_RETURN_DOWN);
          }
        }
        default:break;
      }
      break;
    }
    case GDDC_PAGE_RENAME:{
        switch(control_id){
        case GDDC_PAGE_RENAME_KEY_EXIT:{
          if(state){
            SSET(R_RENAME_KEY_EXIT_DOWN);
          }
          break;
        }
        default:break;
      }
      break;
    }
    case GDDC_PAGE_DIAGNOSIS_CALI:{
      switch(control_id){
        case GDDC_PAGE_DIAGNOSIS_CALI_KEY_ENTER_OK:{
          if(state){
            SSET(R_DIAGNOSIS_CORRECTION_RETURN_DOWN);
          }
          break;
        }
        case GDDC_PAGE_DIAGNOSIS_CALI_KEY_SAVE_CH0:{
          if(state){
            saveCalibrationTable(LASER_DAC_CHANNEL_CH0);
            SetButtonValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_KEY_SAVE_CH0, false);
          }
          break;
        }
        case GDDC_PAGE_DIAGNOSIS_CALI_KEY_SAVE_CH1:{
          if(state){
            saveCalibrationTable(LASER_DAC_CHANNEL_CH1);
            SetButtonValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_KEY_SAVE_CH1, false);
          }
          break;
        }
        case GDDC_PAGE_DIAGNOSIS_CALI_KEY_SAVE_CH2:{
          if(state){
            saveCalibrationTable(LASER_DAC_CHANNEL_CH2);
            SetButtonValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_KEY_SAVE_CH2, false);
          }
          break;
        }
        case GDDC_PAGE_DIAGNOSIS_CALI_KEY_SAVE_CH3:{
          if(state){
            saveCalibrationTable(LASER_DAC_CHANNEL_CH3);
            SetButtonValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_KEY_SAVE_CH3, false);
          }
          break;
        }
        case GDDC_PAGE_DIAGNOSIS_CALI_KEY_SAVE_CH4:{
          if(state){
            saveCalibrationTable(LASER_DAC_CHANNEL_CH4);
            SetButtonValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_KEY_SAVE_CH4, false);
          }
          break;
        }
        case GDDC_PAGE_DIAGNOSIS_CALI_KEY_SAVE_CH5:{
          if(state){
            saveCalibrationTable(LASER_DAC_CHANNEL_CH5);
            SetButtonValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_KEY_SAVE_CH5, false);
          }
          break;
        }
        case GDDC_PAGE_DIAGNOSIS_CALI_KEY_SAVE_CH6:{
          if(state){
            saveCalibrationTable(LASER_DAC_CHANNEL_CH6);
            SetButtonValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_KEY_SAVE_CH6, false);
          }
          break;
        }
        case GDDC_PAGE_DIAGNOSIS_CALI_KEY_SAVE_CH7:{
          if(state){
            saveCalibrationTable(LASER_DAC_CHANNEL_CH7);
            SetButtonValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_KEY_SAVE_CH7, false);
          }
          break;
        }
        
        case GDDC_PAGE_DIAGNOSIS_CALI_KEY_UPDATE_CH0:{
          if(state){
            NVRAM0[SPREG_DAC_0] = fitLaserToCode(LASER_DAC_CHANNEL_CH0, NVRAM0[EM_CALI_CUR_SET_CH0], &deviceConfig, false);
            UPDAC0();
            printf("%s,%d,%s:SPREG_DAC_0=0x%04X\n", __FILE__, __LINE__, __func__, NVRAM0[SPREG_DAC_0]);
          }
          break;
        }
        case GDDC_PAGE_DIAGNOSIS_CALI_KEY_UPDATE_CH1:{
          if(state){
            NVRAM0[SPREG_DAC_1] = fitLaserToCode(LASER_DAC_CHANNEL_CH1, NVRAM0[EM_CALI_CUR_SET_CH1], &deviceConfig, false);
            UPDAC1();
            printf("%s,%d,%s:SPREG_DAC_1=0x%04X\n", __FILE__, __LINE__, __func__, NVRAM0[SPREG_DAC_1]);
          }
          break;
        }
        case GDDC_PAGE_DIAGNOSIS_CALI_KEY_UPDATE_CH2:{
          if(state){
            NVRAM0[SPREG_DAC_2] = fitLaserToCode(LASER_DAC_CHANNEL_CH2, NVRAM0[EM_CALI_CUR_SET_CH2], &deviceConfig, false);
            UPDAC2();
            printf("%s,%d,%s:SPREG_DAC_2=0x%04X\n", __FILE__, __LINE__, __func__, NVRAM0[SPREG_DAC_2]);
          }
          break;
        }
        case GDDC_PAGE_DIAGNOSIS_CALI_KEY_UPDATE_CH3:{
          if(state){
            NVRAM0[SPREG_DAC_3] = fitLaserToCode(LASER_DAC_CHANNEL_CH3, NVRAM0[EM_CALI_CUR_SET_CH3], &deviceConfig, false);
            UPDAC3();
            printf("%s,%d,%s:SPREG_DAC_3=0x%04X\n", __FILE__, __LINE__, __func__, NVRAM0[SPREG_DAC_3]);
          }
          break;
        }
        case GDDC_PAGE_DIAGNOSIS_CALI_KEY_UPDATE_CH4:{
          if(state){
            NVRAM0[SPREG_DAC_4] = fitLaserToCode(LASER_DAC_CHANNEL_CH4, NVRAM0[EM_CALI_CUR_SET_CH4], &deviceConfig, false);
            UPDAC4();
            printf("%s,%d,%s:SPREG_DAC_4=0x%04X\n", __FILE__, __LINE__, __func__, NVRAM0[SPREG_DAC_4]);
          }
          break;
        }
        case GDDC_PAGE_DIAGNOSIS_CALI_KEY_UPDATE_CH5:{
          if(state){
            NVRAM0[SPREG_DAC_5] = fitLaserToCode(LASER_DAC_CHANNEL_CH5, NVRAM0[EM_CALI_CUR_SET_CH5], &deviceConfig, false);
            UPDAC5();
            printf("%s,%d,%s:SPREG_DAC_5=0x%04X\n", __FILE__, __LINE__, __func__, NVRAM0[SPREG_DAC_5]);
          }
          break;
        }
        case GDDC_PAGE_DIAGNOSIS_CALI_KEY_UPDATE_CH6:{
          if(state){
            NVRAM0[SPREG_DAC_6] = fitLaserToCode(LASER_DAC_CHANNEL_CH6, NVRAM0[EM_CALI_CUR_SET_CH6], &deviceConfig, false);
            UPDAC6();
            printf("%s,%d,%s:SPREG_DAC_6=0x%04X\n", __FILE__, __LINE__, __func__, NVRAM0[SPREG_DAC_6]);
          }
          break;
        }
        case GDDC_PAGE_DIAGNOSIS_CALI_KEY_UPDATE_CH7:{
          if(state){
            NVRAM0[SPREG_DAC_7] = fitLaserToCode(LASER_DAC_CHANNEL_CH7, NVRAM0[EM_CALI_CUR_SET_CH7], &deviceConfig, false);
            UPDAC7();
            printf("%s,%d,%s:SPREG_DAC_7=0x%04X\n", __FILE__, __LINE__, __func__, NVRAM0[SPREG_DAC_7]);
          }
          break;
        }
        case GDDC_PAGE_DIAGNOSIS_CALI_KEY_LAS_PWM_CH0:{
          if(state){
            SET_LASER_CH0_ON;
            printf("SET LASER CH0 PWM ON\n");
          }
          else{
            SET_LASER_CH0_OFF;
            printf("SET LASER CH0 PWM OFF\n");
          }
          break;
        }
        case GDDC_PAGE_DIAGNOSIS_CALI_KEY_LAS_PWM_CH1:{
          if(state){
            SET_LASER_CH1_ON;
            printf("SET LASER CH1 PWM ON\n");
          }
          else{
            SET_LASER_CH1_OFF;
            printf("SET LASER CH1 PWM OFF\n");
          }
          break;
        }
        case GDDC_PAGE_DIAGNOSIS_CALI_KEY_LAS_PWM_CH2:{
          if(state){
            SET_LASER_CH2_ON;
            printf("SET LASER CH2 PWM ON\n");
          }
          else{
            SET_LASER_CH2_OFF;
            printf("SET LASER CH3 PWM OFF\n");
          }
          break;
        }
        case GDDC_PAGE_DIAGNOSIS_CALI_KEY_LAS_PWM_CH3:{
          if(state){
            SET_LASER_CH3_ON;
            printf("SET LASER CH3 PWM ON\n");
          }
          else{
            SET_LASER_CH3_OFF;
            printf("SET LASER CH3 PWM OFF\n");
          }
          break;
        }
        case GDDC_PAGE_DIAGNOSIS_CALI_KEY_LAS_PWM_CH4:{
          if(state){
            SET_LASER_CH4_ON;
            printf("SET LASER CH4 PWM ON\n");
          }
          else{
            SET_LASER_CH4_OFF;
            printf("SET LASER CH0 PWM OFF\n");
          }
          break;
        }
        case GDDC_PAGE_DIAGNOSIS_CALI_KEY_LAS_PWM_CH5:{
          if(state){
            SET_LASER_CH5_ON;
            printf("SET LASER CH5 PWM ON\n");
          }
          else{
            SET_LASER_CH5_OFF;
            printf("SET LASER CH5 PWM OFF\n");
          }
          break;
        }
        case GDDC_PAGE_DIAGNOSIS_CALI_KEY_LAS_PWM_CH6:{
          if(state){
            SET_LASER_CH6_ON;
            printf("SET LASER CH6 PWM ON\n");
          }
          else{
            SET_LASER_CH6_OFF;
            printf("SET LASER CH6 PWM OFF\n");
          }
          break;
        }
        case GDDC_PAGE_DIAGNOSIS_CALI_KEY_LAS_PWM_CH7:{
          if(state){
            SET_LASER_CH7_ON;
            printf("SET LASER CH7 PWM ON\n");
          }
          else{
            SET_LASER_CH7_OFF;
            printf("SET LASER CH0 PWM OFF\n");
          }
          break;
        }
        case GDDC_PAGE_DIAGNOSIS_CALI_KEY_AUTOTUNE:{
          if(state){
            //PID_StartTune(&ClassicPid_A);
          }

        }
        default:break;
      }
      break;
    }
    case GDDC_PAGE_POWEROFF_CONFIRM:{
      switch(control_id){
        case GDDC_PAGE_POWEROFF_CONFIRM_KEY_YES:{
          if(state){
            NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_HIBERNATE;//进入关机确认状态
            NVRAM0[EM_DC_PAGE] = GDDC_PAGE_START;
            SetScreen(NVRAM0[EM_DC_PAGE]);
            PmuPowerDown();
          }
          break;
        }
        case GDDC_PAGE_POWEROFF_CONFIRM_KEY_CANCEL:{
          if(state){
            NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_STANDBY;//退出关机确认状态
            SetScreen(NVRAM0[EM_DC_PAGE]);
          }
          break;
        }
        default:break;
      }
      break;
    }
    default:break;
  }
}





