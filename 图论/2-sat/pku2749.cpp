/*poj 2749 Building roads (二分 + 2-sat)
思路：见官方解题报告：
http://acm.pku.edu.cn/JudgeOnline/showcontest?contest_id=1177
*/
#include<iostream>
#include<vector>
using namespace std;
#define maxn 1110
vector<int> vA[maxn],vT[maxn];
int used[maxn],order[maxn],co,bg[maxn];
int n,A,B,a[maxn][2],b[maxn][2],xS,yS,xT,yT;
int d[maxn],D;

void dfsT(int x)
{
       used[x]=1;
       int i;
       for(i=0;i<vT[x].size();i++)
              if(!used[vT[x][i]])
                     dfsT(vT[x][i]);
       order[co++]=x;
}

void dfsA(int x,int id)
{
       used[x]=1;
       bg[x]=id;
       int i;
       for(i=0;i<vA[x].size();i++)
              if(!used[vA[x][i]])
                     dfsA(vA[x][i],id);
}

bool ok(int mid)
{
       int i,j,x,y;
       memset(used,0,sizeof(used));
       memset(bg,-1,sizeof(bg));
       for(i=0;i<=2*n;i++)
       {
              vA[i].clear();
              vT[i].clear();
       }
       for(i=0;i<A;i++)
       {
              x=a[i][0];
              y=a[i][1];
              vA[x].push_back(y+n);
              vA[y].push_back(x+n);
              vA[x+n].push_back(y);
              vA[y+n].push_back(x);
              vT[y+n].push_back(x);
              vT[x+n].push_back(y);
              vT[y].push_back(x+n);
              vT[x].push_back(y+n);
       }
       for(i=0;i<B;i++)
       {
              x=b[i][0];
              y=b[i][1];
              vA[x].push_back(y);
              vA[y].push_back(x);
              vA[x+n].push_back(y+n);
              vA[y+n].push_back(x+n);
             vT[y].push_back(x);
              vT[x].push_back(y);
              vT[y+n].push_back(x+n);
              vT[x+n].push_back(y+n);
       }
       for(i=0;i<n;i++)
       {
              for(j=i+1;j<n;j++)
              {
                     if(d[i]+d[j]>mid)
                     {
                            vA[i].push_back(j+n);
                            vA[j].push_back(i+n);
                           vT[j+n].push_back(i);
                            vT[i+n].push_back(j);
                     }
                     if(d[i+n]+d[j+n]>mid)
                     {
                            vA[i+n].push_back(j);
                            vA[j+n].push_back(i);
                           vT[j].push_back(i+n);
                            vT[i].push_back(j+n);
                     }
                     if(d[i]+D+d[j+n]>mid)
                     {
                            vA[i].push_back(j);
                            vA[j+n].push_back(i+n);
                            vT[j].push_back(i);
                            vT[i+n].push_back(j+n);
                     }
                     if(d[i+n]+D+d[j]>mid)
                     {
                            vA[i+n].push_back(j+n);
                            vA[j].push_back(i);
                            vT[j+n].push_back(i+n);
                            vT[i].push_back(j);
                     }
              }
       }
       for(i=0,co=0;i<2*n;i++)
       {
              if(!used[i])
                     dfsT(i);
       }
       memset(used,0,sizeof(used));
       for(i=n*2-1;i>=0;i--)
       {
              if(!used[order[i]])
                     dfsA(order[i],order[i]);
       }
       for(i=0;i<n;i++)
       {
              if(bg[i]==bg[i+n] && bg[i]!=-1)
                     return 0;
       }
       return 1;
}

int main()
{
       int i,j,x,y;
       int l,r,mid,key;
       while(scanf("%d%d%d",&n,&A,&B)==3)
       {
              scanf("%d%d%d%d",&xS,&yS,&xT,&yT);
              D=abs(xS-xT)+abs(yS-yT);
              for(i=0;i<n;i++)
              {
                     scanf("%d%d",&x,&y);
                     d[i]=abs(x-xS)+abs(y-yS);
                     d[i+n]=abs(x-xT)+abs(y-yT);
              }
              for(i=0;i<A;i++)
              {
                     scanf("%d%d",&a[i][0],&a[i][1]);
                     a[i][0]--;
                     a[i][1]--;
              }
              for(i=0;i<B;i++)
              {
                     scanf("%d%d",&b[i][0],&b[i][1]);
                     b[i][0]--;
                     b[i][1]--;
              }
              l=1;r=5000000;key=-1;
              while(l<=r)
              {
                     mid=(l+r)/2;
                     if(ok(mid))
                     {
                            key=mid;
                            r=mid-1;
                     }
                     else
                            l=mid+1;
              }
              printf("%d\n",key);
       }
       return 0;
}

 
