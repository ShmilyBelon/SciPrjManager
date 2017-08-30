#include"ExternInfoList.h"


/**
 * ��������: LoadData
 * ��������: ������������ݴ������ļ����뵽�ڴ滺������ʮ��������.
 * �������: ��
 * �������: ��
 * �� �� ֵ: BOOL����, ���ܺ����г��˺���ExitSys�ķ���ֵ����ΪFALSE��,
 *           ���������ķ���ֵ����ΪTRUE.
 *
 * ����˵��: Ϊ���ܹ���ͳһ�ķ�ʽ���ø����ܺ���, ����Щ���ܺ�����ԭ����Ϊ
 *           һ��, ���޲����ҷ���ֵΪBOOL. ����ֵΪFALSEʱ, ������������.
 */
BOOL LoadData()
{
    int Re = 0;

    Re = CreatList(&gp_head);
    gc_sys_state |= Re;
    gc_sys_state &= ~(4 + 8 + 16 - Re);
    if (gc_sys_state < ( 4 | 8 | 16))
    {  /*���ݼ�����ʾ��Ϣ*/
        printf("\nϵͳ�������ݲ�����!\n");
        printf("\n�����������...\n");
        getch();

    }


    return TRUE;
}


/**
 * ��������: CreatList
 * ��������: �������ļ���ȡ��������, ����ŵ���������ʮ��������.
 * �������: ��
 * �������: phead ����ͷָ��ĵ�ַ, ����������������ʮ����.
 * �� �� ֵ: int����ֵ, ��ʾ�����������.
 *           0  ����, ������
 *           4  �Ѽ�������¥��Ϣ���ݣ���ѧ��������Ϣ�ͽɷ���Ϣ����
 *           12 �Ѽ�������¥��Ϣ��ѧ��������Ϣ���ݣ��޽ɷ���Ϣ����
 *           28 ����������ݶ��Ѽ���
 *
 * ����˵��:
 */
