class Solution {
private:
    int di[4] = {0, 1, 0, -1};
    int dj[4] = {1, 0, -1, 0};
    vector<vector<int>> target = {
        {1, 2, 3},
        {4, 5, 0}
    };

    int encode(vector<vector<int>>& board) {
        vector<int> pos(6);
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 3; j++) {
                pos[board[i][j]] = 3*i+j;
            }
        }
        int state = 0;
        for (int i = 5; i >= 0; i--) {
            state = (i+1)*state + pos[i];
            for (int j = i-1; j >= 0; j--) {
                if (pos[j] > pos[i]) {
                    pos[j]--;
                }
            }
        }
        return state;
    }
    vector<vector<int>> decode(int state) {
        vector<int> boardArr;
        for (int i = 0; i < 6; i++) {
            int insertAt = state%(i+1);
            state /= (i+1);
            boardArr.insert(boardArr.begin() + insertAt, i);
        }
        vector<vector<int>> board(2, vector<int>(3));
        for (int t = 0; t < 6; t++) {
            int i = t/3, j = t%3;
            board[i][j] = boardArr[t];
        }
        return board;
    }
    vector<int> findNeighbors(int state) {
        vector<vector<int>> board = decode(state);
        
        int zi, zj;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == 0) {
                    zi = i, zj = j;
                }
            }
        }

        vector<int> neighbors;
        for (int d = 0; d < 4; d++) {
            int i = zi + di[d], j = zj + dj[d];
            if (i < 0 || j < 0 || i >= 2 || j >= 3) {
                continue;
            }
            swap(board[zi][zj], board[i][j]);
            neighbors.push_back(encode(board));
            swap(board[zi][zj], board[i][j]);
        }
        return neighbors;
    }
public:
    int slidingPuzzle(vector<vector<int>>& board) {
        queue<int> q;
        vector<int> dist(720, -1);
        int s = encode(board);
        int t = encode(target);
        dist[s] = 0;
        q.push(s);

        while (!q.empty()) {
            int u = q.front();
            if (u == t) {
                return dist[u];
            }
            q.pop();
            for (int v : findNeighbors(u)) {
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }
        return -1;
    }
};
