/*ͷ�ļ���*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>

/*�궨����*/
#define  ADMIN_password "123456" /*����Ա��¼����*/

/*�ṹ��������*/
typedef struct bookinfo/*ϵͳͼ����Ϣ */
{
    char number[15];/*ͼ����*/
    char name[30];/*ͼ������*/
    char author[20];/*����*/
    char press[30];/*������*/
    char category[20]; /*���*/
    float price;/*����*/
    int  quantity;/*�ݲ���*/
    int  time;/*�������*/
}BOOKINFO;

typedef struct bookgrasp/*��Ա������鼮��Ϣ*/
{
    char number[15];/*ͼ����*/
    char name[30];/*ͼ������*/
    char author[20];/*����*/
    char press[30];/*������*/
    char category[20]; /*���*/
    float price;/*����*/
    char account[30];/*������ID*/
}BOOKGRASP;

typedef struct member/*��Ա������Ϣ */
{
    char name[30];
    char ID[20];
    char password[30];
    char sex[15];
    char password_key[30];
}MEMBER;

/*�˵�������*/
void menu1();
void menu2();
void menu3();
void AboutMe();

/*���ߺ�����*/
int compare_password(char password[20]);/*����ȶԺ��� */
void clock_delay(); /*ʱ����ʱ����*/
void password_circle();/*�����װ�κ���*/
void find_account_circle();/*�һ��ʻ���������*/

/*������Ϣϵͳ�㼶������*/
int user_account(char account[20]);/*�����˻���Ϣ*/
void member_log_up();/*����ע�ắ��*/
int member_log_in(char account[20]);/*���ߵ�¼����*/
void ADMIN_watch_member();/*�鿴������Ϣ����*/
void display_memberbook();/*�鿴����ͼ�������Ϣ����*/
int check_repeat_ID(char id_account[20]);/*����˻��ظ��Ժ���*/
void find_account();/*�˻��һغ���*/

/*ͼ����Ϣϵͳ�㼶������*/
void add_book();/*�����½���ͼ����Ϣ*/
void delete_book();/*����ͼ�����ƶ�ͼ����Ϣ����ɾ��*/
void modify_book();/*�޸�ͼ����Ϣ*/
void display_book();/*��ʾȫ��ͼ����Ϣ*/
void search_book();/*����ͼ��������ʾͼ�����Ϣ*/
void borrow_book(char account[20]);/*����*/
void return_book(char account[20]);/*����*/
void display_price_lower();/*���ݼ۸��г�ͼ����Ϣ*/
/*void dispaly_popular();/*ͼ���ܻ�ӭ�����а�*/
int check_repeat_book(char number[30]);/*�����鼮���*/


void menu1() {
    system("color E9");
    printf("|=================================================================================|\n");
    printf("|                                                                                 |\n");
    printf("|                               ��ӭʹ��ͼ�����ϵͳ                                  |\n");
    printf("|                                                                                 |\n");
    printf("|=================================================================================|\n");
    printf("|                                      �˵�                                        |\n");
    printf("|---------------------------------------------------------------------------------|\n");
    printf("|               |               |               |                |                |\n");
    printf("|               |               |               |                |                |\n");
    printf("|      1.       |               |       3.      |       4.       |       5.       |\n");
    printf("|    �û���¼    |                |    ����Ա��¼   |       ����      |       �˳�      |\n");
    printf("|               |               |               |                |                |\n");
    printf("|               |               |               |                |                |\n");
    printf("|=================================================================================|\n");

}

void menu2(){
    system("color BC");
    printf("\n\n");
    printf("\t\t\t*=======================================================*\n");
    printf("\t\t\t||------------------------�û���¼ ---------------------||\n");
    printf("\t\t\t*                                                      *|\n");
    printf("\t\t\t||    [1]     ��ѯ�ݲ�ͼ����Ϣ                            ||\n");
    printf("\t\t\t|*    [2]     ����ͼ��                                   *|\n");
    printf("\t\t\t||    [3]     �黹ͼ��                                   ||\n");
    printf("\t\t\t|*    [4]     �˻���Ϣ                                   *|\n");
    printf("\t\t\t||    [5]     �˳���¼                                   ||\n");
    printf("\t\t\t*=======================================================*\n");
}


