/*-----------------------------------------------------------------------
 *作者：罗戬浩
 *学号：20170060220
 *专业：17大数据2
 *创建时间：2018/06/27
 *最后修改时间：2018/07/08
 *文件功能描述：英汉电子字典
------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#define _CRT_SECURE_NO_WARNINGS

//getch()函数要用到头文件conio.h
//_CRT_SECURE_NO_WARNINGS:预编时处理,忽略安全检测

#define WORDNUM 30
#define MEANNUM 30

//数据内容
struct content
{
    //设置英文长度
    char word[WORDNUM+1];
    //设置中文长度
    char mean[MEANNUM+1];
	//设置单词词性长度
	char format[WORDNUM+1];
};

 //链表
struct listNode
{
    //数据域，存放数据
    struct content data;
    //指向下一个链表节点
    struct listNode *next;
};

/*************************************************************************
 *函数名：函数声明
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
 *函数名：AddContent
 *添加词条内容
*************************************************************************/
void AddContent(struct listNode *list)
{
	//创建词条结构体来接受输入的词条信息
    struct content input;
	//创建链表结构体判断所添加的单词是否已经存在
    struct listNode *judge;
	//创建链表结构体辅助词条数据按顺序插入list链表
    struct listNode *add;

	//清除读写缓冲区
	fflush(stdin);

	//利用词条结构体输入词条数据
    printf("请输入一个英文单词：");
    scanf("%s",&input.word);
	
    printf("请输入这个英文单词的解释：");
	scanf("%s", &input.mean);

	printf("请输入这个英文单词的词性：");
	scanf("%s", &input.format);

    //判断添加的单词是否已经存在（若存在则显示该词条，若不存在则添加该词条）
    if((judge=ExistOrNot(list,input.word))==NULL)
    {
		//新建链表结构体add
        add=(struct listNode *)malloc(sizeof(struct listNode));
        if(add != NULL)
        {
            //把词条内容复制到add链表结构体当中
            strcpy((add->data).word,input.word);
            strcpy((add->data).mean,input.mean);
			strcpy((add->data).format,input.format);
            //把add中的英文单词首字母按字母表顺序插入list链表中
            InsertList(list,add);
        }
    }
    else
    {
		//若该英文单词已经存在则显示“该词条已经存在”，并将该词条显示出来
        printf("该词条已存在\n");
		//打印表头
        DisplayHead();
		//打印一个该词条
        DisplayOne(judge);
    }
}

/*************************************************************************
 *函数名：EditContent
 *修改所选词条内容
*************************************************************************/
void EditContent(struct listNode *list)
{
	//创建词条结构体接受新的词条数据
    struct content edit;
	//创建链表结构体判断字典是否存在该英文单词
    struct listNode *judge;
	//定义一个字符数组接受用户输入的英文单词
    char editWord[WORDNUM+1];

	//清除读写缓冲区
	fflush(stdin);
    //输入要修改的词条的英文单词
    printf("请输入要修改的英文单词：");
	scanf("%s", &editWord);

    //判断添加的单词是否已经存在（若存在则修改该词条）
    if((judge=ExistOrNot(list,editWord))!=NULL)
    {
		//清除读写缓冲区
        fflush(stdin);
		//输入新的要修改的词条内容，并用词条结构体接收词条内容
        printf("请输入要修改成的英文单词：");
		scanf("%s", &edit.word);
        printf("请输入要修改成的英文单词的中文解释：");
		scanf("%s", &edit.mean);
		printf("请输入要修改成的英文单词的词性：");
		scanf("%s", &edit.format);
        //利用链表结构体judge复制内容
        strcpy((judge->data).word,edit.word);
        strcpy((judge->data).mean,edit.mean);
		strcpy((judge->data).format,edit.format);
    }
    else
    {
		//若不存在则显示“不存在该词条”
        printf("不存在该词条\n");
    }
}

