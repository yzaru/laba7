#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <locale.h>  // Добавили библиотеку для установки локали

#define N 5  // Размер графа

// Генерация матрицы смежности
void generateAdjacencyMatrix(int graph[N][N]) {
    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        for (int j = i; j < N; j++) {
            if (i == j) {
                graph[i][j] = 0;
            }
            else {
                int edge = rand() % 2;
                graph[i][j] = edge;
                graph[j][i] = edge;
            }
        }
    }
}

// Печать матрицы смежности
void printMatrix(int graph[N][N]) {
    printf("Матрица смежности:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
}

// Рекурсивный обход в глубину по матрице смежности
void DFS_Matrix_Recursive(int v, bool visited[], int graph[N][N]) {
    visited[v] = true;
    printf("%d ", v);

    for (int i = 0; i < N; i++) {
        if (graph[v][i] && !visited[i]) {
            DFS_Matrix_Recursive(i, visited, graph);
        }
    }
}

// Нерекурсивный обход в глубину по матрице смежности (с использованием стека)
void DFS_Matrix_NonRecursive(int graph[N][N], int start) {
    bool visited[N] = { false };
    int stack[N];
    int top = -1;

    stack[++top] = start;

    while (top >= 0) {
        int v = stack[top--];

        if (!visited[v]) {
            visited[v] = true;
            printf("%d ", v);
        }

        for (int i = N - 1; i >= 0; i--) {  // Добавляем в стек вершины в обратном порядке
            if (graph[v][i] && !visited[i]) {
                stack[++top] = i;
            }
        }
    }
}

// Узел для списка смежности
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// Создание нового узла
Node* createNode(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// Добавление ребра в список смежности
void addEdge(Node* adjList[], int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = adjList[src];
    adjList[src] = newNode;

    newNode = createNode(src);
    newNode->next = adjList[dest];
    adjList[dest] = newNode;
}

// Печать списка смежности
void printAdjList(Node* adjList[]) {
    printf("Список смежности:\n");
    for (int i = 0; i < N; i++) {
        printf("%d: ", i);
        Node* temp = adjList[i];
        while (temp) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

// Рекурсивный обход в глубину по спискам смежности
void DFS_List(int v, bool visited[], Node* adjList[]) {
    visited[v] = true;
    printf("%d ", v);

    Node* temp = adjList[v];
    while (temp) {
        int adjVertex = temp->vertex;
        if (!visited[adjVertex]) {
            DFS_List(adjVertex, visited, adjList);
        }
        temp = temp->next;
    }
}

// Освобождение памяти для списка смежности
void freeGraph(Node* adjList[]) {
    for (int i = 0; i < N; i++) {
        Node* temp = adjList[i];
        while (temp) {
            Node* next = temp->next;
            free(temp);
            temp = next;
        }
    }
}

int main() {
    setlocale(LC_ALL, "");  // Установили локаль для поддержки русского языка

    int graph[N][N];
    generateAdjacencyMatrix(graph);
    printMatrix(graph);

    // Рекурсивный обход в глубину по матрице смежности
    bool visited[N] = { false };
    printf("Рекурсивный обход в глубину (матрица смежности): ");
    DFS_Matrix_Recursive(0, visited, graph);
    printf("\n");

    // Нерекурсивный обход в глубину по матрице смежности
    printf("Нерекурсивный обход в глубину (матрица смежности): ");
    DFS_Matrix_NonRecursive(graph, 0);
    printf("\n");

    // Создание списка смежности
    Node* adjList[N] = { NULL };
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (graph[i][j] == 1) {
                addEdge(adjList, i, j);
            }
        }
    }

    printAdjList(adjList);

    // Обход в глубину по спискам смежности
    for (int i = 0; i < N; i++) visited[i] = false;  // Сброс массива visited
    printf("Рекурсивный обход в глубину (список смежности): ");
    DFS_List(0, visited, adjList);
    printf("\n");

    // Освобождение памяти
    freeGraph(adjList);

    return 0;
}

