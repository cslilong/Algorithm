#include <iostream>

using namespace std;
const __int64 MAXN=20005;
const __int64 lmax=1000000000;
struct Edge
{
    int v;
    int next;
    int cost;
}e[MAXN];
int p[MAXN],q[MAXN];
__int64 Dis[MAXN][4],sum;
bool vist[MAXN];
int m,n,s[3];

void init()
{
    int i;
    int eid = 0;
    int from,to,cost;
    memset(p,-1,sizeof(p));
    scanf("%ld%ld%ld",&s[0],&s[1],&s[2]);
    for ( i = 0; i < m; ++i )
    {
        scanf("%ld%ld%ld",&from,&to,&cost);
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

void SPF(int i)
{
    int t,j,h,d;
    memset(vist,0,sizeof(vist));
    h = -1;
    d = 0;
    for ( j = 1; j <= n; j++ )
        Dis[j][i] = lmax;
    Dis[s[i]][i] = 0;
    vist[s[i]] = true;
    q[0] = s[i];
    while ( h < d )
    {
        h++;
        t = q[h];
        vist[t]=false;
        for ( j = p[t]; j != -1; j = e[j].next )
            if ( e[j].cost+Dis[t][i] < Dis[e[j].v][i] )
            {
                Dis[e[j].v][i] = e[j].cost+Dis[t][i];
                if (!vist[e[j].v])
                {
                    vist[e[j].v] = true;
                    d++;
                    q[d] = e[j].v;
                }
            }
    }
}

int main()
{
    int i,k=1;
    __int64 min;
    while (scanf("%ld%ld",&n,&m)!=EOF)
    {
        init();
        min = 3*lmax;
        for ( i = 0; i < 3; i++ )
            SPF(i);
        memset(vist,0,sizeof(vist));
        for ( i = 1; i <= n; i++ )
            if ( Dis[i][0]==lmax || Dis[i][1]==lmax || Dis[i][2]==lmax ) vist[i] = true;
            else
            {
                Dis[i][3] = Dis[i][0]+Dis[i][1]+Dis[i][2];
                if ( min > Dis[i][3] ) min = Dis[i][3];
            }
        printf("Scenario #%d\n",k);
        k++;
        if ( min<3*lmax ) printf("%I64d\n\n",min);
        else printf("Can not reach!\n\n");
    }
    return 0;
} 
