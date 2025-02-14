#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <set>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <algorithm>
#include <cmath>
#include <string>

using namespace std;

const int INF = INT_MAX;
#define M_PI 3.14159265358979323846

void drawLine(vector<vector<char>>& grid, int x0, int y0, int x1, int y1) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx - dy;

    while (true) {
        if (x0 >= 0 && x0 < grid[0].size() && y0 >= 0 && y0 < grid.size()) {
            if (grid[y0][x0] == ' ') grid[y0][x0] = '*';
        }
        if (x0 == x1 && y0 == y1) break;
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

void drawGraph(const vector<pair<int, int>>& edges, const vector<int>& pesos, bool dirigido, int n) {
    const int gridWidth = 60;
    const int gridHeight = 30;
    vector<vector<char>> grid(gridHeight, vector<char>(gridWidth, ' '));

    int centerX = gridWidth / 2;
    int centerY = gridHeight / 2;
    int radius = min(centerX, centerY) - 2;

    vector<pair<int, int>> nodePositions(n);
    for (int i = 0; i < n; ++i) {
        double angle = 2 * M_PI * i / n;
        int x = centerX + static_cast<int>(radius * cos(angle));
        int y = centerY + static_cast<int>(-radius * sin(angle));
        nodePositions[i] = {x, y};
    }
    
     // Dibujar aristas
    for (int i = 0; i < edges.size(); ++i) {
        int u = edges[i].first;
        int v = edges[i].second;
        int peso = pesos[i];

        int x1 = nodePositions[u].first;
        int y1 = nodePositions[u].second;
        int x2 = nodePositions[v].first;
        int y2 = nodePositions[v].second;

        drawLine(grid, x1, y1, x2, y2);

        // Flecha para grafos dirigidos
        if (dirigido) {
            if (x2 >= 0 && x2 < gridWidth && y2 >= 0 && y2 < gridHeight) {
                grid[y2][x2] = '>';
            }
        }

        // Mostrar peso
        int midX = (x1 + x2) / 2;
        int midY = (y1 + y2) / 2;
        string pesoStr = to_string(peso);
        for (int j = 0; j < pesoStr.size() && midX + j < gridWidth; ++j) {
            if (midY >= 0 && midY < gridHeight) {
                grid[midY][midX + j] = pesoStr[j];
            }
        }
    }
    
        // Dibujar nodos
    for (int i = 0; i < n; ++i) {
        int x = nodePositions[i].first;
        int y = nodePositions[i].second;
        string nodeLabel = to_string(i);
        for (int j = 0; j < nodeLabel.size() && x + j < gridWidth; ++j) {
            if (y >= 0 && y < gridHeight) {
                grid[y][x + j] = nodeLabel[j];
            }
        }
    }

    // Imprimir el grafo
    for (const auto& row : grid) {
        for (char c : row) {
            cout << c;
        }
        cout << endl;
    }
}


    

void printAdjList(const vector<list<pair<int, int>>>& adj) {
    for (int i = 0; i < adj.size(); ++i) {
        cout << "Nodo " << i << ": ";
        for (auto& edge : adj[i]) {
            cout << "-> " << edge.first << " (peso " << edge.second << ") ";
        }
        cout << endl;
    }
}

void printAdjMatrix(const vector<vector<int>>& matrix) {
    int n = matrix.size();
    cout << "Matriz de adyacencia:\n   ";
    for (int i = 0; i < n; ++i) cout << i << " ";
    cout << endl;
    for (int i = 0; i < n; ++i) {
        cout << i << ": ";
        for (int j = 0; j < n; ++j) {
            if (matrix[i][j] == INF)
                cout << "INF ";
            else
                cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void dijkstraList(const vector<list<pair<int, int>>>& adj, int start) {
    int n = adj.size();
    vector<int> dist(n, INF);
    vector<bool> visited(n, false);

    dist[start] = 0;

    for (int count = 0; count < n-1; ++count) {
        int u = -1;
        for (int i = 0; i < n; ++i) {
            if (!visited[i] && (u == -1 || dist[i] < dist[u]))
                u = i;
        }

        if (u == -1 || dist[u] == INF) break;

        visited[u] = true;

        for (auto& edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;
            if (!visited[v] && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }

    cout << "Distancias mas cortas desde el nodo " << start << ":\n";
    for (int i = 0; i < n; ++i) {
        cout << "Nodo " << i << ": ";
        if (dist[i] == INF)
            cout << "INF";
        else
            cout << dist[i];
        cout << endl;
    }
}

void dijkstraMatrix(const vector<vector<int>>& matrix, int start) {
    int n = matrix.size();
    vector<int> dist(n, INF);
    vector<bool> visited(n, false);

    dist[start] = 0;

    for (int count = 0; count < n-1; ++count) {
        int u = -1;
        for (int i = 0; i < n; ++i) {
            if (!visited[i] && (u == -1 || dist[i] < dist[u]))
                u = i;
        }

        if (u == -1 || dist[u] == INF) break;

        visited[u] = true;

        for (int v = 0; v < n; ++v) {
            if (!visited[v] && matrix[u][v] != INF && dist[u] + matrix[u][v] < dist[v]) {
                dist[v] = dist[u] + matrix[u][v];
            }
        }
    }

    cout << "Distancias mas cortas desde el nodo " << start << ":\n";
    for (int i = 0; i < n; ++i) {
        cout << "Nodo " << i << ": ";
        if (dist[i] == INF)
            cout << "INF";
        else
            cout << dist[i];
        cout << endl;
    }
}

int main() {
    srand(time(0));

    int opcion;
    cout << "Menu:\n1. Lista de adyacencia\n2. Matriz de adyacencia\nElija una opcion: ";
    cin >> opcion;
    if (opcion != 1 && opcion != 2) {
        cout << "Opcion invalida.\n";
        return 1;
    }

    bool dirigido = rand() % 2;
    int n = rand() % 7 + 2;
    int max_possible = dirigido ? n * (n - 1) : n * (n - 1) / 2;
    int m = rand() % (min(8, max_possible) + 1);

    set<pair<int, int>> aristas;

    cout << "\nGrafo generado:\n";
    cout << "Tipo: " << (dirigido ? "Dirigido" : "No dirigido") << endl;
    cout << "Nodos: " << n << endl;
    cout << "Aristas: " << m << endl;

    for (int i = 0; i < m; ) {
        int u = rand() % n;
        int v = rand() % n;

        if (u == v) continue;

        if (!dirigido && u > v) swap(u, v);

        pair<int, int> arista = {u, v};

        if (aristas.find(arista) == aristas.end()) {
            aristas.insert(arista);
            i++;
        }
    }

    vector<pair<int, int>> listaAristas(aristas.begin(), aristas.end());
    vector<int> pesos(listaAristas.size());
    for (auto& w : pesos) {
        w = rand() % 10 + 1;
    }
    
    cout << "\nRepresentacion visual del grafo:\n";
    drawGraph(listaAristas, pesos, dirigido, n);

    if (opcion == 1) {
        vector<list<pair<int, int>>> adj(n);
        for (int i = 0; i < listaAristas.size(); ++i) {
            int u = listaAristas[i].first;
            int v = listaAristas[i].second;
            int peso = pesos[i];
            adj[u].emplace_back(v, peso);
            if (!dirigido) {
                adj[v].emplace_back(u, peso);
            }
        }
        cout << "\nLista de adyacencia:\n";
        printAdjList(adj);
        dijkstraList(adj, 0);
    } else {
        vector<vector<int>> matriz(n, vector<int>(n, INF));
        for (int i = 0; i < listaAristas.size(); ++i) {
            int u = listaAristas[i].first;
            int v = listaAristas[i].second;
            int peso = pesos[i];
            matriz[u][v] = peso;
            if (!dirigido) {
                matriz[v][u] = peso;
            }
        }
        cout << "\nMatriz de adyacencia:\n";
        printAdjMatrix(matriz);
        dijkstraMatrix(matriz, 0);
    }

    return 0;
}
