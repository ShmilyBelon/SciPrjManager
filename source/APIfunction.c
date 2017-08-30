#include"ExternInfoList.h"



/**
 * 函数名称: ExeFunction
 * 函数功能: 执行由主菜单号和子菜单号确定的功能函数.
 * 输入参数: m 主菜单项号
 *           s 子菜单项号
 * 输出参数: 无
 * 返 回 值: BOOL类型, TRUE 或 FALSE
 *
 * 调用说明: 仅在执行函数ExitSys时, 才可能返回FALSE, 其他情况下总是返回TRUE
 */
BOOL ExeFunction(int m, int s)
{
    BOOL bRet = TRUE;
    /*函数指针数组，用来存放所有功能函数的入口地址*/
    BOOL (*pFunction[ga_sub_menu_count[0]+ga_sub_menu_count[1]+ga_sub_menu_count[2]+ga_sub_menu_count[3]+ga_sub_menu_count[4]])(void);
    int i, loc;

    /*将功能函数入口地址存入与功能函数所在主菜单号和子菜单号对应下标的数组元素*/
    pFunction[0] = SaveData;
    pFunction[1] = BackupData;
    pFunction[2] = RestoreData;
    pFunction[3] = ExitSys;
    pFunction[4] = Warnings;
    pFunction[5] = MaintainInfofile;
    pFunction[6] = NULL;
    pFunction[7] = MaintainSchInfo;
    pFunction[8] = MaintainTeamInfo;
    pFunction[9] = MaintainSciprjInfo;
    pFunction[10] = QueryWarnings;
    pFunction[11] = QueryAllInfo;
    pFunction[12] = NULL;
    pFunction[13] = QuerySchInfo;
    pFunction[14] = QueryTeamInfo;
    pFunction[15] = QuerySciprjInfo;
    pFunction[16] = StatResearcherNumberInfo;
    pFunction[17] = StatSciprjNumberInfo;
    pFunction[18] = StatNatureScienceTop10;
    pFunction[19] = StatPrjAndProfRate;
    pFunction[20] = OtherStat;
    pFunction[21] = HelpTopic;
    pFunction[22] = NULL;
    pFunction[23] = AboutSystem;

    for (i=1,loc=0; i<m; i++)  /*根据主菜单号和子菜单号计算对应下标*/
    {
        loc += ga_sub_menu_count[i-1];
    }
    loc += s - 1;

    if (pFunction[loc] != NULL)
    {
        bRet = (*pFunction[loc])();  /*用函数指针调用所指向的功能函数*/
    }

    return bRet;
}

BOOL SaveData(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"主菜单项：文件",
                           "子菜单项：数据保存",
                           "确认"
                          };

    ShowModule(plabel_name, 3);
    SaveSysData();//保存数据的函数 ，总是从头指针 gp_head开始

    char *p_anotherlabel_name[] = {"数据保存成功！",
                           "  ",
                           "确认"
                          };

    ShowModule(p_anotherlabel_name, 3);

 /*隐藏光标*/
    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible=FALSE;
    SetConsoleCursorInfo(gh_std_out,&lpCur);

    ClearScreenTotalInputArea();//清屏



    return bRet;
}

BOOL BackupData(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"主菜单项：文件",
                           "子菜单项：数据备份",
                           "确认"
                          };

    ShowModule(plabel_name, 3);

    char filename[100];
    GetBackupFilename(filename);//得到备份文件储存路径以及备份文件的文件名，并把该路径以及文件名存在filename字符串中

    BackupSysData(gp_head,filename);//把头指针所指向的十字链表中的数据备份到filename所指示的文件中



    char *Anotherplabel_name[] = {"数据备份成功！",
                           "备份文件存储在当前目录的backup文件夹中",
                           "确认"
                          };

    ShowModule(Anotherplabel_name, 3);




    return bRet;
}

