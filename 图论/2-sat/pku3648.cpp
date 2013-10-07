/*
2-SAT����:
��n���ˣ�0��1��һ��ģ�2��3��һ��ģ�....��n-2��n-1��һ��ġ���m������������ÿ������������a��b��ɣ���ʾa��b�ǲ����ദ�ġ�
����Ҫ��ÿ����ѡһ���˳�������һ�����壬��������2���˶������ദ�ġ� 
*/
#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

const int N = 210;     //������� 

vector<int> g[N];     //ԭͼ��������� 
int n, m, h[N], id[N];     //id[]��ʾԭͼ��ÿ���㶼�����ĸ�ǿ��ͨ���� 
int cnt, scnt, dfn[N], low[N], cur[N];
int stack[N], top, est[N], etop;
vector<int> tree[N];     //�����޻�ͼ�ı��������(��ͼ) 
vector<int> contain[N];     //��ͼ��ÿ���㶼����ԭͼ�е���Щ�� 


/*
����build�Ƕ�ԭͼ��ʼ��(����ʵ�������������Ӧ�ĸ���) 
��n��nŮ, ����һ��������, ����n-1���Ƿ���, ������һ�ų�����������(��Ŀû��Ҫ��������һ����), 
Ҫ���������ﲻ��ͬһ��, ÿ�Է��޲���ͬһ��. 
����, n��������m���м���(�п�����ͬ����, �п��������ɻ�����), Ҫ���м���������˲��ܶ������������, 
���ܰ�����λ, �������������һ�ߵ���, �������"bad luck".
solution: 2-SAT
��������Ҫ������Ŀ, ������˵�м����������һ����������ͬһ��("it is bad luck for the bride to see both members of such a pair"),
 �������ﲻ��ͬһ��("The bride and groom sit at one end, opposite each other"), 
 ����Ϊÿ�Է��޲���ͬһ��, ���������������. 

Ȼ��ͼ, ����λ����ߺ��ұ�, ����2i��ʾi�����������, 2i+1��ʾi���������ұ�, 
����2i+2n��ʾi��Ů�������, 2i+1+2n��ʾi��Ů�����ұ�.
 ÿ�Զ�����ͬһ�ߺð�, ÿ����4������߼���, ���Ǽ����Ҫ����ô��ʾ��? 
 ͨ��������˿���������ͬһ��, Ҳ��������һ�����������, �޷���X��Y����ʾ.  

���������������, ��ôͨ�����������һ�����ұߵĻ�, ��һ����Ȼ�����.
 ��, ����һ��ͨ���Ҫ��㶨��, ��ô��ΰ�����һ������߱�ʾ������ͼ����? 

��ô����˵��, ��Ϊ����һ�����ұ�, ��������������ұ�, ��ô����Ҳһ�����ұ�, 
����������������, ����Ҳһ�������, ���Ѿ���Ҫ���������ﲻ��ͬһ��, 
����ֻҪ�ټ���������������߼��ɱ�֤����һ�������.
��Ϊ��һ�Է��޲���ͬʱ������ͬһ�ߣ�������aΪ��ʾѡ���У�!a��ʾѡ��Ů�ģ������Ǳ�ѡ��
��ͼ���̣�
1���������ѡ������(a->!a)
2������ÿ��adulterous pairs(a,b)������(!a->b),(!b->a) Ҳ����a or b =1
*/

#define opp(x) ((x)^1)

bool build() 
{
     if (scanf("%d%d",&n,&m)==EOF)  return false;
     if(n==0) return false;
     n = n+n;
     int i,a,b;
     char ch[10];
     int s[10];
     for (i=0;i<n;i++) g[i].clear();
     for(i=1;i<=m;i++)
    {
      cin>>a>>ch[0]>>b>>ch[1];
      if(ch[0]=='w')a=a+a;
      else a=a+a+1;
      if(ch[1]=='w')b=b+b;
      else b=b+b+1;
      g[opp(a)].push_back(b);
      g[opp(b)].push_back(a);      
    }
    g[1].push_back(0);
    return true;
}

void dfs(int src) 
{
     etop = top = 0;
     stack[top++] = src;
     while(top != 0) 
     {
         int     c = stack[top-1];
         if(dfn[c] == -1) 
         { 
             h[c] = dfn[c] = low[c] = cnt++; 
             est[etop++] = c; 
         }
         for(; cur[c] >= 0; cur[c]--) 
         {
             int no = g[c][cur[c]];
             if(dfn[no] == -1) 
             { 
                 stack[top++] = no; 
                 break; 
             }
            // h[c] <?= low[no];
            h[c] = (h[c]<low[no])?h[c]:low[no];
         }
         if(cur[c] >= 0) 
             continue;
         top--; 
         int k;
         if(h[c] != low[c]) 
         { 
             low[c] = h[c]; 
             continue; 
         }
         do 
         {
             k = est[--etop];
             id[k] = scnt; low[k] = N;
         } while(k != c);
         scnt++;
     }
}

