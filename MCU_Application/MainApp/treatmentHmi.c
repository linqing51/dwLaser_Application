//----------------------------------------------------------------------------
// 文件编码约定: 本文件为 UTF-8 编码(带BOM)。
// 本工程源码统一使用 UTF-8(带BOM) 保存, 以 UTF-8 编码保存并在文件头保留本注释。
//----------------------------------------------------------------------------
#include "dcHmiApp.h"
#include "treatment.h"
#include "treatmentCsv.h"//U盘CSV导入导出/U盘在位检测/进度回调

// ***************************************************************************
//病历储存页面:显示病历信息(idText: ID显示文本; log: 病历数据指针, NULL显示为空)
//注册页与编辑页控件编号完全一致, 仅页面ID不同, 由screenId指定目标页面
static void dcHmiShowTreatmentCommon(uint16_t screenId, const char *idText, const treatmentLog_t *log){
  char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
  if(log == NULL){
    SetTextValue(screenId, GDDC_PAGE_EDIT_PATIENT_TEXT_ID, (uint8_t*)"--");
    SetTextValue(screenId, GDDC_PAGE_EDIT_PATIENT_TEXT_NAME, (uint8_t*)"--");
    SetTextValue(screenId, GDDC_PAGE_EDIT_PATIENT_TEXT_AGE, (uint8_t*)"--");
    SetSelectorValue(screenId, GDDC_PAGE_EDIT_PATIENT_MENU_GENDER, 0);//性别下拉默认第0项
    return;
  }
  memset(dispBuf, 0x0, sizeof(dispBuf));
  SetTextValue(screenId, GDDC_PAGE_EDIT_PATIENT_TEXT_ID, (uint8_t*)idText);
  memset(dispBuf, 0x0, sizeof(dispBuf));
  sprintf(dispBuf, "%s", log->name);
  SetTextValue(screenId, GDDC_PAGE_EDIT_PATIENT_TEXT_NAME, (uint8_t*)dispBuf);
  memset(dispBuf, 0x0, sizeof(dispBuf));
  //年龄未填写(age=0)时下发空串保持空白, 不得显示"0"; 已填写才输出数字
  if(log->age != 0){
    sprintf(dispBuf, "%d", log->age);
  }
  SetTextValue(screenId, GDDC_PAGE_EDIT_PATIENT_TEXT_AGE, (uint8_t*)dispBuf);
  //性别下拉菜单: 屏幕工程选项顺序"Male;Female"(索引0=男MALE, 1=女FEMALE)
  SetSelectorValue(screenId, GDDC_PAGE_EDIT_PATIENT_MENU_GENDER,
                   (uint8_t)((log->gender == MALE) ? 0 : 1));
}

void dcHmiShowTreatmentRecord(uint16_t index, const treatmentLog_t *log){//显示EPROM历史病历
  char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
  uint16_t screenId = NVRAM0[EM_DC_PAGE];//保持函数签名不变, 目标页面取当前页
  (void)index;
  if(log == NULL){
    dcHmiShowTreatmentCommon(screenId, "--", NULL);
    return;
  }
  memset(dispBuf, 0x0, sizeof(dispBuf));
  sprintf(dispBuf, "AR %04u", (unsigned int)log->id);//患者ID取自记录本身(与患者绑定), 规则见treatment.c注释
  dcHmiShowTreatmentCommon(screenId, dispBuf, log);
}

void updateListTreatmentDisplay(void){//病历储存页面:显示当前治疗记录(待保存)
  dcHmiShowTreatmentCommon(NVRAM0[EM_DC_PAGE], "NEW", &treatmentLog);
}

//病历列表页单页可显示的患者数量(对应GDDC_PAGE_LIST_TREATMENT_TEXT_NAME_0-4)
#define LIST_TREATMENT_WINDOW_SIZE 5
//患者历史记录页单页可显示的记录数量(对应GDDC_PAGE_LIST_RECORD各5行控件)
#define LIST_RECORD_WINDOW_SIZE 5
//病历相关运行状态集中管理: 列表页窗口/选中 + U盘提示页状态机 + 待存病历快照
typedef struct{
  uint16_t topIndex;//列表窗口第一个患者在"过滤后患者视图"中的位置(整页翻页, 恒为窗口大小的整数倍)
  uint16_t selectedIndex;//当前选中患者在"过滤后患者视图"中的位置
  uint16_t usbState;//U盘流程状态: 0空闲 6确认页等待 7执行中 8完成态(100%后等1秒再切页)
  uint16_t usbCount;//本次保存/载入的病历条数
  uint32_t usbDoneTick;//状态7完成时刻(HAL_GetTick毫秒), 供状态8判定1秒停留
  char usbText[64];//USB操作页SUMMARY_USB当前应显示的内容(默认U盘在位状态, 导出/导入后为本次结果, 取消后为空)
  uint8_t  usbOp;//1=导出(save) 2=导入(load), 决定确认页文案与轮询执行分支
  uint8_t  usbErr;//U盘操作结果(0=成功)
  uint8_t  pendingValid;//1=本次治疗确实发射过且尚未落成病历
  treatmentLog_t pending;//待存病历快照(功率/波长/方案/发射时间/发射能量)
  //患者视图过滤: findText为SEARCH_NAME输入的查找字母(空串=不过滤), filteredCount为命中总数;
  //紧凑索引sortedIndex存命中患者的全局索引(按姓名+原始索引全序排序), 仅2字节/条, 物理上限4710字节;
  //窗口/选择直接按索引O(1)定位, 渲染时才回读整行, 不再为每次翻页做全表多轮扫描
  char findText[16];
  uint16_t filteredCount;//过滤后命中的患者数量(视图总数)
  uint16_t sortedIndex[TREATMENT_PHYSICAL_PATIENT_CAP];//命中患者全局索引, 已按显示顺序排序
  //当前选中患者: selectedPatientId为稳定患者编号(0=未选择), 后续治疗记录以该id为外键归属; selectedPatientName供待机页PATIENT_NAME显示
  uint16_t selectedPatientId;
  char selectedPatientName[TREATMENT_NAME_SIZE];
  //删除确认页: deletePatientId缓存待删除患者编号(0=不在删除确认流程), 确认后级联删除该患者及其全部治疗记录
  uint16_t deletePatientId;
  //LIST_RECORD治疗记录列表: recordPatientId为当前查看患者(0=未进入), recordTop为窗口起始(整页),
  //recordCount为该患者记录总数(u16), 不缓存全量索引, 仅按窗口(5)按需扫描, recordWindow存当前窗口全局索引
  uint16_t recordPatientId;
  uint16_t recordTop;
  uint16_t recordCount;//该患者记录总数(无上限, 仅受区块物理容量约束)
  uint16_t recordWindowTop;//recordWindow当前对应窗口起点(0xFFFF=缓存失效)
  uint16_t recordWindow[LIST_RECORD_WINDOW_SIZE];//当前窗口记录在扁平表中的全局索引
  //DELETE_RECORD单条记录删除确认: deleteRecordGlobalIndex缓存待删记录全局索引(0xFFFF=不在流程)
  uint16_t deleteRecordGlobalIndex;
  //EDIT_PATIENT患者信息编辑模式: 0=正常新建/追加流程, 1=从记录页进入只更新患者信息(不追加记录)
  uint8_t editPatientMode;
  //EDIT_PATIENT编辑页(17)返回目标页: 记录页进入=15, 正常新建流程=13; OK/CANCEL后显式回到该页, 不依赖隐式状态
  uint16_t editReturnPage;
  //GDDC_PAGE_REGISTER_PATIENT注册页: registerReturnPage为进入该页之前的来源页(2026-11-25起仅
  //GDDC_PAGE_LIST_TREATMENT(页面13)的CREATE_NEW手动新建; GDDC_PAGE_VERIFY_TREATMENT(页面22)已改为本页录入、
  //不再跳GDDC_PAGE_REGISTER_PATIENT), CANCEL/完成后返回该页;
  //verifySelectMode=1表示GDDC_PAGE_LIST_TREATMENT正被GDDC_PAGE_VERIFY_TREATMENT用来选择已有患者,
  //选中后回GDDC_PAGE_VERIFY_TREATMENT而非待机页
  uint16_t registerReturnPage;
  uint8_t verifySelectMode;
}listTreatmentCtx_t;
static listTreatmentCtx_t listTreatmentCtx;//病历页相关运行状态(开机全为0, 全部放ZI段)

//待机页PATIENT_NAME访问器: 已选患者显示其姓名, 未选择(开机selectedPatientId=0)清空, 保证任何路径回待机页显示一致
//非static: 由dcHmiApp.c待机页刷新跨文件调用, 声明见treatmentHmi.h
void listTreatmentWriteStandbyPatientName(void){
  if(listTreatmentCtx.selectedPatientId != 0U){
    SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXT_PATIENT_NAME,
                 (uint8_t*)listTreatmentCtx.selectedPatientName);
  }
  else{
    SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXT_PATIENT_NAME, (uint8_t*)"");
  }
}

//获取EPROM中有效病历数量:数量由DM_TREATMENT_NUM寄存器维护(treatment数据层增删时自动同步)
static uint16_t listTreatmentGetCount(void){
  if(NVRAM0[DM_TREATMENT_NUM] < 0){//异常负值防御
    return 0;
  }
  return (uint16_t)NVRAM0[DM_TREATMENT_NUM];
}

//姓名是否命中查找字母: 按SEARCH_NAME输入做大小写敏感的前缀匹配(输入"l"不命中大写"L"开头, 输入"la"只命中"la"前缀);
//findText为空串时不过滤全部命中; 姓名提前结束或任一位不同(含大小写不同)即不匹配
static uint8_t listTreatmentMatchFind(const char *name){
  uint8_t i;
  if(name == NULL){
    return 0U;
  }
  for(i = 0U; i < 16U; i++){
    char fc = listTreatmentCtx.findText[i];
    if(fc == '\0'){
      return 1U;//查找字母已全部匹配完
    }
    if(name[i] != fc){//大小写敏感: 直接逐位比较, 不做大小写归一
      return 0U;
    }
  }
  return 0U;//findText达到16位仍未结束(理论上findText被限制在15位内, 防御兜底)
}

//两个姓名的大小写敏感字典序(ASCII)比较: nameA靠前返回负, 靠后返回正, 完全相同返回0;
//按字符原始值逐位比较(大写A-Z码值65-90, 排在小写a-z 97-122之前), 短名先结束(如"li"排在"linqing"前), 非ASCII字节按原值比较
static int16_t listTreatmentCompareName(const char *nameA, const char *nameB){
  uint8_t i;
  for(i = 0U; i < TREATMENT_NAME_SIZE; i++){
    char ca = nameA[i];
    char cb = nameB[i];
    if(ca != cb){
      return (int16_t)((uint8_t)ca - (uint8_t)cb);
    }
    if(ca == '\0'){
      return 0;//两者同时结束
    }
  }
  return 0;
}

//全序键: 先按姓名ASCII字典序, 姓名相同再按患者表原始索引(唯一且稳定), 保证重名患者也能正确逐条枚举
static int16_t listTreatmentOrderCmp(const char *nameA, uint16_t idxA,
                                     const char *nameB, uint16_t idxB){
  int16_t c = listTreatmentCompareName(nameA, nameB);
  if(c != 0){ return c; }
  if(idxA < idxB){ return -1; }
  if(idxA > idxB){ return 1; }
  return 0;
}

//RAM内排序键: 仅缓存排序所需的全局索引+姓名(不缓存整行), 排序过程零FRAM访问
typedef struct{
  uint16_t globalIndex;
  char name[TREATMENT_NAME_SIZE];
}listPatientKey_t;
//RAM排序键缓冲(快速路径, 固定大小); 命中数超过该值时改用FRAM堆排序回退
static listPatientKey_t ramKeys[CONFIG_LIST_TREATMENT_RAM_KEYS];
//患者表批量读分块缓冲(对齐的患者行数组, 单次FRAM事务读16行)
static patientRecord_t chunkPat[CONFIG_LIST_TREATMENT_PATIENT_CHUNK_ROWS];
//记录行批量读分块缓冲(28B对齐, 单事务地址自增读8行); 仅refresh串行使用, 替代逐行2字节事务
#define LIST_TREATMENT_RECORD_CHUNK_ROWS 8U
static treatmentRecord_t listRecordChunk[LIST_TREATMENT_RECORD_CHUNK_ROWS];

//两个RAM键的全序比较: 复用姓名ASCII+全局索引口径, 纯内存不读FRAM
static int16_t listTreatmentKeyCmp(const listPatientKey_t *a, const listPatientKey_t *b){
  return listTreatmentOrderCmp(a->name, a->globalIndex, b->name, b->globalIndex);
}

//RAM键堆排序下沉: 大顶堆(全序键最大者在根), 无递归、栈占用恒定, 全程零FRAM
static void listTreatmentSiftDownKeys(listPatientKey_t *arr, uint16_t heapSize, uint16_t root){
  uint16_t cur = root;
  while(1){
    uint16_t left = (uint16_t)(2U * cur + 1U);
    uint16_t right = (uint16_t)(2U * cur + 2U);
    uint16_t largest = cur;
    if((left < heapSize) && (listTreatmentKeyCmp(&arr[left], &arr[largest]) > 0)){
      largest = left;
    }
    if((right < heapSize) && (listTreatmentKeyCmp(&arr[right], &arr[largest]) > 0)){
      largest = right;
    }
    if(largest == cur){ break; }
    {
      listPatientKey_t tmp = arr[cur];
      arr[cur] = arr[largest];
      arr[largest] = tmp;
    }
    cur = largest;
  }
}

//对RAM键做原地堆排序(升序), 纯CPU O(N log N), 之后由键序列生成sortedIndex
static void listTreatmentSortKeys(listPatientKey_t *arr, uint16_t n){
  if(n < 2U){ return; }
  for(int32_t k = (int32_t)(n / 2U) - 1; k >= 0; k--){
    listTreatmentSiftDownKeys(arr, n, (uint16_t)k);
  }
  for(uint16_t end = (uint16_t)(n - 1U); end > 0U; end--){
    listPatientKey_t tmp = arr[0];
    arr[0] = arr[end];
    arr[end] = tmp;
    listTreatmentSiftDownKeys(arr, end, 0U);
  }
}

//全序比较两个全局索引对应患者: 读两行(仅排序时一次性发生), 按姓名+原始索引全序键
static int16_t listTreatmentOrderOfIndices(uint16_t idxA, uint16_t idxB){
  patientRecord_t a, b;
  if(treatmentPatientGetByIndex(idxA, &a) != TREATMENT_EPROM_OK){ return 0; }
  if(treatmentPatientGetByIndex(idxB, &b) != TREATMENT_EPROM_OK){ return 0; }
  return listTreatmentOrderCmp(a.name, idxA, b.name, idxB);
}

//堆排序下沉: 维护"全序键最大者在根"的大顶堆, 比较时按需读FRAM, 无递归、栈占用恒定
static void listTreatmentSiftDown(uint16_t *arr, uint16_t heapSize, uint16_t root){
  uint16_t cur = root;
  while(1){
    uint16_t left = (uint16_t)(2U * cur + 1U);
    uint16_t right = (uint16_t)(2U * cur + 2U);
    uint16_t largest = cur;
    if((left < heapSize) && (listTreatmentOrderOfIndices(arr[left], arr[largest]) > 0)){
      largest = left;
    }
    if((right < heapSize) && (listTreatmentOrderOfIndices(arr[right], arr[largest]) > 0)){
      largest = right;
    }
    if(largest == cur){ break; }
    uint16_t tmp = arr[cur];
    arr[cur] = arr[largest];
    arr[largest] = tmp;
    cur = largest;
  }
}

//对命中全局索引做原地堆排序(升序), 一次性O(N log N)比较, 之后任意翻页/选择O(1)
static void listTreatmentSortIndices(uint16_t *arr, uint16_t n){
  if(n < 2U){ return; }
  for(int32_t k = (int32_t)(n / 2U) - 1; k >= 0; k--){
    listTreatmentSiftDown(arr, n, (uint16_t)k);
  }
  for(uint16_t end = (uint16_t)(n - 1U); end > 0U; end--){
    uint16_t tmp = arr[0];
    arr[0] = arr[end];
    arr[end] = tmp;
    listTreatmentSiftDown(arr, end, 0U);
  }
}

