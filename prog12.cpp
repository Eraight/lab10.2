#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
using namespace std;
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
// Процедура поиска расстояний в ориентированном взвешенном графе
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
    vector<vector<int>> randomWeightedDirectedGraph = generateRandomWeightedDirectedGraph(n);
    cout << "Ориентированный граф:\n";
    for (const auto& row : randomWeightedDirectedGraph) {
        for (int weight : row) {
            cout << weight << ' ';
        }
        cout << '\n';
    }
    // Выбор случайной вершины в качестве стартовой для поиска расстояний
    int startVertex;
    cout << "Стартовая вершина: ";
    cin >> startVertex;
    if (startVertex < 0 || startVertex >= size ) {
        cout << "Нет такой вершины";
        return 0;
    }
    cout << "\nВершина, от которой ищем расстояние: " << startVertex << "\n\n";
    // Поиск расстояний в графе и вывод результатов
    bfsDistance(randomWeightedDirectedGraph, startVertex);
    return 0;
}
