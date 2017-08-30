#include"ExternInfoList.h"



/**����Ϊ�Լ��¼ӵĺ���*/
BOOL SchInfoInput(void)
{
    CONSOLE_CURSOR_INFO lpCur;  //�洢�����Ϣ

    SCH_NODE *pSchNode=gp_head,*pSeekReturn;
    char cmd;
    ClearScreenTotalInputArea();  //����


    for(;;)
     {


                pSchNode = (SCH_NODE*)malloc(sizeof(SCH_NODE));
                pSchNode->next = NULL; //ָ���ÿգ��˲�����룬��������ָ��
                pSchNode->tnext=NULL;  //ָ���ÿգ��˲�����룬��������ָ��
                pSchNode->next=gp_head;
                gp_head  = pSchNode;

                printf("##�밴���¸�ʽҪ����������##\n1,���ݼ��ÿո����\n2,ͬһ���������޿ո� \n3,���ݱ����������벻�����\n4��Ժϵ��Ψһ�����ظ���\n\n");
                printf("��ʽ��\n       Ժϵ����                ������                ��ϵ�绰\n");
                scanf("%s %s %s",gp_head->sch_name,gp_head->boss_name,gp_head->tel);
                getchar();  //�̻س�

                pSeekReturn = SeekSchNode(pSchNode->next,gp_head->sch_name);  //����,��������Ϣ�ظ�����ǰ�Ľ��


                if(pSeekReturn==NULL) //���û���ظ�

                     goto Cmdinput2;

                else
               {
                     SchInfoDel( &gp_head, gp_head->sch_name);  //��Ϊ�ո�¼�����������Ժϵ�����ظ��ˣ����ǹ涨Ժϵ���Ʋ����ظ������ɾ���ոմ�����һ�����
                     printf("\n��Ժϵ����Ϣ�Ѿ�����\n�����������µ�Ժϵ��Ϣ\n�����޸Ĺ������޸Ĵ�Ժϵ��Ϣ\n\n");
                     printf("�Ƿ���������?  ��(Y),��(N)\n\n");


                     goto Cmdinput3;// �ظ�����ٴ�����ͣ�����һ����ɺ�ļ��������ڹ����Ϻܴ�̶�������

                }








Cmdinput2:

             printf("\n\n�Ƿ�����������ݣ�  ��(Y),��(N) ");

Cmdinput3:
             printf("\n��ѡ��  ");


             scanf("%1s",&cmd);
             getchar();  //�̻س�
             if((cmd=='Y') || (cmd=='y'))
             {
                ClearScreenTotalInputArea();
                continue;  //�Ӵ˺����������forѭ���еĵ�һ����俪ʼִ��
             }

             else if((cmd=='N') || (cmd=='n'))
             {

                 char *plabel_name[] = {"���ظ���Ϣ�⣬������Ϣ�Ѿ�����",
                           "�����ļ��˵���ѡ�񱣴浽�����ļ�",
                           "ȷ��"
                          };

                 ShowModule(plabel_name, 3);

                 ClearScreenTotalInputArea();


                 break; //�����˺�����������Ǹ����forѭ�� ִ�д˺�������������ع��
             }
             else
                {
                  char *plabel_name[] = {"�����������!",
                           "���������룡",
                           "ȷ��"
                          };

                 ShowModule(plabel_name, 3);
                 ClearScreenTotalInputArea();

                 goto Cmdinput2;

                }



        }  //�������forѭ��������
        /*���ع��*/
        GetConsoleCursorInfo(gh_std_out,&lpCur);
        lpCur.bVisible=FALSE;
        SetConsoleCursorInfo(gh_std_out,&lpCur);

 return TRUE;


}

void ClearScreenTotalInputArea(void)
{

    CONSOLE_SCREEN_BUFFER_INFO bInfo;
    COORD home = {0,1};
    unsigned long size , ul;


    GetConsoleScreenBufferInfo(gh_std_out,&bInfo);  //ȡ��Ļ��������Ϣ
    size = bInfo.dwSize.X * (bInfo.dwSize.Y-1);   //������Ļ���������˵�һ���ַ���Ԫ��

    /*����Ļ���������˵�һ�����е�Ԫ���ַ���������Ϊ��ǰ��Ļ�������ַ�����*/

    FillConsoleOutputAttribute(gh_std_out, bInfo.wAttributes, size, home, &ul);


    /*����Ļ���������˵�һ�����е�Ԫ���Ϊ�ո��*/
    FillConsoleOutputCharacter(gh_std_out, ' ', size, home, &ul);
    SetConsoleCursorPosition(gh_std_out,home);


    return;

}

BOOL SchInfoMod(void)
{
    char sch_name[20] , cmd;
    SCH_NODE *psch_node_temp;



Cmdinput4:

    ClearScreenTotalInputArea();  //����

    printf("��Ҫ�޸��ĸ�Ժϵ��Ժϵ��Ϣ��\n");
    printf("(����Ժϵ���ƣ�����20�ַ�,�м��޿ո�)\n\n");
    printf("  ��    ");

    scanf("%s",sch_name);
    getchar();

    psch_node_temp = SeekSchNode(gp_head,sch_name);

    if(psch_node_temp != NULL)
    {
        printf("\n������Ҫ�޸���Ϣ��Ժϵ��\n");


        for(;;)
        {

             printf("�����������Ժϵ������Ϣ��\n\n");
             printf("\n\n  �밴���¸�ʽҪ���������ݣ�\n1,���ݼ��ÿո����\n2,ͬһ���������޿ո� \n3,���ݱ����������벻�����\n\n");

             char *tab[3]={"Ժϵ����","������", "��ϵ�绰"};

             printf(" %-20s%-12s%-15s\n",tab[0],tab[1],tab[2]);
             printf("------------------------------------------------------------\n");

             scanf("%s %s %s",psch_node_temp->sch_name,psch_node_temp->boss_name,psch_node_temp->tel);
             getchar();  //�̻س�

Cmdinput3:

             printf("\n\n�Ƿ�����޸ģ�  ����޸�(Y),�����޸�(N) ");
             printf("\n��ѡ��  ");


             scanf("%1s",&cmd);
             getchar();  //�̻س�
             if((cmd=='N') || (cmd=='n'))
             {
                ClearScreenTotalInputArea();
                continue;
             }

             else if((cmd=='Y') || (cmd=='y'))
             {

                 char *plabel_name[] = {"�µ���Ϣ�Ѿ�����",
                           "�����ļ��˵���ѡ�񱣴浽�����ļ�",
                           "ȷ��"
                          };

                 ShowModule(plabel_name, 3);

                 ClearScreenTotalInputArea();


                 break;
             }
             else
                {
                  char *plabel_name[] = {"�����������!",
                           "���������룡",
                           "ȷ��"
                          };

                 ShowModule(plabel_name, 3);
                 ClearScreenTotalInputArea();

                 goto Cmdinput3;

                }

    }

 Cmdinput6:

 printf("�Ƿ��������Ժϵ�����Ϣ�޸ģ�\n");
 printf("    ��(Y),��(N)\n");
 printf("��ѡ��  ");

 scanf("%1s",&cmd);
 getchar();
 switch(cmd)
 {
    case 'Y':

    case 'y': goto Cmdinput4;

    case 'n':

    case 'N':
    {
        char *plabel_name[] = {"��Ϣ�޸����",
                            "�µ���Ϣ�Ѿ�����",
                           "�����ļ��˵���ѡ�񱣴浽�����ļ�",
                           "ȷ��"
                          };
        ShowModule(plabel_name, 4);
        ClearScreenTotalInputArea();



                 /*���ع��*/
        GetConsoleCursorInfo(gh_std_out,&lpCur);
        lpCur.bVisible=FALSE;
        SetConsoleCursorInfo(gh_std_out,&lpCur);

        break;
    }

    default :
    {
        char *plabel_name[] = {"�����������!",
                           "���������룡",
                           "ȷ��"
                          };

                 ShowModule(plabel_name, 3);
                 ClearScreenTotalInputArea();
                 goto Cmdinput6;


    }


  }

  return TRUE;


}


    else
   {
 Cmdinput5:

         printf("\n�������Ժϵ������! �Ƿ��������룿 ");
         printf("\n ��(Y),��(N)\n��ѡ��  ");

         scanf("%1s",&cmd);
         getchar();

         if((cmd=='Y') || (cmd=='y'))
          {
               goto Cmdinput4;
          }


          else  if((cmd=='N') || (cmd=='n'))
              {


                char *plabel_name[] = {"�޸Ĳ�������",
                                  "�����һ�������޸�ʧ�ܣ�",
                                  "(��Ϊ�����ҵ�Ժϵ������)",
                                  "ȷ��"
                                   };
                ShowModule(plabel_name, 4);
                ClearScreenTotalInputArea();

                  /*���ع��*/
             GetConsoleCursorInfo(gh_std_out,&lpCur);
             lpCur.bVisible=FALSE;
             SetConsoleCursorInfo(gh_std_out,&lpCur);

             return TRUE;
              }

          else
             {
               char *plabel_name[] = {"�����������",
                                      "���������룡",
                                        "ȷ��"
                                      };

                ShowModule(plabel_name, 3);
                ClearScreenTotalInputArea();

                goto Cmdinput5;

              }



    }


}
SCH_NODE* SeekSchNode(SCH_NODE *hp,char *sch_name)
{


    while(hp!=NULL)
    {
        if(strcmp(hp->sch_name,sch_name)==0)
        {
          break;
        }
        hp=hp->next;
    }


  return hp;
}

SCH_NODE* SchInfoDel(SCH_NODE **hp, char* sch_name)
{
   SCH_NODE *pToDel, *current=*hp, *prior=*hp;
   pToDel = SeekSchNode(*hp,sch_name);

   while((current!=pToDel) && (current!=NULL))
   {
       prior=current;
       current=current->next;
   }

   if(!current)
      return NULL;


   if(current==*hp)
        *hp=current->next;

   else
      prior->next=current->next;


   free(current);
   return current;



}



BOOL SchInfoDelete(void)
 {
            char sch_name[20],cmd;

             Cmdinput2:
                   printf("\n\n����Ҫɾ���Ǹ�Ժϵ����Ϣ��\n:    ");
                   scanf("%s",sch_name);
                   getchar();

                   if(SeekSchNode(gp_head,sch_name)!=NULL)
                   {
                        SchInfoDel(&gp_head,sch_name);
                        char *plabel_name[] = {"ɾ���ɹ���",
                           "�����ļ��˵���ѡ���޸ı��浽�����ļ�",
                           "ȷ��"
                          };

                          ShowModule(plabel_name, 3);

                          ClearScreenTotalInputArea();

                    Cmdinput3:
                          printf("�Ƿ����ִ��ɾ�����ܣ�  ��(Y),  ��(N)\n��ѡ��  ");
                          scanf("%1s",&cmd);
                          getchar();

                          switch(cmd)
                             {
                                case 'Y':
                                case 'y':
                                       {
                                           ClearScreenTotalInputArea();
                                           goto Cmdinput2;
                                       }


                                case 'N':
                                case 'n':
                                       {
                                           char *plabel_name[] = {"ɾ������ִ����ϣ�",
                                            "�����ļ��˵���ѡ���޸ı��浽�����ļ�",
                                               "ȷ��"
                                                        };

                                           ShowModule(plabel_name, 3);

                                           ClearScreenTotalInputArea();

                                           return TRUE;
                                        }
                                default:

                                       {
                                           char *plabel_name[] = {"��������������������룡",
                                            "  ",
                                               "ȷ��"
                                                        };

                                           ShowModule(plabel_name, 3);

                                           ClearScreenTotalInputArea();

                                           goto Cmdinput3;

                                       }



                                }





                    }

                    else
                    {
                         char *plabel_name[] = {"����Ҫɾ����Ժϵ������!",
                           "  ",
                           "ȷ��"
                          };

                          ShowModule(plabel_name, 3);
                          ClearScreenTotalInputArea();
                          goto Cmdinput3;


                    }


};