//重建过滤视图: 分块批量读患者表(每块1次FRAM事务), 单遍收集命中患者的全局索引与RAM排序键;
//命中数在RAM键缓冲内则纯内存排序(零FRAM回读), 超限回退FRAM堆排序。数据变化(新建/删除/U盘载入)
//或查找字母变化时调用, 翻页期间直接复用排序结果, 不再重复扫描
static void listTreatmentRebuildFilter(void){
  uint16_t total = treatmentGetPatientCount();
  uint16_t start = 0U;
  uint16_t hits = 0U;
  listTreatmentCtx.filteredCount = 0U;
  while(start < total){
    //批量读一个分块(对齐的患者行), 读不到即终止
    uint16_t rows = treatmentPatientReadRows(start, (uint8_t*)chunkPat, (uint16_t)sizeof(chunkPat));
    if(rows == 0U){ break; }
    for(uint16_t r = 0U; r < rows; r++){
      patientRecord_t *pat = &chunkPat[r];
      uint16_t globalIndex;
      if(listTreatmentMatchFind(pat->name) == 0U){
        continue;
      }
      //物理容量保护: 命中数不超过紧凑索引上界(实际由区块容量保证, 防御兜底)
      if(hits >= TREATMENT_PHYSICAL_PATIENT_CAP){
        break;
      }
      globalIndex = (uint16_t)(start + r);
      //sortedIndex始终收集全部命中(回退路径也需要), RAM键仅在缓冲容量内填充
      listTreatmentCtx.sortedIndex[hits] = globalIndex;
      if(hits < CONFIG_LIST_TREATMENT_RAM_KEYS){
        ramKeys[hits].globalIndex = globalIndex;
        memcpy(ramKeys[hits].name, pat->name, TREATMENT_NAME_SIZE);
      }
      hits++;
    }
    start = (uint16_t)(start + rows);
  }
  listTreatmentCtx.filteredCount = hits;
  if(hits <= CONFIG_LIST_TREATMENT_RAM_KEYS){
    //快速路径: RAM键纯内存排序, 再由键序列生成sortedIndex, 排序过程零FRAM
    uint16_t k;
    listTreatmentSortKeys(ramKeys, hits);
    for(k = 0U; k < hits; k++){
      listTreatmentCtx.sortedIndex[k] = ramKeys[k].globalIndex;
    }
  }
  else{
    //回退路径: 命中超过RAM键缓冲, 用FRAM堆排序(正确, 不限制写入, 仅更慢)
    listTreatmentSortIndices(listTreatmentCtx.sortedIndex, hits);
  }
}

//视图位置 -> 患者行: 视图外位置返回0, 命中则经紧凑索引O(1)定位全局索引并回读整行;
//不再依赖窗口缓存, 任意有效视图位置都可取, 每次仅1次FRAM行读
static uint8_t listTreatmentGetViewPatient(uint16_t viewPos, patientRecord_t *out){
  uint16_t globalIndex;
  if(out == NULL){
    return 0U;
  }
  if(viewPos >= listTreatmentCtx.filteredCount){
    return 0U;
  }
  globalIndex = listTreatmentCtx.sortedIndex[viewPos];
  if(treatmentPatientGetByIndex(globalIndex, out) != TREATMENT_EPROM_OK){
    return 0U;
  }
  return 1U;
}

//窗口起始索引的合法上限(整页对齐): 视图患者超过一屏时, 取不超过"末位索引"的最大整页边界;
//不足一屏(无需滚动)时为0。保证topIndex恒为窗口大小的整数倍, 与整页翻页(±窗口大小)及页码计算一致
static uint16_t listTreatmentGetMaxTop(void){
  uint16_t viewCount = listTreatmentCtx.filteredCount;
  if(viewCount <= LIST_TREATMENT_WINDOW_SIZE){
    return 0U;
  }
  return (uint16_t)(((viewCount - 1U) / LIST_TREATMENT_WINDOW_SIZE) * LIST_TREATMENT_WINDOW_SIZE);
}

//把窗口/选中钳制到当前过滤视图的合法范围(防御: 记录式删除等路径改完索引后视图仍保持一致)
static void listTreatmentClampWindow(void){
  if(listTreatmentCtx.filteredCount == 0U){
    listTreatmentCtx.topIndex = 0U;
    listTreatmentCtx.selectedIndex = 0U;
    return;
  }
  //先把窗口起点向下对齐到整页边界(消除非整页路径遗留的偏移), 再夹到合法上限
  listTreatmentCtx.topIndex = (uint16_t)((listTreatmentCtx.topIndex / LIST_TREATMENT_WINDOW_SIZE)
                                         * LIST_TREATMENT_WINDOW_SIZE);
  if(listTreatmentCtx.topIndex > listTreatmentGetMaxTop()){
    listTreatmentCtx.topIndex = listTreatmentGetMaxTop();
  }
  if(listTreatmentCtx.selectedIndex >= listTreatmentCtx.filteredCount){
    listTreatmentCtx.selectedIndex = (uint16_t)(listTreatmentCtx.filteredCount - 1U);
  }
}

//刷新病历列表页:按窗口起始位置把过滤后患者的姓名/ID/病历数写入对应控件,并更新选中按钮状态;
//空槽位三类文本清空, 选择/删除/编辑三个按键隐藏并禁止触摸, 有效槽位恢复显示与使能
//翻页键(PAGE_UP/PAGE_DOWN)的使能不在本函数内管理, 统一由listTreatmentUpdatePageKeys在进入/动作完成/切页返回路径显式调用
static void listTreatmentUpdatePageKeys(void);//前置声明: 按当前topIndex/边界设置两键使能
void refreshListTreatmentDisplay(void){
  char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
  uint16_t recordCount = listTreatmentGetCount();
  uint16_t pageCount;
  uint16_t pageNow;
  patientRecord_t windowPat[LIST_TREATMENT_WINDOW_SIZE];
  uint16_t windowRecCount[LIST_TREATMENT_WINDOW_SIZE];
  listTreatmentClampWindow();
  //第一步: 预读当前窗口患者行(最多5次FRAM行读), 记录数先清零
  for(uint8_t i = 0U; i < LIST_TREATMENT_WINDOW_SIZE; i++){
    uint16_t viewPos = (uint16_t)(listTreatmentCtx.topIndex + i);
    memset(&windowPat[i], 0, sizeof(windowPat[i]));
    windowRecCount[i] = 0U;
    (void)listTreatmentGetViewPatient(viewPos, &windowPat[i]);
  }
  //第二步: 连续批量读记录行(单事务地址自增, 8行/块), 提取每行首字段patientId统计窗口各患者记录数;
  //替代逐行2字节独立事务(最多2019次), 消除每事务命令/地址开销, 数据时钟占主导, 耗时由约百ms降到约20-30ms
  {
    uint16_t totalRec = treatmentEpromGetCount();
    uint16_t pos = 0U;
    while(pos < totalRec){
      uint16_t got = treatmentRecordReadRows(pos, (uint8_t*)listRecordChunk,
                                             (uint16_t)sizeof(listRecordChunk));
      if(got == 0U){
        break;
      }
      for(uint16_t k = 0U; k < got; k++){
        uint16_t rid = listRecordChunk[k].patientId;
        for(uint8_t s = 0U; s < LIST_TREATMENT_WINDOW_SIZE; s++){
          if((windowPat[s].id != 0U) && (rid == windowPat[s].id)){
            windowRecCount[s]++;
            break;
          }
        }
      }
      pos = (uint16_t)(pos + got);
    }
  }
  //进入/重进本页先建立"全部按键未按下"基线: 显式清零页面13全部20个按钮(20-29, 31-40),
  //不依赖切页前后无应答的逐个复位; 选中患者仍由selectedPatientId/Name记录, 不再用按钮down态高亮
  for(uint16_t btn = GDDC_PAGE_LIST_TREATMENT_KEY_SELECT_PATIENT_0;
      btn <= GDDC_PAGE_LIST_TREATMENT_KEY_DELETE_4; btn++){
    SetButtonValue(GDDC_PAGE_LIST_TREATMENT, btn, 0);
  }
  for(uint16_t btn = GDDC_PAGE_LIST_TREATMENT_KEY_EDIT_RECORD_0;
      btn <= GDDC_PAGE_LIST_TREATMENT_KEY_OPERATOR_USB; btn++){
    SetButtonValue(GDDC_PAGE_LIST_TREATMENT, btn, 0);
  }
  //第三步: 按预读结果渲染各槽位(渲染循环内不再产生FRAM访问)
  for(uint8_t i = 0; i < LIST_TREATMENT_WINDOW_SIZE; i++){
    uint16_t nameCtrl = (uint16_t)(GDDC_PAGE_LIST_TREATMENT_TEXT_NAME_0 + i);
    uint16_t idCtrl = (uint16_t)(GDDC_PAGE_LIST_TREATMENT_TEXT_ID_0 + i);
    uint16_t countCtrl = (uint16_t)(GDDC_PAGE_LIST_TREATMENT_TEXT_RECORD_COUNT_0 + i);
    uint16_t selectCtrl = (uint16_t)(GDDC_PAGE_LIST_TREATMENT_KEY_SELECT_PATIENT_0 + i);
    uint16_t deleteCtrl = (uint16_t)(GDDC_PAGE_LIST_TREATMENT_KEY_DELETE_0 + i);
    uint16_t editCtrl = (uint16_t)(GDDC_PAGE_LIST_TREATMENT_KEY_EDIT_RECORD_0 + i);
    uint8_t slotOccupied = (windowPat[i].id != 0U) ? 1U : 0U;
    memset(dispBuf, 0x0, sizeof(dispBuf));
    if(slotOccupied != 0U){
      //列表只显示患者姓名: 患者信息存在即显示, 同一患者只出现一次, 与其病历数量无关(含0个病历)
      strncpy(dispBuf, windowPat[i].name, sizeof(windowPat[i].name));
      dispBuf[sizeof(windowPat[i].name) - 1U] = '\0';
      SetTextValue(GDDC_PAGE_LIST_TREATMENT, nameCtrl, (uint8_t*)dispBuf);
      sprintf(dispBuf, "AR %04u", (unsigned int)windowPat[i].id);//患者ID(AR编号)
      SetTextValue(GDDC_PAGE_LIST_TREATMENT, idCtrl, (uint8_t*)dispBuf);
      sprintf(dispBuf, "Records: %u", (unsigned int)windowRecCount[i]);//该患者已有病历数, 0条时显示"Records: 0"
      SetTextValue(GDDC_PAGE_LIST_TREATMENT, countCtrl, (uint8_t*)dispBuf);
    }
    else{//视图外空槽位: 三类文本全部清空
      SetTextValue(GDDC_PAGE_LIST_TREATMENT, nameCtrl, (uint8_t*)"");
      SetTextValue(GDDC_PAGE_LIST_TREATMENT, idCtrl, (uint8_t*)"");
      SetTextValue(GDDC_PAGE_LIST_TREATMENT, countCtrl, (uint8_t*)"");
    }
    //有效槽位三个按键显示并允许触摸, 空槽位三个按键隐藏并禁止触摸; 过滤/翻页/重进后槽位状态变化也按此显式恢复
    SetControlVisiable(GDDC_PAGE_LIST_TREATMENT, selectCtrl, slotOccupied);
    SetControlEnable(GDDC_PAGE_LIST_TREATMENT, selectCtrl, slotOccupied);
    SetControlVisiable(GDDC_PAGE_LIST_TREATMENT, deleteCtrl, slotOccupied);
    SetControlEnable(GDDC_PAGE_LIST_TREATMENT, deleteCtrl, slotOccupied);
    SetControlVisiable(GDDC_PAGE_LIST_TREATMENT, editCtrl, slotOccupied);
    SetControlEnable(GDDC_PAGE_LIST_TREATMENT, editCtrl, slotOccupied);
  }
  memset(dispBuf, 0x0, sizeof(dispBuf));
  //CAPACITY保持全局口径: 去重患者人数/治疗记录次数(同一患者多次治疗只计1人, 不受当前过滤影响)
  sprintf(dispBuf, "P:%u/R:%u",
    (unsigned int)treatmentEpromGetPatientCount(), (unsigned int)recordCount);
  SetTextValue(GDDC_PAGE_LIST_TREATMENT, GDDC_PAGE_LIST_TREATMENT_TEXT_CAPACITY, (uint8_t*)dispBuf);
  //PAGE_NUM: 当前页/总页数(空视图按1页显示, 避免出现0/0)
  pageCount = (listTreatmentCtx.filteredCount + LIST_TREATMENT_WINDOW_SIZE - 1U) / LIST_TREATMENT_WINDOW_SIZE;
  if(pageCount == 0U){
    pageCount = 1U;
  }
  pageNow = (uint16_t)(listTreatmentCtx.topIndex / LIST_TREATMENT_WINDOW_SIZE + 1U);
  sprintf(dispBuf, "PAGE %u/%u", (unsigned int)pageNow, (unsigned int)pageCount);
  SetTextValue(GDDC_PAGE_LIST_TREATMENT, GDDC_PAGE_LIST_TREATMENT_TEXT_PAGE_NUM, (uint8_t*)dispBuf);
  //注: 翻页键使能/禁用统一由listTreatmentUpdatePageKeys管理(动作期禁用+边界禁用), 本函数只渲染文本、不碰使能(与页面15同构)
}

//SEARCH_NAME文本通知: 保存查找字母并重建过滤视图, 新查找下窗口回到第一页(空串=恢复全部患者)
void listTreatmentSetFindText(const char *text){
  if(text == NULL){
    listTreatmentCtx.findText[0] = '\0';
  }
  else{
    strncpy(listTreatmentCtx.findText, text, sizeof(listTreatmentCtx.findText) - 1U);
    listTreatmentCtx.findText[sizeof(listTreatmentCtx.findText) - 1U] = '\0';
  }
  listTreatmentCtx.topIndex = 0U;
  listTreatmentRebuildFilter();
  refreshListTreatmentDisplay();
  listTreatmentUpdatePageKeys();//查找过滤后窗口回到首页, 按新视图重算两键使能
}

//进入病历列表页:清空查找字母并重建患者视图, 窗口从第一页开始, 默认选中第一个;
//同时清空屏幕搜索框, 保证CLOSE关闭后再进入页面时上次输入不残留(USB操作页返回不走此函数, 保留搜索内容)
void enterListTreatmentPage(void){
  listTreatmentCtx.topIndex = 0U;
  listTreatmentCtx.selectedIndex = 0U;
  listTreatmentCtx.findText[0] = '\0';
  SetTextValue(GDDC_PAGE_LIST_TREATMENT, GDDC_PAGE_LIST_TREATMENT_TEXT_SEARCH_NAME, (uint8_t*)"");
  listTreatmentRebuildFilter();
  SetTextValue(GDDC_PAGE_LIST_TREATMENT, GDDC_PAGE_LIST_TREATMENT_TEXT_CAPACITY, (uint8_t*)"");
  refreshListTreatmentDisplay();
  listTreatmentUpdatePageKeys();//进入页面: 建立两键使能基线(首页即禁用PAGE_UP), 再由后续切屏显示
}

//USB操作页SUMMARY_USB文案: 统一由usbText保存, 页面冷加载重发同一内容, 避免本次导出/导入结果被"UDISK OK"覆盖
static void setOperatorUsbText(const char *text){
  if(text == NULL){
    listTreatmentCtx.usbText[0] = '\0';
    return;
  }
  strncpy(listTreatmentCtx.usbText, text, sizeof(listTreatmentCtx.usbText) - 1U);
  listTreatmentCtx.usbText[sizeof(listTreatmentCtx.usbText) - 1U] = '\0';
}

//USB操作页: 刷新机内病历摘要(患者数/记录数), SUMMARY_USB按usbText下发(默认U盘在位状态, 导出/导入后为本次结果)
void refreshOperatorUsbDisplay(void){
  char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
  //进入/重进先建立"全部按键未按下"基线: 显式清零本页SAVE/LOAD/CANCEL三个自锁键,
  //不依赖切页前后的逐个复位, 与页面13进入即全键未按下的规则保持一致
  for(uint16_t btn = GDDC_PAGE_OPERATOR_USB_KEY_SAVE_UDISK;
      btn <= GDDC_PAGE_OPERATOR_USB_KEY_CLOSE; btn++){
    SetButtonValue(GDDC_PAGE_OPERATOR_USB, btn, 0);
  }
  memset(dispBuf, 0x0, sizeof(dispBuf));
  //机内病历储存概况: 现有患者数量/累计历史治疗记录数(全局去重患者数/记录数, 不受列表过滤影响); 文本控件一律英文显示
  sprintf(dispBuf, "Existing patients: %u, total treatment records: %u",
    (unsigned int)treatmentEpromGetPatientCount(), (unsigned int)listTreatmentGetCount());
  SetTextValue(GDDC_PAGE_OPERATOR_USB, GDDC_PAGE_OPERATOR_USB_TEXT_SUMMARY, (uint8_t*)dispBuf);
  SetTextValue(GDDC_PAGE_OPERATOR_USB, GDDC_PAGE_OPERATOR_USB_TEXT_SUMMARY_USB, (uint8_t*)listTreatmentCtx.usbText);
}

