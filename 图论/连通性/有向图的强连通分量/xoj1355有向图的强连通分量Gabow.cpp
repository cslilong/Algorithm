#include <iostream>
#include<vector>
using namespace std;
const int MAXN = 10010;

int      n;
int      intm[MAXN]; //标记进入顶点时间
int      belg[MAXN]; //存储强连通分量,其中belg[i]表示顶点i属于第belg[i]个强连通分量
int      stk1[MAXN]; //辅助堆栈
int      stk2[MAXN]; //辅助堆栈
vector<int> adj[MAXN];//邻接表
int num[MAXN];
//深搜过程,该算法的主体都在这里
void Visit(int cur, int &sig, int &scc_num)
{
   int i;
   intm[cur] = ++sig;
   stk1[++stk1[0]] = cur;
   stk2[++stk2[0]] = cur;
   for ( i=0; i<adj[cur].size(); ++i )
   {
      if ( 0==intm[adj[cur][i]] )
      {
          Visit(adj[cur][i],sig,scc_num);
      }
      else if ( 0==belg[adj[cur][i]] )
      {
          while ( intm[stk2[stk2[0]]]>intm[adj[cur][i]] )
          {
             -- stk2[0];
          }
      }
   }
   if ( stk2[stk2[0]]==cur )
   {
      -- stk2[0]; ++ scc_num;
      do
      {
          belg[stk1[stk1[0]]] = scc_num;
      }
      while ( stk1[stk1[0]--]!=cur );
   }   
}
//Gabow算法,求解belg[1..n],且返回强连通分量个数,
int Gabow()
{
   int i, sig, scc_num;
   memset(belg+1,0,sizeof(int)*n);
   memset(intm+1,0,sizeof(int)*n);
   sig = 0; scc_num = 0; stk1[0] = 0; stk2[0] = 0; 
   for ( i=1; i<=n; ++i )
   {
      if ( 0==intm[i] )
      {
          Visit(i,sig,scc_num);
      }
   }
   for(i=1;i<=n;++i) num[i]=0;
   for(i=1;i<=n;++i) ++num[belg[i]];
    int	maxsum=0;
	for(i=1;i<=n;++i) if(num[i]>maxsum) maxsum=num[i];
	//printf("%d\n",maxsum);
	return maxsum;
   //return scc_num;
} 

int main()
{
	int m,i,x,y;
	while(scanf("%d",&n)!=EOF) {
		scanf("%d",&m);
		for(i=1;i<=n;++i) { adj[i].clear();  }
		while(m--) {
			scanf("%d%d",&x,&y);			
			adj[x].push_back(y);			
		}
		printf("%d\n",Gabow());
	}	
	return 0;
}
