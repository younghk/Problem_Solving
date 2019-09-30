#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <cstdlib>
#include <functional>
#include <algorithm>
#define min2(x,y) (x<y?x:y)
#define max2(x,y) (x>y?x:y)

using namespace std;
typedef long long ll;
typedef pair<double, int> pdi;

const int MAXN = 310;

struct Point {
	int x, y;
	Point operator- (const Point a)const {
		return{ x - a.x, y - a.y };
	}
	Point operator+ (const Point a)const {
		return{ x + a.x, y + a.y };
	}
} s, e;

Point operator* (const Point &a, const ll b) {
	return{ a.x*b,a.y*b };

}
vector<Point> convex[MAXN], node;
double d[MAXN];
priority_queue<pdi, vector<pdi>, greater<pdi> > pq;
bool out_conv[MAXN];
vector<pdi> dist[MAXN];

ll outer(Point A, Point B) {
	ll t = A.x*B.y - A.y*B.x;
	return t < 0 ? -1 : t>0;
}

ll CCW(Point A, Point B, Point C) {
	return outer(B - A, C - A);
}

bool isCross(Point A, Point B, Point C, Point D) {
	ll abc = CCW(A, B, C);
	ll abd = CCW(A, B, D);
	ll cda = CCW(C, D, A);
	ll cdb = CCW(C, D, B);
	ll ab = abc*abd;
	ll cd = cda*cdb;
	if (ab < 0 && cd < 0) return 1;
	if (cd < 0 && (abc^abd)) return 1;
	return 0;
}

ll square(ll x, ll y) {
	return x*x + y*y;
}

bool isIn(Point M, int idx) {
	ll ccw = CCW(convex[idx].back() * 2, convex[idx][0] * 2, M);
	for (int i = 0; i < convex[idx].size() - 1; i++) {
		if (ccw != CCW(convex[idx][i] * 2, convex[idx][i + 1] * 2, M)) return 0;
	}
	return 1;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
    
	int N;
	cin >> N >> s.x >> s.y >> e.x >> e.y;
	node.push_back(s);
	for (int i = 1; i <= N; i++) {
		int M;
		cin >> M;
		for (int j = 0; j < M; j++) {
			Point K;
			cin >> K.x >> K.y;
			convex[i].push_back(K);
			node.push_back(K);
		}
	}
	node.push_back(e);
	for (int i = 0; i < node.size(); i++) {
		bool flag = true;
		for (int k = 1; k <= N && flag; k++) {
			flag &= !isIn(node[i] * 2, k);
		}
		out_conv[i] = flag;
	}
	for (int i = 0; i < node.size(); i++) {
		if (!out_conv[i]) continue;
		for (int j = i + 1; j < node.size(); j++) {
			if (!out_conv[j]) continue;
			bool flag = true;
			for (int k = 1; k <= N && flag; k++) {
				for (int l = 0; l < convex[k].size() - 1 && flag; l++) {
					flag &= !isCross(node[i], node[j], convex[k][l], convex[k][l + 1]);
				}
				flag &= !isIn(node[i] + node[j], k);
				flag &= !isCross(node[i], node[j], convex[k].back(), convex[k][0]);
			}
			if (!flag) continue;

			double dista = sqrt(square(node[i].x - node[j].x, node[i].y - node[j].y));
			dist[i].push_back({ dista,j });
			dist[j].push_back({ dista,i });
		}
	}
	for (int i = 1; i < node.size(); i++) d[i] = 1e9;
	d[0] = 0;
	pq.push({ 0,0 });
	while (!pq.empty()) {
		double val = pq.top().first;
		int here = pq.top().second;
		pq.pop();
		if (d[here] < val) continue;
		for (pdi k : dist[here]) {
			if (d[k.second] > d[here] + k.first) {
				d[k.second] = d[here] + k.first;
				pq.push({ d[k.second],k.second });
			}
		}
	}
	if (d[node.size() - 1] >= 1e9) cout << -1;
	else {
		cout.precision(5);
		cout << fixed << d[node.size() - 1];
	}
	return 0;
}