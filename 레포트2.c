#include <stdio.h>
#include <string.h>//문자열 찾기
#include <ctype.h>//문자 처리 라이브러리 함수
#include <stdbool.h>//bool 정의하는 헤더가 따로있네요
#define SIZE 6
FILE* fp = NULL;//파일을 전역 변수로 정의하여 다른 함수에서도 사용 가능하도록 만듦.

void roll(bool manual);
void moneyroll();//함수 선언

int main() {
	printf("컴퓨터소프트웨어공학과 20192719 곽현진\n");//내가 만든것
	srand((unsigned)time(NULL));//시간 시드 생성
	int menu;
	printf("원하시는 메뉴를 선택하세요\n1.통계적 분석(최소 1회의 생성 필요) \n2.일부 수동입력\n3.원하는 돈만큼 생성\n");
	scanf_s("%d", &menu);

	switch (menu) {
	case 1:{
		char target;//파일에서 읽어온 문자
		int datanum[45] = { 0, };//당첨 횟수 저장소 ex:1번이 5개 있으면 datanum[0]=5;		
		fopen_s(&fp ,"data", "r");//데이터 파일 불러오기
		if (fp == NULL)
		{
			fprintf(stderr, "데이터 파일이 존재하지 않거나 열 수 없습니다.\n");
			exit(1);
		}//파일 미존재시 에러
		while ((target = fgetc(fp))	 != EOF)
		{
			//역산. 0~9 아스키 코드(48~57)를 숫자 0~9로, A~Z(65~90)를 10~35로, a~i(97~105)를 36~44로 
			if (isdigit(target))
				datanum[target - 48]++;
			else if (isupper(target))
				datanum[target - 55]++;
			else if (islower(target))
				datanum[target - 61]++;
			else
				printf("에러가 발생하였습니다. 값이 등록되지 않습니다.");//예외 처리
		}
		fclose(fp);

		//가장 많이 뽑인 6개의 숫자 출력 중복 시 낮은 숫자 우선
		int Max = 0; //Max 최댓값
		int Mn = 0;//Maxnum.최댓값이 있는 배열 번호
		for (int j = 0; j < 6; j++) {//뽑기 6번 하기
			for (int k = 0; k < 45; k++) {
				if (Max < datanum[k]) {
					Max = datanum[k];
					Mn = k;
				}//최댓값과 최댓값이 있는 배열 번호 저장
			}
			datanum[Mn] = 0;//이미 추출되었으므로 원소의 값을 0으로 만들어 줌. 데이터 파일에는 영향 없음
			printf("%d ", Mn + 1);
			Max = 0;//Max값 초기화
		}
	}
		break;
	case 2:
		roll(true);//수동 모드로 추첨
		break;
	case 3:
		moneyroll();
		break;
	default:
		printf("ERROR!");
	}
	return 0;
}
void roll(bool manual) {//로또 뽑기 함수
	int atari[SIZE] = { 0, };;//당첨 숫자 대기열 정의,초기화
	int num;
	int i;
	char numc;
	fopen_s(&fp , "data", "a");//SQL검사를 켜 놓고 해서 이렇게 했습니다.
	for (i = 0; i < SIZE; i++) {
		if (manual==true) {//수동 모드
			printf("숫자를 입력하세요(1~45 아닌 값 입력 시 나머지 자동추천):");
			scanf_s("%d", &num);
			if (num < 1 || num>45) {
				manual = false;//자동모드로 전환
				num = (rand() % 45) + 1;//비정상적인 값이 atari에 입력되면 안되므로 다시 1~45값으로 만듦.
				printf("숫자를 자동추첨합니다.\n");
			}
		}
		else {
			num = (rand() % 45) + 1;//자동 모드 랜덤함수. 0~44의 수이므로 1을 더해줘야 함.
		}
		for (int j = 0; j <= i; j++) {//배열 0번째부터 현재 진행중인 것까지 체크
			if (num == atari[j]) {//같은 것이 있으면
				if (manual == true)//수동 입력 시 알림.
					printf("중복된 숫자입니다. 다시 입력해 주세요.");
				i--;//슬롯 하나 앞당겨서 for문의 i++에 대비
				break;//루프 탈출
			}
			else {
				if (i == j)//같은 게 없으면 등록
				{
					atari[i] = num;//j는 중복체크용. 실질적인 번호는 i번째.
				}
			}//i==j&&num==atari[j]일 가능성 사전 배제(초기값 0, 0입력시 비정상 처리)
		}
	}
	for (i = 0; i < SIZE; i++) {
		printf("%d ", atari[i]);
		//숫자 한 문자로 만들어 표본에 추가하기(문자열 인식이 제대로 안 됩니다 ㅠㅠ)
		if (atari[i] <= 0 || atari[i] >= 46) {
			printf("ERROR!");
			exit(1);
		}			
		else if (atari[i] < 11)//1~10까지 아스키코드 0~9로
			numc = atari[i] + 47;
		else if (atari[i] < 37)//11~36까지 영어 대문자로
			numc = atari[i] + 54;
		else //37~45부터 영어 소문자(a~i)까지 
			numc = atari[i] + 60;
		fprintf(fp, "%c", numc);//
	}
	printf("\n");
	fclose(fp);
}
void moneyroll() {
	int money;
	printf("원하는 금액(원):");
	scanf_s("%d", &money);//money변수 생성하여 입력받음.
	int count = money / 1000;//복권 돌릴 횟수 정의
	if (count < 1) printf("돈이 부족합니다.");//돈없으면 부족하다고 알림.

	for (int r = 0; r < count; r++) {
		roll(false);//자동 모드로 추첨
	}
}

//고쳐야 할 점
//왜 fprk 0일 수도 있다는 건지 모르겠음.