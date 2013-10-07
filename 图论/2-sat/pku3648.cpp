/*
2-SAT问题:
有n个人，0，1是一组的；2，3是一组的；....；n-2，n-1是一组的。有m个限制条件，每个限制条件由a，b组成，表示a和b是不能相处的。
现在要从每组中选一个人出来构成一个团体，并且任意2个人都是能相处的。 
*/
#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

const int N = 210;     //最大人数 

vector<int> g[N];     //原图边连接情况 
int n, m, h[N], id[N];     //id[]表示原图中每个点都属于哪个强连通分量 
int cnt, scnt, dfn[N], low[N], cur[N];
int stack[N], top, est[N], etop;
vector<int> tree[N];     //有向无环图的边连接情况(新图) 
vector<int> contain[N];     //新图中每个点都包含原图中的哪些点 


/*
函数build是对原图初始化(根据实际输入情况做相应的更改) 
有n男n女, 其中一对是新人, 其他n-1对是夫妻, 现在有一张长桌两边坐人(题目没有要求两边人一样多), 
要求新郎新娘不在同一边, 每对夫妻不在同一边. 
另外, n对人中有m对有奸情(有可能是同性恋, 有可能是新郎或新娘), 要求有奸情的两个人不能都坐在新娘对面, 
若能安排座位, 则输出跟新娘在一边的人, 否则输出"bad luck".
solution: 2-SAT
这题首先要看清题目, 并不是说有奸情的两个人一定不能坐在同一边("it is bad luck for the bride to see both members of such a pair"),
 新郎新娘不在同一边("The bride and groom sit at one end, opposite each other"), 
 又因为每对夫妻不在同一边, 所以两边人数相等. 

然后构图, 设座位分左边和右边, 顶点2i表示i号男人坐左边, 2i+1表示i号男人坐右边, 
顶点2i+2n表示i号女人坐左边, 2i+1+2n表示i号女人坐右边.
 每对都不在同一边好办, 每对连4条有向边即可, 但是奸情的要求怎么表示呢? 
 通奸的两个人可以在新娘同一边, 也可以其中一个在新娘对面, 无法用X∪Y来表示.  

不妨设新娘在左边, 那么通奸的两人其中一个在右边的话, 另一个必然在左边.
 嗯, 这样一来通奸的要求搞定了, 那么如何把新娘一定在左边表示在有向图中呢? 

那么换个说法, 因为新郎一定在右边, 所以如果新娘在右边, 那么新郎也一定在右边, 
并且如果新郎在左边, 新娘也一定在左边, 又已经有要求新郎新娘不在同一边, 
所以只要再加上上述两条有向边即可保证新娘一定在左边.
因为有一对夫妻不能同时出现在同一边，所以设a为表示选择男，!a表示选择女的（新娘那边选择）
建图过程：
1、新娘必须选择，则有(a->!a)
2、对于每对adulterous pairs(a,b)，则有(!a->b),(!b->a) 也就是a or b =1
*/

#define opp(x) ((x)^1)

bool build() 
{
     if (scanf("%d%d",&n,&m)==EOF)  return false;
     if(n==0) return false;
     n = n+n;
     int i,a,b;
     char ch[10];
     int s[10];
     for (i=0;i<n;i++) g[i].clear();
     for(i=1;i<=m;i++)
    {
      cin>>a>>ch[0]>>b>>ch[1];
      if(ch[0]=='w')a=a+a;
      else a=a+a+1;
      if(ch[1]=='w')b=b+b;
      else b=b+b+1;
      g[opp(a)].push_back(b);
      g[opp(b)].push_back(a);      
    }
    g[1].push_back(0);
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
        // printf("YES\n");
         getOneAnswer();
     }
     else  printf("bad luck\n");
}

int main()
{
     while (build())
     {
         solve();
     }
     return 0;
} 