/*************************************************************************
 * 函数名：SearchContent
 * 精确查找词条内容
*************************************************************************/
void SearchContent(struct listNode *list)
{
	//创建链表结构体判断字典是否存在该英文单词
    struct listNode *judge;
	//创建链表结构体辅助词条数据的搜索功能
	struct listNode *listNext;
	//定义一个字符数组作为要搜索的英文单词
    char searchWord[WORDNUM+1];
	//定义一个字符数组作为要搜索的中文翻译
	char searchMean[MEANNUM+1];

	//定义一个整形数据接收用户对功能的选择
	int choose;

	//把用户选择初始化为0
	choose = 0;
	//把辅助链表结构体初始化为list链表头的下一个结点
	listNext = list->next;

	//搜索功能菜单
	printf("\n");
	printf("____________________________________________________\n");
	printf("|------------------(0)英译汉-----------------------|\n");
	printf("|------------------(1)汉译英-----------------------|\n");
	printf("|__________________________________________________|\n");
	printf("\n");

	//清除读写缓冲区
	fflush(stdin);
	//接收用户的选择
	printf("请根据需求输入数字(0-1)：");
	scanf("%d", &choose);

	//当用户的选择在0-1之外的范围则提示用户输入错误，请重新输入
	while(choose<0||choose>1)
	{
		//清除读写缓冲区
		fflush(stdin);
		printf("输入错误，请重新输入\n");
		scanf("%d", &choose);
	}

	//根据用户选择实现（英译汉，汉译英的功能）
	switch (choose)
	{
	case 0:
		//输入要搜索的词条的英文单词
		printf("请输入要搜索的英文单词：");
		getchar();
		scanf("%s", &searchWord);

		//判断添加的单词是否已经存在（若存在则显示该词条)
		if ((judge = ExistOrNot(list, searchWord)) != NULL)
		{
			printf("|-------------------搜索结果如下-------------------|\n");
			//打印表头
			DisplayHead();
			//打印一个该词条
			DisplayOne(judge);
		}
		else
		{
			//若词条不存在则显示“不存在该词条”
			printf("不存在该词条\n");
		}
		break;
	case 1:
		//输入要搜索的词条的中文
		printf("请输入要搜索的中文：");
		getchar();
		scanf("%s", &searchMean);

		//判断添加的单词是否已经存在（若存在则显示该词条)
		while (listNext != NULL)
		{
			if (strcmp((listNext->data).mean,searchMean)==0)
			{
				printf("|-------------------搜索结果如下-------------------|\n");
				//打印表头
				DisplayHead();
				//打印一个该词条
				DisplayOne(listNext);
				break;
			}
			//继续遍历直到listNext=NULL
			listNext = listNext->next;
		}
		break;
	default :
		//提示用户输入错误
		printf("输入错误，请重新输入\n");
	}
}

/*************************************************************************
 * 函数名：FuzzySearch
 * 模糊查找词条内容
*************************************************************************/
void FuzzySearch(struct listNode *list)
{
	//创建链表结构体辅助词条数据的模糊搜索功能
	struct listNode *listNext;
	//定义一个字符数组来接收用户输入的英文字符（串）
	char input[WORDNUM+1];
	//定义一个字符数组来接收用户输入的英文字符（串）的长度
	int inputLen;
	//定义一个整形来接收英文单词与用户输入的字符（串）的匹配个数
	int matchNum;

	//把辅助链表结构体初始化为list链表头的下一个结点
	listNext=list->next;
	//初始化用户输入的英文字符（串）的长度为0
	inputLen=0;
	//初始化英文单词与用户输入的字符（串）的匹配个数为0
	matchNum=0;
	
	//清除读写缓冲区
	fflush(stdin);
	//提示用户输入英文单词的关键词
	printf("请输入英文单词的关键词：");
	scanf("%s", &input);

	//接收用户输入英文单词的关键词的长度
	inputLen=strlen(input);

	//显示表头
	printf("|-------------------搜索结果如下-------------------|\n");
	//打印表头
	DisplayHead();

	while(listNext!=NULL)
	{
		//memcmp比较(listNext->data).word与input的前inputLen个英文字符的匹配度，当两者前input个字符完全匹配时返回值为0
		matchNum=memcmp((listNext->data).word,input,inputLen);

		//matchNum=0时表示两者前input个字符完全匹配
		if(matchNum==0)
		{
			//显示与input开头匹配的一个英文单词
			DisplayOne(listNext);
		}
		//继续遍历直到listNext=NULL
		listNext=listNext->next;
	}
}