void menu3(){
    system("color 1B");
    printf("\n\n");
    printf("\t\t\t*=======================================================*\n");
    printf("\t\t\t||-----------------------����Ա��¼ ---------------------||\n");
    printf("\t\t\t*                                                      *|\n");
    printf("\t\t\t||    [1]     ����ͼ��                                   ||\n");
    printf("\t\t\t|*    [2]     ɾ��ͼ��                                   *|\n");
    printf("\t\t\t||    [3]     ����ͼ��                                   ||\n");
    printf("\t\t\t|*    [4]     �޸�ͼ����Ϣ                                *|\n");
    printf("\t\t\t||    [5]     ��ʾȫ��ͼ����Ϣ                             ||\n");
    printf("\t\t\t||    [6]     ��ʾ�����û���Ϣ                             ||\n");
    printf("\t\t\t||    [7]     ��ʾ��ǰͼ�������Ϣ                          ||\n");
    printf("\t\t\t||    [8]     �˳�����Աϵͳ                               ||\n");
    printf("\t\t\t*=======================================================*\n");
}


void AboutMe(){
    system("color 1D");
    printf("\n\n");
    printf("\t\t\t*=======================================================*\n");
    printf("\t\t\t||------------------------ ���� ------------------------||\n");
    printf("\t\t\t|            ���241���    202400406040                |\n");
    printf("\t\t\t|                                                       |\n");
    printf("\t\t\t|             C_V1.0  ͼ��ݹ������  24/12/10             |\n");
    printf("\t\t\t|                                                       |\n");
    printf("\t\t\t|       ˼·��ʵ��:�廪��ѧ������-C���Դ����ŵ���ͨ             |\n");
    printf("\t\t\t|                ֪��-@Jarry                             |\n");
    printf("\t\t\t|                       ��������˳�                      |\n");
    printf("\t\t\t*=======================================================*\n");
    getch();
}

void add_book() /*�����½���ͼ����Ϣ*/
{
    char choice;
    FILE *p1;
    BOOKINFO newbook;
    int flag;
    system("cls");
    while(1)
    {
        flag=0;
        fflush(stdin);
        printf("������ͼ����:");
        gets(newbook.number);

        if(check_repeat_book(newbook.number))
        {
            printf("��ͼ�����ѱ�ʹ�ã�");
            printf("\n�����������ע��\n\n");
            getch();
            flag=1;
        }
        else{
            fflush(stdin);
            printf("����������:");
            gets(newbook.name);

            printf("����������:");
            gets(newbook.author);

            printf("�����������:");
            gets(newbook.press);

            printf("���������(��ѧ/��ѧ/��ѧ/��ѧ/��):");
            gets(newbook.category);

            printf("������۸�:");
            scanf("%f",&newbook.price);

            printf("������ݲ���:");
            scanf("%d",&newbook.quantity);

            printf("��������Ĵ���(��������0):");
            scanf("%d",&newbook.time);
            fflush(stdin);
            printf("�Ƿ񱣴������Ŀ(y/n):");
            choice=getch();
            while(choice!='Y'&&choice!='y'&&choice!='N'&&choice!='n')
                choice=getch();
            printf("%c",choice);
            if(choice=='Y'||choice=='y')
            {
                p1=fopen("library.txt","a");
                fprintf(p1,"%s %s %s %s %s %f %d %d\n",
                        newbook.number,newbook.name,newbook.author,newbook.press,
                        newbook.category,newbook.price,newbook.quantity,newbook.time);
                fclose(p1);
                printf("\n������Ŀ����ӵ�library.txt�ļ���!\n");
            }
            else
            {
                printf("\n������Ŀδ����!\n");
            }
            printf("\n\n�Ƿ���������Ŀ(y/n):");
            choice=getch();
            while(choice!='Y'&&choice!='y'&&choice!='N'&&choice!='n')
                choice=getch();
            printf("%c",choice);
            printf("\n");
        }
        if(choice=='Y'||choice=='y'||flag==1)
            continue;
        else
            break;
    }
}

