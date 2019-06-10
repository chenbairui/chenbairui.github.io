#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
struct stulink
{
   int xh;
   char xm[10];
   int cj;
   char dj;
   int mc;
   struct stulink *next;

};

int main()
{   
	int sel,num,sel2;int selp,sell,flag=0;
	struct stulink *head=NULL,*p;
	struct stulink *  creat_link (struct stulink * );
	struct stulink *  insert_nobe(struct stulink *head,struct stulink *p);
	struct stulink *  edit_node (struct stulink *head ,int num);
	struct stulink *  delete_node(struct stulink *head  ,int num);
	struct stulink *  query_noded (struct stulink *head,int num);
	struct stulink *  query_node (struct stulink *head,int num);
	struct stulink *  rank_link (struct stulink *head);
	struct stulink *  analysis_link (struct stulink *head,int n);
	struct stulink *  sort_link (struct stulink *head);
	void output_link (struct stulink *head);
	struct stulink *  creat ( );
	void SaveToFile(struct stulink * head);
	struct stulink *Sort_Link(struct stulink *head,int flag);
	printf("正在从文件读取数据到链表，请稍等...\n");
	head=creat();
	while(1)
	{
		system("cls");
		printf("        学生成绩管理系统\n");
		printf("====================================\n");
		printf("1-批量添加        2-链表维护\n");
		printf("3-计算排序        4-统计分析\n");
		printf("5-报表输出        0-退出\n");
		printf("====================================\n");
		printf("     请输入菜单编号（1-5,0）:");
		scanf("%d",&sel);
		switch(sel)

		{
		case 1:
			
			head= creat_link(head);
			getchar();
			break;
        case 2:
		while(1)
		{
		system("cls");
		printf("     二级菜单-学生成绩维护管理\n");
		printf("====================================\n");
		printf("  1-添加一个学生成绩\n");
		printf("  2-修改一个学生成绩\n");
		printf("  3-删除一个学生成绩\n");
		printf("  4-查询一个学生成绩\n");
		printf("  0-退回上级菜单\n");
		printf("====================================\n");
		printf("   请输入菜单编号（1-4,0）:");
		scanf("%d",&sel2);
	        	switch(sel2){
			  case 1:
			   if((p=(struct stulink *) malloc(sizeof(struct stulink )))==NULL)
			   { printf("不能成功分配储存块\n");
			    exit (9);
		     	}
			    (*p).next=NULL;
			    printf("请输入姓名和成绩\n");
			    head=insert_nobe(head,p);head=rank_link(head);
				
			    getchar();getchar();
			    break;
		       case 2:
			    printf("请输入修改的学生的学号：");
			    scanf("%d",&num);
				head=edit_node(head,num);head=rank_link(head);
				 getchar();getchar();
		     	break;
	          case 3:
		     	printf("请输入删除学生的学号：");
			    scanf("%d",&num);
				head= delete_node (head,num);head=rank_link(head);
			   getchar();getchar();
			    break;
		      case 4:
			   printf("请输入查询学生的学号：");
			   scanf("%d",&num);
			   head=query_node (head,num);
			   getchar();getchar();
			   break;
		     case 0:
		    	printf("返回一级菜单成功！\n");flag=1;
			    break;
	         }
			if(flag)	break;
		}flag=0;
		break;
		case 3:
        while(1)
	    {
	    system("cls");
		printf("     二级菜单-计算排序管理\n");
		printf("========================================\n");
		printf("1-计算学生名次");
		printf("        2-按学号升序排序\n");
		printf("3-按成绩降序序排序");
		printf("     4-退回上级菜单\n");
		printf("========================================\n");
		printf("   请输入菜单编号（1-4）:");
		scanf("%d",&selp);
	  	        switch(selp){
	          	case 1:
			         head=rank_link(head);
			         printf("名次计算结果如下：\n");
					 output_link(head);
			         getchar();getchar();
			        break;
		        case 2: head=Sort_Link(head,1);output_link(head); getchar();getchar();break;
				case 3: head=Sort_Link(head,0);output_link(head); getchar();getchar();break;
		        case 4: flag=1;break;
	             	}
				if(flag) break;
	 }
		flag=0;
	   break;
		case 4:
			      printf("统计结果如下：\n");
			      head=analysis_link(head,1);
			      getchar();
			      break;
		case 5:
           while(1)
	    {
	       system("cls");
			printf("     二级菜单-报表输出管理\n");
		    printf("=======================================\n");
			printf("1-学号升序  2-成绩降序  0-退回上一级菜单\n");
			 printf("======================================\n");
			printf("请输入菜单编号（1-2,0）：");
			scanf("%d",&sell);
		
			       switch(sell){
				   case 1:head=Sort_Link(head,1);output_link(head);getchar();getchar();break;
				   case 2:head=Sort_Link(head,0);output_link(head);getchar();getchar();break;
				   case 0:flag=1;break;		
			}
				   if(flag) break;
		   }
		   break;
		case 0:
			SaveToFile(head);
			printf("欢迎使用学生管理系统，谢谢！\n");
			getchar();getchar();
			return 0;
		default :
			printf("输入错误，请重新选择\n");
		    getchar();getchar();
			break;
		}
		printf("按任意键继续....");
		getchar();
		}
		
return 0;
}
struct stulink *  creat ( )  //读取//
{   FILE * fp;
	int sum=0;
    struct stulink  *head=NULL;
	struct stulink *p1;struct stulink *p2=NULL;
	int cjj,xhh,mcc;
	char djj;
	char str[10];