BOOL RestoreData(void)
{
    BOOL bRet = TRUE;
    CONSOLE_CURSOR_INFO lpCur;
    char filename[100];
    char *plabel_name[] = {"主菜单项：文件",
                           "子菜单项：数据恢复",
                           "确认"
                          };

    ShowModule(plabel_name, 3);


    char *Anoplabel_name[] = {"请输入备份文件名",
                              "  (含储存路径)",
                           "确认"
                          };

    ShowModule(Anoplabel_name, 3);
     /*显示光标*/
   GetConsoleCursorInfo(gh_std_out,&lpCur);
   lpCur.bVisible=TRUE;
   SetConsoleCursorInfo(gh_std_out,&lpCur);

    scanf("%s",filename);
    AddBackslash(filename);//把字符串中的单个\变成\\ , 以便转义。



    RestoreSysData(&gp_head,filename);//恢复数据

    /*隐藏光标*/
    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible=FALSE;
    SetConsoleCursorInfo(gh_std_out,&lpCur);

    ClearScreenTotalInputArea();//清屏





    return bRet;
}

BOOL ExitSys(void)
{
    LABEL_BUNDLE labels;
    HOT_AREA areas;
    BOOL bRet = TRUE;
    SMALL_RECT rcPop;
    COORD pos;
    WORD att;
    char *pCh[] = {"确认退出系统吗？", "确定    取消"};
    int iHot = 1;

    pos.X = strlen(pCh[0]) + 6;
    pos.Y = 7;
    rcPop.Left = (SCR_COL - pos.X) / 2;
    rcPop.Right = rcPop.Left + pos.X - 1;
    rcPop.Top = (SCR_ROW - pos.Y) / 2;
    rcPop.Bottom = rcPop.Top + pos.Y - 1;

    att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*白底黑字*/
    labels.num = 2;
    labels.ppLabel = pCh;
    COORD aLoc[] = {{rcPop.Left+3, rcPop.Top+2},
                    {rcPop.Left+5, rcPop.Top+5}};
    labels.pLoc = aLoc;

    areas.num = 2;
    SMALL_RECT aArea[] = {{rcPop.Left + 5, rcPop.Top + 5,
                           rcPop.Left + 8, rcPop.Top + 5},
                          {rcPop.Left + 13, rcPop.Top + 5,
                           rcPop.Left + 16, rcPop.Top + 5}};
    char aSort[] = {0, 0};
    char aTag[] = {1, 2};
    areas.pArea = aArea;
    areas.pSort = aSort;
    areas.pTag = aTag;
    PopUp(&rcPop, att, &labels, &areas);

    pos.X = rcPop.Left + 1;
    pos.Y = rcPop.Top + 4;
    FillConsoleOutputCharacter(gh_std_out, '-', rcPop.Right-rcPop.Left-1, pos, &ul);

    if (DealInput(&areas, &iHot) == 13 && iHot == 1)
    {
        bRet = FALSE;
    }
    else
    {
        bRet = TRUE;
    }
    PopOff();

    return bRet;
}

BOOL Warnings(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"主菜单项：数据维护",
                           "子菜单项：警告！",
                           "确认"
                          };

    ShowModule(plabel_name, 3);
    system(".\\warnings\\MaintainWarning.pdf");


    return bRet;
}

BOOL MaintainInfofile(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"主菜单项：数据维护",
                           "子菜单项：文件维护",
                           "确认"
                          };

    ShowModule(plabel_name, 3);

    char dir_togo[100];//存放要去的那个目录
    char DataDir[7]="\\data";//存放数据文件的那一层目录
    char cmd[110]="explorer ";

    getcwd(dir_togo,sizeof(dir_togo));//把当前目录地址字符串复制到dir_togo中
    strcat(dir_togo,DataDir);//在当前工作地址之后加上\data构造数据文件夹所在目录
    /**注意不用AddBackslash(dir_togo)，system函数与fopen等函数不同，表达\不需要用\\转意
    而且注意，比如char DataDir[7]="\\data"内存单元中只有一个\,转意的意思是用\\来表示\而已  */

     strcat(cmd,dir_togo);//构造打开目录的cmd命令

     system(cmd);





    return bRet;
}