BOOL TeamInfoInput(void)
{
    CONSOLE_CURSOR_INFO lpCur;  //�洢�����Ϣ

    SCH_NODE *pSeekSchReturn;
    TEAM_NODE *pTeamNode=NULL, *pSeekTeamReturn;
    char cmd,sch_name[20],team_name[30];
    ClearScreenTotalInputArea();  //����



    for(;;)
     {

        Cmdinput1:

                printf("�����룺��Ҫ������Ϣ�Ŀ����Ŷ�����Ժϵ(����20���ַ�)��\n :    ");
                scanf("%s",sch_name);
                getchar();
                pSeekSchReturn = SeekSchNode(gp_head,sch_name);
                if(pSeekSchReturn==NULL)  //��Ժϵ������
                {
                    Cmdinput2:
                          printf("\n\n�������Ժϵ�����ڣ��Ƿ��������룿  ��(Y),  ��(N)\n��ѡ��  ");
                          scanf("%1s",&cmd);
                          getchar();

                          switch(cmd)
                             {
                                case 'Y':
                                case 'y':
                                       {
                                           ClearScreenTotalInputArea();
                                           goto Cmdinput1;
                                       }


                                case 'N':
                                case 'n':
                                       {
                                           char *plabel_name[] = {"��Ϣ¼�빦��ִ����ϣ�",
                                            "�����ļ��˵���ѡ���޸ı��浽�����ļ�",
                                               "ȷ��"
                                                        };

                                           ShowModule(plabel_name, 3);

                                           ClearScreenTotalInputArea();

                                           return TRUE;
                                        }
                                default:

                                       {
                                           char *plabel_name[] = {"��������������������룡",
                                            "  ",
                                               "ȷ��"
                                                        };

                                           ShowModule(plabel_name, 3);

                                           ClearScreenTotalInputArea();

                                           goto Cmdinput2;

                                       }

                             }
                }

                else //���������Ժϵ����
                {


                       printf("\n��������Ҫ¼����Ϣ�Ŀ����Ŷ���(����30�ַ�):\n    ");
                       scanf("%s",team_name);
                       getchar();

                       pSeekTeamReturn=SeekTeamNode(pSeekSchReturn->tnext,team_name);
                       if( pSeekTeamReturn == NULL)//�����Ŷ���������
                       {
                             /*�Ƚ���������붯̬�ռ�,Ȼ����б�Ҫ�ĳ�ʼ��*/
                              pTeamNode = (TEAM_NODE*)malloc(sizeof(TEAM_NODE));
                              pTeamNode->snext=NULL; //��������ָ�� ����һ���Ǳ���ģ���
                              pTeamNode->next=NULL;/*��������ָ�룡����һ���Ǳ��յģ�����Ϊ��Ժϵ��������ʱ��Ӧ���Ѿ���tnext�ÿ��ˣ�
                              �����������Ŷ���Ϣ�Ǹ�Ժϵ�ĵ�һ��¼����Ϣ���Ŷӣ���ô��һ�д����൱��next�ÿա�������һ���б������ã�����Ҫ����*/
                              pTeamNode->next = pSeekSchReturn->tnext;
                              pSeekSchReturn->tnext = pTeamNode;

                              strcpy(pTeamNode->sch,sch_name);//��ΪԺϵ���Ѿ�ȷ���ˣ�����sch_name
                              strcpy(pTeamNode->team_name,team_name);//��Ϊ�Ŷ�������ʱ���Ѿ�ȷ�� ����team_name



                               printf("\n##�밴���¸�ʽҪ����������##\n1,���ݼ��ÿո����\n2,ͬһ���������޿ո� \n3,���ݱ����������벻�����\n\n");
                               printf("��ʽ��\n       ������          ��ʦ����        �о�������  \n");
                               scanf(" %s %d %d",pTeamNode->boss_name,&pTeamNode->prof_num,&pTeamNode->stu_num);
                               getchar();  //�̻س�
                        }


                        else
                         {

                               printf("\n�˿����Ŷӵ���Ϣ�Ѿ�����\n�����������µ��Ŷ���Ϣ\n�����޸Ĺ������޸Ĵ��Ŷ���Ϣ\n\n");
                               printf("�Ƿ���������?  ��(Y),��(N)\n\n");


                                goto Cmdinput4;// �ظ�����ٴ�����ͣ�����һ����ɺ�ļ��������ڹ����Ϻܴ�̶�������

                          }


                }












Cmdinput3:

             printf("\n\n�Ƿ�����������ݣ�  ��(Y),��(N) ");

Cmdinput4:
             printf("\n��ѡ��  ");


             scanf("%1s",&cmd);
             getchar();  //�̻س�
             if((cmd=='Y') || (cmd=='y'))
             {
                ClearScreenTotalInputArea();
                continue;  //�Ӵ˺����������forѭ���еĵ�һ����俪ʼִ��
             }

             else if((cmd=='N') || (cmd=='n'))
             {

                 char *plabel_name[] = {"���ظ���Ϣ�⣬������Ϣ�Ѿ�����",
                           "�����ļ��˵���ѡ�񱣴浽�����ļ�",
                           "ȷ��"
                          };

                 ShowModule(plabel_name, 3);

                 ClearScreenTotalInputArea();


                 break; //�����˺�����������Ǹ����forѭ�� ִ�д˺�������������ع��
             }
             else
                {
                  char *plabel_name[] = {"�����������!",
                           "���������룡",
                           "ȷ��"
                          };

                 ShowModule(plabel_name, 3);
                 ClearScreenTotalInputArea();

                 goto Cmdinput3;

                }



        }  //�������forѭ��������
        /*���ع��*/
        GetConsoleCursorInfo(gh_std_out,&lpCur);
        lpCur.bVisible=FALSE;
        SetConsoleCursorInfo(gh_std_out,&lpCur);

 return TRUE;


}



TEAM_NODE* SeekTeamNode(TEAM_NODE*hp, char *team_name)
{


    while(hp!=NULL)
    {
        if(strcmp(hp->team_name,team_name)==0)
        {
          break;
        }
        hp=hp->next;
    }


  return hp;
}


BOOL TeamInfoMod(void)
{
    char sch_name[20] ,team_name[30], cmd;
    SCH_NODE *psch_node_temp;
    TEAM_NODE *pteam_node_temp;



Cmdinput4:

    ClearScreenTotalInputArea();  //����

    printf("��Ҫ�޸��ĸ�Ժϵ���ĸ��Ŷӵ���Ϣ��\n");
    printf("(����Ժϵ�����Լ��Ŷ�����)\n(���������ڲ��޿ո�)\n(��������֮���ÿո����)\n\n");
    printf("��ʽ��   Ժϵ����                �����Ŷ�����\n");
    printf("    ��   ");

    scanf("%s %s",sch_name,team_name);
    getchar();

    if(  (  psch_node_temp = SeekSchNode(gp_head,sch_name)  ) != NULL );
         pteam_node_temp = SeekTeamNode(psch_node_temp->tnext, team_name );//��ô������Ϊ����Ҫͬʱ���������ҵ�Ժϵ�Ϳ����Ŷ�ͬʱ����

    if( (psch_node_temp!=NULL) && (pteam_node_temp!=NULL) )  //��������ҵ�Ժϵ�������ڵĿ���ͬ��ͬʱ����
    {
        printf("\n������Ҫ�޸ĵ���Ϣ��㣡\n");


        for(;;)
        {

             printf("����������ÿ����Ŷӵ�����Ϣ��\n\n");
             printf("\n\n  �밴���¸�ʽҪ���������ݣ�\n1,���ݼ��ÿո����\n2,ͬһ���������޿ո� \n3,���ݱ����������벻�����\n\n");
             printf("��ʽ��\n        �Ŷ�����\t������\t     ��ʦ����\t    �о�������\t\n");

             scanf("%s %s %d %d",pteam_node_temp->team_name, pteam_node_temp->boss_name, &pteam_node_temp->prof_num, &pteam_node_temp->stu_num);

             getchar();  //�̻س�

Cmdinput3:

             printf("\n\n�Ƿ�����޸ģ�  ����޸�(Y),�����޸�(N) ");
             printf("\n��ѡ��  ");


             scanf("%1s",&cmd);
             getchar();  //�̻س�
             if((cmd=='N') || (cmd=='n'))
             {
                ClearScreenTotalInputArea();
                continue;
             }

             else if((cmd=='Y') || (cmd=='y'))
             {

                 char *plabel_name[] = {"�µ���Ϣ�Ѿ�����",
                           "�����ļ��˵���ѡ�񱣴浽�����ļ�",
                           "ȷ��"
                          };

                 ShowModule(plabel_name, 3);

                 ClearScreenTotalInputArea();


                 break;
             }
             else
                {
                  char *plabel_name[] = {"�����������!",
                           "���������룡",
                           "ȷ��"
                          };

                 ShowModule(plabel_name, 3);
                 ClearScreenTotalInputArea();

                 goto Cmdinput3;

                }

    }//����for���Ľ�����

 Cmdinput6://for��������֮��һ���޸���ɣ�����ѯ���Ƿ�����޸�

 printf("�Ƿ�������п����Ŷ������Ϣ�޸ģ�\n");
 printf("    ��(Y),��(N)\n");
 printf("��ѡ��  ");

 scanf("%1s",&cmd);
 getchar();
 switch(cmd)
 {
    case 'Y':

    case 'y': goto Cmdinput4;

    case 'n':

    case 'N':
    {
        char *plabel_name[] = {"��Ϣ�޸����",
                            "�µ���Ϣ�Ѿ�����",
                           "�����ļ��˵���ѡ�񱣴浽�����ļ�",
                           "ȷ��"
                          };
        ShowModule(plabel_name, 4);
        ClearScreenTotalInputArea();



                 /*���ع��*/
        GetConsoleCursorInfo(gh_std_out,&lpCur);
        lpCur.bVisible=FALSE;
        SetConsoleCursorInfo(gh_std_out,&lpCur);

        break; //�˳�switch��� ��ִ�������return���ֱ�ӽ����޸ĺ���
    }

    default :
    {
        char *plabel_name[] = {"�����������!",
                           "���������룡",
                           "ȷ��"
                          };

                 ShowModule(plabel_name, 3);
                 ClearScreenTotalInputArea();
                 goto Cmdinput6;


    }


  }

  return TRUE;


}  //��������Ǹ����if���Ľ�����


    else //���û�з�����Ҫ�ҵ��Ŷ� ������������Ǹ����if��Ӧ
   {
 Cmdinput5:

         printf("\n������Ŀ����ŶӲ�����! �Ƿ��������룿 ");
         printf("\n ��(Y),��(N)\n��ѡ��  ");

         scanf("%1s",&cmd);
         getchar();

         if((cmd=='Y') || (cmd=='y'))
          {
               goto Cmdinput4;
          }


          else  if((cmd=='N') || (cmd=='n'))
              {


                char *plabel_name[] = {"�޸Ĳ�������",
                                  "�����һ�������޸�ʧ�ܣ�",
                                  "(��Ϊ�����ҵ��ŶӲ�����)",
                                  "ȷ��"
                                   };
                ShowModule(plabel_name, 4);
                ClearScreenTotalInputArea();

                  /*���ع��*/
             GetConsoleCursorInfo(gh_std_out,&lpCur);
             lpCur.bVisible=FALSE;
             SetConsoleCursorInfo(gh_std_out,&lpCur);

             return TRUE;
              }

          else
             {
               char *plabel_name[] = {"�����������",
                                      "���������룡",
                                        "ȷ��"
                                      };

                ShowModule(plabel_name, 3);
                ClearScreenTotalInputArea();

                goto Cmdinput5;

              }



    }


}

BOOL TeamInfoDelete(void)
{
    char sch_name[20] ,team_name[30], cmd;
    SCH_NODE *psch_node_temp;
    TEAM_NODE *pteam_node_temp;



Cmdinput1:

    ClearScreenTotalInputArea();  //����

    printf("��Ҫɾ���ĸ�Ժϵ���ĸ��Ŷӵ���Ϣ��\n");
    printf("(����Ժϵ�����Լ��Ŷ�����)\n(���������ڲ��޿ո�)\n(��������֮���ÿո����)\n\n");
    printf("��ʽ��  Ժϵ����                �����Ŷ�����\n");
    printf("    ��  ");

    scanf("%s %s",sch_name,team_name);
    getchar();

    if(  (  psch_node_temp = SeekSchNode(gp_head,sch_name)  ) != NULL )
         pteam_node_temp = SeekTeamNode(psch_node_temp->tnext, team_name );//��ô������Ϊ����Ҫͬʱ���������ҵ�Ժϵ�Ϳ����Ŷ�ͬʱ����

    if( (psch_node_temp!=NULL) && (pteam_node_temp!=NULL) )  //��������ҵ�Ժϵ�������ڵĿ���ͬ��ͬʱ����
    {
        TeamInfoDel(&(psch_node_temp->tnext) , team_name ); //ɾ�����
        char *plabel_name[] = {"ɾ���ɹ���",
                           "�����ļ��˵���ѡ���޸ı��浽�����ļ�",
                           "ȷ��"
                          };

                          ShowModule(plabel_name, 3);

                          ClearScreenTotalInputArea();

                    Cmdinput2:
                          printf("�Ƿ����ִ��ɾ�����ܣ�  ��(Y),  ��(N)\n��ѡ��  ");
                          scanf("%1s",&cmd);
                          getchar();

                          switch(cmd)
                             {
                                case 'Y':
                                case 'y':
                                       {
                                           ClearScreenTotalInputArea();
                                           goto Cmdinput1;
                                       }


                                case 'N':
                                case 'n':
                                       {
                                           char *plabel_name[] = {"ɾ������ִ����ϣ�",
                                            "�����ļ��˵���ѡ���޸ı��浽�����ļ�",
                                               "ȷ��"
                                                        };

                                           ShowModule(plabel_name, 3);

                                           ClearScreenTotalInputArea();

                                           return TRUE;
                                        }
                                default:

                                       {
                                           char *plabel_name[] = {"��������������������룡",
                                            "  ",
                                               "ȷ��"
                                                        };

                                           ShowModule(plabel_name, 3);

                                           ClearScreenTotalInputArea();

                                           goto Cmdinput2;

                                       }



                                }





    }


    else //���Ҫɾ���Ŀ����ŶӲ�����
        {
                         char *plabel_name[] = {"����Ҫɾ���ĸ�Ժϵ�ڵĸ��ŶӲ�����!",
                           "  ",
                           "ȷ��"
                          };

                          ShowModule(plabel_name, 3);
                          ClearScreenTotalInputArea();
                          goto Cmdinput2;


        }


}

TEAM_NODE* TeamInfoDel(TEAM_NODE **hp, char* team_name)
{
   TEAM_NODE *pToDel, *current=*hp, *prior=*hp;
   pToDel = SeekTeamNode(*hp,team_name);

   while((current!=pToDel) && (current!=NULL))
   {
       prior=current;
       current=current->next;
   }

   if(!current)
      return NULL;


   if(current==*hp)
        *hp=current->next;

   else
      prior->next=current->next;


   free(current);
   return current;



}