/*
����scR��dfs����ԭͼ��ǿ��ͨ����(������wywcgsԭ��) 
*/
void scR() 
{
     memset(dfn, -1, sizeof(dfn));
     cnt = scnt = 0;
     for(int i = 0; i < n; i++)
     { 
         cur[i] = g[i].size()-1;
         contain[i].clear();
     }
     for(int i = 0; i < n; i++)
         if(dfn[i] == -1) 
             dfs(i);
    
     /*
     ͳ��ÿ��ǿ��ͨ������������Щ�㣬Ϊ��������з�����׼�������������н⣬��ע�͵��� 
     */
     for (int i=0;i<n;i++)
     {
         contain[id[i]].push_back(i);
     }
}

/*
����judge�ж��Ƿ����ҳ�һ�����з������� 
*/
bool judge()
{
     for (int i=0;i<n;i+=2)
         if (id[i]==id[i+1])
             return false;
     return true;
}

/*
����buildGraph��ÿ��ǿ��ͨ������Ϊһ���㣬���¹�ͼ��(���㣬�õ�����һ�������޻�ͼ) 
�õ������ӱ����ʽ�������кܶ��رߡ����Լ�һЩԤ���������رߡ� 
*/
void buildGraph()
{
     for (int i=0;i<scnt;i++)
         tree[i].clear();
     for (int i=0;i<n;i++)
         for (int j=0;j<g[i].size();j++)
         {
             int a=id[i];
             int b=id[g[i][j]];
             if (a!=b)
             {
                 tree[b].push_back(a);
             }
         }
}

void tsDfs(int k)
{
     dfn[k]=cnt++;
     for (int i=0;i<tree[k].size();i++)
     {
         int w=tree[k][i];
         if (dfn[w]==-1)
         {
             tsDfs(w);
         } 
     }  
     low[scnt++]=k;             
}

/*
����topologicalSort��tsDfs�Ƕ���ͼ�����������������Ľ������low������ 
*/
void topologicalSort()
{
     for (int i=0;i<scnt;i++)
     {
         dfn[i]=-1;
         low[i]=-1;
     }
     int nn=scnt;
     cnt=scnt=0;
     for (int i=0;i<nn;i++)
     {
         if (dfn[i]==-1)
             tsDfs(i);
     }
}

void colorDfs(int k)
{
     dfn[k]=2;
     for (int i=0;i<tree[k].size();i++)
     {
         int w=tree[k][i];
         if (dfn[w]==-1)
         {
             colorDfs(w);
         } 
     }          
}

/*
����color��colorDfs�Ƕ���ͼ������ɫ����ͼ����ɫΪ1�ĵ����һ����н� 
*/ 
void color()
{
     for (int i=0;i<scnt;i++)
         dfn[i]=-1; 
     for (int i=scnt-1;i>=0;i--)
         if (dfn[low[i]]==-1) 
         {
             /*
             ��ͼ��low[i]��ɫΪ1������ì�ܵ�Ӧ���Ϊ2 
             */
             int a=contain[low[i]][0];     //��ԭͼ����һ������ǿ��ͨ����low[i]�ĵ�a����a���������һ��b������ǿ��ͨ����id[b]һ����low[i]ì�ܵ㡣 
             int b;
             if (a%2==0)
                 b=a+1;
             else
                 b=a-1;
             dfn[low[i]]=1;
             if (dfn[id[b]]==-1)
                 colorDfs(id[b]);     //����������ϵ����id[b]�ܴ�ĵ㶼��low[i]��ì�ܵ� 
         }
}

/*
����tagAnswer����ͼ��ԭͼ�ĵ���б�ǣ��õ�ԭͼ�Ŀ��н� 
*/
void tagAnswer()
{
     for (int i=0;i<n;i++)
         low[i]=-1;
     for (int i=0;i<scnt;i++)
         if (dfn[i]==1)//iΪ��ͼ�п��н�����ĵ㣬��ôԭͼ��ǿ��ͨ��������i�ĵ㶼��ԭͼ�п��н�ĵ� 
         {
             for (int j=0;j<contain[i].size();j++)
                 low[contain[i][j]]=1;
         }
}

/*
����printAnswer��ӡԭͼ�Ŀ��н� 
*/ 
void printAnswer()
{
     for (int i=2;i<n;i++)
         if (low[i]==1)
         {
             if(i>3)printf(" ");
			 printf("%d",i>>1);
             if(i&1) printf("h"); else printf("w");			
             //if (j!=n>>1-2)  printf(" ");
             //else  printf("\n");
             
		}
		printf("\n");
	//	cout<<low[0]<<" # "<<endl;
}

/*
����getOneAnswer�õ�ԭͼ��һ����н� 
*/ 
void getOneAnswer()
{
     buildGraph();
     topologicalSort();
     color();
     tagAnswer();
     printAnswer();
}

/*
����solve�ɸ���ʵ��Ҫ�󣬽��и������ 
*/ 
void solve()
{
     scR();
     if (judge())
     {
        // printf("YES\n");
         getOneAnswer();
     }
     else  printf("bad luck\n");
}

int main()
{
     while (build())
     {
         solve();
     }
     return 0;
} 
