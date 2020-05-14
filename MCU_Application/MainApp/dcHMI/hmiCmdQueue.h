#ifndef __HMICMDQUEUE_H__
#define __HMICMDQUEUE_H__
/*****************************************************************************/
#include "hmiLib.h"
/*****************************************************************************/
typedef unsigned char qdata;
typedef unsigned short qsize;

/*! 
*  \brief  ���ָ������
*/
extern void queue_reset(void);

/*! 
* \brief  ���ָ������
* \detial ���ڽ��յ����ݣ�ͨ���˺�������ָ����� 
*  \param  _data ָ������
*/
extern void queue_push(qdata _data);

/*! 
*  \brief  ��ָ�������ȡ��һ��������ָ��
*  \param  cmd ָ����ջ�����
*  \param  buf_len ָ����ջ�������С
*  \return  ָ��ȣ�0��ʾ������������ָ��
*/
extern qsize queue_find_cmd(qdata *cmd,qsize buf_len);

#endif