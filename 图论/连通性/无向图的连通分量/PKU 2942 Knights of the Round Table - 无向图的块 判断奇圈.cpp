/* PKU 2942 Knights of the Round Table - 无向图的块 判断奇圈 收藏 
题目大意:
N个骑士某些骑士之间会有仇恨。骑士们开会时围坐在一个圆桌旁。
一次会议能够举行，当且仅当没有相邻的两个骑士相互仇恨，且开会人数为大于2的奇数。
若某个骑士任何会议都不能参加，那么就必须将它踢出。给出骑士之间的仇恨关系，问需要踢出多少个骑士。

分析：
首先，求出无向图的块（即同一个块中没有割点）。块中的节点一定是可以组成环的。
可以证明，若块中存在一个奇圈，那么块中所有顶点都在一个奇圈上。
那么，对于每个块进行判定，若该块存在奇圈，则块中所有的骑士都不会被踢出。即可求解。
需要注意的是，同一个顶点可能出现在多个块当中。所以在计数时不能直接累加含有奇圈的块的顶点，而是要先标记再累加。
至于只有一个骑士的情况怎么处理，貌似题目没有这样的数据……

*/ 

#include <stdio.h> 
#include <memory.h> 

#define clr(a) memset(a,0,sizeof(a)) 
#define MIN(a,b) ((a)>(b)?(b):(a)) 

#define N 1005 
#define M 4000005 

typedef struct NS{ int j; struct NS *next; }Node; 
Node mem[M]; int memp; 
void addEdge(Node *e[],int i,int j){ 
    Node *p=&mem[memp++]; p->j=j; p->next=e[i]; e[i]=p; 
} 

int anc[N],mark[N],deep[N],stack[N],sp,nblock;  //anc[] DFS中i可达最远祖先的深度 


int DFS_block(Node *e[],int i,int father,int dth,int cut[],Node *be[]){ 
    int j,k,tofather=0,sons=0; Node *p; 
    stack[sp++]=i; mark[i]=1; anc[i]=deep[i]=dth; 
     
    for(p=e[i];p!=NULL;p=p->next){ 
        j=p->j; 
        if(mark[j]==1 && (j!=father||tofather)) anc[i]=MIN(anc[i],deep[j]); 
        if(mark[j]==0){ 
            DFS_block(e,j,i,dth+1,cut,be); 
            anc[i]=MIN(anc[i],anc[j]); sons++; 
            if((father==-1&&sons>1)||(father!=-1&&anc[j]>=deep[i])) 
                cut[i]=1; 
            if(anc[j]>=deep[i]) { 
                addEdge(be,nblock,i); 
                for(stack[sp]=-1;stack[sp]!=j;addEdge(be,nblock,stack[--sp])); 
                nblock++; 
            } 
        } 
        if(j==father) tofather=1; 
    } 
    mark[i]=2; 
} 

/* 
无向图的块 
参数: 
    传入无向图邻接表e[], 返回无向图块的个数nblock 
    cut[]返回顶点i是否为割顶 
    be[]返回每个块所包含的顶点,be[k]之后是块k包含的所有顶点. 
*/ 
int Block(Node *e[],int n,int cut[],Node *be[]){ 
    int i,j,k,f[N];  
    clr(mark); nblock=0; sp=0; 
    for(i=0;i<n;i++) if(mark[i]==0) DFS_block(e,i,-1,1,cut,be); 
    return nblock; 
} 

/**************************************/ 


int DFS_judge(Node *e[],int i,int col,int in[],int color[]){ 
    int j,k; Node *p; 
    color[i]=col; 
    for(p=e[i];p!=NULL;p=p->next){ 
        j=p->j; 
        if(!in[j]) continue; 
        if(!color[j]){ if(DFS_judge(e,j,-col,in,color)) return 1;} 
        else { 
            if(color[j]==col) { 
                return 1; 
            } 
        } 
    } 
    return 0; 
} 

void Judge(Node *e[],Node *block,int good[]){ 
    int i,j,k; Node *p,*q; 
    int in[N],color[N]; 
    clr(in); clr(color); 
    for(p=block;p!=NULL;p=p->next){ 
        in[p->j]=1; 
    } 
    if(DFS_judge(e,block->j,1,in,color)){ 
        for(p=block;p!=NULL;p=p->next) good[p->j]=1; 
    } 
} 


int n,m,w; 
Node *e[N]; 
Node *be[N]; 
int cut[N]; 
int good[N],count; 
int hate[N][N]; 

int main() 
{ 
    int i,j,k; 
     
    while(scanf("%d%d",&n,&w)!=EOF && n+w){ 
        //init 
        memp=0; clr(e); clr(be); clr(hate); clr(cut); 
        //input 
        for(k=0;k<w;k++) { 
            scanf("%d%d",&i,&j); i--;j--; 
            hate[i][j]=hate[j][i]=1; 
        } 
        //create map 
        for(i=0;i<n;i++) for(j=i+1;j<n;j++) if(!hate[i][j]){ 
            addEdge(e,i,j); 
            addEdge(e,j,i); 
        } 
        //block 
        m=Block(e,n,cut,be); 
         
        //count 
        clr(good); count=0; 
        for(k=0;k<m;k++) Judge(e,be[k],good); 
        for(i=0;i<n;i++) if(good[i]) count++; 
        //output 
        printf("%d\n",n-count); 
    } 
     
    return 0; 
} 

本文来自CSDN博客，转载请标明出处：http://blog.csdn.net/tiaotiaoyly/archive/2008/11/15/3306727.aspx