BOOL MaintainSchInfo(void)
{
    char cmd ;
    CONSOLE_CURSOR_INFO lpCur;

    char *plabel_name[] = {"主菜单项：数据维护",
                           "子菜单项：院系基本信息",
                           "确认"
                          };


    ShowModule(plabel_name, 3);
Cmdinput1:
    printf("请输入需要执行的功能代码：\n");
    printf("    录入(I)\n    修改(M)\n    删除(D)\n    退出(L)\n\n");
    printf("您选择：    ");


    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible = TRUE;  //显示光标
    SetConsoleCursorInfo(gh_std_out,&lpCur);

    scanf("%1s",&cmd);
    getchar();
    switch(cmd)
    {
       case 'I' :
       case 'i' : SchInfoInput(); break;
       case 'M' :
       case 'm' : SchInfoMod();   break;
       case 'D' :
       case 'd' : SchInfoDelete();break;
       case 'L' :
       case 'l' :
           {
               char *plabel_name[] = {"您已成功退出此功能块！",
                                            "  ",
                                               "确认"
                                                        };

                                           ShowModule(plabel_name, 3);

                                           ClearScreenTotalInputArea();

                                           goto End;
           }

       default:
           {
               char *plabel_name[] = {"命令输入错误请重新输入！",
                                            "  ",
                                               "确认"
                                                        };

                                           ShowModule(plabel_name, 3);

                                           ClearScreenTotalInputArea();

                                           goto Cmdinput1;

           }




  }
 End:
    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible = FALSE;  //隐藏光标
    SetConsoleCursorInfo(gh_std_out,&lpCur);

    return TRUE;
}

BOOL MaintainTeamInfo(void)
{
     char cmd ;
    CONSOLE_CURSOR_INFO lpCur;
    //BOOL bRet = TRUE;
    char *plabel_name[] = {"主菜单项：数据维护",
                           "子菜单项：科研团队基本信息",
                           "确认"
                          };


    ShowModule(plabel_name, 3);
Cmdinput1:
    printf("请输入需要执行的功能代码：\n");
    printf("    录入(I)\n    修改(M)\n    删除(D)\n    退出(L)\n\n");
    printf("您选择：    ");


    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible = TRUE;  //显示光标
    SetConsoleCursorInfo(gh_std_out,&lpCur);

    scanf("%1s",&cmd);
    getchar();

     switch(cmd)
    {
       case 'I' :
       case 'i' : TeamInfoInput(); break;
       case 'M' :
       case 'm' : TeamInfoMod();   break;
       case 'D' :
       case 'd' : TeamInfoDelete();break;
       case 'L' :
       case 'l' :
           {
               char *plabel_name[] = {"您已成功退出此功能块！",
                                            "  ",
                                               "确认"
                                                        };

                                           ShowModule(plabel_name, 3);

                                           ClearScreenTotalInputArea();

                                           goto End;
           }




       default:
           {
               char *plabel_name[] = {"命令输入错误请重新输入！",
                                            "  ",
                                               "确认"
                                                        };

                                           ShowModule(plabel_name, 3);

                                           ClearScreenTotalInputArea();

                                           goto Cmdinput1;

           }




  }
End:
    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible = FALSE;  //隐藏光标
    SetConsoleCursorInfo(gh_std_out,&lpCur);

    return TRUE;
}




BOOL MaintainSciprjInfo(void)
{


    char cmd ;
    CONSOLE_CURSOR_INFO lpCur;
    //BOOL bRet = TRUE;
    char *plabel_name[] = {"主菜单项：数据维护",
                           "子菜单项：科研团队基本信息",
                           "确认"
                          };


    ShowModule(plabel_name, 3);
Cmdinput1:
    printf("请输入需要执行的功能代码：\n");
    printf("    录入(I)\n    修改(M)\n    删除(D)\n    退出(L)\n\n");
    printf("您选择：    ");


    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible = TRUE;  //显示光标
    SetConsoleCursorInfo(gh_std_out,&lpCur);

    scanf("%1s",&cmd);
    getchar();

     switch(cmd)
    {
       case 'I' :
       case 'i' : SciprjInfoInput(); break;
       case 'M' :
       case 'm' : SciprjInfoMod();   break;
       case 'D' :
       case 'd' : SciprjInfoDelete();break;
       case 'L' :
       case 'l' :
           {
               char *plabel_name[] = {"您已成功退出此功能块！",
                                            "  ",
                                               "确认"
                                                        };

                                           ShowModule(plabel_name, 3);

                                           ClearScreenTotalInputArea();

                                           goto End;
           }




       default:
           {
               char *plabel_name[] = {"命令输入错误请重新输入！",
                                            "  ",
                                               "确认"
                                                        };

                                           ShowModule(plabel_name, 3);

                                           ClearScreenTotalInputArea();

                                           goto Cmdinput1;

           }




  }
End:
    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible = FALSE;  //隐藏光标
    SetConsoleCursorInfo(gh_std_out,&lpCur);

    return TRUE;

}

