#include"ExternInfoList.h"


/**
 * 函数名称: LoadData
 * 函数功能: 将三类基础数据从数据文件载入到内存缓冲区和十字链表中.
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值: BOOL类型, 功能函数中除了函数ExitSys的返回值可以为FALSE外,
 *           其他函数的返回值必须为TRUE.
 *
 * 调用说明: 为了能够以统一的方式调用各功能函数, 将这些功能函数的原型设为
 *           一致, 即无参数且返回值为BOOL. 返回值为FALSE时, 结束程序运行.
 */
BOOL LoadData()
{
    int Re = 0;

    Re = CreatList(&gp_head);
    gc_sys_state |= Re;
    gc_sys_state &= ~(4 + 8 + 16 - Re);
    if (gc_sys_state < ( 4 | 8 | 16))
    {  /*数据加载提示信息*/
        printf("\n系统基础数据不完整!\n");
        printf("\n按任意键继续...\n");
        getch();

    }


    return TRUE;
}


/**
 * 函数名称: CreatList
 * 函数功能: 从数据文件读取基础数据, 并存放到所创建的十字链表中.
 * 输入参数: 无
 * 输出参数: phead 主链头指针的地址, 用来返回所创建的十字链.
 * 返 回 值: int型数值, 表示链表创建的情况.
 *           0  空链, 无数据
 *           4  已加载宿舍楼信息数据，无学生基本信息和缴费信息数据
 *           12 已加载宿舍楼信息和学生基本信息数据，无缴费信息数据
 *           28 三类基础数据都已加载
 *
 * 调用说明:
 */
