/*----------------------------------------------------------------------------
 * 文件编码约定: 本文件为 UTF-8 编码(带BOM)。
 * 本工程源码统一使用 UTF-8(带BOM) 保存: 新建或修改任何源文件时,
 * 请以 UTF-8 编码保存, 并在文件头保留本注释。
 *----------------------------------------------------------------------------*/
#ifndef __MINICSVAPP_H__
#define __MINICSVAPP_H__
/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/
#include "minicsv.h"
#include "ff.h"
#include <string.h>
#include <stdio.h>
#include "dcHmiApp.h"
/*****************************************************************************/
//治疗记录导出/导入U盘(U盘CSV文件, 文件名由TREATMENTLOG_FILENAME定义)
typedef enum{
	TREATMENT_USB_OK = 0,//成功
	TREATMENT_USB_ERR_EMPTY,//机内无病历可导出
	TREATMENT_USB_ERR_MOUNT,//挂载U盘失败
	TREATMENT_USB_ERR_OPEN,//打开文件失败
	TREATMENT_USB_ERR_IO,//读写文件失败
	TREATMENT_USB_ERR_FORMAT//文件格式/字段内容非法
}treatmentUsbErr_t;

treatmentUsbErr_t treatmentLogSaveToUdisk(uint16_t *saved);//把机内全部病历写入U盘CSV(覆盖同名文件)
treatmentUsbErr_t treatmentLogLoadFromUdisk(uint16_t *loaded);//读取U盘CSV并覆盖机内病历(先清空再写入)
uint8_t treatmentUsbDiskPresent(void);//检查USBFS口U盘(MSC)是否已在位(1=在位, 0=不在位)

/******************************************************************************/
#ifdef __cplusplus
}
#endif

#endif