BOOL SciprjInfoInput(void)
{
    CONSOLE_CURSOR_INFO lpCur;  //�洢�����Ϣ

    SCH_NODE *pSeekSchReturn;
    TEAM_NODE  *pSeekTeamReturn;
    SCIPRJ_NODE *pSciprjNode=NULL,*pSeekSciprjReturn;
    char cmd,sch_name[20],team_name[30],prj_num[15];
    ClearScreenTotalInputArea();  //����



    for(;;)
     {

        Cmdinput1:

                printf("�����룺��Ҫ������Ϣ�Ŀ�����Ŀ����Ժϵ�Լ��Ŷ�!");
                printf("\n(����Ժϵ�����Լ��Ŷ�����)\n(���������ڲ��޿ո�)\n(��������֮���ÿո����)\n\n");
                printf("��ʽ��  Ժϵ����                �����Ŷ���\n");
                printf("    ��  ");

                scanf("%s %s",sch_name,team_name);
                getchar();

                if(  (  pSeekSchReturn = SeekSchNode(gp_head,sch_name)  ) != NULL )
                              pSeekTeamReturn = SeekTeamNode(pSeekSchReturn->tnext, team_name );//��ô������Ϊ����Ҫͬʱ���������ҵ�Ժϵ�Ϳ����Ŷ�ͬʱ����

                if( (pSeekSchReturn!=NULL) && (pSeekTeamReturn!=NULL) )  //��������ҵ�Ժϵ�������ڵĿ���ͬ��ͬʱ����
                {
                     printf("\n��������Ҫ¼����Ϣ�Ŀ�����Ŀ���(����15�ַ�):\n    ");
                       scanf("%s",prj_num);
                       getchar();

                       pSeekSciprjReturn=SeekSciprjNode(pSeekTeamReturn->snext,prj_num);
                       if( pSeekSciprjReturn == NULL)//����ñ�ſ�����Ŀ������
                       {
                             /*�Ƚ���������붯̬�ռ�,Ȼ����б�Ҫ�ĳ�ʼ��*/
                              pSciprjNode = (SCIPRJ_NODE*)malloc(sizeof(SCIPRJ_NODE));
                              pSciprjNode->next=NULL;/*��������ָ�룡��*/
                              pSciprjNode->next = pSeekTeamReturn->snext;
                              pSeekTeamReturn->snext = pSciprjNode;

                              strcpy(pSciprjNode->team,team_name);//��Ϊ�����Ŷ����Ѿ�ȷ���ˣ�����team_name
                              strcpy(pSciprjNode->prj_num,prj_num);



                               printf("\n##�밴���¸�ʽҪ����������##\n1,���ݼ��ÿո����\n2,ͬһ���������޿ո� \n3,���ݱ����������벻�����\n\n");
                               printf("��ʽ��\n       ��Ŀ���(1�ַ�)  ��ʼʱ��(��19491001)  ��Ŀ����(��Ԫ)  ��Ŀ������\n       ");
                               scanf("%1s %s %f %s",&(pSciprjNode->type) , pSciprjNode->start_time, &(pSciprjNode->prj_fund), pSciprjNode->boss_name);
                               getchar();  //�̻س�
                        }


                        else
                         {

                               printf("\n�˿�����Ŀ����Ϣ�Ѿ�����\n�����������µ���Ŀ��Ϣ\n�����޸Ĺ������޸Ĵ���Ϣ\n\n");
                               printf("�Ƿ���������?  ��(Y),��(N)\n\n");


                                goto Cmdinput4;// �ظ�����ٴ�����ͣ�����һ����ɺ�ļ��������ڹ����Ϻܴ�̶�������

                          }

                }


                else //���������Ժϵ�ڵĿ����ŶӲ�����
                {

                        Cmdinput2:
                          printf("\n\n�������Ժϵ�ڵ��ŶӲ����ڣ��Ƿ��������룿  ��(Y),  ��(N)\n��ѡ��  ");
                          scanf("%1s",&cmd);
                          getchar();

                          switch(cmd)
                             {
                                case 'Y':
                                case 'y':
                                       {
                                           ClearScreenTotalInputArea();
                                           goto Cmdinput1;
                                       }


                                case 'N':
                                case 'n':
                                       {
                                           char *plabel_name[] = {"��Ϣ¼�빦��ִ����ϣ�",
                                            "�����ļ��˵���ѡ���޸ı��浽�����ļ�",
                                               "ȷ��"
                                                        };

                                           ShowModule(plabel_name, 3);

                                           ClearScreenTotalInputArea();

                                           return TRUE;
                                        }
                                default:

                                       {
                                           char *plabel_name[] = {"��������������������룡",
                                            "  ",
                                               "ȷ��"
                                                        };

                                           ShowModule(plabel_name, 3);

                                           ClearScreenTotalInputArea();

                                           goto Cmdinput2;

                                       }

                             }


                }



Cmdinput3:

             printf("\n\n�Ƿ�����������ݣ�  ��(Y),��(N) ");

Cmdinput4:
             printf("\n��ѡ��  ");


             scanf("%1s",&cmd);
             getchar();  //�̻س�
             if((cmd=='Y') || (cmd=='y'))
             {
                ClearScreenTotalInputArea();
                continue;  //�Ӵ˺����������forѭ���еĵ�һ����俪ʼִ��
             }

             else if((cmd=='N') || (cmd=='n'))
             {

                 char *plabel_name[] = {"���ظ���Ϣ�⣬������Ϣ�Ѿ�����",
                           "�����ļ��˵���ѡ�񱣴浽�����ļ�",
                           "ȷ��"
                          };

                 ShowModule(plabel_name, 3);

                 ClearScreenTotalInputArea();


                 break; //�����˺�����������Ǹ����forѭ�� ִ�д˺�������������ع��
             }
             else
                {
                  char *plabel_name[] = {"�����������!",
                           "���������룡",
                           "ȷ��"
                          };

                 ShowModule(plabel_name, 3);
                 ClearScreenTotalInputArea();

                 goto Cmdinput3;

                }



        }  //�������forѭ��������
        /*���ع��*/
        GetConsoleCursorInfo(gh_std_out,&lpCur);
        lpCur.bVisible=FALSE;
        SetConsoleCursorInfo(gh_std_out,&lpCur);

 return TRUE;

}

SCIPRJ_NODE* SeekSciprjNode(SCIPRJ_NODE* hp,char* prj_num)
{
    while(hp!=NULL)
    {
        if(strcmp(hp->prj_num,prj_num)==0)
        {
          break;
        }
        hp=hp->next;
    }


  return hp;
}

BOOL SciprjInfoMod(void)
{
    char sch_name[20] ,team_name[30],prj_num[15], cmd;
    SCH_NODE *pSeekSchReturn=NULL;
    TEAM_NODE *pSeekTeamReturn=NULL;
    SCIPRJ_NODE *pSeekSciprjReturn=NULL;



Cmdinput4:

    ClearScreenTotalInputArea();  //����

    printf("��Ҫ�޸��ĸ�Ժϵ���ĸ��Ŷӵ��ĸ���Ŀ����Ϣ��\n");
    printf("(����Ժϵ���ơ��Ŷ����ơ���Ŀ���)\n(ÿ���������ڲ��޿ո�)\n(����������֮���ÿո����)\n\n");
    printf("��ʽ��Ժϵ����                �����Ŷ���                    ��Ŀ���\n");
    printf("    ��");

    scanf("%s %s %s",sch_name,team_name,prj_num);
    getchar();

    if(  (  pSeekSchReturn = SeekSchNode(gp_head,sch_name)  ) != NULL );
        {
             pSeekTeamReturn = SeekTeamNode(pSeekSchReturn->tnext, team_name );//��ô������Ϊ����Ҫͬʱ���������ҵ�Ժϵ�Ϳ����Ŷ�ͬʱ����
             if( pSeekTeamReturn != NULL )
                pSeekSciprjReturn = SeekSciprjNode(pSeekTeamReturn->snext,prj_num); //��ô������Ϊ����Ҫ��Ҫͬʱ���������ҵ�Ժϵ�Ϳ����Ŷ�ͬʱ����ʱ���ٲ�����Ŀ
        }

    if( (pSeekSchReturn!=NULL) && (pSeekTeamReturn!=NULL) && (pSeekSciprjReturn!=NULL) )  //��������ҵ�Ժϵ�������ڵĿ���ͬ���Լ���Ŀͬʱ����
    {
        printf("\n������Ҫ�޸ĵ���Ϣ��㣡\n");


        for(;;)
        {

             printf("����������ÿ�����Ŀ������Ϣ��\n\n");
             printf("\n\n  �밴���¸�ʽҪ���������ݣ�\n1,���ݼ��ÿո����\n2,ͬһ���������޿ո� \n3,���ݱ����������벻�����\n\n");
             printf("��ʽ��\n       ��Ŀ���    ��Ŀ���    ��ʼʱ��    ��Ŀ����(��Ԫ)    ������\n       ");

             scanf("%s %1s %s %f %s",pSeekSciprjReturn->prj_num, &(pSeekSciprjReturn->type), pSeekSciprjReturn->start_time, &(pSeekSciprjReturn->prj_fund), pSeekSciprjReturn->boss_name);

             getchar();  //�̻س�

Cmdinput3:

             printf("\n\n�Ƿ�����޸ģ�  ����޸�(Y),�����޸�(N) ");
             printf("\n��ѡ��  ");


             scanf("%1s",&cmd);
             getchar();  //�̻س�
             if((cmd=='N') || (cmd=='n'))
             {
                ClearScreenTotalInputArea();
                continue;
             }

             else if((cmd=='Y') || (cmd=='y'))
             {

                 char *plabel_name[] = {"�µ���Ϣ�Ѿ�����",
                           "�����ļ��˵���ѡ�񱣴浽�����ļ�",
                           "ȷ��"
                          };

                 ShowModule(plabel_name, 3);

                 ClearScreenTotalInputArea();


                 break;
             }
             else
                {
                  char *plabel_name[] = {"�����������!",
                           "���������룡",
                           "ȷ��"
                          };

                 ShowModule(plabel_name, 3);
                 ClearScreenTotalInputArea();

                 goto Cmdinput3;

                }

    }//����for���Ľ�����

 Cmdinput6://for��������֮��һ���޸���ɣ�����ѯ���Ƿ�����޸�

 printf("�Ƿ�������п�����Ŀ�����Ϣ�޸ģ�\n");
 printf("    ��(Y),��(N)\n");
 printf("��ѡ��  ");

 scanf("%1s",&cmd);
 getchar();
 switch(cmd)
 {
    case 'Y':

    case 'y': goto Cmdinput4;

    case 'n':

    case 'N':
    {
        char *plabel_name[] = {"��Ϣ�޸����",
                            "�µ���Ϣ�Ѿ�����",
                           "�����ļ��˵���ѡ�񱣴浽�����ļ�",
                           "ȷ��"
                          };
        ShowModule(plabel_name, 4);
        ClearScreenTotalInputArea();



                 /*���ع��*/
        GetConsoleCursorInfo(gh_std_out,&lpCur);
        lpCur.bVisible=FALSE;
        SetConsoleCursorInfo(gh_std_out,&lpCur);

        break; //�˳�switch��� ��ִ�������return���ֱ�ӽ����޸ĺ���
    }

    default :
    {
        char *plabel_name[] = {"�����������!",
                           "���������룡",
                           "ȷ��"
                          };

                 ShowModule(plabel_name, 3);
                 ClearScreenTotalInputArea();
                 goto Cmdinput6;


    }


  }

  return TRUE;


}  //��������Ǹ����if���Ľ�����


    else //���û�з�����Ҫ�ҵ��Ŷ� ������������Ǹ����if��Ӧ
   {
 Cmdinput5:

         printf("\n������Ŀ�����Ŀ������! �Ƿ��������룿 ");
         printf("\n ��(Y),��(N)\n��ѡ��  ");

         scanf("%1s",&cmd);
         getchar();

         if((cmd=='Y') || (cmd=='y'))
          {
               goto Cmdinput4;
          }


          else  if((cmd=='N') || (cmd=='n'))
              {


                char *plabel_name[] = {"�޸Ĳ�������",
                                  "�����һ�������޸�ʧ�ܣ�",
                                  "(��Ϊ�����ҵ���Ŀ������)",
                                  "ȷ��"
                                   };
                ShowModule(plabel_name, 4);
                ClearScreenTotalInputArea();

                  /*���ع��*/
             GetConsoleCursorInfo(gh_std_out,&lpCur);
             lpCur.bVisible=FALSE;
             SetConsoleCursorInfo(gh_std_out,&lpCur);

             return TRUE;
              }

          else
             {
               char *plabel_name[] = {"�����������",
                                      "���������룡",
                                        "ȷ��"
                                      };

                ShowModule(plabel_name, 3);
                ClearScreenTotalInputArea();

                goto Cmdinput5;

              }



    }

}

