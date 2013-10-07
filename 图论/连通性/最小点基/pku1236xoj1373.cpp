/*
题目大意：

N个高校之间有一些单向的网络链接（N<100），当发布一个软件时，学校i收到软件时，
它可以将软件发送给所有它链接到的学校。现在要求发布一款软件，最少需要发给多少个学校，
使得所有学校都可以收到软件（问题A）。最少需要添加多少条单向网络链接，
可以使得将软件任意发给一个学校，使得所有学校都可以收到（问题B）。

分析：
我们先来讨论问题A。这个问题在吴文虎的OI图论书上有介绍过，叫做有向图的最小点基。
首先，求出有向图的极大强连通分量，在同一个强连通分量里的学校任意一个收到软件，
整个强连通分量里的学校都可以收到。将每个强连通分量缩成一个点，构成一个新的有向无环图。
当强连通分量i收到软件，那么i可达的强连通分量都可以收到软件。
我们称入度为0的强连通分量为最高强连通分量。显然，每个最高强连通分量都必须单独发送一次软件，
而其他强连通分量都可以通过最高强连通分量到达。所以，最高强连通分量的个数也就是问题A的解。
至于问题B，我猜测是MAX(入度为0的点的个数,出度为0的点的个数)，没想到居然对了，也没仔细证明。
注意的是，当原图只有一个强连通分量是，问题B的答案是0。
*/

#include<iostream>
#include<vector>
using namespace std;
const int MAXN    = 10010;
const char NOTVIS = 0x00;   //顶点没有访问过的状态
const char VIS     = 0x01;   //顶点访问过,但没有删除的状态
const char OVER    = 0x02;   //顶点删除的状态

vector<int> adj[MAXN]; //正向邻接表
int num[MAXN];
int n;

char     flag[MAXN];         //用于标记顶点状态,状态有NOTVIS,VIS,OVER
int      belg[MAXN];         //存储强连通分量,其中belg[i]表示顶点i属于第belg[i]个强连通分量
int      stck[MAXN];         //堆栈,辅助作用
int      mlik[MAXN];         //很关键,与其邻接但未删除顶点地最小访问时间
int      indx[MAXN];         //顶点访问时间
int in_num[MAXN],out_num[MAXN];

//深搜过程,该算法的主体都在这里
void Visit(int cur, int &sig, int &scc_num)
{
   int i;
   stck[++stck[0]] = cur; flag[cur] = VIS;
   mlik[cur] = indx[cur] = ++sig;
   for ( i=0; i<adj[cur].size(); ++i )
   {
      if ( NOTVIS==flag[adj[cur][i]] )
      {
          Visit(adj[cur][i],sig,scc_num);
          if ( mlik[cur]>mlik[adj[cur][i]] )
          {
             mlik[cur] = mlik[adj[cur][i]];
          }
      }
      else if ( VIS==flag[adj[cur][i]] )
      {
          if ( mlik[cur]>indx[adj[cur][i]] ) //该部分的indx应该是mlik,但是根据算法的属性,使用indx也可以,且时间更少
          {
             mlik[cur] = indx[adj[cur][i]]; 
          }
      }
   }
   if ( mlik[cur]==indx[cur] )
   {
      ++ scc_num;
      do
      {
          belg[stck[stck[0]]] = scc_num;
          flag[stck[stck[0]]] = OVER;
      }
      while ( stck[stck[0]--]!=cur );    
   }
}
//Tarjan算法,求解belg[1..n],且返回强连通分量个数,
int Tarjan()
{
   int i,j,k, sig, scc_num;
   memset(flag+1,NOTVIS,sizeof(char)*n);
   sig = 0; scc_num = 0; stck[0] = 0;
   for ( i=1; i<=n; ++i )
   {
      if ( NOTVIS==flag[i] )
      {
          Visit(i,sig,scc_num);
      }
   }
   for(i=1;i<=n;++i){  in_num[i]=0; out_num[i]=0; }
   //for(i=1;i<=n;++i) ++num[belg[i]];
    //int	maxsum=0;
//	for(i=1;i<=n;++i) if(num[i]>maxsum) maxsum=num[i];
	//printf("%d\n",maxsum);

   for(i=1;i<=n;++i) {
	   int len = adj[i].size();
	   for(k=0;k<len;++k) {
		   j=adj[i][k];
		   if(belg[i]!=belg[j]) {
			   ++in_num[belg[j]];
			   ++out_num[belg[i]];
		   }
	   }
   }
   if(scc_num==1) {
	   printf("1\n0\n");
   } else {
   int in_sum=0;
   int out_sum=0;
   for(i=1;i<=scc_num;++i){
	   if(in_num[i]==0) in_sum++;
	   if(out_num[i]==0) out_sum++;
   }
   if(in_sum>out_sum) out_sum=in_sum;
   printf("%d\n%d\n",in_sum,out_sum);
   }
   return scc_num;
} 


int main()
{
	int m,i,x,y;
	while(scanf("%d",&n)!=EOF) {		
		for(i=1;i<=n;++i) { adj[i].clear();  }
		for(i=1;i<=n;++i) {
		while(scanf("%d",&m)==1) {
			if(m==0) break;		
			adj[i].push_back(m);			
		}
		}
		Tarjan();
	}	
	return 0;
}