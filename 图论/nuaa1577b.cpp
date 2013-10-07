#include<iostream>
using namespace std;

#define INFINITY 1000000
#define MAXE 88005
#define MAXN 20002

int n;
long m,e,d[MAXE];
long s[MAXE]; 
long p[MAXN];

struct cow{
long t1;
long t2;
long w;
}c[MAXN];

void dijkstra()
{
    long i,j,min;
    for ( i = m; i <= e+1; i++ ) 
        d[i] = INFINITY;
    d[c[0].t1] = 0;
    j = 0;
    while ( j < n )
    {
        for ( i = s[c[j].t1]; i < s[c[j].t2]; i++ )
            if ( d[c[j].t2] > d[p[i]]+c[j].w )
               d[c[j].t2] = d[p[i]]+c[j].w;
        j++;
    }
}

int cmp1(const void *a,const void *b)
{
    if (((struct cow *)a)->t1==((struct cow *)b)->t1 )
    return ((struct cow *)a)->t2-((struct cow *)b)->t2;
    return ((struct cow *)a)->t1-((struct cow *)b)->t1;
}

int cmp2(const void *a, const void *b)
{
    return *(long *)a-*(long *)b;
}

int main()
{
    int i,j;
    scanf("%ld%ld%ld",&n,&m,&e);
    memset(s,0,sizeof(s[0]));
    for( i = 0,j = 0; i < n; i++ )
    {
        scanf("%ld%ld%ld",&c[i].t1,&c[i].t2,&c[i].w);
        c[i].t2++;
        if ( s[c[i].t1]==0 )
        {
            p[j++] = c[i].t1;
            s[c[i].t1] = 1;
        }
        if ( s[c[i].t2]==0 )
        {
            p[j++] = c[i].t2;
            s[c[i].t1] = 1;
        }
    }
    qsort(p,j,sizeof(p[0]),cmp2);
    for ( i = 0; i < j; i++ )
        s[p[i]] = i;
    qsort(c,n,sizeof(c[0]),cmp1);
    dijkstra();
    if ( d[e+1]==INFINITY )
       printf("-1\n");
    else printf("%ld\n",d[e+1]);
    return 0;
}  
