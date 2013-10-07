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
   int i, sig, scc_num;
   memset(flag+1,NOTVIS,sizeof(char)*n);
   sig = 0; scc_num = 0; stck[0] = 0;
   for ( i=1; i<=n; ++i )
   {
      if ( NOTVIS==flag[i] )
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
		printf("%d\n",Tarjan());
	}	
	return 0;
}
