 /*PKU3177 Redundant Paths- 无向图的双连通分量和桥
 题目大意:
给出一个无向连通图,判断最少需要加多少条边,才能使得任意两点之间至少有两条相互"边独立"的道路.注意,可能含有重边.
分析:
显然,在同一个双连通分量里的所有点可以等价地看做一个点.收缩后,新图是一棵树,树的边是原无向图的桥.
现在问题转化为了在树中至少添加多少条边能使图变为双连通图.
结论是: 
添加边数 = (树中度为1的节点数+1) / 2
说点题外话,无向图的双连通分量分为"边独立"和"顶点独立"两种,他们的性质略有差异,注意区别.注意区别无向图的块 
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
            if(anc[j]<=deep[i]) UniteSet(f,i,j); //i,j在同一个双连通分量 
            //if((father==-1&&sons>1)||(father!=-1&&anc[j]>=deep[i])) cut[i]=1; //i是割点 
            if(anc[j]>deep[i]) bridge[nbridge][0]=i,bridge[nbridge++][1]=j; //边(i,j)是桥
        }
        if(j==father) tofather=1;
    }
    mark[i]=2;
}

/*
无向图极大双连通分量
参数:
    无向图邻接表e[],  返回双连通分量个数ncon
    belong[]返回节点i所在的双连通分量编号belong[i],[0,ncon-1] 
    可以处理重边和不连通的情况. 
*/
int DoubleConnection(Node *e[],int n,int belong[]){
    int i,j,k,f[N],ncon=0;
    for(i=0;i<n;i++) f[i]=i,belong[i]=-1;   //f[]并查集数组 
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
