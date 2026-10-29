/*----------------------------------------------------------------------------
 * 文件编码约定: 本文件为 UTF-8 编码(带BOM)。
 * 本工程源码统一使用 UTF-8(带BOM) 保存: 新建或修改任何源文件时,
 * 请以 UTF-8 编码保存, 并在文件头保留本注释。
 *----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * cli_console.c
 * FreeRTOS+CLI 控制台任务(应用层):
 *  - 输入: 轮询调试串口(CONFIG_DEBUG_UART=huart3) RX, 逐字符收集命令行
 *  - 执行: FreeRTOS_CLI_ProcessCommand 解释并生成输出
 *  - 输出: printf -> libdbg.c fputc -> 同一调试串口 TX(与既有调试信息共享)
 * 原有 printf 调试输出路径完全不变, CLI 只是新增一个消费同一串口的任务
 *----------------------------------------------------------------------------*/
#include "cli_console.h"
#include "FreeRTOS.h"
#include "task.h"
#include "FreeRTOS_CLI.h"
#include "cmd_fun.h"
#include "..\config\myConfig.h"
#include "stm32f4xx_hal.h"
/*****************************************************************************/
#define CLI_INPUT_MAX_LEN          120//命令行最大长度(含回车)
#define CLI_RX_POLL_TIMEOUT_MS     50 //RX轮询超时(ms), 兼顾任务调度
/*****************************************************************************/
void StartCliTask(void *argument){
    char cRxedChar;
    char pcInputString[CLI_INPUT_MAX_LEN];
    size_t uxInputStringLength = 0;
    BaseType_t xMoreDataToFollow;

    (void)argument;

    /* 注册所有CLI命令(见 cmd_fun.c) */
    CMD_Init();

    printf("\r\nFreeRTOS+CLI console ready. Type 'help' for command list.\r\n");

    for(;;){
        /* 轮询接收调试串口字符(与 printf 共用同一串口, 互不冲突) */
        if(HAL_UART_Receive(&CONFIG_DEBUG_UART, (uint8_t *)&cRxedChar, 1, CLI_RX_POLL_TIMEOUT_MS) == HAL_OK){
            if((cRxedChar == '\r') || (cRxedChar == '\n')){
                /* 回车: 执行命令行 */
                if(uxInputStringLength > 0){
                    pcInputString[uxInputStringLength] = 0;
                    uxInputStringLength = 0;
                    printf("\r\n");
                    do{
                        /* 解释命令, 输出写入 CLI 共享输出缓冲 */
                        xMoreDataToFollow = FreeRTOS_CLIProcessCommand(
                                                pcInputString,
                                                FreeRTOS_CLIGetOutputBuffer(),
                                                configCOMMAND_INT_MAX_OUTPUT_SIZE);
                        printf("%s", FreeRTOS_CLIGetOutputBuffer());
                    }while(xMoreDataToFollow != pdFALSE);
                    printf("\r\n");
                }
                else{
                    printf("\r\n");
                }
            }
            else if((cRxedChar == '\b') || (cRxedChar == 0x7F)){
                /* 退格/删除 */
                if(uxInputStringLength > 0){
                    uxInputStringLength--;
                    printf("\b \b");
                }
            }
            else if(uxInputStringLength < (CLI_INPUT_MAX_LEN - 1)){
                /* 普通字符: 入行缓冲并回显 */
                pcInputString[uxInputStringLength++] = cRxedChar;
                printf("%c", cRxedChar);
            }
        }
    }
}
