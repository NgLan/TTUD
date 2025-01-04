#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005; 

vector<int> adj[MAXN]; // Danh sach ke
stack<int> S;
int Num[MAXN], Low[MAXN];
int cur_num = 1;

void SCC(int v, int pv) {
    Low[v] = Num[v] = cur_num++;
	S.push(v);
	
    for (int u : adj[v]) {
        if (u == pv) continue; // Neu u la cha cua v thi bo qua (vi u chac chan duoc duyet roi)

        if (Num[u] == -1) { // Neu u chua duoc tham
            SCC(u, v);
            // Cap nhat Low[v] sau khi tham u
            Low[v] = min(Low[v], Low[u]);
        } else {
        	// Neu u duoc tham roi ma khong la cha truc tiep cua v tuc la co canh nguoc tu v len u
			Low[v] = min(Low[v], Low[u]); 
		}
    }
    
    // Neu Num[v] == Low[v], tìm duoc mot thanh phan lien thong manh
	if (Num[v] == Low[v]) {
		cout << "SCC: ";
		while (1) {
			int u = S.top();
			S.pop();
			cout << u << " ";
			if (u == v) break;
		}
		cout << endl;
	}
}

int main() {
    int n, m; // n: so dinh, m: so canh
    cin >> n >> m;

    // Khoi tao danh sach ke
    for (int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v); 
        adj[v].push_back(u); // Do thi vo huong
    }

    // Khoi tao Num và Low
    fill(Num, Num + n + 1, -1);
    fill(Low, Low + n + 1, -1);
    
    // Danh cho do thi lien thong
    SCC(1, -1);
    
    // Danh cho do thi khong lien thong
//    for (int i = 1; i <= n; ++i) {
//        if (Num[i] == -1) {
//            SCC(i, -1);
//        }
//    }

    // In ket qua Num Low
    cout << "i\t";
    for (int i = 1; i <= n; ++i) {
    	cout << i << "\t";
    }
    cout << "\nNum[i]\t";
    for (int i = 1; i <= n; ++i) {
        cout << Num[i] << "\t"; 
    }
    cout << "\nLow[i]\t";
	for (int i = 1; i <= n; ++i) {
        cout << Low[i] << "\t"; 
    }
    cout << endl << "Minh phat hien sau khi tao cay DFS theo cau truc Low Num thi cac dinh co cung Low se la 1 thanh phan lien thong manh" << endl;
    return 0;
}

// Test case
//11 14
//1 2
//2 3
//3 1
//3 4
//4 6
//6 5
//5 8
//8 11
//11 5
//6 7
//7 9
//9 4
//7 10
//6 9


