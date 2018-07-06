/*-----------------------------------------------------------------------
 *���ߣ���꯺�
 *ѧ�ţ�20170060220
 *רҵ��17������2
 *����ʱ�䣺2018/06/27
 *����޸�ʱ�䣺2018/07/08
 *�ļ�����������Ӣ�������ֵ�
------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#define _CRT_SECURE_NO_WARNINGS

//getch()����Ҫ�õ�ͷ�ļ�conio.h
//_CRT_SECURE_NO_WARNINGS:Ԥ��ʱ����,���԰�ȫ���

#define WORDNUM 30
#define MEANNUM 30

//��������
struct content
{
    //����Ӣ�ĳ���
    char word[WORDNUM+1];
    //�������ĳ���
    char mean[MEANNUM+1];
	//���õ��ʴ��Գ���
	char format[WORDNUM+1];
};

 //����
struct listNode
{
    //�����򣬴������
    struct content data;
    //ָ����һ������ڵ�
    struct listNode *next;
};

/*************************************************************************
 *����������������
*************************************************************************/
void AddContent(struct listNode *list);
void SearchContent(struct listNode *list);
void FuzzySearch(struct listNode *list);
void wordFormation(struct listNode *list);
void wordFormation1(struct listNode *list,int choose);
void EditContent(struct listNode *list);
void DeleteContent(struct listNode *list);
void DisplayAll(struct listNode *list);
struct listNode *ExistOrNot(struct listNode *list,char *inputWord);
void InsertList(struct listNode *list,struct listNode *insert);
void FreeList(struct listNode *list);
void DisplayHead();
void DisplayOne(struct listNode *display);
void DisplayMenu();
void Goodbye(double start,double finish);
void SaveContent(struct listNode *list);
void ReadContent(struct listNode *list);
int Password();

/*************************************************************************
 *��������AddContent
 *��Ӵ�������
*************************************************************************/
void AddContent(struct listNode *list)
{
	//���������ṹ������������Ĵ�����Ϣ
    struct content input;
	//��������ṹ���ж�����ӵĵ����Ƿ��Ѿ�����
    struct listNode *judge;
	//��������ṹ�帨���������ݰ�˳�����list����
    struct listNode *add;

	//�����д������
	fflush(stdin);

	//���ô����ṹ�������������
    printf("������һ��Ӣ�ĵ��ʣ�");
    scanf("%s",&input.word);
	
    printf("���������Ӣ�ĵ��ʵĽ��ͣ�");
	scanf("%s", &input.mean);

	printf("���������Ӣ�ĵ��ʵĴ��ԣ�");
	scanf("%s", &input.format);

    //�ж���ӵĵ����Ƿ��Ѿ����ڣ�����������ʾ�ô�����������������Ӹô�����
    if((judge=ExistOrNot(list,input.word))==NULL)
    {
		//�½�����ṹ��add
        add=(struct listNode *)malloc(sizeof(struct listNode));
        if(add != NULL)
        {
            //�Ѵ������ݸ��Ƶ�add����ṹ�嵱��
            strcpy((add->data).word,input.word);
            strcpy((add->data).mean,input.mean);
			strcpy((add->data).format,input.format);
            //��add�е�Ӣ�ĵ�������ĸ����ĸ��˳�����list������
            InsertList(list,add);
        }
    }
    else
    {
		//����Ӣ�ĵ����Ѿ���������ʾ���ô����Ѿ����ڡ��������ô�����ʾ����
        printf("�ô����Ѵ���\n");
		//��ӡ��ͷ
        DisplayHead();
		//��ӡһ���ô���
        DisplayOne(judge);
    }
}