void display_book()/*��ʾȫ��ͼ����Ϣ*/
{
    FILE *p1;
    int n;
    BOOKINFO bookinfo[100];
    int booknumber=0;
    system("cls");
    fflush(stdin);
    p1=fopen("library.txt","r");
    while(!feof(p1))
    {
        fscanf(p1,"%s %s %s %s %s %f %d %d\n",
               bookinfo[booknumber].number,bookinfo[booknumber].name,bookinfo[booknumber].author,
               bookinfo[booknumber].press,bookinfo[booknumber].category,
               &bookinfo[booknumber].price,&bookinfo[booknumber].quantity,&bookinfo[booknumber].time);
        booknumber++;
    }
    fclose(p1);
    printf("��ǰͼ�������%dĿ�鼮\n\n",booknumber);
    if(bookinfo[0].quantity==0)
    {
        printf("\nû���κ�ͼ����Ϣ!\n\n");
    }
    else
    {
        n=0;
        printf("|---------------------------------ͼ����Ϣ---------------------------------|\n");
        printf("|���  ����        ����      ������          ���    ����    �ݲ���  ������|\n");
        printf("|                                                                          |\n");
        while(n<booknumber)
        {
            printf("|%-6s%-12s%-10s%-16s%-8s%-8.1f%-8d%-6d|\n",bookinfo[n].number,bookinfo[n].name,bookinfo[n].author,
                   bookinfo[n].press,bookinfo[n].category,bookinfo[n].price,bookinfo[n].quantity,bookinfo[n].time);
            n++;
        }
    }
    printf("\n\n�������������һ���˵�!\n");
    getch();
}

void search_book()/*����ͼ��������ʾͼ�����Ϣ*/
{
    int flag=1,flag1=1;
    char select;
    char name_compare[30]="";/*name_compare�������Ҫ��ѯ������*/
    char number_compare[30]=""; /*number_compare�������Ҫ��ѯ���鼮���*/
    char author_compare[30]="";/*author_compare�������Ҫ��ѯ����������*/
    char search[30]="";/*search�Ǳȶ�����,����Ҫ���ҵ���������ȶ�����*/
    char compare[30]="";/*compare�Ǳȶ�����,������е���������ȶ�����*/
    int n=0;
    FILE *p1;
    char choice;
    BOOKINFO bookinfo[100];
    int booknumber=0;

    system("cls");
    fflush(stdin);
    p1=fopen("library.txt","r");
    while(!feof(p1))
    {
        fscanf(p1,"%s %s %s %s %s %f %d %d\n",
               bookinfo[booknumber].number,bookinfo[booknumber].name,bookinfo[booknumber].author,
               bookinfo[booknumber].press,bookinfo[booknumber].category,
               &bookinfo[booknumber].price,&bookinfo[booknumber].quantity,&bookinfo[booknumber].time);
        booknumber++;
    }
    fclose(p1);

    while(flag)
    {
        system("cls");
        while(flag1)
        {
            system("cls");
            fflush(stdin);
            printf("����ͨ��\n\n1.<-ͼ����->\n\n2.<-����->\n\n3.<-������->\n\n���ַ�ʽ��ѯͼ��:");
            select=getch();
            printf("%c",select);
            printf("\n\n�������������Ϣ:");
            switch(select)
            {
                case '1':gets(number_compare);strcpy(search,number_compare);flag1=0;break;
                case '2':gets(name_compare);strcpy(search,name_compare);flag1=0;break;
                case '3':gets(author_compare);strcpy(search,author_compare);flag1=0;break;
                default :
                    printf("\n��Ҫ����˵�֮�������~�������������");
                    fflush(stdin);
                    getch();
            }
        }

        flag1=1;
        if(bookinfo[0].quantity==0)
        {
            printf("�����û���κ���Ϣ!\n\n");
            printf("��������ص����˵�!\n\n");
            getch();
            break;
        }
        else
        {
            for(n=0;n<booknumber;n++)
            {
                switch(select)
                {
                    case '1':strcpy(compare,bookinfo[n].number);break;
                    case '2':strcpy(compare,bookinfo[n].name);break;
                    case '3':strcpy(compare,bookinfo[n].author);break;
                }
                if(strcmp(compare,search)==0)
                {
                    printf("|---------------------------------ͼ����Ϣ---------------------------------|\n");
                    printf("|���  ����        ����      ������          ���    ����    �ݲ���  ������|\n");
                    printf("|                                                                          |\n");
                    printf("|%-6s%-12s%-10s%-16s%-8s%-8.1f%-8d%-6d|\n",bookinfo[n].number,bookinfo[n].name,bookinfo[n].author,
                           bookinfo[n].press,bookinfo[n].category,bookinfo[n].price,bookinfo[n].quantity,bookinfo[n].time);
                    break;
                }
            }
            if(n>=booknumber)
                printf("\nû�в��ҷ�����Ҫ����鼮!\n");

            printf("\n\n�Ƿ������ѯ(y/n):");
            choice=getch();
            while(choice!='Y'&&choice!='y'&&choice!='N'&&choice!='n')
                choice=getch();
            printf("%c",choice);
            printf("\n");
            if(choice=='Y'||choice=='y')
                flag=1;
            else
                flag=0;

        }
    }
}

