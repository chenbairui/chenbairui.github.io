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
	printf("���ڴ��ļ���ȡ���ݵ��������Ե�...\n");
	head=creat();
	while(1)
	{
		system("cls");
		printf("        ѧ���ɼ�����ϵͳ\n");
		printf("====================================\n");
		printf("1-�������        2-����ά��\n");
		printf("3-��������        4-ͳ�Ʒ���\n");
		printf("5-�������        0-�˳�\n");
		printf("====================================\n");
		printf("     ������˵���ţ�1-5,0��:");
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
		printf("     �����˵�-ѧ���ɼ�ά������\n");
		printf("====================================\n");
		printf("  1-���һ��ѧ���ɼ�\n");
		printf("  2-�޸�һ��ѧ���ɼ�\n");
		printf("  3-ɾ��һ��ѧ���ɼ�\n");
		printf("  4-��ѯһ��ѧ���ɼ�\n");
		printf("  0-�˻��ϼ��˵�\n");
		printf("====================================\n");
		printf("   ������˵���ţ�1-4,0��:");
		scanf("%d",&sel2);
	        	switch(sel2){
			  case 1:
			   if((p=(struct stulink *) malloc(sizeof(struct stulink )))==NULL)
			   { printf("���ܳɹ����䴢���\n");
			    exit (9);
		     	}
			    (*p).next=NULL;
			    printf("�����������ͳɼ�\n");
			    head=insert_nobe(head,p);head=rank_link(head);
				
			    getchar();getchar();
			    break;
		       case 2:
			    printf("�������޸ĵ�ѧ����ѧ�ţ�");
			    scanf("%d",&num);
				head=edit_node(head,num);head=rank_link(head);
				 getchar();getchar();
		     	break;
	          case 3:
		     	printf("������ɾ��ѧ����ѧ�ţ�");
			    scanf("%d",&num);
				head= delete_node (head,num);head=rank_link(head);
			   getchar();getchar();
			    break;
		      case 4:
			   printf("�������ѯѧ����ѧ�ţ�");
			   scanf("%d",&num);
			   head=query_node (head,num);
			   getchar();getchar();
			   break;
		     case 0:
		    	printf("����һ���˵��ɹ���\n");flag=1;
			    break;
	         }
			if(flag)	break;
		}flag=0;
		break;
		case 3:
        while(1)
	    {
	    system("cls");
		printf("     �����˵�-�����������\n");
		printf("========================================\n");
		printf("1-����ѧ������");
		printf("        2-��ѧ����������\n");
		printf("3-���ɼ�����������");
		printf("     4-�˻��ϼ��˵�\n");
		printf("========================================\n");
		printf("   ������˵���ţ�1-4��:");
		scanf("%d",&selp);
	  	        switch(selp){
	          	case 1:
			         head=rank_link(head);
			         printf("���μ��������£�\n");
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
			      printf("ͳ�ƽ�����£�\n");
			      head=analysis_link(head,1);
			      getchar();
			      break;
		case 5:
           while(1)
	    {
	       system("cls");
			printf("     �����˵�-�����������\n");
		    printf("=======================================\n");
			printf("1-ѧ������  2-�ɼ�����  0-�˻���һ���˵�\n");
			 printf("======================================\n");
			printf("������˵���ţ�1-2,0����");
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
			printf("��ӭʹ��ѧ������ϵͳ��лл��\n");
			getchar();getchar();
			return 0;
		default :
			printf("�������������ѡ��\n");
		    getchar();getchar();
			break;
		}
		printf("�����������....");
		getchar();
		}
		
return 0;
}
struct stulink *  creat ( )  //��ȡ//
{   FILE * fp;
	int sum=0;
    struct stulink  *head=NULL;
	struct stulink *p1;struct stulink *p2=NULL;
	int cjj,xhh,mcc;
	char djj;
	char str[10];


  if((fp=fopen("student.dat","r"))==NULL) 
{  printf("�޷����ļ�����������ʧ�ܣ�\n"); exit(0);}


  while (fscanf(fp,"%d%s%d %c%d",&xhh,str,&cjj,&djj,&mcc)!=EOF){
	sum++;
	if((p1=(struct stulink *) malloc(sizeof(struct stulink )))==NULL)
	{ printf("���ܳɹ����䴢���\n");exit (0);}

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
	if(fclose(fp)){printf("�ر��ļ�����!\n");exit(0);}
	printf("��ȡ����������ȡ%d��ѧ����Ϣ\n",sum);
	printf("�����������....");
	getchar();
	return head;
}
struct stulink *  creat_link (struct stulink *head )  //�������//
{  				
	int cj,i;
	int max_num=0;
	char xm[20];
	struct stulink *p=head,*p1,*p2=NULL;
	
