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

typedef struct bookgrasp/*������鼮��Ϣ*/
{
    char number[15];/*ͼ����*/
    char name[30];/*ͼ������*/
    char author[20];/*����*/
    char press[30];/*������*/
    char category[20]; /*���*/
    float price;/*����*/
    char account[30];/*������ID*/
}BOOKGRASP;

typedef struct member/*���߸�����Ϣ */
{
    char name[30];
    char ID[20];
    char password[30];
    char sex[15];
    char password_key[30];
}MEMBER;

/*�˵�������1111*/
void menu1();
void menu2();
void menu3();
void AboutMe();

/*���ߺ�����*/
int compare_password(char password[20]);/*����ȶԺ��� */

/*������Ϣϵͳ�㼶������*/
int user_account(char account[20]);/*�����˻���Ϣ1111*/
void member_log_up();/*����ע�ắ��1111*/
int member_log_in(char account[20]);/*���ߵ�¼����1111*/
void ADMIN_watch_member();/*�鿴������Ϣ����1111*/

/*ͼ����Ϣϵͳ�㼶������*/
void add_book();/*�����½���ͼ����Ϣ1111*/
void delete_book();/*����ͼ�����ƶ�ͼ����Ϣ����ɾ��1111*/
void modify_book();/*�޸�ͼ����Ϣ1111*/
void display_book();/*��ʾȫ��ͼ����Ϣ1111*/
void search_book();/*����ͼ��������ʾͼ�����Ϣ1111*/
void borrow_book(char account[20]);/*����1111*/
void return_book(char account[20]);/*����1111*/
void display_price_lower();/*���ݼ۸��г�ͼ����Ϣ1111*/
int check_repeat_book(char number[30]);/*�����鼮���1111*/



// ͨ�õ�������֤���������������ȷ������ʽ
char validateInput(const char* validChars) {
    char input;
    input = getch();
    while (1) {
        int i;
        for (i = 0; validChars[i]!= '\0'; i++) {
            if (input == validChars[i]) {
                return input;
            }
        }
        input = getch();
    }
}

int main() {
    int flag1 = 1, flag2 = 1, flag3 = 1;
    char choice1, choice2, choice3;
    FILE *p1, *p2, *p3;

    system("title ��ӭʹ��ͼ��������");

    if ((p1 = fopen("library.txt", "r")) == NULL) /*p1��ͼ�����ϵͳ���鼮��Ϣ�ļ�ָ��*/
    {
        p1 = fopen("library.txt", "w");
        fclose(p1);
    }
    if ((p2 = fopen("infomember.txt", "r")) == NULL) /*p2��ͼ�����ϵͳ�Ļ�Ա������Ϣ�ļ�ָ��*/
    {
        p2 = fopen("infomember.txt", "w");
        fclose(p2);
    }
    if ((p3 = fopen("memberbook.txt", "r")) == NULL) /*p3��ͼ�����ϵͳ�Ļ�Ա�鼮��Ϣ�ļ�ָ��*/
    {
        p3 = fopen("memberbook.txt", "w");
        fclose(p3);
    }

    while (flag1) {
        system("cls");
        menu1();
        printf("\n");
        printf("����ѡ��(1-5):");
        choice1 = validateInput("121345");
        printf("%c", choice1);

        switch (choice1) {
            case '1': {  // ��¼
                int flag = 0;
                char account1[20];
                system("cls");
                fflush(stdin);
                fgets(account1, sizeof(account1), stdin);
                size_t len = strlen(account1);
                if (len > 0 && account1[len - 1] == '\n') {
                    account1[len - 1] = '\0';
                }
                flag = member_log_in(account1);
                if (flag == 2) {
                    system("cls");
                    fflush(stdin);
                    fgets(account1, sizeof(account1), stdin);
                    len = strlen(account1);
                    if (len > 0 && account1[len - 1] == '\n') {
                        account1[len - 1] = '\0';
                    }
                    flag = member_log_in(account1);
                }
                if (flag == 1) {
                    while (flag2 && flag3) {
                        system("cls");
                        menu2();
                        printf("\n");
                        printf("����ѡ��(1-4):");
                        choice2 = validateInput("12345678");
                        printf("%c", choice2);
                        switch (choice2) {
                            case '1': search_book(); break;
                            case '2': borrow_book(account1); break;
                            case '3': return_book(account1); break;
                            case '4': user_account((char *) 20); break;
                            case '5':
                                flag2 = 0;
                                printf("\n\n\t\t\t�����˳��û�����...");
                                break;
                            default: break;
                        }
                    }
                }
                break;
            }
            case '2': {  // ע��
                system("cls");
                printf("\n\n\n\t\t\t���ڽ����û�ע�����...");
                member_log_up();
                break;
            }
            case '3': {  // ����Ա��¼
                if (compare_password(ADMIN_password)) {
                    printf("\n\n\t\t\t\t  ����������ȷ\n\n\t\t\t\t���ڽ������Ա����\n");
                    while (flag2) {
                        system("cls");
                        menu3();
                        printf("\n");
                        printf("����ѡ��(1-8):");
                        choice3 = validateInput("12345678");
                        printf("%c", choice3);
                        switch (choice3) {
                            case '1': add_book(); break;
                            case '2': delete_book(); break;
                            case '3': modify_book(); break;
                            case '4': search_book(); break;
                            case '5': display_book(); break;
                            case '6': ADMIN_watch_member(); break;
                            case '7':
                                flag2 = 0;
                                printf("\n\n\t\t\t�����˳�����Ա����...");
                                break;
                            default: break;
                        }
                    }
                }
                else {
                    printf("\n\n\t\t\t\t  --�����������!--\n");
                }
                flag2 = 1;
                break;
            }
            case '4': {  // ����coder
                AboutMe();
                break;
            }
            case '5': {  // �˳�ϵͳ
                flag1 = 0;
                break;
            }
            default: break;
        }
    }
    fflush(stdin);
    system("cls");
    printf("�����˳�ϵͳ!(��������رս���)\n");
    getch();
    return 0;
}