void delete_book()/*����ͼ�����ƶ�ͼ����Ϣ����ɾ��*/
{
    char search[20]="";/*search�������Ҫɾ��������*/
    int n,i;
    FILE *p1;
    char choice;
    BOOKINFO bookinfo[100];
    int booknumber;

    system("cls");
    while(1)
    {
        fflush(stdin);
        printf("����Ҫɾ�����鱾����:");
        gets(search);
        p1=fopen("library.txt","r");
        booknumber=0;
        while(!feof(p1))
        {
            fscanf(p1,"%s %s %s %s %s %f %d %d\n",
                   bookinfo[booknumber].number,bookinfo[booknumber].name,bookinfo[booknumber].author,
                   bookinfo[booknumber].press,bookinfo[booknumber].category,
                   &bookinfo[booknumber].price,&bookinfo[booknumber].quantity,&bookinfo[booknumber].time);
            booknumber++;
        }
        fclose(p1);
        if(bookinfo[0].quantity==0)
        {
            printf("�����û���κ���Ϣ!\n\n");
            printf("��������ص����˵�!\n\n");
            getch();
            break;
        }/*if����*/
        else
        {
            for(n=0;n<booknumber;n++)
                if(strcmp(bookinfo[n].name,search)==0)
                {
                    break;
                }
            if(n>=booknumber)
                printf("\nû�в��Ҹ�����κ���Ϣ!\n");
            else
            {
                printf("\n�Ƿ�ȷ����Ҫɾ��������Ŀ(Y/N):");
                choice=getch();
                while(choice!='Y'&&choice!='y'&&choice!='N'&&choice!='n')
                    choice=getch();
                printf("%c",choice);
                if(choice=='Y'||choice=='y')
                {
                    for(i=n;i<booknumber-1;i++)
                        bookinfo[i]=bookinfo[i+1];
                    booknumber--;
                    p1=fopen("library.txt","w");
                    for(n=0;n<booknumber;n++)
                        fprintf(p1,"%s %s %s %s %s %f %d %d\n",
                                bookinfo[n].number,bookinfo[n].name,bookinfo[n].author,
                                bookinfo[n].press,bookinfo[n].category,bookinfo[n].price,bookinfo[n].quantity,bookinfo[n].time);
                    fclose(p1);
                    printf("\nɾ���ɹ�!");
                }
                else
                    printf("\n������Ŀû�б�ɾ��!");
            }
            printf("\n\n�Ƿ��������ɾ������(y/n):");
            choice=getch();
            while(choice!='Y'&&choice!='y'&&choice!='N'&&choice!='n')
                choice=getch();
            printf("%c",choice);
            printf("\n");
            if(choice=='Y'||choice=='y')
                continue;
            else
                break;
        }/*else����*/
    }/*while(1)����*/
}