/*************************************************************************
 * 函数名：wordFormation
 * 按词性分类词条
*************************************************************************/
void wordFormation(struct listNode *list)
{
	//声明其封装的子函数
	void wordFormation1(struct listNode *list, int choose);

	//创建链表结构体辅助词条数据的分类功能
	struct listNode *listNext;

	//把辅助链表结构体初始化为list链表头的下一个结点
	listNext=list->next;

	//把英文单词的词性数字化，并初始化用户选择choose为N所对应的数字
	enum {N,V,ADJ,ADV} choose=N;

	//词条按词性分类的功能菜单
	printf("\n");
    printf("____________________________________________________\n");
	printf("|-----------------(0)名词(n)-----------------------|\n");
	printf("|-----------------(1)动词(v)-----------------------|\n");
	printf("|-----------------(2)形容词(adj)-------------------|\n");
	printf("|-----------------(3)形容词(adv)-------------------|\n");
	printf("|__________________________________________________|\n");
    printf("\n");

	//清除读写缓冲区
	fflush(stdin);
	//提示用户输入数字对应英文单词的词性
	printf("请输入数字对应英文单词的词性:");
	scanf("%d",&choose);

	//用户输入数字不在（0-3）间时提示用户输入错误，请重新输入
	while(choose<N||choose>ADV)
	{
		//清除读写缓冲区
		fflush(stdin);
		printf("输入错误，请重新输入数字(0-3)：");
        scanf("%d",&choose);
	}

	//按用户输入的数字实现不同的功能
	switch(choose)
	{
	case N:
		//显示所有词性为名词的词条
		wordFormation1(list,N);
		break;
	case V:
		//显示所有词性为动词的词条
		wordFormation1(list,V);
		break;
	case ADJ:
		//显示所有词性为形容词的词条
		wordFormation1(list,ADJ);
		break;
	case ADV:
		//显示所有词性为副词的词条
		wordFormation1(list,ADV);
		break;
	default :
		//用户输入数字不在（0-3）间时提示用户输入错误，请重新输入
		printf("输入错误,请重新输入:\n");
		break;
	}
}

/*************************************************************************
 * 函数名：wordFormation1
 * 按词性分类词条（封装函数）
 * 接收函数：wordFormation中的choose变量
*************************************************************************/
void wordFormation1(struct listNode *list,int choose)
{
	//创建字符指针把上述用户选择符号化
	char *formation;

	//创建链表结构体辅助词条数据的分类功能
	struct listNode *listNext;

	//统计某词性的英文单词的数量
	int num;

	//把辅助链表结构体初始化为list链表头的下一个结点
	listNext=list->next;

	//统计个数初始化为0
	num=0;

	//把用户选择符号化
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
		//用户输入数字不在（0-3）间时提示用户输入错误，请重新输入
		printf("输入错误,请重新输入:\n");
		break;
	}

	printf("|-------------------搜索结果如下-------------------|\n");
	//显示表头
	DisplayHead();

	while(listNext!=NULL)
	{
		if(strcmp((listNext->data).format,formation)==0)
		{
			//显示一个该词性的词条
			DisplayOne(listNext);
			//统计该词性词条的个数
			num++;
		}
		//继续遍历直到listNext=NULL
		listNext=listNext->next;
	}
	//显示统计该词性的词条的个数
	printf("|-----------字典已记录(%d)条词性为%s词条-----------|\n",num,formation);
}

