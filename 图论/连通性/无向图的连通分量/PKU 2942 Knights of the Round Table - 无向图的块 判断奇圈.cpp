/* PKU 2942 Knights of the Round Table - ����ͼ�Ŀ� �ж���Ȧ �ղ� 
��Ŀ����:
N����ʿĳЩ��ʿ֮����г�ޡ���ʿ�ǿ���ʱΧ����һ��Բ���ԡ�
һ�λ����ܹ����У����ҽ���û�����ڵ�������ʿ�໥��ޣ��ҿ�������Ϊ����2��������
��ĳ����ʿ�κλ��鶼���ܲμӣ���ô�ͱ��뽫���߳���������ʿ֮��ĳ�޹�ϵ������Ҫ�߳����ٸ���ʿ��

������
���ȣ��������ͼ�Ŀ飨��ͬһ������û�и�㣩�����еĽڵ�һ���ǿ�����ɻ��ġ�
����֤���������д���һ����Ȧ����ô�������ж��㶼��һ����Ȧ�ϡ�
��ô������ÿ��������ж������ÿ������Ȧ����������е���ʿ�����ᱻ�߳���������⡣
��Ҫע����ǣ�ͬһ��������ܳ����ڶ���鵱�С������ڼ���ʱ����ֱ���ۼӺ�����Ȧ�Ŀ�Ķ��㣬����Ҫ�ȱ�����ۼӡ�
����ֻ��һ����ʿ�������ô����ò����Ŀû�����������ݡ���

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

int anc[N],mark[N],deep[N],stack[N],sp,nblock;  //anc[] DFS��i�ɴ���Զ���ȵ���� 


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
����ͼ�Ŀ� 
����: 
    ��������ͼ�ڽӱ�e[], ��������ͼ��ĸ���nblock 
    cut[]���ض���i�Ƿ�Ϊ� 
    be[]����ÿ�����������Ķ���,be[k]֮���ǿ�k���������ж���. 
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

��������CSDN���ͣ�ת�������������http://blog.csdn.net/tiaotiaoyly/archive/2008/11/15/3306727.aspx
