#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include <locale.h>

#define INF INT_MAX

// Функция для создания случайного графа
int** generateRandomGraph(int n, int weighted, int directed) {
    int** graph = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; ++i) {
        graph[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; ++j) {
            graph[i][j] = 0;
            if (i != j && (directed || i < j) && (rand() % 2 == 1 || !weighted)) {
                int weight = (weighted) ? (rand() % 10 + 1) : (rand() % 2);
                graph[i][j] = weight;
                if (!directed) {
                    graph[j][i] = weight;
                }
            }
        }
    }
    return graph;
}

// Функция для вывода матрицы смежности графа
void printGraphMatrix(int** graph, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
}

// Процедура поиска расстояний в графе
void bfsDistance(int** graph, int n, int start) {
    int* distance = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i) {
        distance[i] = INF;
    }

    int* queue = (int*)malloc(n * sizeof(int));
    int front = 0, rear = 0;

    distance[start] = 0;
    queue[rear++] = start;

    while (front != rear) {
        int current = queue[front++];
        for (int neighbor = 0; neighbor < n; ++neighbor) {
            if (graph[current][neighbor] > 0 && (distance[neighbor] == INF || distance[neighbor] > distance[current] +
                graph[current][neighbor])) {
                distance[neighbor] = distance[current] + graph[current][neighbor];
                queue[rear++] = neighbor;
            }
        }
    }

    // Вывод расстояний от start до остальных вершин
    printf("Дистанция от вершины %d:\n", start);
    for (int i = 0; i < n; ++i) {
        printf("До вершины %d: %d\n", i, distance[i]);
    }

    free(distance);
    free(queue);
}
int contains(int* array, int size, int value) {
    for (int i = 0; i < size; ++i) {
        if (array[i] == value) {
            return 1;
        }
    }
    return 0;
}
// Функция для нахождения радиуса, диаметра и центральных/периферийных вершин
void findRadiusDiameter(int** graph, int n, int* radius, int* diameter, int* centralVertices, int* centralVerticesCount, int* peripheralVertices, int* peripheralVerticesCount) {
    *radius = 0;
    *diameter = 0;
    int* distance = (int*)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) {
            distance[i] = 0;
            for (int j = 0; j < n; j++) {
                distance[i] = (graph[i][j] >= distance[i]) ? graph[i][j] : distance[i];
            }
        }
        /*distance[startVertex] = 0;
        queue[rear++] = startVertex;

        while (front != rear) {
            int current = queue[front++];
            for (int neighbor = 0; neighbor < n; ++neighbor) {
                if (graph[current][neighbor] > 0 && distance[neighbor] == INF) {
                    distance[neighbor] = distance[current] + graph[current][neighbor];
                    queue[rear++] = neighbor;
                }
            }
        }*/

        // Используем переменную maxDiameter для отслеживания максимального диаметра
        int maxDiameter = 0, minDiameter = INF;

        // Находим максимальное расстояние внутри distance
        for (int i = 0; i < n; ++i) {
            if (distance[i] != INF && distance[i] != 0) {
                maxDiameter = (maxDiameter > distance[i]) ? maxDiameter : distance[i];
                minDiameter = (minDiameter <= distance[i]) ? minDiameter : distance[i];
            }
        }

        // После завершения внутреннего цикла обновляем diameter
        *diameter = maxDiameter;
        *radius = *radius == INF ? 0 : minDiameter;

        // Находим центральные вершины
        for (int i = 0; i < n; ++i) {
            if (distance[i] == minDiameter && distance[i] != 0) {
                centralVertices[(*centralVerticesCount)++] = i;
            }
            if (distance[i] == maxDiameter && distance[i] != 0) {
                peripheralVertices[(*peripheralVerticesCount)++] = i;
            }
        }
    }



int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "RUS");
    srand(time(0));

    if (argc != 4) {
        printf("Используйте: %s <graph_type> <directed> <size>\n", argv[0]);
        printf("Тип графа: weighted unweighted\n");
        printf("Тип: 0 (undirected) or 1 (directed)\n");
        return 1;
    }

    char* graphType = argv[1];
    int weighted = (strcmp(graphType, "weighted") == 0) ? 1 : 0;
    int directed = atoi(argv[2]) == 1 ? 1 : 0;
    int n = atoi(argv[3]);

    int** randomGraph = generateRandomGraph(n, weighted, 1);

    printf("Матрица графа:\n");
    printGraphMatrix(randomGraph, n);

    int radius, diameter;
    int* centralVertices = (int*)malloc(sizeof(int) * n);
    int* peripheralVertices = (int*)malloc(sizeof(int) * n);
    int centralVerticesCount = 0;
    int peripheralVerticesCount = 0;

    // Находим радиус, диаметр, центральные и пери  ферийные вершины
    findRadiusDiameter(randomGraph, n, &radius, &diameter, centralVertices, &centralVerticesCount, peripheralVertices,
        &peripheralVerticesCount);

    if (n <= 1 || radius == INF || radius == 0) {
        printf("\nРадиус: Нет, ай ай ай\n");
        printf("Диаметр: Нет, ой ой ой\n");
        printf("Центральные вершины: \n");
        printf("Периферийные вершины: \n");
        return 0;
    }
    printf("\nРадиус: %d\n", radius == INF ? 0 : radius);
    printf("Диаметр: %d\n", diameter == INF ? 0 : diameter);

    printf("Центральные вершины: ");
    for (int i = 0; i < centralVerticesCount; ++i) {
        printf("%d ", centralVertices[i]);
    }
    printf("\n");

    printf("Периферийные вершины: ");
    for (int i = 0; i < peripheralVerticesCount; ++i) {
        printf("%d ", peripheralVertices[i]);
    }
    printf("\n");

    // Освобождаем выделенную память
    for (int i = 0; i < n; ++i) {
        free(randomGraph[i]);
    }
    free(randomGraph);

    return 0;
}
