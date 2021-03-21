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
	int num;  //ѧ��
	char name[20];  //����
	char id[20];	//���֤��
	char school[50];  //ѧԺ
	char type[50];  //ѧ������
	char major[50];  //רҵ
	char route[50];  //��У·��
	char closeContact[50];  //���нӴ�
	double temperature;  //�¶�
	char his[100];  //����
	bool isSick;  //�Ƿ�����
	char date[50];  //��Уʱ��
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
    FILE *fps;
    if ((fps = fopen("super.pass", "rb")) == NULL){  //�������ļ�
        printf("���������ļ�����\n");
        exit(0);
    }
    fread(a_superpass, sizeof(char), 10, fps);  //������ܺ������
    fclose(fps);
    printf("������8λ�������룺");    scanf("%s", superpass); 
    Encrypt(superpass, 8);  //�������������ܣ��Ա�Ƚ�
    if (strcmp(superpass, a_superpass)){
        printf("����������������ԣ�\n");
        system("pause");
        return 0;
    }
    else    return 1;
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
    //�����˺�����
	printf("���������ID:");    scanf("%s", admin.ID);
	printf("�������������:");    scanf("%s", admin.pass);
    Encrypt(admin.pass, 8);  //�����Ա�У��
    FILE *fp;
    if ((fp = fopen("admin", "rb")) == NULL){  //�򿪹���Ա�˺��ļ�
        printf("����Ա�˺��ļ�����\n");
        exit(0);
    }
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

void Input(){
    
}


int Menu(){  //�˵�
    Clean();
    char choice;
    printf("���ѳɹ��������ϵͳ��\n");
    printf("0.�˳�ϵͳ\n");
    printf("1.�鿴ѧԺ��Ϣ\n");
    printf("2.��ѯѧ����Ϣ\n");
    printf("3.��ѯ��Σ��Ⱥ\n");
    printf("4.¼��ѧ����Ϣ\n");
    printf("�������Ӧ����ѡ��");
    scanf("%c", &choice);
    switch (choice){
        case '0':  //�˳�ϵͳ
            exit(0);
        case '1':

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
    while (!Menu());
}

