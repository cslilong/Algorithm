#include <iostream>
#include<vector>
using namespace std;
const int MAXN = 10010;
const int MAXV = 4000000; //素数表范围
bool mark[MAXV + 10]; //标志一个数是否为素数

struct node
{
    int x;
    bool flag;
    int maxi;
}p[MAXN];
int total;
vector<int> ad[MAXN];
int tt[MAXN];
int kk;

void primeinit()
{
    int i,j,k,t;    
    for (i=2;i<=MAXV;i+=2) mark[i]=0;
    for (i=1;i<=MAXV;i+=2) mark[i]=1;
    mark[1]=0; mark[2]=1;
    for (i=3;i<=2000;i+=2)
    {
        if (mark[i])  {
            k=2*i;
            t=i+k;
            while (t<=MAXV)
            {
                mark[t]=0;
                t=t+k;
            }
        }
    }   
}

void f(int k)
{     
    tt[k]=++kk;
    int i,j,len  = ad[k].size();
    for(i=0;i<len;++i) if(tt[ad[k][i]]==0) f(ad[k][i]);
    int maxt=0;
    for(i=0;i<len;++i) 
    {        
        j=ad[k][i];
        if(tt[j]>tt[k]) {
           if(p[j].flag == false) { p[k].flag = false;  }
           if(p[j].maxi > maxt) { maxt = p[j].maxi; }
       }
    }
    if(p[k].flag==true && p[k].x>maxt) ++total;
    if(p[k].maxi < maxt) p[k].maxi = maxt;
}

int main()
{
    int n,i,x,y;
    primeinit();
    while(scanf("%d",&n)!=EOF)
    {        
        for(i=1;i<=n;++i) { ad[i].clear();  }
        for(i=1;i<=n;++i) {
            scanf("%d",&p[i].x);
            p[i].maxi=p[i].x;
            p[i].flag = mark[p[i].x];
            tt[i]=0;
        }
        for(i=1;i<n;++i) 
        {
            scanf("%d%d",&x,&y);
            ad[x].push_back(y);
            ad[y].push_back(x);
        }
        kk=0;
        total = 0;
        f(1);
        printf("%d\n\n",total);
    
    }
//    system("pause");
    return 0;
}

/*
5
3 11 13 12 17
3 4
1 2
 1 3
1 5

5
2 3 4 5 6
1 2
1 3 
1 4
1 5

5
2 3 7 5 11
1 2
1 3 1 4
1 5

*/