int CreatList(SCH_NODE **phead)
{
    SCH_NODE *hd = NULL, *pSchNode, tmp1;
    TEAM_NODE *pTeamNode, tmp2;
    SCIPRJ_NODE *pSciprjNode, tmp3;
    FILE *pFile;
    int find;
    int re = 0;

    char dir_current[100];//�������浱ǰ�Ĺ���Ŀ¼
    char dir_togo[100];//������� Ҫ���ĳɵ��µ�Ŀ¼ �ĵ�ַ�ַ���
    char DataDir[7]="\\data";//��������ļ�����һ��Ŀ¼

    getcwd(dir_current,sizeof(dir_current));//��ȡ��ǰ����Ŀ¼
    getcwd(dir_togo,sizeof(dir_togo));//�ٴλ�ȡ��ǰ����Ŀ¼

    strcat(dir_togo,DataDir);//�ڵ�ǰ������ַ֮�����\data���������ļ�������Ŀ¼
    AddBackslash(dir_togo);//������·���ַ����������еĵ��� \ ���\\  �Ա㵱���ļ����ַ�����create�Ⱥ�������ʵ��ʱ \\ ת��� ��\��
    AddBackslash(dir_current);//������·���ַ����������еĵ��� \ ���\\  �Ա㵱���ļ����ַ�����create�Ⱥ�������ʵ��ʱ \\ ת��� ��\��

    chdir(dir_togo);//���ĵ�ǰ����Ŀ¼Ϊ�����ļ������ڵ�Ŀ¼���Ա�����ĳ��������Ŀ¼�� ������������ļ����е������ļ�



    if ((pFile = fopen(gp_sch_info_filename, "rb")) == NULL)
    {
        printf("Ժϵ��Ϣ�����ļ���ʧ��!\n");
        return re;
    }
    printf("Ժϵ��Ϣ�����ļ��򿪳ɹ�!\n");

    /*�������ļ��ж�Ժϵ��Ϣ���ݣ������Ժ���ȳ���ʽ������������*/
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
        printf("Ժϵ��Ϣ�����ļ�����ʧ��!\n");
        return re;
    }
    printf("Ժϵ��Ϣ�����ļ����سɹ�!\n");
    *phead = hd;
    re += 4;

    if ((pFile = fopen(gp_team_info_filename, "rb")) == NULL)
    {
        printf("�����Ŷӻ�����Ϣ�����ļ���ʧ��!\n");
        return re;
    }
    printf("�����Ŷӻ�����Ϣ�����ļ��򿪳ɹ�!\n");
    re += 8;

    /*�������ļ��ж�ȡ�����Ŷӻ�����Ϣ���ݣ�����������Ӧ���Ŀ����Ŷӻ�����Ϣ֧����*/
    while (fread(&tmp2, sizeof(TEAM_NODE), 1, pFile) == 1)
    {
        /*������㣬��Ŵ������ļ��ж����Ŀ����Ŷӻ�����Ϣ*/
        pTeamNode = (TEAM_NODE *)malloc(sizeof(TEAM_NODE));
        *pTeamNode = tmp2;
        pTeamNode->snext = NULL;

        /*�������ϲ��Ҹÿ����Ŷ�����Ժϵ��Ӧ���������*/
        pSchNode = hd;
        while (pSchNode != NULL
               && strcmp(pSchNode->sch_name, pTeamNode->sch) != 0)
        {
            pSchNode = pSchNode->next;
        }
        if (pSchNode != NULL) /*����ҵ����򽫽���Ժ���ȳ���ʽ��������Ŷ���Ϣ֧��*/
        {
            pTeamNode->next = pSchNode->tnext;
            pSchNode->tnext = pTeamNode;
        }
        else  /*���δ�ҵ������ͷ������������ڴ�ռ�*/
        {
            free(pTeamNode);
        }
    }
    fclose(pFile);

    if ((pFile = fopen(gp_sciprj_info_filename, "rb")) == NULL)
    {
        printf("������Ŀ��Ϣ�����ļ���ʧ��!\n");
        return re;
    }
    printf("������Ŀ��Ϣ�����ļ��򿪳ɹ�!\n");
    re += 16;

    /*�������ļ��ж�ȡ������Ŀ��Ϣ���ݣ���������Ŷӻ�����Ϣ֧����Ӧ���Ŀ�����Ŀ֧����*/
    while (fread(&tmp3, sizeof(SCIPRJ_NODE), 1, pFile) == 1)
    {
        /*������㣬��Ŵ������ļ��ж����Ŀ�����Ŀ�ɷ���Ϣ*/
        pSciprjNode = (SCIPRJ_NODE *)malloc(sizeof(SCIPRJ_NODE));
        *pSciprjNode = tmp3;

        /*�����Ŷ���Ϣ֧���϶�Ӧ�Ŷ���Ϣ���*/
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
        if (find)  /*����ҵ����򽫽���Ժ���ȳ���ʽ���������Ŀ��Ϣ֧����*/
        {
            pSciprjNode->next = pTeamNode->snext;
            pTeamNode->snext = pSciprjNode;
        }
        else /*���δ�ҵ������ͷ������������ڴ�ռ�*/
        {
            free(pSciprjNode);
        }
    }
    fclose(pFile);


    chdir(dir_current);//��Ŀ¼����Ϊԭ���Ĺ���Ŀ¼




    return re;
}



/**
 * ��������: SaveSysData
 * ��������: ���������������.
 * �������: void
 * �������:
 * �� �� ֵ: BOOL����, ����ΪTRUE
 *
 * ����˵��:
 */
BOOL SaveSysData(void) //�����ϲ�һ������Ϊ�ҵ������ǣ��������Ǵ�ȫ�ֱ���gp_head��ʼ���棬��˾Ͳ����β��ˣ�
{

    SCH_NODE *psch_node;
    TEAM_NODE *pteam_node;
    SCIPRJ_NODE *psciprj_node;
    FILE *pfout;
    //int handle;
    char dir_current[100];//�������浱ǰ�Ĺ���Ŀ¼
    char dir_togo[100];//������� Ҫ���ĳɵ��µ�Ŀ¼ �ĵ�ַ�ַ���
    char DataDir[7]="\\data";//��������ļ�����һ��Ŀ¼

    getcwd(dir_current,sizeof(dir_current));//��ȡ��ǰ����Ŀ¼
    getcwd(dir_togo,sizeof(dir_togo));//�ٴλ�ȡ��ǰ����Ŀ¼

    strcat(dir_togo,DataDir);//�ڵ�ǰ������ַ֮�����\data���������ļ�������Ŀ¼
    AddBackslash(dir_togo);//������·���ַ����������еĵ��� \ ���\\  �Ա㵱���ļ����ַ�����create�Ⱥ�������ʵ��ʱ \\ ת��� ��\��
    AddBackslash(dir_current);//������·���ַ����������еĵ��� \ ���\\  �Ա㵱���ļ����ַ�����create�Ⱥ�������ʵ��ʱ \\ ת��� ��\��

    chdir(dir_togo);//���ĵ�ǰ����Ŀ¼Ϊ�����ļ������ڵ�Ŀ¼���Ա�����ĳ��������Ŀ¼�� ������������ļ����е������ļ�

    pfout=fopen(gp_sch_info_filename,"wb");  //����Ժϵ������Ϣ
    for(psch_node=gp_head;psch_node!=NULL;psch_node=psch_node->next)
    {
        fwrite(psch_node,sizeof(SCH_NODE),1,pfout);

    }

    fclose(pfout);


    pfout=fopen(gp_team_info_filename,"wb");//��������Ŷӻ�����Ϣ
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

    //���������Ŀ������Ϣ
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

    chdir(dir_current);//��Ŀ¼����Ϊԭ���Ĺ���Ŀ¼

    fclose(pfout);


    return TRUE;
}

