/*
Ψһ����С������ 
Acceteped : 4    Submit : 14  
Time Limit : 1000 MS   Memory Limit : 65536 KB 
  
Description 
��һ���Ǹ�Ȩ�ߵ�������ͨͼ����С������������������ͼ�����������������ϵ���С�������������Not Unique�����������С�������ıߵ�Ȩֵ�͡�


���룺

��һ����һ������K����ʾ�ж��ٸ������������Ժ�ÿ����������ռm+1�С�ÿ�����������ĵ�һ��Ϊ��������n��m��3<=n<=100������ʾͼ�Ķ������ͱ������ӵڶ��п�ʼÿ��Ϊ��������i��j,w,��ʾ��i��j�����Ȩֵ��


�����

ÿ�����һ�����������Ľ��������������ͼ�����������������ϵ���С�������������Not Unique�����������С�������ıߵ�Ȩֵ�͡�
 
  
Sample Input  
2
3 3
1 2 1
2 3 2
3 1 3
4 4
1 2 2
2 3 2
3 4 2
4 1 2 
  
Sample Output  
3
Not Unique 
*/
#include<iostream>
using namespace std;
int a[110][110],b[110];
bool mark[110],flag;
int cases,n,m,i,j,k,minn,minsum,pre,next,x,y,z;
int main()
{
	scanf("%d",&cases);
	while(cases--)
	{
		memset(mark,false,sizeof(mark));
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		minsum=0;flag=false;
		mark[1]=true;b[1]=1;
		scanf("%d%d",&n,&m);
		for(i=1;i<=m;i++) { scanf("%d%d%d",&x,&y,&z); a[x][y]=z;a[y][x]=z; }		
		for(k=2;k<=n;k++){
			minn=9999999;
			for(i=1;i<k;i++){
				for(j=1;j<=n;j++){
					if(!mark[j]) {
						if(a[b[i]][j]<minn&&a[b[i]][j]!=0) { minn=a[b[i]][j]; next=j; pre=b[i]; }
					}
				}
			}
			b[k]=next;
			for(i=1;i<k;i++)
			{
				if(b[i]==pre) continue;
				if(a[b[i]][next]==minn) { flag=true; break; }
			}
			if(flag) break;
			mark[next]=true;
			minsum+=minn;
		}
		if(flag) printf("Not Unique\n"); else printf("%d\n",minsum);
	//}
	return 0;
}