void display_price_lower()/*���ݼ۸��г�ͼ����Ϣ*/
{
    float price;
    FILE *p1;
    int n;
    int count=0;
    BOOKINFO bookinfo[100];
    int booknumber;

    system("cls");
    printf("�������������۸�,���ǽ��Ƽ����������λ�Ե͵��鼮:");
    scanf("%f",&price);
    p1=fopen("library.txt","r");
    booknumber=0;
    while(!feof(p1))
    {
        fscanf(p1,"%s %s %s %s %s %f %d %d\n",
               bookinfo[booknumber].number,bookinfo[booknumber].name,bookinfo[booknumber].author,
               bookinfo[booknumber].press,bookinfo[booknumber].category,
               &bookinfo[booknumber].price,&bookinfo[booknumber].quantity,&bookinfo[booknumber].time);
        booknumber++;
    }
    fclose(p1);
    if(bookinfo[0].quantity==0)
    {
        printf("\nû���κ�ͼ����Ϣ!\n");
    }
    else
    {
        for(n=0;n<booknumber;n++)
        {
            if(bookinfo[n].price<=price)
                count++;
        }
        if(count==0)
            printf("�����û�б�%.1fԪ�۸���͵�ͼ�顣",price);
        else
        {
            printf("\n�۸����%.1fԪ��ͼ����Ϣ��%d��\n",price,count);
            printf("|---------------------------------ͼ����Ϣ---------------------------------|\n");
            printf("|���  ����        ����      ������          ���    ����    �ݲ���  ������|\n");
            printf("|                                                                          |\n");
            for(n=0;n<booknumber;n++)
            {
                if(bookinfo[n].price<=price)
                    printf("|%-6s%-12s%-10s%-16s%-8s%-8.1f%-8d%-6d|\n",bookinfo[n].number,bookinfo[n].name,bookinfo[n].author,
                           bookinfo[n].press,bookinfo[n].category,bookinfo[n].price,bookinfo[n].quantity,bookinfo[n].time);
            }
        }
    }
    printf("\n\n��������ص����˵�!\n");
    getch();
}

void modify_book()
{
    int flag=1,flag1=1,flag2,n;
    char change,choice;
    char number[15];/*ͼ����*/
    char name[30];/*ͼ������*/
    char author[20];/*����*/
    char press[30];/*������*/
    char category[20];/*���*/
    int  quantity;/*������*/
    float price;/*����*/

    char search[30];/*Ҫ�޸ĵ�����*/
    FILE *p1;
    BOOKINFO bookinfo[100];
    int booknumber;
    while(flag)
    {
        flag2=0;
        system("cls");
        fflush(stdin);
        printf("����Ҫ�޸���Ϣ���鱾��:");
        gets(search);
        p1=fopen("library.txt","r");
        booknumber=0;
        while(!feof(p1))
        {
            fscanf(p1,"%s %s %s %s %s %f %d %d\n",
                   bookinfo[booknumber].number,bookinfo[booknumber].name,bookinfo[booknumber].author,
                   bookinfo[booknumber].press,bookinfo[booknumber].category,
                   &bookinfo[booknumber].price,&bookinfo[booknumber].quantity,&bookinfo[booknumber].time);
            booknumber++;
        }
        fclose(p1);
        if(bookinfo[0].quantity==0)
        {
            printf("�����û���κ���Ϣ!\n\n");
            printf("��������ص����˵�!\n\n");
            getch();
            break;
        }
        else
        {
            for(n=0;n<booknumber;n++)
                if(strcmp(bookinfo[n].name,search)==0)
                {
                    printf("\n");
                    printf("|---------------------------------ͼ����Ϣ---------------------------------|\n");
                    printf("|���  ����        ����      ������          ���    ����    �ݲ���  ������|\n");
                    printf("|                                                                          |\n");
                    printf("|%-6s%-12s%-10s%-16s%-8s%-8.1f%-8d%-6d|\n",bookinfo[n].number,bookinfo[n].name,bookinfo[n].author,
                           bookinfo[n].press,bookinfo[n].category,bookinfo[n].price,bookinfo[n].quantity,bookinfo[n].time);

                    while(flag1){
                        printf("\n1.�鼮���\n2.�鼮����\n3.�鼮����\n4.������\n5.�鼮���\n6.�鼮����\n7.������\n\n����Ҫ�޸ĵ���:");
                        change=getch();
                        while(change!='1'&&change!='2'&&change!='3'&&change!='4'&&change!='5'&&change!='6'&&change!='7')
                            change=getch();
                        printf("%c",change);
                        printf("\n�������µ�����:");
                        fflush(stdin);
                        switch(change)
                        {
                            case '1':gets(number);flag1=0;flag2=check_repeat_book(number);
                                if(!flag2)
                                    strcpy(bookinfo[n].number,number);
                                break;
                            case '2':gets(name);strcpy(bookinfo[n].name,name);flag1=0;break;
                            case '3':gets(author);strcpy(bookinfo[n].author,author);flag1=0;break;
                            case '4':gets(press);strcpy(bookinfo[n].press,press);flag1=0;break;
                            case '5':gets(category);strcpy(bookinfo[n].category,category);flag1=0;break;
                            case '6':scanf("%f",&price);bookinfo[n].price=price;flag1=0;break;
                            case '7':scanf("%d",&quantity);bookinfo[n].quantity=quantity;flag1=0;break;
                            default:break;/*��Ȼѹ���������default����������º���������©���¼ӵ�case��while�������Լ���*/
                        }
                    }
                    flag1=1;
                    break;
                }
            if(n>=booknumber)
                printf("\nû�в��Ҹ�����κ���Ϣ!");
            else if(!flag2)
            {
                p1=fopen("library.txt","w");
                for(n=0;n<booknumber;n++)
                    fprintf(p1,"%s %s %s %s %s %f %d %d\n",
                            bookinfo[n].number,bookinfo[n].name,bookinfo[n].author,
                            bookinfo[n].press,bookinfo[n].category,bookinfo[n].price,bookinfo[n].quantity,bookinfo[n].time);
                fclose(p1);
                printf("\n�޸ĳɹ�!");
            }
            else
                printf("�����޸ĵ�ͼ����Ϣ�������Ϣ�ظ���");
            printf("\n�Ƿ���������޸�(y/n):");
            choice=getch();
            while(choice!='Y'&&choice!='y'&&choice!='N'&&choice!='n')
                choice=getch();
            printf("%c",choice);
            printf("\n");
            if(choice=='Y'||choice=='y')
                flag=1;
            else
                flag=0;
        }
    }
}