//列表页"操作USB"按键: 进入USB导入导出操作页(保存/载入的U盘检测与读写沿用既有流程)
void enterOperatorUsbPage(void){
  //重新进入操作页: SUMMARY_USB回到U盘在位状态, 覆盖上一次残留的导出/导入结果
  setOperatorUsbText((treatmentUsbDiskPresent() != 0U) ? "UDISK OK" : "NO UDISK");
  NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_LIST_TREATMENT;
  NVRAM0[EM_DC_PAGE] = GDDC_PAGE_OPERATOR_USB;
  refreshOperatorUsbDisplay();//先刷新本页控件, 再切页避免上一页控件残留
  SetScreen(GDDC_PAGE_OPERATOR_USB);
}

//USB操作页返回: 回到病历列表页(EPROM不改变, 保留当前名字窗口与选中)
void listTreatmentOperatorUsbBack(void){
  //从USB流程返回: 导入可能已整体替换EPROM, RAM里的filteredCount/sortedIndex/ramKeys是旧数据,
  //必须先按当前findText重建过滤再渲染, 否则会显示空白/旧数量(关闭重进才正常); findText与窗口保留
  listTreatmentRebuildFilter();
  refreshListTreatmentDisplay();
  listTreatmentUpdatePageKeys();//USB返回: 切屏前按重建后视图恢复两键使能
  NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_LIST_TREATMENT;
  NVRAM0[EM_DC_PAGE] = GDDC_PAGE_LIST_TREATMENT;
  SetScreen(GDDC_PAGE_LIST_TREATMENT);
  //CANCEL自锁键释放已上移到notify层(无条件)
}

//PAGE_UP键: 向前翻一整页, 已在第一页(窗口起始位置为0)时不再移动
void listTreatmentMoveUp(void){
  if(listTreatmentCtx.topIndex >= LIST_TREATMENT_WINDOW_SIZE){
    listTreatmentCtx.topIndex = (uint16_t)(listTreatmentCtx.topIndex - LIST_TREATMENT_WINDOW_SIZE);
    refreshListTreatmentDisplay();
  }
}

//PAGE_DOWN键: 向后翻一整页, 当前页之后已无患者时不再移动
void listTreatmentMoveDown(void){
  if((uint16_t)(listTreatmentCtx.topIndex + LIST_TREATMENT_WINDOW_SIZE) < listTreatmentCtx.filteredCount){
    listTreatmentCtx.topIndex = (uint16_t)(listTreatmentCtx.topIndex + LIST_TREATMENT_WINDOW_SIZE);
    refreshListTreatmentDisplay();
  }
}

//列表页翻页键: 瞬变按钮按下即翻页, 松开由屏幕自动弹起; 按边界更新两键使能(首页禁用PAGE_UP/末页禁用PAGE_DOWN)

//按当前(已钳制)topIndex/最大整页边界设置两键使能: 首页禁用PAGE_UP, 末页禁用PAGE_DOWN; 0条/不足1页时两键均禁用
static void listTreatmentUpdatePageKeys(void){
  uint16_t maxTop = listTreatmentGetMaxTop();
  SetControlEnable(GDDC_PAGE_LIST_TREATMENT, GDDC_PAGE_LIST_TREATMENT_KEY_PAGE_UP,
                   (listTreatmentCtx.topIndex > 0U) ? 1U : 0U);
  SetControlEnable(GDDC_PAGE_LIST_TREATMENT, GDDC_PAGE_LIST_TREATMENT_KEY_PAGE_DOWN,
                   (listTreatmentCtx.topIndex < maxTop) ? 1U : 0U);
}

//翻页键统一入口(由notify在state=1调用): dir 0=PAGE_UP 1=PAGE_DOWN
//瞬变按钮: 按下直接翻页并按边界更新使能, 无需去抖/延迟; 松开屏幕自动弹起, 互锁由state=0释放
void listTreatmentPageKey(uint8_t dir){
  if(dir != 0U){
    listTreatmentMoveDown();
  }
  else{
    listTreatmentMoveUp();
  }
  listTreatmentUpdatePageKeys();
}

//选择窗口内第slot个患者(slot 0-4对应KEY_SELECT_PATIENT_0-4),空槽位不响应;
//选中后缓存患者编号/姓名并自动返回待机页(PATIENT_NAME显示该患者), 后续治疗记录归属该患者
static void listTreatmentEnterVerifyPage(void);
void listTreatmentSelect(uint8_t slot){
  uint16_t viewPos;
  patientRecord_t pat;
  if(slot >= LIST_TREATMENT_WINDOW_SIZE){
    return;
  }
  viewPos = (uint16_t)(listTreatmentCtx.topIndex + slot);
  if(viewPos >= listTreatmentCtx.filteredCount){//空槽位: 不响应
    return;
  }
  if(listTreatmentGetViewPatient(viewPos, &pat) == 0U){//视图位置取不到患者(数据异常): 不响应
    return;
  }
  if(listTreatmentCtx.verifySelectMode != 0U){//核对页选择已有患者: 载入该患者并回核对页, 不回待机
    listTreatmentCtx.verifySelectMode = 0U;
    treatmentLog.id = pat.id;
    treatmentLog.age = pat.age;
    treatmentLog.gender = (GENDER_ENUM)pat.gender;
    memcpy(treatmentLog.name, pat.name, TREATMENT_NAME_SIZE);
    //持久记录本次选择: 更新selectedPatientId/Name, 使SAVE回待机页时PATIENT_NAME显示该患者名,
    //且再次激光核验经listTreatmentPrefillSelectedPatient自动归属该患者, 直到重新选择
    listTreatmentCtx.selectedPatientId = pat.id;
    memset(listTreatmentCtx.selectedPatientName, 0x0, sizeof(listTreatmentCtx.selectedPatientName));
    strncpy(listTreatmentCtx.selectedPatientName, pat.name,
            sizeof(listTreatmentCtx.selectedPatientName) - 1U);
    listTreatmentEnterVerifyPage();
    return;
  }
  listTreatmentCtx.selectedIndex = viewPos;//列表内选中位置(仅内部状态, 按钮未按下基线见refreshListTreatmentDisplay)
  listTreatmentCtx.selectedPatientId = pat.id;//缓存稳定患者编号, 后续治疗记录以该id为外键归属
  memset(listTreatmentCtx.selectedPatientName, 0x0, sizeof(listTreatmentCtx.selectedPatientName));
  strncpy(listTreatmentCtx.selectedPatientName, pat.name, sizeof(listTreatmentCtx.selectedPatientName) - 1U);
  refreshListTreatmentDisplay();//先刷新列表选中按钮状态
  returnStandbyDisplay();//自动返回待机页: 内部updateStandbyDisplay会向PATIENT_NAME下发该患者名
}

//删除当前选中病历: 后续病历前移并重新编号(treatment层同步DM_TREATMENT_NUM), 删完刷新列表与总数
void listTreatmentDelete(void){
  char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
  uint16_t count = listTreatmentGetCount();
  treatmentEpromErr_t err;
  treatmentLog_t rec;
  //注: 本函数为旧记录式删除逻辑(无调用者, 暂保留); 新UI的DELETE_0-4患者级联删除已由listTreatmentDeleteStart/Confirm确认页实现
  if(count == 0U){//没有病历可删
    memset(dispBuf, 0x0, sizeof(dispBuf));
    sprintf(dispBuf, "NO RECORD");
    SetTextValue(GDDC_PAGE_LIST_TREATMENT, GDDC_PAGE_LIST_TREATMENT_TEXT_DEBUG, (uint8_t*)dispBuf);
    return;
  }
  if(listTreatmentCtx.selectedIndex >= count){//选中索引越界时退到最后一条
    listTreatmentCtx.selectedIndex = (uint16_t)(count - 1U);
  }
  memset(dispBuf, 0x0, sizeof(dispBuf));
  if(treatmentEpromGet(listTreatmentCtx.selectedIndex, &rec) == TREATMENT_EPROM_OK){//提示正在删除的是哪个ID(直接取记录里的id字段)
    sprintf(dispBuf, "DEL AR %04u...", (unsigned int)rec.id);
  }
  else{
    sprintf(dispBuf, "DEL...");
  }
  SetTextValue(GDDC_PAGE_LIST_TREATMENT, GDDC_PAGE_LIST_TREATMENT_TEXT_DEBUG, (uint8_t*)dispBuf);
  err = treatmentEpromDelete(listTreatmentCtx.selectedIndex);//删除(后续病历前移, 各患者ID保持不变)
  if(err != TREATMENT_EPROM_OK){
    memset(dispBuf, 0x0, sizeof(dispBuf));
    sprintf(dispBuf, "DEL ERR:%d", (int)err);
    SetTextValue(GDDC_PAGE_LIST_TREATMENT, GDDC_PAGE_LIST_TREATMENT_TEXT_DEBUG, (uint8_t*)dispBuf);
    return;
  }
  count--;//有效病历数量-1
  if(count == 0U){//删空: 窗口与选中回到第一条
    listTreatmentCtx.selectedIndex = 0;
    listTreatmentCtx.topIndex = 0;
  }
  else{
    if(listTreatmentCtx.selectedIndex >= count){//删的是最后一条: 选中新的最后一条
      listTreatmentCtx.selectedIndex = (uint16_t)(count - 1U);
    }
    if(count <= LIST_TREATMENT_WINDOW_SIZE){//病历不足一页: 窗口从头开始
      listTreatmentCtx.topIndex = 0;
    }
    else if((uint16_t)(listTreatmentCtx.topIndex + LIST_TREATMENT_WINDOW_SIZE) > count){//窗口尾部越过新末尾: 前移到刚好显示末尾
      listTreatmentCtx.topIndex = (uint16_t)(count - LIST_TREATMENT_WINDOW_SIZE);
    }
  }
  refreshListTreatmentDisplay();
  listTreatmentUpdatePageKeys();//删除记录后窗口可能已夹取, 按新位置重算两键使能
  memset(dispBuf, 0x0, sizeof(dispBuf));
  sprintf(dispBuf, "DEL OK, NUM:%d", NVRAM0[DM_TREATMENT_NUM]);
  SetTextValue(GDDC_PAGE_LIST_TREATMENT, GDDC_PAGE_LIST_TREATMENT_TEXT_DEBUG, (uint8_t*)dispBuf);
}

//***************************************************************************
//待存病历快照: 在停光那一刻把本次实际治疗参数(发射时间/能量/功率/波长/方案)整条存下来,
//避免停光后操作员在待机页改方案或功率, 造成"存档参数与本次实际发射不匹配"; 没有实际发射时保持无效

//记录治疗时刻RTC(完整4位年): 停光瞬间取当前时刻, 随病历一起落盘
static void listTreatmentStampRtc(treatmentLog_t *log){
  if(log == NULL){
    return;
  }
  RtcGetDateTime(&log->rtcYear,
                 &log->rtcMonth,
                 &log->rtcDay,
                 &log->rtcHour,
                 &log->rtcMinute,
                 &log->rtcSecond);
}

static void listTreatmentPendingCapture(void){//退出ready时调用: 补齐累计后整条快照
  int32_t trigTicks;
  updateReleaseTimeEnergy();//用当前参数刷新整个ready累计的时间/能量, 补齐最后一个节拍
  trigTicks = *((int32_t*)&NVRAM0[EM_LASER_TRIG_TIME]);//整个ready累计的激光实际打开时间(10ms计数)
  if(trigTicks <= 0){//整个ready没有实际发射: 不产生待存病历
    return;
  }
  listTreatmentCtx.pending = treatmentLog;//整条快照: 功率/波长/方案/累计发射时间/累计发射能量
  //退出ready瞬间捕获RTC治疗时刻, 随病历一起落盘(完整4位年)
  listTreatmentStampRtc(&listTreatmentCtx.pending);
  listTreatmentCtx.pendingValid = 1U;
}

// 正常退出ready(点READY键回待机)前调用: 用整个ready期间累计的发射时间/能量抓一次快照;
// 确有发射则进核对页(22)由用户确认是否保存并返回1; 整个ready没有发射则返回0, 调用方继续正常回待机
// 非static: 由主状态机gddcHmiLoop跨文件调用, 声明见treatmentHmi.h
uint8_t listTreatmentExitReadyVerify(void){
  listTreatmentPendingCapture();//内部按EM_LASER_TRIG_TIME判断, 无发射直接返回且不置pendingValid
  if(listTreatmentCtx.pendingValid == 0U){
    return 0U;
  }
  listTreatmentVerifyAfterLaser();
  return 1U;
}

//姓名非空判定(全部为空格等同于没填)
static uint8_t listTreatmentNameValid(const char *name){
  uint8_t i;
  if(name == NULL){
    return 0U;
  }
  for(i = 0U; i < sizeof(treatmentLog.name); i++){
    if(name[i] == '\0'){
      break;
    }
    if((name[i] != ' ') && (name[i] != '\t')){
      return 1U;
    }
  }
  return 0U;
}

void listTreatmentCreateStart(void){//CREATE按键: 本次治疗确实发射过激光才允许新建病历(编辑页确认后追加到区块末尾)
  char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
  int32_t trigTicks;
  patientRecord_t selPat;//已选患者路径: 按id取出的患者行
  uint16_t patIndex;//已选患者在患者表内的索引
  if(listTreatmentCtx.pendingValid == 0U){//没抓到停光快照(极短发射/步骤跳变): 再用发射时间计数判断
    trigTicks = *((int32_t*)&NVRAM0[EM_LASER_TRIG_TIME]);//激光实际打开时间(20ms计数)
    if(trigTicks <= 0){//本次没有实际发射: 不允许凭空新建病历
      memset(dispBuf, 0x0, sizeof(dispBuf));
      sprintf(dispBuf, "CREATE:NO LASER");
      SetTextValue(GDDC_PAGE_LIST_TREATMENT, GDDC_PAGE_LIST_TREATMENT_TEXT_DEBUG, (uint8_t*)dispBuf);
      return;
    }
    listTreatmentCtx.pending = treatmentLog;//漏抓兜底: 直接用当前累计值
    listTreatmentStampRtc(&listTreatmentCtx.pending);//兜底: 用当前时刻补齐治疗时间
    listTreatmentCtx.pendingValid = 1U;
  }
  //用停光快照还原本次实际治疗参数(与之后是否改方案/功率无关)
  treatmentLog.releaseEnergy = listTreatmentCtx.pending.releaseEnergy;
  treatmentLog.releaseTime = listTreatmentCtx.pending.releaseTime;
  treatmentLog.laserPower = listTreatmentCtx.pending.laserPower;
  treatmentLog.laserWave = listTreatmentCtx.pending.laserWave;
  treatmentLog.protocol = listTreatmentCtx.pending.protocol;
  //治疗时刻RTC随病历落盘(编辑页OK后treatmentEpromAdd写入EPROM)
  treatmentLog.rtcYear = listTreatmentCtx.pending.rtcYear;
  treatmentLog.rtcMonth = listTreatmentCtx.pending.rtcMonth;
  treatmentLog.rtcDay = listTreatmentCtx.pending.rtcDay;
  treatmentLog.rtcHour = listTreatmentCtx.pending.rtcHour;
  treatmentLog.rtcMinute = listTreatmentCtx.pending.rtcMinute;
  treatmentLog.rtcSecond = listTreatmentCtx.pending.rtcSecond;
  //患者信息按是否已选患者分路径: 默认清空(新患者, id=0由treatmentEpromAdd分配); 已选则预填该患者(老患者, 保存时id已存在不新建)
  treatmentLog.id = 0U;
  treatmentLog.age = 0U;
  treatmentLog.gender = (GENDER_ENUM)0;
  memset(treatmentLog.name, 0x0, sizeof(treatmentLog.name));
  if(listTreatmentCtx.selectedPatientId != 0U){
    patIndex = 0U;
    if((treatmentPatientFind(listTreatmentCtx.selectedPatientId, &patIndex) == TREATMENT_EPROM_OK)
       && (treatmentPatientGetByIndex(patIndex, &selPat) == TREATMENT_EPROM_OK)){
      treatmentLog.id = selPat.id;
      treatmentLog.age = selPat.age;
      treatmentLog.gender = (GENDER_ENUM)selPat.gender;
      strncpy(treatmentLog.name, selPat.name, sizeof(treatmentLog.name) - 1U);
    }
    //选中患者若已被删除等导致查不到: 保持id=0的新患者兜底路径, 避免外键悬空
  }
  //新患者进注册页, 已选老患者进编辑页; 先定页面再刷新, 避免控件残留
  if(treatmentLog.id != 0U){
    //正常流程进编辑页(17): 非患者信息更新模式, OK/CANCEL后回病历列表页13
    listTreatmentCtx.editPatientMode = 0U;
    listTreatmentCtx.editReturnPage = GDDC_PAGE_LIST_TREATMENT;
  }
  NVRAM0[EM_DC_PAGE] = (treatmentLog.id == 0U)
    ? GDDC_PAGE_REGISTER_PATIENT : GDDC_PAGE_EDIT_PATIENT;
  updateListTreatmentDisplay();
  NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_EDIT_TREATMENT;
  SetScreen(NVRAM0[EM_DC_PAGE]);
}

