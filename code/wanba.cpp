#include <stdio.h>
#include <time.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

struct card {                //������
	char id[25];
	char codon[25];
	double funds;
	int state;
	struct card *next;
};
struct account {            //�Ʒѱ�׼����
	int hour;
	int condume;
	struct account *next;
};
struct chargerecord {       //���Ѽ�¼����
	char id[25];
	int beginday;
	int beginmin;
	int endday;
	int endmin;
	double pay;
	long long int now;     //�ϻ�ʱ������
	struct chargerecord *next;
};
struct administ {           //����Ա����
	char id[25];
	char codon[25];
	char authority[7];
	struct administ *next;
};
void readfile();    //��ȡ�ļ����浽�ĸ�����
void savefile();     //��ȡ�ĸ������浽�ļ�

void enter();      //����Ա��¼ϵͳ
void menu(char *author);  //�˵�

void addcard();        //����¿�
void querycard();         //��ѯ��
void deletecard();        //ע����

void addaccount();     //���ӼƷѱ�׼
void queryaccount();   //��ѯ�Ʒѱ�׼
void deleteaccount();   //ɾ���Ʒѱ�׼
void alteraccount();     //�޸ļƷѱ�׼

void upline();        //����
void offline();          //����

void recharge();     //��ֵ
void returnmoney();    //�˷�

void querryrecord();    //��ѯ����
void acountmoney();     //ͳ��һ��ʱ���Ӫҵ��
void monthmoney();        //ͳ��һ���Ӫҵ

void addadminist();      //��ӹ���Ա������Ȩ��
void deleteadminist();   //ɾ������Ա

struct card *headcard = NULL;
struct account *headaccount = NULL;
struct chargerecord *headrecord = NULL;
struct administ *headadminist = NULL;
const  char * author[6] = { "������Ȩ��","�Ʒѱ�׼Ȩ��","�Ʒѹ���Ȩ��","���ù���Ȩ��","��ѯͳ��Ȩ��","Ȩ�޹���Ȩ��" };
int main()
{
	readfile();
	enter();
	savefile();
	return 0;
}

