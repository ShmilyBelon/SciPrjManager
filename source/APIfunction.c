#include"ExternInfoList.h"



/**
 * ��������: ExeFunction
 * ��������: ִ�������˵��ź��Ӳ˵���ȷ���Ĺ��ܺ���.
 * �������: m ���˵����
 *           s �Ӳ˵����
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE �� FALSE
 *
 * ����˵��: ����ִ�к���ExitSysʱ, �ſ��ܷ���FALSE, ������������Ƿ���TRUE
 */
BOOL ExeFunction(int m, int s)
{
    BOOL bRet = TRUE;
    /*����ָ�����飬����������й��ܺ�������ڵ�ַ*/
    BOOL (*pFunction[ga_sub_menu_count[0]+ga_sub_menu_count[1]+ga_sub_menu_count[2]+ga_sub_menu_count[3]+ga_sub_menu_count[4]])(void);
    int i, loc;

    /*�����ܺ�����ڵ�ַ�����빦�ܺ����������˵��ź��Ӳ˵��Ŷ�Ӧ�±������Ԫ��*/
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

    for (i=1,loc=0; i<m; i++)  /*�������˵��ź��Ӳ˵��ż����Ӧ�±�*/
    {
        loc += ga_sub_menu_count[i-1];
    }
    loc += s - 1;

    if (pFunction[loc] != NULL)
    {
        bRet = (*pFunction[loc])();  /*�ú���ָ�������ָ��Ĺ��ܺ���*/
    }

    return bRet;
}

BOOL SaveData(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"���˵���ļ�",
                           "�Ӳ˵�����ݱ���",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);
    SaveSysData();//�������ݵĺ��� �����Ǵ�ͷָ�� gp_head��ʼ

    char *p_anotherlabel_name[] = {"���ݱ���ɹ���",
                           "  ",
                           "ȷ��"
                          };

    ShowModule(p_anotherlabel_name, 3);

 /*���ع��*/
    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible=FALSE;
    SetConsoleCursorInfo(gh_std_out,&lpCur);

    ClearScreenTotalInputArea();//����



    return bRet;
}

BOOL BackupData(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"���˵���ļ�",
                           "�Ӳ˵�����ݱ���",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);

    char filename[100];
    GetBackupFilename(filename);//�õ������ļ�����·���Լ������ļ����ļ��������Ѹ�·���Լ��ļ�������filename�ַ�����

    BackupSysData(gp_head,filename);//��ͷָ����ָ���ʮ�������е����ݱ��ݵ�filename��ָʾ���ļ���



    char *Anotherplabel_name[] = {"���ݱ��ݳɹ���",
                           "�����ļ��洢�ڵ�ǰĿ¼��backup�ļ�����",
                           "ȷ��"
                          };

    ShowModule(Anotherplabel_name, 3);




    return bRet;
}

BOOL RestoreData(void)
{
    BOOL bRet = TRUE;
    CONSOLE_CURSOR_INFO lpCur;
    char filename[100];
    char *plabel_name[] = {"���˵���ļ�",
                           "�Ӳ˵�����ݻָ�",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);


    char *Anoplabel_name[] = {"�����뱸���ļ���",
                              "  (������·��)",
                           "ȷ��"
                          };

    ShowModule(Anoplabel_name, 3);
     /*��ʾ���*/
   GetConsoleCursorInfo(gh_std_out,&lpCur);
   lpCur.bVisible=TRUE;
   SetConsoleCursorInfo(gh_std_out,&lpCur);

    scanf("%s",filename);
    AddBackslash(filename);//���ַ����еĵ���\���\\ , �Ա�ת�塣



    RestoreSysData(&gp_head,filename);//�ָ�����

    /*���ع��*/
    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible=FALSE;
    SetConsoleCursorInfo(gh_std_out,&lpCur);

    ClearScreenTotalInputArea();//����





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
    char *pCh[] = {"ȷ���˳�ϵͳ��", "ȷ��    ȡ��"};
    int iHot = 1;

    pos.X = strlen(pCh[0]) + 6;
    pos.Y = 7;
    rcPop.Left = (SCR_COL - pos.X) / 2;
    rcPop.Right = rcPop.Left + pos.X - 1;
    rcPop.Top = (SCR_ROW - pos.Y) / 2;
    rcPop.Bottom = rcPop.Top + pos.Y - 1;

    att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/
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
    char *plabel_name[] = {"���˵������ά��",
                           "�Ӳ˵�����棡",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);
    system(".\\warnings\\MaintainWarning.pdf");


    return bRet;
}