  if((fp=fopen("student.dat","r"))==NULL) 
{  printf("无法打开文件，创建链表失败！\n"); exit(0);}


  while (fscanf(fp,"%d%s%d %c%d",&xhh,str,&cjj,&djj,&mcc)!=EOF){
	sum++;
	if((p1=(struct stulink *) malloc(sizeof(struct stulink )))==NULL)
	{ printf("不能成功分配储存块\n");exit (0);}

	else { 
	      strcpy(p1->xm,str);
	       p1->cj=cjj;
           p1->xh=xhh;p1->dj=djj;p1->mc=mcc;
		 	p1->next=NULL;
	   if(sum==1) head=p1;
	   else p2->next=p1;
	   p2=p1;
	   
	}
	}
	if(fclose(fp)){printf("关闭文件出错!\n");exit(0);}
	printf("读取结束，共读取%d名学生信息\n",sum);
	printf("按任意键继续....");
	getchar();
	return head;
}
struct stulink *  creat_link (struct stulink *head )  //批量添加//
{  				
	int cj,i;
	int max_num=0;
	char xm[20];
	struct stulink *p=head,*p1,*p2=NULL;
	
	while(p!=NULL){
		if((p->xh)>(max_num)) max_num=p->xh ;									//查找最大学号
		
		p=p->next ;
	}
	p=head;
	if(p!=NULL){
		while(p->next!=NULL){
			p=p->next ;										//把p指向末结点的next( 即是向末结点扩展链表 )
		}
	}

	i=max_num;
	printf("请输入姓名和成绩\n输入成绩为-1，输入结束！\n");
	scanf("%s%d",xm,&cj);
	while(cj!=-1){
		i++;
		if((p1=(struct stulink *)malloc(sizeof(struct stulink)))==NULL){
			exit(0);
		}
		p1->next=NULL;
		p1->xh=i;
		p1->cj=cj;
		strcpy(p1->xm,xm);

		if(head==NULL) head=p1;
		else p->next=p1;
		p=p1;
		scanf("%s%d",xm,&cj);
	}

	head=rank_link(head);
	head= analysis_link(head,0);
	printf("批量添加后的结果如下：\n");
	output_link(head);


	return head;
}
struct stulink *  insert_nobe(struct stulink *head ,struct stulink *p0)  //插入//
{    
	struct stulink * p1=head,*p2=head;
	while(p1->next!=NULL) {p1=p1->next; }
	p0->xh=(p1->xh+1);
	scanf("%s%d",p0->xm,&p0->cj);
	printf("\n");
	if(head==NULL)
	{head=p0; head->next=NULL;}
	else 
	{
		
		p1->next=p0;p0->next=NULL;

	}
	head=rank_link (head);
	head= analysis_link(head,0);
	p1=head;
	printf("插入后的结果如下：\n");
	output_link(head);
	return head;

}
struct stulink *  query_noded (struct stulink *head,int num) // 查找//
{
   struct stulink *p=head;
   while((p->xh!=num)&&(p->next!=NULL)){ p=p->next;}
   if(p->xh!=num) p=NULL;
   return p;
}
struct stulink *  edit_node (struct stulink *head ,int num)   //修改//
{
	struct stulink *p=head;
	p=query_noded(head,num);
	if(p==NULL) printf("无该生的信息\n");
	else {
		
		printf("学号：%d  姓名：%s 成绩=%d  等级=%c  名次=%d\n",p->xh,p->xm,p->cj,p->dj,p->mc);
		printf("请输入姓名和成绩：");
		scanf("%s%d",p->xm,&p->cj);
	}
	printf("修改后的结果如下：\n");
	head=rank_link (head);
	head= analysis_link(head,0);
	output_link(head);
	return head;
}

