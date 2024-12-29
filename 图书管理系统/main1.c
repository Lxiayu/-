#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//�궨����
#define MAX_USERS 100
#define BUFFER_SIZE 20
#define MAX_BOOKS 100

typedef struct book_system{
    char name[20];//����
    char author[20];//����
    char press[20];//������
    char isbn[20];//Ψһ��ʶ��isbn
    char category[20];//���
    int price;//�۸�
    int num;//����
}Book;
typedef struct user_system{
    char id[20];//�û�id
    char name[20];//�û���
    char password[20];//����
    char phone[20];//�绰����
    int num;//��������
}User;
typedef struct borrow_system{
    char id[20];//�û�id
    char book_name[20];//����
    char isbn[20];//Ψһ��ʶ��isbn
    int num;//��������
    int time;//����ʱ��
    int price;//������
}Borrow;
//������
int File_open();//������⺯��
void menu1();//�˵�1
void about_menu();//����
void menu2();//�˵�2
void menu3();//�˵�3
//����ע�ắ��
void user_register();
//���ߵ�¼��غ�����
int user_login();//���ߵ�¼
int user_login_verify(char password[20]);//����������֤
void all_book();//ȫ��ͼ��
void borrow_book(char id[20]);//����ͼ��
void return_book(char id[20]);//����
void user_info(char id[20]);//������Ϣ
void print_user_info(const User *user);//���������Ϣ
void modify_user_info(User *user);//�޸Ķ�����Ϣ
void load_books(FILE *file, Book books[], int *count);//��ȡͼ����Ϣ
void load_borrows(FILE *file, Borrow borrows[], int *count);//��ȡ������Ϣ
void save_books(FILE *file, Book books[], int count);//����ͼ����Ϣ
void save_borrows(FILE *file, Borrow borrows[], int count);//���������Ϣ
//����Ա��غ�����
void Administrator();//����Ա������
#define ADMIN_password "123456"//����Ա��¼����
void add_book();//����ͼ��
void delete_book();//ɾ��ͼ��
void modify_book();//�޸�ͼ����Ϣ
void search_book();//��ѯͼ��
void all_user();//ȫ��������Ϣ
void all_borrow();//ȫ��������Ϣ


