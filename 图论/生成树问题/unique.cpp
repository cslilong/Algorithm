#include<iostream>
#include<algorithm>
using namespace std;
struct Line
{
    int from,to,value;
    bool mark;
}line[20001];
bool cmp(const Line &a,const Line &b)
{
     return a.value<b.value;
}
int cases;
int fat[200];
int get(int n)
{
    if(fat[n]==n)
    return n;
    else
    return fat[n]=get(fat[n]);
}
bool merge(int a,int b)
{
     int fa=get(a),fb=get(b);
     if(fa!=fb)
     {
         fat[fa]=fb;
         return true;
     }
     return false;
}
int main()
{
    scanf("%d",&cases);
    while(cases--)
    {
         int n,m;
         scanf("%d%d",&n,&m);
         for(int i=1;i<=n;i++)
         fat[i]=i;
         for(int i=0;i<m;i++)
         {
         scanf("%d%d%d",&line[i].from,&line[i].to,&line[i].value);
         line[i].mark=false;
         }
         sort(line,line+m,cmp);
         int p=0,q=0;
         int res=0;
         while(p<n-1)
         {
             if(get(line[q].from)!=get(line[q].to))
             {
                  if(line[q].mark==false)
                  {
                       int tt=q+1;
                       while(tt<m&&line[tt].value==line[q].value)
                       {
                           if(get(line[tt].from)!=get(line[tt].to))
                           line[tt].mark=true;
                           tt++;
                       }
                  }
                  else  line[q].mark=false;
                  merge(line[q].from,line[q].to);
                  res+=line[q].value;
                  p++;
             }
                  q++;
         }
         bool judge=false;
         for(int i=0;i<m;i++)
         if(line[i].mark)  {  judge=true;    break; }
         if(judge)  printf("Not Unique\n");
         else  printf("%d\n",res);
    }
	return 0;
}
