#include<iostream>
#include<cstring>
#include<stdio.h>
#include<algorithm>
#include<vector>


using namespace std;

vector<int> Lf[4003];
vector<int> Ls[4003];
vector<int> pq1[1003];
vector<int> pq2[1003];

struct data {
    int deep;
    int son;
};
data Tf[4003];
data Ts[4003];
char s[4003];
int Nf, Ns;
int father[4003];
int snum;

bool cmp(data A, data B) {
    if (A.deep != B.deep) return A.deep < B.deep;
    return A.son < B.son;
}

void dfs1(int k,int pre)
{
	int i,len=pq1[k].size();
	for(i=0;i<len;++i)
	{		
		if(pq1[k][i]!=pre) {
			s[snum++]='0';
		//	cout<<s[snum-1]; /////
			dfs1(pq1[k][i],k);
			s[snum++]='1';
		//	cout<<s[snum-1]; /////
		}
	}
	
	
}

void dfs2(int k,int pre)
{
	int i,len=pq2[k].size();
	for(i=0;i<len;++i)
	{		
		if(pq2[k][i]!=pre) {
			s[snum++]='0';
		//	cout<<s[snum-1]; /////
			dfs2(pq2[k][i],k);
			s[snum++]='1';
		//	cout<<s[snum-1]; /////
		}
	}
	
}

int main() {
    int cas,n,i,x,y;
    scanf("%d", &cas);
    while (cas--) {
		scanf("%d",&n);
		for(i=1;i<=n;++i) { pq1[i].clear(); pq2[i].clear(); }
		for(i=1;i<n;++i) {
			scanf("%d%d",&x,&y);
			pq1[x].push_back(y);
			pq1[y].push_back(x);			
		}
		//cout<<" s1 snum "<<endl; ////
		snum=0;
		dfs1(1,-1);
		s[snum]=0;
        //scanf("%s", s);
        int Len = strlen(s);
        Lf[1].clear();
        Tf[1].deep = 0; Nf = 1;
        int cur = 1;
        for (i = 0; i < Len; i++) { if (s[i] == '0') {
                Nf++;
                Lf[cur].push_back(Nf);
                father[Nf] = cur;
                Tf[Nf].deep = Tf[cur].deep + 1;
                Lf[Nf].clear();
                cur = Nf;
            } else {
                cur = father[cur];
            }
        }
        for (i = 1; i <= Nf; i++) {
            Tf[i].son = 1;
        }
        for (i = Nf; i > 1; i--) {
            Tf[father[i]].son += Tf[i].son;
        }
       // cout<<" s2 snum "<<endl; ////
        for(i=1;i<n;++i) {
			scanf("%d%d",&x,&y);
			pq2[x].push_back(y);
			pq2[y].push_back(x);			
		}
		int flag=0;
		for(int ii=1;ii<=n;++ii) {
			snum=0;
			dfs2(ii,-1);
			s[snum]=0;
	        //scanf("%s", s);
	        Len = strlen(s);
	        Ns = 1;
	        cur = 1;
	        Ts[1].deep = 0;
	        for (i = 0; i < Len; i++) {
	            if (s[i] == '0') {
	                Ns++;
	                Ls[cur].push_back(Ns);
	                father[Ns] = cur;
	                Ls[Ns].clear();
	                Ts[Ns].deep = Ts[cur].deep + 1;
	                cur = Ns;
	            } else {
	                cur = father[cur];
	            }
	        }
	        for (i = 1; i <= Ns; i++) {
	            Ts[i].son = 1;
	        }
	        for (i = Ns; i > 1; i--) {
	            Ts[father[i]].son += Ts[i].son;
	        }
	       // if(Nf>1501 || Ns>1501) while(1);
	
	        if (Nf != Ns) {
	            printf("different\n");
	            continue;
	        }
	        sort(Tf + 1, Tf + Nf + 1, cmp);
	        sort(Ts + 1, Ts + Ns + 1, cmp);
	
	
	
	        int check = 0;
	        for (i = 1; i <= Nf; i++) {
	            if (Tf[i].deep != Ts[i].deep || Tf[i].son != Ts[i].son) {
	                check = 1;
	                break;
	            }
	        }
	        if(!check) flag =1;
	        if(flag) break;
		}
        if (!flag) printf("different\n");
        else printf("same\n");
    }
    //system("pause");
    return 0;
}