/*************************************************************************
 *��������EditContent
 *�޸���ѡ��������
*************************************************************************/
void EditContent(struct listNode *list)
{
	//���������ṹ������µĴ�������
    struct content edit;
	//��������ṹ���ж��ֵ��Ƿ���ڸ�Ӣ�ĵ���
    struct listNode *judge;
	//����һ���ַ���������û������Ӣ�ĵ���
    char editWord[WORDNUM+1];

	//�����д������
	fflush(stdin);
    //����Ҫ�޸ĵĴ�����Ӣ�ĵ���
    printf("������Ҫ�޸ĵ�Ӣ�ĵ��ʣ�");
	scanf("%s", &editWord);

    //�ж���ӵĵ����Ƿ��Ѿ����ڣ����������޸ĸô�����
    if((judge=ExistOrNot(list,editWord))!=NULL)
    {
		//�����д������
        fflush(stdin);
		//�����µ�Ҫ�޸ĵĴ������ݣ����ô����ṹ����մ�������
        printf("������Ҫ�޸ĳɵ�Ӣ�ĵ��ʣ�");
		scanf("%s", &edit.word);
        printf("������Ҫ�޸ĳɵ�Ӣ�ĵ��ʵ����Ľ��ͣ�");
		scanf("%s", &edit.mean);
		printf("������Ҫ�޸ĳɵ�Ӣ�ĵ��ʵĴ��ԣ�");
		scanf("%s", &edit.format);
        //��������ṹ��judge��������
        strcpy((judge->data).word,edit.word);
        strcpy((judge->data).mean,edit.mean);
		strcpy((judge->data).format,edit.format);
    }
    else
    {
		//������������ʾ�������ڸô�����
        printf("�����ڸô���\n");
    }
}

/*************************************************************************
 * ��������SearchContent
 * ��ȷ���Ҵ�������
*************************************************************************/
void SearchContent(struct listNode *list)
{
	//��������ṹ���ж��ֵ��Ƿ���ڸ�Ӣ�ĵ���
    struct listNode *judge;
	//��������ṹ�帨���������ݵ���������
	struct listNode *listNext;
	//����һ���ַ�������ΪҪ������Ӣ�ĵ���
    char searchWord[WORDNUM+1];
	//����һ���ַ�������ΪҪ���������ķ���
	char searchMean[MEANNUM+1];

	//����һ���������ݽ����û��Թ��ܵ�ѡ��
	int choose;

	//���û�ѡ���ʼ��Ϊ0
	choose = 0;
	//�Ѹ�������ṹ���ʼ��Ϊlist����ͷ����һ�����
	listNext = list->next;

	//�������ܲ˵�
	printf("\n");
	printf("____________________________________________________\n");
	printf("|------------------(0)Ӣ�뺺-----------------------|\n");
	printf("|------------------(1)����Ӣ-----------------------|\n");
	printf("|__________________________________________________|\n");
	printf("\n");

	//�����д������
	fflush(stdin);
	//�����û���ѡ��
	printf("�����������������(0-1)��");
	scanf("%d", &choose);

	//���û���ѡ����0-1֮��ķ�Χ����ʾ�û������������������
	while(choose<0||choose>1)
	{
		//�����д������
		fflush(stdin);
		printf("�����������������\n");
		scanf("%d", &choose);
	}

	//�����û�ѡ��ʵ�֣�Ӣ�뺺������Ӣ�Ĺ��ܣ�
	switch (choose)
	{
	case 0:
		//����Ҫ�����Ĵ�����Ӣ�ĵ���
		printf("������Ҫ������Ӣ�ĵ��ʣ�");
		getchar();
		scanf("%s", &searchWord);

		//�ж���ӵĵ����Ƿ��Ѿ����ڣ�����������ʾ�ô���)
		if ((judge = ExistOrNot(list, searchWord)) != NULL)
		{
			printf("|-------------------�����������-------------------|\n");
			//��ӡ��ͷ
			DisplayHead();
			//��ӡһ���ô���
			DisplayOne(judge);
		}
		else
		{
			//����������������ʾ�������ڸô�����
			printf("�����ڸô���\n");
		}
		break;
	case 1:
		//����Ҫ�����Ĵ���������
		printf("������Ҫ���������ģ�");
		getchar();
		scanf("%s", &searchMean);

		//�ж���ӵĵ����Ƿ��Ѿ����ڣ�����������ʾ�ô���)
		while (listNext != NULL)
		{
			if (strcmp((listNext->data).mean,searchMean)==0)
			{
				printf("|-------------------�����������-------------------|\n");
				//��ӡ��ͷ
				DisplayHead();
				//��ӡһ���ô���
				DisplayOne(listNext);
				break;
			}
			//��������ֱ��listNext=NULL
			listNext = listNext->next;
		}
		break;
	default :
		//��ʾ�û��������
		printf("�����������������\n");
	}
}

