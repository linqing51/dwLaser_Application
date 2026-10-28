#ifndef __CLI_CONSOLE_H__
#define __CLI_CONSOLE_H__
/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/
/* FreeRTOS+CLI 控制台任务: 与 printf 共用调试串口(huart3)                    */
/* 输入: 轮询 huart3 RX 逐字符收集命令行, 回车执行                            */
/* 输出: 命令结果经 printf -> huart3 TX(与既有调试输出共享)                   */
void StartCliTask(void *argument);
/*****************************************************************************/
#ifdef __cplusplus
}
#endif
#endif /* __CLI_CONSOLE_H__ */
