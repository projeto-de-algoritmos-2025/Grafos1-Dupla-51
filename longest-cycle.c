int longestCycle(int* edges, int n) {
    int* visited = (int*)calloc(n, sizeof(int)); // 0: não visitado, 1: visitado global
    int maxLen = -1;
    for (int i = 0; i < n; ++i) {
        if (visited[i]) continue;
        int* pos = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; ++j) pos[j] = -1;
        int curr = i, step = 0;
        while (curr != -1 && !visited[curr]) {
            pos[curr] = step++;
            visited[curr] = 1;
            curr = edges[curr];
            if (curr != -1 && pos[curr] != -1) {
                int len = step - pos[curr];
                if (len > maxLen) maxLen = len;
                break;
            }
        }
        free(pos);
    }
    free(visited);
    return maxLen;
}