/*************************************************************************
 * ��������FuzzySearch
 * ģ�����Ҵ�������
*************************************************************************/
void FuzzySearch(struct listNode *list)
{
	//��������ṹ�帨���������ݵ�ģ����������
	struct listNode *listNext;
	//����һ���ַ������������û������Ӣ���ַ�������
	char input[WORDNUM+1];
	//����һ���ַ������������û������Ӣ���ַ��������ĳ���
	int inputLen;
	//����һ������������Ӣ�ĵ������û�������ַ���������ƥ�����
	int matchNum;

	//�Ѹ�������ṹ���ʼ��Ϊlist����ͷ����һ�����
	listNext=list->next;
	//��ʼ���û������Ӣ���ַ��������ĳ���Ϊ0
	inputLen=0;
	//��ʼ��Ӣ�ĵ������û�������ַ���������ƥ�����Ϊ0
	matchNum=0;
	
	//�����д������
	fflush(stdin);
	//��ʾ�û�����Ӣ�ĵ��ʵĹؼ���
	printf("������Ӣ�ĵ��ʵĹؼ��ʣ�");
	scanf("%s", &input);

	//�����û�����Ӣ�ĵ��ʵĹؼ��ʵĳ���
	inputLen=strlen(input);

	//��ʾ��ͷ
	printf("|-------------------�����������-------------------|\n");
	//��ӡ��ͷ
	DisplayHead();

	while(listNext!=NULL)
	{
		//memcmp�Ƚ�(listNext->data).word��input��ǰinputLen��Ӣ���ַ���ƥ��ȣ�������ǰinput���ַ���ȫƥ��ʱ����ֵΪ0
		matchNum=memcmp((listNext->data).word,input,inputLen);

		//matchNum=0ʱ��ʾ����ǰinput���ַ���ȫƥ��
		if(matchNum==0)
		{
			//��ʾ��input��ͷƥ���һ��Ӣ�ĵ���
			DisplayOne(listNext);
		}
		//��������ֱ��listNext=NULL
		listNext=listNext->next;
	}
}

/*************************************************************************
 * ��������wordFormation
 * �����Է������
*************************************************************************/
void wordFormation(struct listNode *list)
{
	//�������װ���Ӻ���
	void wordFormation1(struct listNode *list, int choose);

	//��������ṹ�帨���������ݵķ��๦��
	struct listNode *listNext;

	//�Ѹ�������ṹ���ʼ��Ϊlist����ͷ����һ�����
	listNext=list->next;

	//��Ӣ�ĵ��ʵĴ������ֻ�������ʼ���û�ѡ��chooseΪN����Ӧ������
	enum {N,V,ADJ,ADV} choose=N;

	//���������Է���Ĺ��ܲ˵�
	printf("\n");
    printf("____________________________________________________\n");
	printf("|-----------------(0)����(n)-----------------------|\n");
	printf("|-----------------(1)����(v)-----------------------|\n");
	printf("|-----------------(2)���ݴ�(adj)-------------------|\n");
	printf("|-----------------(3)���ݴ�(adv)-------------------|\n");
	printf("|__________________________________________________|\n");
    printf("\n");

	//�����д������
	fflush(stdin);
	//��ʾ�û��������ֶ�ӦӢ�ĵ��ʵĴ���
	printf("���������ֶ�ӦӢ�ĵ��ʵĴ���:");
	scanf("%d",&choose);

	//�û��������ֲ��ڣ�0-3����ʱ��ʾ�û������������������
	while(choose<N||choose>ADV)
	{
		//�����д������
		fflush(stdin);
		printf("���������������������(0-3)��");
        scanf("%d",&choose);
	}

	//���û����������ʵ�ֲ�ͬ�Ĺ���
	switch(choose)
	{
	case N:
		//��ʾ���д���Ϊ���ʵĴ���
		wordFormation1(list,N);
		break;
	case V:
		//��ʾ���д���Ϊ���ʵĴ���
		wordFormation1(list,V);
		break;
	case ADJ:
		//��ʾ���д���Ϊ���ݴʵĴ���
		wordFormation1(list,ADJ);
		break;
	case ADV:
		//��ʾ���д���Ϊ���ʵĴ���
		wordFormation1(list,ADV);
		break;
	default :
		//�û��������ֲ��ڣ�0-3����ʱ��ʾ�û������������������
		printf("�������,����������:\n");
		break;
	}
}

