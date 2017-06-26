#include<iostream>
using namespace std;
#include<stdio.h>
#include<string.h>
#include<stdlib.h>





#define n 100//叶节点的个数小于等于n
#define m 2*n-1//总结点的个数为m=2*n-1
int num;//定义一个全局变量用于存放字符种类个数

typedef struct
//结构体用于存放树节点包括节点的父节点、左子节点、右子节点以及权值
{
	int weight;
	int parent;
	int lchild;
	int rchild;
}HTNode;


typedef HTNode HafumanTree[m+1];//重命名HTNode  HT

typedef struct//结构体用于存放每个字符的密文和长度
{
	char ch;
	char bits[10];
	int len;
}CodeNode;


typedef CodeNode HafumanCode[n+1];

int main(int argc,char*argv[])
{
	int quan[27],k=1,length,count=1,total,method;//申明一个数组用以存放26个字符的权值，length表示要加密字符串的长度
	                                             //count用于控制输入字符和权值的次数，total用于循环控制，k用于控制解密、加密
		                                         //method用于控制使用各种方法进行输入权值
	char getstr[300],str[27];//申明两个字符串数组一个用于存输入，一个用于存放，输入中含有字符
	char*s;//申明一个char型指针用于指向字符HafumanTree HT;
	HafumanCode HC;//申明m+1个树节点
	HafumanTree HT;//声明n+1个code
	int counttotal(char*s,int quan[],char str[]);//声明需要调用的函数
	void creathafumantree(HafumanTree HT,HafumanCode HC,int quan[],char str[]);
	void Hafumanencode(HafumanTree HT,HafumanCode HC);
	void codenum(HafumanCode HC,char*str);
	void exit(int status);
	char*decode(HafumanCode HC);


	while(k)
	{
		printf("                        ******************************                                \n");
		printf("                         欢迎使用哈夫曼加密解密系统!                                  \n");
		printf("                        ******************************                                \n");
		printf("请输入获得权值的方法,输入1表示输入每个节点的权值,输入0表示将每个字符在输入字符串中出现的次数作为其权值:");
			scanf("%d",&method);
		if(method==0)
		{
		    printf("请输入要编码的字符串(请输入小写字母): ");
		    gets(getstr);
		    scanf("%S",&getstr);//获得输入的字符串
		    num=counttotal(getstr,quan,str);//统计字符串中含有字符种类个数
		    creathafumantree(HT,HC,quan,str);//根据字符权值构建哈夫曼树
		    Hafumanencode(HT,HC);//根据哈夫曼树确定每个字符的code
		    codenum(HC,getstr);//将字符串译码存入文件夹
		    s=decode(HC);//将暗文解码
		    printf("解密为: \n");
		    printf("%s\n",&s);
		    printf("是否想继续编码、解码,是输入1回车,否输入0回车: ");
		    scanf("%d",&k);

		}
		else if(method==1)
        {
            total=1;//每次都要将其清零，以达到控制循环的效果
            scanf("%d",&length);
            for(count=1;count<=length;count++)
            {
                printf("请输入第%d个字符和该字符的权值(中间留一个空格): ");
                cin>>str[total]>>quan[total];
                total++;
            }
            num=length;
            creathafumantree(HT,HC,quan,str);//根据字符权值构建哈夫曼树
            Hafumanencode(HT,HC);//根据哈夫曼树确定每个字符的code
            printf("请输入要编码的字符串: ");
            cin>>getstr;

            codenum(HC,getstr);//将字符串译码存入文件夹
            s=decode(HC);
            printf("解密为: \n");
            printf("%s\n",&s);
            printf("是否想继续编码、解码,是输入1回车,否输入0回车: \n");
            scanf("%d",&k);

        }
        else
        {
            printf("错误输入!\n");
            exit(0);

        }
	}
	system("pause");
	return 0;
}



int counttotal(char*s,int quan[],char str[])//计算字符串中字符权值
{
    char*p;
    int i,j,k,quantemp[27];
    for(i=1;i<27;i++)//将所有字符的权值赋成0
        quantemp[i]=0;
    for(p=s;*p!='\0';p++)//判断字符串是否结束


        if(*p>'a'&&*p<='z')//判断字符是否为26字母
        {
            k=*p-96;//看是26个字符中的哪个字符
            quantemp[k]++;//字符权值加1

        }
        j=0;
        for(i=1,j=0;i<27;i++)
        {
            if(quantemp[i]!=0)
            {
                j++;//用于统计字符种类个数
                str[j]=i+96;//str按字母表顺序存储出现过的字符
                quan[j]=quantemp[i];

            }
        }
        return j;//返回该数据给num赋值


}




