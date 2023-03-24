#include<iostream>
#include<algorithm>
const int N = 1010;
using namespace std;

int n,m;//n为物品个数，m为背包容量
int v[N],w[N];
int f[N];


//二维数组
int main()
{
    cin>>n>>m;//n为物品个数
    for(int i = 1; i<=n;i++)
    {
        cin>>v[i]>>w[i];   
    }
    for(int i =1;i<=n;i++)
    {
        for(int j = m;j>=v[i];j--)
        {
            f[j] = max(f[j-v[i]]+w[i],f[j]);
        }
    }
    cout<<f[n]<<endl;
    system("pause");
    return 0;
}