BOOL SciprjInfoDelete(void)
{
char sch_name[20] ,team_name[30],prj_num[15], cmd;
    SCH_NODE *pSeekSchReturn=NULL;
    TEAM_NODE *pSeekTeamReturn=NULL;
    SCIPRJ_NODE *pSeekSciprjReturn=NULL;



Cmdinput1:

    ClearScreenTotalInputArea();  //����

    printf("��Ҫɾ���ĸ�Ժϵ���ĸ��Ŷӵ��ĸ���Ŀ����Ϣ��\n");
    printf("(����Ժϵ���ơ��Ŷ����ơ���Ŀ���)\n(ÿ���������ڲ��޿ո�)\n(����������֮���ÿո����)\n\n");
    printf("��ʽ��Ժϵ����            �����Ŷ���                    ��Ŀ���\n");
    printf("    ��");

    scanf("%s %s %s",sch_name,team_name,prj_num);

    getchar();

    if(  (  pSeekSchReturn = SeekSchNode(gp_head,sch_name)  ) != NULL )
        {
             pSeekTeamReturn = SeekTeamNode(pSeekSchReturn->tnext, team_name );//��ô������Ϊ����Ҫͬʱ���������ҵ�Ժϵ�Ϳ����Ŷ�ͬʱ����
             if( pSeekTeamReturn != NULL )
                pSeekSciprjReturn = SeekSciprjNode(pSeekTeamReturn->snext,prj_num); //��ô������Ϊ����Ҫ��Ҫͬʱ���������ҵ�Ժϵ�Ϳ����Ŷ�ͬʱ����ʱ���ٲ�����Ŀ
        }

    if( (pSeekSchReturn!=NULL) && (pSeekTeamReturn!=NULL) && (pSeekSciprjReturn!=NULL) )  //��������ҵ�Ժϵ�������ڵĿ���ͬ���Լ���Ŀͬʱ����
    {
        SciprjInfoDel(&(pSeekTeamReturn->snext) , prj_num ); //ɾ�����
        char *plabel_name[] = {"ɾ���ɹ���",
                           "�����ļ��˵���ѡ���޸ı��浽�����ļ�",
                           "ȷ��"
                          };

                          ShowModule(plabel_name, 3);

                          ClearScreenTotalInputArea();

                    Cmdinput2:
                          printf("�Ƿ����ִ��ɾ�����ܣ�  ��(Y),  ��(N)\n��ѡ��  ");
                          scanf("%1s",&cmd);
                          getchar();

                          switch(cmd)
                             {
                                case 'Y':
                                case 'y':
                                       {
                                           ClearScreenTotalInputArea();
                                           goto Cmdinput1;
                                       }


                                case 'N':
                                case 'n':
                                       {
                                           char *plabel_name[] = {"ɾ������ִ����ϣ�",
                                            "�����ļ��˵���ѡ���޸ı��浽�����ļ�",
                                               "ȷ��"
                                                        };

                                           ShowModule(plabel_name, 3);

                                           ClearScreenTotalInputArea();

                                           return TRUE;
                                        }
                                default:

                                       {
                                           char *plabel_name[] = {"��������������������룡",
                                            "  ",
                                               "ȷ��"
                                                        };

                                           ShowModule(plabel_name, 3);

                                           ClearScreenTotalInputArea();

                                           goto Cmdinput2;

                                       }



                                }

                          // break;



    }


    else //���Ҫɾ���Ŀ����ŶӲ�����
        {
                         char *plabel_name[] = {"����Ҫɾ���ĸ�Ժϵ�ڵĸ��Ŷӵĸ���Ŀ������!",
                           "  ",
                           "ȷ��"
                          };

                          ShowModule(plabel_name, 3);
                          ClearScreenTotalInputArea();
                          goto Cmdinput2;


        }



}


SCIPRJ_NODE* SciprjInfoDel(SCIPRJ_NODE **hp, char* prj_num)
{
   SCIPRJ_NODE *pToDel, *current=*hp, *prior=*hp;
   pToDel = SeekSciprjNode(*hp,prj_num);

   while((current!=pToDel) && (current!=NULL))
   {
       prior=current;
       current=current->next;
   }

   if(!current)
      return NULL;


   if(current==*hp)
        *hp=current->next;

   else
      prior->next=current->next;


   free(current);
   return current;



}

void SpaceToUnderline(char*s) //C������create�����ܴ������ļ����ļ���ֻ���Ǳ�ʶ������˰�ϵͳʱ���ַ����е�ð�ŵĿո����»���
{
    int i=0;
    for(i=0;(s)[i]!='\0';i++)
    {
        if( (s[i]==' ' ) ||  (s[i]==':' )   )
            s[i]='_';
        else
        {
            continue;
        }
    }

    return;
}

 void AddBackslash(char*s) //��һ����������������2������������ \ �ַ����ַ����У��ѳ��ֵ� \ �ַ����  "\\"
 {
     int i=0,j,len;
     for(i=0;s[i]!='\0';i++)
     {
         if(s[i]=='\\') // ���s[i]��\ ��
         {
             len=strlen(s);
             for(j=len;j>i;j--)//forѭ���ǰ�s[i]����������ַ����ƽ��һ�£�Ϊ����s[i]�����\�ڳ��ռ�
             {
               s[j+1]=s[j];
             }
             s[i+1]='\\';
             i++;  //ע����ʱ��s[i]֮����Ǹ��ַ�Ҳ��\�ˣ����iҪ����1��������ӵ�\ �����������\��

         }
         else
            continue;
     }
return;

}

void GetBackupFilename(char *dir )//�õ�����·���ı����ļ���

{
    int len;//�ַ�������

    time_t t;//����һ��ʱ�����
    t=time(NULL);

    char *time;//����һ���ַ������������ȡ�������ں�ʱ��
    time=ctime(&t);//��ֵ

    SpaceToUnderline(time);//C������create�����ܴ������ļ����ļ���ֻ���Ǳ�ʶ������˰�ϵͳʱ���ַ����е�ð�ŵĿո����»���

/*��ʱ���ַ���������Ϻ�׺�������ļ�����ע�ⲻ����strcat��������Ϊʱ���ַ���time��'\0'�ַ�֮ǰ���и��������Ļ��з���ֱ�ӽ��ϻ��".dat"�ӵ����з�����*/
      len=strlen(time);
      time[len-1]='.';
      time[len]='d';
      time[len+1]='a';
      time[len+2]='t';
      time[len+3]='\0';    //�����ļ�����������ˣ���ʱtime������ַ����Ǵ���׺�����ļ����ˣ���������ʱ���ַ���




      char BackupDir[9]="\\backup\\";
      getcwd(dir,100);//��ȡ��ǰ������ַ,�ص��ǣ���������һ�У�
/*char *getcwd(char *buf, size_t size);  ���ǻ�ȡ��ǰ��ַ������ԭ�ͣ������ڶ�������Ӧ����sizeof(dir),����ע���������Ǹ�ָ�볣��������ȫͬ��ָ�����������char s[10],*p=s **pp=&p; ,sizeof(s)����10
��sizeof(p)��sizeof(pp)ȴ����4����Ϊһ��ָ�����ռ�ĸ��ֽ��ǹ̶��ģ����charָ����Ϊ��������ʱ�򴫵ݲ����ַ�����ռ���ֽ�������˵ڶ�������ֻ����100����Ϊ��BackupData������
���������ڴ��溬��ַ�ı����ļ������ַ����� Ϊchar filename[100] sizeof(filename)����100*����getcwd(dir,sizeof(dir))�Ǵ����*/


      strcat(dir,BackupDir);//�ڵ�ǰ������ַ֮�����\backup\���챸���ļ�������Ŀ¼
      strcat(dir,time);//��Ŀ¼��������ļ���
      AddBackslash(dir);//������·���ַ����������еĵ��� \ ���\\  �Ա㵱���ļ����ַ�����create�Ⱥ�������ʵ��ʱ \\ ת��� ��\��


     return ;
}



BOOL Choice(char*pCh[],int n)//������ʾ��ѡ���ǡ�  ���ǡ��� ����������Ӧ����ֵ�ĺ���,����char*pCh[]��Ҫ��ʾ���ַ������飬n���ַ��������Ԫ�ظ���������ʾ�����ֵ�����
{
   //����char *pCh[] = {"ȷ���˳�ϵͳ��", "ȷ��    ȡ��"};

    LABEL_BUNDLE labels;//����������ʾ���е��ı���Ϣ�������ı������ݣ��ı���ÿ���ַ��������λ�ã��ı�������
    HOT_AREA areas;
    BOOL bRet = TRUE;
    SMALL_RECT rcPop;
    COORD pos,home;
    WORD att;
    att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/

    int iHot = 1,i=0,maxlen,str_len,size;

     for (i=0,maxlen=0; i<n; i++)//�����i<n�����n����ʾ�������ֵ�������Ҳ�����ַ�������char*pCh[]����ʵ�κ��Ԫ�ظ���
    {
        str_len = strlen(pCh[i]);
        if (maxlen < str_len)
        {
            maxlen = str_len;
        }
    }  //maxlen���ַ�����������ַ�������



    pos.X = maxlen + 6;  //��ʾ��Ŀ��
    pos.Y = n+5;    //��ʾ������ĳ���
    rcPop.Left = (SCR_COL - pos.X) / 2;   //��ʾ���������
    rcPop.Right = rcPop.Left + pos.X - 1; //��ʾ����ұ����
    rcPop.Top = (SCR_ROW - pos.Y) / 2;    //��ʾ����ϱ����
    rcPop.Bottom = rcPop.Top + pos.Y - 1; //��ʾ����±����




   /*home��ʼ��Ϊ������ʾ������Ͻ����꣬*/
    home.X=rcPop.Left;
    home.Y=rcPop.Top;
    size=maxlen + 6; //sizeΪ��ʾ���ȣ���ʵ����pos.X

     /*����ʾ�������е�Ԫ���Ϊ�ո��*/
    for(i=0;i<pos.Y; ++i,++home.Y)  //pos.YΪ��ʾ������
    FillConsoleOutputCharacter(gh_std_out, ' ', size, home, &ul);




    COORD aLoc[n]; //��������ַ��������λ��
    for (i=0; i<n; i++) //��forѭ��������ʾ������ʾ��ÿһ���ַ��������λ�ó�ʼ��������i���ַ����ĵ�һ���ַ������￪ʼ�����
    {
        aLoc[i].X = rcPop.Left + 3;
        aLoc[i].Y = rcPop.Top + 2 + i;

    }

   /*����3�д�����ȷ���βδ��ݽ������ַ�����������һ���ַ��������λ�ã�����һ���� ����  �� �������ַ�������˿��м�һ��ȽϺÿ�*/
    str_len = strlen(pCh[n-1]);
    aLoc[n-1].X = rcPop.Left + 3 + (maxlen-str_len)/2;
    aLoc[n-1].Y = aLoc[n-1].Y + 2;
   //���� aLoc�Ѿ���ɸ�ֵ


    labels.pLoc = aLoc;//��aLoc�д����λ����Ϣ�浽labels�ṹ��pLoc��Ա��
    labels.num = n;  //��ʾ����ı�����Ϊn
    labels.ppLabel = pCh;//��ʾ���е��ı�����Ϊ�βδ��ݹ���������


/*aArea������������ʾ�����һ�С���  ���ϱ�עѡ��Ĺ���λ�ã���һ����Ԫ�ص��ĸ�СԪ�طֱ��ʾ��
����ڡ��ǡ���ʱ����߽��X��Y���꣬�ұ߽��X��Y���ꡣ�ڶ�����Ԫ���ǡ��񡱵�,����ͬ��*/
    SMALL_RECT aArea[] = {
                           {aLoc[n-1].X, aLoc[n-1].Y,
                           aLoc[n-1].X + 3, aLoc[n-1].Y},

                           {aLoc[n-1].X+8, aLoc[n-1].Y,
                           aLoc[n-1].X+8+3, aLoc[n-1].Y}

                          };


    /*home��ʼ��Ϊ������ʾ������Ͻ����꣬*/
    home.X=rcPop.Left;
    home.Y=rcPop.Top;
    size=maxlen + 6; //sizeΪ��ʾ���ȣ���ʵ����pos.X

     /*����ʾ�������е�Ԫ���Ϊ�ո��*/
    for(i=0;i<pos.Y; ++i,++home.Y)  //pos.YΪ��ʾ������
    FillConsoleOutputCharacter(gh_std_out, ' ', size, home, &ul);


    char aSort[] = {0, 0};
    char aTag[] = {1, 2};
    areas.num = 2;//��������  ����  ��  ���Ϊ2
    areas.pArea = aArea;  //�������Ƿ�ѡ���λ��
    areas.pSort = aSort;
    areas.pTag = aTag;
    PopUp(&rcPop, att, &labels, &areas);

    pos.X = rcPop.Left + 1;
    pos.Y = rcPop.Top + 2 + n;   //��ʱpos�е����ݱ�����Ϊ���'-'����ʼλ�ã������������ʾ������Ĵ�С��ͬ
    FillConsoleOutputCharacter(gh_std_out, '-', rcPop.Right-rcPop.Left-1, pos, &ul);

    if (DealInput(&areas, &iHot) == 13 && iHot == 1)
    {
        bRet = TRUE;
    }
    else
    {
        bRet = FALSE;
    }
    PopOff();

    return bRet;

}
BOOL QuerySchInfoViaBossname(void)//��ѯԺϵ������Ϣ�Ĵ����е�ʵ����Ҫ���ܵ�С����
{

    BOOL bRet;
    CONSOLE_CURSOR_INFO lpCur;
    char boss_name[12];
    SCH_NODE *psch_node;
    int i=0,num=0;


Cmdinput1:
    psch_node=gp_head;

    char *plabel_name[] = {"��������Ҫ��ѯ��Ϣ��Ժϵ�ĸ���������",
                           "         ( ����12�ַ� ��            ",
                           "ȷ��"
                          };

                          ShowModule(plabel_name, 3);

                          ClearScreenTotalInputArea();

    /*��ʾ���*/
    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible=TRUE;
    SetConsoleCursorInfo(gh_std_out,&lpCur);


    printf("������������  ");
    scanf("%s",boss_name);
    getchar();


    num=0;
    i=0;//�����������������ٳ�ʼ��Ϊ�㣬��Ȼ������ѯʱ��num����һ�β�ѯ�Ļ������������Ϳ��ܳ��ִ���


    while(psch_node!=NULL)//��һ���ж��ٸ��������������������Ժϵ
    {
        if(strcmp(psch_node->boss_name,boss_name)==0)
        {
          num++;
        }
        psch_node=psch_node->next;
    }
    psch_node=gp_head;//psch_node����ָ������ͷ

    SCH_NODE *find[num+1];//Ԫ�ظ�����һ��������NULL��Ϊ������
    find[0]=NULL;//����ĵ�һ��ָ���ÿգ����һ��������Ϊ��������˵�Ժϵ��û�ҵ�����ôfind[0]Ϊ���򲻻�ı䣬��֮��ı䣬��˿����������жϱ�־


    while(psch_node!=NULL)//�������и�������������������˵�������ͬ�ı���ָ���¼����
    {
        if(strcmp(psch_node->boss_name,boss_name)==0)
        {
          find[i]=psch_node;i++;
        }
        psch_node=psch_node->next;
    }
    find[i]=NULL;//���һ��ָ���ÿգ����һ��û�ҵ����þ�find[0]=NULL;



    if(find[0]!=NULL)//���ٷ���һ��������Ϊ�������������Ժϵ
    {   int i;
        printf("\n               ###�鵽���Ժϵ��Ϣ###\n\n");
        char *tab[3]={"Ժϵ����","������", "��ϵ�绰"};

        printf(" %-20s%-12s%-15s\n",tab[0],tab[1],tab[2]);
        printf("------------------------------------------------------------\n");

        for(i=0;find[i]!=NULL;i++)//ѭ��������и�����Ϊ��������˵�Ժϵ�����Ϣ
       {
           printf(" %-20s%-12s%-15s\n",find[i]->sch_name, find[i]->boss_name, find[i]->tel);
       }


        getch();
        char *plabel_name[] = {"�Ƿ������ѯ��",  " "," ��      �� "};
        bRet=Choice(plabel_name,3) ;
        switch(bRet)
        {
            case TRUE:   {
                           ClearScreenTotalInputArea();
                           goto Cmdinput1;
                         }


            case FALSE:  {
                            char *plabel_name[] = {"��ɲ�ѯ��",
                                                "  ",
                                                "ȷ��"
                                                };

                           ShowModule(plabel_name, 3);

                           ClearScreenTotalInputArea();

                             goto End;
                         }



        }






    }

    else //һ��������Ϊ���˵���Ϣ��û�ҵ�
    {
        char *plabel_name[] = {"������������!"," ","�Ƿ��������룿"," ��      �� "};
        bRet=Choice(plabel_name,4) ;

         switch(bRet)
        {
            case TRUE:   {
                           ClearScreenTotalInputArea();
                           goto Cmdinput1;
                         }


            case FALSE:  {
                            char *plabel_name[] = {"��ɲ�ѯ��",
                                                "  ",
                                                "ȷ��"
                                                };

                           ShowModule(plabel_name, 3);

                           ClearScreenTotalInputArea();

                             goto End;
                         }



        }
    }

End:
    /*���ع��*/
    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible=FALSE;
    SetConsoleCursorInfo(gh_std_out,&lpCur);


    return TRUE;





}



