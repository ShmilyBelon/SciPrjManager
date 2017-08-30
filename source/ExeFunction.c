#include"ExternInfoList.h"



/**以下为自己新加的函数*/
BOOL SchInfoInput(void)
{
    CONSOLE_CURSOR_INFO lpCur;  //存储光标信息

    SCH_NODE *pSchNode=gp_head,*pSeekReturn;
    char cmd;
    ClearScreenTotalInputArea();  //清屏


    for(;;)
     {


                pSchNode = (SCH_NODE*)malloc(sizeof(SCH_NODE));
                pSchNode->next = NULL; //指针置空，此步骤必须，不能悬挂指针
                pSchNode->tnext=NULL;  //指针置空，此步骤必须，不能悬挂指针
                pSchNode->next=gp_head;
                gp_head  = pSchNode;

                printf("##请按以下格式要求输入数据##\n1,数据间用空格隔开\n2,同一数据项中无空格 \n3,数据必须完整输入不许空项\n4，院系名唯一不许重复！\n\n");
                printf("格式：\n       院系名称                负责人                联系电话\n");
                scanf("%s %s %s",gp_head->sch_name,gp_head->boss_name,gp_head->tel);
                getchar();  //吞回车

                pSeekReturn = SeekSchNode(pSchNode->next,gp_head->sch_name);  //查重,并返回信息重复的先前的结点


                if(pSeekReturn==NULL) //如果没有重复

                     goto Cmdinput2;

                else
               {
                     SchInfoDel( &gp_head, gp_head->sch_name);  //因为刚刚录入的这组数据院系名字重复了，我们规定院系名称不能重复，因此删除刚刚创建的一个结点
                     printf("\n此院系的信息已经存在\n请重新输入新的院系信息\n或在修改功能中修改此院系信息\n\n");
                     printf("是否重新输入?  是(Y),否(N)\n\n");


                     goto Cmdinput3;// 重复后的再次输入和，输入一个完成后的继续输入在功能上很大程度上相似

                }








Cmdinput2:

             printf("\n\n是否继续输入数据？  是(Y),否(N) ");

Cmdinput3:
             printf("\n您选择：  ");


             scanf("%1s",&cmd);
             getchar();  //吞回车
             if((cmd=='Y') || (cmd=='y'))
             {
                ClearScreenTotalInputArea();
                continue;  //从此函数最上面的for循环中的第一个语句开始执行
             }

             else if((cmd=='N') || (cmd=='n'))
             {

                 char *plabel_name[] = {"除重复信息外，正常信息已经读入",
                           "可在文件菜单中选择保存到本地文件",
                           "确认"
                          };

                 ShowModule(plabel_name, 3);

                 ClearScreenTotalInputArea();


                 break; //跳出此函数最上面的那个大的for循环 执行此函数最下面的隐藏光标
             }
             else
                {
                  char *plabel_name[] = {"命令输入错误!",
                           "请重新输入！",
                           "确认"
                          };

                 ShowModule(plabel_name, 3);
                 ClearScreenTotalInputArea();

                 goto Cmdinput2;

                }



        }  //最上面的for循环结束点
        /*隐藏光标*/
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


    GetConsoleScreenBufferInfo(gh_std_out,&bInfo);  //取屏幕缓冲区信息
    size = bInfo.dwSize.X * (bInfo.dwSize.Y-1);   //计算屏幕缓冲区除了第一行字符单元数

    /*将屏幕缓冲区除了第一行所有单元的字符属性设置为当前屏幕缓冲区字符属性*/

    FillConsoleOutputAttribute(gh_std_out, bInfo.wAttributes, size, home, &ul);


    /*将屏幕缓冲区除了第一行所有单元填充为空格符*/
    FillConsoleOutputCharacter(gh_std_out, ' ', size, home, &ul);
    SetConsoleCursorPosition(gh_std_out,home);


    return;

}

