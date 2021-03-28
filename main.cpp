#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

const int MAX = 50000;
char schoolname[4][20] = {"�����ѧԺ", "���ѧԺ",
     "ͨ��ѧԺ", "�Զ���ѧԺ"};  //��ѧԺ��Ϣ

struct Admin{  //����Ա��Ϣ
    int a;
    char ID[10];
	char pass[10];
    Admin(){
        memset(ID, 0, sizeof(ID));
        memset(pass, 0, sizeof(pass));
    }
};

struct Student{  //ѧ���ṹ�嶨��
	char name[20];  //����
	char id[20];	//���֤��
    int num;  //ѧ��
	char major[20];  //רҵ
    Student(){
        memset(name, 0, sizeof(name));
        memset(id, 0, sizeof(id));
        num = 0;
        memset(major, 0, sizeof(major));
    }
}student[MAX];

void Clean(){  //��������ջ�����
    system("cls");  //��������
    fflush(stdin);  //������뻺����
}

void Encrypt(char a[], int n){  //�����ַ���
    int i;
    for (i = 0; i < n; i++)    a[i] = a[i] ^ 15;
}

int CheckSupPas(){  //��鳬������
    char superpass[10] = {0};
    char a_superpass[10] = {0};
    FILE *fp;
    if ((fp = fopen("super.pass", "rb")) == NULL){  //�������ļ�
        printf("���������ļ�����\n");
        exit(0);
    }
    fread(a_superpass, sizeof(char), 10, fp);  //������ܺ������
    fclose(fp);
    printf("������8λ�������룺");    scanf("%s", superpass); 
    Encrypt(superpass, 8);  //�������������ܣ��Ա�Ƚ�
    if (strcmp(superpass, a_superpass)){
        printf("����������������ԣ�\n");
        system("pause");
        return 0;
    }
    else    return 1;
}

int CheckSchool(char str[]){  //���ѧԺ��
    int i;
    for (i = 0; i < 4; i++){
        if (!strcmp(str, schoolname[i]))    return i;
    }
    return -1;
}

int CheckID(char str[]){
    struct Admin a_admin;  //�洢�ļ��еĹ���Ա��Ϣ
    FILE *fp;
    if ((fp = fopen("admin", "rb")) == NULL){  //�򿪹���Ա�˺��ļ�
        printf("����Ա�˺��ļ�����\n");
        exit(0);
    }
    while (!feof(fp)){
        fread(&a_admin, sizeof(struct Admin), 1, fp);
        if (!strcmp(a_admin.ID, str)){
            printf("����ԱID�ظ���\n");
            fclose(fp);
            system("pause");
            return 0;
        }
    }
    fclose(fp);
    return 1;
}

int SignUp(){  //ע��
    Clean();
    printf("��֤�ɹ�\n�뿪ʼע�ᣡ\n");
    struct Admin admin;
    printf("���������ID:");
    scanf("%s", admin.ID);
    if (!CheckID(admin.ID))    return 0;  //���ID�Ƿ��ظ�
	printf("�������������:");
    scanf("%s", admin.pass);
    FILE *fp;
    if ((fp = fopen("admin", "ab")) == NULL){  //��׷�Ӷ�дģʽ�򿪹���Ա�˺��ļ�
        printf("����Ա�˺��ļ�����\n");
        exit(0);
    }
    printf("�뱣�������˺����룡\n����ID:%s\n��������:%s\n", admin.ID, admin.pass);
    Encrypt(admin.pass, 8);  //��������
    fwrite(&admin , sizeof(struct Admin), 1, fp);
    fclose(fp);
    system("pause");
}

