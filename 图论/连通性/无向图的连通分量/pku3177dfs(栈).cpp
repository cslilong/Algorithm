#include <iostream>
 using namespace std;

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

 int anc[N],mark[N],deep[N],stck[N],scc_num;

 int bridge[M][2],nbridge;

 int n,m,w;
 Node *e[N];
 Node *ce[N];
 int belong[N];
 int d[N];

 void DFS_2conn(Node *e[],int i,int father,int dth,int f[]){
     int j,k,tofather=0; Node *p;
     mark[i]=1; anc[i]=deep[i]=dth;
     stck[++stck[0]]=i;
     for(p=e[i];p!=NULL;p=p->next){
         j=p->j;
         if(mark[j]==1 && (j!=father||tofather)) anc[i]=MIN(anc[i],deep[j]);
         if(mark[j]==0){
             DFS_2conn(e,j,i,dth+1,f);
             anc[i]=MIN(anc[i],anc[j]);
             //if(anc[j]<=deep[i]) UniteSet(f,i,j); //i,j在同一个双连通分量 
             //if((father==-1&&sons>1)||(father!=-1&&anc[j]>=deep[i])) cut[i]=1; //i是割点 
             if(anc[j]>deep[i]) bridge[nbridge][0]=i,bridge[nbridge++][1]=j; //边(i,j)是桥
         }
         if(j==father) tofather=1;
     }
     if(anc[i]==deep[i]) {
         ++scc_num;
         do {
             belong[stck[stck[0]]]=scc_num;
             mark[stck[stck[0]]]=2;
         } while(stck[stck[0]--]!=i);
     }
 }

 /*
 无向图极大双连通分量
 参数:
     无向图邻接表e[],  返回双连通分量个数ncon
     belong[]返回节点i所在的双连通分量编号belong[i],[0,ncon-1] 
     可以处理重边和不连通的情况. 
 */
 int DoubleConnection(Node *e[],int n){
     int i,j,k,f[N],ncon=0;
     clr(mark); nbridge=0;
        stck[0]=0; scc_num=0;
     for(i=0;i<n;i++) if(mark[i]==0) DFS_2conn(e,i,-1,1,f);
     return scc_num;
 }


 int main()
 {
     int i,j,k;

     while(scanf("%d%d",&n,&w)!=EOF){
         memp=0; clr(e);
         for(k=0;k<w;k++){
             scanf("%d%d",&i,&j); i--; j--;
             addEdge(e,i,j);
             addEdge(e,j,i);
         }
         m=DoubleConnection(e,n);
         clr(d);
         for(k=0;k<nbridge;k++){
             i=bridge[k][0];
             j=bridge[k][1];
             d[belong[i]]++;
             d[belong[j]]++;
         }
         //cout<<" ### "<<endl;
         //for(i=1;i<=n;++i) cout<<" belong[ "<<i<<" ] = "<<belong[i]<<endl;
         int count=0;
         for(i=1;i<=m;i++) if(d[i]==1) count++;
         printf("%d\n",(count+1)/2);
     }
     
     return 0;
 }
 
/*

*/