/*************************************************************************
 * ��������wordFormation1
 * �����Է����������װ������
 * ���պ�����wordFormation�е�choose����
*************************************************************************/
void wordFormation1(struct listNode *list,int choose)
{
	//�����ַ�ָ��������û�ѡ����Ż�
	char *formation;

	//��������ṹ�帨���������ݵķ��๦��
	struct listNode *listNext;

	//ͳ��ĳ���Ե�Ӣ�ĵ��ʵ�����
	int num;

	//�Ѹ�������ṹ���ʼ��Ϊlist����ͷ����һ�����
	listNext=list->next;

	//ͳ�Ƹ�����ʼ��Ϊ0
	num=0;

	//���û�ѡ����Ż�
	switch(choose)
	{
	case 0:
		//strcpy(formation,"n");
		formation = "n";
		break;
	case 1:
		//strcpy(formation,"v");
		formation = "v";
		break;
	case 2:
		//strcpy(formation,"adj");
		formation = "adj";
		break;
	case 3:
		//strcpy(formation,"adv");
		formation = "adv";
		break;
	default :
		//�û��������ֲ��ڣ�0-3����ʱ��ʾ�û������������������
		printf("�������,����������:\n");
		break;
	}

	printf("|-------------------�����������-------------------|\n");
	//��ʾ��ͷ
	DisplayHead();

	while(listNext!=NULL)
	{
		if(strcmp((listNext->data).format,formation)==0)
		{
			//��ʾһ���ô��ԵĴ���
			DisplayOne(listNext);
			//ͳ�Ƹô��Դ����ĸ���
			num++;
		}
		//��������ֱ��listNext=NULL
		listNext=listNext->next;
	}
	//��ʾͳ�Ƹô��ԵĴ����ĸ���
	printf("|-----------�ֵ��Ѽ�¼(%d)������Ϊ%s����-----------|\n",num,formation);
}

/*************************************************************************
 * ��������DeleteContent
 * ɾ����ѡ��������
*************************************************************************/
void DeleteContent(struct listNode *list)
{
	//��������ṹ��1�����������ݵ�ɾ������
    struct listNode *listHead;
	//��������ṹ��2�����������ݵ�ɾ������
    struct listNode *listNext;
	//����һ���ַ��������Ҫɾ����Ӣ�ĵ���
    char deleteWord[WORDNUM+1];
	//����һ��������Ϊɾ����ʶ
	int flag;

	//�Ѹ�������ṹ��1��ʼ��Ϊlist����ͷ
    listHead=list;
	//�Ѹ�������ṹ��2��ʼ��Ϊlist����ͷ����һ�����
    listNext=list->next;
	//��ʼ��ɾ����ʶΪ0
	flag=0;

	//�����д������
	fflush(stdin);
    //����Ҫɾ���Ĵ�����Ӣ�ĵ���
    printf("������Ҫɾ����Ӣ�ĵ��ʣ�");
	scanf("%s", &deleteWord);

    while(listNext!=NULL)
    {
		//�ж��ֵ����Ƿ����Ҫɾ����Ӣ�ĵ���
        if(strcmp((listNext->data).word,deleteWord)==0)
        {
			//�Ѹ�������ṹ��1����һ�����ָ��������ṹ��2����һ�����
            listHead->next=listNext->next;
			//�ͷŸ�������ṹ��2
            free(listNext);
			//ɾ����ʶ��Ϊ1
			flag=1;
			//��ӡɾ���ɹ�
			printf("ɾ���ɹ�\n");
            return;
        }
		//�Ѹ�������ṹ��2��ֵ���Ѹ�������ṹ��1
        listHead=listNext;
		//��������ֱ��listNext=NULL
        listNext=listNext->next;
    }
	//�ж�ɾ����ʶ��Ϊ0���ʾɾ�����ɹ�����ʾ�����ڸõ���
	if(flag==0)
	{
		printf("�����ڸõ���\n");
	}
}

