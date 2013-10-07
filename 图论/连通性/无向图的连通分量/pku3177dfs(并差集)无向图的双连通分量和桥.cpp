 /*PKU3177 Redundant Paths- ����ͼ��˫��ͨ��������
 ��Ŀ����:
����һ��������ͨͼ,�ж�������Ҫ�Ӷ�������,����ʹ����������֮�������������໥"�߶���"�ĵ�·.ע��,���ܺ����ر�.
����:
��Ȼ,��ͬһ��˫��ͨ����������е���Եȼ۵ؿ���һ����.������,��ͼ��һ����,���ı���ԭ����ͼ����.
��������ת��Ϊ��������������Ӷ���������ʹͼ��Ϊ˫��ͨͼ.
������: 
��ӱ��� = (���ж�Ϊ1�Ľڵ���+1) / 2
˵�����⻰,����ͼ��˫��ͨ������Ϊ"�߶���"��"�������"����,���ǵ��������в���,ע������.ע����������ͼ�Ŀ� 
 */
#include <stdio.h>
#include <memory.h>

#define clr(a) memset(a,0,sizeof(a))
#define MIN(a,b) ((a)>(b)?(b):(a))

#define N 1005
#define M 20005

typedef struct NodeStr{
    int j; struct NodeStr *next;
}Node;
Node mem[M]; int memp;
void addEdge(Node *e[],int i,int j){
    Node *p=&mem[memp++];
    p->j=j; p->next=e[i]; e[i]=p;
}

int FindSet(int f[],int i){
    int j=i,t;
    while(f[j]!=j) j=f[j];
    while(f[i]!=i) {t=f[i];f[i]=j;i=t;}
    return j;
}
void UniteSet(int f[],int i,int j){
    int p=FindSet(f,i), q=FindSet(f,j);
    if(p!=q) f[p]=q;
}

int anc[N],mark[N],deep[N];

int bridge[M][2],nbridge;

void DFS_2conn(Node *e[],int i,int father,int dth,int f[]){
    int j,k,tofather=0; Node *p;
    mark[i]=1; anc[i]=deep[i]=dth;
    
    for(p=e[i];p!=NULL;p=p->next){
        j=p->j;
        if(mark[j]==1 && (j!=father||tofather)) anc[i]=MIN(anc[i],deep[j]);
        if(mark[j]==0){
            DFS_2conn(e,j,i,dth+1,f);
            anc[i]=MIN(anc[i],anc[j]);
            if(anc[j]<=deep[i]) UniteSet(f,i,j); //i,j��ͬһ��˫��ͨ���� 
            //if((father==-1&&sons>1)||(father!=-1&&anc[j]>=deep[i])) cut[i]=1; //i�Ǹ�� 
            if(anc[j]>deep[i]) bridge[nbridge][0]=i,bridge[nbridge++][1]=j; //��(i,j)����
        }
        if(j==father) tofather=1;
    }
    mark[i]=2;
}

/*
����ͼ����˫��ͨ����
����:
    ����ͼ�ڽӱ�e[],  ����˫��ͨ��������ncon
    belong[]���ؽڵ�i���ڵ�˫��ͨ�������belong[i],[0,ncon-1] 
    ���Դ����رߺͲ���ͨ�����. 
*/
int DoubleConnection(Node *e[],int n,int belong[]){
    int i,j,k,f[N],ncon=0;
    for(i=0;i<n;i++) f[i]=i,belong[i]=-1;   //f[]���鼯���� 
    clr(mark); nbridge=0;

    for(i=0;i<n;i++) if(mark[i]==0) DFS_2conn(e,i,-1,1,f);

    for(i=0;i<n;i++){
        k=FindSet(f,i); if(belong[k]==-1) belong[k]=ncon++;
        belong[i]=belong[k];
    }
    return ncon;
}
/************************************/

int n,m,w;
Node *e[N];
Node *ce[N];
int belong[N];
int d[N],count;

int main()
{
    int i,j,k;

    while(scanf("%d%d",&n,&w)!=EOF){
        //init
        memp=0; clr(e);
        //input
        for(k=0;k<w;k++){
            scanf("%d%d",&i,&j); i--; j--;
            addEdge(e,i,j);
            addEdge(e,j,i);
        }
        //DoubleConnection
        m=DoubleConnection(e,n,belong);
        //for(i=0;i<n;i++) printf("%d: %d\n",i+1,belong[i]);
        //work d[]
        clr(d);
        for(k=0;k<nbridge;k++){
            i=bridge[k][0];
            j=bridge[k][1];
            d[belong[i]]++;
            d[belong[j]]++;
        }
        //get ans
        count=0;
        for(i=0;i<m;i++) if(d[i]==1) count++;
        printf("%d\n",(count+1)/2);
    }
    
    return 0;
}
