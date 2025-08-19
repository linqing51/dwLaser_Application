#line 1 "..\\..\\deviceInfo\\preScheme.c"

#line 1 "..\\..\\deviceInfo\\preScheme.h"


 
#line 1 "../../sPlc/sPlc.h"


 
#line 1 "../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os.h"
























































































































 
 



#line 1 "../Middlewares/Third_Party/FreeRTOS/Source/include/FreeRTOS.h"

























 






 
#line 1 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stddef.h"
 






 

 
 
 





 





#line 34 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stddef.h"




  typedef signed int ptrdiff_t;



  



    typedef unsigned int size_t;    
#line 57 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stddef.h"



   



      typedef unsigned short wchar_t;  
#line 82 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stddef.h"



    




   




  typedef long double max_align_t;









#line 114 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stddef.h"



 

#line 35 "../Middlewares/Third_Party/FreeRTOS/Source/include/FreeRTOS.h"













 
#line 1 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"
 
 





 









     
#line 27 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"
     











#line 46 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"





 

     

     
typedef   signed          char int8_t;
typedef   signed short     int int16_t;
typedef   signed           int int32_t;
typedef   signed       __int64 int64_t;

     
typedef unsigned          char uint8_t;
typedef unsigned short     int uint16_t;
typedef unsigned           int uint32_t;
typedef unsigned       __int64 uint64_t;

     

     
     
typedef   signed          char int_least8_t;
typedef   signed short     int int_least16_t;
typedef   signed           int int_least32_t;
typedef   signed       __int64 int_least64_t;

     
typedef unsigned          char uint_least8_t;
typedef unsigned short     int uint_least16_t;
typedef unsigned           int uint_least32_t;
typedef unsigned       __int64 uint_least64_t;

     

     
typedef   signed           int int_fast8_t;
typedef   signed           int int_fast16_t;
typedef   signed           int int_fast32_t;
typedef   signed       __int64 int_fast64_t;

     
typedef unsigned           int uint_fast8_t;
typedef unsigned           int uint_fast16_t;
typedef unsigned           int uint_fast32_t;
typedef unsigned       __int64 uint_fast64_t;

     




typedef   signed           int intptr_t;
typedef unsigned           int uintptr_t;


     
typedef   signed     long long intmax_t;
typedef unsigned     long long uintmax_t;




     

     





     





     





     

     





     





     





     

     





     





     





     

     






     






     






     

     


     


     


     

     
#line 216 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"

     



     






     
    
 



#line 241 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"

     







     










     











#line 305 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"






 
#line 50 "../Middlewares/Third_Party/FreeRTOS/Source/include/FreeRTOS.h"





 
#line 1 "../Core/Inc/FreeRTOSConfig.h"
 


























 
 














 

 
 
 

 
#line 53 "../Core/Inc/FreeRTOSConfig.h"
  extern uint32_t SystemCoreClock;








#line 81 "../Core/Inc/FreeRTOSConfig.h"
 

 

 

 



 





 
#line 104 "../Core/Inc/FreeRTOSConfig.h"


 
#line 120 "../Core/Inc/FreeRTOSConfig.h"




 


 
#line 134 "../Core/Inc/FreeRTOSConfig.h"


 





 



 


 



 
 

 


 



 



 
 
 

#line 57 "../Middlewares/Third_Party/FreeRTOS/Source/include/FreeRTOS.h"

 
#line 1 "../Middlewares/Third_Party/FreeRTOS/Source/include/projdefs.h"

























 







 
typedef void (*TaskFunction_t)( void * );



 












 




 











 
#line 110 "../Middlewares/Third_Party/FreeRTOS/Source/include/projdefs.h"


 



 








#line 60 "../Middlewares/Third_Party/FreeRTOS/Source/include/FreeRTOS.h"

 
#line 1 "../Middlewares/Third_Party/FreeRTOS/Source/include/portable.h"

























 



 













 
#line 1 "../Middlewares/Third_Party/FreeRTOS/Source/include/deprecated_definitions.h"

























 












 











































































































































































#line 218 "../Middlewares/Third_Party/FreeRTOS/Source/include/deprecated_definitions.h"

#line 226 "../Middlewares/Third_Party/FreeRTOS/Source/include/deprecated_definitions.h"







#line 240 "../Middlewares/Third_Party/FreeRTOS/Source/include/deprecated_definitions.h"








































#line 46 "../Middlewares/Third_Party/FreeRTOS/Source/include/portable.h"




 
#line 1 "../Middlewares/Third_Party/FreeRTOS/Source/portable/RVDS/ARM_CM4F/portmacro.h"

























 

















 

 
#line 54 "../Middlewares/Third_Party/FreeRTOS/Source/portable/RVDS/ARM_CM4F/portmacro.h"

typedef uint32_t StackType_t;
typedef long BaseType_t;
typedef unsigned long UBaseType_t;





	typedef uint32_t TickType_t;


	
 


 

 




 


 

 
#line 93 "../Middlewares/Third_Party/FreeRTOS/Source/portable/RVDS/ARM_CM4F/portmacro.h"
 





 

 
extern void vPortEnterCritical( void );
extern void vPortExitCritical( void );

#line 111 "../Middlewares/Third_Party/FreeRTOS/Source/portable/RVDS/ARM_CM4F/portmacro.h"

 

 

	extern void vPortSuppressTicksAndSleep( TickType_t xExpectedIdleTime );


 

 




#line 142 "../Middlewares/Third_Party/FreeRTOS/Source/portable/RVDS/ARM_CM4F/portmacro.h"
 



 


 


	void vPortValidateInterruptPriority( void );



 








 

static __forceinline void vPortSetBASEPRI( uint32_t ulBASEPRI )
{
	__asm
	{
		
 
		msr basepri, ulBASEPRI
	}
}
 

static __forceinline void vPortRaiseBASEPRI( void )
{
uint32_t ulNewBASEPRI = ( 5 << (8 - 4) );

	__asm
	{
		
 
		msr basepri, ulNewBASEPRI
		dsb
		isb
	}
}
 

static __forceinline void vPortClearBASEPRIFromISR( void )
{
	__asm
	{
		

 
		msr basepri, #0
	}
}
 

static __forceinline uint32_t ulPortRaiseBASEPRI( void )
{
uint32_t ulReturn, ulNewBASEPRI = ( 5 << (8 - 4) );

	__asm
	{
		
 
		mrs ulReturn, basepri
		msr basepri, ulNewBASEPRI
		dsb
		isb
	}

	return ulReturn;
}
 

static __forceinline BaseType_t xPortIsInsideInterrupt( void )
{
uint32_t ulCurrentInterrupt;
BaseType_t xReturn;

	 
	__asm
	{
		mrs ulCurrentInterrupt, ipsr
	}

	if( ulCurrentInterrupt == 0 )
	{
		xReturn = ( ( BaseType_t ) 0 );
	}
	else
	{
		xReturn = ( ( BaseType_t ) 1 );
	}

	return xReturn;
}








#line 53 "../Middlewares/Third_Party/FreeRTOS/Source/include/portable.h"














































#line 1 "../Middlewares/Third_Party/FreeRTOS/Source/include/mpu_wrappers.h"

























 





 
#line 179 "../Middlewares/Third_Party/FreeRTOS/Source/include/mpu_wrappers.h"











#line 100 "../Middlewares/Third_Party/FreeRTOS/Source/include/portable.h"






 
#line 117 "../Middlewares/Third_Party/FreeRTOS/Source/include/portable.h"
		StackType_t *pxPortInitialiseStack( StackType_t *pxTopOfStack, TaskFunction_t pxCode, void *pvParameters ) ;




 
typedef struct HeapRegion
{
	uint8_t *pucStartAddress;
	size_t xSizeInBytes;
} HeapRegion_t;

 
typedef struct xHeapStats
{
	size_t xAvailableHeapSpaceInBytes;		 
	size_t xSizeOfLargestFreeBlockInBytes; 	 
	size_t xSizeOfSmallestFreeBlockInBytes;  
	size_t xNumberOfFreeBlocks;				 
	size_t xMinimumEverFreeBytesRemaining;	 
	size_t xNumberOfSuccessfulAllocations;	 
	size_t xNumberOfSuccessfulFrees;		 
} HeapStats_t;











 
void vPortDefineHeapRegions( const HeapRegion_t * const pxHeapRegions ) ;




 
void vPortGetHeapStats( HeapStats_t *pxHeapStats );



 
void *pvPortMalloc( size_t xSize ) ;
void vPortFree( void *pv ) ;
void vPortInitialiseBlocks( void ) ;
size_t xPortGetFreeHeapSize( void ) ;
size_t xPortGetMinimumEverFreeHeapSize( void ) ;




 
BaseType_t xPortStartScheduler( void ) ;





 
void vPortEndScheduler( void ) ;







 











#line 63 "../Middlewares/Third_Party/FreeRTOS/Source/include/FreeRTOS.h"

 




 







 































































































































































#line 243 "../Middlewares/Third_Party/FreeRTOS/Source/include/FreeRTOS.h"





 
#line 255 "../Middlewares/Third_Party/FreeRTOS/Source/include/FreeRTOS.h"









 


















































 

	
 




	
 




	
 




	
 




	 




	 




	
 




	



 




	


 




	


 




	


 




	


 















 





















































































































































































































































































































#line 732 "../Middlewares/Third_Party/FreeRTOS/Source/include/FreeRTOS.h"




























































































































	
 



#line 867 "../Middlewares/Third_Party/FreeRTOS/Source/include/FreeRTOS.h"

 


















#line 896 "../Middlewares/Third_Party/FreeRTOS/Source/include/FreeRTOS.h"
	
 







 





	








 




	
 




	
 



#line 957 "../Middlewares/Third_Party/FreeRTOS/Source/include/FreeRTOS.h"

	
 





	
 










 





 





 





 





 













































 












 
struct xSTATIC_LIST_ITEM
{



	TickType_t xDummy2;
	void *pvDummy3[ 4 ];



};
typedef struct xSTATIC_LIST_ITEM StaticListItem_t;

 
struct xSTATIC_MINI_LIST_ITEM
{



	TickType_t xDummy2;
	void *pvDummy3[ 2 ];
};
typedef struct xSTATIC_MINI_LIST_ITEM StaticMiniListItem_t;

 
typedef struct xSTATIC_LIST
{



	UBaseType_t uxDummy2;
	void *pvDummy3;
	StaticMiniListItem_t xDummy4;



} StaticList_t;













 
typedef struct xSTATIC_TCB
{
	void				*pxDummy1;



	StaticListItem_t	xDummy3[ 2 ];
	UBaseType_t			uxDummy5;
	void				*pxDummy6;
	uint8_t				ucDummy7[ ( 16 ) ];
#line 1129 "../Middlewares/Third_Party/FreeRTOS/Source/include/FreeRTOS.h"
		UBaseType_t		uxDummy10[ 2 ];


		UBaseType_t		uxDummy12[ 2 ];


		void			*pxDummy14;
#line 1147 "../Middlewares/Third_Party/FreeRTOS/Source/include/FreeRTOS.h"
		uint32_t 		ulDummy18;
		uint8_t 		ucDummy19;


		uint8_t			uxDummy20;


#line 1160 "../Middlewares/Third_Party/FreeRTOS/Source/include/FreeRTOS.h"
} StaticTask_t;














 
typedef struct xSTATIC_QUEUE
{
	void *pvDummy1[ 3 ];

	union
	{
		void *pvDummy2;
		UBaseType_t uxDummy2;
	} u;

	StaticList_t xDummy3[ 2 ];
	UBaseType_t uxDummy4[ 3 ];
	uint8_t ucDummy5[ 2 ];


		uint8_t ucDummy6;







		UBaseType_t uxDummy8;
		uint8_t ucDummy9;


} StaticQueue_t;
typedef StaticQueue_t StaticSemaphore_t;














 
typedef struct xSTATIC_EVENT_GROUP
{
	TickType_t xDummy1;
	StaticList_t xDummy2;


		UBaseType_t uxDummy3;



			uint8_t ucDummy4;


} StaticEventGroup_t;














 
typedef struct xSTATIC_TIMER
{
	void				*pvDummy1;
	StaticListItem_t	xDummy2;
	TickType_t			xDummy3;
	void 				*pvDummy5;
	TaskFunction_t		pvDummy6;

		UBaseType_t		uxDummy7;

	uint8_t 			ucDummy8;

} StaticTimer_t;














 
typedef struct xSTATIC_STREAM_BUFFER
{
	size_t uxDummy1[ 4 ];
	void * pvDummy2[ 3 ];
	uint8_t ucDummy3;

		UBaseType_t uxDummy4;

} StaticStreamBuffer_t;

 
typedef StaticStreamBuffer_t StaticMessageBuffer_t;







#line 127 "../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os.h"
#line 1 "../Middlewares/Third_Party/FreeRTOS/Source/include/task.h"

























 









#line 1 "../Middlewares/Third_Party/FreeRTOS/Source/include/list.h"

























 



























 



































 












 

	 
#line 134 "../Middlewares/Third_Party/FreeRTOS/Source/include/list.h"




 
struct xLIST;
struct xLIST_ITEM
{
				 
	 TickType_t xItemValue;			 
	struct xLIST_ITEM *  pxNext;		 
	struct xLIST_ITEM *  pxPrevious;	 
	void * pvOwner;										 
	struct xLIST *  pvContainer;		 
				 
};
typedef struct xLIST_ITEM ListItem_t;					 

struct xMINI_LIST_ITEM
{
				 
	 TickType_t xItemValue;
	struct xLIST_ITEM *  pxNext;
	struct xLIST_ITEM *  pxPrevious;
};
typedef struct xMINI_LIST_ITEM MiniListItem_t;



 
typedef struct xLIST
{
					 
	volatile UBaseType_t uxNumberOfItems;
	ListItem_t *  pxIndex;			 
	MiniListItem_t xListEnd;							 
					 
} List_t;







 








 








 









 








 







 







 







 








 




 





















 
#line 289 "../Middlewares/Third_Party/FreeRTOS/Source/include/list.h"

















 










 







 






 











 
void vListInitialise( List_t * const pxList ) ;









 
void vListInitialiseItem( ListItem_t * const pxItem ) ;











 
void vListInsert( List_t * const pxList, ListItem_t * const pxNewListItem ) ;



















 
void vListInsertEnd( List_t * const pxList, ListItem_t * const pxNewListItem ) ;













 
UBaseType_t uxListRemove( ListItem_t * const pxItemToRemove ) ;







#line 37 "../Middlewares/Third_Party/FreeRTOS/Source/include/task.h"







 







 















 
struct tskTaskControlBlock;  
typedef struct tskTaskControlBlock* TaskHandle_t;




 
typedef BaseType_t (*TaskHookFunction_t)( void * );

 
typedef enum
{
	eRunning = 0,	 
	eReady,			 
	eBlocked,		 
	eSuspended,		 
	eDeleted,		 
	eInvalid		 
} eTaskState;

 
typedef enum
{
	eNoAction = 0,				 
	eSetBits,					 
	eIncrement,					 
	eSetValueWithOverwrite,		 
	eSetValueWithoutOverwrite	 
} eNotifyAction;



 
typedef struct xTIME_OUT
{
	BaseType_t xOverflowCount;
	TickType_t xTimeOnEntering;
} TimeOut_t;



 
typedef struct xMEMORY_REGION
{
	void *pvBaseAddress;
	uint32_t ulLengthInBytes;
	uint32_t ulParameters;
} MemoryRegion_t;



 
typedef struct xTASK_PARAMETERS
{
	TaskFunction_t pvTaskCode;
	const char * const pcName;	 
	uint16_t usStackDepth;
	void *pvParameters;
	UBaseType_t uxPriority;
	StackType_t *puxStackBuffer;
	MemoryRegion_t xRegions[ 1 ];



} TaskParameters_t;


 
typedef struct xTASK_STATUS
{
	TaskHandle_t xHandle;			 
	const char *pcTaskName;			   
	UBaseType_t xTaskNumber;		 
	eTaskState eCurrentState;		 
	UBaseType_t uxCurrentPriority;	 
	UBaseType_t uxBasePriority;		 
	uint32_t ulRunTimeCounter;		 
	StackType_t *pxStackBase;		 
	uint16_t usStackHighWaterMark;	 
} TaskStatus_t;

 
typedef enum
{
	eAbortSleep = 0,		 
	eStandardSleep,			 
	eNoTasksWaitingTimeout	 
} eSleepModeStatus;





 









 













 














 









 









 




 







 





























































































 

	BaseType_t xTaskCreate(	TaskFunction_t pxTaskCode,
							const char * const pcName,	 
							const uint16_t usStackDepth,
							void * const pvParameters,
							UBaseType_t uxPriority,
							TaskHandle_t * const pxCreatedTask ) ;












































































































 

	TaskHandle_t xTaskCreateStatic(	TaskFunction_t pxTaskCode,
									const char * const pcName,  
									const uint32_t ulStackDepth,
									void * const pvParameters,
									UBaseType_t uxPriority,
									StackType_t * const puxStackBuffer,
									StaticTask_t * const pxTaskBuffer ) ;









































































 























































































 

















































 
void vTaskAllocateMPURegions( TaskHandle_t xTask, const MemoryRegion_t * const pxRegions ) ;







































 
void vTaskDelete( TaskHandle_t xTaskToDelete ) ;



 














































 
void vTaskDelay( const TickType_t xTicksToDelay ) ;

























































 
void vTaskDelayUntil( TickType_t * const pxPreviousWakeTime, const TickType_t xTimeIncrement ) ;




























 
BaseType_t xTaskAbortDelay( TaskHandle_t xTask ) ;













































 
UBaseType_t uxTaskPriorityGet( const TaskHandle_t xTask ) ;






 
UBaseType_t uxTaskPriorityGetFromISR( const TaskHandle_t xTask ) ;
















 
eTaskState eTaskGetState( TaskHandle_t xTask ) ;






















































 
void vTaskGetInfo( TaskHandle_t xTask, TaskStatus_t *pxTaskStatus, BaseType_t xGetFreeStackSpace, eTaskState eState ) ;








































 
void vTaskPrioritySet( TaskHandle_t xTask, UBaseType_t uxNewPriority ) ;

















































 
void vTaskSuspend( TaskHandle_t xTaskToSuspend ) ;















































 
void vTaskResume( TaskHandle_t xTaskToResume ) ;



























 
BaseType_t xTaskResumeFromISR( TaskHandle_t xTaskToResume ) ;



 



























 
void vTaskStartScheduler( void ) ;






















































 
void vTaskEndScheduler( void ) ;

















































 
void vTaskSuspendAll( void ) ;




















































 
BaseType_t xTaskResumeAll( void ) ;



 









 
TickType_t xTaskGetTickCount( void ) ;














 
TickType_t xTaskGetTickCountFromISR( void ) ;












 
UBaseType_t uxTaskGetNumberOfTasks( void ) ;











 
char *pcTaskGetName( TaskHandle_t xTaskToQuery ) ;  














 
TaskHandle_t xTaskGetHandle( const char *pcNameToQuery ) ;  

























 
UBaseType_t uxTaskGetStackHighWaterMark( TaskHandle_t xTask ) ;

























 
uint16_t uxTaskGetStackHighWaterMark2( TaskHandle_t xTask ) ;






 


		






 
		void vTaskSetApplicationTaskTag( TaskHandle_t xTask, TaskHookFunction_t pxHookFunction ) ;

		






 
		TaskHookFunction_t xTaskGetApplicationTaskTag( TaskHandle_t xTask ) ;

		





 
		TaskHookFunction_t xTaskGetApplicationTaskTagFromISR( TaskHandle_t xTask ) ;



#line 1521 "../Middlewares/Third_Party/FreeRTOS/Source/include/task.h"











 
BaseType_t xTaskCallApplicationTaskHook( TaskHandle_t xTask, void *pvParameter ) ;







 
TaskHandle_t xTaskGetIdleTaskHandle( void ) ;

































































































 
UBaseType_t uxTaskGetSystemState( TaskStatus_t * const pxTaskStatusArray, const UBaseType_t uxArraySize, uint32_t * const pulTotalRunTime ) ;













































 
void vTaskList( char * pcWriteBuffer ) ;  




















































 
void vTaskGetRunTimeStats( char *pcWriteBuffer ) ;  




























 
uint32_t ulTaskGetIdleRunTimeCounter( void ) ;















































































 
BaseType_t xTaskGenericNotify( TaskHandle_t xTaskToNotify, uint32_t ulValue, eNotifyAction eAction, uint32_t *pulPreviousNotificationValue ) ;

























































































 
BaseType_t xTaskGenericNotifyFromISR( TaskHandle_t xTaskToNotify, uint32_t ulValue, eNotifyAction eAction, uint32_t *pulPreviousNotificationValue, BaseType_t *pxHigherPriorityTaskWoken ) ;











































































 
BaseType_t xTaskNotifyWait( uint32_t ulBitsToClearOnEntry, uint32_t ulBitsToClearOnExit, uint32_t *pulNotificationValue, TickType_t xTicksToWait ) ;












































 






















































 
void vTaskNotifyGiveFromISR( TaskHandle_t xTaskToNotify, BaseType_t *pxHigherPriorityTaskWoken ) ;



































































 
uint32_t ulTaskNotifyTake( BaseType_t xClearCountOnExit, TickType_t xTicksToWait ) ;














 
BaseType_t xTaskNotifyStateClear( TaskHandle_t xTask );
















 
uint32_t ulTaskNotifyValueClear( TaskHandle_t xTask, uint32_t ulBitsToClear ) ;












 
void vTaskSetTimeOutState( TimeOut_t * const pxTimeOut ) ;

















































































 
BaseType_t xTaskCheckForTimeOut( TimeOut_t * const pxTimeOut, TickType_t * const pxTicksToWait ) ;



 















 
BaseType_t xTaskIncrementTick( void ) ;































 
void vTaskPlaceOnEventList( List_t * const pxEventList, const TickType_t xTicksToWait ) ;
void vTaskPlaceOnUnorderedEventList( List_t * pxEventList, const TickType_t xItemValue, const TickType_t xTicksToWait ) ;











 
void vTaskPlaceOnEventListRestricted( List_t * const pxEventList, TickType_t xTicksToWait, const BaseType_t xWaitIndefinitely ) ;
























 
BaseType_t xTaskRemoveFromEventList( const List_t * const pxEventList ) ;
void vTaskRemoveFromUnorderedEventList( ListItem_t * pxEventListItem, const TickType_t xItemValue ) ;








 
 void vTaskSwitchContext( void ) ;




 
TickType_t uxTaskResetEventItemValue( void ) ;



 
TaskHandle_t xTaskGetCurrentTaskHandle( void ) ;




 
void vTaskMissedYield( void ) ;




 
BaseType_t xTaskGetSchedulerState( void ) ;




 
BaseType_t xTaskPriorityInherit( TaskHandle_t const pxMutexHolder ) ;




 
BaseType_t xTaskPriorityDisinherit( TaskHandle_t const pxMutexHolder ) ;








 
void vTaskPriorityDisinheritAfterTimeout( TaskHandle_t const pxMutexHolder, UBaseType_t uxHighestPriorityWaitingTask ) ;



 
UBaseType_t uxTaskGetTaskNumber( TaskHandle_t xTask ) ;




 
void vTaskSetTaskNumber( TaskHandle_t xTask, const UBaseType_t uxHandle ) ;








 
void vTaskStepTick( const TickType_t xTicksToJump ) ;











 
BaseType_t xTaskCatchUpTicks( TickType_t xTicksToCatchUp ) ;














 
eSleepModeStatus eTaskConfirmSleepModeStatus( void ) ;




 
TaskHandle_t pvTaskIncrementMutexHeldCount( void ) ;




 
void vTaskInternalSetTimeOutState( TimeOut_t * const pxTimeOut ) ;









#line 128 "../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os.h"







 

 
#line 146 "../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os.h"
 
#line 154 "../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os.h"
 
#line 1 "../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os2.h"






















 




#line 41 "../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os2.h"

#line 43 "../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os2.h"
#line 44 "../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os2.h"










typedef struct {
  uint32_t                       api;   
  uint32_t                    kernel;   
} osVersion_t;


typedef enum {
  osKernelInactive        =  0,         
  osKernelReady           =  1,         
  osKernelRunning         =  2,         
  osKernelLocked          =  3,         
  osKernelSuspended       =  4,         
  osKernelError           = -1,         
  osKernelReserved        = 0x7FFFFFFFU 
} osKernelState_t;


typedef enum {
  osThreadInactive        =  0,         
  osThreadReady           =  1,         
  osThreadRunning         =  2,         
  osThreadBlocked         =  3,         
  osThreadTerminated      =  4,         
  osThreadError           = -1,         
  osThreadReserved        = 0x7FFFFFFF  
} osThreadState_t;


typedef enum {
  osPriorityNone          =  0,         
  osPriorityIdle          =  1,         
  osPriorityLow           =  8,         
  osPriorityLow1          =  8+1,       
  osPriorityLow2          =  8+2,       
  osPriorityLow3          =  8+3,       
  osPriorityLow4          =  8+4,       
  osPriorityLow5          =  8+5,       
  osPriorityLow6          =  8+6,       
  osPriorityLow7          =  8+7,       
  osPriorityBelowNormal   = 16,         
  osPriorityBelowNormal1  = 16+1,       
  osPriorityBelowNormal2  = 16+2,       
  osPriorityBelowNormal3  = 16+3,       
  osPriorityBelowNormal4  = 16+4,       
  osPriorityBelowNormal5  = 16+5,       
  osPriorityBelowNormal6  = 16+6,       
  osPriorityBelowNormal7  = 16+7,       
  osPriorityNormal        = 24,         
  osPriorityNormal1       = 24+1,       
  osPriorityNormal2       = 24+2,       
  osPriorityNormal3       = 24+3,       
  osPriorityNormal4       = 24+4,       
  osPriorityNormal5       = 24+5,       
  osPriorityNormal6       = 24+6,       
  osPriorityNormal7       = 24+7,       
  osPriorityAboveNormal   = 32,         
  osPriorityAboveNormal1  = 32+1,       
  osPriorityAboveNormal2  = 32+2,       
  osPriorityAboveNormal3  = 32+3,       
  osPriorityAboveNormal4  = 32+4,       
  osPriorityAboveNormal5  = 32+5,       
  osPriorityAboveNormal6  = 32+6,       
  osPriorityAboveNormal7  = 32+7,       
  osPriorityHigh          = 40,         
  osPriorityHigh1         = 40+1,       
  osPriorityHigh2         = 40+2,       
  osPriorityHigh3         = 40+3,       
  osPriorityHigh4         = 40+4,       
  osPriorityHigh5         = 40+5,       
  osPriorityHigh6         = 40+6,       
  osPriorityHigh7         = 40+7,       
  osPriorityRealtime      = 48,         
  osPriorityRealtime1     = 48+1,       
  osPriorityRealtime2     = 48+2,       
  osPriorityRealtime3     = 48+3,       
  osPriorityRealtime4     = 48+4,       
  osPriorityRealtime5     = 48+5,       
  osPriorityRealtime6     = 48+6,       
  osPriorityRealtime7     = 48+7,       
  osPriorityISR           = 56,         
  osPriorityError         = -1,         
  osPriorityReserved      = 0x7FFFFFFF  
} osPriority_t;


typedef void (*osThreadFunc_t) (void *argument);


typedef void (*osTimerFunc_t) (void *argument);


typedef enum {
  osTimerOnce               = 0,          
  osTimerPeriodic           = 1           
} osTimerType_t;










#line 165 "../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os2.h"











typedef enum {
  osOK                      =  0,         
  osError                   = -1,         
  osErrorTimeout            = -2,         
  osErrorResource           = -3,         
  osErrorParameter          = -4,         
  osErrorNoMemory           = -5,         
  osErrorISR                = -6,         
  osStatusReserved          = 0x7FFFFFFF  
} osStatus_t;



typedef void *osThreadId_t;


typedef void *osTimerId_t;


typedef void *osEventFlagsId_t;


typedef void *osMutexId_t;


typedef void *osSemaphoreId_t;


typedef void *osMemoryPoolId_t;


typedef void *osMessageQueueId_t;





typedef uint32_t TZ_ModuleId_t;




typedef struct {
  const char                   *name;   
  uint32_t                 attr_bits;   
  void                      *cb_mem;    
  uint32_t                   cb_size;   
  void                   *stack_mem;    
  uint32_t                stack_size;   
  osPriority_t              priority;   
  TZ_ModuleId_t            tz_module;   
  uint32_t                  reserved;   
} osThreadAttr_t;


typedef struct {
  const char                   *name;   
  uint32_t                 attr_bits;   
  void                      *cb_mem;    
  uint32_t                   cb_size;   
} osTimerAttr_t;


typedef struct {
  const char                   *name;   
  uint32_t                 attr_bits;   
  void                      *cb_mem;    
  uint32_t                   cb_size;   
} osEventFlagsAttr_t;


typedef struct {
  const char                   *name;   
  uint32_t                 attr_bits;   
  void                      *cb_mem;    
  uint32_t                   cb_size;   
} osMutexAttr_t;


typedef struct {
  const char                   *name;   
  uint32_t                 attr_bits;   
  void                      *cb_mem;    
  uint32_t                   cb_size;   
} osSemaphoreAttr_t;


typedef struct {
  const char                   *name;   
  uint32_t                 attr_bits;   
  void                      *cb_mem;    
  uint32_t                   cb_size;   
  void                      *mp_mem;    
  uint32_t                   mp_size;   
} osMemoryPoolAttr_t;


typedef struct {
  const char                   *name;   
  uint32_t                 attr_bits;   
  void                      *cb_mem;    
  uint32_t                   cb_size;   
  void                      *mq_mem;    
  uint32_t                   mq_size;   
} osMessageQueueAttr_t;






osStatus_t osKernelInitialize (void);






osStatus_t osKernelGetInfo (osVersion_t *version, char *id_buf, uint32_t id_size);



osKernelState_t osKernelGetState (void);



osStatus_t osKernelStart (void);



int32_t osKernelLock (void);



int32_t osKernelUnlock (void);




int32_t osKernelRestoreLock (int32_t lock);



uint32_t osKernelSuspend (void);



void osKernelResume (uint32_t sleep_ticks);



uint32_t osKernelGetTickCount (void);



uint32_t osKernelGetTickFreq (void);



uint32_t osKernelGetSysTimerCount (void);



uint32_t osKernelGetSysTimerFreq (void);









osThreadId_t osThreadNew (osThreadFunc_t func, void *argument, const osThreadAttr_t *attr);




const char *osThreadGetName (osThreadId_t thread_id);



osThreadId_t osThreadGetId (void);




osThreadState_t osThreadGetState (osThreadId_t thread_id);




uint32_t osThreadGetStackSize (osThreadId_t thread_id);




uint32_t osThreadGetStackSpace (osThreadId_t thread_id);





osStatus_t osThreadSetPriority (osThreadId_t thread_id, osPriority_t priority);




osPriority_t osThreadGetPriority (osThreadId_t thread_id);



osStatus_t osThreadYield (void);




osStatus_t osThreadSuspend (osThreadId_t thread_id);




osStatus_t osThreadResume (osThreadId_t thread_id);




osStatus_t osThreadDetach (osThreadId_t thread_id);




osStatus_t osThreadJoin (osThreadId_t thread_id);


__declspec(noreturn) void osThreadExit (void);




osStatus_t osThreadTerminate (osThreadId_t thread_id);



uint32_t osThreadGetCount (void);





uint32_t osThreadEnumerate (osThreadId_t *thread_array, uint32_t array_items);








uint32_t osThreadFlagsSet (osThreadId_t thread_id, uint32_t flags);




uint32_t osThreadFlagsClear (uint32_t flags);



uint32_t osThreadFlagsGet (void);






uint32_t osThreadFlagsWait (uint32_t flags, uint32_t options, uint32_t timeout);







osStatus_t osDelay (uint32_t ticks);




osStatus_t osDelayUntil (uint32_t ticks);










osTimerId_t osTimerNew (osTimerFunc_t func, osTimerType_t type, void *argument, const osTimerAttr_t *attr);




const char *osTimerGetName (osTimerId_t timer_id);





osStatus_t osTimerStart (osTimerId_t timer_id, uint32_t ticks);




osStatus_t osTimerStop (osTimerId_t timer_id);




uint32_t osTimerIsRunning (osTimerId_t timer_id);




osStatus_t osTimerDelete (osTimerId_t timer_id);







osEventFlagsId_t osEventFlagsNew (const osEventFlagsAttr_t *attr);




const char *osEventFlagsGetName (osEventFlagsId_t ef_id);





uint32_t osEventFlagsSet (osEventFlagsId_t ef_id, uint32_t flags);





uint32_t osEventFlagsClear (osEventFlagsId_t ef_id, uint32_t flags);




uint32_t osEventFlagsGet (osEventFlagsId_t ef_id);







uint32_t osEventFlagsWait (osEventFlagsId_t ef_id, uint32_t flags, uint32_t options, uint32_t timeout);




osStatus_t osEventFlagsDelete (osEventFlagsId_t ef_id);







osMutexId_t osMutexNew (const osMutexAttr_t *attr);




const char *osMutexGetName (osMutexId_t mutex_id);





osStatus_t osMutexAcquire (osMutexId_t mutex_id, uint32_t timeout);




osStatus_t osMutexRelease (osMutexId_t mutex_id);




osThreadId_t osMutexGetOwner (osMutexId_t mutex_id);




osStatus_t osMutexDelete (osMutexId_t mutex_id);









osSemaphoreId_t osSemaphoreNew (uint32_t max_count, uint32_t initial_count, const osSemaphoreAttr_t *attr);




const char *osSemaphoreGetName (osSemaphoreId_t semaphore_id);





osStatus_t osSemaphoreAcquire (osSemaphoreId_t semaphore_id, uint32_t timeout);




osStatus_t osSemaphoreRelease (osSemaphoreId_t semaphore_id);




uint32_t osSemaphoreGetCount (osSemaphoreId_t semaphore_id);




osStatus_t osSemaphoreDelete (osSemaphoreId_t semaphore_id);









osMemoryPoolId_t osMemoryPoolNew (uint32_t block_count, uint32_t block_size, const osMemoryPoolAttr_t *attr);




const char *osMemoryPoolGetName (osMemoryPoolId_t mp_id);





void *osMemoryPoolAlloc (osMemoryPoolId_t mp_id, uint32_t timeout);





osStatus_t osMemoryPoolFree (osMemoryPoolId_t mp_id, void *block);




uint32_t osMemoryPoolGetCapacity (osMemoryPoolId_t mp_id);




uint32_t osMemoryPoolGetBlockSize (osMemoryPoolId_t mp_id);




uint32_t osMemoryPoolGetCount (osMemoryPoolId_t mp_id);




uint32_t osMemoryPoolGetSpace (osMemoryPoolId_t mp_id);




osStatus_t osMemoryPoolDelete (osMemoryPoolId_t mp_id);









osMessageQueueId_t osMessageQueueNew (uint32_t msg_count, uint32_t msg_size, const osMessageQueueAttr_t *attr);




const char *osMessageQueueGetName (osMessageQueueId_t mq_id);







osStatus_t osMessageQueuePut (osMessageQueueId_t mq_id, const void *msg_ptr, uint8_t msg_prio, uint32_t timeout);







osStatus_t osMessageQueueGet (osMessageQueueId_t mq_id, void *msg_ptr, uint8_t *msg_prio, uint32_t timeout);




uint32_t osMessageQueueGetCapacity (osMessageQueueId_t mq_id);




uint32_t osMessageQueueGetMsgSize (osMessageQueueId_t mq_id);




uint32_t osMessageQueueGetCount (osMessageQueueId_t mq_id);




uint32_t osMessageQueueGetSpace (osMessageQueueId_t mq_id);




osStatus_t osMessageQueueReset (osMessageQueueId_t mq_id);




osStatus_t osMessageQueueDelete (osMessageQueueId_t mq_id);






#line 156 "../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os.h"
 




 
 

 

#line 181 "../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os.h"


typedef void (*os_pthread) (void const *argument);
 

typedef void (*os_ptimer) (void const *argument);
 

#line 197 "../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os.h"
 


 

#line 221 "../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os.h"
typedef int32_t                  osStatus;
#line 232 "../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os.h"
 
 

 






 






 






 






 

typedef void *osPoolId;
 

typedef void *osMessageQId;
 

typedef void *osMailQId;
 
 

#line 283 "../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os.h"
typedef struct os_thread_def {
  os_pthread                 pthread;   
  osThreadAttr_t                attr;   
} osThreadDef_t;

 






typedef struct os_timer_def {
  os_ptimer                   ptimer;   
  osTimerAttr_t                 attr;   
} osTimerDef_t;

 

#line 309 "../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os.h"
 

#line 318 "../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os.h"
 

#line 327 "../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os.h"
typedef struct os_pool_def {
  uint32_t                   pool_sz;   
  uint32_t                   item_sz;   
  osMemoryPoolAttr_t            attr;   
} osPoolDef_t;

 

#line 341 "../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os.h"
typedef struct os_messageQ_def {
  uint32_t                  queue_sz;   
  osMessageQueueAttr_t          attr;   
} osMessageQDef_t;

 

#line 355 "../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os.h"
typedef struct os_mailQ_def {
  uint32_t                  queue_sz;   
  uint32_t                   item_sz;   
  void                         *mail;   
  osMemoryPoolAttr_t         mp_attr;   
  osMessageQueueAttr_t       mq_attr;   
} osMailQDef_t;

 
 

typedef struct {
  osStatus                    status;   
  union {
    uint32_t                       v;   
    void                          *p;   
    int32_t                  signals;   
  } value;                              
  union {
    osMailQId                mail_id;   
    osMessageQId          message_id;   
  } def;                                
} osEvent;
 
 

 





 





 





 

 







 





 








 

 
 

 





#line 451 "../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os.h"
 




 




osThreadId_t osThreadCreate (const osThreadDef_t *thread_def, void *argument);
 





 







 






 





 






 
 

 




int32_t osSignalSet (osThreadId_t thread_id, int32_t signals);
 




int32_t osSignalClear (osThreadId_t thread_id, int32_t signals);
 




__value_in_regs osEvent osSignalWait (int32_t signals, uint32_t millisec);
 
 

 






 
#line 536 "../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os.h"
 
 

 



#line 552 "../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os.h"
 




 





osTimerId_t osTimerCreate (const osTimerDef_t *timer_def, osTimerType_t type, void *argument);
 







 






 






 
 

 


#line 601 "../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os.h"
 




 



osMutexId_t osMutexCreate (const osMutexAttr_t *mutex_def);
 









 






 






 
 

 

 


#line 652 "../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os.h"
 




 




osSemaphoreId_t osSemaphoreCreate (const osSemaphoreAttr_t *semaphore_def, int32_t count);
 




int32_t osSemaphoreWait (osSemaphoreId_t semaphore_id, uint32_t millisec);
 






 






 

 
 


#line 731 "../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os.h"
 
 

 

  




#line 753 "../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os.h"
 




 




osMessageQId osMessageCreate (const osMessageQDef_t *queue_def, osThreadId_t thread_id);
 





osStatus osMessagePut (osMessageQId queue_id, uint32_t info, uint32_t millisec);
 




__value_in_regs osEvent osMessageGet (osMessageQId queue_id, uint32_t millisec);
 

 
 

 
#line 840 "../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os.h"
 
 



 
#line 5 "../../sPlc/sPlc.h"
#line 1 "../Core/Inc/main.h"
 
















 
 

 







 
#line 1 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal.h"

















  

 







 
#line 1 "../Core/Inc/stm32f4xx_hal_conf.h"
 


















 
 

 







 
 

 


 


   

 

 

 
 
 
 
 
 
 
 
 
 

 
 
 

 
 
 
 
 


 
 
 
 
 
 

 
 
 
 
 
 
 
 
 
#line 91 "../Core/Inc/stm32f4xx_hal_conf.h"

 




 












 






 







 












 





 

 


 
#line 156 "../Core/Inc/stm32f4xx_hal_conf.h"

#line 196 "../Core/Inc/stm32f4xx_hal_conf.h"

 



 
 

 

 

 
#line 215 "../Core/Inc/stm32f4xx_hal_conf.h"

 





 

 

 

 





 




#line 249 "../Core/Inc/stm32f4xx_hal_conf.h"





 





 




 



 


 

#line 1 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"















 

 







 
#line 1 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_def.h"

















 

 







 
#line 1 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f4xx.h"


























 



 



 










 



 






 
#line 94 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f4xx.h"



 
#line 106 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f4xx.h"



 
#line 118 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f4xx.h"



 



 

#line 1 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"






















 



 



 










 



 








 



 




 
typedef enum
{
   
  NonMaskableInt_IRQn         = -14,     
  MemoryManagement_IRQn       = -12,     
  BusFault_IRQn               = -11,     
  UsageFault_IRQn             = -10,     
  SVCall_IRQn                 = -5,      
  DebugMonitor_IRQn           = -4,      
  PendSV_IRQn                 = -2,      
  SysTick_IRQn                = -1,      
   
  WWDG_IRQn                   = 0,       
  PVD_IRQn                    = 1,       
  TAMP_STAMP_IRQn             = 2,       
  RTC_WKUP_IRQn               = 3,       
  FLASH_IRQn                  = 4,       
  RCC_IRQn                    = 5,       
  EXTI0_IRQn                  = 6,       
  EXTI1_IRQn                  = 7,       
  EXTI2_IRQn                  = 8,       
  EXTI3_IRQn                  = 9,       
  EXTI4_IRQn                  = 10,      
  DMA1_Stream0_IRQn           = 11,      
  DMA1_Stream1_IRQn           = 12,      
  DMA1_Stream2_IRQn           = 13,      
  DMA1_Stream3_IRQn           = 14,      
  DMA1_Stream4_IRQn           = 15,      
  DMA1_Stream5_IRQn           = 16,      
  DMA1_Stream6_IRQn           = 17,      
  ADC_IRQn                    = 18,      
  CAN1_TX_IRQn                = 19,      
  CAN1_RX0_IRQn               = 20,      
  CAN1_RX1_IRQn               = 21,      
  CAN1_SCE_IRQn               = 22,      
  EXTI9_5_IRQn                = 23,      
  TIM1_BRK_TIM9_IRQn          = 24,      
  TIM1_UP_TIM10_IRQn          = 25,      
  TIM1_TRG_COM_TIM11_IRQn     = 26,      
  TIM1_CC_IRQn                = 27,      
  TIM2_IRQn                   = 28,      
  TIM3_IRQn                   = 29,      
  TIM4_IRQn                   = 30,      
  I2C1_EV_IRQn                = 31,      
  I2C1_ER_IRQn                = 32,      
  I2C2_EV_IRQn                = 33,      
  I2C2_ER_IRQn                = 34,      
  SPI1_IRQn                   = 35,      
  SPI2_IRQn                   = 36,      
  USART1_IRQn                 = 37,      
  USART2_IRQn                 = 38,      
  USART3_IRQn                 = 39,      
  EXTI15_10_IRQn              = 40,      
  RTC_Alarm_IRQn              = 41,      
  OTG_FS_WKUP_IRQn            = 42,      
  TIM8_BRK_TIM12_IRQn         = 43,      
  TIM8_UP_TIM13_IRQn          = 44,      
  TIM8_TRG_COM_TIM14_IRQn     = 45,      
  TIM8_CC_IRQn                = 46,      
  DMA1_Stream7_IRQn           = 47,      
  FSMC_IRQn                   = 48,      
  SDIO_IRQn                   = 49,      
  TIM5_IRQn                   = 50,      
  SPI3_IRQn                   = 51,      
  UART4_IRQn                  = 52,      
  UART5_IRQn                  = 53,      
  TIM6_DAC_IRQn               = 54,      
  TIM7_IRQn                   = 55,      
  DMA2_Stream0_IRQn           = 56,      
  DMA2_Stream1_IRQn           = 57,      
  DMA2_Stream2_IRQn           = 58,      
  DMA2_Stream3_IRQn           = 59,      
  DMA2_Stream4_IRQn           = 60,      
  CAN2_TX_IRQn                = 63,      
  CAN2_RX0_IRQn               = 64,      
  CAN2_RX1_IRQn               = 65,      
  CAN2_SCE_IRQn               = 66,      
  OTG_FS_IRQn                 = 67,      
  DMA2_Stream5_IRQn           = 68,      
  DMA2_Stream6_IRQn           = 69,      
  DMA2_Stream7_IRQn           = 70,      
  USART6_IRQn                 = 71,      
  I2C3_EV_IRQn                = 72,      
  I2C3_ER_IRQn                = 73,      
  OTG_HS_EP1_OUT_IRQn         = 74,      
  OTG_HS_EP1_IN_IRQn          = 75,      
  OTG_HS_WKUP_IRQn            = 76,      
  OTG_HS_IRQn                 = 77,      
  RNG_IRQn                    = 80,      
  FPU_IRQn                    = 81       
} IRQn_Type;
 




 

#line 1 "../Drivers/CMSIS/Include/core_cm4.h"
 




 
















 










#line 35 "../Drivers/CMSIS/Include/core_cm4.h"

















 




 



 

#line 1 "../Drivers/CMSIS/Include/cmsis_version.h"
 




 
















 










 
#line 64 "../Drivers/CMSIS/Include/core_cm4.h"

 









 
#line 87 "../Drivers/CMSIS/Include/core_cm4.h"

#line 161 "../Drivers/CMSIS/Include/core_cm4.h"

#line 1 "../Drivers/CMSIS/Include/cmsis_compiler.h"
 




 
















 




#line 29 "../Drivers/CMSIS/Include/cmsis_compiler.h"



 
#line 1 "../Drivers/CMSIS/Include/cmsis_armcc.h"
 




 
















 









 













   
   
   

 




 
#line 111 "../Drivers/CMSIS/Include/cmsis_armcc.h"

 





















 



 




 






 







 






 








 






 






 








 








 

__attribute__((section(".rev16_text"))) static __inline __asm uint32_t __REV16(uint32_t value)
{
  rev16 r0, r0
  bx lr
}








 

__attribute__((section(".revsh_text"))) static __inline __asm int16_t __REVSH(int16_t value)
{
  revsh r0, r0
  bx lr
}









 









 








 
#line 277 "../Drivers/CMSIS/Include/cmsis_armcc.h"







 











 












 












 














 














 














 










 









 









 









 

__attribute__((section(".rrx_text"))) static __inline __asm uint32_t __RRX(uint32_t value)
{
  rrx r0, r0
  bx lr
}








 








 








 








 








 








 


#line 525 "../Drivers/CMSIS/Include/cmsis_armcc.h"

   


 



 





 
 






 
 





 
static __inline uint32_t __get_CONTROL(void)
{
  register uint32_t __regControl         __asm("control");
  return(__regControl);
}






 
static __inline void __set_CONTROL(uint32_t control)
{
  register uint32_t __regControl         __asm("control");
  __regControl = control;
  __isb(0xF);
}






 
static __inline uint32_t __get_IPSR(void)
{
  register uint32_t __regIPSR          __asm("ipsr");
  return(__regIPSR);
}






 
static __inline uint32_t __get_APSR(void)
{
  register uint32_t __regAPSR          __asm("apsr");
  return(__regAPSR);
}






 
static __inline uint32_t __get_xPSR(void)
{
  register uint32_t __regXPSR          __asm("xpsr");
  return(__regXPSR);
}






 
static __inline uint32_t __get_PSP(void)
{
  register uint32_t __regProcessStackPointer  __asm("psp");
  return(__regProcessStackPointer);
}






 
static __inline void __set_PSP(uint32_t topOfProcStack)
{
  register uint32_t __regProcessStackPointer  __asm("psp");
  __regProcessStackPointer = topOfProcStack;
}






 
static __inline uint32_t __get_MSP(void)
{
  register uint32_t __regMainStackPointer     __asm("msp");
  return(__regMainStackPointer);
}






 
static __inline void __set_MSP(uint32_t topOfMainStack)
{
  register uint32_t __regMainStackPointer     __asm("msp");
  __regMainStackPointer = topOfMainStack;
}






 
static __inline uint32_t __get_PRIMASK(void)
{
  register uint32_t __regPriMask         __asm("primask");
  return(__regPriMask);
}






 
static __inline void __set_PRIMASK(uint32_t priMask)
{
  register uint32_t __regPriMask         __asm("primask");
  __regPriMask = (priMask);
}









 







 







 
static __inline uint32_t  __get_BASEPRI(void)
{
  register uint32_t __regBasePri         __asm("basepri");
  return(__regBasePri);
}






 
static __inline void __set_BASEPRI(uint32_t basePri)
{
  register uint32_t __regBasePri         __asm("basepri");
  __regBasePri = (basePri & 0xFFU);
}







 
static __inline void __set_BASEPRI_MAX(uint32_t basePri)
{
  register uint32_t __regBasePriMax      __asm("basepri_max");
  __regBasePriMax = (basePri & 0xFFU);
}






 
static __inline uint32_t __get_FAULTMASK(void)
{
  register uint32_t __regFaultMask       __asm("faultmask");
  return(__regFaultMask);
}






 
static __inline void __set_FAULTMASK(uint32_t faultMask)
{
  register uint32_t __regFaultMask       __asm("faultmask");
  __regFaultMask = (faultMask & (uint32_t)1U);
}









 
static __inline uint32_t __get_FPSCR(void)
{


  register uint32_t __regfpscr         __asm("fpscr");
  return(__regfpscr);



}






 
static __inline void __set_FPSCR(uint32_t fpscr)
{


  register uint32_t __regfpscr         __asm("fpscr");
  __regfpscr = (fpscr);



}


 


 



 



#line 870 "../Drivers/CMSIS/Include/cmsis_armcc.h"















 


#line 35 "../Drivers/CMSIS/Include/cmsis_compiler.h"




 
#line 280 "../Drivers/CMSIS/Include/cmsis_compiler.h"




#line 163 "../Drivers/CMSIS/Include/core_cm4.h"

















 
#line 212 "../Drivers/CMSIS/Include/core_cm4.h"

 






 
#line 228 "../Drivers/CMSIS/Include/core_cm4.h"

 




 













 



 






 



 
typedef union
{
  struct
  {
    uint32_t _reserved0:16;               
    uint32_t GE:4;                        
    uint32_t _reserved1:7;                
    uint32_t Q:1;                         
    uint32_t V:1;                         
    uint32_t C:1;                         
    uint32_t Z:1;                         
    uint32_t N:1;                         
  } b;                                    
  uint32_t w;                             
} APSR_Type;

 





















 
typedef union
{
  struct
  {
    uint32_t ISR:9;                       
    uint32_t _reserved0:23;               
  } b;                                    
  uint32_t w;                             
} IPSR_Type;

 






 
typedef union
{
  struct
  {
    uint32_t ISR:9;                       
    uint32_t _reserved0:1;                
    uint32_t ICI_IT_1:6;                  
    uint32_t GE:4;                        
    uint32_t _reserved1:4;                
    uint32_t T:1;                         
    uint32_t ICI_IT_2:2;                  
    uint32_t Q:1;                         
    uint32_t V:1;                         
    uint32_t C:1;                         
    uint32_t Z:1;                         
    uint32_t N:1;                         
  } b;                                    
  uint32_t w;                             
} xPSR_Type;

 

































 
typedef union
{
  struct
  {
    uint32_t nPRIV:1;                     
    uint32_t SPSEL:1;                     
    uint32_t FPCA:1;                      
    uint32_t _reserved0:29;               
  } b;                                    
  uint32_t w;                             
} CONTROL_Type;

 









 







 



 
typedef struct
{
  volatile uint32_t ISER[8U];                
        uint32_t RESERVED0[24U];
  volatile uint32_t ICER[8U];                
        uint32_t RESERVED1[24U];
  volatile uint32_t ISPR[8U];                
        uint32_t RESERVED2[24U];
  volatile uint32_t ICPR[8U];                
        uint32_t RESERVED3[24U];
  volatile uint32_t IABR[8U];                
        uint32_t RESERVED4[56U];
  volatile uint8_t  IP[240U];                
        uint32_t RESERVED5[644U];
  volatile  uint32_t STIR;                    
}  NVIC_Type;

 



 







 



 
typedef struct
{
  volatile const  uint32_t CPUID;                   
  volatile uint32_t ICSR;                    
  volatile uint32_t VTOR;                    
  volatile uint32_t AIRCR;                   
  volatile uint32_t SCR;                     
  volatile uint32_t CCR;                     
  volatile uint8_t  SHP[12U];                
  volatile uint32_t SHCSR;                   
  volatile uint32_t CFSR;                    
  volatile uint32_t HFSR;                    
  volatile uint32_t DFSR;                    
  volatile uint32_t MMFAR;                   
  volatile uint32_t BFAR;                    
  volatile uint32_t AFSR;                    
  volatile const  uint32_t PFR[2U];                 
  volatile const  uint32_t DFR;                     
  volatile const  uint32_t ADR;                     
  volatile const  uint32_t MMFR[4U];                
  volatile const  uint32_t ISAR[5U];                
        uint32_t RESERVED0[5U];
  volatile uint32_t CPACR;                   
} SCB_Type;

 















 






























 



 





















 









 


















 










































 









 


















 





















 


















 









 















 







 



 
typedef struct
{
        uint32_t RESERVED0[1U];
  volatile const  uint32_t ICTR;                    
  volatile uint32_t ACTLR;                   
} SCnSCB_Type;

 



 















 







 



 
typedef struct
{
  volatile uint32_t CTRL;                    
  volatile uint32_t LOAD;                    
  volatile uint32_t VAL;                     
  volatile const  uint32_t CALIB;                   
} SysTick_Type;

 












 



 



 









 







 



 
typedef struct
{
  volatile  union
  {
    volatile  uint8_t    u8;                  
    volatile  uint16_t   u16;                 
    volatile  uint32_t   u32;                 
  }  PORT [32U];                          
        uint32_t RESERVED0[864U];
  volatile uint32_t TER;                     
        uint32_t RESERVED1[15U];
  volatile uint32_t TPR;                     
        uint32_t RESERVED2[15U];
  volatile uint32_t TCR;                     
        uint32_t RESERVED3[32U];
        uint32_t RESERVED4[43U];
  volatile  uint32_t LAR;                     
  volatile const  uint32_t LSR;                     
        uint32_t RESERVED5[6U];
  volatile const  uint32_t PID4;                    
  volatile const  uint32_t PID5;                    
  volatile const  uint32_t PID6;                    
  volatile const  uint32_t PID7;                    
  volatile const  uint32_t PID0;                    
  volatile const  uint32_t PID1;                    
  volatile const  uint32_t PID2;                    
  volatile const  uint32_t PID3;                    
  volatile const  uint32_t CID0;                    
  volatile const  uint32_t CID1;                    
  volatile const  uint32_t CID2;                    
  volatile const  uint32_t CID3;                    
} ITM_Type;

 



 



























 









   







 



 
typedef struct
{
  volatile uint32_t CTRL;                    
  volatile uint32_t CYCCNT;                  
  volatile uint32_t CPICNT;                  
  volatile uint32_t EXCCNT;                  
  volatile uint32_t SLEEPCNT;                
  volatile uint32_t LSUCNT;                  
  volatile uint32_t FOLDCNT;                 
  volatile const  uint32_t PCSR;                    
  volatile uint32_t COMP0;                   
  volatile uint32_t MASK0;                   
  volatile uint32_t FUNCTION0;               
        uint32_t RESERVED0[1U];
  volatile uint32_t COMP1;                   
  volatile uint32_t MASK1;                   
  volatile uint32_t FUNCTION1;               
        uint32_t RESERVED1[1U];
  volatile uint32_t COMP2;                   
  volatile uint32_t MASK2;                   
  volatile uint32_t FUNCTION2;               
        uint32_t RESERVED2[1U];
  volatile uint32_t COMP3;                   
  volatile uint32_t MASK3;                   
  volatile uint32_t FUNCTION3;               
} DWT_Type;

 






















































 



 



 



 



 



 



 



























   







 



 
typedef struct
{
  volatile const  uint32_t SSPSR;                   
  volatile uint32_t CSPSR;                   
        uint32_t RESERVED0[2U];
  volatile uint32_t ACPR;                    
        uint32_t RESERVED1[55U];
  volatile uint32_t SPPR;                    
        uint32_t RESERVED2[131U];
  volatile const  uint32_t FFSR;                    
  volatile uint32_t FFCR;                    
  volatile const  uint32_t FSCR;                    
        uint32_t RESERVED3[759U];
  volatile const  uint32_t TRIGGER;                 
  volatile const  uint32_t FIFO0;                   
  volatile const  uint32_t ITATBCTR2;               
        uint32_t RESERVED4[1U];
  volatile const  uint32_t ITATBCTR0;               
  volatile const  uint32_t FIFO1;                   
  volatile uint32_t ITCTRL;                  
        uint32_t RESERVED5[39U];
  volatile uint32_t CLAIMSET;                
  volatile uint32_t CLAIMCLR;                
        uint32_t RESERVED7[8U];
  volatile const  uint32_t DEVID;                   
  volatile const  uint32_t DEVTYPE;                 
} TPI_Type;

 



 



 












 






 



 





















 






 





















 






 



 


















 






   








 



 
typedef struct
{
  volatile const  uint32_t TYPE;                    
  volatile uint32_t CTRL;                    
  volatile uint32_t RNR;                     
  volatile uint32_t RBAR;                    
  volatile uint32_t RASR;                    
  volatile uint32_t RBAR_A1;                 
  volatile uint32_t RASR_A1;                 
  volatile uint32_t RBAR_A2;                 
  volatile uint32_t RASR_A2;                 
  volatile uint32_t RBAR_A3;                 
  volatile uint32_t RASR_A3;                 
} MPU_Type;



 









 









 



 









 






























 








 



 
typedef struct
{
        uint32_t RESERVED0[1U];
  volatile uint32_t FPCCR;                   
  volatile uint32_t FPCAR;                   
  volatile uint32_t FPDSCR;                  
  volatile const  uint32_t MVFR0;                   
  volatile const  uint32_t MVFR1;                   
  volatile const  uint32_t MVFR2;                   
} FPU_Type;

 



























 



 












 
























 












 




 







 



 
typedef struct
{
  volatile uint32_t DHCSR;                   
  volatile  uint32_t DCRSR;                   
  volatile uint32_t DCRDR;                   
  volatile uint32_t DEMCR;                   
} CoreDebug_Type;

 




































 






 







































 







 






 







 


 







 

 
#line 1558 "../Drivers/CMSIS/Include/core_cm4.h"

#line 1567 "../Drivers/CMSIS/Include/core_cm4.h"









 










 


 



 





 

#line 1621 "../Drivers/CMSIS/Include/core_cm4.h"

#line 1631 "../Drivers/CMSIS/Include/core_cm4.h"




 
#line 1642 "../Drivers/CMSIS/Include/core_cm4.h"










 
static __inline void __NVIC_SetPriorityGrouping(uint32_t PriorityGroup)
{
  uint32_t reg_value;
  uint32_t PriorityGroupTmp = (PriorityGroup & (uint32_t)0x07UL);              

  reg_value  =  ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR;                                                    
  reg_value &= ~((uint32_t)((0xFFFFUL << 16U) | (7UL << 8U)));  
  reg_value  =  (reg_value                                   |
                ((uint32_t)0x5FAUL << 16U) |
                (PriorityGroupTmp << 8U)  );               
  ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR =  reg_value;
}






 
static __inline uint32_t __NVIC_GetPriorityGrouping(void)
{
  return ((uint32_t)((((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR & (7UL << 8U)) >> 8U));
}







 
static __inline void __NVIC_EnableIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    __memory_changed();
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISER[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
    __memory_changed();
  }
}









 
static __inline uint32_t __NVIC_GetEnableIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    return((uint32_t)(((((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISER[(((uint32_t)IRQn) >> 5UL)] & (1UL << (((uint32_t)IRQn) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
  }
  else
  {
    return(0U);
  }
}







 
static __inline void __NVIC_DisableIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ICER[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
    __dsb(0xF);
    __isb(0xF);
  }
}









 
static __inline uint32_t __NVIC_GetPendingIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    return((uint32_t)(((((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISPR[(((uint32_t)IRQn) >> 5UL)] & (1UL << (((uint32_t)IRQn) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
  }
  else
  {
    return(0U);
  }
}







 
static __inline void __NVIC_SetPendingIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISPR[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
  }
}







 
static __inline void __NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ICPR[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
  }
}









 
static __inline uint32_t __NVIC_GetActive(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    return((uint32_t)(((((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IABR[(((uint32_t)IRQn) >> 5UL)] & (1UL << (((uint32_t)IRQn) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
  }
  else
  {
    return(0U);
  }
}










 
static __inline void __NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority)
{
  if ((int32_t)(IRQn) >= 0)
  {
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IP[((uint32_t)IRQn)]               = (uint8_t)((priority << (8U - 4U)) & (uint32_t)0xFFUL);
  }
  else
  {
    ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHP[(((uint32_t)IRQn) & 0xFUL)-4UL] = (uint8_t)((priority << (8U - 4U)) & (uint32_t)0xFFUL);
  }
}










 
static __inline uint32_t __NVIC_GetPriority(IRQn_Type IRQn)
{

  if ((int32_t)(IRQn) >= 0)
  {
    return(((uint32_t)((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IP[((uint32_t)IRQn)]               >> (8U - 4U)));
  }
  else
  {
    return(((uint32_t)((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHP[(((uint32_t)IRQn) & 0xFUL)-4UL] >> (8U - 4U)));
  }
}












 
static __inline uint32_t NVIC_EncodePriority (uint32_t PriorityGroup, uint32_t PreemptPriority, uint32_t SubPriority)
{
  uint32_t PriorityGroupTmp = (PriorityGroup & (uint32_t)0x07UL);    
  uint32_t PreemptPriorityBits;
  uint32_t SubPriorityBits;

  PreemptPriorityBits = ((7UL - PriorityGroupTmp) > (uint32_t)(4U)) ? (uint32_t)(4U) : (uint32_t)(7UL - PriorityGroupTmp);
  SubPriorityBits     = ((PriorityGroupTmp + (uint32_t)(4U)) < (uint32_t)7UL) ? (uint32_t)0UL : (uint32_t)((PriorityGroupTmp - 7UL) + (uint32_t)(4U));

  return (
           ((PreemptPriority & (uint32_t)((1UL << (PreemptPriorityBits)) - 1UL)) << SubPriorityBits) |
           ((SubPriority     & (uint32_t)((1UL << (SubPriorityBits    )) - 1UL)))
         );
}












 
static __inline void NVIC_DecodePriority (uint32_t Priority, uint32_t PriorityGroup, uint32_t* const pPreemptPriority, uint32_t* const pSubPriority)
{
  uint32_t PriorityGroupTmp = (PriorityGroup & (uint32_t)0x07UL);    
  uint32_t PreemptPriorityBits;
  uint32_t SubPriorityBits;

  PreemptPriorityBits = ((7UL - PriorityGroupTmp) > (uint32_t)(4U)) ? (uint32_t)(4U) : (uint32_t)(7UL - PriorityGroupTmp);
  SubPriorityBits     = ((PriorityGroupTmp + (uint32_t)(4U)) < (uint32_t)7UL) ? (uint32_t)0UL : (uint32_t)((PriorityGroupTmp - 7UL) + (uint32_t)(4U));

  *pPreemptPriority = (Priority >> SubPriorityBits) & (uint32_t)((1UL << (PreemptPriorityBits)) - 1UL);
  *pSubPriority     = (Priority                   ) & (uint32_t)((1UL << (SubPriorityBits    )) - 1UL);
}










 
static __inline void __NVIC_SetVector(IRQn_Type IRQn, uint32_t vector)
{
  uint32_t *vectors = (uint32_t *)((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->VTOR;
  vectors[(int32_t)IRQn + 16] = vector;
   
}









 
static __inline uint32_t __NVIC_GetVector(IRQn_Type IRQn)
{
  uint32_t *vectors = (uint32_t *)((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->VTOR;
  return vectors[(int32_t)IRQn + 16];
}





 
__declspec(noreturn) static __inline void __NVIC_SystemReset(void)
{
  __dsb(0xF);                                                          
 
  ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR  = (uint32_t)((0x5FAUL << 16U)    |
                           (((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR & (7UL << 8U)) |
                            (1UL << 2U)    );          
  __dsb(0xF);                                                           

  for(;;)                                                            
  {
    __nop();
  }
}

 


 



#line 1 "../Drivers/CMSIS/Include/mpu_armv7.h"





 
















 
 





 



#line 62 "../Drivers/CMSIS/Include/mpu_armv7.h"

#line 69 "../Drivers/CMSIS/Include/mpu_armv7.h"





 












   














 
#line 110 "../Drivers/CMSIS/Include/mpu_armv7.h"












                          









  










  












  




 




 




 




 





 
typedef struct {
  uint32_t RBAR; 
  uint32_t RASR; 
} ARM_MPU_Region_t;
    


 
static __inline void ARM_MPU_Enable(uint32_t MPU_Control)
{
  __dmb(0xF);
  ((MPU_Type *) ((0xE000E000UL) + 0x0D90UL) )->CTRL = MPU_Control | (1UL );

  ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHCSR |= (1UL << 16U);

  __dsb(0xF);
  __isb(0xF);
}


 
static __inline void ARM_MPU_Disable(void)
{
  __dmb(0xF);

  ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHCSR &= ~(1UL << 16U);

  ((MPU_Type *) ((0xE000E000UL) + 0x0D90UL) )->CTRL  &= ~(1UL );
  __dsb(0xF);
  __isb(0xF);
}



 
static __inline void ARM_MPU_ClrRegion(uint32_t rnr)
{
  ((MPU_Type *) ((0xE000E000UL) + 0x0D90UL) )->RNR = rnr;
  ((MPU_Type *) ((0xE000E000UL) + 0x0D90UL) )->RASR = 0U;
}




    
static __inline void ARM_MPU_SetRegion(uint32_t rbar, uint32_t rasr)
{
  ((MPU_Type *) ((0xE000E000UL) + 0x0D90UL) )->RBAR = rbar;
  ((MPU_Type *) ((0xE000E000UL) + 0x0D90UL) )->RASR = rasr;
}





    
static __inline void ARM_MPU_SetRegionEx(uint32_t rnr, uint32_t rbar, uint32_t rasr)
{
  ((MPU_Type *) ((0xE000E000UL) + 0x0D90UL) )->RNR = rnr;
  ((MPU_Type *) ((0xE000E000UL) + 0x0D90UL) )->RBAR = rbar;
  ((MPU_Type *) ((0xE000E000UL) + 0x0D90UL) )->RASR = rasr;
}





 
static __inline void ARM_MPU_OrderedMemcpy(volatile uint32_t* dst, const uint32_t* __restrict src, uint32_t len)
{
  uint32_t i;
  for (i = 0U; i < len; ++i) 
  {
    dst[i] = src[i];
  }
}




 
static __inline void ARM_MPU_Load(ARM_MPU_Region_t const* table, uint32_t cnt) 
{
  const uint32_t rowWordSize = sizeof(ARM_MPU_Region_t)/4U;
  while (cnt > 4U) {
    ARM_MPU_OrderedMemcpy(&(((MPU_Type *) ((0xE000E000UL) + 0x0D90UL) )->RBAR), &(table->RBAR), 4U*rowWordSize);
    table += 4U;
    cnt -= 4U;
  }
  ARM_MPU_OrderedMemcpy(&(((MPU_Type *) ((0xE000E000UL) + 0x0D90UL) )->RBAR), &(table->RBAR), cnt*rowWordSize);
}

#line 1961 "../Drivers/CMSIS/Include/core_cm4.h"




 





 








 
static __inline uint32_t SCB_GetFPUType(void)
{
  uint32_t mvfr0;

  mvfr0 = ((FPU_Type *) ((0xE000E000UL) + 0x0F30UL) )->MVFR0;
  if      ((mvfr0 & ((0xFUL << 4U) | (0xFUL << 8U))) == 0x020U)
  {
    return 1U;            
  }
  else
  {
    return 0U;            
  }
}


 



 





 













 
static __inline uint32_t SysTick_Config(uint32_t ticks)
{
  if ((ticks - 1UL) > (0xFFFFFFUL ))
  {
    return (1UL);                                                    
  }

  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->LOAD  = (uint32_t)(ticks - 1UL);                          
  __NVIC_SetPriority (SysTick_IRQn, (1UL << 4U) - 1UL);  
  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->VAL   = 0UL;                                              
  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->CTRL  = (1UL << 2U) |
                   (1UL << 1U)   |
                   (1UL );                          
  return (0UL);                                                      
}



 



 





 

extern volatile int32_t ITM_RxBuffer;                               










 
static __inline uint32_t ITM_SendChar (uint32_t ch)
{
  if (((((ITM_Type *) (0xE0000000UL) )->TCR & (1UL )) != 0UL) &&       
      ((((ITM_Type *) (0xE0000000UL) )->TER & 1UL               ) != 0UL)   )      
  {
    while (((ITM_Type *) (0xE0000000UL) )->PORT[0U].u32 == 0UL)
    {
      __nop();
    }
    ((ITM_Type *) (0xE0000000UL) )->PORT[0U].u8 = (uint8_t)ch;
  }
  return (ch);
}







 
static __inline int32_t ITM_ReceiveChar (void)
{
  int32_t ch = -1;                            

  if (ITM_RxBuffer != ((int32_t)0x5AA55AA5U))
  {
    ch = ITM_RxBuffer;
    ITM_RxBuffer = ((int32_t)0x5AA55AA5U);        
  }

  return (ch);
}







 
static __inline int32_t ITM_CheckChar (void)
{

  if (ITM_RxBuffer == ((int32_t)0x5AA55AA5U))
  {
    return (0);                               
  }
  else
  {
    return (1);                               
  }
}

 










#line 164 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"
#line 1 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/system_stm32f4xx.h"
















 



 



 



 









 



 




 







 
extern uint32_t SystemCoreClock;           

extern const uint8_t  AHBPrescTable[16];     
extern const uint8_t  APBPrescTable[8];      



 



 



 



 



 



 

extern void SystemInit(void);
extern void SystemCoreClockUpdate(void);


 









 



 
#line 165 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"
#line 166 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"



 



 

typedef struct
{
  volatile uint32_t SR;      
  volatile uint32_t CR1;     
  volatile uint32_t CR2;     
  volatile uint32_t SMPR1;   
  volatile uint32_t SMPR2;   
  volatile uint32_t JOFR1;   
  volatile uint32_t JOFR2;   
  volatile uint32_t JOFR3;   
  volatile uint32_t JOFR4;   
  volatile uint32_t HTR;     
  volatile uint32_t LTR;     
  volatile uint32_t SQR1;    
  volatile uint32_t SQR2;    
  volatile uint32_t SQR3;    
  volatile uint32_t JSQR;    
  volatile uint32_t JDR1;    
  volatile uint32_t JDR2;    
  volatile uint32_t JDR3;    
  volatile uint32_t JDR4;    
  volatile uint32_t DR;      
} ADC_TypeDef;

typedef struct
{
  volatile uint32_t CSR;     
  volatile uint32_t CCR;     
  volatile uint32_t CDR;    
 
} ADC_Common_TypeDef;




 

typedef struct
{
  volatile uint32_t TIR;   
  volatile uint32_t TDTR;  
  volatile uint32_t TDLR;  
  volatile uint32_t TDHR;  
} CAN_TxMailBox_TypeDef;



 

typedef struct
{
  volatile uint32_t RIR;   
  volatile uint32_t RDTR;  
  volatile uint32_t RDLR;  
  volatile uint32_t RDHR;  
} CAN_FIFOMailBox_TypeDef;



 

typedef struct
{
  volatile uint32_t FR1;  
  volatile uint32_t FR2;  
} CAN_FilterRegister_TypeDef;



 

typedef struct
{
  volatile uint32_t              MCR;                  
  volatile uint32_t              MSR;                  
  volatile uint32_t              TSR;                  
  volatile uint32_t              RF0R;                 
  volatile uint32_t              RF1R;                 
  volatile uint32_t              IER;                  
  volatile uint32_t              ESR;                  
  volatile uint32_t              BTR;                  
  uint32_t                   RESERVED0[88];        
  CAN_TxMailBox_TypeDef      sTxMailBox[3];        
  CAN_FIFOMailBox_TypeDef    sFIFOMailBox[2];      
  uint32_t                   RESERVED1[12];        
  volatile uint32_t              FMR;                  
  volatile uint32_t              FM1R;                 
  uint32_t                   RESERVED2;            
  volatile uint32_t              FS1R;                 
  uint32_t                   RESERVED3;            
  volatile uint32_t              FFA1R;                
  uint32_t                   RESERVED4;            
  volatile uint32_t              FA1R;                 
  uint32_t                   RESERVED5[8];         
  CAN_FilterRegister_TypeDef sFilterRegister[28];  
} CAN_TypeDef;



 

typedef struct
{
  volatile uint32_t DR;          
  volatile uint8_t  IDR;         
  uint8_t       RESERVED0;   
  uint16_t      RESERVED1;   
  volatile uint32_t CR;          
} CRC_TypeDef;



 

typedef struct
{
  volatile uint32_t CR;        
  volatile uint32_t SWTRIGR;   
  volatile uint32_t DHR12R1;   
  volatile uint32_t DHR12L1;   
  volatile uint32_t DHR8R1;    
  volatile uint32_t DHR12R2;   
  volatile uint32_t DHR12L2;   
  volatile uint32_t DHR8R2;    
  volatile uint32_t DHR12RD;   
  volatile uint32_t DHR12LD;   
  volatile uint32_t DHR8RD;    
  volatile uint32_t DOR1;      
  volatile uint32_t DOR2;      
  volatile uint32_t SR;        
} DAC_TypeDef;



 

typedef struct
{
  volatile uint32_t IDCODE;   
  volatile uint32_t CR;       
  volatile uint32_t APB1FZ;   
  volatile uint32_t APB2FZ;   
} DBGMCU_TypeDef;




 

typedef struct
{
  volatile uint32_t CR;      
  volatile uint32_t NDTR;    
  volatile uint32_t PAR;     
  volatile uint32_t M0AR;    
  volatile uint32_t M1AR;    
  volatile uint32_t FCR;     
} DMA_Stream_TypeDef;

typedef struct
{
  volatile uint32_t LISR;    
  volatile uint32_t HISR;    
  volatile uint32_t LIFCR;   
  volatile uint32_t HIFCR;   
} DMA_TypeDef;



 

typedef struct
{
  volatile uint32_t IMR;     
  volatile uint32_t EMR;     
  volatile uint32_t RTSR;    
  volatile uint32_t FTSR;    
  volatile uint32_t SWIER;   
  volatile uint32_t PR;      
} EXTI_TypeDef;



 

typedef struct
{
  volatile uint32_t ACR;       
  volatile uint32_t KEYR;      
  volatile uint32_t OPTKEYR;   
  volatile uint32_t SR;        
  volatile uint32_t CR;        
  volatile uint32_t OPTCR;     
  volatile uint32_t OPTCR1;    
} FLASH_TypeDef;





 

typedef struct
{
  volatile uint32_t BTCR[8];     
} FSMC_Bank1_TypeDef;



 

typedef struct
{
  volatile uint32_t BWTR[7];     
} FSMC_Bank1E_TypeDef;



 

typedef struct
{
  volatile uint32_t PCR2;        
  volatile uint32_t SR2;         
  volatile uint32_t PMEM2;       
  volatile uint32_t PATT2;       
  uint32_t      RESERVED0;   
  volatile uint32_t ECCR2;       
  uint32_t      RESERVED1;   
  uint32_t      RESERVED2;   
  volatile uint32_t PCR3;        
  volatile uint32_t SR3;         
  volatile uint32_t PMEM3;       
  volatile uint32_t PATT3;       
  uint32_t      RESERVED3;   
  volatile uint32_t ECCR3;       
} FSMC_Bank2_3_TypeDef;



 

typedef struct
{
  volatile uint32_t PCR4;        
  volatile uint32_t SR4;         
  volatile uint32_t PMEM4;       
  volatile uint32_t PATT4;       
  volatile uint32_t PIO4;        
} FSMC_Bank4_TypeDef;



 

typedef struct
{
  volatile uint32_t MODER;     
  volatile uint32_t OTYPER;    
  volatile uint32_t OSPEEDR;   
  volatile uint32_t PUPDR;     
  volatile uint32_t IDR;       
  volatile uint32_t ODR;       
  volatile uint32_t BSRR;      
  volatile uint32_t LCKR;      
  volatile uint32_t AFR[2];    
} GPIO_TypeDef;



 

typedef struct
{
  volatile uint32_t MEMRMP;        
  volatile uint32_t PMC;           
  volatile uint32_t EXTICR[4];     
  uint32_t      RESERVED[2];   
  volatile uint32_t CMPCR;         
} SYSCFG_TypeDef;



 

typedef struct
{
  volatile uint32_t CR1;         
  volatile uint32_t CR2;         
  volatile uint32_t OAR1;        
  volatile uint32_t OAR2;        
  volatile uint32_t DR;          
  volatile uint32_t SR1;         
  volatile uint32_t SR2;         
  volatile uint32_t CCR;         
  volatile uint32_t TRISE;       
} I2C_TypeDef;



 

typedef struct
{
  volatile uint32_t KR;    
  volatile uint32_t PR;    
  volatile uint32_t RLR;   
  volatile uint32_t SR;    
} IWDG_TypeDef;




 

typedef struct
{
  volatile uint32_t CR;    
  volatile uint32_t CSR;   
} PWR_TypeDef;



 

typedef struct
{
  volatile uint32_t CR;             
  volatile uint32_t PLLCFGR;        
  volatile uint32_t CFGR;           
  volatile uint32_t CIR;            
  volatile uint32_t AHB1RSTR;       
  volatile uint32_t AHB2RSTR;       
  volatile uint32_t AHB3RSTR;       
  uint32_t      RESERVED0;      
  volatile uint32_t APB1RSTR;       
  volatile uint32_t APB2RSTR;       
  uint32_t      RESERVED1[2];   
  volatile uint32_t AHB1ENR;        
  volatile uint32_t AHB2ENR;        
  volatile uint32_t AHB3ENR;        
  uint32_t      RESERVED2;      
  volatile uint32_t APB1ENR;        
  volatile uint32_t APB2ENR;        
  uint32_t      RESERVED3[2];   
  volatile uint32_t AHB1LPENR;      
  volatile uint32_t AHB2LPENR;      
  volatile uint32_t AHB3LPENR;      
  uint32_t      RESERVED4;      
  volatile uint32_t APB1LPENR;      
  volatile uint32_t APB2LPENR;      
  uint32_t      RESERVED5[2];   
  volatile uint32_t BDCR;           
  volatile uint32_t CSR;            
  uint32_t      RESERVED6[2];   
  volatile uint32_t SSCGR;          
  volatile uint32_t PLLI2SCFGR;     
} RCC_TypeDef;



 

typedef struct
{
  volatile uint32_t TR;       
  volatile uint32_t DR;       
  volatile uint32_t CR;       
  volatile uint32_t ISR;      
  volatile uint32_t PRER;     
  volatile uint32_t WUTR;     
  volatile uint32_t CALIBR;   
  volatile uint32_t ALRMAR;   
  volatile uint32_t ALRMBR;   
  volatile uint32_t WPR;      
  volatile uint32_t SSR;      
  volatile uint32_t SHIFTR;   
  volatile uint32_t TSTR;     
  volatile uint32_t TSDR;     
  volatile uint32_t TSSSR;    
  volatile uint32_t CALR;     
  volatile uint32_t TAFCR;    
  volatile uint32_t ALRMASSR; 
  volatile uint32_t ALRMBSSR; 
  uint32_t RESERVED7;     
  volatile uint32_t BKP0R;    
  volatile uint32_t BKP1R;    
  volatile uint32_t BKP2R;    
  volatile uint32_t BKP3R;    
  volatile uint32_t BKP4R;    
  volatile uint32_t BKP5R;    
  volatile uint32_t BKP6R;    
  volatile uint32_t BKP7R;    
  volatile uint32_t BKP8R;    
  volatile uint32_t BKP9R;    
  volatile uint32_t BKP10R;   
  volatile uint32_t BKP11R;   
  volatile uint32_t BKP12R;   
  volatile uint32_t BKP13R;   
  volatile uint32_t BKP14R;   
  volatile uint32_t BKP15R;   
  volatile uint32_t BKP16R;   
  volatile uint32_t BKP17R;   
  volatile uint32_t BKP18R;   
  volatile uint32_t BKP19R;   
} RTC_TypeDef;



 

typedef struct
{
  volatile uint32_t POWER;                  
  volatile uint32_t CLKCR;                  
  volatile uint32_t ARG;                    
  volatile uint32_t CMD;                    
  volatile const uint32_t  RESPCMD;         
  volatile const uint32_t  RESP1;           
  volatile const uint32_t  RESP2;           
  volatile const uint32_t  RESP3;           
  volatile const uint32_t  RESP4;           
  volatile uint32_t DTIMER;                 
  volatile uint32_t DLEN;                   
  volatile uint32_t DCTRL;                  
  volatile const uint32_t  DCOUNT;          
  volatile const uint32_t  STA;             
  volatile uint32_t ICR;                    
  volatile uint32_t MASK;                   
  uint32_t      RESERVED0[2];           
  volatile const uint32_t  FIFOCNT;         
  uint32_t      RESERVED1[13];          
  volatile uint32_t FIFO;                   
} SDIO_TypeDef;



 

typedef struct
{
  volatile uint32_t CR1;         
  volatile uint32_t CR2;         
  volatile uint32_t SR;          
  volatile uint32_t DR;          
  volatile uint32_t CRCPR;       
  volatile uint32_t RXCRCR;      
  volatile uint32_t TXCRCR;      
  volatile uint32_t I2SCFGR;     
  volatile uint32_t I2SPR;       
} SPI_TypeDef;




 

typedef struct
{
  volatile uint32_t CR1;          
  volatile uint32_t CR2;          
  volatile uint32_t SMCR;         
  volatile uint32_t DIER;         
  volatile uint32_t SR;           
  volatile uint32_t EGR;          
  volatile uint32_t CCMR1;        
  volatile uint32_t CCMR2;        
  volatile uint32_t CCER;         
  volatile uint32_t CNT;          
  volatile uint32_t PSC;          
  volatile uint32_t ARR;          
  volatile uint32_t RCR;          
  volatile uint32_t CCR1;         
  volatile uint32_t CCR2;         
  volatile uint32_t CCR3;         
  volatile uint32_t CCR4;         
  volatile uint32_t BDTR;         
  volatile uint32_t DCR;          
  volatile uint32_t DMAR;         
  volatile uint32_t OR;           
} TIM_TypeDef;



 

typedef struct
{
  volatile uint32_t SR;          
  volatile uint32_t DR;          
  volatile uint32_t BRR;         
  volatile uint32_t CR1;         
  volatile uint32_t CR2;         
  volatile uint32_t CR3;         
  volatile uint32_t GTPR;        
} USART_TypeDef;



 

typedef struct
{
  volatile uint32_t CR;    
  volatile uint32_t CFR;   
  volatile uint32_t SR;    
} WWDG_TypeDef;



 

typedef struct
{
  volatile uint32_t CR;   
  volatile uint32_t SR;   
  volatile uint32_t DR;   
} RNG_TypeDef;



 
typedef struct
{
  volatile uint32_t GOTGCTL;               
  volatile uint32_t GOTGINT;               
  volatile uint32_t GAHBCFG;               
  volatile uint32_t GUSBCFG;               
  volatile uint32_t GRSTCTL;               
  volatile uint32_t GINTSTS;               
  volatile uint32_t GINTMSK;               
  volatile uint32_t GRXSTSR;               
  volatile uint32_t GRXSTSP;               
  volatile uint32_t GRXFSIZ;               
  volatile uint32_t DIEPTXF0_HNPTXFSIZ;    
  volatile uint32_t HNPTXSTS;              
  uint32_t Reserved30[2];              
  volatile uint32_t GCCFG;                 
  volatile uint32_t CID;                   
  uint32_t  Reserved40[48];            
  volatile uint32_t HPTXFSIZ;              
  volatile uint32_t DIEPTXF[0x0F];         
} USB_OTG_GlobalTypeDef;



 
typedef struct
{
  volatile uint32_t DCFG;             
  volatile uint32_t DCTL;             
  volatile uint32_t DSTS;             
  uint32_t Reserved0C;            
  volatile uint32_t DIEPMSK;          
  volatile uint32_t DOEPMSK;          
  volatile uint32_t DAINT;            
  volatile uint32_t DAINTMSK;         
  uint32_t  Reserved20;           
  uint32_t Reserved9;             
  volatile uint32_t DVBUSDIS;         
  volatile uint32_t DVBUSPULSE;       
  volatile uint32_t DTHRCTL;          
  volatile uint32_t DIEPEMPMSK;       
  volatile uint32_t DEACHINT;         
  volatile uint32_t DEACHMSK;         
  uint32_t Reserved40;            
  volatile uint32_t DINEP1MSK;        
  uint32_t  Reserved44[15];       
  volatile uint32_t DOUTEP1MSK;       
} USB_OTG_DeviceTypeDef;



 
typedef struct
{
  volatile uint32_t DIEPCTL;            
  uint32_t Reserved04;              
  volatile uint32_t DIEPINT;            
  uint32_t Reserved0C;              
  volatile uint32_t DIEPTSIZ;           
  volatile uint32_t DIEPDMA;            
  volatile uint32_t DTXFSTS;            
  uint32_t Reserved18;              
} USB_OTG_INEndpointTypeDef;



 
typedef struct
{
  volatile uint32_t DOEPCTL;        
  uint32_t Reserved04;          
  volatile uint32_t DOEPINT;        
  uint32_t Reserved0C;          
  volatile uint32_t DOEPTSIZ;       
  volatile uint32_t DOEPDMA;        
  uint32_t Reserved18[2];       
} USB_OTG_OUTEndpointTypeDef;



 
typedef struct
{
  volatile uint32_t HCFG;              
  volatile uint32_t HFIR;              
  volatile uint32_t HFNUM;             
  uint32_t Reserved40C;            
  volatile uint32_t HPTXSTS;           
  volatile uint32_t HAINT;             
  volatile uint32_t HAINTMSK;          
} USB_OTG_HostTypeDef;



 
typedef struct
{
  volatile uint32_t HCCHAR;            
  volatile uint32_t HCSPLT;            
  volatile uint32_t HCINT;             
  volatile uint32_t HCINTMSK;          
  volatile uint32_t HCTSIZ;            
  volatile uint32_t HCDMA;             
  uint32_t Reserved[2];            
} USB_OTG_HostChannelTypeDef;



 



 
#line 825 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 



 





 
#line 864 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 874 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"
 
#line 883 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 915 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 


 






 

 



#line 944 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"






 



 
#line 991 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"
 
#line 1038 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"



 



 



 



 



 

 
 
 

 
 
 
 
 


 


 
#line 1092 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 1146 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 1196 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 1252 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 1314 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 




 




 




 




 




 
#line 1385 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 1435 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 1485 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 1524 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 




 




 




 
#line 1552 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 1608 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 
#line 1649 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 1657 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 



 
 
 
 
 
 
 
#line 1699 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"
 
#line 1727 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 1777 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 1790 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 1803 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 1817 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 1831 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 1876 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 1887 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 1894 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 1901 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 1930 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"


 
 
#line 1949 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 1960 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 1974 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 1988 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 2005 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 2016 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 2030 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 2044 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 2061 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 2072 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 2086 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 2100 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 2114 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 2125 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 2139 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 2153 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 2167 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 2178 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 2192 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 2206 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
 
#line 2215 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 2304 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 2393 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 2482 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 2571 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"


 
#line 2670 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 2768 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 2866 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 2964 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 3062 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 3160 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 3258 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 3356 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 3454 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 3552 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 3650 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 3748 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 3846 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 3944 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 4042 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 4140 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 4238 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 4336 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 4434 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 4532 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 4630 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 4728 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 4826 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 4924 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 5022 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 5120 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 5218 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 5316 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
 
 
 
 
 





 





 




 
 
 
 
 


 

 
#line 5358 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 5365 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"







#line 5379 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 5395 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 5402 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"







#line 5416 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 5423 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 5431 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 




 




 




 




 




 
#line 5469 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 5477 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 5485 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 




 
#line 5503 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"


 
 
 
 
 
 
#line 5583 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 
#line 5609 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 5628 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 5690 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 5752 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 5814 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 5876 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 




 





 
 
 
 
 
 
#line 5968 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 5996 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 6067 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 6092 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 6163 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 6234 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 6305 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 6376 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
 
 
 
 
 
#line 6394 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"


#line 6411 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 6434 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 6469 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 6477 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 6518 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 6535 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"
 
#line 6545 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
 
 
 
 
 
#line 6558 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"













#line 6607 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 6615 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"













#line 6664 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 6672 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"













#line 6721 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 6729 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"













#line 6778 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 6787 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 6795 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 6807 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 6815 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 6823 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 6831 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"







 
#line 6846 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 6854 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 6866 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 6874 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 6882 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 6890 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"







 
#line 6905 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 6913 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 6925 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 6933 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 6941 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 6949 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"







 
#line 6964 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 6972 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 6984 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 6992 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7000 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7008 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"







 
#line 7023 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7031 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7043 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7051 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"







 
#line 7066 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7074 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7086 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7094 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"







 
#line 7109 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7117 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7129 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7137 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"







 
#line 7152 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7160 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7172 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7180 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"







 
#line 7197 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"











#line 7215 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7223 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7230 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 7241 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"











#line 7259 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7267 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7274 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 7285 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"











#line 7303 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7311 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7318 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 7341 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 7364 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 7387 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 7400 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7412 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7424 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7436 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 7449 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7461 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7473 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7485 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 7498 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7510 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7522 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7534 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 7547 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7559 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7571 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7583 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 7596 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7608 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7620 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7632 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 7645 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7657 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7669 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7681 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 7694 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7706 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7718 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 7730 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 




 
 
 
 
 
 
#line 7827 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 7909 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 7959 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 7977 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 8059 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 8109 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 8191 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 8241 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 8291 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 8309 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 8359 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"
 
#line 8376 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 8474 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 8556 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"
 
#line 8608 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"
 
#line 8665 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 8707 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 8765 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 8807 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"


 
 
 
 
 
 
#line 8857 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 8868 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 8884 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 



#line 8919 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"





 
#line 8931 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 
#line 8980 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 9006 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 9017 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 





 
 
 
 
 
 




 
#line 9041 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 
#line 9054 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"



 
 
 
 
 
 
#line 9078 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 9085 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 9104 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 


 
#line 9130 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 


 
 
 
 
 
 
#line 9146 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 9155 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 9167 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 9186 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"


 


#line 9197 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 9208 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 9221 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"







#line 9235 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 9243 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"


 
 










 










 
#line 9276 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 9286 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 9294 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"







 
#line 9308 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"







 
#line 9324 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 










#line 9342 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 9349 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"







 
#line 9375 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 9397 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 9416 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"





 
#line 9461 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 9469 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"
 





 
#line 9545 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 9580 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 


 
#line 9633 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"
 


 


#line 9645 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 


 






 
#line 9726 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 9767 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 9817 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 9824 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 9832 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 
#line 9908 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 9949 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 9960 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"







#line 9973 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 10005 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"
 



 
#line 10022 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 10036 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 10043 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"


 
 
 
 
 
 
#line 10057 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 10074 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
 
 
 
 


 


 
#line 10127 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 10171 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 10241 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 


 
#line 10294 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 10302 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 
#line 10315 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 10385 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 10455 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 




 
#line 10473 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 10516 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 10546 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 
#line 10574 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 10622 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 


 
#line 10637 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 10649 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 




 




 




 




 




 




 




 




 




 




 




 




 




 




 




 




 




 




 




 



 
 
 
 
 
 






 
#line 10779 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"







#line 10792 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 










#line 10830 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 




 




 




 




 




 




 




 
#line 10884 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 10892 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 10905 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 
#line 10984 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 11025 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 11099 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 




 
 
 
 
 


 
#line 11127 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 11134 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 11165 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 11188 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 11217 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 




 




 




 






























#line 11275 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 11286 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
 
 
 
 
 





 



 


 
#line 11318 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"


 
#line 11330 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"



 
#line 11343 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"



 
#line 11356 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"



 
#line 11369 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 11383 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"



 
#line 11396 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"



 
#line 11409 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"



 
#line 11422 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"



 
#line 11435 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 11449 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"



 
#line 11462 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"



 
#line 11475 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"



 
#line 11488 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"



 
#line 11501 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 11515 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"



 
#line 11527 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"



 
#line 11539 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"



 
#line 11551 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"



 
#line 11563 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 11571 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
 
 
 
 
 
#line 11593 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

















 
#line 11620 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 11627 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 11652 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 11660 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 11667 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"





#line 11679 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"







#line 11692 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 11739 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 11777 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 11803 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 






#line 11817 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 11824 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"











#line 11841 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 11848 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"





 







#line 11868 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"







#line 11882 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 






#line 11896 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 11903 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"











#line 11920 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 11927 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"





 







#line 11947 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"







#line 11961 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 12008 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 




 




 




 




 




 




 




 
#line 12061 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"







#line 12086 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 12096 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 12105 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 






#line 12128 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"


 
 
 
 
 
 
#line 12166 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 
#line 12179 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 12226 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 12249 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"











 
#line 12297 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 12310 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"





 
 
 
 
 
 
#line 12331 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"
 
#line 12339 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"





 
#line 12355 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"
 
#line 12363 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"






 







 





 
 
 
 
 
 
#line 12395 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 12409 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"







 
#line 12468 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"
 


 
#line 12487 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
 
 
 
 
 
#line 12524 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 

#line 12535 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 

#line 12546 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 12557 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"





















 
#line 12588 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 12608 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 12622 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 12644 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 
#line 12657 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




#line 12674 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 12696 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 

#line 12760 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 12777 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"


#line 12793 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 12819 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 12835 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 12847 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 
#line 12890 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"
 
#line 12969 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 13049 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 13057 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 
#line 13076 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 13084 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 




 
#line 13108 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 




#line 13130 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 13141 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 13149 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 13165 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 13181 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 
#line 13194 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 13214 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 13222 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 
#line 13256 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 13285 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 13294 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 13302 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"







 
#line 13343 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 13351 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 13365 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 13374 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 13400 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




#line 13419 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"













#line 13451 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 

#line 13464 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 13475 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 13487 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 13522 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 13563 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 13598 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 

#line 13610 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"
 
#line 13625 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 




 




 
#line 13648 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 

#line 13689 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 13724 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"
 

#line 13732 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"







 
#line 13749 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
 
#line 13762 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"







#line 13776 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 13784 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

#line 13792 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"


 



 



 

 








 


 


 



 
#line 13840 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 13851 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 


 




 


 


 


 



 





 
#line 13899 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 13913 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 13923 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 13931 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 13939 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 



 
#line 13951 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 13961 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 13969 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 13977 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 13985 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 13995 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 14005 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"
 



 
#line 14016 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 
#line 14079 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 14091 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 14099 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 14113 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 




 
#line 14126 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 14136 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 14144 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 14154 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 
#line 14164 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 



 
#line 14178 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"
 
#line 14185 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"
 



 





 
#line 14202 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"

 


 




 


 





 
#line 14227 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"


 



 



 


 


 


 







 



#line 14265 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f405xx.h"



















 
 
 
 
 
 
 
 


 




 



 



 





#line 129 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f4xx.h"
#line 176 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f4xx.h"



 



 
typedef enum
{
  RESET = 0U,
  SET = !RESET
} FlagStatus, ITStatus;

typedef enum
{
  DISABLE = 0U,
  ENABLE = !DISABLE
} FunctionalState;


typedef enum
{
  SUCCESS = 0U,
  ERROR = !SUCCESS
} ErrorStatus;



 




 
















 
 
#line 236 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f4xx.h"

 
#line 245 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f4xx.h"

 
#line 254 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f4xx.h"

 
#line 263 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f4xx.h"

 
#line 272 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f4xx.h"

 
#line 281 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f4xx.h"



 

#line 1 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal.h"

















  

 
#line 296 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal.h"


#line 288 "../Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f4xx.h"









 



 
#line 30 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_def.h"
#line 1 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

















 

 







 
 
 



 
#line 46 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"


 



 
#line 93 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 101 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"
















 



 





 



 
#line 150 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 217 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"







 



 
#line 235 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"


 



 
#line 249 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"


 



 






 



 

#line 277 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"






#line 289 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"














 



 
#line 322 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"





#line 367 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 377 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 439 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"






 



 

#line 567 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"



 



 

#line 584 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"



 



 

#line 609 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 618 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 717 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"




 




 
#line 738 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"


 



 





 



 


















#line 789 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"





#line 801 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 808 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"









#line 824 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 839 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"


 



 
#line 867 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"


 



 
#line 883 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 892 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"





#line 907 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 1019 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 1035 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"



 



 
#line 1060 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"


 



 





 



 






 



 















 
 







 



 








 



 














 



 










 



 







































 



 


#line 1217 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"






 



 

 
#line 1239 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

 












 



 

































#line 1300 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"
















#line 1322 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"



 




 















 




 
#line 1363 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"


 



 









#line 1393 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"



 



 



#line 1431 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 1441 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 1460 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"










#line 1487 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"







 



 




 



 

























 




 








 



 




 



 
#line 1571 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"



 



 

#line 1588 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 1600 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 1641 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"





 



 











 

#line 1691 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 1705 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"



 



 

 



 



 



 








 




 




 



 
#line 1756 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

 





































 



 
#line 1826 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"



 



 
#line 1841 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"



 



 









#line 1874 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 1885 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"


 



 

#line 1915 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 1923 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"






#line 1939 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"



#line 2028 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"



 



 
#line 2042 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"



 



 





 



 



 



 
#line 2081 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"


 



 



 



 






 




 



 

 



 





 



 
#line 2142 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"









 




 
#line 2170 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 2191 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 2202 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 2211 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 2224 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 2233 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"



 



 







 



 
#line 2269 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 2284 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"


#line 2317 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"



 



 
#line 2485 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"



#line 2495 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"


 

#line 2511 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"



 







 



 

#line 2534 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"



 



 

#line 2562 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"


 



 










 



 














 




 




 




 







 




 
#line 2640 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"



 




 
#line 2690 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 2704 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"


 




 








#line 2984 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 2998 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 3215 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 3234 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 3241 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 3262 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 3410 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

 



#line 3435 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 3456 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 3573 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 3582 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 3599 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 3614 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"






#line 3643 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

















#line 3669 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"





#line 3696 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"





#line 3708 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 3717 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 3750 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 3768 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"












#line 3786 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 3809 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 3849 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 3935 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"



 



 




 



 
#line 3961 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 3989 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 3996 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 4011 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"











 



 




#line 4039 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 4061 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"
 




#line 4091 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 4098 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 4110 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"


 



 

#line 4124 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"








 



 
#line 4145 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"


 



 







 



 













 




 









#line 4199 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"


 



 












#line 4225 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 4234 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 4243 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"




#line 4276 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"


 



 








#line 4303 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"







 



 

#line 4323 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"






 



 




 



 
#line 4357 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"


 



 







 



 
#line 4384 "../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"


 



 





 



 





 



 



 








#line 31 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_def.h"
#line 32 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_def.h"

 



   
typedef enum 
{
  HAL_OK       = 0x00U,
  HAL_ERROR    = 0x01U,
  HAL_BUSY     = 0x02U,
  HAL_TIMEOUT  = 0x03U
} HAL_StatusTypeDef;



 
typedef enum 
{
  HAL_UNLOCKED = 0x00U,
  HAL_LOCKED   = 0x01U  
} HAL_LockTypeDef;

 






























 


#line 104 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_def.h"







#line 126 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_def.h"


 
#line 155 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_def.h"




  









 


#line 188 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_def.h"



  



 


#line 205 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_def.h"








#line 28 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"

 
 
#line 1 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"















 

 







 
#line 28 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"



 



 

 


 



 
typedef struct
{
  uint32_t PLLState;   
 

  uint32_t PLLSource;  
 

  uint32_t PLLM;       
 

  uint32_t PLLN;       

 

  uint32_t PLLP;       
 

  uint32_t PLLQ;       
 
#line 73 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"
} RCC_PLLInitTypeDef;

#line 174 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 200 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 291 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 376 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"





 
typedef struct
{





  uint32_t PLLI2SN;    


 

  uint32_t PLLI2SR;    

 

} RCC_PLLI2SInitTypeDef;



 
typedef struct
{
  uint32_t PeriphClockSelection; 
 

  RCC_PLLI2SInitTypeDef PLLI2S;  
 

  uint32_t RTCClockSelection;      
 




} RCC_PeriphCLKInitTypeDef;



 

 


 



 
 
#line 452 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"
 

 
#line 462 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"
 

 
#line 479 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"
 

 
#line 493 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"
 

 
#line 505 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"
 

 
#line 517 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"
 


 






 




 





 
#line 546 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"


 



 
#line 560 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"


 



 
#line 573 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"


 

#line 598 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 627 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 720 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 775 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 854 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 888 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 905 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 920 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"








 






 




#line 952 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"



 

 


 
 
#line 2026 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"
 

 







 
#line 2168 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"


 







 
#line 2189 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 2222 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"


 







 






#line 2247 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 2258 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 2277 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"


 








 











#line 2307 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"


 







 
#line 2326 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"


 







 




 







 
#line 2478 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"


 







 
#line 2505 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 2522 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"


 







 
#line 2575 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 2582 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"


 







 
#line 2599 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 2606 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"


 




 
#line 2628 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 2637 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"


 




 
#line 2652 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"






#line 2665 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"








 




 







 




 
#line 2709 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 2726 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"


 




 












 








 
#line 2772 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 2789 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"


 








 











#line 2819 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"


 








 




 








 
#line 2861 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 2878 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"


 








 
#line 2896 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 2903 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"


 

 

 
#line 3288 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"
 

 
#line 3571 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"
 

 
#line 3950 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"
 

 
#line 4757 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"
 

 
#line 5795 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"
 

 
#line 5841 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"




























 
#line 5876 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"
 

 








 



#line 5959 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"














 





#line 6004 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 6027 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"
 

 
#line 6117 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"
 

 
#line 6136 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 6155 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 6167 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"
 

 











 








 



#line 6226 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 6391 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 6440 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 6674 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 6729 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 6753 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

 

#line 6780 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 6793 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"



 

 


 



 
HAL_StatusTypeDef HAL_RCCEx_PeriphCLKConfig(RCC_PeriphCLKInitTypeDef  *PeriphClkInit);
void HAL_RCCEx_GetPeriphCLKConfig(RCC_PeriphCLKInitTypeDef  *PeriphClkInit);

uint32_t HAL_RCCEx_GetPeriphCLKFreq(uint32_t PeriphClk);

#line 6818 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"
HAL_StatusTypeDef HAL_RCCEx_EnablePLLI2S(RCC_PLLI2SInitTypeDef  *PLLI2SInit);
HAL_StatusTypeDef HAL_RCCEx_DisablePLLI2S(void);







 



 
 
 
 


 




 
 
#line 6852 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"






 






 
#line 6878 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

 





 







#line 6904 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 6914 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"




 



 

 


 


 





































#line 6987 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 6995 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 7015 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 7067 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 7088 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"

#line 7152 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc_ex.h"




















 



 



 



 






#line 32 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"



 



 

 


 



 
typedef struct
{
  uint32_t OscillatorType;       
 

  uint32_t HSEState;             
 

  uint32_t LSEState;             
 

  uint32_t HSIState;             
 

  uint32_t HSICalibrationValue;  
 

  uint32_t LSIState;             
 

  RCC_PLLInitTypeDef PLL;         
} RCC_OscInitTypeDef;



 
typedef struct
{
  uint32_t ClockType;             
 

  uint32_t SYSCLKSource;          
 

  uint32_t AHBCLKDivider;         
 

  uint32_t APB1CLKDivider;        
 

  uint32_t APB2CLKDivider;        
 

} RCC_ClkInitTypeDef;



 

 


 



 







 



 





 



 





 



 






 



 




 



 





 



 






 



 




 



 






 





 






 





 






 



 
#line 234 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"


 



 







 



 
#line 287 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"


 



 




 



 






 



 







 



 
#line 333 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"


 









 
 





 


 
#line 364 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"


 



 

 


 







 
#line 426 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"

#line 433 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"


 







 
#line 450 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"

#line 457 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"


 







 
#line 517 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"

#line 525 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"


 







 
#line 543 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"

#line 551 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"


 







 
#line 618 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"

#line 627 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"


 







 
#line 646 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"

#line 655 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"


 




 
#line 669 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"

#line 677 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"


 




 
#line 692 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"

#line 701 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"


 




 
#line 717 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"

#line 727 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"


 








 
#line 745 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"

#line 752 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"


 








 
#line 771 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"

#line 779 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"


 








 
#line 799 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"

#line 808 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"


 



 















 









 




 



 








 




 



 





















 
#line 907 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"


 



 


















 
#line 950 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"


 



 



 























 













 






 






 




 



 







 










 










 



 



 









 










 







 



 



 















 




















 




 




 











 












 













 













 




 



















 







 



 

 


 



 
 
HAL_StatusTypeDef HAL_RCC_DeInit(void);
HAL_StatusTypeDef HAL_RCC_OscConfig(const RCC_OscInitTypeDef *RCC_OscInitStruct);
HAL_StatusTypeDef HAL_RCC_ClockConfig(const RCC_ClkInitTypeDef *RCC_ClkInitStruct, uint32_t FLatency);


 



 
 
void     HAL_RCC_MCOConfig(uint32_t RCC_MCOx, uint32_t RCC_MCOSource, uint32_t RCC_MCODiv);
void     HAL_RCC_EnableCSS(void);
void     HAL_RCC_DisableCSS(void);
uint32_t HAL_RCC_GetSysClockFreq(void);
uint32_t HAL_RCC_GetHCLKFreq(void);
uint32_t HAL_RCC_GetPCLK1Freq(void);
uint32_t HAL_RCC_GetPCLK2Freq(void);
void     HAL_RCC_GetOscConfig(RCC_OscInitTypeDef *RCC_OscInitStruct);
void     HAL_RCC_GetClockConfig(RCC_ClkInitTypeDef *RCC_ClkInitStruct, uint32_t *pFLatency);

 
void HAL_RCC_NMI_IRQHandler(void);

 
void HAL_RCC_CSSCallback(void);



 



 

 
 
 


 




 

 
 



 


 



 
 



 



 
 




 


 


 


 












 



 

 


 



 






















#line 1408 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rcc.h"































 



 



 



 







#line 276 "../Core/Inc/stm32f4xx_hal_conf.h"


#line 1 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio.h"
















  

 







 
#line 29 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio.h"



 



  

 


 



  
typedef struct
{
  uint32_t Pin;       
 

  uint32_t Mode;      
 

  uint32_t Pull;      
 

  uint32_t Speed;     
 

  uint32_t Alternate;  
 
}GPIO_InitTypeDef;



 
typedef enum
{
  GPIO_PIN_RESET = 0,
  GPIO_PIN_SET
}GPIO_PinState;


 

 



  



 
#line 102 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio.h"




 









  







    



 






 




 






 

 


   





 
  


 

 


 






 







 







 







 







 



 

 
#line 1 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio_ex.h"
















  

 







 
#line 29 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio_ex.h"



 



  

 
 


 
  


 

 
#line 165 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio_ex.h"
 

 
#line 280 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio_ex.h"
 

 
#line 386 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio_ex.h"
 

 



  








  





  






  







  






  






  





  







  






  








  





  






  



 

 
#line 572 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio_ex.h"
 

 
#line 681 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio_ex.h"

 

 
#line 815 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio_ex.h"

 
#line 907 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio_ex.h"

 
#line 981 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio_ex.h"

 
#line 1101 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio_ex.h"
 

 
#line 1224 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio_ex.h"
 


  



 

 


 


 

 


 


 

 
 
 


 


 

 


 


 
#line 1276 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio_ex.h"

#line 1290 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio_ex.h"







#line 1304 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio_ex.h"

#line 1332 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio_ex.h"



 



   
 
#line 1366 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio_ex.h"
 

 
#line 1393 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio_ex.h"
 

 
#line 1417 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio_ex.h"
 

 
#line 1438 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio_ex.h"



 

 
#line 1460 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio_ex.h"
 
 




 
#line 1485 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio_ex.h"
 

 
#line 1517 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio_ex.h"
 

 
#line 1546 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio_ex.h"
 

 



 

 



 



  



 

 


 



 



  



  
  






#line 214 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio.h"

 


 



 
 
void  HAL_GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init);
void  HAL_GPIO_DeInit(GPIO_TypeDef  *GPIOx, uint32_t GPIO_Pin);


 



 
 
GPIO_PinState HAL_GPIO_ReadPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void HAL_GPIO_WritePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);
void HAL_GPIO_TogglePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
HAL_StatusTypeDef HAL_GPIO_LockPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void HAL_GPIO_EXTI_IRQHandler(uint16_t GPIO_Pin);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);



  



  
 
 
 


 
#line 272 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio.h"



 

 


 
#line 299 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio.h"


 

 


 



 



  



 







#line 280 "../Core/Inc/stm32f4xx_hal_conf.h"


#line 1 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_exti.h"
















 

 







 
#line 29 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_exti.h"



 




 

 



 
typedef enum
{
  HAL_EXTI_COMMON_CB_ID          = 0x00U
} EXTI_CallbackIDTypeDef;



 
typedef struct
{
  uint32_t Line;                     
  void (* PendingCallback)(void);    
} EXTI_HandleTypeDef;



 
typedef struct
{
  uint32_t Line;      
 
  uint32_t Mode;      
 
  uint32_t Trigger;   
 
  uint32_t GPIOSel;   

 
} EXTI_ConfigTypeDef;



 

 


 



 
#line 124 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_exti.h"



 



 





 



 







 




 
#line 182 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_exti.h"



 



 

 


 



 

 


 


 








 




 




 




 








 

 


 














#line 309 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_exti.h"




 

 



 




 
 
HAL_StatusTypeDef HAL_EXTI_SetConfigLine(EXTI_HandleTypeDef *hexti, EXTI_ConfigTypeDef *pExtiConfig);
HAL_StatusTypeDef HAL_EXTI_GetConfigLine(EXTI_HandleTypeDef *hexti, EXTI_ConfigTypeDef *pExtiConfig);
HAL_StatusTypeDef HAL_EXTI_ClearConfigLine(EXTI_HandleTypeDef *hexti);
HAL_StatusTypeDef HAL_EXTI_RegisterCallback(EXTI_HandleTypeDef *hexti, EXTI_CallbackIDTypeDef CallbackID, void (*pPendingCbfn)(void));
HAL_StatusTypeDef HAL_EXTI_GetHandle(EXTI_HandleTypeDef *hexti, uint32_t ExtiLine);


 




 
 
void HAL_EXTI_IRQHandler(EXTI_HandleTypeDef *hexti);
uint32_t HAL_EXTI_GetPending(EXTI_HandleTypeDef *hexti, uint32_t Edge);
void HAL_EXTI_ClearPending(EXTI_HandleTypeDef *hexti, uint32_t Edge);
void HAL_EXTI_GenerateSWI(EXTI_HandleTypeDef *hexti);



 



 



 



 







#line 284 "../Core/Inc/stm32f4xx_hal_conf.h"


#line 1 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dma.h"
















  

 







 
#line 29 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dma.h"



 



  

 




 
   


 
typedef struct
{
  uint32_t Channel;              
 

  uint32_t Direction;            

 

  uint32_t PeriphInc;            
 

  uint32_t MemInc;               
 

  uint32_t PeriphDataAlignment;  
 

  uint32_t MemDataAlignment;     
 

  uint32_t Mode;                 


 

  uint32_t Priority;             
 

  uint32_t FIFOMode;             


 

  uint32_t FIFOThreshold;        
 

  uint32_t MemBurst;             



 

  uint32_t PeriphBurst;          



 
}DMA_InitTypeDef;




 
typedef enum
{
  HAL_DMA_STATE_RESET             = 0x00U,   
  HAL_DMA_STATE_READY             = 0x01U,   
  HAL_DMA_STATE_BUSY              = 0x02U,   
  HAL_DMA_STATE_TIMEOUT           = 0x03U,   
  HAL_DMA_STATE_ERROR             = 0x04U,   
  HAL_DMA_STATE_ABORT             = 0x05U,   
}HAL_DMA_StateTypeDef;



 
typedef enum
{
  HAL_DMA_FULL_TRANSFER           = 0x00U,   
  HAL_DMA_HALF_TRANSFER           = 0x01U    
}HAL_DMA_LevelCompleteTypeDef;



 
typedef enum
{
  HAL_DMA_XFER_CPLT_CB_ID         = 0x00U,   
  HAL_DMA_XFER_HALFCPLT_CB_ID     = 0x01U,   
  HAL_DMA_XFER_M1CPLT_CB_ID       = 0x02U,   
  HAL_DMA_XFER_M1HALFCPLT_CB_ID   = 0x03U,   
  HAL_DMA_XFER_ERROR_CB_ID        = 0x04U,   
  HAL_DMA_XFER_ABORT_CB_ID        = 0x05U,   
  HAL_DMA_XFER_ALL_CB_ID          = 0x06U    
}HAL_DMA_CallbackIDTypeDef;



 
typedef struct __DMA_HandleTypeDef
{
  DMA_Stream_TypeDef         *Instance;                                                         

  DMA_InitTypeDef            Init;                                                               

  HAL_LockTypeDef            Lock;                                                                

  volatile HAL_DMA_StateTypeDef  State;                                                             

  void                       *Parent;                                                            

  void                       (* XferCpltCallback)( struct __DMA_HandleTypeDef * hdma);          

  void                       (* XferHalfCpltCallback)( struct __DMA_HandleTypeDef * hdma);      

  void                       (* XferM1CpltCallback)( struct __DMA_HandleTypeDef * hdma);        
  
  void                       (* XferM1HalfCpltCallback)( struct __DMA_HandleTypeDef * hdma);    
  
  void                       (* XferErrorCallback)( struct __DMA_HandleTypeDef * hdma);         
  
  void                       (* XferAbortCallback)( struct __DMA_HandleTypeDef * hdma);           

  volatile uint32_t              ErrorCode;                                                         
  
  uint32_t                   StreamBaseAddress;                                                 

  uint32_t                   StreamIndex;                                                       
 
}DMA_HandleTypeDef;



 

 




 




  
#line 193 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dma.h"


 




  
#line 219 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dma.h"


 




  





 
        



  




  




  




 




  





  




 





 




  





 




 






  




 




  




 






  




  






  




  






 




 







 




  
#line 382 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dma.h"


 



 
 
 




 













 






 






 


 





 
#line 447 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dma.h"





       
#line 467 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dma.h"





 
#line 487 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dma.h"





 
#line 507 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dma.h"





 
#line 527 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dma.h"













 

















 
















 














 














 




















 







 



 
#line 1 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dma_ex.h"
















 

 







 
#line 29 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dma_ex.h"



 



  

 



 
   


  
typedef enum
{
  MEMORY0      = 0x00U,     
  MEMORY1      = 0x01U      
}HAL_DMA_MemoryTypeDef;



 

 



 




 

 
HAL_StatusTypeDef HAL_DMAEx_MultiBufferStart(DMA_HandleTypeDef *hdma, uint32_t SrcAddress, uint32_t DstAddress, uint32_t SecondMemAddress, uint32_t DataLength);
HAL_StatusTypeDef HAL_DMAEx_MultiBufferStart_IT(DMA_HandleTypeDef *hdma, uint32_t SrcAddress, uint32_t DstAddress, uint32_t SecondMemAddress, uint32_t DataLength);
HAL_StatusTypeDef HAL_DMAEx_ChangeMemory(DMA_HandleTypeDef *hdma, uint32_t Address, HAL_DMA_MemoryTypeDef memory);



 


 
         
 



 


 



 



 







#line 640 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dma.h"

 




 




 
HAL_StatusTypeDef HAL_DMA_Init(DMA_HandleTypeDef *hdma); 
HAL_StatusTypeDef HAL_DMA_DeInit(DMA_HandleTypeDef *hdma);


 




 
HAL_StatusTypeDef HAL_DMA_Start (DMA_HandleTypeDef *hdma, uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength);
HAL_StatusTypeDef HAL_DMA_Start_IT(DMA_HandleTypeDef *hdma, uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength);
HAL_StatusTypeDef HAL_DMA_Abort(DMA_HandleTypeDef *hdma);
HAL_StatusTypeDef HAL_DMA_Abort_IT(DMA_HandleTypeDef *hdma);
HAL_StatusTypeDef HAL_DMA_PollForTransfer(DMA_HandleTypeDef *hdma, HAL_DMA_LevelCompleteTypeDef CompleteLevel, uint32_t Timeout);
void              HAL_DMA_IRQHandler(DMA_HandleTypeDef *hdma);
HAL_StatusTypeDef HAL_DMA_CleanCallbacks(DMA_HandleTypeDef *hdma);
HAL_StatusTypeDef HAL_DMA_RegisterCallback(DMA_HandleTypeDef *hdma, HAL_DMA_CallbackIDTypeDef CallbackID, void (* pCallback)(DMA_HandleTypeDef *_hdma));
HAL_StatusTypeDef HAL_DMA_UnRegisterCallback(DMA_HandleTypeDef *hdma, HAL_DMA_CallbackIDTypeDef CallbackID);



  




 
HAL_DMA_StateTypeDef HAL_DMA_GetState(DMA_HandleTypeDef *hdma);
uint32_t             HAL_DMA_GetError(DMA_HandleTypeDef *hdma);


  


  
 



 


  

 



 
#line 729 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dma.h"

















































  

 



 


 



  



 







#line 288 "../Core/Inc/stm32f4xx_hal_conf.h"


#line 1 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_cortex.h"















  

 







 
#line 28 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_cortex.h"



 



  
 


 





 
typedef struct
{
  uint8_t                Enable;                
 
  uint8_t                Number;                
 
  uint32_t               BaseAddress;            
  uint8_t                Size;                  
 
  uint8_t                SubRegionDisable;      
          
  uint8_t                TypeExtField;          
                  
  uint8_t                AccessPermission;      
 
  uint8_t                DisableExec;           
 
  uint8_t                IsShareable;           
 
  uint8_t                IsCacheable;           
 
  uint8_t                IsBufferable;          
 
}MPU_Region_InitTypeDef;


 




 

 



 



 
#line 98 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_cortex.h"


 



 





 




 







 



 




 



 




 



 




 



 




 



 




 



 





 



 
#line 211 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_cortex.h"


 
   


 
#line 224 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_cortex.h"


 



 
#line 239 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_cortex.h"


 




 


 

 


 
  


 
 
void HAL_NVIC_SetPriorityGrouping(uint32_t PriorityGroup);
void HAL_NVIC_SetPriority(IRQn_Type IRQn, uint32_t PreemptPriority, uint32_t SubPriority);
void HAL_NVIC_EnableIRQ(IRQn_Type IRQn);
void HAL_NVIC_DisableIRQ(IRQn_Type IRQn);
void HAL_NVIC_SystemReset(void);
uint32_t HAL_SYSTICK_Config(uint32_t TicksNumb);


 



 
 
uint32_t HAL_NVIC_GetPriorityGrouping(void);
void HAL_NVIC_GetPriority(IRQn_Type IRQn, uint32_t PriorityGroup, uint32_t* pPreemptPriority, uint32_t* pSubPriority);
uint32_t HAL_NVIC_GetPendingIRQ(IRQn_Type IRQn);
void HAL_NVIC_SetPendingIRQ(IRQn_Type IRQn);
void HAL_NVIC_ClearPendingIRQ(IRQn_Type IRQn);
uint32_t HAL_NVIC_GetActive(IRQn_Type IRQn);
void HAL_SYSTICK_CLKSourceConfig(uint32_t CLKSource);
void HAL_SYSTICK_IRQHandler(void);
void HAL_SYSTICK_Callback(void);


void HAL_MPU_Enable(uint32_t MPU_Control);
void HAL_MPU_Disable(void);
void HAL_MPU_EnableRegion(uint32_t RegionNumber);
void HAL_MPU_DisableRegion(uint32_t RegionNumber);
void HAL_MPU_ConfigRegion(MPU_Region_InitTypeDef *MPU_Init);

void HAL_CORTEX_ClearEvent(void);


 



 

 
 
 
 


 



































#line 348 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_cortex.h"

#line 357 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_cortex.h"

#line 386 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_cortex.h"






 

 



  



 
  





 

#line 292 "../Core/Inc/stm32f4xx_hal_conf.h"


#line 1 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_adc.h"
















 

 







 
#line 29 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_adc.h"

 
#line 1 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_adc.h"
















 

 







 
#line 29 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_adc.h"



 





 

 
 

 


 

 
 
 
 

 
 








 
 
#line 81 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_adc.h"

 
 
 
 
 

 
 





 
 









 
 
 
 


 
 
 





 
 
 





 





 
 
 
 


 
 
 





 
 
 





 



 
 
 
 
 
 
 



 


 





 
 







 
 
#line 209 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_adc.h"

 
 
#line 231 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_adc.h"

 
 
 
 
 
 

 







 




 



 
 


 








 


 


 








 










 





 


 
#line 492 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_adc.h"

 


 




 
#line 522 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_adc.h"


 




 






 



 
 
 
 






 



 






 



 
 
 
 
 
 






 



 






 



 




 



 




 



 





 



 
#line 648 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_adc.h"


 



 
#line 672 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_adc.h"


 



 





 



 




 



 





 



 




 



 
#line 733 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_adc.h"


 



 
#line 749 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_adc.h"


 



 
#line 772 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_adc.h"


 



 
#line 796 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_adc.h"


 



 





 



 




 




 






 



 




 



 






 



 
#line 862 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_adc.h"


 



 



 



 
#line 954 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_adc.h"


 



 




 




 
#line 987 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_adc.h"


 



 
#line 1001 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_adc.h"


 



 
#line 1024 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_adc.h"


 



 





 










 

 
 
 
 
 
 
 
 
 
 
 
 

 
 
 
 


 
 
 
 




 



 


 


 



 







 







 



 



 





































 







































 
#line 1205 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_adc.h"














































 






























































 


























 
#line 1348 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_adc.h"




















































































































 
#line 1474 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_adc.h"



















 





















 
















 













 
#line 1557 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_adc.h"

















 
#line 1588 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_adc.h"













 




















 





















 
#line 1651 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_adc.h"

























 
#line 1683 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_adc.h"

 
 
 













































 
#line 1747 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_adc.h"












































 
#line 1809 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_adc.h"



 



 


 


 



 
 
 
 






























 

static __inline uint32_t LL_ADC_DMA_GetRegAddr(const ADC_TypeDef *ADCx, uint32_t Register)
{
  uint32_t data_reg_addr = 0UL;

  if (Register == 0x00000000UL)
  {
     
    data_reg_addr = (uint32_t) & (ADCx->DR);
  }
  else  
  {
     
    data_reg_addr = (uint32_t) & (((((ADC_Common_TypeDef *) ((0x40000000UL + 0x00010000UL) + 0x2300UL))))->CDR);
  }

  return data_reg_addr;
}
#line 1889 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_adc.h"



 



 












 
static __inline void LL_ADC_SetCommonClock(ADC_Common_TypeDef *ADCxy_COMMON, uint32_t CommonClock)
{
  (((ADCxy_COMMON->CCR)) = ((((((ADCxy_COMMON->CCR))) & (~((0x3UL << (16U))))) | (CommonClock))));
}











 
static __inline uint32_t LL_ADC_GetCommonClock(const ADC_Common_TypeDef *ADCxy_COMMON)
{
  return (uint32_t)(((ADCxy_COMMON->CCR) & ((0x3UL << (16U)))));
}




























 
static __inline void LL_ADC_SetCommonPathInternalCh(ADC_Common_TypeDef *ADCxy_COMMON, uint32_t PathInternal)
{
  (((ADCxy_COMMON->CCR)) = ((((((ADCxy_COMMON->CCR))) & (~((0x1UL << (23U)) | (0x1UL << (22U))))) | (PathInternal))));
}
















 
static __inline uint32_t LL_ADC_GetCommonPathInternalCh(const ADC_Common_TypeDef *ADCxy_COMMON)
{
  return (uint32_t)(((ADCxy_COMMON->CCR) & ((0x1UL << (23U)) | (0x1UL << (22U)))));
}



 



 













 
static __inline void LL_ADC_SetResolution(ADC_TypeDef *ADCx, uint32_t Resolution)
{
  (((ADCx->CR1)) = ((((((ADCx->CR1))) & (~((0x3UL << (24U))))) | (Resolution))));
}












 
static __inline uint32_t LL_ADC_GetResolution(const ADC_TypeDef *ADCx)
{
  return (uint32_t)(((ADCx->CR1) & ((0x3UL << (24U)))));
}











 
static __inline void LL_ADC_SetDataAlignment(ADC_TypeDef *ADCx, uint32_t DataAlignment)
{
  (((ADCx->CR2)) = ((((((ADCx->CR2))) & (~((0x1UL << (11U))))) | (DataAlignment))));
}










 
static __inline uint32_t LL_ADC_GetDataAlignment(const ADC_TypeDef *ADCx)
{
  return (uint32_t)(((ADCx->CR2) & ((0x1UL << (11U)))));
}





















 
static __inline void LL_ADC_SetSequencersScanMode(ADC_TypeDef *ADCx, uint32_t ScanMode)
{
  (((ADCx->CR1)) = ((((((ADCx->CR1))) & (~((0x1UL << (8U))))) | (ScanMode))));
}




















 
static __inline uint32_t LL_ADC_GetSequencersScanMode(const ADC_TypeDef *ADCx)
{
  return (uint32_t)(((ADCx->CR1) & ((0x1UL << (8U)))));
}



 



 































 
static __inline void LL_ADC_REG_SetTriggerSource(ADC_TypeDef *ADCx, uint32_t TriggerSource)
{
   
   
   
   
   
  (((ADCx->CR2)) = ((((((ADCx->CR2))) & (~((0xFUL << (24U))))) | ((TriggerSource & (0xFUL << (24U)))))));
}


































 
static __inline uint32_t LL_ADC_REG_GetTriggerSource(const ADC_TypeDef *ADCx)
{
  uint32_t TriggerSource = ((ADCx->CR2) & ((0xFUL << (24U)) | (0x3UL << (28U))));

   
   
  uint32_t ShiftExten = ((TriggerSource & (0x3UL << (28U))) >> ((28UL) - 2UL));

   
   
  return ((TriggerSource
           & ((((0x00000000UL & (0xFUL << (24U))) >> (4UL * 0UL)) | (((0xFUL << (24U))) >> (4UL * 1UL)) | (((0xFUL << (24U))) >> (4UL * 2UL)) | (((0xFUL << (24U))) >> (4UL * 3UL))) << ShiftExten) & (0xFUL << (24U)))
          | (((((0x00000000UL & (0x3UL << (28U))) >> (4UL * 0UL)) | ((((0x1UL << (28U)))) >> (4UL * 1UL)) | ((((0x1UL << (28U)))) >> (4UL * 2UL)) | ((((0x1UL << (28U)))) >> (4UL * 3UL))) << ShiftExten) & (0x3UL << (28U)))
         );
}











 
static __inline uint32_t LL_ADC_REG_IsTriggerSourceSWStart(const ADC_TypeDef *ADCx)
{
  return (((ADCx->CR2) & ((0x3UL << (28U)))) == (0x00000000UL & (0x3UL << (28U))));
}












 
static __inline uint32_t LL_ADC_REG_GetTriggerEdge(const ADC_TypeDef *ADCx)
{
  return (uint32_t)(((ADCx->CR2) & ((0x3UL << (28U)))));
}

























































 
static __inline void LL_ADC_REG_SetSequencerLength(ADC_TypeDef *ADCx, uint32_t SequencerNbRanks)
{
  (((ADCx->SQR1)) = ((((((ADCx->SQR1))) & (~((0xFUL << (20U))))) | (SequencerNbRanks))));
}























































 
static __inline uint32_t LL_ADC_REG_GetSequencerLength(const ADC_TypeDef *ADCx)
{
  return (uint32_t)(((ADCx->SQR1) & ((0xFUL << (20U)))));
}























 
static __inline void LL_ADC_REG_SetSequencerDiscont(ADC_TypeDef *ADCx, uint32_t SeqDiscont)
{
  (((ADCx->CR1)) = ((((((ADCx->CR1))) & (~((0x1UL << (11U)) | (0x7UL << (13U))))) | (SeqDiscont))));
}


















 
static __inline uint32_t LL_ADC_REG_GetSequencerDiscont(const ADC_TypeDef *ADCx)
{
  return (uint32_t)(((ADCx->CR1) & ((0x1UL << (11U)) | (0x7UL << (13U)))));
}














































































 
static __inline void LL_ADC_REG_SetSequencerRanks(ADC_TypeDef *ADCx, uint32_t Rank, uint32_t Channel)
{
   
   
   
   
  volatile uint32_t *preg = ((volatile uint32_t *)((uint32_t) ((uint32_t)(&(ADCx->SQR1)) + (((((Rank) & ((0x00000000UL | 0x00000100UL | 0x00000200UL | 0x00000300UL))) >> (__clz(__rbit(((0x00000000UL | 0x00000100UL | 0x00000200UL | 0x00000300UL))))))) << 2UL))));

  (((*preg)) = ((((((*preg))) & (~(((0x1FUL << (0U))) << (Rank & (0x0000001FU))))) | ((Channel & ((0x1FUL << (0U)))) << (Rank & (0x0000001FU))))));


}




















































































 
static __inline uint32_t LL_ADC_REG_GetSequencerRanks(const ADC_TypeDef *ADCx, uint32_t Rank)
{
  volatile uint32_t const *preg = ((volatile uint32_t *)((uint32_t) ((uint32_t)(&(ADCx->SQR1)) + (((((Rank) & ((0x00000000UL | 0x00000100UL | 0x00000200UL | 0x00000300UL))) >> (__clz(__rbit(((0x00000000UL | 0x00000100UL | 0x00000200UL | 0x00000300UL))))))) << 2UL))));

  return (uint32_t)(((*preg) & (((0x1FUL << (0U))) << (Rank & (0x0000001FU))))

                    >> (Rank & (0x0000001FU))
                   );
}















 
static __inline void LL_ADC_REG_SetContinuousMode(ADC_TypeDef *ADCx, uint32_t Continuous)
{
  (((ADCx->CR2)) = ((((((ADCx->CR2))) & (~((0x1UL << (1U))))) | (Continuous))));
}












 
static __inline uint32_t LL_ADC_REG_GetContinuousMode(const ADC_TypeDef *ADCx)
{
  return (uint32_t)(((ADCx->CR2) & ((0x1UL << (1U)))));
}































 
static __inline void LL_ADC_REG_SetDMATransfer(ADC_TypeDef *ADCx, uint32_t DMATransfer)
{
  (((ADCx->CR2)) = ((((((ADCx->CR2))) & (~((0x1UL << (8U)) | (0x1UL << (9U))))) | (DMATransfer))));
}






























 
static __inline uint32_t LL_ADC_REG_GetDMATransfer(const ADC_TypeDef *ADCx)
{
  return (uint32_t)(((ADCx->CR2) & ((0x1UL << (8U)) | (0x1UL << (9U)))));
}

















 
static __inline void LL_ADC_REG_SetFlagEndOfConversion(ADC_TypeDef *ADCx, uint32_t EocSelection)
{
  (((ADCx->CR2)) = ((((((ADCx->CR2))) & (~((0x1UL << (10U))))) | (EocSelection))));
}










 
static __inline uint32_t LL_ADC_REG_GetFlagEndOfConversion(const ADC_TypeDef *ADCx)
{
  return (uint32_t)(((ADCx->CR2) & ((0x1UL << (10U)))));
}



 



 































 
static __inline void LL_ADC_INJ_SetTriggerSource(ADC_TypeDef *ADCx, uint32_t TriggerSource)
{
   
   
   
   
   
  (((ADCx->CR2)) = ((((((ADCx->CR2))) & (~((0xFUL << (16U))))) | ((TriggerSource & (0xFUL << (16U)))))));
}


































 
static __inline uint32_t LL_ADC_INJ_GetTriggerSource(const ADC_TypeDef *ADCx)
{
  uint32_t TriggerSource = ((ADCx->CR2) & ((0xFUL << (16U)) | (0x3UL << (20U))));

   
   
  uint32_t ShiftExten = ((TriggerSource & (0x3UL << (20U))) >> ((20UL) - 2UL));

   
   
  return ((TriggerSource
           & ((((0x00000000UL & (0xFUL << (16U))) >> (4UL * 0UL)) | (((0xFUL << (16U))) >> (4UL * 1UL)) | (((0xFUL << (16U))) >> (4UL * 2UL)) | (((0xFUL << (16U))) >> (4UL * 3UL))) << ShiftExten) & (0xFUL << (16U)))
          | (((((0x00000000UL & (0x3UL << (20U))) >> (4UL * 0UL)) | ((((0x1UL << (20U)))) >> (4UL * 1UL)) | ((((0x1UL << (20U)))) >> (4UL * 2UL)) | ((((0x1UL << (20U)))) >> (4UL * 3UL))) << ShiftExten) & (0x3UL << (20U)))
         );
}











 
static __inline uint32_t LL_ADC_INJ_IsTriggerSourceSWStart(const ADC_TypeDef *ADCx)
{
  return (((ADCx->CR2) & ((0x3UL << (20U)))) == (0x00000000UL & (0x3UL << (20U))));
}










 
static __inline uint32_t LL_ADC_INJ_GetTriggerEdge(const ADC_TypeDef *ADCx)
{
  return (uint32_t)(((ADCx->CR2) & ((0x3UL << (20U)))));
}























 
static __inline void LL_ADC_INJ_SetSequencerLength(ADC_TypeDef *ADCx, uint32_t SequencerNbRanks)
{
  (((ADCx->JSQR)) = ((((((ADCx->JSQR))) & (~((0x3UL << (20U))))) | (SequencerNbRanks))));
}






















 
static __inline uint32_t LL_ADC_INJ_GetSequencerLength(const ADC_TypeDef *ADCx)
{
  return (uint32_t)(((ADCx->JSQR) & ((0x3UL << (20U)))));
}













 
static __inline void LL_ADC_INJ_SetSequencerDiscont(ADC_TypeDef *ADCx, uint32_t SeqDiscont)
{
  (((ADCx->CR1)) = ((((((ADCx->CR1))) & (~((0x1UL << (12U))))) | (SeqDiscont))));
}










 
static __inline uint32_t LL_ADC_INJ_GetSequencerDiscont(const ADC_TypeDef *ADCx)
{
  return (uint32_t)(((ADCx->CR1) & ((0x1UL << (12U)))));
}















































 
static __inline void LL_ADC_INJ_SetSequencerRanks(ADC_TypeDef *ADCx, uint32_t Rank, uint32_t Channel)
{
   
   
   
   
  uint32_t tmpreg1 = (((ADCx->JSQR) & ((0x3UL << (20U)))) >> (20U)) + 1UL;

  (((ADCx->JSQR)) = ((((((ADCx->JSQR))) & (~(((0x1FUL << (0U))) << (5UL * (uint8_t)(((Rank) + 3UL) - (tmpreg1)))))) | ((Channel & ((0x1FUL << (0U)))) << (5UL * (uint8_t)(((Rank) + 3UL) - (tmpreg1)))))));


}
























































 
static __inline uint32_t LL_ADC_INJ_GetSequencerRanks(const ADC_TypeDef *ADCx, uint32_t Rank)
{
  uint32_t tmpreg1 = (((ADCx->JSQR) & ((0x3UL << (20U)))) >> (20U))  + 1UL;

  return (uint32_t)(((ADCx->JSQR) & (((0x1FUL << (0U))) << (5UL * (uint8_t)(((Rank) + 3UL) - (tmpreg1)))))

                    >> (5UL * (uint8_t)(((Rank) + 3UL) - (tmpreg1)))
                   );
}


























 
static __inline void LL_ADC_INJ_SetTrigAuto(ADC_TypeDef *ADCx, uint32_t TrigAuto)
{
  (((ADCx->CR1)) = ((((((ADCx->CR1))) & (~((0x1UL << (10U))))) | (TrigAuto))));
}









 
static __inline uint32_t LL_ADC_INJ_GetTrigAuto(const ADC_TypeDef *ADCx)
{
  return (uint32_t)(((ADCx->CR1) & ((0x1UL << (10U)))));
}

























 
static __inline void LL_ADC_INJ_SetOffset(ADC_TypeDef *ADCx, uint32_t Rank, uint32_t OffsetLevel)
{
  volatile uint32_t *preg = ((volatile uint32_t *)((uint32_t) ((uint32_t)(&(ADCx->JOFR1)) + (((((Rank) & ((0x00000000UL | 0x00001000UL | 0x00002000UL | 0x00003000UL))) >> (__clz(__rbit(((0x00000000UL | 0x00001000UL | 0x00002000UL | 0x00003000UL))))))) << 2UL))));

  (((*preg)) = ((((((*preg))) & (~((0xFFFUL << (0U))))) | (OffsetLevel))));


}


















 
static __inline uint32_t LL_ADC_INJ_GetOffset(const ADC_TypeDef *ADCx, uint32_t Rank)
{
  volatile uint32_t const *preg = ((volatile uint32_t *)((uint32_t) ((uint32_t)(&(ADCx->JOFR1)) + (((((Rank) & ((0x00000000UL | 0x00001000UL | 0x00002000UL | 0x00003000UL))) >> (__clz(__rbit(((0x00000000UL | 0x00001000UL | 0x00002000UL | 0x00003000UL))))))) << 2UL))));

  return (uint32_t)(((*preg) & ((0xFFFUL << (0U))))

                   );
}



 



 












































































 
static __inline void LL_ADC_SetChannelSamplingTime(ADC_TypeDef *ADCx, uint32_t Channel, uint32_t SamplingTime)
{
   
   
   
   
  volatile uint32_t *preg = ((volatile uint32_t *)((uint32_t) ((uint32_t)(&(ADCx->SMPR1)) + (((((Channel) & ((0x00000000UL | 0x02000000UL))) >> (__clz(__rbit(((0x00000000UL | 0x02000000UL))))))) << 2UL))));

  (((*preg)) = ((((((*preg))) & (~((0x7UL << (0U)) << (((Channel) & (0x01F00000UL)) >> (__clz(__rbit((0x01F00000UL)))))))) | (SamplingTime << (((Channel) & (0x01F00000UL)) >> (__clz(__rbit((0x01F00000UL)))))))));


}
































































 
static __inline uint32_t LL_ADC_GetChannelSamplingTime(const ADC_TypeDef *ADCx, uint32_t Channel)
{
  volatile uint32_t const *preg = ((volatile uint32_t *)((uint32_t) ((uint32_t)(&(ADCx->SMPR1)) + (((((Channel) & ((0x00000000UL | 0x02000000UL))) >> (__clz(__rbit(((0x00000000UL | 0x02000000UL))))))) << 2UL))));

  return (uint32_t)(((*preg) & ((0x7UL << (0U)) << (((Channel) & (0x01F00000UL)) >> (__clz(__rbit((0x01F00000UL)))))))

                    >> (((Channel) & (0x01F00000UL)) >> (__clz(__rbit((0x01F00000UL)))))
                   );
}



 



 
































































































 
static __inline void LL_ADC_SetAnalogWDMonitChannels(ADC_TypeDef *ADCx, uint32_t AWDChannelGroup)
{
  (((ADCx->CR1)) = ((((((ADCx->CR1))) & (~(((0x1UL << (23U)) | (0x1UL << (22U)) | (0x1UL << (9U)) | (0x1FUL << (0U)))))) | (AWDChannelGroup))));


}

























































































 
static __inline uint32_t LL_ADC_GetAnalogWDMonitChannels(const ADC_TypeDef *ADCx)
{
  return (uint32_t)(((ADCx->CR1) & (((0x1UL << (23U)) | (0x1UL << (22U)) | (0x1UL << (9U)) | (0x1FUL << (0U))))));
}






















 
static __inline void LL_ADC_SetAnalogWDThresholds(ADC_TypeDef *ADCx, uint32_t AWDThresholdsHighLow, uint32_t AWDThresholdValue)
{
  volatile uint32_t *preg = ((volatile uint32_t *)((uint32_t) ((uint32_t)(&(ADCx->HTR)) + ((AWDThresholdsHighLow) << 2UL))));

  (((*preg)) = ((((((*preg))) & (~((0xFFFUL << (0U))))) | (AWDThresholdValue))));


}














 
static __inline uint32_t LL_ADC_GetAnalogWDThresholds(const ADC_TypeDef *ADCx, uint32_t AWDThresholdsHighLow)
{
  volatile uint32_t const *preg = ((volatile uint32_t *)((uint32_t) ((uint32_t)(&(ADCx->HTR)) + ((AWDThresholdsHighLow) << 2UL))));

  return (uint32_t)(((*preg) & ((0xFFFUL << (0U)))));
}



 



 



























 
static __inline void LL_ADC_SetMultimode(ADC_Common_TypeDef *ADCxy_COMMON, uint32_t Multimode)
{
  (((ADCxy_COMMON->CCR)) = ((((((ADCxy_COMMON->CCR))) & (~((0x1FUL << (0U))))) | (Multimode))));
}

























 
static __inline uint32_t LL_ADC_GetMultimode(const ADC_Common_TypeDef *ADCxy_COMMON)
{
  return (uint32_t)(((ADCxy_COMMON->CCR) & ((0x1FUL << (0U)))));
}












































 
static __inline void LL_ADC_SetMultiDMATransfer(ADC_Common_TypeDef *ADCxy_COMMON, uint32_t MultiDMATransfer)
{
  (((ADCxy_COMMON->CCR)) = ((((((ADCxy_COMMON->CCR))) & (~((0x3UL << (14U)) | (0x1UL << (13U))))) | (MultiDMATransfer))));
}











































 
static __inline uint32_t LL_ADC_GetMultiDMATransfer(const ADC_Common_TypeDef *ADCxy_COMMON)
{
  return (uint32_t)(((ADCxy_COMMON->CCR) & ((0x3UL << (14U)) | (0x1UL << (13U)))));
}





























 
static __inline void LL_ADC_SetMultiTwoSamplingDelay(ADC_Common_TypeDef *ADCxy_COMMON, uint32_t MultiTwoSamplingDelay)
{
  (((ADCxy_COMMON->CCR)) = ((((((ADCxy_COMMON->CCR))) & (~((0xFUL << (8U))))) | (MultiTwoSamplingDelay))));
}























 
static __inline uint32_t LL_ADC_GetMultiTwoSamplingDelay(const ADC_Common_TypeDef *ADCxy_COMMON)
{
  return (uint32_t)(((ADCxy_COMMON->CCR) & ((0xFUL << (8U)))));
}




 


 










 
static __inline void LL_ADC_Enable(ADC_TypeDef *ADCx)
{
  ((ADCx->CR2) |= ((0x1UL << (0U))));
}






 
static __inline void LL_ADC_Disable(ADC_TypeDef *ADCx)
{
  ((ADCx->CR2) &= ~((0x1UL << (0U))));
}






 
static __inline uint32_t LL_ADC_IsEnabled(const ADC_TypeDef *ADCx)
{
  return (((ADCx->CR2) & ((0x1UL << (0U)))) == ((0x1UL << (0U))));
}



 



 
















 
static __inline void LL_ADC_REG_StartConversionSWStart(ADC_TypeDef *ADCx)
{
  ((ADCx->CR2) |= ((0x1UL << (30U))));
}
















 
static __inline void LL_ADC_REG_StartConversionExtTrig(ADC_TypeDef *ADCx, uint32_t ExternalTriggerEdge)
{
  ((ADCx->CR2) |= (ExternalTriggerEdge));
}













 
static __inline void LL_ADC_REG_StopConversionExtTrig(ADC_TypeDef *ADCx)
{
  ((ADCx->CR2) &= ~((0x3UL << (28U))));
}









 
static __inline uint32_t LL_ADC_REG_ReadConversionData32(const ADC_TypeDef *ADCx)
{
  return (uint16_t)(((ADCx->DR) & ((0xFFFFUL << (0U)))));
}










 
static __inline uint16_t LL_ADC_REG_ReadConversionData12(const ADC_TypeDef *ADCx)
{
  return (uint16_t)(((ADCx->DR) & ((0xFFFFUL << (0U)))));
}










 
static __inline uint16_t LL_ADC_REG_ReadConversionData10(const ADC_TypeDef *ADCx)
{
  return (uint16_t)(((ADCx->DR) & ((0xFFFFUL << (0U)))));
}










 
static __inline uint8_t LL_ADC_REG_ReadConversionData8(const ADC_TypeDef *ADCx)
{
  return (uint8_t)(((ADCx->DR) & ((0xFFFFUL << (0U)))));
}










 
static __inline uint8_t LL_ADC_REG_ReadConversionData6(const ADC_TypeDef *ADCx)
{
  return (uint8_t)(((ADCx->DR) & ((0xFFFFUL << (0U)))));
}






















 
static __inline uint32_t LL_ADC_REG_ReadMultiConversionData32(const ADC_Common_TypeDef *ADCxy_COMMON, uint32_t ConversionData)
{
  return (uint32_t)(((ADCxy_COMMON->CDR) & ((0xFFFFUL << (16U))))

                    >> (__clz(__rbit(ConversionData)))
                   );
}




 



 
















 
static __inline void LL_ADC_INJ_StartConversionSWStart(ADC_TypeDef *ADCx)
{
  ((ADCx->CR2) |= ((0x1UL << (22U))));
}
















 
static __inline void LL_ADC_INJ_StartConversionExtTrig(ADC_TypeDef *ADCx, uint32_t ExternalTriggerEdge)
{
  ((ADCx->CR2) |= (ExternalTriggerEdge));
}













 
static __inline void LL_ADC_INJ_StopConversionExtTrig(ADC_TypeDef *ADCx)
{
  ((ADCx->CR2) &= ~((0x3UL << (20U))));
}

















 
static __inline uint32_t LL_ADC_INJ_ReadConversionData32(const ADC_TypeDef *ADCx, uint32_t Rank)
{
  volatile uint32_t const *preg = ((volatile uint32_t *)((uint32_t) ((uint32_t)(&(ADCx->JDR1)) + (((((Rank) & ((0x00000000UL | 0x00000100UL | 0x00000200UL | 0x00000300UL))) >> (__clz(__rbit(((0x00000000UL | 0x00000100UL | 0x00000200UL | 0x00000300UL))))))) << 2UL))));

  return (uint32_t)(((*preg) & ((0xFFFFUL << (0U))))

                   );
}


















 
static __inline uint16_t LL_ADC_INJ_ReadConversionData12(const ADC_TypeDef *ADCx, uint32_t Rank)
{
  volatile uint32_t const *preg = ((volatile uint32_t *)((uint32_t) ((uint32_t)(&(ADCx->JDR1)) + (((((Rank) & ((0x00000000UL | 0x00000100UL | 0x00000200UL | 0x00000300UL))) >> (__clz(__rbit(((0x00000000UL | 0x00000100UL | 0x00000200UL | 0x00000300UL))))))) << 2UL))));

  return (uint16_t)(((*preg) & ((0xFFFFUL << (0U))))

                   );
}


















 
static __inline uint16_t LL_ADC_INJ_ReadConversionData10(const ADC_TypeDef *ADCx, uint32_t Rank)
{
  volatile uint32_t const *preg = ((volatile uint32_t *)((uint32_t) ((uint32_t)(&(ADCx->JDR1)) + (((((Rank) & ((0x00000000UL | 0x00000100UL | 0x00000200UL | 0x00000300UL))) >> (__clz(__rbit(((0x00000000UL | 0x00000100UL | 0x00000200UL | 0x00000300UL))))))) << 2UL))));

  return (uint16_t)(((*preg) & ((0xFFFFUL << (0U))))

                   );
}


















 
static __inline uint8_t LL_ADC_INJ_ReadConversionData8(const ADC_TypeDef *ADCx, uint32_t Rank)
{
  volatile uint32_t const *preg = ((volatile uint32_t *)((uint32_t) ((uint32_t)(&(ADCx->JDR1)) + (((((Rank) & ((0x00000000UL | 0x00000100UL | 0x00000200UL | 0x00000300UL))) >> (__clz(__rbit(((0x00000000UL | 0x00000100UL | 0x00000200UL | 0x00000300UL))))))) << 2UL))));

  return (uint8_t)(((*preg) & ((0xFFFFUL << (0U))))

                  );
}


















 
static __inline uint8_t LL_ADC_INJ_ReadConversionData6(const ADC_TypeDef *ADCx, uint32_t Rank)
{
  volatile uint32_t const *preg = ((volatile uint32_t *)((uint32_t) ((uint32_t)(&(ADCx->JDR1)) + (((((Rank) & ((0x00000000UL | 0x00000100UL | 0x00000200UL | 0x00000300UL))) >> (__clz(__rbit(((0x00000000UL | 0x00000100UL | 0x00000200UL | 0x00000300UL))))))) << 2UL))));

  return (uint8_t)(((*preg) & ((0xFFFFUL << (0U))))

                  );
}



 



 










 
static __inline uint32_t LL_ADC_IsActiveFlag_EOCS(const ADC_TypeDef *ADCx)
{
  return (((ADCx->SR) & ((0x1UL << (1U)))) == ((0x1UL << (1U))));
}






 
static __inline uint32_t LL_ADC_IsActiveFlag_OVR(const ADC_TypeDef *ADCx)
{
  return (((ADCx->SR) & ((0x1UL << (5U)))) == ((0x1UL << (5U))));
}







 
static __inline uint32_t LL_ADC_IsActiveFlag_JEOS(const ADC_TypeDef *ADCx)
{
   
   
   
   
  return (((ADCx->SR) & ((0x1UL << (2U)))) == ((0x1UL << (2U))));
}






 
static __inline uint32_t LL_ADC_IsActiveFlag_AWD1(const ADC_TypeDef *ADCx)
{
  return (((ADCx->SR) & ((0x1UL << (0U)))) == ((0x1UL << (0U))));
}










 
static __inline void LL_ADC_ClearFlag_EOCS(ADC_TypeDef *ADCx)
{
  ((ADCx->SR) = (~(0x1UL << (1U))));
}






 
static __inline void LL_ADC_ClearFlag_OVR(ADC_TypeDef *ADCx)
{
  ((ADCx->SR) = (~(0x1UL << (5U))));
}







 
static __inline void LL_ADC_ClearFlag_JEOS(ADC_TypeDef *ADCx)
{
   
   
   
   
  ((ADCx->SR) = (~(0x1UL << (2U))));
}






 
static __inline void LL_ADC_ClearFlag_AWD1(ADC_TypeDef *ADCx)
{
  ((ADCx->SR) = (~(0x1UL << (0U))));
}












 
static __inline uint32_t LL_ADC_IsActiveFlag_MST_EOCS(const ADC_Common_TypeDef *ADCxy_COMMON)
{
  return (((ADCxy_COMMON->CSR) & ((0x1UL << (1U)))) == ((0x1UL << (1U))));
}











 
static __inline uint32_t LL_ADC_IsActiveFlag_SLV1_EOCS(const ADC_Common_TypeDef *ADCxy_COMMON)
{
  return (((ADCxy_COMMON->CSR) & ((0x1UL << (9U)))) == ((0x1UL << (9U))));
}











 
static __inline uint32_t LL_ADC_IsActiveFlag_SLV2_EOCS(const ADC_Common_TypeDef *ADCxy_COMMON)
{
  return (((ADCxy_COMMON->CSR) & ((0x1UL << (17U)))) == ((0x1UL << (17U))));
}






 
static __inline uint32_t LL_ADC_IsActiveFlag_MST_OVR(const ADC_Common_TypeDef *ADCxy_COMMON)
{
  return (((ADCxy_COMMON->CSR) & ((0x1UL << (5U)))) == ((0x1UL << (5U))));
}







 
static __inline uint32_t LL_ADC_IsActiveFlag_SLV1_OVR(const ADC_Common_TypeDef *ADCxy_COMMON)
{
  return (((ADCxy_COMMON->CSR) & ((0x1UL << (13U)))) == ((0x1UL << (13U))));
}







 
static __inline uint32_t LL_ADC_IsActiveFlag_SLV2_OVR(const ADC_Common_TypeDef *ADCxy_COMMON)
{
  return (((ADCxy_COMMON->CSR) & ((0x1UL << (21U)))) == ((0x1UL << (21U))));
}








 
static __inline uint32_t LL_ADC_IsActiveFlag_MST_JEOS(const ADC_Common_TypeDef *ADCxy_COMMON)
{
   
   
   
   
  return (((ADCxy_COMMON->CSR) & ((0x1UL << (2U)))) == ((0x1UL << (2U))));
}







 
static __inline uint32_t LL_ADC_IsActiveFlag_SLV1_JEOS(const ADC_Common_TypeDef *ADCxy_COMMON)
{
   
   
   
   
  return (((ADCxy_COMMON->CSR) & ((0x1UL << (10U)))) == ((0x1UL << (10U))));
}







 
static __inline uint32_t LL_ADC_IsActiveFlag_SLV2_JEOS(const ADC_Common_TypeDef *ADCxy_COMMON)
{
   
   
   
   
  return (((ADCxy_COMMON->CSR) & ((0x1UL << (18U)))) == ((0x1UL << (18U))));
}







 
static __inline uint32_t LL_ADC_IsActiveFlag_MST_AWD1(const ADC_Common_TypeDef *ADCxy_COMMON)
{
  return (((ADCxy_COMMON->CSR) & ((0x1UL << (0U)))) == ((0x1UL << (0U))));
}







 
static __inline uint32_t LL_ADC_IsActiveFlag_SLV1_AWD1(const ADC_Common_TypeDef *ADCxy_COMMON)
{
  return (((ADCxy_COMMON->CSR) & ((0x1UL << (8U)))) == ((0x1UL << (8U))));
}







 
static __inline uint32_t LL_ADC_IsActiveFlag_SLV2_AWD1(const ADC_Common_TypeDef *ADCxy_COMMON)
{
  return (((ADCxy_COMMON->CSR) & ((0x1UL << (16U)))) == ((0x1UL << (16U))));
}





 



 










 
static __inline void LL_ADC_EnableIT_EOCS(ADC_TypeDef *ADCx)
{
  ((ADCx->CR1) |= ((0x1UL << (5U))));
}






 
static __inline void LL_ADC_EnableIT_OVR(ADC_TypeDef *ADCx)
{
  ((ADCx->CR1) |= ((0x1UL << (26U))));
}







 
static __inline void LL_ADC_EnableIT_JEOS(ADC_TypeDef *ADCx)
{
   
   
   
   
  ((ADCx->CR1) |= ((0x1UL << (7U))));
}






 
static __inline void LL_ADC_EnableIT_AWD1(ADC_TypeDef *ADCx)
{
  ((ADCx->CR1) |= ((0x1UL << (6U))));
}










 
static __inline void LL_ADC_DisableIT_EOCS(ADC_TypeDef *ADCx)
{
  ((ADCx->CR1) &= ~((0x1UL << (5U))));
}






 
static __inline void LL_ADC_DisableIT_OVR(ADC_TypeDef *ADCx)
{
  ((ADCx->CR1) &= ~((0x1UL << (26U))));
}







 
static __inline void LL_ADC_DisableIT_JEOS(ADC_TypeDef *ADCx)
{
   
   
   
   
  ((ADCx->CR1) &= ~((0x1UL << (7U))));
}






 
static __inline void LL_ADC_DisableIT_AWD1(ADC_TypeDef *ADCx)
{
  ((ADCx->CR1) &= ~((0x1UL << (6U))));
}











 
static __inline uint32_t LL_ADC_IsEnabledIT_EOCS(const ADC_TypeDef *ADCx)
{
  return (((ADCx->CR1) & ((0x1UL << (5U)))) == ((0x1UL << (5U))));
}







 
static __inline uint32_t LL_ADC_IsEnabledIT_OVR(const ADC_TypeDef *ADCx)
{
  return (((ADCx->CR1) & ((0x1UL << (26U)))) == ((0x1UL << (26U))));
}








 
static __inline uint32_t LL_ADC_IsEnabledIT_JEOS(const ADC_TypeDef *ADCx)
{
   
   
   
   
  return (((ADCx->CR1) & ((0x1UL << (7U)))) == ((0x1UL << (7U))));
}







 
static __inline uint32_t LL_ADC_IsEnabledIT_AWD1(const ADC_TypeDef *ADCx)
{
  return (((ADCx->CR1) & ((0x1UL << (6U)))) == ((0x1UL << (6U))));
}



 

#line 4762 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_adc.h"



 



 





 







#line 32 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_adc.h"



 



 

 


 













 
typedef struct
{
  uint32_t ClockPrescaler;               

 
  uint32_t Resolution;                   
 
  uint32_t DataAlign;                    

 
  uint32_t ScanConvMode;                 





 
  uint32_t EOCSelection;                 





 
  FunctionalState ContinuousConvMode;    

 
  uint32_t NbrOfConversion;              

 
  FunctionalState DiscontinuousConvMode; 


 
  uint32_t NbrOfDiscConversion;          

 
  uint32_t ExternalTrigConv;             


 
  uint32_t ExternalTrigConvEdge;         

 
  FunctionalState DMAContinuousRequests; 



 
} ADC_InitTypeDef;







 
typedef struct
{
  uint32_t Channel;                
 
  uint32_t Rank;                   
 
  uint32_t SamplingTime;           







 
  uint32_t Offset;                  
} ADC_ChannelConfTypeDef;



 
typedef struct
{
  uint32_t WatchdogMode;      
 
  uint32_t HighThreshold;     
 
  uint32_t LowThreshold;      
 
  uint32_t Channel;           

 
  FunctionalState ITMode;     

 
  uint32_t WatchdogNumber;     
} ADC_AnalogWDGConfTypeDef;



 
 





 




 





 




 




 





 



typedef struct

{
  ADC_TypeDef                   *Instance;                    

  ADC_InitTypeDef               Init;                         

  volatile uint32_t                 NbrOfCurrentConversionRank;   

  DMA_HandleTypeDef             *DMA_Handle;                  

  HAL_LockTypeDef               Lock;                         

  volatile uint32_t                 State;                        

  volatile uint32_t                 ErrorCode;                    
#line 220 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_adc.h"
} ADC_HandleTypeDef;

#line 243 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_adc.h"



 

 


 



 
#line 264 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_adc.h"


 




 






 



 
#line 299 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_adc.h"


 



 






 



 






 



 
 
 
#line 347 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_adc.h"


 



 




 



 
#line 382 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_adc.h"





 



 
#line 400 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_adc.h"


 



 





 



 




 



 
#line 433 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_adc.h"


 



 






 



 
#line 457 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_adc.h"


 



 





 



 

 


 




 
#line 495 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_adc.h"





 






 







 







 






 







 







 




 

 
#line 1 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_adc_ex.h"
















 

 







 
#line 29 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_adc_ex.h"



 



 

 


 












 
typedef struct
{
  uint32_t InjectedChannel;                      

 
  uint32_t InjectedRank;                         

 
  uint32_t InjectedSamplingTime;                 







 
  uint32_t InjectedOffset;                       


 
  uint32_t InjectedNbrOfConversion;              



 
  FunctionalState InjectedDiscontinuousConvMode; 





 
  FunctionalState AutoInjectedConv;              






 
  uint32_t ExternalTrigInjecConv;                






 
  uint32_t ExternalTrigInjecConvEdge;            



 
} ADC_InjectionConfTypeDef;



 
typedef struct
{
  uint32_t Mode;              
 
  uint32_t DMAAccessMode;     
 
  uint32_t TwoSamplingDelay;  
 
} ADC_MultiModeTypeDef;



 

 


 



 
#line 149 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_adc_ex.h"


 



 






 



 






 



 
#line 195 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_adc_ex.h"


 



 






 



 
#line 220 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_adc_ex.h"








 




 

 


 
#line 253 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_adc_ex.h"


 

 


 



 

 
HAL_StatusTypeDef HAL_ADCEx_InjectedStart(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef HAL_ADCEx_InjectedStop(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef HAL_ADCEx_InjectedPollForConversion(ADC_HandleTypeDef *hadc, uint32_t Timeout);
HAL_StatusTypeDef HAL_ADCEx_InjectedStart_IT(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef HAL_ADCEx_InjectedStop_IT(ADC_HandleTypeDef *hadc);
uint32_t HAL_ADCEx_InjectedGetValue(ADC_HandleTypeDef *hadc, uint32_t InjectedRank);
HAL_StatusTypeDef HAL_ADCEx_MultiModeStart_DMA(ADC_HandleTypeDef *hadc, uint32_t *pData, uint32_t Length);
HAL_StatusTypeDef HAL_ADCEx_MultiModeStop_DMA(ADC_HandleTypeDef *hadc);
uint32_t HAL_ADCEx_MultiModeGetValue(ADC_HandleTypeDef *hadc);
void HAL_ADCEx_InjectedConvCpltCallback(ADC_HandleTypeDef *hadc);

 
HAL_StatusTypeDef HAL_ADCEx_InjectedConfigChannel(ADC_HandleTypeDef *hadc, ADC_InjectionConfTypeDef *sConfigInjected);
HAL_StatusTypeDef HAL_ADCEx_MultiModeConfigChannel(ADC_HandleTypeDef *hadc, ADC_MultiModeTypeDef *multimode);



 



 
 
 
 


 



 

 


 
#line 311 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_adc_ex.h"

#line 318 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_adc_ex.h"

#line 359 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_adc_ex.h"







 







 







 

 


 



 



 



 








#line 555 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_adc.h"

 


 



 
 
HAL_StatusTypeDef HAL_ADC_Init(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef HAL_ADC_DeInit(ADC_HandleTypeDef *hadc);
void HAL_ADC_MspInit(ADC_HandleTypeDef *hadc);
void HAL_ADC_MspDeInit(ADC_HandleTypeDef *hadc);








 



 
 
HAL_StatusTypeDef HAL_ADC_Start(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef HAL_ADC_Stop(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef HAL_ADC_PollForConversion(ADC_HandleTypeDef *hadc, uint32_t Timeout);

HAL_StatusTypeDef HAL_ADC_PollForEvent(ADC_HandleTypeDef *hadc, uint32_t EventType, uint32_t Timeout);

HAL_StatusTypeDef HAL_ADC_Start_IT(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef HAL_ADC_Stop_IT(ADC_HandleTypeDef *hadc);

void HAL_ADC_IRQHandler(ADC_HandleTypeDef *hadc);

HAL_StatusTypeDef HAL_ADC_Start_DMA(ADC_HandleTypeDef *hadc, uint32_t *pData, uint32_t Length);
HAL_StatusTypeDef HAL_ADC_Stop_DMA(ADC_HandleTypeDef *hadc);

uint32_t HAL_ADC_GetValue(ADC_HandleTypeDef *hadc);

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc);
void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef *hadc);
void HAL_ADC_LevelOutOfWindowCallback(ADC_HandleTypeDef *hadc);
void HAL_ADC_ErrorCallback(ADC_HandleTypeDef *hadc);


 



 
 
HAL_StatusTypeDef HAL_ADC_ConfigChannel(ADC_HandleTypeDef *hadc, ADC_ChannelConfTypeDef *sConfig);
HAL_StatusTypeDef HAL_ADC_AnalogWDGConfig(ADC_HandleTypeDef *hadc, ADC_AnalogWDGConfTypeDef *AnalogWDGConfig);


 



 
 
uint32_t HAL_ADC_GetState(ADC_HandleTypeDef *hadc);
uint32_t HAL_ADC_GetError(ADC_HandleTypeDef *hadc);


 



 
 
 
 


 
 
 
 

 
 
 



 

 



 

 





 









 








 









 






 




#line 772 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_adc.h"

#line 781 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_adc.h"





 







 







 







 







 







 






 






 






 






 






 






 




 

 


 



 



 



 








#line 296 "../Core/Inc/stm32f4xx_hal_conf.h"










#line 1 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_crc.h"
















 

 







 
#line 29 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_crc.h"



 



 

 


 



 
typedef enum
{
  HAL_CRC_STATE_RESET     = 0x00U,   
  HAL_CRC_STATE_READY     = 0x01U,   
  HAL_CRC_STATE_BUSY      = 0x02U,   
  HAL_CRC_STATE_TIMEOUT   = 0x03U,   
  HAL_CRC_STATE_ERROR     = 0x04U    
} HAL_CRC_StateTypeDef;




 
typedef struct
{
  CRC_TypeDef                 *Instance;    

  HAL_LockTypeDef             Lock;         

  volatile HAL_CRC_StateTypeDef   State;        

} CRC_HandleTypeDef;


 

 


 



 

 


 




 






 








 







 



 


 


 



 

 


 

 


 
HAL_StatusTypeDef HAL_CRC_Init(CRC_HandleTypeDef *hcrc);
HAL_StatusTypeDef HAL_CRC_DeInit(CRC_HandleTypeDef *hcrc);
void HAL_CRC_MspInit(CRC_HandleTypeDef *hcrc);
void HAL_CRC_MspDeInit(CRC_HandleTypeDef *hcrc);


 

 


 
uint32_t HAL_CRC_Accumulate(CRC_HandleTypeDef *hcrc, uint32_t pBuffer[], uint32_t BufferLength);
uint32_t HAL_CRC_Calculate(CRC_HandleTypeDef *hcrc, uint32_t pBuffer[], uint32_t BufferLength);


 

 


 
HAL_CRC_StateTypeDef HAL_CRC_GetState(const CRC_HandleTypeDef *hcrc);


 



 



 



 





#line 308 "../Core/Inc/stm32f4xx_hal_conf.h"










#line 1 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dac.h"
















 

 









 

 
#line 33 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dac.h"





 

 



 



 
typedef enum
{
  HAL_DAC_STATE_RESET             = 0x00U,   
  HAL_DAC_STATE_READY             = 0x01U,   
  HAL_DAC_STATE_BUSY              = 0x02U,   
  HAL_DAC_STATE_TIMEOUT           = 0x03U,   
  HAL_DAC_STATE_ERROR             = 0x04U    

} HAL_DAC_StateTypeDef;



 



typedef struct

{
  DAC_TypeDef                 *Instance;      

  volatile HAL_DAC_StateTypeDef   State;          

  HAL_LockTypeDef             Lock;           

  DMA_HandleTypeDef           *DMA_Handle1;   

  DMA_HandleTypeDef           *DMA_Handle2;   

  volatile uint32_t               ErrorCode;      

#line 95 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dac.h"

} DAC_HandleTypeDef;



 
typedef struct
{
  uint32_t DAC_Trigger;                  
 

  uint32_t DAC_OutputBuffer;             
 

} DAC_ChannelConfTypeDef;

#line 137 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dac.h"



 

 



 



 
#line 161 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dac.h"



 



 
#line 178 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dac.h"



 



 





 



 






 



 






 



 







 



 







 



 

 



 




 
#line 262 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dac.h"





 







 






 






 






 









 









 









 










 









 




 

 



 



#line 368 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dac.h"









 

 
#line 1 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dac_ex.h"
















 

 









 

 
#line 33 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dac_ex.h"





 

 



 

 



 



 
#line 79 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dac_ex.h"



 




 

 


 



 
#line 106 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dac_ex.h"

#line 131 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dac_ex.h"


 

 
 



 



 
 

HAL_StatusTypeDef HAL_DACEx_TriangleWaveGenerate(DAC_HandleTypeDef *hdac, uint32_t Channel, uint32_t Amplitude);
HAL_StatusTypeDef HAL_DACEx_NoiseWaveGenerate(DAC_HandleTypeDef *hdac, uint32_t Channel, uint32_t Amplitude);


HAL_StatusTypeDef HAL_DACEx_DualStart(DAC_HandleTypeDef *hdac);
HAL_StatusTypeDef HAL_DACEx_DualStop(DAC_HandleTypeDef *hdac);
HAL_StatusTypeDef HAL_DACEx_DualSetValue(DAC_HandleTypeDef *hdac, uint32_t Alignment, uint32_t Data1, uint32_t Data2);
uint32_t HAL_DACEx_DualGetValue(const DAC_HandleTypeDef *hdac);



void HAL_DACEx_ConvCpltCallbackCh2(DAC_HandleTypeDef *hdac);
void HAL_DACEx_ConvHalfCpltCallbackCh2(DAC_HandleTypeDef *hdac);
void HAL_DACEx_ErrorCallbackCh2(DAC_HandleTypeDef *hdac);
void HAL_DACEx_DMAUnderrunCallbackCh2(DAC_HandleTypeDef *hdac);




 



 



 



 

 
 
void DAC_DMAConvCpltCh2(DMA_HandleTypeDef *hdma);
void DAC_DMAErrorCh2(DMA_HandleTypeDef *hdma);
void DAC_DMAHalfConvCpltCh2(DMA_HandleTypeDef *hdma);



 



 





 





#line 381 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dac.h"

 



 



 
 
HAL_StatusTypeDef HAL_DAC_Init(DAC_HandleTypeDef *hdac);
HAL_StatusTypeDef HAL_DAC_DeInit(DAC_HandleTypeDef *hdac);
void HAL_DAC_MspInit(DAC_HandleTypeDef *hdac);
void HAL_DAC_MspDeInit(DAC_HandleTypeDef *hdac);



 



 
 
HAL_StatusTypeDef HAL_DAC_Start(DAC_HandleTypeDef *hdac, uint32_t Channel);
HAL_StatusTypeDef HAL_DAC_Stop(DAC_HandleTypeDef *hdac, uint32_t Channel);
HAL_StatusTypeDef HAL_DAC_Start_DMA(DAC_HandleTypeDef *hdac, uint32_t Channel, const uint32_t *pData, uint32_t Length,
                                    uint32_t Alignment);
HAL_StatusTypeDef HAL_DAC_Stop_DMA(DAC_HandleTypeDef *hdac, uint32_t Channel);
void HAL_DAC_IRQHandler(DAC_HandleTypeDef *hdac);
HAL_StatusTypeDef HAL_DAC_SetValue(DAC_HandleTypeDef *hdac, uint32_t Channel, uint32_t Alignment, uint32_t Data);

void HAL_DAC_ConvCpltCallbackCh1(DAC_HandleTypeDef *hdac);
void HAL_DAC_ConvHalfCpltCallbackCh1(DAC_HandleTypeDef *hdac);
void HAL_DAC_ErrorCallbackCh1(DAC_HandleTypeDef *hdac);
void HAL_DAC_DMAUnderrunCallbackCh1(DAC_HandleTypeDef *hdac);

#line 424 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_dac.h"



 



 
 
uint32_t HAL_DAC_GetValue(const DAC_HandleTypeDef *hdac, uint32_t Channel);
HAL_StatusTypeDef HAL_DAC_ConfigChannel(DAC_HandleTypeDef *hdac,
                                        const DAC_ChannelConfTypeDef *sConfig, uint32_t Channel);


 



 
 
HAL_DAC_StateTypeDef HAL_DAC_GetState(const DAC_HandleTypeDef *hdac);
uint32_t HAL_DAC_GetError(const DAC_HandleTypeDef *hdac);



 



 



 
void DAC_DMAConvCpltCh1(DMA_HandleTypeDef *hdma);
void DAC_DMAErrorCh1(DMA_HandleTypeDef *hdma);
void DAC_DMAHalfConvCpltCh1(DMA_HandleTypeDef *hdma);


 



 





 






#line 320 "../Core/Inc/stm32f4xx_hal_conf.h"














#line 1 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash.h"















 

 







 
#line 28 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash.h"



 



 

 


 



 
typedef enum
{
  FLASH_PROC_NONE = 0U,
  FLASH_PROC_SECTERASE,
  FLASH_PROC_MASSERASE,
  FLASH_PROC_PROGRAM
} FLASH_ProcedureTypeDef;



 
typedef struct
{
  volatile FLASH_ProcedureTypeDef ProcedureOnGoing;    

  volatile uint32_t               NbSectorsToErase;    

  volatile uint8_t                VoltageForErase;     

  volatile uint32_t               Sector;              

  volatile uint32_t               Bank;                

  volatile uint32_t               Address;             

  HAL_LockTypeDef             Lock;                

  volatile uint32_t               ErrorCode;           

} FLASH_ProcessTypeDef;



 

 


 



 
#line 95 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash.h"


 



 






 




 
#line 124 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash.h"


 




 




 



 







 



 







 



 

 


 





 






 





 





 





 





 





 





 






 








 










 









 
















 















 



 

 
#line 1 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"















 

 







 
#line 28 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"



 



 

 


 



 
typedef struct
{
  uint32_t TypeErase;   
 

  uint32_t Banks;       
 

  uint32_t Sector;      
 

  uint32_t NbSectors;   
 

  uint32_t VoltageRange;
 

} FLASH_EraseInitTypeDef;



 
typedef struct
{
  uint32_t OptionType;   
 

  uint32_t WRPState;     
 

  uint32_t WRPSector;         
 

  uint32_t Banks;        
 

  uint32_t RDPLevel;     
 

  uint32_t BORLevel;     
 

  uint8_t  USERConfig;    

} FLASH_OBProgramInitTypeDef;



 
#line 131 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"


 

 



 



 




 



 






 



 




 



 






 



 






 



 




 



 




 




 




 



 






 

#line 247 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"



 






#line 264 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"


 



 
 
#line 291 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"
 

 





#line 309 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"
 



 




 
#line 325 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"

#line 334 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"


 



 





#line 354 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"


 



 
 
#line 389 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"
 

 
#line 410 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"
 

 
#line 428 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"
 

 
#line 439 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"
 

 
#line 449 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"
 

 
#line 462 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"
 



 



 
 
#line 500 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"
 

 
#line 522 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"
 

 
#line 541 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"
 

 
#line 553 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"
 

 
#line 564 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"
 

 
#line 578 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"
 


 



 
 
#line 615 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"
 

 
#line 637 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"
 

 
#line 649 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"
 

 
#line 660 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"
 

 
#line 675 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"
 



 



 







 



 
#line 706 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"


 



 

 

 


 



 
 
HAL_StatusTypeDef HAL_FLASHEx_Erase(FLASH_EraseInitTypeDef *pEraseInit, uint32_t *SectorError);
HAL_StatusTypeDef HAL_FLASHEx_Erase_IT(FLASH_EraseInitTypeDef *pEraseInit);
HAL_StatusTypeDef HAL_FLASHEx_OBProgram(FLASH_OBProgramInitTypeDef *pOBInit);
void              HAL_FLASHEx_OBGetConfig(FLASH_OBProgramInitTypeDef *pOBInit);

#line 742 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"







 



 
 
 
 


 
 




 




 





 




 




 






 






 

 


 



 



























#line 847 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"







#line 861 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"

#line 881 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"

#line 896 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"







#line 911 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"

#line 926 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"

#line 937 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"

#line 947 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"













#line 966 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"

























































#line 1032 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ex.h"


 



 

 


 
void FLASH_Erase_Sector(uint32_t Sector, uint8_t VoltageRange);
void FLASH_FlushCaches(void);


 



 



 







#line 296 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash.h"
#line 1 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ramfunc.h"















 

 



#line 73 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash_ramfunc.h"




#line 297 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_flash.h"

 


 


 
 
HAL_StatusTypeDef HAL_FLASH_Program(uint32_t TypeProgram, uint32_t Address, uint64_t Data);
HAL_StatusTypeDef HAL_FLASH_Program_IT(uint32_t TypeProgram, uint32_t Address, uint64_t Data);
 
void HAL_FLASH_IRQHandler(void);
 
void HAL_FLASH_EndOfOperationCallback(uint32_t ReturnValue);
void HAL_FLASH_OperationErrorCallback(uint32_t ReturnValue);


 



 
 
HAL_StatusTypeDef HAL_FLASH_Unlock(void);
HAL_StatusTypeDef HAL_FLASH_Lock(void);
HAL_StatusTypeDef HAL_FLASH_OB_Unlock(void);
HAL_StatusTypeDef HAL_FLASH_OB_Lock(void);
 
HAL_StatusTypeDef HAL_FLASH_OB_Launch(void);


 



 
 
uint32_t HAL_FLASH_GetError(void);
HAL_StatusTypeDef FLASH_WaitForLastOperation(uint32_t Timeout);


 



 
 
 


 



 
 


 



 



 



 



 



 




 

 


 



 






 



 

 


 



 



 



 







#line 336 "../Core/Inc/stm32f4xx_hal_conf.h"


























#line 1 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_i2c.h"
















 

 







 
#line 29 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_i2c.h"



 



 

 


 




 
typedef struct
{
  uint32_t ClockSpeed;       
 

  uint32_t DutyCycle;        
 

  uint32_t OwnAddress1;      
 

  uint32_t AddressingMode;   
 

  uint32_t DualAddressMode;  
 

  uint32_t OwnAddress2;      
 

  uint32_t GeneralCallMode;  
 

  uint32_t NoStretchMode;    
 

} I2C_InitTypeDef;



 



























 
typedef enum
{
  HAL_I2C_STATE_RESET             = 0x00U,    
  HAL_I2C_STATE_READY             = 0x20U,    
  HAL_I2C_STATE_BUSY              = 0x24U,    
  HAL_I2C_STATE_BUSY_TX           = 0x21U,    
  HAL_I2C_STATE_BUSY_RX           = 0x22U,    
  HAL_I2C_STATE_LISTEN            = 0x28U,    
  HAL_I2C_STATE_BUSY_TX_LISTEN    = 0x29U,   
 
  HAL_I2C_STATE_BUSY_RX_LISTEN    = 0x2AU,   
 
  HAL_I2C_STATE_ABORT             = 0x60U,    
  HAL_I2C_STATE_TIMEOUT           = 0xA0U,    
  HAL_I2C_STATE_ERROR             = 0xE0U     

} HAL_I2C_StateTypeDef;



 


















 
typedef enum
{
  HAL_I2C_MODE_NONE               = 0x00U,    
  HAL_I2C_MODE_MASTER             = 0x10U,    
  HAL_I2C_MODE_SLAVE              = 0x20U,    
  HAL_I2C_MODE_MEM                = 0x40U     

} HAL_I2C_ModeTypeDef;



 




 
#line 176 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_i2c.h"


 




 



typedef struct

{
  I2C_TypeDef                *Instance;       

  I2C_InitTypeDef            Init;            

  uint8_t                    *pBuffPtr;       

  uint16_t                   XferSize;        

  volatile uint16_t              XferCount;       

  volatile uint32_t              XferOptions;     

  volatile uint32_t              PreviousState;  
 

  DMA_HandleTypeDef          *hdmatx;         

  DMA_HandleTypeDef          *hdmarx;         

  HAL_LockTypeDef            Lock;            

  volatile HAL_I2C_StateTypeDef  State;           

  volatile HAL_I2C_ModeTypeDef   Mode;            

  volatile uint32_t              ErrorCode;       

  volatile uint32_t              Devaddress;      

  volatile uint32_t              Memaddress;      

  volatile uint32_t              MemaddSize;      

  volatile uint32_t              EventCount;      


#line 243 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_i2c.h"
} I2C_HandleTypeDef;

#line 273 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_i2c.h"


 



 
 



 



 




 



 




 



 




 



 




 



 




 



 




 



 




 



 
#line 358 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_i2c.h"



 




 






 





 



 

#line 401 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_i2c.h"


 



 

 



 




 
#line 428 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_i2c.h"









 











 
























 













 






 
#line 503 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_i2c.h"




 
#line 515 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_i2c.h"




 





 




 

 
#line 1 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_i2c_ex.h"
















 

 







#line 108 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_i2c_ex.h"








#line 534 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_i2c.h"

 


 



 
 
HAL_StatusTypeDef HAL_I2C_Init(I2C_HandleTypeDef *hi2c);
HAL_StatusTypeDef HAL_I2C_DeInit(I2C_HandleTypeDef *hi2c);
void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c);
void HAL_I2C_MspDeInit(I2C_HandleTypeDef *hi2c);

 
#line 557 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_i2c.h"


 



 
 
 
HAL_StatusTypeDef HAL_I2C_Master_Transmit(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_I2C_Master_Receive(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_I2C_Slave_Transmit(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_I2C_Slave_Receive(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_I2C_Mem_Write(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_I2C_Mem_Read(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_I2C_IsDeviceReady(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint32_t Trials, uint32_t Timeout);

 
HAL_StatusTypeDef HAL_I2C_Master_Transmit_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_I2C_Master_Receive_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_I2C_Slave_Transmit_IT(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_I2C_Slave_Receive_IT(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_I2C_Mem_Write_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_I2C_Mem_Read_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size);

HAL_StatusTypeDef HAL_I2C_Master_Seq_Transmit_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t XferOptions);
HAL_StatusTypeDef HAL_I2C_Master_Seq_Receive_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t XferOptions);
HAL_StatusTypeDef HAL_I2C_Slave_Seq_Transmit_IT(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size, uint32_t XferOptions);
HAL_StatusTypeDef HAL_I2C_Slave_Seq_Receive_IT(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size, uint32_t XferOptions);
HAL_StatusTypeDef HAL_I2C_EnableListen_IT(I2C_HandleTypeDef *hi2c);
HAL_StatusTypeDef HAL_I2C_DisableListen_IT(I2C_HandleTypeDef *hi2c);
HAL_StatusTypeDef HAL_I2C_Master_Abort_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress);

 
HAL_StatusTypeDef HAL_I2C_Master_Transmit_DMA(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_I2C_Master_Receive_DMA(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_I2C_Slave_Transmit_DMA(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_I2C_Slave_Receive_DMA(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_I2C_Mem_Write_DMA(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_I2C_Mem_Read_DMA(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size);

HAL_StatusTypeDef HAL_I2C_Master_Seq_Transmit_DMA(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t XferOptions);
HAL_StatusTypeDef HAL_I2C_Master_Seq_Receive_DMA(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t XferOptions);
HAL_StatusTypeDef HAL_I2C_Slave_Seq_Transmit_DMA(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size, uint32_t XferOptions);
HAL_StatusTypeDef HAL_I2C_Slave_Seq_Receive_DMA(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size, uint32_t XferOptions);


 



 
 
void HAL_I2C_EV_IRQHandler(I2C_HandleTypeDef *hi2c);
void HAL_I2C_ER_IRQHandler(I2C_HandleTypeDef *hi2c);
void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c);
void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c);
void HAL_I2C_SlaveTxCpltCallback(I2C_HandleTypeDef *hi2c);
void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c);
void HAL_I2C_AddrCallback(I2C_HandleTypeDef *hi2c, uint8_t TransferDirection, uint16_t AddrMatchCode);
void HAL_I2C_ListenCpltCallback(I2C_HandleTypeDef *hi2c);
void HAL_I2C_MemTxCpltCallback(I2C_HandleTypeDef *hi2c);
void HAL_I2C_MemRxCpltCallback(I2C_HandleTypeDef *hi2c);
void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c);
void HAL_I2C_AbortCpltCallback(I2C_HandleTypeDef *hi2c);


 



 
 
HAL_I2C_StateTypeDef HAL_I2C_GetState(I2C_HandleTypeDef *hi2c);
HAL_I2C_ModeTypeDef HAL_I2C_GetMode(I2C_HandleTypeDef *hi2c);
uint32_t HAL_I2C_GetError(I2C_HandleTypeDef *hi2c);



 



 
 
 
 


 





 

 


 

#line 668 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_i2c.h"













 
#line 704 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_i2c.h"








 



 

 


 



 



 



 








#line 364 "../Core/Inc/stm32f4xx_hal_conf.h"


















#line 1 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_pwr.h"















  

 







 
#line 28 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_pwr.h"



 



  

 



 
   


 
typedef struct
{
  uint32_t PVDLevel;   
 

  uint32_t Mode;      
 
}PWR_PVDTypeDef;



 

 


 
  


 



 



  
#line 84 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_pwr.h"


    
 


 
#line 98 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_pwr.h"


 




 




 
    


 






 



 





 



 







 



  
  
 


 





















 







 





 





 





 





 





 





 





 






 






 








 







 





 





 




 

 
#line 1 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_pwr_ex.h"















  

 







 
#line 28 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_pwr_ex.h"



 



  

  
 


 
#line 64 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_pwr_ex.h"



 
#line 78 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_pwr_ex.h"


 
#line 97 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_pwr_ex.h"



  
  
 


 










 
#line 143 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_pwr_ex.h"

#line 191 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_pwr_ex.h"


 

 


 
 


 
void HAL_PWREx_EnableFlashPowerDown(void);
void HAL_PWREx_DisableFlashPowerDown(void); 
HAL_StatusTypeDef HAL_PWREx_EnableBkUpReg(void);
HAL_StatusTypeDef HAL_PWREx_DisableBkUpReg(void); 
uint32_t HAL_PWREx_GetVoltageRange(void);
HAL_StatusTypeDef HAL_PWREx_ControlVoltageScaling(uint32_t VoltageScaling);

#line 219 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_pwr_ex.h"

#line 226 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_pwr_ex.h"



 



 
 
 
 


 



 
 
 
 



 



 


    
 



 



 

 



   
 
 





 



 

 


 



 






#line 308 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_pwr_ex.h"

#line 319 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_pwr_ex.h"


 



 



  



 
  





#line 276 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_pwr.h"

 


 
  


 
 
void HAL_PWR_DeInit(void);
void HAL_PWR_EnableBkUpAccess(void);
void HAL_PWR_DisableBkUpAccess(void);


 



 
 
 
void HAL_PWR_ConfigPVD(PWR_PVDTypeDef *sConfigPVD);
void HAL_PWR_EnablePVD(void);
void HAL_PWR_DisablePVD(void);

 
void HAL_PWR_EnableWakeUpPin(uint32_t WakeUpPinx);
void HAL_PWR_DisableWakeUpPin(uint32_t WakeUpPinx);

 
void HAL_PWR_EnterSTOPMode(uint32_t Regulator, uint8_t STOPEntry);
void HAL_PWR_EnterSLEEPMode(uint32_t Regulator, uint8_t SLEEPEntry);
void HAL_PWR_EnterSTANDBYMode(void);

 
void HAL_PWR_PVD_IRQHandler(void);
void HAL_PWR_PVDCallback(void);

 
void HAL_PWR_EnableSleepOnExit(void);
void HAL_PWR_DisableSleepOnExit(void);
void HAL_PWR_EnableSEVOnPend(void);
void HAL_PWR_DisableSEVOnPend(void);


 



 

 
 
 


 



 



 



 
 







 



 
 
 



 



 




 



 
 
 




 



 
 


 



 
#line 407 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_pwr.h"










 



 



  



 
  





#line 384 "../Core/Inc/stm32f4xx_hal_conf.h"


#line 1 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rng.h"
















 

 







 
#line 29 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rng.h"



 






 

 



 



 



 



 
typedef enum
{
  HAL_RNG_STATE_RESET     = 0x00U,   
  HAL_RNG_STATE_READY     = 0x01U,   
  HAL_RNG_STATE_BUSY      = 0x02U,   
  HAL_RNG_STATE_TIMEOUT   = 0x03U,   
  HAL_RNG_STATE_ERROR     = 0x04U    

} HAL_RNG_StateTypeDef;



 



 



typedef struct

{
  RNG_TypeDef                 *Instance;     

  HAL_LockTypeDef             Lock;          

  volatile HAL_RNG_StateTypeDef   State;         

  volatile  uint32_t              ErrorCode;     

  uint32_t                    RandomNumber;  

#line 98 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rng.h"

} RNG_HandleTypeDef;

#line 121 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rng.h"



 



 

 


 



 





 



 





 



 
#line 166 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rng.h"


 



 

 


 




 
#line 192 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rng.h"





 






 











 









 






 






 











 











 




 

 


 



 
HAL_StatusTypeDef HAL_RNG_Init(RNG_HandleTypeDef *hrng);
HAL_StatusTypeDef HAL_RNG_DeInit(RNG_HandleTypeDef *hrng);
void HAL_RNG_MspInit(RNG_HandleTypeDef *hrng);
void HAL_RNG_MspDeInit(RNG_HandleTypeDef *hrng);

 
#line 293 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_rng.h"



 



 
uint32_t HAL_RNG_GetRandomNumber(RNG_HandleTypeDef
                                 *hrng);     
uint32_t HAL_RNG_GetRandomNumber_IT(RNG_HandleTypeDef
                                    *hrng);  
HAL_StatusTypeDef HAL_RNG_GenerateRandomNumber(RNG_HandleTypeDef *hrng, uint32_t *random32bit);
HAL_StatusTypeDef HAL_RNG_GenerateRandomNumber_IT(RNG_HandleTypeDef *hrng);
uint32_t HAL_RNG_ReadLastRandomNumber(const RNG_HandleTypeDef *hrng);

void HAL_RNG_IRQHandler(RNG_HandleTypeDef *hrng);
void HAL_RNG_ErrorCallback(RNG_HandleTypeDef *hrng);
void HAL_RNG_ReadyDataCallback(RNG_HandleTypeDef *hrng, uint32_t random32bit);



 



 
HAL_RNG_StateTypeDef HAL_RNG_GetState(const RNG_HandleTypeDef *hrng);
uint32_t             HAL_RNG_GetError(const RNG_HandleTypeDef *hrng);


 



 

 


 









 



 





 








#line 388 "../Core/Inc/stm32f4xx_hal_conf.h"


















#line 1 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim.h"
















 

 







 
#line 29 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim.h"



 



 

 


 



 
typedef struct
{
  uint32_t Prescaler;         
 

  uint32_t CounterMode;       
 

  uint32_t Period;            

 

  uint32_t ClockDivision;     
 

  uint32_t RepetitionCounter;  








 

  uint32_t AutoReloadPreload;  
 
} TIM_Base_InitTypeDef;



 
typedef struct
{
  uint32_t OCMode;        
 

  uint32_t Pulse;         
 

  uint32_t OCPolarity;    
 

  uint32_t OCNPolarity;   

 

  uint32_t OCFastMode;    

 


  uint32_t OCIdleState;   

 

  uint32_t OCNIdleState;  

 
} TIM_OC_InitTypeDef;



 
typedef struct
{
  uint32_t OCMode;        
 

  uint32_t Pulse;         
 

  uint32_t OCPolarity;    
 

  uint32_t OCNPolarity;   

 

  uint32_t OCIdleState;   

 

  uint32_t OCNIdleState;  

 

  uint32_t ICPolarity;    
 

  uint32_t ICSelection;   
 

  uint32_t ICFilter;      
 
} TIM_OnePulse_InitTypeDef;



 
typedef struct
{
  uint32_t  ICPolarity;  
 

  uint32_t ICSelection;  
 

  uint32_t ICPrescaler;  
 

  uint32_t ICFilter;     
 
} TIM_IC_InitTypeDef;



 
typedef struct
{
  uint32_t EncoderMode;   
 

  uint32_t IC1Polarity;   
 

  uint32_t IC1Selection;  
 

  uint32_t IC1Prescaler;  
 

  uint32_t IC1Filter;     
 

  uint32_t IC2Polarity;   
 

  uint32_t IC2Selection;  
 

  uint32_t IC2Prescaler;  
 

  uint32_t IC2Filter;     
 
} TIM_Encoder_InitTypeDef;



 
typedef struct
{
  uint32_t ClockSource;     
 
  uint32_t ClockPolarity;   
 
  uint32_t ClockPrescaler;  
 
  uint32_t ClockFilter;     
 
} TIM_ClockConfigTypeDef;



 
typedef struct
{
  uint32_t ClearInputState;      
 
  uint32_t ClearInputSource;     
 
  uint32_t ClearInputPolarity;   
 
  uint32_t ClearInputPrescaler;  

 
  uint32_t ClearInputFilter;     
 
} TIM_ClearInputConfigTypeDef;



 
typedef struct
{
  uint32_t  MasterOutputTrigger;   
 
  uint32_t  MasterSlaveMode;       





 
} TIM_MasterConfigTypeDef;



 
typedef struct
{
  uint32_t  SlaveMode;         
 
  uint32_t  InputTrigger;      
 
  uint32_t  TriggerPolarity;   
 
  uint32_t  TriggerPrescaler;  
 
  uint32_t  TriggerFilter;     
 

} TIM_SlaveConfigTypeDef;





 
typedef struct
{
  uint32_t OffStateRunMode;       

  uint32_t OffStateIDLEMode;      

  uint32_t LockLevel;             

  uint32_t DeadTime;              

  uint32_t BreakState;            

  uint32_t BreakPolarity;         

  uint32_t BreakFilter;           

  uint32_t AutomaticOutput;       

} TIM_BreakDeadTimeConfigTypeDef;



 
typedef enum
{
  HAL_TIM_STATE_RESET             = 0x00U,     
  HAL_TIM_STATE_READY             = 0x01U,     
  HAL_TIM_STATE_BUSY              = 0x02U,     
  HAL_TIM_STATE_TIMEOUT           = 0x03U,     
  HAL_TIM_STATE_ERROR             = 0x04U      
} HAL_TIM_StateTypeDef;



 
typedef enum
{
  HAL_TIM_CHANNEL_STATE_RESET             = 0x00U,     
  HAL_TIM_CHANNEL_STATE_READY             = 0x01U,     
  HAL_TIM_CHANNEL_STATE_BUSY              = 0x02U,     
} HAL_TIM_ChannelStateTypeDef;



 
typedef enum
{
  HAL_DMA_BURST_STATE_RESET             = 0x00U,     
  HAL_DMA_BURST_STATE_READY             = 0x01U,     
  HAL_DMA_BURST_STATE_BUSY              = 0x02U,     
} HAL_TIM_DMABurstStateTypeDef;



 
typedef enum
{
  HAL_TIM_ACTIVE_CHANNEL_1        = 0x01U,     
  HAL_TIM_ACTIVE_CHANNEL_2        = 0x02U,     
  HAL_TIM_ACTIVE_CHANNEL_3        = 0x04U,     
  HAL_TIM_ACTIVE_CHANNEL_4        = 0x08U,     
  HAL_TIM_ACTIVE_CHANNEL_CLEARED  = 0x00U      
} HAL_TIM_ActiveChannel;



 



typedef struct

{
  TIM_TypeDef                        *Instance;          
  TIM_Base_InitTypeDef               Init;               
  HAL_TIM_ActiveChannel              Channel;            
  DMA_HandleTypeDef                  *hdma[7];          
 
  HAL_LockTypeDef                    Lock;               
  volatile HAL_TIM_StateTypeDef          State;              
  volatile HAL_TIM_ChannelStateTypeDef   ChannelState[4];    
  volatile HAL_TIM_ChannelStateTypeDef   ChannelNState[4];   
  volatile HAL_TIM_DMABurstStateTypeDef  DMABurstState;      

#line 380 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim.h"
} TIM_HandleTypeDef;

#line 423 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim.h"



 
 

 


 



 




 



 
#line 466 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim.h"


 



 
#line 481 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim.h"


 



 





 



 




 



 






 



 







 



 





 



 




 



 





 



 




 



 




 



 




 



 




 



 




 



 




 



 





 



 




 



 





 



 






 



 




 



 





 



 
#line 680 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim.h"


 



 




 



 
#line 703 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim.h"


 



 




 



 
#line 731 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim.h"


 



 







 



 
#line 760 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim.h"


 



 







 



 






 



 




 



 






 



 




 



 




 


 






 



 




 



 




 



 




 



 
#line 873 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim.h"


 



 




 



 







 



 
#line 909 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim.h"


 



 
#line 925 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim.h"


 



 







 



 






 



 




 



 
#line 982 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim.h"


 



 
#line 996 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim.h"


 



 






 



 
 

 


 




 
#line 1066 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim.h"





 






 






 
#line 1096 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim.h"







 
#line 1114 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim.h"






 















 















 














 














 



















 



















 
















 
















 








 







 







 






 







 










 











 
#line 1326 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim.h"








 



















 




















 

















 
















 
















 
















 




















 




















 













 












 
















 













 





 
 

 


 

 




 
 

 


 



#line 1591 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim.h"









































































#line 1674 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim.h"














































#line 1728 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim.h"













#line 1747 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim.h"

#line 1756 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim.h"























#line 1797 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim.h"













































#line 1849 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim.h"













#line 1873 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim.h"



 
 

 
#line 1 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim_ex.h"
















 

 







 
#line 29 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim_ex.h"



 



 

 


 



 

typedef struct
{
  uint32_t IC1Polarity;         
 

  uint32_t IC1Prescaler;        
 

  uint32_t IC1Filter;           
 

  uint32_t Commutation_Delay;   
 
} TIM_HallSensor_InitTypeDef;


 
 

 


 



 
#line 82 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim_ex.h"












#line 106 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim_ex.h"


 



 
 

 


 



 
 

 


 
#line 193 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim_ex.h"



 
 

 


 




 
 
HAL_StatusTypeDef HAL_TIMEx_HallSensor_Init(TIM_HandleTypeDef *htim, const TIM_HallSensor_InitTypeDef *sConfig);
HAL_StatusTypeDef HAL_TIMEx_HallSensor_DeInit(TIM_HandleTypeDef *htim);

void HAL_TIMEx_HallSensor_MspInit(TIM_HandleTypeDef *htim);
void HAL_TIMEx_HallSensor_MspDeInit(TIM_HandleTypeDef *htim);

 
HAL_StatusTypeDef HAL_TIMEx_HallSensor_Start(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIMEx_HallSensor_Stop(TIM_HandleTypeDef *htim);
 
HAL_StatusTypeDef HAL_TIMEx_HallSensor_Start_IT(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIMEx_HallSensor_Stop_IT(TIM_HandleTypeDef *htim);
 
HAL_StatusTypeDef HAL_TIMEx_HallSensor_Start_DMA(TIM_HandleTypeDef *htim, uint32_t *pData, uint16_t Length);
HAL_StatusTypeDef HAL_TIMEx_HallSensor_Stop_DMA(TIM_HandleTypeDef *htim);


 




 
 
 
HAL_StatusTypeDef HAL_TIMEx_OCN_Start(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIMEx_OCN_Stop(TIM_HandleTypeDef *htim, uint32_t Channel);

 
HAL_StatusTypeDef HAL_TIMEx_OCN_Start_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIMEx_OCN_Stop_IT(TIM_HandleTypeDef *htim, uint32_t Channel);

 
HAL_StatusTypeDef HAL_TIMEx_OCN_Start_DMA(TIM_HandleTypeDef *htim, uint32_t Channel, const uint32_t *pData,
                                          uint16_t Length);
HAL_StatusTypeDef HAL_TIMEx_OCN_Stop_DMA(TIM_HandleTypeDef *htim, uint32_t Channel);


 




 
 
 
HAL_StatusTypeDef HAL_TIMEx_PWMN_Start(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIMEx_PWMN_Stop(TIM_HandleTypeDef *htim, uint32_t Channel);

 
HAL_StatusTypeDef HAL_TIMEx_PWMN_Start_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIMEx_PWMN_Stop_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
 
HAL_StatusTypeDef HAL_TIMEx_PWMN_Start_DMA(TIM_HandleTypeDef *htim, uint32_t Channel, const uint32_t *pData,
                                           uint16_t Length);
HAL_StatusTypeDef HAL_TIMEx_PWMN_Stop_DMA(TIM_HandleTypeDef *htim, uint32_t Channel);


 




 
 
 
HAL_StatusTypeDef HAL_TIMEx_OnePulseN_Start(TIM_HandleTypeDef *htim, uint32_t OutputChannel);
HAL_StatusTypeDef HAL_TIMEx_OnePulseN_Stop(TIM_HandleTypeDef *htim, uint32_t OutputChannel);

 
HAL_StatusTypeDef HAL_TIMEx_OnePulseN_Start_IT(TIM_HandleTypeDef *htim, uint32_t OutputChannel);
HAL_StatusTypeDef HAL_TIMEx_OnePulseN_Stop_IT(TIM_HandleTypeDef *htim, uint32_t OutputChannel);


 




 
 
HAL_StatusTypeDef HAL_TIMEx_ConfigCommutEvent(TIM_HandleTypeDef *htim, uint32_t  InputTrigger,
                                              uint32_t  CommutationSource);
HAL_StatusTypeDef HAL_TIMEx_ConfigCommutEvent_IT(TIM_HandleTypeDef *htim, uint32_t  InputTrigger,
                                                 uint32_t  CommutationSource);
HAL_StatusTypeDef HAL_TIMEx_ConfigCommutEvent_DMA(TIM_HandleTypeDef *htim, uint32_t  InputTrigger,
                                                  uint32_t  CommutationSource);
HAL_StatusTypeDef HAL_TIMEx_MasterConfigSynchronization(TIM_HandleTypeDef *htim,
                                                        const TIM_MasterConfigTypeDef *sMasterConfig);
HAL_StatusTypeDef HAL_TIMEx_ConfigBreakDeadTime(TIM_HandleTypeDef *htim,
                                                const TIM_BreakDeadTimeConfigTypeDef *sBreakDeadTimeConfig);
HAL_StatusTypeDef HAL_TIMEx_RemapConfig(TIM_HandleTypeDef *htim, uint32_t Remap);


 




 
 
void HAL_TIMEx_CommutCallback(TIM_HandleTypeDef *htim);
void HAL_TIMEx_CommutHalfCpltCallback(TIM_HandleTypeDef *htim);
void HAL_TIMEx_BreakCallback(TIM_HandleTypeDef *htim);


 




 
 
HAL_TIM_StateTypeDef HAL_TIMEx_HallSensor_GetState(const TIM_HandleTypeDef *htim);
HAL_TIM_ChannelStateTypeDef HAL_TIMEx_GetChannelNState(const TIM_HandleTypeDef *htim,  uint32_t ChannelN);


 



 
 

 


 
void TIMEx_DMACommutationCplt(DMA_HandleTypeDef *hdma);
void TIMEx_DMACommutationHalfCplt(DMA_HandleTypeDef *hdma);


 
 



 



 






#line 1881 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim.h"

 


 




 
 
HAL_StatusTypeDef HAL_TIM_Base_Init(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIM_Base_DeInit(TIM_HandleTypeDef *htim);
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim);
void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef *htim);
 
HAL_StatusTypeDef HAL_TIM_Base_Start(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIM_Base_Stop(TIM_HandleTypeDef *htim);
 
HAL_StatusTypeDef HAL_TIM_Base_Start_IT(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIM_Base_Stop_IT(TIM_HandleTypeDef *htim);
 
HAL_StatusTypeDef HAL_TIM_Base_Start_DMA(TIM_HandleTypeDef *htim, const uint32_t *pData, uint16_t Length);
HAL_StatusTypeDef HAL_TIM_Base_Stop_DMA(TIM_HandleTypeDef *htim);


 




 
 
HAL_StatusTypeDef HAL_TIM_OC_Init(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIM_OC_DeInit(TIM_HandleTypeDef *htim);
void HAL_TIM_OC_MspInit(TIM_HandleTypeDef *htim);
void HAL_TIM_OC_MspDeInit(TIM_HandleTypeDef *htim);
 
HAL_StatusTypeDef HAL_TIM_OC_Start(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_OC_Stop(TIM_HandleTypeDef *htim, uint32_t Channel);
 
HAL_StatusTypeDef HAL_TIM_OC_Start_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_OC_Stop_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
 
HAL_StatusTypeDef HAL_TIM_OC_Start_DMA(TIM_HandleTypeDef *htim, uint32_t Channel, const uint32_t *pData,
                                       uint16_t Length);
HAL_StatusTypeDef HAL_TIM_OC_Stop_DMA(TIM_HandleTypeDef *htim, uint32_t Channel);


 




 
 
HAL_StatusTypeDef HAL_TIM_PWM_Init(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIM_PWM_DeInit(TIM_HandleTypeDef *htim);
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim);
void HAL_TIM_PWM_MspDeInit(TIM_HandleTypeDef *htim);
 
HAL_StatusTypeDef HAL_TIM_PWM_Start(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_PWM_Stop(TIM_HandleTypeDef *htim, uint32_t Channel);
 
HAL_StatusTypeDef HAL_TIM_PWM_Start_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_PWM_Stop_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
 
HAL_StatusTypeDef HAL_TIM_PWM_Start_DMA(TIM_HandleTypeDef *htim, uint32_t Channel, const uint32_t *pData,
                                        uint16_t Length);
HAL_StatusTypeDef HAL_TIM_PWM_Stop_DMA(TIM_HandleTypeDef *htim, uint32_t Channel);


 




 
 
HAL_StatusTypeDef HAL_TIM_IC_Init(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIM_IC_DeInit(TIM_HandleTypeDef *htim);
void HAL_TIM_IC_MspInit(TIM_HandleTypeDef *htim);
void HAL_TIM_IC_MspDeInit(TIM_HandleTypeDef *htim);
 
HAL_StatusTypeDef HAL_TIM_IC_Start(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_IC_Stop(TIM_HandleTypeDef *htim, uint32_t Channel);
 
HAL_StatusTypeDef HAL_TIM_IC_Start_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_IC_Stop_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
 
HAL_StatusTypeDef HAL_TIM_IC_Start_DMA(TIM_HandleTypeDef *htim, uint32_t Channel, uint32_t *pData, uint16_t Length);
HAL_StatusTypeDef HAL_TIM_IC_Stop_DMA(TIM_HandleTypeDef *htim, uint32_t Channel);


 




 
 
HAL_StatusTypeDef HAL_TIM_OnePulse_Init(TIM_HandleTypeDef *htim, uint32_t OnePulseMode);
HAL_StatusTypeDef HAL_TIM_OnePulse_DeInit(TIM_HandleTypeDef *htim);
void HAL_TIM_OnePulse_MspInit(TIM_HandleTypeDef *htim);
void HAL_TIM_OnePulse_MspDeInit(TIM_HandleTypeDef *htim);
 
HAL_StatusTypeDef HAL_TIM_OnePulse_Start(TIM_HandleTypeDef *htim, uint32_t OutputChannel);
HAL_StatusTypeDef HAL_TIM_OnePulse_Stop(TIM_HandleTypeDef *htim, uint32_t OutputChannel);
 
HAL_StatusTypeDef HAL_TIM_OnePulse_Start_IT(TIM_HandleTypeDef *htim, uint32_t OutputChannel);
HAL_StatusTypeDef HAL_TIM_OnePulse_Stop_IT(TIM_HandleTypeDef *htim, uint32_t OutputChannel);


 




 
 
HAL_StatusTypeDef HAL_TIM_Encoder_Init(TIM_HandleTypeDef *htim, const TIM_Encoder_InitTypeDef *sConfig);
HAL_StatusTypeDef HAL_TIM_Encoder_DeInit(TIM_HandleTypeDef *htim);
void HAL_TIM_Encoder_MspInit(TIM_HandleTypeDef *htim);
void HAL_TIM_Encoder_MspDeInit(TIM_HandleTypeDef *htim);
 
HAL_StatusTypeDef HAL_TIM_Encoder_Start(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_Encoder_Stop(TIM_HandleTypeDef *htim, uint32_t Channel);
 
HAL_StatusTypeDef HAL_TIM_Encoder_Start_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_Encoder_Stop_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
 
HAL_StatusTypeDef HAL_TIM_Encoder_Start_DMA(TIM_HandleTypeDef *htim, uint32_t Channel, uint32_t *pData1,
                                            uint32_t *pData2, uint16_t Length);
HAL_StatusTypeDef HAL_TIM_Encoder_Stop_DMA(TIM_HandleTypeDef *htim, uint32_t Channel);


 




 
 
void HAL_TIM_IRQHandler(TIM_HandleTypeDef *htim);


 




 
 
HAL_StatusTypeDef HAL_TIM_OC_ConfigChannel(TIM_HandleTypeDef *htim, const TIM_OC_InitTypeDef *sConfig,
                                           uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_PWM_ConfigChannel(TIM_HandleTypeDef *htim, const TIM_OC_InitTypeDef *sConfig,
                                            uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_IC_ConfigChannel(TIM_HandleTypeDef *htim, const TIM_IC_InitTypeDef *sConfig,
                                           uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_OnePulse_ConfigChannel(TIM_HandleTypeDef *htim, TIM_OnePulse_InitTypeDef *sConfig,
                                                 uint32_t OutputChannel,  uint32_t InputChannel);
HAL_StatusTypeDef HAL_TIM_ConfigOCrefClear(TIM_HandleTypeDef *htim,
                                           const TIM_ClearInputConfigTypeDef *sClearInputConfig,
                                           uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_ConfigClockSource(TIM_HandleTypeDef *htim, const TIM_ClockConfigTypeDef *sClockSourceConfig);
HAL_StatusTypeDef HAL_TIM_ConfigTI1Input(TIM_HandleTypeDef *htim, uint32_t TI1_Selection);
HAL_StatusTypeDef HAL_TIM_SlaveConfigSynchro(TIM_HandleTypeDef *htim, const TIM_SlaveConfigTypeDef *sSlaveConfig);
HAL_StatusTypeDef HAL_TIM_SlaveConfigSynchro_IT(TIM_HandleTypeDef *htim, const TIM_SlaveConfigTypeDef *sSlaveConfig);
HAL_StatusTypeDef HAL_TIM_DMABurst_WriteStart(TIM_HandleTypeDef *htim, uint32_t BurstBaseAddress,
                                              uint32_t BurstRequestSrc, const uint32_t  *BurstBuffer,
                                              uint32_t  BurstLength);
HAL_StatusTypeDef HAL_TIM_DMABurst_MultiWriteStart(TIM_HandleTypeDef *htim, uint32_t BurstBaseAddress,
                                                   uint32_t BurstRequestSrc, const uint32_t *BurstBuffer,
                                                   uint32_t BurstLength,  uint32_t DataLength);
HAL_StatusTypeDef HAL_TIM_DMABurst_WriteStop(TIM_HandleTypeDef *htim, uint32_t BurstRequestSrc);
HAL_StatusTypeDef HAL_TIM_DMABurst_ReadStart(TIM_HandleTypeDef *htim, uint32_t BurstBaseAddress,
                                             uint32_t BurstRequestSrc, uint32_t  *BurstBuffer, uint32_t  BurstLength);
HAL_StatusTypeDef HAL_TIM_DMABurst_MultiReadStart(TIM_HandleTypeDef *htim, uint32_t BurstBaseAddress,
                                                  uint32_t BurstRequestSrc, uint32_t  *BurstBuffer,
                                                  uint32_t  BurstLength, uint32_t  DataLength);
HAL_StatusTypeDef HAL_TIM_DMABurst_ReadStop(TIM_HandleTypeDef *htim, uint32_t BurstRequestSrc);
HAL_StatusTypeDef HAL_TIM_GenerateEvent(TIM_HandleTypeDef *htim, uint32_t EventSource);
uint32_t HAL_TIM_ReadCapturedValue(const TIM_HandleTypeDef *htim, uint32_t Channel);


 




 
 
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_PeriodElapsedHalfCpltCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_IC_CaptureHalfCpltCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_PWM_PulseFinishedHalfCpltCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_TriggerCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_TriggerHalfCpltCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_ErrorCallback(TIM_HandleTypeDef *htim);

 








 




 
 
HAL_TIM_StateTypeDef HAL_TIM_Base_GetState(const TIM_HandleTypeDef *htim);
HAL_TIM_StateTypeDef HAL_TIM_OC_GetState(const TIM_HandleTypeDef *htim);
HAL_TIM_StateTypeDef HAL_TIM_PWM_GetState(const TIM_HandleTypeDef *htim);
HAL_TIM_StateTypeDef HAL_TIM_IC_GetState(const TIM_HandleTypeDef *htim);
HAL_TIM_StateTypeDef HAL_TIM_OnePulse_GetState(const TIM_HandleTypeDef *htim);
HAL_TIM_StateTypeDef HAL_TIM_Encoder_GetState(const TIM_HandleTypeDef *htim);

 
HAL_TIM_ActiveChannel HAL_TIM_GetActiveChannel(const TIM_HandleTypeDef *htim);
HAL_TIM_ChannelStateTypeDef HAL_TIM_GetChannelState(const TIM_HandleTypeDef *htim,  uint32_t Channel);
HAL_TIM_DMABurstStateTypeDef HAL_TIM_DMABurstState(const TIM_HandleTypeDef *htim);


 



 
 

 


 
void TIM_Base_SetConfig(TIM_TypeDef *TIMx, const TIM_Base_InitTypeDef *Structure);
void TIM_TI1_SetConfig(TIM_TypeDef *TIMx, uint32_t TIM_ICPolarity, uint32_t TIM_ICSelection, uint32_t TIM_ICFilter);
void TIM_OC2_SetConfig(TIM_TypeDef *TIMx, const TIM_OC_InitTypeDef *OC_Config);
void TIM_ETR_SetConfig(TIM_TypeDef *TIMx, uint32_t TIM_ExtTRGPrescaler,
                       uint32_t TIM_ExtTRGPolarity, uint32_t ExtTRGFilter);

void TIM_DMADelayPulseHalfCplt(DMA_HandleTypeDef *hdma);
void TIM_DMAError(DMA_HandleTypeDef *hdma);
void TIM_DMACaptureCplt(DMA_HandleTypeDef *hdma);
void TIM_DMACaptureHalfCplt(DMA_HandleTypeDef *hdma);
void TIM_CCxChannelCmd(TIM_TypeDef *TIMx, uint32_t Channel, uint32_t ChannelState);







 
 



 



 





#line 408 "../Core/Inc/stm32f4xx_hal_conf.h"


#line 1 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_uart.h"
















 

 







 
#line 29 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_uart.h"



 



 

 


 



 
typedef struct
{
  uint32_t BaudRate;                  



 

  uint32_t WordLength;                
 

  uint32_t StopBits;                  
 

  uint32_t Parity;                    




 

  uint32_t Mode;                      
 

  uint32_t HwFlowCtl;                 
 

  uint32_t OverSampling;              
 
} UART_InitTypeDef;







































 
typedef enum
{
  HAL_UART_STATE_RESET             = 0x00U,    
 
  HAL_UART_STATE_READY             = 0x20U,    
 
  HAL_UART_STATE_BUSY              = 0x24U,    
 
  HAL_UART_STATE_BUSY_TX           = 0x21U,    
 
  HAL_UART_STATE_BUSY_RX           = 0x22U,    
 
  HAL_UART_STATE_BUSY_TX_RX        = 0x23U,    

 
  HAL_UART_STATE_TIMEOUT           = 0xA0U,    
 
  HAL_UART_STATE_ERROR             = 0xE0U     
 
} HAL_UART_StateTypeDef;







 
typedef uint32_t HAL_UART_RxTypeTypeDef;









 
typedef uint32_t HAL_UART_RxEventTypeTypeDef;



 
typedef struct __UART_HandleTypeDef
{
  USART_TypeDef                 *Instance;         

  UART_InitTypeDef              Init;              

  const uint8_t                 *pTxBuffPtr;       

  uint16_t                      TxXferSize;        

  volatile uint16_t                 TxXferCount;       

  uint8_t                       *pRxBuffPtr;       

  uint16_t                      RxXferSize;        

  volatile uint16_t                 RxXferCount;       

  volatile HAL_UART_RxTypeTypeDef ReceptionType;       

  volatile HAL_UART_RxEventTypeTypeDef RxEventType;    

  DMA_HandleTypeDef             *hdmatx;           

  DMA_HandleTypeDef             *hdmarx;           

  HAL_LockTypeDef               Lock;              

  volatile HAL_UART_StateTypeDef    gState;           

 

  volatile HAL_UART_StateTypeDef    RxState;          
 

  volatile uint32_t                 ErrorCode;         

#line 212 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_uart.h"

} UART_HandleTypeDef;

#line 243 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_uart.h"



 

 


 



 
#line 265 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_uart.h"


 



 




 



 




 



 





 



 






 



 





 



 




 



 




 



 




 



 




 





 
#line 369 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_uart.h"


 









 













 



 




 



 





 



 

 


 






 
#line 444 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_uart.h"





 



















 























 







 
#line 509 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_uart.h"






 







 







 







 

















 



















 


















 
















 



















 



















 



















 









 





 






 





 



 

 


 



 

 
HAL_StatusTypeDef HAL_UART_Init(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_HalfDuplex_Init(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_LIN_Init(UART_HandleTypeDef *huart, uint32_t BreakDetectLength);
HAL_StatusTypeDef HAL_MultiProcessor_Init(UART_HandleTypeDef *huart, uint8_t Address, uint32_t WakeUpMethod);
HAL_StatusTypeDef HAL_UART_DeInit(UART_HandleTypeDef *huart);
void HAL_UART_MspInit(UART_HandleTypeDef *huart);
void HAL_UART_MspDeInit(UART_HandleTypeDef *huart);

 
#line 735 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_uart.h"



 



 

 
HAL_StatusTypeDef HAL_UART_Transmit(UART_HandleTypeDef *huart, const uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_UART_Receive(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_UART_Transmit_IT(UART_HandleTypeDef *huart, const uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_UART_Receive_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_UART_Transmit_DMA(UART_HandleTypeDef *huart, const uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_UART_Receive_DMA(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_UART_DMAPause(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_DMAResume(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_DMAStop(UART_HandleTypeDef *huart);

HAL_StatusTypeDef HAL_UARTEx_ReceiveToIdle(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint16_t *RxLen,
                                           uint32_t Timeout);
HAL_StatusTypeDef HAL_UARTEx_ReceiveToIdle_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_UARTEx_ReceiveToIdle_DMA(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);

HAL_UART_RxEventTypeTypeDef HAL_UARTEx_GetRxEventType(UART_HandleTypeDef *huart);

 
HAL_StatusTypeDef HAL_UART_Abort(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_AbortTransmit(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_AbortReceive(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_Abort_IT(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_AbortTransmit_IT(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_AbortReceive_IT(UART_HandleTypeDef *huart);

void HAL_UART_IRQHandler(UART_HandleTypeDef *huart);
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_TxHalfCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_RxHalfCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart);
void HAL_UART_AbortCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_AbortTransmitCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_AbortReceiveCpltCallback(UART_HandleTypeDef *huart);

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size);



 



 
 
HAL_StatusTypeDef HAL_LIN_SendBreak(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_MultiProcessor_EnterMuteMode(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_MultiProcessor_ExitMuteMode(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_HalfDuplex_EnableTransmitter(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_HalfDuplex_EnableReceiver(UART_HandleTypeDef *huart);


 



 
 
HAL_UART_StateTypeDef HAL_UART_GetState(const UART_HandleTypeDef *huart);
uint32_t              HAL_UART_GetError(const UART_HandleTypeDef *huart);


 



 
 
 
 


 


 







 

 


 
#line 859 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_uart.h"






 









 






 

 


 

HAL_StatusTypeDef UART_Start_Receive_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef UART_Start_Receive_DMA(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);



 



 



 







#line 412 "../Core/Inc/stm32f4xx_hal_conf.h"






















#line 1 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_hcd.h"
















 

 







 
#line 1 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_usb.h"
















 

 







 
#line 29 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_usb.h"




 



 

 










 

typedef enum
{
  USB_DEVICE_MODE = 0,
  USB_HOST_MODE   = 1,
  USB_DRD_MODE    = 2
} USB_ModeTypeDef;



 
typedef enum
{
  URB_IDLE = 0,
  URB_DONE,
  URB_NOTREADY,
  URB_NYET,
  URB_ERROR,
  URB_STALL
} USB_URBStateTypeDef;



 
typedef enum
{
  HC_IDLE = 0,
  HC_XFRC,
  HC_HALTED,
  HC_ACK,
  HC_NAK,
  HC_NYET,
  HC_STALL,
  HC_XACTERR,
  HC_BBLERR,
  HC_DATATGLERR
} USB_HCStateTypeDef;




 
typedef struct
{
  uint8_t dev_endpoints;            

 

  uint8_t Host_channels;            

 

  uint8_t dma_enable;              
 

  uint8_t speed;                   

 

  uint8_t ep0_mps;                  

  uint8_t phy_itface;              
 

  uint8_t Sof_enable;               

  uint8_t low_power_enable;         

  uint8_t lpm_enable;               

  uint8_t battery_charging_enable;  

  uint8_t vbus_sensing_enable;      

  uint8_t use_dedicated_ep1;        

  uint8_t use_external_vbus;        

} USB_CfgTypeDef;

typedef struct
{
  uint8_t   num;                  
 

  uint8_t   is_in;                
 

  uint8_t   is_stall;             
 

  uint8_t   is_iso_incomplete;    
 

  uint8_t   type;                 
 

  uint8_t   data_pid_start;       
 

  uint32_t  maxpacket;            
 

  uint8_t   *xfer_buff;            

  uint32_t  xfer_len;              

  uint32_t  xfer_count;            

  uint8_t   even_odd_frame;       
 

  uint16_t  tx_fifo_num;          
 

  uint32_t  dma_addr;              

  uint32_t  xfer_size;             
} USB_EPTypeDef;

typedef struct
{
  uint8_t   dev_addr;           
 

  uint8_t   ch_num;             
 

  uint8_t   ep_num;             
 

  uint8_t   ep_is_in;           
 

  uint8_t   speed;              

 

  uint8_t   do_ping;             
  uint8_t   do_ssplit;           
  uint8_t   do_csplit;           
  uint8_t   ep_ss_schedule;      
  uint32_t  iso_splt_xactPos;    

  uint8_t   hub_port_nbr;        
  uint8_t   hub_addr;            

  uint8_t   ep_type;            
 

  uint16_t  max_packet;         
 

  uint8_t   data_pid;           
 

  uint8_t   *xfer_buff;          

  uint32_t  XferSize;            

  uint32_t  xfer_len;            

  uint32_t  xfer_count;          

  uint8_t   toggle_in;          
 

  uint8_t   toggle_out;         
 

  uint32_t  dma_addr;            

  uint32_t  ErrCnt;              
  uint32_t  NyetErrCnt;          

  USB_URBStateTypeDef urb_state;  
 

  USB_HCStateTypeDef state;       
 
} USB_HCTypeDef;

typedef USB_ModeTypeDef     USB_OTG_ModeTypeDef;
typedef USB_CfgTypeDef      USB_OTG_CfgTypeDef;
typedef USB_EPTypeDef       USB_OTG_EPTypeDef;
typedef USB_URBStateTypeDef USB_OTG_URBStateTypeDef;
typedef USB_HCStateTypeDef  USB_OTG_HCStateTypeDef;
typedef USB_HCTypeDef       USB_OTG_HCTypeDef;

 



 




 




 



 





 



 





 



 




 



 
#line 295 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_ll_usb.h"


 



 





 



 





 



 






 



 






 



 







 



 





 



 






 



 







 




 







 



 





 



 





 



 





 

















































 

 


 









 

 


 

HAL_StatusTypeDef USB_CoreInit(USB_OTG_GlobalTypeDef *USBx, USB_OTG_CfgTypeDef cfg);
HAL_StatusTypeDef USB_DevInit(USB_OTG_GlobalTypeDef *USBx, USB_OTG_CfgTypeDef cfg);
HAL_StatusTypeDef USB_EnableGlobalInt(USB_OTG_GlobalTypeDef *USBx);
HAL_StatusTypeDef USB_DisableGlobalInt(USB_OTG_GlobalTypeDef *USBx);
HAL_StatusTypeDef USB_SetTurnaroundTime(USB_OTG_GlobalTypeDef *USBx, uint32_t hclk, uint8_t speed);
HAL_StatusTypeDef USB_SetCurrentMode(USB_OTG_GlobalTypeDef *USBx, USB_OTG_ModeTypeDef mode);
HAL_StatusTypeDef USB_SetDevSpeed(const USB_OTG_GlobalTypeDef *USBx, uint8_t speed);
HAL_StatusTypeDef USB_FlushRxFifo(USB_OTG_GlobalTypeDef *USBx);
HAL_StatusTypeDef USB_FlushTxFifo(USB_OTG_GlobalTypeDef *USBx, uint32_t num);
HAL_StatusTypeDef USB_ActivateEndpoint(const USB_OTG_GlobalTypeDef *USBx, const USB_OTG_EPTypeDef *ep);
HAL_StatusTypeDef USB_DeactivateEndpoint(const USB_OTG_GlobalTypeDef *USBx, const USB_OTG_EPTypeDef *ep);
HAL_StatusTypeDef USB_ActivateDedicatedEndpoint(const USB_OTG_GlobalTypeDef *USBx, const USB_OTG_EPTypeDef *ep);
HAL_StatusTypeDef USB_DeactivateDedicatedEndpoint(const USB_OTG_GlobalTypeDef *USBx, const USB_OTG_EPTypeDef *ep);
HAL_StatusTypeDef USB_EPStartXfer(USB_OTG_GlobalTypeDef *USBx, USB_OTG_EPTypeDef *ep, uint8_t dma);
HAL_StatusTypeDef USB_WritePacket(const USB_OTG_GlobalTypeDef *USBx, uint8_t *src,
                                  uint8_t ch_ep_num, uint16_t len, uint8_t dma);

void             *USB_ReadPacket(const USB_OTG_GlobalTypeDef *USBx, uint8_t *dest, uint16_t len);
HAL_StatusTypeDef USB_EPSetStall(const USB_OTG_GlobalTypeDef *USBx, const USB_OTG_EPTypeDef *ep);
HAL_StatusTypeDef USB_EPClearStall(const USB_OTG_GlobalTypeDef *USBx, const USB_OTG_EPTypeDef *ep);
HAL_StatusTypeDef USB_EPStopXfer(const USB_OTG_GlobalTypeDef *USBx, USB_OTG_EPTypeDef *ep);
HAL_StatusTypeDef USB_SetDevAddress(const USB_OTG_GlobalTypeDef *USBx, uint8_t address);
HAL_StatusTypeDef USB_DevConnect(const USB_OTG_GlobalTypeDef *USBx);
HAL_StatusTypeDef USB_DevDisconnect(const USB_OTG_GlobalTypeDef *USBx);
HAL_StatusTypeDef USB_StopDevice(USB_OTG_GlobalTypeDef *USBx);
HAL_StatusTypeDef USB_ActivateSetup(const USB_OTG_GlobalTypeDef *USBx);
HAL_StatusTypeDef USB_EP0_OutStart(const USB_OTG_GlobalTypeDef *USBx, uint8_t dma, const uint8_t *psetup);
uint8_t           USB_GetDevSpeed(const USB_OTG_GlobalTypeDef *USBx);
uint32_t          USB_GetMode(const USB_OTG_GlobalTypeDef *USBx);
uint32_t          USB_ReadInterrupts(USB_OTG_GlobalTypeDef const *USBx);
uint32_t          USB_ReadChInterrupts(const USB_OTG_GlobalTypeDef *USBx, uint8_t chnum);
uint32_t          USB_ReadDevAllOutEpInterrupt(const USB_OTG_GlobalTypeDef *USBx);
uint32_t          USB_ReadDevOutEPInterrupt(const USB_OTG_GlobalTypeDef *USBx, uint8_t epnum);
uint32_t          USB_ReadDevAllInEpInterrupt(const USB_OTG_GlobalTypeDef *USBx);
uint32_t          USB_ReadDevInEPInterrupt(const USB_OTG_GlobalTypeDef *USBx, uint8_t epnum);
void              USB_ClearInterrupts(USB_OTG_GlobalTypeDef *USBx, uint32_t interrupt);

HAL_StatusTypeDef USB_HostInit(USB_OTG_GlobalTypeDef *USBx, USB_OTG_CfgTypeDef cfg);
HAL_StatusTypeDef USB_InitFSLSPClkSel(const USB_OTG_GlobalTypeDef *USBx, uint8_t freq);
HAL_StatusTypeDef USB_ResetPort(const USB_OTG_GlobalTypeDef *USBx);
HAL_StatusTypeDef USB_DriveVbus(const USB_OTG_GlobalTypeDef *USBx, uint8_t state);
uint32_t          USB_GetHostSpeed(USB_OTG_GlobalTypeDef const *USBx);
uint32_t          USB_GetCurrentFrame(USB_OTG_GlobalTypeDef const *USBx);
HAL_StatusTypeDef USB_HC_Init(USB_OTG_GlobalTypeDef *USBx, uint8_t ch_num,
                              uint8_t epnum, uint8_t dev_address, uint8_t speed,
                              uint8_t ep_type, uint16_t mps);
HAL_StatusTypeDef USB_HC_StartXfer(USB_OTG_GlobalTypeDef *USBx,
                                   USB_OTG_HCTypeDef *hc, uint8_t dma);

uint32_t          USB_HC_ReadInterrupt(const USB_OTG_GlobalTypeDef *USBx);
HAL_StatusTypeDef USB_HC_Halt(const USB_OTG_GlobalTypeDef *USBx, uint8_t hc_num);
HAL_StatusTypeDef USB_DoPing(const USB_OTG_GlobalTypeDef *USBx, uint8_t ch_num);
HAL_StatusTypeDef USB_StopHost(USB_OTG_GlobalTypeDef *USBx);
HAL_StatusTypeDef USB_ActivateRemoteWakeup(const USB_OTG_GlobalTypeDef *USBx);
HAL_StatusTypeDef USB_DeActivateRemoteWakeup(const USB_OTG_GlobalTypeDef *USBx);




 



 



 



 







#line 29 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_hcd.h"




 



 

 


 



 
typedef enum
{
  HAL_HCD_STATE_RESET    = 0x00,
  HAL_HCD_STATE_READY    = 0x01,
  HAL_HCD_STATE_ERROR    = 0x02,
  HAL_HCD_STATE_BUSY     = 0x03,
  HAL_HCD_STATE_TIMEOUT  = 0x04
} HCD_StateTypeDef;

typedef USB_OTG_GlobalTypeDef   HCD_TypeDef;
typedef USB_OTG_CfgTypeDef      HCD_InitTypeDef;
typedef USB_OTG_HCTypeDef       HCD_HCTypeDef;
typedef USB_OTG_URBStateTypeDef HCD_URBStateTypeDef;
typedef USB_OTG_HCStateTypeDef  HCD_HCStateTypeDef;


 



 



typedef struct

{
  HCD_TypeDef               *Instance;   
  HCD_InitTypeDef           Init;        
  HCD_HCTypeDef             hc[16];      
  HAL_LockTypeDef           Lock;        
  volatile HCD_StateTypeDef     State;       
  volatile  uint32_t            ErrorCode;   
  void                      *pData;      
#line 93 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_hcd.h"
} HCD_HandleTypeDef;


 



 

 


 



 





 



 





 



 




 




 






 



 

 



 












#line 177 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_hcd.h"


 

 


 



 
HAL_StatusTypeDef HAL_HCD_Init(HCD_HandleTypeDef *hhcd);
HAL_StatusTypeDef HAL_HCD_DeInit(HCD_HandleTypeDef *hhcd);
HAL_StatusTypeDef HAL_HCD_HC_Init(HCD_HandleTypeDef *hhcd, uint8_t ch_num,
                                  uint8_t epnum, uint8_t dev_address,
                                  uint8_t speed, uint8_t ep_type, uint16_t mps);

HAL_StatusTypeDef HAL_HCD_HC_Halt(HCD_HandleTypeDef *hhcd, uint8_t ch_num);
void              HAL_HCD_MspInit(HCD_HandleTypeDef *hhcd);
void              HAL_HCD_MspDeInit(HCD_HandleTypeDef *hhcd);

#line 245 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_hcd.h"


 

 


 
HAL_StatusTypeDef HAL_HCD_HC_SubmitRequest(HCD_HandleTypeDef *hhcd, uint8_t ch_num,
                                           uint8_t direction, uint8_t ep_type,
                                           uint8_t token, uint8_t *pbuff,
                                           uint16_t length, uint8_t do_ping);

HAL_StatusTypeDef HAL_HCD_HC_SetHubInfo(HCD_HandleTypeDef *hhcd, uint8_t ch_num,
                                        uint8_t addr, uint8_t PortNbr);

HAL_StatusTypeDef HAL_HCD_HC_ClearHubInfo(HCD_HandleTypeDef *hhcd, uint8_t ch_num);

 
void HAL_HCD_IRQHandler(HCD_HandleTypeDef *hhcd);
void HAL_HCD_WKUP_IRQHandler(HCD_HandleTypeDef *hhcd);
void HAL_HCD_SOF_Callback(HCD_HandleTypeDef *hhcd);
void HAL_HCD_Connect_Callback(HCD_HandleTypeDef *hhcd);
void HAL_HCD_Disconnect_Callback(HCD_HandleTypeDef *hhcd);
void HAL_HCD_PortEnabled_Callback(HCD_HandleTypeDef *hhcd);
void HAL_HCD_PortDisabled_Callback(HCD_HandleTypeDef *hhcd);
void HAL_HCD_HC_NotifyURBChange_Callback(HCD_HandleTypeDef *hhcd, uint8_t chnum,
                                         HCD_URBStateTypeDef urb_state);


 

 


 
HAL_StatusTypeDef HAL_HCD_ResetPort(HCD_HandleTypeDef *hhcd);
HAL_StatusTypeDef HAL_HCD_Start(HCD_HandleTypeDef *hhcd);
HAL_StatusTypeDef HAL_HCD_Stop(HCD_HandleTypeDef *hhcd);


 

 


 
HCD_StateTypeDef        HAL_HCD_GetState(HCD_HandleTypeDef const *hhcd);
HCD_URBStateTypeDef     HAL_HCD_HC_GetURBState(HCD_HandleTypeDef const *hhcd, uint8_t chnum);
HCD_HCStateTypeDef      HAL_HCD_HC_GetState(HCD_HandleTypeDef const *hhcd, uint8_t chnum);
uint32_t                HAL_HCD_HC_GetXferCount(HCD_HandleTypeDef const *hhcd, uint8_t chnum);
uint32_t                HAL_HCD_GetCurrentFrame(HCD_HandleTypeDef *hhcd);
uint32_t                HAL_HCD_GetCurrentSpeed(HCD_HandleTypeDef *hhcd);




 

 


 


 
 



 


 


 






#line 436 "../Core/Inc/stm32f4xx_hal_conf.h"






































 
#line 490 "../Core/Inc/stm32f4xx_hal_conf.h"





#line 30 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal.h"



 



  

 
 



 



 
typedef enum
{
  HAL_TICK_FREQ_10HZ         = 100U,
  HAL_TICK_FREQ_100HZ        = 10U,
  HAL_TICK_FREQ_1KHZ         = 1U,
  HAL_TICK_FREQ_DEFAULT      = HAL_TICK_FREQ_1KHZ
} HAL_TickFreqTypeDef;


 



 
   
 


 


 
#line 93 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal.h"

#line 116 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal.h"


 



 





 






 





#line 155 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal.h"

#line 185 "../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal.h"


 



 





 

 



 
extern volatile uint32_t uwTick;
extern uint32_t uwTickPrio;
extern HAL_TickFreqTypeDef uwTickFreq;


 

 


 


 
 
HAL_StatusTypeDef HAL_Init(void);
HAL_StatusTypeDef HAL_DeInit(void);
void HAL_MspInit(void);
void HAL_MspDeInit(void);
HAL_StatusTypeDef HAL_InitTick (uint32_t TickPriority);


 



 
 
void HAL_IncTick(void);
void HAL_Delay(uint32_t Delay);
uint32_t HAL_GetTick(void);
uint32_t HAL_GetTickPrio(void);
HAL_StatusTypeDef HAL_SetTickFreq(HAL_TickFreqTypeDef Freq);
HAL_TickFreqTypeDef HAL_GetTickFreq(void);
void HAL_SuspendTick(void);
void HAL_ResumeTick(void);
uint32_t HAL_GetHalVersion(void);
uint32_t HAL_GetREVID(void);
uint32_t HAL_GetDEVID(void);
void HAL_DBGMCU_EnableDBGSleepMode(void);
void HAL_DBGMCU_DisableDBGSleepMode(void);
void HAL_DBGMCU_EnableDBGStopMode(void);
void HAL_DBGMCU_DisableDBGStopMode(void);
void HAL_DBGMCU_EnableDBGStandbyMode(void);
void HAL_DBGMCU_DisableDBGStandbyMode(void);
void HAL_EnableCompensationCell(void);
void HAL_DisableCompensationCell(void);
uint32_t HAL_GetUIDw0(void);
uint32_t HAL_GetUIDw1(void);
uint32_t HAL_GetUIDw2(void);







 



 
 
 


 


 
 


 


 
 
 


 



  
  







#line 31 "../Core/Inc/main.h"

 
 

 

 
 

 

 
 

 

 
 

 

 
void Error_Handler(void);

 

 

 
#line 140 "../Core/Inc/main.h"

 

 





#line 6 "../../sPlc/sPlc.h"
#line 1 "C:\\Keil_v5\\ARM\\CMSIS\\Include\\arm_math.h"






































 



























































































 




 








 









 



 






































































 



 



 



 


 






 



 





#line 1 "C:\\Keil_v5\\ARM\\CMSIS\\Include\\core_cm4.h"
 







 

























 










#line 192 "C:\\Keil_v5\\ARM\\CMSIS\\Include\\core_cm4.h"

#line 1787 "C:\\Keil_v5\\ARM\\CMSIS\\Include\\core_cm4.h"

#line 264 "C:\\Keil_v5\\ARM\\CMSIS\\Include\\arm_math.h"
#line 276 "C:\\Keil_v5\\ARM\\CMSIS\\Include\\arm_math.h"

#line 1 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\string.h"
 
 
 
 




 








 












#line 38 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\string.h"


  



    typedef unsigned int size_t;    
#line 54 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\string.h"




extern __declspec(__nothrow) void *memcpy(void * __restrict  ,
                    const void * __restrict  , size_t  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) void *memmove(void *  ,
                    const void *  , size_t  ) __attribute__((__nonnull__(1,2)));
   







 
extern __declspec(__nothrow) char *strcpy(char * __restrict  , const char * __restrict  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) char *strncpy(char * __restrict  , const char * __restrict  , size_t  ) __attribute__((__nonnull__(1,2)));
   





 

extern __declspec(__nothrow) char *strcat(char * __restrict  , const char * __restrict  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) char *strncat(char * __restrict  , const char * __restrict  , size_t  ) __attribute__((__nonnull__(1,2)));
   






 






 

extern __declspec(__nothrow) int memcmp(const void *  , const void *  , size_t  ) __attribute__((__nonnull__(1,2)));
   





 
extern __declspec(__nothrow) int strcmp(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) int strncmp(const char *  , const char *  , size_t  ) __attribute__((__nonnull__(1,2)));
   






 
extern __declspec(__nothrow) int strcasecmp(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   





 
extern __declspec(__nothrow) int strncasecmp(const char *  , const char *  , size_t  ) __attribute__((__nonnull__(1,2)));
   






 
extern __declspec(__nothrow) int strcoll(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   







 

extern __declspec(__nothrow) size_t strxfrm(char * __restrict  , const char * __restrict  , size_t  ) __attribute__((__nonnull__(2)));
   













 


#line 193 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\string.h"
extern __declspec(__nothrow) void *memchr(const void *  , int  , size_t  ) __attribute__((__nonnull__(1)));

   





 

#line 209 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\string.h"
extern __declspec(__nothrow) char *strchr(const char *  , int  ) __attribute__((__nonnull__(1)));

   




 

extern __declspec(__nothrow) size_t strcspn(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   




 

#line 232 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\string.h"
extern __declspec(__nothrow) char *strpbrk(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));

   




 

#line 247 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\string.h"
extern __declspec(__nothrow) char *strrchr(const char *  , int  ) __attribute__((__nonnull__(1)));

   





 

extern __declspec(__nothrow) size_t strspn(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   



 

#line 270 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\string.h"
extern __declspec(__nothrow) char *strstr(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));

   





 

extern __declspec(__nothrow) char *strtok(char * __restrict  , const char * __restrict  ) __attribute__((__nonnull__(2)));
extern __declspec(__nothrow) char *_strtok_r(char *  , const char *  , char **  ) __attribute__((__nonnull__(2,3)));

extern __declspec(__nothrow) char *strtok_r(char *  , const char *  , char **  ) __attribute__((__nonnull__(2,3)));

   

































 

extern __declspec(__nothrow) void *memset(void *  , int  , size_t  ) __attribute__((__nonnull__(1)));
   



 
extern __declspec(__nothrow) char *strerror(int  );
   





 
extern __declspec(__nothrow) size_t strlen(const char *  ) __attribute__((__nonnull__(1)));
   



 

extern __declspec(__nothrow) size_t strlcpy(char *  , const char *  , size_t  ) __attribute__((__nonnull__(1,2)));
   
















 

extern __declspec(__nothrow) size_t strlcat(char *  , const char *  , size_t  ) __attribute__((__nonnull__(1,2)));
   






















 

extern __declspec(__nothrow) void _membitcpybl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpybb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpyhl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpyhb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpywl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpywb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovebl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovebb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovehl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovehb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovewl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovewb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
    














































 







#line 502 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\string.h"



 

#line 279 "C:\\Keil_v5\\ARM\\CMSIS\\Include\\arm_math.h"
#line 1 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\math.h"




 





 












 






   









 






#line 61 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\math.h"

#line 75 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\math.h"







   




 















 
#line 112 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\math.h"











 





extern __attribute__((__pcs__("aapcs"))) unsigned __ARM_dcmp4(double  , double  );
extern __attribute__((__pcs__("aapcs"))) unsigned __ARM_fcmp4(float  , float  );
    




 

extern __declspec(__nothrow) __attribute__((__pcs__("aapcs"))) int __ARM_fpclassifyf(float  );
extern __declspec(__nothrow) __attribute__((__pcs__("aapcs"))) int __ARM_fpclassify(double  );
     
     

static inline __declspec(__nothrow) __attribute__((__pcs__("aapcs"))) int __ARM_isfinitef(float __x)
{
    return (((*(unsigned *)&(__x)) >> 23) & 0xff) != 0xff;
}
static inline __declspec(__nothrow) __attribute__((__pcs__("aapcs"))) int __ARM_isfinite(double __x)
{
    return (((*(1 + (unsigned *)&(__x))) >> 20) & 0x7ff) != 0x7ff;
}
     
     

static inline __declspec(__nothrow) __attribute__((__pcs__("aapcs"))) int __ARM_isinff(float __x)
{
    return ((*(unsigned *)&(__x)) << 1) == 0xff000000;
}
static inline __declspec(__nothrow) __attribute__((__pcs__("aapcs"))) int __ARM_isinf(double __x)
{
    return (((*(1 + (unsigned *)&(__x))) << 1) == 0xffe00000) && ((*(unsigned *)&(__x)) == 0);
}
     
     

static inline __declspec(__nothrow) __attribute__((__pcs__("aapcs"))) int __ARM_islessgreaterf(float __x, float __y)
{
    unsigned __f = __ARM_fcmp4(__x, __y) >> 28;
    return (__f == 8) || (__f == 2);  
}
static inline __declspec(__nothrow) __attribute__((__pcs__("aapcs"))) int __ARM_islessgreater(double __x, double __y)
{
    unsigned __f = __ARM_dcmp4(__x, __y) >> 28;
    return (__f == 8) || (__f == 2);  
}
    


 

static inline __declspec(__nothrow) __attribute__((__pcs__("aapcs"))) int __ARM_isnanf(float __x)
{
    return (0x7f800000 - ((*(unsigned *)&(__x)) & 0x7fffffff)) >> 31;
}
static inline __declspec(__nothrow) __attribute__((__pcs__("aapcs"))) int __ARM_isnan(double __x)
{
    unsigned __xf = (*(1 + (unsigned *)&(__x))) | (((*(unsigned *)&(__x)) == 0) ? 0 : 1);
    return (0x7ff00000 - (__xf & 0x7fffffff)) >> 31;
}
     
     

static inline __declspec(__nothrow) __attribute__((__pcs__("aapcs"))) int __ARM_isnormalf(float __x)
{
    unsigned __xe = ((*(unsigned *)&(__x)) >> 23) & 0xff;
    return (__xe != 0xff) && (__xe != 0);
}
static inline __declspec(__nothrow) __attribute__((__pcs__("aapcs"))) int __ARM_isnormal(double __x)
{
    unsigned __xe = ((*(1 + (unsigned *)&(__x))) >> 20) & 0x7ff;
    return (__xe != 0x7ff) && (__xe != 0);
}
     
     

static inline __declspec(__nothrow) __attribute__((__pcs__("aapcs"))) int __ARM_signbitf(float __x)
{
    return (*(unsigned *)&(__x)) >> 31;
}
static inline __declspec(__nothrow) __attribute__((__pcs__("aapcs"))) int __ARM_signbit(double __x)
{
    return (*(1 + (unsigned *)&(__x))) >> 31;
}
     
     








#line 230 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\math.h"







   
  typedef float float_t;
  typedef double double_t;
#line 251 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\math.h"



extern const int math_errhandling;
#line 261 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\math.h"

extern __declspec(__nothrow) double acos(double  );
    
    
    
extern __declspec(__nothrow) double asin(double  );
    
    
    
    

extern __declspec(__nothrow) __attribute__((const)) double atan(double  );
    
    

extern __declspec(__nothrow) double atan2(double  , double  );
    
    
    
    

extern __declspec(__nothrow) double cos(double  );
    
    
    
    
extern __declspec(__nothrow) double sin(double  );
    
    
    
    

extern void __use_accurate_range_reduction(void);
    
    

extern __declspec(__nothrow) double tan(double  );
    
    
    
    

extern __declspec(__nothrow) double cosh(double  );
    
    
    
    
extern __declspec(__nothrow) double sinh(double  );
    
    
    
    
    

extern __declspec(__nothrow) __attribute__((const)) double tanh(double  );
    
    

extern __declspec(__nothrow) double exp(double  );
    
    
    
    
    

extern __declspec(__nothrow) double frexp(double  , int *  ) __attribute__((__nonnull__(2)));
    
    
    
    
    
    

extern __declspec(__nothrow) double ldexp(double  , int  );
    
    
    
    
extern __declspec(__nothrow) double log(double  );
    
    
    
    
    
extern __declspec(__nothrow) double log10(double  );
    
    
    
extern __declspec(__nothrow) double modf(double  , double *  ) __attribute__((__nonnull__(2)));
    
    
    
    

extern __declspec(__nothrow) double pow(double  , double  );
    
    
    
    
    
    
extern __declspec(__nothrow) double sqrt(double  );
    
    
    




    inline double _sqrt(double __x) { return sqrt(__x); }


    inline float _sqrtf(float __x) { return __sqrtf(__x); }



    



 

extern __declspec(__nothrow) __attribute__((const)) double ceil(double  );
    
    
extern __declspec(__nothrow) __attribute__((const)) double fabs(double  );
    
    

extern __declspec(__nothrow) __attribute__((const)) double floor(double  );
    
    

extern __declspec(__nothrow) double fmod(double  , double  );
    
    
    
    
    

    









 



extern __declspec(__nothrow) double acosh(double  );
    

 
extern __declspec(__nothrow) double asinh(double  );
    

 
extern __declspec(__nothrow) double atanh(double  );
    

 
extern __declspec(__nothrow) double cbrt(double  );
    

 
inline __declspec(__nothrow) __attribute__((const)) double copysign(double __x, double __y)
    

 
{
    (*(1 + (unsigned *)&(__x))) = ((*(1 + (unsigned *)&(__x))) & 0x7fffffff) | ((*(1 + (unsigned *)&(__y))) & 0x80000000);
    return __x;
}
inline __declspec(__nothrow) __attribute__((const)) float copysignf(float __x, float __y)
    

 
{
    (*(unsigned *)&(__x)) = ((*(unsigned *)&(__x)) & 0x7fffffff) | ((*(unsigned *)&(__y)) & 0x80000000);
    return __x;
}
extern __declspec(__nothrow) double erf(double  );
    

 
extern __declspec(__nothrow) double erfc(double  );
    

 
extern __declspec(__nothrow) double expm1(double  );
    

 



    

 






#line 479 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\math.h"


extern __declspec(__nothrow) double hypot(double  , double  );
    




 
extern __declspec(__nothrow) int ilogb(double  );
    

 
extern __declspec(__nothrow) int ilogbf(float  );
    

 
extern __declspec(__nothrow) int ilogbl(long double  );
    

 







    

 





    



 





    



 





    

 





    



 





    



 





    



 





    

 





    

 





    


 

extern __declspec(__nothrow) double lgamma (double  );
    


 
extern __declspec(__nothrow) double log1p(double  );
    

 
extern __declspec(__nothrow) double logb(double  );
    

 
extern __declspec(__nothrow) float logbf(float  );
    

 
extern __declspec(__nothrow) long double logbl(long double  );
    

 
extern __declspec(__nothrow) double nextafter(double  , double  );
    


 
extern __declspec(__nothrow) float nextafterf(float  , float  );
    


 
extern __declspec(__nothrow) long double nextafterl(long double  , long double  );
    


 
extern __declspec(__nothrow) double nexttoward(double  , long double  );
    


 
extern __declspec(__nothrow) float nexttowardf(float  , long double  );
    


 
extern __declspec(__nothrow) long double nexttowardl(long double  , long double  );
    


 
extern __declspec(__nothrow) double remainder(double  , double  );
    

 
extern __declspec(__nothrow) __attribute__((const)) double rint(double  );
    

 
extern __declspec(__nothrow) double scalbln(double  , long int  );
    

 
extern __declspec(__nothrow) float scalblnf(float  , long int  );
    

 
extern __declspec(__nothrow) long double scalblnl(long double  , long int  );
    

 
extern __declspec(__nothrow) double scalbn(double  , int  );
    

 
extern __declspec(__nothrow) float scalbnf(float  , int  );
    

 
extern __declspec(__nothrow) long double scalbnl(long double  , int  );
    

 




    

 



 
extern __declspec(__nothrow) __attribute__((const)) float _fabsf(float);  
inline __declspec(__nothrow) __attribute__((const)) float fabsf(float __f) { return _fabsf(__f); }
extern __declspec(__nothrow) float sinf(float  );
extern __declspec(__nothrow) float cosf(float  );
extern __declspec(__nothrow) float tanf(float  );
extern __declspec(__nothrow) float acosf(float  );
extern __declspec(__nothrow) float asinf(float  );
extern __declspec(__nothrow) float atanf(float  );
extern __declspec(__nothrow) float atan2f(float  , float  );
extern __declspec(__nothrow) float sinhf(float  );
extern __declspec(__nothrow) float coshf(float  );
extern __declspec(__nothrow) float tanhf(float  );
extern __declspec(__nothrow) float expf(float  );
extern __declspec(__nothrow) float logf(float  );
extern __declspec(__nothrow) float log10f(float  );
extern __declspec(__nothrow) float powf(float  , float  );
extern __declspec(__nothrow) float sqrtf(float  );
extern __declspec(__nothrow) float ldexpf(float  , int  );
extern __declspec(__nothrow) float frexpf(float  , int *  ) __attribute__((__nonnull__(2)));
extern __declspec(__nothrow) __attribute__((const)) float ceilf(float  );
extern __declspec(__nothrow) __attribute__((const)) float floorf(float  );
extern __declspec(__nothrow) float fmodf(float  , float  );
extern __declspec(__nothrow) float modff(float  , float *  ) __attribute__((__nonnull__(2)));

 
 













 
__declspec(__nothrow) long double acosl(long double );
__declspec(__nothrow) long double asinl(long double );
__declspec(__nothrow) long double atanl(long double );
__declspec(__nothrow) long double atan2l(long double , long double );
__declspec(__nothrow) long double ceill(long double );
__declspec(__nothrow) long double cosl(long double );
__declspec(__nothrow) long double coshl(long double );
__declspec(__nothrow) long double expl(long double );
__declspec(__nothrow) long double fabsl(long double );
__declspec(__nothrow) long double floorl(long double );
__declspec(__nothrow) long double fmodl(long double , long double );
__declspec(__nothrow) long double frexpl(long double , int* ) __attribute__((__nonnull__(2)));
__declspec(__nothrow) long double ldexpl(long double , int );
__declspec(__nothrow) long double logl(long double );
__declspec(__nothrow) long double log10l(long double );
__declspec(__nothrow) long double modfl(long double  , long double *  ) __attribute__((__nonnull__(2)));
__declspec(__nothrow) long double powl(long double , long double );
__declspec(__nothrow) long double sinl(long double );
__declspec(__nothrow) long double sinhl(long double );
__declspec(__nothrow) long double sqrtl(long double );
__declspec(__nothrow) long double tanl(long double );
__declspec(__nothrow) long double tanhl(long double );





 
extern __declspec(__nothrow) float acoshf(float  );
__declspec(__nothrow) long double acoshl(long double );
extern __declspec(__nothrow) float asinhf(float  );
__declspec(__nothrow) long double asinhl(long double );
extern __declspec(__nothrow) float atanhf(float  );
__declspec(__nothrow) long double atanhl(long double );
__declspec(__nothrow) long double copysignl(long double , long double );
extern __declspec(__nothrow) float cbrtf(float  );
__declspec(__nothrow) long double cbrtl(long double );
extern __declspec(__nothrow) float erff(float  );
__declspec(__nothrow) long double erfl(long double );
extern __declspec(__nothrow) float erfcf(float  );
__declspec(__nothrow) long double erfcl(long double );
extern __declspec(__nothrow) float expm1f(float  );
__declspec(__nothrow) long double expm1l(long double );
extern __declspec(__nothrow) float log1pf(float  );
__declspec(__nothrow) long double log1pl(long double );
extern __declspec(__nothrow) float hypotf(float  , float  );
__declspec(__nothrow) long double hypotl(long double , long double );
extern __declspec(__nothrow) float lgammaf(float  );
__declspec(__nothrow) long double lgammal(long double );
extern __declspec(__nothrow) float remainderf(float  , float  );
__declspec(__nothrow) long double remainderl(long double , long double );
extern __declspec(__nothrow) float rintf(float  );
__declspec(__nothrow) long double rintl(long double );






 
extern __declspec(__nothrow) double exp2(double  );  
extern __declspec(__nothrow) float exp2f(float  );
__declspec(__nothrow) long double exp2l(long double );
extern __declspec(__nothrow) double fdim(double  , double  );
extern __declspec(__nothrow) float fdimf(float  , float  );
__declspec(__nothrow) long double fdiml(long double , long double );
#line 803 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\math.h"
extern __declspec(__nothrow) double fma(double  , double  , double  );
extern __declspec(__nothrow) float fmaf(float  , float  , float  );

inline __declspec(__nothrow) long double fmal(long double __x, long double __y, long double __z)     { return (long double)fma((double)__x, (double)__y, (double)__z); }


extern __declspec(__nothrow) __attribute__((const)) double fmax(double  , double  );
extern __declspec(__nothrow) __attribute__((const)) float fmaxf(float  , float  );
__declspec(__nothrow) long double fmaxl(long double , long double );
extern __declspec(__nothrow) __attribute__((const)) double fmin(double  , double  );
extern __declspec(__nothrow) __attribute__((const)) float fminf(float  , float  );
__declspec(__nothrow) long double fminl(long double , long double );
extern __declspec(__nothrow) double log2(double  );  
extern __declspec(__nothrow) float log2f(float  );
__declspec(__nothrow) long double log2l(long double );
extern __declspec(__nothrow) long lrint(double  );
extern __declspec(__nothrow) long lrintf(float  );

inline __declspec(__nothrow) long lrintl(long double __x)     { return lrint((double)__x); }


extern __declspec(__nothrow) long long llrint(double  );
extern __declspec(__nothrow) long long llrintf(float  );

inline __declspec(__nothrow) long long llrintl(long double __x)     { return llrint((double)__x); }


extern __declspec(__nothrow) long lround(double  );
extern __declspec(__nothrow) long lroundf(float  );

inline __declspec(__nothrow) long lroundl(long double __x)     { return lround((double)__x); }


extern __declspec(__nothrow) long long llround(double  );
extern __declspec(__nothrow) long long llroundf(float  );

inline __declspec(__nothrow) long long llroundl(long double __x)     { return llround((double)__x); }


extern __declspec(__nothrow) __attribute__((const)) double nan(const char * );
extern __declspec(__nothrow) __attribute__((const)) float nanf(const char * );

inline __declspec(__nothrow) __attribute__((const)) long double nanl(const char *__t)     { return (long double)nan(__t); }
#line 856 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\math.h"
extern __declspec(__nothrow) __attribute__((const)) double nearbyint(double  );
extern __declspec(__nothrow) __attribute__((const)) float nearbyintf(float  );
__declspec(__nothrow) long double nearbyintl(long double );
extern  double remquo(double  , double  , int * );
extern  float remquof(float  , float  , int * );

inline long double remquol(long double __x, long double __y, int *__q)     { return (long double)remquo((double)__x, (double)__y, __q); }


extern __declspec(__nothrow) __attribute__((const)) double round(double  );
extern __declspec(__nothrow) __attribute__((const)) float roundf(float  );
__declspec(__nothrow) long double roundl(long double );
extern __declspec(__nothrow) double tgamma(double  );  
extern __declspec(__nothrow) float tgammaf(float  );
__declspec(__nothrow) long double tgammal(long double );
extern __declspec(__nothrow) __attribute__((const)) double trunc(double  );
extern __declspec(__nothrow) __attribute__((const)) float truncf(float  );
__declspec(__nothrow) long double truncl(long double );






#line 896 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\math.h"

#line 1087 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\math.h"











#line 1317 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\math.h"





 
#line 280 "C:\\Keil_v5\\ARM\\CMSIS\\Include\\arm_math.h"






  

 

#line 296 "C:\\Keil_v5\\ARM\\CMSIS\\Include\\arm_math.h"

  

 

#line 308 "C:\\Keil_v5\\ARM\\CMSIS\\Include\\arm_math.h"

  

 
   
   


  

 
#line 328 "C:\\Keil_v5\\ARM\\CMSIS\\Include\\arm_math.h"

  

 

  typedef enum
  {
    ARM_MATH_SUCCESS = 0,                 
    ARM_MATH_ARGUMENT_ERROR = -1,         
    ARM_MATH_LENGTH_ERROR = -2,           
    ARM_MATH_SIZE_MISMATCH = -3,          
    ARM_MATH_NANINF = -4,                 
    ARM_MATH_SINGULAR = -5,               
    ARM_MATH_TEST_FAILURE = -6            
  } arm_status;

  

 
  typedef int8_t q7_t;

  

 
  typedef int16_t q15_t;

  

 
  typedef int32_t q31_t;

  

 
  typedef int64_t q63_t;

  

 
  typedef float float32_t;

  

 
  typedef double float64_t;

  

 
#line 392 "C:\\Keil_v5\\ARM\\CMSIS\\Include\\arm_math.h"








#line 410 "C:\\Keil_v5\\ARM\\CMSIS\\Include\\arm_math.h"


   

 


#line 429 "C:\\Keil_v5\\ARM\\CMSIS\\Include\\arm_math.h"


  

 
  static __inline q31_t clip_q63_to_q31(
  q63_t x)
  {
    return ((q31_t) (x >> 32) != ((q31_t) x >> 31)) ?
      ((0x7FFFFFFF ^ ((q31_t) (x >> 63)))) : (q31_t) x;
  }

  

 
  static __inline q15_t clip_q63_to_q15(
  q63_t x)
  {
    return ((q31_t) (x >> 32) != ((q31_t) x >> 31)) ?
      ((0x7FFF ^ ((q15_t) (x >> 63)))) : (q15_t) (x >> 15);
  }

  

 
  static __inline q7_t clip_q31_to_q7(
  q31_t x)
  {
    return ((q31_t) (x >> 24) != ((q31_t) x >> 23)) ?
      ((0x7F ^ ((q7_t) (x >> 31)))) : (q7_t) x;
  }

  

 
  static __inline q15_t clip_q31_to_q15(
  q31_t x)
  {
    return ((q31_t) (x >> 16) != ((q31_t) x >> 15)) ?
      ((0x7FFF ^ ((q15_t) (x >> 31)))) : (q15_t) x;
  }

  

 

  static __inline q63_t mult32x64(
  q63_t x,
  q31_t y)
  {
    return ((((q63_t) (x & 0x00000000FFFFFFFF) * y) >> 32) +
            (((q63_t) (x >> 32) * y)));
  }






#line 511 "C:\\Keil_v5\\ARM\\CMSIS\\Include\\arm_math.h"

  

 

  static __inline uint32_t arm_recip_q31(
  q31_t in,
  q31_t * dst,
  q31_t * pRecipTable)
  {

    uint32_t out, tempVal;
    uint32_t index, i;
    uint32_t signBits;

    if(in > 0)
    {
      signBits = __clz(in) - 1;
    }
    else
    {
      signBits = __clz(-in) - 1;
    }

     
    in = in << signBits;

     
    index = (uint32_t) (in >> 24u);
    index = (index & 0x0000003F);

     
    out = pRecipTable[index];

     
     
    for (i = 0u; i < 2u; i++)
    {
      tempVal = (q31_t) (((q63_t) in * out) >> 31u);
      tempVal = 0x7FFFFFFF - tempVal;
       
      
      out = (q31_t) clip_q63_to_q31(((q63_t) out * tempVal) >> 30u);
    }

     
    *dst = out;

     
    return (signBits + 1u);

  }

  

 
  static __inline uint32_t arm_recip_q15(
  q15_t in,
  q15_t * dst,
  q15_t * pRecipTable)
  {

    uint32_t out = 0, tempVal = 0;
    uint32_t index = 0, i = 0;
    uint32_t signBits = 0;

    if(in > 0)
    {
      signBits = __clz(in) - 17;
    }
    else
    {
      signBits = __clz(-in) - 17;
    }

     
    in = in << signBits;

     
    index = in >> 8;
    index = (index & 0x0000003F);

     
    out = pRecipTable[index];

     
     
    for (i = 0; i < 2; i++)
    {
      tempVal = (q15_t) (((q31_t) in * out) >> 15);
      tempVal = 0x7FFF - tempVal;
       
      out = (q15_t) (((q31_t) out * tempVal) >> 14);
    }

     
    *dst = out;

     
    return (signBits + 1);

  }


  

 
#line 657 "C:\\Keil_v5\\ARM\\CMSIS\\Include\\arm_math.h"



  

 
#line 1040 "C:\\Keil_v5\\ARM\\CMSIS\\Include\\arm_math.h"


  

 
  typedef struct
  {
    uint16_t numTaps;         
    q7_t *pState;             
    q7_t *pCoeffs;            
  } arm_fir_instance_q7;

  

 
  typedef struct
  {
    uint16_t numTaps;          
    q15_t *pState;             
    q15_t *pCoeffs;            
  } arm_fir_instance_q15;

  

 
  typedef struct
  {
    uint16_t numTaps;          
    q31_t *pState;             
    q31_t *pCoeffs;            
  } arm_fir_instance_q31;

  

 
  typedef struct
  {
    uint16_t numTaps;      
    float32_t *pState;     
    float32_t *pCoeffs;    
  } arm_fir_instance_f32;


  






 
  void arm_fir_q7(
  const arm_fir_instance_q7 * S,
  q7_t * pSrc,
  q7_t * pDst,
  uint32_t blockSize);


  







 
  void arm_fir_init_q7(
  arm_fir_instance_q7 * S,
  uint16_t numTaps,
  q7_t * pCoeffs,
  q7_t * pState,
  uint32_t blockSize);


  






 
  void arm_fir_q15(
  const arm_fir_instance_q15 * S,
  q15_t * pSrc,
  q15_t * pDst,
  uint32_t blockSize);

  






 
  void arm_fir_fast_q15(
  const arm_fir_instance_q15 * S,
  q15_t * pSrc,
  q15_t * pDst,
  uint32_t blockSize);

  








 

  arm_status arm_fir_init_q15(
  arm_fir_instance_q15 * S,
  uint16_t numTaps,
  q15_t * pCoeffs,
  q15_t * pState,
  uint32_t blockSize);

  






 
  void arm_fir_q31(
  const arm_fir_instance_q31 * S,
  q31_t * pSrc,
  q31_t * pDst,
  uint32_t blockSize);

  






 
  void arm_fir_fast_q31(
  const arm_fir_instance_q31 * S,
  q31_t * pSrc,
  q31_t * pDst,
  uint32_t blockSize);

  







 
  void arm_fir_init_q31(
  arm_fir_instance_q31 * S,
  uint16_t numTaps,
  q31_t * pCoeffs,
  q31_t * pState,
  uint32_t blockSize);

  






 
  void arm_fir_f32(
  const arm_fir_instance_f32 * S,
  float32_t * pSrc,
  float32_t * pDst,
  uint32_t blockSize);

  







 
  void arm_fir_init_f32(
  arm_fir_instance_f32 * S,
  uint16_t numTaps,
  float32_t * pCoeffs,
  float32_t * pState,
  uint32_t blockSize);


  

 
  typedef struct
  {
    int8_t numStages;          
    q15_t *pState;             
    q15_t *pCoeffs;            
    int8_t postShift;          

  } arm_biquad_casd_df1_inst_q15;


  

 
  typedef struct
  {
    uint32_t numStages;       
    q31_t *pState;            
    q31_t *pCoeffs;           
    uint8_t postShift;        

  } arm_biquad_casd_df1_inst_q31;

  

 
  typedef struct
  {
    uint32_t numStages;          
    float32_t *pState;           
    float32_t *pCoeffs;          


  } arm_biquad_casd_df1_inst_f32;



  






 

  void arm_biquad_cascade_df1_q15(
  const arm_biquad_casd_df1_inst_q15 * S,
  q15_t * pSrc,
  q15_t * pDst,
  uint32_t blockSize);

  







 

  void arm_biquad_cascade_df1_init_q15(
  arm_biquad_casd_df1_inst_q15 * S,
  uint8_t numStages,
  q15_t * pCoeffs,
  q15_t * pState,
  int8_t postShift);


  






 

  void arm_biquad_cascade_df1_fast_q15(
  const arm_biquad_casd_df1_inst_q15 * S,
  q15_t * pSrc,
  q15_t * pDst,
  uint32_t blockSize);


  






 

  void arm_biquad_cascade_df1_q31(
  const arm_biquad_casd_df1_inst_q31 * S,
  q31_t * pSrc,
  q31_t * pDst,
  uint32_t blockSize);

  






 

  void arm_biquad_cascade_df1_fast_q31(
  const arm_biquad_casd_df1_inst_q31 * S,
  q31_t * pSrc,
  q31_t * pDst,
  uint32_t blockSize);

  







 

  void arm_biquad_cascade_df1_init_q31(
  arm_biquad_casd_df1_inst_q31 * S,
  uint8_t numStages,
  q31_t * pCoeffs,
  q31_t * pState,
  int8_t postShift);

  






 

  void arm_biquad_cascade_df1_f32(
  const arm_biquad_casd_df1_inst_f32 * S,
  float32_t * pSrc,
  float32_t * pDst,
  uint32_t blockSize);

  






 

  void arm_biquad_cascade_df1_init_f32(
  arm_biquad_casd_df1_inst_f32 * S,
  uint8_t numStages,
  float32_t * pCoeffs,
  float32_t * pState);


  

 

  typedef struct
  {
    uint16_t numRows;      
    uint16_t numCols;      
    float32_t *pData;      
  } arm_matrix_instance_f32;

  

 

  typedef struct
  {
    uint16_t numRows;      
    uint16_t numCols;      
    q15_t *pData;          

  } arm_matrix_instance_q15;

  

 

  typedef struct
  {
    uint16_t numRows;      
    uint16_t numCols;      
    q31_t *pData;          

  } arm_matrix_instance_q31;



  






 

  arm_status arm_mat_add_f32(
  const arm_matrix_instance_f32 * pSrcA,
  const arm_matrix_instance_f32 * pSrcB,
  arm_matrix_instance_f32 * pDst);

  






 

  arm_status arm_mat_add_q15(
  const arm_matrix_instance_q15 * pSrcA,
  const arm_matrix_instance_q15 * pSrcB,
  arm_matrix_instance_q15 * pDst);

  






 

  arm_status arm_mat_add_q31(
  const arm_matrix_instance_q31 * pSrcA,
  const arm_matrix_instance_q31 * pSrcB,
  arm_matrix_instance_q31 * pDst);

  






 

  arm_status arm_mat_cmplx_mult_f32(
  const arm_matrix_instance_f32 * pSrcA,
  const arm_matrix_instance_f32 * pSrcB,
  arm_matrix_instance_f32 * pDst);

  






 

  arm_status arm_mat_cmplx_mult_q15(
  const arm_matrix_instance_q15 * pSrcA,
  const arm_matrix_instance_q15 * pSrcB,
  arm_matrix_instance_q15 * pDst,
  q15_t * pScratch);

  






 

  arm_status arm_mat_cmplx_mult_q31(
  const arm_matrix_instance_q31 * pSrcA,
  const arm_matrix_instance_q31 * pSrcB,
  arm_matrix_instance_q31 * pDst);


  





 

  arm_status arm_mat_trans_f32(
  const arm_matrix_instance_f32 * pSrc,
  arm_matrix_instance_f32 * pDst);


  





 

  arm_status arm_mat_trans_q15(
  const arm_matrix_instance_q15 * pSrc,
  arm_matrix_instance_q15 * pDst);

  





 

  arm_status arm_mat_trans_q31(
  const arm_matrix_instance_q31 * pSrc,
  arm_matrix_instance_q31 * pDst);


  






 

  arm_status arm_mat_mult_f32(
  const arm_matrix_instance_f32 * pSrcA,
  const arm_matrix_instance_f32 * pSrcB,
  arm_matrix_instance_f32 * pDst);

  







 

  arm_status arm_mat_mult_q15(
  const arm_matrix_instance_q15 * pSrcA,
  const arm_matrix_instance_q15 * pSrcB,
  arm_matrix_instance_q15 * pDst,
  q15_t * pState);

  







 

  arm_status arm_mat_mult_fast_q15(
  const arm_matrix_instance_q15 * pSrcA,
  const arm_matrix_instance_q15 * pSrcB,
  arm_matrix_instance_q15 * pDst,
  q15_t * pState);

  






 

  arm_status arm_mat_mult_q31(
  const arm_matrix_instance_q31 * pSrcA,
  const arm_matrix_instance_q31 * pSrcB,
  arm_matrix_instance_q31 * pDst);

  






 

  arm_status arm_mat_mult_fast_q31(
  const arm_matrix_instance_q31 * pSrcA,
  const arm_matrix_instance_q31 * pSrcB,
  arm_matrix_instance_q31 * pDst);


  






 

  arm_status arm_mat_sub_f32(
  const arm_matrix_instance_f32 * pSrcA,
  const arm_matrix_instance_f32 * pSrcB,
  arm_matrix_instance_f32 * pDst);

  






 

  arm_status arm_mat_sub_q15(
  const arm_matrix_instance_q15 * pSrcA,
  const arm_matrix_instance_q15 * pSrcB,
  arm_matrix_instance_q15 * pDst);

  






 

  arm_status arm_mat_sub_q31(
  const arm_matrix_instance_q31 * pSrcA,
  const arm_matrix_instance_q31 * pSrcB,
  arm_matrix_instance_q31 * pDst);

  






 

  arm_status arm_mat_scale_f32(
  const arm_matrix_instance_f32 * pSrc,
  float32_t scale,
  arm_matrix_instance_f32 * pDst);

  







 

  arm_status arm_mat_scale_q15(
  const arm_matrix_instance_q15 * pSrc,
  q15_t scaleFract,
  int32_t shift,
  arm_matrix_instance_q15 * pDst);

  







 

  arm_status arm_mat_scale_q31(
  const arm_matrix_instance_q31 * pSrc,
  q31_t scaleFract,
  int32_t shift,
  arm_matrix_instance_q31 * pDst);


  






 

  void arm_mat_init_q31(
  arm_matrix_instance_q31 * S,
  uint16_t nRows,
  uint16_t nColumns,
  q31_t * pData);

  






 

  void arm_mat_init_q15(
  arm_matrix_instance_q15 * S,
  uint16_t nRows,
  uint16_t nColumns,
  q15_t * pData);

  






 

  void arm_mat_init_f32(
  arm_matrix_instance_f32 * S,
  uint16_t nRows,
  uint16_t nColumns,
  float32_t * pData);



  

 
  typedef struct
  {
    q15_t A0;     




    q31_t A1;            

    q15_t state[3];        
    q15_t Kp;            
    q15_t Ki;            
    q15_t Kd;            
  } arm_pid_instance_q15;

  

 
  typedef struct
  {
    q31_t A0;             
    q31_t A1;             
    q31_t A2;             
    q31_t state[3];       
    q31_t Kp;             
    q31_t Ki;             
    q31_t Kd;             

  } arm_pid_instance_q31;

  

 
  typedef struct
  {
    float32_t A0;           
    float32_t A1;           
    float32_t A2;           
    float32_t state[3];     
    float32_t Kp;                
    float32_t Ki;                
    float32_t Kd;                
  } arm_pid_instance_f32;



  




 
  void arm_pid_init_f32(
  arm_pid_instance_f32 * S,
  int32_t resetStateFlag);

  



 
  void arm_pid_reset_f32(
  arm_pid_instance_f32 * S);


  




 
  void arm_pid_init_q31(
  arm_pid_instance_q31 * S,
  int32_t resetStateFlag);


  



 

  void arm_pid_reset_q31(
  arm_pid_instance_q31 * S);

  




 
  void arm_pid_init_q15(
  arm_pid_instance_q15 * S,
  int32_t resetStateFlag);

  



 
  void arm_pid_reset_q15(
  arm_pid_instance_q15 * S);


  

 
  typedef struct
  {
    uint32_t nValues;            
    float32_t x1;                
    float32_t xSpacing;          
    float32_t *pYData;           
  } arm_linear_interp_instance_f32;

  

 

  typedef struct
  {
    uint16_t numRows;    
    uint16_t numCols;    
    float32_t *pData;    
  } arm_bilinear_interp_instance_f32;

   

 

  typedef struct
  {
    uint16_t numRows;    
    uint16_t numCols;    
    q31_t *pData;        
  } arm_bilinear_interp_instance_q31;

   

 

  typedef struct
  {
    uint16_t numRows;    
    uint16_t numCols;    
    q15_t *pData;        
  } arm_bilinear_interp_instance_q15;

   

 

  typedef struct
  {
    uint16_t numRows;    
    uint16_t numCols;    
    q7_t *pData;                 
  } arm_bilinear_interp_instance_q7;


  






 

  void arm_mult_q7(
  q7_t * pSrcA,
  q7_t * pSrcB,
  q7_t * pDst,
  uint32_t blockSize);

  






 

  void arm_mult_q15(
  q15_t * pSrcA,
  q15_t * pSrcB,
  q15_t * pDst,
  uint32_t blockSize);

  






 

  void arm_mult_q31(
  q31_t * pSrcA,
  q31_t * pSrcB,
  q31_t * pDst,
  uint32_t blockSize);

  






 

  void arm_mult_f32(
  float32_t * pSrcA,
  float32_t * pSrcB,
  float32_t * pDst,
  uint32_t blockSize);






  

 

  typedef struct
  {
    uint16_t fftLen;                  
    uint8_t ifftFlag;                 
    uint8_t bitReverseFlag;           
    q15_t *pTwiddle;                      
    uint16_t *pBitRevTable;           
    uint16_t twidCoefModifier;        
    uint16_t bitRevFactor;            
  } arm_cfft_radix2_instance_q15;

  arm_status arm_cfft_radix2_init_q15(
  arm_cfft_radix2_instance_q15 * S,
  uint16_t fftLen,
  uint8_t ifftFlag,
  uint8_t bitReverseFlag);

  void arm_cfft_radix2_q15(
  const arm_cfft_radix2_instance_q15 * S,
  q15_t * pSrc);



  

 

  typedef struct
  {
    uint16_t fftLen;                  
    uint8_t ifftFlag;                 
    uint8_t bitReverseFlag;           
    q15_t *pTwiddle;                  
    uint16_t *pBitRevTable;           
    uint16_t twidCoefModifier;        
    uint16_t bitRevFactor;            
  } arm_cfft_radix4_instance_q15;

  arm_status arm_cfft_radix4_init_q15(
  arm_cfft_radix4_instance_q15 * S,
  uint16_t fftLen,
  uint8_t ifftFlag,
  uint8_t bitReverseFlag);

  void arm_cfft_radix4_q15(
  const arm_cfft_radix4_instance_q15 * S,
  q15_t * pSrc);

  

 

  typedef struct
  {
    uint16_t fftLen;                  
    uint8_t ifftFlag;                 
    uint8_t bitReverseFlag;           
    q31_t *pTwiddle;                      
    uint16_t *pBitRevTable;           
    uint16_t twidCoefModifier;        
    uint16_t bitRevFactor;            
  } arm_cfft_radix2_instance_q31;

  arm_status arm_cfft_radix2_init_q31(
  arm_cfft_radix2_instance_q31 * S,
  uint16_t fftLen,
  uint8_t ifftFlag,
  uint8_t bitReverseFlag);

  void arm_cfft_radix2_q31(
  const arm_cfft_radix2_instance_q31 * S,
  q31_t * pSrc);

  

 

  typedef struct
  {
    uint16_t fftLen;                  
    uint8_t ifftFlag;                 
    uint8_t bitReverseFlag;           
    q31_t *pTwiddle;                  
    uint16_t *pBitRevTable;           
    uint16_t twidCoefModifier;        
    uint16_t bitRevFactor;            
  } arm_cfft_radix4_instance_q31;

  void arm_cfft_radix4_q31(
  const arm_cfft_radix4_instance_q31 * S,
  q31_t * pSrc);

  arm_status arm_cfft_radix4_init_q31(
  arm_cfft_radix4_instance_q31 * S,
  uint16_t fftLen,
  uint8_t ifftFlag,
  uint8_t bitReverseFlag);

  

 

  typedef struct
  {
    uint16_t fftLen;                    
    uint8_t ifftFlag;                   
    uint8_t bitReverseFlag;             
    float32_t *pTwiddle;                
    uint16_t *pBitRevTable;             
    uint16_t twidCoefModifier;          
    uint16_t bitRevFactor;              
    float32_t onebyfftLen;                  
  } arm_cfft_radix2_instance_f32;

 
  arm_status arm_cfft_radix2_init_f32(
  arm_cfft_radix2_instance_f32 * S,
  uint16_t fftLen,
  uint8_t ifftFlag,
  uint8_t bitReverseFlag);

 
  void arm_cfft_radix2_f32(
  const arm_cfft_radix2_instance_f32 * S,
  float32_t * pSrc);

  

 

  typedef struct
  {
    uint16_t fftLen;                    
    uint8_t ifftFlag;                   
    uint8_t bitReverseFlag;             
    float32_t *pTwiddle;                
    uint16_t *pBitRevTable;             
    uint16_t twidCoefModifier;          
    uint16_t bitRevFactor;              
    float32_t onebyfftLen;                  
  } arm_cfft_radix4_instance_f32;

 
  arm_status arm_cfft_radix4_init_f32(
  arm_cfft_radix4_instance_f32 * S,
  uint16_t fftLen,
  uint8_t ifftFlag,
  uint8_t bitReverseFlag);

 
  void arm_cfft_radix4_f32(
  const arm_cfft_radix4_instance_f32 * S,
  float32_t * pSrc);

  

 

  typedef struct
  {
    uint16_t fftLen;                    
    const float32_t *pTwiddle;          
    const uint16_t *pBitRevTable;       
    uint16_t bitRevLength;              
  } arm_cfft_instance_f32;

  void arm_cfft_f32(
  const arm_cfft_instance_f32 * S,
  float32_t * p1,
  uint8_t ifftFlag,
  uint8_t bitReverseFlag);

  

 

  typedef struct
  {
    uint32_t fftLenReal;                       
    uint32_t fftLenBy2;                        
    uint8_t ifftFlagR;                         
    uint8_t bitReverseFlagR;                       
    uint32_t twidCoefRModifier;                
    q15_t *pTwiddleAReal;                      
    q15_t *pTwiddleBReal;                      
    arm_cfft_radix4_instance_q15 *pCfft;           
  } arm_rfft_instance_q15;

  arm_status arm_rfft_init_q15(
  arm_rfft_instance_q15 * S,
  arm_cfft_radix4_instance_q15 * S_CFFT,
  uint32_t fftLenReal,
  uint32_t ifftFlagR,
  uint32_t bitReverseFlag);

  void arm_rfft_q15(
  const arm_rfft_instance_q15 * S,
  q15_t * pSrc,
  q15_t * pDst);

  

 

  typedef struct
  {
    uint32_t fftLenReal;                         
    uint32_t fftLenBy2;                          
    uint8_t ifftFlagR;                           
    uint8_t bitReverseFlagR;                         
    uint32_t twidCoefRModifier;                  
    q31_t *pTwiddleAReal;                        
    q31_t *pTwiddleBReal;                        
    arm_cfft_radix4_instance_q31 *pCfft;         
  } arm_rfft_instance_q31;

  arm_status arm_rfft_init_q31(
  arm_rfft_instance_q31 * S,
  arm_cfft_radix4_instance_q31 * S_CFFT,
  uint32_t fftLenReal,
  uint32_t ifftFlagR,
  uint32_t bitReverseFlag);

  void arm_rfft_q31(
  const arm_rfft_instance_q31 * S,
  q31_t * pSrc,
  q31_t * pDst);

  

 

  typedef struct
  {
    uint32_t fftLenReal;                         
    uint16_t fftLenBy2;                          
    uint8_t ifftFlagR;                           
    uint8_t bitReverseFlagR;                     
    uint32_t twidCoefRModifier;                      
    float32_t *pTwiddleAReal;                    
    float32_t *pTwiddleBReal;                    
    arm_cfft_radix4_instance_f32 *pCfft;         
  } arm_rfft_instance_f32;

  arm_status arm_rfft_init_f32(
  arm_rfft_instance_f32 * S,
  arm_cfft_radix4_instance_f32 * S_CFFT,
  uint32_t fftLenReal,
  uint32_t ifftFlagR,
  uint32_t bitReverseFlag);

  void arm_rfft_f32(
  const arm_rfft_instance_f32 * S,
  float32_t * pSrc,
  float32_t * pDst);

  

 

typedef struct
  {
    arm_cfft_instance_f32 Sint;       
    uint16_t fftLenRFFT;                         
	float32_t * pTwiddleRFFT;					 
  } arm_rfft_fast_instance_f32 ;

arm_status arm_rfft_fast_init_f32 (
	arm_rfft_fast_instance_f32 * S,
	uint16_t fftLen);

void arm_rfft_fast_f32(
  arm_rfft_fast_instance_f32 * S,
  float32_t * p, float32_t * pOut,
  uint8_t ifftFlag);

  

 

  typedef struct
  {
    uint16_t N;                          
    uint16_t Nby2;                       
    float32_t normalize;                 
    float32_t *pTwiddle;                 
    float32_t *pCosFactor;               
    arm_rfft_instance_f32 *pRfft;         
    arm_cfft_radix4_instance_f32 *pCfft;  
  } arm_dct4_instance_f32;

  








 

  arm_status arm_dct4_init_f32(
  arm_dct4_instance_f32 * S,
  arm_rfft_instance_f32 * S_RFFT,
  arm_cfft_radix4_instance_f32 * S_CFFT,
  uint16_t N,
  uint16_t Nby2,
  float32_t normalize);

  





 

  void arm_dct4_f32(
  const arm_dct4_instance_f32 * S,
  float32_t * pState,
  float32_t * pInlineBuffer);

  

 

  typedef struct
  {
    uint16_t N;                          
    uint16_t Nby2;                       
    q31_t normalize;                     
    q31_t *pTwiddle;                     
    q31_t *pCosFactor;                   
    arm_rfft_instance_q31 *pRfft;         
    arm_cfft_radix4_instance_q31 *pCfft;  
  } arm_dct4_instance_q31;

  








 

  arm_status arm_dct4_init_q31(
  arm_dct4_instance_q31 * S,
  arm_rfft_instance_q31 * S_RFFT,
  arm_cfft_radix4_instance_q31 * S_CFFT,
  uint16_t N,
  uint16_t Nby2,
  q31_t normalize);

  





 

  void arm_dct4_q31(
  const arm_dct4_instance_q31 * S,
  q31_t * pState,
  q31_t * pInlineBuffer);

  

 

  typedef struct
  {
    uint16_t N;                          
    uint16_t Nby2;                       
    q15_t normalize;                     
    q15_t *pTwiddle;                     
    q15_t *pCosFactor;                   
    arm_rfft_instance_q15 *pRfft;         
    arm_cfft_radix4_instance_q15 *pCfft;  
  } arm_dct4_instance_q15;

  








 

  arm_status arm_dct4_init_q15(
  arm_dct4_instance_q15 * S,
  arm_rfft_instance_q15 * S_RFFT,
  arm_cfft_radix4_instance_q15 * S_CFFT,
  uint16_t N,
  uint16_t Nby2,
  q15_t normalize);

  





 

  void arm_dct4_q15(
  const arm_dct4_instance_q15 * S,
  q15_t * pState,
  q15_t * pInlineBuffer);

  






 

  void arm_add_f32(
  float32_t * pSrcA,
  float32_t * pSrcB,
  float32_t * pDst,
  uint32_t blockSize);

  






 

  void arm_add_q7(
  q7_t * pSrcA,
  q7_t * pSrcB,
  q7_t * pDst,
  uint32_t blockSize);

  






 

  void arm_add_q15(
  q15_t * pSrcA,
  q15_t * pSrcB,
  q15_t * pDst,
  uint32_t blockSize);

  






 

  void arm_add_q31(
  q31_t * pSrcA,
  q31_t * pSrcB,
  q31_t * pDst,
  uint32_t blockSize);

  






 

  void arm_sub_f32(
  float32_t * pSrcA,
  float32_t * pSrcB,
  float32_t * pDst,
  uint32_t blockSize);

  






 

  void arm_sub_q7(
  q7_t * pSrcA,
  q7_t * pSrcB,
  q7_t * pDst,
  uint32_t blockSize);

  






 

  void arm_sub_q15(
  q15_t * pSrcA,
  q15_t * pSrcB,
  q15_t * pDst,
  uint32_t blockSize);

  






 

  void arm_sub_q31(
  q31_t * pSrcA,
  q31_t * pSrcB,
  q31_t * pDst,
  uint32_t blockSize);

  






 

  void arm_scale_f32(
  float32_t * pSrc,
  float32_t scale,
  float32_t * pDst,
  uint32_t blockSize);

  







 

  void arm_scale_q7(
  q7_t * pSrc,
  q7_t scaleFract,
  int8_t shift,
  q7_t * pDst,
  uint32_t blockSize);

  







 

  void arm_scale_q15(
  q15_t * pSrc,
  q15_t scaleFract,
  int8_t shift,
  q15_t * pDst,
  uint32_t blockSize);

  







 

  void arm_scale_q31(
  q31_t * pSrc,
  q31_t scaleFract,
  int8_t shift,
  q31_t * pDst,
  uint32_t blockSize);

  





 

  void arm_abs_q7(
  q7_t * pSrc,
  q7_t * pDst,
  uint32_t blockSize);

  





 

  void arm_abs_f32(
  float32_t * pSrc,
  float32_t * pDst,
  uint32_t blockSize);

  





 

  void arm_abs_q15(
  q15_t * pSrc,
  q15_t * pDst,
  uint32_t blockSize);

  





 

  void arm_abs_q31(
  q31_t * pSrc,
  q31_t * pDst,
  uint32_t blockSize);

  






 

  void arm_dot_prod_f32(
  float32_t * pSrcA,
  float32_t * pSrcB,
  uint32_t blockSize,
  float32_t * result);

  






 

  void arm_dot_prod_q7(
  q7_t * pSrcA,
  q7_t * pSrcB,
  uint32_t blockSize,
  q31_t * result);

  






 

  void arm_dot_prod_q15(
  q15_t * pSrcA,
  q15_t * pSrcB,
  uint32_t blockSize,
  q63_t * result);

  






 

  void arm_dot_prod_q31(
  q31_t * pSrcA,
  q31_t * pSrcB,
  uint32_t blockSize,
  q63_t * result);

  






 

  void arm_shift_q7(
  q7_t * pSrc,
  int8_t shiftBits,
  q7_t * pDst,
  uint32_t blockSize);

  






 

  void arm_shift_q15(
  q15_t * pSrc,
  int8_t shiftBits,
  q15_t * pDst,
  uint32_t blockSize);

  






 

  void arm_shift_q31(
  q31_t * pSrc,
  int8_t shiftBits,
  q31_t * pDst,
  uint32_t blockSize);

  






 

  void arm_offset_f32(
  float32_t * pSrc,
  float32_t offset,
  float32_t * pDst,
  uint32_t blockSize);

  






 

  void arm_offset_q7(
  q7_t * pSrc,
  q7_t offset,
  q7_t * pDst,
  uint32_t blockSize);

  






 

  void arm_offset_q15(
  q15_t * pSrc,
  q15_t offset,
  q15_t * pDst,
  uint32_t blockSize);

  






 

  void arm_offset_q31(
  q31_t * pSrc,
  q31_t offset,
  q31_t * pDst,
  uint32_t blockSize);

  





 

  void arm_negate_f32(
  float32_t * pSrc,
  float32_t * pDst,
  uint32_t blockSize);

  





 

  void arm_negate_q7(
  q7_t * pSrc,
  q7_t * pDst,
  uint32_t blockSize);

  





 

  void arm_negate_q15(
  q15_t * pSrc,
  q15_t * pDst,
  uint32_t blockSize);

  





 

  void arm_negate_q31(
  q31_t * pSrc,
  q31_t * pDst,
  uint32_t blockSize);
  





 
  void arm_copy_f32(
  float32_t * pSrc,
  float32_t * pDst,
  uint32_t blockSize);

  





 
  void arm_copy_q7(
  q7_t * pSrc,
  q7_t * pDst,
  uint32_t blockSize);

  





 
  void arm_copy_q15(
  q15_t * pSrc,
  q15_t * pDst,
  uint32_t blockSize);

  





 
  void arm_copy_q31(
  q31_t * pSrc,
  q31_t * pDst,
  uint32_t blockSize);
  





 
  void arm_fill_f32(
  float32_t value,
  float32_t * pDst,
  uint32_t blockSize);

  





 
  void arm_fill_q7(
  q7_t value,
  q7_t * pDst,
  uint32_t blockSize);

  





 
  void arm_fill_q15(
  q15_t value,
  q15_t * pDst,
  uint32_t blockSize);

  





 
  void arm_fill_q31(
  q31_t value,
  q31_t * pDst,
  uint32_t blockSize);









 

  void arm_conv_f32(
  float32_t * pSrcA,
  uint32_t srcALen,
  float32_t * pSrcB,
  uint32_t srcBLen,
  float32_t * pDst);


  









 


  void arm_conv_opt_q15(
  q15_t * pSrcA,
  uint32_t srcALen,
  q15_t * pSrcB,
  uint32_t srcBLen,
  q15_t * pDst,
  q15_t * pScratch1,
  q15_t * pScratch2);










 

  void arm_conv_q15(
  q15_t * pSrcA,
  uint32_t srcALen,
  q15_t * pSrcB,
  uint32_t srcBLen,
  q15_t * pDst);

  







 

  void arm_conv_fast_q15(
			  q15_t * pSrcA,
			 uint32_t srcALen,
			  q15_t * pSrcB,
			 uint32_t srcBLen,
			 q15_t * pDst);

  









 

  void arm_conv_fast_opt_q15(
  q15_t * pSrcA,
  uint32_t srcALen,
  q15_t * pSrcB,
  uint32_t srcBLen,
  q15_t * pDst,
  q15_t * pScratch1,
  q15_t * pScratch2);



  







 

  void arm_conv_q31(
  q31_t * pSrcA,
  uint32_t srcALen,
  q31_t * pSrcB,
  uint32_t srcBLen,
  q31_t * pDst);

  







 

  void arm_conv_fast_q31(
  q31_t * pSrcA,
  uint32_t srcALen,
  q31_t * pSrcB,
  uint32_t srcBLen,
  q31_t * pDst);


    









 

  void arm_conv_opt_q7(
  q7_t * pSrcA,
  uint32_t srcALen,
  q7_t * pSrcB,
  uint32_t srcBLen,
  q7_t * pDst,
  q15_t * pScratch1,
  q15_t * pScratch2);



  







 

  void arm_conv_q7(
  q7_t * pSrcA,
  uint32_t srcALen,
  q7_t * pSrcB,
  uint32_t srcBLen,
  q7_t * pDst);


  









 

  arm_status arm_conv_partial_f32(
  float32_t * pSrcA,
  uint32_t srcALen,
  float32_t * pSrcB,
  uint32_t srcBLen,
  float32_t * pDst,
  uint32_t firstIndex,
  uint32_t numPoints);

    











 

  arm_status arm_conv_partial_opt_q15(
  q15_t * pSrcA,
  uint32_t srcALen,
  q15_t * pSrcB,
  uint32_t srcBLen,
  q15_t * pDst,
  uint32_t firstIndex,
  uint32_t numPoints,
  q15_t * pScratch1,
  q15_t * pScratch2);












 

  arm_status arm_conv_partial_q15(
  q15_t * pSrcA,
  uint32_t srcALen,
  q15_t * pSrcB,
  uint32_t srcBLen,
  q15_t * pDst,
  uint32_t firstIndex,
  uint32_t numPoints);

  









 

  arm_status arm_conv_partial_fast_q15(
				        q15_t * pSrcA,
				       uint32_t srcALen,
				        q15_t * pSrcB,
				       uint32_t srcBLen,
				       q15_t * pDst,
				       uint32_t firstIndex,
				       uint32_t numPoints);


  











 

  arm_status arm_conv_partial_fast_opt_q15(
  q15_t * pSrcA,
  uint32_t srcALen,
  q15_t * pSrcB,
  uint32_t srcBLen,
  q15_t * pDst,
  uint32_t firstIndex,
  uint32_t numPoints,
  q15_t * pScratch1,
  q15_t * pScratch2);


  









 

  arm_status arm_conv_partial_q31(
  q31_t * pSrcA,
  uint32_t srcALen,
  q31_t * pSrcB,
  uint32_t srcBLen,
  q31_t * pDst,
  uint32_t firstIndex,
  uint32_t numPoints);


  









 

  arm_status arm_conv_partial_fast_q31(
  q31_t * pSrcA,
  uint32_t srcALen,
  q31_t * pSrcB,
  uint32_t srcBLen,
  q31_t * pDst,
  uint32_t firstIndex,
  uint32_t numPoints);


  











 

  arm_status arm_conv_partial_opt_q7(
  q7_t * pSrcA,
  uint32_t srcALen,
  q7_t * pSrcB,
  uint32_t srcBLen,
  q7_t * pDst,
  uint32_t firstIndex,
  uint32_t numPoints,
  q15_t * pScratch1,
  q15_t * pScratch2);












 

  arm_status arm_conv_partial_q7(
  q7_t * pSrcA,
  uint32_t srcALen,
  q7_t * pSrcB,
  uint32_t srcBLen,
  q7_t * pDst,
  uint32_t firstIndex,
  uint32_t numPoints);



  

 

  typedef struct
  {
    uint8_t M;                       
    uint16_t numTaps;                
    q15_t *pCoeffs;                   
    q15_t *pState;                    
  } arm_fir_decimate_instance_q15;

  

 

  typedef struct
  {
    uint8_t M;                   
    uint16_t numTaps;            
    q31_t *pCoeffs;               
    q31_t *pState;                

  } arm_fir_decimate_instance_q31;

  

 

  typedef struct
  {
    uint8_t M;                           
    uint16_t numTaps;                    
    float32_t *pCoeffs;                   
    float32_t *pState;                    

  } arm_fir_decimate_instance_f32;



  






 

  void arm_fir_decimate_f32(
  const arm_fir_decimate_instance_f32 * S,
  float32_t * pSrc,
  float32_t * pDst,
  uint32_t blockSize);


  









 

  arm_status arm_fir_decimate_init_f32(
  arm_fir_decimate_instance_f32 * S,
  uint16_t numTaps,
  uint8_t M,
  float32_t * pCoeffs,
  float32_t * pState,
  uint32_t blockSize);

  






 

  void arm_fir_decimate_q15(
  const arm_fir_decimate_instance_q15 * S,
  q15_t * pSrc,
  q15_t * pDst,
  uint32_t blockSize);

  






 

  void arm_fir_decimate_fast_q15(
  const arm_fir_decimate_instance_q15 * S,
  q15_t * pSrc,
  q15_t * pDst,
  uint32_t blockSize);



  









 

  arm_status arm_fir_decimate_init_q15(
  arm_fir_decimate_instance_q15 * S,
  uint16_t numTaps,
  uint8_t M,
  q15_t * pCoeffs,
  q15_t * pState,
  uint32_t blockSize);

  






 

  void arm_fir_decimate_q31(
  const arm_fir_decimate_instance_q31 * S,
  q31_t * pSrc,
  q31_t * pDst,
  uint32_t blockSize);

  






 

  void arm_fir_decimate_fast_q31(
  arm_fir_decimate_instance_q31 * S,
  q31_t * pSrc,
  q31_t * pDst,
  uint32_t blockSize);


  









 

  arm_status arm_fir_decimate_init_q31(
  arm_fir_decimate_instance_q31 * S,
  uint16_t numTaps,
  uint8_t M,
  q31_t * pCoeffs,
  q31_t * pState,
  uint32_t blockSize);



  

 

  typedef struct
  {
    uint8_t L;                       
    uint16_t phaseLength;            
    q15_t *pCoeffs;                  
    q15_t *pState;                   
  } arm_fir_interpolate_instance_q15;

  

 

  typedef struct
  {
    uint8_t L;                       
    uint16_t phaseLength;            
    q31_t *pCoeffs;                   
    q31_t *pState;                    
  } arm_fir_interpolate_instance_q31;

  

 

  typedef struct
  {
    uint8_t L;                      
    uint16_t phaseLength;           
    float32_t *pCoeffs;              
    float32_t *pState;               
  } arm_fir_interpolate_instance_f32;


  






 

  void arm_fir_interpolate_q15(
  const arm_fir_interpolate_instance_q15 * S,
  q15_t * pSrc,
  q15_t * pDst,
  uint32_t blockSize);


  









 

  arm_status arm_fir_interpolate_init_q15(
  arm_fir_interpolate_instance_q15 * S,
  uint8_t L,
  uint16_t numTaps,
  q15_t * pCoeffs,
  q15_t * pState,
  uint32_t blockSize);

  






 

  void arm_fir_interpolate_q31(
  const arm_fir_interpolate_instance_q31 * S,
  q31_t * pSrc,
  q31_t * pDst,
  uint32_t blockSize);

  









 

  arm_status arm_fir_interpolate_init_q31(
  arm_fir_interpolate_instance_q31 * S,
  uint8_t L,
  uint16_t numTaps,
  q31_t * pCoeffs,
  q31_t * pState,
  uint32_t blockSize);


  






 

  void arm_fir_interpolate_f32(
  const arm_fir_interpolate_instance_f32 * S,
  float32_t * pSrc,
  float32_t * pDst,
  uint32_t blockSize);

  









 

  arm_status arm_fir_interpolate_init_f32(
  arm_fir_interpolate_instance_f32 * S,
  uint8_t L,
  uint16_t numTaps,
  float32_t * pCoeffs,
  float32_t * pState,
  uint32_t blockSize);

  

 

  typedef struct
  {
    uint8_t numStages;        
    q63_t *pState;            
    q31_t *pCoeffs;           
    uint8_t postShift;        

  } arm_biquad_cas_df1_32x64_ins_q31;


  





 

  void arm_biquad_cas_df1_32x64_q31(
  const arm_biquad_cas_df1_32x64_ins_q31 * S,
  q31_t * pSrc,
  q31_t * pDst,
  uint32_t blockSize);


  






 

  void arm_biquad_cas_df1_32x64_init_q31(
  arm_biquad_cas_df1_32x64_ins_q31 * S,
  uint8_t numStages,
  q31_t * pCoeffs,
  q63_t * pState,
  uint8_t postShift);



  

 

  typedef struct
  {
    uint8_t numStages;          
    float32_t *pState;          
    float32_t *pCoeffs;         
  } arm_biquad_cascade_df2T_instance_f32;


  






 

  void arm_biquad_cascade_df2T_f32(
  const arm_biquad_cascade_df2T_instance_f32 * S,
  float32_t * pSrc,
  float32_t * pDst,
  uint32_t blockSize);


  






 

  void arm_biquad_cascade_df2T_init_f32(
  arm_biquad_cascade_df2T_instance_f32 * S,
  uint8_t numStages,
  float32_t * pCoeffs,
  float32_t * pState);



  

 

  typedef struct
  {
    uint16_t numStages;                           
    q15_t *pState;                                
    q15_t *pCoeffs;                               
  } arm_fir_lattice_instance_q15;

  

 

  typedef struct
  {
    uint16_t numStages;                           
    q31_t *pState;                                
    q31_t *pCoeffs;                               
  } arm_fir_lattice_instance_q31;

  

 

  typedef struct
  {
    uint16_t numStages;                   
    float32_t *pState;                    
    float32_t *pCoeffs;                   
  } arm_fir_lattice_instance_f32;

  






 

  void arm_fir_lattice_init_q15(
  arm_fir_lattice_instance_q15 * S,
  uint16_t numStages,
  q15_t * pCoeffs,
  q15_t * pState);


  






 
  void arm_fir_lattice_q15(
  const arm_fir_lattice_instance_q15 * S,
  q15_t * pSrc,
  q15_t * pDst,
  uint32_t blockSize);

  






 

  void arm_fir_lattice_init_q31(
  arm_fir_lattice_instance_q31 * S,
  uint16_t numStages,
  q31_t * pCoeffs,
  q31_t * pState);


  






 

  void arm_fir_lattice_q31(
  const arm_fir_lattice_instance_q31 * S,
  q31_t * pSrc,
  q31_t * pDst,
  uint32_t blockSize);








 

  void arm_fir_lattice_init_f32(
  arm_fir_lattice_instance_f32 * S,
  uint16_t numStages,
  float32_t * pCoeffs,
  float32_t * pState);

  






 

  void arm_fir_lattice_f32(
  const arm_fir_lattice_instance_f32 * S,
  float32_t * pSrc,
  float32_t * pDst,
  uint32_t blockSize);

  

 
  typedef struct
  {
    uint16_t numStages;                          
    q15_t *pState;                               
    q15_t *pkCoeffs;                             
    q15_t *pvCoeffs;                             
  } arm_iir_lattice_instance_q15;

  

 
  typedef struct
  {
    uint16_t numStages;                          
    q31_t *pState;                               
    q31_t *pkCoeffs;                             
    q31_t *pvCoeffs;                             
  } arm_iir_lattice_instance_q31;

  

 
  typedef struct
  {
    uint16_t numStages;                          
    float32_t *pState;                           
    float32_t *pkCoeffs;                         
    float32_t *pvCoeffs;                         
  } arm_iir_lattice_instance_f32;

  






 

  void arm_iir_lattice_f32(
  const arm_iir_lattice_instance_f32 * S,
  float32_t * pSrc,
  float32_t * pDst,
  uint32_t blockSize);

  








 

  void arm_iir_lattice_init_f32(
  arm_iir_lattice_instance_f32 * S,
  uint16_t numStages,
  float32_t * pkCoeffs,
  float32_t * pvCoeffs,
  float32_t * pState,
  uint32_t blockSize);


  






 

  void arm_iir_lattice_q31(
  const arm_iir_lattice_instance_q31 * S,
  q31_t * pSrc,
  q31_t * pDst,
  uint32_t blockSize);


  








 

  void arm_iir_lattice_init_q31(
  arm_iir_lattice_instance_q31 * S,
  uint16_t numStages,
  q31_t * pkCoeffs,
  q31_t * pvCoeffs,
  q31_t * pState,
  uint32_t blockSize);


  






 

  void arm_iir_lattice_q15(
  const arm_iir_lattice_instance_q15 * S,
  q15_t * pSrc,
  q15_t * pDst,
  uint32_t blockSize);











 

  void arm_iir_lattice_init_q15(
  arm_iir_lattice_instance_q15 * S,
  uint16_t numStages,
  q15_t * pkCoeffs,
  q15_t * pvCoeffs,
  q15_t * pState,
  uint32_t blockSize);

  

 

  typedef struct
  {
    uint16_t numTaps;     
    float32_t *pState;    
    float32_t *pCoeffs;   
    float32_t mu;         
  } arm_lms_instance_f32;

  








 

  void arm_lms_f32(
  const arm_lms_instance_f32 * S,
  float32_t * pSrc,
  float32_t * pRef,
  float32_t * pOut,
  float32_t * pErr,
  uint32_t blockSize);

  








 

  void arm_lms_init_f32(
  arm_lms_instance_f32 * S,
  uint16_t numTaps,
  float32_t * pCoeffs,
  float32_t * pState,
  float32_t mu,
  uint32_t blockSize);

  

 

  typedef struct
  {
    uint16_t numTaps;     
    q15_t *pState;        
    q15_t *pCoeffs;       
    q15_t mu;             
    uint32_t postShift;   
  } arm_lms_instance_q15;


  









 

  void arm_lms_init_q15(
  arm_lms_instance_q15 * S,
  uint16_t numTaps,
  q15_t * pCoeffs,
  q15_t * pState,
  q15_t mu,
  uint32_t blockSize,
  uint32_t postShift);

  








 

  void arm_lms_q15(
  const arm_lms_instance_q15 * S,
  q15_t * pSrc,
  q15_t * pRef,
  q15_t * pOut,
  q15_t * pErr,
  uint32_t blockSize);


  

 

  typedef struct
  {
    uint16_t numTaps;     
    q31_t *pState;        
    q31_t *pCoeffs;       
    q31_t mu;             
    uint32_t postShift;   

  } arm_lms_instance_q31;

  








 

  void arm_lms_q31(
  const arm_lms_instance_q31 * S,
  q31_t * pSrc,
  q31_t * pRef,
  q31_t * pOut,
  q31_t * pErr,
  uint32_t blockSize);

  









 

  void arm_lms_init_q31(
  arm_lms_instance_q31 * S,
  uint16_t numTaps,
  q31_t * pCoeffs,
  q31_t * pState,
  q31_t mu,
  uint32_t blockSize,
  uint32_t postShift);

  

 

  typedef struct
  {
    uint16_t numTaps;      
    float32_t *pState;     
    float32_t *pCoeffs;    
    float32_t mu;         
    float32_t energy;     
    float32_t x0;         
  } arm_lms_norm_instance_f32;

  








 

  void arm_lms_norm_f32(
  arm_lms_norm_instance_f32 * S,
  float32_t * pSrc,
  float32_t * pRef,
  float32_t * pOut,
  float32_t * pErr,
  uint32_t blockSize);

  








 

  void arm_lms_norm_init_f32(
  arm_lms_norm_instance_f32 * S,
  uint16_t numTaps,
  float32_t * pCoeffs,
  float32_t * pState,
  float32_t mu,
  uint32_t blockSize);


  

 
  typedef struct
  {
    uint16_t numTaps;      
    q31_t *pState;         
    q31_t *pCoeffs;        
    q31_t mu;              
    uint8_t postShift;     
    q31_t *recipTable;     
    q31_t energy;          
    q31_t x0;              
  } arm_lms_norm_instance_q31;

  








 

  void arm_lms_norm_q31(
  arm_lms_norm_instance_q31 * S,
  q31_t * pSrc,
  q31_t * pRef,
  q31_t * pOut,
  q31_t * pErr,
  uint32_t blockSize);

  









 

  void arm_lms_norm_init_q31(
  arm_lms_norm_instance_q31 * S,
  uint16_t numTaps,
  q31_t * pCoeffs,
  q31_t * pState,
  q31_t mu,
  uint32_t blockSize,
  uint8_t postShift);

  

 

  typedef struct
  {
    uint16_t numTaps;     
    q15_t *pState;         
    q15_t *pCoeffs;        
    q15_t mu;             
    uint8_t postShift;    
    q15_t *recipTable;    
    q15_t energy;         
    q15_t x0;             
  } arm_lms_norm_instance_q15;

  








 

  void arm_lms_norm_q15(
  arm_lms_norm_instance_q15 * S,
  q15_t * pSrc,
  q15_t * pRef,
  q15_t * pOut,
  q15_t * pErr,
  uint32_t blockSize);


  









 

  void arm_lms_norm_init_q15(
  arm_lms_norm_instance_q15 * S,
  uint16_t numTaps,
  q15_t * pCoeffs,
  q15_t * pState,
  q15_t mu,
  uint32_t blockSize,
  uint8_t postShift);

  







 

  void arm_correlate_f32(
  float32_t * pSrcA,
  uint32_t srcALen,
  float32_t * pSrcB,
  uint32_t srcBLen,
  float32_t * pDst);


   








 
  void arm_correlate_opt_q15(
  q15_t * pSrcA,
  uint32_t srcALen,
  q15_t * pSrcB,
  uint32_t srcBLen,
  q15_t * pDst,
  q15_t * pScratch);


  







 

  void arm_correlate_q15(
  q15_t * pSrcA,
  uint32_t srcALen,
  q15_t * pSrcB,
  uint32_t srcBLen,
  q15_t * pDst);

  







 

  void arm_correlate_fast_q15(
			       q15_t * pSrcA,
			      uint32_t srcALen,
			       q15_t * pSrcB,
			      uint32_t srcBLen,
			      q15_t * pDst);



  








 

  void arm_correlate_fast_opt_q15(
  q15_t * pSrcA,
  uint32_t srcALen,
  q15_t * pSrcB,
  uint32_t srcBLen,
  q15_t * pDst,
  q15_t * pScratch);

  







 

  void arm_correlate_q31(
  q31_t * pSrcA,
  uint32_t srcALen,
  q31_t * pSrcB,
  uint32_t srcBLen,
  q31_t * pDst);

  







 

  void arm_correlate_fast_q31(
  q31_t * pSrcA,
  uint32_t srcALen,
  q31_t * pSrcB,
  uint32_t srcBLen,
  q31_t * pDst);



 









 

  void arm_correlate_opt_q7(
  q7_t * pSrcA,
  uint32_t srcALen,
  q7_t * pSrcB,
  uint32_t srcBLen,
  q7_t * pDst,
  q15_t * pScratch1,
  q15_t * pScratch2);


  







 

  void arm_correlate_q7(
  q7_t * pSrcA,
  uint32_t srcALen,
  q7_t * pSrcB,
  uint32_t srcBLen,
  q7_t * pDst);


  

 
  typedef struct
  {
    uint16_t numTaps;              
    uint16_t stateIndex;           
    float32_t *pState;             
    float32_t *pCoeffs;            
    uint16_t maxDelay;             
    int32_t *pTapDelay;            
  } arm_fir_sparse_instance_f32;

  

 

  typedef struct
  {
    uint16_t numTaps;              
    uint16_t stateIndex;           
    q31_t *pState;                 
    q31_t *pCoeffs;                
    uint16_t maxDelay;             
    int32_t *pTapDelay;            
  } arm_fir_sparse_instance_q31;

  

 

  typedef struct
  {
    uint16_t numTaps;              
    uint16_t stateIndex;           
    q15_t *pState;                 
    q15_t *pCoeffs;                
    uint16_t maxDelay;             
    int32_t *pTapDelay;            
  } arm_fir_sparse_instance_q15;

  

 

  typedef struct
  {
    uint16_t numTaps;              
    uint16_t stateIndex;           
    q7_t *pState;                  
    q7_t *pCoeffs;                 
    uint16_t maxDelay;             
    int32_t *pTapDelay;            
  } arm_fir_sparse_instance_q7;

  







 

  void arm_fir_sparse_f32(
  arm_fir_sparse_instance_f32 * S,
  float32_t * pSrc,
  float32_t * pDst,
  float32_t * pScratchIn,
  uint32_t blockSize);

  









 

  void arm_fir_sparse_init_f32(
  arm_fir_sparse_instance_f32 * S,
  uint16_t numTaps,
  float32_t * pCoeffs,
  float32_t * pState,
  int32_t * pTapDelay,
  uint16_t maxDelay,
  uint32_t blockSize);

  







 

  void arm_fir_sparse_q31(
  arm_fir_sparse_instance_q31 * S,
  q31_t * pSrc,
  q31_t * pDst,
  q31_t * pScratchIn,
  uint32_t blockSize);

  









 

  void arm_fir_sparse_init_q31(
  arm_fir_sparse_instance_q31 * S,
  uint16_t numTaps,
  q31_t * pCoeffs,
  q31_t * pState,
  int32_t * pTapDelay,
  uint16_t maxDelay,
  uint32_t blockSize);

  








 

  void arm_fir_sparse_q15(
  arm_fir_sparse_instance_q15 * S,
  q15_t * pSrc,
  q15_t * pDst,
  q15_t * pScratchIn,
  q31_t * pScratchOut,
  uint32_t blockSize);


  









 

  void arm_fir_sparse_init_q15(
  arm_fir_sparse_instance_q15 * S,
  uint16_t numTaps,
  q15_t * pCoeffs,
  q15_t * pState,
  int32_t * pTapDelay,
  uint16_t maxDelay,
  uint32_t blockSize);

  








 

  void arm_fir_sparse_q7(
  arm_fir_sparse_instance_q7 * S,
  q7_t * pSrc,
  q7_t * pDst,
  q7_t * pScratchIn,
  q31_t * pScratchOut,
  uint32_t blockSize);

  









 

  void arm_fir_sparse_init_q7(
  arm_fir_sparse_instance_q7 * S,
  uint16_t numTaps,
  q7_t * pCoeffs,
  q7_t * pState,
  int32_t * pTapDelay,
  uint16_t maxDelay,
  uint32_t blockSize);


  





 

  void arm_sin_cos_f32(
  float32_t theta,
  float32_t * pSinVal,
  float32_t * pCcosVal);

  





 

  void arm_sin_cos_q31(
  q31_t theta,
  q31_t * pSinVal,
  q31_t * pCosVal);


  





 

  void arm_cmplx_conj_f32(
  float32_t * pSrc,
  float32_t * pDst,
  uint32_t numSamples);

  





 

  void arm_cmplx_conj_q31(
  q31_t * pSrc,
  q31_t * pDst,
  uint32_t numSamples);

  





 

  void arm_cmplx_conj_q15(
  q15_t * pSrc,
  q15_t * pDst,
  uint32_t numSamples);



  





 

  void arm_cmplx_mag_squared_f32(
  float32_t * pSrc,
  float32_t * pDst,
  uint32_t numSamples);

  





 

  void arm_cmplx_mag_squared_q31(
  q31_t * pSrc,
  q31_t * pDst,
  uint32_t numSamples);

  





 

  void arm_cmplx_mag_squared_q15(
  q15_t * pSrc,
  q15_t * pDst,
  uint32_t numSamples);


 

 

  






















































 

  


 

  




 


  static __inline float32_t arm_pid_f32(
  arm_pid_instance_f32 * S,
  float32_t in)
  {
    float32_t out;

     
    out = (S->A0 * in) +
      (S->A1 * S->state[0]) + (S->A2 * S->state[1]) + (S->state[2]);

     
    S->state[1] = S->state[0];
    S->state[0] = in;
    S->state[2] = out;

     
    return (out);

  }

  












 

  static __inline q31_t arm_pid_q31(
  arm_pid_instance_q31 * S,
  q31_t in)
  {
    q63_t acc;
    q31_t out;

     
    acc = (q63_t) S->A0 * in;

     
    acc += (q63_t) S->A1 * S->state[0];

     
    acc += (q63_t) S->A2 * S->state[1];

     
    out = (q31_t) (acc >> 31u);

     
    out += S->state[2];

     
    S->state[1] = S->state[0];
    S->state[0] = in;
    S->state[2] = out;

     
    return (out);

  }

  













 

  static __inline q15_t arm_pid_q15(
  arm_pid_instance_q15 * S,
  q15_t in)
  {
    q63_t acc;
    q15_t out;


    int32_t __packed *vstate;

     

     
    acc = (q31_t) __smuad(S->A0, in);

     
    vstate = ((int32_t __packed *)(S->state));
    acc = __smlald(S->A1, (q31_t) *vstate, acc);

#line 5033 "C:\\Keil_v5\\ARM\\CMSIS\\Include\\arm_math.h"

     
    acc += (q31_t) S->state[2] << 15;

     
    out = (q15_t) (__ssat((acc >> 15), 16));

     
    S->state[1] = S->state[0];
    S->state[0] = in;
    S->state[2] = out;

     
    return (out);

  }

  

 


  





 

  arm_status arm_mat_inverse_f32(
  const arm_matrix_instance_f32 * src,
  arm_matrix_instance_f32 * dst);



  

 


  



















 

  


 

  







 

  static __inline void arm_clarke_f32(
  float32_t Ia,
  float32_t Ib,
  float32_t * pIalpha,
  float32_t * pIbeta)
  {
     
    *pIalpha = Ia;

     
    *pIbeta =
      ((float32_t) 0.57735026919 * Ia + (float32_t) 1.15470053838 * Ib);

  }

  












 

  static __inline void arm_clarke_q31(
  q31_t Ia,
  q31_t Ib,
  q31_t * pIalpha,
  q31_t * pIbeta)
  {
    q31_t product1, product2;                     

     
    *pIalpha = Ia;

     
    product1 = (q31_t) (((q63_t) Ia * 0x24F34E8B) >> 30);

     
    product2 = (q31_t) (((q63_t) Ib * 0x49E69D16) >> 30);

     
    *pIbeta = __qadd(product1, product2);
  }

  

 

  





 
  void arm_q7_to_q31(
  q7_t * pSrc,
  q31_t * pDst,
  uint32_t blockSize);




  

 

  













 

  


 

   






 


  static __inline void arm_inv_clarke_f32(
  float32_t Ialpha,
  float32_t Ibeta,
  float32_t * pIa,
  float32_t * pIb)
  {
     
    *pIa = Ialpha;

     
    *pIb = -0.5 * Ialpha + (float32_t) 0.8660254039 *Ibeta;

  }

  












 

  static __inline void arm_inv_clarke_q31(
  q31_t Ialpha,
  q31_t Ibeta,
  q31_t * pIa,
  q31_t * pIb)
  {
    q31_t product1, product2;                     

     
    *pIa = Ialpha;

     
    product1 = (q31_t) (((q63_t) (Ialpha) * (0x40000000)) >> 31);

     
    product2 = (q31_t) (((q63_t) (Ibeta) * (0x6ED9EBA1)) >> 31);

     
    *pIb = __qsub(product2, product1);

  }

  

 

  





 
  void arm_q7_to_q15(
  q7_t * pSrc,
  q15_t * pDst,
  uint32_t blockSize);



  

 

  





















 

  


 

  











 

  static __inline void arm_park_f32(
  float32_t Ialpha,
  float32_t Ibeta,
  float32_t * pId,
  float32_t * pIq,
  float32_t sinVal,
  float32_t cosVal)
  {
     
    *pId = Ialpha * cosVal + Ibeta * sinVal;

     
    *pIq = -Ialpha * sinVal + Ibeta * cosVal;

  }

  














 


  static __inline void arm_park_q31(
  q31_t Ialpha,
  q31_t Ibeta,
  q31_t * pId,
  q31_t * pIq,
  q31_t sinVal,
  q31_t cosVal)
  {
    q31_t product1, product2;                     
    q31_t product3, product4;                     

     
    product1 = (q31_t) (((q63_t) (Ialpha) * (cosVal)) >> 31);

     
    product2 = (q31_t) (((q63_t) (Ibeta) * (sinVal)) >> 31);


     
    product3 = (q31_t) (((q63_t) (Ialpha) * (sinVal)) >> 31);

     
    product4 = (q31_t) (((q63_t) (Ibeta) * (cosVal)) >> 31);

     
    *pId = __qadd(product1, product2);

     
    *pIq = __qsub(product4, product3);
  }

  

 

  





 
  void arm_q7_to_float(
  q7_t * pSrc,
  float32_t * pDst,
  uint32_t blockSize);


  

 

  














 

  


 

   








 

  static __inline void arm_inv_park_f32(
  float32_t Id,
  float32_t Iq,
  float32_t * pIalpha,
  float32_t * pIbeta,
  float32_t sinVal,
  float32_t cosVal)
  {
     
    *pIalpha = Id * cosVal - Iq * sinVal;

     
    *pIbeta = Id * sinVal + Iq * cosVal;

  }


  














 


  static __inline void arm_inv_park_q31(
  q31_t Id,
  q31_t Iq,
  q31_t * pIalpha,
  q31_t * pIbeta,
  q31_t sinVal,
  q31_t cosVal)
  {
    q31_t product1, product2;                     
    q31_t product3, product4;                     

     
    product1 = (q31_t) (((q63_t) (Id) * (cosVal)) >> 31);

     
    product2 = (q31_t) (((q63_t) (Iq) * (sinVal)) >> 31);


     
    product3 = (q31_t) (((q63_t) (Id) * (sinVal)) >> 31);

     
    product4 = (q31_t) (((q63_t) (Iq) * (cosVal)) >> 31);

     
    *pIalpha = __qsub(product1, product2);

     
    *pIbeta = __qadd(product4, product3);

  }

  

 


  





 
  void arm_q31_to_float(
  q31_t * pSrc,
  float32_t * pDst,
  uint32_t blockSize);

  

 

  





























 

  


 

  





 

  static __inline float32_t arm_linear_interp_f32(
  arm_linear_interp_instance_f32 * S,
  float32_t x)
  {

    float32_t y;
    float32_t x0, x1;                             
    float32_t y0, y1;                             
    float32_t xSpacing = S->xSpacing;             
    int32_t i;                                    
    float32_t *pYData = S->pYData;                

     
    i = (int32_t) ((x - S->x1) / xSpacing);

    if(i < 0)
    {
       
      y = pYData[0];
    }
    else if((uint32_t)i >= S->nValues)
    {
       
      y = pYData[S->nValues - 1];
    }
    else
    {
       
      x0 = S->x1 + i * xSpacing;
      x1 = S->x1 + (i + 1) * xSpacing;

       
      y0 = pYData[i];
      y1 = pYData[i + 1];

       
      y = y0 + (x - x0) * ((y1 - y0) / (x1 - x0));

    }

     
    return (y);
  }

   











 


  static __inline q31_t arm_linear_interp_q31(
  q31_t * pYData,
  q31_t x,
  uint32_t nValues)
  {
    q31_t y;                                      
    q31_t y0, y1;                                 
    q31_t fract;                                  
    int32_t index;                                

     
     
     
    index = ((x & 0xFFF00000) >> 20);

    if(index >= (int32_t)(nValues - 1))
    {
      return (pYData[nValues - 1]);
    }
    else if(index < 0)
    {
      return (pYData[0]);
    }
    else
    {

       
       
      fract = (x & 0x000FFFFF) << 11;

       
      y0 = pYData[index];
      y1 = pYData[index + 1u];

       
      y = ((q31_t) ((q63_t) y0 * (0x7FFFFFFF - fract) >> 32));

       
      y += ((q31_t) (((q63_t) y1 * fract) >> 32));

       
      return (y << 1u);

    }

  }

  











 


  static __inline q15_t arm_linear_interp_q15(
  q15_t * pYData,
  q31_t x,
  uint32_t nValues)
  {
    q63_t y;                                      
    q15_t y0, y1;                                 
    q31_t fract;                                  
    int32_t index;                                

     
     
     
    index = ((x & 0xFFF00000) >> 20u);

    if(index >= (int32_t)(nValues - 1))
    {
      return (pYData[nValues - 1]);
    }
    else if(index < 0)
    {
      return (pYData[0]);
    }
    else
    {
       
       
      fract = (x & 0x000FFFFF);

       
      y0 = pYData[index];
      y1 = pYData[index + 1u];

       
      y = ((q63_t) y0 * (0xFFFFF - fract));

       
      y += ((q63_t) y1 * (fract));

       
      return (y >> 20);
    }


  }

  










 


  static __inline q7_t arm_linear_interp_q7(
  q7_t * pYData,
  q31_t x,
  uint32_t nValues)
  {
    q31_t y;                                      
    q7_t y0, y1;                                  
    q31_t fract;                                  
    uint32_t index;                               

     
     
     
    if (x < 0)
    {
      return (pYData[0]);
    }
    index = (x >> 20) & 0xfff;


    if(index >= (nValues - 1))
    {
      return (pYData[nValues - 1]);
    }
    else
    {

       
       
      fract = (x & 0x000FFFFF);

       
      y0 = pYData[index];
      y1 = pYData[index + 1u];

       
      y = ((y0 * (0xFFFFF - fract)));

       
      y += (y1 * fract);

       
      return (y >> 20u);

    }

  }
  

 

  



 

  float32_t arm_sin_f32(
  float32_t x);

  



 

  q31_t arm_sin_q31(
  q31_t x);

  



 

  q15_t arm_sin_q15(
  q15_t x);

  



 

  float32_t arm_cos_f32(
  float32_t x);

  



 

  q31_t arm_cos_q31(
  q31_t x);

  



 

  q15_t arm_cos_q15(
  q15_t x);


  

 


  

















 


  


 

  





 

  static __inline arm_status arm_sqrt_f32(
  float32_t in,
  float32_t * pOut)
  {
    if(in > 0)
    {



      *pOut = __sqrtf(in);




      return (ARM_MATH_SUCCESS);
    }
    else
    {
      *pOut = 0.0f;
      return (ARM_MATH_ARGUMENT_ERROR);
    }

  }


  





 
  arm_status arm_sqrt_q31(
  q31_t in,
  q31_t * pOut);

  





 
  arm_status arm_sqrt_q15(
  q15_t in,
  q15_t * pOut);

  

 






  

 

  static __inline void arm_circularWrite_f32(
  int32_t * circBuffer,
  int32_t L,
  uint16_t * writeOffset,
  int32_t bufferInc,
  const int32_t * src,
  int32_t srcInc,
  uint32_t blockSize)
  {
    uint32_t i = 0u;
    int32_t wOffset;

    
 
    wOffset = *writeOffset;

     
    i = blockSize;

    while(i > 0u)
    {
       
      circBuffer[wOffset] = *src;

       
      src += srcInc;

       
      wOffset += bufferInc;
      if(wOffset >= L)
        wOffset -= L;

       
      i--;
    }

     
    *writeOffset = wOffset;
  }



  

 
  static __inline void arm_circularRead_f32(
  int32_t * circBuffer,
  int32_t L,
  int32_t * readOffset,
  int32_t bufferInc,
  int32_t * dst,
  int32_t * dst_base,
  int32_t dst_length,
  int32_t dstInc,
  uint32_t blockSize)
  {
    uint32_t i = 0u;
    int32_t rOffset, dst_end;

    
 
    rOffset = *readOffset;
    dst_end = (int32_t) (dst_base + dst_length);

     
    i = blockSize;

    while(i > 0u)
    {
       
      *dst = circBuffer[rOffset];

       
      dst += dstInc;

      if(dst == (int32_t *) dst_end)
      {
        dst = dst_base;
      }

       
      rOffset += bufferInc;

      if(rOffset >= L)
      {
        rOffset -= L;
      }

       
      i--;
    }

     
    *readOffset = rOffset;
  }

  

 

  static __inline void arm_circularWrite_q15(
  q15_t * circBuffer,
  int32_t L,
  uint16_t * writeOffset,
  int32_t bufferInc,
  const q15_t * src,
  int32_t srcInc,
  uint32_t blockSize)
  {
    uint32_t i = 0u;
    int32_t wOffset;

    
 
    wOffset = *writeOffset;

     
    i = blockSize;

    while(i > 0u)
    {
       
      circBuffer[wOffset] = *src;

       
      src += srcInc;

       
      wOffset += bufferInc;
      if(wOffset >= L)
        wOffset -= L;

       
      i--;
    }

     
    *writeOffset = wOffset;
  }



  

 
  static __inline void arm_circularRead_q15(
  q15_t * circBuffer,
  int32_t L,
  int32_t * readOffset,
  int32_t bufferInc,
  q15_t * dst,
  q15_t * dst_base,
  int32_t dst_length,
  int32_t dstInc,
  uint32_t blockSize)
  {
    uint32_t i = 0;
    int32_t rOffset, dst_end;

    
 
    rOffset = *readOffset;

    dst_end = (int32_t) (dst_base + dst_length);

     
    i = blockSize;

    while(i > 0u)
    {
       
      *dst = circBuffer[rOffset];

       
      dst += dstInc;

      if(dst == (q15_t *) dst_end)
      {
        dst = dst_base;
      }

       
      rOffset += bufferInc;

      if(rOffset >= L)
      {
        rOffset -= L;
      }

       
      i--;
    }

     
    *readOffset = rOffset;
  }


  

 

  static __inline void arm_circularWrite_q7(
  q7_t * circBuffer,
  int32_t L,
  uint16_t * writeOffset,
  int32_t bufferInc,
  const q7_t * src,
  int32_t srcInc,
  uint32_t blockSize)
  {
    uint32_t i = 0u;
    int32_t wOffset;

    
 
    wOffset = *writeOffset;

     
    i = blockSize;

    while(i > 0u)
    {
       
      circBuffer[wOffset] = *src;

       
      src += srcInc;

       
      wOffset += bufferInc;
      if(wOffset >= L)
        wOffset -= L;

       
      i--;
    }

     
    *writeOffset = wOffset;
  }



  

 
  static __inline void arm_circularRead_q7(
  q7_t * circBuffer,
  int32_t L,
  int32_t * readOffset,
  int32_t bufferInc,
  q7_t * dst,
  q7_t * dst_base,
  int32_t dst_length,
  int32_t dstInc,
  uint32_t blockSize)
  {
    uint32_t i = 0;
    int32_t rOffset, dst_end;

    
 
    rOffset = *readOffset;

    dst_end = (int32_t) (dst_base + dst_length);

     
    i = blockSize;

    while(i > 0u)
    {
       
      *dst = circBuffer[rOffset];

       
      dst += dstInc;

      if(dst == (q7_t *) dst_end)
      {
        dst = dst_base;
      }

       
      rOffset += bufferInc;

      if(rOffset >= L)
      {
        rOffset -= L;
      }

       
      i--;
    }

     
    *readOffset = rOffset;
  }


  





 

  void arm_power_q31(
  q31_t * pSrc,
  uint32_t blockSize,
  q63_t * pResult);

  





 

  void arm_power_f32(
  float32_t * pSrc,
  uint32_t blockSize,
  float32_t * pResult);

  





 

  void arm_power_q15(
  q15_t * pSrc,
  uint32_t blockSize,
  q63_t * pResult);

  





 

  void arm_power_q7(
  q7_t * pSrc,
  uint32_t blockSize,
  q31_t * pResult);

  





 

  void arm_mean_q7(
  q7_t * pSrc,
  uint32_t blockSize,
  q7_t * pResult);

  





 
  void arm_mean_q15(
  q15_t * pSrc,
  uint32_t blockSize,
  q15_t * pResult);

  





 
  void arm_mean_q31(
  q31_t * pSrc,
  uint32_t blockSize,
  q31_t * pResult);

  





 
  void arm_mean_f32(
  float32_t * pSrc,
  uint32_t blockSize,
  float32_t * pResult);

  





 

  void arm_var_f32(
  float32_t * pSrc,
  uint32_t blockSize,
  float32_t * pResult);

  





 

  void arm_var_q31(
  q31_t * pSrc,
  uint32_t blockSize,
  q31_t * pResult);

  





 

  void arm_var_q15(
  q15_t * pSrc,
  uint32_t blockSize,
  q15_t * pResult);

  





 

  void arm_rms_f32(
  float32_t * pSrc,
  uint32_t blockSize,
  float32_t * pResult);

  





 

  void arm_rms_q31(
  q31_t * pSrc,
  uint32_t blockSize,
  q31_t * pResult);

  





 

  void arm_rms_q15(
  q15_t * pSrc,
  uint32_t blockSize,
  q15_t * pResult);

  





 

  void arm_std_f32(
  float32_t * pSrc,
  uint32_t blockSize,
  float32_t * pResult);

  





 

  void arm_std_q31(
  q31_t * pSrc,
  uint32_t blockSize,
  q31_t * pResult);

  





 

  void arm_std_q15(
  q15_t * pSrc,
  uint32_t blockSize,
  q15_t * pResult);

  





 

  void arm_cmplx_mag_f32(
  float32_t * pSrc,
  float32_t * pDst,
  uint32_t numSamples);

  





 

  void arm_cmplx_mag_q31(
  q31_t * pSrc,
  q31_t * pDst,
  uint32_t numSamples);

  





 

  void arm_cmplx_mag_q15(
  q15_t * pSrc,
  q15_t * pDst,
  uint32_t numSamples);

  







 

  void arm_cmplx_dot_prod_q15(
  q15_t * pSrcA,
  q15_t * pSrcB,
  uint32_t numSamples,
  q31_t * realResult,
  q31_t * imagResult);

  







 

  void arm_cmplx_dot_prod_q31(
  q31_t * pSrcA,
  q31_t * pSrcB,
  uint32_t numSamples,
  q63_t * realResult,
  q63_t * imagResult);

  







 

  void arm_cmplx_dot_prod_f32(
  float32_t * pSrcA,
  float32_t * pSrcB,
  uint32_t numSamples,
  float32_t * realResult,
  float32_t * imagResult);

  






 

  void arm_cmplx_mult_real_q15(
  q15_t * pSrcCmplx,
  q15_t * pSrcReal,
  q15_t * pCmplxDst,
  uint32_t numSamples);

  






 

  void arm_cmplx_mult_real_q31(
  q31_t * pSrcCmplx,
  q31_t * pSrcReal,
  q31_t * pCmplxDst,
  uint32_t numSamples);

  






 

  void arm_cmplx_mult_real_f32(
  float32_t * pSrcCmplx,
  float32_t * pSrcReal,
  float32_t * pCmplxDst,
  uint32_t numSamples);

  






 

  void arm_min_q7(
  q7_t * pSrc,
  uint32_t blockSize,
  q7_t * result,
  uint32_t * index);

  






 

  void arm_min_q15(
  q15_t * pSrc,
  uint32_t blockSize,
  q15_t * pResult,
  uint32_t * pIndex);

  






 
  void arm_min_q31(
  q31_t * pSrc,
  uint32_t blockSize,
  q31_t * pResult,
  uint32_t * pIndex);

  






 

  void arm_min_f32(
  float32_t * pSrc,
  uint32_t blockSize,
  float32_t * pResult,
  uint32_t * pIndex);








 

  void arm_max_q7(
  q7_t * pSrc,
  uint32_t blockSize,
  q7_t * pResult,
  uint32_t * pIndex);








 

  void arm_max_q15(
  q15_t * pSrc,
  uint32_t blockSize,
  q15_t * pResult,
  uint32_t * pIndex);








 

  void arm_max_q31(
  q31_t * pSrc,
  uint32_t blockSize,
  q31_t * pResult,
  uint32_t * pIndex);








 

  void arm_max_f32(
  float32_t * pSrc,
  uint32_t blockSize,
  float32_t * pResult,
  uint32_t * pIndex);

  






 

  void arm_cmplx_mult_cmplx_q15(
  q15_t * pSrcA,
  q15_t * pSrcB,
  q15_t * pDst,
  uint32_t numSamples);

  






 

  void arm_cmplx_mult_cmplx_q31(
  q31_t * pSrcA,
  q31_t * pSrcB,
  q31_t * pDst,
  uint32_t numSamples);

  






 

  void arm_cmplx_mult_cmplx_f32(
  float32_t * pSrcA,
  float32_t * pSrcB,
  float32_t * pDst,
  uint32_t numSamples);

  





 
  void arm_float_to_q31(
  float32_t * pSrc,
  q31_t * pDst,
  uint32_t blockSize);

  





 
  void arm_float_to_q15(
  float32_t * pSrc,
  q15_t * pDst,
  uint32_t blockSize);

  





 
  void arm_float_to_q7(
  float32_t * pSrc,
  q7_t * pDst,
  uint32_t blockSize);


  





 
  void arm_q31_to_q15(
  q31_t * pSrc,
  q15_t * pDst,
  uint32_t blockSize);

  





 
  void arm_q31_to_q7(
  q31_t * pSrc,
  q7_t * pDst,
  uint32_t blockSize);

  





 
  void arm_q15_to_float(
  q15_t * pSrc,
  float32_t * pDst,
  uint32_t blockSize);


  





 
  void arm_q15_to_q31(
  q15_t * pSrc,
  q31_t * pDst,
  uint32_t blockSize);


  





 
  void arm_q15_to_q7(
  q15_t * pSrc,
  q7_t * pDst,
  uint32_t blockSize);


  

 

  

















































 

  


 

  






 


  static __inline float32_t arm_bilinear_interp_f32(
  const arm_bilinear_interp_instance_f32 * S,
  float32_t X,
  float32_t Y)
  {
    float32_t out;
    float32_t f00, f01, f10, f11;
    float32_t *pData = S->pData;
    int32_t xIndex, yIndex, index;
    float32_t xdiff, ydiff;
    float32_t b1, b2, b3, b4;

    xIndex = (int32_t) X;
    yIndex = (int32_t) Y;

     
     
    if(xIndex < 0 || xIndex > (S->numRows - 1) || yIndex < 0
       || yIndex > (S->numCols - 1))
    {
      return (0);
    }

     
    index = (xIndex - 1) + (yIndex - 1) * S->numCols;


     
    f00 = pData[index];
    f01 = pData[index + 1];

     
    index = (xIndex - 1) + (yIndex) * S->numCols;


     
    f10 = pData[index];
    f11 = pData[index + 1];

     
    b1 = f00;
    b2 = f01 - f00;
    b3 = f10 - f00;
    b4 = f00 - f01 - f10 + f11;

     
    xdiff = X - xIndex;

     
    ydiff = Y - yIndex;

     
    out = b1 + b2 * xdiff + b3 * ydiff + b4 * xdiff * ydiff;

     
    return (out);

  }

  






 

  static __inline q31_t arm_bilinear_interp_q31(
  arm_bilinear_interp_instance_q31 * S,
  q31_t X,
  q31_t Y)
  {
    q31_t out;                                    
    q31_t acc = 0;                                
    q31_t xfract, yfract;                         
    q31_t x1, x2, y1, y2;                         
    int32_t rI, cI;                               
    q31_t *pYData = S->pData;                     
    uint32_t nCols = S->numCols;                  


     
     
     
    rI = ((X & 0xFFF00000) >> 20u);

     
     
     
    cI = ((Y & 0xFFF00000) >> 20u);

     
     
    if(rI < 0 || rI > (S->numRows - 1) || cI < 0 || cI > (S->numCols - 1))
    {
      return (0);
    }

     
     
    xfract = (X & 0x000FFFFF) << 11u;

     
    x1 = pYData[(rI) + nCols * (cI)];
    x2 = pYData[(rI) + nCols * (cI) + 1u];

     
     
    yfract = (Y & 0x000FFFFF) << 11u;

     
    y1 = pYData[(rI) + nCols * (cI + 1)];
    y2 = pYData[(rI) + nCols * (cI + 1) + 1u];

     
    out = ((q31_t) (((q63_t) x1 * (0x7FFFFFFF - xfract)) >> 32));
    acc = ((q31_t) (((q63_t) out * (0x7FFFFFFF - yfract)) >> 32));

     
    out = ((q31_t) ((q63_t) x2 * (0x7FFFFFFF - yfract) >> 32));
    acc += ((q31_t) ((q63_t) out * (xfract) >> 32));

     
    out = ((q31_t) ((q63_t) y1 * (0x7FFFFFFF - xfract) >> 32));
    acc += ((q31_t) ((q63_t) out * (yfract) >> 32));

     
    out = ((q31_t) ((q63_t) y2 * (xfract) >> 32));
    acc += ((q31_t) ((q63_t) out * (yfract) >> 32));

     
    return (acc << 2u);

  }

  





 

  static __inline q15_t arm_bilinear_interp_q15(
  arm_bilinear_interp_instance_q15 * S,
  q31_t X,
  q31_t Y)
  {
    q63_t acc = 0;                                
    q31_t out;                                    
    q15_t x1, x2, y1, y2;                         
    q31_t xfract, yfract;                         
    int32_t rI, cI;                               
    q15_t *pYData = S->pData;                     
    uint32_t nCols = S->numCols;                  

     
     
     
    rI = ((X & 0xFFF00000) >> 20);

     
     
     
    cI = ((Y & 0xFFF00000) >> 20);

     
     
    if(rI < 0 || rI > (S->numRows - 1) || cI < 0 || cI > (S->numCols - 1))
    {
      return (0);
    }

     
     
    xfract = (X & 0x000FFFFF);

     
    x1 = pYData[(rI) + nCols * (cI)];
    x2 = pYData[(rI) + nCols * (cI) + 1u];


     
     
    yfract = (Y & 0x000FFFFF);

     
    y1 = pYData[(rI) + nCols * (cI + 1)];
    y2 = pYData[(rI) + nCols * (cI + 1) + 1u];

     

     
     
    out = (q31_t) (((q63_t) x1 * (0xFFFFF - xfract)) >> 4u);
    acc = ((q63_t) out * (0xFFFFF - yfract));

     
    out = (q31_t) (((q63_t) x2 * (0xFFFFF - yfract)) >> 4u);
    acc += ((q63_t) out * (xfract));

     
    out = (q31_t) (((q63_t) y1 * (0xFFFFF - xfract)) >> 4u);
    acc += ((q63_t) out * (yfract));

     
    out = (q31_t) (((q63_t) y2 * (xfract)) >> 4u);
    acc += ((q63_t) out * (yfract));

     
     
    return (acc >> 36);

  }

  





 

  static __inline q7_t arm_bilinear_interp_q7(
  arm_bilinear_interp_instance_q7 * S,
  q31_t X,
  q31_t Y)
  {
    q63_t acc = 0;                                
    q31_t out;                                    
    q31_t xfract, yfract;                         
    q7_t x1, x2, y1, y2;                          
    int32_t rI, cI;                               
    q7_t *pYData = S->pData;                      
    uint32_t nCols = S->numCols;                  

     
     
     
    rI = ((X & 0xFFF00000) >> 20);

     
     
     
    cI = ((Y & 0xFFF00000) >> 20);

     
     
    if(rI < 0 || rI > (S->numRows - 1) || cI < 0 || cI > (S->numCols - 1))
    {
      return (0);
    }

     
     
    xfract = (X & 0x000FFFFF);

     
    x1 = pYData[(rI) + nCols * (cI)];
    x2 = pYData[(rI) + nCols * (cI) + 1u];


     
     
    yfract = (Y & 0x000FFFFF);

     
    y1 = pYData[(rI) + nCols * (cI + 1)];
    y2 = pYData[(rI) + nCols * (cI + 1) + 1u];

     
    out = ((x1 * (0xFFFFF - xfract)));
    acc = (((q63_t) out * (0xFFFFF - yfract)));

     
    out = ((x2 * (0xFFFFF - yfract)));
    acc += (((q63_t) out * (xfract)));

     
    out = ((y1 * (0xFFFFF - xfract)));
    acc += (((q63_t) out * (yfract)));

     
    out = ((y2 * (yfract)));
    acc += (((q63_t) out * (xfract)));

     
    return (acc >> 40);

  }

  

 






























#line 7339 "C:\\Keil_v5\\ARM\\CMSIS\\Include\\arm_math.h"
















 
#line 7 "../../sPlc/sPlc.h"
#line 1 "../Middlewares/ST/STM32_USB_Host_Library/Core/Inc/usbh_core.h"
















 
 







 
#line 1 "../USB_HOST/Target/usbh_conf.h"
 
















 
 

 






 

#line 1 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdio.h"
 
 
 





 






 







 




  
 








#line 47 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdio.h"


  



    typedef unsigned int size_t;    









 
 

 



    typedef struct __va_list __va_list;






   




 




typedef struct __fpos_t_struct {
    unsigned __int64 __pos;
    



 
    struct {
        unsigned int __state1, __state2;
    } __mbstate;
} fpos_t;
   


 


   

 

typedef struct __FILE FILE;
   






 

#line 136 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdio.h"


extern FILE __stdin, __stdout, __stderr;
extern FILE *__aeabi_stdin, *__aeabi_stdout, *__aeabi_stderr;

#line 166 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdio.h"
    

    

    





     



   


 


   


 

   



 

   


 




   


 





    


 






extern __declspec(__nothrow) int remove(const char *  ) __attribute__((__nonnull__(1)));
   





 
extern __declspec(__nothrow) int rename(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   








 
extern __declspec(__nothrow) FILE *tmpfile(void);
   




 
extern __declspec(__nothrow) char *tmpnam(char *  );
   











 

extern __declspec(__nothrow) int fclose(FILE *  ) __attribute__((__nonnull__(1)));
   







 
extern __declspec(__nothrow) int fflush(FILE *  );
   







 
extern __declspec(__nothrow) FILE *fopen(const char * __restrict  ,
                           const char * __restrict  ) __attribute__((__nonnull__(1,2)));
   








































 
extern __declspec(__nothrow) FILE *freopen(const char * __restrict  ,
                    const char * __restrict  ,
                    FILE * __restrict  ) __attribute__((__nonnull__(2,3)));
   








 
extern __declspec(__nothrow) void setbuf(FILE * __restrict  ,
                    char * __restrict  ) __attribute__((__nonnull__(1)));
   




 
extern __declspec(__nothrow) int setvbuf(FILE * __restrict  ,
                   char * __restrict  ,
                   int  , size_t  ) __attribute__((__nonnull__(1)));
   















 
#pragma __printf_args
extern __declspec(__nothrow) int fprintf(FILE * __restrict  ,
                    const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   


















 
#pragma __printf_args
extern __declspec(__nothrow) int _fprintf(FILE * __restrict  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   



 
#pragma __printf_args
extern __declspec(__nothrow) int printf(const char * __restrict  , ...) __attribute__((__nonnull__(1)));
   




 
#pragma __printf_args
extern __declspec(__nothrow) int _printf(const char * __restrict  , ...) __attribute__((__nonnull__(1)));
   



 
#pragma __printf_args
extern __declspec(__nothrow) int sprintf(char * __restrict  , const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   






 
#pragma __printf_args
extern __declspec(__nothrow) int _sprintf(char * __restrict  , const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   



 

#pragma __printf_args
extern __declspec(__nothrow) int __ARM_snprintf(char * __restrict  , size_t  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(3)));


#pragma __printf_args
extern __declspec(__nothrow) int snprintf(char * __restrict  , size_t  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(3)));
   















 

#pragma __printf_args
extern __declspec(__nothrow) int _snprintf(char * __restrict  , size_t  ,
                      const char * __restrict  , ...) __attribute__((__nonnull__(3)));
   



 
#pragma __scanf_args
extern __declspec(__nothrow) int fscanf(FILE * __restrict  ,
                    const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   






























 
#pragma __scanf_args
extern __declspec(__nothrow) int _fscanf(FILE * __restrict  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   



 
#pragma __scanf_args
extern __declspec(__nothrow) int scanf(const char * __restrict  , ...) __attribute__((__nonnull__(1)));
   






 
#pragma __scanf_args
extern __declspec(__nothrow) int _scanf(const char * __restrict  , ...) __attribute__((__nonnull__(1)));
   



 
#pragma __scanf_args
extern __declspec(__nothrow) int sscanf(const char * __restrict  ,
                    const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   








 
#pragma __scanf_args
extern __declspec(__nothrow) int _sscanf(const char * __restrict  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   



 

 
extern __declspec(__nothrow) int vfscanf(FILE * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) int vscanf(const char * __restrict  , __va_list) __attribute__((__nonnull__(1)));
extern __declspec(__nothrow) int vsscanf(const char * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));

extern __declspec(__nothrow) int _vfscanf(FILE * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) int _vscanf(const char * __restrict  , __va_list) __attribute__((__nonnull__(1)));
extern __declspec(__nothrow) int _vsscanf(const char * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) int __ARM_vsscanf(const char * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));

extern __declspec(__nothrow) int vprintf(const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1)));
   





 
extern __declspec(__nothrow) int _vprintf(const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1)));
   



 
extern __declspec(__nothrow) int vfprintf(FILE * __restrict  ,
                    const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1,2)));
   






 
extern __declspec(__nothrow) int vsprintf(char * __restrict  ,
                     const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1,2)));
   






 
extern __declspec(__nothrow) int __ARM_vsnprintf(char * __restrict  , size_t  ,
                     const char * __restrict  , __va_list  ) __attribute__((__nonnull__(3)));

extern __declspec(__nothrow) int vsnprintf(char * __restrict  , size_t  ,
                     const char * __restrict  , __va_list  ) __attribute__((__nonnull__(3)));
   







 

extern __declspec(__nothrow) int _vsprintf(char * __restrict  ,
                      const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1,2)));
   



 
extern __declspec(__nothrow) int _vfprintf(FILE * __restrict  ,
                     const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1,2)));
   



 
extern __declspec(__nothrow) int _vsnprintf(char * __restrict  , size_t  ,
                      const char * __restrict  , __va_list  ) __attribute__((__nonnull__(3)));
   



 

#pragma __printf_args
extern __declspec(__nothrow) int asprintf(char **  , const char * __restrict  , ...) __attribute__((__nonnull__(2)));
extern __declspec(__nothrow) int vasprintf(char **  , const char * __restrict  , __va_list  ) __attribute__((__nonnull__(2)));

#pragma __printf_args
extern __declspec(__nothrow) int __ARM_asprintf(char **  , const char * __restrict  , ...) __attribute__((__nonnull__(2)));
extern __declspec(__nothrow) int __ARM_vasprintf(char **  , const char * __restrict  , __va_list  ) __attribute__((__nonnull__(2)));
   








 

extern __declspec(__nothrow) int fgetc(FILE *  ) __attribute__((__nonnull__(1)));
   







 
extern __declspec(__nothrow) char *fgets(char * __restrict  , int  ,
                    FILE * __restrict  ) __attribute__((__nonnull__(1,3)));
   










 
extern __declspec(__nothrow) int fputc(int  , FILE *  ) __attribute__((__nonnull__(2)));
   







 
extern __declspec(__nothrow) int fputs(const char * __restrict  , FILE * __restrict  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) int getc(FILE *  ) __attribute__((__nonnull__(1)));
   







 




    extern __declspec(__nothrow) int (getchar)(void);

   





 
extern __declspec(__nothrow) char *gets(char *  ) __attribute__((__nonnull__(1)));
   









 
extern __declspec(__nothrow) int putc(int  , FILE *  ) __attribute__((__nonnull__(2)));
   





 




    extern __declspec(__nothrow) int (putchar)(int  );

   



 
extern __declspec(__nothrow) int puts(const char *  ) __attribute__((__nonnull__(1)));
   





 
extern __declspec(__nothrow) int ungetc(int  , FILE *  ) __attribute__((__nonnull__(2)));
   






















 

extern __declspec(__nothrow) size_t fread(void * __restrict  ,
                    size_t  , size_t  , FILE * __restrict  ) __attribute__((__nonnull__(1,4)));
   











 

extern __declspec(__nothrow) size_t __fread_bytes_avail(void * __restrict  ,
                    size_t  , FILE * __restrict  ) __attribute__((__nonnull__(1,3)));
   











 

extern __declspec(__nothrow) size_t fwrite(const void * __restrict  ,
                    size_t  , size_t  , FILE * __restrict  ) __attribute__((__nonnull__(1,4)));
   







 

extern __declspec(__nothrow) int fgetpos(FILE * __restrict  , fpos_t * __restrict  ) __attribute__((__nonnull__(1,2)));
   








 
extern __declspec(__nothrow) int fseek(FILE *  , long int  , int  ) __attribute__((__nonnull__(1)));
   














 
extern __declspec(__nothrow) int fsetpos(FILE * __restrict  , const fpos_t * __restrict  ) __attribute__((__nonnull__(1,2)));
   










 
extern __declspec(__nothrow) long int ftell(FILE *  ) __attribute__((__nonnull__(1)));
   











 
extern __declspec(__nothrow) void rewind(FILE *  ) __attribute__((__nonnull__(1)));
   





 

extern __declspec(__nothrow) void clearerr(FILE *  ) __attribute__((__nonnull__(1)));
   




 

extern __declspec(__nothrow) int feof(FILE *  ) __attribute__((__nonnull__(1)));
   


 
extern __declspec(__nothrow) int ferror(FILE *  ) __attribute__((__nonnull__(1)));
   


 
extern __declspec(__nothrow) void perror(const char *  );
   









 

extern __declspec(__nothrow) int _fisatty(FILE *   ) __attribute__((__nonnull__(1)));
    
 

extern __declspec(__nothrow) void __use_no_semihosting_swi(void);
extern __declspec(__nothrow) void __use_no_semihosting(void);
    





 











#line 1021 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdio.h"



 

#line 31 "../USB_HOST/Target/usbh_conf.h"
#line 1 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdlib.h"
 
 
 




 
 



 






   














  


 








#line 54 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdlib.h"


  



    typedef unsigned int size_t;    
#line 70 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdlib.h"






    



    typedef unsigned short wchar_t;  
#line 91 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdlib.h"

typedef struct div_t { int quot, rem; } div_t;
    
typedef struct ldiv_t { long int quot, rem; } ldiv_t;
    

typedef struct lldiv_t { long long quot, rem; } lldiv_t;
    


#line 112 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdlib.h"
   



 

   




 
#line 131 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdlib.h"
   


 
extern __declspec(__nothrow) int __aeabi_MB_CUR_MAX(void);

   




 

   




 




extern __declspec(__nothrow) double atof(const char *  ) __attribute__((__nonnull__(1)));
   



 
extern __declspec(__nothrow) int atoi(const char *  ) __attribute__((__nonnull__(1)));
   



 
extern __declspec(__nothrow) long int atol(const char *  ) __attribute__((__nonnull__(1)));
   



 

extern __declspec(__nothrow) long long atoll(const char *  ) __attribute__((__nonnull__(1)));
   



 


extern __declspec(__nothrow) double strtod(const char * __restrict  , char ** __restrict  ) __attribute__((__nonnull__(1)));
   

















 

extern __declspec(__nothrow) float strtof(const char * __restrict  , char ** __restrict  ) __attribute__((__nonnull__(1)));
extern __declspec(__nothrow) long double strtold(const char * __restrict  , char ** __restrict  ) __attribute__((__nonnull__(1)));
   

 

extern __declspec(__nothrow) long int strtol(const char * __restrict  ,
                        char ** __restrict  , int  ) __attribute__((__nonnull__(1)));
   



























 
extern __declspec(__nothrow) unsigned long int strtoul(const char * __restrict  ,
                                       char ** __restrict  , int  ) __attribute__((__nonnull__(1)));
   


























 

 
extern __declspec(__nothrow) long long strtoll(const char * __restrict  ,
                                  char ** __restrict  , int  )
                          __attribute__((__nonnull__(1)));
   




 
extern __declspec(__nothrow) unsigned long long strtoull(const char * __restrict  ,
                                            char ** __restrict  , int  )
                                   __attribute__((__nonnull__(1)));
   



 

extern __declspec(__nothrow) int rand(void);
   







 
extern __declspec(__nothrow) void srand(unsigned int  );
   






 

struct _rand_state { int __x[57]; };
extern __declspec(__nothrow) int _rand_r(struct _rand_state *);
extern __declspec(__nothrow) void _srand_r(struct _rand_state *, unsigned int);
struct _ANSI_rand_state { int __x[1]; };
extern __declspec(__nothrow) int _ANSI_rand_r(struct _ANSI_rand_state *);
extern __declspec(__nothrow) void _ANSI_srand_r(struct _ANSI_rand_state *, unsigned int);
   


 

extern __declspec(__nothrow) void *calloc(size_t  , size_t  );
   



 
extern __declspec(__nothrow) void free(void *  );
   





 
extern __declspec(__nothrow) void *malloc(size_t  );
   



 
extern __declspec(__nothrow) void *realloc(void *  , size_t  );
   













 

extern __declspec(__nothrow) int posix_memalign(void **  , size_t  , size_t  );
   









 

typedef int (*__heapprt)(void *, char const *, ...);
extern __declspec(__nothrow) void __heapstats(int (*  )(void *  ,
                                           char const *  , ...),
                        void *  ) __attribute__((__nonnull__(1)));
   










 
extern __declspec(__nothrow) int __heapvalid(int (*  )(void *  ,
                                           char const *  , ...),
                       void *  , int  ) __attribute__((__nonnull__(1)));
   














 
extern __declspec(__nothrow) __declspec(__noreturn) void abort(void);
   







 

extern __declspec(__nothrow) int atexit(void (*  )(void)) __attribute__((__nonnull__(1)));
   




 
#line 436 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdlib.h"


extern __declspec(__nothrow) __declspec(__noreturn) void exit(int  );
   












 

extern __declspec(__nothrow) __declspec(__noreturn) void _Exit(int  );
   







      

extern __declspec(__nothrow) char *getenv(const char *  ) __attribute__((__nonnull__(1)));
   









 

extern __declspec(__nothrow) int  system(const char *  );
   









 

extern  void *bsearch(const void *  , const void *  ,
              size_t  , size_t  ,
              int (*  )(const void *, const void *)) __attribute__((__nonnull__(1,2,5)));
   












 
#line 524 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdlib.h"


extern  void qsort(void *  , size_t  , size_t  ,
           int (*  )(const void *, const void *)) __attribute__((__nonnull__(1,4)));
   









 

#line 553 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdlib.h"

extern __declspec(__nothrow) __attribute__((const)) int abs(int  );
   



 

extern __declspec(__nothrow) __attribute__((const)) div_t div(int  , int  );
   









 
extern __declspec(__nothrow) __attribute__((const)) long int labs(long int  );
   



 




extern __declspec(__nothrow) __attribute__((const)) ldiv_t ldiv(long int  , long int  );
   











 







extern __declspec(__nothrow) __attribute__((const)) long long llabs(long long  );
   



 




extern __declspec(__nothrow) __attribute__((const)) lldiv_t lldiv(long long  , long long  );
   











 
#line 634 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdlib.h"




 
typedef struct __sdiv32by16 { int quot, rem; } __sdiv32by16;
typedef struct __udiv32by16 { unsigned int quot, rem; } __udiv32by16;
    
typedef struct __sdiv64by32 { int rem, quot; } __sdiv64by32;

__value_in_regs extern __declspec(__nothrow) __attribute__((const)) __sdiv32by16 __rt_sdiv32by16(
     int  ,
     short int  );
   

 
__value_in_regs extern __declspec(__nothrow) __attribute__((const)) __udiv32by16 __rt_udiv32by16(
     unsigned int  ,
     unsigned short  );
   

 
__value_in_regs extern __declspec(__nothrow) __attribute__((const)) __sdiv64by32 __rt_sdiv64by32(
     int  , unsigned int  ,
     int  );
   

 




 
extern __declspec(__nothrow) unsigned int __fp_status(unsigned int  , unsigned int  );
   







 























 
extern __declspec(__nothrow) int mblen(const char *  , size_t  );
   












 
extern __declspec(__nothrow) int mbtowc(wchar_t * __restrict  ,
                   const char * __restrict  , size_t  );
   















 
extern __declspec(__nothrow) int wctomb(char *  , wchar_t  );
   













 





 
extern __declspec(__nothrow) size_t mbstowcs(wchar_t * __restrict  ,
                      const char * __restrict  , size_t  ) __attribute__((__nonnull__(2)));
   














 
extern __declspec(__nothrow) size_t wcstombs(char * __restrict  ,
                      const wchar_t * __restrict  , size_t  ) __attribute__((__nonnull__(2)));
   














 

extern __declspec(__nothrow) void __use_realtime_heap(void);
extern __declspec(__nothrow) void __use_realtime_division(void);
extern __declspec(__nothrow) void __use_two_region_memory(void);
extern __declspec(__nothrow) void __use_no_heap(void);
extern __declspec(__nothrow) void __use_no_heap_region(void);

extern __declspec(__nothrow) char const *__C_library_version_string(void);
extern __declspec(__nothrow) int __C_library_version_number(void);











#line 892 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdlib.h"





 
#line 32 "../USB_HOST/Target/usbh_conf.h"
#line 33 "../USB_HOST/Target/usbh_conf.h"
#line 34 "../USB_HOST/Target/usbh_conf.h"

#line 36 "../USB_HOST/Target/usbh_conf.h"
#line 37 "../USB_HOST/Target/usbh_conf.h"

 

 



 




 




 



 




 

 


 


 


 


 


 


 


 


 


 
 



#line 99 "../USB_HOST/Target/usbh_conf.h"






 




 

 

 


 


 


 


 

#line 136 "../USB_HOST/Target/usbh_conf.h"



#line 147 "../USB_HOST/Target/usbh_conf.h"

#line 157 "../USB_HOST/Target/usbh_conf.h"



 




 



 




 

 



 



 



 

#line 28 "../Middlewares/ST/STM32_USB_Host_Library/Core/Inc/usbh_core.h"
#line 1 "../Middlewares/ST/STM32_USB_Host_Library/Core/Inc/usbh_def.h"
















 

 







 
#line 29 "../Middlewares/ST/STM32_USB_Host_Library/Core/Inc/usbh_def.h"



 



 




 









































#line 91 "../Middlewares/ST/STM32_USB_Host_Library/Core/Inc/usbh_def.h"












#line 110 "../Middlewares/ST/STM32_USB_Host_Library/Core/Inc/usbh_def.h"

 




 





 





 
 
#line 141 "../Middlewares/ST/STM32_USB_Host_Library/Core/Inc/usbh_def.h"

 
#line 153 "../Middlewares/ST/STM32_USB_Host_Library/Core/Inc/usbh_def.h"








 
 
#line 173 "../Middlewares/ST/STM32_USB_Host_Library/Core/Inc/usbh_def.h"































 











typedef union
{
  uint16_t w;
  struct BW
  {
    uint8_t msb;
    uint8_t lsb;
  }
  bw;
}
uint16_t_uint8_t;


typedef union _USB_Setup
{
  uint32_t d8[2];

  struct _SetupPkt_Struc
  {
    uint8_t           bmRequestType;
    uint8_t           bRequest;
    uint16_t_uint8_t  wValue;
    uint16_t_uint8_t  wIndex;
    uint16_t_uint8_t  wLength;
  } b;
}
USB_Setup_TypeDef;

typedef  struct  _DescHeader
{
  uint8_t  bLength;
  uint8_t  bDescriptorType;
}
USBH_DescHeader_t;

typedef struct _DeviceDescriptor
{
  uint8_t   bLength;
  uint8_t   bDescriptorType;
  uint16_t  bcdUSB;         
  uint8_t   bDeviceClass;
  uint8_t   bDeviceSubClass;
  uint8_t   bDeviceProtocol;
  

 
  uint8_t   bMaxPacketSize;
  uint16_t   idVendor;       
  uint16_t   idProduct;      
  uint16_t   bcdDevice;      
  uint8_t   iManufacturer;   
  uint8_t   iProduct;        
  uint8_t   iSerialNumber;   
  uint8_t   bNumConfigurations;  
}
USBH_DevDescTypeDef;

typedef struct _EndpointDescriptor
{
  uint8_t   bLength;
  uint8_t   bDescriptorType;
  uint8_t   bEndpointAddress;    
  uint8_t   bmAttributes;        
  uint16_t  wMaxPacketSize;      
  uint8_t   bInterval;           
}
USBH_EpDescTypeDef;

typedef struct _InterfaceDescriptor
{
  uint8_t bLength;
  uint8_t bDescriptorType;
  uint8_t bInterfaceNumber;
  uint8_t bAlternateSetting;     
  uint8_t bNumEndpoints;         
  uint8_t bInterfaceClass;       
  uint8_t bInterfaceSubClass;    
  uint8_t bInterfaceProtocol;    
  uint8_t iInterface;            
  USBH_EpDescTypeDef               Ep_Desc[5U];
}
USBH_InterfaceDescTypeDef;


typedef struct _ConfigurationDescriptor
{
  uint8_t   bLength;
  uint8_t   bDescriptorType;
  uint16_t  wTotalLength;          
  uint8_t   bNumInterfaces;        
  uint8_t   bConfigurationValue;   
  uint8_t   iConfiguration;        
  uint8_t   bmAttributes;          
  uint8_t   bMaxPower;             
  USBH_InterfaceDescTypeDef        Itf_Desc[10U];
}
USBH_CfgDescTypeDef;


 
typedef enum
{
  USBH_OK = 0,
  USBH_BUSY,
  USBH_FAIL,
  USBH_NOT_SUPPORTED,
  USBH_UNRECOVERED_ERROR,
  USBH_ERROR_SPEED_UNKNOWN,
} USBH_StatusTypeDef;




 

typedef enum
{
  USBH_SPEED_HIGH  = 0U,
  USBH_SPEED_FULL  = 1U,
  USBH_SPEED_LOW   = 2U,

} USBH_SpeedTypeDef;

 
typedef enum
{
  HOST_IDLE = 0U,
  HOST_DEV_WAIT_FOR_ATTACHMENT,
  HOST_DEV_ATTACHED,
  HOST_DEV_DISCONNECTED,
  HOST_DETECT_DEVICE_SPEED,
  HOST_ENUMERATION,
  HOST_CLASS_REQUEST,
  HOST_INPUT,
  HOST_SET_CONFIGURATION,
  HOST_SET_WAKEUP_FEATURE,
  HOST_CHECK_CLASS,
  HOST_CLASS,
  HOST_SUSPENDED,
  HOST_ABORT_STATE,
} HOST_StateTypeDef;

 
typedef enum
{
  ENUM_IDLE = 0U,
  ENUM_GET_FULL_DEV_DESC,
  ENUM_SET_ADDR,
  ENUM_GET_CFG_DESC,
  ENUM_GET_FULL_CFG_DESC,
  ENUM_GET_MFC_STRING_DESC,
  ENUM_GET_PRODUCT_STRING_DESC,
  ENUM_GET_SERIALNUM_STRING_DESC,
} ENUM_StateTypeDef;

 
typedef enum
{
  CTRL_IDLE = 0U,
  CTRL_SETUP,
  CTRL_SETUP_WAIT,
  CTRL_DATA_IN,
  CTRL_DATA_IN_WAIT,
  CTRL_DATA_OUT,
  CTRL_DATA_OUT_WAIT,
  CTRL_STATUS_IN,
  CTRL_STATUS_IN_WAIT,
  CTRL_STATUS_OUT,
  CTRL_STATUS_OUT_WAIT,
  CTRL_ERROR,
  CTRL_STALLED,
  CTRL_COMPLETE
} CTRL_StateTypeDef;


 
typedef enum
{
  CMD_IDLE = 0U,
  CMD_SEND,
  CMD_WAIT
} CMD_StateTypeDef;

typedef enum
{
  USBH_URB_IDLE = 0U,
  USBH_URB_DONE,
  USBH_URB_NOTREADY,
  USBH_URB_NYET,
  USBH_URB_ERROR,
  USBH_URB_STALL,
  USBH_URB_NAK_WAIT
} USBH_URBStateTypeDef;

typedef enum
{
  USBH_PORT_EVENT = 1U,
  USBH_URB_EVENT,
  USBH_CONTROL_EVENT,
  USBH_CLASS_EVENT,
  USBH_STATE_CHANGED_EVENT,
}
USBH_OSEventTypeDef;

 
typedef struct
{
  uint8_t               pipe_in;
  uint8_t               pipe_out;
  uint8_t               pipe_size;
  uint8_t               *buff;
  uint16_t              length;
  uint16_t              timer;
  USB_Setup_TypeDef     setup;
  CTRL_StateTypeDef     state;
  uint8_t               errorcount;

} USBH_CtrlTypeDef;

 
typedef struct
{
  uint8_t                           CfgDesc_Raw[256U];
  uint8_t                           Data[1024U];
  uint8_t                           address;
  uint8_t                           speed;
  uint8_t                           EnumCnt;
  uint8_t                           RstCnt;
  volatile uint8_t                      is_connected;
  volatile uint8_t                      is_disconnected;
  volatile uint8_t                      is_ReEnumerated;
  volatile uint8_t                      PortEnabled;
  uint8_t                           current_interface;
  USBH_DevDescTypeDef               DevDesc;
  USBH_CfgDescTypeDef               CfgDesc;
} USBH_DeviceTypeDef;

struct _USBH_HandleTypeDef;

 
typedef struct
{
  const char          *Name;
  uint8_t              ClassCode;
  USBH_StatusTypeDef(*Init)(struct _USBH_HandleTypeDef *phost);
  USBH_StatusTypeDef(*DeInit)(struct _USBH_HandleTypeDef *phost);
  USBH_StatusTypeDef(*Requests)(struct _USBH_HandleTypeDef *phost);
  USBH_StatusTypeDef(*BgndProcess)(struct _USBH_HandleTypeDef *phost);
  USBH_StatusTypeDef(*SOFProcess)(struct _USBH_HandleTypeDef *phost);
  void                *pData;
} USBH_ClassTypeDef;

 
typedef struct _USBH_HandleTypeDef
{
  volatile HOST_StateTypeDef     gState;        
  ENUM_StateTypeDef     EnumState;     
  CMD_StateTypeDef      RequestState;
  USBH_CtrlTypeDef      Control;
  USBH_DeviceTypeDef    device;
  USBH_ClassTypeDef    *pClass[5U];
  USBH_ClassTypeDef    *pActiveClass;
  uint32_t              ClassNumber;
  uint32_t              Pipes[16];
  volatile uint32_t         Timer;




  uint32_t              Timeout;
  uint8_t               id;
  void                 *pData;
  void (* pUser)(struct _USBH_HandleTypeDef *pHandle, uint8_t id);






  osMessageQueueId_t    os_event;
  osThreadId_t          thread;

  uint32_t              os_msg;


} USBH_HandleTypeDef;


#line 512 "../Middlewares/ST/STM32_USB_Host_Library/Core/Inc/usbh_def.h"








#line 29 "../Middlewares/ST/STM32_USB_Host_Library/Core/Inc/usbh_core.h"
#line 1 "../Middlewares/ST/STM32_USB_Host_Library/Core/Inc/usbh_ioreq.h"
















 

 







 
#line 29 "../Middlewares/ST/STM32_USB_Host_Library/Core/Inc/usbh_ioreq.h"
#line 1 "../Middlewares/ST/STM32_USB_Host_Library/Core/Inc/usbh_core.h"
















 
 
#line 165 "../Middlewares/ST/STM32_USB_Host_Library/Core/Inc/usbh_core.h"


 



 



 



#line 30 "../Middlewares/ST/STM32_USB_Host_Library/Core/Inc/usbh_ioreq.h"



 



 




 




 












 




 


 




 


 



 


 



 
USBH_StatusTypeDef USBH_CtlSendSetup(USBH_HandleTypeDef *phost,
                                     uint8_t *buff,
                                     uint8_t pipe_num);

USBH_StatusTypeDef USBH_CtlSendData(USBH_HandleTypeDef *phost,
                                    uint8_t *buff,
                                    uint16_t length,
                                    uint8_t pipe_num,
                                    uint8_t do_ping);

USBH_StatusTypeDef USBH_CtlReceiveData(USBH_HandleTypeDef *phost,
                                       uint8_t *buff,
                                       uint16_t length,
                                       uint8_t pipe_num);

USBH_StatusTypeDef USBH_BulkReceiveData(USBH_HandleTypeDef *phost,
                                        uint8_t *buff,
                                        uint16_t length,
                                        uint8_t pipe_num);

USBH_StatusTypeDef USBH_BulkSendData(USBH_HandleTypeDef *phost,
                                     uint8_t *buff,
                                     uint16_t length,
                                     uint8_t pipe_num,
                                     uint8_t do_ping);

USBH_StatusTypeDef USBH_InterruptReceiveData(USBH_HandleTypeDef *phost,
                                             uint8_t             *buff,
                                             uint8_t             length,
                                             uint8_t             pipe_num);

USBH_StatusTypeDef USBH_InterruptSendData(USBH_HandleTypeDef *phost,
                                          uint8_t *buff,
                                          uint8_t length,
                                          uint8_t pipe_num);


USBH_StatusTypeDef USBH_IsocReceiveData(USBH_HandleTypeDef *phost,
                                        uint8_t *buff,
                                        uint32_t length,
                                        uint8_t pipe_num);


USBH_StatusTypeDef USBH_IsocSendData(USBH_HandleTypeDef *phost,
                                     uint8_t *buff,
                                     uint32_t length,
                                     uint8_t pipe_num);


 









 



 



 


#line 30 "../Middlewares/ST/STM32_USB_Host_Library/Core/Inc/usbh_core.h"
#line 1 "../Middlewares/ST/STM32_USB_Host_Library/Core/Inc/usbh_pipes.h"
















 

 







 
#line 29 "../Middlewares/ST/STM32_USB_Host_Library/Core/Inc/usbh_pipes.h"



 



 




 



 


 



 


 




 


 



 


 



 

USBH_StatusTypeDef USBH_OpenPipe(USBH_HandleTypeDef *phost,
                                 uint8_t pipe_num,
                                 uint8_t epnum,
                                 uint8_t dev_address,
                                 uint8_t speed,
                                 uint8_t ep_type,
                                 uint16_t mps);

USBH_StatusTypeDef USBH_ClosePipe(USBH_HandleTypeDef *phost,
                                  uint8_t pipe_num);

uint8_t USBH_AllocPipe(USBH_HandleTypeDef *phost,
                       uint8_t ep_addr);

USBH_StatusTypeDef USBH_FreePipe(USBH_HandleTypeDef *phost,
                                 uint8_t idx);








 











 



 



 


#line 31 "../Middlewares/ST/STM32_USB_Host_Library/Core/Inc/usbh_core.h"
#line 1 "../Middlewares/ST/STM32_USB_Host_Library/Core/Inc/usbh_ctlreq.h"
















 

 







 
#line 29 "../Middlewares/ST/STM32_USB_Host_Library/Core/Inc/usbh_ctlreq.h"



 



 




 




 
 











 




 


 




 


 



 
extern uint8_t USBH_CfgDesc[512];


 



 
USBH_StatusTypeDef USBH_CtlReq(USBH_HandleTypeDef *phost, uint8_t *buff,
                               uint16_t length);

USBH_StatusTypeDef USBH_GetDescriptor(USBH_HandleTypeDef *phost,
                                      uint8_t  req_type, uint16_t value_idx,
                                      uint8_t *buff, uint16_t length);

USBH_StatusTypeDef USBH_Get_DevDesc(USBH_HandleTypeDef *phost, uint16_t length);

USBH_StatusTypeDef USBH_Get_StringDesc(USBH_HandleTypeDef *phost,
                                       uint8_t string_index, uint8_t *buff,
                                       uint16_t length);

USBH_StatusTypeDef USBH_SetCfg(USBH_HandleTypeDef *phost, uint16_t cfg_idx);

USBH_StatusTypeDef USBH_Get_CfgDesc(USBH_HandleTypeDef *phost, uint16_t length);

USBH_StatusTypeDef USBH_SetAddress(USBH_HandleTypeDef *phost,
                                   uint8_t DeviceAddress);

USBH_StatusTypeDef USBH_SetInterface(USBH_HandleTypeDef *phost, uint8_t ep_num,
                                     uint8_t altSetting);

USBH_StatusTypeDef USBH_SetFeature(USBH_HandleTypeDef *phost, uint8_t wValue);

USBH_StatusTypeDef USBH_ClrFeature(USBH_HandleTypeDef *phost, uint8_t ep_num);

USBH_DescHeader_t *USBH_GetNextDesc(uint8_t *pbuf, uint16_t *ptr);


 









 



 



 


#line 32 "../Middlewares/ST/STM32_USB_Host_Library/Core/Inc/usbh_core.h"



 



 




 




 



 
#line 60 "../Middlewares/ST/STM32_USB_Host_Library/Core/Inc/usbh_core.h"




 





 



 



 



 



 
USBH_StatusTypeDef USBH_Init(USBH_HandleTypeDef *phost,
                             void (*pUsrFunc)(USBH_HandleTypeDef *phost, uint8_t id), uint8_t id);

USBH_StatusTypeDef USBH_DeInit(USBH_HandleTypeDef *phost);
USBH_StatusTypeDef USBH_Start(USBH_HandleTypeDef *phost);
USBH_StatusTypeDef USBH_Stop(USBH_HandleTypeDef *phost);
USBH_StatusTypeDef USBH_Process(USBH_HandleTypeDef *phost);
USBH_StatusTypeDef USBH_ReEnumerate(USBH_HandleTypeDef *phost);
USBH_StatusTypeDef USBH_RegisterClass(USBH_HandleTypeDef *phost, USBH_ClassTypeDef *pclass);
USBH_StatusTypeDef USBH_SelectInterface(USBH_HandleTypeDef *phost, uint8_t interface);

uint8_t            USBH_FindInterfaceIndex(USBH_HandleTypeDef *phost, uint8_t interface_number, uint8_t alt_settings);
uint8_t            USBH_FindInterface(USBH_HandleTypeDef *phost, uint8_t Class, uint8_t SubClass, uint8_t Protocol);
uint8_t            USBH_GetActiveClass(USBH_HandleTypeDef *phost);
uint8_t            USBH_IsPortEnabled(USBH_HandleTypeDef *phost);

 
USBH_StatusTypeDef USBH_LL_Init(USBH_HandleTypeDef *phost);
USBH_StatusTypeDef USBH_LL_DeInit(USBH_HandleTypeDef *phost);
USBH_StatusTypeDef USBH_LL_Start(USBH_HandleTypeDef *phost);
USBH_StatusTypeDef USBH_LL_Stop(USBH_HandleTypeDef *phost);

USBH_StatusTypeDef USBH_LL_Connect(USBH_HandleTypeDef *phost);
USBH_StatusTypeDef USBH_LL_Disconnect(USBH_HandleTypeDef *phost);
USBH_SpeedTypeDef  USBH_LL_GetSpeed(USBH_HandleTypeDef *phost);
USBH_StatusTypeDef USBH_LL_ResetPort(USBH_HandleTypeDef *phost);
uint32_t           USBH_LL_GetLastXferSize(USBH_HandleTypeDef *phost, uint8_t pipe);

USBH_StatusTypeDef USBH_LL_DriverVBUS(USBH_HandleTypeDef *phost, uint8_t state);

USBH_StatusTypeDef USBH_LL_OpenPipe(USBH_HandleTypeDef *phost,
                                    uint8_t pipe,
                                    uint8_t epnum,
                                    uint8_t dev_address,
                                    uint8_t speed,
                                    uint8_t ep_type,
                                    uint16_t mps);

USBH_StatusTypeDef USBH_LL_ActivatePipe(USBH_HandleTypeDef *phost, uint8_t pipe);
USBH_StatusTypeDef USBH_LL_ClosePipe(USBH_HandleTypeDef *phost, uint8_t pipe);

USBH_StatusTypeDef USBH_LL_SubmitURB(USBH_HandleTypeDef *phost,
                                     uint8_t pipe,
                                     uint8_t direction,
                                     uint8_t ep_type,
                                     uint8_t token,
                                     uint8_t *pbuff,
                                     uint16_t length,
                                     uint8_t do_ping);

USBH_URBStateTypeDef USBH_LL_GetURBState(USBH_HandleTypeDef *phost, uint8_t pipe);


USBH_StatusTypeDef USBH_LL_NotifyURBChange(USBH_HandleTypeDef *phost);
void USBH_OS_PutMessage(USBH_HandleTypeDef *phost, USBH_OSEventTypeDef message, uint32_t timeout, uint32_t priority);


USBH_StatusTypeDef USBH_LL_SetToggle(USBH_HandleTypeDef *phost, uint8_t pipe, uint8_t toggle);

uint8_t USBH_LL_GetToggle(USBH_HandleTypeDef *phost, uint8_t pipe);

void USBH_LL_PortDisabled(USBH_HandleTypeDef *phost);
void USBH_LL_PortEnabled(USBH_HandleTypeDef *phost);

 
void USBH_LL_SetTimer(USBH_HandleTypeDef *phost, uint32_t time);
void USBH_LL_IncTimer(USBH_HandleTypeDef *phost);

void USBH_Delay(uint32_t Delay);


 








 



 



 



#line 8 "../../sPlc/sPlc.h"
 
#line 10 "../../sPlc/sPlc.h"
#line 11 "../../sPlc/sPlc.h"
#line 12 "../../sPlc/sPlc.h"
#line 1 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\ctype.h"
 
 
 
 





 






 








#line 35 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\ctype.h"






#line 49 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\ctype.h"

 
#line 59 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\ctype.h"

 
 









 
#line 81 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\ctype.h"





#line 133 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\ctype.h"

extern __declspec(__nothrow) __attribute__((const)) unsigned char **__rt_ctype_table(void);







    extern int (isalnum)(int  );

     





    extern int (isalpha)(int  );

     





    extern int (iscntrl)(int  );

     
     

 




    extern int (isdigit)(int  );

     

    extern int (isblank)(int  );
     
     
     





    extern int (isgraph)(int  );

     





    extern int (islower)(int  );

     





    extern int (isprint)(int  );

     
     





    extern int (ispunct)(int  );

     





    extern int (isspace)(int  );

     





    extern int (isupper)(int  );

     

 
 

static inline int __isxdigit_helper(int __t) { return (__t ^ (__t << 2)); }




    extern int (isxdigit)(int  );

     



extern int tolower(int  );
     
     

extern int toupper(int  );
     
     







#line 272 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\ctype.h"



 

#line 13 "../../sPlc/sPlc.h"
#line 1 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\LIMITS.H"
 
 
 





 






     

     

     

     
#line 30 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\LIMITS.H"
       

       






#line 45 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\LIMITS.H"
     
     


     

     

     

     

     

     





     





     





     


       

       

       




 

#line 14 "../../sPlc/sPlc.h"
#line 1 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdbool.h"
 






 





#line 25 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdbool.h"



#line 15 "../../sPlc/sPlc.h"
#line 16 "../../sPlc/sPlc.h"
#line 17 "../../sPlc/sPlc.h"
 
#line 1 "../../lib/libcrc.h"


 
#line 5 "../../lib/libcrc.h"
 
uint16_t crc16Calculate(uint8_t *buf, uint32_t len);
uint16_t crc16CalculateAdd(uint8_t dat);
void crc16Clear(void);
void crc16SetCrcOld(uint16_t old);
 
uint32_t crc32Calculate(uint8_t *buf, uint32_t len);
uint32_t crc32CalculateAdd(uint8_t dat);
void crc32Clear(void);
void crc32SetCrcOld(uint32_t old);






#line 19 "../../sPlc/sPlc.h"
#line 1 "../../deviceInfo/deviceConfig.h"


 
#line 5 "../../deviceInfo/deviceConfig.h"
 
typedef struct{
	uint16_t calibrationPwr0[10];
	uint16_t calibrationPwr1[10];
	char serialNumber[16];
	int16_t mfg_year;
	int16_t mfg_month;
	int16_t mfg_day;
	int8_t redLedDc;
	int8_t greenLedDc;
	int8_t blueLedDc;
	int8_t aimGain;
	int16_t fiberDetect;
	char normalOpenInterLock;
}deviceConfig_t;
typedef struct{
	uint32_t powerUpCycle;
	uint32_t runTime;
	int16_t laserMaxPhotoDiode;
	int16_t mucMaxTemper;
}deviceLogInfo_t;
 
extern deviceConfig_t deviceConfig;
extern deviceLogInfo_t deviceLogInfo;
extern uint32_t	UniqueId[3];
 
extern uint16_t cpuGetFlashSize(void);
extern void readStm32UniqueID(void);




#line 20 "../../sPlc/sPlc.h"
#line 1 "../../sPlc/sPlcConfig.h"


 





 

 

 
#line 21 "../../sPlc/sPlcConfig.h"
 
#line 32 "../../sPlc/sPlcConfig.h"
 

#line 41 "../../sPlc/sPlcConfig.h"


















 



 
#line 74 "../../sPlc/sPlcConfig.h"
 

 
#line 92 "../../sPlc/sPlcConfig.h"
 				




 

 


 



 


#line 118 "../../sPlc/sPlcConfig.h"
 









#line 135 "../../sPlc/sPlcConfig.h"





 
#line 152 "../../sPlc/sPlcConfig.h"

#line 161 "../../sPlc/sPlcConfig.h"
 

 

 





 





 
#line 188 "../../sPlc/sPlcConfig.h"
 









#line 210 "../../sPlc/sPlcConfig.h"

#line 223 "../../sPlc/sPlcConfig.h"

#line 232 "../../sPlc/sPlcConfig.h"
 
#line 241 "../../sPlc/sPlcConfig.h"
 
#line 250 "../../sPlc/sPlcConfig.h"
 












 


 


 
#line 290 "../../sPlc/sPlcConfig.h"
 
#line 311 "../../sPlc/sPlcConfig.h"
 
#line 332 "../../sPlc/sPlcConfig.h"
 
#line 353 "../../sPlc/sPlcConfig.h"
 

























































 

 



 



 
#line 431 "../../sPlc/sPlcConfig.h"
 
#line 438 "../../sPlc/sPlcConfig.h"
 


 


 
#line 453 "../../sPlc/sPlcConfig.h"
 
#line 470 "../../sPlc/sPlcConfig.h"

#line 479 "../../sPlc/sPlcConfig.h"
 
#line 500 "../../sPlc/sPlcConfig.h"
 




 

#line 517 "../../sPlc/sPlcConfig.h"
 
#line 525 "../../sPlc/sPlcConfig.h"
 
#line 532 "../../sPlc/sPlcConfig.h"

#line 541 "../../sPlc/sPlcConfig.h"
 				





 
#line 554 "../../sPlc/sPlcConfig.h"
 



 
#line 569 "../../sPlc/sPlcConfig.h"
 















































 















































 
#line 698 "../../sPlc/sPlcConfig.h"

#line 731 "../../sPlc/sPlcConfig.h"
 
#line 741 "../../sPlc/sPlcConfig.h"
 





 
#line 755 "../../sPlc/sPlcConfig.h"
 
#line 784 "../../sPlc/sPlcConfig.h"

#line 796 "../../sPlc/sPlcConfig.h"
 
#line 821 "../../sPlc/sPlcConfig.h"
 
#line 832 "../../sPlc/sPlcConfig.h"
 
#line 840 "../../sPlc/sPlcConfig.h"
 


 
#line 878 "../../sPlc/sPlcConfig.h"



 


 



 
 


 




 
#line 910 "../../sPlc/sPlcConfig.h"
 







#line 21 "../../sPlc/sPlc.h"
#line 1 "../../sPlc/sPlcFun.h"


 
#line 1 "../../sPlc/sPlc.h"
#line 5 "../../sPlc/sPlcFun.h"





#line 22 "../../sPlc/sPlc.h"
#line 1 "../../MainApp/dcHmiApp.h"


 
#line 5 "../../MainApp/dcHmiApp.h"
 










#line 22 "../../MainApp/dcHmiApp.h"








 


 
#line 51 "../../MainApp/dcHmiApp.h"
 
void dcHmiLoop(void);
void dcHmiLoopInit(void);
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
 
void loadSelectScheme(int16_t classify, int16_t index);
void updateSchemeDetail(int16_t classify, int16_t index);
void unselectSchemeAll(void);
void seletcSchemeNum(int16_t classify, int16_t index);
void unselectSchemeNum(int16_t index);
 
void clearReleaseTimeEnergy(void);
void updateReleaseTimeEnergy(void);
void updateSchemeInfo(int16_t classify, int16_t cn);
void updateWarnMsgDisplay(uint8_t id);
void returnStandbyDisplay(void);
void standbyKeyValue(uint8_t value);
void standbyKeyTouchEnable(int8_t enable);
 
void updateExtralDisplay(void);
void standbyDebugInfoVisiable(int8_t enable);
void optionKeyEnable(uint8_t enable);
 
void loadDeviceConfig(void);
void saveDeviceConfig(void);
 







#line 23 "../../sPlc/sPlc.h"
#line 1 "../../deviceInfo/preScheme.h"
#line 31 "../../deviceInfo/preScheme.h"


#line 24 "../../sPlc/sPlc.h"
#line 1 "../../dcHmi/hmiLib.h"


 
#line 5 "../../dcHmi/hmiLib.h"
#line 1 "../../dcHmi/hmiCmdQueue.h"






 



 
#line 1 "../../dcHmi/hmiLib.h"
#line 16 "../../dcHmi/hmiLib.h"





#line 13 "../../dcHmi/hmiCmdQueue.h"
 
typedef unsigned char qdata;
typedef unsigned short qsize;



 
extern void queue_reset(void);





 
extern void queue_push(qdata _data);






 
extern qsize queue_find_cmd(qdata *cmd,qsize buf_len);



#line 6 "../../dcHmi/hmiLib.h"
#line 1 "../../dcHmi/hmiDriver.h"


 
#line 5 "../../dcHmi/hmiDriver.h"
 





 





 
uint16_t CheckCRC16(uint8_t *buffer,uint16_t n);




 
void DelayMS(unsigned int n);



 
void LockDeviceConfig(void);



 
void UnlockDeviceConfig(void);






 
void SetCommBps(uint8_t option);



 
void SetHandShake(void);




 
void SetFcolor(uint16_t color);




 
void SetBcolor(uint16_t color);



 
void GUI_CleanScreen(void);





 
void SetTextSpace(uint8_t x_w, uint8_t y_w);






 
void SetFont_Region(uint8_t enable,uint16_t width,uint16_t height );





 
void SetFilterColor(uint16_t fillcolor_dwon, uint16_t fillcolor_up);








 
void DisText(uint16_t x, uint16_t y,uint8_t back,uint8_t font,uint8_t *strings );








 
void DisCursor(uint8_t enable,uint16_t x, uint16_t y,uint8_t width,uint8_t height );





 
void DisFull_Image(uint16_t image_id,uint8_t masken);







 
void DisArea_Image(uint16_t x,uint16_t y,uint16_t image_id,uint8_t masken);











 
void DisCut_Image(uint16_t x,uint16_t y,uint16_t image_id,uint16_t image_x,uint16_t image_y,
                  uint16_t image_l, uint16_t image_w,uint8_t masken);








 
void DisFlashImage(uint16_t x,uint16_t y,uint16_t flashimage_id,uint8_t enable,uint8_t playnum);





 
void GUI_Dot(uint16_t x,uint16_t y);







 
void GUI_Line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);






 
void GUI_ConDots(uint8_t mode,uint16_t *dot,uint16_t dot_cnt);






 
void GUI_Circle(uint16_t x0, uint16_t y0, uint16_t r);






 
void GUI_CircleFill(uint16_t x0, uint16_t y0, uint16_t r);








 
void GUI_Arc(uint16_t x,uint16_t y, uint16_t r,uint16_t sa, uint16_t ea);







 
void GUI_Rectangle(uint16_t x0, uint16_t y0, uint16_t x1,uint16_t y1 );







 
void GUI_RectangleFill(uint16_t x0, uint16_t y0, uint16_t x1,uint16_t y1 );







 
void GUI_Ellipse (uint16_t x0, uint16_t y0, uint16_t x1,uint16_t y1 );







 
void GUI_EllipseFill (uint16_t x0, uint16_t y0, uint16_t x1,uint16_t y1 );







 
void SetBackLight(uint8_t light_level);




 
void SetBuzzer(uint8_t time);







 
void SetTouchPaneOption(uint8_t enbale,uint8_t beep_on,uint8_t work_mode,uint8_t press_calibration);



 
void    CalibrateTouchPane(void);



 
void TestTouchPane(void);














 
void WriteLayer(uint8_t layer);




 
void DisplyLayer(uint8_t layer);




 
void ClearLayer(uint8_t layer);






 
void WriteUserFlash(uint32_t startAddress,uint16_t length,uint8_t *_data);





 
void ReadUserFlash(uint32_t startAddress,uint16_t length);





 
void CopyLayer(uint8_t src_layer,uint8_t dest_layer);




 
void SetScreen(uint16_t screen_id);



 
void GetScreen(uint16_t screen_id);









 
void SetScreenUpdateEnable(uint8_t enable);






 
void SetControlFocus(uint16_t screen_id,uint16_t control_id,uint8_t focus);






 
void SetControlVisiable(uint16_t screen_id,uint16_t control_id,uint8_t visible);






 
void SetControlEnable(uint16_t screen_id,uint16_t control_id,uint8_t enable);





 
void GetControlValue(uint16_t screen_id,uint16_t control_id);






 
void SetButtonValue(uint16_t screen_id,uint16_t control_id,uint8_t value);






 
void SetTextValue(uint16_t screen_id,uint16_t control_id,uint8_t *str);










 
void SetTextInt32(uint16_t screen_id,uint16_t control_id,uint32_t value,uint8_t sign,uint8_t fill_zero);








 
void SetTextFloat(uint16_t screen_id,uint16_t control_id,float value,uint8_t precision,uint8_t show_zeros);








 
void SetProgressValue(uint16_t screen_id,uint16_t control_id,uint32_t value);






 
void SetMeterValue(uint16_t screen_id,uint16_t control_id,uint32_t value);






 
void Set_picMeterValue(uint16_t screen_id,uint16_t control_id,uint16_t value);






 

void SetSliderValue(uint16_t screen_id,uint16_t control_id,uint32_t value);






 
void SetSelectorValue(uint16_t screen_id,uint16_t control_id,uint8_t item);





 
void AnimationStart(uint16_t screen_id,uint16_t control_id);





 
void AnimationStop(uint16_t screen_id,uint16_t control_id);





 
void AnimationPause(uint16_t screen_id,uint16_t control_id);






 
void AnimationPlayFrame(uint16_t screen_id,uint16_t control_id,uint8_t frame_id);





 
void AnimationPlayPrev(uint16_t screen_id,uint16_t control_id);





 
void AnimationPlayNext(uint16_t screen_id,uint16_t control_id);







 
void GraphChannelAdd(uint16_t screen_id,uint16_t control_id,uint8_t channel,uint16_t color);






 
void GraphChannelDel(uint16_t screen_id,uint16_t control_id,uint8_t channel);








 
void GraphChannelDataAdd(uint16_t screen_id,uint16_t control_id,uint8_t channel,uint8_t *pData,uint16_t nDataLen);






 
void GraphChannelDataClear(uint16_t screen_id,uint16_t control_id,uint8_t channel);









 
void GraphSetViewport(uint16_t screen_id,uint16_t control_id,int16_t x_offset,uint16_t x_mul,int16_t y_offset,uint16_t y_mul);




 
void BatchBegin(uint16_t screen_id);





 
void BatchSetButtonValue(uint16_t control_id,uint8_t state);





 
void BatchSetProgressValue(uint16_t control_id,uint32_t value);





 
void BatchSetSliderValue(uint16_t control_id,uint32_t value);





 
void BatchSetMeterValue(uint16_t control_id,uint32_t value);





 
void BatchSetText(uint16_t control_id,uint8_t *strings);





 
void BatchSetFrame(uint16_t control_id,uint16_t frame_id);







 
void BatchSetVisible(uint16_t control_id,uint8_t visible);





 
void BatchSetEnable(uint16_t control_id,uint8_t enable);





 
void BatchEnd(void);






 
void SeTimer(uint16_t screen_id,uint16_t control_id,uint32_t timeout);





 
void StartTimer(uint16_t screen_id,uint16_t control_id);





 
void StopTimer(uint16_t screen_id,uint16_t control_id);





 
void PauseTimer(uint16_t screen_id,uint16_t control_id);







 
void SetControlBackColor(uint16_t screen_id,uint16_t control_id,uint16_t color);







 
void SetControlForeColor(uint16_t screen_id,uint16_t control_id,uint16_t color);







 
void ShowPopupMenu(uint16_t screen_id,uint16_t control_id,uint8_t show,uint16_t focus_control_id);









 
void ShowKeyboard(uint8_t show,uint16_t x,uint16_t y,uint8_t type,uint8_t option,uint8_t max_len);






 
void SetLanguage(uint8_t ui_lang,uint8_t sys_lang);







 
void FlashBeginSaveControl(uint32_t version,uint32_t address);





 
void FlashSaveControl(uint16_t screen_id,uint16_t control_id);



 
void FlashEndSaveControl(void);





 
void FlashRestoreControl(uint32_t version,uint32_t address);









 
void HistoryGraph_SetValueInt8(uint16_t screen_id,uint16_t control_id,uint8_t *value,uint8_t channel);







 
void HistoryGraph_SetValueInt16(uint16_t screen_id,uint16_t control_id,uint16_t *value,uint8_t channel);







 
void HistoryGraph_SetValueInt32(uint16_t screen_id,uint16_t control_id,uint32_t *value,uint8_t channel);







 
void HistoryGraph_SetValueFloat(uint16_t screen_id,uint16_t control_id,float *value,uint8_t channel);






 
void HistoryGraph_EnableSampling(uint16_t screen_id,uint16_t control_id,uint8_t enable);







 
void HistoryGraph_ShowChannel(uint16_t screen_id,uint16_t control_id,uint8_t channel,uint8_t show);







 
void HistoryGraph_SetTimeLength(uint16_t screen_id,uint16_t control_id,uint16_t sample_count);





 
void HistoryGraph_SetTimeFullScreen(uint16_t screen_id,uint16_t control_id);








 
void HistoryGraph_SetTimeZoom(uint16_t screen_id,uint16_t control_id,uint16_t zoom,uint16_t max_zoom,uint16_t min_zoom);


#line 847 "../../dcHmi/hmiDriver.h"







 
void Record_SetEvent(uint16_t screen_id,uint16_t control_id,uint16_t value,uint8_t *time);







 
void Record_ResetEvent(uint16_t screen_id,uint16_t control_id,uint16_t value,uint8_t *time);






 
void Record_Add(uint16_t screen_id,uint16_t control_id,uint8_t *record);





 
void Record_Clear(uint16_t screen_id,uint16_t control_id);






 
void Record_SetOffset(uint16_t screen_id,uint16_t control_id,uint16_t offset);





 
void Record_GetCount(uint16_t screen_id,uint16_t control_id);


void ReadRTC(void);




 
void PlayMusic(uint8_t *buffer);

 
void SetMusicVolume(uint8_t volume);
void PlayMusicId(uint16_t id, uint8_t loop);
void SuspendMusicId(void);
void ResumeMusicId(void);
void StopMusicId(void);
 
void resetGddcHmi(void);
#line 7 "../../dcHmi/hmiLib.h"
#line 1 "../../dcHmi/hmiCmdProcess.h"






 




 
#line 14 "../../dcHmi/hmiCmdProcess.h"
 
#line 28 "../../dcHmi/hmiCmdProcess.h"





enum CtrlType
{
    kCtrlUnknown=0x0,
    kCtrlButton=0x10,                     
    kCtrlText,                            
    kCtrlProgress,                        
    kCtrlSlider,                          
    kCtrlMeter,                            
    kCtrlDropList,                        
    kCtrlAnimation,                       
    kCtrlRTC,                             
    kCtrlGraph,                           
    kCtrlTable,                           
    kCtrlMenu,                            
    kCtrlSelector,                        
    kCtrlQRCode,                          
};

#pragma pack(push)
#pragma pack(1)                           

typedef struct
{
    uint8_t    cmd_head;                    

    uint8_t    cmd_type;                    
    uint8_t    ctrl_msg;                    
    uint16_t   screen_id;                   
    uint16_t   control_id;                  
    uint8_t    control_type;                

    uint8_t    param[256];                  

    uint8_t  cmd_tail[4];                   
}CTRL_MSG,*PCTRL_MSG;

#pragma pack(pop)



 
void NOTIFYHandShake(void);





 
void ProcessMessage( PCTRL_MSG msg, uint16_t size );




 
void NotifyScreen(uint16_t screen_id);





 
void NotifyTouchXY(uint8_t press,uint16_t x,uint16_t y);







 
void NotifyButton(uint16_t screen_id, uint16_t control_id, uint8_t state);








 
void NotifyText(uint16_t screen_id, uint16_t control_id, uint8_t *str);






    
void NotifyProgress(uint16_t screen_id, uint16_t control_id, uint32_t value);






     
void NotifySlider(uint16_t screen_id, uint16_t control_id, uint32_t value);






 
void NotifyMeter(uint16_t screen_id, uint16_t control_id, uint32_t value);







 
void NotifyMenu(uint16_t screen_id, uint16_t control_id, uint8_t  item, uint8_t  state);







 
void NotifySelector(uint16_t screen_id, uint16_t control_id, uint8_t  item);




 
void NotifyTimer(uint16_t screen_id, uint16_t control_id);





 
void NotifyReadFlash(uint8_t status,uint8_t *_data,uint16_t length);




 
void NotifyWriteFlash(uint8_t status);









 
void NotifyReadRTC(uint8_t year,uint8_t month,uint8_t week,uint8_t day,uint8_t hour,uint8_t minute,uint8_t second);

#line 8 "../../dcHmi/hmiLib.h"
 
extern void hmiUartSendChar(uint8_t t);
extern void hmiUartInit(void);
extern void Uart0sr(void);









#line 25 "../../sPlc/sPlc.h"
#line 1 "../../MainApp/dcHmiRes.h"


 
#line 20 "../../MainApp/dcHmiRes.h"
 

#line 39 "../../MainApp/dcHmiRes.h"

#line 55 "../../MainApp/dcHmiRes.h"
 
#line 71 "../../MainApp/dcHmiRes.h"
 
#line 118 "../../MainApp/dcHmiRes.h"
 
#line 137 "../../MainApp/dcHmiRes.h"
 
#line 152 "../../MainApp/dcHmiRes.h"
 


 
#line 167 "../../MainApp/dcHmiRes.h"
 

#line 209 "../../MainApp/dcHmiRes.h"
 
#line 218 "../../MainApp/dcHmiRes.h"
 
#line 225 "../../MainApp/dcHmiRes.h"

#line 236 "../../MainApp/dcHmiRes.h"

#line 247 "../../MainApp/dcHmiRes.h"

#line 258 "../../MainApp/dcHmiRes.h"

#line 279 "../../MainApp/dcHmiRes.h"

#line 296 "../../MainApp/dcHmiRes.h"
 



 




#line 26 "../../sPlc/sPlc.h"
#line 1 "../../MainApp/MainAppLib.h"


 
#line 5 "../../MainApp/MainAppLib.h"
#line 6 "../../MainApp/MainAppLib.h"
 
typedef struct{
	float kp;
	float ki;
	float kd;
	float ek0;
	float ek1;
	float ek2;
}IncPid_t;
 
void addAcousticTime(void);
void decAcousticTime(void);
void addAcousticEnergy(void);
void decAcousticEnergy(void);
uint8_t fanSpeedToPwm(uint8_t speed);
uint8_t getLcdDuty(int16_t LcdBrg);
int16_t keyRuleAdd(int16_t ps, int16_t max);
int16_t keyRuleDec(int16_t ps, int16_t min);
void loadScheme(void);
void updateSchemeName(void);
void updateCustomScheme(uint8_t index);
int8_t checkScheme(int8_t cn);
void defaultScheme(void);
void restoreDefault(void);
uint16_t fitLaserToCode(uint8_t ch, int16_t power, deviceConfig_t *pcfg);
uint16_t fitLaserToCodeLine(uint8_t ch, int16_t power);
uint8_t saveSchemeToUdisk(void);
uint8_t loadSchemeFromUdisk(void);
int16_t IncPidCalc(IncPid_t *t, int16_t ref, int16_t fb);
 




#line 27 "../../sPlc/sPlc.h"
#line 1 "../../MainApp/dcHmiLanguage.H"
#line 4 "../../MainApp/dcHmiLanguage.H"
 
extern const char WARN_MSG_NO_ERROR[];
extern const char WARN_MSG_INTERLOCK_UNPLUG[];
extern const char WARN_MSG_FOOTSWITCH_UNPLUG[];
extern const char WARN_MSG_ESTOP_PRESS[];
extern const char WARN_MSG_FIBER_UNPLUG[];
extern const char WARN_MSG_OUT_ENERGY[];
extern const char WARN_MSG_DIODE_HTEMP[];
extern const char WARN_MSG_DIODE_LTEMP[];
extern const char WARN_MSG_DIODE0_OVERCURRENT[];
extern const char WARN_MSG_DIODE1_OVERCURRENT[];
extern const char WARN_MSG_NTC_ERROR[];
extern const char WARN_MSG_ENVI_HTEMP[];
extern const char WARN_MSG_ENVI_LTEMP[];
extern const char WARN_MSG_FOOT_DEPRESSED[];
extern const char WARN_MSG_LASER_EMIT[];
extern const char WARN_MSG_WAIT_TRIGGER[];
extern const char WARN_MSG_FIBER_MISSMATE[];
extern const char INFO_MSG_TYPE[];
extern const char INFO_MSG_SN[];
extern const char INFO_MSG_WAVELENGTH[];
extern const char INFO_MSG_LASER_POWER[];
extern const char INFO_MSG_VERSION[];
extern const char INFO_MSG_MANUFACTURE_DATE[];
 








#line 28 "../../sPlc/sPlc.h"
#line 29 "../../sPlc/sPlc.h"
 
#line 1 "../USB_HOST/Target/usbh_platform.h"
 















 
 

 







 
#line 1 "../USB_HOST/App/usb_host.h"
 
















 
 

 







 
#line 31 "../USB_HOST/App/usb_host.h"
#line 32 "../USB_HOST/App/usb_host.h"

 

 



 




 




 



 

 
typedef enum {
  APPLICATION_IDLE = 0,
  APPLICATION_START,
  APPLICATION_READY,
  APPLICATION_DISCONNECT
}ApplicationTypeDef;




 

 

 
void MX_USB_HOST_Init(void);



 



 



 







#line 30 "../USB_HOST/Target/usbh_platform.h"

 

 

void MX_DriverVbusFS(uint8_t state);







#line 31 "../../sPlc/sPlc.h"
#line 32 "../../sPlc/sPlc.h"
#line 1 "../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc/usbh_msc.h"
















 

 







 
#line 29 "../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc/usbh_msc.h"
#line 1 "../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc/usbh_msc_bot.h"
















 

 







 
#line 29 "../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc/usbh_msc_bot.h"



 



 



 




 




 

typedef enum
{
  BOT_OK          = 0,
  BOT_FAIL        = 1,
  BOT_PHASE_ERROR = 2,
  BOT_BUSY        = 3
}
BOT_StatusTypeDef;

typedef enum
{
  BOT_CMD_IDLE  = 0,
  BOT_CMD_SEND,
  BOT_CMD_WAIT,
}
BOT_CMDStateTypeDef;

 
typedef enum
{

  BOT_CSW_CMD_PASSED   =        0x00,
  BOT_CSW_CMD_FAILED   =        0x01,
  BOT_CSW_PHASE_ERROR  =        0x02,
}
BOT_CSWStatusTypeDef;

typedef enum
{
  BOT_SEND_CBW  = 1,
  BOT_SEND_CBW_WAIT,
  BOT_DATA_IN,
  BOT_DATA_IN_WAIT,
  BOT_DATA_OUT,
  BOT_DATA_OUT_WAIT,
  BOT_RECEIVE_CSW,
  BOT_RECEIVE_CSW_WAIT,
  BOT_ERROR_IN,
  BOT_ERROR_OUT,
  BOT_UNRECOVERED_ERROR
}
BOT_StateTypeDef;

typedef union
{
  struct __CBW
  {
    uint32_t Signature;
    uint32_t Tag;
    uint32_t DataTransferLength;
    uint8_t  Flags;
    uint8_t  LUN;
    uint8_t  CBLength;
    uint8_t  CB[16];
  } field;
  uint8_t data[31];
}
BOT_CBWTypeDef;

typedef union
{
  struct __CSW
  {
    uint32_t Signature;
    uint32_t Tag;
    uint32_t DataResidue;
    uint8_t  Status;
  } field;
  uint8_t data[13];
}
BOT_CSWTypeDef;

typedef struct
{
  uint32_t                   data[16];
  BOT_StateTypeDef           state;
  BOT_StateTypeDef           prev_state;
  BOT_CMDStateTypeDef        cmd_state;
  BOT_CBWTypeDef             cbw;
  uint8_t                    Reserved1;
  BOT_CSWTypeDef             csw;
  uint8_t                    Reserved2[3];
  uint8_t                    *pbuf;
}
BOT_HandleTypeDef;



 





 




























 



 


 



 



 



 
USBH_StatusTypeDef USBH_MSC_BOT_REQ_Reset(USBH_HandleTypeDef *phost);
USBH_StatusTypeDef USBH_MSC_BOT_REQ_GetMaxLUN(USBH_HandleTypeDef *phost, uint8_t *Maxlun);

USBH_StatusTypeDef USBH_MSC_BOT_Init(USBH_HandleTypeDef *phost);
USBH_StatusTypeDef USBH_MSC_BOT_Process(USBH_HandleTypeDef *phost, uint8_t lun);
USBH_StatusTypeDef USBH_MSC_BOT_Error(USBH_HandleTypeDef *phost, uint8_t lun);





 










 



 



 



 

#line 30 "../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc/usbh_msc.h"
#line 1 "../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc/usbh_msc_scsi.h"
















 

 







 
#line 29 "../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc/usbh_msc_scsi.h"




 



 



 




 


 
typedef struct
{
  uint32_t block_nbr;
  uint16_t block_size;
} SCSI_CapacityTypeDef;


 
typedef struct
{
  uint8_t key;
  uint8_t asc;
  uint8_t ascq;
} SCSI_SenseTypeDef;

 
typedef struct
{
  uint8_t PeripheralQualifier;
  uint8_t DeviceType;
  uint8_t RemovableMedia;
  uint8_t vendor_id[9];
  uint8_t product_id[17];
  uint8_t revision_id[5];
} SCSI_StdInquiryDataTypeDef;



 
#line 85 "../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc/usbh_msc_scsi.h"











 
#line 111 "../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc/usbh_msc_scsi.h"


 




 
#line 127 "../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc/usbh_msc_scsi.h"


 




 






 



 


 



 



 



 
USBH_StatusTypeDef USBH_MSC_SCSI_TestUnitReady(USBH_HandleTypeDef *phost,
                                               uint8_t lun);

USBH_StatusTypeDef USBH_MSC_SCSI_ReadCapacity(USBH_HandleTypeDef *phost,
                                              uint8_t lun,
                                              SCSI_CapacityTypeDef *capacity);

USBH_StatusTypeDef USBH_MSC_SCSI_Inquiry(USBH_HandleTypeDef *phost,
                                         uint8_t lun,
                                         SCSI_StdInquiryDataTypeDef *inquiry);

USBH_StatusTypeDef USBH_MSC_SCSI_RequestSense(USBH_HandleTypeDef *phost,
                                              uint8_t lun,
                                              SCSI_SenseTypeDef *sense_data);

USBH_StatusTypeDef USBH_MSC_SCSI_Write(USBH_HandleTypeDef *phost,
                                       uint8_t lun,
                                       uint32_t address,
                                       uint8_t *pbuf,
                                       uint32_t length);

USBH_StatusTypeDef USBH_MSC_SCSI_Read(USBH_HandleTypeDef *phost,
                                      uint8_t lun,
                                      uint32_t address,
                                      uint8_t *pbuf,
                                      uint32_t length);




 










 



 



 



 

#line 31 "../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc/usbh_msc.h"



 



 



 




 




 

typedef enum
{
  MSC_INIT = 0,
  MSC_IDLE,
  MSC_TEST_UNIT_READY,
  MSC_READ_CAPACITY10,
  MSC_READ_INQUIRY,
  MSC_REQUEST_SENSE,
  MSC_READ,
  MSC_WRITE,
  MSC_UNRECOVERED_ERROR,
  MSC_PERIODIC_CHECK,
  MSC_USER_NOTIFY
}
MSC_StateTypeDef;

typedef enum
{
  MSC_OK,
  MSC_NOT_READY,
  MSC_ERROR,

}
MSC_ErrorTypeDef;

typedef enum
{
  MSC_REQ_IDLE = 0,
  MSC_REQ_RESET,
  MSC_REQ_GET_MAX_LUN,
  MSC_REQ_ERROR,
}
MSC_ReqStateTypeDef;






 
typedef struct
{
  MSC_StateTypeDef            state;
  MSC_ErrorTypeDef            error;
  USBH_StatusTypeDef          prev_ready_state;
  SCSI_CapacityTypeDef        capacity;
  SCSI_SenseTypeDef           sense;
  SCSI_StdInquiryDataTypeDef  inquiry;
  uint8_t                     state_changed;

}
MSC_LUNTypeDef;

 
typedef struct _MSC_Process
{
  uint8_t              max_lun;
  uint8_t              Reserved[3];
  uint8_t              InPipe;
  uint8_t              OutPipe;
  uint8_t              OutEp;
  uint8_t              InEp;
  uint16_t             OutEpSize;
  uint16_t             InEpSize;
  MSC_StateTypeDef     state;
  MSC_ErrorTypeDef     error;
  MSC_ReqStateTypeDef  req_state;
  MSC_ReqStateTypeDef  prev_req_state;
  BOT_HandleTypeDef    hbot;
  MSC_LUNTypeDef       unit[2U];
  uint16_t             current_lun;
  uint16_t             lun;
  uint16_t             rw_lun;
  uint32_t             timer;
}
MSC_HandleTypeDef;




 





 





 


 




 



 


 



 
extern USBH_ClassTypeDef  USBH_msc;




 



 
uint8_t USBH_MSC_IsReady(USBH_HandleTypeDef *phost);
uint8_t USBH_MSC_GetMaxLUN(USBH_HandleTypeDef *phost);
uint8_t USBH_MSC_UnitIsReady(USBH_HandleTypeDef *phost, uint8_t lun);

USBH_StatusTypeDef USBH_MSC_GetLUNInfo(USBH_HandleTypeDef *phost, uint8_t lun,
                                       MSC_LUNTypeDef *info);

USBH_StatusTypeDef USBH_MSC_Read(USBH_HandleTypeDef *phost, uint8_t lun,
                                 uint32_t address, uint8_t *pbuf, uint32_t length);

USBH_StatusTypeDef USBH_MSC_Write(USBH_HandleTypeDef *phost, uint8_t lun,
                                  uint32_t address, uint8_t *pbuf, uint32_t length);


 










 



 



 



 



#line 33 "../../sPlc/sPlc.h"
#line 34 "../../sPlc/sPlc.h"
#line 35 "../../sPlc/sPlc.h"
#line 1 "../Middlewares/ST/STM32_USB_Host_Library/Class/AUDIO/Inc/usbh_audio.h"
















 

 







 
#line 29 "../Middlewares/ST/STM32_USB_Host_Library/Class/AUDIO/Inc/usbh_audio.h"



 



 



 




 




 

 
typedef enum
{
  AUDIO_INIT = 0,
  AUDIO_IDLE,
  AUDIO_CS_REQUESTS,
  AUDIO_SET_DEFAULT_FEATURE_UNIT,
  AUDIO_SET_INTERFACE,
  AUDIO_SET_STREAMING_INTERFACE,
  AUDIO_SET_CUR1,
  AUDIO_GET_MIN,
  AUDIO_GET_MAX,
  AUDIO_GET_RES,
  AUDIO_GET_CUR1,
  AUDIO_SET_CUR2,
  AUDIO_GET_CUR2,
  AUDIO_SET_CUR3,
  AUDIO_SET_INTERFACE0,
  AUDIO_SET_INTERFACE1,
  AUDIO_SET_INTERFACE2,
  AUDIO_ISOC_OUT,
  AUDIO_ISOC_IN,
  AUDIO_ISOC_POLL,
  AUDIO_ERROR,
}
AUDIO_StateTypeDef;

typedef enum
{
  AUDIO_REQ_INIT = 1,
  AUDIO_REQ_IDLE,
  AUDIO_REQ_SET_DEFAULT_IN_INTERFACE,
  AUDIO_REQ_SET_DEFAULT_OUT_INTERFACE,
  AUDIO_REQ_SET_IN_INTERFACE,
  AUDIO_REQ_SET_OUT_INTERFACE,
  AUDIO_REQ_CS_REQUESTS,
}
AUDIO_ReqStateTypeDef;

typedef enum
{
  AUDIO_REQ_SET_VOLUME = 1,
  AUDIO_REQ_SET_MUTE,
  AUDIO_REQ_GET_CURR_VOLUME,
  AUDIO_REQ_GET_MIN_VOLUME,
  AUDIO_REQ_GET_MAX_VOLUME,
  AUDIO_REQ_GET_VOLUME,
  AUDIO_REQ_GET_RESOLUTION,
  AUDIO_REQ_CS_IDLE,
}
AUDIO_CSReqStateTypeDef;

typedef enum
{
  AUDIO_PLAYBACK_INIT = 1,
  AUDIO_PLAYBACK_SET_EP,
  AUDIO_PLAYBACK_SET_EP_FREQ,
  AUDIO_PLAYBACK_PLAY,
  AUDIO_PLAYBACK_IDLE,
}
AUDIO_PlayStateTypeDef;

typedef enum
{
  VOLUME_UP = 1,
  VOLUME_DOWN = 2,
}
AUDIO_VolumeCtrlTypeDef;

typedef enum
{
  AUDIO_CONTROL_INIT = 1,
  AUDIO_CONTROL_CHANGE,
  AUDIO_CONTROL_IDLE,
  AUDIO_CONTROL_VOLUME_UP,
  AUDIO_CONTROL_VOLUME_DOWN,
}
AUDIO_ControlStateTypeDef;


typedef enum
{
  AUDIO_DATA_START_OUT = 1,
  AUDIO_DATA_OUT,
}
AUDIO_ProcessingTypeDef;

 
typedef struct
{
  uint8_t   Channels;
  uint8_t   Bits;
  uint32_t  SampleRate;
}
AUDIO_FormatTypeDef;

typedef struct
{
  uint8_t              Ep;
  uint16_t             EpSize;
  uint8_t              AltSettings;
  uint8_t              interface;
  uint8_t              valid;
  uint16_t             Poll;
}
AUDIO_STREAMING_IN_HandleTypeDef;

typedef struct
{
  uint8_t              Ep;
  uint16_t             EpSize;
  uint8_t              AltSettings;
  uint8_t              interface;
  uint8_t              valid;
  uint16_t             Poll;
}
AUDIO_STREAMING_OUT_HandleTypeDef;


typedef struct
{
  uint8_t              mute;
  uint32_t             volumeMin;
  uint32_t             volumeMax;
  uint32_t             volume;
  uint32_t             resolution;
}
AUDIO_ControlAttributeTypeDef;

typedef struct
{

  uint8_t              Ep;
  uint16_t             EpSize;
  uint8_t              interface;
  uint8_t              AltSettings;
  uint8_t              supported;

  uint8_t              Pipe;
  uint8_t              Poll;
  uint32_t             timer;

  uint8_t              asociated_as;
  uint8_t              asociated_mixer;
  uint8_t              asociated_selector;
  uint8_t              asociated_feature;
  uint8_t              asociated_terminal;
  uint8_t              asociated_channels;

  uint32_t             frequency;
  uint8_t              *buf;
  uint8_t              *cbuf;
  uint32_t             partial_ptr;

  uint32_t             global_ptr;
  uint16_t             frame_length;
  uint32_t             total_length;

  AUDIO_ControlAttributeTypeDef attribute;
}
AUDIO_InterfaceStreamPropTypeDef;

typedef struct
{

  uint8_t              Ep;
  uint16_t             EpSize;
  uint8_t              interface;
  uint8_t              supported;

  uint8_t              Pipe;
  uint8_t              Poll;
  uint32_t             timer;
}
AUDIO_InterfaceControlPropTypeDef;


#line 237 "../Middlewares/ST/STM32_USB_Host_Library/Class/AUDIO/Inc/usbh_audio.h"









 
typedef struct
{
  uint8_t bLength;
  uint8_t bDescriptorType;
  uint8_t bDescriptorSubtype;
  uint8_t bTerminalLink;
  uint8_t bDelay;
  uint8_t wFormatTag[2];
}
AUDIO_ASGeneralDescTypeDef;

 
typedef struct
{
  uint8_t bLength;
  uint8_t bDescriptorType;
  uint8_t bDescriptorSubtype;
  uint8_t bFormatType;
  uint8_t bNrChannels;
  uint8_t bSubframeSize;
  uint8_t bBitResolution;
  uint8_t bSamFreqType;
  uint8_t tSamFreq[5U][3];
}
AUDIO_ASFormatTypeDescTypeDef;

 
typedef struct
{
  AUDIO_ASGeneralDescTypeDef      *GeneralDesc;
  AUDIO_ASFormatTypeDescTypeDef   *FormatTypeDesc;
}
AUDIO_ASDescTypeDef;

 

typedef struct
{
  uint8_t  bLength;
  uint8_t  bDescriptorType;
  uint8_t  bDescriptorSubtype;
  uint8_t  bcdADC[2];
  uint8_t  wTotalLength[2];
  uint8_t  bInCollection;
  uint8_t  baInterfaceNr[5U];
}
AUDIO_HeaderDescTypeDef;

 
typedef struct
{
  uint8_t  bLength;
  uint8_t  bDescriptorType;
  uint8_t  bDescriptorSubtype;
  uint8_t  bTerminalID;
  uint8_t  wTerminalType[2];
  uint8_t  bAssocTerminal;
  uint8_t  bNrChannels;
  uint8_t  wChannelConfig[2];
  uint8_t  iChannelNames;
  uint8_t  iTerminal;
}
AUDIO_ITDescTypeDef;

 
typedef struct
{
  uint8_t  bLength;
  uint8_t  bDescriptorType;
  uint8_t  bDescriptorSubtype;
  uint8_t  bTerminalID;
  uint8_t  wTerminalType[2];
  uint8_t  bAssocTerminal;
  uint8_t  bSourceID;
  uint8_t  iTerminal;
}
AUDIO_OTDescTypeDef;

 
typedef struct
{
  uint8_t  bLength;
  uint8_t  bDescriptorType;
  uint8_t  bDescriptorSubtype;
  uint8_t  bUnitID;
  uint8_t  bSourceID;
  uint8_t  bControlSize;
  uint8_t  bmaControls[5U][2];
}
AUDIO_FeatureDescTypeDef;


 
typedef struct
{
  uint8_t  bLength;
  uint8_t  bDescriptorType;
  uint8_t  bDescriptorSubtype;
  uint8_t  bUnitID;
  uint8_t  bNrInPins;
  uint8_t  bSourceID0;
  uint8_t  bSourceID1;
  uint8_t  bNrChannels;
  uint8_t  bmChannelsConfig[2];
  uint8_t iChannelsNames;
  uint8_t bmaControls;
  uint8_t iMixer;
}
AUDIO_MixerDescTypeDef;



 
typedef struct
{
  uint8_t  bLength;
  uint8_t  bDescriptorType;
  uint8_t  bDescriptorSubtype;
  uint8_t  bUnitID;
  uint8_t  bNrInPins;
  uint8_t  bSourceID0;
  uint8_t  iSelector;
}
AUDIO_SelectorDescTypeDef;

 
typedef struct
{
  AUDIO_HeaderDescTypeDef   *HeaderDesc;
  AUDIO_ITDescTypeDef       *InputTerminalDesc [4U];
  AUDIO_OTDescTypeDef       *OutputTerminalDesc[4U];
  AUDIO_FeatureDescTypeDef  *FeatureUnitDesc   [4U];
  AUDIO_MixerDescTypeDef    *MixerUnitDesc     [4U];
  AUDIO_SelectorDescTypeDef *SelectorUnitDesc  [4U];
}
AUDIO_ACDescTypeDef;

 

typedef struct
{
  AUDIO_ACDescTypeDef   cs_desc;  
  AUDIO_ASDescTypeDef   as_desc[5U];

  uint16_t ASNum;
  uint16_t InputTerminalNum;
  uint16_t OutputTerminalNum;
  uint16_t FeatureUnitNum;
  uint16_t SelectorUnitNum;
  uint16_t MixerUnitNum;
}
AUDIO_ClassSpecificDescTypedef;


typedef struct _AUDIO_Process
{
  AUDIO_ReqStateTypeDef              req_state;
  AUDIO_CSReqStateTypeDef            cs_req_state;
  AUDIO_PlayStateTypeDef             play_state;
  AUDIO_ControlStateTypeDef          control_state;
  AUDIO_ProcessingTypeDef            processing_state;

  AUDIO_STREAMING_IN_HandleTypeDef   stream_in[5U];
  AUDIO_STREAMING_OUT_HandleTypeDef  stream_out[5U];
  AUDIO_ClassSpecificDescTypedef     class_desc;

  AUDIO_InterfaceStreamPropTypeDef   headphone;
  AUDIO_InterfaceStreamPropTypeDef   microphone;
  AUDIO_InterfaceControlPropTypeDef  control;
  uint16_t                            mem [8];
  uint8_t                            temp_feature;
  uint8_t                            temp_channels;
}
AUDIO_HandleTypeDef;



 



 


 


 







 
#line 451 "../Middlewares/ST/STM32_USB_Host_Library/Class/AUDIO/Inc/usbh_audio.h"

 




 
#line 469 "../Middlewares/ST/STM32_USB_Host_Library/Class/AUDIO/Inc/usbh_audio.h"

 




 




 


 









#line 503 "../Middlewares/ST/STM32_USB_Host_Library/Class/AUDIO/Inc/usbh_audio.h"



 




 


 






 



 


 



 
extern USBH_ClassTypeDef  AUDIO_Class;



 



 
USBH_StatusTypeDef USBH_AUDIO_SetFrequency(USBH_HandleTypeDef *phost,
                                           uint16_t SampleRate,
                                           uint8_t NbrChannels,
                                           uint8_t BitPerSample);

USBH_StatusTypeDef USBH_AUDIO_Play(USBH_HandleTypeDef *phost, uint8_t *buf, uint32_t length);
USBH_StatusTypeDef USBH_AUDIO_Stop(USBH_HandleTypeDef *phost);
USBH_StatusTypeDef USBH_AUDIO_Suspend(USBH_HandleTypeDef *phost);
USBH_StatusTypeDef USBH_AUDIO_Resume(USBH_HandleTypeDef *phost);
USBH_StatusTypeDef USBH_AUDIO_SetVolume(USBH_HandleTypeDef *phost, AUDIO_VolumeCtrlTypeDef volume_ctl);
USBH_StatusTypeDef USBH_AUDIO_ChangeOutBuffer(USBH_HandleTypeDef *phost, uint8_t *buf);
int32_t            USBH_AUDIO_GetOutOffset(USBH_HandleTypeDef *phost);

void        USBH_AUDIO_FrequencySet(USBH_HandleTypeDef *phost);


void        USBH_AUDIO_BufferEmptyCallback(USBH_HandleTypeDef *phost);


 









 



 



 



 

#line 36 "../../sPlc/sPlc.h"
#line 1 "../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc/usbh_cdc.h"
















 

 







 
#line 29 "../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc/usbh_cdc.h"




 



 



 




 




 



 


 
#line 67 "../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc/usbh_cdc.h"


 








 






#line 91 "../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc/usbh_cdc.h"






#line 108 "../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc/usbh_cdc.h"













 








 



 

 
typedef enum
{
  CDC_IDLE = 0U,
  CDC_SEND_DATA,
  CDC_SEND_DATA_WAIT,
  CDC_RECEIVE_DATA,
  CDC_RECEIVE_DATA_WAIT,
}
CDC_DataStateTypeDef;

typedef enum
{
  CDC_IDLE_STATE = 0U,
  CDC_SET_LINE_CODING_STATE,
  CDC_GET_LAST_LINE_CODING_STATE,
  CDC_TRANSFER_DATA,
  CDC_ERROR_STATE,
}
CDC_StateTypeDef;


 
typedef union _CDC_LineCodingStructure
{
  uint8_t Array[0x07U];

  struct
  {

    uint32_t             dwDTERate;      
    uint8_t              bCharFormat;   


 
    uint8_t              bParityType;   




 
    uint8_t                bDataBits;      
  } b;
}
CDC_LineCodingTypeDef;

















 
typedef struct _FunctionalDescriptorHeader
{
  uint8_t     bLength;             
  uint8_t     bDescriptorType;     
  uint8_t     bDescriptorSubType;  
  uint16_t    bcdCDC;             

 
}
CDC_HeaderFuncDesc_TypeDef;






























 
typedef struct _CallMgmtFunctionalDescriptor
{
  uint8_t    bLength;             
  uint8_t    bDescriptorType;     
  uint8_t    bDescriptorSubType;  
  uint8_t    bmCapabilities;       
  uint8_t    bDataInterface;       
}
CDC_CallMgmtFuncDesc_TypeDef;




























 
typedef struct _AbstractCntrlMgmtFunctionalDescriptor
{
  uint8_t    bLength;             
  uint8_t    bDescriptorType;     
  uint8_t    bDescriptorSubType; 
 
  uint8_t    bmCapabilities;       
}
CDC_AbstCntrlMgmtFuncDesc_TypeDef;













 
typedef struct _UnionFunctionalDescriptor
{
  uint8_t    bLength;             
  uint8_t    bDescriptorType;     
  uint8_t    bDescriptorSubType;  
  uint8_t    bMasterInterface;   
 
  uint8_t    bSlaveInterface0;    
}
CDC_UnionFuncDesc_TypeDef;

typedef struct _USBH_CDCInterfaceDesc
{
  CDC_HeaderFuncDesc_TypeDef           CDC_HeaderFuncDesc;
  CDC_CallMgmtFuncDesc_TypeDef         CDC_CallMgmtFuncDesc;
  CDC_AbstCntrlMgmtFuncDesc_TypeDef    CDC_AbstCntrlMgmtFuncDesc;
  CDC_UnionFuncDesc_TypeDef            CDC_UnionFuncDesc;
}
CDC_InterfaceDesc_Typedef;


 
typedef struct
{
  uint8_t              NotifPipe;
  uint8_t              NotifEp;
  uint8_t              buff[8];
  uint16_t             NotifEpSize;
}
CDC_CommItfTypedef;

typedef struct
{
  uint8_t              InPipe;
  uint8_t              OutPipe;
  uint8_t              OutEp;
  uint8_t              InEp;
  uint8_t              buff[8];
  uint16_t             OutEpSize;
  uint16_t             InEpSize;
}
CDC_DataItfTypedef;

 
typedef struct _CDC_Process
{
  CDC_CommItfTypedef                CommItf;
  CDC_DataItfTypedef                DataItf;
  uint8_t                           *pTxData;
  uint8_t                           *pRxData;
  uint32_t                           TxDataLength;
  uint32_t                           RxDataLength;
  CDC_InterfaceDesc_Typedef         CDC_Desc;
  CDC_LineCodingTypeDef             LineCoding;
  CDC_LineCodingTypeDef             *pUserLineCoding;
  CDC_StateTypeDef                  state;
  CDC_DataStateTypeDef              data_tx_state;
  CDC_DataStateTypeDef              data_rx_state;
  uint8_t                           Rx_Poll;
}
CDC_HandleTypeDef;



 



 



 



 


 



 
extern USBH_ClassTypeDef  CDC_Class;




 



 

USBH_StatusTypeDef  USBH_CDC_SetLineCoding(USBH_HandleTypeDef *phost,
                                           CDC_LineCodingTypeDef *linecoding);

USBH_StatusTypeDef  USBH_CDC_GetLineCoding(USBH_HandleTypeDef *phost,
                                           CDC_LineCodingTypeDef *linecoding);

USBH_StatusTypeDef  USBH_CDC_Transmit(USBH_HandleTypeDef *phost,
                                      uint8_t *pbuff,
                                      uint32_t length);

USBH_StatusTypeDef  USBH_CDC_Receive(USBH_HandleTypeDef *phost,
                                     uint8_t *pbuff,
                                     uint32_t length);


uint16_t            USBH_CDC_GetLastReceivedDataSize(USBH_HandleTypeDef *phost);

USBH_StatusTypeDef  USBH_CDC_Stop(USBH_HandleTypeDef *phost);

void USBH_CDC_LineCodingChanged(USBH_HandleTypeDef *phost);

void USBH_CDC_TransmitCallback(USBH_HandleTypeDef *phost);

void USBH_CDC_ReceiveCallback(USBH_HandleTypeDef *phost);



 









 



 



 



 

#line 37 "../../sPlc/sPlc.h"
#line 38 "../../sPlc/sPlc.h"
#line 1 "../Middlewares/ST/STM32_USB_Host_Library/Class/HID/Inc/usbh_hid.h"
















 

 







 
#line 29 "../Middlewares/ST/STM32_USB_Host_Library/Class/HID/Inc/usbh_hid.h"
#line 1 "../Middlewares/ST/STM32_USB_Host_Library/Class/HID/Inc/usbh_hid_mouse.h"
















 

 







 
#line 1 "../Middlewares/ST/STM32_USB_Host_Library/Class/HID/Inc/usbh_hid.h"
















 

 
#line 326 "../Middlewares/ST/STM32_USB_Host_Library/Class/HID/Inc/usbh_hid.h"



 



 



 



 

#line 29 "../Middlewares/ST/STM32_USB_Host_Library/Class/HID/Inc/usbh_hid_mouse.h"



 



 



 




 




 

typedef struct _HID_MOUSE_Info
{
  uint8_t x;
  uint8_t y;
  uint8_t buttons[3];
}
HID_MOUSE_Info_TypeDef;



 



 





 



 


 



 


 



 
USBH_StatusTypeDef USBH_HID_MouseInit(USBH_HandleTypeDef *phost);
HID_MOUSE_Info_TypeDef *USBH_HID_GetMouseInfo(USBH_HandleTypeDef *phost);



 









 



 



 



 

#line 30 "../Middlewares/ST/STM32_USB_Host_Library/Class/HID/Inc/usbh_hid.h"
#line 1 "../Middlewares/ST/STM32_USB_Host_Library/Class/HID/Inc/usbh_hid_keybd.h"
















 

 







 
#line 29 "../Middlewares/ST/STM32_USB_Host_Library/Class/HID/Inc/usbh_hid_keybd.h"
#line 1 "../Middlewares/ST/STM32_USB_Host_Library/Class/HID/Inc/usbh_hid_keybd.h"
















 

 
#line 304 "../Middlewares/ST/STM32_USB_Host_Library/Class/HID/Inc/usbh_hid_keybd.h"



 



 



 



 

#line 30 "../Middlewares/ST/STM32_USB_Host_Library/Class/HID/Inc/usbh_hid_keybd.h"



 



 



 




 




 




#line 275 "../Middlewares/ST/STM32_USB_Host_Library/Class/HID/Inc/usbh_hid_keybd.h"

typedef struct
{
  uint8_t state;
  uint8_t lctrl;
  uint8_t lshift;
  uint8_t lalt;
  uint8_t lgui;
  uint8_t rctrl;
  uint8_t rshift;
  uint8_t ralt;
  uint8_t rgui;
  uint8_t keys[6];
}
HID_KEYBD_Info_TypeDef;

USBH_StatusTypeDef USBH_HID_KeybdInit(USBH_HandleTypeDef *phost);
HID_KEYBD_Info_TypeDef *USBH_HID_GetKeybdInfo(USBH_HandleTypeDef *phost);
uint8_t USBH_HID_GetASCIICode(HID_KEYBD_Info_TypeDef *info);



 









 



 



 



 

#line 31 "../Middlewares/ST/STM32_USB_Host_Library/Class/HID/Inc/usbh_hid.h"



 



 



 




 




 






















#line 87 "../Middlewares/ST/STM32_USB_Host_Library/Class/HID/Inc/usbh_hid.h"


#line 99 "../Middlewares/ST/STM32_USB_Host_Library/Class/HID/Inc/usbh_hid.h"


 
typedef enum
{
  USBH_HID_INIT = 0,
  USBH_HID_IDLE,
  USBH_HID_SEND_DATA,
  USBH_HID_BUSY,
  USBH_HID_GET_DATA,
  USBH_HID_SYNC,
  USBH_HID_POLL,
  USBH_HID_ERROR,
}
USBH_HID_StateTypeDef;

typedef enum
{
  USBH_HID_REQ_INIT = 0,
  USBH_HID_REQ_IDLE,
  USBH_HID_REQ_GET_REPORT_DESC,
  USBH_HID_REQ_GET_HID_DESC,
  USBH_HID_REQ_SET_IDLE,
  USBH_HID_REQ_SET_PROTOCOL,
  USBH_HID_REQ_SET_REPORT,

}
HID_CtlStateTypeDef;

typedef enum
{
  HID_MOUSE    = 0x01,
  HID_KEYBOARD = 0x02,
  HID_UNKNOWN = 0xFF,
}
HID_TypeTypeDef;


typedef  struct  _HID_ReportData
{
  uint8_t   ReportID;
  uint8_t   ReportType;
  uint16_t  UsagePage;
  uint32_t  Usage[10U];
  uint32_t  NbrUsage;
  uint32_t  UsageMin;
  uint32_t  UsageMax;
  int32_t   LogMin;
  int32_t   LogMax;
  int32_t   PhyMin;
  int32_t   PhyMax;
  int32_t   UnitExp;
  uint32_t  Unit;
  uint32_t  ReportSize;
  uint32_t  ReportCnt;
  uint32_t  Flag;
  uint32_t  PhyUsage;
  uint32_t  AppUsage;
  uint32_t  LogUsage;
}
HID_ReportDataTypeDef;

typedef  struct  _HID_ReportIDTypeDef
{
  uint8_t  Size;          
  uint8_t  ReportID;      
  uint8_t  Type;          
} HID_ReportIDTypeDef;

typedef struct  _HID_CollectionTypeDef
{
  uint32_t                       Usage;
  uint8_t                        Type;
  struct _HID_CollectionTypeDef  *NextPtr;
} HID_CollectionTypeDef;


typedef  struct  _HID_AppCollectionTypeDef
{
  uint32_t               Usage;
  uint8_t                Type;
  uint8_t                NbrReportFmt;
  HID_ReportDataTypeDef  ReportData[10U];
} HID_AppCollectionTypeDef;


typedef struct _HIDDescriptor
{
  uint8_t   bLength;
  uint8_t   bDescriptorType;
  uint16_t  bcdHID;                
  uint8_t   bCountryCode;         
  uint8_t   bNumDescriptors;      
  uint8_t   bReportDescriptorType;     
  uint16_t  wItemLength;           
}
HID_DescTypeDef;


typedef struct
{
  uint8_t  *buf;
  uint16_t  head;
  uint16_t tail;
  uint16_t size;
  uint8_t  lock;
} FIFO_TypeDef;


 
typedef struct _HID_Process
{
  uint8_t              OutPipe;
  uint8_t              InPipe;
  USBH_HID_StateTypeDef     state;
  uint8_t              OutEp;
  uint8_t              InEp;
  HID_CtlStateTypeDef  ctl_state;
  FIFO_TypeDef         fifo;
  uint8_t              *pData;
  uint16_t             length;
  uint8_t              ep_addr;
  uint16_t             poll;
  uint32_t             timer;
  uint8_t              DataReady;
  HID_DescTypeDef      HID_Desc;
  USBH_StatusTypeDef(* Init)(USBH_HandleTypeDef *phost);
}
HID_HandleTypeDef;



 



 

#line 243 "../Middlewares/ST/STM32_USB_Host_Library/Class/HID/Inc/usbh_hid.h"




 


 







 



 


 



 
extern USBH_ClassTypeDef  HID_Class;



 



 

USBH_StatusTypeDef USBH_HID_SetReport(USBH_HandleTypeDef *phost,
                                      uint8_t reportType,
                                      uint8_t reportId,
                                      uint8_t *reportBuff,
                                      uint8_t reportLen);

USBH_StatusTypeDef USBH_HID_GetReport(USBH_HandleTypeDef *phost,
                                      uint8_t reportType,
                                      uint8_t reportId,
                                      uint8_t *reportBuff,
                                      uint8_t reportLen);

USBH_StatusTypeDef USBH_HID_GetHIDReportDescriptor(USBH_HandleTypeDef *phost,
                                                   uint16_t length);

USBH_StatusTypeDef USBH_HID_GetHIDDescriptor(USBH_HandleTypeDef *phost,
                                             uint16_t length);

USBH_StatusTypeDef USBH_HID_SetIdle(USBH_HandleTypeDef *phost,
                                    uint8_t duration,
                                    uint8_t reportId);

USBH_StatusTypeDef USBH_HID_SetProtocol(USBH_HandleTypeDef *phost,
                                        uint8_t protocol);

void USBH_HID_EventCallback(USBH_HandleTypeDef *phost);

HID_TypeTypeDef USBH_HID_GetDeviceType(USBH_HandleTypeDef *phost);

uint8_t USBH_HID_GetPollInterval(USBH_HandleTypeDef *phost);

void USBH_HID_FifoInit(FIFO_TypeDef *f, uint8_t *buf, uint16_t size);

uint16_t  USBH_HID_FifoRead(FIFO_TypeDef *f, void *buf, uint16_t  nbytes);

uint16_t  USBH_HID_FifoWrite(FIFO_TypeDef *f, void *buf, uint16_t nbytes);



 









 



 



 



 

#line 39 "../../sPlc/sPlc.h"
#line 1 "../Middlewares/ST/STM32_USB_Host_Library/Class/MTP/Inc/usbh_mtp.h"
















 

 







 
#line 1 "../Middlewares/ST/STM32_USB_Host_Library/Class/MTP/Inc/usbh_mtp_ptp.h"
















 

 







 
#line 29 "../Middlewares/ST/STM32_USB_Host_Library/Class/MTP/Inc/usbh_mtp_ptp.h"



 



 



 




 


 

 
#line 80 "../Middlewares/ST/STM32_USB_Host_Library/Class/MTP/Inc/usbh_mtp_ptp.h"

 
#line 91 "../Middlewares/ST/STM32_USB_Host_Library/Class/MTP/Inc/usbh_mtp_ptp.h"

 
#line 105 "../Middlewares/ST/STM32_USB_Host_Library/Class/MTP/Inc/usbh_mtp_ptp.h"


 

 
#line 143 "../Middlewares/ST/STM32_USB_Host_Library/Class/MTP/Inc/usbh_mtp_ptp.h"
 




 







 
#line 171 "../Middlewares/ST/STM32_USB_Host_Library/Class/MTP/Inc/usbh_mtp_ptp.h"

 







 

typedef enum
{
  PTP_REQ_IDLE = 0,
  PTP_REQ_SEND,
  PTP_REQ_WAIT,
  PTP_REQ_ERROR,
}
PTP_RequestStateTypeDef;

typedef enum
{
  PTP_IDLE = 0,
  PTP_OP_REQUEST_STATE,
  PTP_OP_REQUEST_WAIT_STATE,
  PTP_DATA_OUT_PHASE_STATE,
  PTP_DATA_OUT_PHASE_WAIT_STATE,
  PTP_DATA_IN_PHASE_STATE,
  PTP_DATA_IN_PHASE_WAIT_STATE,
  PTP_RESPONSE_STATE,
  PTP_RESPONSE_WAIT_STATE,
  PTP_ERROR,
}
PTP_ProcessStateTypeDef;

 
typedef struct
{
  uint16_t Code;
  uint32_t SessionID;
  uint32_t Transaction_ID;
   
  uint32_t Param1;
  uint32_t Param2;
  uint32_t Param3;
   
  uint32_t Param4;
  uint32_t Param5;
   
  uint8_t Nparam;
}
PTP_ContainerTypedef;

#line 231 "../Middlewares/ST/STM32_USB_Host_Library/Class/MTP/Inc/usbh_mtp_ptp.h"

typedef struct
{
  uint32_t length;
  uint16_t type;
  uint16_t code;
  uint32_t trans_id;
  uint32_t param1;
  uint32_t param2;
  uint32_t param3;
  uint32_t param4;
  uint32_t param5;
}
PTP_RespContainerTypedef;


typedef struct
{
  uint32_t length;
  uint16_t type;
  uint16_t code;
  uint32_t trans_id;
  uint32_t param1;
  uint32_t param2;
  uint32_t param3;
  uint32_t param4;
  uint32_t param5;
}
PTP_OpContainerTypedef;

typedef struct
{
  uint32_t length;
  uint16_t type;
  uint16_t code;
  uint32_t trans_id;
  union
  {
    struct
    {
      uint32_t param1;
      uint32_t param2;
      uint32_t param3;
      uint32_t param4;
      uint32_t param5;
    } params;
    uint8_t  data[(1024U - ((2U * sizeof(uint32_t)) + (2U * sizeof(uint16_t))))];
  } payload;
}
PTP_DataContainerTypedef;

 
typedef struct
{
  uint32_t length;
  uint16_t type;
  uint16_t code;
  uint32_t trans_id;
  uint32_t param1;
  uint32_t param2;
  uint32_t param3;
}
PTP_EventContainerTypedef;

 
typedef struct
{
  PTP_ProcessStateTypeDef      state;
  PTP_RequestStateTypeDef      req_state;
  PTP_OpContainerTypedef       op_container;
  PTP_DataContainerTypedef     data_container;
  PTP_RespContainerTypedef     resp_container;

   
  uint32_t  transaction_id;

   
  uint32_t  session_id;

   
  uint32_t  flags;

   

   
  uint8_t *data_ptr;

   
  uint32_t  data_length;

   
  uint32_t  data_packet;

   
  uint32_t  iteration;

   
  uint32_t   data_packet_counter;

   

   
  uint8_t *object_ptr;

}
PTP_HandleTypeDef;

 
#line 345 "../Middlewares/ST/STM32_USB_Host_Library/Class/MTP/Inc/usbh_mtp_ptp.h"

 
#line 353 "../Middlewares/ST/STM32_USB_Host_Library/Class/MTP/Inc/usbh_mtp_ptp.h"
 
typedef struct
{
  uint16_t StandardVersion;
  uint32_t VendorExtensionID;
  uint16_t VendorExtensionVersion;
  uint8_t  VendorExtensionDesc[255U];
  uint16_t FunctionalMode;
  uint32_t OperationsSupported_len;
  uint16_t OperationsSupported[100U];
  uint32_t EventsSupported_len;
  uint16_t EventsSupported[100U];
  uint32_t DevicePropertiesSupported_len;
  uint16_t DevicePropertiesSupported[100U];
  uint32_t CaptureFormats_len;
  uint16_t CaptureFormats[100U];
  uint32_t ImageFormats_len;
  uint16_t ImageFormats[100U];
  uint8_t  Manufacturer[255U];
  uint8_t  Model[255U];
  uint8_t  DeviceVersion[255U];
  uint8_t  SerialNumber[255U];
}
PTP_DeviceInfoTypedef;


 
typedef struct
{
  uint32_t n;
  uint32_t Storage [5];
}
PTP_StorageIDsTypedef;

 

#line 396 "../Middlewares/ST/STM32_USB_Host_Library/Class/MTP/Inc/usbh_mtp_ptp.h"


 







 






 





typedef struct
{
  uint16_t StorageType;
  uint16_t FilesystemType;
  uint16_t AccessCapability;
  uint64_t MaxCapability;
  uint64_t FreeSpaceInBytes;
  uint32_t FreeSpaceInImages;
  uint8_t  StorageDescription[255U];
  uint8_t  VolumeLabel[255U];
}
PTP_StorageInfoTypedef;

 

 
#line 450 "../Middlewares/ST/STM32_USB_Host_Library/Class/MTP/Inc/usbh_mtp_ptp.h"
 
#line 467 "../Middlewares/ST/STM32_USB_Host_Library/Class/MTP/Inc/usbh_mtp_ptp.h"
 


 
#line 528 "../Middlewares/ST/STM32_USB_Host_Library/Class/MTP/Inc/usbh_mtp_ptp.h"

 
#line 697 "../Middlewares/ST/STM32_USB_Host_Library/Class/MTP/Inc/usbh_mtp_ptp.h"

 



 
#line 711 "../Middlewares/ST/STM32_USB_Host_Library/Class/MTP/Inc/usbh_mtp_ptp.h"


typedef struct
{
  uint32_t n;
  uint32_t Handler[0x255U];
}
PTP_ObjectHandlesTypedef;


#line 738 "../Middlewares/ST/STM32_USB_Host_Library/Class/MTP/Inc/usbh_mtp_ptp.h"

typedef struct
{
  uint32_t StorageID;
  uint16_t ObjectFormat;
  uint16_t ProtectionStatus;
  
 
  uint64_t ObjectCompressedSize;
  uint16_t ThumbFormat;
  uint32_t ThumbCompressedSize;
  uint32_t ThumbPixWidth;
  uint32_t ThumbPixHeight;
  uint32_t ImagePixWidth;
  uint32_t ImagePixHeight;
  uint32_t ImageBitDepth;
  uint32_t ParentObject;
  uint16_t AssociationType;
  uint32_t AssociationDesc;
  uint32_t SequenceNumber;
  uint8_t  Filename[255U];
  uint32_t CaptureDate;
  uint32_t ModificationDate;
  uint8_t  Keywords[255U];
}
PTP_ObjectInfoTypedef;

 

typedef union  _PTP_PropertyValueTypedef
{
  char  str[255U];
  uint8_t u8;
  int8_t i8;
  uint16_t u16;
  int16_t i16;
  uint32_t u32;
  int32_t i32;
  uint64_t u64;
  int64_t i64;
  struct array
  {
    uint32_t count;
    union _PTP_PropertyValueTypedef *v;
  } a;
} PTP_PropertyValueTypedef;

typedef struct
{
  PTP_PropertyValueTypedef MinimumValue;
  PTP_PropertyValueTypedef MaximumValue;
  PTP_PropertyValueTypedef StepSize;
}
PTP_PropDescRangeFormTypedef;

 

typedef struct
{
  uint16_t NumberOfValues;
  PTP_PropertyValueTypedef SupportedValue[100U];
}
PTP_PropDescEnumFormTypedef;

 





typedef struct
{
  uint16_t    ObjectPropertyCode;
  uint16_t    DataType;
  uint8_t     GetSet;
  PTP_PropertyValueTypedef FactoryDefaultValue;
  uint32_t    GroupCode;
  uint8_t     FormFlag;
  union
  {
    PTP_PropDescEnumFormTypedef Enum;
    PTP_PropDescRangeFormTypedef  Range;
  } FORM;
}
PTP_ObjectPropDescTypeDef;

 
typedef struct
{
  uint16_t   property;
  uint16_t   datatype;
  uint32_t   ObjectHandle;
  PTP_PropertyValueTypedef propval;
}
MTP_PropertiesTypedef;


 





 
#line 850 "../Middlewares/ST/STM32_USB_Host_Library/Class/MTP/Inc/usbh_mtp_ptp.h"

 






 

typedef struct
{
  uint16_t  DevicePropertyCode;
  uint16_t  DataType;
  uint8_t   GetSet;
  PTP_PropertyValueTypedef FactoryDefaultValue;
  PTP_PropertyValueTypedef CurrentValue;
  uint8_t   FormFlag;
  union
  {
    PTP_PropDescEnumFormTypedef  Enum;
    PTP_PropDescRangeFormTypedef  Range;
  } FORM;
}
PTP_DevicePropDescTypdef;

 

#line 889 "../Middlewares/ST/STM32_USB_Host_Library/Class/MTP/Inc/usbh_mtp_ptp.h"



#line 902 "../Middlewares/ST/STM32_USB_Host_Library/Class/MTP/Inc/usbh_mtp_ptp.h"



 

#line 922 "../Middlewares/ST/STM32_USB_Host_Library/Class/MTP/Inc/usbh_mtp_ptp.h"




 



 


 



 



 



 
USBH_StatusTypeDef USBH_PTP_Init(USBH_HandleTypeDef *phost);
USBH_StatusTypeDef USBH_PTP_Process(USBH_HandleTypeDef *phost);

USBH_StatusTypeDef USBH_PTP_SendRequest(USBH_HandleTypeDef *phost, PTP_ContainerTypedef  *req);
USBH_StatusTypeDef USBH_PTP_GetResponse(USBH_HandleTypeDef *phost, PTP_ContainerTypedef  *resp);

USBH_StatusTypeDef USBH_PTP_OpenSession(USBH_HandleTypeDef *phost, uint32_t session);
USBH_StatusTypeDef USBH_PTP_GetDeviceInfo(USBH_HandleTypeDef *phost, PTP_DeviceInfoTypedef *dev_info);
USBH_StatusTypeDef USBH_PTP_GetStorageIds(USBH_HandleTypeDef *phost, PTP_StorageIDsTypedef *storage_ids);

USBH_StatusTypeDef USBH_PTP_GetStorageInfo(USBH_HandleTypeDef *phost,
                                           uint32_t storage_id,
                                           PTP_StorageInfoTypedef *storage_info);

USBH_StatusTypeDef USBH_PTP_GetNumObjects(USBH_HandleTypeDef *phost,
                                          uint32_t storage_id,
                                          uint32_t objectformatcode,
                                          uint32_t associationOH,
                                          uint32_t *numobs);

USBH_StatusTypeDef USBH_PTP_GetObjectHandles(USBH_HandleTypeDef *phost,
                                             uint32_t storage_id,
                                             uint32_t objectformatcode,
                                             uint32_t associationOH,
                                             PTP_ObjectHandlesTypedef *objecthandles);

USBH_StatusTypeDef USBH_PTP_GetObjectInfo(USBH_HandleTypeDef *phost,
                                          uint32_t handle,
                                          PTP_ObjectInfoTypedef *object_info);

USBH_StatusTypeDef USBH_PTP_DeleteObject(USBH_HandleTypeDef *phost,
                                         uint32_t handle,
                                         uint32_t objectformatcode);

USBH_StatusTypeDef USBH_PTP_GetObject(USBH_HandleTypeDef *phost,
                                      uint32_t handle,
                                      uint8_t *object);

USBH_StatusTypeDef USBH_PTP_GetPartialObject(USBH_HandleTypeDef *phost,
                                             uint32_t handle,
                                             uint32_t offset,
                                             uint32_t maxbytes, uint8_t *object,
                                             uint32_t *len);

USBH_StatusTypeDef USBH_PTP_GetObjectPropsSupported(USBH_HandleTypeDef *phost,
                                                    uint16_t ofc,
                                                    uint32_t *propnum,
                                                    uint16_t *props);

USBH_StatusTypeDef USBH_PTP_GetObjectPropDesc(USBH_HandleTypeDef *phost,
                                              uint16_t opc,
                                              uint16_t ofc,
                                              PTP_ObjectPropDescTypeDef *opd);

USBH_StatusTypeDef USBH_PTP_GetObjectPropList(USBH_HandleTypeDef *phost,
                                              uint32_t handle,
                                              MTP_PropertiesTypedef *pprops,
                                              uint32_t *nrofprops);

USBH_StatusTypeDef USBH_PTP_SendObject(USBH_HandleTypeDef *phost,
                                       uint32_t handle,
                                       uint8_t *object,
                                       uint32_t size);

USBH_StatusTypeDef USBH_PTP_GetDevicePropDesc(USBH_HandleTypeDef *phost,
                                              uint16_t propcode,
                                              PTP_DevicePropDescTypdef *devicepropertydesc);



 










 



 



 



 

#line 29 "../Middlewares/ST/STM32_USB_Host_Library/Class/MTP/Inc/usbh_mtp.h"
#line 30 "../Middlewares/ST/STM32_USB_Host_Library/Class/MTP/Inc/usbh_mtp.h"




 



 



 




 




 





 



 
typedef enum
{
  MTP_IDLE = 0,
  MTP_GETDEVICEINFO,
  MTP_OPENSESSION,
  MTP_CLOSESESSION,
  MTP_GETSTORAGEIDS,
  MTP_GETSTORAGEINFO,
}
MTP_StateTypeDef;


typedef enum
{
  MTP_EVENTS_INIT = 0,
  MTP_EVENTS_GETDATA,
}
MTP_EventsStateTypeDef;


typedef struct
{
  MTP_EventsStateTypeDef   state;
  uint32_t timer;
  uint16_t poll;
  PTP_EventContainerTypedef  container;
}
MTP_EventHandleTypedef;

typedef struct
{

  uint32_t        CurrentStorageId;
  uint32_t        ObjectFormatCode;
  uint32_t        CurrentObjectHandler;
  uint8_t         ObjectHandlerNbr;
  uint32_t        Objdepth;
}
MTP_ParamsTypedef;


typedef struct
{
  PTP_DeviceInfoTypedef     devinfo;
  PTP_StorageIDsTypedef     storids;
  PTP_StorageInfoTypedef    storinfo[5];
  PTP_ObjectHandlesTypedef  Handles;
}
MTP_InfoTypedef;

 
typedef struct _MTP_Process
{
  MTP_InfoTypedef       info;
  MTP_ParamsTypedef     params;

  uint8_t               DataInPipe;
  uint8_t               DataOutPipe;
  uint8_t               NotificationPipe;

  uint8_t               DataOutEp;
  uint8_t               DataInEp;
  uint8_t               NotificationEp;

  uint16_t              DataOutEpSize;
  uint16_t              DataInEpSize;
  uint16_t              NotificationEpSize;
  MTP_StateTypeDef      state;
  MTP_EventHandleTypedef events;
  PTP_HandleTypeDef     ptp;
  uint32_t              current_storage_unit;
  uint32_t              is_ready;
}
MTP_HandleTypeDef;






 



 



 



 


 



 
extern USBH_ClassTypeDef  MTP_Class;




 



 
uint8_t            USBH_MTP_IsReady(USBH_HandleTypeDef *phost);
USBH_StatusTypeDef USBH_MTP_SelectStorage(USBH_HandleTypeDef *phost, uint8_t storage_idx);
USBH_StatusTypeDef USBH_MTP_GetNumStorage(USBH_HandleTypeDef *phost, uint8_t *storage_num);
USBH_StatusTypeDef USBH_MTP_GetNumObjects(USBH_HandleTypeDef *phost,
                                          uint32_t storage_idx,
                                          uint32_t objectformatcode,
                                          uint32_t associationOH,
                                          uint32_t *numobs);
USBH_StatusTypeDef USBH_MTP_GetStorageInfo(USBH_HandleTypeDef *phost,
                                           uint8_t storage_idx,
                                           PTP_StorageInfoTypedef *info);

USBH_StatusTypeDef USBH_MTP_GetObjectHandles(USBH_HandleTypeDef *phost,
                                             uint32_t storage_idx,
                                             uint32_t objectformatcode,
                                             uint32_t associationOH,
                                             PTP_ObjectHandlesTypedef *objecthandles);

USBH_StatusTypeDef USBH_MTP_GetObjectInfo(USBH_HandleTypeDef *phost,
                                          uint32_t handle,
                                          PTP_ObjectInfoTypedef *objectinfo);

USBH_StatusTypeDef USBH_MTP_DeleteObject(USBH_HandleTypeDef *phost,
                                         uint32_t handle,
                                         uint32_t objectformatcode);

USBH_StatusTypeDef USBH_MTP_GetObject(USBH_HandleTypeDef *phost,
                                      uint32_t handle,
                                      uint8_t *object);

USBH_StatusTypeDef USBH_MTP_GetPartialObject(USBH_HandleTypeDef *phost,
                                             uint32_t handle,
                                             uint32_t offset,
                                             uint32_t maxbytes,
                                             uint8_t *object,
                                             uint32_t *len);

USBH_StatusTypeDef USBH_MTP_GetObjectPropsSupported(USBH_HandleTypeDef *phost,
                                                    uint16_t ofc,
                                                    uint32_t *propnum,
                                                    uint16_t *props);

USBH_StatusTypeDef USBH_MTP_GetObjectPropDesc(USBH_HandleTypeDef *phost,
                                              uint16_t opc,
                                              uint16_t ofc,
                                              PTP_ObjectPropDescTypeDef *opd);

USBH_StatusTypeDef USBH_MTP_GetObjectPropList(USBH_HandleTypeDef *phost,
                                              uint32_t handle,
                                              MTP_PropertiesTypedef *pprops,
                                              uint32_t *nrofprops);

USBH_StatusTypeDef USBH_MTP_SendObject(USBH_HandleTypeDef *phost,
                                       uint32_t handle,
                                       uint8_t *object,
                                       uint32_t size);

USBH_StatusTypeDef USBH_MTP_GetDevicePropDesc(USBH_HandleTypeDef *phost,
                                              uint16_t propcode,
                                              PTP_DevicePropDescTypdef *devicepropertydesc);

void USBH_MTP_EventsCallback(USBH_HandleTypeDef *phost, uint32_t event, uint32_t param);


 









 



 



 



 

#line 40 "../../sPlc/sPlc.h"
 
#line 1 "../Middlewares/Third_Party/FatFs/src/ff.h"

















 









#line 1 "../Middlewares/Third_Party/FatFs/src/integer.h"
 
 
 




#line 16 "../Middlewares/Third_Party/FatFs/src/integer.h"

 
typedef int				INT;
typedef unsigned int	UINT;

 
typedef unsigned char	BYTE;

 
typedef short			SHORT;
typedef unsigned short	WORD;
typedef unsigned short	WCHAR;

 
typedef long			LONG;
typedef unsigned long	DWORD;

 
typedef unsigned long long QWORD;



#line 29 "../Middlewares/Third_Party/FatFs/src/ff.h"
#line 1 "../FATFS/Target/ffconf.h"
 














 
 






 
#line 26 "../FATFS/Target/ffconf.h"
#line 27 "../FATFS/Target/ffconf.h"
#line 28 "../FATFS/Target/ffconf.h"
#line 29 "../FATFS/Target/ffconf.h"
#line 30 "../FATFS/Target/ffconf.h"
 




 





 








 







 



 


 


 


 



 



 


 



 



























 
















 




 










 







 



 


 

 






 
 







 







 




 










 



 





 




 












 










 





















 

 





#line 30 "../Middlewares/Third_Party/FatFs/src/ff.h"







 

#line 46 "../Middlewares/Third_Party/FatFs/src/ff.h"



 

#line 62 "../Middlewares/Third_Party/FatFs/src/ff.h"
typedef char TCHAR;







 





typedef QWORD FSIZE_t;






 

typedef struct {
	BYTE	fs_type;		 
	BYTE	drv;			 
	BYTE	n_fats;			 
	BYTE	wflag;			 
	BYTE	fsi_flag;		 
	WORD	id;				 
	WORD	n_rootdir;		 
	WORD	csize;			 




	WCHAR*	lfnbuf;			 


	BYTE*	dirbuf;			 


	osMutexId_t	sobj;			 


	DWORD	last_clst;		 
	DWORD	free_clst;		 
#line 118 "../Middlewares/Third_Party/FatFs/src/ff.h"
	DWORD	n_fatent;		 
	DWORD	fsize;			 
	DWORD	volbase;		 
	DWORD	fatbase;		 
	DWORD	dirbase;		 
	DWORD	database;		 
	DWORD	winsect;		 
	BYTE	win[512];	 
} FATFS;



 

typedef struct {
	FATFS*	fs;			 
	WORD	id;			 
	BYTE	attr;		 
	BYTE	stat;		 
	DWORD	sclust;		 
	FSIZE_t	objsize;	 

	DWORD	n_cont;		 
	DWORD	n_frag;		 
	DWORD	c_scl;		 
	DWORD	c_size;		 
	DWORD	c_ofs;		 


	UINT	lockid;		 

} _FDID;



 

typedef struct {
	_FDID	obj;			 
	BYTE	flag;			 
	BYTE	err;			 
	FSIZE_t	fptr;			 
	DWORD	clust;			 
	DWORD	sect;			 

	DWORD	dir_sect;		 
	BYTE*	dir_ptr;		 


	DWORD*	cltbl;			 


	BYTE	buf[512];	 

} FIL;



 

typedef struct {
	_FDID	obj;			 
	DWORD	dptr;			 
	DWORD	clust;			 
	DWORD	sect;			 
	BYTE*	dir;			 
	BYTE	fn[12];			 

	DWORD	blk_ofs;		 


	const TCHAR* pat;		 

} DIR;



 

typedef struct {
	FSIZE_t	fsize;			 
	WORD	fdate;			 
	WORD	ftime;			 
	BYTE	fattrib;		 

	TCHAR	altname[13];			 
	TCHAR	fname[255 + 1];	 



} FILINFO;



 

typedef enum {
	FR_OK = 0,				 
	FR_DISK_ERR,			 
	FR_INT_ERR,				 
	FR_NOT_READY,			 
	FR_NO_FILE,				 
	FR_NO_PATH,				 
	FR_INVALID_NAME,		 
	FR_DENIED,				 
	FR_EXIST,				 
	FR_INVALID_OBJECT,		 
	FR_WRITE_PROTECTED,		 
	FR_INVALID_DRIVE,		 
	FR_NOT_ENABLED,			 
	FR_NO_FILESYSTEM,		 
	FR_MKFS_ABORTED,		 
	FR_TIMEOUT,				 
	FR_LOCKED,				 
	FR_NOT_ENOUGH_CORE,		 
	FR_TOO_MANY_OPEN_FILES,	 
	FR_INVALID_PARAMETER	 
} FRESULT;



 
 

FRESULT f_open (FIL* fp, const TCHAR* path, BYTE mode);				 
FRESULT f_close (FIL* fp);											 
FRESULT f_read (FIL* fp, void* buff, UINT btr, UINT* br);			 
FRESULT f_write (FIL* fp, const void* buff, UINT btw, UINT* bw);	 
FRESULT f_lseek (FIL* fp, FSIZE_t ofs);								 
FRESULT f_truncate (FIL* fp);										 
FRESULT f_sync (FIL* fp);											 
FRESULT f_opendir (DIR* dp, const TCHAR* path);						 
FRESULT f_closedir (DIR* dp);										 
FRESULT f_readdir (DIR* dp, FILINFO* fno);							 
FRESULT f_findfirst (DIR* dp, FILINFO* fno, const TCHAR* path, const TCHAR* pattern);	 
FRESULT f_findnext (DIR* dp, FILINFO* fno);							 
FRESULT f_mkdir (const TCHAR* path);								 
FRESULT f_unlink (const TCHAR* path);								 
FRESULT f_rename (const TCHAR* path_old, const TCHAR* path_new);	 
FRESULT f_stat (const TCHAR* path, FILINFO* fno);					 
FRESULT f_chmod (const TCHAR* path, BYTE attr, BYTE mask);			 
FRESULT f_utime (const TCHAR* path, const FILINFO* fno);			 
FRESULT f_chdir (const TCHAR* path);								 
FRESULT f_chdrive (const TCHAR* path);								 
FRESULT f_getcwd (TCHAR* buff, UINT len);							 
FRESULT f_getfree (const TCHAR* path, DWORD* nclst, FATFS** fatfs);	 
FRESULT f_getlabel (const TCHAR* path, TCHAR* label, DWORD* vsn);	 
FRESULT f_setlabel (const TCHAR* label);							 
FRESULT f_forward (FIL* fp, UINT(*func)(const BYTE*,UINT), UINT btf, UINT* bf);	 
FRESULT f_expand (FIL* fp, FSIZE_t szf, BYTE opt);					 
FRESULT f_mount (FATFS* fs, const TCHAR* path, BYTE opt);			 
FRESULT f_mkfs (const TCHAR* path, BYTE opt, DWORD au, void* work, UINT len);	 
FRESULT f_fdisk (BYTE pdrv, const DWORD* szt, void* work);			 
int f_putc (TCHAR c, FIL* fp);										 
int f_puts (const TCHAR* str, FIL* cp);								 
int f_printf (FIL* fp, const TCHAR* str, ...);						 
TCHAR* f_gets (TCHAR* buff, int len, FIL* fp);						 

#line 283 "../Middlewares/Third_Party/FatFs/src/ff.h"








 
 

 

DWORD get_fattime (void);


 

WCHAR ff_convert (WCHAR chr, UINT dir);	 
WCHAR ff_wtoupper (WCHAR chr);			 






 

int ff_cre_syncobj (BYTE vol, osMutexId_t* sobj);	 
int ff_req_grant (osMutexId_t sobj);				 
void ff_rel_grant (osMutexId_t sobj);				 
int ff_del_syncobj (osMutexId_t sobj);				 





 
 


 
#line 332 "../Middlewares/Third_Party/FatFs/src/ff.h"

 


 






 





 











#line 42 "../../sPlc/sPlc.h"
#line 1 "../Middlewares/Third_Party/FatFs/src/ff_gen_drv.h"
















 

 







 
#line 1 "../Middlewares/Third_Party/FatFs/src/diskio.h"


 











#line 16 "../Middlewares/Third_Party/FatFs/src/diskio.h"


 
typedef BYTE	DSTATUS;

 
typedef enum {
	RES_OK = 0,		 
	RES_ERROR,		 
	RES_WRPRT,		 
	RES_NOTRDY,		 
	RES_PARERR		 
} DRESULT;


 
 


DSTATUS disk_initialize (BYTE pdrv);
DSTATUS disk_status (BYTE pdrv);
DRESULT disk_read (BYTE pdrv, BYTE* buff, DWORD sector, UINT count);
DRESULT disk_write (BYTE pdrv, const BYTE* buff, DWORD sector, UINT count);
DRESULT disk_ioctl (BYTE pdrv, BYTE cmd, void* buff);
DWORD get_fattime (void);

 






 

 






 





 






 








#line 29 "../Middlewares/Third_Party/FatFs/src/ff_gen_drv.h"
#line 30 "../Middlewares/Third_Party/FatFs/src/ff_gen_drv.h"
#line 31 "../Middlewares/Third_Party/FatFs/src/ff_gen_drv.h"


 



 
typedef struct
{
  DSTATUS (*disk_initialize) (BYTE);                      
  DSTATUS (*disk_status)     (BYTE);                      
  DRESULT (*disk_read)       (BYTE, BYTE*, DWORD, UINT);        

  DRESULT (*disk_write)      (BYTE, const BYTE*, DWORD, UINT);  


  DRESULT (*disk_ioctl)      (BYTE, BYTE, void*);               


}Diskio_drvTypeDef;



 
typedef struct
{
  uint8_t                 is_initialized[1];
  const Diskio_drvTypeDef *drv[1];
  uint8_t                 lun[1];
  volatile uint8_t        nbr;

}Disk_drvTypeDef;

 
 
 
uint8_t FATFS_LinkDriver(const Diskio_drvTypeDef *drv, char *path);
uint8_t FATFS_UnLinkDriver(char *path);
uint8_t FATFS_LinkDriverEx(const Diskio_drvTypeDef *drv, char *path, BYTE lun);
uint8_t FATFS_UnLinkDriverEx(char *path, BYTE lun);
uint8_t FATFS_GetAttachedDriversNbr(void);







 

#line 43 "../../sPlc/sPlc.h"
#line 1 "../../MainApp/flash_if.h"











































 

 







 
#line 56 "../../MainApp/flash_if.h"

 
typedef  void (*pFunction)(void);

#line 72 "../../MainApp/flash_if.h"


 
#line 107 "../../MainApp/flash_if.h"
 
 
void FLASH_If_FlashUnlock(void);
FlagStatus FLASH_If_ReadOutProtectionStatus(void);
uint32_t FLASH_If_WriteApplication(uint32_t Address, uint32_t Data);
uint32_t FLASH_lf_WriteBootload(uint32_t Address, uint32_t Data);
uint32_t FLASH_If_EraseBootload(void);
uint32_t FLASH_If_EraseApplication(void);






 
#line 44 "../../sPlc/sPlc.h"
 



 
#line 55 "../../sPlc/sPlc.h"
 


 

 


 
#line 76 "../../sPlc/sPlc.h"
 
#line 83 "../../sPlc/sPlc.h"





#line 96 "../../sPlc/sPlc.h"
















extern uint16_t audioSineTable[]; 







 
#line 179 "../../sPlc/sPlc.h"
 










 
typedef enum {
	CLEAR_EPROM_ALL 														= 0x01,
	CLEAR_EPROM_NVRAM														= 0x02,
	CLEAR_EPROM_FDRAM														= 0x03,
	CLEAR_EPROM_FIRMWARE_CRC										= 0x04,
	CLEAR_EPROM_DEVICE_CONFIG										= 0x05,
	CLEAR_EPROM_LOG_INFO												= 0x06
}clarmEpromCmd_t;
 

extern I2C_HandleTypeDef hi2c1;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart4;
extern USBH_HandleTypeDef hUsbHostFS;
extern ADC_HandleTypeDef hadc1;
extern DMA_HandleTypeDef hdma_adc1;
extern CRC_HandleTypeDef hcrc;
extern DAC_HandleTypeDef hdac;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim7;
extern TIM_HandleTypeDef htim10;
extern TIM_HandleTypeDef htim12;
extern TIM_HandleTypeDef htim14;
extern RNG_HandleTypeDef hrng;

 
#line 237 "../../sPlc/sPlc.h"
 
extern int16_t NVRAM0[(1463 + 1)];
extern int16_t NVRAM1[(1463 + 1)];
extern int16_t FDRAM0[(2047 - 0 + 1)], FDRAM1[(2047 - 0 + 1)];
extern uint16_t TimerCounter_10mS;
extern uint16_t TimerCounter_100mS;
extern uint16_t TimerCounter_200mS;
extern uint16_t TimerCounter_500mS;
extern uint16_t TimerCounter_1000mS;
extern uint16_t TimerCounter_60000mS;
extern uint8_t TD_10MS_SP;
extern uint8_t TD_100MS_SP;
extern uint8_t TD_200MS_SP;
extern uint8_t TD_500MS_SP;
extern uint8_t TD_1000MS_SP;
extern uint8_t TD_60000MS_SP;
extern uint32_t sPlcTick;
extern uint32_t BootloadCrc, ApplicationCrc;
 
extern int8_t LaserTimer_Mode;
extern int16_t LaserTimer_TCounter;
extern int16_t LaserTimer_TMate;
extern int16_t LaserTimer_TOvertime;
extern int16_t LaserTimer_PCounter;
extern int16_t LaserTimer_PMate;
extern int16_t LaserTimer_POvertime;
extern int16_t LaserTimer_ReleaseTime;
extern int16_t LaserTimer_ReleaseCounter;
extern int8_t  LaserFlag_Emiting;
extern int8_t LaserFlag_Emitover;
 
extern void sPlcInit(void);
extern void sPlcProcessStart(void);
extern void sPlcProcessEnd(void);
extern void sPlcPortProcess(void);
extern void sPlcAssertCoilAddress(uint16_t adr);
extern void sPlcAssertRegisterAddress(uint16_t adr);
 
extern void sPlcInputInit(void);
extern void sPlcInputRefresh(void);
extern void sPlcOutputInit(void);
extern void sPlcOutputRefresh(void);
extern void sPlcIsrDisable(void);
extern void sPlcIsrEnable(void);
extern void sPlcTimerInit(void);
extern void sPlcTimerIsr(void);
extern void sPlcTimerDisalbe(void);
extern void sPlcTimerEnable(void);
extern void sPlcDacInit(void);
extern void sPlcDacRefresh(void);
extern void sPlcAdcInit(void);
extern void sPlcAdcProcess(void);
extern void sPlcSpeakerFreq(int16_t freq);
extern void sPlcSpeakerVolume(int16_t volume);
extern void sPlcSpeakerEnable(void);
extern void sPlcSpeakerDisable(void);
extern void sPlcSpeakerInit(void);
extern void sPlcLaserInit(void);
extern void sPlcLaserTimerIsr(void);
extern void sPlcLaserTimerTestBench(uint8_t st);
extern void sPlcNvramUpdate(void);
extern void sPlcNvramLoad(void);
extern void sPlcNvramSave(void);
extern void sPlcNvramClear(void);
extern void sPlcFdramLoad(void);
extern void sPlcFdramSave(void);
extern void sPlcFdramClear(void);
extern void sPlcDeviceConfigClear(void);
extern void sPlcDeviceLogClear(void);
extern void softDelayMs(uint16_t ms);
extern void mucReboot(void);
extern void resetInit(void);
extern void SystemClock_Reset(void);
extern void UsbGpioReset(void);
extern void setRedLaserPwm(int16_t pwm);
extern void setPower_635(int16_t pwr);
extern void setFanSpeed(int16_t speed);
extern void morseCodeDiag(uint8_t diag);

extern HAL_StatusTypeDef epromReadByte(uint16_t ReadAddr, uint8_t *rdat);
extern HAL_StatusTypeDef epromReadHword(uint16_t ReadAddr, uint16_t *rdat);
extern HAL_StatusTypeDef epromReadDword(uint16_t ReadAddr, uint32_t *rdat);
extern HAL_StatusTypeDef epromWriteByte(uint16_t WriteAddr, uint8_t *wdat);
extern HAL_StatusTypeDef epromWriteHword(uint16_t WriteAddr, uint16_t *wdat);
extern HAL_StatusTypeDef epromWriteDword(uint16_t WriteAddr, uint32_t *wdat);
extern HAL_StatusTypeDef epromRead(uint16_t ReadAddr, uint8_t *pBuffer, uint16_t NumToRead);
extern HAL_StatusTypeDef epromWrite(uint16_t WriteAddr, uint8_t *pBuffer, uint16_t NumToWrite);
extern uint8_t sPlcEpromTest(void);
extern uint8_t checkBlank(uint32_t adr, uint32_t size);
void clearEprom(clarmEpromCmd_t cmd);
void listEpromTable(void);

extern uint32_t getOriginBootloadCrc(void);
extern uint32_t getOriginAppCrc(void);
extern uint8_t updateBootloadReq(void);
extern void confirmBootloadUpdate(void);
extern void exitBootloadUpdate(void);
void softDelayMs(uint16_t ms);
 
extern arm_pid_instance_f32 laserTecPids;
extern arm_pid_instance_f32 laserFanPids;
 
extern void REBOOT(void) ;

extern void SSET(uint16_t A);
extern void RRES(uint16_t A);
extern void FLIP(uint16_t A) ;
extern uint8_t LD(uint16_t A) ;
extern uint8_t LDB(uint16_t A) ;
extern uint8_t LDP(uint16_t A) ;
extern uint8_t LDN(uint16_t A) ;

extern void T10MS(uint8_t A, uint8_t start, uint16_t value) ;
extern void T100MS(uint8_t A, uint8_t start, uint16_t value) ;

extern void CLR(uint16_t A) ;
extern void CLRD(uint16_t A) ;
extern void MOV(uint16_t dist, uint16_t src) ;
extern void MOVD(uint16_t dist, uint16_t src) ;
extern void SWAP(uint16_t dist, uint16_t src) ;
extern void ABS16(uint16_t dist, uint16_t src) ;
extern void ABS32(uint16_t dist, uint16_t src) ;
extern void SMIN16(uint16_t index, uint16_t length, uint16_t min) ;
extern void SMAX16(uint16_t index, uint16_t length, uint16_t max) ;
extern void UMIN16(uint16_t index, uint16_t length, uint16_t min) ;
extern void UMAX16(uint16_t index, uint16_t length, uint16_t max) ;
extern void SUM16(uint16_t index, uint16_t length, uint16_t sum) ;
extern void MULT32(uint16_t Sa, uint16_t Sb, uint16_t D) ;
extern void MULTS16(uint16_t Sa, uint16_t Sb, uint16_t D) ;
extern void MULT16(uint16_t Sa, uint16_t Sb, uint16_t D) ;
extern void SUB32(uint16_t Sa, uint16_t Sb, uint16_t D) ;
extern void SUBS16(uint16_t Sa, uint16_t Sb, uint16_t D) ;
extern void SUB16(uint16_t Sa, uint16_t Sb, uint16_t D) ;
extern void ADD32(uint16_t Sa, uint16_t Sb, uint16_t D) ;
extern void ADDS32(uint16_t Sa, uint16_t Sb, uint16_t D) ;
extern void ADDS16(uint16_t Sa, uint16_t Sb, uint16_t D) ;
extern void ADD16(uint16_t Sa, uint16_t Sb, uint16_t D) ;
extern void ADD1(uint16_t Sa) ;
extern void ADDS1(uint16_t Sa) ;
extern void DEC1(uint16_t Sa) ;
extern void DECS1(uint16_t Sa) ;
extern void ADL1(uint16_t Sa) ;
extern void ADLS1(uint16_t Sa) ;
extern void DEL1(uint16_t Sa) ;
extern void DELS1(uint16_t Sa) ;
extern void TNTUC(uint16_t dist, uint16_t src);
extern void TNTLC(uint16_t dist, uint16_t src);
extern void TENV(uint16_t dist, uint16_t src);
extern void BCPY(uint16_t dist, uint16_t src, uint16_t length);
extern void LIMS16(uint16_t src, uint16_t min, uint16_t max);
extern void UPDAC0(void);
extern void UPDAC1(void);
extern void UPDAC2(void);
extern void UPDAC3(void);
extern void UPDAC4(void);
extern void UPDAC5(void);
extern void UPDAC6(void);
extern void UPDAC7(void);
extern void CLDAC(void);
extern void IMDIO(void) ;
extern void NVSAVE(void);
extern void NVFSAVE(void);
extern void NVLOAD(void);
extern void FDSAV(void);
extern void FDLAD(void);
extern void FDSAV_ONE(int16_t cn);
extern void FDLAD_ONE(int16_t cn);
extern void PRTM(uint16_t adr, uint8_t len);
extern void LINKS(void);
extern void LINKM(void);
extern void EDLAR(void);
extern void STLAR(void);
 
#line 5 "..\\..\\deviceInfo\\preScheme.h"
 
typedef struct{
	char *name;
	int16_t channel;
	int16_t pulse_mode;
	int16_t power_ch0;
	int16_t power_ch1;
	int16_t power_red;
	int16_t poswidth;
	int16_t negwidth;
}myScheme_t;
 
extern myScheme_t sPhlebology[32];
extern myScheme_t sProctology[32];
extern myScheme_t sGynecology[32];
extern myScheme_t sENT[32];
extern myScheme_t sNeurosurgery[32];
extern myScheme_t sDermatology[32];
extern myScheme_t sLiposuction[32];
extern myScheme_t sDentistry[32];
extern myScheme_t sTherapy[32];
 
void schemeInit(uint8_t reDef);
void goNextScheme(void);
void goLastScheme(void);



#line 3 "..\\..\\deviceInfo\\preScheme.c"




 
myScheme_t sPhlebology[32];
myScheme_t sProctology[32];
myScheme_t sGynecology[32];
myScheme_t sENT[32];
myScheme_t sNeurosurgery[32];
myScheme_t sDermatology[32];
myScheme_t sLiposuction[32];
myScheme_t sDentistry[32];
myScheme_t sTherapy[32];
 
void goNextScheme(void){
	switch(NVRAM0[(32 + 0)]){
		case 0x0001:{
			if(NVRAM0[(32 + 1)] < (3 - 1)){
				ADDS1((32 + 1));
			}
			break;
		}
		case 0x0002:{
			if(NVRAM0[(32 + 1)] < (6 - 1)){
				ADDS1((32 + 1));
			}
			break;
		}
		case 0x0003:{
			if(NVRAM0[(32 + 1)] < (22 - 1)){
				ADDS1((32 + 1));
			}
			break;
		}
		case 0x0004:{
			if(NVRAM0[(32 + 1)] < (16 - 1)){
				ADDS1((32 + 1));
			}
			break;
		}
		case 0x0005:{
			if(NVRAM0[(32 + 1)] < (3 - 1)){
				ADDS1((32 + 1));
			}				
			break;
		}
		case 0x0006:{
			if(NVRAM0[(32 + 1)] < (9 - 1)){
				ADDS1((32 + 1));
			}
			break;
		}
		case 0x0007:{
			if(NVRAM0[(32 + 1)] < (7 - 1)){
				ADDS1((32 + 1));
			}
			break;
		}
		case 0x0008:{
			if(NVRAM0[(32 + 1)] < (23 - 1)){
					ADDS1((32 + 1));
			}
			break;
		}
		case 0x0009:{
			if(NVRAM0[(32 + 1)] < (3 - 1)){
				ADDS1((32 + 1));
			}
			break;
		}	
		case 0x0000:{
			if(NVRAM0[(32 + 1)] < (32 - 1)){
				ADDS1((32 + 1));
			}
			break;
		}
		default:break;
	}
}

void goLastScheme(void){
	if(NVRAM0[(32 + 1)] > 0){
			DECS1((32 + 1));
	}
}
void loadSelectScheme(int16_t classify, int16_t index){
	switch(classify){
		case 0x0001:{
			if(NVRAM0[(32 + 1)] > (3-1)){
				NVRAM0[(32 + 1)] = (3-1);
			}
			strcpy((char*)(&NVRAM0[(576 + 0)]), (char*)(sPhlebology[index].name));
			NVRAM0[(576 + 55)] = sPhlebology[index].channel;
			NVRAM0[(576 + 56)] = sPhlebology[index].pulse_mode;
			NVRAM0[(576 + 57)] = sPhlebology[index].power_ch0;
			NVRAM0[(576 + 58)] = sPhlebology[index].power_ch1;
			NVRAM0[(576 + 61)] = sPhlebology[index].power_red;
			NVRAM0[(576 + 62)] = sPhlebology[index].poswidth;
			NVRAM0[(576 + 63)] = sPhlebology[index].negwidth;
			break;
		}
		case 0x0002:{
			if(index > (6 - 1)){
				 index = (6 - 1);
			}
			strcpy((char*)(&NVRAM0[(576 + 0)]), (char*)(sProctology[index].name));
			NVRAM0[(576 + 55)] = sProctology[index].channel;
			NVRAM0[(576 + 56)] = sProctology[index].pulse_mode;
			NVRAM0[(576 + 57)] = sProctology[index].power_ch0;
			NVRAM0[(576 + 58)] = sProctology[index].power_ch1;
			NVRAM0[(576 + 61)] = sProctology[index].power_red;
			NVRAM0[(576 + 62)] = sProctology[index].poswidth;
			NVRAM0[(576 + 63)] = sProctology[index].negwidth;
			break;			
		}
		case 0x0003:{
			if(index > (22 - 1)){
				index = (22 - 1);
			}
			strcpy((char*)(&NVRAM0[(576 + 0)]), (char*)(sGynecology[index].name));
			NVRAM0[(576 + 55)] = sGynecology[index].channel;
			NVRAM0[(576 + 56)] = sGynecology[index].pulse_mode;
			NVRAM0[(576 + 57)] = sGynecology[index].power_ch0;
			NVRAM0[(576 + 58)] = sGynecology[index].power_ch1;
			NVRAM0[(576 + 61)] = sGynecology[index].power_red;
			NVRAM0[(576 + 62)] = sGynecology[index].poswidth;
			NVRAM0[(576 + 63)] = sGynecology[index].negwidth;
			break;
		}			
		case 0x0004:{
			if(index > (16 - 1)){
				index = (16 - 1);
			}
			strcpy((char*)(&NVRAM0[(576 + 0)]), (char*)(sENT[index].name));
			NVRAM0[(576 + 55)] = sENT[index].channel;
			NVRAM0[(576 + 56)] = sENT[index].pulse_mode;
			NVRAM0[(576 + 57)] = sENT[index].power_ch0;
			NVRAM0[(576 + 58)] = sENT[index].power_ch1;
			NVRAM0[(576 + 61)] = sENT[index].power_red;
			NVRAM0[(576 + 62)] = sENT[index].poswidth;
			NVRAM0[(576 + 63)] = sENT[index].negwidth;
			break;
		}			
		case 0x0005:{
			if(index > (3 - 1)){
				index = (3 - 1);
			}
			strcpy((char*)(&NVRAM0[(576 + 0)]), (char*)(sNeurosurgery[index].name));
			NVRAM0[(576 + 55)] = sNeurosurgery[index].channel;
			NVRAM0[(576 + 56)] = sNeurosurgery[index].pulse_mode;
			NVRAM0[(576 + 57)] = sNeurosurgery[index].power_ch0;
			NVRAM0[(576 + 58)] = sNeurosurgery[index].power_ch1;
			NVRAM0[(576 + 61)] = sNeurosurgery[index].power_red;
			NVRAM0[(576 + 62)] = sNeurosurgery[index].poswidth;
			NVRAM0[(576 + 63)] = sNeurosurgery[index].negwidth;
			break;
		}
		case 0x0006:{
			if(index > (9 - 1)){
				index = (9 - 1);
			}
			strcpy((char*)(&NVRAM0[(576 + 0)]), (char*)(sDermatology[index].name));
			NVRAM0[(576 + 55)] = sDermatology[index].channel;
			NVRAM0[(576 + 56)] = sDermatology[index].pulse_mode;
			NVRAM0[(576 + 57)] = sDermatology[index].power_ch0;
			NVRAM0[(576 + 58)] = sDermatology[index].power_ch1;
			NVRAM0[(576 + 61)] = sDermatology[index].power_red;
			NVRAM0[(576 + 62)] = sDermatology[index].poswidth;
			NVRAM0[(576 + 63)] = sDermatology[index].negwidth;			
			break;
		}
		case 0x0007:{
			if(index > (7 - 1)){
				index = (7 - 1);
			}
			strcpy((char*)(&NVRAM0[(576 + 0)]), (char*)(sLiposuction[index].name));
			NVRAM0[(576 + 55)] = sLiposuction[index].channel;
			NVRAM0[(576 + 56)] = sLiposuction[index].pulse_mode;
			NVRAM0[(576 + 57)] = sLiposuction[index].power_ch0;
			NVRAM0[(576 + 58)] = sLiposuction[index].power_ch1;
			NVRAM0[(576 + 61)] = sLiposuction[index].power_red;
			NVRAM0[(576 + 62)] = sLiposuction[index].poswidth;
			NVRAM0[(576 + 63)] = sLiposuction[index].negwidth;
			break;
		}
		case 0x0008:{
			if(index > (23 - 1)){
				index = (23 - 1);
			}
			strcpy((char*)(&NVRAM0[(576 + 0)]), (char*)(sDentistry[index].name));
			NVRAM0[(576 + 55)] = sDentistry[index].channel;
			NVRAM0[(576 + 56)] = sDentistry[index].pulse_mode;
			NVRAM0[(576 + 57)] = sDentistry[index].power_ch0;
			NVRAM0[(576 + 58)] = sDentistry[index].power_ch1;
			NVRAM0[(576 + 61)] = sDentistry[index].power_red;
			NVRAM0[(576 + 62)] = sDentistry[index].poswidth;
			NVRAM0[(576 + 63)] = sDentistry[index].negwidth;
			break;
		}
		case 0x0009:{
			if(index > (3 - 1)){
				index = (3 - 1);
			}
			strcpy((char*)(&NVRAM0[(576 + 0)]), (char*)(sTherapy[index].name));
			NVRAM0[(576 + 55)] = sTherapy[index].channel;
			NVRAM0[(576 + 56)] = sTherapy[index].pulse_mode;
			NVRAM0[(576 + 57)] = sTherapy[index].power_ch0;
			NVRAM0[(576 + 58)] = sTherapy[index].power_ch1;
			NVRAM0[(576 + 61)] = sTherapy[index].power_red;
			NVRAM0[(576 + 62)] = sTherapy[index].poswidth;
			NVRAM0[(576 + 63)] = sTherapy[index].negwidth;			
			break;
		}
		case 0x0000:{
			if(index > (32 - 1)){
				index = (32 - 1);
			}
			memcpy((char*)(&NVRAM0[(576 + 0)]), (char*)(&FDRAM0[index * 64 + (0 + 0)]) , 112);
			NVRAM0[(576 + 55)] = FDRAM0[index * 64 + (0 + 55)];
			NVRAM0[(576 + 56)] = FDRAM0[index * 64 + (0 + 56)];
			NVRAM0[(576 + 57)] = FDRAM0[index * 64 + (0 + 57)];
			NVRAM0[(576 + 58)] = FDRAM0[index * 64 + (0 + 58)];
			NVRAM0[(576 + 61)] = FDRAM0[index * 64 + (0 + 61)];
			NVRAM0[(576 + 62)] = FDRAM0[index * 64 + (0 + 62)];
			NVRAM0[(576 + 63)] = FDRAM0[index * 64 + (0 + 63)];				
			break;
		}
		default:break;		
	}
	printf("%s,%d,%s:scheme classify:%d\n", "..\\..\\deviceInfo\\preScheme.c", 233, __func__, classify);
	printf("%s,%d,%s:scheme index:%d\n", "..\\..\\deviceInfo\\preScheme.c", 234, __func__, index);
	printf("%s,%d,%s:scheme name:%s\n", "..\\..\\deviceInfo\\preScheme.c", 235, __func__, (char*)(&NVRAM0[(576 + 0)]));
	printf("%s,%d,%s:scheme select:%d\n", "..\\..\\deviceInfo\\preScheme.c", 236, __func__, NVRAM0[(576 + 55)]);
	printf("%s,%d,%s:scheme mode:%d\n", "..\\..\\deviceInfo\\preScheme.c", 237, __func__, NVRAM0[(576 + 56)]);
	printf("%s,%d,%s:scheme power 1470:%d\n", "..\\..\\deviceInfo\\preScheme.c", 238, __func__,NVRAM0[(576 + 57)]);
	printf("%s,%d,%s:scheme power 980:%d\n", "..\\..\\deviceInfo\\preScheme.c", 239, __func__, NVRAM0[(576 + 58)]);
	printf("%s,%d,%s:scheme power 635:%d\n", "..\\..\\deviceInfo\\preScheme.c", 240, __func__, NVRAM0[(576 + 61)]);
	printf("%s,%d,%s:scheme poswidth:%d\n", "..\\..\\deviceInfo\\preScheme.c", 241, __func__, NVRAM0[(576 + 62)]);
	printf("%s,%d,%s:scheme negwidth:%d\n", "..\\..\\deviceInfo\\preScheme.c", 242, __func__, NVRAM0[(576 + 63)]);
}

void schemeInit(uint8_t reDef){
	myScheme_t *p;
	int16_t i;
	for (i = 0;i < 32; i ++){
		if(reDef == 1){
			sprintf(((char*)&FDRAM0[(0 + 0) + (i * 64)]), "Custom %d", (i+1)); 
			FDRAM0[(0 + 55) + (i * 64)] = 0x01;
			FDRAM0[(0 + 56) + (i * 64)] = 0x01;
			FDRAM0[(0 + 57) + (i * 64)] = 10;
			FDRAM0[(0 + 58) + (i * 64)] = 1;
			FDRAM0[(0 + 61) + (i * 64)] = 1;
			FDRAM0[(0 + 62) + (i * 64)] = 1000;
			FDRAM0[(0 + 63) + (i * 64)] = 1000;	
		}
		else{
			if(	(FDRAM0[(0 + 55) + (i * 64)] != 0x01) 			&&
					(FDRAM0[(0 + 55) + (i * 64)] != 0x02)  			&&
					(FDRAM0[(0 + 55) + (i * 64)] != 0x05)  			&&
					(FDRAM0[(0 + 55) + (i * 64)] != 0x06)		&&
					(FDRAM0[(0 + 55) + (i * 64)] != 0x07)){
				sprintf(((char*)&FDRAM0[(0 + 0) + (i * 64)]), "Custom %d", (i+1)); 
				FDRAM0[(0 + 55) + (i * 64)] = 0x01;
				FDRAM0[(0 + 56) + (i * 64)] = 0x01;
				FDRAM0[(0 + 57) + (i * 64)] = 10;
				FDRAM0[(0 + 58) + (i * 64)] = 1;
				FDRAM0[(0 + 61) + (i * 64)] = 1;
				FDRAM0[(0 + 62) + (i * 64)] = 1000;
				FDRAM0[(0 + 63) + (i * 64)] = 1000;		
			}
		}
	}
 
	
	
	sPhlebology[0].name = "EVLA Thigh";
	sPhlebology[0].channel = 0x01;
	sPhlebology[0].pulse_mode = 0x01; 
	sPhlebology[0].power_ch0 = 80;
	sPhlebology[0].power_ch1 = 1;
	sPhlebology[0].power_red = 1;
	sPhlebology[0].poswidth = 1000;
	sPhlebology[0].negwidth = 1000;
	
	
	sPhlebology[1].name = "EVLA calf";
	sPhlebology[1].channel = 0x01;
	sPhlebology[1].pulse_mode = 0x01; 
	sPhlebology[1].power_ch0 = 60;
	sPhlebology[1].power_ch1 = 1;
	sPhlebology[1].power_red = 1;
	sPhlebology[1].poswidth = 1000;
	sPhlebology[1].negwidth = 1000;
	
	
	p = &sPhlebology[2];
	p->name = "EVLA Small Vessel";
	p->channel = 0x01;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 30;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
 
	
	
	p = &sProctology[0];
	p->name = "Hemorrhoids Grade 2, 250J";
	p->channel = 0x01;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 70;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	
	p = &sProctology[1];
	p->name ="Hemorrhoids Grade 3, 350J";
	p->channel = 0x01;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 80;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000; 	
	
	
	p = &sProctology[2];
	p->name = "Hemorrhoids Grade 4, 350J";
	p->channel = 0x01;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 80;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000; 
	
	
	p = &sProctology[3];
	p->name = "Fistula";
	p->channel = 0x01;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 120;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000; 

	
	p = &sProctology[4];
	p->name = "Pilonidal Sinus";
	p->channel = 0x01;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 120;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000; 
	
	
	p = &sProctology[5];
	p->name = "Fissure Ablation";
	p->channel = 0x01;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 70;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000; 
 
	
	p = &sGynecology[0];
	p->name = "Laser Vaginal Tightening 1st 600J";
	p->channel = 0x01;
	p->pulse_mode = 0x02; 
	p->power_ch0 = 60;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 500;
	p->negwidth = 500; 	
	
	
	p = &sGynecology[1];
	p->name = "Laser Vaginal Tightening 2nd 600J";
	p->channel = 0x01;
	p->pulse_mode = 0x02; 
	p->power_ch0 = 70;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 500;
	p->negwidth = 500; 
	
	
	p = &sGynecology[2];
	p->name = "Laser Vaginal Tightening 3rd 600J";
	p->channel = 0x01;
	p->pulse_mode = 0x02; 
	p->power_ch0 = 80;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 500;
	p->negwidth = 500; 
	
	
	p = &sGynecology[3];
	p->name = "Laser Vaginal Tightening 4th 600J";
	p->channel = 0x01;
	p->pulse_mode = 0x02; 
	p->power_ch0 = 80;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 500;
	p->negwidth = 500; 
	
	
	p = &sGynecology[4];
	p->name ="Laser Vaginal Rejuvenation 360J";
	p->channel = 0x01;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 60;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000; 	
	
	
	p = &sGynecology[5];
	p->name = "Laser Vaginal Rejuvenation+ 600J"; 
	p->channel = 0x01;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 100;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 15000;
	p->negwidth = 1000; 	
	
	
	p = &sGynecology[6];
	p->name = "Stress Incontinence, 75J";
	p->channel = 0x01;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 50;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000; 
	
	
	p = &sGynecology[7];
	p->name = "Infection control, 50J";
	p->channel = 0x01;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 50;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000; 	
	
	
	p = &sGynecology[8];
	p->name = "Treatment after Menopause, 480J";
	p->channel = 0x01;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 80;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000; 	

	
	p = &sGynecology[9];
	p->name = "Hysteroscopy Myomas";
	p->channel = 0x01;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 120;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	
	p = &sGynecology[10];
	p->name = "Hysteroscopy Polyps";
	p->channel = 0x01;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 80;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;	
	
	
	p = &sGynecology[11];
	p->name = "Hysteroscopy Septum";
	p->channel = 0x01;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 100;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;		
	
	
	p = &sGynecology[12];
	p->name = "Hysteroscopy Adhesion";
	p->channel = 0x01;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 100;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;		
	
	
	p = &sGynecology[13];
	p->name = "Hysteroscopy Dysmorphic Uterus";
	p->channel = 0x01;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 120;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;		
	
	
	p = &sGynecology[14];
	p->name = "Hysteroscopy Isthmocele";
	p->channel = 0x01;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 120;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;		
	
	
	p = &sGynecology[15];
	p->name = "Hysteroscopy T-Shape Uterus";
	p->channel = 0x01;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 120;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;		
	
	
	p = &sGynecology[16];
	p->name = "Laparoscopy Myomas";
	p->channel = 0x01;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 120;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;

	
	p = &sGynecology[17];
	p->name = "Laparoscopy Ovarian Cysts";
	p->channel = 0x01;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 100;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	
	p = &sGynecology[18];
	p->name = "Laparoscopy Adhesion";
	p->channel = 0x01;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 100;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	
	p = &sGynecology[19];
	p->name = "Laparoscopy Salpingectomy";
	p->channel = 0x01;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 100;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	
	p = &sGynecology[20];
	p->name = "Laparoscopy Cysts";
	p->channel = 0x01;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 100;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;	
	
	
	p = &sGynecology[21];
	p->name = "Laparoscopy Endometriosis";
	p->channel = 0x01;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 100;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
 
#line 675 "..\\..\\deviceInfo\\preScheme.c"



	p = &sNeurosurgery[0];
	p->name = "PLDD L2-L3, L3-L4, L5-S1 800-1500J";
	p->channel = 0x01;
	p->pulse_mode = 0x02; 
	p->power_ch0 = 70;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 5000;

	
	p = &sNeurosurgery[1];
	p->name = "PLDD L4-L5 Total 800-1800J";
	p->channel = 0x01;
	p->pulse_mode = 0x02; 
	p->power_ch0 = 70;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 5000;
	
	
	
	p = &sNeurosurgery[2];
	p->name = "Tumour 1470nm";
	p->channel = 0x01;
	p->pulse_mode = 0x02; 
	p->power_ch0 = 70;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 5000;	

 
	
	
	p = &sENT[0];
	p->name = "Vocal Polyps";
	p->channel = 0x02;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 1;
	p->power_ch1 = 130;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;

	
	p = &sENT[1];
	p->name = "Cordectomy";
	p->channel = 0x02;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 1;
	p->power_ch1 = 120;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	
	p = &sENT[2];
	p->name = "Laryngeal Carcinoma";
	p->channel = 0x02;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 1;
	p->power_ch1 = 140;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	
	p = &sENT[3];
	p->name = "Haematomas";
	p->channel = 0x02;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 1;
	p->power_ch1 = 140;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	
	p = &sENT[4];
	p->name = "Fibromas";
	p->channel = 0x02;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 1;
	p->power_ch1 = 140;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	
	p = &sENT[5];
	p->name = "Larynxpapillomatosis";
	p->channel = 0x02;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 1;
	p->power_ch1 = 140;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	
	p = &sENT[6];
	p->name = "Paracentesis";		
	p->channel = 0x02;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 1;
	p->power_ch1 = 130;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	
	p = &sENT[7];
	p->name = "Acoustic Neuroma";
	p->channel = 0x02;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 1;
	p->power_ch1 = 130;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	
	p = &sENT[8];
	p->name = "Cholesteatoma";
	p->channel = 0x02;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 1;
	p->power_ch1 = 100;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	
	p = &sENT[9];
	p->name = "Tonsillectomy";
	p->channel = 0x02;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 1;
	p->power_ch1 = 130;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	
	p = &sENT[10];
	p->name = "Tumour Vaporisation";
	p->channel = 0x02;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 1;
	p->power_ch1 = 130;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	
	p = &sENT[11];
	p->name = "Uvulopalatoplasty (LAUP)";
	p->channel = 0x02;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 1;
	p->power_ch1 = 100;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	
	p = &sENT[12];
	p->name = "Conchotomy";
	p->channel = 0x02;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 1;
	p->power_ch1 = 130;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	
	p = &sENT[13];
	p->name = "Dacryocystorhinostomy (DCR)";
	p->channel = 0x02;
	p->pulse_mode = 0x02; 
	p->power_ch0 = 1;
	p->power_ch1 = 100;
	p->power_red = 1;
	p->poswidth = 50;
	p->negwidth = 90;
	
	
	p = &sENT[14];
	p->name = "Turbinate Reduction";
	p->channel = 0x02;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 1;
	p->power_ch1 = 100;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	
	p = &sENT[15];
	p->name = "Nasal Polypectomy";
	p->channel = 0x02;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 1;
	p->power_ch1 = 120;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
 
	
	
	p = &sDermatology[0];
	p->name = "Cut";
	p->channel = 0x02;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 1;
	p->power_ch1 = 100;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	
	p = &sDermatology[1];
	p->name = "Coagulation";
	p->channel = 0x02;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 1;
	p->power_ch1 = 30;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;	
	
	
	p = &sDermatology[2];
	p->name = "Moles Removal";
	p->channel = 0x02;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 1;
	p->power_ch1 = 80;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	
	p = &sDermatology[3];
	p->name = "Warts Removal";
	p->channel = 0x02;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 1;
	p->power_ch1 = 100;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;

	
	p = &sDermatology[4];
	p->name = "Nail Fungus";
	p->channel = 0x02;
	p->pulse_mode = 0x02; 
	p->power_ch0 = 1;
	p->power_ch1 = 60;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;

	
	p = &sDermatology[5];
	p->name = "Venectasia";
	p->channel = 0x02;
	p->pulse_mode = 0x02; 
	p->power_ch0 = 1;
	p->power_ch1 = 150;
	p->power_red = 1;
	p->poswidth = 70;
	p->negwidth = 120;

	
	p = &sDermatology[6];
	p->name = "Spider Vein 0.5mm";
	p->channel = 0x02;
	p->pulse_mode = 0x02; 
	p->power_ch0 = 1;
	p->power_ch1 = 80;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 5000;
	
	
	p = &sDermatology[7];
	p->name = "Spider Vein 1mm";
	p->channel = 0x02;
	p->pulse_mode = 0x02; 
	p->power_ch0 = 1;
	p->power_ch1 = 80;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 5000;

	
	p = &sDermatology[8];
	p->name = "Spider Vein 1.5mm";
	p->channel = 0x02;
	p->pulse_mode = 0x02; 
	p->power_ch0 = 1;
	p->power_ch1 = 80;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 5000;
	
 
	
	
	p = &sLiposuction[0];
	p->name =  "Liposuction Under Eye";
	p->channel = 0x01;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 30;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;

	
	p = &sLiposuction[1];
	p->name = "Liposuction Chin";
	p->channel = 0x01;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 60;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	
	p = &sLiposuction[2];
	p->name = "Liposuction Arm";
	p->channel = 0x01;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 80;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	
	p = &sLiposuction[3];
	p->name = "Liposuction Abdomen";
	p->channel = 0x01;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 120;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	
	p = &sLiposuction[4];
	p->name = "Liposuction Buttock";
	p->channel = 0x01;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 100;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	
	p = &sLiposuction[5];
	p->name = "Liposuction Thigh";
	p->channel = 0x01;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 80;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
		
	
	p = &sLiposuction[6];
	p->name = "Gynecomastia";
	p->channel = 0x01;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 80;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
 
	
	
	p = &sDentistry[0];
	p->name = "Incision & Drainage Of Abscess";
	p->channel = 0x02;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 1;
	p->power_ch1 = 12;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	p = &sDentistry[1];
	p->name = "Excision & Incisional Biopsy";
	p->channel = 0x02;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 1;
	p->power_ch1 = 10;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	p = &sDentistry[2];
	p->name = "Aphthous Ulcer & herpetic";
	p->channel = 0x02;
	p->pulse_mode = 0x02; 
	p->power_ch0 = 1;
	p->power_ch1 = 20;
	p->power_red = 1;
	p->poswidth = 50;
	p->negwidth = 50;	
	
	p = &sDentistry[3];
	p->name = "Pulpotomy";
	p->channel = 0x02;
	p->pulse_mode = 0x02; 
	p->power_ch0 = 1;
	p->power_ch1 = 15;
	p->power_red = 1;
	p->poswidth = 50;
	p->negwidth = 50;	
	
	p = &sDentistry[4];
	p->name = "Expose of unerupted teeth";
	p->channel = 0x02;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 1;
	p->power_ch1 = 10;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;	
	
	p = &sDentistry[5];
	p->name = "Fibroma Removal";
	p->channel = 0x02;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 1;
	p->power_ch1 = 10;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;	
	
	p = &sDentistry[6];
	p->name = "Frenectomy";
	p->channel = 0x02;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 1;
	p->power_ch1 = 10;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;	
	
	p = &sDentistry[7];
	p->name = "Gingivectomy";
	p->channel = 0x02;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 1;
	p->power_ch1 = 10;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;	
	
	p = &sDentistry[8];
	p->name = "Gingivoplasty";
	p->channel = 0x02;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 1;
	p->power_ch1 = 10;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;	
	
	p = &sDentistry[9];
	p->name = "Gingival incision & excision Hemostasis";
	p->channel = 0x02;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 1;
	p->power_ch1 = 10;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;	
	
	p = &sDentistry[10];
	p->name = "Crown Lengthening";
	p->channel = 0x02;
	p->pulse_mode = 0x02; 
	p->power_ch0 = 1;
	p->power_ch1 = 18;
	p->power_red = 1;
	p->poswidth = 50;
	p->negwidth = 50;	
	
	p = &sDentistry[11];
	p->name = "Reduction of Gingival Hypertrophy";
	p->channel = 0x02;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 1;
	p->power_ch1 = 15;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;	
	
	p = &sDentistry[12];
	p->name = "Implant Recovery";
	p->channel = 0x02;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 1;
	p->power_ch1 = 10;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;	
	
	p = &sDentistry[13];
	p->name = "Hemostasis and Coagulation";
	p->channel = 0x02;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 1;
	p->power_ch1 = 12;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;

	p = &sDentistry[14];
	p->name = "Gingival Troughing";
	p->channel = 0x02;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 1;
	p->power_ch1 = 18;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	p = &sDentistry[15];
	p->name = "Operculectomy";
	p->channel = 0x02;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 1;
	p->power_ch1 = 15;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	p = &sDentistry[16];
	p->name = "Infected Pockets Removal";
	p->channel = 0x02;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 1;
	p->power_ch1 = 18;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	p = &sDentistry[17];
	p->name = "Gingival Bleeding Index";
	p->channel = 0x02;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 1;
	p->power_ch1 = 8;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;

	p = &sDentistry[18];
	p->name = "Sulcular Debridement";
	p->channel = 0x02;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 1;
	p->power_ch1 = 8;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	p = &sDentistry[19];
	p->name = "Leukoplakia";
	p->channel = 0x02;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 1;
	p->power_ch1 = 10;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;

	p = &sDentistry[20];
	p->name = "Vestibuloplasty";
	p->channel = 0x02;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 1;
	p->power_ch1 = 10;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	p = &sDentistry[21];
	p->name = "Oral Papilectomies";
	p->channel = 0x02;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 1;
	p->power_ch1 = 9;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;

	p = &sDentistry[22];
	p->name = "Tooth Whitening";
	p->channel = 0x02;
	p->pulse_mode = 0x02; 
	p->power_ch0 = 1;
	p->power_ch1 = 50;
	p->power_red = 1;
	p->poswidth = 50;
	p->negwidth = 50;

 
#line 1393 "..\\..\\deviceInfo\\preScheme.c"
	
	
	p = &sTherapy[0];
	p->name = "Wound Healing";
	p->channel = 0x05;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 1;
	p->power_ch1 = 1;
	p->power_red = 5;
	p->poswidth = 1000;
	p->negwidth = 1000;

	
	p = &sTherapy[1];
	p->name = "Low Laser Therapy";
	p->channel = 0x05;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 1;
	p->power_ch1 = 1;
	p->power_red = 5;
	p->poswidth = 1000;
	p->negwidth = 1000;

	
	p = &sTherapy[2];
	p->name = "Biostimulation";
	p->channel = 0x05;
	p->pulse_mode = 0x01; 
	p->power_ch0 = 1;
	p->power_ch1 = 1;
	p->power_red = 5;
	p->poswidth = 1000;
	p->negwidth = 1000;



}




#line 1607 "..\\..\\deviceInfo\\preScheme.c"

