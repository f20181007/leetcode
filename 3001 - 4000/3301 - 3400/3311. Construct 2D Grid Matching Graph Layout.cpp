class Solution {
private:
    std::vector<std::vector<int32_t>> graph, grid;
    std::vector<int32_t> deg;

public:
    std::vector<std::vector<int32_t>> constructGridLayout(int32_t n, std::vector<std::vector<int32_t>>& edges) {
        graph.resize(n); deg.resize(n);
        
        for(const std::vector<int32_t>& edge: edges) {
            graph[edge[0]].push_back(edge[1]); deg[edge[0]]++;
            graph[edge[1]].push_back(edge[0]); deg[edge[1]]++;
        }
        std::vector<int32_t> :: iterator it;

        if((int32_t) edges.size() == n - 1) {
            assert(std::count(deg.begin(), deg.end(), 1) != 0);

            grid.resize(1);
            it = std::find(deg.begin(), deg.end(), 1);
            
            std::function<void(int32_t, int32_t)> dfs = [&](int32_t curr, int32_t prev) -> void {
                grid[0].push_back(curr);
                for(const int32_t& next: graph[curr]) {
                    if(next == prev) continue;
                    dfs(next, curr);
                }
            };
            dfs(std::distance(deg.begin(), it), -1);
            return grid;
        }

        std::vector<bool> visited(n, false);

        std::vector<int32_t> currRow;
        it = std::find(deg.begin(), deg.end(), 2); currRow.push_back(std::distance(deg.begin(), it));
        visited[currRow.back()] = true;

        std::function<int32_t(int32_t)> findNext = [&](int32_t curr) -> int32_t {
            int32_t val = -1, d = 5;
            for(const int32_t& i: graph[curr]) {
                if(!visited[i] and deg[i] < d) {
                    val = i; d = deg[i];
                }
            }
            return val;
        };

        while(true) {
            int32_t curr = currRow.back();
            int32_t next = findNext(curr);

            currRow.push_back(next); visited[next] = true;
            --deg[curr];
            --deg[next];
            if(deg[next] == 1) break;
        }
        
        int32_t rows = n / (int32_t) currRow.size(), cols = currRow.size();
        grid.resize(rows, std::vector<int32_t>(cols));

        grid[0] = currRow;
        for(int32_t i = 1; i < rows; ++i) {
            for(int32_t j = 0; j < cols; ++j) {
                int32_t curr = grid[i - 1][j];
                int32_t next = findNext(curr);

                grid[i][j] = next; visited[next] = true;
                --deg[curr];
                --deg[next];
            }
        }
        return grid;
    }
};