BOOL QueryWarnings(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"主菜单项：数据查询",
                           "子菜单项：  警告！",
                           "确认"
                          };

    ShowModule(plabel_name, 3);
    system(".\\warnings\\QueryWarning.pdf");

    return bRet;
}

BOOL QueryAllInfo(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"主菜单项：数据查询",
                           "子菜单项：遍历所有信息",
                           "确认"
                          };

    ShowModule(plabel_name, 3);

    QueryAll();

    return bRet;
}

BOOL QuerySchInfo(void)
{
    char cmd;

    char *plabel_name[] = {"主菜单项：数据查询",
                           "子菜单项：院系基本信息",
                           "确认"
                          };

    ShowModule(plabel_name, 3);
    ClearScreenTotalInputArea();  //清屏

Cmdinput1:

    printf("请输入需要执行的功能代码：\n");
    printf("    1,通过负责人姓名查询院系信息(B)\n    2,通过院系名称全部或部分查询院系信息(S)\n    3,退出(L)\n\n");
    printf("您选择：    ");


    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible = TRUE;  //显示光标
    SetConsoleCursorInfo(gh_std_out,&lpCur);


    scanf("%1s",&cmd);
    getchar();

     switch(cmd)
     {
        case '1':
        case 'B':
        case 'b': QuerySchInfoViaBossname();break;

        case '2':
        case 'S':
        case 's': QuerySchInfoViaSchsname();break;

        case '3':
        case 'L':
        case 'l':
                 {
                     char *plabel_name[] = {"您已成功退出此功能块！",
                                            "  ",
                                               "确认"
                                                        };

                                           ShowModule(plabel_name, 3);

                                           ClearScreenTotalInputArea();

                                           goto End;
                 }


        default:
                {

                   char *plabel_name[] = {"命令输入错误请重新输入！",
                                            "  ",
                                               "确认"
                                                        };

                                           ShowModule(plabel_name, 3);

                                           ClearScreenTotalInputArea();

                                           goto Cmdinput1;



                }
     }

End:

    ClearScreenTotalInputArea();
    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible = FALSE;  //显示光标
    SetConsoleCursorInfo(gh_std_out,&lpCur);

    return TRUE;
}

BOOL QueryTeamInfo(void)
{
    char cmd;

    char *plabel_name[] = {"主菜单项：数据查询",
                           "子菜单项：科研团队基本信息",
                           "确认"
                          };


    ShowModule(plabel_name, 3);


    ClearScreenTotalInputArea();  //清屏

Cmdinput1:

    printf("请输入需要执行的功能代码：\n");
    printf("    1,通过团队名称全部或部分查询院系信息(T)\n    2,通过教师人数下限查询院系信息(S)\n    3,退出(L)\n\n");
    printf("您选择：    ");


    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible = TRUE;  //显示光标
    SetConsoleCursorInfo(gh_std_out,&lpCur);


    scanf("%1s",&cmd);
    getchar();

     switch(cmd)
     {
        case '1':
        case 'T':
        case 't': QueryTeamInfoViaTeamname();break;

        case '2':
        case 'S':
        case 's': QuerySchInfoViaProfnum();break;

        case '3':
        case 'L':
        case 'l':
                 {
                     char *plabel_name[] = {"您已成功退出此功能块！",
                                            "  ",
                                               "确认"
                                                        };

                                           ShowModule(plabel_name, 3);

                                           ClearScreenTotalInputArea();

                                           goto End;
                 }


        default:
                {

                   char *plabel_name[] = {"命令输入错误请重新输入！",
                                            "  ",
                                               "确认"
                                                        };

                                           ShowModule(plabel_name, 3);

                                           ClearScreenTotalInputArea();

                                           goto Cmdinput1;



                }
     }

End:

    ClearScreenTotalInputArea();
    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible = FALSE;  //显示光标
    SetConsoleCursorInfo(gh_std_out,&lpCur);




    return TRUE;

}

