#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <wincon.h>
#include <conio.h>
#include <string.h>//字符串处理函数
#include <io.h>
#include <fcntl.h>//底层io的mode常量信息
#include <sys\stat.h>//create函数有关头文件（信息来自网络，自己加的，可能不加也好使）
#include <sys/types.h>//create函数有关头文件（信息来自网络，自己加的，可能不加也好使）
#include <ctype.h>
#include <time.h>//获取系统时间
#include <unistd.h>   //获得当前工作路径,改变当前目录的函数所在头文件

#ifndef TYPE_H_INCLUDED
#define TYPE_H_INCLUDED

#define SCR_ROW 25             /*屏幕行数*/
#define SCR_COL 80             /*屏幕列数*/

/*储存三类基本信息的结构*/
typedef struct sch_node {
    char sch_name[20];         /**< 院系名称*/
    char boss_name[12];           /**< 负责人姓名*/
    char tel[15];            /**< 联系电话*/

    struct team_node *tnext;  /**< 指向科研团队基本信息支链的指针*/
    struct sch_node *next;  /**< 指向下一结点的指针*/
} SCH_NODE;

typedef struct team_node {
    char team_name[30];         /**< 团队名称*/
    char boss_name[12];           /**< 负责人*/
    int  prof_num;            /**< 教师人数*/
    int  stu_num;          /**< 研究生人数*/
    char sch[20];       /**< 所属院系*/

    struct sciprj_node *snext;  /**< 指向科研项目基本信息支链的指针*/
    struct team_node *next;  /**< 指向下一结点的指针*/
} TEAM_NODE;


typedef struct sciprj_node {
    char prj_num[15];    /**< 项目编号*/
    char type;           /**< 项目类别*/
    char start_time[10];   /**< 起始时间*/
    float prj_fund;       /**< 项目经费 （万元）*/
    char  boss_name[12];  /**< 项目负责人*/
    char  team[30]  ;      /**< 所属团队*/

    struct sciprj_node *next;  /**< 指向下一结点的指针*/
} SCIPRJ_NODE;



extern char *gp_sys_name ;    /*系统名称*/
extern char *gp_team_info_filename;        /*科研团队基本信息数据文件*/
extern char *gp_sciprj_info_filename;  /*科研项目基本信息数据文件*/
extern char *gp_sch_info_filename;      /*院系基本信息数据文件*/



/**
 *屏幕窗口信息链结点结点结构
 */
typedef struct layer_node {
    char LayerNo;            /**< 弹出窗口层数*/
    SMALL_RECT rcArea;       /**< 弹出窗口区域坐标*/
    CHAR_INFO *pContent;     /**< 弹出窗口区域字符单元原信息存储缓冲区*/
    char *pScrAtt;           /**< 弹出窗口区域字符单元原属性值存储缓冲区*/
    struct layer_node *next; /**< 指向下一结点的指针*/
} LAYER_NODE;

/**
 *标签束结构
 */
typedef struct labe1_bundle {
    char **ppLabel;        /**< 标签字符串数组首地址*/
    COORD *pLoc;           /**< 标签定位数组首地址*/
    int num;               /**< 标签个数*/
} LABEL_BUNDLE;

/**
 *热区结构
 */
typedef struct hot_area {
    SMALL_RECT *pArea;     /**< 热区定位数组首地址*/
    char *pSort;           /**< 热区类别(按键、文本框、选项框)数组首地址*/
    char *pTag;            /**< 热区序号数组首地址*/
    int num;               /**< 热区个数*/
} HOT_AREA;

extern LAYER_NODE *gp_top_layer ;               /*弹出窗口信息链链头*/
extern SCH_NODE *gp_head ;                     /*主链头指针*/



extern char *ga_main_menu[];       /*系统主菜单名*/

extern char *ga_sub_menu[] ;         /*系统子菜单名*/


extern int ga_sub_menu_count[];  /*各主菜单项下子菜单的个数*/
extern int gi_sel_menu ;                        /*被选中的主菜单项号,初始为1*/
extern int gi_sel_sub_menu ;                    /*被选中的子菜单项号,初始为0,表示未选中*/

extern CHAR_INFO *gp_buff_menubar_info;     /*存放菜单条屏幕区字符信息的缓冲区*/
extern CHAR_INFO *gp_buff_stateBar_info;    /*存放状态条屏幕区字符信息的缓冲区*/

