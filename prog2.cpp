#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;
const int INF = INT_MAX;
// Функция для создания случайного ориентированного взвешенного графа
vector<vector<int>> generateRandomWeightedDirectedGraph(int n) {
    vector<vector<int>> graph(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j && rand() % 2 == 1) {
                int weight = rand() % 10 + 1; // случайный вес от 1 до 10
                graph[i][j] = weight;
            }
        }
    }
    return graph;
}
// Функция для нахождения радиуса, диаметра и центральных/периферийных вершин
void findRadiusDiameter(const vector<vector<int>>& graph, int& radius, int& diameter,
    vector<int>& centralVertices, vector<int>& peripheralVertices) {
    int n = graph.size();
    radius = INF;
    diameter = 0;
    for (int startVertex = 0; startVertex < n; ++startVertex) {
        vector<int> distance(n, INF);
        queue<int> q;
        distance[startVertex] = 0;
        q.push(startVertex);
        while (!q.empty()) {
            int current = q.front();
            q.pop();
            for (int neighbor = 0; neighbor < n; ++neighbor) {
                if (graph[current][neighbor] > 0 && distance[neighbor] == INF) {
                    distance[neighbor] = distance[current] + graph[current][neighbor];
                    q.push(neighbor);
                }
            }
        }
        int maxDistance = *max_element(distance.begin(), distance.end());
        if (maxDistance < radius) {
            radius = maxDistance;
            centralVertices = { startVertex };
        }
        else if (maxDistance == radius) {
            centralVertices.push_back(startVertex);
        }
        diameter = max(diameter, maxDistance);
        for (int i = 0; i < n; ++i) {
            if (distance[i] == radius) {
                peripheralVertices.push_back(i);
            }
        }
    }
    radius = radius == INF ? 0 : radius;
    diameter = diameter == INF ? 0 : diameter;
}
int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(0)); // Инициализация генератора случайных чисел
    int size;
    cout << "Введите размер графа: ";
    cin >> size;
    int n = size; // Размер графа 
    if (size  <= 0) {
        cout << "Недопустимый размер графа";
        return 0;
    }
    vector<vector<int>> randomWeightedDirectedGraph = generateRandomWeightedDirectedGraph(n);
    cout << "Матрица ориентированного графа: \n";
    for (const auto& row : randomWeightedDirectedGraph) {
        for (int weight : row) {
            cout << weight << ' ';
        }
        cout << '\n';
    }
    int radius, diameter;
    vector<int> centralVertices, peripheralVertices;
    // Находим радиус, диаметр, центральные и периферийные вершины
    findRadiusDiameter(randomWeightedDirectedGraph, radius, diameter, centralVertices, peripheralVertices);
    cout << "\nРадиус: " << radius << "\n";
    cout << "Диаметр: " << diameter << "\n";
    cout << "Центральная вершина: ";
    for (int vertex : centralVertices) {
        cout << vertex << " ";
    }
    cout << "\n";
    cout << "Переферийные вершины: ";
    for (int vertex : peripheralVertices) {
        cout << vertex << " ";
    }
    cout << "\n";
    return 0;
} 