/*************************************************************************
 * 函数名：DeleteContent
 * 删除所选词条内容
*************************************************************************/
void DeleteContent(struct listNode *list)
{
	//创建链表结构体1辅助词条数据的删除功能
    struct listNode *listHead;
	//创建链表结构体2辅助词条数据的删除功能
    struct listNode *listNext;
	//定义一个字符数组接收要删除的英文单词
    char deleteWord[WORDNUM+1];
	//定义一个整形作为删除标识
	int flag;

	//把辅助链表结构体1初始化为list链表头
    listHead=list;
	//把辅助链表结构体2初始化为list链表头的下一个结点
    listNext=list->next;
	//初始化删除标识为0
	flag=0;

	//清除读写缓冲区
	fflush(stdin);
    //输入要删除的词条的英文单词
    printf("请输入要删除的英文单词：");
	scanf("%s", &deleteWord);

    while(listNext!=NULL)
    {
		//判断字典中是否存在要删除的英文单词
        if(strcmp((listNext->data).word,deleteWord)==0)
        {
			//把辅助链表结构体1的下一个结点指向辅助链表结构体2的下一个结点
            listHead->next=listNext->next;
			//释放辅助链表结构体2
            free(listNext);
			//删除标识标为1
			flag=1;
			//打印删除成功
			printf("删除成功\n");
            return;
        }
		//把辅助链表结构体2赋值给把辅助链表结构体1
        listHead=listNext;
		//继续遍历直到listNext=NULL
        listNext=listNext->next;
    }
	//判断删除标识若为0则表示删除不成功，显示不存在该单词
	if(flag==0)
	{
		printf("不存在该单词\n");
	}
}

/*************************************************************************
 *函数名：DisplayAll
 *显示所有词条
*************************************************************************/
void DisplayAll(struct listNode *list)
{
	//创建链表结构体1辅助词条数据的显示功能
	struct listNode *listNext;
	//创建链表结构体2辅助词条数据的显示功能
	struct listNode *listHead;
	//定义一个字符数组作为辅助英文单词
	char tmpWord[WORDNUM+1];
	//定义一个字符数组作为辅助中文解释
	char tmpMean[MEANNUM+1];
	//定义一个字符数组作为辅助单词词性
	char tmpFormat[WORDNUM+1];

	//定义一个整形作为统计单词的数量
    int wordNum;

	//把辅助链表结构体1初始化为list链表头的下一个结点
	listNext=list->next;
	//把辅助链表结构体2初始化为list链表头
	listHead=list;
	//统计单词的数量初始化为0
    wordNum=0;

	//利用冒泡法，把所有词条按照字母表顺序排序
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

    //显示所有记录的词条
    printf("|----------------显示所有记录的词条----------------|\n");
	//显示表头
    DisplayHead();

	while(listNext!=NULL)
	{
		//显示一个词条
		DisplayOne(listNext);
		//统计所有词条的个数
		wordNum++;
		//继续遍历直到listNext=NULL
		listNext=listNext->next;
	}
	//显示统计的所有词条的个数
    printf("|----------------字典已记录(%d)条词条---------------|\n",wordNum);
}

/*************************************************************************
 *函数名：ExistOrNot
 *判断词条是否已经存在
 *需要对应函数传inputWord的值
*************************************************************************/
struct listNode *ExistOrNot(struct listNode *list,char *inputWord)
{
	//创建链表结构体辅助词条数据的判断是否存在的功能
    struct listNode *listNext;
	//把辅助链表结构体初始化为list链表头的下一个结点
	listNext=list->next;