extern char *gp_scr_att ;    /*存放屏幕上字符单元属性值的缓冲区*/
extern char gc_sys_state ;   /*用来保存系统状态的字符*/


extern HANDLE gh_std_out;          /*标准输出设备句柄*/
extern HANDLE gh_std_in;           /*标准输入设备句柄*/



extern CONSOLE_CURSOR_INFO lpCur;  //存储光标信息
extern unsigned long ul;    //储存某些函数的无用的返回值，比如字符填充函数成功填充了多少个字符


/*UI函数*/
int CreatList(SCH_NODE **pphead);              /*数据链表初始化*/
void InitInterface(void);                 /*系统界面初始化*/
void ClearScreen(void);                         /*清屏*/
void ShowMenu(void);                            /*显示菜单栏*/
void PopMenu(int num);                          /*显示下拉菜单*/
void PopPrompt(int num);                        /*显示弹出窗口*/
void PopUp(SMALL_RECT *, WORD, LABEL_BUNDLE *, HOT_AREA *);  /*弹出窗口屏幕信息维护*/
void PopOff(void);                              /*关闭顶层弹出窗口*/
void DrawBox(SMALL_RECT *parea);                /*绘制边框*/
void LocSubMenu(int num, SMALL_RECT *parea);    /*主菜单下拉菜单定位*/
void ShowState(void);                           /*显示状态栏*/
void TagMainMenu(int num);                      /*标记被选中的主菜单项*/
void TagSubMenu(int num);                       /*标记被选中的子菜单项*/
int DealInput(HOT_AREA *phot_area, int *pihot_num);  /*控制台输入处理*/
void SetHotPoint(HOT_AREA *phot_area, int hot_num);     /*设置热区*/
void RunSys(SCH_NODE **pphd);                  /*系统功能模块的选择和运行*/
BOOL ExeFunction(int main_menu_num, int sub_menu_num);  /*功能模块的调用*/
void CloseSys(SCH_NODE *phd);                  /*退出系统*/
BOOL ShowModule(char **pString, int n); //  弹出提示框

/*接口函数*/
BOOL LoadData(void);           /*数据加载*/
BOOL SaveData(void);           /*保存数据*/
BOOL BackupData(void);         /*备份数据*/
BOOL RestoreData(void);        /*恢复数据*/
BOOL ExitSys(void);            /*退出系统*/
BOOL HelpTopic(void);          /*帮助主体*/
BOOL AboutSystem(void);          /*关于系统*/

BOOL Warnings(void);    /*输出警告信息*/
BOOL MaintainInfofile(void);   /*直接维护储存信息的文件*/
BOOL MaintainSchInfo(void);   /*维护院系基本信息 */
BOOL MaintainTeamInfo(void);    /*维护科研团队基本信息*/
BOOL MaintainSciprjInfo(void); /*维护科研项目信息*/

BOOL QueryWarnings(void);       /*查询警告*/
BOOL QueryAllInfo(void);          /*查询输出所有信息*/
BOOL QuerySchInfo(void);      /*查院系基本信息*/
BOOL QueryTeamInfo(void);       /*查询科研团队基本信息*/
BOOL QuerySciprjInfo(void);    /*查询科研项目基本信息*/

BOOL StatResearcherNumberInfo(void);       /*统计科研人员信息*/
BOOL StatSciprjNumberInfo(void);        /*统计科研项目信息*/
BOOL StatNatureScienceTop10(void);         /*统计国家自科基金top10*/
BOOL StatPrjAndProfRate(void);       /* 统计项目/人 排行*/
BOOL OtherStat(void);                /*其他统计*/ //这里为最土豪团队


