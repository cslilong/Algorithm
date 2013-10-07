/*pku 3207 3207 -- Ikki's Story IV - Panda's Trick
题目原来的叙述不太好理解, 换个说法. 一个圆盘的边沿上有n个点, 下标从0开始, 有m条
线连接2m个互不相同的点, 线可以从圆盘任意一面过, 要求任意两条线不能相交. 给出m条
线(正反面随意), 问是否存在一种给每条线的正反面的分配方法, 使满足要求.
 

这题是2-SAT(2判定性问题(http://en.wikipedia.org/wiki/2-satisfiability))的基础题,
关键在于建图.
 

令第i条线(i从0开始)在正面为第2i个顶点, 在反面为第2i+1个顶点. 若第i条线和第j条线
构成一个四边形的两条对角线, 则在2i和2j+1之间连一条双向边, 2i+1和2j之间连一条双向
边. 这样建图后求强连通分量, 看点2i和点2i+1是否在同一个强连通分量中, 只要有, 就说
明不满足要求, 如果没有则满足.
 

这里对建图的方式做一点解释. 首先, 我们知道若第i条线和第j条线构成一个四边形的两条
对角线, 则2i和2j不相容, 又2i和2i+1中必须出现一个, 且2j和2j+1中必须出现一个, 所以
可以说2i+1和2j+1中至少出现一个, 这就是2-SAT的合取式中的"或"的来路. 换句话说, 从
2i到2j+1连一条有向边表示如果选择了2i就必须选择2j+1, 从2j到2i+1连一条有向边表示如
果选择了2j就必须选择2i+1, 同理对于2i+1和2j+1的不相容也可以连两条有向边, 所以最后
跟上面的组成了两条双向边.
*/
#include<iostream>
#include<vector>
using namespace std;
const int MAXN    = 1010;
const char NOTVIS = 0x00;   //顶点没有访问过的状态
const char VIS     = 0x01;   //顶点访问过,但没有删除的状态
const char OVER    = 0x02;   //顶点删除的状态

vector<int> adj[MAXN]; //正向邻接表
int num[MAXN];
int n,m;

char     flag[MAXN];         //用于标记顶点状态,状态有NOTVIS,VIS,OVER
int      belg[MAXN];         //存储强连通分量,其中belg[i]表示顶点i属于第belg[i]个强连通分量
int      stck[MAXN];         //堆栈,辅助作用
int      mlik[MAXN];         //很关键,与其邻接但未删除顶点地最小访问时间
int      indx[MAXN];         //顶点访问时间
struct{int x,y;}dr[MAXN];   //记录door上的两把锁 
#define opp(x) ((x)^1)
//opp[i]表示与i冲突的元素。即同组的钥匙。

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
         if ( mlik[cur]>indx[adj[cur][i]] ) 
		  //该部分的indx应该是mlik,但是根据算法的属性,使用indx也可以,且时间更少
		  // if(mlik[cur]>mlik[adj[cur][i]])
          {
             mlik[cur] = indx[adj[cur][i]]; 
             //mlik[cur] = mlik[adj[cur][i]]; 
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
   memset(flag,NOTVIS,sizeof(char)*n);
   sig = 0; scc_num = 0; stck[0] = 0;
   for ( i=0; i<n; ++i )
   {
      if ( NOTVIS==flag[i] )
      {
          Visit(i,sig,scc_num);
      }
   }
   return scc_num;
}

bool judge()
{
	for(int i=0;i<n;++i) if(belg[i]==belg[opp(i)]) return false;
	return true;
}



int main()
{
	int i,j;
	while(scanf("%d%d",&m,&n)!=EOF)
    {
      for(i=0;i<n;++i) scanf("%d%d",&dr[i].x,&dr[i].y);
      n=n<<1;
      for(i=0;i<n;++i) adj[i].clear();
      n=n>>1;
      for(i=0;i<n;++i) {
		for(j=i+1;j<n;++j) {
			if (   (dr[i].x>dr[j].x&&dr[i].y>dr[j].y&&dr[j].y>dr[i].x)
			   ||(dr[j].y>dr[i].y&&dr[j].x>dr[i].y&&dr[i].y>dr[j].x)   )
			{
				adj[i+i].push_back(opp(j+j));
				adj[opp(j+j)].push_back(i+i);
				adj[j+j].push_back(opp(i+i));
				adj[opp(i+i)].push_back(j+j);
			}
		}	
	  }
	  n=n<<1;
	  Tarjan();
	  if(judge()) printf("panda is telling the truth...\n");
	  else printf("the evil panda is lying again\n");
    }
    return 0;
}
