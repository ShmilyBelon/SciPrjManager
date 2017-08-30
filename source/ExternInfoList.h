#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <wincon.h>
#include <conio.h>
#include <string.h>//�ַ���������
#include <io.h>
#include <fcntl.h>//�ײ�io��mode������Ϣ
#include <sys\stat.h>//create�����й�ͷ�ļ�����Ϣ�������磬�Լ��ӵģ����ܲ���Ҳ��ʹ��
#include <sys/types.h>//create�����й�ͷ�ļ�����Ϣ�������磬�Լ��ӵģ����ܲ���Ҳ��ʹ��
#include <ctype.h>
#include <time.h>//��ȡϵͳʱ��
#include <unistd.h>   //��õ�ǰ����·��,�ı䵱ǰĿ¼�ĺ�������ͷ�ļ�

#ifndef TYPE_H_INCLUDED
#define TYPE_H_INCLUDED

#define SCR_ROW 25             /*��Ļ����*/
#define SCR_COL 80             /*��Ļ����*/

/*�������������Ϣ�Ľṹ*/
typedef struct sch_node {
    char sch_name[20];         /**< Ժϵ����*/
    char boss_name[12];           /**< ����������*/
    char tel[15];            /**< ��ϵ�绰*/

    struct team_node *tnext;  /**< ָ������Ŷӻ�����Ϣ֧����ָ��*/
    struct sch_node *next;  /**< ָ����һ����ָ��*/
} SCH_NODE;

typedef struct team_node {
    char team_name[30];         /**< �Ŷ�����*/
    char boss_name[12];           /**< ������*/
    int  prof_num;            /**< ��ʦ����*/
    int  stu_num;          /**< �о�������*/
    char sch[20];       /**< ����Ժϵ*/

    struct sciprj_node *snext;  /**< ָ�������Ŀ������Ϣ֧����ָ��*/
    struct team_node *next;  /**< ָ����һ����ָ��*/
} TEAM_NODE;


typedef struct sciprj_node {
    char prj_num[15];    /**< ��Ŀ���*/
    char type;           /**< ��Ŀ���*/
    char start_time[10];   /**< ��ʼʱ��*/
    float prj_fund;       /**< ��Ŀ���� ����Ԫ��*/
    char  boss_name[12];  /**< ��Ŀ������*/
    char  team[30]  ;      /**< �����Ŷ�*/

    struct sciprj_node *next;  /**< ָ����һ����ָ��*/
} SCIPRJ_NODE;



extern char *gp_sys_name ;    /*ϵͳ����*/
extern char *gp_team_info_filename;        /*�����Ŷӻ�����Ϣ�����ļ�*/
extern char *gp_sciprj_info_filename;  /*������Ŀ������Ϣ�����ļ�*/
extern char *gp_sch_info_filename;      /*Ժϵ������Ϣ�����ļ�*/



/**
 *��Ļ������Ϣ�������ṹ
 */
typedef struct layer_node {
    char LayerNo;            /**< �������ڲ���*/
    SMALL_RECT rcArea;       /**< ����������������*/
    CHAR_INFO *pContent;     /**< �������������ַ���Ԫԭ��Ϣ�洢������*/
    char *pScrAtt;           /**< �������������ַ���Ԫԭ����ֵ�洢������*/
    struct layer_node *next; /**< ָ����һ����ָ��*/
} LAYER_NODE;

/**
 *��ǩ���ṹ
 */
typedef struct labe1_bundle {
    char **ppLabel;        /**< ��ǩ�ַ��������׵�ַ*/
    COORD *pLoc;           /**< ��ǩ��λ�����׵�ַ*/
    int num;               /**< ��ǩ����*/
} LABEL_BUNDLE;

/**
 *�����ṹ
 */