    while(listNext!=NULL)
    {
		//比较inputWord与(listNext->data).word是否相同，即判断该单词是否存在于字典内
        if(strcmp((listNext->data).word,inputWord)==0)
        {
			//返回满足条件的链表结构体
            return listNext;
        }
		//继续遍历直到listNext=NULL
        listNext=listNext->next;
    }
	//若该单词不存在字典内就返回NULL
    return NULL;
}

/*************************************************************************
 *函数名：InsertList
 *按照字母表升序的顺序插入词条
 *需要对应函数传insert链表结构体的值
*************************************************************************/
void InsertList(struct listNode *list,struct listNode *insert)
{
	//创建链表结构体辅助词条数据的按顺序插入的功能
    struct listNode *listHead;
	//把辅助链表结构体初始化为list链表头
    listHead=list;

    //插入词条（前一个词条单词比该词条单词的ASCII小，后一个词条单词比该词条单词的ASCII大）
    while(listHead->next!=NULL&&strcmp((listHead->next->data).word,(insert->data).word)<0)
    {
		//辅助链表结构体指向其下一个结点
        listHead=listHead->next;
    }
	//insert链表结构体的下一个结点指向辅助链表结构体的下一个结点
    insert->next=listHead->next;
	//辅助链表结构体的下一个结点指向insert链表结构体
    listHead->next=insert;
}

/*************************************************************************
 *函数名：FreeList
 *释放链表空间
*************************************************************************/
void FreeList(struct listNode *list)
{
	//创建链表结构体辅助词条数据的清理链表结构体的功能
    struct listNode *listHead;
	//把辅助链表结构体初始化为list链表头
    listHead=list;

    //逐个释放链表空间
    while(listHead->next!=NULL)
    {
		//辅助链表结构体指向其下一个结点
        listHead=listHead->next;
		//释放list链表结构体
        free(list);
		//list链表结构体指向辅助链表结构体
        list=listHead;
    }
	//释放辅助链表结构体
    free(listHead);
}

/*************************************************************************
 *函数名：DisplayHead
 *显示表头
*************************************************************************/
void DisplayHead()
{
	//显示表头
	printf("%10s %10s %10s\n","英文单词","中文解释","单词词性");
}

/*************************************************************************
 *函数名：DisplayOne
 *显示一个词条
*************************************************************************/
void DisplayOne(struct listNode *display)
{
	//显示一个词条的内容
	printf("%10s %10s %10s\n",(display->data).word,(display->data).mean,(display->data).format);
}

/*************************************************************************
 *函数名：SaveContent
 *保存所有词条
*************************************************************************/
void SaveContent(struct listNode *list)
{
	//创建链表结构体辅助词条数据的保存的功能
    struct listNode *listNext;
	//把辅助链表结构体初始化为list链表头的下一个结点
    listNext=list->next;

	//自定义saveFile以写入的方式打开dictionary.txt
    FILE *saveFile = fopen("dictionary.txt","w");
	//当saveFile创建不成功，即不存在dictionary.txt文件
    if(saveFile==NULL)
    {
        printf("不存在dictionary.txt文件\n");
        return;
    }
    else
    {
        //保存表头
        //fprintf(saveFile,"%10s %10s %10s\n","英文单词","中文解释","单词词性");
        //保存数据
        while(listNext!=NULL)
        {
			//按格式吧词条数据写入dictionary.txt文件
			fprintf(saveFile,"%10s %10s %10s\n",(listNext->data).word,(listNext->data).mean,(listNext->data).format);
			//继续遍历直到listNext=NULL
            listNext=listNext->next;
        }
		//提示所有词条已保存在当前目录的dictionary.txt中
        printf("所有词条已保存在当前目录的dictionary.txt中");
		//关闭saveFile
        fclose(saveFile);
    }
}