int main(){
    int flag=0,k;
    flag = File_open();
    if(flag==0){
        printf("�����ļ���ʧ�ܣ�����\n");
        printf("��������˳�...\n");
        getchar();
        exit(0);//�˳�����
    }else{
        printf("�����ļ��򿪳ɹ�\n");
        printf("���ڴ�ͼ��������\n");
        while(1){
            menu1();
            printf("����������ѡ��");
            scanf_s("%d",&k,3);
            switch(k){
                case 1:
                    printf("����ǰ���û���¼ҳ�棡\n");
                    user_login();
                    break;
                case 2:
                    user_register();
                    break;
                case 3:
                    printf("����ǰ�ڹ���Աҳ�棡\n");
                    Administrator();
                    break;
                case 4:
                    printf("����ǰ�ڹ���ҳ�棡\n");
                    about_menu();
                    break;
                case 5:
                    printf("��л����ʹ�ã��ټ���\n");
                    exit(0);
                default:
                    printf("���������������������룡\n");
                    break;
            }
        }
    }
}
void all_borrow(){
    FILE *p1 = fopen("borrow.txt", "r");
    if (p1 == NULL) {
        perror("�ļ���ʧ��");//���ļ�ʧ��
        return;
    }
    Borrow borrows[MAX_BOOKS];
    int number = 0;
    while (number < MAX_BOOKS && fscanf(p1, "%19s %49s %19s %d %d %d",
                                        borrows[number].id, borrows[number].book_name,
                                        borrows[number].isbn, &borrows[number].num,
                                        &borrows[number].time, &borrows[number].price) == 6) {
        number++;
    }
    fclose(p1);
    printf("���\t�û�id\tͼ������\tisbn\t��������\t����ʱ��\t������\n");
    for (int i = 0; i < number; i++) {
        printf("%d\t%s\t%s\t%s\t%d\t%d\t%d\n", i + 1, borrows[i].id, borrows[i].book_name,
               borrows[i].isbn, borrows[i].num, borrows[i].time, borrows[i].price);
    }
}
void all_user() {
    FILE *p1 = fopen("user.txt", "r");
    if (p1 == NULL) {
        perror("�ļ���ʧ��");//���ļ�ʧ��
        return;
    }

    User users[MAX_USERS];
    int number = 0;
    while (number < MAX_USERS && fscanf(p1, "%19s %49s %19s %14s %d",
                                        users[number].id, users[number].name,
                                        users[number].password, users[number].phone,
                                        &users[number].num) == 5) {
        number++;
    }

    fclose(p1);

    printf("���\t�û�id\t�û���\t����\t�绰����\t��������\n");
    for (int i = 0; i < number; i++) {
        printf("%d\t%s\t%s\t%s\t%s\t%d\n", i + 1, users[i].id, users[i].name, users[i].password, users[i].phone, users[i].num);
    }
}
void search_book(){
    FILE *p1;
    int number = 0, flag = 1, i,flag2=1,found=0;
    char name[20], choice[3],choice1[3],choice2[2];
    Book books[MAX_BOOKS];
    p1 = fopen("book.txt", "r");
    load_books(p1, books, &number);
    fclose(p1);
    while(flag){
        printf("��������Ҫ��ѯ���鼮���ƣ�");
        scanf_s("%s", name, 20);
        for(i=0;i<number;i++){
            if(strcmp(name,books[i].name)==0){
                found=1;
                break;
            }
        }
        if(found){
            printf("��ͼ����ڣ�����Ϊ��ѯ���鼮��Ϣ��\n");
            printf("���\t����\t����\t������\tisbn\t���\t�۸�\t����\n");
            printf("%d\t%s\t%s\t%s\t%s\t%s\t%d\t%d\n",i+1,books[i].name,books[i].author,books[i].press
                   ,books[i].isbn,books[i].category,books[i].price,books[i].num);
            printf("�Ƿ������ѯ����y/n��");
            scanf_s("%s",choice,3);
            if(choice[0]=='y'||choice[0]=='Y'){
                flag=1;
            }else{
                flag = 0;
            }
        }else{
            printf("��ͼ�鲻���ڣ�������������飡\n");
            printf("�Ƿ����²�ѯ����y/n��");
            scanf_s("%s",choice1,3);
            if(choice1[0]=='y'||choice1[0]=='Y'){
                flag=1;
            }else{
                flag = 0;
            }
        }
    }
}
void modify_book(){
    FILE *p1;
    int number = 0, flag = 1, i,flag2=1,found=0;
    char name[20], choice[3],choice1[3],choice2[2];
    Book books[MAX_BOOKS];
    p1 = fopen("book.txt", "r");
    load_books(p1, books, &number);
    fclose(p1);
    while(flag){
        printf("��������Ҫ�޸ĵ��鼮���ƣ�");
        scanf_s("%s", name, 20);
        for(i=0;i<number;i++){
            if(strcmp(name,books[i].name)==0){
                found=1;
                break;
            }
        }
        if(found){
            printf("��ͼ����ڣ��Ƿ�ȷ���޸ģ���y/n��");
            scanf_s("%s",choice,3);
            if(choice[0]=='y'||choice[0]=='Y'){
                flag2=1;
            }else{
                printf("����ȡ���޸Ĳ�����\n");
                flag2 = 0;
                flag = 0;
            }
        }else{
            printf("��ͼ�鲻���ڣ�������������飡\n");
            flag2 = 0;
            flag = 1;
        }
        if(flag2){
            printf("�����ͨ������������鼮��ϸ��Ϣ���޸�\n");
            printf("1.����  2.����  3.������  4.isbn  5.���  6.�۸�  7.����  8.ȡ���޸�\n");
            scanf_s("%d",choice1,3);
            switch(choice1[0]){
                case 1:
                    printf("�������µ�������");
                    scanf_s("%s", books[i].name, 20);
                    break;
                case 2:
                    printf("�������µ����ߣ�");
                    scanf_s("%s", books[i].author, 20);
                    break;
                case 3:
                    printf("�������µĳ����磺");
                    scanf_s("%s", books[i].press, 20);
                    break;
                case 4:
                    printf("�������µ�isbn��");
                    scanf_s("%s", books[i].isbn, 20);
                    break;
                case 5:
                    printf("�������µ����");
                    scanf_s("%s", books[i].category, 20);
                    break;
                case 6:
                    printf("�������µļ۸�");
                    scanf_s("%d", &books[i].price, 3);
                    break;
                case 7:
                    printf("�������µ�������");
                    scanf_s("%d", &books[i].num, 3);
                    break;
                case 8:
                    printf("ȡ���޸�\n");
                    break;
                default:
                    printf("�����������������룡\n");
                    break;
            }
            p1 = fopen("book.txt", "w");
            save_books(p1, books, number);
            fclose(p1);
            printf("ͼ����Ϣ�޸ĳɹ���\n");
            printf("�����Ƿ�����޸ģ���y/n��");
            scanf_s("%s", choice2, 3);
            if(choice2[0]=='y'||choice2[0]=='Y'){
                flag = 1;
            }else{
                flag = 0;
            }
        }
    }
}
void delete_book() {
    FILE *p1, *p2;  // ����һ���ļ�ָ��������ʱ�ļ�
    int number = 0, flag = 0, i;
    char name[20], choice[3];
    printf("�㵱ǰ��ɾ��ͼ�����");
    Book books[MAX_BOOKS];
    p1 = fopen("book.txt", "r");
    if (p1 == NULL) {
        perror("���ļ�book.txtʧ��");
        return;
    }
    load_books(p1, books, &number);
    fclose(p1);

    printf("��������Ҫɾ�����鼮��ע�⣬��ֻɾ��������������һ���飬��ʹ���޸�ͼ����Ϣ����");
    printf("������Ҫɾ�����鼮���ƣ�");
    scanf_s("%s", name, 20);

    for (i = 0; i < number; i++) {
        if (strcmp(name, books[i].name) == 0) {
            flag = 1;
            break;
        }
    }

    if (flag) {
        printf("��ͼ����ڣ��Ƿ�ȷ��ɾ������y/n��");
        scanf_s("%s", choice, 3);
        if (choice[0] == 'y' || choice[0] == 'Y') {
            p2 = fopen("temp_book.txt", "w");  // ����ʱ�ļ�����д�뱣��������
            if (p2 == NULL) {
                perror("����ʱ�ļ�temp_book.txtʧ��");
                return;
            }
            for (int j = 0; j < number; j++) {
                if (j!= i) {
                    fprintf(p2, "%s %s %s %s %s %d %d\n", books[j].name, books[j].author,
                            books[j].press, books[j].isbn, books[j].category, books[j].price,
                            books[j].num);
                }
            }
            fclose(p2);
            fclose(p1);
            remove("book.txt");  // ɾ��ԭ�ļ�
            rename("temp_book.txt", "book.txt");  // ����ʱ�ļ�������Ϊԭ�ļ���
            if (remove("book.txt")!= 0) {
                perror("ɾ��book.txt�ļ�ʧ��");
                return;
            }
            if (rename("temp_book.txt", "book.txt")!= 0) {
                perror("��������ʱ�ļ�ʧ��");
                return;
            }
            printf("ͼ����Ϣɾ���ɹ���\n");
            printf("�����������...\n");
            getchar();
        } else {
            printf("����ȡ��ɾ��������\n");
        }
    } else {
        printf("��ͼ�鲻���ڣ����������룡\n");
    }
}
void add_book(){
    FILE *p1;
    int flag=1,number=0,flag1=0,price,num;
    char name[20],author[20],press[20],isbn[20],category[20],choice[3];
    printf("�㵱ǰ������ͼ�����\n");
    printf("��ע�����Ƿ��ظ����ͼ�飬�����޸�����ͼ�����ݣ���ʹ���޸�ͼ��ѡ�\n");
    Book books[MAX_USERS];
    int count=0;
    p1 = fopen("book.txt", "r");
    load_books(p1, books, &count);
    fclose(p1);
    while(flag){
        printf("������ͼ�����ƣ�");
        scanf_s("%s",name,20);
        for(int i=0;i<count;i++){//�ж��Ƿ��ظ����ͼ��
            if(strcmp(name,books[i].name)==0){
                flag1 = 1;
                break;
            }
        }
        if(flag1){
            printf("��ͼ���Ѵ��ڣ����������룡\n");
            flag = 1;
        }else{
            printf("������ͼ�����ߣ�");
            scanf_s("%s",author,20);
            printf("������ͼ������磺");
            scanf_s("%s",press,20);
            printf("������ͼ��isbn��");
            scanf_s("%s",isbn,20);
            printf("������ͼ�����");
            scanf_s("%s",category,20);
            printf("������ͼ��۸�");
            scanf_s("%d",&price,5);
            printf("������ͼ��������");
            scanf_s("%d",&num,5);
            p1 = fopen("book.txt", "a");
            fprintf(p1, "\n%s %s %s %s %s %d %d", name, author, press, isbn, category, price, num);
            fclose(p1);
            printf("ͼ����ӳɹ���\n");
            printf("�Ƿ�������ͼ�飿��y/n��");
            scanf_s("%s",choice,3);
            if(choice[0]=='y'||choice[0]=='Y'){
                flag = 1;
            }else{
                flag = 0;
            }
        }
    }
}
void Administrator(){
    int flag=1,k;
    char password[20];
    printf("���������Ա���룺");
    scanf_s("%s",password,20);
    if(strcmp(password,ADMIN_password)==0){
        printf("����Ա��¼�ɹ���\n");
        printf("���ڴ򿪹���Աҳ��\n");
        while(flag){
            menu3();
            printf("����������ѡ��");
            scanf_s("%d",&k,3);
            switch(k){
                case 1:
                    //����ͼ��
                    add_book();
                    break;
                case 2:
                    //ɾ��ͼ��
                    delete_book();
                    break;
                case 3:
                    //�޸�ͼ����Ϣ
                    modify_book();
                    break;
                case 4:
                   //��ѯͼ��
                    search_book();
                    break;
                case 5:
                    //��ʾ����ͼ����Ϣ
                    all_book();
                    break;
                case 6:
                    //��ʾ�����û���Ϣ
                    all_user();
                    break;
                case 7:
                    //��ʾ���н�����Ϣ
                    all_borrow();
                    break;
                case 8:
                    //�˳�����Աϵͳ
                    flag = 0;
                    break;
                default:
                    printf("���������������������룡\n");
                    break;
            }
        }
    }else{
        printf("����Ա��¼ʧ��,�������룡\n");
    }
}
void user_register() {
    FILE *p1;
    User user_system[MAX_USERS];
    int number = 0, flag = 1, flag1 = 1;
    char n[BUFFER_SIZE], k[BUFFER_SIZE], g[BUFFER_SIZE], a[BUFFER_SIZE], m[3];

    printf("��ӭʹ���û�ע�Ṧ�ܣ�\n");

    // ��ȡ�����û���Ϣ
    p1 = fopen("user.txt", "r");
    if (p1 == NULL) {
        printf("�޷����ļ� user.txt\n");
        return;
    }
    while (fscanf(p1, "%s %s %s %s %d", user_system[number].id, user_system[number].name, user_system[number].password, user_system[number].phone, &user_system[number].num) == 5 && number < MAX_USERS) {
        number++;
    }
    fclose(p1);

    while (flag) {
        printf("�����������û�����");
        scanf_s("%s", n, BUFFER_SIZE);
        printf("�������������룺");
        scanf_s("%s", k, BUFFER_SIZE);
        printf("���������ĵ绰���룺");
        scanf_s("%s", g, BUFFER_SIZE);
        printf("����������id��");
        scanf_s("%s", a, BUFFER_SIZE);

        flag1 = 1;
        for (int i = 0; i < number; i++) {
            if (strcmp(user_system[i].id, a) == 0) {
                printf("��id�ѱ�ע�ᣬ���������룡\n");
                flag1 = 0;
                break;
            }
        }

        if (flag1) {
            printf("�õģ�����ע����Ϣ�Ѿ���������ӭ����ʹ��\n");
            p1 = fopen("user.txt", "a");
            if (p1 == NULL) {
                printf("�޷����ļ� user.txt\n");
                return;
            }
            fprintf(p1, "%s %s %s %s %d\n", a, n, k, g, 0);
            fclose(p1);
        } else {
            continue;
        }

        printf("�Ƿ�Ҫ����ע�᣿��y/n��");
        scanf_s("%s", m, 3);
        if (m[0] == 'y' || m[0] == 'Y') {
            flag = 1;
        } else {
            flag = 0;
        }
    }
}
void user_info(char *id) {
    FILE *p1 = NULL;
    int flag = 1, number = 0;
    char n[3], k[3], g[3], a[3];
    User user_system[MAX_USERS];

    printf("��ӭʹ�ö�����Ϣ��ѯ���ܣ�\n");

    while (flag) {
        p1 = fopen("user.txt", "r");
        if (p1 == NULL) {
            printf("�޷����ļ� user.txt\n");
            return;
        }

        while (number < MAX_USERS && fscanf(p1, "%s %s %s %s %d", user_system[number].id, user_system[number].name,
                                           user_system[number].password, user_system[number].phone,
                                           &user_system[number].num) == 5) {
            number++;
        }
        fclose(p1);

        int found = 0;
        for (int i = 0; i < number; i++) {
            if (strcmp(user_system[i].id, id) == 0) {
                found = 1;
                printf("������Ϣ���£�\n");
                print_user_info(&user_system[i]);

                printf("�Ƿ�Ҫ�޸�������Ϣ����y/n��");
                scanf_s("%s", n, _countof(n));

                if (n[0] == 'y' || n[0] == 'Y') {
                    modify_user_info(&user_system[i]);

                    p1 = fopen("user.txt", "w");
                    if (p1 == NULL) {
                        printf("�޷����ļ� user.txt\n");
                        return;
                    }

                    for (int j = 0; j < number; j++) {
                        fprintf(p1, "%s %s %s %s %d\n", user_system[j].id, user_system[j].name,
                                user_system[j].password, user_system[j].phone, user_system[j].num);
                    }
                    fclose(p1);

                    printf("�޸ĳɹ���\n");
                    printf("�Ƿ�鿴���޸ĺ����Ϣ����y/n��");
                    scanf_s("%s", g, _countof(g));

                    if (g[0] == 'y' || g[0] == 'Y') {
                        print_user_info(&user_system[i]);
                        printf("�Ƿ�Ҫ����ʹ�ã���y/n��");
                        scanf_s("%s", a, _countof(a));
                        if (a[0] != 'y' && a[0] != 'Y') {
                            printf("��л����ʹ�ã��ټ���\n");
                            flag = 0;
                        }
                    } else {
                        printf("��л����ʹ�ã��ټ���\n");
                        flag = 0;
                    }
                } else {
                    printf("��л����ʹ�ã��ټ���\n");
                    flag = 0;
                }
                break;
            }
        }

        if (!found) {
            printf("δ�ҵ�ƥ����û���Ϣ��\n");
            flag = 0;
        }
    }
}
void return_book(char *id) {
    FILE *p1, *p2;
    int number = 0, number1 = 0;
    char choice1[20], choice2[3];
    Book book_system[1000];
    Borrow borrow_system[1000];

    // Load data from files
    if ((p1 = fopen("book.txt", "r")) == NULL) {
        printf("�޷��� book.txt �ļ���\n");
        return;
    }
    if ((p2 = fopen("borrow.txt", "r")) == NULL) {
        fclose(p1);
        printf("�޷��� borrow.txt �ļ���\n");
        return;
    }

    load_books(p1, book_system, &number);
    load_borrows(p2, borrow_system, &number1);

    fclose(p1);
    fclose(p2);

    printf("�㵱ǰ���ĵ�ͼ�����£�\n");
    printf("����id\t����\tisbn\t��������\t����ʱ��\t������\n");
    for (int t = 0; t < number1; t++) {
        if (strcmp(borrow_system[t].id, id) == 0) {
            printf("%s\t%s\t%s\t%d\t%d\t%d\n", borrow_system[t].id, borrow_system[t].book_name,
                   borrow_system[t].isbn, borrow_system[t].num, borrow_system[t].time, borrow_system[t].price);
        }
    }

    int flag = 1;
    while (flag) {
        printf("������Ҫ�黹��������");
        scanf("%19s", choice1);

        int index = -1;
        for (int i = 0; i < number1; i++) {
            if (strcmp(borrow_system[i].book_name, choice1) == 0 && strcmp(borrow_system[i].id, id) == 0) {
                index = i;
                break;
            }
        }

        if (index != -1) {
            printf("�Ƿ�ȷ�Ϲ黹����y/n��");
            scanf("%2s", choice2);

            if (choice2[0] == 'y' || choice2[0] == 'Y') {
                // ����ͼ��������
                int book_index = -1;
                for (int j = 0; j < number; j++) {
                    if (strcmp(book_system[j].name, choice1) == 0) {
                        book_index = j;
                        break;
                    }
                }

                if (book_index == -1) {
                    printf("���ִ���δ�ҵ���Ӧͼ����Ϣ��\n");
                    return;
                }

                book_system[book_index].num += borrow_system[index].num;

                // ɾ�����ļ�¼
                for (int k = index; k < number1 - 1; k++) {
                    borrow_system[k] = borrow_system[k + 1];
                }
                number1--;

                // ������º�����ݵ��ļ�
                if ((p1 = fopen("book.txt", "w")) == NULL) {
                    printf("�޷��� book.txt �ļ���\n");
                    return;
                }
                if ((p2 = fopen("borrow.txt", "w")) == NULL) {
                    fclose(p1);
                    printf("�޷��� borrow.txt �ļ���\n");
                    return;
                }

                save_books(p1, book_system, number);
                save_borrows(p2, borrow_system, number1);

                fclose(p1);
                fclose(p2);

                printf("����ɹ���\n");
            }
        } else {
            printf("δ�ҵ�����ǰ�����鼮���Ƿ����ԣ���y/n��");
            scanf("%2s", choice2);
            if (choice2[0] != 'y' && choice2[0] != 'Y') {
                flag = 0;
            }
        }

        if (flag) {
            printf("�Ƿ�������飿��y/n��");
            scanf("%2s", choice2);
            if (choice2[0] != 'y' && choice2[0] != 'Y') {
                flag = 0;
            }
        }
    }
}
void borrow_book(char *id){
    FILE *p1 , *p2;
    int number = 0,number1 = 0,n,flag = 0;
    char choice1;
    char choice2[20];
    Book book_system[1000];
    Borrow borrow_system[1000];
    p1 = fopen("book.txt", "r");
    p2 = fopen("borrow.txt", "r");
    while(number < 1000 && fscanf(p1, "%s %s %s %s %s %d %d\n", book_system[number].name, book_system[number].author,
                                  book_system[number].press, book_system[number].isbn,book_system[number].category,
                                  &book_system[number].price, &book_system[number].num)) {
        number++;
    }
    while (number1 < 1000 && fscanf(p2, "%s %s %s %d %d %d\n", borrow_system[number1].id, borrow_system[number1].book_name,
                                      borrow_system[number1].isbn, &borrow_system[number1].num,
                                      &borrow_system[number1].time, &borrow_system[number1].price)) {
        number1++;
    }
    fclose(p1);//�ر��ļ�
    fclose(p2);
    for (n = 0; n < number; n++) {
        printf("������Ҫ���ĵ�������");
        scanf_s("%s",choice2,20);
        if (strcmp(book_system[number].name,choice2) == 0) {
            flag = 1;
            break;
        }else{
            printf("δ�ҵ������鼮���Ƿ����ԣ���y/n��");
            char i;
            scanf_s("%s", &i, 3);
            if(i == 'y'|| i == 'Y'){
                continue;
            }else{
                printf("����ȡ�����ģ�\n");
                return;
            }
        }
    }
    if(flag){
        printf("��Ҫ���ĵ����ڹݣ��Ƿ�ȷ�Ͻ��ģ���y/n��");
        scanf_s("%s", &choice1, 3);
        if (choice1 == 'y'|| choice1 == 'Y') {
            p2 = fopen("borrow.txt", "a");
            fprintf(p2, "%s %s %s %d %d %d\n", id, book_system[number].name, book_system[number].isbn, 1, 0, 0);
            printf("���ĳɹ���\n");
            fclose(p2);
        } else {
            printf("����ȡ�����ģ�\n");

        }
    }
}
void all_book() {
    FILE *p2;
    int number = 0, n;
    Book *book_system = (Book *)malloc(MAX_BOOKS * sizeof(Book));
    if (book_system == NULL) {
        printf("�ڴ����ʧ��\n");
        return;
    }//��̬�����ڴ棬ʹ����numberС��1000��ʱ�򲻻��ȡ������Ŀ���Ϣ����ֻ��ȡ��Ч��Ϣ��

    printf("ͼ����Ϣ���£�\n");
    p2 = fopen("book.txt", "r");
    if (p2 == NULL) {
        printf("�޷����ļ� book.txt\n");
        free(book_system);
        return;
    }

    while (number < MAX_BOOKS && fscanf(p2, "%99s %99s %99s %19s %49s %d %d",
                                        book_system[number].name, book_system[number].author,
                                        book_system[number].press, book_system[number].isbn,
                                        book_system[number].category, &book_system[number].price,
                                        &book_system[number].num) == 7) {
        number++;
    }

    fclose(p2);
    printf("����Ϊ�ݲ���Ϣ��\n");
    printf("���\t����\t����\t������\tisbn\t���\t�۸�\t����\n");
    for (n = 0; n < number; n++) {
        printf("%d\t%s\t%s\t%s\t%s\t%s\t%d\t%d\n", n + 1, book_system[n].name, book_system[n].author,
               book_system[n].press, book_system[n].isbn, book_system[n].category, book_system[n].price,
               book_system[n].num);
    }
    free(book_system);//�ͷ��ڴ�
}
int user_login(){
    FILE *p1;
    User user_system[100];
    int number = 0,n,k = 5,b;
    char id[20], password[20],choice1;
    int flag = 0;
    p1 = fopen("user.txt", "r");
    while (number < 100 && fscanf(p1, "%s %s %s %s %d\n", user_system[number].id, user_system[number].name,
                                  user_system[number].password, user_system[number].phone, &user_system[number].num)) {
        number++;
    }//ѭ����ȡ�ļ��е�����
    fclose(p1);//�ر��ļ�
    printf("����������id��");
    scanf_s("%s", id,20);
    for (n = 0; n < number; n++) {
        if (strcmp(user_system[n].id, id) == 0) {
            flag = 1;
            break;
        }
    }
    if (flag) {
        while (k > 0) {
            if (user_login_verify(user_system[n].password)) {//����˶�
                printf("�˶���ȷ�������û���¼����...");
                while (1) {
                    menu2();
                    printf("����������ѡ��");
                    scanf_s("%d", &b, 3);
                    switch (b) {
                        case 1:
                            //��ѯͼ��ݲ���Ϣ
                            all_book();
                            break;
                        case 2:
                            //����ͼ��
                            borrow_book(id);
                            break;
                        case 3:
                            //����
                            return_book(id);
                            break;
                        case 4:
                            //�˻���Ϣ
                            user_info(id);
                            break;
                        case 5:
                            //��ѯͼ��
                            search_book();
                            break;
                        case 6:
                            printf("���ѳɹ��˳���¼��\n");
                            return 0;
                        default:
                            printf("���������������������룡\n");
                            break;
                    }
                }
            } else {
                --k;
                if (k > 0) {
                    printf("����������������!����%d�λ��������������룡", k);
                    printf("���Ƿ�Ҫ������������(y/n): ");
                    choice1 = getchar();
                    while ((choice1 != 'Y') && (choice1 != 'y') && (choice1 != 'N') && (choice1 != 'n')) {
                        choice1 = getchar();
                    }
                    if (choice1 == 'Y' || choice1 == 'y') {
                        continue;
                    } else {
                        return 2;
                    }
                } else {
                    printf("��������������꣡��������˳�...");
                    getchar();
                    return 0;
                }
            }
        }
    } else {
        printf("��ID��δע�ᣡ\n");
        return 0;
    }
    return 0;
}
int user_login_verify(char *password){
    int i=0;
    char compare[20];
    fflush(stdin);
    printf("����(password):");
    scanf_s("%s",compare,20);
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
int File_open(){
    FILE *p1,*p2,*p3;
    if((p1=fopen("book.txt","r"))==NULL){
        printf("ͼ���ļ���ʧ��\n");
        return 0;
    }else{
        printf("ͼ���ļ��򿪳ɹ�\n");
        if((p2=fopen("user.txt","r"))==NULL){
            printf("�û��ļ���ʧ��\n");
            return 0;
        }else{
            printf("�û��ļ��򿪳ɹ�\n");
            if((p3=fopen("borrow.txt","r"))==NULL){
                printf("�����ļ���ʧ��\n");
                return 0;
           }else{
            printf("�����ļ��򿪳ɹ�\n");}
        }
    }
    return 1;
}
void print_user_info(const User *user) {
    printf("����id\t�û���\t����\t�绰����\t��������\n");
    printf("%s\t%s\t%s\t%s\t%d\n", user->id, user->name, user->password, user->phone, user->num);
}
void modify_user_info(User *user) {
    char choice[3];
    printf("������Ҫ�޸ĵ���Ϣ(ע���ɶ�1.�û���  2.����  3.�绰����  �����޸�)��");
    scanf_s("%s", choice, _countof(choice));

    if (choice[0] == '1') {
        printf("�������µ��û�����");
        scanf_s("%s", user->name, _countof(user->name));
    } else if (choice[0] == '2') {
        printf("�������µ����룺");
        scanf_s("%s", user->password, _countof(user->password));
    } else if (choice[0] == '3') {
        printf("�������µĵ绰���룺");
        scanf_s("%s", user->phone, _countof(user->phone));
    } else {
        printf("�����������������룡\n");
    }
}
void load_books(FILE *file, Book books[], int *count) {
    while (*count < 1000 && fscanf(file, "%s %s %s %s %s %d %d\n",
                                   books[*count].name, books[*count].author,
                                   books[*count].press, books[*count].isbn,
                                   books[*count].category, &books[*count].price,
                                   &books[*count].num) == 7) {
        (*count)++;
    }
}
void load_borrows(FILE *file, Borrow borrows[], int *count) {
    while (*count < 1000 && fscanf(file, "%s %s %s %d %d %d\n",
                                   borrows[*count].id, borrows[*count].book_name,
                                   borrows[*count].isbn, &borrows[*count].num,
                                   &borrows[*count].time, &borrows[*count].price) == 6) {
        (*count)++;
    }
}
void save_books(FILE *file, Book books[], int count) {
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s %s %s %s %s %d %d\n", books[i].name, books[i].author,
                books[i].press, books[i].isbn, books[i].category,
                books[i].price, books[i].num);
    }
}
void save_borrows(FILE *file, Borrow borrows[], int count) {
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s %s %s %d %d %d\n", borrows[i].id, borrows[i].book_name,
                borrows[i].isbn, borrows[i].num,
                borrows[i].time, borrows[i].price);
    }
}
void menu1(){
    printf("\n\n");
    printf("\t\t\t*=======================================================*\n");
    printf("\t\t\t||-------------------����ʹ��ͼ��������-------------------||\n");
    printf("\t\t\t*     [1]     ���ߵ�¼                                    *|\n");
    printf("\t\t\t||    [2]     ����ע��                                   ||\n");
    printf("\t\t\t|*    [3]     ����Ա��¼                                  *|\n");
    printf("\t\t\t||    [4]     ����                                      ||\n");
    printf("\t\t\t|*    [5]     �˳�                                      *|\n");
    printf("\t\t\t*=======================================================*\n");
}
void menu2(){
    printf("\n\n");
    printf("\t\t\t*=======================================================*\n");
    printf("\t\t\t||------------------------�û���¼ ---------------------||\n");
    printf("\t\t\t||    [1]     ��ѯ�ݲ�ͼ����Ϣ                            ||\n");
    printf("\t\t\t|*    [2]     ����ͼ��                                   *|\n");
    printf("\t\t\t||    [3]     �黹ͼ��                                   ||\n");
    printf("\t\t\t|*    [4]     �˻���Ϣ                                   *|\n");
    printf("\t\t\t||    [5]     ��ѯͼ��                                   ||\n");
    printf("\t\t\t||    [6]     �˳���¼                                   ||\n");
    printf("\t\t\t*=======================================================*\n");
}
void menu3(){
    printf("\n\n");
    printf("\t\t\t*=======================================================*\n");
    printf("\t\t\t||-----------------------����Ա��¼ ---------------------||\n");
    printf("\t\t\t||    [1]     ����ͼ��                                   ||\n");
    printf("\t\t\t|*    [2]     ɾ��ͼ��                                   *|\n");
    printf("\t\t\t||    [3]     �޸�ͼ����Ϣ                                ||\n");
    printf("\t\t\t|*    [4]     ����ͼ��                                   *|\n");
    printf("\t\t\t||    [5]     ��ʾ����ͼ����Ϣ                             ||\n");
    printf("\t\t\t||    [6]     ��ʾ�����û���Ϣ                             ||\n");
    printf("\t\t\t||    [7]     ��ʾ���н�����Ϣ                              ||\n");
    printf("\t\t\t||    [8]     �˳�����Աϵͳ                               ||\n");
    printf("\t\t\t*=======================================================*\n");
}
void about_menu(){
    printf("\n\n");
    printf("\t\t\t*=======================================================*\n");
    printf("\t\t\t||------------------------ ���� ------------------------||\n");
    printf("\t\t\t|            ���241���    202400406040                |\n");
    printf("\t\t\t|                                                       |\n");
    printf("\t\t\t|             C_V1.0  ͼ��ݹ������  24/12/10             |\n");
    printf("\t\t\t|                                                       |\n");
    printf("\t\t\t|       ˼·��ʵ��:�廪��ѧ������-C���Դ����ŵ���ͨ             |\n");
    printf("\t\t\t|                ֪��-@Jarry                             |\n");
    printf("\t\t\t|                       �����������                      |\n");
    printf("\t\t\t*=======================================================*\n");
    getchar();
}