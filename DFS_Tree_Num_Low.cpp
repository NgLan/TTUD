#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005; 

vector<int> adj[MAXN]; // Danh sach ke
vector<pair<int, int>> bridgeList; // Danh sach canh cau
int Num[MAXN], Low[MAXN];
bool joint[MAXN]; // Danh sach dinh khop
int cur_num = 1;

void Analyze(int v, int pv) {
	int child = 0;
    Low[v] = Num[v] = cur_num++;
	
    for (int u : adj[v]) {
        if (u == pv) continue; // Neu u la cha cua v thi bo qua (vi u chac chan duoc duyet roi)

        if (Num[u] == -1) { // Neu u chua duoc tham
            Analyze(u, v);
            child++;
            
            // Cap nhat Low[v] sau khi tham u
            Low[v] = min(Low[v], Low[u]);
            
            // Kiem tra dinh khop
            if ((pv == -1) && child > 1) {
            	// TH1: Dinh goc co hon 1 cay con
            	joint[v] = true;
			}
            if ((pv != -1) && Low[u] >= Num[v]) {
            	// TH2: Khong phai dinh goc
            	joint[v] = true;
			}
        } else {
        	// Neu u duoc tham roi ma khong la cha truc tiep cua v tuc la co canh nguoc tu v len u
			Low[v] = min(Low[v], Low[u]); 
		}
		
		// Kiem tra canh cau
		if (Low[u] > Num[v]) {
			bridgeList.push_back(make_pair(v, u));
		}
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
    fill(joint, joint + n + 1, false);

    // Goi hàm Analyze tu dinh 1 (hoac bat ki dinh nào)
    // Danh cho do thi lien thong
    Analyze(1, -1);

    // Danh cho do thi khong lien thong
//    for (int i = 1; i <= n; ++i) {
//        if (Num[i] == -1) {
//            Analyze(i, -1);
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
    cout << endl;
    
    // In ket qua canh cau
    cout << "Bridges:\n";
    for (pair<int, int> u : bridgeList) {
    	cout << u.first << " -- " << u.second << endl;
	}
    
    // In ket qua các dinh khop
    cout << "Articulation points:\n";
    for (int i = 1; i <= n; ++i) {
        if (joint[i]) {
            cout << i << " ";
        }
    }
    cout << endl;
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


