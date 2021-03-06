#include<iostream>
using namespace std;

void sift(int r[],int k,int m)  //下滤操作
{
	int i,j;
	i=k;
	j=2*i;
	r[0]=r[k];
	while(j<=m)
	{
		if((j<m)&&(r[j+1]>r[j])) j++;
		if(r[0]<r[j])
		{
			r[i]=r[j];
			i=j;
			j=2*i;
		}
		else j=m+1;		
	}
	r[i]=r[0];
}

void heapsort(int r[],int n)
{
	int i;
	for(i=n/2;i>=1;i--) sift(r,i,n);//建立一个初始堆
	for(i=n;i>=2;i--)
	{
		r[0]=r[i];  //删除堆顶元素
		r[i]=r[1];
		r[1]=r[0];
		sift(r,1,i-1); //下滤
	}
}

int main()
{
	int i,n,a[200];
	while(scanf("%d",&n)){
	for(i=1;i<=n;i++) scanf("%d",&a[i]);
	heapsort(a,n);
	for(i=1;i<=n;i++) printf("%d ",a[i]);}
	return 0;
}
 