void borrow_book(char account[20])
{
    FILE *p1,*p3;
    BOOKINFO bookinfo[100];
    char search[30],choice;
    int flag=1,n;
    int booknumber1;
    system("cls");

    while(flag)
    {
        printf("����Ҫ���ĵ��鱾��:");
        gets(search);
        p1=fopen("library.txt","r");
        booknumber1=0;
        while(!feof(p1))
        {
            fscanf(p1,"%s %s %s %s %s %f %d %d\n",
                   bookinfo[booknumber1].number,bookinfo[booknumber1].name,bookinfo[booknumber1].author,
                   bookinfo[booknumber1].press,bookinfo[booknumber1].category,
                   &bookinfo[booknumber1].price,&bookinfo[booknumber1].quantity,&bookinfo[booknumber1].time);
            booknumber1++;
        }
        fclose(p1);

        if(bookinfo[0].quantity==0)
        {
            printf("\n�����û���κ���Ϣ!\n");
            printf("��������ص����˵�!\n\n");
            getch();
            break;
        }
        else
        {
            for(n=0;n<booknumber1;n++)
                if(strcmp(bookinfo[n].name,search)==0)
                {
                    bookinfo[n].quantity--;
                    bookinfo[n].time++;

                    p3=fopen("memberbook.txt","a");  /*������a׷�ӵķ�ʽ�����ļ�������һ����*/
                    fprintf(p1,"%s %s %s %s %s %f %s\n",
                            bookinfo[n].number,bookinfo[n].name,bookinfo[n].author,bookinfo[n].press,
                            bookinfo[n].category,bookinfo[n].price,account);
                    fclose(p3);
                    break;
                }
        }
        if(n>=booknumber1)
            printf("\nû�в��Ҹ�����κ���Ϣ!\n");
        else
        {
            p1=fopen("library.txt","w");
            for(n=0;n<booknumber1;n++)
                fprintf(p1,"%s %s %s %s %s %f %d %d\n",
                        bookinfo[n].number,bookinfo[n].name,bookinfo[n].author,bookinfo[n].press,
                        bookinfo[n].category,bookinfo[n].price,bookinfo[n].quantity,bookinfo[n].time);
            fclose(p1);
            printf("\n����ɹ�!\n");
        }
        printf("\n�Ƿ��������(y/n):");
        choice=getch();
        while(choice!='Y'&&choice!='y'&&choice!='N'&&choice!='n')
            choice=getch();
        printf("%c",choice);
        printf("\n");
        if(choice=='Y'||choice=='y')
            flag=1;
        else
            flag=0;
    }
}