void listTreatmentCreateConfirm(void){//编辑页OK: 校验患者信息后把当前治疗记录追加到EPROM末尾
  char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
  treatmentEpromErr_t err;
  treatmentLog_t rec;
  uint16_t count;
  //校验提示写入当前所在页面(注册页/编辑页控件编号一致)
  if(listTreatmentNameValid(treatmentLog.name) == 0U){//姓名必须录入
    SetTextValue(NVRAM0[EM_DC_PAGE], GDDC_PAGE_EDIT_PATIENT_TEXT_ID, (uint8_t*)"SET NAME");
    return;
  }
  if((treatmentLog.gender != MALE) && (treatmentLog.gender != FEMALE)){//性别必须选择
    SetTextValue(NVRAM0[EM_DC_PAGE], GDDC_PAGE_EDIT_PATIENT_TEXT_ID, (uint8_t*)"SET GENDER");
    return;
  }
  if((treatmentLog.age == 0U) || (treatmentLog.age > PATIENT_AGE_LIMIT)){//年龄范围检查(1-PATIENT_AGE_LIMIT, 与全局口径统一)
    SetTextValue(NVRAM0[EM_DC_PAGE], GDDC_PAGE_EDIT_PATIENT_TEXT_ID, (uint8_t*)"SET AGE");
    return;
  }
  err = treatmentEpromAdd(&treatmentLog);//末尾追加: 自动分配新患者ID, 已有病历位置不变
  memset(dispBuf, 0x0, sizeof(dispBuf));
  if(err == TREATMENT_EPROM_OK){
    clearReleaseTimeEnergy();//本次发射已落成病历: 清发射计数, 防止同一台治疗被重复新建
    listTreatmentCtx.pendingValid = 0U;//本次治疗已落成病历, 避免重复新建
    //新患者建在患者表末尾: 清空查找字母保证新患者可见, 重建视图后窗口滚到末尾并选中新患者
    listTreatmentCtx.findText[0] = '\0';
    SetTextValue(GDDC_PAGE_LIST_TREATMENT, GDDC_PAGE_LIST_TREATMENT_TEXT_CAPACITY, (uint8_t*)"");
    listTreatmentRebuildFilter();
    if(listTreatmentCtx.filteredCount > 0U){
      listTreatmentCtx.selectedIndex = (uint16_t)(listTreatmentCtx.filteredCount - 1U);
      listTreatmentCtx.topIndex = listTreatmentGetMaxTop();
      count = listTreatmentGetCount();
      if(treatmentEpromGet((uint16_t)(count - 1U), &rec) == TREATMENT_EPROM_OK){
        sprintf(dispBuf, "NEW AR %04u", (unsigned int)rec.id);
      }
    }
  }
  else if(err == TREATMENT_EPROM_ERR_FULL){
    sprintf(dispBuf, "TREAT FULL");
  }
  else{
    sprintf(dispBuf, "SAVE ERR:%d", (int)err);
  }
  refreshListTreatmentDisplay();
  listTreatmentUpdatePageKeys();//新建确认返回: 切屏前恢复两键使能
  SetTextValue(GDDC_PAGE_LIST_TREATMENT, GDDC_PAGE_LIST_TREATMENT_TEXT_DEBUG, (uint8_t*)dispBuf);
  NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_LIST_TREATMENT;
  NVRAM0[EM_DC_PAGE] = GDDC_PAGE_LIST_TREATMENT;
  SetScreen(GDDC_PAGE_LIST_TREATMENT);
}

void listTreatmentCreateCancel(void){//编辑页CANCEL: 放弃本次新建, 返回病历列表页(EPROM不变)
  refreshListTreatmentDisplay();
  listTreatmentUpdatePageKeys();//取消新建返回: 切屏前恢复两键使能
  NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_LIST_TREATMENT;
  NVRAM0[EM_DC_PAGE] = GDDC_PAGE_LIST_TREATMENT;
  SetScreen(GDDC_PAGE_LIST_TREATMENT);
}

//***************************************************************************
// 新建患者注册页(18) + 激光核对页(22)/放弃页(23)流程(见规格第十七节)
// 两入口: 激光停光自动弹核对页(22)后SAVE_RECORD; 列表页(13)CREATE_NEW手动新建
//***************************************************************************
static void listTreatmentEnterRegisterPage(void);
static void listTreatmentEnterVerifyPage(void);
// listTreatmentRefreshVerifyDisplay已改外部可见, 声明见treatmentHmi.h, 不再static前置声明
static void listTreatmentGoListPage(void);
static void listTreatmentClearVerifyFields(void);
static void listTreatmentClearRegisterFields(void);

// 回病历列表页(13): 重建过滤视图并刷新、切页
static void listTreatmentGoListPage(void){
  //患者表可能已变(注册OK新建患者): RAM里的sortedIndex/filteredCount/ramKeys是进入注册页前的旧缓存,
  //必须先按当前findText重建过滤再渲染, 否则新患者不显示(关闭回STANDBY重进才正常); CANCEL路径EPROM未变, 重建结果一致亦无害
  listTreatmentRebuildFilter();
  refreshListTreatmentDisplay();
  listTreatmentUpdatePageKeys();//注册/核对/放弃流程返回: 切屏前恢复两键使能
  NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_LIST_TREATMENT;
  NVRAM0[EM_DC_PAGE] = GDDC_PAGE_LIST_TREATMENT;
  SetScreen(GDDC_PAGE_LIST_TREATMENT);
}

// 按当前treatmentLog渲染注册页(先无条件清空再渲染), 供进入时预刷新与NotifyScreen冷加载重发复用
// 非static: 由dcHmiApp.c的NotifyScreen冷加载回调跨文件调用, 声明见treatmentHmi.h
void listTreatmentRenderRegisterDisplay(void){
  char idBuf[16];
  uint16_t suggestId = treatmentPatientSuggestId();
  if(suggestId != 0U){
    sprintf(idBuf, "%04u", (unsigned int)suggestId);
  }
  else{
    sprintf(idBuf, "----");
  }
  // 先无条件清空姓名/年龄/性别/提示, 再按当前treatmentLog渲染(先清后绘, 杜绝上一次残留)
  listTreatmentClearRegisterFields();
  dcHmiShowTreatmentCommon(GDDC_PAGE_REGISTER_PATIENT, idBuf, &treatmentLog);
  //性别文本控件: dcHmiShowTreatmentCommon只更新性别菜单, 文本需单独下发, 否则切页后TEXT_GENDER残留旧值
  if(treatmentLog.gender == MALE){
    SetTextValue(GDDC_PAGE_REGISTER_PATIENT, GDDC_PAGE_REGISTER_PATIENT_TEXT_GENDER,
                 (uint8_t*)"Male");
  }
  else if(treatmentLog.gender == FEMALE){
    SetTextValue(GDDC_PAGE_REGISTER_PATIENT, GDDC_PAGE_REGISTER_PATIENT_TEXT_GENDER,
                 (uint8_t*)"Female");
  }
  else{
    SetTextValue(GDDC_PAGE_REGISTER_PATIENT, GDDC_PAGE_REGISTER_PATIENT_TEXT_GENDER,
                 (uint8_t*)"");
  }
}

// 进入注册页: 建立按键未按下基线, 预刷新后台页面后切页;
// 冷加载完成后由NotifyScreen调用listTreatmentRenderRegisterDisplay重发(SetScreen后立即发会在冷加载窗口丢帧)
static void listTreatmentEnterRegisterPage(void){
  // 切页前先建立按键未按下基线
  SetButtonValue(GDDC_PAGE_REGISTER_PATIENT, GDDC_PAGE_REGISTER_PATIENT_KEY_OK, 0);
  SetButtonValue(GDDC_PAGE_REGISTER_PATIENT, GDDC_PAGE_REGISTER_PATIENT_KEY_CANCEL, 0);
  NVRAM0[EM_DC_PAGE] = GDDC_PAGE_REGISTER_PATIENT;
  // 冻结: 屏幕保持列表页, 预刷新与切页加载过程不可见
  SetScreenUpdateEnable(0U);
  listTreatmentRenderRegisterDisplay();//预刷新后台注册页(指令带screen id)
  SetScreen(GDDC_PAGE_REGISTER_PATIENT);
  // 解冻: 一次性重绘注册页; 若冷加载覆盖预刷新值, 由NotifyScreen加载完成后再次渲染兜底
  SetScreenUpdateEnable(1U);
}

// 列表页CREATE_NEW: 手动新建患者(不要求激光发射), 清空患者字段后进注册页
void listTreatmentRegisterNewPatient(void){
  treatmentLog.id = 0U;
  treatmentLog.age = 0U;
  treatmentLog.gender = (GENDER_ENUM)0;
  memset(treatmentLog.name, 0, sizeof(treatmentLog.name));
  listTreatmentCtx.registerReturnPage = GDDC_PAGE_LIST_TREATMENT;
  listTreatmentEnterRegisterPage();
}

// 注册页OK: 校验姓名/年龄(1-150)/性别, 通过则新建患者(仅建患者);
// 若本次有激光待存记录则一并把治疗记录归属到新患者
void listTreatmentRegisterConfirm(void){
  patientRecord_t pat;
  uint16_t newId = 0U;
  treatmentEpromErr_t ce;
  uint8_t hadPending = listTreatmentCtx.pendingValid;
  if((listTreatmentNameValid(treatmentLog.name) == 0U)
     || ((treatmentLog.gender != MALE) && (treatmentLog.gender != FEMALE))
     || (treatmentLog.age == 0U) || (treatmentLog.age > PATIENT_AGE_LIMIT)){
    SetTextValue(GDDC_PAGE_REGISTER_PATIENT, GDDC_PAGE_REGISTER_PATIENT_TEXT_SUMMARY_0,
                 (uint8_t*)"Invalid input, please re-enter!");
    return;
  }
  memset(&pat, 0, sizeof(pat));
  pat.age = treatmentLog.age;
  pat.gender = (uint8_t)treatmentLog.gender;
  memcpy(pat.name, treatmentLog.name, TREATMENT_NAME_SIZE);
  ce = treatmentPatientCreate(&pat, &newId);
  if(ce != TREATMENT_EPROM_OK){
    SetTextValue(GDDC_PAGE_REGISTER_PATIENT, GDDC_PAGE_REGISTER_PATIENT_TEXT_SUMMARY_0,
                 (uint8_t*)"Save failed, please retry!");
    return;
  }
  if(listTreatmentCtx.verifySelectMode != 0U){
    //核对页22选择流程(SELECT_TREATMENT->列表13->CREATE_NEW)中的新建: 只创建患者,
    //不把待存治疗记录归属(不AddToPatient), 保留pendingValid与verifySelectMode, 回列表页13
    //由操作者决定是否选中该新患者; 选中后listTreatmentSelect回填患者字段并回核对页,
    //治疗参数(能量/时长/功率/方案/脉宽)一直保留在treatmentLog未被清空
    listTreatmentGoListPage();
    return;
  }
  if(hadPending != 0U){//激光流程: 患者已建, 把本次治疗记录归属到新患者
    treatmentLog.id = newId;
    ce = treatmentEpromAddToPatient(newId, &treatmentLog);
    if(ce != TREATMENT_EPROM_OK){
      // 患者已建但记录落盘失败: 保留待存与当前页, 提示重试(不回待机、不清待存)
      SetTextValue(GDDC_PAGE_REGISTER_PATIENT, GDDC_PAGE_REGISTER_PATIENT_TEXT_SUMMARY_0,
                   (uint8_t*)"Save failed, please retry!");
      return;
    }
    listTreatmentCtx.pendingValid = 0U;
    returnStandbyDisplay();//记录已落盘, 回待机页
  }
  listTreatmentGoListPage();//手动新建: 回列表页
}

// 注册页CANCEL: 不写入, 按来源页返回(核对页22/列表页13), 激光待存记录保留
void listTreatmentRegisterCancel(void){
  if(listTreatmentCtx.registerReturnPage == GDDC_PAGE_VERIFY_TREATMENT){
    listTreatmentEnterVerifyPage();
  }
  else{
    listTreatmentGoListPage();
  }
}

// 进入核对页前清空本页可残留的显示控件(姓名/年龄/性别/提示), 防止上一次数据残留;
// 清空后再由listTreatmentRefreshVerifyDisplay按当前treatmentLog渲染, 已选患者仍会正常回填
static void listTreatmentClearVerifyFields(void){
  SetTextValue(GDDC_PAGE_VERIFY_TREATMENT, GDDC_PAGE_VERIFY_TREATMENT_TEXT_NAME, (uint8_t*)"");
  SetTextValue(GDDC_PAGE_VERIFY_TREATMENT, GDDC_PAGE_VERIFY_TREATMENT_TEXT_AGE, (uint8_t*)"");
  SetTextValue(GDDC_PAGE_VERIFY_TREATMENT, GDDC_PAGE_VERIFY_TREATMENT_TEXT_GENDER, (uint8_t*)"");
  SetTextValue(GDDC_PAGE_VERIFY_TREATMENT, GDDC_PAGE_VERIFY_TREATMENT_TEXT_MSG, (uint8_t*)"");
}

// 进入注册页前清空本页可残留的显示控件(姓名/年龄/性别/提示), 防止上一次数据残留
static void listTreatmentClearRegisterFields(void){
  SetTextValue(GDDC_PAGE_REGISTER_PATIENT, GDDC_PAGE_REGISTER_PATIENT_TEXT_NAME, (uint8_t*)"");
  SetTextValue(GDDC_PAGE_REGISTER_PATIENT, GDDC_PAGE_REGISTER_PATIENT_TEXT_AGE, (uint8_t*)"");
  SetTextValue(GDDC_PAGE_REGISTER_PATIENT, GDDC_PAGE_REGISTER_PATIENT_TEXT_GENDER, (uint8_t*)"");
  SetTextValue(GDDC_PAGE_REGISTER_PATIENT, GDDC_PAGE_REGISTER_PATIENT_TEXT_SUMMARY_0, (uint8_t*)"");
}

