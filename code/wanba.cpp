#include <stdio.h>
#include <time.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

struct card {                //卡链表
	char id[25];
	char codon[25];
	double funds;
	int state;
	struct card *next;
};
struct account {            //计费标准链表
	int hour;
	int condume;
	struct account *next;
};
struct chargerecord {       //消费记录链表
	char id[25];
	int beginday;
	int beginmin;
	int endday;
	int endmin;
	double pay;
	long long int now;     //上机时的秒数
	struct chargerecord *next;
};
struct administ {           //管理员链表
	char id[25];
	char codon[25];
	char authority[7];
	struct administ *next;
};
void readfile();    //读取文件保存到四个链表
void savefile();     //读取四个链表保存到文件

void enter();      //管理员登录系统
void menu(char *author);  //菜单

void addcard();        //添加新卡
void querycard();         //查询卡
void deletecard();        //注销卡

void addaccount();     //增加计费标准
void queryaccount();   //查询计费标准
void deleteaccount();   //删除计费标准
void alteraccount();     //修改计费标准

void upline();        //上线
void offline();          //下线

void recharge();     //充值
void returnmoney();    //退费

void querryrecord();    //查询消费
void acountmoney();     //统计一段时间的营业额
void monthmoney();        //统计一年的营业

void addadminist();      //添加管理员并配置权限
void deleteadminist();   //删除管理员

struct card *headcard = NULL;
struct account *headaccount = NULL;
struct chargerecord *headrecord = NULL;
struct administ *headadminist = NULL;
const  char * author[6] = { "卡管理权限","计费标准权限","计费管理权限","费用管理权限","查询统计权限","权限管理权限" };
int main()
{
	readfile();
	enter();
	savefile();
	return 0;
}

