#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

const int MAX = 50000;


struct Admin{
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

void Clean(){  //����������ջ�����
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
    char school[4][20] = {"�����ѧԺ","���ѧԺ","ͨ��ѧԺ","�Զ���ѧԺ"};
    int i;
    for (i = 0; i < 4; i++){
        if (!strcmp(str, school[i]))    return i + 1;
    }
    return 0;
}

int SignUp(){  //ע��
    Clean();
    printf("��֤�ɹ�\n�뿪ʼע�ᣡ\n");
    struct Admin admin;
    struct Admin *a_admin;
    a_admin = (struct Admin*)malloc(sizeof(struct Admin)); 
    printf("���������ID:");
    scanf("%s", admin.ID);

    //���ID�Ƿ��ظ�
    FILE *fp1;
    if ((fp1 = fopen("admin", "rb")) == NULL){  //�򿪹���Ա�˺��ļ�
        printf("����Ա�˺��ļ�����\n");
        exit(0);
    }
    while (!feof(fp1)){
        fread(a_admin, sizeof(struct Admin), 1, fp1);
        if (!strcmp(a_admin->ID, admin.ID)){
            printf("����ԱID�ظ���\n");
            fclose(fp1);
            system("pause");
            return 0;
        }
    }
    fclose(fp1);

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
        if (!CheckSchool(school)){  //���ѧԺ���Ƿ�������ȷ
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
    system("pause");
}

void ViewSchool(){
    Clean();
    char school[20];
    printf("��У����ѧԺ���£�\n");
    printf("�����ѧԺ�����ѧԺ��ͨ��ѧԺ���Զ���ѧԺ\n");
    printf("������ѧԺ����");    scanf("%s", school);
    switch(CheckSchool(school)){
        case 1:
            ShowStu("�����ѧԺ");
            break;
        case 2:
            ShowStu("���ѧԺ");
            break;
        case 3:
            ShowStu("ͨ��ѧԺ");
            break;
        case 4:
            ShowStu("�Զ���ѧԺ");
            break;
        default:
            printf("������������ԣ�");
            system("pause");
    }
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

            break;
        case '3':

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