/*************************************************************************
 *函数名：ReadContent
 *读取所有词条
**************************************************************************/
void ReadContent(struct listNode *list)
{
	//创建链表结构体辅助词条数据的读取的功能
	struct listNode *add;

	//释放已创建链表
	FreeList(list);
	//重新创建链表结构体
	list=(struct listNode *)malloc(sizeof(struct listNode));
	if(list!=NULL)
	{
		//把list的下一个结点指向NULL
		list->next=NULL;
	}

	//定义一个整形作为统计词条数量
	int num;
	//初始化统计数据为0
	num=0;

	//自定义readFile以读取的方式打开dictionary.txt
	FILE *readFile = fopen("dictionary.txt","r");
	//当readFile创建不成功，即不存在dictionary.txt文件
	if(readFile==NULL)
    {
        printf("不存在dictionary.txt文件\n");
        return;
    }
	else
	{
		//当读取文件不为文件结束符
		while(!feof(readFile))
		{
			//创建链表结构体辅助数据的读取功能
			add=(struct listNode *)malloc(sizeof(struct listNode));
			if(add!=NULL)
			{
				//num统计文件所传值到add的数据个数
				num=fscanf(readFile,"%10s %10s %10s\n",(add->data).word,(add->data).mean,(add->data).format);
				//当传值到add的数据个数小于3则跳出循环
				if(num<3)
				{
					break;
				}
				//英文单词首字母按字母表的顺序把add的数据插入到list中
				InsertList(list,add);
			}
		}
		//打印读取成功
		printf("dictionary.txt中的所有词条已保存在字典中");
	}
}


/*************************************************************************
 *函数名：Password
 *程序加密
**************************************************************************/
int Password()
{
	//设置原始密码
	char password[]="123456";
	//设置密码标志
	int flag;
	//定义一个字符数组作为用户输入的密码
	char getWord[WORDNUM+1];

	//为实现输入密码是显示"*"号的功能，定义一个整形接收每一个输入的ASCII值，定义一个整形作为用户输入密码的长度
	int oneWord;
	int len;

	//初始化密码标志为0
	flag=0;
	//每一个输入的ASCII值初始化为0
	oneWord=0;
	//用户输入密码的长度初始化为0
	len=0;
    
	//要求用户输入密码
	printf("请输入密码：");
	getchar();

	//ASCII中13为回车键，即当输入的字符不为回车键
    while ((oneWord = getch()) != 13)
    {
		//把每一个输入的字符ASCII值转化为字符类型，并利用len的自增将密码保存在getWord中
        getWord[len++] = oneWord;
		//每一个输入用“*”号代替
        putc('*', stdout);
    }
	//把用户输入密码的最后一位赋值为0
    getWord[len] = 0;
	printf("\n");

	//判断密码是否正确
	if(strcmp(getWord,password)==0)
	{
		//若密码正确则密码标识为1
		flag=1;
	}
	else
	{
		//提示密码不正确
		printf("输入密码错误\n");
		flag=0;
	}
	//返回flag的值为对应函数利用
	return flag;
}

/*************************************************************************
 *函数名：Goodbye
 *感谢使用
*************************************************************************/
void Goodbye(double start,double finish)
{
	//显示GoodBye界面
    printf("\n");
    printf("____________________________________________________\n");
    printf("|--------------------------------------------------|\n");
    printf("|---------------感谢使用英汉电子字典---------------|\n");
    printf("|---------------作者：罗戬浩-----------------------|\n");
    printf("|---------------学号：20170060220------------------|\n");
    printf("|---------------专业：17大数据2--------------------|\n");
    printf("|---------------创建时间：2018/06/27---------------|\n");
    printf("|---------------最后修改时间：2018/07/08-----------|\n");
    printf("|---------------文件功能描述：英汉电子字典---------|\n");
	printf("|---------------使用时间：%lf 秒--------------|\n",(finish - start) / CLOCKS_PER_SEC);
    printf("|__________________________________________________|\n");
    printf("\n");
}