/*************************************************************************
 *��������DisplayAll
 *��ʾ���д���
*************************************************************************/
void DisplayAll(struct listNode *list)
{
	//��������ṹ��1�����������ݵ���ʾ����
	struct listNode *listNext;
	//��������ṹ��2�����������ݵ���ʾ����
	struct listNode *listHead;
	//����һ���ַ�������Ϊ����Ӣ�ĵ���
	char tmpWord[WORDNUM+1];
	//����һ���ַ�������Ϊ�������Ľ���
	char tmpMean[MEANNUM+1];
	//����һ���ַ�������Ϊ�������ʴ���
	char tmpFormat[WORDNUM+1];

	//����һ��������Ϊͳ�Ƶ��ʵ�����
    int wordNum;

	//�Ѹ�������ṹ��1��ʼ��Ϊlist����ͷ����һ�����
	listNext=list->next;
	//�Ѹ�������ṹ��2��ʼ��Ϊlist����ͷ
	listHead=list;
	//ͳ�Ƶ��ʵ�������ʼ��Ϊ0
    wordNum=0;

	//����ð�ݷ��������д���������ĸ��˳������
	while(listHead->next!=NULL)
	{
		while(listHead->next->next!=NULL)
		{
			if(strcmp((listHead->next->data).word,(listHead->next->next->data).word)>0)
			{
				strcpy(tmpWord,(listHead->next->data).word);
				strcpy(tmpMean,(listHead->next->data).mean);
				strcpy(tmpFormat,(listHead->next->data).format);
				strcpy((listHead->next->data).word,(listHead->next->next->data).word);
				strcpy((listHead->next->data).mean,(listHead->next->next->data).mean);
				strcpy((listHead->next->data).format,(listHead->next->next->data).format);
				strcpy((listHead->next->next->data).word,tmpWord);
				strcpy((listHead->next->next->data).mean,tmpMean);
				strcpy((listHead->next->next->data).format,tmpFormat);
			}
			listHead=listHead->next;
		}
		listHead=listHead->next;
	}

    //��ʾ���м�¼�Ĵ���
    printf("|----------------��ʾ���м�¼�Ĵ���----------------|\n");
	//��ʾ��ͷ
    DisplayHead();

	while(listNext!=NULL)
	{
		//��ʾһ������
		DisplayOne(listNext);
		//ͳ�����д����ĸ���
		wordNum++;
		//��������ֱ��listNext=NULL
		listNext=listNext->next;
	}
	//��ʾͳ�Ƶ����д����ĸ���
    printf("|----------------�ֵ��Ѽ�¼(%d)������---------------|\n",wordNum);
}

/*************************************************************************
 *��������ExistOrNot
 *�жϴ����Ƿ��Ѿ�����
 *��Ҫ��Ӧ������inputWord��ֵ
*************************************************************************/
struct listNode *ExistOrNot(struct listNode *list,char *inputWord)
{
	//��������ṹ�帨���������ݵ��ж��Ƿ���ڵĹ���
    struct listNode *listNext;
	//�Ѹ�������ṹ���ʼ��Ϊlist����ͷ����һ�����
	listNext=list->next;

    while(listNext!=NULL)
    {
		//�Ƚ�inputWord��(listNext->data).word�Ƿ���ͬ�����жϸõ����Ƿ�������ֵ���
        if(strcmp((listNext->data).word,inputWord)==0)
        {
			//������������������ṹ��
            return listNext;
        }
		//��������ֱ��listNext=NULL
        listNext=listNext->next;
    }
	//���õ��ʲ������ֵ��ھͷ���NULL
    return NULL;
}

