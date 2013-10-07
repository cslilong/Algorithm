#include <iostream>
#include <queue>
using namespace std;
const long MAXN=105;
const long lmax=0x7FFFFFFF;

struct Edge
{
    long v;
    long next;
    long cost;
}e[MAXN];
__int64 Dis[MAXN],min[105];
long p[MAXN];
long luguan[105];
bool vist[MAXN];
bool b[MAXN];
long a[105][105];
queue<long> q;
long m,n,h;

void init()
{
    long i,x;
    long eid=0;
	long from,to,cost;
    memset(p,-1,sizeof(p));
    memset(b,0,sizeof(b));
	scanf("%d",&h);
	luguan[0] = 1;
	for ( i = 1 ; i <= h; i++ )
	{
		scanf("%d",&x);
		b[x] = true;
		luguan[i] = x;
	}
	luguan[h+1] = n;
    scanf("%d",&m);
    for ( i = 0; i < m; ++i )
    {
        scanf("%d%d%d",&from,&to,&cost);
        e[eid].next=p[from];
        e[eid].v=to;
        e[eid].cost=cost;
        p[from]=eid++;        
        e[eid].next=p[to];
        e[eid].v=from;
        e[eid].cost=cost;
        p[to]=eid++;
    }
}
void dijkstra()
{
	int i,j,k;
	bool v[105];
	memset(v,0,sizeof(v));
	for ( i = 0; i <= h+1; i++ )
		min[i] = lmax;
	min[0] = 0;
	for ( j = 0; j <= h+1; j++ )
	{
		k = -1;
		for ( i = 0; i <= h+1; i++ )
			if ( !v[i] &&(k==-1|| min[i]<min[k]) )
				k = i;
		if ( k==-1 ) break;
		v[k] = true;
		for ( i = 0; i <= h+1; i++ )
			if ( !v[i] && min[k]+a[k][i]<min[i] )
				min[i] = min[k]+a[k][i];
	}
	if ( min[h+1] >= lmax ) printf("-1\n");
	else printf("%I64d\n",min[h+1]-1);
}

void SPFA(long i)
{
	long t,j,w;
	memset(vist,0,sizeof(vist));
	for ( j = 0; j <= n; j++ )
		Dis[j] = lmax;
	while (!q.empty()) q.pop();
	Dis[luguan[i]] = 0;
    vist[luguan[i]] = true;
    q.push(luguan[i]);
    while (!q.empty())
    {
        t = q.front();
        q.pop();
        vist[t] = false;
        for ( j = p[t]; j!=-1; j = e[j].next )
        {
            w = e[j].cost;
            if ( w+Dis[t]<Dis[e[j].v]  )
            {
				Dis[e[j].v] = w+Dis[t];
                if (!vist[e[j].v])
                {
                     vist[e[j].v] = true;
                     q.push(e[j].v);
                }
            }
        }
    }
}

int main()
{
	int i,j;
    while (scanf("%d",&n)==1 && n!=0)
    {
		init();
		for ( i = 0; i <=h+1; i++ )
			for ( j = 0; j <= h+1; j++ )
				if ( i!=j ) a[i][j] = lmax;
				else a[i][j] = 0;
		for ( i = 0; i <= h; i++ )
		{
			SPFA(i);
			for ( j = 1; j <= h+1; j++ )
				if ( Dis[luguan[j]] <= 600 && i!=j )
					a[i][j] = a[j][i] = 1;
		}
		dijkstra();
    }
}