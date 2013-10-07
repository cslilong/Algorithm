#include<iostream>
using namespace std;

typedef int type;
struct avl
{
	type key;
	int height;
	avl *left;
	avl *right;
	avl(const type &k,avl *l,avl *r,int h=0){
		key=k;
		left=l;
		right=r;
	}
};

const int heightt(avl *t) 
{
	if(t == NULL) return -1; return t->height;
}

int max(int x,int y){ if(x>y) return x; return y; }

void L(avl * &k2)
{
	avl *k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	k2->height = max( heightt(k2->left) , heightt(k2->right) ) + 1;
	k1->height = max( heightt(k1->left) , k2->height ) + 1;
	k2=k1;
}

void R(avl * &k2)
{
	avl *k1 = k2->right;
	k2->right = k1->left;
	k1->left = k2;
	k2->height = max( heightt(k2->left) , heightt(k2->right) ) + 1;
	k1->height = max( heightt(k1->right) , k2->height ) + 1;
	k2=k1;
}

void LL(avl * &k3)
{
	R(k3->left);
	L(k3);
}

void RR(avl * &k3)
{
	L(k3->right);
	R(k3);
}

void insert(avl * &t,type &x)
{
	if(t == NULL){
		t = new avl(x,NULL,NULL);
	}
	else if(x< t->key){
		insert(t->left,x);
		if(heightt(t->left) - heightt(t->right) ==2){
			if(x < t->left->key) L(t);
			else LL(t);
		}
	}
	else if(t->key < x){
		insert(t->right,x);
		if(heightt(t->right) - heightt(t->left) == 2){
			if(t->right->key < x) R(t);
			else RR(t);
		}
	}
	t->height = max( heightt(t->left) , heightt(t->right) ) + 1;
}

void bfs(avl *t)
{
	avl *p=t;
	avl *q[110];
	int head,tail;
	head=tail=0;
	q[tail++]=p;
	while(head<tail) {
		avl *tmp=q[head++];
		printf("%d",tmp->key);
		if(tmp->left != NULL) { q[tail++]=tmp->left; printf(" %d",tmp->left->key); } else printf(" #");
		if(tmp->right != NULL) { q[tail++]=tmp->right; printf(" %d\n",tmp->right->key); } else printf(" #\n");
	}
}

int main()
{
	int cases,n,m;	
	scanf("%d",&cases);
	while(cases--) {
		scanf("%d",&n); 
		avl *tree=NULL;
		while(n--) { scanf("%d",&m); insert(tree,m); }
		bfs(tree);
		if(cases != 0) printf("0\n");
	}
	return 0;
}