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
	char name[20];  //姓名
	char id[20];	//身份证号
    int num;  //学号
	char major[20];  //专业
    Student(){
        memset(name, 0, sizeof(name));
        memset(id, 0, sizeof(id));
        num = 0;
        memset(major, 0, sizeof(major));
    }
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
    FILE *fp;
    if ((fp = fopen("super.pass", "rb")) == NULL){  //打开密码文件
        printf("超级密码文件出错。\n");
        exit(0);
    }
    fread(a_superpass, sizeof(char), 10, fp);  //读入加密后的密码
    fclose(fp);
    printf("请输入8位超级密码：");    scanf("%s", superpass); 
    Encrypt(superpass, 8);  //将输入的密码加密，以便比较
    if (strcmp(superpass, a_superpass)){
        printf("超级密码错误，请重试！\n");
        system("pause");
        return 0;
    }
    else    return 1;
}

int CheckSchool(char str[]){  //检查学院名
    char school[4][20] = {"计算机学院","软件学院","通信学院","自动化学院"};
    int i;
    for (i = 0; i < 4; i++){
        if (!strcmp(str, school[i]))    return i + 1;
    }
    return 0;
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
    FILE *fp;
    if ((fp = fopen("admin", "rb")) == NULL){  //打开管理员账号文件
        printf("管理员账号文件出错。\n");
        exit(0);
    }
    //输入账号密码
	printf("请输入你的ID:");    scanf("%s", admin.ID);
	printf("请输入你的密码:");    scanf("%s", admin.pass);
    Encrypt(admin.pass, 8);  //加密以便校验
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

void Input(){  //输入学生信息
    int iscontinue = 1;
    char school[20] = {0};  //用于保存学院名
    struct Student tempstu;
    while (iscontinue){
        Clean();
        printf("开始输入！\n");
        printf("本校共有学院如下：\n");
        printf("计算机学院、软件学院、通信学院、自动化学院\n");
        printf("请输入学院名：");    scanf("%s", school);
        if (!CheckSchool(school)){  //检查学院名是否输入正确
            printf("学校名输入错误，请检查！\n");
            system("pause");
            continue;
        }
        printf("请输入姓名：");    scanf("%s", tempstu.name);
        printf("请输入身份证号(1001开始)：");    scanf("%s", tempstu.id);
        printf("请输入学号(101开始)：");    scanf("%d", &tempstu.num);
        printf("请输入专业名：");    scanf("%s", tempstu.major); 
        FILE *fp;
        if ((fp = fopen(school, "ab")) == NULL){  //打开学生账号文件
            printf("管理员账号文件出错。\n");
            exit(0);
        }
        fwrite(&tempstu , sizeof(struct Student), 1, fp);
        fclose(fp);
        printf("Y继续\n是否继续:");
        getchar();
        if (getchar() != 'Y')    iscontinue = 0;
    }
}

void ShowStu(char school[]){
    struct Student tempstu;
    FILE *fp;
    if ((fp = fopen(school, "rb")) == NULL){  //打开对应学院文件
        printf("%s文件出错。\n", school);
        exit(0);
    }
    printf("\n%s学院共有学生如下：\n", school);
    //防止末行重复
    fread(&tempstu, sizeof(struct Student), 1, fp);
    while (!feof(fp)){  //若没有到文件末尾，就循环读入并判断
        printf("%-10s %-10s %-10d %-20s\n", tempstu.name, tempstu.id, tempstu.num, tempstu.major);
        fread(&tempstu, sizeof(struct Student), 1, fp);
    }
    putchar('\n');
    system("pause");
}

void ViewSchool(){
    Clean();
    char school[20];
    printf("本校共有学院如下：\n");
    printf("计算机学院、软件学院、通信学院、自动化学院\n");
    printf("请输入学院名：");    scanf("%s", school);
    switch(CheckSchool(school)){
        case 1:
            ShowStu("计算机学院");
            break;
        case 2:
            ShowStu("软件学院");
            break;
        case 3:
            ShowStu("通信学院");
            break;
        case 4:
            ShowStu("自动化学院");
            break;
        default:
            printf("输入错误，请重试！");
            system("pause");
    }
}

void Menu(){  //菜单
    Clean();
    char choice;
    printf("您已成功进入管理系统！\n");
    printf("0.退出系统\n");
    printf("1.查看学院信息\n");
    printf("2.查询学生信息\n");
    printf("3.修改学生信息\n");
    printf("4.录入学生信息\n");
    printf("请输入对应数字选择：");
    scanf("%c", &choice);
    switch (choice){
        case '0':  //退出系统
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
            printf("输入错误，请重试！");
            system("pause");
    } 
}

int main(){
    while (!StartMenu());
    while (1)    Menu();
}