BOOL MaintainInfofile(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"���˵������ά��",
                           "�Ӳ˵���ļ�ά��",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);

    char dir_togo[100];//���Ҫȥ���Ǹ�Ŀ¼
    char DataDir[7]="\\data";//��������ļ�����һ��Ŀ¼
    char cmd[110]="explorer ";

    getcwd(dir_togo,sizeof(dir_togo));//�ѵ�ǰĿ¼��ַ�ַ������Ƶ�dir_togo��
    strcat(dir_togo,DataDir);//�ڵ�ǰ������ַ֮�����\data���������ļ�������Ŀ¼
    /**ע�ⲻ��AddBackslash(dir_togo)��system������fopen�Ⱥ�����ͬ�����\����Ҫ��\\ת��
    ����ע�⣬����char DataDir[7]="\\data"�ڴ浥Ԫ��ֻ��һ��\,ת�����˼����\\����ʾ\����  */

     strcat(cmd,dir_togo);//�����Ŀ¼��cmd����

     system(cmd);





    return bRet;
}

BOOL MaintainSchInfo(void)
{
    char cmd ;
    CONSOLE_CURSOR_INFO lpCur;

    char *plabel_name[] = {"���˵������ά��",
                           "�Ӳ˵��Ժϵ������Ϣ",
                           "ȷ��"
                          };


    ShowModule(plabel_name, 3);
Cmdinput1:
    printf("��������Ҫִ�еĹ��ܴ��룺\n");
    printf("    ¼��(I)\n    �޸�(M)\n    ɾ��(D)\n    �˳�(L)\n\n");
    printf("��ѡ��    ");


    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible = TRUE;  //��ʾ���
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
               char *plabel_name[] = {"���ѳɹ��˳��˹��ܿ飡",
                                            "  ",
                                               "ȷ��"
                                                        };

                                           ShowModule(plabel_name, 3);

                                           ClearScreenTotalInputArea();

                                           goto End;
           }

       default:
           {
               char *plabel_name[] = {"��������������������룡",
                                            "  ",
                                               "ȷ��"
                                                        };

                                           ShowModule(plabel_name, 3);

                                           ClearScreenTotalInputArea();

                                           goto Cmdinput1;

           }




  }
 End:
    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible = FALSE;  //���ع��
    SetConsoleCursorInfo(gh_std_out,&lpCur);

    return TRUE;
}

BOOL MaintainTeamInfo(void)
{
     char cmd ;
    CONSOLE_CURSOR_INFO lpCur;
    //BOOL bRet = TRUE;
    char *plabel_name[] = {"���˵������ά��",
                           "�Ӳ˵�������Ŷӻ�����Ϣ",
                           "ȷ��"
                          };


    ShowModule(plabel_name, 3);
Cmdinput1:
    printf("��������Ҫִ�еĹ��ܴ��룺\n");
    printf("    ¼��(I)\n    �޸�(M)\n    ɾ��(D)\n    �˳�(L)\n\n");
    printf("��ѡ��    ");


    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible = TRUE;  //��ʾ���
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
               char *plabel_name[] = {"���ѳɹ��˳��˹��ܿ飡",
                                            "  ",
                                               "ȷ��"
                                                        };

                                           ShowModule(plabel_name, 3);

                                           ClearScreenTotalInputArea();

                                           goto End;
           }




       default:
           {
               char *plabel_name[] = {"��������������������룡",
                                            "  ",
                                               "ȷ��"
                                                        };

                                           ShowModule(plabel_name, 3);

                                           ClearScreenTotalInputArea();

                                           goto Cmdinput1;

           }




  }
End:
    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible = FALSE;  //���ع��
    SetConsoleCursorInfo(gh_std_out,&lpCur);

    return TRUE;
}




