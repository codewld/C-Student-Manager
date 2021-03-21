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

struct Student{  //学生结构体定义
	int num;  //学号
	char name[20];  //姓名
	char id[20];	//身份证号
	char school[50];  //学院
	char type[50];  //学生类型
	char major[50];  //专业
	char route[50];  //返校路线
	char closeContact[50];  //密切接触
	double temperature;  //温度
	char his[100];  //病历
	bool isSick;  //是否生病
	char date[50];  //进校时间
}student[MAX];

void Clean(){  //清屏，并清空缓存区
    system("cls");  //清屏函数
    fflush(stdin);  //清空输入缓存区
}

void Encrypt(char a[], int n){  //加密字符串
    int i;
    for (i = 0; i < n; i++)    a[i] = a[i] ^ 15;
}

int CheckSupPas(){  //检查超级密码
    char superpass[10] = {0};
    char a_superpass[10] = {0};
    FILE *fps;
    if ((fps = fopen("super.pass", "rb")) == NULL){  //打开密码文件
        printf("超级密码文件出错。\n");
        exit(0);
    }
    fread(a_superpass, sizeof(char), 10, fps);  //读入加密后的密码
    fclose(fps);
    printf("请输入8位超级密码：");    scanf("%s", superpass); 
    Encrypt(superpass, 8);  //将输入的密码加密，以便比较
    if (strcmp(superpass, a_superpass)){
        printf("超级密码错误，请重试！\n");
        system("pause");
        return 0;
    }
    else    return 1;
}

int SignUp(){  //注册
    Clean();
    printf("验证成功\n请开始注册！\n");
    struct Admin admin;
    struct Admin *a_admin;
    a_admin = (struct Admin*)malloc(sizeof(struct Admin)); 
    printf("请输入你的ID:");
    scanf("%s", admin.ID);
    
    //检查ID是否重复
    FILE *fp1;
    if ((fp1 = fopen("admin", "rb")) == NULL){  //打开管理员账号文件
        printf("管理员账号文件出错。\n");
        exit(0);
    }
    while (!feof(fp1)){
        fread(a_admin, sizeof(struct Admin), 1, fp1);
        if (!strcmp(a_admin->ID, admin.ID)){
            printf("管理员ID重复！\n");
            fclose(fp1);
            system("pause");
            return 0;
        }
    }
    fclose(fp1);

	printf("请输入你的密码:");
    scanf("%s", admin.pass);
    FILE *fp;
    if ((fp = fopen("admin", "ab")) == NULL){  //以追加读写模式打开管理员账号文件
        printf("管理员账号文件出错。\n");
        exit(0);
    }
    printf("请保存好你的账号密码！\n您的ID:%s\n您的密码:%s\n", admin.ID, admin.pass);
    Encrypt(admin.pass, 8);  //加密密码
    fwrite(&admin , sizeof(struct Admin), 1, fp);
    fclose(fp);
    system("pause");
}

int SignIn(){  //登录
    Clean();
    struct Admin admin;
    struct Admin *a_admin;
    a_admin = (struct Admin*)malloc(sizeof(struct Admin));
    //输入账号密码
	printf("请输入你的ID:");    scanf("%s", admin.ID);
	printf("请输入你的密码:");    scanf("%s", admin.pass);
    Encrypt(admin.pass, 8);  //加密以便校验
    FILE *fp;
    if ((fp = fopen("admin", "rb")) == NULL){  //打开管理员账号文件
        printf("管理员账号文件出错。\n");
        exit(0);
    }
    while (!feof(fp)){  //若没有到文件末尾，就循环读入并判断
        fread(a_admin, sizeof(struct Admin), 1, fp);
        if (!strcmp(a_admin->ID, admin.ID) && !strcmp(a_admin->pass, admin.pass)){
            fclose(fp);
            printf("登陆成功！\n");
            system("pause");
            return 1;
        }
    }
    fclose(fp);
    printf("账号密码错误，请重试！\n");
    system("pause");
    return 0;
}

int StartMenu(){  //开始菜单
    Clean();
    printf("0.退出系统\n");
    printf("1.管理员登录\n");
    printf("2.管理员账号注册\n");
    printf("请输入对应数字选择：");
    char choice; //用于选择
    scanf("%c", &choice);
    //用户选择退出
    if (choice == '0')    exit(0);
    
    //用户选择登录
    else if (choice == '1')    return SignIn();

    //用户选择注册
    else if (choice == '2'){
        while (!CheckSupPas());  //检查是否为管理员
        SignUp();
    }    
    
    //用户输入错误
    else{
        printf("输入错误,请重试！\n");
        system("pause");   //用于暂停进程，等待继续的指令
    }    
    return 0;
}

void Input(){
    
}


int Menu(){  //菜单
    Clean();
    char choice;
    printf("您已成功进入管理系统！\n");
    printf("0.退出系统\n");
    printf("1.查看学院信息\n");
    printf("2.查询学生信息\n");
    printf("3.查询高危人群\n");
    printf("4.录入学生信息\n");
    printf("请输入对应数字选择：");
    scanf("%c", &choice);
    switch (choice){
        case '0':  //退出系统
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
            printf("输入错误，请重试！");
            system("pause");
    } 
}

int main(){
    while (!StartMenu());
    while (!Menu());
}

