#include<iostream>
#include<cstring>
#include<stdio.h>
#include<algorithm>
#include<vector>


using namespace std;

vector<int> Lf[3003];
vector<int> Ls[3003];

struct data {
    int deep;
    int son;
};
data Tf[3003];
data Ts[3003];
char s[3003];
int Nf, Ns;
int father[3003];

bool cmp(data A, data B) {
    if (A.deep != B.deep) return A.deep < B.deep;
    return A.son < B.son;
}

int main() {
    int cas;
    scanf("%d", &cas);
    while (cas--) {
        scanf("%s", s);
        int Len = strlen(s);
        Lf[1].clear();
        Tf[1].deep = 0; Nf = 1;
        int cur = 1;
        for (int i = 0; i < Len; i++) { if (s[i] == '0') {
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
        for (int i = 1; i <= Nf; i++) {
            Tf[i].son = 1;
        }
        for (int i = Nf; i > 1; i--) {
            Tf[father[i]].son += Tf[i].son;
        }
        scanf("%s", s);
        Len = strlen(s);
        Ns = 1;
        cur = 1;
        Ts[1].deep = 0;
        for (int i = 0; i < Len; i++) {
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
        for (int i = 1; i <= Ns; i++) {
            Ts[i].son = 1;
        }
        for (int i = Ns; i > 1; i--) {
            Ts[father[i]].son += Ts[i].son;
        }
        //if(Nf>1501 || Ns>1501) while(1); 

        if (Nf != Ns) {
            printf("different\n");
            continue;
        }
        sort(Tf + 1, Tf + Nf + 1, cmp);
        sort(Ts + 1, Ts + Ns + 1, cmp);



        int check = 0;
        for (int i = 1; i <= Nf; i++) {
            if (Tf[i].deep != Ts[i].deep || Tf[i].son != Ts[i].son) {
                check = 1;
                break;
            }
        }
        if (check) printf("different\n");
        else printf("same\n");
    }
    return 0;
}

/*
2
01001011
01001101

*/