	while(p!=NULL){
		if((p->xh)>(max_num)) max_num=p->xh ;									//�������ѧ��
		
		p=p->next ;
	}
	p=head;
	if(p!=NULL){
		while(p->next!=NULL){
			p=p->next ;										//��pָ��ĩ����next( ������ĩ�����չ���� )
		}
	}

	i=max_num;
	printf("�����������ͳɼ�\n����ɼ�Ϊ-1�����������\n");
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
	printf("������Ӻ�Ľ�����£�\n");
	output_link(head);


	return head;
}
struct stulink *  insert_nobe(struct stulink *head ,struct stulink *p0)  //����//
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
	printf("�����Ľ�����£�\n");
	output_link(head);
	return head;

}
struct stulink *  query_noded (struct stulink *head,int num) // ����//
{
   struct stulink *p=head;
   while((p->xh!=num)&&(p->next!=NULL)){ p=p->next;}
   if(p->xh!=num) p=NULL;
   return p;
}
struct stulink *  edit_node (struct stulink *head ,int num)   //�޸�//
{
	struct stulink *p=head;
	p=query_noded(head,num);
	if(p==NULL) printf("�޸�������Ϣ\n");
	else {
		
		printf("ѧ�ţ�%d  ������%s �ɼ�=%d  �ȼ�=%c  ����=%d\n",p->xh,p->xm,p->cj,p->dj,p->mc);
		printf("�����������ͳɼ���");
		scanf("%s%d",p->xm,&p->cj);
	}
	printf("�޸ĺ�Ľ�����£�\n");
	head=rank_link (head);
	head= analysis_link(head,0);
	output_link(head);
	return head;
}

struct stulink *  delete_node (struct stulink *head ,int num)   //ɾ��//
{   struct stulink * p1=head,*p2=head;
while((p1->xh!=num)&&(p1->next!=NULL))
{  
	p2=p1;p1=p1->next;
}
if(p1->xh==num){
	if(head==p1) head=p1->next;
	else p2->next=p1->next;
	printf("ѧ�ţ�%d  ������%s �ɼ�=%d  �ȼ�=%c  ����=%d\n",p1->xh,p1->xm,p1->cj,p1->dj,p1->mc);
	free(p1);
	printf("ɾ����Ľ�����£�\n");
	head=rank_link (head);
	head= analysis_link(head,0);
	output_link(head);
}
else printf("��ɾ���Ľڵ㣡\n");
return head;
}

struct stulink *  query_node (struct stulink *head,int num)   //��ѯ//
{   
	struct stulink *p=head;
	
	p=query_noded(head,num);                                                                                                                                                                                                                                               
	if(p==NULL) printf("�޸�������Ϣ!\n");
	else printf("��ѯ�����\n����������%s��ѧ�ţ�%d,�ɼ���%d,���Σ�%d�ȼ�:%c\n",p->xm,p->xh,p->cj,p->mc,p->dj);
	return head;
}

struct stulink *  rank_link (struct stulink *head) //��������//
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
struct stulink *  analysis_link (struct stulink *head,int n)  //����ȼ�����//
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
		printf("A:90������ B:80������ C:70������ D:60������ E��60����\n");
		printf("A�ȼ�����=%d\nB�ȼ�����=%d\nC�ȼ�����=%d\nD�ȼ�����=%d\nE�ȼ�����=%d\n",a[0],a[1],a[2],a[3],a[4]);}
	return head;


}
void output_link (struct stulink *head)  //����ȼ�������ѧ���ɼ���//
{    
	struct stulink *p1=head;
	printf("ѧ��            ����     �ɼ�   �ȼ�   ����\n");
	 for(;p1!=NULL;p1=p1->next)
    printf(" %-15d%-8s%5d%6c%5d\n",p1->xh,p1->xm,p1->cj,p1->dj,p1->mc);
	 
}
void SaveToFile(struct stulink *head){
	FILE *fp;
	struct stulink *p;
	
	int sum=0;
	printf("���ڽ������е����ݱ��浽�ļ������Ժ�...\n\n");
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
	printf("\n�����������������%d��ѧ�����ݣ�\n",sum);

}
struct stulink *Sort_Link(struct stulink *head,int flag){		//ֱ��������0�ǳɼ�����1��ѧ������//
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
		//ȥ��ԭ�������еĽ��//
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