BOOL QuerySchInfoViaSchsname(void)
{
    BOOL bRet;
    CONSOLE_CURSOR_INFO lpCur;
    char sch_name[20];
    SCH_NODE *psch_node;
    int i=0,num=0;


Cmdinput1:
    psch_node=gp_head;

    char *plabel_name[] = {"��������Ҫ��ѯ��Ϣ��Ժϵ�����Ƶ�ȫ���򲿷�",
                           "             ( ����20�ַ� ��              ",
                           "ȷ��"
                          };

                          ShowModule(plabel_name, 3);

                          ClearScreenTotalInputArea();

    /*��ʾ���*/
    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible=TRUE;
    SetConsoleCursorInfo(gh_std_out,&lpCur);


    printf("Ժϵ����ȫ���򲿷�(���޿ո�)��  ");
    scanf("%s",sch_name);
    getchar();


    num=0;
    i=0;//�����������������ٳ�ʼ��Ϊ�㣬��Ȼ������ѯʱ��num����һ�β�ѯ�Ļ������������Ϳ��ܳ��ִ���


    while(psch_node!=NULL)//��һ���ж��ٸ����йؼ��ֵ�ѧԺ��
    {
        if(strstr(psch_node->sch_name,sch_name)!=NULL)
        {
          num++;
        }
        psch_node=psch_node->next;
    }
    psch_node=gp_head;//psch_node����ָ������ͷ

    SCH_NODE *find[num+1];//Ԫ�ظ�����һ��������NULL��Ϊ������
    find[0]=NULL;//����ĵ�һ��ָ���ÿգ����һ����ص�Ժϵ��û�ҵ�����ôfind[0]Ϊ���򲻻�ı䣬��֮��ı䣬��˿����������жϱ�־


    while(psch_node!=NULL)//��������Ժϵ���к�������Ĺؼ��ֵı���ָ���¼����
    {
        if(strstr(psch_node->sch_name,sch_name)!=NULL)
        {
          find[i]=psch_node;i++;
        }
        psch_node=psch_node->next;
    }
    find[i]=NULL;//���һ��ָ���ÿգ����һ��û�ҵ����þ�find[0]=NULL;



    if(find[0]!=NULL)//���ٷ���һ�����Ժϵ
    {   int i;
        printf("\n               ###�鵽���Ժϵ��Ϣ###\n\n");
        char *tab[3]={"Ժϵ����","������", "��ϵ�绰"};

        printf(" %-20s%-12s%-15s\n",tab[0],tab[1],tab[2]);
        printf("------------------------------------------------------------\n");

        for(i=0;find[i]!=NULL;i++)//ѭ��������к��йؼ��ֵ�Ժϵ�����Ϣ
       {
           printf(" %-20s%-12s%-15s\n",find[i]->sch_name, find[i]->boss_name, find[i]->tel);
       }


        getch();
        char *plabel_name[] = {"�Ƿ������ѯ��",  " "," ��      �� "};
        bRet=Choice(plabel_name,3) ;
        switch(bRet)
        {
            case TRUE:   {
                           ClearScreenTotalInputArea();
                           goto Cmdinput1;
                         }


            case FALSE:  {
                            char *plabel_name[] = {"��ɲ�ѯ��",
                                                "  ",
                                                "ȷ��"
                                                };

                           ShowModule(plabel_name, 3);

                           ClearScreenTotalInputArea();

                             goto End;
                         }



        }






    }

    else //һ����������ؼ��ֵ�Ժϵ����Ϣ��û�ҵ�
    {
        char *plabel_name[] = {"�����Ժϵ������!"," ","�Ƿ��������룿"," ��      �� "};
        bRet=Choice(plabel_name,4) ;

         switch(bRet)
        {
            case TRUE:   {
                           ClearScreenTotalInputArea();
                           goto Cmdinput1;
                         }


            case FALSE:  {
                            char *plabel_name[] = {"��ɲ�ѯ��",
                                                "  ",
                                                "ȷ��"
                                                };

                           ShowModule(plabel_name, 3);

                           ClearScreenTotalInputArea();

                             goto End;
                         }



        }
    }

End:
    /*���ع��*/
    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible=FALSE;
    SetConsoleCursorInfo(gh_std_out,&lpCur);


    return TRUE;



}


BOOL QueryTeamInfoViaTeamname(void)
{
    BOOL bRet;
    CONSOLE_CURSOR_INFO lpCur;
    char team_name[30];
    SCH_NODE *psch_node;
    TEAM_NODE *pteam_node;
    int i=0,num=0;


Cmdinput1:
    psch_node=gp_head;

    char *plabel_name[] = {"��������Ҫ��ѯ��Ϣ���Ŷӵ����Ƶ�ȫ���򲿷�",
                           "             ( ����30�ַ� ��              ",
                           "ȷ��"
                          };

                          ShowModule(plabel_name, 3);

                          ClearScreenTotalInputArea();

    /*��ʾ���*/
    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible=TRUE;
    SetConsoleCursorInfo(gh_std_out,&lpCur);


    printf("�Ŷ�����ȫ���򲿷�(���޿ո�)��  ");
    scanf("%s",team_name);
    getchar();


    num=0;
    i=0;//�����������������ٳ�ʼ��Ϊ�㣬��Ȼ������ѯʱ��num����һ�β�ѯ�Ļ������������Ϳ��ܳ��ִ���


    while(psch_node!=NULL)//��һ���ж����Ŷ����к�������ؼ��ֵ��Ŷ�
    {
        pteam_node=psch_node->tnext;
        while(pteam_node!=NULL)
        {

             if(strstr(pteam_node->team_name,team_name)!=NULL)
             {
               num++;
             }

             pteam_node=pteam_node->next;

         }

        psch_node=psch_node->next;
    }
    psch_node=gp_head;//psch_node����ָ������ͷ

    TEAM_NODE *find[num+1];//Ԫ�ظ�����һ��������NULL��Ϊ������
    find[0]=NULL;//����ĵ�һ��ָ���ÿգ����һ������ŶӶ�û�ҵ�����ôfind[0]Ϊ���򲻻�ı䣬��֮��ı䣬��˿����������жϱ�־


   while(psch_node!=NULL)
    {
        pteam_node=psch_node->tnext;
        while(pteam_node!=NULL)
        {

             if(strstr(pteam_node->team_name,team_name)!=NULL)
             {
               find[i]=pteam_node;i++;
             }

             pteam_node=pteam_node->next;

         }

        psch_node=psch_node->next;
    }

    find[i]=NULL;//���һ��ָ���ÿգ����һ��û�ҵ����þ�find[0]=NULL;




    if(find[0]!=NULL)//���ٷ���һ������Ŷ�
    {   int i;
        printf("\n               ###�鵽����Ŷ���Ϣ###\n\n");
        char *tab[5]={"�Ŷ�����","������", "��ʦ����", "�о�������","����Ժϵ"};

        printf(" %-30s%-12s%-14s%-14s%-20s\n",tab[0],tab[1],tab[2],tab[3],tab[4]);
        printf("-------------------------------------------------------------------------------\n");

        for(i=0;find[i]!=NULL;i++)//ѭ�������������Ŷ������Ϣ
       {
           printf(" %-30s%-12s%-14d%-14d%-20s\n",find[i]->team_name, find[i]->boss_name, find[i]->prof_num, find[i]->stu_num, find[i]->sch);
       }


        getch();
        char *plabel_name[] = {"�Ƿ������ѯ��",  " "," ��      �� "};
        bRet=Choice(plabel_name,3) ;
        switch(bRet)
        {
            case TRUE:   {
                           ClearScreenTotalInputArea();
                           goto Cmdinput1;
                         }


            case FALSE:  {
                            char *plabel_name[] = {"��ɲ�ѯ��",
                                                "  ",
                                                "ȷ��"
                                                };

                           ShowModule(plabel_name, 3);

                           ClearScreenTotalInputArea();

                             goto End;
                         }



        }






    }

    else //һ���Ŷ����к�������ؼ��ֵ��Ŷӵ���Ϣ��û�ҵ�
    {
        char *plabel_name[] = {"������ŶӲ�����!"," ","�Ƿ��������룿"," ��      �� "};
        bRet=Choice(plabel_name,4) ;

         switch(bRet)
        {
            case TRUE:   {
                           ClearScreenTotalInputArea();
                           goto Cmdinput1;
                         }


            case FALSE:  {
                            char *plabel_name[] = {"��ɲ�ѯ��",
                                                "  ",
                                                "ȷ��"
                                                };

                           ShowModule(plabel_name, 3);

                           ClearScreenTotalInputArea();

                             goto End;
                         }



        }
    }

End:
    /*���ع��*/
    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible=FALSE;
    SetConsoleCursorInfo(gh_std_out,&lpCur);


    return TRUE;





}


BOOL QuerySchInfoViaProfnum(void)
{
    BOOL bRet;
    CONSOLE_CURSOR_INFO lpCur;

    SCH_NODE *psch_node;
    TEAM_NODE *pteam_node;
    int i=0,num=0,prof_num;


Cmdinput1:
    psch_node=gp_head;

    char *plabel_name[] = {"�������Ŷӽ�ʦ����������",
                           " ",
                           "ȷ��"
                          };

                          ShowModule(plabel_name, 3);

                          ClearScreenTotalInputArea();

    /*��ʾ���*/
    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible=TRUE;
    SetConsoleCursorInfo(gh_std_out,&lpCur);


    printf("��ʦ�������ޣ�  ");
    scanf("%d",&prof_num);
    getchar();


    num=0;
    i=0;//�����������������ٳ�ʼ��Ϊ�㣬��Ȼ������ѯʱ��num����һ�β�ѯ�Ļ������������Ϳ��ܳ��ִ���


    while(psch_node!=NULL)//��һ���ж��ٸ���ʦ��������������������޵��Ŷ�
    {
        pteam_node=psch_node->tnext;
        while(pteam_node!=NULL)
        {

             if(pteam_node->prof_num>=prof_num)
             {
               num++;
             }

             pteam_node=pteam_node->next;

         }

        psch_node=psch_node->next;
    }
    psch_node=gp_head;//psch_node����ָ������ͷ

    TEAM_NODE *find[num+1];//Ԫ�ظ�����һ��������NULL��Ϊ������
    find[0]=NULL;//����ĵ�һ��ָ���ÿգ����һ������ŶӶ�û�ҵ�����ôfind[0]Ϊ���򲻻�ı䣬��֮��ı䣬��˿����������жϱ�־


   while(psch_node!=NULL)
    {
        pteam_node=psch_node->tnext;
        while(pteam_node!=NULL)
        {

             if(pteam_node->prof_num>=prof_num)
             {
               find[i]=pteam_node;i++;
             }

             pteam_node=pteam_node->next;

         }

        psch_node=psch_node->next;
    }

    find[i]=NULL;//���һ��ָ���ÿգ����һ��û�ҵ����þ�find[0]=NULL;




    if(find[0]!=NULL)//���ٷ���һ�����������Ŷ�
    {   int i;
        printf("\n               ###�鵽����Ŷ���Ϣ###\n\n");
        char *tab[5]={"�Ŷ�����","������", "��ʦ����", "�о�������","����Ժϵ"};

        printf(" %-30s%-12s%-14s%-14s%-20s\n",tab[0],tab[1],tab[2],tab[3],tab[4]);
        printf("-------------------------------------------------------------------------------\n");

        for(i=0;find[i]!=NULL;i++)//ѭ�������������Ŷ�
       {
           printf(" %-30s%-12s%-14d%-14d%-20s\n",find[i]->team_name, find[i]->boss_name, find[i]->prof_num, find[i]->stu_num, find[i]->sch);
       }


        getch();
        char *plabel_name[] = {"�Ƿ������ѯ��",  " "," ��      �� "};
        bRet=Choice(plabel_name,3) ;
        switch(bRet)
        {
            case TRUE:   {
                           ClearScreenTotalInputArea();
                           goto Cmdinput1;
                         }


            case FALSE:  {
                            char *plabel_name[] = {"��ɲ�ѯ��",
                                                "  ",
                                                "ȷ��"
                                                };

                           ShowModule(plabel_name, 3);

                           ClearScreenTotalInputArea();

                             goto End;
                         }



        }






    }

    else //һ����ʦ���������û��������޵��ŶӶ�û�ҵ�
    {
        char *plabel_name[] = {"������ŶӲ�����!"," ","�Ƿ��������룿"," ��      �� "};
        bRet=Choice(plabel_name,4) ;

         switch(bRet)
        {
            case TRUE:   {
                           ClearScreenTotalInputArea();
                           goto Cmdinput1;
                         }


            case FALSE:  {
                            char *plabel_name[] = {"��ɲ�ѯ��",
                                                "  ",
                                                "ȷ��"
                                                };

                           ShowModule(plabel_name, 3);

                           ClearScreenTotalInputArea();

                             goto End;
                         }



        }
    }

End:
    /*���ع��*/
    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible=FALSE;
    SetConsoleCursorInfo(gh_std_out,&lpCur);


    return TRUE;

}