/*功能函数*/
BOOL SchInfoInput(void); //把院系信息输入并储存到链表，但是不储存到本地文件
BOOL SchInfoMod(void); //修改院系基本信息并存储到链表，但是不储存到本地文件
void ClearScreenTotalInputArea(void) ;   //清除屏幕中除了第一行（主菜单）以外的所有内容
SCH_NODE* SeekSchNode(SCH_NODE *hp,char *sch_name);  //查找院系信息链表的某个结点
SCH_NODE* SchInfoDel(SCH_NODE **hp, char* sch_name);  // 删除一个sch_name等于形参中sch_name结点,这个函数虽然是针对院系信息的，但是可以灵活使用；
BOOL SchInfoDelete(void);  //删除一个院系信息链表中的节点的具体实现模块，其中调用了SCH_NODE* SchInfoDel函数
BOOL TeamInfoInput(void);  //把团队信息输入并储存到链表，但是不储存到本地文件
TEAM_NODE* SeekTeamNode(TEAM_NODE*hp, char *team_name);//查找团队信息的某个节点
BOOL TeamInfoMod(void);  //修改某个院系下某个科研团队的信息的函数
TEAM_NODE* TeamInfoDel(TEAM_NODE **hp, char* team_name);  //给一个头指针，然后删除科研团队名为team_name的那个结点
BOOL TeamInfoDelete(void);  //删除一个科研团队信息结点的具体实现
SCIPRJ_NODE* SeekSciprjNode(SCIPRJ_NODE* hp,char* prj_num) ; //查找科研项目信息的某个节点
BOOL SciprjInfoInput(void); //把科研项目信息输入并储存到链表，但是不储存到本地文件
BOOL SciprjInfoMod(void); //修改某个院系下某个科研项目的信息的函数
BOOL SciprjInfoDelete(void);//删除一个科研项目信息结点的具体实现
SCIPRJ_NODE* SciprjInfoDel(SCIPRJ_NODE **hp, char* prj_num);//给一个头指针，然后删除科研项目编号为team_name的那个结点
void SpaceToUnderline(char*s) ;//C语言中create函数能创建的文件的文件名只能是标识符，因此把系统时间字符串中的冒号的空格变成下划线
void AddBackslash(char*s) ;//在一个不可能连续出现2个或两个以上 \ 字符的字符串中，把出现的 \ 字符变成  "\\"
void GetBackupFilename(char *dir );//得到包含路径的备份文件名,储存在字符串dir中，！且作为实参的字符串必须只能占100字节！
BOOL QuerySchInfoViaBossname(void); //查询院系基本信息的大函数中的实现主要功能的小函数,这个函数的功能是通过负责人查询院系信息
BOOL Choice(char*pCh[],int n);//弹出提示框，选择“是”  还是“否” ，并返回相应布尔值的函数，需要的参数是：需要提示框输出的字符串数组
BOOL QuerySchInfoViaSchsname(void);//以院系名称的全部或一部分为条件来查找并显示满足条件的院系基本信息
BOOL QueryTeamInfoViaTeamname(void);//以团队名称的全部或一部分为条件来查找并显示满足条件的团队基本信息
BOOL QuerySchInfoViaProfnum(void);//通过科研团队教师人数下限来查询科研团队基本信息
BOOL QuerySciprjInfoViaID(void);//通过项目编号查询科研团队基本信息
BOOL QuerySciprjInfoViaTeam(void);//通过项目所属团队查询项目基本信息
BOOL StatResearcherNumInfo(void);//统计各院系教师总数，研究生总数，及研究生与教师的人数比（保留 2 位小数），按学生教师 人数比值降序排序后，输出统计结果
BOOL StatSciprjNumInfo(void);//统计某年度各院系科研项目数，973 项目数，863 项目数，及科研总经费，科研项目数降序排 序后输出；
BOOL JudgeYearRight(char *s);//判断输入的字符串是否形如 “2017”  是返回TRUE  否则返回FALSE
BOOL JudgeYearEqual(char *s , char *t);//判断两个字符串的前4个字符是否全等，用来判断一个日期（如20170901）是否属于一个年份（2017）
BOOL StatNatureSciTop10(void);//统计历年来类别为国家自然科学基金的科研项目数最多的 10 个科研团队，按项目数降序排序 后输出科研团队名称，类别为国家自然科学基金的科研项目数，以及项目经费总数。
BOOL StatFundProfRate(void);//统计人均科研经费的具体实现函数
BOOL StatPrjProfRate(void);//统计科研项目数和教师人数的比值最高的 5 个科研团队，按比值（保留两位小数）
BOOL QueryAll(void);//遍历所有信息并输出
BOOL Help(void);//输出帮助文档

/*系统数据函数*/
BOOL SaveSysData(void);                       /*保存系统数据*/
BOOL BackupSysData(SCH_NODE *hd, char *filename);     /*备份系统数据*/
BOOL RestoreSysData(SCH_NODE **pphd, char *filename);  /*恢复系统数据*/

#endif /**< TYPE_H_INCLUDED*/