BOOL QuerySciprjInfo(void)
{
    char cmd;

    char *plabel_name[] = {"主菜单项：数据查询",
                           "子菜单项：科研项目基本信息",
                           "确认"
                          };

    ShowModule(plabel_name, 3);

    ClearScreenTotalInputArea();  //清屏

Cmdinput1:

    printf("请输入需要执行的功能代码：\n");
    printf("    1,通过项目编号查找满足条件的科研项目基本信息(I)\n    2,通过科研项目所属团队查询项目信息(T)\n    3,退出(L)\n\n");
    printf("您选择：    ");


    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible = TRUE;  //显示光标
    SetConsoleCursorInfo(gh_std_out,&lpCur);


    scanf("%1s",&cmd);
    getchar();

     switch(cmd)
     {
        case '1':
        case 'I':
        case 'i': QuerySciprjInfoViaID();break;

        case '2':
        case 'T':
        case 't': QuerySciprjInfoViaTeam();break;

        case '3':
        case 'L':
        case 'l':
                 {
                     char *plabel_name[] = {"您已成功退出此功能块！",
                                            "  ",
                                               "确认"
                                                        };

                                           ShowModule(plabel_name, 3);

                                           ClearScreenTotalInputArea();

                                           goto End;
                 }


        default:
                {

                   char *plabel_name[] = {"命令输入错误请重新输入！",
                                            "  ",
                                               "确认"
                                                        };

                                           ShowModule(plabel_name, 3);

                                           ClearScreenTotalInputArea();

                                           goto Cmdinput1;



                }
     }

End:

    ClearScreenTotalInputArea();
    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible = FALSE;  //显示光标
    SetConsoleCursorInfo(gh_std_out,&lpCur);


    return TRUE;

}

BOOL StatResearcherNumberInfo(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"主菜单项：数据统计",
                           "子菜单项：科研人员信息",
                           "确认"
                          };

    ShowModule(plabel_name, 3);

    StatResearcherNumInfo();

    return bRet;
}

BOOL StatSciprjNumberInfo(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"主菜单项：数据统计",
                           "子菜单项：科研项目信息",
                           "确认"
                          };

    ShowModule(plabel_name, 3);

    StatSciprjNumInfo();



    return bRet;
}

BOOL StatNatureScienceTop10(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"主菜单项：数据统计",
                           "子菜单项：国家自科基金top10",
                           "确认"
                          };

    ShowModule(plabel_name, 3);

    StatNatureSciTop10();

    return bRet;
}

BOOL StatPrjAndProfRate(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"主菜单项：数据统计",
                           "子菜单项：项目/人 排行",
                           "确认"
                          };


    ShowModule(plabel_name, 3);

    StatPrjProfRate();

    return bRet;
}
BOOL OtherStat(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"主菜单项：数据统计",
                           "子菜单项：最土豪团队",
                           "确认"
                          };

    ShowModule(plabel_name, 3);

    StatFundProfRate();

    return bRet;
}


BOOL HelpTopic(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"主菜单项：帮助",
                           "子菜单项：帮助主题",
                           "确认"
                          };

    ShowModule(plabel_name, 3);

    Help();

    return bRet;
}

BOOL AboutSystem(void)
{
    CONSOLE_CURSOR_INFO lpCur;
    BOOL bRet = TRUE;
    char *plabel_name[] = {"主菜单项：帮助",
                           "子菜单项：关于...",
                           "确认"
                          };

    ShowModule(plabel_name, 3);
    ShellExecute(NULL,"open","https://github.com/ShmilyBelon/Science-Project-Information-Management-System.git",NULL,NULL,SW_SHOWNORMAL);

    /*显示光标*/
    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible=TRUE;
    SetConsoleCursorInfo(gh_std_out,&lpCur);






   printf("\n开发者：陈国轩\n");
   printf("\n单位：华中科技大学计算机科学与技术学院，计算机校交1601班\n");
   printf("\n版本：win1701\n");

   printf("\n参考文献：《C语言与程序设计》 电子工业出版社，曹计昌 卢萍 李开编著\n");
   printf("           《C语言实验与课程设计》科学出版社， 李开 卢萍 曹计昌编著\n");
   printf("\n\n鸣谢：刘芳、王多强老师\n\n");
   printf("备注：此系统为windows版本，不支持在linux，Mac OS X等其他系统上运行！\n\n");
   printf("按任意键继续...");

   getch();

   ClearScreenTotalInputArea();//清屏

    /*隐藏光标*/
    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible=FALSE;
    SetConsoleCursorInfo(gh_std_out,&lpCur);



    return bRet;
}
