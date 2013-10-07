/*
2-SAT问题:
http://acm.hdu.edu.cn/showproblem.php?pid=3062
Problem Description
有n对夫妻被邀请参加一个聚会，因为场地的问题，每对夫妻中只有1人可以列席。
在2n 个人中，某些人之间有着很大的矛盾（当然夫妻之间是没有矛盾的），
有矛盾的2个人是不会同时出现在聚会上的。有没有可能会有n 个人同时列席？ 

Input
n： 表示有n对夫妻被邀请 (n<= 1000)
m： 表示有m 对矛盾关系 ( m < (n - 1) * (n -1))

在接下来的m行中，每行会有4个数字，分别是 A1,A2,C1,C2 
A1,A2分别表示是夫妻的编号 
C1,C2 表示是妻子还是丈夫 ，0表示妻子 ，1是丈夫
夫妻编号从 0 到 n -1  

Output
如果存在一种情况 则输出YES 
否则输出 NO  

Sample Input
2 
1
0 1 1 1 
 

Sample Output
YES
*/
#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

const int N = 2010;     //最大人数 

vector<int> g[N];     //原图边连接情况 
int n, m, h[N], id[N];     //id[]表示原图中每个点都属于哪个强连通分量 
int cnt, scnt, dfn[N], low[N], cur[N];
int stack[N], top, est[N], etop;
vector<int> tree[N];     //有向无环图的边连接情况(新图) 
vector<int> contain[N];     //新图中每个点都包含原图中的哪些点 

/*
对于每对adulterous pairs(a,b)，则有(!a->b),(!b->a) 也就是a or b =1
*/

#define opp(x) ((x)^1)

bool build() 
{
     if (scanf("%d%d",&n,&m)==EOF)  return false;
     if(n==0) return false;
     n = n+n;
     int i,a,b,ax1,ax2,ax3,ax4;
     //char ch[10];
     //int s[10];
     for (i=0;i<n;i++) g[i].clear();
     //for(i=0;i<n;i+=2) { g[opp(i)].push_back(i); g[i].push_back(opp(i)); }
     for(i=1;i<=m;i++)
    {
      //cin>>a>>ch[0]>>b>>ch[1];
      scanf("%d%d%d%d",&ax1,&ax2,&ax3,&ax4);
      ax1; ax2;
      if(ax3==0) a=ax1+ax1; else a=ax1+ax1+1;
      if(ax4==0) b=ax2+ax2; else b=ax2+ax2+1;
      g[opp(a)].push_back(b);
      g[opp(b)].push_back(a);      
    }
    
    return true;
}

void dfs(int src) 
{
     etop = top = 0;
     stack[top++] = src;
     while(top != 0) 
     {
         int     c = stack[top-1];
         if(dfn[c] == -1) 
         { 
             h[c] = dfn[c] = low[c] = cnt++; 
             est[etop++] = c; 
         }
         for(; cur[c] >= 0; cur[c]--) 
         {
             int no = g[c][cur[c]];
             if(dfn[no] == -1) 
             { 
                 stack[top++] = no; 
                 break; 
             }
            // h[c] <?= low[no];
            h[c] = (h[c]<low[no])?h[c]:low[no];
         }
         if(cur[c] >= 0) 
             continue;
         top--; 
         int k;
         if(h[c] != low[c]) 
         { 
             low[c] = h[c]; 
             continue; 
         }
         do 
         {
             k = est[--etop];
             id[k] = scnt; low[k] = N;
         } while(k != c);
         scnt++;
     }
}

/*
函数scR和dfs是求原图的强连通分量(代码由wywcgs原创) 
*/
void scR() 
{
     memset(dfn, -1, sizeof(dfn));
     cnt = scnt = 0;
     for(int i = 0; i < n; i++)
     { 
         cur[i] = g[i].size()-1;
         contain[i].clear();
     }
     for(int i = 0; i < n; i++)
         if(dfn[i] == -1) 
             dfs(i);
    
     /*
     统计每个强连通分量都包含哪些点，为后面求可行方案做准备。如果不求可行解，可注释掉。 
     */
     for (int i=0;i<n;i++)
     {
         contain[id[i]].push_back(i);
     }
}

