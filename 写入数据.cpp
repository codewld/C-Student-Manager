#include <stdio.h>
#include <string.h>
#include <stdlib.h> 



struct Admin{
    int a;
    char ID[10];
	char pass[10];
};

int main(){
    struct Admin ad;
    printf("��֤�ɹ�\n�뿪ʼע�ᣡ\n");
    strcpy(ad.ID, "admin1");
	strcpy(ad.pass, "111111");
    for (int i = 0; i < 10; i++)  printf("%d %d\n", ad.ID[i], ad.pass[i]);
    FILE *fp;
    if ((fp = fopen("admin", "wb")) == NULL){  //�򿪹���Ա�˺��ļ�
        printf("����Ա�˺��ļ�����\n");
        exit(0);
    }
    if (fwrite(&ad , sizeof(Admin), 1, fp) != 1){
        printf("cuo");
    }
}