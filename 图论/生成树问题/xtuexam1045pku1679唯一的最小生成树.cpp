#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
using namespace std;

const int maxn=110;
const int inf = 0x7FFFFFFF;

struct node
{
	int u,v,cost,next;
}adj[maxn*maxn*10];
int head[maxn],dist[maxn],vis[maxn];
int tot,n,mincost;
int qnum,que[maxn],least[maxn];

void init() {
	tot=0;
	memset(head,-1,sizeof(head));	
}

void add(int from,int to,int cost)
{	
	adj[tot].next=head[from];
	adj[tot].u = from;
	adj[tot].v = to;
	adj[tot].cost = cost;
	head[from] = tot;
	++tot;
}

bool prim(int root) {
	bool flag;
	int s,i,k,minsum,mini;
	for(i=1;i<=n;++i) { 
		dist[i]=inf; 
		vis[i]=0; 
	//	pre[i]=root; 
		least[i]=-1;
	}
	dist[root]=0; vis[root]=1;
	for(i=head[root];i!=-1;i=adj[i].next) {
		if(adj[i].cost < dist[adj[i].v] ) dist[adj[i].v]=adj[i].cost;
	}
	mincost = 0; flag=false;
	for(k=1;k<n;++k)
	{
		minsum = inf; 
		for(i=1;i<=n;++i) {
			if(!vis[i] && dist[i]<minsum) {
				minsum=dist[i];
				mini=i;
				qnum = 1;
			}
			if(!vis[i] && dist[i]==minsum) {
				que[qnum++]=i;
			}
		}
		vis[mini]=1;
		mincost += minsum;
		//条件一 
		s = 0;
		for(i=head[mini];i!=-1;i=adj[i].next){
			if(vis[adj[i].v] && adj[i].cost==minsum) s++;
		}		
		if(s>1) { return true; }		
				 
		for(i=head[mini];i!=-1;i=adj[i].next) {
			if(!vis[adj[i].v] && dist[adj[i].v]>adj[i].cost) {
				dist[adj[i].v]=adj[i].cost;
			//	pre[adj[i].v] = mini; 
			}
		}
		
		//条件二
		if(least[mini]!=-1&&least[mini]!=minsum)  {
            //flag=true;      break;
            return true;
        }
		if(qnum!=1) {
			for(i=1;i<qnum;++i) {
				if(dist[que[i]]!=minsum) { /*flag=true; break;*/ return true; }
				else if(least[que[i]]!=-1 && least[que[i]]!=minsum ) { return true; }
				else least[que[i]]=minsum;
			}			
		} 
	}
	return false;
}

int main()
{
	int ncase,m;
	int x,y,z;
	
  	//freopen("in.txt","r",stdin);
 	//freopen("out.txt","w",stdout);
	
	scanf("%d",&ncase);
	while(ncase--)
	{
		init();
		scanf("%d%d",&n,&m);
		while(m--)
		{
			scanf("%d%d%d",&x,&y,&z);
			if(x==y) continue;
			add(x,y,z);
			add(y,x,z);
		}	
		
		if(prim(1)) printf("Not Unique\n");
		else printf("%d\n",mincost);
	}
	return 0;
}