BOOL QuerySciprjInfoViaID(void)
{
    BOOL bRet;
    CONSOLE_CURSOR_INFO lpCur;
    char prj_num[15];
    SCH_NODE *psch_node;
    TEAM_NODE *pteam_node;
    SCIPRJ_NODE *psciprj_node;
    int i=0,num=0;


Cmdinput1:
    psch_node=gp_head;

    char *plabel_name[] = {"��������Ҫ��ѯ��Ϣ�Ŀ�����Ŀ�ı��",
                           "         ( ����15�ַ� ��            ",
                           "ȷ��"
                          };

                          ShowModule(plabel_name, 3);

                          ClearScreenTotalInputArea();

    /*��ʾ���*/
    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible=TRUE;
    SetConsoleCursorInfo(gh_std_out,&lpCur);


    printf("��Ŀ��ţ�  ");
    scanf("%s",prj_num);
    getchar();


    num=0;
    i=0;//�����������������ٳ�ʼ��Ϊ�㣬��Ȼ������ѯʱ��num����һ�β�ѯ�Ļ������������Ϳ��ܳ��ִ���


    while(psch_node!=NULL)//��һ���ж��ٸ���Ŀ�����������Ǹ���ţ���ʵ������Ŀ���Ψһ�����㷨����
    {
        pteam_node=psch_node->tnext;
        while(pteam_node!=NULL)
        {
            psciprj_node=pteam_node->snext;
            while(psciprj_node!=NULL)
             {

                 if(strcmp(psciprj_node->prj_num,prj_num)==0)
                 {
                    num++;
                 }
                 psciprj_node=psciprj_node->next;
             }
             pteam_node=pteam_node->next;

         }

        psch_node=psch_node->next;
    }
    psch_node=gp_head;//psch_node����ָ������ͷ

    SCIPRJ_NODE *find[num+1];//Ԫ�ظ�����һ��������NULL��Ϊ������
    find[0]=NULL;//����ĵ�һ��ָ���ÿգ����û�ҵ�����ôfind[0]Ϊ���򲻻�ı䣬��֮��ı䣬��˿����������жϱ�־



    while(psch_node!=NULL)//����������Ŀ��ź���������˵ı����ͬ�ı���ָ���¼��������ʵ���ڱ��Ψһ��û��Ҫ��ôд
    {
        pteam_node=psch_node->tnext;
        while(pteam_node!=NULL)
        {
            psciprj_node=pteam_node->snext;
            while(psciprj_node!=NULL)
             {

                 if(strcmp(psciprj_node->prj_num,prj_num)==0)
                 {
                    find[i]=psciprj_node;i++;
                 }
                 psciprj_node=psciprj_node->next;
             }
             pteam_node=pteam_node->next;

         }

        psch_node=psch_node->next;
    }
    find[i]=NULL;//���һ��ָ���ÿգ����һ��û�ҵ����þ�find[0]=NULL;




    if(find[0]!=NULL)//���ٷ���һ��������������Ŀ
    {   int i=0;
        printf("\n               ###�鵽�����Ŀ��Ϣ###\n\n");
        char *tab[6]={"��Ŀ���","��Ŀ���", "��ʼʱ��","��Ŀ����(��Ԫ)","������","�����Ŷ�"};

        printf(" %-20s%-10s%-16s%-16s%-16s%-30s\n",tab[0],tab[1],tab[2],tab[3],tab[4],tab[5]);
        printf("---------------------------------------------------------------------------------------------\n");

        for(i=0;find[i]!=NULL;i++)//ѭ��������з�����������Ŀ
       {
           printf(" %-20s%-10c%-16s%-16.2f%-16s%-30s\n",find[i]->prj_num, find[i]->type, find[i]->start_time, find[i]->prj_fund, find[i]->boss_name, find[i]->team);
       }


        getch();
        char *plabel_name[] = {"�Ƿ������ѯ��",  " ", " ��      �� "};
        bRet=Choice(plabel_name,3) ;
        switch(bRet)
        {
            case TRUE:   {
                           ClearScreenTotalInputArea();
                           goto Cmdinput1;
                         }


            case FALSE:  {
                            char *plabel_name[] = {"��ɲ�ѯ��",
                                                "  ",
                                                "ȷ��"
                                                };

                           ShowModule(plabel_name, 3);

                           ClearScreenTotalInputArea();

                             goto End;
                         }



        }






    }

    else //û�з��ָñ�ŵ���Ŀ
    {
        char *plabel_name[] = {"�ñ�Ų����ڣ�"," ","�Ƿ��������룿"," ��      �� "};
        bRet=Choice(plabel_name,4) ;

         switch(bRet)
        {
            case TRUE:   {
                           ClearScreenTotalInputArea();
                           goto Cmdinput1;
                         }


            case FALSE:  {
                            char *plabel_name[] = {"��ɲ�ѯ��",
                                                "  ",
                                                "ȷ��"
                                                };

                           ShowModule(plabel_name, 3);

                           ClearScreenTotalInputArea();

                             goto End;
                         }



        }
    }

End:
    /*���ع��*/
    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible=FALSE;
    SetConsoleCursorInfo(gh_std_out,&lpCur);


    return TRUE;
}


BOOL QuerySciprjInfoViaTeam(void)
{
BOOL bRet;
    CONSOLE_CURSOR_INFO lpCur;
    char team[30];
    SCH_NODE *psch_node;
    TEAM_NODE *pteam_node;
    SCIPRJ_NODE *psciprj_node;
    int i=0,num=0;


Cmdinput1:
    psch_node=gp_head;

    char *plabel_name[] = {"��������Ҫ��ѯ��Ϣ�Ŀ�����Ŀ�������Ŷ�",
                           "          ( ����30�ַ� ��            ",
                           "ȷ��"
                          };

                          ShowModule(plabel_name, 3);

                          ClearScreenTotalInputArea();

    /*��ʾ���*/
    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible=TRUE;
    SetConsoleCursorInfo(gh_std_out,&lpCur);


    printf("�����Ŷӣ�  ");
    scanf("%s",team);
    getchar();


    num=0;
    i=0;//�����������������ٳ�ʼ��Ϊ�㣬��Ȼ������ѯʱ��num����һ�β�ѯ�Ļ������������Ϳ��ܳ��ִ���


    while(psch_node!=NULL)//��һ���ж��ٸ���Ŀ�����������Ǹ���ţ���ʵ������Ŀ���Ψһ�����㷨����
    {
        pteam_node=psch_node->tnext;
        while(pteam_node!=NULL)
        {
            psciprj_node=pteam_node->snext;
            while(psciprj_node!=NULL)
             {

                 if(strcmp(psciprj_node->team,team)==0)
                 {
                    num++;
                 }
                 psciprj_node=psciprj_node->next;
             }
             pteam_node=pteam_node->next;

         }

        psch_node=psch_node->next;
    }
    psch_node=gp_head;//psch_node����ָ������ͷ

    SCIPRJ_NODE *find[num+1];//Ԫ�ظ�����һ��������NULL��Ϊ������
    find[0]=NULL;//����ĵ�һ��ָ���ÿգ����û�ҵ�����ôfind[0]Ϊ���򲻻�ı䣬��֮��ı䣬��˿����������жϱ�־



    while(psch_node!=NULL)//����������Ŀ��ź���������˵ı����ͬ�ı���ָ���¼��������ʵ���ڱ��Ψһ��û��Ҫ��ôд
    {
        pteam_node=psch_node->tnext;
        while(pteam_node!=NULL)
        {
            psciprj_node=pteam_node->snext;
            while(psciprj_node!=NULL)
             {

                 if(strcmp(psciprj_node->team,team)==0)
                 {
                    find[i]=psciprj_node;i++;
                 }
                 psciprj_node=psciprj_node->next;
             }
             pteam_node=pteam_node->next;

         }

        psch_node=psch_node->next;
    }
    find[i]=NULL;//���һ��ָ���ÿգ����һ��û�ҵ����þ�find[0]=NULL;




    if(find[0]!=NULL)//���ٷ���һ��������Ϊ�������������Ժϵ
    {   int i=0;
        printf("\n               ###�鵽�����Ŀ��Ϣ###\n\n");
        char *tab[6]={"��Ŀ���","��Ŀ���", "��ʼʱ��","��Ŀ����(��Ԫ)","������","�����Ŷ�"};

        printf(" %-20s%-10s%-16s%-16s%-16s%-30s\n",tab[0],tab[1],tab[2],tab[3],tab[4],tab[5]);
        printf("---------------------------------------------------------------------------------------------\n");

        for(i=0;find[i]!=NULL;i++)//ѭ��������и�����Ϊ��������˵�Ժϵ�����Ϣ
       {
           printf(" %-20s%-10c%-16s%-16.2f%-16s%-30s\n",find[i]->prj_num, find[i]->type, find[i]->start_time, find[i]->prj_fund, find[i]->boss_name, find[i]->team);
       }


        getch();
        char *plabel_name[] = {"�Ƿ������ѯ��",  " ", " ��      �� "};
        bRet=Choice(plabel_name,3) ;
        switch(bRet)
        {
            case TRUE:   {
                           ClearScreenTotalInputArea();
                           goto Cmdinput1;
                         }


            case FALSE:  {
                            char *plabel_name[] = {"��ɲ�ѯ��",
                                                "  ",
                                                "ȷ��"
                                                };

                           ShowModule(plabel_name, 3);

                           ClearScreenTotalInputArea();

                             goto End;
                         }



        }






    }

    else //һ��������Ϊ���˵���Ϣ��û�ҵ�
    {
        char *plabel_name[] = {"�������ŶӲ����ڣ�"," ","�Ƿ��������룿"," ��      �� "};
        bRet=Choice(plabel_name,4) ;

         switch(bRet)
        {
            case TRUE:   {
                           ClearScreenTotalInputArea();
                           goto Cmdinput1;
                         }


            case FALSE:  {
                            char *plabel_name[] = {"��ɲ�ѯ��",
                                                "  ",
                                                "ȷ��"
                                                };

                           ShowModule(plabel_name, 3);

                           ClearScreenTotalInputArea();

                             goto End;
                         }



        }
    }

End:
    /*���ع��*/
    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible=FALSE;
    SetConsoleCursorInfo(gh_std_out,&lpCur);


    return TRUE;
}


