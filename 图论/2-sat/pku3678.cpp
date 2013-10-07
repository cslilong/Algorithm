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

const int N = 2100;     //最大人数 

vector<int> g[N];     //原图边连接情况 
int n, m, h[N], id[N];     //id[]表示原图中每个点都属于哪个强连通分量 
int cnt, scnt, dfn[N], low[N], cur[N];
int stack[N], top, est[N], etop;
vector<int> tree[N];     //有向无环图的边连接情况(新图) 
vector<int> contain[N];     //新图中每个点都包含原图中的哪些点 


/*
函数build是对原图初始化(根据实际输入情况做相应的更改) 
因为a，b必选，!a -> a这样会导致a一定被选，为什么？
想想构造一组解的时候，经过求强连通分量和缩点后，对新图进行拓扑排序，然后按拓扑倒序对点进行染色。
现在明白了吧！因为存在!a->a，所以呢染色的顺序一定是a ,!a，
这时如果a没被染色，那么a就一定被染红色，则！a一定被染蓝色（看赵爽的论文）。
如果a与!a之间不存在边的关系呢，则表示a,!a任选一个，因为其中一个被染红色，则另外一个一定被染蓝色，
具体你的程序选择哪个，就看你的拓扑部分是怎么写的（点的访问顺序）。

a and b = 1    转换为 ：(!a -> a),(!b->b)，
a and b = 0 转换为：(a->!b),(b->!a)
a or b = 1    转换为：(!a->b),(!b->a)
a or b = 0   转换为：(a->!a),(b->!b)
a xor b = 1   转换为：(a->!b),(!b->a),(b->!a),(!a->b)
a xor b = 0   转换为：(a->b),(b->a),(!a->!b),(!b->!a)
*/
bool build() 
{
     if (scanf("%d %d",&n,&m)==EOF)  return false;
     n = n+n;
     int cc;
     char ss[10];
     for (int i=0;i<n;i++)
         g[i].clear();
     for (int i=0;i<m;i++)
     {
         int a,b,c,d;
         scanf("%d%d%d%s",&a,&b,&cc,ss);     //a，b是互斥的。a所在组的另一点为c，b所在组的另一点为d。原图中插入边a->d和边b->c。 
         a = a+a;
         b = b+b;
		 if (a%2==0) c=a+1;  else  c=a-1;
         if (b%2==0) d=b+1;  else  d=b-1;
         if(ss[0]=='A') {
		 	if(cc==1) { g[c].push_back(a);  g[d].push_back(b); }
		 	else { g[a].push_back(d);  g[b].push_back(c); }
		 } else if(ss[0]=='O') {
			if(cc==1) { g[c].push_back(b);  g[d].push_back(a); }
		 	else { g[a].push_back(c);  g[b].push_back(d); }
		 } else {
		 	if(cc==1) { g[a].push_back(d);  g[d].push_back(a); g[c].push_back(b);  g[b].push_back(c); }
		 	else { g[a].push_back(b);  g[b].push_back(a); g[c].push_back(d);  g[d].push_back(c); }
		 }         
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
     for (int i=0,j=0;i<n;i++,j++)
         if (low[i]==1)
         {
             printf("%d",i);
             if (j!=n/2-1)
                 printf(" ");
             else
                 printf("\n");
         }
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
} 
