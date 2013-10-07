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

const int N = 2100;     //������� 

vector<int> g[N];     //ԭͼ��������� 
int n, m, h[N], id[N];     //id[]��ʾԭͼ��ÿ���㶼�����ĸ�ǿ��ͨ���� 
int cnt, scnt, dfn[N], low[N], cur[N];
int stack[N], top, est[N], etop;
vector<int> tree[N];     //�����޻�ͼ�ı��������(��ͼ) 
vector<int> contain[N];     //��ͼ��ÿ���㶼����ԭͼ�е���Щ�� 


/*
����build�Ƕ�ԭͼ��ʼ��(����ʵ�������������Ӧ�ĸ���) 
��Ϊa��b��ѡ��!a -> a�����ᵼ��aһ����ѡ��Ϊʲô��
���빹��һ����ʱ�򣬾�����ǿ��ͨ����������󣬶���ͼ������������Ȼ�����˵���Ե����Ⱦɫ��
���������˰ɣ���Ϊ����!a->a��������Ⱦɫ��˳��һ����a ,!a��
��ʱ���aû��Ⱦɫ����ôa��һ����Ⱦ��ɫ����aһ����Ⱦ��ɫ������ˬ�����ģ���
���a��!a֮�䲻���ڱߵĹ�ϵ�أ����ʾa,!a��ѡһ������Ϊ����һ����Ⱦ��ɫ��������һ��һ����Ⱦ��ɫ��
������ĳ���ѡ���ĸ����Ϳ�������˲�������ôд�ģ���ķ���˳�򣩡�

a and b = 1    ת��Ϊ ��(!a -> a),(!b->b)��
a and b = 0 ת��Ϊ��(a->!b),(b->!a)
a or b = 1    ת��Ϊ��(!a->b),(!b->a)
a or b = 0   ת��Ϊ��(a->!a),(b->!b)
a xor b = 1   ת��Ϊ��(a->!b),(!b->a),(b->!a),(!a->b)
a xor b = 0   ת��Ϊ��(a->b),(b->a),(!a->!b),(!b->!a)
*/
bool build() 
{
     if (scanf("%d %d",&n,&m)==EOF)  return false;
     n = n+n;
     int cc;
     char ss[10];
     for (int i=0;i<n;i++)
         g[i].clear();
     for (int i=0;i<m;i++)
     {
         int a,b,c,d;
         scanf("%d%d%d%s",&a,&b,&cc,ss);     //a��b�ǻ���ġ�a���������һ��Ϊc��b���������һ��Ϊd��ԭͼ�в����a->d�ͱ�b->c�� 
         a = a+a;
         b = b+b;
		 if (a%2==0) c=a+1;  else  c=a-1;
         if (b%2==0) d=b+1;  else  d=b-1;
         if(ss[0]=='A') {
		 	if(cc==1) { g[c].push_back(a);  g[d].push_back(b); }
		 	else { g[a].push_back(d);  g[b].push_back(c); }
		 } else if(ss[0]=='O') {
			if(cc==1) { g[c].push_back(b);  g[d].push_back(a); }
		 	else { g[a].push_back(c);  g[b].push_back(d); }
		 } else {
		 	if(cc==1) { g[a].push_back(d);  g[d].push_back(a); g[c].push_back(b);  g[b].push_back(c); }
		 	else { g[a].push_back(b);  g[b].push_back(a); g[c].push_back(d);  g[d].push_back(c); }
		 }         
     }
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
     for (int i=0,j=0;i<n;i++,j++)
         if (low[i]==1)
         {
             printf("%d",i);
             if (j!=n/2-1)
                 printf(" ");
             else
                 printf("\n");
         }
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
         printf("YES\n");
        // getOneAnswer();
     }
     else  printf("NO\n");
}

int main()
{
     while (build())
     {
         solve();
     }
} 
