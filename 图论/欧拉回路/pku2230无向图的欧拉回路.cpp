/*
双向欧拉回路，有向图欧拉回路的特殊形式，故入度＝出度，所以只要连通就一定有经过所有顶点的欧拉回路。题目已经告诉了一定存在，故直接输出即可。
*/
#include<iostream>
using namespace std;
const int maxn=10010;
const int maxm=100100;

int head[maxn];
struct ad
{
	int v,vis;
	int next;
}adj[maxm];
int adjid;

void addedge(int x,int y)
{
	adjid++;
	adj[adjid].v=y;
	adj[adjid].vis=0;
	adj[adjid].next=head[x];
	head[x]=adjid;
}

/*void euler(int k)
{
	for(int i=head[k];i!=-1;i=adj[i].next)
	{
		if(adj[i].vis==0) {
			adj[i].vis=1;
			euler(adj[i].v);
		}
	}
	printf("%d\n",k);
}*/
void euler(int k)
{
	int j=-1;
	for(int i=head[k];i!=-1;i=adj[i].next)
	{
		if(adj[i].vis==0) {
			adj[i].vis=1;
			if(j==-1) adj[head[k]].next=adj[i].next;
			else adj[j].next = adj[i].next;
			euler(adj[i].v);
		} else j = i;
	}
	printf("%d\n",k);
}


int main()
{
	int n,m,i,x,y;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;++i) {  head[i]=-1; }
	adjid=0;
	for(i=0;i<m;++i) 
	{
		scanf("%d%d",&x,&y);
		addedge(x,y);
		addedge(y,x);
	}
	euler(1);
	system("pause");
	return 0;
}