int CreatList(SCH_NODE **phead)
{
    SCH_NODE *hd = NULL, *pSchNode, tmp1;
    TEAM_NODE *pTeamNode, tmp2;
    SCIPRJ_NODE *pSciprjNode, tmp3;
    FILE *pFile;
    int find;
    int re = 0;

    char dir_current[100];//用来储存当前的工作目录
    char dir_togo[100];//用来存放 要更改成的新的目录 的地址字符串
    char DataDir[7]="\\data";//存放数据文件的那一层目录

    getcwd(dir_current,sizeof(dir_current));//获取当前工作目录
    getcwd(dir_togo,sizeof(dir_togo));//再次获取当前工作目录

    strcat(dir_togo,DataDir);//在当前工作地址之后加上\data构造数据文件夹所在目录
    AddBackslash(dir_togo);//把整个路径字符串里面所有的单个 \ 变成\\  以便当做文件名字符串在create等函数中做实参时 \\ 转意成 “\”
    AddBackslash(dir_current);//把整个路径字符串里面所有的单个 \ 变成\\  以便当做文件名字符串在create等函数中做实参时 \\ 转意成 “\”

    chdir(dir_togo);//更改当前工作目录为数据文件夹所在的目录，以便下面的程序在这个目录下 载入这个数据文件夹中的数据文件



    if ((pFile = fopen(gp_sch_info_filename, "rb")) == NULL)
    {
        printf("院系信息数据文件打开失败!\n");
        return re;
    }
    printf("院系信息数据文件打开成功!\n");

    /*从数据文件中读院系信息数据，存入以后进先出方式建立的主链中*/
    while (fread(&tmp1, sizeof(SCH_NODE), 1, pFile) == 1)
    {
        pSchNode = (SCH_NODE *)malloc(sizeof(SCH_NODE));
        *pSchNode = tmp1;
        pSchNode->tnext = NULL;
        pSchNode->next = hd;
        hd = pSchNode;
    }
    fclose(pFile);
    if (hd == NULL)
    {
        printf("院系信息数据文件加载失败!\n");
        return re;
    }
    printf("院系信息数据文件加载成功!\n");
    *phead = hd;
    re += 4;

    if ((pFile = fopen(gp_team_info_filename, "rb")) == NULL)
    {
        printf("科研团队基本信息数据文件打开失败!\n");
        return re;
    }
    printf("科研团队基本信息数据文件打开成功!\n");
    re += 8;

    /*从数据文件中读取科研团队基本信息数据，存入主链对应结点的科研团队基本信息支链中*/
    while (fread(&tmp2, sizeof(TEAM_NODE), 1, pFile) == 1)
    {
        /*创建结点，存放从数据文件中读出的科研团队基本信息*/
        pTeamNode = (TEAM_NODE *)malloc(sizeof(TEAM_NODE));
        *pTeamNode = tmp2;
        pTeamNode->snext = NULL;

        /*在主链上查找该科研团队所在院系对应的主链结点*/
        pSchNode = hd;
        while (pSchNode != NULL
               && strcmp(pSchNode->sch_name, pTeamNode->sch) != 0)
        {
            pSchNode = pSchNode->next;
        }
        if (pSchNode != NULL) /*如果找到，则将结点以后进先出方式插入科研团队信息支链*/
        {
            pTeamNode->next = pSchNode->tnext;
            pSchNode->tnext = pTeamNode;
        }
        else  /*如果未找到，则释放所创建结点的内存空间*/
        {
            free(pTeamNode);
        }
    }
    fclose(pFile);

    if ((pFile = fopen(gp_sciprj_info_filename, "rb")) == NULL)
    {
        printf("科研项目信息数据文件打开失败!\n");
        return re;
    }
    printf("科研项目信息数据文件打开成功!\n");
    re += 16;

    /*从数据文件中读取科研项目信息数据，存入科研团队基本信息支链对应结点的科研项目支链中*/
    while (fread(&tmp3, sizeof(SCIPRJ_NODE), 1, pFile) == 1)
    {
        /*创建结点，存放从数据文件中读出的科研项目缴费信息*/
        pSciprjNode = (SCIPRJ_NODE *)malloc(sizeof(SCIPRJ_NODE));
        *pSciprjNode = tmp3;

        /*查找团队信息支链上对应团队信息结点*/
        pSchNode = hd;
        find = 0;
        while (pSchNode != NULL && find == 0)
        {
            pTeamNode = pSchNode->tnext;
            while (pTeamNode != NULL && find == 0)
            {
                if (strcmp(pTeamNode->team_name, pSciprjNode->team) == 0)
                {
                    find = 1;
                    break;
                }
                pTeamNode = pTeamNode->next;
            }
            pSchNode = pSchNode->next;
        }
        if (find)  /*如果找到，则将结点以后进先出方式插入科研项目信息支链中*/
        {
            pSciprjNode->next = pTeamNode->snext;
            pTeamNode->snext = pSciprjNode;
        }
        else /*如果未找到，则释放所创建结点的内存空间*/
        {
            free(pSciprjNode);
        }
    }
    fclose(pFile);


    chdir(dir_current);//把目录更改为原来的工作目录




    return re;
}



/**
 * 函数名称: SaveSysData
 * 函数功能: 保存三类基础数据.
 * 输入参数: void
 * 输出参数:
 * 返 回 值: BOOL类型, 总是为TRUE
 *
 * 调用说明:
 */