BOOL MaintainSciprjInfo(void)
{


    char cmd ;
    CONSOLE_CURSOR_INFO lpCur;
    //BOOL bRet = TRUE;
    char *plabel_name[] = {"���˵������ά��",
                           "�Ӳ˵�������Ŷӻ�����Ϣ",
                           "ȷ��"
                          };


    ShowModule(plabel_name, 3);
Cmdinput1:
    printf("��������Ҫִ�еĹ��ܴ��룺\n");
    printf("    ¼��(I)\n    �޸�(M)\n    ɾ��(D)\n    �˳�(L)\n\n");
    printf("��ѡ��    ");


    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible = TRUE;  //��ʾ���
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
               char *plabel_name[] = {"���ѳɹ��˳��˹��ܿ飡",
                                            "  ",
                                               "ȷ��"
                                                        };

                                           ShowModule(plabel_name, 3);

                                           ClearScreenTotalInputArea();

                                           goto End;
           }




       default:
           {
               char *plabel_name[] = {"��������������������룡",
                                            "  ",
                                               "ȷ��"
                                                        };

                                           ShowModule(plabel_name, 3);

                                           ClearScreenTotalInputArea();

                                           goto Cmdinput1;

           }




  }
End:
    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible = FALSE;  //���ع��
    SetConsoleCursorInfo(gh_std_out,&lpCur);

    return TRUE;

}

BOOL QueryWarnings(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"���˵�����ݲ�ѯ",
                           "�Ӳ˵��  ���棡",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);
    system(".\\warnings\\QueryWarning.pdf");

    return bRet;
}

BOOL QueryAllInfo(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"���˵�����ݲ�ѯ",
                           "�Ӳ˵������������Ϣ",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);

    QueryAll();

    return bRet;
}

BOOL QuerySchInfo(void)
{
    char cmd;

    char *plabel_name[] = {"���˵�����ݲ�ѯ",
                           "�Ӳ˵��Ժϵ������Ϣ",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);
    ClearScreenTotalInputArea();  //����

Cmdinput1:

    printf("��������Ҫִ�еĹ��ܴ��룺\n");
    printf("    1,ͨ��������������ѯԺϵ��Ϣ(B)\n    2,ͨ��Ժϵ����ȫ���򲿷ֲ�ѯԺϵ��Ϣ(S)\n    3,�˳�(L)\n\n");
    printf("��ѡ��    ");


    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible = TRUE;  //��ʾ���
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
                     char *plabel_name[] = {"���ѳɹ��˳��˹��ܿ飡",
                                            "  ",
                                               "ȷ��"
                                                        };

                                           ShowModule(plabel_name, 3);

                                           ClearScreenTotalInputArea();

                                           goto End;
                 }


        default:
                {

                   char *plabel_name[] = {"��������������������룡",
                                            "  ",
                                               "ȷ��"
                                                        };

                                           ShowModule(plabel_name, 3);

                                           ClearScreenTotalInputArea();

                                           goto Cmdinput1;



                }
     }

End:

    ClearScreenTotalInputArea();
    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible = FALSE;  //��ʾ���
    SetConsoleCursorInfo(gh_std_out,&lpCur);

    return TRUE;
}

BOOL QueryTeamInfo(void)
{
    char cmd;

    char *plabel_name[] = {"���˵�����ݲ�ѯ",
                           "�Ӳ˵�������Ŷӻ�����Ϣ",
                           "ȷ��"
                          };


    ShowModule(plabel_name, 3);


    ClearScreenTotalInputArea();  //����

Cmdinput1:

    printf("��������Ҫִ�еĹ��ܴ��룺\n");
    printf("    1,ͨ���Ŷ�����ȫ���򲿷ֲ�ѯԺϵ��Ϣ(T)\n    2,ͨ����ʦ�������޲�ѯԺϵ��Ϣ(S)\n    3,�˳�(L)\n\n");
    printf("��ѡ��    ");


    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible = TRUE;  //��ʾ���
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
                     char *plabel_name[] = {"���ѳɹ��˳��˹��ܿ飡",
                                            "  ",
                                               "ȷ��"
                                                        };

                                           ShowModule(plabel_name, 3);

                                           ClearScreenTotalInputArea();

                                           goto End;
                 }


        default:
                {

                   char *plabel_name[] = {"��������������������룡",
                                            "  ",
                                               "ȷ��"
                                                        };

                                           ShowModule(plabel_name, 3);

                                           ClearScreenTotalInputArea();

                                           goto Cmdinput1;



                }
     }