typedef struct hot_area {
    SMALL_RECT *pArea;     /**< ������λ�����׵�ַ*/
    char *pSort;           /**< �������(�������ı���ѡ���)�����׵�ַ*/
    char *pTag;            /**< ������������׵�ַ*/
    int num;               /**< ��������*/
} HOT_AREA;

extern LAYER_NODE *gp_top_layer ;               /*����������Ϣ����ͷ*/
extern SCH_NODE *gp_head ;                     /*����ͷָ��*/



extern char *ga_main_menu[];       /*ϵͳ���˵���*/

extern char *ga_sub_menu[] ;         /*ϵͳ�Ӳ˵���*/


extern int ga_sub_menu_count[];  /*�����˵������Ӳ˵��ĸ���*/
extern int gi_sel_menu ;                        /*��ѡ�е����˵����,��ʼΪ1*/
extern int gi_sel_sub_menu ;                    /*��ѡ�е��Ӳ˵����,��ʼΪ0,��ʾδѡ��*/

extern CHAR_INFO *gp_buff_menubar_info;     /*��Ų˵�����Ļ���ַ���Ϣ�Ļ�����*/
extern CHAR_INFO *gp_buff_stateBar_info;    /*���״̬����Ļ���ַ���Ϣ�Ļ�����*/

extern char *gp_scr_att ;    /*�����Ļ���ַ���Ԫ����ֵ�Ļ�����*/
extern char gc_sys_state ;   /*��������ϵͳ״̬���ַ�*/


extern HANDLE gh_std_out;          /*��׼����豸���*/
extern HANDLE gh_std_in;           /*��׼�����豸���*/



extern CONSOLE_CURSOR_INFO lpCur;  //�洢�����Ϣ
extern unsigned long ul;    //����ĳЩ���������õķ���ֵ�������ַ���亯���ɹ�����˶��ٸ��ַ�


/*UI����*/
int CreatList(SCH_NODE **pphead);              /*���������ʼ��*/
void InitInterface(void);                 /*ϵͳ�����ʼ��*/
void ClearScreen(void);                         /*����*/
void ShowMenu(void);                            /*��ʾ�˵���*/
void PopMenu(int num);                          /*��ʾ�����˵�*/
void PopPrompt(int num);                        /*��ʾ��������*/
void PopUp(SMALL_RECT *, WORD, LABEL_BUNDLE *, HOT_AREA *);  /*����������Ļ��Ϣά��*/
void PopOff(void);                              /*�رն��㵯������*/
void DrawBox(SMALL_RECT *parea);                /*���Ʊ߿�*/
void LocSubMenu(int num, SMALL_RECT *parea);    /*���˵������˵���λ*/
void ShowState(void);                           /*��ʾ״̬��*/
void TagMainMenu(int num);                      /*��Ǳ�ѡ�е����˵���*/
void TagSubMenu(int num);                       /*��Ǳ�ѡ�е��Ӳ˵���*/
int DealInput(HOT_AREA *phot_area, int *pihot_num);  /*����̨���봦��*/
void SetHotPoint(HOT_AREA *phot_area, int hot_num);     /*��������*/
void RunSys(SCH_NODE **pphd);                  /*ϵͳ����ģ���ѡ�������*/
BOOL ExeFunction(int main_menu_num, int sub_menu_num);  /*����ģ��ĵ���*/
void CloseSys(SCH_NODE *phd);                  /*�˳�ϵͳ*/
BOOL ShowModule(char **pString, int n); //  ������ʾ��

/*�ӿں���*/
BOOL LoadData(void);           /*���ݼ���*/
BOOL SaveData(void);           /*��������*/
BOOL BackupData(void);         /*��������*/
BOOL RestoreData(void);        /*�ָ�����*/
BOOL ExitSys(void);            /*�˳�ϵͳ*/
BOOL HelpTopic(void);          /*��������*/
BOOL AboutSystem(void);          /*����ϵͳ*/