// 核对页渲染: 把待存治疗(已在treatmentLog)写入核对页各控件
// 非static: 由dcHmiApp.c的NotifyScreen冷加载回调跨文件调用, 声明见treatmentHmi.h
void listTreatmentRefreshVerifyDisplay(void){
  char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
  char idBuf[16];
  // 先无条件清空姓名/年龄/性别/提示, 再按当前treatmentLog渲染(先清后绘, 杜绝上一次残留)
  listTreatmentClearVerifyFields();
  uint16_t suggestId;
  int32_t energyWhole, energyFrac;
  uint16_t mm, ss;
  suggestId = (treatmentLog.id != 0U)
    ? treatmentLog.id : treatmentPatientSuggestId();//已选已有患者显其真实id, 新患者显预生成最小空缺id
  if(suggestId != 0U){
    sprintf(idBuf, "%04u", (unsigned int)suggestId);
  }
  else{
    sprintf(idBuf, "----");
  }
  SetTextValue(GDDC_PAGE_VERIFY_TREATMENT, GDDC_PAGE_VERIFY_TREATMENT_TEXT_ID, (uint8_t*)idBuf);
  SetTextValue(GDDC_PAGE_VERIFY_TREATMENT, GDDC_PAGE_VERIFY_TREATMENT_TEXT_NAME,
               (uint8_t*)treatmentLog.name);
  if(treatmentLog.age != 0U){
    sprintf(dispBuf, "%u", (unsigned int)treatmentLog.age);
  }
  else{
    sprintf(dispBuf, "");
  }
  SetTextValue(GDDC_PAGE_VERIFY_TREATMENT, GDDC_PAGE_VERIFY_TREATMENT_TEXT_AGE, (uint8_t*)dispBuf);
  //性别菜单(0=Male,1=Female)与性别文本
  if(treatmentLog.gender == MALE){
    SetSelectorValue(GDDC_PAGE_VERIFY_TREATMENT, GDDC_PAGE_VERIFY_TREATMENT_MENU_GENDER, 0);
    SetTextValue(GDDC_PAGE_VERIFY_TREATMENT, GDDC_PAGE_VERIFY_TREATMENT_TEXT_GENDER, (uint8_t*)"Male");
  }
  else if(treatmentLog.gender == FEMALE){
    SetSelectorValue(GDDC_PAGE_VERIFY_TREATMENT, GDDC_PAGE_VERIFY_TREATMENT_MENU_GENDER, 1);
    SetTextValue(GDDC_PAGE_VERIFY_TREATMENT, GDDC_PAGE_VERIFY_TREATMENT_TEXT_GENDER, (uint8_t*)"Female");
  }
  else{
    SetSelectorValue(GDDC_PAGE_VERIFY_TREATMENT, GDDC_PAGE_VERIFY_TREATMENT_MENU_GENDER, 0);
    SetTextValue(GDDC_PAGE_VERIFY_TREATMENT, GDDC_PAGE_VERIFY_TREATMENT_TEXT_GENDER, (uint8_t*)"");
  }
  //治疗时刻
  if(treatmentLog.rtcYear >= 2000U){
    sprintf(dispBuf, "%04u-%02u-%02u %02u:%02u",
            (unsigned int)treatmentLog.rtcYear, (unsigned int)treatmentLog.rtcMonth,
            (unsigned int)treatmentLog.rtcDay, (unsigned int)treatmentLog.rtcHour,
            (unsigned int)treatmentLog.rtcMinute);
  }
  else{
    sprintf(dispBuf, "----");
  }
  SetTextValue(GDDC_PAGE_VERIFY_TREATMENT, GDDC_PAGE_VERIFY_TREATMENT_TEXT_SUMMARY_TIME, (uint8_t*)dispBuf);
  //能量(0.1J)
  energyWhole = treatmentLog.releaseEnergy / 10;
  energyFrac = treatmentLog.releaseEnergy % 10;
  if(energyFrac < 0){ energyFrac = -energyFrac; }
  sprintf(dispBuf, "%d.%d J", (int)energyWhole, (int)energyFrac);
  SetTextValue(GDDC_PAGE_VERIFY_TREATMENT, GDDC_PAGE_VERIFY_TREATMENT_TEXT_SUMMARY_ENERGY, (uint8_t*)dispBuf);
  //输出时长
  mm = (uint16_t)(treatmentLog.releaseTime / 60);
  ss = (uint16_t)(treatmentLog.releaseTime % 60);
  sprintf(dispBuf, "%02u:%02u", (unsigned int)mm, (unsigned int)ss);
  SetTextValue(GDDC_PAGE_VERIFY_TREATMENT, GDDC_PAGE_VERIFY_TREATMENT_TEXT_SUMMARY_OUT_TIME, (uint8_t*)dispBuf);
  //功率
  sprintf(dispBuf, "%d W", (int)treatmentLog.laserPower);
  SetTextValue(GDDC_PAGE_VERIFY_TREATMENT, GDDC_PAGE_VERIFY_TREATMENT_TEXT_SUMMARY_POWER, (uint8_t*)dispBuf);
  //方案
  if(treatmentLog.protocol == eCustiom){
    sprintf(dispBuf, "Custom");
  }
  else if(treatmentLog.pulseMode == LASER_MODE_MP){
    //脉冲模式: 与历史记录页15同口径, 追加正/负脉宽(ON=正脉宽posWidth, OFF=负脉宽negWidth, 单位ms)
    sprintf(dispBuf, "%s %u - Pulse - ON %u / OFF %u ms",
            treatmentProtocolName(treatmentLog.protocol),
            (unsigned int)treatmentLog.schemeIndex + 1U,
            (unsigned int)treatmentLog.posWidth,
            (unsigned int)treatmentLog.negWidth);
  }
  else{
    sprintf(dispBuf, "%s %u - CW", treatmentProtocolName(treatmentLog.protocol),
            (unsigned int)treatmentLog.schemeIndex + 1U);
  }
  SetTextValue(GDDC_PAGE_VERIFY_TREATMENT, GDDC_PAGE_VERIFY_TREATMENT_TEXT_SUMMARY_SCHEME, (uint8_t*)dispBuf);
  // GDDC_PAGE_VERIFY_TREATMENT_TEXT_MSG进入时保持空白(已在函数开头清空), 仅校验或落盘失败时才显示具体错误
}

// 进入核对页: 渲染并切页(不复制快照, 调用方负责treatmentLog内容)
// 核对页三键(SAVE/DISCARD/SELECT)弹起基线: SAVE成功切走时按钮可能停在物理按下态,
// 屏幕冷加载重绘会恢复该按下态, 故每次进入及冷加载完成后都重发弹起, 保证不卡按下
// 非static: 由dcHmiApp.c的NotifyScreen冷加载回调跨文件调用, 声明见treatmentHmi.h
void listTreatmentReleaseVerifyKeys(void){
  SetButtonValue(GDDC_PAGE_VERIFY_TREATMENT, GDDC_PAGE_VERIFY_TREATMENT_KEY_SAVE_RECORD, 0);
  SetButtonValue(GDDC_PAGE_VERIFY_TREATMENT, GDDC_PAGE_VERIFY_TREATMENT_KEY_DISCARD_RECORD, 0);
  SetButtonValue(GDDC_PAGE_VERIFY_TREATMENT, GDDC_PAGE_VERIFY_TREATMENT_KEY_SELECT_TREATMENT, 0);
}

static void listTreatmentEnterVerifyPage(void){
  listTreatmentReleaseVerifyKeys();//切页前先建立按键未按下基线
  NVRAM0[EM_DC_PAGE] = GDDC_PAGE_VERIFY_TREATMENT;
  listTreatmentRefreshVerifyDisplay();
  SetScreen(GDDC_PAGE_VERIFY_TREATMENT);
}

// 核对页预填已选患者: 选中患者仍存在则把id/年龄/性别/姓名填入treatmentLog并返回1;
// 未选择或已查不到(被删除)返回0, 调用方走新患者路径, 避免外键悬空
static uint8_t listTreatmentPrefillSelectedPatient(void){
  patientRecord_t selPat;
  uint16_t patIndex = 0U;
  if(listTreatmentCtx.selectedPatientId == 0U){
    return 0U;
  }
  if((treatmentPatientFind(listTreatmentCtx.selectedPatientId, &patIndex) != TREATMENT_EPROM_OK)
     || (treatmentPatientGetByIndex(patIndex, &selPat) != TREATMENT_EPROM_OK)){
    return 0U;
  }
  treatmentLog.id = selPat.id;
  treatmentLog.age = selPat.age;
  treatmentLog.gender = (GENDER_ENUM)selPat.gender;
  memset(treatmentLog.name, 0x0, sizeof(treatmentLog.name));
  strncpy(treatmentLog.name, selPat.name, sizeof(treatmentLog.name) - 1U);
  return 1U;
}

// 激光停光后自动进入核对页: 用待存快照填充treatmentLog; 已选患者则自动归属其名下, 否则走新患者路径
void listTreatmentVerifyAfterLaser(void){
  if(listTreatmentCtx.pendingValid != 0U){
    treatmentLog = listTreatmentCtx.pending;
  }
  treatmentLog.id = 0U;//默认新患者路径
  if(listTreatmentPrefillSelectedPatient() == 0U){
    //无选中患者(新患者路径): 停光快照可能带着上一次新建患者的字段, 必须清空,
    //使核对页姓名/年龄/性别保持空白待录入, 不残留过去患者信息
    treatmentLog.age = 0U;
    treatmentLog.gender = (GENDER_ENUM)0;
    memset(treatmentLog.name, 0, sizeof(treatmentLog.name));
  }
  listTreatmentEnterVerifyPage();
}

// GDDC_PAGE_VERIFY_TREATMENT的SAVE_RECORD: 本页校验后落盘, 全程不切GDDC_PAGE_REGISTER_PATIENT(2026-11-25 规则)
void listTreatmentVerifySaveRecord(void){
  patientRecord_t pat;
  uint16_t newId = 0U;
  treatmentEpromErr_t ce;
  if(treatmentLog.id != 0U){
    // 已有患者: 只追加治疗记录, 患者主表24字节不变
    ce = treatmentEpromAddToPatient(treatmentLog.id, &treatmentLog);
    if(ce != TREATMENT_EPROM_OK){
      // 记录落盘失败: 保留待存与当前页, 提示重试(不回待机、不清待存)
      SetTextValue(GDDC_PAGE_VERIFY_TREATMENT, GDDC_PAGE_VERIFY_TREATMENT_TEXT_MSG,
                   (uint8_t*)"Save failed, please retry!");
      return;
    }
    listTreatmentCtx.pendingValid = 0U;
    returnStandbyDisplay();
    return;
  }
  // 新患者: 逐字段校验, 每个失败在本页给出具体原因(不切页不写盘), 直接定位是哪个字段未回写
  if(listTreatmentNameValid(treatmentLog.name) == 0U){
    SetTextValue(GDDC_PAGE_VERIFY_TREATMENT, GDDC_PAGE_VERIFY_TREATMENT_TEXT_MSG,
                 (uint8_t*)"Invalid name: please enter the patient name.");
    return;
  }
  if((treatmentLog.gender != MALE) && (treatmentLog.gender != FEMALE)){
    SetTextValue(GDDC_PAGE_VERIFY_TREATMENT, GDDC_PAGE_VERIFY_TREATMENT_TEXT_MSG,
                 (uint8_t*)"Invalid gender: please select Male or Female.");
    return;
  }
  if((treatmentLog.age == 0U) || (treatmentLog.age > PATIENT_AGE_LIMIT)){
    SetTextValue(GDDC_PAGE_VERIFY_TREATMENT, GDDC_PAGE_VERIFY_TREATMENT_TEXT_MSG,
                 (uint8_t*)"Invalid age: please enter a value from 1 to 150.");
    return;
  }
  memset(&pat, 0, sizeof(pat));
  pat.age = treatmentLog.age;
  pat.gender = (uint8_t)treatmentLog.gender;
  memcpy(pat.name, treatmentLog.name, TREATMENT_NAME_SIZE);
  ce = treatmentPatientCreate(&pat, &newId);
  if(ce != TREATMENT_EPROM_OK){
    SetTextValue(GDDC_PAGE_VERIFY_TREATMENT, GDDC_PAGE_VERIFY_TREATMENT_TEXT_MSG,
                 (uint8_t*)"Save failed, please retry!");
    return;
  }
  // 患者已建(分配最小空缺ID), 把本次治疗记录归属到新患者
  treatmentLog.id = newId;
  ce = treatmentEpromAddToPatient(newId, &treatmentLog);
  if(ce != TREATMENT_EPROM_OK){
    // 患者已建但记录落盘失败: 保留待存与当前页, 提示重试(不回待机、不清待存);
    // treatmentLog.id已为newId, 重试走已有患者分支, 不会重复建患者
    SetTextValue(GDDC_PAGE_VERIFY_TREATMENT, GDDC_PAGE_VERIFY_TREATMENT_TEXT_MSG,
                 (uint8_t*)"Save failed, please retry!");
    return;
  }
  // 新建患者成功落盘: 持久记录为当前选中患者, 使回待机页PATIENT_NAME显示其名,
  // 且重新选择前后续治疗经listTreatmentPrefillSelectedPatient自动归属该患者
  listTreatmentCtx.selectedPatientId = newId;
  memset(listTreatmentCtx.selectedPatientName, 0x0, sizeof(listTreatmentCtx.selectedPatientName));
  strncpy(listTreatmentCtx.selectedPatientName, treatmentLog.name,
          sizeof(listTreatmentCtx.selectedPatientName) - 1U);
  listTreatmentCtx.pendingValid = 0U;
  returnStandbyDisplay();
}

// 核对页SELECT_TREATMENT: 列表页进入"选择已有患者"模式, 选中后回核对页
void listTreatmentVerifySelect(void){
  listTreatmentCtx.verifySelectMode = 1U;
  enterListTreatmentPage();
  NVRAM0[EM_DC_PAGE] = GDDC_PAGE_LIST_TREATMENT;
  SetScreen(GDDC_PAGE_LIST_TREATMENT);
}

// 核对页DISCARD_RECORD: 进入放弃页(23)
void listTreatmentVerifyDiscard(void){
  char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
  int32_t energyWhole, energyFrac;
  SetButtonValue(GDDC_PAGE_DISCARD_TREATMENT, GDDC_PAGE_DISCARD_TREATMENT_KEY_RETURN, 0);
  SetButtonValue(GDDC_PAGE_DISCARD_TREATMENT, GDDC_PAGE_DISCARD_TREATMENT_KEY_CANCEL, 0);
  SetTextValue(GDDC_PAGE_DISCARD_TREATMENT, GDDC_PAGE_DISCARD_TREATMENT_TEXT_NAME,
               (uint8_t*)treatmentLog.name);
  energyWhole = treatmentLog.releaseEnergy / 10;
  energyFrac = treatmentLog.releaseEnergy % 10;
  if(energyFrac < 0){ energyFrac = -energyFrac; }
  sprintf(dispBuf, "%d.%d J", (int)energyWhole, (int)energyFrac);
  SetTextValue(GDDC_PAGE_DISCARD_TREATMENT, GDDC_PAGE_DISCARD_TREATMENT_TEXT_ENERGY, (uint8_t*)dispBuf);
  NVRAM0[EM_DC_PAGE] = GDDC_PAGE_DISCARD_TREATMENT;
  SetScreen(GDDC_PAGE_DISCARD_TREATMENT);
}

// 放弃页RETURN: 不放弃, 回核对页(22)
void listTreatmentDiscardReturn(void){
  listTreatmentEnterVerifyPage();
}

// 放弃页CANCEL: 确认放弃本次记录, 清除待存, 回待机页
void listTreatmentDiscardCancel(void){
  listTreatmentCtx.pendingValid = 0U;
  returnStandbyDisplay();
}

//***************************************************************************
//U盘操作确认页流程(非阻塞): SAVE/LOAD按键先进入确认页, 按CONFIRM才在轮询中执行一次整块读写, 按CANCEL直接回操作页
//导出与导入共用GDDC_PAGE_OPERATOR_USB_CONFIRM页面, 由usbOp区分(1=导出, 2=导入); 导入必须先确认, 避免未授权就覆盖机内病历

//触摸放行判断: 写入期间屏蔽一切触摸; 确认页只放行本页的确认与取消按键
//============================================================================
// 病历相关页面按键互锁: 任一按键按下(置1)到被单片机清零(置0)期间, 其他按键一律锁定
//============================================================================
static uint8_t  g_btnLockActive = 0U;//1=有按键处于"在途"状态
static uint16_t g_btnLockScreen = 0U;//在途按键所在画面
static uint16_t g_btnLockControl = 0U;//在途按键控件ID

//画面是否属于需要按键互锁的11个病历相关页面
static uint8_t treatmentIsLockPage(uint16_t screen){
  switch(screen){
    case GDDC_PAGE_LIST_TREATMENT:
    case GDDC_PAGE_DELETE_TREATMENT:
    case GDDC_PAGE_LIST_RECORD:
    case GDDC_PAGE_DELETE_RECORD:
    case GDDC_PAGE_EDIT_PATIENT:
    case GDDC_PAGE_REGISTER_PATIENT:
    case GDDC_PAGE_OPERATOR_USB:
    case GDDC_PAGE_OPERATOR_USB_SAVE:
    case GDDC_PAGE_OPERATOR_USB_LOAD:
    case GDDC_PAGE_VERIFY_TREATMENT:
    case GDDC_PAGE_DISCARD_TREATMENT:
      return 1U;
    default:
      return 0U;
  }
}

static void treatmentBtnLockArm(uint16_t screen, uint16_t control){
  g_btnLockActive = 1U;
  g_btnLockScreen = screen;
  g_btnLockControl = control;
}

//仅当释放的是当前在途按键时才解锁(防止误清其他按键的锁)
static void treatmentBtnLockRelease(uint16_t screen, uint16_t control){
  if((g_btnLockActive != 0U) && (g_btnLockScreen == screen) && (g_btnLockControl == control)){
    g_btnLockActive = 0U;
    g_btnLockScreen = 0U;
    g_btnLockControl = 0U;
  }
}

//画面切换/异常路径强制解锁, 防止在途按键被切走后整页永久锁死
static void treatmentBtnLockReset(void){
  g_btnLockActive = 0U;
  g_btnLockScreen = 0U;
  g_btnLockControl = 0U;
}

//切页安全解锁: 屏幕加载完成回调跨文件调用, 仅当存在在途按键且其所在页不是当前页(原页面被切走,
//按键无法正常复位)时重置互锁; 同页加载不解锁, 避免在途动作期间被误放行。不暴露内部锁变量
void treatmentHmiResetLockIfPageMoved(uint16_t screen_id){
  if((g_btnLockActive != 0U) && (g_btnLockScreen != screen_id)){
    treatmentBtnLockReset();
  }
}

//按键互锁放行门: 非锁定页不干预; 按下时若已有在途按键则只放行同一按键(重复通知), 拒绝其他按键;
//弹起(瞬态键state=0)时释放对应锁。返回1=放行, 0=锁定
uint8_t treatmentButtonLockAllowed(uint16_t screen, uint16_t control, uint8_t state){
  if(treatmentIsLockPage(screen) == 0U){
    return 1U;
  }
  if(state == 0U){
    treatmentBtnLockRelease(screen, control);
    return 1U;
  }
  if(g_btnLockActive == 0U){
    treatmentBtnLockArm(screen, control);
    return 1U;
  }
  if((g_btnLockScreen == screen) && (g_btnLockControl == control)){
    return 1U;
  }
  return 0U;
}

