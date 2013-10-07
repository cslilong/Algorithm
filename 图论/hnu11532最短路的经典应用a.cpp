#include<iostream>
#include<vector>
#include<queue>
using namespace std;

const int maxn=5010;
const __int64 inf=1000000000;

struct node 
{
	int v;
	int c;
};
vector<node> ad[maxn];

__int64 dist[maxn],p[4][maxn];
bool mark[maxn];
int n;

void spfa(int kk,int start)
{
	int i,u,v,cost,len;
	node tmp;
	for(i=1;i<=n;++i) mark[i]=false;
	for(i=1;i<=n;++i) dist[i]=inf;
	dist[start]=0;
	queue<int> q_q;
	q_q.push(start);
	mark[start]=true;
	while(!q_q.empty())
	{
		u = q_q.front();
		q_q.pop();
		mark[u]=false;
		//u = p[tmp].v;
		len = ad[u].size();
		for(i=0;i<len;++i)
		{
			tmp = ad[u][i];
			v = tmp.v;
			cost =tmp.c;
			//cost = ad[u][i].cost;
			if(dist[v] > dist[u]+cost) 
			{
				dist[v]=dist[u]+cost;
				if(!mark[v]) {
					mark[v]=true;
					q_q.push(v);
				}
			}
		}
	}
	for(i=1;i<=n;++i) p[kk][i]=dist[i];
}

int main()
{
	int m,i,x,y,z,c,a,b,cases=0;
	node tmp;
	__int64 minsum;
	while(scanf("%d%d",&n,&m)!=EOF)
	{
		scanf("%d%d%d",&c,&a,&b);
		for(i=1;i<=n;++i) ad[i].clear();
		for(i=1;i<=m;++i) 
		{
			scanf("%d%d%d",&x,&y,&z);
			tmp.v = y;
			tmp.c = z;
			ad[x].push_back(tmp);
			tmp.v = x;
			tmp.c = z;
			ad[y].push_back(tmp);
		}
		spfa(1,c);
		spfa(2,a);
		spfa(3,b);
		minsum = 3*inf;
		for(i=1;i<=n;++i) 
		{
			if(p[1][i]==inf || p[2][i]==inf ||p[3][i]==inf) continue;
			if(p[1][i]+ p[2][i]+ p[3][i]<minsum) minsum = p[1][i]+ p[2][i]+ p[3][i];
		}
		printf("Scenario #%d\n",++cases);
		if(minsum<3*inf) printf("%I64d\n\n",minsum);
		else printf("Can not reach!\n\n");
	}
	return 0;
}