int SignIn(){  //��¼
    Clean();
    struct Admin admin;
    struct Admin *a_admin;
    a_admin = (struct Admin*)malloc(sizeof(struct Admin));
    FILE *fp;
    if ((fp = fopen("admin", "rb")) == NULL){  //�򿪹���Ա�˺��ļ�
        printf("����Ա�˺��ļ�����\n");
        exit(0);
    }
    //�����˺�����
	printf("���������ID:");    scanf("%s", admin.ID);
	printf("�������������:");    scanf("%s", admin.pass);
    Encrypt(admin.pass, 8);  //�����Ա�У��
    while (!feof(fp)){  //��û�е��ļ�ĩβ����ѭ�����벢�ж�
        fread(a_admin, sizeof(struct Admin), 1, fp);
        if (!strcmp(a_admin->ID, admin.ID) && !strcmp(a_admin->pass, admin.pass)){
            fclose(fp);
            printf("��½�ɹ���\n");
            system("pause");
            return 1;
        }
    }
    fclose(fp);
    printf("�˺�������������ԣ�\n");
    system("pause");
    return 0;
}

int StartMenu(){  //��ʼ�˵�
    Clean();
    printf("0.�˳�ϵͳ\n");
    printf("1.����Ա��¼\n");
    printf("2.����Ա�˺�ע��\n");
    printf("�������Ӧ����ѡ��");
    char choice; //����ѡ��
    scanf("%c", &choice);
    //�û�ѡ���˳�
    if (choice == '0')    exit(0);
    //�û�ѡ���¼
    else if (choice == '1')    return SignIn();
    //�û�ѡ��ע��
    else if (choice == '2'){
        while (!CheckSupPas());  //����Ƿ�Ϊ����Ա
        SignUp();
    }    
    //�û��������
    else{
        printf("�������,�����ԣ�\n");
        system("pause");   //������ͣ���̣��ȴ�������ָ��
    }    
    return 0;
}

void Input(){  //����ѧ����Ϣ
    int iscontinue = 1;
    char school[20] = {0};  //���ڱ���ѧԺ��
    struct Student tempstu;
    while (iscontinue){
        Clean();
        printf("��ʼ���룡\n");
        printf("��У����ѧԺ���£�\n");
        printf("�����ѧԺ�����ѧԺ��ͨ��ѧԺ���Զ���ѧԺ\n");
        printf("������ѧԺ����");    scanf("%s", school);
        if (CheckSchool(school) == -1){  //���ѧԺ���Ƿ�������ȷ
            printf("ѧУ������������飡\n");
            system("pause");
            continue;
        }
        printf("������������");    scanf("%s", tempstu.name);
        printf("���������֤��(1001��ʼ)��");    scanf("%s", tempstu.id);
        printf("������ѧ��(101��ʼ)��");    scanf("%d", &tempstu.num);
        printf("������רҵ����");    scanf("%s", tempstu.major); 
        FILE *fp;
        if ((fp = fopen(school, "ab")) == NULL){  //��ѧ���˺��ļ�
            printf("����Ա�˺��ļ�����\n");
            exit(0);
        }
        fwrite(&tempstu , sizeof(struct Student), 1, fp);
        fclose(fp);
        printf("Y����\n�Ƿ����:");
        getchar();
        if (getchar() != 'Y')    iscontinue = 0;
    }
}

void ShowStu(char school[]){
    struct Student tempstu;
    FILE *fp;
    if ((fp = fopen(school, "rb")) == NULL){  //�򿪶�ӦѧԺ�ļ�
        printf("%s�ļ�����\n", school);
        exit(0);
    }
    printf("\n%sѧԺ����ѧ�����£�\n", school);
    //��ֹĩ���ظ�
    fread(&tempstu, sizeof(struct Student), 1, fp);
    while (!feof(fp)){  //��û�е��ļ�ĩβ����ѭ�����벢�ж�
        printf("%-10s %-10s %-10d %-20s\n", tempstu.name, tempstu.id, tempstu.num, tempstu.major);
        fread(&tempstu, sizeof(struct Student), 1, fp);
    }
    putchar('\n');
    fclose(fp);
    system("pause");
}

void ViewSchool(){
    Clean();
    char school[20];
    printf("��У����ѧԺ���£�\n");
    printf("�����ѧԺ�����ѧԺ��ͨ��ѧԺ���Զ���ѧԺ\n");
    printf("������ѧԺ����");    scanf("%s", school);
    if (CheckSchool(school) == -1){  //���������
        printf("������������ԣ�");
        system("pause");
    }
    else    ShowStu(school);
}

