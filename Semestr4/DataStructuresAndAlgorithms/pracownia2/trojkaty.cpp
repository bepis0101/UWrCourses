#include <bits/stdc++.h>

using namespace std;

const int N = 5e5 + 1;

pair<int, int> points[N];

pair<int, int>* find3(int n) {
    int mid = n/2;
    return points + mid;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n; cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> points[i].first >> points[i].second;
    }
    sort(points, points + n);
    
}