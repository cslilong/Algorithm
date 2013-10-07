#include <iostream>
#include <vector>
#include <stack>
using namespace std;
int n,m;
vector<int>map[200];
vector<int>rmap[200];
int order[200],use[200],be[200],coun,cnt;
int in[200],nmap[200][200],mk[200];
void read()
{
    int i;
    char ch[3];
    int a,b;
    int s[2];
    for(i=0;i<2*n;i++){map[i].clear();rmap[i].clear();}
    for(i=1;i<=m;i++)
    {
      cin>>a>>ch[0]>>b>>ch[1];
      if(ch[0]=='w')s[0]=0;
      else s[0]=1;
      if(ch[1]=='w')s[1]=0;
      else s[1]=1;
      map[2*a+s[0]].push_back(2*b+(s[1]+1)%2);
      map[2*b+s[1]].push_back(2*a+(s[0]+1)%2);
      rmap[2*b+(s[1]+1)%2].push_back(2*a+s[0]);
      rmap[2*a+(s[0]+1)%2].push_back(2*b+s[1]);
    }
    map[0].push_back(1);
    rmap[1].push_back(0);
}
void dfs(int u)
{
   use[u]=1;
   int i;
   for(i=0;i<map[u].size();i++)
   {
      int v=map[u][i];
      if(use[v])continue;
      dfs(v);
   }
   order[coun++]=u;
}
void rdfs(int u)
{
    use[u]=1;
    be[u]=cnt;
    int i;
    for(i=0;i<rmap[u].size();i++)
    {
        int v=rmap[u][i];
        if(use[v])continue;
        rdfs(v);                   
    }
}
void Make_G()
{
   int i,j;
   memset(in,0,sizeof(in));
   memset(nmap,0,sizeof(nmap));
   for(i=1;i<=cnt;i++)rmap[i].clear();
   for(i=0;i<2*n;i++)
   {
      for(j=0;j<map[i].size();j++)
      {
        int v=map[i][j];
        if(be[i]!=be[v]&&!nmap[be[v]][be[i]])
        {
           rmap[be[v]].push_back(be[i]);
           nmap[be[v]][be[i]]=1;
           in[be[i]]++;
        }
      }
   }
}
void DFS(int u)
{
    mk[u]=1;
    int i;
    for(i=0;i<rmap[u].size();i++)
    {
       int v=rmap[u][i];
       if(mk[v])continue;
       DFS(v);
    }
}
void toposort()
{
    int i,j,t;
    stack<int>S;
    //printf("in %d\n",in[1]);
    for(i=1;i<=cnt;i++)if(!in[i])S.push(i);
    //while(!S.empty()){printf("%d\n",S.top());S.pop();}
    int s=0;
    while(!S.empty())
    {
      int v=S.top();
      S.pop();
      order[s++]=v;
      //printf("%d\n",order[s]);
      for(j=0;j<rmap[v].size();j++)
      {
        in[rmap[v][j]]--;
        if(!in[rmap[v][j]])S.push(rmap[v][j]);
      }
    }
    memset(use,0,sizeof(use));
    memset(mk,0,sizeof(mk));
    for(i=0;i<s;i++)
    {
       if(mk[order[i]]==0)
       {
         mk[order[i]]=-1;
         for(j=0;j<2*n;j++)
         {
           if(be[j]==order[i])
           {
             if(j%2)t=j-1;
             else t=j+1;
             t=be[t];
             if(mk[t])continue;
             mk[t]=1;
             DFS(t);
           }
         }
       }
    }
    use[0]=1;
    for(i=2;i<2*n;i++)if(mk[be[i]]==mk[be[0]]){use[i]=1;}
    for(i=2;i<2*n;i++)
    if(use[i])
    {
       if(i>3)printf(" ");
       if(i%2)printf("%dh",i/2);
       else printf("%dw",i/2);
    }
    printf("\n");
}
void work()
{
    int i;
    coun=0;
    memset(use,0,sizeof(use));
    for(i=0;i<2*n;i++)
    {
       if(!use[i])
       {
         dfs(i);
       }
    }
    cnt=0;
    memset(use,0,sizeof(use));
    for(i=coun-1;i>=0;i--)
    {
       if(!use[order[i]])
       {
         cnt++;
         rdfs(order[i]);
       }
    }
    int ok=0;
    for(i=0;i<n;i++)
    if(be[2*i]==be[2*i+1]){ok=1;break;}
    if(ok){printf("bad luck\n");return;}
    Make_G();
    toposort();
}
int main()
{
    while(1)
    {
      scanf("%d%d",&n,&m);
      if(n==0&&m==0)break;
      read();
      work();
    }
    return 0;
}
/*
18 19 17 16 12 11 8 14 7 6 13 10 5 4 15 3 2 9 1 0

19 20 18 17 13 12 9 15 8 7 14 11 6 5 16 4 3 10 2 1
*/