/**
 * ��������: BackupSysData
 * ��������: ����������ݱ��ݵ�һ�������ļ�.
 * �������: hd ����ͷ���ָ��
 *           filename �����ļ���
 * �������:
 * �� �� ֵ: BOOL����, ����ΪTRUE
 *
 * ����˵��:
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
    /*����ʮ�������ֱ�ͳ�����ֻ�����Ϣ�ļ�¼����*/
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

        handle=open(filename,O_CREAT|O_BINARY|O_RDWR ,S_IREAD|S_IWRITE);//ע����O_RDWR��ʽ��ʱ��Ҫƥ���дȨ��S_IREAD|S_IWRITE,����û��S_IREAD|S_IWRITEҲ��Ĭ���У���ΪO_RDWR
    }

//S_IREAD|S_IWRITE
    /*��������������ݵļ�¼����*/
    write(handle, (char*)&sch_node_num, sizeof(sch_node_num)  );
    write(handle, (char*)&team_node_num, sizeof(team_node_num)  );
    write(handle, (char*)&sciprj_node_num, sizeof(sciprj_node_num)  );

    for(psch_node=hd; psch_node!=NULL; psch_node=psch_node->next)
    {
        /*����Ժϵ������Ϣ*/
        write(handle, (char*)psch_node, sizeof(SCH_NODE));
    }

    for(psch_node=hd; psch_node!=NULL; psch_node=psch_node->next)
    {
        /*��������Ŷӻ�����Ϣ*/
        pteam_node=psch_node->tnext;
        while(pteam_node!=NULL)
        {
            write(handle, (char*)pteam_node, sizeof(TEAM_NODE));
            pteam_node=pteam_node->next;
        }

    }

    for(psch_node=hd; psch_node!=NULL; psch_node=psch_node->next)
    {
        /*���������Ŀ������Ϣ*/
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
 * ��������: RestoreSysData
 * ��������: ��ָ�������ļ��лָ�ϵͳ�����������.
 * �������: phead ����ͷ���ָ��ĵ�ַ
 *           filename ��ű������ݵ������ļ���
 * �������:
 * �� �� ֵ: BOOL����, ����ΪTRUE
 *
 * ����˵��:
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
       char *plabel_name[] = {"������ı����ļ������ڣ�",
                           "���ݻָ�ʧ��",
                           "ȷ��"
                          };

       ShowModule(plabel_name, 3);


       return FALSE;
   }

   /*��ȡ���ֻ�����Ϣ�ļ�¼����*/
   read(handle, (char*)&sch_node_num, sizeof(sch_node_num));
   read(handle, (char*)&team_node_num, sizeof(team_node_num));
   read(handle, (char*)&sciprj_node_num, sizeof(sciprj_node_num));

   /*��ȡԺϵ������Ϣ������ʮ������*/
   for(ulloop=1; ulloop<=sch_node_num; ulloop++)
   {
       psch_node=(SCH_NODE*)malloc(sizeof(SCH_NODE));
       read(handle, (char*)psch_node, sizeof(SCH_NODE));
       psch_node->tnext=NULL;//��������ָ��
       psch_node->next=hd;
       hd=psch_node;
   }
   *phead=hd;

   /*��ȡ�����Ŷӻ�����Ϣ�����������Ŷ���Ϣ֧��*/
   for(ulloop=1; ulloop<=team_node_num; ulloop++)
   {
       pteam_node=(TEAM_NODE*)malloc(sizeof(TEAM_NODE));
       read(handle, (char*)pteam_node, sizeof(TEAM_NODE));
       pteam_node->snext=NULL;//�������� ָ��
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


    /*��ȡ������Ŀ������Ϣ������������Ŀ������Ϣ֧��*/
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


    char *plabel_name[] = {"���������Ѿ��ָ����ڴ棡",
                           "�����ļ�ѡ����ѡ�񱣴浽�����ļ�",
                           "ȷ��"
                          };

       ShowModule(plabel_name, 3);

       return TRUE;
}