struct stulink *  delete_node (struct stulink *head ,int num)   //删除//
{   struct stulink * p1=head,*p2=head;
while((p1->xh!=num)&&(p1->next!=NULL))
{  
	p2=p1;p1=p1->next;
}
if(p1->xh==num){
	if(head==p1) head=p1->next;
	else p2->next=p1->next;
	printf("学号：%d  姓名：%s 成绩=%d  等级=%c  名次=%d\n",p1->xh,p1->xm,p1->cj,p1->dj,p1->mc);
	free(p1);
	printf("删除后的结果如下：\n");
	head=rank_link (head);
	head= analysis_link(head,0);
	output_link(head);
}
else printf("无删除的节点！\n");
return head;
}

struct stulink *  query_node (struct stulink *head,int num)   //查询//
{   
	struct stulink *p=head;
	
	p=query_noded(head,num);                                                                                                                                                                                                                                               
	if(p==NULL) printf("无该生的信息!\n");
	else printf("查询结果：\n该生姓名：%s，学号：%d,成绩：%d,名次：%d等级:%c\n",p->xm,p->xh,p->cj,p->mc,p->dj);
	return head;
}

struct stulink *  rank_link (struct stulink *head) //计算名次//
{
    int i=0,a[100],j,n,item,t,count=0;
	struct stulink * p1=head;
	if(head->next==NULL)  a[0]=head->cj;
	else for(;p1!=NULL;)     {a[i++]=p1->cj;p1=p1->next;}

	p1=head;
	n=i;
	for(i=0;i<n;i++)
		for(j=0;j<n-1-i;j++)
			if(a[j]<a[j+1]) { item=a[j];a[j]=a[j+1];a[j+1]=item;}
    t=1;
	for(j=0;j<n;){
		for(i=0;i<n;i++)
		{if(p1->cj==a[j])  {p1->mc=t;count++;}p1=p1->next;}
	     j+=count;
		t+=count;
		count=0;
		p1=head;
	}


	return head;
}
struct stulink *  analysis_link (struct stulink *head,int n)  //计算等级人数//
{   int a[5]={0,0,0,0,0};
	struct stulink *p=head;
	while(p!=NULL){
		if(p->cj>=90){ a[0]++; p->dj='A';}
		else if(p->cj>=80) { a[1]++;p->dj='B';}
		else if(p->cj>=70) { a[2]++;p->dj='C';}
		else if(p->cj>=60)  {a[3]++;p->dj='D';}
		else if(p->cj<60)   {a[4]++;p->dj='E';}
		p=p->next;


	}
	if(n==1) {
		printf("A:90及以上 B:80及以上 C:70及以上 D:60及以上 E：60以下\n");
		printf("A等级人数=%d\nB等级人数=%d\nC等级人数=%d\nD等级人数=%d\nE等级人数=%d\n",a[0],a[1],a[2],a[3],a[4]);}
	return head;


}
void output_link (struct stulink *head)  //输出等级人数和学生成绩表//
{    
	struct stulink *p1=head;
	printf("学号            姓名     成绩   等级   名次\n");
	 for(;p1!=NULL;p1=p1->next)
    printf(" %-15d%-8s%5d%6c%5d\n",p1->xh,p1->xm,p1->cj,p1->dj,p1->mc);
	 
}
void SaveToFile(struct stulink *head){
	FILE *fp;
	struct stulink *p;
	
	int sum=0;
	printf("正在将链表中的数据保存到文件，请稍候...\n\n");
	head=Sort_Link(head,1);
	p=head;
	if((fp = fopen("student.dat", "w")) == NULL){ 
        printf("Can't create File!");
    	exit(0);
    }
	 while(p!=NULL){
		 sum++;
		 if(p->next==NULL)
			 fprintf(fp,"%d%c%s%c%d%c%c%c%d",p->xh,' ',p->xm,' ',p->cj,' ',p->dj,' ',p->mc);
		 else
			 fprintf(fp,"%d%c%s%c%d%c%c%c%d%c",p->xh,' ',p->xm,' ',p->cj,' ',p->dj,' ',p->mc,'\n');
		 p=p->next;
	 }
	 fclose(fp); 
	printf("\n保存结束，共保存了%d名学生数据！\n",sum);

}
struct stulink *Sort_Link(struct stulink *head,int flag){		//直接排序函数0是成绩降序1是学号升序//
	struct stulink *first;
	struct stulink *tail;				
	struct stulink *p_min,*min;			
	struct stulink *p;
	first=NULL;						
	while(head!=NULL){
		for(p=head,min=head;p->next!=NULL;p=p->next){
			if(flag){							
				if(p->next->xh<min->xh){
					p_min=p;
					min=p->next;
				}
			}
			else{
				if(p->next->cj>min->cj){
					p_min=p;
					min=p->next;
				}
			}
		}

		if(first==NULL){
			first=min;
			tail=min;
		} else{
			tail->next=min;
			tail=min;
		}
		//去除原来链表中的结点//
		if(min==head){
			head=head->next;
		}else{
			p_min->next=min->next;
		}
		if(first!=NULL)
			tail->next=NULL;
}
	
	return first;
}

