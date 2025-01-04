#include <bits/stdc++.h> 
using namespace std;

const int MAXN = 1005; // So dinh toi da tren cay

struct Edge {
	int destination;
	int weight;
};

vector<Edge> adj[MAXN]; // Danh sach ke
int d[MAXN]; // Tong khoang cach tu dinh v den tat ca cac dinh trong cay con cua v
int parent[MAXN]; // Cha cua moi nut trong DFS
int N[MAXN]; // So luong nut trong cay con cua v (bao gom ca v)
int f[MAXN]; // Tong duong di tu v den tat ca cac dinh con lai trong cay
int n; // So luong nut

void DFS1(int v) {
	for (Edge e : adj[v]) {
		int u = e.destination;
        int w = e.weight;
		if (parent[u] == 0) { // Neu u chua duoc tham
			parent[u] = v;
			DFS1(u);
			d[v] += d[u] + N[u]*w; // Tính tong khoang cach cua v bao gom cay con u
            N[v] += N[u]; // Cap nhat so luong nút trong cay con cua v (bao gom ca v)
		}
	}
}

void Phase1() {
    for (int i = 1; i <= n; ++i) { // Khoi tao giá tri ban dau
        parent[i] = 0; 
        d[i] = 0; 
        N[i] = 1; 
        f[i] = 0; 
    }
    parent[1] = 1; // Goc cua cây
    DFS1(1); // Thuc hien DFS tu goc
}

void DFS2(int v) {
    for (Edge e : adj[v]) {
    	int u = e.destination;
        int w = e.weight;
        if (parent[u] == 0) {
            int F = f[v] - (d[u] + N[u]*w); // Tong khoang cach tu v den tat ca cac dinh khac, ngoai cac dinh thuoc cay con u
            f[u] = F + d[u] + w*(n - N[u]);
            parent[u] = v; // Gán cha cua u là v
            DFS2(u);
        }
    }
}

void Phase2() {
    for (int i = 1; i <= n; ++i) {
        parent[i] = 0; // Ðat lai cha cua các nút
    }
    f[1] = d[1]; // Tong tai goc
    parent[1] = 1; // Goc cua cây
    DFS2(1); // Thuc hien DFS tu goc
}

int main() {
	cin >> n;
    
    // Ðoc các canh
    for (int i = 1; i <= n-1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    Phase1();
    Phase2();

    // Tong duong di tu moi nút
    for (int i = 1; i <= n; ++i) {
        cout << "Total distance from node " << i << ": " << f[i] << endl;
    }

	return 0;
}

// Test case
//5
//1 2 3
//1 3 4
//2 4 2
//2 5 1
