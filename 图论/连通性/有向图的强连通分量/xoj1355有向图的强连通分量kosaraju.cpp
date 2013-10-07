/*
�������
Accepted : 4 	  	Submit : 23
Time Limit : 4000 MS 	  	Memory Limit : 65536 KB 
Description
С����һ�������Ĺ�˾�ϰ࣬�����������죬�����뾡���ܶ�������μ�����������ᡣΪ�����������еø�����죬��ϣ�����μ������˶�������ʶ��������֪����˾����Ա�Ĺ�ϵ��ϣ�����ܰ��������뵽�����ܶ�������μӡ���ע�⣺���A��ʶB��������B��ʶA�����A��ʶB��B��ʶC������˵A��ʶC�������д����ԣ���

Input
ÿ������������һ��������n��1<=n<=10000������ʾ��˾��Ա����Ŀ��������һ���и�������m����ʾ��m����Ա��ϵ�������m�У�ÿ����������a��b����ʾa��ʶb��

Output
������μ��������������
 
Sample Input
3
3
1 2
2 3
3 1 

Sample Output
3

Source
2009��6������,cq1914
*/

#include<iostream>
#include<vector>
using namespace std;
#define MAXN 10010

vector<int> adj[MAXN]; //�����ڽӱ�
vector<int> radj[MAXN]; //�����ڽӱ�
vector<int> ord; //�������˳��
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