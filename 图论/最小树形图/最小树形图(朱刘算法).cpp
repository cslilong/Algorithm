#include <algorithm>
#include <cfloat>
#include <cstdio>
using namespace std;

const int N = 100;
bool visited[N];
int n;
double a[N][N]; //�ڽӾ���

void DFS(int x)
{
    visited[x] = true;
    for (int i = 0; i < n; ++i)
        if (!visited[i] && a[x][i] < DBL_MAX-1) DFS(i);
}

double ZhuYongJin_LiuZhenHong()
{ //�����������
    static bool flag[N];
    static int prev[N];
    double res = 0;
    fill_n(flag, n, false);
    for(;;)
    {
        int i;
        for (i = 1; i < n; ++i)
        {
            if (flag[i]) continue; //�õ��ѱ�ɾ��
            prev[i] = i;
            a[i][i] = INT_MAX; //ɾ���Ի�
            for (int j = 0; j < n; ++j)
                if (!flag[j] && a[j][i] < a[prev[i]][i])
                    prev[i] = j;
        }
        for (i = 1; i < n; ++i)
        {
            if (flag[i]) continue;

            //Ѱ�һ�
            int j = i;
            visited[0] = true;
            fill_n(visited+1, n-1, false);
            do visited[j] = true, j = prev[j];
            while (!visited[j]);

            if (!j) continue; //�������ڵ�
            i = j;
            res += a[prev[i]][i];
 
            for (j = prev[i]; j != i; j = prev[j])
            {
                flag[j] = true; //ɾ�����г��� i ֮������нڵ�
                res += a[prev[j]][j];
            }

            //w(j, i) ��ȥ w(prev(i), i)
            for (j = 0; j < n; ++j)
                if (!flag[j] && a[j][i] < DBL_MAX-1)
                    a[j][i] -= a[prev[i]][i];

            //�޸ĺͻ������ıߵ�Ȩֵ
            for (int k = 0; k < n; ++k)
                if (!flag[k])
                    for (j = prev[i]; j != i; j = prev[j])
                    {
                        if (a[j][k] < a[i][k]) a[i][k] = a[j][k];
                        if (a[k][j] < DBL_MAX-1 && a[k][j]-a[prev[j]][j] < a[k][i]) a[k][i] = a[k][j]-a[prev[j]][j];
                    }
            break;
        }
        if (i == n) //���ٴ��ڻ�
        {
            for (i = 1; i < n; ++i)
                if (!flag[i]) res += a[prev[i]][i];
            break;
        }
    }
    return res;
}

int main()
{
    int m, u, v;
    double w;
    while (scanf("%d%d", &n, &m) != EOF)
    {
        for (int i = 0; i < n; ++i)
            fill_n(a[i], n, DBL_MAX);
        for (; m; --m)
        {
            scanf("%d%d%lf", &u, &v, &w);
            a[u][v] = w;
        }
        fill_n(visited, n, false);
        DFS(0);
        for (int i = 1; i < n; ++i)
            if (!visited[i])
            {
                puts("��С����ͼ������");
                goto L1;
            }
        printf("%lf\n", ZhuYongJin_LiuZhenHong());
L1:;
    }
    return 0;
}  
 