void return_book(char account[20])
{
    FILE *p1,*p3;
    BOOKINFO bookinfo[100];
    BOOKGRASP bookgrasp[100];
    char search[30],choice;
    int flag=1,flag2=0,n,i,k,j,t=0;
    int booknumber,booknumber2;
    system("cls");

    while(flag)
    {
        flag2=0;
        fflush(stdin);
        p1=fopen("library.txt","r");
        booknumber=0;
        while(!feof(p1))
        {
            fscanf(p1,"%s %s %s %s %s %f %d %d\n",
                   bookinfo[booknumber].number,bookinfo[booknumber].name,bookinfo[booknumber].author,
                   bookinfo[booknumber].press,bookinfo[booknumber].category,
                   &bookinfo[booknumber].price,&bookinfo[booknumber].quantity,&bookinfo[booknumber].time);
            booknumber++;
        }
        fclose(p1);

        p3=fopen("memberbook.txt","r");
        booknumber2=0;
        while(!feof(p3))
        {
            fscanf(p3,"%s %s %s %s %s %f %s\n",
                   bookgrasp[booknumber2].number,bookgrasp[booknumber2].name,bookgrasp[booknumber2].author,bookgrasp[booknumber2].press,
                   bookgrasp[booknumber2].category,&bookgrasp[booknumber2].price,bookgrasp[booknumber2].account);
            booknumber2++;
        }
        fclose(p3);

        printf("�������ĵ�����ͼ����Ϣ����:\n");
        printf("|----------------------------ͼ�������Ϣ--------------------|\n");
        printf("|���  ����        ����      ������          ���    ����    |\n");
        while(t<booknumber2)
        {
            if(strcmp(bookgrasp[t].account,account)==0)
            {
                printf("|%-6s%-12s%-10s%-16s%-8s%-8.1f|\n",bookgrasp[t].number,
                       bookgrasp[t].name,bookgrasp[t].author,bookgrasp[t].press,
                       bookgrasp[t].category,bookgrasp[t].price);
            }
            t++;
        }

        printf("\n����Ҫ�黹���鱾��:");
        gets(search);
        if(bookinfo[0].quantity==0)
        {
            printf("\n�����û���κ���Ϣ!\n");
            printf("��������ص����˵�!\n\n");
            getch();
            break;
        }
        else
        {
            for(n=0;n<booknumber;n++)
                if(strcmp(bookinfo[n].name,search)==0)
                {
                    bookinfo[n].quantity++;

                    if(bookgrasp[0].price==0)
                        printf("\n��û�н�����Ϣ��");
                    else{
                        for(k=0;k<booknumber2;k++)
                            if(!strcmp(bookgrasp[k].account,account)&&!strcmp(bookgrasp[k].name,search))
                            {
                                flag2=1;
                                for(i=k;i<booknumber2-1;i++)
                                    bookgrasp[i]=bookgrasp[i+1];
                                booknumber2--;
                                break;
                            }

                        p3=fopen("memberbook.txt","w");
                        for(j=0;j<booknumber2;j++)
                        {
                            fprintf(p3,"%s %s %s %s %s %f %s\n",
                                    bookgrasp[j].number,bookgrasp[j].name,bookgrasp[j].author,bookgrasp[j].press,
                                    bookgrasp[j].category,bookgrasp[j].price,bookgrasp[j].account);
                        }
                        fclose(p3);
                    }
                    break;
                }
        }
        if(n==booknumber||flag2==0)
            printf("����û������������Ϣ!\n");
        if(n<booknumber&&flag2==1)
        {
            p1=fopen("library.txt","w");
            for(n=0;n<booknumber;n++)
                fprintf(p1,"%s %s %s %s %s %f %d %d\n",
                        bookinfo[n].number,bookinfo[n].name,bookinfo[n].author,
                        bookinfo[n].press,bookinfo[n].category,bookinfo[n].price,bookinfo[n].quantity,bookinfo[n].time);
            fclose(p1);
            printf("\n����ɹ���");
        }
        else
            printf("\n����ʧ�ܣ�");

        fflush(stdin);
        printf("\n�Ƿ��������(y/n):");
        choice=getch();
        while(choice!='Y'&&choice!='y'&&choice!='N'&&choice!='n')
            choice=getch();
        printf("%c",choice);
        printf("\n");
        if(choice=='Y'||choice=='y')
            flag=1;
        else
            flag=0;
    }
}