/**ͳ�Ƹ�Ժϵ��ʦ�������о������������о������ʦ�������ȣ����� 2 λС������
��ѧ����ʦ ������ֵ������������ͳ�ƽ��*/
BOOL StatResearcherNumInfo(void)
{

    CONSOLE_CURSOR_INFO lpCur;

    SCH_NODE *psch_node=NULL;
    TEAM_NODE *pteam_node=NULL;
    int i=0,j=0,sch_num=0;
    int temp_prof_num=0,temp_studt_num=0;
    double temp_rate=0;
    char *temp_sch_name=NULL;




     /*��ʾ���*/
    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible=TRUE;
    SetConsoleCursorInfo(gh_std_out,&lpCur);

    psch_node=gp_head;
    while(psch_node!=NULL)//ͳ��Ժϵ����
    {
        sch_num++;
        psch_node=psch_node->next;
    }


    int total_prof_num[sch_num],total_studt_num[sch_num];//�������鴢���Ժϵ������Ա����
    double rate[sch_num];//���������Ժϵ�� �о���  ��ʦ  ������
    char *sch_name[sch_num];//��������Ժϵ��


    for(i=0;i<sch_num;i++)//������Ԫ�س�ʼ��Ϊ0
    {
        total_prof_num[i]=0;
        total_studt_num[i]=0;
        rate[i]=0;
        sch_name[i]=NULL;
    }


    i=0;
    psch_node=gp_head;//��Ժϵ�Ľ�ʦ���о�������ͳ��
    while(psch_node!=NULL)
    {
        sch_name[i]=psch_node->sch_name;
        pteam_node=psch_node->tnext;
        while(pteam_node!=NULL)
        {
            total_prof_num[i] += pteam_node->prof_num;
            total_studt_num[i] += pteam_node->stu_num;

            pteam_node=pteam_node->next;

        }

        psch_node=psch_node->next;
        i++;
    }



    for(i=0;i<sch_num;i++) //�����о�����ʦ�ı�ֵ
    {
        if(total_prof_num[i]!=0)
          rate[i]=(1.0 * total_studt_num[i]) / (1.0 * total_prof_num[i]);

        else
          rate[i]=0;
    }

    for(i=0;i<sch_num;i++)//��ѧ����ʦ ������ֵ��������
    {
        for(j=0;j<(sch_num-i-1);j++)
        {
            if(rate[j]<rate[j+1])
            {
                temp_rate=rate[j]; rate[j]=rate[j+1]; rate[j+1]=temp_rate;

                temp_prof_num=total_prof_num[j];total_prof_num[j]=total_prof_num[j+1];total_prof_num[j+1]=temp_prof_num;

                temp_studt_num=total_studt_num[j];total_studt_num[j]=total_studt_num[j+1];total_studt_num[j+1]=temp_studt_num;

                temp_sch_name=sch_name[j];sch_name[j]=sch_name[j+1];sch_name[j+1]=temp_sch_name;

            }
        }
    }


    /*�����Ժϵ��ʦ���о������������ֵ*/
    printf("\n               ###��Ժϵ��ʦ���о������������ֵ###\n\n");
        char *tab[4]={ "Ժϵ","�о�������","��ʦ����", "�о���/��ʦ"};

         printf("���    %-24s%-16s%-12s%-15s\n", tab[0],tab[1],tab[2],tab[3]);
         printf("------------------------------------------------------------------\n");
        for(i=0;i<sch_num;i++)
        {
            printf("%-8d%-24s%-16d%-12d%-15.2f\n",i+1,sch_name[i],total_studt_num[i], total_prof_num[i], rate[i]);

        }

        printf("\n\n�����������...\n");

        getch();

        char *plabel_name[] = {"ͳ�������ɣ�",
                                    "  ",
                                    "ȷ��"
                                                };

                           ShowModule(plabel_name, 3);

                           ClearScreenTotalInputArea();

         /*���ع��*/
    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible=FALSE;
    SetConsoleCursorInfo(gh_std_out,&lpCur);



        return TRUE;






}


BOOL StatSciprjNumInfo(void)
{
    CONSOLE_CURSOR_INFO lpCur;

    SCH_NODE *psch_node=NULL;
    TEAM_NODE *pteam_node=NULL;
    SCIPRJ_NODE *psciprj_node=NULL;
    int i=0,j=0,sch_num=0;
    char time[10];

    typedef struct statsciprjnum//��������ͳ�Ƶ���Ϣ�Ľṹ
    {
        char sch_name[20];
        int sum_prjnum;
        int num973;
        int num863;
        double sum_fund;
    } STAT_SCIPRJ_NUM;

    STAT_SCIPRJ_NUM temp;


     char *plabel_name[] = {"��������Ҫͳ�ƵĿ�����Ŀ��Ϣ�����!",
                                    "  ",
                                    "ȷ��"
                                                };

                           ShowModule(plabel_name, 3);

                           ClearScreenTotalInputArea();


    /*��ʾ���*/
     GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible=TRUE;
    SetConsoleCursorInfo(gh_std_out,&lpCur);
Input1:
    printf("�������(��ʽ:2017)��");
    scanf("%s",time);
    getchar();

    if(!JudgeYearRight(time))//�����ݸ�ʽ����
    {
        char *plabel_name[] = {"��ʽ��������������",
                               "     (��2017)       ",
                                    "ȷ��"
                                                };

                           ShowModule(plabel_name, 3);

                           ClearScreenTotalInputArea();

                           goto Input1;


    }




    psch_node=gp_head;


   while(psch_node!=NULL)//ͳ��Ժϵ����
    {
        sch_num++;
        psch_node=psch_node->next;
    }



    STAT_SCIPRJ_NUM stat_sciprj_num[sch_num];//�����ṹ���鴢���Ժϵ������Ŀ�����Ϣ


    for(i=0;i<sch_num;i++)//������Ԫ�س�ʼ��Ϊ0
    {
        stat_sciprj_num[i].sum_prjnum=0;
        stat_sciprj_num[i].num973=0;
        stat_sciprj_num[i].num863=0;
        stat_sciprj_num[i].sum_fund=0;
    }


    i=0;
    psch_node=gp_head;
   while(psch_node!=NULL)//ͳ��ĳ��ȸ�Ժϵ������Ŀ����973 ��Ŀ����863 ��Ŀ�����������ܾ���
    {

     strcpy(stat_sciprj_num[i].sch_name , psch_node->sch_name);//����Ժϵ��

      pteam_node=psch_node->tnext;
      while(pteam_node!=NULL)
      {

          psciprj_node=pteam_node->snext;
          while(psciprj_node!=NULL)
          {
              if(JudgeYearEqual(psciprj_node->start_time , time) == TRUE)//�����Ŀ����ʼʱ���е���ݵ�������������
              {


                  stat_sciprj_num[i].sum_prjnum += 1;  //��ʼʱ�������Ϊtime�ĸ�Ժϵ��Ŀ��������1
                  stat_sciprj_num[i].sum_fund += psciprj_node->prj_fund;//ͳ�Ƹ�Ժϵ�ܵĿ��о���

                  if(psciprj_node->type == '1')
                    stat_sciprj_num[i].num973 += 1;//ͳ��973��Ŀ

                  if(psciprj_node->type == '3')
                    stat_sciprj_num[i].num863 += 1;//ͳ��863��Ŀ


              }


            psciprj_node=psciprj_node->next;
          }

          pteam_node=pteam_node->next;
      }

     psch_node=psch_node->next;
     i++; //ͳ����һ��Ժϵ

    }



    for(i=0;i<sch_num;i++)//��������Ŀ����������
    {
        for(j=0;j<(sch_num-i-1);j++)
        {
            if( (stat_sciprj_num[j].sum_prjnum) < (stat_sciprj_num[j+1].sum_prjnum) )
            {
                temp=stat_sciprj_num[j]; stat_sciprj_num[j]=stat_sciprj_num[j+1];stat_sciprj_num[j+1]=temp;
            }
        }
    }


    /*�����������Ŀ������������ĳ��ȸ�Ժϵ������Ŀ����973 ��Ŀ����863 ��Ŀ�����������ܾ���*/
         printf("\n               ###%s���Ժϵ������Ŀ����ͳ��###\n\n",time);
         char *tab[5]={ "Ժϵ","������Ŀ��","973��Ŀ��", "863��Ŀ��","�����ܾ���"};

         printf("���    %-24s%-14s%-13s%-13s%-14s\n", tab[0],tab[1],tab[2],tab[3],tab[4]);
         printf("--------------------------------------------------------------------------------\n");
        for(i=0;i<sch_num;i++)
        {
          printf("%-8d%-24s%-14d%-13d%-13d%-14.2f\n",i+1,stat_sciprj_num[i].sch_name,stat_sciprj_num[i].sum_prjnum, stat_sciprj_num[i].num973, stat_sciprj_num[i].num863,stat_sciprj_num[i].sum_fund);

        }


        printf("\n\n�����������...\n");

        getch();

        char *Anotherplabel_name[] = {"ͳ�������ɣ�",
                                    "  ",
                                    "ȷ��"
                                                };

                           ShowModule(Anotherplabel_name, 3);

                           ClearScreenTotalInputArea();

         /*���ع��*/
    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible=FALSE;
    SetConsoleCursorInfo(gh_std_out,&lpCur);



        return TRUE;


}
BOOL JudgeYearEqual(char *s , char *t)//�ж������ַ�����ǰ4���ַ��Ƿ�ȫ�ȣ������ж�һ�����ڣ���20170901���Ƿ�����һ����ݣ�2017��
{

    if(s[0]==t[0])
    {
        if(s[1]==t[1])
        {
            if(s[2]==t[2])
            {
                if(s[3]==t[3])
                    return TRUE;
            }
        }
    }


    return FALSE;
}

BOOL JudgeYearRight(char *s)//�ж�������ַ����Ƿ����� ��2017��  �Ƿ���TRUE  ���򷵻�FALSE
{
    if((s[0]>='0') && (s[0]<='9') )
    {
        if((s[1]>='0') && (s[1]<='9') )
        {
            if((s[2]>='0') && (s[2]<='9') )
            {
                if((s[3]>='0') && (s[3]<='9') )
                    return TRUE;
            }
        }

    }

    return FALSE;

}

/*ͳ�����������Ϊ������Ȼ��ѧ����Ŀ�����Ŀ������ 10 �������Ŷӣ�����Ŀ����������
����������Ŷ����ƣ����Ϊ������Ȼ��ѧ����Ŀ�����Ŀ�����Լ���Ŀ��������*/
BOOL StatNatureSciTop10(void)
{
    CONSOLE_CURSOR_INFO lpCur;

    SCH_NODE *psch_node=NULL;
    TEAM_NODE *pteam_node=NULL;
    SCIPRJ_NODE *psciprj_node=NULL;
    int i=0,j=0,team_num=0,num=0;


    typedef struct statnaturescinum//��������ͳ����Ϣ�Ľṹ
    {
        char sch[20];
        char team_name[30];
        int  nat_scinum;
        double sum_fund;
    } STAT_NATURE_SCI_NUM;

    STAT_NATURE_SCI_NUM temp;




    /*��ʾ���*/
     GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible=TRUE;
    SetConsoleCursorInfo(gh_std_out,&lpCur);



    psch_node=gp_head;


   while(psch_node!=NULL)//ͳ�Ŷ�ϵ����
    {
        pteam_node=psch_node->tnext;
        while(pteam_node!=NULL)
        {
            team_num++;
            pteam_node=pteam_node->next;
        }
        psch_node=psch_node->next;
    }



    STAT_NATURE_SCI_NUM stat_nature_sci_num[team_num];//�����ṹ���鴢����Ŷӿ�����Ŀ�����Ϣ


    for(i=0;i<team_num;i++)//������Ԫ�س�ʼ��Ϊ0
    {
        stat_nature_sci_num[i].nat_scinum=0;

        stat_nature_sci_num[i].sum_fund=0;
    }


    i=0;
    psch_node=gp_head;
   while(psch_node!=NULL)//ͳ�ƿ����Ŷ����ƣ����Ϊ������Ȼ��ѧ����Ŀ�����Ŀ�����Լ���Ŀ��������
    {

     pteam_node=psch_node->tnext;
      while(pteam_node!=NULL)
      {

          strcpy(stat_nature_sci_num[i].sch , psch_node->sch_name);//����Ժϵ��
          strcpy(stat_nature_sci_num[i].team_name , pteam_node->team_name);//�����Ŷ���

          psciprj_node=pteam_node->snext;
          while(psciprj_node!=NULL)
          {



                  if(psciprj_node->type == '2')
                    {

                     stat_nature_sci_num[i].nat_scinum += 1;//ͳ�ƹ�����Ȼ�������Ŀ��
                     stat_nature_sci_num[i].sum_fund += psciprj_node->prj_fund;//ͳ�Ƹ��Ŷ���Ŀ���Ϊ������Ȼ������ܵĿ��о���

                    }

                  psciprj_node=psciprj_node->next;


          }

          pteam_node=pteam_node->next;
          i++; //ͳ����һ���Ŷ�
      }

     psch_node=psch_node->next;

    }



    for(i=0;i<team_num;i++)//�����Ϊ������Ȼ���������Ŀ����������
    {
        for(j=0;j<(team_num-i-1);j++)
        {
            if( (stat_nature_sci_num[j].nat_scinum) < (stat_nature_sci_num[j+1].nat_scinum) )
            {
                temp=stat_nature_sci_num[j]; stat_nature_sci_num[j]=stat_nature_sci_num[j+1];stat_nature_sci_num[j+1]=temp;
            }
        }
    }


    /*��������Ŷ����ƣ����Ϊ������Ȼ��ѧ����Ŀ�����Ŀ������Ŀ�����������Լ�����Ժϵ*/
         printf("\n               ###������Ȼ��ѧ����(NFSC)�Ŀ�����Ŀ�����top10###\n\n");
         char *tab[4]={ "�Ŷ�����","NSFC��Ŀ��", "��Ŀ��������","����Ժϵ"};

         printf("���    %-34s%-14s%-16s%-24s\n", tab[0],tab[1],tab[2],tab[3]);
         printf("--------------------------------------------------------------------------------------\n");


         if(team_num>=10)//�жϵ�ǰ�Ŷ������Ƿ񳬹�10�����û������  �ж����������
             num=10;

         else
             num=team_num;




        for(i=0;i<num;i++)//���ͳ�Ƶ���Ϣ
        {
          printf("%-8d%-34s%-14d%-16.2f%-24s\n",i+1,stat_nature_sci_num[i].team_name,stat_nature_sci_num[i].nat_scinum, stat_nature_sci_num[i].sum_fund, stat_nature_sci_num[i].sch);

        }


        printf("\n\n�����������...\n");

        getch();

        char *Anotherplabel_name[] = {"ͳ�������ɣ�",
                                    "  ",
                                    "ȷ��"
                                                };

                           ShowModule(Anotherplabel_name, 3);

                           ClearScreenTotalInputArea();

         /*���ع��*/
    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible=FALSE;
    SetConsoleCursorInfo(gh_std_out,&lpCur);



        return TRUE;
}



