/*poj 2749 Building roads (���� + 2-sat)
˼·�����ٷ����ⱨ�棺
http://acm.pku.edu.cn/JudgeOnline/showcontest?contest_id=1177
*/
#include<iostream>
#include<vector>
using namespace std;
#define maxn 1110
vector<int> adj[maxn];
int n,A,B,a[maxn][2],b[maxn][2],xS,yS,xT,yT;
int d[maxn],D;
const int MAXN    = 1110;
const char NOTVIS = 0x00;   //����û�з��ʹ���״̬
const char VIS     = 0x01;   //������ʹ�,��û��ɾ����״̬
const char OVER    = 0x02;   //����ɾ����״̬
char     flag[MAXN];         //���ڱ�Ƕ���״̬,״̬��NOTVIS,VIS,OVER
int      belg[MAXN];         //�洢ǿ��ͨ����,����belg[i]��ʾ����i���ڵ�belg[i]��ǿ��ͨ����
int      stck[MAXN];         //��ջ,��������
int      mlik[MAXN];         //�ܹؼ�,�����ڽӵ�δɾ���������С����ʱ��
int      indx[MAXN];         //�������ʱ��

//���ѹ���,���㷨�����嶼������
void Visit(int cur, int &sig, int &scc_num)
{
   int i;
   stck[++stck[0]] = cur; flag[cur] = VIS;
   mlik[cur] = indx[cur] = ++sig;
   for ( i=0; i<adj[cur].size(); ++i )
   {
      if ( NOTVIS==flag[adj[cur][i]] )
      {
          Visit(adj[cur][i],sig,scc_num);
          if ( mlik[cur]>mlik[adj[cur][i]] )
          {
             mlik[cur] = mlik[adj[cur][i]];
          }
      }
      else if ( VIS==flag[adj[cur][i]] )
      {
         if ( mlik[cur]>indx[adj[cur][i]] ) 
		  //�ò��ֵ�indxӦ����mlik,���Ǹ����㷨������,ʹ��indxҲ����,��ʱ�����
		  // if(mlik[cur]>mlik[adj[cur][i]])
          {
             mlik[cur] = indx[adj[cur][i]]; 
             //mlik[cur] = mlik[adj[cur][i]]; 
          }
      }
   }
   if ( mlik[cur]==indx[cur] )
   {
      ++ scc_num;
      do
      {
          belg[stck[stck[0]]] = scc_num;
          flag[stck[stck[0]]] = OVER;
      }
      while ( stck[stck[0]--]!=cur );    
   }
}
//Tarjan�㷨,���belg[1..n],�ҷ���ǿ��ͨ��������,
int Tarjan()
{
   int i, sig, scc_num;
   memset(flag,NOTVIS,sizeof(char)*n);
   sig = 0; scc_num = 0; stck[0] = 0;
   for ( i=0; i<n; ++i )
   {
      if ( NOTVIS==flag[i] )
      {
          Visit(i,sig,scc_num);
      }
   }
   return scc_num;
}

bool ok(int mid)
{
       int i,j,x,y;
       for(i=0;i<=2*n;i++)
       {
              adj[i].clear();
       }
       for(i=0;i<A;i++)
       {
              x=a[i][0];
              y=a[i][1];
              adj[x].push_back(y+n);
              adj[y].push_back(x+n);
              adj[x+n].push_back(y);
              adj[y+n].push_back(x);
       }
       for(i=0;i<B;i++)
       {
              x=b[i][0];
              y=b[i][1];
              adj[x].push_back(y);
              adj[y].push_back(x);
              adj[x+n].push_back(y+n);
              adj[y+n].push_back(x+n);
       }
       for(i=0;i<n;i++)
       {
              for(j=i+1;j<n;j++)
              {
                     if(d[i]+d[j]>mid)
                     {
                            adj[i].push_back(j+n);
                            adj[j].push_back(i+n);
                     }
                     if(d[i+n]+d[j+n]>mid)
                     {
                            adj[i+n].push_back(j);
                            adj[j+n].push_back(i);
                     }
                     if(d[i]+D+d[j+n]>mid)
                     {
                            adj[i].push_back(j);
                            adj[j+n].push_back(i+n);
                     }
                     if(d[i+n]+D+d[j]>mid)
                     {
                            adj[i+n].push_back(j+n);
                            adj[j].push_back(i);
                     }
              }
       }
       n=n<<1;
       Tarjan();
       n=n>>1;
       for(i=0;i<n;i++)
       {
              if(belg[i]==belg[i+n])
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

 
