#include <iostream>
#include <algorithm>
using namespace std;
const int MAXN = 3010;
const int MAXM = 2;
struct data {
int deep, son;
}d[MAXM][MAXN];
bool cmp(data a, data b)
{
if(a.deep != b.deep) return a.deep > b.deep;
return a.son > b.son;
}
int main()
{
int i, j, k, cases, now[MAXM], f[MAXN];
char str[MAXN];
cin >> cases;
while(cases --) {
for(i = 0; i < MAXM; i ++) {
cin >> str;
now[i] = j = f[1] = 1;
d[i][1].deep = d[i][1].son = 0;
for(k = 0; str[k]; k ++) {
if(str[k] == '0') {
f[++ now[i]] = j;
d[i][now[i]].deep = d[i][j].deep + 1;
d[i][now[i]].son = 0;
d[i][j].son ++;

j = now[i];
}else {
j = f[j];
}
}
for(j = now[i]; j > 1; j --)
d[i][f[j]].son += d[i][j].son;
}
for(i = 1; i < MAXM; i ++)
if(now[i] != now[0]) break;
if(i < MAXM) cout << "different" << endl;
else {
for(i = 0; i < MAXM; i ++)
sort(d[i] + 1, d[i] + now[i] + 1, cmp);
for(i = 1; i < MAXM; i ++) {
for(j = 1; j <= now[0]; j ++)
if((d[i][j].deep != d[0][j].deep) || (d[i][j].son != d[0][j].son))

break;
if(j <= now[0]) break;
}
if(i < MAXM) cout << "different" << endl;
else cout << "same" << endl;
}
}
return(0);
}