void menu1() {
    printf("\n\n");
    printf("\t\t\t*=======================================================*\n");
    printf("\t\t\t||----------------------����ʹ��ͼ��������----------------||\n");
    printf("\t\t\t*     [1]     ���ߵ�¼                                    *|\n");
    printf("\t\t\t||    [2]     ����ע��                                   ||\n");
    printf("\t\t\t|*    [3]     ����Ա��¼                                  *|\n");
    printf("\t\t\t||    [4]     ����                                      ||\n");
    printf("\t\t\t|*    [5]     �˳�                                      *|\n");
    printf("\t\t\t*=======================================================*\n");
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
        fgets(newbook.number,sizeof(newbook.number),stdin);

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
            fgets(newbook.name, sizeof(newbook.name),stdin);

            printf("����������:");
            fgets(newbook.author, sizeof(newbook.author),stdin);

            printf("�����������:");
            fgets(newbook.press, sizeof(newbook.press),stdin);

            printf("���������(��ѧ/��ѧ/��ѧ/��ѧ/��):");
            fgets(newbook.category, sizeof(newbook.category),stdin);

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
                case '1':fgets(number_compare,sizeof(number_compare),stdin);strcpy(search,number_compare);flag1=0;break;
                case '2':fgets(name_compare,sizeof(name_compare),stdin);strcpy(search,name_compare);flag1=0;break;
                case '3':fgets(author_compare, sizeof(author_compare),stdin);strcpy(search,author_compare);flag1=0;break;
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
        fgets(search, sizeof(search),stdin);
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
        fgets(search, sizeof(search),stdin);
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
                            case '1':fgets(number, sizeof(number),stdin);flag1=0;flag2=check_repeat_book(number);
                                if(!flag2)
                                    strcpy(bookinfo[n].number,number);
                                break;
                            case '2':fgets(name, sizeof(name),stdin);strcpy(bookinfo[n].name,name);flag1=0;break;
                            case '3':fgets(author, sizeof(author),stdin);strcpy(bookinfo[n].author,author);flag1=0;break;
                            case '4':fgets(press, sizeof(press),stdin);strcpy(bookinfo[n].press,press);flag1=0;break;
                            case '5':fgets(category, sizeof(category),stdin);strcpy(bookinfo[n].category,category);flag1=0;break;
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
        fgets(search, sizeof(search),stdin);
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
        fgets(search, sizeof(search),stdin);
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

int check_repeat_book(char number[30]){
    FILE *p1;
    BOOKINFO bookinfo[100];
    int flag1=0,n,booknumber;

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
    for(n=0;n<booknumber;n++)
        if(strcmp(bookinfo[n].number,number)==0)
        {
            flag1=1;
            break;
        }
    if(flag1)
    {
        return 1;
    }
    else{
        return 0;
    }
}

int user_account(char account[20])//�û�������Ϣ
{
    FILE *p2, *p3;
    BOOKGRASP bookgrasp[1000];
    MEMBER member[1000];
    char new_password[20], key[20], choice;
    int n, i, flag = 0, flag1 = 1, flag2, number, booknumber;
    int count = 0;
    system("cls");
    p2 = fopen("infomember.txt", "r");
    number = 0;
    while (!feof(p2)) {
        fscanf(p2, "%s %s %s %s %s\n", member[number].ID, member[number].password,
               member[number].password_key, member[number].name, member[number].sex);
        number++;
    }
    fclose(p2);
    p3 = fopen("memberbook", "r");
    booknumber = 0;
    while (!feof(p3)) {
        fscanf(p3, "%s %s %s %s %s %f %s\n",
               bookgrasp[booknumber].number, bookgrasp[booknumber].name, bookgrasp[booknumber].author,
               bookgrasp[booknumber].press,
               bookgrasp[booknumber].category, &bookgrasp[booknumber].price, bookgrasp[booknumber].account);
        booknumber++;
    }
    fclose(p3);
    if (bookgrasp[0].price < 1) {
        printf("��ǰͼ���û�н�����Ϣ");
        flag = 0;
    } else {
        for (n = 0; n < number; n++) {
            if (strcmp(member[n].ID, account) == 0) {
                i = 0;
                printf("\n");
                printf("|---------------------------������Ϣ-------------------------|\n");
                printf("|����        �Ա�      ID              ����                  |\n");
                printf("|%-12s%-10s%-16s%-22s% |\n", member[n].name, member[n].sex, member[n].ID, member[n].password);
                printf("|                                                            |\n");
                printf("|----------------------------ͼ�������Ϣ--------------------|\n");
                printf("|���  ����        ����      ������          ���    ����    |\n");

                while (i < booknumber) {
                    if (strcmp(bookgrasp[i].account, account) == 0) {
                        printf("|%-6s%-12s%-10s%-16s%-8s%-8.1f|\n", bookgrasp[i].number,
                               bookgrasp[i].name, bookgrasp[i].author, bookgrasp[i].press,
                               bookgrasp[i].category, bookgrasp[i].price);
                        count++;
                    }
                    i++;
                }

                if (strcmp(member[n].sex, "male") == 0) {
                    printf("\n%s����ǰ���ĵ��鼮����%d����", member[n].name, count);
                } else if (strcmp(member[n].sex, "female") == 0) {
                    printf("\n%s����ǰ���ĵ��鼮����%d����", member[n].name, count);
                } else {
                    printf("\n%s����ǰ���ĵ��鼮����%d����", member[n].name, count);
                }
                if (bookgrasp[0].price <= 1) {
                    printf("\nͼ����ڹ���0���鼮���ڱ����ġ�\n");
                } else {
                    printf("\nͼ����ڹ���%d�������ڱ����ġ�\n", booknumber);
                }
                printf("\nPS:�Ƿ���Ҫ�޸�����(y/n):");
                fflush(stdin);
                choice = getch();
                while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n')
                    choice = getch();
                printf("%c", choice);
                printf("\n");
                if (choice == 'Y' || choice == 'y') {
                    printf("\n�������޸��������Կ(user_key):");
                    fflush(stdin);
                    fgets(key, sizeof(key),stdin);
                    if (strcmp(member[n].password_key, key) == 0) {
                        printf("�����������룺");
                        fflush(stdin);
                        fgets(new_password, sizeof(new_password),stdin);
                        strcpy(member[n].password, new_password);
                        flag = 1;
                        p2 = fopen("infomember.txt", "w");
                        for (n = 0; n < number; n++)
                            fprintf(p2, "%s %s %s %s %s\n", member[n].ID, member[n].password,
                                    member[n].password_key, member[n].name, member[n].sex);
                        fclose(p2);
                    } else {
                        printf("\n������Կ����,����ϵ����Ա");
                    }
                } else
                    flag = 0;
            }
        }
        if (flag = 1) {
            printf("�����޸ĳɹ�");
            printf("�����������");
            getch();
            return 1;
        } else {
            return 0;
        }
    }
    return 0;
}

void member_log_up() {
    char choice1, choice2;
    int flag = 1;
    FILE *p2;
    MEMBER member;

    while (1) {
        system("cls");
        fflush(stdin);

        printf("����ע��ID:");
        fgets(member.ID, sizeof(member.ID),stdin);

        flag = 0;
        printf("������������:");
        fgets(member.password, sizeof(member.password),stdin);

        printf("�����һ��������Կ(���������˻������벻�ܵ�½��):");
        fgets(member.password_key, sizeof(member.password_key),stdin);

        printf("������������:");
        fgets(member.name, sizeof(member.name),stdin);

        printf("���������Ա�(male/female):");
        fgets(member.sex, sizeof(member.sex),stdin);

        printf("�Ƿ񱣴����ע����Ϣ(y/n):");
        choice1 = getch();
        while (choice1 != 'Y' && choice1 != 'y' && choice1 != 'N' && choice1 != 'n')
            choice1 = getch();
        printf("%c", choice1);
        printf("\n");
        if (choice1 == 'Y' || choice1 == 'y') {
            p2 = fopen("infomember.txt", "a");
            fprintf(p2, "%s %s %s %s %s\n", member.ID, member.password,
                    member.password_key, member.name, member.sex);
            fclose(p2);
            printf("\n�����˻���ע��ɹ���\n");
        } else {
            printf("\n����ע����Ϣδ����!\n");

        }
    }
}

int member_log_in(char account[15])/*���ߵ�¼����*/
{
    FILE *p2;
    MEMBER member[100];
    char choice1;
    int flag1=0,flag2=1,n,k=3;
    int number;

    p2=fopen("infomember.txt","r");
    number=0;
    while(!feof(p2))
    {
        fscanf(p2,"%s %s %s %s %s\n",member[number].ID,member[number].password,
               member[number].password_key,member[number].name,member[number].sex);
        number++;
    }
    fclose(p2);
    for(n=0;n<number;n++)
        if(strcmp(member[n].ID,account)==0)
        {
            flag1=1;
            break;
        }
    if(flag1)
    {
        while(flag2)
        {
            if(compare_password(member[n].password))/* ��������ȶԺ��� */
            {
                printf("\n\n\n\t\t\t   �˶���ȷ�����ڽ����û���¼����...");
                return 1;
            }
            else{
                --k;/*�����������count*/
                if(k!=0)
                {
                    printf("\n\n\n\t\t\t   ����������������!����%d�λ��������������룡",k);
                    printf("\n\t\t\t   ���Ƿ�Ҫ������������(y/n):");
                    fflush(stdin);
                    choice1=getch();
                    while(choice1!='Y'&&choice1!='y'&&choice1!='N'&&choice1!='n')
                        choice1=getch();
                    printf("%c",choice1);
                    printf("\n");
                    if(choice1=='Y'||choice1=='y')
                        flag2=1;
                    else
                        return 0;
                }
                else{
                    printf("\n\n\t\t\t   ��������������꣡��������˳�...");
                    fflush(stdin);
                    getch();
                    return 0;
                }
            }
        }
        flag2=1;
    }
    else{
        printf("\n\n\n\t\t\t  ��ID��δע�ᣡ");
        return 0;

    }
    return 0;
}

void ADMIN_watch_member()/*�鿴������Ϣ����*/
{
    FILE *p2;
    MEMBER member[100];
    int n,number;
    system("cls");
    fflush(stdin);

    p2=fopen("infomember.txt","r");
    number=0;
    while(!feof(p2))
    {
        fscanf(p2,"%s %s %s %s %s\n",member[number].ID,member[number].password,
               member[number].password_key,member[number].name,member[number].sex);
        number++;
    }
    fclose(p2);

    printf("ϵͳע���û���%dλ:",number);
    printf("\n\n");
    printf("|-----------------------��Ա��Ϣ-----------------------|\n");
    printf("|����      �Ա�    ID            ����  	         ��Կ  |\n");
    for(n=0;n<number;n++)
        printf("|%-10s%-8s%-14s%-16s%-6s%|\n",member[n].name,member[n].sex,
               member[n].ID,member[n].password,member[n].password_key);

    printf("\n\n�������������һ���˵�!\n");
    getch();
}

int compare_password(char *password)/*����ȶԺ��� */
{
    int i=0;
    char compare[20],c;
    fflush(stdin);
    printf("\n\t\t\t   ����(password):");
    while((c=getch())!=13)//\r�ǽ�����Ƶ�������λ
    {
        if(c==8&&i>0)
        {
            printf("\b \b");//���*�źʹ��
            i--;
            continue;
        }
        if(c!=8)
        {
            compare[i++]=c;
            putchar('*');
        }
    }
    compare[i]='\0';
    if(strcmp(password,compare)==0)
    {
        printf("\a");  //����
        return 1;
    }
    else
    {
        printf("\a");  //����
        return 0;
    }
}