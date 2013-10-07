/*
生日舞会
Accepted : 4 	  	Submit : 23
Time Limit : 4000 MS 	  	Memory Limit : 65536 KB 
Description
小红在一个著名的公司上班，在她生日这天，想邀请尽可能多的人来参加她的生日舞会。为了能让舞会进行得更加愉快，她希望来参加舞会的人都互相认识。现在她知道公司中人员的关系，希望你能帮助她邀请到尽可能多的人来参加。（注意：如果A认识B，不代表B认识A；如果A认识B，B认识C，可以说A认识C，即具有传递性）。

Input
每个例子先输入一个正整数n（1<=n<=10000），表示公司人员的数目。接下来一个有个正整数m，表示有m组人员关系。下面的m行，每行有两个数a、b，表示a认识b。

Output
输出来参加舞会的最大人数。
 
Sample Input
3
3
1 2
2 3
3 1 

Sample Output
3

Source
2009年6月月赛,cq1914
*/

#include<iostream>
#include<vector>
using namespace std;
#define MAXN 10010

vector<int> adj[MAXN]; //正向邻接表
vector<int> radj[MAXN]; //反向邻接表
vector<int> ord; //后序访问顺序
bool vis[MAXN];
int map[MAXN];
int num[MAXN];
int n,cnt;

void dfs1(int v)
{
    int i,u;
	int t=adj[v].size();
    for(i=0 , vis[v]=true; i<t; ++i) if (!vis[u=adj[v][i]]) dfs1(u);
    ord.push_back(v);
}

void dfs2 ( int v )
{
    int i,u;
	int t=radj[v].size();
    for(i=0,map[v]=cnt,vis[v]=true; i<t; ++i)  if ( !vis[u=radj[v][i]] )  dfs2(u);
}

int kosaraju()
{
    int i,pre,maxsum;
    memset(vis,false,sizeof(vis));
    ord.clear();
    for (i=0 ; i<n; i++ ) if ( !vis[i] )  dfs1(i);
    memset(vis,false,sizeof(vis));
	pre=ord.size()-1; maxsum=0;
    for (cnt=0,i=ord.size()-1 ; i>=0; --i) {
        if ( !vis[ord[i]] )
        {
            dfs2(ord[i]);
			cnt++;
        }
	}
	for(i=0;i<n;++i) num[i]=0;
	for(i=0;i<n;++i) ++num[map[i]];
	maxsum=0;
	for(i=0;i<n;++i) if(num[i]>maxsum) maxsum=num[i];
	//printf("%d\n",maxsum);
	return maxsum;
}

int main()
{
	int m,i,x,y;
	while(scanf("%d",&n)!=EOF) {
		scanf("%d",&m);
		for(i=0;i<n;i++) { adj[i].clear(); radj[i].clear(); }
		while(m--) {
			scanf("%d%d",&x,&y);
			--x; --y;
			adj[x].push_back(y);
			radj[y].push_back(x);
		}
		printf("%d\n",kosaraju());
	}	
	return 0;
}

/*
3
3
1 2
3 2
2 3

5
7
1 2
1 3
1 4
1 5
2 3
3 4
4 5

5
5
1 2
2 3
3 4
4 5
5 1


*/