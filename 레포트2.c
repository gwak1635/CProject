#include <stdio.h>
#include <string.h>//���ڿ� ã��
#include <ctype.h>//���� ó�� ���̺귯�� �Լ�
#include <stdbool.h>//bool �����ϴ� ����� �����ֳ׿�
#define SIZE 6
FILE* fp = NULL;//������ ���� ������ �����Ͽ� �ٸ� �Լ������� ��� �����ϵ��� ����.

void roll(bool manual);
void moneyroll();//�Լ� ����

int main() {
	printf("��ǻ�ͼ���Ʈ������а� 20192719 ������\n");//���� �����
	srand((unsigned)time(NULL));//�ð� �õ� ����
	int menu;
	printf("���Ͻô� �޴��� �����ϼ���\n1.����� �м�(�ּ� 1ȸ�� ���� �ʿ�) \n2.�Ϻ� �����Է�\n3.���ϴ� ����ŭ ����\n");
	scanf_s("%d", &menu);

	switch (menu) {
	case 1:{
		char target;//���Ͽ��� �о�� ����
		int datanum[45] = { 0, };//��÷ Ƚ�� ����� ex:1���� 5�� ������ datanum[0]=5;		
		fopen_s(&fp ,"data", "r");//������ ���� �ҷ�����
		if (fp == NULL)
		{
			fprintf(stderr, "������ ������ �������� �ʰų� �� �� �����ϴ�.\n");
			exit(1);
		}//���� ������� ����
		while ((target = fgetc(fp))	 != EOF)
		{
			//����. 0~9 �ƽ�Ű �ڵ�(48~57)�� ���� 0~9��, A~Z(65~90)�� 10~35��, a~i(97~105)�� 36~44�� 
			if (isdigit(target))
				datanum[target - 48]++;
			else if (isupper(target))
				datanum[target - 55]++;
			else if (islower(target))
				datanum[target - 61]++;
			else
				printf("������ �߻��Ͽ����ϴ�. ���� ��ϵ��� �ʽ��ϴ�.");//���� ó��
		}
		fclose(fp);

		//���� ���� ���� 6���� ���� ��� �ߺ� �� ���� ���� �켱
		int Max = 0; //Max �ִ�
		int Mn = 0;//Maxnum.�ִ��� �ִ� �迭 ��ȣ
		for (int j = 0; j < 6; j++) {//�̱� 6�� �ϱ�
			for (int k = 0; k < 45; k++) {
				if (Max < datanum[k]) {
					Max = datanum[k];
					Mn = k;
				}//�ִ񰪰� �ִ��� �ִ� �迭 ��ȣ ����
			}
			datanum[Mn] = 0;//�̹� ����Ǿ����Ƿ� ������ ���� 0���� ����� ��. ������ ���Ͽ��� ���� ����
			printf("%d ", Mn + 1);
			Max = 0;//Max�� �ʱ�ȭ
		}
	}
		break;
	case 2:
		roll(true);//���� ���� ��÷
		break;
	case 3:
		moneyroll();
		break;
	default:
		printf("ERROR!");
	}
	return 0;
}
void roll(bool manual) {//�ζ� �̱� �Լ�
	int atari[SIZE] = { 0, };;//��÷ ���� ��⿭ ����,�ʱ�ȭ
	int num;
	int i;
	char numc;
	fopen_s(&fp , "data", "a");//SQL�˻縦 �� ���� �ؼ� �̷��� �߽��ϴ�.
	for (i = 0; i < SIZE; i++) {
		if (manual==true) {//���� ���
			printf("���ڸ� �Է��ϼ���(1~45 �ƴ� �� �Է� �� ������ �ڵ���õ):");
			scanf_s("%d", &num);
			if (num < 1 || num>45) {
				manual = false;//�ڵ����� ��ȯ
				num = (rand() % 45) + 1;//���������� ���� atari�� �ԷµǸ� �ȵǹǷ� �ٽ� 1~45������ ����.
				printf("���ڸ� �ڵ���÷�մϴ�.\n");
			}
		}
		else {
			num = (rand() % 45) + 1;//�ڵ� ��� �����Լ�. 0~44�� ���̹Ƿ� 1�� ������� ��.
		}
		for (int j = 0; j <= i; j++) {//�迭 0��°���� ���� �������� �ͱ��� üũ
			if (num == atari[j]) {//���� ���� ������
				if (manual == true)//���� �Է� �� �˸�.
					printf("�ߺ��� �����Դϴ�. �ٽ� �Է��� �ּ���.");
				i--;//���� �ϳ� �մ�ܼ� for���� i++�� ���
				break;//���� Ż��
			}
			else {
				if (i == j)//���� �� ������ ���
				{
					atari[i] = num;//j�� �ߺ�üũ��. �������� ��ȣ�� i��°.
				}
			}//i==j&&num==atari[j]�� ���ɼ� ���� ����(�ʱⰪ 0, 0�Է½� ������ ó��)
		}
	}
	for (i = 0; i < SIZE; i++) {
		printf("%d ", atari[i]);
		//���� �� ���ڷ� ����� ǥ���� �߰��ϱ�(���ڿ� �ν��� ����� �� �˴ϴ� �Ф�)
		if (atari[i] <= 0 || atari[i] >= 46) {
			printf("ERROR!");
			exit(1);
		}			
		else if (atari[i] < 11)//1~10���� �ƽ�Ű�ڵ� 0~9��
			numc = atari[i] + 47;
		else if (atari[i] < 37)//11~36���� ���� �빮�ڷ�
			numc = atari[i] + 54;
		else //37~45���� ���� �ҹ���(a~i)���� 
			numc = atari[i] + 60;
		fprintf(fp, "%c", numc);//
	}
	printf("\n");
	fclose(fp);
}
void moneyroll() {
	int money;
	printf("���ϴ� �ݾ�(��):");
	scanf_s("%d", &money);//money���� �����Ͽ� �Է¹���.
	int count = money / 1000;//���� ���� Ƚ�� ����
	if (count < 1) printf("���� �����մϴ�.");//�������� �����ϴٰ� �˸�.

	for (int r = 0; r < count; r++) {
		roll(false);//�ڵ� ���� ��÷
	}
}

//���ľ� �� ��
//�� fprk 0�� ���� �ִٴ� ���� �𸣰���.