//在途按键释放包装: 瞬变按钮由屏幕在松开时自动弹起, 这里只同步解除互锁, 供各页动作处理统一调用
void treatmentReleaseButton(uint16_t screen, uint16_t control){
  treatmentBtnLockRelease(screen, control);
}

uint8_t listTreatmentUsbButtonAllowed(uint16_t screen_id, uint16_t control_id){
  //删除确认页等待期间: 只放行本页DELETE/CANCEL, 其余控件与页面一律屏蔽(与USB流程互斥)
  if(listTreatmentCtx.deletePatientId != 0U){
    if(screen_id != GDDC_PAGE_DELETE_TREATMENT){
      return 0U;
    }
    if((control_id == GDDC_PAGE_DELETE_TREATMENT_KEY_OK) ||
       (control_id == GDDC_PAGE_DELETE_TREATMENT_KEY_CANCEL)){
      return 1U;
    }
    return 0U;
  }
  if(listTreatmentCtx.usbState == 0U){
    return 1U;//空闲: 正常响应
  }
  if(listTreatmentCtx.usbState == 6U){//确认页(导出/导入分两页): 只放行本页OK/CANCEL
    if((screen_id != GDDC_PAGE_OPERATOR_USB_SAVE) &&
       (screen_id != GDDC_PAGE_OPERATOR_USB_LOAD)){
      return 0U;
    }
    //两个确认页的OK(11)/CANCEL(10)编号一致
    if((control_id == GDDC_PAGE_OPERATOR_USB_SAVE_KEY_OK) ||
       (control_id == GDDC_PAGE_OPERATOR_USB_SAVE_KEY_CANCEL)){
      return 1U;
    }
    return 0U;
  }
  return 0U;//写入中(状态7): 不响应任何触摸操作
}

uint8_t listTreatmentUsbBusy(void){//提示页/确认页显示中
  return (listTreatmentCtx.usbState != 0U) ? 1U : 0U;
}

static uint16_t listTreatmentUsbPageOf(uint16_t state){//确认页状态(6/7/8)对应页面ID, 用于判断页面是否被别处切走
  (void)state;
  //按操作类型返回拆分后的确认页: 导入LOAD, 导出SAVE
  if(listTreatmentCtx.usbOp == 2U){
    return GDDC_PAGE_OPERATOR_USB_LOAD;
  }
  return GDDC_PAGE_OPERATOR_USB_SAVE;
}

//进入USB操作确认页: 导出进SAVE页/导入进LOAD页, 先刷新英文文案再切页, 避免上一页控件残留; 状态6等待用户按键
static void enterOperatorUsbConfirmPage(void){
  char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
  uint16_t page;
  listTreatmentCtx.usbState = 6U;
  if(listTreatmentCtx.usbOp == 2U){//导入(LOAD): 两条文案分别说明"替换范围"与"备份内容", 数量取进入确认页时的机内值
    page = GDDC_PAGE_OPERATOR_USB_LOAD;
    memset(dispBuf, 0x0, sizeof(dispBuf));
    sprintf(dispBuf, "Replace all %u patients and %u treatment records on the device with the USB backup?",
      (unsigned int)treatmentEpromGetPatientCount(), (unsigned int)listTreatmentGetCount());
    SetTextValue(page, GDDC_PAGE_OPERATOR_USB_LOAD_TEXT_SUMMARY_0, (uint8_t*)dispBuf);
    memset(dispBuf, 0x0, sizeof(dispBuf));
    sprintf(dispBuf, "Backup contents: %u patients, %u treatment records.",
      (unsigned int)treatmentEpromGetPatientCount(), (unsigned int)listTreatmentGetCount());
    SetTextValue(page, GDDC_PAGE_OPERATOR_USB_LOAD_TEXT_SUMMARY_1, (uint8_t*)dispBuf);
    //屏幕工程LOAD页只保留SUMMARY_0/1两条文案: 第三方文本(控件3)按空串下发, 避免残留旧文案
    SetTextValue(page, GDDC_PAGE_OPERATOR_USB_LOAD_TEXT_SUMMARY_2, (uint8_t*)"");
  }
  else{//导出(SAVE): 文案带本次待导出的患者数/已保存治疗记录数, 屏幕页只有SUMMARY_0/1两个文本框
    page = GDDC_PAGE_OPERATOR_USB_SAVE;
    memset(dispBuf, 0x0, sizeof(dispBuf));
    sprintf(dispBuf, "Export %u patients and %u saved treatment records to USB?",
      (unsigned int)treatmentEpromGetPatientCount(), (unsigned int)listTreatmentGetCount());
    SetTextValue(page, GDDC_PAGE_OPERATOR_USB_SAVE_TEXT_SUMMARY_0, (uint8_t*)dispBuf);
    SetTextValue(page, GDDC_PAGE_OPERATOR_USB_SAVE_TEXT_SUMMARY_1,
      (uint8_t*)"The existing patient backup in this USB will be replaced.");
  }
  //进入确认页建立"全部按键未按下且可用"基线: 先显式清零OK/CANCEL自锁键按下态(屏幕会保留
  //自锁键运行态、不随切页复位, 不主动清零会出现两键同时显示按下), 再恢复触摸使能;
  //与页面13/19进入即清零一致, 两确认页OK=11/CANCEL=10编号一致
  SetButtonValue(page, GDDC_PAGE_OPERATOR_USB_SAVE_KEY_OK, 0);
  SetButtonValue(page, GDDC_PAGE_OPERATOR_USB_SAVE_KEY_CANCEL, 0);
  SetControlEnable(page, GDDC_PAGE_OPERATOR_USB_SAVE_KEY_OK, 1);
  SetControlEnable(page, GDDC_PAGE_OPERATOR_USB_SAVE_KEY_CANCEL, 1);
  //进入确认页先把本页进度条清零: 上次操作可能停在100%, 等待确认期间应显示0%
  if(page == GDDC_PAGE_OPERATOR_USB_LOAD){
    SetProgressValue(page, GDDC_PAGE_OPERATOR_USB_LOAD_PROGRESS_LDISK, 0);
  }
  else{
    SetProgressValue(page, GDDC_PAGE_OPERATOR_USB_SAVE_PROGRESS_SDISK, 0);
  }
  NVRAM0[EM_DC_PAGE] = page;
  SetScreen(page);
}

void listTreatmentSaveUsbStart(void){//SAVE_USB按键: 不立即写盘, 先进入导出确认页, 由用户确认/取消(实际CSV写入在确认后执行)
  if(listTreatmentCtx.usbState != 0U){
    return;//上一次操作未结束
  }
  listTreatmentCtx.usbOp = 1U;
  listTreatmentCtx.usbErr = (uint8_t)TREATMENT_USB_ERR_MOUNT;
  listTreatmentCtx.usbCount = 0U;
  enterOperatorUsbConfirmPage();//进入导出确认页(状态6), 等待CANCEL/CONFIRM
  //SAVE自锁键释放已上移到notify层(无条件)
}

void listTreatmentLoadUsbStart(void){//LOAD_USB按键: 不立即读盘, 先进入确认页(确认后才读取U盘CSV覆盖机内病历)
  if(listTreatmentCtx.usbState != 0U){
    return;
  }
  listTreatmentCtx.usbOp = 2U;
  listTreatmentCtx.usbErr = (uint8_t)TREATMENT_USB_ERR_MOUNT;
  listTreatmentCtx.usbCount = 0U;
  enterOperatorUsbConfirmPage();//进入确认页(状态6), 等待CANCEL/CONFIRM
  //LOAD自锁键释放已上移到notify层(无条件)
}

//病历U盘进度回调: 数据层经treatmentReportProgress上报, 本函数按当前usbOp选择对应进度条下发,
//使数据层不直接依赖HMI; usbOp=2为导入(LOAD进度条), 其余为导出(SAVE进度条)
static void treatmentHmiProgressCb(uint8_t percent){
  if(listTreatmentCtx.usbOp == 2U){
    SetProgressValue(GDDC_PAGE_OPERATOR_USB_LOAD, GDDC_PAGE_OPERATOR_USB_LOAD_PROGRESS_LDISK, percent);
  }
  else{
    SetProgressValue(GDDC_PAGE_OPERATOR_USB_SAVE, GDDC_PAGE_OPERATOR_USB_SAVE_PROGRESS_SDISK, percent);
  }
}

void listTreatmentUsbConfirm(void){//确认页"OK"(导出/导入通用): 授权执行, 实际读写在轮询里完成一次
  if(listTreatmentCtx.usbState != 6U){
    return;
  }
  //OK按键保持按下: 待listTreatmentUsbLoop中功能执行完毕后再弹起
  listTreatmentCtx.usbState = 7U;
  //注册进度回调: 此后数据层读写/处理进度经treatmentHmiProgressCb驱动对应进度条, 不直接调HMI
  treatmentSetProgressCallback(treatmentHmiProgressCb);
  //U盘读写期间本页OK/CANCEL全部物理禁用(SetControlEnable 0): 按键触摸不产生任何通知,
  //既禁止中途取消, 也禁止读取过程中重复按OK持续下发state=1; 完成后在返回路径统一恢复使能
  {
    uint16_t confirmPage = (listTreatmentCtx.usbOp == 2U)
      ? GDDC_PAGE_OPERATOR_USB_LOAD : GDDC_PAGE_OPERATOR_USB_SAVE;
    SetButtonValue(confirmPage, GDDC_PAGE_OPERATOR_USB_SAVE_KEY_CANCEL, 0);
    SetControlEnable(confirmPage, GDDC_PAGE_OPERATOR_USB_SAVE_KEY_CANCEL, 0);
    SetControlEnable(confirmPage, GDDC_PAGE_OPERATOR_USB_SAVE_KEY_OK, 0);
  }
}

void listTreatmentUsbCancel(void){//确认页"CANCEL"(导出/导入通用): 不读写, 直接返回USB操作页
  if(listTreatmentCtx.usbState != 6U){
    return;
  }
  listTreatmentCtx.usbState = 0U;
  //取消: 清空结果栏返回操作页。进入确认页前的LOAD/SAVE释放帧在切页前下发, 但屏幕对自锁键
  //运行态保留不可靠, 故返回前用refreshOperatorUsbDisplay重建"全部按键未按下"基线(含SAVE/LOAD/CANCEL),
  //否则LOAD键会停在按下态; usbText已置空, 该函数同时把SUMMARY_USB下发为空
  setOperatorUsbText("");
  NVRAM0[EM_DC_PAGE] = GDDC_PAGE_OPERATOR_USB;
  refreshOperatorUsbDisplay();//先清键+刷新控件(当前页仍为确认页, 帧目标操作页), 再切页
  SetScreen(GDDC_PAGE_OPERATOR_USB);
  //CANCEL自锁键释放已上移到notify层(无条件, 按SAVE/LOAD各自页面下发)
}

//***************************************************************************
//删除患者确认流程: DELETE_0-4先进入删除确认页(不立即删除), 确认后级联删除患者及其全部病历, 取消则返回列表页

//列表页DELETE_0-4: 解析窗口内对应患者, 缓存其id并进入删除确认页(英文文案), 等待确认/取消
void listTreatmentDeleteStart(uint8_t slot){
  char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
  uint16_t viewPos;
  patientRecord_t pat;
  if(listTreatmentCtx.deletePatientId != 0U){//已有删除流程在等待确认
    return;
  }
  if(slot >= LIST_TREATMENT_WINDOW_SIZE){
    return;
  }
  viewPos = (uint16_t)(listTreatmentCtx.topIndex + slot);
  if(viewPos >= listTreatmentCtx.filteredCount){//空槽位: 不响应
    return;
  }
  if(listTreatmentGetViewPatient(viewPos, &pat) == 0U){//视图位置取不到患者: 不响应
    return;
  }
  listTreatmentCtx.deletePatientId = pat.id;//缓存待删除患者编号(非0=进入删除确认流程)
  SetTextValue(GDDC_PAGE_DELETE_TREATMENT, GDDC_PAGE_DELETE_TREATMENT_TEXT_NAME_ID,
    (uint8_t*)"Delete Patient?");
  memset(dispBuf, 0x0, sizeof(dispBuf));
  sprintf(dispBuf, "Delete patient %s and all their treatment records?", pat.name);
  SetTextValue(GDDC_PAGE_DELETE_TREATMENT, GDDC_PAGE_DELETE_TREATMENT_TEXT_SUMMARY_0,
    (uint8_t*)dispBuf);
  memset(dispBuf, 0x0, sizeof(dispBuf));
  sprintf(dispBuf, "This patient has %u treatment record(s).",
    (unsigned int)treatmentGetRecordCountForPatient(pat.id));
  SetTextValue(GDDC_PAGE_DELETE_TREATMENT, GDDC_PAGE_DELETE_TREATMENT_TEXT_SUMMARY_1,
    (uint8_t*)dispBuf);
  SetTextValue(GDDC_PAGE_DELETE_TREATMENT, GDDC_PAGE_DELETE_TREATMENT_TEXT_SUMMARY_2,
    (uint8_t*)"This action cannot be undone.");
  NVRAM0[EM_DC_PAGE] = GDDC_PAGE_DELETE_TREATMENT;
  SetScreen(GDDC_PAGE_DELETE_TREATMENT);
}

//删除确认页KEY_DELETE: 确认后级联删除患者及其全部病历, 再重建视图返回列表页
void listTreatmentDeleteConfirm(void){
  char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
  treatmentEpromErr_t err;
  uint16_t delId;
  if(listTreatmentCtx.deletePatientId == 0U){
    return;
  }
  delId = listTreatmentCtx.deletePatientId;
  //自锁键释放已上移到notify层(无条件), 本函数只做级联删除与视图重建
  err = treatmentPatientDelete(delId);//级联删除: 该患者全部记录+患者行
  listTreatmentCtx.deletePatientId = 0U;//退出删除流程
  if(delId == listTreatmentCtx.selectedPatientId){//删的正是当前选中患者: 清空选中, 避免外键/待机名悬空
    listTreatmentCtx.selectedPatientId = 0U;
    memset(listTreatmentCtx.selectedPatientName, 0x0, sizeof(listTreatmentCtx.selectedPatientName));
  }
  listTreatmentRebuildFilter();//患者表已变, 重建过滤视图
  refreshListTreatmentDisplay();//刷新列表(窗口自动夹取)
  listTreatmentUpdatePageKeys();//删除患者确认返回: 切屏前按重建后视图恢复两键使能
  memset(dispBuf, 0x0, sizeof(dispBuf));
  if(err == TREATMENT_EPROM_OK){
    sprintf(dispBuf, "DEL AR %04u OK", (unsigned int)delId);
  }
  else{
    sprintf(dispBuf, "DEL ERR:%d", (int)err);
  }
  SetTextValue(GDDC_PAGE_LIST_TREATMENT, GDDC_PAGE_LIST_TREATMENT_TEXT_DEBUG, (uint8_t*)dispBuf);
  NVRAM0[EM_DC_PAGE] = GDDC_PAGE_LIST_TREATMENT;
  SetScreen(GDDC_PAGE_LIST_TREATMENT);
}

//删除确认页KEY_CANCEL: 不删除, 清除待删除id并返回列表页
void listTreatmentDeleteCancel(void){
  if(listTreatmentCtx.deletePatientId == 0U){
    return;
  }
  //自锁键释放已上移到notify层(无条件)
  listTreatmentCtx.deletePatientId = 0U;
  refreshListTreatmentDisplay();
  listTreatmentUpdatePageKeys();//删除取消返回: 切屏前恢复两键使能
  NVRAM0[EM_DC_PAGE] = GDDC_PAGE_LIST_TREATMENT;
  SetScreen(GDDC_PAGE_LIST_TREATMENT);
}

// ***************************************************************************
//患者历史治疗记录页(GDDC_PAGE_LIST_RECORD, 15): 单患者全部记录的浏览/翻页/删除/患者信息编辑
//单页条数 LIST_RECORD_WINDOW_SIZE 已在文件前部与 LIST_TREATMENT_WINDOW_SIZE 一并定义

//波长数值文本: 单波长"1470 nm", 双波长"1470+980 nm"
static void listRecordWaveText(uint8_t wave, char *buf){
  switch(wave){
    case WAVE_450:       sprintf(buf, "450 nm"); break;
    case WAVE_915:       sprintf(buf, "915 nm"); break;
    case WAVE_980:       sprintf(buf, "980 nm"); break;
    case WAVE_1064:      sprintf(buf, "1064 nm"); break;
    case WAVE_1470:      sprintf(buf, "1470 nm"); break;
    case WAVE_1920:      sprintf(buf, "1920 nm"); break;
    case WAVE_635:       sprintf(buf, "635 nm"); break;
    case WAVE_1940:      sprintf(buf, "1940 nm"); break;
    case WAVE_1470_980:  sprintf(buf, "1470+980 nm"); break;
    default:             sprintf(buf, "-- nm"); break;
  }
}