/*************************************************************************
 *函数名：DisplayMenu
 *显示菜单
*************************************************************************/
void DisplayMenu()
{
	//显示菜单界面
    printf("\n");
    printf("____________________________________________________\n");
    printf("|--------------------------------------------------|\n");
    printf("|---------------欢迎使用英汉电子字典---------------|\n");
    printf("|---------------请根据需求输入数字(0-9)------------|\n");
    printf("|---------------(1)添加词条------------------------|\n");
    printf("|---------------(2)精确搜索词条--------------------|\n");
	printf("|---------------(3)模糊搜索词条--------------------|\n");
	printf("|---------------(4)词性分类词条--------------------|\n");
	printf("|---------------(5)编辑词条------------------------|\n");
    printf("|---------------(6)删除词条------------------------|\n");
    printf("|---------------(7)显示词条------------------------|\n");
    printf("|---------------(8)保存词条------------------------|\n");
	printf("|---------------(9)读取词条------------------------|\n");
    printf("|---------------(0)退出字典------------------------|\n");
    printf("|__________________________________________________|\n");
    printf("\n");
}

/*************************************************************************
 *函数名：main
 *主函数
*************************************************************************/
int main(int argc, char *argv[])
{
	//定义一个双精度浮点型记录系统开始运行时间
	double  start;
	//定义一个双精度浮点型记录系统结束运行时间
	double  finish;
	//创建链表结构体为子函数利用
    struct listNode *dictionary;
	//数字化表示功能，并把function初始化为DISP对应的数字
	enum {EXIT,ADD,SEARCH,FUZSER,CLASSIFY,EDIT,DEL,DISP,SAVE,READ} function=DISP;
	//获取系统开始运行时间
	start=clock();
    //创建链表结构体
    dictionary=(struct listNode *)malloc(sizeof(struct listNode));
    if(dictionary!=NULL)
    {
		//把dictionary的头的下一个结点指向NULL
        dictionary->next = NULL;
    }

    while(function != EXIT)
    {
		//定义一个整形作为密码标志
		int flag;

		//把密码标识初始化为0
		flag=0;

		//显示菜单
        DisplayMenu();

        //提示用户根据需求输入数字
        printf("\n请根据需求输入数字(0-9)：");
        scanf("%d",&function);

		//用户输入数字不在（0-9）间时提示用户输入错误，请重新输入
        while(function<EXIT||function>READ)
        {
			printf("输入错误，请重新输入数字(0-9)：");
            scanf("%d",&function);
        }

        switch(function)
        {
        case ADD:
			//实现添加词条功能
            AddContent(dictionary);
            break;
        case SEARCH:
			//实现搜索词条功能
            SearchContent(dictionary);
            break;
		case FUZSER:
			//实现模糊搜索词条功能
			FuzzySearch(dictionary);
			break;
		case CLASSIFY:
			//实现按词性分类词条功能
			wordFormation(dictionary);
			break;
        case EDIT:
			//先通过密码验证，实现编辑词条功能
			flag=Password();
			if(flag==1)
			{
				EditContent(dictionary);
			}
				break;
        case DEL:
			//先通过密码验证，实现删除词条功能
			flag=Password();
			if(flag==1)
            {
				DeleteContent(dictionary);
			}
				break;
        case DISP:
			//实现显示词条功能
            DisplayAll(dictionary);
            break;
        case SAVE:
			//实现保存词条功能
            SaveContent(dictionary);
            break;
		case READ:
			//实现读取词条功能
            ReadContent(dictionary);
            break;
        case EXIT:
			//获取系统结束运行时间
			finish=clock();
			//实现退出字典功能，并显示GoodBye的界面
            Goodbye(start,finish);
			//让程序停止等待输入任意键实现退出程序
			system("pause");
            exit(0);
            break;
        default:
			//用户输入数字不在（0-9）间时提示用户输入错误，请重新输入
            printf("输入错误！请重新输入：");
            break;
        }
    }
	//结束程序前释放创建的链表结构体dictionary
    FreeList(dictionary);
}
