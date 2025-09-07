// Função auxiliar para criar a lista de adjacência
#include <stdlib.h>
#include <string.h>

int min(int a, int b) { return a < b ? a : b; }

int findShortestCycle(int n, int** edges, int edgesSize, int* edgesColSize) {
	int** adj = (int**)malloc(n * sizeof(int*));
	int* adjSize = (int*)calloc(n, sizeof(int));
	int* adjCap = (int*)calloc(n, sizeof(int));
	for (int i = 0; i < n; ++i) {
		adjCap[i] = 4;
		adj[i] = (int*)malloc(adjCap[i] * sizeof(int));
	}
	for (int i = 0; i < edgesSize; ++i) {
		int u = edges[i][0], v = edges[i][1];
		if (adjSize[u] == adjCap[u]) {
			adjCap[u] *= 2;
			adj[u] = (int*)realloc(adj[u], adjCap[u] * sizeof(int));
		}
		if (adjSize[v] == adjCap[v]) {
			adjCap[v] *= 2;
			adj[v] = (int*)realloc(adj[v], adjCap[v] * sizeof(int));
		}
		adj[u][adjSize[u]++] = v;
		adj[v][adjSize[v]++] = u;
	}

	int shortest = n + 1;
	int* dist = (int*)malloc(n * sizeof(int));
	int* parent = (int*)malloc(n * sizeof(int));
	int* queue = (int*)malloc(n * sizeof(int));

	for (int start = 0; start < n; ++start) {
		for (int i = 0; i < n; ++i) {
			dist[i] = -1;
			parent[i] = -1;
		}
		int front = 0, back = 0;
		dist[start] = 0;
		queue[back++] = start;
		while (front < back) {
			int u = queue[front++];
			for (int k = 0; k < adjSize[u]; ++k) {
				int v = adj[u][k];
				if (dist[v] == -1) {
					dist[v] = dist[u] + 1;
					parent[v] = u;
					queue[back++] = v;
				} else if (parent[u] != v) {
					// Encontrou ciclo
					shortest = min(shortest, dist[u] + dist[v] + 1);
				}
			}
		}
	}

	for (int i = 0; i < n; ++i) free(adj[i]);
	free(adj); free(adjSize); free(adjCap);
	free(dist); free(parent); free(queue);

	return (shortest == n + 1) ? -1 : shortest;
}