BOOL SaveSysData(void) //和书上不一样，因为我的理念是，反正总是从全局变量gp_head开始保存，因此就不用形参了；
{

    SCH_NODE *psch_node;
    TEAM_NODE *pteam_node;
    SCIPRJ_NODE *psciprj_node;
    FILE *pfout;
    //int handle;
    char dir_current[100];//用来储存当前的工作目录
    char dir_togo[100];//用来存放 要更改成的新的目录 的地址字符串
    char DataDir[7]="\\data";//存放数据文件的那一层目录

    getcwd(dir_current,sizeof(dir_current));//获取当前工作目录
    getcwd(dir_togo,sizeof(dir_togo));//再次获取当前工作目录

    strcat(dir_togo,DataDir);//在当前工作地址之后加上\data构造数据文件夹所在目录
    AddBackslash(dir_togo);//把整个路径字符串里面所有的单个 \ 变成\\  以便当做文件名字符串在create等函数中做实参时 \\ 转意成 “\”
    AddBackslash(dir_current);//把整个路径字符串里面所有的单个 \ 变成\\  以便当做文件名字符串在create等函数中做实参时 \\ 转意成 “\”

    chdir(dir_togo);//更改当前工作目录为数据文件夹所在的目录，以便下面的程序在这个目录下 载入这个数据文件夹中的数据文件

    pfout=fopen(gp_sch_info_filename,"wb");  //保存院系基本信息
    for(psch_node=gp_head;psch_node!=NULL;psch_node=psch_node->next)
    {
        fwrite(psch_node,sizeof(SCH_NODE),1,pfout);

    }

    fclose(pfout);


    pfout=fopen(gp_team_info_filename,"wb");//保存科研团队基本信息
    for(psch_node=gp_head;psch_node!=NULL;psch_node=psch_node->next)
    {
        pteam_node=psch_node->tnext;
        while(pteam_node!=NULL)
        {
            fwrite(pteam_node,sizeof(TEAM_NODE),1,pfout);

            pteam_node=pteam_node->next;
        }

    }
    fclose(pfout);

    pfout=fopen(gp_sciprj_info_filename,"wb");

    //保存科研项目基本信息
     for(psch_node=gp_head;psch_node!=NULL;psch_node=psch_node->next)
    {
        pteam_node=psch_node->tnext;
        while(pteam_node!=NULL)
        {
            psciprj_node=pteam_node->snext;

            while(psciprj_node!=NULL)
            {
                fwrite(psciprj_node,sizeof(SCIPRJ_NODE),1,pfout);
                psciprj_node=psciprj_node->next;
            }

            pteam_node=pteam_node->next;

        }

    }

    chdir(dir_current);//把目录更改为原来的工作目录

    fclose(pfout);


    return TRUE;
}

/**
 * 函数名称: BackupSysData
 * 函数功能: 三类基础数据备份到一个数据文件.
 * 输入参数: hd 主链头结点指针
 *           filename 数据文件名
 * 输出参数:
 * 返 回 值: BOOL类型, 总是为TRUE
 *
 * 调用说明:
 */
BOOL BackupSysData(SCH_NODE *hd, char *filename)
{

    SCH_NODE *psch_node;
    TEAM_NODE *pteam_node;
    SCIPRJ_NODE *psciprj_node;
    unsigned long sch_node_num=0;
    unsigned long team_node_num=0;
    unsigned long sciprj_node_num=0;


    int handle;
    /*遍历十字链表，分别统计三种基础信息的记录总数*/
    for(psch_node=hd; psch_node!=NULL; psch_node=psch_node->next)
    {
        sch_node_num++;

        pteam_node=psch_node->tnext;
        while(pteam_node!=NULL)
        {
            team_node_num++;

            psciprj_node=pteam_node->snext;
            while(psciprj_node!=NULL)
            {
                sciprj_node_num++;

                psciprj_node=psciprj_node->next;

            }

            pteam_node=pteam_node->next;
        }
    }

    if(( handle=open(filename,O_WRONLY|O_BINARY) ) == -1)
    {

        handle=open(filename,O_CREAT|O_BINARY|O_RDWR ,S_IREAD|S_IWRITE);//注意以O_RDWR方式打开时候要匹配读写权限S_IREAD|S_IWRITE,但是没有S_IREAD|S_IWRITE也会默认有，因为O_RDWR
    }

//S_IREAD|S_IWRITE
    /*保存三类基础数据的记录总数*/
    write(handle, (char*)&sch_node_num, sizeof(sch_node_num)  );
    write(handle, (char*)&team_node_num, sizeof(team_node_num)  );
    write(handle, (char*)&sciprj_node_num, sizeof(sciprj_node_num)  );

    for(psch_node=hd; psch_node!=NULL; psch_node=psch_node->next)
    {
        /*保存院系基本信息*/
        write(handle, (char*)psch_node, sizeof(SCH_NODE));
    }

    for(psch_node=hd; psch_node!=NULL; psch_node=psch_node->next)
    {
        /*保存科研团队基本信息*/
        pteam_node=psch_node->tnext;
        while(pteam_node!=NULL)
        {
            write(handle, (char*)pteam_node, sizeof(TEAM_NODE));
            pteam_node=pteam_node->next;
        }

    }

    for(psch_node=hd; psch_node!=NULL; psch_node=psch_node->next)
    {
        /*保存科研项目基本信息*/
        pteam_node=psch_node->tnext;
        while(pteam_node!=NULL)
        {
            psciprj_node=pteam_node->snext;
            while(psciprj_node!=NULL)
            {
                write(handle, (char*)psciprj_node, sizeof(SCIPRJ_NODE));
                psciprj_node=psciprj_node->next;
            }

            pteam_node=pteam_node->next;
        }
    }

    close(handle);

    return TRUE;
}