void readfile() {
	//读取文件创建卡链表
	FILE *fp1;
	int i = 0;
	struct card *card, *card2;

	if ((fp1 = fopen("card.txt", "r")) == NULL) {
		printf("打开失败!\n");
		exit(0);
	}

	while (!feof(fp1)) {
		if ((card = (struct card*)malloc(sizeof(struct card))) == NULL) {
			printf("申请内存空间失败!\n");
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

	//读取文件创建管理员链表
	FILE *fp;
	int j = 0;
	struct administ *a, *a1;

	if ((fp = fopen("administor.txt", "r")) == NULL) {
		printf("打开错误!\n");
		exit(0);
	}

	while (!feof(fp)) {
		if ((a = (struct administ*)malloc(sizeof(struct administ))) == NULL) {
			printf("申请内存空间失败!\n");
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
	//读取文件创建计费标准链表
	FILE *fp2;
	int k = 0;
	struct account *c1, *c2;

	if ((fp2 = fopen("rate.txt", "r")) == NULL) {
		printf("打开失败!\n");
		exit(0);
	}

	while (!feof(fp2)) {
		if ((c1 = (struct account*)malloc(sizeof(struct account))) == NULL) {
			printf("申请内存空间失败!\n");
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
	//读取文件创建消费记录链表
	FILE *fp3;
	int l = 0;
	struct chargerecord  *record, *record2;

	if ((fp3 = fopen("record.txt", "r")) == NULL) {
		printf("打开失败!\n");
		exit(0);
	}

	while (!feof(fp3)) {
		if ((record = (struct chargerecord*)malloc(sizeof(struct chargerecord))) == NULL) {
			printf("申请内存空间失败!\n");
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
		printf("输入管理员账号:");scanf("%s", a);
		printf("\n     输入密码:");scanf("%s", b);

		for (a1 = headadminist; a1 != NULL; a1 = a1->next)
			if (!strcmp(a, a1->id) && !strcmp(b, a1->codon)) {
				j = 1;break;
			}
		if (j == 0) printf("\n账号或密码错误请重新输入!\n");

	} while (j != 1);
	printf("尊敬的管理员，你的权限有:");
	for (i = 0; i < 6; i++) {
		if (a1->authority[i] == '1') printf("%s  ", author[i]);
	}
	printf("\n\n\n");
	system("pause");
	menu(a1->authority);
}
void menu(char *author) {
	int i, j = 1;           //j控制是否退出系统，i为菜单选项

	while (j) {
		system("cls");
		printf("         网吧管理系统\n");
		printf("====================================\n");
		printf("1-卡管理**************2-计费标准管理\n");
		printf("3-计费管理************4-费用管理\n");
		printf("5-查询统计************6-权限管理\n");
		printf("-------------0-退出系统-------------\n");
		printf("====================================\n");
		printf("\n请输入菜单标号( 0-6)：");
		scanf("%d", &i);
		if (i > 0 && i <= 6) {
			if (author[i - 1] != '1') i = 7;
		}
		else if (i != 0) { printf("\n输入菜单标号错误请重新( 0-6 ):");break; }
		switch (i) {
		case 0:
			system("cls");
			printf("\n欢迎下次使用！");j = 0;break;
		case 1:
			system("cls");
			printf("\n******************************************");
			printf("\n==============1-添加卡====================");
			printf("\n==============2-查询卡====================");
			printf("\n==============3-注销卡====================");
			printf("\n==============0-返回上级菜单==============");
			printf("\n******************************************");
			printf("\n请输入菜单标号（0-3）：");
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
			printf("\n=== 1 新增计费标准---------2 查询计费标准===");
			printf("                                           ");
			printf("\n=== 3 删除计费标准---------4 修改计费标准===");
			printf("\n============ 0 返回上级菜单 ================");
			printf("\n********************************************");
			printf("\n请输入菜单标号（0-4）：");
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
			printf("\n============ 1 上机---------2 下机============");
			printf("\n                                           ");
			printf("\n=============== 0 返回上级菜单 ===============");
			printf("\n**********************************************");
			printf("\n请输入菜单标号（0-2）：");
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
			printf("\n=========== 1 充值-------2 退费 ============");
			printf("\n                                           ");
			printf("\n============= 0 返回上级菜单 ===============");
			printf("\n********************************************");
			printf("\n请输入菜单标号（0-2）：");
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
			printf("\n==============1-查询消费记录=================");
			printf("\n==============2-统计总营业额=================");
			printf("\n==============3-统计月营业额===============");
			printf("\n==============0-返回上级菜单=================");
			printf("\n*********************************************");
			printf("\n请输入菜单标号（0-3）：");
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
			printf("\n========= 1 添加管理员-----2 删除管理员 =========");
			printf("\n                                           ");
			printf("\n============== 0 返回上级菜单 ===================");
			printf("\n*************************************************");
			printf("\n请输入菜单标号（0-2）：");
			scanf("%d", &i);
			switch (i)
			{
			case 1: addadminist(); break;
			case 2: deleteadminist(); break;
			default: break;
			}break;
		default:
			system("cls");
			printf("\n不在您权限范围内! 请重新输入你的选择：\n");system("pause");
		}
	}

	system("pause");
}
void addcard() {
	struct card *c = headcard, *c1;
	if ((c1 = (struct card*)malloc(sizeof(struct card))) == NULL) {
		printf("申请内存空间失败!\n");
		exit(0);
	}

	printf("\n新卡的账号:");scanf("%s", c1->id);
	printf("\n      密码：");scanf("%s", c1->codon);
	printf("\n      充值金额(单位：元)：");scanf("%lf", &c1->funds);
	c1->state = 1;

	if (headcard == NULL) headcard = c1;
	else {
		while (c->next != NULL) {
			c = c->next;
		}
		c->next = c1;
	}
	c1->next = NULL;
	printf("\n成功！新开的卡号:%s\n", c1->id);
	printf("\n该卡可以上机，余额为%.2lf元", c1->funds);
	system("pause");
}
void querycard() {
	struct card *c;
	char id[20];
	int i = 1;
	printf("\n请输入你需要查询的卡号:");
	while (i) {
		scanf("%s", id);
		for (c = headcard; c != NULL; c = c->next) {
			if (!strcmp(c->id, id)) {
				printf("\n该卡余额为：%.2lf（元）", c->funds);
				if (c->state == 1) printf("\n该卡尚未注销，可以使用！");
				else printf("\n该卡已注销，不能使用！");i = 0;break;
			}
		}
		if (c == NULL) printf("\n卡号错误或该卡不存在，请重新输入：");
	}
	system("pause");
}
void deletecard() {
	struct card c, *c1;
	int i = 1;

	while (i) {
		printf("\n请需要注销的卡号:");	scanf("%s", c.id);
		printf("\n            密码:");scanf("%s", c.codon);
		for (c1 = headcard; c1 != NULL; c1 = c1->next) {
			if (!strcmp(c.id, c1->id) && !strcmp(c.codon, c1->codon)) {
				c1->state = 0;
				printf("\n该卡号已成功注销");i = 0;
				break;
			}
		}
		if (c1 == NULL) printf("\n卡号或密码错误请重新输入!");
	}
	system("pause");
}
void addaccount() {
	struct account *c = headaccount, *c1;int i = 1;
	if ((c1 = (struct account *)malloc(sizeof(struct account))) == NULL) {
		printf("申请内存空间失败!\n");
		exit(0);
	}
	printf("\n请输入新增计费标准(上机的小时及每小时收费):");
	scanf("%d%d", &c1->hour, &c1->condume);
	for (c = headaccount; c != NULL; c = c->next) {
		if (c->hour == c1->hour) { printf("\n该时间段的收费标准已存在!");i = 0;break; }
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
		printf("\n新增的计费标准:上机%d小时则每小时消费%d元.", c1->hour, c1->condume);
	}
	system("pause");
}
void queryaccount() {
	int hour;int i = 0;
	struct account *c;
	printf("\n输入上机的小时数:");
	scanf("%d", &hour);

	for (c = headaccount; c != NULL; c = c->next) {
		if (c->hour == hour) {
			printf("\n若上机%d小时则每小时消费%d元\n", hour, c->condume);i = 1;
			break;
		}
	}
	if (!i) printf("\n没有上机时间为%d小时的计费标准!", hour);system("pause");
}
void deleteaccount() {

	int hour, i = 0;
	struct account *c1, *c2;

	printf("\n请输入你要删除的计费标准的上机时间（小时）:");
	scanf("%d", &hour);
	for (c1 = headaccount; c1 != NULL; c1 = c1->next) {
		if (c1->hour == hour) {
			if (c1 == headaccount) headaccount = c1->next;
			else c2->next = c1->next;
			free(c1);
			printf("\n成功删除该计费标准!");i = 1;
			break;
		}
		c2 = c1;
	}
	if (!i) printf("\n无该计费标准！");system("pause");
}
void alteraccount() {

	int hour, i = 0;
	struct account *c;

	printf("\n请输入你要修改的计费标准的上机时间（小时）:");
	scanf("%d", &hour);

	for (c = headaccount; c != NULL; c = c->next) {
		if (c->hour == hour) {
			printf("\n请输入修改后上机%d小时每小时的计费(元):", hour);
			scanf("%d", &c->condume);i = 1;break;
		}
	}
	if (!i) printf("\n无该计费标准!");system("pause");
}
void upline() {
	time_t nowtime;
	struct tm *lt;
	struct card c, *c1;
	struct chargerecord *r1 = headrecord, *r2;
	time(&nowtime);
	lt = localtime(&nowtime);
	printf("\n请输入卡号: ");scanf("%s", c.id);
	printf("\n      密码：");scanf("%s", c.codon);

	for (c1 = headcard; c1 != NULL; c1 = c1->next) {
		if (!strcmp(c.id, c1->id) && !strcmp(c.codon, c1->codon) && c1->state) {
			printf("\n该卡上机成功！余额为%.2lf", c1->funds);
			if ((r2 = (struct chargerecord*)malloc(sizeof(struct chargerecord))) == NULL) {
				printf("申请内存空间失败!\n");
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
	if (c1 == NULL) printf("\n账号密码错误或该卡已注销");system("pause");
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
	printf("\n请输入需要下机的卡号:");
	do {
		scanf("%s", c.id);
		for (r1 = headrecord; r1 != NULL; r1 = r1->next)
			if (!strcmp(c.id, r1->id) && !r1->pay) {
				j = 1;break;
			}
		if (!j) printf("\n账号错误或该卡未上机，请重新输入:");

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
			if (c1->funds < 0)  printf("\n该卡号已欠费，请及时充值！");
			printf("该卡余额为 %.4lf\n", c1->funds);
			break;
		}
	}system("pause");
}
void recharge() {
	double money, flag = 1;
	struct card *c;
	char id[25];

	printf("\n请输入充值的卡号:");
	scanf("%s", id);
	while (flag) {
		for (c = headcard; c != NULL; c = c->next) {
			if (!strcmp(c->id, id)) {
				printf("\n请输入充值的金额:");
				scanf("%lf", &money);
				c->funds += money;
				printf("\n充值成功！该卡余额为: %.2lf (元)\n", c->funds);
				flag = 0;break;
			}

		}

		if (flag) { printf("\n无法充值！你的卡号错误，请重新输入卡号:");scanf("%s", id); }
	}system("pause");
}
void returnmoney() {
	double money, flag = 1, j = 0;
	struct card *c1, c;
	printf("\n请输入需要退费的卡号:");
	do {
		scanf("%s", c.id);
		for (c1 = headcard; c1 != NULL; c1 = c1->next)
			if (!strcmp(c.id, c1->id)) {
				j = 1;break;
			}
		if (!j) printf("\n账号错误请重新输入:");

	} while (j == 0);

	for (c1 = headcard; c1 != NULL; c1 = c1->next) {
		if (!strcmp(c1->id, c.id)) {
			printf("\n请输入退费金额:");
			scanf("%lf", &money);
			if (c1->funds > money) {
				c1->funds -= money;
				printf("\n退费成功！该卡余额为：%.2lf", c1->funds);break;
			}
			else printf("\n对不起你的余额不足！");
			break;
		}
	}system("pause");
}
void querryrecord() {
	int j = 0;
	char id[25];
	struct chargerecord *r1, c;
	int a1, a2, a3, a4, a5, a6, b1, b2, b3, b4;

	printf("\n请输入查询的卡号:");
	do {
		scanf("%s", c.id);
		for (r1 = headrecord; r1 != NULL; r1 = r1->next)
			if (!strcmp(c.id, r1->id)) { j = 1;break; }
		if (j == 0) printf("\n账号错误请重新输入:");
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

			printf("\n卡号:%s 上机时间:%d-%02d-%02d %02d:%02d 下机时间:%d-%02d-%02d %02d:%02d 消费金额:%.2lf", r1->id, a1, a2, a3, a4, a5, a6, b1, b2, b3, b4, r1->pay);
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

	printf("\n请输入从(2018)某年(05)某月(09)某日到今天的营业额:");
	scanf("%d", &day);
	a = day / 100;b = day / 100 % 100;c = day % 100;
	for (r1 = headrecord; r1 != NULL; r1 = r1->next) {
		if (day < r1->endday) s += r1->pay;
	}

	printf("\n%d-%02d-%02d到今天的营业额为:%.3lf(元)", a, b, c, s);
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

	if ((fp = fopen("monthfunds.txt", "w")) == NULL) { printf("打开文件失败!\n");exit(0); }

	for (i = 0; i < 12; i++) {
		fprintf(fp, "在%d月上机次数是%d,总营业额是%lf\n", i + 1, mon[i].times, mon[i].sum);
	}

	if (fclose(fp)) { printf("error!\n");	exit(0); }

	for (i = 0; i < 12; i++) {
		printf("\n%d月上机次数是%d, 营业额是%.2lf", i + 1, mon[i].times, mon[i].sum);
	}
	printf("\n月营业额已保存到\"monthfunds.txt\"文件!");system("pause");
}
void addadminist() {
	int num = 0, in[6] = { 0,0,0,0,0,0 };
	struct administ  *a1 = headadminist, *a;

	if ((a = (struct administ*)malloc(sizeof(struct administ))) == NULL) {
		printf("申请内存空间失败!\n");
		exit(0);
	}
	printf("\n请输入新增的管理员账号:");
	scanf("%s", a->id);
	printf("\n请输入新增的管理员密码:");
	scanf("%s", a->codon);

	printf("\n");
	for (int i = 0;i < 6;i++) 	printf("%d.%s  ", i, author[i]);
	printf("\n输入新增管理员的权限（对应数字序号,-1结束）：");

	do {
		scanf("%d", &num);
		if (num<6 && num>-1) in[num] = 1;
		else if (num != -1) printf("\n序号错误请重新输入！");
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
		printf("\n成功添加新的管理员账号！");system("pause");
}
void deleteadminist() {
	char str[25];
	struct administ *a1, *a2;

	printf("\n请输入要删除的管理员账号:");
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
		if (a1 == NULL) printf("\n账号错误！请重新输入：");
	} while (a1 == NULL);
	printf("\n删除管理员成功！");system("pause");
}
void savefile() {
	FILE *fp;        //保存卡链表到文件
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
	//保存计费标准链表
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
	//保存消费记录链表
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
	//保存管理元链表

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