#include<iostream>
using namespace std;

const int maxn=500100;

struct node
{
	int key;
	node *nxt[26];
}*root,tire[maxn];
int nodenum,tirenum;
int f[maxn],a[maxn];

void new_node(node* &x)
{
	//x = new node;
	x = &tire[tirenum++];
	memset(x,0,sizeof(node));
	x->key = -1;
}

int getnum(char *x)
{
	node *ptr=root;
	for(int i=0;x[i];++i)
	{
		int k = x[i]-'a';
		if(ptr->nxt[k]==0) new_node(ptr->nxt[k]);
		ptr = ptr->nxt[k];
	}
	if(ptr->key == -1) ptr->key = nodenum++;
	return ptr->key;
}

int find_set(int k)
{
    int root = k;
    while (f[root] != root) root = f[root];
    while (k != root)
    {
        int t = f[k];
        f[k] = root;
        k = t;
    }
    return root;
}


int main()
{
	char s1[20],s2[20];
	nodenum=0; tirenum=0;
	int u,v,i,e = 0;
	new_node(root);
	for(i=0;i<maxn;++i) f[i]=i;
	while(scanf("%s%s",s1,s2)!=EOF)
	{
		u = getnum(s1);
		v = getnum(s2);
		++a[u]; ++a[v];
		f[find_set(u)]=find_set(v);
	}
	e = find_set(0);
	for(i=1;i<nodenum;++i)
	{
		if(e!=find_set(i)) { printf("Impossible\n"); return 0; }
	}
	e = 0;
	for(i=0;i<nodenum;++i) if(a[i]&1) ++e;
	if(e<=2) printf("Possible\n");
	else printf("Impossible\n");
	return 0;
}

