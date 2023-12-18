#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
using namespace std;
// Функция для создания случайного взвешенного графа
vector<vector<int>> generateRandomWeightedGraph(int n) {
    vector<vector<int>> graph(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (rand() % 2 == 1) {
                int weight = rand() % 10 + 1; // случайный вес от 1 до 10
                graph[i][j] = weight;
                graph[j][i] = weight;
            }
        }
    }
    return graph;
}
// Функция для вывода матрицы смежности графа
void printGraphMatrix(const vector<vector<int>>& graph) {
    for (const auto& row : graph) {
        for (int weight : row) {
            cout << weight << ' ';
        }
        cout << '\n';
    }
}
// Процедура поиска расстояний в неориентированном взвешенном графе
void bfsDistance(const vector<vector<int>>& graph, int start) {
    int n = graph.size();
    vector<int> distance(n, -1);
    queue<int> q;
    distance[start] = 0;
    q.push(start);
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        for (int neighbor = 0; neighbor < n; ++neighbor) {
            if (graph[current][neighbor] > 0 && (distance[neighbor] == -1 || distance[neighbor] > distance[current] + graph[current][neighbor])) {
                distance[neighbor] = distance[current] + graph[current][neighbor];
                q.push(neighbor);
            }
        }
    }
    // Вывод расстояний от start до остальных вершин
    cout << "Расстояние от вершины " << start << ":\n";
    for (int i = 0; i < n; ++i) {
        cout << "До вершины " << i << ": " << distance[i] << '\n';
    }
}
int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(0)); // Инициализация генератора случайных чисел
    // Создание графа и вывод его матрицы смежности
    int size;
    cout << "Введите размер графа: ";
    cin >> size; 
    int n = size; // Размер графа 
if (size  <= 0) {
        cout << "Недопустимый размер графа";
        return 0;
    }
    vector<vector<int>> randomWeightedGraph = generateRandomWeightedGraph(n);
    cout << "Граф матрицы:\n";
    printGraphMatrix(randomWeightedGraph);
    // Выбор случайной вершины в качестве стартовой для поиска расстояний
    int startVertex;
    cout << "Стартовая вершина: ";
    cin >> startVertex;
    if (startVertex < 0 || startVertex >= size ) {
        cout << "Нет такой вершины";
        return 0;
    }
    cout << "\nВыбор стартовой вершины для поиска расстояния: " << startVertex << "\n\n";
    // Поиск расстояний в графе и вывод результатов
    bfsDistance(randomWeightedGraph, startVertex);
    return 0;
}