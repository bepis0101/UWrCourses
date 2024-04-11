#include <bits/stdc++.h>

using namespace std;

const int N = 5e5 + 1;

pair<int, int> points[N];

pair<int, int> resPoints[3];

double res = 1e18;

double circCalc(int i, int j, int k) {
    double a = sqrt((points[i].first - points[j].first) * (points[i].first - points[j].first) + (points[i].second - points[j].second) * (points[i].second - points[j].second));
    double b = sqrt((points[i].first - points[k].first) * (points[i].first - points[k].first) + (points[i].second - points[k].second) * (points[i].second - points[k].second));
    double c = sqrt((points[j].first - points[k].first) * (points[j].first - points[k].first) + (points[j].second - points[k].second) * (points[j].second - points[k].second));
    return a + b + c;
}


double circCalc(pair<int, int> x, pair<int, int> y, pair<int, int> z) {
    double a = sqrt((x.first - y.first)*(x.first - y.first) + (x.second - y.second)*(x.second - y.second));
    double b = sqrt((x.first - z.first)*(x.first - z.first) + (x.second - z.second)*(x.second - z.second));
    double c = sqrt((y.first - z.first)*(y.first - z.first) + (y.second - z.second)*(y.second - z.second));
    return a + b + c;
}

void printTable(int l, int r) {
    for(int i = l; i <= r; i++) {
        cout << points[i].first << ' ' << points[i].second << '\n';
    }
    cout << "\n\n\n";
}

void findMinInHalves(int l, int r) {
    if(r-l < 5) {
        for(int i = l; i <= r; i++) {
            for(int j = i+1; j <= r; j++) {
                for(int k = j+1; k <= r; k++) {
                    double circ = circCalc(i, j, k);
                    if(circ < res) {
                        res = circ;
                        resPoints[0] = points[i];
                        resPoints[1] = points[j];
                        resPoints[2] = points[k];
                    }
                }
            }
        }
        return;
    }
    int mid = (l + r) / 2;

    findMinInHalves(l, mid); 
    findMinInHalves(mid+1, r);
}

void findMinAroundMids(int l, int r) {
    // printTable(l, r);
    int len = r-l+1;
    if(len < 6) return;
    int mid = (l + r) / 2;
    vector<pair<int, int>> midPoints;
    double minDist = res/2;
    if(len%2 == 0) {
        double median = (points[mid].first + points[mid+1].first)/2;
        for(int i = mid; i >= l; i--) {
            if(points[mid].first - points[i].first > minDist) break;
            midPoints.push_back(points[i]);
        }
        for(int i = mid+1; i <= r; i++) {
            if(points[i].first - points[mid+1].first > minDist) break;
            midPoints.push_back(points[i]);
        }
    } else {
        double median = points[mid].first;
        for(int i = mid; i >= l; i--) {
            if(points[mid].first - points[i].first > minDist) break;
            midPoints.push_back(points[i]);
        }
        for(int i = mid+1; i <= r; i++) {
            if(points[i].first - points[mid+1].first > minDist) break;
            midPoints.push_back(points[i]);
        }
    }
    sort(midPoints.begin(), midPoints.end(), [](pair<int, int> a, pair<int, int> b) {
        return a.second < b.second;
    });
    /*for(int i = 0; i < midPointsLeft.size(); i++) {
        for(int j = 0; j < midPointsRight.size(); j++) {
            for(int k = j+1; k < midPointsRight.size(); k++) {
                double circ = circCalc(midPointsLeft[i], midPointsRight[j], midPointsRight[k]);
                if(circ < res) {
                    res = circ;
                    resPoints[0] = midPointsLeft[i];
                    resPoints[1] = midPointsRight[j];
                    resPoints[2] = midPointsRight[k];
                }
            }
        }
    }
    for(int i = 0; i < midPointsRight.size(); i++) {
        for(int j = 0; j < midPointsLeft.size(); j++) {
            for(int k = j+1; k < midPointsLeft.size(); k++) {
                double circ = circCalc(midPointsRight[i], midPointsLeft[j], midPointsLeft[k]);
                if(circ < res) {
                    res = circ;
                    resPoints[0] = midPointsRight[i];
                    resPoints[1] = midPointsLeft[j];
                    resPoints[2] = midPointsLeft[k];
                }
            }
        }
    }*/
    for(int i = 0; i < midPoints.size()-2; i++) {
        for(int j = i+1; j < midPoints.size()-1; j++) {
            if(midPoints[j].second - midPoints[i].second >= minDist) {
                i++;
                j = i;
            } else {
                for(int k = j+1; k < midPoints.size(); k++) {
                    if(midPoints[k].second - midPoints[i].second >= minDist) {
                        j++;
                        k = j;
                    } else {
                        double circ = circCalc(midPoints[i], midPoints[j], midPoints[k]);
                        if(circ < res) {
                            res = circ;
                            resPoints[0] = midPoints[i];
                            resPoints[1] = midPoints[j];
                            resPoints[2] = midPoints[k];
                        }
                    }
                }
            
            }
        }
    }
    findMinAroundMids(l, mid);
    findMinAroundMids(mid+1, r);
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
    findMinInHalves(0, n-1);
    findMinAroundMids(0, n-1);
    
    for(int i = 0; i < 3; i++) {
        cout << resPoints[i].first << ' ' << resPoints[i].second << '\n';
    }


}