// newer
#include<iostream>
using namespace std;
#include<stdio.h>
#include<string.h>
#include<stdlib.h>





#define n 100//Ҷ�ڵ��ĸ���С�ڵ���n
#define m 2*n-1//�ܽ����ĸ���Ϊm=2*n-1
int num;//����һ��ȫ�ֱ������ڴ����ַ���������

typedef struct
//�ṹ�����ڴ������ڵ������ڵ��ĸ��ڵ㡢���ӽڵ㡢���ӽڵ��Լ�Ȩֵ
{
	int weight;
	int parent;
	int lchild;
	int rchild;
}HTNode;


typedef HTNode HafumanTree[m+1];//������HTNode  HT

typedef struct//�ṹ�����ڴ���ÿ���ַ������ĺͳ���
{
	char ch;
	char bits[10];
	int len;
}CodeNode;


typedef CodeNode HafumanCode[n+1];

int main(int argc,char*argv[])
{
	int quan[27],k=1,length,count=1,total,method;//����һ���������Դ���26���ַ���Ȩֵ��length��ʾҪ�����ַ����ĳ���
	                                             //count���ڿ��������ַ���Ȩֵ�Ĵ�����total����ѭ�����ƣ�k���ڿ��ƽ��ܡ�����
		                                         //method���ڿ���ʹ�ø��ַ�����������Ȩֵ
	char getstr[300],str[27];//���������ַ�������һ�����ڴ����룬һ�����ڴ��ţ������к����ַ�
	char*s;//����һ��char��ָ������ָ���ַ�HafumanTree HT;
	HafumanCode HC;//����m+1�����ڵ�
	HafumanTree HT;//����n+1��code
	int counttotal(char*s,int quan[],char str[]);//������Ҫ���õĺ���
	void creathafumantree(HafumanTree HT,HafumanCode HC,int quan[],char str[]);
	void Hafumanencode(HafumanTree HT,HafumanCode HC);
	void codenum(HafumanCode HC,char*str);
	void exit(int status);
	char*decode(HafumanCode HC);


	while(k)
	{
		printf("                        ******************************                                \n");
		printf("                         ��ӭʹ�ù��������ܽ���ϵͳ!                                  \n");
		printf("                        ******************************                                \n");
		printf("����������Ȩֵ�ķ���,����1��ʾ����ÿ���ڵ���Ȩֵ,����0��ʾ��ÿ���ַ��������ַ����г��ֵĴ�����Ϊ��Ȩֵ:");
			scanf("%d",&method);
		if(method==0)
		{
		    printf("������Ҫ�������ַ���(������Сд��ĸ): ");
		    gets(getstr);
		    scanf("%S",&getstr);//�����������ַ���
		    num=counttotal(getstr,quan,str);//ͳ���ַ����к����ַ���������
		    creathafumantree(HT,HC,quan,str);//�����ַ�Ȩֵ������������
		    Hafumanencode(HT,HC);//���ݹ�������ȷ��ÿ���ַ���code
		    codenum(HC,getstr);//���ַ������������ļ���
		    s=decode(HC);//�����Ľ���
		    printf("����Ϊ: \n");
		    printf("%s\n",&s);
		    printf("�Ƿ����������롢����,������1�س�,������0�س�: ");
		    scanf("%d",&k);

		}
		else if(method==1)
        {
            total=1;//ÿ�ζ�Ҫ�������㣬�Դﵽ����ѭ����Ч��
            scanf("%d",&length);
            for(count=1;count<=length;count++)
            {
                printf("��������%d���ַ��͸��ַ���Ȩֵ(�м���һ���ո�): ");
                cin>>str[total]>>quan[total];
                total++;
            }
            num=length;
            creathafumantree(HT,HC,quan,str);//�����ַ�Ȩֵ������������
            Hafumanencode(HT,HC);//���ݹ�������ȷ��ÿ���ַ���code
            printf("������Ҫ�������ַ���: ");
            cin>>getstr;

            codenum(HC,getstr);//���ַ������������ļ���
            s=decode(HC);
            printf("����Ϊ: \n");
            printf("%s\n",&s);
            printf("�Ƿ����������롢����,������1�س�,������0�س�: \n");
            scanf("%d",&k);

        }
        else
        {
            printf("��������!\n");
            exit(0);

        }
	}
	system("pause");
	return 0;
}



int counttotal(char*s,int quan[],char str[])//�����ַ������ַ�Ȩֵ
{
    char*p;
    int i,j,k,quantemp[27];
    for(i=1;i<27;i++)//�������ַ���Ȩֵ����0
        quantemp[i]=0;
    for(p=s;*p!='\0';p++)//�ж��ַ����Ƿ�����


        if(*p>'a'&&*p<='z')//�ж��ַ��Ƿ�Ϊ26��ĸ
        {
            k=*p-96;//����26���ַ��е��ĸ��ַ�
            quantemp[k]++;//�ַ�Ȩֵ��1

        }
        j=0;
        for(i=1,j=0;i<27;i++)
        {
            if(quantemp[i]!=0)
            {
                j++;//����ͳ���ַ���������
                str[j]=i+96;//str����ĸ��˳���洢���ֹ����ַ�
                quan[j]=quantemp[i];

            }
        }
        return j;//���ظ����ݸ�num��ֵ


}