BOOL SchInfoMod(void)
{
    char sch_name[20] , cmd;
    SCH_NODE *psch_node_temp;



Cmdinput4:

    ClearScreenTotalInputArea();  //清屏

    printf("您要修改哪个院系的院系信息？\n");
    printf("(输入院系名称，少于20字符,中间无空格)\n\n");
    printf("  ：    ");

    scanf("%s",sch_name);
    getchar();

    psch_node_temp = SeekSchNode(gp_head,sch_name);

    if(psch_node_temp != NULL)
    {
        printf("\n发现需要修改信息的院系！\n");


        for(;;)
        {

             printf("请重新输入该院系的新信息！\n\n");
             printf("\n\n  请按以下格式要求输入数据：\n1,数据间用空格隔开\n2,同一数据项中无空格 \n3,数据必须完整输入不许空项\n\n");

             char *tab[3]={"院系名称","负责人", "联系电话"};

             printf(" %-20s%-12s%-15s\n",tab[0],tab[1],tab[2]);
             printf("------------------------------------------------------------\n");

             scanf("%s %s %s",psch_node_temp->sch_name,psch_node_temp->boss_name,psch_node_temp->tel);
             getchar();  //吞回车

Cmdinput3:

             printf("\n\n是否完成修改？  完成修改(Y),重修修改(N) ");
             printf("\n您选择：  ");


             scanf("%1s",&cmd);
             getchar();  //吞回车
             if((cmd=='N') || (cmd=='n'))
             {
                ClearScreenTotalInputArea();
                continue;
             }

             else if((cmd=='Y') || (cmd=='y'))
             {

                 char *plabel_name[] = {"新的信息已经读入",
                           "可在文件菜单中选择保存到本地文件",
                           "确认"
                          };

                 ShowModule(plabel_name, 3);

                 ClearScreenTotalInputArea();


                 break;
             }
             else
                {
                  char *plabel_name[] = {"命令输入错误!",
                           "请重新输入！",
                           "确认"
                          };

                 ShowModule(plabel_name, 3);
                 ClearScreenTotalInputArea();

                 goto Cmdinput3;

                }

    }

 Cmdinput6:

 printf("是否继续进行院系相关信息修改？\n");
 printf("    是(Y),否(N)\n");
 printf("您选择：  ");

 scanf("%1s",&cmd);
 getchar();
 switch(cmd)
 {
    case 'Y':

    case 'y': goto Cmdinput4;

    case 'n':

    case 'N':
    {
        char *plabel_name[] = {"信息修改完成",
                            "新的信息已经读入",
                           "可在文件菜单中选择保存到本地文件",
                           "确认"
                          };
        ShowModule(plabel_name, 4);
        ClearScreenTotalInputArea();



                 /*隐藏光标*/
        GetConsoleCursorInfo(gh_std_out,&lpCur);
        lpCur.bVisible=FALSE;
        SetConsoleCursorInfo(gh_std_out,&lpCur);

        break;
    }

    default :
    {
        char *plabel_name[] = {"命令输入错误!",
                           "请重新输入！",
                           "确认"
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

         printf("\n您输入的院系不存在! 是否重新输入？ ");
         printf("\n 是(Y),否(N)\n您选择：  ");

         scanf("%1s",&cmd);
         getchar();

         if((cmd=='Y') || (cmd=='y'))
          {
               goto Cmdinput4;
          }


          else  if((cmd=='N') || (cmd=='n'))
              {


                char *plabel_name[] = {"修改操作结束",
                                  "仅最后一组数据修改失败！",
                                  "(因为所查找的院系不存在)",
                                  "确认"
                                   };
                ShowModule(plabel_name, 4);
                ClearScreenTotalInputArea();

                  /*隐藏光标*/
             GetConsoleCursorInfo(gh_std_out,&lpCur);
             lpCur.bVisible=FALSE;
             SetConsoleCursorInfo(gh_std_out,&lpCur);

             return TRUE;
              }

          else
             {
               char *plabel_name[] = {"命令输入错误",
                                      "请重新输入！",
                                        "确认"
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
                   printf("\n\n你需要删除那个院系的信息？\n:    ");
                   scanf("%s",sch_name);
                   getchar();

                   if(SeekSchNode(gp_head,sch_name)!=NULL)
                   {
                        SchInfoDel(&gp_head,sch_name);
                        char *plabel_name[] = {"删除成功！",
                           "可在文件菜单中选择将修改保存到本地文件",
                           "确认"
                          };

                          ShowModule(plabel_name, 3);

                          ClearScreenTotalInputArea();

                    Cmdinput3:
                          printf("是否继续执行删除功能？  是(Y),  否(N)\n您选择：  ");
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
                                           char *plabel_name[] = {"删除功能执行完毕！",
                                            "可在文件菜单中选择将修改保存到本地文件",
                                               "确认"
                                                        };

                                           ShowModule(plabel_name, 3);

                                           ClearScreenTotalInputArea();

                                           return TRUE;
                                        }
                                default:

                                       {
                                           char *plabel_name[] = {"命令输入错误请重新输入！",
                                            "  ",
                                               "确认"
                                                        };

                                           ShowModule(plabel_name, 3);

                                           ClearScreenTotalInputArea();

                                           goto Cmdinput3;

                                       }



                                }





                    }

                    else
                    {
                         char *plabel_name[] = {"您所要删除的院系不存在!",
                           "  ",
                           "确认"
                          };

                          ShowModule(plabel_name, 3);
                          ClearScreenTotalInputArea();
                          goto Cmdinput3;


                    }


};


BOOL TeamInfoInput(void)
{
    CONSOLE_CURSOR_INFO lpCur;  //存储光标信息

    SCH_NODE *pSeekSchReturn;
    TEAM_NODE *pTeamNode=NULL, *pSeekTeamReturn;
    char cmd,sch_name[20],team_name[30];
    ClearScreenTotalInputArea();  //清屏



    for(;;)
     {

        Cmdinput1:

                printf("请输入：您要输入信息的科研团队所在院系(少于20个字符)！\n :    ");
                scanf("%s",sch_name);
                getchar();
                pSeekSchReturn = SeekSchNode(gp_head,sch_name);
                if(pSeekSchReturn==NULL)  //该院系不存在
                {
                    Cmdinput2:
                          printf("\n\n您输入的院系不存在，是否重新输入？  是(Y),  否(N)\n您选择：  ");
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
                                           char *plabel_name[] = {"信息录入功能执行完毕！",
                                            "可在文件菜单中选择将修改保存到本地文件",
                                               "确认"
                                                        };

                                           ShowModule(plabel_name, 3);

                                           ClearScreenTotalInputArea();

                                           return TRUE;
                                        }
                                default:

                                       {
                                           char *plabel_name[] = {"命令输入错误请重新输入！",
                                            "  ",
                                               "确认"
                                                        };

                                           ShowModule(plabel_name, 3);

                                           ClearScreenTotalInputArea();

                                           goto Cmdinput2;

                                       }

                             }
                }

                else //若所输入的院系存在
                {


                       printf("\n请输入需要录入信息的科研团队名(少于30字符):\n    ");
                       scanf("%s",team_name);
                       getchar();

                       pSeekTeamReturn=SeekTeamNode(pSeekSchReturn->tnext,team_name);
                       if( pSeekTeamReturn == NULL)//科研团队名不存在
                       {
                             /*先进后出的申请动态空间,然后进行必要的初始化*/
                              pTeamNode = (TEAM_NODE*)malloc(sizeof(TEAM_NODE));
                              pTeamNode->snext=NULL; //不能悬挂指针 ，这一步是必须的！！
                              pTeamNode->next=NULL;/*不能悬挂指针！！这一步是保险的！！因为在院系的链表创建时候应该已经把tnext置空了，
                              所以如果这个团队信息是该院系的第一个录入信息的团队，那么下一行代码相当于next置空。但是这一步有保险作用，很重要！！*/
                              pTeamNode->next = pSeekSchReturn->tnext;
                              pSeekSchReturn->tnext = pTeamNode;

                              strcpy(pTeamNode->sch,sch_name);//因为院系名已经确定了，就是sch_name
                              strcpy(pTeamNode->team_name,team_name);//因为团队名称这时候已经确定 就是team_name



                               printf("\n##请按以下格式要求输入数据##\n1,数据间用空格隔开\n2,同一数据项中无空格 \n3,数据必须完整输入不许空项\n\n");
                               printf("格式：\n       负责人          教师人数        研究生人数  \n");
                               scanf(" %s %d %d",pTeamNode->boss_name,&pTeamNode->prof_num,&pTeamNode->stu_num);
                               getchar();  //吞回车
                        }


                        else
                         {

                               printf("\n此科研团队的信息已经存在\n请重新输入新的团队信息\n或在修改功能中修改此团队信息\n\n");
                               printf("是否重新输入?  是(Y),否(N)\n\n");


                                goto Cmdinput4;// 重复后的再次输入和，输入一个完成后的继续输入在功能上很大程度上相似

                          }


                }












Cmdinput3:

             printf("\n\n是否继续输入数据？  是(Y),否(N) ");

Cmdinput4:
             printf("\n您选择：  ");


             scanf("%1s",&cmd);
             getchar();  //吞回车
             if((cmd=='Y') || (cmd=='y'))
             {
                ClearScreenTotalInputArea();
                continue;  //从此函数最上面的for循环中的第一个语句开始执行
             }

             else if((cmd=='N') || (cmd=='n'))
             {

                 char *plabel_name[] = {"除重复信息外，正常信息已经读入",
                           "可在文件菜单中选择保存到本地文件",
                           "确认"
                          };

                 ShowModule(plabel_name, 3);

                 ClearScreenTotalInputArea();


                 break; //跳出此函数最上面的那个大的for循环 执行此函数最下面的隐藏光标
             }
             else
                {
                  char *plabel_name[] = {"命令输入错误!",
                           "请重新输入！",
                           "确认"
                          };

                 ShowModule(plabel_name, 3);
                 ClearScreenTotalInputArea();

                 goto Cmdinput3;

                }



        }  //最上面的for循环结束点
        /*隐藏光标*/
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

    ClearScreenTotalInputArea();  //清屏

    printf("您要修改哪个院系的哪个团队的信息？\n");
    printf("(输入院系名称以及团队名称)\n(两个名称内部无空格)\n(两个名称之间用空格隔开)\n\n");
    printf("格式：   院系名称                科研团队名称\n");
    printf("    ：   ");

    scanf("%s %s",sch_name,team_name);
    getchar();

    if(  (  psch_node_temp = SeekSchNode(gp_head,sch_name)  ) != NULL );
         pteam_node_temp = SeekTeamNode(psch_node_temp->tnext, team_name );//这么做事因为，需要同时满足所查找的院系和科研团队同时存在

    if( (psch_node_temp!=NULL) && (pteam_node_temp!=NULL) )  //如果所查找的院系，和其内的科研同队同时存在
    {
        printf("\n发现需要修改的信息结点！\n");


        for(;;)
        {

             printf("请重修输入该科研团队的新信息！\n\n");
             printf("\n\n  请按以下格式要求输入数据：\n1,数据间用空格隔开\n2,同一数据项中无空格 \n3,数据必须完整输入不许空项\n\n");
             printf("格式：\n        团队名称\t负责人\t     教师人数\t    研究生人数\t\n");

             scanf("%s %s %d %d",pteam_node_temp->team_name, pteam_node_temp->boss_name, &pteam_node_temp->prof_num, &pteam_node_temp->stu_num);

             getchar();  //吞回车

Cmdinput3:

             printf("\n\n是否完成修改？  完成修改(Y),重新修改(N) ");
             printf("\n您选择：  ");


             scanf("%1s",&cmd);
             getchar();  //吞回车
             if((cmd=='N') || (cmd=='n'))
             {
                ClearScreenTotalInputArea();
                continue;
             }

             else if((cmd=='Y') || (cmd=='y'))
             {

                 char *plabel_name[] = {"新的信息已经读入",
                           "可在文件菜单中选择保存到本地文件",
                           "确认"
                          };

                 ShowModule(plabel_name, 3);

                 ClearScreenTotalInputArea();


                 break;
             }
             else
                {
                  char *plabel_name[] = {"命令输入错误!",
                           "请重新输入！",
                           "确认"
                          };

                 ShowModule(plabel_name, 3);
                 ClearScreenTotalInputArea();

                 goto Cmdinput3;

                }

    }//上面for语句的结束点

 Cmdinput6://for语句结束点之后，一轮修改完成，下面询问是否继续修改

 printf("是否继续进行科研团队相关信息修改？\n");
 printf("    是(Y),否(N)\n");
 printf("您选择：  ");

 scanf("%1s",&cmd);
 getchar();
 switch(cmd)
 {
    case 'Y':

    case 'y': goto Cmdinput4;

    case 'n':

    case 'N':
    {
        char *plabel_name[] = {"信息修改完成",
                            "新的信息已经读入",
                           "可在文件菜单中选择保存到本地文件",
                           "确认"
                          };
        ShowModule(plabel_name, 4);
        ClearScreenTotalInputArea();



                 /*隐藏光标*/
        GetConsoleCursorInfo(gh_std_out,&lpCur);
        lpCur.bVisible=FALSE;
        SetConsoleCursorInfo(gh_std_out,&lpCur);

        break; //退出switch语句 ，执行下面的return语句直接结束修改函数
    }

    default :
    {
        char *plabel_name[] = {"命令输入错误!",
                           "请重新输入！",
                           "确认"
                          };

                 ShowModule(plabel_name, 3);
                 ClearScreenTotalInputArea();
                 goto Cmdinput6;


    }


  }

  return TRUE;


}  //最上面的那个大的if语句的结束点


    else //如果没有发现所要找的团队 。与最上面的那个大的if对应
   {
 Cmdinput5:

         printf("\n您输入的科研团队不存在! 是否重新输入？ ");
         printf("\n 是(Y),否(N)\n您选择：  ");

         scanf("%1s",&cmd);
         getchar();

         if((cmd=='Y') || (cmd=='y'))
          {
               goto Cmdinput4;
          }


          else  if((cmd=='N') || (cmd=='n'))
              {


                char *plabel_name[] = {"修改操作结束",
                                  "仅最后一组数据修改失败！",
                                  "(因为所查找的团队不存在)",
                                  "确认"
                                   };
                ShowModule(plabel_name, 4);
                ClearScreenTotalInputArea();

                  /*隐藏光标*/
             GetConsoleCursorInfo(gh_std_out,&lpCur);
             lpCur.bVisible=FALSE;
             SetConsoleCursorInfo(gh_std_out,&lpCur);

             return TRUE;
              }

          else
             {
               char *plabel_name[] = {"命令输入错误",
                                      "请重新输入！",
                                        "确认"
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

    ClearScreenTotalInputArea();  //清屏

    printf("您要删除哪个院系的哪个团队的信息？\n");
    printf("(输入院系名称以及团队名称)\n(两个名称内部无空格)\n(两个名称之间用空格隔开)\n\n");
    printf("格式：  院系名称                科研团队名称\n");
    printf("    ：  ");

    scanf("%s %s",sch_name,team_name);
    getchar();

    if(  (  psch_node_temp = SeekSchNode(gp_head,sch_name)  ) != NULL )
         pteam_node_temp = SeekTeamNode(psch_node_temp->tnext, team_name );//这么做事因为，需要同时满足所查找的院系和科研团队同时存在

    if( (psch_node_temp!=NULL) && (pteam_node_temp!=NULL) )  //如果所查找的院系，和其内的科研同队同时存在
    {
        TeamInfoDel(&(psch_node_temp->tnext) , team_name ); //删除结点
        char *plabel_name[] = {"删除成功！",
                           "可在文件菜单中选择将修改保存到本地文件",
                           "确认"
                          };

                          ShowModule(plabel_name, 3);

                          ClearScreenTotalInputArea();

                    Cmdinput2:
                          printf("是否继续执行删除功能？  是(Y),  否(N)\n您选择：  ");
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
                                           char *plabel_name[] = {"删除功能执行完毕！",
                                            "可在文件菜单中选择将修改保存到本地文件",
                                               "确认"
                                                        };

                                           ShowModule(plabel_name, 3);

                                           ClearScreenTotalInputArea();

                                           return TRUE;
                                        }
                                default:

                                       {
                                           char *plabel_name[] = {"命令输入错误请重新输入！",
                                            "  ",
                                               "确认"
                                                        };

                                           ShowModule(plabel_name, 3);

                                           ClearScreenTotalInputArea();

                                           goto Cmdinput2;

                                       }



                                }





    }


    else //如果要删除的科研团队不存在
        {
                         char *plabel_name[] = {"您所要删除的该院系内的该团队不存在!",
                           "  ",
                           "确认"
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
    CONSOLE_CURSOR_INFO lpCur;  //存储光标信息

    SCH_NODE *pSeekSchReturn;
    TEAM_NODE  *pSeekTeamReturn;
    SCIPRJ_NODE *pSciprjNode=NULL,*pSeekSciprjReturn;
    char cmd,sch_name[20],team_name[30],prj_num[15];
    ClearScreenTotalInputArea();  //清屏



    for(;;)
     {

        Cmdinput1:

                printf("请输入：您要输入信息的科研项目所在院系以及团队!");
                printf("\n(输入院系名称以及团队名称)\n(两个名称内部无空格)\n(两个名称之间用空格隔开)\n\n");
                printf("格式：  院系名称                科研团队名\n");
                printf("    ：  ");

                scanf("%s %s",sch_name,team_name);
                getchar();

                if(  (  pSeekSchReturn = SeekSchNode(gp_head,sch_name)  ) != NULL )
                              pSeekTeamReturn = SeekTeamNode(pSeekSchReturn->tnext, team_name );//这么做事因为，需要同时满足所查找的院系和科研团队同时存在

                if( (pSeekSchReturn!=NULL) && (pSeekTeamReturn!=NULL) )  //如果所查找的院系，和其内的科研同队同时存在
                {
                     printf("\n请输入需要录入信息的科研项目编号(少于15字符):\n    ");
                       scanf("%s",prj_num);
                       getchar();

                       pSeekSciprjReturn=SeekSciprjNode(pSeekTeamReturn->snext,prj_num);
                       if( pSeekSciprjReturn == NULL)//如果该编号科研项目不存在
                       {
                             /*先进后出的申请动态空间,然后进行必要的初始化*/
                              pSciprjNode = (SCIPRJ_NODE*)malloc(sizeof(SCIPRJ_NODE));
                              pSciprjNode->next=NULL;/*不能悬挂指针！！*/
                              pSciprjNode->next = pSeekTeamReturn->snext;
                              pSeekTeamReturn->snext = pSciprjNode;

                              strcpy(pSciprjNode->team,team_name);//因为所属团队名已经确定了，就是team_name
                              strcpy(pSciprjNode->prj_num,prj_num);



                               printf("\n##请按以下格式要求输入数据##\n1,数据间用空格隔开\n2,同一数据项中无空格 \n3,数据必须完整输入不许空项\n\n");
                               printf("格式：\n       项目类别(1字符)  起始时间(如19491001)  项目经费(万元)  项目负责人\n       ");
                               scanf("%1s %s %f %s",&(pSciprjNode->type) , pSciprjNode->start_time, &(pSciprjNode->prj_fund), pSciprjNode->boss_name);
                               getchar();  //吞回车
                        }


                        else
                         {

                               printf("\n此科研项目的信息已经存在\n请重新输入新的项目信息\n或在修改功能中修改此信息\n\n");
                               printf("是否重新输入?  是(Y),否(N)\n\n");


                                goto Cmdinput4;// 重复后的再次输入和，输入一个完成后的继续输入在功能上很大程度上相似

                          }

                }


                else //若所输入的院系内的科研团队不存在
                {

                        Cmdinput2:
                          printf("\n\n您输入的院系内的团队不存在，是否重新输入？  是(Y),  否(N)\n您选择：  ");
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
                                           char *plabel_name[] = {"信息录入功能执行完毕！",
                                            "可在文件菜单中选择将修改保存到本地文件",
                                               "确认"
                                                        };

                                           ShowModule(plabel_name, 3);

                                           ClearScreenTotalInputArea();

                                           return TRUE;
                                        }
                                default:

                                       {
                                           char *plabel_name[] = {"命令输入错误请重新输入！",
                                            "  ",
                                               "确认"
                                                        };

                                           ShowModule(plabel_name, 3);

                                           ClearScreenTotalInputArea();

                                           goto Cmdinput2;

                                       }

                             }


                }



Cmdinput3:

             printf("\n\n是否继续输入数据？  是(Y),否(N) ");

Cmdinput4:
             printf("\n您选择：  ");


             scanf("%1s",&cmd);
             getchar();  //吞回车
             if((cmd=='Y') || (cmd=='y'))
             {
                ClearScreenTotalInputArea();
                continue;  //从此函数最上面的for循环中的第一个语句开始执行
             }

             else if((cmd=='N') || (cmd=='n'))
             {

                 char *plabel_name[] = {"除重复信息外，正常信息已经读入",
                           "可在文件菜单中选择保存到本地文件",
                           "确认"
                          };

                 ShowModule(plabel_name, 3);

                 ClearScreenTotalInputArea();


                 break; //跳出此函数最上面的那个大的for循环 执行此函数最下面的隐藏光标
             }
             else
                {
                  char *plabel_name[] = {"命令输入错误!",
                           "请重新输入！",
                           "确认"
                          };

                 ShowModule(plabel_name, 3);
                 ClearScreenTotalInputArea();

                 goto Cmdinput3;

                }



        }  //最上面的for循环结束点
        /*隐藏光标*/
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

    ClearScreenTotalInputArea();  //清屏

    printf("您要修改哪个院系的哪个团队的哪个项目的信息？\n");
    printf("(输入院系名称、团队名称、项目编号)\n(每个数据项内部无空格)\n(两个数据项之间用空格隔开)\n\n");
    printf("格式：院系名称                科研团队名                    项目编号\n");
    printf("    ：");

    scanf("%s %s %s",sch_name,team_name,prj_num);
    getchar();

    if(  (  pSeekSchReturn = SeekSchNode(gp_head,sch_name)  ) != NULL );
        {
             pSeekTeamReturn = SeekTeamNode(pSeekSchReturn->tnext, team_name );//这么做事因为，需要同时满足所查找的院系和科研团队同时存在
             if( pSeekTeamReturn != NULL )
                pSeekSciprjReturn = SeekSciprjNode(pSeekTeamReturn->snext,prj_num); //这么做是因为，需要需要同时满足所查找的院系和科研团队同时存在时候，再查找项目
        }

    if( (pSeekSchReturn!=NULL) && (pSeekTeamReturn!=NULL) && (pSeekSciprjReturn!=NULL) )  //如果所查找的院系，和其内的科研同队以及项目同时存在
    {
        printf("\n发现需要修改的信息结点！\n");


        for(;;)
        {

             printf("请重新输入该科研项目的新信息！\n\n");
             printf("\n\n  请按以下格式要求输入数据：\n1,数据间用空格隔开\n2,同一数据项中无空格 \n3,数据必须完整输入不许空项\n\n");
             printf("格式：\n       项目编号    项目类别    起始时间    项目经费(万元)    负责人\n       ");

             scanf("%s %1s %s %f %s",pSeekSciprjReturn->prj_num, &(pSeekSciprjReturn->type), pSeekSciprjReturn->start_time, &(pSeekSciprjReturn->prj_fund), pSeekSciprjReturn->boss_name);

             getchar();  //吞回车

Cmdinput3:

             printf("\n\n是否完成修改？  完成修改(Y),重新修改(N) ");
             printf("\n您选择：  ");


             scanf("%1s",&cmd);
             getchar();  //吞回车
             if((cmd=='N') || (cmd=='n'))
             {
                ClearScreenTotalInputArea();
                continue;
             }

             else if((cmd=='Y') || (cmd=='y'))
             {

                 char *plabel_name[] = {"新的信息已经读入",
                           "可在文件菜单中选择保存到本地文件",
                           "确认"
                          };

                 ShowModule(plabel_name, 3);

                 ClearScreenTotalInputArea();


                 break;
             }
             else
                {
                  char *plabel_name[] = {"命令输入错误!",
                           "请重新输入！",
                           "确认"
                          };

                 ShowModule(plabel_name, 3);
                 ClearScreenTotalInputArea();

                 goto Cmdinput3;

                }

    }//上面for语句的结束点

 Cmdinput6://for语句结束点之后，一轮修改完成，下面询问是否继续修改

 printf("是否继续进行科研项目相关信息修改？\n");
 printf("    是(Y),否(N)\n");
 printf("您选择：  ");

 scanf("%1s",&cmd);
 getchar();
 switch(cmd)
 {
    case 'Y':

    case 'y': goto Cmdinput4;

    case 'n':

    case 'N':
    {
        char *plabel_name[] = {"信息修改完成",
                            "新的信息已经读入",
                           "可在文件菜单中选择保存到本地文件",
                           "确认"
                          };
        ShowModule(plabel_name, 4);
        ClearScreenTotalInputArea();



                 /*隐藏光标*/
        GetConsoleCursorInfo(gh_std_out,&lpCur);
        lpCur.bVisible=FALSE;
        SetConsoleCursorInfo(gh_std_out,&lpCur);

        break; //退出switch语句 ，执行下面的return语句直接结束修改函数
    }

    default :
    {
        char *plabel_name[] = {"命令输入错误!",
                           "请重新输入！",
                           "确认"
                          };

                 ShowModule(plabel_name, 3);
                 ClearScreenTotalInputArea();
                 goto Cmdinput6;


    }


  }

  return TRUE;


}  //最上面的那个大的if语句的结束点


    else //如果没有发现所要找的团队 。与最上面的那个大的if对应
   {
 Cmdinput5:

         printf("\n您输入的科研项目不存在! 是否重新输入？ ");
         printf("\n 是(Y),否(N)\n您选择：  ");

         scanf("%1s",&cmd);
         getchar();

         if((cmd=='Y') || (cmd=='y'))
          {
               goto Cmdinput4;
          }


          else  if((cmd=='N') || (cmd=='n'))
              {


                char *plabel_name[] = {"修改操作结束",
                                  "仅最后一组数据修改失败！",
                                  "(因为所查找的项目不存在)",
                                  "确认"
                                   };
                ShowModule(plabel_name, 4);
                ClearScreenTotalInputArea();

                  /*隐藏光标*/
             GetConsoleCursorInfo(gh_std_out,&lpCur);
             lpCur.bVisible=FALSE;
             SetConsoleCursorInfo(gh_std_out,&lpCur);

             return TRUE;
              }

          else
             {
               char *plabel_name[] = {"命令输入错误",
                                      "请重新输入！",
                                        "确认"
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

    ClearScreenTotalInputArea();  //清屏

    printf("您要删除哪个院系的哪个团队的哪个项目的信息？\n");
    printf("(输入院系名称、团队名称、项目编号)\n(每个数据项内部无空格)\n(两个数据项之间用空格隔开)\n\n");
    printf("格式：院系名称            科研团队名                    项目编号\n");
    printf("    ：");

    scanf("%s %s %s",sch_name,team_name,prj_num);

    getchar();

    if(  (  pSeekSchReturn = SeekSchNode(gp_head,sch_name)  ) != NULL )
        {
             pSeekTeamReturn = SeekTeamNode(pSeekSchReturn->tnext, team_name );//这么做事因为，需要同时满足所查找的院系和科研团队同时存在
             if( pSeekTeamReturn != NULL )
                pSeekSciprjReturn = SeekSciprjNode(pSeekTeamReturn->snext,prj_num); //这么做是因为，需要需要同时满足所查找的院系和科研团队同时存在时候，再查找项目
        }

    if( (pSeekSchReturn!=NULL) && (pSeekTeamReturn!=NULL) && (pSeekSciprjReturn!=NULL) )  //如果所查找的院系，和其内的科研同队以及项目同时存在
    {
        SciprjInfoDel(&(pSeekTeamReturn->snext) , prj_num ); //删除结点
        char *plabel_name[] = {"删除成功！",
                           "可在文件菜单中选择将修改保存到本地文件",
                           "确认"
                          };

                          ShowModule(plabel_name, 3);

                          ClearScreenTotalInputArea();

                    Cmdinput2:
                          printf("是否继续执行删除功能？  是(Y),  否(N)\n您选择：  ");
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
                                           char *plabel_name[] = {"删除功能执行完毕！",
                                            "可在文件菜单中选择将修改保存到本地文件",
                                               "确认"
                                                        };

                                           ShowModule(plabel_name, 3);

                                           ClearScreenTotalInputArea();

                                           return TRUE;
                                        }
                                default:

                                       {
                                           char *plabel_name[] = {"命令输入错误请重新输入！",
                                            "  ",
                                               "确认"
                                                        };

                                           ShowModule(plabel_name, 3);

                                           ClearScreenTotalInputArea();

                                           goto Cmdinput2;

                                       }



                                }

                          // break;



    }


    else //如果要删除的科研团队不存在
        {
                         char *plabel_name[] = {"您所要删除的该院系内的该团队的该项目不存在!",
                           "  ",
                           "确认"
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

void SpaceToUnderline(char*s) //C语言中create函数能创建的文件的文件名只能是标识符，因此把系统时间字符串中的冒号的空格变成下划线
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

 void AddBackslash(char*s) //在一个不可能连续出现2个或两个以上 \ 字符的字符串中，把出现的 \ 字符变成  "\\"
 {
     int i=0,j,len;
     for(i=0;s[i]!='\0';i++)
     {
         if(s[i]=='\\') // 如果s[i]是\ 。
         {
             len=strlen(s);
             for(j=len;j>i;j--)//for循环是把s[i]后面的所有字符向后平移一下，为了在s[i]后面加\腾出空间
             {
               s[j+1]=s[j];
             }
             s[i+1]='\\';
             i++;  //注意这时候s[i]之后的那个字符也是\了，因此i要自增1来跳过后加的\ 在其后再搜索\。

         }
         else
            continue;
     }
return;

}

void GetBackupFilename(char *dir )//得到包含路径的备份文件名

{
    int len;//字符串长度

    time_t t;//定义一个时间变量
    t=time(NULL);

    char *time;//定义一个字符串用来保存获取到的日期和时间
    time=ctime(&t);//赋值

    SpaceToUnderline(time);//C语言中create函数能创建的文件的文件名只能是标识符，因此把系统时间字符串中的冒号的空格变成下划线

/*把时间字符串后面加上后缀名构成文件名，注意不能用strcat函数，因为时间字符串time在'\0'字符之前还有个看不见的换行符，直接接上会把".dat"接到换行符后面*/
      len=strlen(time);
      time[len-1]='.';
      time[len]='d';
      time[len+1]='a';
      time[len+2]='t';
      time[len+3]='\0';    //这是文件名构造完成了，这时time里面的字符串是带后缀名的文件名了，不仅仅是时间字符串




      char BackupDir[9]="\\backup\\";
      getcwd(dir,100);//获取当前工作地址,重点是！！！看下一行：
/*char *getcwd(char *buf, size_t size);  这是获取当前地址函数的原型，正常第二个参数应该是sizeof(dir),但是注意数组名是个指针常量并不完全同于指针变量，比如char s[10],*p=s **pp=&p; ,sizeof(s)等于10
而sizeof(p)和sizeof(pp)却等于4，因为一个指针变量占四个字节是固定的，因此char指针作为函数参数时候传递不了字符串所占的字节数。因此第二个参数只能是100（因为在BackupData函数中
声明的用于储存含地址的备份文件名的字符数组 为char filename[100] sizeof(filename)等于100*）而getcwd(dir,sizeof(dir))是错误的*/


      strcat(dir,BackupDir);//在当前工作地址之后加上\backup\构造备份文件夹所在目录
      strcat(dir,time);//在目录后面加上文件名
      AddBackslash(dir);//把整个路径字符串里面所有的单个 \ 变成\\  以便当做文件名字符串在create等函数中做实参时 \\ 转意成 “\”


     return ;
}



BOOL Choice(char*pCh[],int n)//弹出提示框，选择“是”  还是“否” ，并返回相应布尔值的函数,其中char*pCh[]是要显示的字符串数组，n是字符串数组的元素个数，即提示框文字的行数
{
   //例如char *pCh[] = {"确认退出系统吗？", "确定    取消"};

    LABEL_BUNDLE labels;//用来储存提示框中的文本信息，包括文本的内容，文本中每个字符串的输出位置，文本的行数
    HOT_AREA areas;
    BOOL bRet = TRUE;
    SMALL_RECT rcPop;
    COORD pos,home;
    WORD att;
    att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*白底黑字*/

    int iHot = 1,i=0,maxlen,str_len,size;

     for (i=0,maxlen=0; i<n; i++)//这里的i<n里面的n是提示框中文字的行数，也就是字符串数组char*pCh[]被赋实参后的元素个数
    {
        str_len = strlen(pCh[i]);
        if (maxlen < str_len)
        {
            maxlen = str_len;
        }
    }  //maxlen是字符数组中最长的字符串长度



    pos.X = maxlen + 6;  //提示框的宽度
    pos.Y = n+5;    //提示框纵向的长度
    rcPop.Left = (SCR_COL - pos.X) / 2;   //提示框的左边左边
    rcPop.Right = rcPop.Left + pos.X - 1; //提示框的右边左边
    rcPop.Top = (SCR_ROW - pos.Y) / 2;    //提示框的上边左边
    rcPop.Bottom = rcPop.Top + pos.Y - 1; //提示框的下边左边




   /*home初始化为弹出提示框的左上角坐标，*/
    home.X=rcPop.Left;
    home.Y=rcPop.Top;
    size=maxlen + 6; //size为提示框宽度，其实就是pos.X

     /*将提示框中所有单元填充为空格符*/
    for(i=0;i<pos.Y; ++i,++home.Y)  //pos.Y为提示框行数
    FillConsoleOutputCharacter(gh_std_out, ' ', size, home, &ul);




    COORD aLoc[n]; //用来存放字符串的输出位置
    for (i=0; i<n; i++) //此for循环给在提示框中显示的每一个字符串输出的位置初始化，即第i个字符串的第一个字符在哪里开始输出；
    {
        aLoc[i].X = rcPop.Left + 3;
        aLoc[i].Y = rcPop.Top + 2 + i;

    }

   /*下面3行代码是确定形参传递进来的字符串数组的最后一个字符串的输出位置，由于一般是 “是  否” 这样的字符串，因此靠中间一点比较好看*/
    str_len = strlen(pCh[n-1]);
    aLoc[n-1].X = rcPop.Left + 3 + (maxlen-str_len)/2;
    aLoc[n-1].Y = aLoc[n-1].Y + 2;
   //至此 aLoc已经完成赋值


    labels.pLoc = aLoc;//把aLoc中储存的位置信息存到labels结构的pLoc成员中
    labels.num = n;  //提示框的文本行数为n
    labels.ppLabel = pCh;//提示框中的文本内容为形参传递过来的内容


/*aArea用来储存在提示框最后一行“是  否”上标注选项的光标的位置，第一个大元素的四个小元素分别表示：
光标在“是”上时候，左边界的X、Y坐标，右边界的X、Y坐标。第二个大元素是“否”的,内容同上*/
    SMALL_RECT aArea[] = {
                           {aLoc[n-1].X, aLoc[n-1].Y,
                           aLoc[n-1].X + 3, aLoc[n-1].Y},

                           {aLoc[n-1].X+8, aLoc[n-1].Y,
                           aLoc[n-1].X+8+3, aLoc[n-1].Y}

                          };


    /*home初始化为弹出提示框的左上角坐标，*/
    home.X=rcPop.Left;
    home.Y=rcPop.Top;
    size=maxlen + 6; //size为提示框宽度，其实就是pos.X

     /*将提示框中所有单元填充为空格符*/
    for(i=0;i<pos.Y; ++i,++home.Y)  //pos.Y为提示框行数
    FillConsoleOutputCharacter(gh_std_out, ' ', size, home, &ul);


    char aSort[] = {0, 0};
    char aTag[] = {1, 2};
    areas.num = 2;//热区数量  “是  否”  因此为2
    areas.pArea = aArea;  //热区“是否”选项的位置
    areas.pSort = aSort;
    areas.pTag = aTag;
    PopUp(&rcPop, att, &labels, &areas);

    pos.X = rcPop.Left + 1;
    pos.Y = rcPop.Top + 2 + n;   //此时pos中的内容被更改为输出'-'的起始位置，与上面代表提示框区域的大小不同
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
BOOL QuerySchInfoViaBossname(void)//查询院系基本信息的大函数中的实现主要功能的小函数
{

    BOOL bRet;
    CONSOLE_CURSOR_INFO lpCur;
    char boss_name[12];
    SCH_NODE *psch_node;
    int i=0,num=0;


Cmdinput1:
    psch_node=gp_head;

    char *plabel_name[] = {"请输入需要查询信息的院系的负责人姓名",
                           "         ( 少于12字符 ）            ",
                           "确认"
                          };

                          ShowModule(plabel_name, 3);

                          ClearScreenTotalInputArea();

    /*显示光标*/
    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible=TRUE;
    SetConsoleCursorInfo(gh_std_out,&lpCur);


    printf("负责人姓名：  ");
    scanf("%s",boss_name);
    getchar();


    num=0;
    i=0;//此两个计数器必须再初始化为零，不然继续查询时候，num在上一次查询的基础上自增，就可能出现错误


    while(psch_node!=NULL)//数一数有多少个负责人是输入的人名的院系
    {
        if(strcmp(psch_node->boss_name,boss_name)==0)
        {
          num++;
        }
        psch_node=psch_node->next;
    }
    psch_node=gp_head;//psch_node重新指向链表头

    SCH_NODE *find[num+1];//元素个数多一个来储存NULL作为结束点
    find[0]=NULL;//储存的第一个指针置空，如果一个负责人为所输入的人的院系都没找到，那么find[0]为空则不会改变，反之会改变，因此可以用其做判断标志


    while(psch_node!=NULL)//把链表中负责人姓名和所输入的人的姓名相同的表格的指针记录下来
    {
        if(strcmp(psch_node->boss_name,boss_name)==0)
        {
          find[i]=psch_node;i++;
        }
        psch_node=psch_node->next;
    }
    find[i]=NULL;//最后一个指针置空，如果一个没找到正好就find[0]=NULL;



    if(find[0]!=NULL)//至少发现一个负责人为所输入的姓名的院系
    {   int i;
        printf("\n               ###查到相关院系信息###\n\n");
        char *tab[3]={"院系名称","负责人", "联系电话"};

        printf(" %-20s%-12s%-15s\n",tab[0],tab[1],tab[2]);
        printf("------------------------------------------------------------\n");

        for(i=0;find[i]!=NULL;i++)//循环输出所有负责人为所输入的人的院系相关信息
       {
           printf(" %-20s%-12s%-15s\n",find[i]->sch_name, find[i]->boss_name, find[i]->tel);
       }


        getch();
        char *plabel_name[] = {"是否继续查询？",  " "," 是      否 "};
        bRet=Choice(plabel_name,3) ;
        switch(bRet)
        {
            case TRUE:   {
                           ClearScreenTotalInputArea();
                           goto Cmdinput1;
                         }


            case FALSE:  {
                            char *plabel_name[] = {"完成查询！",
                                                "  ",
                                                "确认"
                                                };

                           ShowModule(plabel_name, 3);

                           ClearScreenTotalInputArea();

                             goto End;
                         }



        }






    }

    else //一个负责人为此人的信息都没找到
    {
        char *plabel_name[] = {"该姓名不存在!"," ","是否重新输入？"," 是      否 "};
        bRet=Choice(plabel_name,4) ;

         switch(bRet)
        {
            case TRUE:   {
                           ClearScreenTotalInputArea();
                           goto Cmdinput1;
                         }


            case FALSE:  {
                            char *plabel_name[] = {"完成查询！",
                                                "  ",
                                                "确认"
                                                };

                           ShowModule(plabel_name, 3);

                           ClearScreenTotalInputArea();

                             goto End;
                         }



        }
    }

End:
    /*隐藏光标*/
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

    char *plabel_name[] = {"请输入需要查询信息的院系的名称的全部或部分",
                           "             ( 少于20字符 ）              ",
                           "确认"
                          };

                          ShowModule(plabel_name, 3);

                          ClearScreenTotalInputArea();

    /*显示光标*/
    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible=TRUE;
    SetConsoleCursorInfo(gh_std_out,&lpCur);


    printf("院系名称全部或部分(内无空格)：  ");
    scanf("%s",sch_name);
    getchar();


    num=0;
    i=0;//此两个计数器必须再初始化为零，不然继续查询时候，num在上一次查询的基础上自增，就可能出现错误


    while(psch_node!=NULL)//数一数有多少个含有关键字的学院名
    {
        if(strstr(psch_node->sch_name,sch_name)!=NULL)
        {
          num++;
        }
        psch_node=psch_node->next;
    }
    psch_node=gp_head;//psch_node重新指向链表头

    SCH_NODE *find[num+1];//元素个数多一个来储存NULL作为结束点
    find[0]=NULL;//储存的第一个指针置空，如果一个相关的院系都没找到，那么find[0]为空则不会改变，反之会改变，因此可以用其做判断标志


    while(psch_node!=NULL)//把链表中院系名中含有输入的关键字的表格的指针记录下来
    {
        if(strstr(psch_node->sch_name,sch_name)!=NULL)
        {
          find[i]=psch_node;i++;
        }
        psch_node=psch_node->next;
    }
    find[i]=NULL;//最后一个指针置空，如果一个没找到正好就find[0]=NULL;



    if(find[0]!=NULL)//至少发现一个相关院系
    {   int i;
        printf("\n               ###查到相关院系信息###\n\n");
        char *tab[3]={"院系名称","负责人", "联系电话"};

        printf(" %-20s%-12s%-15s\n",tab[0],tab[1],tab[2]);
        printf("------------------------------------------------------------\n");

        for(i=0;find[i]!=NULL;i++)//循环输出所有含有关键字的院系相关信息
       {
           printf(" %-20s%-12s%-15s\n",find[i]->sch_name, find[i]->boss_name, find[i]->tel);
       }


        getch();
        char *plabel_name[] = {"是否继续查询？",  " "," 是      否 "};
        bRet=Choice(plabel_name,3) ;
        switch(bRet)
        {
            case TRUE:   {
                           ClearScreenTotalInputArea();
                           goto Cmdinput1;
                         }


            case FALSE:  {
                            char *plabel_name[] = {"完成查询！",
                                                "  ",
                                                "确认"
                                                };

                           ShowModule(plabel_name, 3);

                           ClearScreenTotalInputArea();

                             goto End;
                         }



        }






    }

    else //一个含有输入关键字的院系名信息都没找到
    {
        char *plabel_name[] = {"该相关院系不存在!"," ","是否重新输入？"," 是      否 "};
        bRet=Choice(plabel_name,4) ;

         switch(bRet)
        {
            case TRUE:   {
                           ClearScreenTotalInputArea();
                           goto Cmdinput1;
                         }


            case FALSE:  {
                            char *plabel_name[] = {"完成查询！",
                                                "  ",
                                                "确认"
                                                };

                           ShowModule(plabel_name, 3);

                           ClearScreenTotalInputArea();

                             goto End;
                         }



        }
    }

End:
    /*隐藏光标*/
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

    char *plabel_name[] = {"请输入需要查询信息的团队的名称的全部或部分",
                           "             ( 少于30字符 ）              ",
                           "确认"
                          };

                          ShowModule(plabel_name, 3);

                          ClearScreenTotalInputArea();

    /*显示光标*/
    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible=TRUE;
    SetConsoleCursorInfo(gh_std_out,&lpCur);


    printf("团队名称全部或部分(内无空格)：  ");
    scanf("%s",team_name);
    getchar();


    num=0;
    i=0;//此两个计数器必须再初始化为零，不然继续查询时候，num在上一次查询的基础上自增，就可能出现错误


    while(psch_node!=NULL)//数一数有多少团队名中含有输入关键字的团队
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
    psch_node=gp_head;//psch_node重新指向链表头

    TEAM_NODE *find[num+1];//元素个数多一个来储存NULL作为结束点
    find[0]=NULL;//储存的第一个指针置空，如果一个相关团队都没找到，那么find[0]为空则不会改变，反之会改变，因此可以用其做判断标志


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

    find[i]=NULL;//最后一个指针置空，如果一个没找到正好就find[0]=NULL;




    if(find[0]!=NULL)//至少发现一个相关团队
    {   int i;
        printf("\n               ###查到相关团队信息###\n\n");
        char *tab[5]={"团队名称","负责人", "教师人数", "研究生人数","所属院系"};

        printf(" %-30s%-12s%-14s%-14s%-20s\n",tab[0],tab[1],tab[2],tab[3],tab[4]);
        printf("-------------------------------------------------------------------------------\n");

        for(i=0;find[i]!=NULL;i++)//循环输出所有相关团队相关信息
       {
           printf(" %-30s%-12s%-14d%-14d%-20s\n",find[i]->team_name, find[i]->boss_name, find[i]->prof_num, find[i]->stu_num, find[i]->sch);
       }


        getch();
        char *plabel_name[] = {"是否继续查询？",  " "," 是      否 "};
        bRet=Choice(plabel_name,3) ;
        switch(bRet)
        {
            case TRUE:   {
                           ClearScreenTotalInputArea();
                           goto Cmdinput1;
                         }


            case FALSE:  {
                            char *plabel_name[] = {"完成查询！",
                                                "  ",
                                                "确认"
                                                };

                           ShowModule(plabel_name, 3);

                           ClearScreenTotalInputArea();

                             goto End;
                         }



        }






    }

    else //一个团队名中含有输入关键字的团队的信息都没找到
    {
        char *plabel_name[] = {"该相关团队不存在!"," ","是否重新输入？"," 是      否 "};
        bRet=Choice(plabel_name,4) ;

         switch(bRet)
        {
            case TRUE:   {
                           ClearScreenTotalInputArea();
                           goto Cmdinput1;
                         }


            case FALSE:  {
                            char *plabel_name[] = {"完成查询！",
                                                "  ",
                                                "确认"
                                                };

                           ShowModule(plabel_name, 3);

                           ClearScreenTotalInputArea();

                             goto End;
                         }



        }
    }

End:
    /*隐藏光标*/
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

    char *plabel_name[] = {"请输入团队教师人数的下限",
                           " ",
                           "确认"
                          };

                          ShowModule(plabel_name, 3);

                          ClearScreenTotalInputArea();

    /*显示光标*/
    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible=TRUE;
    SetConsoleCursorInfo(gh_std_out,&lpCur);


    printf("教师人数下限：  ");
    scanf("%d",&prof_num);
    getchar();


    num=0;
    i=0;//此两个计数器必须再初始化为零，不然继续查询时候，num在上一次查询的基础上自增，就可能出现错误


    while(psch_node!=NULL)//数一数有多少个教师人数大于输入的人数下限的团队
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
    psch_node=gp_head;//psch_node重新指向链表头

    TEAM_NODE *find[num+1];//元素个数多一个来储存NULL作为结束点
    find[0]=NULL;//储存的第一个指针置空，如果一个相关团队都没找到，那么find[0]为空则不会改变，反之会改变，因此可以用其做判断标志


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

    find[i]=NULL;//最后一个指针置空，如果一个没找到正好就find[0]=NULL;




    if(find[0]!=NULL)//至少发现一符合条件的团队
    {   int i;
        printf("\n               ###查到相关团队信息###\n\n");
        char *tab[5]={"团队名称","负责人", "教师人数", "研究生人数","所属院系"};

        printf(" %-30s%-12s%-14s%-14s%-20s\n",tab[0],tab[1],tab[2],tab[3],tab[4]);
        printf("-------------------------------------------------------------------------------\n");

        for(i=0;find[i]!=NULL;i++)//循环输出所有相关团队
       {
           printf(" %-30s%-12s%-14d%-14d%-20s\n",find[i]->team_name, find[i]->boss_name, find[i]->prof_num, find[i]->stu_num, find[i]->sch);
       }


        getch();
        char *plabel_name[] = {"是否继续查询？",  " "," 是      否 "};
        bRet=Choice(plabel_name,3) ;
        switch(bRet)
        {
            case TRUE:   {
                           ClearScreenTotalInputArea();
                           goto Cmdinput1;
                         }


            case FALSE:  {
                            char *plabel_name[] = {"完成查询！",
                                                "  ",
                                                "确认"
                                                };

                           ShowModule(plabel_name, 3);

                           ClearScreenTotalInputArea();

                             goto End;
                         }



        }






    }

    else //一个教师人数大于用户所给下限的团队都没找到
    {
        char *plabel_name[] = {"该相关团队不存在!"," ","是否重新输入？"," 是      否 "};
        bRet=Choice(plabel_name,4) ;

         switch(bRet)
        {
            case TRUE:   {
                           ClearScreenTotalInputArea();
                           goto Cmdinput1;
                         }


            case FALSE:  {
                            char *plabel_name[] = {"完成查询！",
                                                "  ",
                                                "确认"
                                                };

                           ShowModule(plabel_name, 3);

                           ClearScreenTotalInputArea();

                             goto End;
                         }



        }
    }

End:
    /*隐藏光标*/
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

    char *plabel_name[] = {"请输入需要查询信息的科研项目的编号",
                           "         ( 少于15字符 ）            ",
                           "确认"
                          };

                          ShowModule(plabel_name, 3);

                          ClearScreenTotalInputArea();

    /*显示光标*/
    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible=TRUE;
    SetConsoleCursorInfo(gh_std_out,&lpCur);


    printf("项目编号：  ");
    scanf("%s",prj_num);
    getchar();


    num=0;
    i=0;//此两个计数器必须再初始化为零，不然继续查询时候，num在上一次查询的基础上自增，就可能出现错误


    while(psch_node!=NULL)//数一数有多少个项目编号是输入的那个编号，其实由于项目编号唯一，此算法多余
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
    psch_node=gp_head;//psch_node重新指向链表头

    SCIPRJ_NODE *find[num+1];//元素个数多一个来储存NULL作为结束点
    find[0]=NULL;//储存的第一个指针置空，如果没找到，那么find[0]为空则不会改变，反之会改变，因此可以用其做判断标志



    while(psch_node!=NULL)//把链表中项目编号和所输入的人的编号相同的表格的指针记录下来，其实由于编号唯一，没必要这么写
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
    find[i]=NULL;//最后一个指针置空，如果一个没找到正好就find[0]=NULL;




    if(find[0]!=NULL)//至少发现一个符合条件的项目
    {   int i=0;
        printf("\n               ###查到相关项目信息###\n\n");
        char *tab[6]={"项目编号","项目类别", "起始时间","项目经费(万元)","负责人","所属团队"};

        printf(" %-20s%-10s%-16s%-16s%-16s%-30s\n",tab[0],tab[1],tab[2],tab[3],tab[4],tab[5]);
        printf("---------------------------------------------------------------------------------------------\n");

        for(i=0;find[i]!=NULL;i++)//循环输出所有符合条件的项目
       {
           printf(" %-20s%-10c%-16s%-16.2f%-16s%-30s\n",find[i]->prj_num, find[i]->type, find[i]->start_time, find[i]->prj_fund, find[i]->boss_name, find[i]->team);
       }


        getch();
        char *plabel_name[] = {"是否继续查询？",  " ", " 是      否 "};
        bRet=Choice(plabel_name,3) ;
        switch(bRet)
        {
            case TRUE:   {
                           ClearScreenTotalInputArea();
                           goto Cmdinput1;
                         }


            case FALSE:  {
                            char *plabel_name[] = {"完成查询！",
                                                "  ",
                                                "确认"
                                                };

                           ShowModule(plabel_name, 3);

                           ClearScreenTotalInputArea();

                             goto End;
                         }



        }






    }

    else //没有发现该编号的项目
    {
        char *plabel_name[] = {"该编号不存在！"," ","是否重新输入？"," 是      否 "};
        bRet=Choice(plabel_name,4) ;

         switch(bRet)
        {
            case TRUE:   {
                           ClearScreenTotalInputArea();
                           goto Cmdinput1;
                         }


            case FALSE:  {
                            char *plabel_name[] = {"完成查询！",
                                                "  ",
                                                "确认"
                                                };

                           ShowModule(plabel_name, 3);

                           ClearScreenTotalInputArea();

                             goto End;
                         }



        }
    }

End:
    /*隐藏光标*/
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

    char *plabel_name[] = {"请输入需要查询信息的科研项目的所属团队",
                           "          ( 少于30字符 ）            ",
                           "确认"
                          };

                          ShowModule(plabel_name, 3);

                          ClearScreenTotalInputArea();

    /*显示光标*/
    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible=TRUE;
    SetConsoleCursorInfo(gh_std_out,&lpCur);


    printf("所属团队：  ");
    scanf("%s",team);
    getchar();


    num=0;
    i=0;//此两个计数器必须再初始化为零，不然继续查询时候，num在上一次查询的基础上自增，就可能出现错误


    while(psch_node!=NULL)//数一数有多少个项目编号是输入的那个编号，其实由于项目编号唯一，此算法多余
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
    psch_node=gp_head;//psch_node重新指向链表头

    SCIPRJ_NODE *find[num+1];//元素个数多一个来储存NULL作为结束点
    find[0]=NULL;//储存的第一个指针置空，如果没找到，那么find[0]为空则不会改变，反之会改变，因此可以用其做判断标志



    while(psch_node!=NULL)//把链表中项目编号和所输入的人的编号相同的表格的指针记录下来，其实由于编号唯一，没必要这么写
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
    find[i]=NULL;//最后一个指针置空，如果一个没找到正好就find[0]=NULL;




    if(find[0]!=NULL)//至少发现一个负责人为所输入的姓名的院系
    {   int i=0;
        printf("\n               ###查到相关项目信息###\n\n");
        char *tab[6]={"项目编号","项目类别", "起始时间","项目经费(万元)","负责人","所属团队"};

        printf(" %-20s%-10s%-16s%-16s%-16s%-30s\n",tab[0],tab[1],tab[2],tab[3],tab[4],tab[5]);
        printf("---------------------------------------------------------------------------------------------\n");

        for(i=0;find[i]!=NULL;i++)//循环输出所有负责人为所输入的人的院系相关信息
       {
           printf(" %-20s%-10c%-16s%-16.2f%-16s%-30s\n",find[i]->prj_num, find[i]->type, find[i]->start_time, find[i]->prj_fund, find[i]->boss_name, find[i]->team);
       }


        getch();
        char *plabel_name[] = {"是否继续查询？",  " ", " 是      否 "};
        bRet=Choice(plabel_name,3) ;
        switch(bRet)
        {
            case TRUE:   {
                           ClearScreenTotalInputArea();
                           goto Cmdinput1;
                         }


            case FALSE:  {
                            char *plabel_name[] = {"完成查询！",
                                                "  ",
                                                "确认"
                                                };

                           ShowModule(plabel_name, 3);

                           ClearScreenTotalInputArea();

                             goto End;
                         }



        }






    }

    else //一个负责人为此人的信息都没找到
    {
        char *plabel_name[] = {"该所属团队不存在！"," ","是否重新输入？"," 是      否 "};
        bRet=Choice(plabel_name,4) ;

         switch(bRet)
        {
            case TRUE:   {
                           ClearScreenTotalInputArea();
                           goto Cmdinput1;
                         }


            case FALSE:  {
                            char *plabel_name[] = {"完成查询！",
                                                "  ",
                                                "确认"
                                                };

                           ShowModule(plabel_name, 3);

                           ClearScreenTotalInputArea();

                             goto End;
                         }



        }
    }

End:
    /*隐藏光标*/
    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible=FALSE;
    SetConsoleCursorInfo(gh_std_out,&lpCur);


    return TRUE;
}


/**统计各院系教师总数，研究生总数，及研究生与教师的人数比（保留 2 位小数），
按学生教师 人数比值降序排序后，输出统计结果*/
BOOL StatResearcherNumInfo(void)
{

    CONSOLE_CURSOR_INFO lpCur;

    SCH_NODE *psch_node=NULL;
    TEAM_NODE *pteam_node=NULL;
    int i=0,j=0,sch_num=0;
    int temp_prof_num=0,temp_studt_num=0;
    double temp_rate=0;
    char *temp_sch_name=NULL;




     /*显示光标*/
    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible=TRUE;
    SetConsoleCursorInfo(gh_std_out,&lpCur);

    psch_node=gp_head;
    while(psch_node!=NULL)//统计院系数量
    {
        sch_num++;
        psch_node=psch_node->next;
    }


    int total_prof_num[sch_num],total_studt_num[sch_num];//声明数组储存各院系科研人员人数
    double rate[sch_num];//用来储存各院系的 研究生  教师  人数比
    char *sch_name[sch_num];//用来储存院系名


    for(i=0;i<sch_num;i++)//给数组元素初始化为0
    {
        total_prof_num[i]=0;
        total_studt_num[i]=0;
        rate[i]=0;
        sch_name[i]=NULL;
    }


    i=0;
    psch_node=gp_head;//各院系的教师和研究生人数统计
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



    for(i=0;i<sch_num;i++) //计算研究生教师的比值
    {
        if(total_prof_num[i]!=0)
          rate[i]=(1.0 * total_studt_num[i]) / (1.0 * total_prof_num[i]);

        else
          rate[i]=0;
    }

    for(i=0;i<sch_num;i++)//按学生教师 人数比值降序排序
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


    /*输入各院系教师、研究生人数及其比值*/
    printf("\n               ###各院系教师、研究生人数及其比值###\n\n");
        char *tab[4]={ "院系","研究生人数","教师人数", "研究生/教师"};

         printf("序号    %-24s%-16s%-12s%-15s\n", tab[0],tab[1],tab[2],tab[3]);
         printf("------------------------------------------------------------------\n");
        for(i=0;i<sch_num;i++)
        {
            printf("%-8d%-24s%-16d%-12d%-15.2f\n",i+1,sch_name[i],total_studt_num[i], total_prof_num[i], rate[i]);

        }

        printf("\n\n按任意键继续...\n");

        getch();

        char *plabel_name[] = {"统计输出完成！",
                                    "  ",
                                    "确认"
                                                };

                           ShowModule(plabel_name, 3);

                           ClearScreenTotalInputArea();

         /*隐藏光标*/
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

    typedef struct statsciprjnum//用来储存统计的信息的结构
    {
        char sch_name[20];
        int sum_prjnum;
        int num973;
        int num863;
        double sum_fund;
    } STAT_SCIPRJ_NUM;

    STAT_SCIPRJ_NUM temp;


     char *plabel_name[] = {"请输入需要统计的科研项目信息的年份!",
                                    "  ",
                                    "确认"
                                                };

                           ShowModule(plabel_name, 3);

                           ClearScreenTotalInputArea();


    /*显示光标*/
     GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible=TRUE;
    SetConsoleCursorInfo(gh_std_out,&lpCur);
Input1:
    printf("输入年份(格式:2017)：");
    scanf("%s",time);
    getchar();

    if(!JudgeYearRight(time))//如果年份格式不对
    {
        char *plabel_name[] = {"格式错误！请重新输入",
                               "     (如2017)       ",
                                    "确认"
                                                };

                           ShowModule(plabel_name, 3);

                           ClearScreenTotalInputArea();

                           goto Input1;


    }




    psch_node=gp_head;


   while(psch_node!=NULL)//统计院系数量
    {
        sch_num++;
        psch_node=psch_node->next;
    }



    STAT_SCIPRJ_NUM stat_sciprj_num[sch_num];//声明结构数组储存各院系科研项目相关信息


    for(i=0;i<sch_num;i++)//给数组元素初始化为0
    {
        stat_sciprj_num[i].sum_prjnum=0;
        stat_sciprj_num[i].num973=0;
        stat_sciprj_num[i].num863=0;
        stat_sciprj_num[i].sum_fund=0;
    }


    i=0;
    psch_node=gp_head;
   while(psch_node!=NULL)//统计某年度各院系科研项目数，973 项目数，863 项目数，及科研总经费
    {

     strcpy(stat_sciprj_num[i].sch_name , psch_node->sch_name);//储存院系名

      pteam_node=psch_node->tnext;
      while(pteam_node!=NULL)
      {

          psciprj_node=pteam_node->snext;
          while(psciprj_node!=NULL)
          {
              if(JudgeYearEqual(psciprj_node->start_time , time) == TRUE)//如果项目的起始时间中的年份等于所输出的年份
              {


                  stat_sciprj_num[i].sum_prjnum += 1;  //起始时间中年份为time的该院系项目总数自增1
                  stat_sciprj_num[i].sum_fund += psciprj_node->prj_fund;//统计该院系总的科研经费

                  if(psciprj_node->type == '1')
                    stat_sciprj_num[i].num973 += 1;//统计973项目

                  if(psciprj_node->type == '3')
                    stat_sciprj_num[i].num863 += 1;//统计863项目


              }


            psciprj_node=psciprj_node->next;
          }

          pteam_node=pteam_node->next;
      }

     psch_node=psch_node->next;
     i++; //统计下一个院系

    }



    for(i=0;i<sch_num;i++)//按科研项目数降序排序。
    {
        for(j=0;j<(sch_num-i-1);j++)
        {
            if( (stat_sciprj_num[j].sum_prjnum) < (stat_sciprj_num[j+1].sum_prjnum) )
            {
                temp=stat_sciprj_num[j]; stat_sciprj_num[j]=stat_sciprj_num[j+1];stat_sciprj_num[j+1]=temp;
            }
        }
    }


    /*输出按科研项目数降序排序后的某年度各院系科研项目数，973 项目数，863 项目数，及科研总经费*/
         printf("\n               ###%s年各院系科研项目数量统计###\n\n",time);
         char *tab[5]={ "院系","科研项目数","973项目数", "863项目数","科研总经费"};

         printf("序号    %-24s%-14s%-13s%-13s%-14s\n", tab[0],tab[1],tab[2],tab[3],tab[4]);
         printf("--------------------------------------------------------------------------------\n");
        for(i=0;i<sch_num;i++)
        {
          printf("%-8d%-24s%-14d%-13d%-13d%-14.2f\n",i+1,stat_sciprj_num[i].sch_name,stat_sciprj_num[i].sum_prjnum, stat_sciprj_num[i].num973, stat_sciprj_num[i].num863,stat_sciprj_num[i].sum_fund);

        }


        printf("\n\n按任意键继续...\n");

        getch();

        char *Anotherplabel_name[] = {"统计输出完成！",
                                    "  ",
                                    "确认"
                                                };

                           ShowModule(Anotherplabel_name, 3);

                           ClearScreenTotalInputArea();

         /*隐藏光标*/
    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible=FALSE;
    SetConsoleCursorInfo(gh_std_out,&lpCur);



        return TRUE;


}
BOOL JudgeYearEqual(char *s , char *t)//判断两个字符串的前4个字符是否全等，用来判断一个日期（如20170901）是否属于一个年份（2017）
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

BOOL JudgeYearRight(char *s)//判断输入的字符串是否形如 “2017”  是返回TRUE  否则返回FALSE
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

/*统计历年来类别为国家自然科学基金的科研项目数最多的 10 个科研团队，按项目数降序排序
后输出科研团队名称，类别为国家自然科学基金的科研项目数，以及项目经费总数*/
BOOL StatNatureSciTop10(void)
{
    CONSOLE_CURSOR_INFO lpCur;

    SCH_NODE *psch_node=NULL;
    TEAM_NODE *pteam_node=NULL;
    SCIPRJ_NODE *psciprj_node=NULL;
    int i=0,j=0,team_num=0,num=0;


    typedef struct statnaturescinum//用来储存统计信息的结构
    {
        char sch[20];
        char team_name[30];
        int  nat_scinum;
        double sum_fund;
    } STAT_NATURE_SCI_NUM;

    STAT_NATURE_SCI_NUM temp;




    /*显示光标*/
     GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible=TRUE;
    SetConsoleCursorInfo(gh_std_out,&lpCur);



    psch_node=gp_head;


   while(psch_node!=NULL)//统团队系数量
    {
        pteam_node=psch_node->tnext;
        while(pteam_node!=NULL)
        {
            team_num++;
            pteam_node=pteam_node->next;
        }
        psch_node=psch_node->next;
    }



    STAT_NATURE_SCI_NUM stat_nature_sci_num[team_num];//声明结构数组储存各团队科研项目相关信息


    for(i=0;i<team_num;i++)//给数组元素初始化为0
    {
        stat_nature_sci_num[i].nat_scinum=0;

        stat_nature_sci_num[i].sum_fund=0;
    }


    i=0;
    psch_node=gp_head;
   while(psch_node!=NULL)//统计科研团队名称，类别为国家自然科学基金的科研项目数，以及项目经费总数
    {

     pteam_node=psch_node->tnext;
      while(pteam_node!=NULL)
      {

          strcpy(stat_nature_sci_num[i].sch , psch_node->sch_name);//储存院系名
          strcpy(stat_nature_sci_num[i].team_name , pteam_node->team_name);//储存团队名

          psciprj_node=pteam_node->snext;
          while(psciprj_node!=NULL)
          {



                  if(psciprj_node->type == '2')
                    {

                     stat_nature_sci_num[i].nat_scinum += 1;//统计国家自然基金的项目数
                     stat_nature_sci_num[i].sum_fund += psciprj_node->prj_fund;//统计该团队项目类别为国家自然基金的总的科研经费

                    }

                  psciprj_node=psciprj_node->next;


          }

          pteam_node=pteam_node->next;
          i++; //统计下一个团队
      }

     psch_node=psch_node->next;

    }



    for(i=0;i<team_num;i++)//按类别为国家自然基金科研项目数降序排序。
    {
        for(j=0;j<(team_num-i-1);j++)
        {
            if( (stat_nature_sci_num[j].nat_scinum) < (stat_nature_sci_num[j+1].nat_scinum) )
            {
                temp=stat_nature_sci_num[j]; stat_nature_sci_num[j]=stat_nature_sci_num[j+1];stat_nature_sci_num[j+1]=temp;
            }
        }
    }


    /*输出科研团队名称，类别为国家自然科学基金的科研项目数，项目经费总数，以及所属院系*/
         printf("\n               ###国家自然科学基金(NFSC)的科研项目数最多top10###\n\n");
         char *tab[4]={ "团队名称","NSFC项目数", "项目经费总数","所属院系"};

         printf("序号    %-34s%-14s%-16s%-24s\n", tab[0],tab[1],tab[2],tab[3]);
         printf("--------------------------------------------------------------------------------------\n");


         if(team_num>=10)//判断当前团队总数是否超过10，如果没超过则  有多少输出多少
             num=10;

         else
             num=team_num;




        for(i=0;i<num;i++)//输出统计的信息
        {
          printf("%-8d%-34s%-14d%-16.2f%-24s\n",i+1,stat_nature_sci_num[i].team_name,stat_nature_sci_num[i].nat_scinum, stat_nature_sci_num[i].sum_fund, stat_nature_sci_num[i].sch);

        }


        printf("\n\n按任意键继续...\n");

        getch();

        char *Anotherplabel_name[] = {"统计输出完成！",
                                    "  ",
                                    "确认"
                                                };

                           ShowModule(Anotherplabel_name, 3);

                           ClearScreenTotalInputArea();

         /*隐藏光标*/
    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible=FALSE;
    SetConsoleCursorInfo(gh_std_out,&lpCur);



        return TRUE;
}



/*统计科研项目数和教师人数的比值最高的 5 个科研团队，按比值（保留两位小数）
降序排序后， 输出科研团队名称，教师人数，科研项目数，项目数和教师人数比值。*/
BOOL StatPrjProfRate(void)
{
    CONSOLE_CURSOR_INFO lpCur;

    SCH_NODE *psch_node=NULL;
    TEAM_NODE *pteam_node=NULL;
    SCIPRJ_NODE *psciprj_node=NULL;
    int i=0,j=0,team_num=0,num=0;


    typedef struct statprjandprofrate//用来储存统计信息的结构
    {
        char sch[20];
        char team_name[30];
        int  prof_num;
        int  sciprj_num;
        double rate;
    } STAT_PRJ_PROF_RATE;

    STAT_PRJ_PROF_RATE temp;




    /*显示光标*/
     GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible=TRUE;
    SetConsoleCursorInfo(gh_std_out,&lpCur);



    psch_node=gp_head;


   while(psch_node!=NULL)//统团队系数量
    {
        pteam_node=psch_node->tnext;
        while(pteam_node!=NULL)
        {
            team_num++;
            pteam_node=pteam_node->next;
        }
        psch_node=psch_node->next;
    }



    STAT_PRJ_PROF_RATE   stat_prj_prof_rate[team_num];//声明结构数组储存各团队教师人数和科研项目数相关信息


    for(i=0;i<team_num;i++)//给数组元素初始化为0
    {
        stat_prj_prof_rate[i].prof_num=0;

        stat_prj_prof_rate[i].sciprj_num=0;

        stat_prj_prof_rate[i].rate=0;
    }


    i=0;
    psch_node=gp_head;
   while(psch_node!=NULL)//统计科研团队名称，所属院系，科研项目数，以及教师人数
    {

     pteam_node=psch_node->tnext;
      while(pteam_node!=NULL)
      {

          strcpy(stat_prj_prof_rate[i].sch , psch_node->sch_name);//储存院系名
          strcpy(stat_prj_prof_rate[i].team_name , pteam_node->team_name);//储存团队名

          psciprj_node=pteam_node->snext;
          while(psciprj_node!=NULL)//统计科研项目数
          {
                  stat_prj_prof_rate[i].sciprj_num += 1;
                  psciprj_node=psciprj_node->next;
          }

          stat_prj_prof_rate[i].prof_num= pteam_node->prof_num;//统计教师人数
          stat_prj_prof_rate[i].rate=(1.0 * stat_prj_prof_rate[i].sciprj_num) / (1.0 * stat_prj_prof_rate[i].prof_num);//计算比率

          pteam_node=pteam_node->next;
          i++; //统计下一个团队
      }

     psch_node=psch_node->next;

    }



    for(i=0;i<team_num;i++)//按比率降序排序。
    {
        for(j=0;j<(team_num-i-1);j++)
        {
            if( (stat_prj_prof_rate[j].rate) < (stat_prj_prof_rate[j+1].rate) )
            {
                temp=stat_prj_prof_rate[j]; stat_prj_prof_rate[j]=stat_prj_prof_rate[j+1];stat_prj_prof_rate[j+1]=temp;
            }
        }
    }


    /*输出科研团队名称，科研项目数，教师人数，比率，以及所属院系*/
         printf("\n               ###科研项目数和教师人数的比值最高的科研团队top5###\n\n");
         char *tab[5]={ "团队名称", "科研项目数","教师人数","项目数/教师数","所属院系"};

         printf("序号    %-34s%-14s%-12s%-17s%-30s\n", tab[0],tab[1],tab[2],tab[3],tab[4]);
         printf("------------------------------------------------------------------------------------------------------\n");


         if(team_num>=5)//判断当前团队总数是否超过5，如果没超过则有多少输出多少
             num=5;

         else
             num=team_num;




        for(i=0;i<num;i++)//输出统计的信息
        {
          printf("%-8d%-34s%-14d%-12d%-17.2f%-30s\n",i+1,stat_prj_prof_rate[i].team_name,stat_prj_prof_rate[i].sciprj_num, stat_prj_prof_rate[i].prof_num, stat_prj_prof_rate[i].rate,stat_prj_prof_rate[i].sch);

        }


        printf("\n\n按任意键继续...\n");

        getch();

        char *Anotherplabel_name[] = {"统计输出完成！",
                                    "  ",
                                    "确认"
                                                };

                           ShowModule(Anotherplabel_name, 3);

                           ClearScreenTotalInputArea();

         /*隐藏光标*/
    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible=FALSE;
    SetConsoleCursorInfo(gh_std_out,&lpCur);



        return TRUE;
}


/*统计一个团队总的教师人数还有科研经费，计算人均科研经费
然后根据人均科研经费降序排列输出*/
BOOL StatFundProfRate(void)
{
    CONSOLE_CURSOR_INFO lpCur;

    SCH_NODE *psch_node=NULL;
    TEAM_NODE *pteam_node=NULL;
    SCIPRJ_NODE *psciprj_node=NULL;
    int i=0,j=0,team_num=0;;


    typedef struct statfundandprofrate//用来储存统计信息的结构
    {
        char sch[20];
        char team_name[30];
        int  prof_num;
        double fund;
        double rate;
    } STAT_FUND_PROF_RATE;

    STAT_FUND_PROF_RATE temp;




    /*显示光标*/
     GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible=TRUE;
    SetConsoleCursorInfo(gh_std_out,&lpCur);



    psch_node=gp_head;


   while(psch_node!=NULL)//统团队系数量
    {
        pteam_node=psch_node->tnext;
        while(pteam_node!=NULL)
        {
            team_num++;
            pteam_node=pteam_node->next;
        }
        psch_node=psch_node->next;
    }



    STAT_FUND_PROF_RATE   stat_fund_prof_rate[team_num];//声明结构数组储存教师人数，总科研经费相关信息


    for(i=0;i<team_num;i++)//给数组元素初始化为0
    {
        stat_fund_prof_rate[i].prof_num=0;

        stat_fund_prof_rate[i].fund=0;

        stat_fund_prof_rate[i].rate=0;
    }


    i=0;
    psch_node=gp_head;
   while(psch_node!=NULL)//统计科研团队名称，所属院系，总的科研经费，教师人数，以及计算比率
    {

     pteam_node=psch_node->tnext;
      while(pteam_node!=NULL)
      {

          strcpy(stat_fund_prof_rate[i].sch , psch_node->sch_name);//储存院系名
          strcpy(stat_fund_prof_rate[i].team_name , pteam_node->team_name);//储存团队名

          psciprj_node=pteam_node->snext;
          while(psciprj_node!=NULL)//利用循环，统计整个团队总的科研经费
          {
                  stat_fund_prof_rate[i].fund += psciprj_node->prj_fund;
                  psciprj_node=psciprj_node->next;
          }

          stat_fund_prof_rate[i].prof_num= pteam_node->prof_num;//统计团队的教师人数
          stat_fund_prof_rate[i].rate=(1.0 * stat_fund_prof_rate[i].fund) / (1.0 * stat_fund_prof_rate[i].prof_num);

          pteam_node=pteam_node->next;
          i++; //统计下一个团队
      }

     psch_node=psch_node->next;

    }



    for(i=0;i<team_num;i++)//按总的经费和教师人数的比值降序排序。
    {
        for(j=0;j<(team_num-i-1);j++)
        {
            if( (stat_fund_prof_rate[j].rate) < (stat_fund_prof_rate[j+1].rate) )
            {
                temp=stat_fund_prof_rate[j]; stat_fund_prof_rate[j]=stat_fund_prof_rate[j+1];stat_fund_prof_rate[j+1]=temp;
            }
        }
    }


    /*输出科研团队名称，总的科研经费，教师人数，，比率以及所属院系*/
         printf("\n                                 ###最土豪团队排行榜###\n\n");
         char *tab[5]={ "团队名称", "总科研经费","教师人数","总经费/教师数","所属院系"};

         printf("序号    %-34s%-14s%-12s%-17s%-30s\n", tab[0],tab[1],tab[2],tab[3],tab[4]);
         printf("------------------------------------------------------------------------------------------------------\n");




        for(i=0;i<team_num;i++)//输出统计的信息
        {
          printf("%-8d%-34s%-14.2f%-12d%-17.2f%-30s\n",i+1,stat_fund_prof_rate[i].team_name,stat_fund_prof_rate[i].fund, stat_fund_prof_rate[i].prof_num, stat_fund_prof_rate[i].rate,stat_fund_prof_rate[i].sch);

        }


        printf("\n\n按任意键继续...\n");

        getch();

        char *Anotherplabel_name[] = {"统计输出完成！",
                                    "  ",
                                    "确认"
                                                };

                           ShowModule(Anotherplabel_name, 3);

                           ClearScreenTotalInputArea();

         /*隐藏光标*/
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


    char *tab1[3]={"院系名称","负责人姓名","联系电话"};
    char *tab2[5]={"团队名称","负责人姓名","教师人数","研究生人数","所属院系"};
    char *tab3[6]={"项目编号","项目类别","起始时间","项目经费(万元)","负责人","所属团队"};

     /*显示光标*/
    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible=TRUE;
    SetConsoleCursorInfo(gh_std_out,&lpCur);

    printf("信息以录入时间的顺序输出！\n后录入的先输出...\n\n\n\n\n");




    printf("                    ###院系基本信息表###\n\n");//表的标题
    printf("序号    %-24s%-16s%-19s\n",tab1[0],tab1[1],tab1[2]);//输出表头
    printf("-------------------------------------------------------------\n");

    psch_node=gp_head;
    while(psch_node!=NULL)//循环输出所有信息
    {
        printf("%-8d%-24s%-16s%-19s\n",i,psch_node->sch_name , psch_node->boss_name , psch_node->tel);
        psch_node=psch_node->next;
        i++;
    }




    printf("\n\n\n\n\n\n                         ###科研团队基本信息表###\n\n");//输出科研团队信息的表标题
    printf("序号    %-34s%-16s%-12s%-14s%-24s\n",tab2[0],tab2[1],tab2[2],tab2[3],tab2[4]);//输出表头
    printf("-----------------------------------------------------------------------------------------------\n");

    psch_node=gp_head;
    i=1;
    while(psch_node!=NULL)//循环输出科研团队基本信息
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


    printf("\n\n\n\n\n\n                                  ###科研团队基本信息表###\n\n");//输出科研项目基本信息的表标题
    printf("序号    %-19s%-12s%-12s%-18s%-16s%-24s\n",tab3[0],tab3[1],tab3[2],tab3[3],tab3[4],tab3[5]);//输出表头
    printf("-----------------------------------------------------------------------------------------------------\n");

    psch_node=gp_head;
    i=1;
     while(psch_node!=NULL)//循环输出科研团队基本信息
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


    printf("\n所有信息输出完成，按任意键继续...");

    getch();


    ClearScreenTotalInputArea();//清屏

         /*隐藏光标*/
    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible=FALSE;
    SetConsoleCursorInfo(gh_std_out,&lpCur);





    return TRUE;




}



