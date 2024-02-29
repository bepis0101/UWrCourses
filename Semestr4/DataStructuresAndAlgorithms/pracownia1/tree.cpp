#include <bits/stdc++.h>

using namespace std;

const int N = 1e5+2;

vector <int> drz[N];

bool vis[N];
int pre[N];
int post[N];

int pree, postt;
void dfs(int u)
{
    pree++;
    pre[u] = pree;
    vis[u] = true;
    for (int j = 0; j < drz[u].size(); j++)
    {
        int v = drz[u][j];
        if (vis[v] == 0)
        {
            dfs(v);
        }
    }
    postt++;
    post[u] = postt;    
}

int main ()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, q;
    cin >> n >> q;
    for (int i = 2; i <= n; i++)
    {
        int a;
        cin >> a;
        drz[i].push_back(a);
        drz[a].push_back(i);
    }
    dfs(1);
    while(q--)
    {
        int u, v;
        cin >> v >> u;
        if (pre[v] <= pre[u] and post[u] <= post[v])
        {
            cout << "TAK" << "\n";
        }
        else 
        {
            cout << "NIE" << "\n";
        }
    }
}