BOOL Warnings(void);    /*���������Ϣ*/
BOOL MaintainInfofile(void);   /*ֱ��ά��������Ϣ���ļ�*/
BOOL MaintainSchInfo(void);   /*ά��Ժϵ������Ϣ */
BOOL MaintainTeamInfo(void);    /*ά�������Ŷӻ�����Ϣ*/
BOOL MaintainSciprjInfo(void); /*ά��������Ŀ��Ϣ*/

BOOL QueryWarnings(void);       /*��ѯ����*/
BOOL QueryAllInfo(void);          /*��ѯ���������Ϣ*/
BOOL QuerySchInfo(void);      /*��Ժϵ������Ϣ*/
BOOL QueryTeamInfo(void);       /*��ѯ�����Ŷӻ�����Ϣ*/
BOOL QuerySciprjInfo(void);    /*��ѯ������Ŀ������Ϣ*/

BOOL StatResearcherNumberInfo(void);       /*ͳ�ƿ�����Ա��Ϣ*/
BOOL StatSciprjNumberInfo(void);        /*ͳ�ƿ�����Ŀ��Ϣ*/
BOOL StatNatureScienceTop10(void);         /*ͳ�ƹ����Կƻ���top10*/
BOOL StatPrjAndProfRate(void);       /* ͳ����Ŀ/�� ����*/
BOOL OtherStat(void);                /*����ͳ��*/ //����Ϊ�������Ŷ�


/*���ܺ���*/
BOOL SchInfoInput(void); //��Ժϵ��Ϣ���벢���浽�������ǲ����浽�����ļ�
BOOL SchInfoMod(void); //�޸�Ժϵ������Ϣ���洢���������ǲ����浽�����ļ�
void ClearScreenTotalInputArea(void) ;   //�����Ļ�г��˵�һ�У����˵����������������
SCH_NODE* SeekSchNode(SCH_NODE *hp,char *sch_name);  //����Ժϵ��Ϣ�����ĳ�����
SCH_NODE* SchInfoDel(SCH_NODE **hp, char* sch_name);  // ɾ��һ��sch_name�����β���sch_name���,���������Ȼ�����Ժϵ��Ϣ�ģ����ǿ������ʹ�ã�
BOOL SchInfoDelete(void);  //ɾ��һ��Ժϵ��Ϣ�����еĽڵ�ľ���ʵ��ģ�飬���е�����SCH_NODE* SchInfoDel����
BOOL TeamInfoInput(void);  //���Ŷ���Ϣ���벢���浽�������ǲ����浽�����ļ�
TEAM_NODE* SeekTeamNode(TEAM_NODE*hp, char *team_name);//�����Ŷ���Ϣ��ĳ���ڵ�
BOOL TeamInfoMod(void);  //�޸�ĳ��Ժϵ��ĳ�������Ŷӵ���Ϣ�ĺ���
TEAM_NODE* TeamInfoDel(TEAM_NODE **hp, char* team_name);  //��һ��ͷָ�룬Ȼ��ɾ�������Ŷ���Ϊteam_name���Ǹ����
BOOL TeamInfoDelete(void);  //ɾ��һ�������Ŷ���Ϣ���ľ���ʵ��
SCIPRJ_NODE* SeekSciprjNode(SCIPRJ_NODE* hp,char* prj_num) ; //���ҿ�����Ŀ��Ϣ��ĳ���ڵ�
BOOL SciprjInfoInput(void); //�ѿ�����Ŀ��Ϣ���벢���浽�������ǲ����浽�����ļ�
BOOL SciprjInfoMod(void); //�޸�ĳ��Ժϵ��ĳ��������Ŀ����Ϣ�ĺ���
BOOL SciprjInfoDelete(void);//ɾ��һ��������Ŀ��Ϣ���ľ���ʵ��
SCIPRJ_NODE* SciprjInfoDel(SCIPRJ_NODE **hp, char* prj_num);//��һ��ͷָ�룬Ȼ��ɾ��������Ŀ���Ϊteam_name���Ǹ����
void SpaceToUnderline(char*s) ;//C������create�����ܴ������ļ����ļ���ֻ���Ǳ�ʶ������˰�ϵͳʱ���ַ����е�ð�ŵĿո����»���
void AddBackslash(char*s) ;//��һ����������������2������������ \ �ַ����ַ����У��ѳ��ֵ� \ �ַ����  "\\"
void GetBackupFilename(char *dir );//�õ�����·���ı����ļ���,�������ַ���dir�У�������Ϊʵ�ε��ַ�������ֻ��ռ100�ֽڣ�
BOOL QuerySchInfoViaBossname(void); //��ѯԺϵ������Ϣ�Ĵ����е�ʵ����Ҫ���ܵ�С����,��������Ĺ�����ͨ�������˲�ѯԺϵ��Ϣ
BOOL Choice(char*pCh[],int n);//������ʾ��ѡ���ǡ�  ���ǡ��� ����������Ӧ����ֵ�ĺ�������Ҫ�Ĳ����ǣ���Ҫ��ʾ��������ַ�������
BOOL QuerySchInfoViaSchsname(void);//��Ժϵ���Ƶ�ȫ����һ����Ϊ���������Ҳ���ʾ����������Ժϵ������Ϣ
BOOL QueryTeamInfoViaTeamname(void);//���Ŷ����Ƶ�ȫ����һ����Ϊ���������Ҳ���ʾ�����������Ŷӻ�����Ϣ
BOOL QuerySchInfoViaProfnum(void);//ͨ�������Ŷӽ�ʦ������������ѯ�����Ŷӻ�����Ϣ
BOOL QuerySciprjInfoViaID(void);//ͨ����Ŀ��Ų�ѯ�����Ŷӻ�����Ϣ
BOOL QuerySciprjInfoViaTeam(void);//ͨ����Ŀ�����ŶӲ�ѯ��Ŀ������Ϣ
BOOL StatResearcherNumInfo(void);//ͳ�Ƹ�Ժϵ��ʦ�������о������������о������ʦ�������ȣ����� 2 λС��������ѧ����ʦ ������ֵ������������ͳ�ƽ��
BOOL StatSciprjNumInfo(void);//ͳ��ĳ��ȸ�Ժϵ������Ŀ����973 ��Ŀ����863 ��Ŀ�����������ܾ��ѣ�������Ŀ�������� ��������
BOOL JudgeYearRight(char *s);//�ж�������ַ����Ƿ����� ��2017��  �Ƿ���TRUE  ���򷵻�FALSE
BOOL JudgeYearEqual(char *s , char *t);//�ж������ַ�����ǰ4���ַ��Ƿ�ȫ�ȣ������ж�һ�����ڣ���20170901���Ƿ�����һ����ݣ�2017��
BOOL StatNatureSciTop10(void);//ͳ�����������Ϊ������Ȼ��ѧ����Ŀ�����Ŀ������ 10 �������Ŷӣ�����Ŀ���������� ����������Ŷ����ƣ����Ϊ������Ȼ��ѧ����Ŀ�����Ŀ�����Լ���Ŀ����������
BOOL StatFundProfRate(void);//ͳ���˾����о��ѵľ���ʵ�ֺ���
BOOL StatPrjProfRate(void);//ͳ�ƿ�����Ŀ���ͽ�ʦ�����ı�ֵ��ߵ� 5 �������Ŷӣ�����ֵ��������λС����
BOOL QueryAll(void);//����������Ϣ�����
BOOL Help(void);//��������ĵ�

/*ϵͳ���ݺ���*/
BOOL SaveSysData(void);                       /*����ϵͳ����*/
BOOL BackupSysData(SCH_NODE *hd, char *filename);     /*����ϵͳ����*/
BOOL RestoreSysData(SCH_NODE **pphd, char *filename);  /*�ָ�ϵͳ����*/

#endif /**< TYPE_H_INCLUDED*/





