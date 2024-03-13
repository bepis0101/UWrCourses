#include <bits/stdc++.h>

using namespace std;

const int N = 1e6+2;

pair<int,int> drz[N];
int pre[N];
int post[N];
int timer = 1;
int children[N];

bool cmp(pair<int,int> a, pair<int,int> b)
{
    if (a.first == b.first) return a.second > b.second;
    return a.first < b.first;
}

void dfs(int u, int n)
{
    stack<int> s;
    s.push(u);
    int pointer = 2;
    while(!s.empty())
    {
        int v = s.top();
        if (pre[v] != 0)
        {
            s.pop();
            post[v] = timer++;
            continue;
        } 
        else 
        {
            pre[v] = timer++;
        }
        pointer = children[v];
        while(pointer <= n and drz[pointer].first == v)
        {
            s.push(drz[pointer].second);
            pointer++;
        }
    }

}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, q;
    cin >> n >> q;
    drz[1] = {0, 1};
    for (int i = 2; i <= n; i++)
    {
        int a;
        cin >> a;
        drz[i] = {a, i};
    }
    sort(drz+1, drz+n+1, &cmp);
    for(int i = 1; i <= n; i++)
    {
        if(children[drz[i].first] == 0) children[drz[i].first] = i;
    }
    dfs(1, n);
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