//按需收集当前患者记录窗口: 单遍扫描扁平记录, 用2字节id轻读过滤并统计该患者记录总数,
//仅缓存当前窗口(5)的全局索引, 完整行在渲染时才读; 记录按存储顺序(即追加/时间顺序)枚举
static void listTreatmentRecordCollectWindow(void){
  uint16_t total = treatmentEpromGetCount();
  uint16_t n = 0U;//该患者记录的累计序号
  uint8_t slot;
  listTreatmentCtx.recordCount = 0U;
  for(slot = 0U; slot < LIST_RECORD_WINDOW_SIZE; slot++){
    listTreatmentCtx.recordWindow[slot] = 0U;
  }
  for(uint16_t i = 0U; i < total; i++){
    uint16_t rowId;
    //id轻读: 仅读外键2字节(替代整行28字节), 写不下/读失败即终止
    if(treatmentRecordGetPatientIdByIndex(i, &rowId) != TREATMENT_EPROM_OK){
      break;
    }
    if(rowId == listTreatmentCtx.recordPatientId){
      if((n >= listTreatmentCtx.recordTop) &&
         (n < (uint16_t)(listTreatmentCtx.recordTop + LIST_RECORD_WINDOW_SIZE))){
        listTreatmentCtx.recordWindow[(uint8_t)(n - listTreatmentCtx.recordTop)] = i;
      }
      n++;
    }
  }
  listTreatmentCtx.recordCount = n;
  listTreatmentCtx.recordWindowTop = listTreatmentCtx.recordTop;
}

//重新枚举(进入/删除后): 令窗口缓存失效并立即按当前recordTop收集
//非static: 由dcHmiApp.c的NotifyScreen冷加载回调跨文件调用, 声明见treatmentHmi.h
void listTreatmentRecordEnumerate(void){
  listTreatmentCtx.recordWindowTop = 0xFFFFU;
  listTreatmentRecordCollectWindow();
}

//记录页窗口最后一个合法recordTop(整页翻页, 恒为窗口大小整数倍)
static uint16_t listTreatmentRecordMaxTop(void){
  if(listTreatmentCtx.recordCount == 0U){
    return 0U;
  }
  return (uint16_t)(((uint16_t)listTreatmentCtx.recordCount - 1U)
                    / LIST_RECORD_WINDOW_SIZE * LIST_RECORD_WINDOW_SIZE);
}

//从病历列表页(13)KEY_EDIT_RECORD进入: slot为该页窗口内的槽位(0-4)
// listTreatmentRecordUpdatePageKeys已改外部可见, 声明见treatmentHmi.h, 不再static前置声明
void listTreatmentRecordEnter(uint8_t slot){
  uint16_t viewPos;
  patientRecord_t pat;
  if(listTreatmentCtx.recordPatientId != 0U){
    return;
  }
  if(slot >= LIST_TREATMENT_WINDOW_SIZE){
    return;
  }
  viewPos = (uint16_t)(listTreatmentCtx.topIndex + slot);
  if(viewPos >= listTreatmentCtx.filteredCount){
    return;
  }
  if(listTreatmentGetViewPatient(viewPos, &pat) == 0U){
    return;
  }
  listTreatmentCtx.recordPatientId = pat.id;
  listTreatmentCtx.recordTop = 0U;
  listTreatmentCtx.deleteRecordGlobalIndex = 0xFFFFU;
  listTreatmentCtx.editPatientMode = 0U;
  listTreatmentRecordEnumerate();
  NVRAM0[EM_DC_PAGE] = GDDC_PAGE_LIST_RECORD;
  //先建立"全部按键未按下"基线并渲染, 再切页(与页面13/19进入路径一致); 不依赖屏幕冷加载
  //回传(DeviceScreenNotify=0时该回传不可靠), 否则进入即空白且按键停在按下态。控件20-28均为按钮
  for(uint16_t btn = GDDC_PAGE_LIST_RECORD_KEY_DELETE_0;
      btn <= GDDC_PAGE_LIST_RECORD_KEY_EDIT_PATIENT; btn++){
    SetButtonValue(GDDC_PAGE_LIST_RECORD, btn, 0);
  }
  refreshListRecordDisplay();
  listTreatmentRecordUpdatePageKeys();//建立两键使能基线(首页即禁用PAGE_UP), 再切页
  SetScreen(GDDC_PAGE_LIST_RECORD);
}

//记录页显示刷新: 姓名行 + 5个记录槽(空槽隐藏) + 页码
void refreshListRecordDisplay(void){
  char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
  char waveText[24];
  uint16_t patientIndex;
  patientRecord_t pat;
  uint16_t pageCount, pageNow;
  uint16_t maxTop;
  //先钳制recordTop到合法范围, 再按需收集当前窗口(翻页/删除后缓存可能失效)
  maxTop = listTreatmentRecordMaxTop();
  if(listTreatmentCtx.recordTop > maxTop){
    listTreatmentCtx.recordTop = maxTop;
  }
  if(listTreatmentCtx.recordWindowTop != listTreatmentCtx.recordTop){
    listTreatmentRecordCollectWindow();
  }
  //姓名行: "name - AR 0001", 患者ID统一加AR前缀(EPROM内仅存数字)
  if((treatmentPatientFind(listTreatmentCtx.recordPatientId, &patientIndex) == TREATMENT_EPROM_OK)
     && (treatmentPatientGetByIndex(patientIndex, &pat) == TREATMENT_EPROM_OK)){
    sprintf(dispBuf, "%s - AR %04u", pat.name, (unsigned int)pat.id);
  }
  else{
    sprintf(dispBuf, "-- - AR %04u", (unsigned int)listTreatmentCtx.recordPatientId);
  }
  SetTextValue(GDDC_PAGE_LIST_RECORD, GDDC_PAGE_LIST_RECORD_TEXT_NAME, (uint8_t*)dispBuf);
  //5个记录槽
  for(uint8_t i=0U; i<LIST_RECORD_WINDOW_SIZE; i++){
    uint16_t recPos = (uint16_t)(listTreatmentCtx.recordTop + i);
    uint16_t energyCtrl = (uint16_t)(GDDC_PAGE_LIST_RECORD_TEXT_TIME_ENERGY_0 + i);
    uint16_t schemeCtrl = (uint16_t)(GDDC_PAGE_LIST_RECORD_TEXT_SCHEME_WIDTH_0 + i);
    uint16_t deleteCtrl = (uint16_t)(GDDC_PAGE_LIST_RECORD_KEY_DELETE_0 + i);
    uint8_t occupied = 0U;
    if(recPos < listTreatmentCtx.recordCount){
      treatmentLog_t log;
      if(treatmentEpromGet(listTreatmentCtx.recordWindow[i], &log) == TREATMENT_EPROM_OK){
        uint16_t mm, ss;
        int32_t energyWhole, energyFrac;
        occupied = 1U;
        //时间/能量行: "2026-11-10 18:00 - 262.7 J - 00:19 - 30 W - 1470 nm"
        listRecordWaveText(log.laserWave, waveText);
        mm = (uint16_t)(log.releaseTime / 60);
        ss = (uint16_t)(log.releaseTime % 60);
        energyWhole = log.releaseEnergy / 10;
        energyFrac = log.releaseEnergy % 10;
        if(energyFrac < 0){
          energyFrac = -energyFrac;
        }
        if(log.rtcYear >= 2000U){
          sprintf(dispBuf,
                  "%04u-%02u-%02u %02u:%02u - %d.%d J - %02u:%02u - %d W - %s",
                  (unsigned int)log.rtcYear, (unsigned int)log.rtcMonth,
                  (unsigned int)log.rtcDay, (unsigned int)log.rtcHour,
                  (unsigned int)log.rtcMinute, (int)energyWhole, (int)energyFrac,
                  (unsigned int)mm, (unsigned int)ss, (int)log.laserPower, waveText);
        }
        else{
          sprintf(dispBuf,
                  "---- --:-- - %d.%d J - %02u:%02u - %d W - %s",
                  (int)energyWhole, (int)energyFrac, (unsigned int)mm,
                  (unsigned int)ss, (int)log.laserPower, waveText);
        }
        SetTextValue(GDDC_PAGE_LIST_RECORD, energyCtrl, (uint8_t*)dispBuf);
        //方案/模式行: 连续"Phlebology 1 - CW"; 脉冲"Phlebology 1 - Pulse - ON 600 / OFF 700 ms"
        if(log.protocol == eCustiom){
          sprintf(dispBuf, "Custom");
        }
        else if(log.pulseMode == LASER_MODE_MP){
          sprintf(dispBuf, "%s %u - Pulse - ON %u / OFF %u ms",
                  treatmentProtocolName(log.protocol),
                  (unsigned int)log.schemeIndex + 1U,
                  (unsigned int)log.posWidth, (unsigned int)log.negWidth);
        }
        else{
          sprintf(dispBuf, "%s %u - CW",
                  treatmentProtocolName(log.protocol),
                  (unsigned int)log.schemeIndex + 1U);
        }
        SetTextValue(GDDC_PAGE_LIST_RECORD, schemeCtrl, (uint8_t*)dispBuf);
      }
    }
    //空槽: 两行文本与删除键全部隐藏, 删除键同时禁用
    SetControlVisiable(GDDC_PAGE_LIST_RECORD, energyCtrl, occupied);
    SetControlVisiable(GDDC_PAGE_LIST_RECORD, schemeCtrl, occupied);
    SetControlVisiable(GDDC_PAGE_LIST_RECORD, deleteCtrl, occupied);
    SetControlEnable(GDDC_PAGE_LIST_RECORD, deleteCtrl, occupied);
  }
  //页码: "PAGE 1/2"(recordTop已在函数开头钳制)
  pageCount = (uint16_t)((listTreatmentCtx.recordCount
                         + (LIST_RECORD_WINDOW_SIZE - 1U)) / LIST_RECORD_WINDOW_SIZE);
  if(pageCount == 0U){
    pageCount = 1U;
  }
  pageNow = (uint16_t)(listTreatmentCtx.recordTop / LIST_RECORD_WINDOW_SIZE + 1U);
  sprintf(dispBuf, "PAGE %u/%u", (unsigned int)pageNow, (unsigned int)pageCount);
  SetTextValue(GDDC_PAGE_LIST_RECORD, GDDC_PAGE_LIST_RECORD_TEXT_PAGE, (uint8_t*)dispBuf);
  //注: 翻页键的使能/禁用统一由listTreatmentRecordUpdatePageKeys管理(动作期禁用+边界禁用), 本函数只渲染文本
}

//按当前(已钳制)recordTop/maxTop设置两键触摸使能: 首页禁用PAGE_UP, 末页禁用PAGE_DOWN, 0条时两键均禁用
//非static: 由dcHmiApp.c的NotifyScreen冷加载回调跨文件调用, 声明见treatmentHmi.h
void listTreatmentRecordUpdatePageKeys(void){
  uint16_t maxTop = listTreatmentRecordMaxTop();
  SetControlEnable(GDDC_PAGE_LIST_RECORD, GDDC_PAGE_LIST_RECORD_KEY_PAGE_UP,
                   (listTreatmentCtx.recordTop > 0U) ? 1U : 0U);
  SetControlEnable(GDDC_PAGE_LIST_RECORD, GDDC_PAGE_LIST_RECORD_KEY_PAGE_DOWN,
                   (listTreatmentCtx.recordTop < maxTop) ? 1U : 0U);
}

//翻页键统一入口(由notify在state=1调用): dir 0=PAGE_UP 1=PAGE_DOWN
//瞬变按钮: 按下直接翻页并按边界更新使能, 无需去抖/延迟; 松开屏幕自动弹起, 互锁由state=0释放
void listTreatmentRecordPageKey(uint8_t dir){
  if(dir != 0U){
    listTreatmentRecordPageDown();
  }
  else{
    listTreatmentRecordPageUp();
  }
  listTreatmentRecordUpdatePageKeys();
}

//向前翻页(记录窗口上移5条)
void listTreatmentRecordPageUp(void){
  if(listTreatmentCtx.recordTop >= LIST_RECORD_WINDOW_SIZE){
    listTreatmentCtx.recordTop = (uint16_t)(listTreatmentCtx.recordTop - LIST_RECORD_WINDOW_SIZE);
    refreshListRecordDisplay();
  }
}

//向后翻页(记录窗口下移5条)
void listTreatmentRecordPageDown(void){
  uint16_t maxTop = listTreatmentRecordMaxTop();
  if(listTreatmentCtx.recordTop < maxTop){
    listTreatmentCtx.recordTop = (uint16_t)(listTreatmentCtx.recordTop + LIST_RECORD_WINDOW_SIZE);
    refreshListRecordDisplay();
  }
}

//CLOSE返回病历列表页(13)
void listTreatmentRecordClose(void){
  listTreatmentCtx.recordPatientId = 0U;
  listTreatmentCtx.editPatientMode = 0U;
  refreshListTreatmentDisplay();
  listTreatmentUpdatePageKeys();//记录页关闭返回: 切屏前恢复两键使能
  NVRAM0[EM_DC_PAGE] = GDDC_PAGE_LIST_TREATMENT;
  SetScreen(GDDC_PAGE_LIST_TREATMENT);
}

//DELETE键统一入口(由notify在state=1调用): 先禁用5个DELETE键关闭触摸窗口, 再进删除确认页, 并解除本页互锁。
//不在手指仍触摸时立即清零(必被活动触摸压过而卡按下); 按下视觉在确认页返回时由NotifyScreen(15)统一清零
void listTreatmentRecordDeleteKey(uint8_t slot){
  uint16_t recPos;
  uint8_t d;
  if(slot >= LIST_RECORD_WINDOW_SIZE){
    treatmentBtnLockReset();
    return;
  }
  recPos = (uint16_t)(listTreatmentCtx.recordTop + slot);
  if(recPos >= listTreatmentCtx.recordCount){
    treatmentBtnLockReset();
    return;
  }
  //清掉可能残留的确认索引(异常中断的上一次流程), 使DeleteStart守卫通过
  listTreatmentCtx.deleteRecordGlobalIndex = 0xFFFFU;
  //1) 立即禁用5个DELETE键: 阻塞切页期间屏幕物理上不接受这些键的新触摸、不产生重复state=1
  for(d = 0U; d < LIST_RECORD_WINDOW_SIZE; d++){
    SetControlEnable(GDDC_PAGE_LIST_RECORD,
                     (uint16_t)(GDDC_PAGE_LIST_RECORD_KEY_DELETE_0 + d), 0U);
  }
  //2) 置确认索引/文案并切到确认页16(DeleteStart守卫此时通过, 其内部recPos校验同样通过)
  listTreatmentRecordDeleteStart(slot);
  //3) 解除本页互锁: 已切到确认页, 其OK/CANCEL会重新武装; 即使内部早退也不残留锁
  treatmentBtnLockReset();
}