void readfile() {
	//��ȡ�ļ�����������
	FILE *fp1;
	int i = 0;
	struct card *card, *card2;

	if ((fp1 = fopen("card.txt", "r")) == NULL) {
		printf("��ʧ��!\n");
		exit(0);
	}

	while (!feof(fp1)) {
		if ((card = (struct card*)malloc(sizeof(struct card))) == NULL) {
			printf("�����ڴ�ռ�ʧ��!\n");
			exit(0);
		}
		fscanf(fp1, "%s", card->id);
		fscanf(fp1, "%s", card->codon);
		fscanf(fp1, "%lf", &card->funds);
		fscanf(fp1, "%d", &card->state);
		i++;
		if (i == 1) headcard = card;
		else card2->next = card;
		card2 = card;
	}
	card->next = NULL;

	if (fclose(fp1)) {
		printf("error!\n");
	}

	//��ȡ�ļ���������Ա����
	FILE *fp;
	int j = 0;
	struct administ *a, *a1;

	if ((fp = fopen("administor.txt", "r")) == NULL) {
		printf("�򿪴���!\n");
		exit(0);
	}

	while (!feof(fp)) {
		if ((a = (struct administ*)malloc(sizeof(struct administ))) == NULL) {
			printf("�����ڴ�ռ�ʧ��!\n");
			exit(0);
		}
		fscanf(fp, "%s", a->id);
		fscanf(fp, "%s", a->codon);
		fscanf(fp, "%s", a->authority);
		j++;

		if (j == 1) headadminist = a;
		else a1->next = a;
		a1 = a;
	}
	a->next = NULL;
	if (fclose(fp)) {
		printf("error!\n");
	}
	//��ȡ�ļ������Ʒѱ�׼����
	FILE *fp2;
	int k = 0;
	struct account *c1, *c2;

	if ((fp2 = fopen("rate.txt", "r")) == NULL) {
		printf("��ʧ��!\n");
		exit(0);
	}

	while (!feof(fp2)) {
		if ((c1 = (struct account*)malloc(sizeof(struct account))) == NULL) {
			printf("�����ڴ�ռ�ʧ��!\n");
			exit(0);
		}
		fscanf(fp2, "%d", &c1->hour);
		fscanf(fp2, "%d", &c1->condume);
		k++;
		if (k == 1) headaccount = c1;
		else c2->next = c1;
		c2 = c1;
	}
	c1->next = NULL;
	if (fclose(fp2)) {
		printf("error!\n");
	}
	//��ȡ�ļ��������Ѽ�¼����
	FILE *fp3;
	int l = 0;
	struct chargerecord  *record, *record2;

	if ((fp3 = fopen("record.txt", "r")) == NULL) {
		printf("��ʧ��!\n");
		exit(0);
	}

	while (!feof(fp3)) {
		if ((record = (struct chargerecord*)malloc(sizeof(struct chargerecord))) == NULL) {
			printf("�����ڴ�ռ�ʧ��!\n");
			exit(0);
		}
		fscanf(fp3, "%s", record->id);
		fscanf(fp3, "%d", &record->beginday);
		fscanf(fp3, "%d", &record->beginmin);
		fscanf(fp3, "%d", &record->endday);
		fscanf(fp3, "%d", &record->endmin);
		fscanf(fp3, "%lf", &record->pay);
		l++;

		if (l == 1) headrecord = record;
		else record2->next = record;
		record2 = record;
	}
	record->next = NULL;
	if (fclose(fp3)) {
		printf("error!\n");
	}

}
void enter() {
	int i, j = 0;
	char a[25], b[25];
	struct administ *a1;
	do {
		printf("�������Ա�˺�:");scanf("%s", a);
		printf("\n     ��������:");scanf("%s", b);

		for (a1 = headadminist; a1 != NULL; a1 = a1->next)
			if (!strcmp(a, a1->id) && !strcmp(b, a1->codon)) {
				j = 1;break;
			}
		if (j == 0) printf("\n�˺Ż������������������!\n");

	} while (j != 1);
	printf("�𾴵Ĺ���Ա�����Ȩ����:");
	for (i = 0; i < 6; i++) {
		if (a1->authority[i] == '1') printf("%s  ", author[i]);
	}
	printf("\n\n\n");
	system("pause");
	menu(a1->authority);
}
void menu(char *author) {
	int i, j = 1;           //j�����Ƿ��˳�ϵͳ��iΪ�˵�ѡ��

	while (j) {
		system("cls");
		printf("         ���ɹ���ϵͳ\n");
		printf("====================================\n");
		printf("1-������**************2-�Ʒѱ�׼����\n");
		printf("3-�Ʒѹ���************4-���ù���\n");
		printf("5-��ѯͳ��************6-Ȩ�޹���\n");
		printf("-------------0-�˳�ϵͳ-------------\n");
		printf("====================================\n");
		printf("\n������˵����( 0-6)��");
		scanf("%d", &i);
		if (i > 0 && i <= 6) {
			if (author[i - 1] != '1') i = 7;
		}
		else if (i != 0) { printf("\n����˵���Ŵ���������( 0-6 ):");break; }
		switch (i) {
		case 0:
			system("cls");
			printf("\n��ӭ�´�ʹ�ã�");j = 0;break;
		case 1:
			system("cls");
			printf("\n******************************************");
			printf("\n==============1-��ӿ�====================");
			printf("\n==============2-��ѯ��====================");
			printf("\n==============3-ע����====================");
			printf("\n==============0-�����ϼ��˵�==============");
			printf("\n******************************************");
			printf("\n������˵���ţ�0-3����");
			scanf("%d", &i);
			switch (i)
			{
			case 1: addcard(); break;
			case 2: querycard(); break;
			case 3: deletecard(); break;
			default: break;
			}break;
		case 2:
			system("cls");
			printf("\n********************************************");
			printf("\n=== 1 �����Ʒѱ�׼---------2 ��ѯ�Ʒѱ�׼===");
			printf("                                           ");
			printf("\n=== 3 ɾ���Ʒѱ�׼---------4 �޸ļƷѱ�׼===");
			printf("\n============ 0 �����ϼ��˵� ================");
			printf("\n********************************************");
			printf("\n������˵���ţ�0-4����");
			scanf("%d", &i);
			switch (i)
			{
			case 1: addaccount(); break;
			case 2: queryaccount(); break;
			case 3: deleteaccount(); break;
			case 4: alteraccount(); break;
			default: break;
			}break;
		case 3:
			system("cls");
			printf("\n**********************************************");
			printf("\n============ 1 �ϻ�---------2 �»�============");
			printf("\n                                           ");
			printf("\n=============== 0 �����ϼ��˵� ===============");
			printf("\n**********************************************");
			printf("\n������˵���ţ�0-2����");
			scanf("%d", &i);
			switch (i)
			{
			case 1:upline(); break;
			case 2:offline(); break;
			default: break;
			}break;
		case 4:
			system("cls");
			printf("\n********************************************");
			printf("\n=========== 1 ��ֵ-------2 �˷� ============");
			printf("\n                                           ");
			printf("\n============= 0 �����ϼ��˵� ===============");
			printf("\n********************************************");
			printf("\n������˵���ţ�0-2����");
			scanf("%d", &i);
			switch (i)
			{
			case 1: recharge(); break;
			case 2: returnmoney(); break;
			default: break;
			}break;
		case 5:
			system("cls");
			printf("\n*********************************************");
			printf("\n==============1-��ѯ���Ѽ�¼=================");
			printf("\n==============2-ͳ����Ӫҵ��=================");
			printf("\n==============3-ͳ����Ӫҵ��===============");
			printf("\n==============0-�����ϼ��˵�=================");
			printf("\n*********************************************");
			printf("\n������˵���ţ�0-3����");
			scanf("%d", &i);
			switch (i)
			{
			case 1: querryrecord(); break;
			case 2: acountmoney(); break;
			case 3:	monthmoney(); break;
			default: break;
			}break;
		case 6:
			system("cls");
			printf("\n*************************************************");
			printf("\n========= 1 ��ӹ���Ա-----2 ɾ������Ա =========");
			printf("\n                                           ");
			printf("\n============== 0 �����ϼ��˵� ===================");
			printf("\n*************************************************");
			printf("\n������˵���ţ�0-2����");
			scanf("%d", &i);
			switch (i)
			{
			case 1: addadminist(); break;
			case 2: deleteadminist(); break;
			default: break;
			}break;
		default:
			system("cls");
			printf("\n������Ȩ�޷�Χ��! �������������ѡ��\n");system("pause");
		}
	}

	system("pause");
}
void addcard() {
	struct card *c = headcard, *c1;
	if ((c1 = (struct card*)malloc(sizeof(struct card))) == NULL) {
		printf("�����ڴ�ռ�ʧ��!\n");
		exit(0);
	}

	printf("\n�¿����˺�:");scanf("%s", c1->id);
	printf("\n      ���룺");scanf("%s", c1->codon);
	printf("\n      ��ֵ���(��λ��Ԫ)��");scanf("%lf", &c1->funds);
	c1->state = 1;

	if (headcard == NULL) headcard = c1;
	else {
		while (c->next != NULL) {
			c = c->next;
		}
		c->next = c1;
	}
	c1->next = NULL;
	printf("\n�ɹ����¿��Ŀ���:%s\n", c1->id);
	printf("\n�ÿ������ϻ������Ϊ%.2lfԪ", c1->funds);
	system("pause");
}
void querycard() {
	struct card *c;
	char id[20];
	int i = 1;
	printf("\n����������Ҫ��ѯ�Ŀ���:");
	while (i) {
		scanf("%s", id);
		for (c = headcard; c != NULL; c = c->next) {
			if (!strcmp(c->id, id)) {
				printf("\n�ÿ����Ϊ��%.2lf��Ԫ��", c->funds);
				if (c->state == 1) printf("\n�ÿ���δע��������ʹ�ã�");
				else printf("\n�ÿ���ע��������ʹ�ã�");i = 0;break;
			}
		}
		if (c == NULL) printf("\n���Ŵ����ÿ������ڣ����������룺");
	}
	system("pause");
}
void deletecard() {
	struct card c, *c1;
	int i = 1;

	while (i) {
		printf("\n����Ҫע���Ŀ���:");	scanf("%s", c.id);
		printf("\n            ����:");scanf("%s", c.codon);
		for (c1 = headcard; c1 != NULL; c1 = c1->next) {
			if (!strcmp(c.id, c1->id) && !strcmp(c.codon, c1->codon)) {
				c1->state = 0;
				printf("\n�ÿ����ѳɹ�ע��");i = 0;
				break;
			}
		}
		if (c1 == NULL) printf("\n���Ż������������������!");
	}
	system("pause");
}
void addaccount() {
	struct account *c = headaccount, *c1;int i = 1;
	if ((c1 = (struct account *)malloc(sizeof(struct account))) == NULL) {
		printf("�����ڴ�ռ�ʧ��!\n");
		exit(0);
	}
	printf("\n�����������Ʒѱ�׼(�ϻ���Сʱ��ÿСʱ�շ�):");
	scanf("%d%d", &c1->hour, &c1->condume);
	for (c = headaccount; c != NULL; c = c->next) {
		if (c->hour == c1->hour) { printf("\n��ʱ��ε��շѱ�׼�Ѵ���!");i = 0;break; }
	}
	c = headaccount;
	if (i) {
		if (headaccount == NULL) headaccount = c1;
		else {
			while (c->next != NULL) {
				c = c->next;
			}
			c->next = c1;
		}
		c1->next = NULL;
		printf("\n�����ļƷѱ�׼:�ϻ�%dСʱ��ÿСʱ����%dԪ.", c1->hour, c1->condume);
	}
	system("pause");
}
void queryaccount() {
	int hour;int i = 0;
	struct account *c;
	printf("\n�����ϻ���Сʱ��:");
	scanf("%d", &hour);

	for (c = headaccount; c != NULL; c = c->next) {
		if (c->hour == hour) {
			printf("\n���ϻ�%dСʱ��ÿСʱ����%dԪ\n", hour, c->condume);i = 1;
			break;
		}
	}
	if (!i) printf("\nû���ϻ�ʱ��Ϊ%dСʱ�ļƷѱ�׼!", hour);system("pause");
}
void deleteaccount() {

	int hour, i = 0;
	struct account *c1, *c2;

	printf("\n��������Ҫɾ���ļƷѱ�׼���ϻ�ʱ�䣨Сʱ��:");
	scanf("%d", &hour);
	for (c1 = headaccount; c1 != NULL; c1 = c1->next) {
		if (c1->hour == hour) {
			if (c1 == headaccount) headaccount = c1->next;
			else c2->next = c1->next;
			free(c1);
			printf("\n�ɹ�ɾ���üƷѱ�׼!");i = 1;
			break;
		}
		c2 = c1;
	}
	if (!i) printf("\n�޸üƷѱ�׼��");system("pause");
}
void alteraccount() {

	int hour, i = 0;
	struct account *c;

	printf("\n��������Ҫ�޸ĵļƷѱ�׼���ϻ�ʱ�䣨Сʱ��:");
	scanf("%d", &hour);

	for (c = headaccount; c != NULL; c = c->next) {
		if (c->hour == hour) {
			printf("\n�������޸ĺ��ϻ�%dСʱÿСʱ�ļƷ�(Ԫ):", hour);
			scanf("%d", &c->condume);i = 1;break;
		}
	}
	if (!i) printf("\n�޸üƷѱ�׼!");system("pause");
}
void upline() {
	time_t nowtime;
	struct tm *lt;
	struct card c, *c1;
	struct chargerecord *r1 = headrecord, *r2;
	time(&nowtime);
	lt = localtime(&nowtime);
	printf("\n�����뿨��: ");scanf("%s", c.id);
	printf("\n      ���룺");scanf("%s", c.codon);

	for (c1 = headcard; c1 != NULL; c1 = c1->next) {
		if (!strcmp(c.id, c1->id) && !strcmp(c.codon, c1->codon) && c1->state) {
			printf("\n�ÿ��ϻ��ɹ������Ϊ%.2lf", c1->funds);
			if ((r2 = (struct chargerecord*)malloc(sizeof(struct chargerecord))) == NULL) {
				printf("�����ڴ�ռ�ʧ��!\n");
				exit(0);
			}
			r2->now = nowtime;
			r2->beginday = lt->tm_mday + lt->tm_mon * 100 + (1900 + lt->tm_year) * 10000 + 100;
			r2->beginmin = lt->tm_min + lt->tm_hour * 100;
			r2->endday = 0;
			r2->endmin = 0;
			r2->pay = 0;
			strcpy(r2->id, c1->id);

			if (headrecord == NULL) headrecord = r2;
			else {
				while (r1->next != NULL) { r1 = r1->next; }
				r1->next = r2;
			}
			r2->next = NULL;
			break;
		}
	}
	if (c1 == NULL) printf("\n�˺���������ÿ���ע��");system("pause");
}
void offline() {
	int j = 0;long long int t;
	time_t nowtime;
	struct tm *lt;
	struct card c, *c1;
	struct account *ac;
	struct chargerecord *r1;
	double hourr, hour;
	time(&nowtime);
	lt = localtime(&nowtime);
	printf("\n��������Ҫ�»��Ŀ���:");
	do {
		scanf("%s", c.id);
		for (r1 = headrecord; r1 != NULL; r1 = r1->next)
			if (!strcmp(c.id, r1->id) && !r1->pay) {
				j = 1;break;
			}
		if (!j) printf("\n�˺Ŵ����ÿ�δ�ϻ�������������:");

	} while (j == 0);

	t = nowtime;
	for (r1 = headrecord; r1 != NULL; r1 = r1->next) {
		if (!strcmp(r1->id, c.id) && !r1->endday && !r1->endmin) {
			r1->endday = lt->tm_mday + lt->tm_mon * 100 + (1900 + lt->tm_year) * 10000 + 100;
			r1->endmin = lt->tm_min * 100 + lt->tm_hour * 100;
			hourr = ((nowtime % 100000) - (r1->now % 100000));
			hour = hourr / 3600;
			break;
		}
	}

	for (ac = headaccount; ac != NULL; ac = ac->next) {
		if (ac->hour >= hour) break;
	}

	for (c1 = headcard; c1 != NULL; c1 = c1->next) {
		if (!strcmp(c1->id, c.id)) {
			r1->pay += (double)(ac->condume)* hour;
			c1->funds -= (double)(ac->condume) * hour;
		}
	}

	for (c1 = headcard; c1 != NULL; c1 = c1->next) {
		if (!strcmp(c1->id, c.id)) {
			if (c1->funds < 0)  printf("\n�ÿ�����Ƿ�ѣ��뼰ʱ��ֵ��");
			printf("�ÿ����Ϊ %.4lf\n", c1->funds);
			break;
		}
	}system("pause");
}
void recharge() {
	double money, flag = 1;
	struct card *c;
	char id[25];

	printf("\n�������ֵ�Ŀ���:");
	scanf("%s", id);
	while (flag) {
		for (c = headcard; c != NULL; c = c->next) {
			if (!strcmp(c->id, id)) {
				printf("\n�������ֵ�Ľ��:");
				scanf("%lf", &money);
				c->funds += money;
				printf("\n��ֵ�ɹ����ÿ����Ϊ: %.2lf (Ԫ)\n", c->funds);
				flag = 0;break;
			}

		}

		if (flag) { printf("\n�޷���ֵ����Ŀ��Ŵ������������뿨��:");scanf("%s", id); }
	}system("pause");
}
void returnmoney() {
	double money, flag = 1, j = 0;
	struct card *c1, c;
	printf("\n��������Ҫ�˷ѵĿ���:");
	do {
		scanf("%s", c.id);
		for (c1 = headcard; c1 != NULL; c1 = c1->next)
			if (!strcmp(c.id, c1->id)) {
				j = 1;break;
			}
		if (!j) printf("\n�˺Ŵ�������������:");

	} while (j == 0);

	for (c1 = headcard; c1 != NULL; c1 = c1->next) {
		if (!strcmp(c1->id, c.id)) {
			printf("\n�������˷ѽ��:");
			scanf("%lf", &money);
			if (c1->funds > money) {
				c1->funds -= money;
				printf("\n�˷ѳɹ����ÿ����Ϊ��%.2lf", c1->funds);break;
			}
			else printf("\n�Բ���������㣡");
			break;
		}
	}system("pause");
}
void querryrecord() {
	int j = 0;
	char id[25];
	struct chargerecord *r1, c;
	int a1, a2, a3, a4, a5, a6, b1, b2, b3, b4;

	printf("\n�������ѯ�Ŀ���:");
	do {
		scanf("%s", c.id);
		for (r1 = headrecord; r1 != NULL; r1 = r1->next)
			if (!strcmp(c.id, r1->id)) { j = 1;break; }
		if (j == 0) printf("\n�˺Ŵ�������������:");
	} while (j == 0);
	strcpy(id, c.id);

	for (r1 = headrecord; r1 != NULL; r1 = r1->next) {
		if (!strcmp(id, r1->id)) {
			a1 = r1->beginday / 10000;
			a2 = r1->beginday / 100 % 100;
			a3 = r1->beginday % 100;
			a4 = r1->endday / 10000;
			a5 = r1->endday / 100 % 100;
			a6 = r1->endday % 100;

			b1 = r1->beginmin / 100;
			b2 = r1->beginmin % 100;
			b3 = r1->endmin / 100;
			b4 = r1->endmin % 100;

			printf("\n����:%s �ϻ�ʱ��:%d-%02d-%02d %02d:%02d �»�ʱ��:%d-%02d-%02d %02d:%02d ���ѽ��:%.2lf", r1->id, a1, a2, a3, a4, a5, a6, b1, b2, b3, b4, r1->pay);
		}
	}system("pause");
}
void acountmoney() {

	int day;double s = 0;
	int a, b, c;
	struct chargerecord *r1;

	time_t t;
	struct tm *lt;
	time(&t);
	lt = localtime(&t);

	printf("\n�������(2018)ĳ��(05)ĳ��(09)ĳ�յ������Ӫҵ��:");
	scanf("%d", &day);
	a = day / 100;b = day / 100 % 100;c = day % 100;
	for (r1 = headrecord; r1 != NULL; r1 = r1->next) {
		if (day < r1->endday) s += r1->pay;
	}

	printf("\n%d-%02d-%02d�������Ӫҵ��Ϊ:%.3lf(Ԫ)", a, b, c, s);
	system("pause");
}
void monthmoney() {
	int i;
	struct month {
		int times;
		double sum;
	}mon[12];

	time_t t;
	struct tm *lt;
	time(&t);
	lt = localtime(&t);
	struct chargerecord *r1;
	FILE *fp;

	for (i = 0; i < 12; i++) {
		mon[i].times = 0;
		mon[i].sum = 0;
	}

	for (r1 = headrecord; r1 != NULL; r1 = r1->next) {
		if ((lt->tm_year + 1900) == (r1->endday) / 10000 % 10000) {
			mon[(r1->endday / 100) % 100 - 1].times++;
			mon[(r1->endday / 100) % 100 - 1].sum += r1->pay;
		}
	}

	if ((fp = fopen("monthfunds.txt", "w")) == NULL) { printf("���ļ�ʧ��!\n");exit(0); }

	for (i = 0; i < 12; i++) {
		fprintf(fp, "��%d���ϻ�������%d,��Ӫҵ����%lf\n", i + 1, mon[i].times, mon[i].sum);
	}

	if (fclose(fp)) { printf("error!\n");	exit(0); }

	for (i = 0; i < 12; i++) {
		printf("\n%d���ϻ�������%d, Ӫҵ����%.2lf", i + 1, mon[i].times, mon[i].sum);
	}
	printf("\n��Ӫҵ���ѱ��浽\"monthfunds.txt\"�ļ�!");system("pause");
}
void addadminist() {
	int num = 0, in[6] = { 0,0,0,0,0,0 };
	struct administ  *a1 = headadminist, *a;

	if ((a = (struct administ*)malloc(sizeof(struct administ))) == NULL) {
		printf("�����ڴ�ռ�ʧ��!\n");
		exit(0);
	}
	printf("\n�����������Ĺ���Ա�˺�:");
	scanf("%s", a->id);
	printf("\n�����������Ĺ���Ա����:");
	scanf("%s", a->codon);

	printf("\n");
	for (int i = 0;i < 6;i++) 	printf("%d.%s  ", i, author[i]);
	printf("\n������������Ա��Ȩ�ޣ���Ӧ�������,-1��������");

	do {
		scanf("%d", &num);
		if (num<6 && num>-1) in[num] = 1;
		else if (num != -1) printf("\n��Ŵ������������룡");
	} while (num != -1);
	for (int j = 0;j < 6;j++)
		if (in[j] == 1) a->authority[j] = '1';
		else a->authority[j] = '0';
		a->authority[6] = '\0';
		if (headadminist == NULL) headadminist = a;
		else {
			while (a1->next != NULL) {
				a1 = a1->next;
			}
			a1->next = a;
		}
		a->next = NULL;
		printf("\n�ɹ�����µĹ���Ա�˺ţ�");system("pause");
}
void deleteadminist() {
	char str[25];
	struct administ *a1, *a2;

	printf("\n������Ҫɾ���Ĺ���Ա�˺�:");
	do {
		scanf("%s", str);
		for (a1 = headadminist; a1 != NULL; a1 = a1->next) {
			if (!strcmp(str, a1->id)) {
				if (a1 == headadminist) {
					headadminist = a1->next;
				}
				else {
					a2->next = a1->next;
				}
				free(a1);
				break;
			}
			a2 = a1;
		}
		if (a1 == NULL) printf("\n�˺Ŵ������������룺");
	} while (a1 == NULL);
	printf("\nɾ������Ա�ɹ���");system("pause");
}
void savefile() {
	FILE *fp;        //���濨�����ļ�
	struct card *c;
	if ((fp = fopen("card.txt", "w")) == NULL) {
		printf("open error!\n");
		exit(0);
	}
	for (c = headcard; c != NULL; c = c->next) {
		if (c->next == NULL) fprintf(fp, "%s %s %lf %d", c->id, c->codon, c->funds, c->state);
		else  fprintf(fp, "%s %s %lf %d\n", c->id, c->codon, c->funds, c->state);
	}
	if (fclose(fp)) {
		printf("error!\n");
	}
	//����Ʒѱ�׼����
	FILE *fp1;
	struct account *c1;
	if ((fp1 = fopen("rate.txt", "w")) == NULL) {
		printf("open error!\n");
		exit(0);
	}
	for (c1 = headaccount; c1 != NULL; c1 = c1->next) {
		if (c1->next == NULL)	fprintf(fp, "%d %d", c1->hour, c1->condume);
		else fprintf(fp, "%d %d\n", c1->hour, c1->condume);
	}
	if (fclose(fp1)) { printf("error!\n"); }
	//�������Ѽ�¼����
	FILE *fp2;
	struct chargerecord *c2;

	if ((fp2 = fopen("record.txt", "w")) == NULL) {
		printf("open error!\n");
		exit(0);
	}
	for (c2 = headrecord; c2 != NULL; c2 = c2->next) {
		if (c2->next == NULL) fprintf(fp, "%s %d %d %d %d %lf", c2->id, c2->beginday, c2->beginmin, c2->endday, c2->endmin, c2->pay);
		else fprintf(fp, "%s %d %d %d %d %lf\n", c2->id, c2->beginday, c2->beginmin, c2->endday, c2->endmin, c2->pay);
	}
	if (fclose(fp2)) { printf("error!\n"); }
	//�������Ԫ����

	FILE *fp3;
	struct administ *a3;
	if ((fp3 = fopen("administor.txt", "w")) == NULL) {
		printf("open error!\n");
		exit(0);
	}
	for (a3 = headadminist; a3 != NULL; a3 = a3->next) {
		if (a3->next == NULL)   fprintf(fp, "%s %s %s", a3->id, a3->codon, a3->authority);
		else	fprintf(fp, "%s %s %s\n", a3->id, a3->codon, a3->authority);
	}
	if (fclose(fp3)) { printf("error!\n"); }
	system("pause");
}