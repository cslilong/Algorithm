#include<iostream>
using namespace std;
const __int64 maxlongint = 2147483647;
struct node 
{
    long l,r;
    __int64 s;
}tree[400010];

long n,s,e,tot,a,b,cc,nn,i;
__int64  m,ints;

__int64 f[160010];
long  st[10010],ed[10010],c[10010];

void quk(long l,long r)
{
    long x,i,j,temp;
    
    i=l;j=r;
    x=ed[(i+j)/2];
    do{
        while (ed[i]<x) ++i;
        while (ed[j]>x) --j;
        if (i<=j) {
            temp=st[i];st[i]=st[j];st[j]=temp;
            temp=ed[i];ed[i]=ed[j];ed[j]=temp;
            temp=c[i];c[i]=c[j];c[j]=temp;
            ++i;--j;
        }
    } while(i<=j);
    if (i<r) quk(i,r);
    if (l<j) quk(l,j);
}




void btree(long v,long l,long r)
{
    tree[v].l = l;
    tree[v].r = r;
    tree[v].s = maxlongint*10;
    if(l<r) {
        btree(v+v,l,(l+r)/2);
        btree(2*v+1,(l+r)/2+1,r);
    }
    
}

void search(long v,long l,long r)
{
    long mid;
    if(tree[v].l==l && tree[v].r==r) {
        if(m>tree[v].s) m = tree[v].s;
        return ;
    }
    mid = (tree[v].l+tree[v].r)/ 2;
    if (r<=mid) search(v*2,l,r);
    else if (l>=mid+1) search(v*2+1,l,r);
    else {
        search(v*2,l,mid);
        search(v*2+1,mid+1,r);
    }
}



void ins(long v,long r)
{
    long mid;
    if( tree[v].s >ints) tree[v].s=ints;
    if (tree[v].l-tree[v].r==0) return;
    mid=(tree[v].l+tree[v].r)/ 2;
    if (r<=mid) ins(v*2,r);
        else ins(v*2+1,r);
}

int main()
{
    scanf("%ld%ld%ld",&n,&s,&e);
   e=e-s+1;
  nn=0;
  for (i=1;i<=n;++i) {
      scanf("%ld%ld%ld",&a,&b,&cc);
      
      a=a-s+1;
      b=b-s+1;
      if (a<=0) a=1;
      if (b>=e ) b=e;
      if (b<=0 ) continue;
      nn++;
      st[nn]=a;
      ed[nn]=b;
      c[nn]=cc;
  }
  n=nn;
  quk(1,n);
  tot=0;
  btree(1,0,e);
  for (i=1;i<=e;++i) f[i]=maxlongint*10;
  for (i=1;i<=n;++i) {
      m=maxlongint*10;
      if (st[i]==1) m=0;
      else search(1,st[i]-1,ed[i]-1);
      if (m+c[i]<f[ed[i]]) f[ed[i]]=m+c[i];
      ints=f[ed[i]];
      ins(1,ed[i]);
  }
     if (f[e]<maxlongint)printf("%I64d\n",f[e]);
     else printf("-1\n");
     return 0;
}