/*************************************************************************
 *��������InsertList
 *������ĸ�������˳��������
 *��Ҫ��Ӧ������insert����ṹ���ֵ
*************************************************************************/
void InsertList(struct listNode *list,struct listNode *insert)
{
	//��������ṹ�帨���������ݵİ�˳�����Ĺ���
    struct listNode *listHead;
	//�Ѹ�������ṹ���ʼ��Ϊlist����ͷ
    listHead=list;

    //���������ǰһ���������ʱȸô������ʵ�ASCIIС����һ���������ʱȸô������ʵ�ASCII��
    while(listHead->next!=NULL&&strcmp((listHead->next->data).word,(insert->data).word)<0)
    {
		//��������ṹ��ָ������һ�����
        listHead=listHead->next;
    }
	//insert����ṹ�����һ�����ָ��������ṹ�����һ�����
    insert->next=listHead->next;
	//��������ṹ�����һ�����ָ��insert����ṹ��
    listHead->next=insert;
}

/*************************************************************************
 *��������FreeList
 *�ͷ�����ռ�
*************************************************************************/
void FreeList(struct listNode *list)
{
	//��������ṹ�帨���������ݵ���������ṹ��Ĺ���
    struct listNode *listHead;
	//�Ѹ�������ṹ���ʼ��Ϊlist����ͷ
    listHead=list;

    //����ͷ�����ռ�
    while(listHead->next!=NULL)
    {
		//��������ṹ��ָ������һ�����
        listHead=listHead->next;
		//�ͷ�list����ṹ��
        free(list);
		//list����ṹ��ָ��������ṹ��
        list=listHead;
    }
	//�ͷŸ�������ṹ��
    free(listHead);
}

/*************************************************************************
 *��������DisplayHead
 *��ʾ��ͷ
*************************************************************************/
void DisplayHead()
{
	//��ʾ��ͷ
	printf("%10s %10s %10s\n","Ӣ�ĵ���","���Ľ���","���ʴ���");
}

/*************************************************************************
 *��������DisplayOne
 *��ʾһ������
*************************************************************************/
void DisplayOne(struct listNode *display)
{
	//��ʾһ������������
	printf("%10s %10s %10s\n",(display->data).word,(display->data).mean,(display->data).format);
}

/*************************************************************************
 *��������SaveContent
 *�������д���
*************************************************************************/
void SaveContent(struct listNode *list)
{
	//��������ṹ�帨���������ݵı���Ĺ���
    struct listNode *listNext;
	//�Ѹ�������ṹ���ʼ��Ϊlist����ͷ����һ�����
    listNext=list->next;

	//�Զ���saveFile��д��ķ�ʽ��dictionary.txt
    FILE *saveFile = fopen("dictionary.txt","w");
	//��saveFile�������ɹ�����������dictionary.txt�ļ�
    if(saveFile==NULL)
    {
        printf("������dictionary.txt�ļ�\n");
        return;
    }
    else
    {
        //�����ͷ
        //fprintf(saveFile,"%10s %10s %10s\n","Ӣ�ĵ���","���Ľ���","���ʴ���");
        //��������
        while(listNext!=NULL)
        {
			//����ʽ�ɴ�������д��dictionary.txt�ļ�
			fprintf(saveFile,"%10s %10s %10s\n",(listNext->data).word,(listNext->data).mean,(listNext->data).format);
			//��������ֱ��listNext=NULL
            listNext=listNext->next;
        }
		//��ʾ���д����ѱ����ڵ�ǰĿ¼��dictionary.txt��
        printf("���д����ѱ����ڵ�ǰĿ¼��dictionary.txt��");
		//�ر�saveFile
        fclose(saveFile);
    }
}

