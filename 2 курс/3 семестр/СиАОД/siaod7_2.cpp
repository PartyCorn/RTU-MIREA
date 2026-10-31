#include <iostream>
#include <vector>
#include <algorithm>
#include <clocale>
using namespace std;

const int MAXN = 20;
const int INF = 1000000000;

int n = 0;
int g[MAXN][MAXN]; // матрица смежности, 0 означает отсутствие ребра

struct Path {
    vector<int> nodes;
    int cost;
};

// Алгоритм Дейкстры с учётом запрещённых вершин и рёбер
bool dijkstra(int s, int t, bool blockedNode[], bool blockedEdge[][MAXN], Path& res) {
    int dist[MAXN], prev[MAXN];
    bool used[MAXN];
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
        prev[i] = 0;
        used[i] = false;
    }
    dist[s] = 0;
    for (int k = 0; k < n; k++) {
        int v = 0;
        for (int i = 1; i <= n; i++)
            if (!used[i] && !blockedNode[i] && dist[i] < INF && (v == 0 || dist[i] < dist[v]))
                v = i;
        if (v == 0) break;
        used[v] = true;
        for (int u = 1; u <= n; u++)
            if (g[v][u] > 0 && !blockedNode[u] && !blockedEdge[v][u] && dist[v] + g[v][u] < dist[u]) {
                dist[u] = dist[v] + g[v][u];
                prev[u] = v;
            }
    }
    if (dist[t] == INF) return false;
    res.nodes.clear();
    for (int v = t; v != 0; v = prev[v]) res.nodes.push_back(v);
    reverse(res.nodes.begin(), res.nodes.end());
    res.cost = dist[t];
    return true;
}

// Совпадают ли первые len + 1 вершин двух путей
bool samePrefix(const vector<int>& a, const vector<int>& b, int len) {
    for (int i = 0; i <= len; i++)
        if (a[i] != b[i]) return false;
    return true;
}

bool inList(const vector<Path>& list, const Path& p) {
    for (int i = 0; i < (int)list.size(); i++)
        if (list[i].nodes == p.nodes) return true;
    return false;
}

void printPath(const Path& p) {
    for (int i = 0; i < (int)p.nodes.size(); i++) {
        if (i > 0) cout << " -> ";
        cout << p.nodes[i];
    }
    cout << ", длина " << p.cost << endl;
}

// Метод Йена: K кратчайших путей из s в t
void yen(int s, int t, int K) {
    vector<Path> A, B;
    bool noNode[MAXN] = { false };
    bool noEdge[MAXN][MAXN] = { {false} };
    Path first;
    if (!dijkstra(s, t, noNode, noEdge, first)) {
        cout << "Путь не существует\n";
        return;
    }
    A.push_back(first);
    for (int k = 1; k < K; k++) {
        Path last = A[k - 1];
        for (int i = 0; i + 1 < (int)last.nodes.size(); i++) {
            int spur = last.nodes[i];
            bool blockedNode[MAXN] = { false };
            bool blockedEdge[MAXN][MAXN] = { {false} };
            // Запрет рёбер, которыми уже продолжались пути с тем же началом
            for (int j = 0; j < (int)A.size(); j++)
                if ((int)A[j].nodes.size() > i + 1 && samePrefix(A[j].nodes, last.nodes, i)) {
                    int a = A[j].nodes[i], b = A[j].nodes[i + 1];
                    blockedEdge[a][b] = blockedEdge[b][a] = true;
                }
            // Запрет вершин начальной части пути
            int rootCost = 0;
            for (int j = 0; j < i; j++) {
                blockedNode[last.nodes[j]] = true;
                rootCost += g[last.nodes[j]][last.nodes[j + 1]];
            }
            Path spurPath;
            if (dijkstra(spur, t, blockedNode, blockedEdge, spurPath)) {
                Path total;
                total.nodes.assign(last.nodes.begin(), last.nodes.begin() + i);
                total.nodes.insert(total.nodes.end(), spurPath.nodes.begin(), spurPath.nodes.end());
                total.cost = rootCost + spurPath.cost;
                if (!inList(B, total) && !inList(A, total)) B.push_back(total);
            }
        }
        if (B.empty()) break;
        int best = 0;
        for (int j = 1; j < (int)B.size(); j++)
            if (B[j].cost < B[best].cost) best = j;
        A.push_back(B[best]);
        B.erase(B.begin() + best);
    }
    cout << "Найдено путей: " << A.size() << endl;
    for (int i = 0; i < (int)A.size(); i++) {
        cout << i + 1 << ") ";
        printPath(A[i]);
    }
}

void clearGraph() {
    for (int i = 0; i < MAXN; i++)
        for (int j = 0; j < MAXN; j++) g[i][j] = 0;
}

void addEdge(int u, int v, int w) {
    g[u][v] = g[v][u] = w;
}

void inputGraph() {
    int m, u, v, w;
    clearGraph();
    cout << "Число вершин (до " << MAXN - 1 << "): ";
    cin >> n;
    cout << "Число рёбер: ";
    cin >> m;
    cout << "Введите рёбра (вершина вершина вес):\n";
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        addEdge(u, v, w);
    }
}

void loadVariant() {
    clearGraph();
    n = 8;
    addEdge(1, 2, 23); addEdge(1, 3, 12); addEdge(2, 3, 25); addEdge(2, 5, 22);
    addEdge(2, 8, 35); addEdge(3, 4, 18); addEdge(4, 6, 20); addEdge(5, 6, 23);
    addEdge(5, 7, 14); addEdge(6, 7, 24); addEdge(7, 8, 16);
}

void printMatrix() {
    cout << "Матрица смежности:\n    ";
    for (int j = 1; j <= n; j++) cout << j << "\t";
    cout << endl;
    for (int i = 1; i <= n; i++) {
        cout << i << " | ";
        for (int j = 1; j <= n; j++) cout << g[i][j] << "\t";
        cout << endl;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    int choice, s, t, K;
    do {
        cout << "\n=== Метод Йена ===\n";
        cout << "1. Ввести граф с клавиатуры\n2. Загрузить граф варианта\n";
        cout << "3. Показать матрицу смежности\n4. Найти K кратчайших путей\n0. Выход\nВыбор: ";
        cin >> choice;
        if (choice == 1) {
            inputGraph();
        }
        else if (choice == 2) {
            loadVariant();
        }
        else if (choice == 3 || choice == 4) {
            if (n == 0) {
                cout << "Граф не задан\n";
            }
            else if (choice == 3) {
                printMatrix();
            }
            else {
                cout << "Начало, конец, K: ";
                cin >> s >> t >> K;
                if (s < 1 || s > n || t < 1 || t > n || s == t || K < 1)
                    cout << "Неверные данные\n";
                else
                    yen(s, t, K);
            }
        }
    } while (choice != 0);
    return 0;
}