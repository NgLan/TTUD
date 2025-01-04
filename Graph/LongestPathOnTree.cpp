#include <bits/stdc++.h> 
using namespace std;

const int MAXN = 1005; // So dinh toi da tren cay

struct Edge {
	int destination;
	int weight;
};

vector<Edge> adj[MAXN]; // Danh sach ke
int w[MAXN][MAXN]; // Ma tran trong so
int d[MAXN]; // Khoang cach tu dinh goc (co the chon) den cac dinh khac
int parent[MAXN]; // Luu parent cua moi nut trong DFS

void init(int n) {
	fill(d, d + n + 1, -1);
	fill(parent, parent + n + 1, -1);
}

void DFS(int v) {
	for (Edge e : adj[v]) {
		int u = e.destination;
        int w = e.weight;
		if (d[u] < 0) { // Neu x chua duoc duyet
			d[u] = d[v] + w;
			parent[u] = v;
			DFS(u);
		}
	}
}

vector<int> longestPathOnTree(int n) {
	init(n);
	
	// Bat dau tu mot nut bat ki (gia su la nut 1)
	d[1] = 0;
	DFS(1);
	
	// Tim nut co khoang cach lon nhat (x) tinh tu nut 1
	int x = 1;
	for (int i = 2; i <= n; i++) {
		if (d[i] > d[x]) {
			x = i;
		}
	}
	
	// Khoi tao lai d và parent cho DFS tu nút x
	init(n);
	
	d[x] = 0;
	DFS(x);
	
	// Tim nut co khoang cach lon nhat (y) tinh tu nut x
	int y = x;
    for (int i = 1; i <= n; i++) {
        if (d[i] > d[y]) {
            y = i;
        }
    }
    
    // Lay duong di tu x den y
    vector<int> path;
    for (int v = y; v != -1 /*parent cua x la -1*/; v = parent[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());
    
    return path;
}

int main() {
	int n; // So luong nut
	cin >> n;
	int m; // So luong canh
    cin >> m; 
    
    // Ðoc các canh
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    // Tìm và in duong di dài nhat
    vector<int> path = longestPathOnTree(n);
    cout << "Longest Path: ";
    for (int node : path) {
        cout << node << " ";
    }
    cout << endl;

    return 0;
}