/**
 * 函数名称: RestoreSysData
 * 函数功能: 从指定数据文件中恢复系统三类基础数据.
 * 输入参数: phead 主链头结点指针的地址
 *           filename 存放备份数据的数据文件名
 * 输出参数:
 * 返 回 值: BOOL类型, 总是为TRUE
 *
 * 调用说明:
 */
BOOL RestoreSysData(SCH_NODE **phead, char *filename)
{
   SCH_NODE *hd=NULL,*psch_node;
   TEAM_NODE *pteam_node;
   SCIPRJ_NODE *psciprj_node;

   unsigned long sch_node_num=0;
   unsigned long team_node_num=0;
   unsigned long sciprj_node_num=0;
   unsigned long ulloop;
   int handle,find;


   if( (handle=open(filename,O_RDONLY|O_BINARY)) == -1)
   {
       char *plabel_name[] = {"您输入的备份文件不存在！",
                           "数据恢复失败",
                           "确认"
                          };

       ShowModule(plabel_name, 3);


       return FALSE;
   }

   /*读取三种基本信息的记录条数*/
   read(handle, (char*)&sch_node_num, sizeof(sch_node_num));
   read(handle, (char*)&team_node_num, sizeof(team_node_num));
   read(handle, (char*)&sciprj_node_num, sizeof(sciprj_node_num));

   /*读取院系基本信息，建立十字链表*/
   for(ulloop=1; ulloop<=sch_node_num; ulloop++)
   {
       psch_node=(SCH_NODE*)malloc(sizeof(SCH_NODE));
       read(handle, (char*)psch_node, sizeof(SCH_NODE));
       psch_node->tnext=NULL;//不能悬挂指针
       psch_node->next=hd;
       hd=psch_node;
   }
   *phead=hd;

   /*读取科研团队基本信息，建立科研团队信息支链*/
   for(ulloop=1; ulloop<=team_node_num; ulloop++)
   {
       pteam_node=(TEAM_NODE*)malloc(sizeof(TEAM_NODE));
       read(handle, (char*)pteam_node, sizeof(TEAM_NODE));
       pteam_node->snext=NULL;//不能悬挂 指针
       psch_node=hd;
       while( (psch_node!=NULL)  &&  ( strcmp(psch_node->sch_name,pteam_node->sch )!=0)  )
       {
          psch_node=psch_node->next;
       }

       if(psch_node!=NULL)
       {
           pteam_node->next=psch_node->tnext;
           psch_node->tnext=pteam_node;

       }
       else
       {
           free(pteam_node);
       }


   }


    /*读取科研项目基本信息，建立科研项目基本信息支链*/
    for(ulloop=1; ulloop<=sciprj_node_num; ulloop++)
    {
        psciprj_node=(SCIPRJ_NODE*)malloc(sizeof(SCIPRJ_NODE));
        read(handle, (char*)psciprj_node, sizeof(SCIPRJ_NODE));
        psch_node=hd;
        find=0;

        while( (psch_node!=NULL) && (find==0) )
        {
            pteam_node=psch_node->tnext;
            while(  (pteam_node!=NULL)&&(find==0)  )
            {
                if( strcmp(pteam_node->team_name, psciprj_node->team) == 0  )
                {
                    find=1;
                    break;
                }

                pteam_node=pteam_node->next;

            }

            psch_node=psch_node->next;

        }

        if(find)
        {
            psciprj_node->next=pteam_node->snext;
            pteam_node->snext=psciprj_node;
        }
        else
        {
            free(psciprj_node);
        }

    }

    close(handle);


    char *plabel_name[] = {"备份数据已经恢复到内存！",
                           "可在文件选项中选择保存到本地文件",
                           "确认"
                          };

       ShowModule(plabel_name, 3);

       return TRUE;
}

