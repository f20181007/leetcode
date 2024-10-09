class Solution {
private:
    int n, u, v, time;
    std::vector<std::vector<int>> graph;
    std::vector<int> time_u, time_v, answer;

public:
    std::vector<int> timeTaken(std::vector<std::vector<int>>& edges) {
        n = edges.size() + 1; 
        graph.resize(n); time_u.assign(n, -1); time_v.assign(n, -1); answer.resize(n);

        for(const std::vector<int>& edge: edges) {
            graph[edge[0]].emplace_back(edge[1]);
            graph[edge[1]].emplace_back(edge[0]);
        }

        std::function<void(int, int, int, int&)> dfs = [&](int curr, int prev, int t, int& w) -> void {
            if(t > time) { time = t; w = curr; }

            for(const int& next: graph[curr]) {
                if(next == prev) continue;
                dfs(next, curr, (next & 1)? t + 1: t + 2, w);
            }
        };
        u = -1; time = -1; dfs(0, -1, 0, u); // dfs(1)
        v = -1; time = -1; dfs(u, -1, 0, v); // dfs(2)

        std::queue<std::array<int, 2>> qbfs;
        std::function<void(std::vector<int>&)> bfs = [&](std::vector<int>& time_w) -> void {
            while(!qbfs.empty()) {
                int sz = qbfs.size();
                for(int i = 0; i < sz; i++) {
                    int node = qbfs.front()[0];
                    int time = qbfs.front()[1];
                    for(const int& next: graph[node]) {
                        if(time_w[next] > -1) continue;
                        time_w[next] = (next & 1)? time + 1: time + 2;
                        qbfs.push({next, time_w[next]});
                    }
                    qbfs.pop();
                }
            }
        };
        time_u[u] = 0; qbfs.push({u, 0}); bfs(time_u); // bfs(1)
        time_v[v] = 0; qbfs.push({v, 0}); bfs(time_v); // bfs(2)

        for(int i = 0; i < n; i++) {
            int tu, tv;
            if((u ^ i) & 1) tu = (i & 1)? time_u[i] + 1: time_u[i] - 1;
            else tu = time_u[i];
            if((v ^ i) & 1) tv = (i & 1)? time_v[i] + 1: time_v[i] - 1;
            else tv = time_v[i];

            answer[i] = std::max(tu, tv);
        }
        return answer;
    }
};