End:

    ClearScreenTotalInputArea();
    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible = FALSE;  //��ʾ���
    SetConsoleCursorInfo(gh_std_out,&lpCur);




    return TRUE;

}

BOOL QuerySciprjInfo(void)
{
    char cmd;

    char *plabel_name[] = {"���˵�����ݲ�ѯ",
                           "�Ӳ˵��������Ŀ������Ϣ",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);

    ClearScreenTotalInputArea();  //����

Cmdinput1:

    printf("��������Ҫִ�еĹ��ܴ��룺\n");
    printf("    1,ͨ����Ŀ��Ų������������Ŀ�����Ŀ������Ϣ(I)\n    2,ͨ��������Ŀ�����ŶӲ�ѯ��Ŀ��Ϣ(T)\n    3,�˳�(L)\n\n");
    printf("��ѡ��    ");


    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible = TRUE;  //��ʾ���
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
                     char *plabel_name[] = {"���ѳɹ��˳��˹��ܿ飡",
                                            "  ",
                                               "ȷ��"
                                                        };

                                           ShowModule(plabel_name, 3);

                                           ClearScreenTotalInputArea();

                                           goto End;
                 }


        default:
                {

                   char *plabel_name[] = {"��������������������룡",
                                            "  ",
                                               "ȷ��"
                                                        };

                                           ShowModule(plabel_name, 3);

                                           ClearScreenTotalInputArea();

                                           goto Cmdinput1;



                }
     }

End:

    ClearScreenTotalInputArea();
    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible = FALSE;  //��ʾ���
    SetConsoleCursorInfo(gh_std_out,&lpCur);


    return TRUE;

}

BOOL StatResearcherNumberInfo(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"���˵������ͳ��",
                           "�Ӳ˵��������Ա��Ϣ",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);

    StatResearcherNumInfo();

    return bRet;
}

BOOL StatSciprjNumberInfo(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"���˵������ͳ��",
                           "�Ӳ˵��������Ŀ��Ϣ",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);

    StatSciprjNumInfo();



    return bRet;
}

BOOL StatNatureScienceTop10(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"���˵������ͳ��",
                           "�Ӳ˵�������Կƻ���top10",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);

    StatNatureSciTop10();

    return bRet;
}

BOOL StatPrjAndProfRate(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"���˵������ͳ��",
                           "�Ӳ˵����Ŀ/�� ����",
                           "ȷ��"
                          };


    ShowModule(plabel_name, 3);

    StatPrjProfRate();

    return bRet;
}
BOOL OtherStat(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"���˵������ͳ��",
                           "�Ӳ˵���������Ŷ�",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);

    StatFundProfRate();

    return bRet;
}


BOOL HelpTopic(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"���˵������",
                           "�Ӳ˵����������",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);

    Help();

    return bRet;
}

BOOL AboutSystem(void)
{
    CONSOLE_CURSOR_INFO lpCur;
    BOOL bRet = TRUE;
    char *plabel_name[] = {"���˵������",
                           "�Ӳ˵������...",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);
    ShellExecute(NULL,"open","https://github.com/ShmilyBelon/Science-Project-Information-Management-System.git",NULL,NULL,SW_SHOWNORMAL);

    /*��ʾ���*/
    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible=TRUE;
    SetConsoleCursorInfo(gh_std_out,&lpCur);






   printf("\n�����ߣ��¹���\n");
   printf("\n��λ�����пƼ���ѧ�������ѧ�뼼��ѧԺ�������У��1601��\n");
   printf("\n�汾��win1701\n");

   printf("\n�ο����ף���C�����������ơ� ���ӹ�ҵ�����磬�ܼƲ� ¬Ƽ �����\n");
   printf("           ��C����ʵ����γ���ơ���ѧ�����磬 � ¬Ƽ �ܼƲ�����\n");
   printf("\n\n��л������������ǿ��ʦ\n\n");
   printf("��ע����ϵͳΪwindows�汾����֧����linux��Mac OS X������ϵͳ�����У�\n\n");
   printf("�����������...");

   getch();

   ClearScreenTotalInputArea();//����

    /*���ع��*/
    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible=FALSE;
    SetConsoleCursorInfo(gh_std_out,&lpCur);



    return bRet;
}