//DELETE进入删除确认页(16): slot为记录页窗口内槽位(0-4)
void listTreatmentRecordDeleteStart(uint8_t slot){
  char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
  uint16_t recPos;
  uint16_t globalIndex;
  if(listTreatmentCtx.deleteRecordGlobalIndex != 0xFFFFU){
    return;
  }
  if(slot >= LIST_RECORD_WINDOW_SIZE){
    return;
  }
  recPos = (uint16_t)(listTreatmentCtx.recordTop + slot);
  if(recPos >= listTreatmentCtx.recordCount){
    return;
  }
  globalIndex = listTreatmentCtx.recordWindow[slot];
  listTreatmentCtx.deleteRecordGlobalIndex = globalIndex;
  //TEXT_NAME: 待删记录所属患者"姓名 - AR 编号"(与记录页姓名行同口径); 查不到再回退占位
  {
    uint16_t patientIndex;
    patientRecord_t pat;
    if((treatmentPatientFind(listTreatmentCtx.recordPatientId, &patientIndex) == TREATMENT_EPROM_OK)
       && (treatmentPatientGetByIndex(patientIndex, &pat) == TREATMENT_EPROM_OK)){
      sprintf(dispBuf, "%s - AR %04u", pat.name, (unsigned int)pat.id);
    }
    else{
      sprintf(dispBuf, "-- - AR %04u", (unsigned int)listTreatmentCtx.recordPatientId);
    }
    SetTextValue(GDDC_PAGE_DELETE_RECORD, GDDC_PAGE_DELETE_RECORD_TEXT_NAME,
                 (uint8_t*)dispBuf);
  }
  //摘要: "治疗日期 - 发射能量 - 发射时间 - 发射功率", 显示该条待删记录的真实数据; 读不到再回退通用提示
  {
    treatmentLog_t log;
    if(treatmentEpromGet(globalIndex, &log) == TREATMENT_EPROM_OK){
      uint16_t mm, ss;
      int32_t energyWhole, energyFrac;
      mm = (uint16_t)(log.releaseTime / 60);
      ss = (uint16_t)(log.releaseTime % 60);
      energyWhole = log.releaseEnergy / 10;
      energyFrac = log.releaseEnergy % 10;
      if(energyFrac < 0){
        energyFrac = -energyFrac;
      }
      if(log.rtcYear >= 2000U){
        sprintf(dispBuf,
                "%04u-%02u-%02u %02u:%02u - %d.%d J - %02u:%02u - %d W",
                (unsigned int)log.rtcYear, (unsigned int)log.rtcMonth,
                (unsigned int)log.rtcDay, (unsigned int)log.rtcHour,
                (unsigned int)log.rtcMinute, (int)energyWhole, (int)energyFrac,
                (unsigned int)mm, (unsigned int)ss, (int)log.laserPower);
      }
      else{
        sprintf(dispBuf,
                "---- --:-- - %d.%d J - %02u:%02u - %d W",
                (int)energyWhole, (int)energyFrac, (unsigned int)mm,
                (unsigned int)ss, (int)log.laserPower);
      }
    }
    else{
      sprintf(dispBuf, "Delete this treatment record?");
    }
  }
  SetTextValue(GDDC_PAGE_DELETE_RECORD, GDDC_PAGE_DELETE_RECORD_TEXT_SUMMARY_0,
               (uint8_t*)dispBuf);
  //切页前建立确认页两键"未按下"基线(屏幕会保留自锁键运行态), 防止进入即显示CANCEL/OK按下
  SetButtonValue(GDDC_PAGE_DELETE_RECORD, GDDC_PAGE_DELETE_RECORD_KEY_OK, 0U);
  SetButtonValue(GDDC_PAGE_DELETE_RECORD, GDDC_PAGE_DELETE_RECORD_KEY_CANCEL, 0U);
  NVRAM0[EM_DC_PAGE] = GDDC_PAGE_DELETE_RECORD;
  SetScreen(GDDC_PAGE_DELETE_RECORD);
}

//删除确认页OK: 删除该条记录, 切页前完成记录页清零/重渲染/使能恢复, 再回记录页(15)
void listTreatmentDeleteRecordConfirm(void){
  uint16_t idx = listTreatmentCtx.deleteRecordGlobalIndex;
  if(idx != 0xFFFFU){
    if(idx < treatmentEpromGetCount()){
      treatmentRecordDeleteByIndex(idx);
    }
    listTreatmentCtx.deleteRecordGlobalIndex = 0xFFFFU;
    listTreatmentRecordEnumerate();
  }
  //切页前(确认页仍为当前页)对记录页建立"全部按钮未按下"基线并重渲染、恢复使能;
  //DeviceScreenNotify=0使切页后的NotifyScreen不可靠, 不能依赖返回回调清理
  for(uint16_t btn = GDDC_PAGE_LIST_RECORD_KEY_DELETE_0;
      btn <= GDDC_PAGE_LIST_RECORD_KEY_EDIT_PATIENT; btn++){
    SetButtonValue(GDDC_PAGE_LIST_RECORD, btn, 0U);
  }
  refreshListRecordDisplay();//重渲染: 剩余记录上移回缩, 空槽文本隐藏、DELETE键隐藏并禁用
  listTreatmentRecordUpdatePageKeys();//恢复翻页键使能
  NVRAM0[EM_DC_PAGE] = GDDC_PAGE_LIST_RECORD;
  SetScreen(GDDC_PAGE_LIST_RECORD);
}

//删除确认页CANCEL: 不删除, 切页前同样清零/重渲染/恢复使能, 再回记录页(15)
void listTreatmentDeleteRecordCancel(void){
  listTreatmentCtx.deleteRecordGlobalIndex = 0xFFFFU;
  for(uint16_t btn = GDDC_PAGE_LIST_RECORD_KEY_DELETE_0;
      btn <= GDDC_PAGE_LIST_RECORD_KEY_EDIT_PATIENT; btn++){
    SetButtonValue(GDDC_PAGE_LIST_RECORD, btn, 0U);
  }
  refreshListRecordDisplay();
  listTreatmentRecordUpdatePageKeys();
  NVRAM0[EM_DC_PAGE] = GDDC_PAGE_LIST_RECORD;
  SetScreen(GDDC_PAGE_LIST_RECORD);
}

// ===== 患者信息编辑页(由GDDC_PAGE_LIST_RECORD的GDDC_PAGE_LIST_RECORD_KEY_EDIT_PATIENT进入) =====
// 瞬变按钮按下即触发、松开由屏幕自动弹起, 无需切页基线/延迟/弹出层释放等自锁机制

//实际执行 GDDC_PAGE_LIST_RECORD -> GDDC_PAGE_EDIT_PATIENT:
//预填患者信息, 置更新模式(GDDC_PAGE_EDIT_PATIENT_KEY_OK只更新患者, 不追加记录)
static void listTreatmentDoEditPatient(void){
  uint16_t patientIndex;
  patientRecord_t pat;
  char idBuf[16];
  if((treatmentPatientFind(listTreatmentCtx.recordPatientId, &patientIndex) != TREATMENT_EPROM_OK)
     || (treatmentPatientGetByIndex(patientIndex, &pat) != TREATMENT_EPROM_OK)){
    return;
  }
  memset(&treatmentLog, 0x0, sizeof(treatmentLog));
  treatmentLog.id = pat.id;
  treatmentLog.age = pat.age;
  treatmentLog.gender = (GENDER_ENUM)pat.gender;
  memcpy(treatmentLog.name, pat.name, TREATMENT_NAME_SIZE);
  sprintf(idBuf, "AR %04u", (unsigned int)pat.id);
  listTreatmentCtx.editPatientMode = 1U;
  listTreatmentCtx.editReturnPage = GDDC_PAGE_LIST_RECORD;
  dcHmiShowTreatmentCommon(GDDC_PAGE_EDIT_PATIENT, idBuf, &treatmentLog);
  //性别文本控件: 进入编辑页即按患者性别刷新(男Male/女Female), 与注册页同口径;
  //dcHmiShowTreatmentCommon只更新菜单, 文本需单独下发避免残留
  if(treatmentLog.gender == MALE){
    SetTextValue(GDDC_PAGE_EDIT_PATIENT, GDDC_PAGE_EDIT_PATIENT_TEXT_GENDER, (uint8_t*)"Male");
  }
  else if(treatmentLog.gender == FEMALE){
    SetTextValue(GDDC_PAGE_EDIT_PATIENT, GDDC_PAGE_EDIT_PATIENT_TEXT_GENDER, (uint8_t*)"Female");
  }
  else{
    SetTextValue(GDDC_PAGE_EDIT_PATIENT, GDDC_PAGE_EDIT_PATIENT_TEXT_GENDER, (uint8_t*)"");
  }
  //释放源按钮 GDDC_PAGE_LIST_RECORD_KEY_EDIT_PATIENT 的互锁: 源按钮随旧整页消失, 新页面不得继承该锁
  treatmentBtnLockRelease(GDDC_PAGE_LIST_RECORD, GDDC_PAGE_LIST_RECORD_KEY_EDIT_PATIENT);
  NVRAM0[EM_DC_PAGE] = GDDC_PAGE_EDIT_PATIENT;
  SetScreen(GDDC_PAGE_EDIT_PATIENT);
}

//GDDC_PAGE_LIST_RECORD_KEY_EDIT_PATIENT按下入口: 瞬变按钮按下直接切页(无延迟)
void listTreatmentRecordEditPatient(void){
  listTreatmentDoEditPatient();
}

//患者信息编辑页GDDC_PAGE_EDIT_PATIENT_KEY_OK: 校验后更新患者信息, 回记录页
void listTreatmentEditPatientConfirm(void){
  patientRecord_t row;
  if(listTreatmentCtx.editPatientMode == 0U){
    return;
  }
  if(treatmentLog.name[0] == 0){
    //姓名为空: 停留本页, 瞬变按钮松开由屏幕自动弹起, 不卡按下
    return;
  }
  memset(&row, 0x0, sizeof(row));
  row.id = listTreatmentCtx.recordPatientId;
  row.age = treatmentLog.age;
  row.gender = (uint8_t)treatmentLog.gender;
  memcpy(row.name, treatmentLog.name, TREATMENT_NAME_SIZE);
  treatmentPatientUpdate(listTreatmentCtx.recordPatientId, &row);
  listTreatmentCtx.editPatientMode = 0U;
  NVRAM0[EM_DC_PAGE] = listTreatmentCtx.editReturnPage;
  //冻结画面: 切页过程不可见, 解冻后一次性重绘记录页(防闪烁, 与按钮自锁无关)
  SetScreenUpdateEnable(0U);
  //释放GDDC_PAGE_EDIT_PATIENT_KEY_OK互锁: 瞬变按钮无需清零, 记录页各键默认弹起
  treatmentBtnLockRelease(GDDC_PAGE_EDIT_PATIENT, GDDC_PAGE_EDIT_PATIENT_KEY_OK);
  SetScreen(listTreatmentCtx.editReturnPage);
  SetScreenUpdateEnable(1U);
}

//患者信息编辑页GDDC_PAGE_EDIT_PATIENT_KEY_CANCEL: 不更新, 按来源页返回
void listTreatmentEditPatientCancel(void){
  listTreatmentCtx.editPatientMode = 0U;
  NVRAM0[EM_DC_PAGE] = listTreatmentCtx.editReturnPage;
  //冻结画面: 切页过程不可见, 解冻后一次性重绘记录页(防闪烁)
  SetScreenUpdateEnable(0U);
  //释放GDDC_PAGE_EDIT_PATIENT_KEY_CANCEL互锁: 瞬变按钮无需清零
  treatmentBtnLockRelease(GDDC_PAGE_EDIT_PATIENT, GDDC_PAGE_EDIT_PATIENT_KEY_CANCEL);
  SetScreen(listTreatmentCtx.editReturnPage);
  SetScreenUpdateEnable(1U);
}

//供NotifyButton判断当前编辑页是否为"患者信息更新模式"
uint8_t listTreatmentIsEditPatientMode(void){
  return listTreatmentCtx.editPatientMode;
}

//供NotifyButton判断列表页是否处于核对页"选择已有患者"模式
uint8_t listTreatmentIsVerifySelectMode(void){
  return listTreatmentCtx.verifySelectMode;
}

//核对选择模式下不选择而关闭列表: 取消该模式, 回核对页
void listTreatmentVerifySelectCancel(void){
  listTreatmentCtx.verifySelectMode = 0U;
  listTreatmentEnterVerifyPage();
}

void listTreatmentUsbLoop(void){//USB确认页轮询(非阻塞): 确认页等待按键, 确认后执行一次CSV导出/导入, 完成回USB操作页
  char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
  if(listTreatmentCtx.usbState == 0U){
    return;
  }
  if(NVRAM0[EM_DC_PAGE] != listTreatmentUsbPageOf(listTreatmentCtx.usbState)){//页面被别处切走(如关机确认/休眠): 放弃本次流程
    uint16_t confirmPage = (listTreatmentCtx.usbOp == 2U)
      ? GDDC_PAGE_OPERATOR_USB_LOAD : GDDC_PAGE_OPERATOR_USB_SAVE;
    //中止路径: 本确认页OK/CANCEL都可能处于按下态, 统一弹起并解除互锁避免按键永久锁死
    treatmentReleaseButton(confirmPage, GDDC_PAGE_OPERATOR_USB_SAVE_KEY_OK);
    treatmentReleaseButton(confirmPage, GDDC_PAGE_OPERATOR_USB_SAVE_KEY_CANCEL);
    //恢复按键可用基线(读写期间CANCEL曾被禁用), 便于下次进入确认页状态一致
    SetControlEnable(confirmPage, GDDC_PAGE_OPERATOR_USB_SAVE_KEY_OK, 1);
    SetControlEnable(confirmPage, GDDC_PAGE_OPERATOR_USB_SAVE_KEY_CANCEL, 1);
    listTreatmentCtx.usbState = 0U;//退出忙状态, 否则触摸会被一直屏蔽
    return;
  }
  if(listTreatmentCtx.usbState == 6U){//确认页: 等用户按键, 不做读写
    return;
  }
  if(listTreatmentCtx.usbState == 8U){//完成态: 进度条保持100%, 非阻塞等满停留时长再切回操作页
    if((HAL_GetTick() - listTreatmentCtx.usbDoneTick) < CONFIG_USB_DONE_HOLD_MS){
      return;//停留未满, 保持确认页100%完成态
    }
    //停留满: 恢复OK/CANCEL使能并切回操作页(此时手指已抬起, 恢复不会被活动触摸干扰)
    {
      uint16_t confirmPage = (listTreatmentCtx.usbOp == 2U)
        ? GDDC_PAGE_OPERATOR_USB_LOAD : GDDC_PAGE_OPERATOR_USB_SAVE;
      //先弹起OK并解除互锁, 再恢复OK/CANCEL使能(读写期间两键均被物理禁用)
      treatmentReleaseButton(confirmPage, GDDC_PAGE_OPERATOR_USB_SAVE_KEY_OK);
      SetControlEnable(confirmPage, GDDC_PAGE_OPERATOR_USB_SAVE_KEY_OK, 1);
      SetControlEnable(confirmPage, GDDC_PAGE_OPERATOR_USB_SAVE_KEY_CANCEL, 1);
    }
    NVRAM0[EM_DC_PAGE] = GDDC_PAGE_OPERATOR_USB;
    SetScreen(GDDC_PAGE_OPERATOR_USB);
    listTreatmentCtx.usbState = 0U;//回到空闲, 允许后续触摸
    return;
  }
  //状态7: 已确认, 执行一次导出或导入(完成后切状态8, 停留1秒再切页)
  memset(dispBuf, 0x0, sizeof(dispBuf));
  if(listTreatmentCtx.usbOp == 2U){//导入: 读U盘CSV覆盖机内EPROM, 再回读本机与U盘逐条比较; 载入失败或比较不一致统一按失败提示
    listTreatmentCtx.usbErr = (uint8_t)treatmentLogLoadFromUdisk(&listTreatmentCtx.usbCount);
    if((listTreatmentCtx.usbErr == (uint8_t)TREATMENT_USB_OK) && (treatmentLogVerifyUdisk() != 0U)){
      sprintf(dispBuf, "Backup imported from USB. Device records have been replaced.");
    }
    else{
      sprintf(dispBuf, "USB backup import failed!");
    }
  }
  else{//导出: 机内病历写CSV到U盘; 成功文案由下方"USB backup: X patients, Y treatment records"统一生成
    listTreatmentCtx.usbErr = (uint8_t)treatmentLogSaveToUdisk(&listTreatmentCtx.usbCount);
    if(listTreatmentCtx.usbErr != (uint8_t)TREATMENT_USB_OK){//失败: 按错误码填结果栏; 成功文案在下方统一生成
      if(listTreatmentCtx.usbErr == (uint8_t)TREATMENT_USB_ERR_MOUNT){
        sprintf(dispBuf, "NO UDISK");
      }
      else if(listTreatmentCtx.usbErr == (uint8_t)TREATMENT_USB_ERR_EMPTY){
        sprintf(dispBuf, "NO RECORDS");
      }
      else if(listTreatmentCtx.usbErr == (uint8_t)TREATMENT_USB_ERR_OPEN){
        sprintf(dispBuf, "USB OPEN FAILED");
      }
      else{
        sprintf(dispBuf, "USB BACKUP FAILED");
      }
    }
  }
  //导出成功文案(导入分支已在上面填好); 结果文案交给usbText统一维护, 页面冷加载重发同内容不覆盖
  if((listTreatmentCtx.usbOp != 2U) && (listTreatmentCtx.usbErr == (uint8_t)TREATMENT_USB_OK)){
    memset(dispBuf, 0x0, sizeof(dispBuf));
    sprintf(dispBuf, "USB backup: %u patients, %u treatment records",
      (unsigned int)treatmentEpromGetPatientCount(), (unsigned int)listTreatmentCtx.usbCount);
  }
  setOperatorUsbText(dispBuf);
  refreshOperatorUsbDisplay();//先下发操作页结果帧(当前仍为确认页, 帧目标操作页)
  //状态7完成: 进度条已到100%, 记录完成时刻切状态8, 停留1秒让用户看到100%完成态, 不立即切页
  listTreatmentCtx.usbDoneTick = HAL_GetTick();
  listTreatmentCtx.usbState = 8U;
}