void selectmin(HafumanTree HT,int k,int *s1,int *s2)//选择权值最小的两个
{
    int i,j;
    int min=9999;//声明一个int类型的数值min，赋个较大的输给它
    for(i=1;i<=k;i++);//选择权值最小的一个节点（且该节点无父节点）
    {
        if(HT[i].weight<min&&(HT[i].parent==0))
        {
            j=i;
            min=HT[i].weight;
        }
    }
    *s1=j;
    min=9999;
    for(i=1;i<=k;i++)
    {
        if((HT[i].weight<min)&&(HT[i].parent==0)&&(i!=*s1))//选择权值最小的一个节点（且该节点无父节点）
        {
            j=i;
            min=HT[i].weight;

        }

    }
    *s2=j;
}

//构建哈夫曼树


void creathafumantree(HafumanTree HT,HafumanCode HC,int quan[],char str[])
{
    int i,s1,s2;
    for(i=1;i<2*num-1;i++)//将所有的节点赋空
    {
        HT[i].lchild=0;HT[i].rchild=0;
        HT[i].parent=0;HT[i].weight=0;
    }
    for(i=1;i<=num;i++)//将num个字符的权值9赋给num叶节点
    {
        HT[i].weight=quan[i];
    }
    for(i=1;i<=num;i++)//将num个字符赋给codenode
    {
        HC[i].ch=str[i];

    }
    i=1;
    while(i<=num)
        {
            printf("字符为%c,权值为%d\n",HC[i].ch,quan[i]);
            i++;
        }//输出每个字符及权值
        for(i=num+1;i<=2*num-1;i++)
        {
            selectmin(HT,i-1,&s1,&s2);
            //选择两个权值最小的叶节点，分别存放于s1和s2
            HT[s1].parent=i;
            HT[s2].parent=i;//两个节点指向同一个父节点
            HT[i].lchild=s1;HT[i].rchild=s2;
            HT[i].weight=HT[s1].weight+HT[s2].weight;
            //父节点的权值为子节点相加（父节点继续放入选择区）

        }



}



void Hafumanencode(HafumanTree HT,HafumanCode HC)
{
    int c,p,i;
    char cd[n];//临时数组用于记录字符在哈夫曼树的位置
    int start;
    cd[num]='\0';//给cd赋个结束符
    for(i=1;i<=num;i++)
    {
        start=num;
        c=i;
        while((p=HT[c].parent)>0)
            //根据节点是其父节点的左右子来记录他的位置
        {
            cd[--start]=(HT[p].lchild==c)?'0':'1';
            c=p;//将父节点转为子节点
        }
        strcpy(HC[i].bits,&cd[start]);//将得到的0、1字串存入结构体HC
        printf("%c:%s\n",HC[i].ch,HC[i].bits);
        HC[i].len=num-start;//求每个字符0、1编码长度
    }

}

//根据哈夫曼树确定每个字符的0/1代码code



void codenum(HafumanCode HC,char*str)
{
    int i,j;
    FILE*fp;//声明一个文件夹指针
    fp=fopen("code.txt","w");//打开文件夹codefile
    printf("密文为:\n");
    while(*str)//字符串未结束时
    {
        for(i=1;i<=num;i++)
        {
            if(HC[i].ch==*str)//判断字符是否在Codenode中存在
            {
                for(j=0;j<HC[i].len;j++)
                    //将codenode中该字符的1、0代码存入文件夹
                {
                    fputc(HC[i].bits[j],fp);
                }
                printf("%s",HC[i].bits);
                break;
            }
        }
        str++;//字符后移
    }
    printf("\n");
    printf("编码写入一个文件--code.txt成功!!!");//提示写入文件成功
    printf("\n");
    fclose(fp);
}



char*decode(HafumanCode HC)
{
    FILE*fp;
    char tempstr[9999];
    char*p;
    static char cd[n+1];//char型数组用于存放从文件夹中读取的1、0代码
    int i,j,k=0,end;
    fp=fopen("code.txt","r");

    while(!feof(fp))//当文件夹读取没有结束
    {
        end=0;//判断一个字符是否译码结束
        for(i=0;(i<num)&&(end==0)&&(!feof(fp));i++)
            //当一个字符未译完且文件未读取结束
        {
            cd[i]=' ';cd[i+1]='\0';//cd[]赋成空格
            cd[i]=fgetc(fp);//读取文件夹中的一个字符
            for(j=1;j<=num;j++)
            {
                if(strcmp(HC[j].bits,cd)==0)//看cd[]的字符串是否等于Codenode中的某个密文
                {
                    tempstr[k]=HC[j].ch;
                    end=1;
                    printf("=%s=",HC[j].bits);
                    k++;
                    break;
                }

            }
            //将译出的字符赋给临时字符串tempstr[],标记一个字符译码结束jsjs赋1，跳出循环

        }
    }



    printf("\n");
    tempstr[k]='\0';//赋给临时字符串一个结束符
    p=tempstr;//char型指针指向临时字符串
    return p;
}
