#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#define inf 1000000000
int n,m,flag;
int adj1[30][30],adj2[30][30],used[30],pp[30],dua[30],dub[30];

int judge(int x,int y)
{
    int i;
    for(i=1;i<x;i++)
    {
        if(adj1[i][x]!=adj2[pp[i]][y])
            return 0;
    }
    return 1;
}
int dfs(int x,int y,int cnt)
{
    if(cnt>=n)
    {
        return 1;
    }
    int j;
    for(j=1;j<=n;j++)
    {
        if(!used[j] && dua[x+1]==dub[j] && judge(x+1,j))
        {
            used[j]=1;
            pp[x+1]=j;
            if(dfs(x+1,j,cnt+1))
            {
                return 1;
            }
            used[j]=0;
        }
    }
    return 0;
}
int main()
{
    int i,j,x,y,cases;

    scanf("%d",&cases);

    while(cases--)
    {
        scanf("%d%d",&n,&m);
        memset(adj1,0,sizeof(adj1));
        memset(adj2,0,sizeof(adj2));
        memset(dua,0,sizeof(dua));
        memset(dub,0,sizeof(dub));
        for(i=0;i<m;i++)
        {
            scanf("%d%d",&x,&y);
            adj1[x][y]++;
            adj1[y][x]++;
            dua[x]++;
            dua[y]++;
        }
        for(i=0;i<m;i++)
        {
            scanf("%d%d",&y,&x);
            adj2[x][y]++;
            adj2[y][x]++;
            dub[x]++;
            dub[y]++;
        }
        flag=0;
        memset(used,0,sizeof(used));
        for(i=1;i<=n;i++)
        {
            if(dua[1]!=dub[i])
            {
                continue;
            }
            used[i]=1;
            pp[1]=i;
            if(dfs(1,i,1))
            {
                flag=1;
                break;
            }
            used[i]=0;
        }
        if(flag)
            printf("same\n");
        else
            printf("different\n");
    }
    //system("pause");
    return 0;
}
