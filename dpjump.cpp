#include <bits/stdc++.h>
using namespace std;

const int N = 4;

// x[]数组存储对应物品0-1向量,0不装入背包，1表示装入背包
void Traceback(int n, int w[], int v[], int **p, int *head, int x[])
{

    int j = p[head[0] - 1][0], m = p[head[0] - 1][1];
    for (int i = 1; i <= n; i++)
    {
        x[i] = 0;                                        
        for (int k = head[i + 1]; k <= head[i] - 1; k++) 
        {
            if (p[k][0] + w[i] == j && p[k][1] + v[i] == m)
            {
                x[i] = 1;
                j = p[k][0]; 
                m = p[k][1]; 
                break;       
            }
        }
    }
}

int Knapsack(int n, int c, int v[], int w[], int **p, int x[])
{
    int *head = new int[n + 2];
    head[n + 1] = 0;            

    p[0][0] = 0;
    p[0][1] = 0; 

    int left = 0, right = 0, next = 1; 
    head[n] = 1;                       

    for (int i = n; i >= 1; i--)
    {
        int k = left;
        for (int j = left; j <= right; j++)
        {
            if (p[j][0] + w[i] > c)
                break;                                  
            int y = p[j][0] + w[i], m = p[j][1] + v[i];

            while (k <= right && p[k][0] < y)
            {
                p[next][0] = p[k][0];
                p[next++][1] = p[k++][1];
            }

            if (k <= right && p[k][0] == y)
            {
                if (m < p[k][1])
                {
                    m = p[k][1];
                }
                k++;
            }

            if (m > p[next - 1][1])
            {
                p[next][0] = y;
                p[next++][1] = m;
            }

            while (k <= right && p[k][1] <= p[next - 1][1])
            {
                k++;
            }
        }

        while (k <= right)
        {
            p[next][0] = p[k][0];
            p[next++][1] = p[k++][1];
        }

        left = right + 1;
        right = next - 1;

        head[i - 1] = next;
    }
    Traceback(n, w, v, p, head, x);
    return p[next - 1][1];
}

void solve()
{
    int c = 5;
    int v[] = {0, 2, 4, 4, 5}, w[] = {0, 1, 2, 3, 4}; // 下标从1开始
    int x[N + 1];

    int **p = new int *[50];
    for (int i = 0; i < 50; i++)
    {
        p[i] = new int[2];
    }

    cout << "weight: " << endl;
    for (int i = 1; i <= N; i++)
    {
        cout << w[i] << " ";
    }
    cout << endl;

    cout << "value: " << endl;
    for (int i = 1; i <= N; i++)
    {
        cout << v[i] << " ";
    }
    cout << endl;

    cout << "max-value: " << Knapsack(N, c, v, w, p, x) << endl;

    cout << "id: " << endl;
    for (int i = 1; i <= N; i++)
    {
        if (x[i] == 1)
        {
            cout << i << " ";
        }
    }
    cout << endl;

    for (int i = 0; i < 50; i++)
    {
        delete p[i];
    }

    delete[] p;
}

int main()
{

    solve();
    system("pause");
    return 0;
}