/*! 
*  \file cmd_queue.h
*  \brief 串口指令队列
*  \version 1.0
*  \date 2012-2018
*  \copyright 广州大彩光电科技有限公司
*/

#ifndef __HMICMDQUEUE_H__
#define __HMICMDQUEUE_H__
/*****************************************************************************/
#include "hmiLib.h"
/*****************************************************************************/
typedef unsigned char qdata;
typedef unsigned short qsize;

/*! 
*  \brief  清空指令数据
*/
extern void queue_reset(void);

/*! 
* \brief  添加指令数据
* \detial 串口接收的数据，通过此函数放入指令队列 
*  \param  _data 指令数据
*/
extern void queue_push(qdata _data);

/*! 
*  \brief  从指令队列中取出一条完整的指令
*  \param  cmd 指令接收缓存区
*  \param  buf_len 指令接收缓存区大小
*  \return  指令长度，0表示队列中无完整指令
*/
extern qsize queue_find_cmd(qdata *cmd,qsize buf_len);

#endif