/*************************************************************************
 *��������ReadContent
 *��ȡ���д���
**************************************************************************/
void ReadContent(struct listNode *list)
{
	//��������ṹ�帨���������ݵĶ�ȡ�Ĺ���
	struct listNode *add;

	//�ͷ��Ѵ�������
	FreeList(list);
	//���´�������ṹ��
	list=(struct listNode *)malloc(sizeof(struct listNode));
	if(list!=NULL)
	{
		//��list����һ�����ָ��NULL
		list->next=NULL;
	}

	//����һ��������Ϊͳ�ƴ�������
	int num;
	//��ʼ��ͳ������Ϊ0
	num=0;

	//�Զ���readFile�Զ�ȡ�ķ�ʽ��dictionary.txt
	FILE *readFile = fopen("dictionary.txt","r");
	//��readFile�������ɹ�����������dictionary.txt�ļ�
	if(readFile==NULL)
    {
        printf("������dictionary.txt�ļ�\n");
        return;
    }
	else
	{
		//����ȡ�ļ���Ϊ�ļ�������
		while(!feof(readFile))
		{
			//��������ṹ�帨�����ݵĶ�ȡ����
			add=(struct listNode *)malloc(sizeof(struct listNode));
			if(add!=NULL)
			{
				//numͳ���ļ�����ֵ��add�����ݸ���
				num=fscanf(readFile,"%10s %10s %10s\n",(add->data).word,(add->data).mean,(add->data).format);
				//����ֵ��add�����ݸ���С��3������ѭ��
				if(num<3)
				{
					break;
				}
				//Ӣ�ĵ�������ĸ����ĸ���˳���add�����ݲ��뵽list��
				InsertList(list,add);
			}
		}
		//��ӡ��ȡ�ɹ�
		printf("dictionary.txt�е����д����ѱ������ֵ���");
	}
}


/*************************************************************************
 *��������Password
 *�������
**************************************************************************/
int Password()
{
	//����ԭʼ����
	char password[]="123456";
	//���������־
	int flag;
	//����һ���ַ�������Ϊ�û����������
	char getWord[WORDNUM+1];

	//Ϊʵ��������������ʾ"*"�ŵĹ��ܣ�����һ�����ν���ÿһ�������ASCIIֵ������һ��������Ϊ�û���������ĳ���
	int oneWord;
	int len;

	//��ʼ�������־Ϊ0
	flag=0;
	//ÿһ�������ASCIIֵ��ʼ��Ϊ0
	oneWord=0;
	//�û���������ĳ��ȳ�ʼ��Ϊ0
	len=0;
    
	//Ҫ���û���������
	printf("���������룺");
	getchar();

	//ASCII��13Ϊ�س���������������ַ���Ϊ�س���
    while ((oneWord = getch()) != 13)
    {
		//��ÿһ��������ַ�ASCIIֵת��Ϊ�ַ����ͣ�������len�����������뱣����getWord��
        getWord[len++] = oneWord;
		//ÿһ�������á�*���Ŵ���
        putc('*', stdout);
    }
	//���û�������������һλ��ֵΪ0
    getWord[len] = 0;
	printf("\n");

	//�ж������Ƿ���ȷ
	if(strcmp(getWord,password)==0)
	{
		//��������ȷ�������ʶΪ1
		flag=1;
	}
	else
	{
		//��ʾ���벻��ȷ
		printf("�����������\n");
		flag=0;
	}
	//����flag��ֵΪ��Ӧ��������
	return flag;
}

/*************************************************************************
 *��������Goodbye
 *��лʹ��
*************************************************************************/
void Goodbye(double start,double finish)
{
	//��ʾGoodBye����
    printf("\n");
    printf("____________________________________________________\n");
    printf("|--------------------------------------------------|\n");
    printf("|---------------��лʹ��Ӣ�������ֵ�---------------|\n");
    printf("|---------------���ߣ���꯺�-----------------------|\n");
    printf("|---------------ѧ�ţ�20170060220------------------|\n");
    printf("|---------------רҵ��17������2--------------------|\n");
    printf("|---------------����ʱ�䣺2018/06/27---------------|\n");
    printf("|---------------����޸�ʱ�䣺2018/07/08-----------|\n");
    printf("|---------------�ļ�����������Ӣ�������ֵ�---------|\n");
	printf("|---------------ʹ��ʱ�䣺%lf ��--------------|\n",(finish - start) / CLOCKS_PER_SEC);
    printf("|__________________________________________________|\n");
    printf("\n");
}