/*ͳ�ƿ�����Ŀ���ͽ�ʦ�����ı�ֵ��ߵ� 5 �������Ŷӣ�����ֵ��������λС����
��������� ��������Ŷ����ƣ���ʦ������������Ŀ������Ŀ���ͽ�ʦ������ֵ��*/
BOOL StatPrjProfRate(void)
{
    CONSOLE_CURSOR_INFO lpCur;

    SCH_NODE *psch_node=NULL;
    TEAM_NODE *pteam_node=NULL;
    SCIPRJ_NODE *psciprj_node=NULL;
    int i=0,j=0,team_num=0,num=0;


    typedef struct statprjandprofrate//��������ͳ����Ϣ�Ľṹ
    {
        char sch[20];
        char team_name[30];
        int  prof_num;
        int  sciprj_num;
        double rate;
    } STAT_PRJ_PROF_RATE;

    STAT_PRJ_PROF_RATE temp;




    /*��ʾ���*/
     GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible=TRUE;
    SetConsoleCursorInfo(gh_std_out,&lpCur);



    psch_node=gp_head;


   while(psch_node!=NULL)//ͳ�Ŷ�ϵ����
    {
        pteam_node=psch_node->tnext;
        while(pteam_node!=NULL)
        {
            team_num++;
            pteam_node=pteam_node->next;
        }
        psch_node=psch_node->next;
    }



    STAT_PRJ_PROF_RATE   stat_prj_prof_rate[team_num];//�����ṹ���鴢����Ŷӽ�ʦ�����Ϳ�����Ŀ�������Ϣ


    for(i=0;i<team_num;i++)//������Ԫ�س�ʼ��Ϊ0
    {
        stat_prj_prof_rate[i].prof_num=0;

        stat_prj_prof_rate[i].sciprj_num=0;

        stat_prj_prof_rate[i].rate=0;
    }


    i=0;
    psch_node=gp_head;
   while(psch_node!=NULL)//ͳ�ƿ����Ŷ����ƣ�����Ժϵ��������Ŀ�����Լ���ʦ����
    {

     pteam_node=psch_node->tnext;
      while(pteam_node!=NULL)
      {

          strcpy(stat_prj_prof_rate[i].sch , psch_node->sch_name);//����Ժϵ��
          strcpy(stat_prj_prof_rate[i].team_name , pteam_node->team_name);//�����Ŷ���

          psciprj_node=pteam_node->snext;
          while(psciprj_node!=NULL)//ͳ�ƿ�����Ŀ��
          {
                  stat_prj_prof_rate[i].sciprj_num += 1;
                  psciprj_node=psciprj_node->next;
          }

          stat_prj_prof_rate[i].prof_num= pteam_node->prof_num;//ͳ�ƽ�ʦ����
          stat_prj_prof_rate[i].rate=(1.0 * stat_prj_prof_rate[i].sciprj_num) / (1.0 * stat_prj_prof_rate[i].prof_num);//�������

          pteam_node=pteam_node->next;
          i++; //ͳ����һ���Ŷ�
      }

     psch_node=psch_node->next;

    }



    for(i=0;i<team_num;i++)//�����ʽ�������
    {
        for(j=0;j<(team_num-i-1);j++)
        {
            if( (stat_prj_prof_rate[j].rate) < (stat_prj_prof_rate[j+1].rate) )
            {
                temp=stat_prj_prof_rate[j]; stat_prj_prof_rate[j]=stat_prj_prof_rate[j+1];stat_prj_prof_rate[j+1]=temp;
            }
        }
    }


    /*��������Ŷ����ƣ�������Ŀ������ʦ���������ʣ��Լ�����Ժϵ*/
         printf("\n               ###������Ŀ���ͽ�ʦ�����ı�ֵ��ߵĿ����Ŷ�top5###\n\n");
         char *tab[5]={ "�Ŷ�����", "������Ŀ��","��ʦ����","��Ŀ��/��ʦ��","����Ժϵ"};

         printf("���    %-34s%-14s%-12s%-17s%-30s\n", tab[0],tab[1],tab[2],tab[3],tab[4]);
         printf("------------------------------------------------------------------------------------------------------\n");


         if(team_num>=5)//�жϵ�ǰ�Ŷ������Ƿ񳬹�5�����û�������ж����������
             num=5;

         else
             num=team_num;




        for(i=0;i<num;i++)//���ͳ�Ƶ���Ϣ
        {
          printf("%-8d%-34s%-14d%-12d%-17.2f%-30s\n",i+1,stat_prj_prof_rate[i].team_name,stat_prj_prof_rate[i].sciprj_num, stat_prj_prof_rate[i].prof_num, stat_prj_prof_rate[i].rate,stat_prj_prof_rate[i].sch);

        }


        printf("\n\n�����������...\n");

        getch();

        char *Anotherplabel_name[] = {"ͳ�������ɣ�",
                                    "  ",
                                    "ȷ��"
                                                };

                           ShowModule(Anotherplabel_name, 3);

                           ClearScreenTotalInputArea();

         /*���ع��*/
    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible=FALSE;
    SetConsoleCursorInfo(gh_std_out,&lpCur);



        return TRUE;
}


/*ͳ��һ���Ŷ��ܵĽ�ʦ�������п��о��ѣ������˾����о���
Ȼ������˾����о��ѽ����������*/
BOOL StatFundProfRate(void)
{
    CONSOLE_CURSOR_INFO lpCur;

    SCH_NODE *psch_node=NULL;
    TEAM_NODE *pteam_node=NULL;
    SCIPRJ_NODE *psciprj_node=NULL;
    int i=0,j=0,team_num=0;;


    typedef struct statfundandprofrate//��������ͳ����Ϣ�Ľṹ
    {
        char sch[20];
        char team_name[30];
        int  prof_num;
        double fund;
        double rate;
    } STAT_FUND_PROF_RATE;

    STAT_FUND_PROF_RATE temp;




    /*��ʾ���*/
     GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible=TRUE;
    SetConsoleCursorInfo(gh_std_out,&lpCur);



    psch_node=gp_head;


   while(psch_node!=NULL)//ͳ�Ŷ�ϵ����
    {
        pteam_node=psch_node->tnext;
        while(pteam_node!=NULL)
        {
            team_num++;
            pteam_node=pteam_node->next;
        }
        psch_node=psch_node->next;
    }



    STAT_FUND_PROF_RATE   stat_fund_prof_rate[team_num];//�����ṹ���鴢���ʦ�������ܿ��о��������Ϣ


    for(i=0;i<team_num;i++)//������Ԫ�س�ʼ��Ϊ0
    {
        stat_fund_prof_rate[i].prof_num=0;

        stat_fund_prof_rate[i].fund=0;

        stat_fund_prof_rate[i].rate=0;
    }


    i=0;
    psch_node=gp_head;
   while(psch_node!=NULL)//ͳ�ƿ����Ŷ����ƣ�����Ժϵ���ܵĿ��о��ѣ���ʦ�������Լ��������
    {

     pteam_node=psch_node->tnext;
      while(pteam_node!=NULL)
      {

          strcpy(stat_fund_prof_rate[i].sch , psch_node->sch_name);//����Ժϵ��
          strcpy(stat_fund_prof_rate[i].team_name , pteam_node->team_name);//�����Ŷ���

          psciprj_node=pteam_node->snext;
          while(psciprj_node!=NULL)//����ѭ����ͳ�������Ŷ��ܵĿ��о���
          {
                  stat_fund_prof_rate[i].fund += psciprj_node->prj_fund;
                  psciprj_node=psciprj_node->next;
          }

          stat_fund_prof_rate[i].prof_num= pteam_node->prof_num;//ͳ���ŶӵĽ�ʦ����
          stat_fund_prof_rate[i].rate=(1.0 * stat_fund_prof_rate[i].fund) / (1.0 * stat_fund_prof_rate[i].prof_num);

          pteam_node=pteam_node->next;
          i++; //ͳ����һ���Ŷ�
      }

     psch_node=psch_node->next;

    }



    for(i=0;i<team_num;i++)//���ܵľ��Ѻͽ�ʦ�����ı�ֵ��������
    {
        for(j=0;j<(team_num-i-1);j++)
        {
            if( (stat_fund_prof_rate[j].rate) < (stat_fund_prof_rate[j+1].rate) )
            {
                temp=stat_fund_prof_rate[j]; stat_fund_prof_rate[j]=stat_fund_prof_rate[j+1];stat_fund_prof_rate[j+1]=temp;
            }
        }
    }


    /*��������Ŷ����ƣ��ܵĿ��о��ѣ���ʦ�������������Լ�����Ժϵ*/
         printf("\n                                 ###�������Ŷ����а�###\n\n");
         char *tab[5]={ "�Ŷ�����", "�ܿ��о���","��ʦ����","�ܾ���/��ʦ��","����Ժϵ"};

         printf("���    %-34s%-14s%-12s%-17s%-30s\n", tab[0],tab[1],tab[2],tab[3],tab[4]);
         printf("------------------------------------------------------------------------------------------------------\n");




        for(i=0;i<team_num;i++)//���ͳ�Ƶ���Ϣ
        {
          printf("%-8d%-34s%-14.2f%-12d%-17.2f%-30s\n",i+1,stat_fund_prof_rate[i].team_name,stat_fund_prof_rate[i].fund, stat_fund_prof_rate[i].prof_num, stat_fund_prof_rate[i].rate,stat_fund_prof_rate[i].sch);

        }


        printf("\n\n�����������...\n");

        getch();

        char *Anotherplabel_name[] = {"ͳ�������ɣ�",
                                    "  ",
                                    "ȷ��"
                                                };

                           ShowModule(Anotherplabel_name, 3);

                           ClearScreenTotalInputArea();

         /*���ع��*/
    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible=FALSE;
    SetConsoleCursorInfo(gh_std_out,&lpCur);



        return TRUE;
}



BOOL Help(void)
{
    system(".\\help\\help.pdf");

    return TRUE;
}

BOOL QueryAll(void)
{
    CONSOLE_CURSOR_INFO lpCur;
    SCH_NODE *psch_node=NULL;
    TEAM_NODE *pteam_node=NULL;
    SCIPRJ_NODE *psciprj_node=NULL;
    int i=1;


    char *tab1[3]={"Ժϵ����","����������","��ϵ�绰"};
    char *tab2[5]={"�Ŷ�����","����������","��ʦ����","�о�������","����Ժϵ"};
    char *tab3[6]={"��Ŀ���","��Ŀ���","��ʼʱ��","��Ŀ����(��Ԫ)","������","�����Ŷ�"};

     /*��ʾ���*/
    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible=TRUE;
    SetConsoleCursorInfo(gh_std_out,&lpCur);

    printf("��Ϣ��¼��ʱ���˳�������\n��¼��������...\n\n\n\n\n");




    printf("                    ###Ժϵ������Ϣ��###\n\n");//��ı���
    printf("���    %-24s%-16s%-19s\n",tab1[0],tab1[1],tab1[2]);//�����ͷ
    printf("-------------------------------------------------------------\n");

    psch_node=gp_head;
    while(psch_node!=NULL)//ѭ�����������Ϣ
    {
        printf("%-8d%-24s%-16s%-19s\n",i,psch_node->sch_name , psch_node->boss_name , psch_node->tel);
        psch_node=psch_node->next;
        i++;
    }




    printf("\n\n\n\n\n\n                         ###�����Ŷӻ�����Ϣ��###\n\n");//��������Ŷ���Ϣ�ı����
    printf("���    %-34s%-16s%-12s%-14s%-24s\n",tab2[0],tab2[1],tab2[2],tab2[3],tab2[4]);//�����ͷ
    printf("-----------------------------------------------------------------------------------------------\n");

    psch_node=gp_head;
    i=1;
    while(psch_node!=NULL)//ѭ����������Ŷӻ�����Ϣ
    {
        pteam_node=psch_node->tnext;
        while(pteam_node!=NULL)
        {
            printf("%-8d%-34s%-16s%-12d%-14d%-24s\n",i,pteam_node->team_name,pteam_node->boss_name,pteam_node->prof_num,pteam_node->stu_num,pteam_node->sch);
            pteam_node=pteam_node->next;
            i++;
        }

        psch_node=psch_node->next;
    }


    printf("\n\n\n\n\n\n                                  ###�����Ŷӻ�����Ϣ��###\n\n");//���������Ŀ������Ϣ�ı����
    printf("���    %-19s%-12s%-12s%-18s%-16s%-24s\n",tab3[0],tab3[1],tab3[2],tab3[3],tab3[4],tab3[5]);//�����ͷ
    printf("-----------------------------------------------------------------------------------------------------\n");

    psch_node=gp_head;
    i=1;
     while(psch_node!=NULL)//ѭ����������Ŷӻ�����Ϣ
    {
        pteam_node=psch_node->tnext;
        while(pteam_node!=NULL)
        {
            psciprj_node=pteam_node->snext;
            while(psciprj_node!=NULL)
            {
                printf("%-8d%-19s%-12c%-12s%-18.2f%-16s%-24s\n",i,psciprj_node->prj_num,psciprj_node->type,psciprj_node->start_time,psciprj_node->prj_fund,psciprj_node->boss_name,psciprj_node->team);
                psciprj_node=psciprj_node->next;
                i++;
            }
            pteam_node=pteam_node->next;
        }

        psch_node=psch_node->next;
    }


    printf("\n������Ϣ�����ɣ������������...");

    getch();


    ClearScreenTotalInputArea();//����

         /*���ع��*/
    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible=FALSE;
    SetConsoleCursorInfo(gh_std_out,&lpCur);





    return TRUE;




}