void selectmin(HafumanTree HT,int k,int *s1,int *s2)//ѡ��Ȩֵ��С������
{
    int i,j;
    int min=9999;//����һ��int���͵���ֵmin�������ϴ���������
    for(i=1;i<=k;i++);//ѡ��Ȩֵ��С��һ���ڵ㣨�Ҹýڵ��޸��ڵ㣩
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
        if((HT[i].weight<min)&&(HT[i].parent==0)&&(i!=*s1))//ѡ��Ȩֵ��С��һ���ڵ㣨�Ҹýڵ��޸��ڵ㣩
        {
            j=i;
            min=HT[i].weight;

        }

    }
    *s2=j;
}

//������������


void creathafumantree(HafumanTree HT,HafumanCode HC,int quan[],char str[])
{
    int i,s1,s2;
    for(i=1;i<2*num-1;i++)//�����еĽڵ㸳��
    {
        HT[i].lchild=0;HT[i].rchild=0;
        HT[i].parent=0;HT[i].weight=0;
    }
    for(i=1;i<=num;i++)//��num���ַ���Ȩֵ9����numҶ�ڵ�
    {
        HT[i].weight=quan[i];
    }
    for(i=1;i<=num;i++)//��num���ַ�����codenode
    {
        HC[i].ch=str[i];

    }
    i=1;
    while(i<=num)
        {
            printf("�ַ�Ϊ%c,ȨֵΪ%d\n",HC[i].ch,quan[i]);
            i++;
        }//����ÿ���ַ���Ȩֵ
        for(i=num+1;i<=2*num-1;i++)
        {
            selectmin(HT,i-1,&s1,&s2);
            //ѡ������Ȩֵ��С��Ҷ�ڵ㣬�ֱ�������s1��s2
            HT[s1].parent=i;
            HT[s2].parent=i;//�����ڵ�ָ��ͬһ�����ڵ�
            HT[i].lchild=s1;HT[i].rchild=s2;
            HT[i].weight=HT[s1].weight+HT[s2].weight;
            //���ڵ���ȨֵΪ�ӽڵ����ӣ����ڵ���������ѡ������

        }



}



void Hafumanencode(HafumanTree HT,HafumanCode HC)
{
    int c,p,i;
    char cd[n];//��ʱ�������ڼ�¼�ַ��ڹ���������λ��
    int start;
    cd[num]='\0';//��cd����������
    for(i=1;i<=num;i++)
    {
        start=num;
        c=i;
        while((p=HT[c].parent)>0)
            //���ݽڵ����丸�ڵ�������������¼����λ��
        {
            cd[--start]=(HT[p].lchild==c)?'0':'1';
            c=p;//�����ڵ�תΪ�ӽڵ�
        }
        strcpy(HC[i].bits,&cd[start]);//���õ���0��1�ִ������ṹ��HC
        printf("%c:%s\n",HC[i].ch,HC[i].bits);
        HC[i].len=num-start;//��ÿ���ַ�0��1���볤��
    }

}

//���ݹ�������ȷ��ÿ���ַ���0/1����code



void codenum(HafumanCode HC,char*str)
{
    int i,j;
    FILE*fp;//����һ���ļ���ָ��
    fp=fopen("code.txt","w");//�����ļ���codefile
    printf("����Ϊ:\n");
    while(*str)//�ַ���δ����ʱ
    {
        for(i=1;i<=num;i++)
        {
            if(HC[i].ch==*str)//�ж��ַ��Ƿ���Codenode�д���
            {
                for(j=0;j<HC[i].len;j++)
                    //��codenode�и��ַ���1��0���������ļ���
                {
                    fputc(HC[i].bits[j],fp);
                }
                printf("%s",HC[i].bits);
                break;
            }
        }
        str++;//�ַ�����
    }
    printf("\n");
    printf("����д��һ���ļ�--code.txt�ɹ�!!!");//��ʾд���ļ��ɹ�
    printf("\n");
    fclose(fp);
}



char*decode(HafumanCode HC)
{
    FILE*fp;
    char tempstr[9999];
    char*p;
    static char cd[n+1];//char���������ڴ��Ŵ��ļ����ж�ȡ��1��0����
    int i,j,k=0,end;
    fp=fopen("code.txt","r");

    while(!feof(fp))//���ļ��ж�ȡû�н���
    {
        end=0;//�ж�һ���ַ��Ƿ���������
        for(i=0;(i<num)&&(end==0)&&(!feof(fp));i++)
            //��һ���ַ�δ�������ļ�δ��ȡ����
        {
            cd[i]=' ';cd[i+1]='\0';//cd[]���ɿո�
            cd[i]=fgetc(fp);//��ȡ�ļ����е�һ���ַ�
            for(j=1;j<=num;j++)
            {
                if(strcmp(HC[j].bits,cd)==0)//��cd[]���ַ����Ƿ�����Codenode�е�ĳ������
                {
                    tempstr[k]=HC[j].ch;
                    end=1;
                    printf("=%s=",HC[j].bits);
                    k++;
                    break;
                }

            }
            //���������ַ�������ʱ�ַ���tempstr[],����һ���ַ���������jsjs��1������ѭ��

        }
    }



    printf("\n");
    tempstr[k]='\0';//������ʱ�ַ���һ��������
    p=tempstr;//char��ָ��ָ����ʱ�ַ���
    return p;
}