/*************************************************************************
 *��������DisplayMenu
 *��ʾ�˵�
*************************************************************************/
void DisplayMenu()
{
	//��ʾ�˵�����
    printf("\n");
    printf("____________________________________________________\n");
    printf("|--------------------------------------------------|\n");
    printf("|---------------��ӭʹ��Ӣ�������ֵ�---------------|\n");
    printf("|---------------�����������������(0-9)------------|\n");
    printf("|---------------(1)��Ӵ���------------------------|\n");
    printf("|---------------(2)��ȷ��������--------------------|\n");
	printf("|---------------(3)ģ����������--------------------|\n");
	printf("|---------------(4)���Է������--------------------|\n");
	printf("|---------------(5)�༭����------------------------|\n");
    printf("|---------------(6)ɾ������------------------------|\n");
    printf("|---------------(7)��ʾ����------------------------|\n");
    printf("|---------------(8)�������------------------------|\n");
	printf("|---------------(9)��ȡ����------------------------|\n");
    printf("|---------------(0)�˳��ֵ�------------------------|\n");
    printf("|__________________________________________________|\n");
    printf("\n");
}

/*************************************************************************
 *��������main
 *������
*************************************************************************/
int main(int argc, char *argv[])
{
	//����һ��˫���ȸ����ͼ�¼ϵͳ��ʼ����ʱ��
	double  start;
	//����һ��˫���ȸ����ͼ�¼ϵͳ��������ʱ��
	double  finish;
	//��������ṹ��Ϊ�Ӻ�������
    struct listNode *dictionary;
	//���ֻ���ʾ���ܣ�����function��ʼ��ΪDISP��Ӧ������
	enum {EXIT,ADD,SEARCH,FUZSER,CLASSIFY,EDIT,DEL,DISP,SAVE,READ} function=DISP;
	//��ȡϵͳ��ʼ����ʱ��
	start=clock();
    //��������ṹ��
    dictionary=(struct listNode *)malloc(sizeof(struct listNode));
    if(dictionary!=NULL)
    {
		//��dictionary��ͷ����һ�����ָ��NULL
        dictionary->next = NULL;
    }

    while(function != EXIT)
    {
		//����һ��������Ϊ�����־
		int flag;

		//�������ʶ��ʼ��Ϊ0
		flag=0;

		//��ʾ�˵�
        DisplayMenu();

        //��ʾ�û�����������������
        printf("\n�����������������(0-9)��");
        scanf("%d",&function);

		//�û��������ֲ��ڣ�0-9����ʱ��ʾ�û������������������
        while(function<EXIT||function>READ)
        {
			printf("���������������������(0-9)��");
            scanf("%d",&function);
        }

        switch(function)
        {
        case ADD:
			//ʵ����Ӵ�������
            AddContent(dictionary);
            break;
        case SEARCH:
			//ʵ��������������
            SearchContent(dictionary);
            break;
		case FUZSER:
			//ʵ��ģ��������������
			FuzzySearch(dictionary);
			break;
		case CLASSIFY:
			//ʵ�ְ����Է����������
			wordFormation(dictionary);
			break;
        case EDIT:
			//��ͨ��������֤��ʵ�ֱ༭��������
			flag=Password();
			if(flag==1)
			{
				EditContent(dictionary);
			}
				break;
        case DEL:
			//��ͨ��������֤��ʵ��ɾ����������
			flag=Password();
			if(flag==1)
            {
				DeleteContent(dictionary);
			}
				break;
        case DISP:
			//ʵ����ʾ��������
            DisplayAll(dictionary);
            break;
        case SAVE:
			//ʵ�ֱ����������
            SaveContent(dictionary);
            break;
		case READ:
			//ʵ�ֶ�ȡ��������
            ReadContent(dictionary);
            break;
        case EXIT:
			//��ȡϵͳ��������ʱ��
			finish=clock();
			//ʵ���˳��ֵ书�ܣ�����ʾGoodBye�Ľ���
            Goodbye(start,finish);
			//�ó���ֹͣ�ȴ����������ʵ���˳�����
			system("pause");
            exit(0);
            break;
        default:
			//�û��������ֲ��ڣ�0-9����ʱ��ʾ�û������������������
            printf("����������������룺");
            break;
        }
    }
	//��������ǰ�ͷŴ���������ṹ��dictionary
    FreeList(dictionary);
}