void SearchStudent(){
    int i;
    int s_num;
    printf("������ѧ��ѧ�ţ�");
    scanf("%d", &s_num);
    for (i = 0; i < 4; i++){
        struct Student tempstu;
        FILE *fp;
        if ((fp = fopen(schoolname[i], "rb")) == NULL){  //�򿪶�ӦѧԺ�ļ�
            printf("%s�ļ�����\n", schoolname[i]);
            exit(0);
        }
        while (!feof(fp)){  //��û�е��ļ�ĩβ����ѭ�����벢�ж�
            fread(&tempstu, sizeof(struct Student), 1, fp);
            if (s_num == tempstu.num){
                printf("ѧ�����ҵ���\n");
                printf("%-10s %-10s %-10d %-20s\n\n", tempstu.name, tempstu.id, tempstu.num, tempstu.major);
                fclose(fp);
                system("pause");
                return;
            }
        }
        fclose(fp);
    }
    printf("ѧ��δ�ҵ���");
    system("pause");
}

void ChangeStu(){  //�޸�ѧ����Ϣ
    char school[20] = {0};  //���ڱ���ѧԺ��
    int num = 0;
    int isfind = 0;
    struct Student tempstu;
    Clean();
    printf("��ʼ���룡\n");
    printf("��У����ѧԺ���£�\n");
    printf("�����ѧԺ�����ѧԺ��ͨ��ѧԺ���Զ���ѧԺ\n");
    printf("�������ѧ�����ڵ�ѧԺ����");    scanf("%s", school);
    if (CheckSchool(school) == -1){  //���ѧԺ���Ƿ�������ȷ
        printf("ѧУ������������飡\n");
        system("pause");
    }
    printf("�����������ѧ�ţ�");
    scanf("%d", &num);
    FILE *fp;
    if ((fp = fopen(school, "rb+")) == NULL){  //�򿪶�ӦѧԺ�ļ�
        printf("%s�ļ�����\n", school);
        exit(0);
    }
    while (!feof(fp)){  //��û�е��ļ�ĩβ����ѭ�����벢�ж�
        fread(&tempstu, sizeof(struct Student), 1, fp);
        if (num == tempstu.num){
            printf("������������");    scanf("%s", tempstu.name);
            printf("���������֤��(1001��ʼ)��");    scanf("%s", tempstu.id);
            printf("������רҵ����");    scanf("%s", tempstu.major); 
            fseek(fp, -sizeof(struct Student), 1);
            fwrite(&tempstu, sizeof(struct Student), 1, fp);
            /*printf("%-10s %-10s %-10d %-20s\n", tempstu.name, tempstu.id, tempstu.num, tempstu.major);
            struct Student stu;
            stu.num = num;
            printf("������������");    scanf("%s", stu.name);
            printf("���������֤��(1001��ʼ)��");    scanf("%s", stu.id);
            printf("������רҵ����");    scanf("%s", stu.major); 
            printf("%-10s %-10s %-10d %-20s\n", stu.name, stu.id, stu.num, stu.major);
            int a = fwrite(&stu, sizeof(struct Student), 1, fp);
            printf("%d\n", a);*/
            fclose(fp);
            printf("�޸ĳɹ���");
            system("pause");
            return;
        }
    }
    fclose(fp);
    printf("ѧ��δ�ҵ���");
    system("pause");
}

void Menu(){  //�˵�
    Clean();
    char choice;
    printf("���ѳɹ��������ϵͳ��\n");
    printf("0.�˳�ϵͳ\n");
    printf("1.�鿴ѧԺ��Ϣ\n");
    printf("2.��ѯѧ����Ϣ\n");
    printf("3.�޸�ѧ����Ϣ\n");
    printf("4.¼��ѧ����Ϣ\n");
    printf("�������Ӧ����ѡ��");
    scanf("%c", &choice);
    switch (choice){
        case '0':  //�˳�ϵͳ
            exit(0);
        case '1':
            ViewSchool();
            break;
        case '2':
            SearchStudent();
            break;
        case '3':
            ChangeStu();
            break;
        case '4':
            Input();
            break;
        default:
            printf("������������ԣ�");
            system("pause");
    } 
}

int main(){
    while (!StartMenu());
    while (1)    Menu();
}

