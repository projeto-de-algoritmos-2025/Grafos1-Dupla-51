#include <stdbool.h>
#include <stdlib.h>

bool isBipartite(int** graph, int graphSize, int* graphColSize) {
    int* color = (int*)malloc(graphSize * sizeof(int));
    for (int i = 0; i < graphSize; ++i) color[i] = -1;
    int* queue = (int*)malloc(graphSize * sizeof(int));
    for (int start = 0; start < graphSize; ++start) {
        if (color[start] != -1) continue;
        int front = 0, back = 0;
        queue[back++] = start;
        color[start] = 0;
        while (front < back) {
            int u = queue[front++];
            for (int i = 0; i < graphColSize[u]; ++i) {
                int v = graph[u][i];
                if (color[v] == -1) {
                    color[v] = 1 - color[u];
                    queue[back++] = v;
                } else if (color[v] == color[u]) {
                    free(color); free(queue);
                    return false;
                }
            }
        }
    }
    free(color); free(queue);
    return true;
}