/*
函数judge判断是否能找出一个可行方案出来 
*/
bool judge()
{
     for (int i=0;i<n;i+=2)
         if (id[i]==id[i+1])
             return false;
     return true;
}

/*
函数buildGraph把每个强连通分量作为一个点，重新构图。(缩点，得到的是一个有向无环图) 
用的是链接表的形式，可能有很多重边。可以加一些预处理消除重边。 
*/
void buildGraph()
{
     for (int i=0;i<scnt;i++)
         tree[i].clear();
     for (int i=0;i<n;i++)
         for (int j=0;j<g[i].size();j++)
         {
             int a=id[i];
             int b=id[g[i][j]];
             if (a!=b)
             {
                 tree[b].push_back(a);
             }
         }
}

void tsDfs(int k)
{
     dfn[k]=cnt++;
     for (int i=0;i<tree[k].size();i++)
     {
         int w=tree[k][i];
         if (dfn[w]==-1)
         {
             tsDfs(w);
         } 
     }  
     low[scnt++]=k;             
}

/*
函数topologicalSort和tsDfs是对新图进行拓扑排序，排序后的结果存在low数组中 
*/
void topologicalSort()
{
     for (int i=0;i<scnt;i++)
     {
         dfn[i]=-1;
         low[i]=-1;
     }
     int nn=scnt;
     cnt=scnt=0;
     for (int i=0;i<nn;i++)
     {
         if (dfn[i]==-1)
             tsDfs(i);
     }
}

void colorDfs(int k)
{
     dfn[k]=2;
     for (int i=0;i<tree[k].size();i++)
     {
         int w=tree[k][i];
         if (dfn[w]==-1)
         {
             colorDfs(w);
         } 
     }          
}

/*
函数color和colorDfs是对新图进行着色，新图中着色为1的点组成一组可行解 
*/ 
void color()
{
     for (int i=0;i<scnt;i++)
         dfn[i]=-1; 
     for (int i=scnt-1;i>=0;i--)
         if (dfn[low[i]]==-1) 
         {
             /*
             新图中low[i]着色为1后，它的矛盾点应标记为2 
             */
             int a=contain[low[i]][0];     //在原图中找一点属于强连通分量low[i]的点a，点a所属组的另一点b所属的强连通分量id[b]一定是low[i]矛盾点。 
             int b;
             if (a%2==0)
                 b=a+1;
             else
                 b=a-1;
             dfn[low[i]]=1;
             if (dfn[id[b]]==-1)
                 colorDfs(id[b]);     //由于依赖关系，有id[b]能达的点都是low[i]的矛盾点 
         }
}

/*
函数tagAnswer由新图对原图的点进行标记，得到原图的可行解 
*/
void tagAnswer()
{
     for (int i=0;i<n;i++)
         low[i]=-1;
     for (int i=0;i<scnt;i++)
         if (dfn[i]==1)//i为新图中可行解包含的点，那么原图中强连通分量属于i的点都是原图中可行解的点 
         {
             for (int j=0;j<contain[i].size();j++)
                 low[contain[i][j]]=1;
         }
}

/*
函数printAnswer打印原图的可行解 
*/ 
void printAnswer()
{
     for (int i=2;i<n;i++)
         if (low[i]==1)
         {
             if(i>3)printf(" ");
			 printf("%d",i>>1);
             if(i&1) printf("h"); else printf("w");			
             //if (j!=n>>1-2)  printf(" ");
             //else  printf("\n");
             
		}
		printf("\n");
	//	cout<<low[0]<<" # "<<endl;
}

/*
函数getOneAnswer得到原图的一组可行解 
*/ 
void getOneAnswer()
{
     buildGraph();
     topologicalSort();
     color();
     tagAnswer();
     printAnswer();
}

/*
函数solve可根据实际要求，进行更改输出 
*/ 
void solve()
{
     scR();
     if (judge())
     {
         printf("YES\n");
        // getOneAnswer();
     }
     else  printf("NO\n");
}

int main()
{
     while (build())
     {
         solve();
     }
     return 0;
} 
