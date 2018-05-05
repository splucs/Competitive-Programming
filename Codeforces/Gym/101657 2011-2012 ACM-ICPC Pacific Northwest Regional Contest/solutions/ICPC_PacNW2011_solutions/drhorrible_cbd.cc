#include <iostream>
#include <cassert>
#include <cstdlib>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

typedef vector<string> VS;
typedef vector<VS> VVS;
typedef vector<VVS> VVVS;

int dr[] = {-1, -1, 0, 0, 1, 1,  0,  0};
int dc[] = { 0,  0, 1, 1, 0, 0, -1, -1};
string mapping = "FEHGBADC";

int main() {
    int b = 0;
    int h, w;
    string s;
    while (getline(cin, s)) {
        
        // read iput
        istringstream iss(s);
        iss >> h >> w;
        if (h == 0 && w == 0) break;

        if (b > 0) cout << endl;
        cout << "Board " << ++b << ":" << endl;
        VVVS board(h, VVS(w));
        while (getline(cin, s)) {
            if (s == "0") break;
            istringstream iss(s);
            int num;
            iss >> num;
            if (num == 0) break;
            VS &square = board[(num-1) / w][(num-1) % w];
            string description;
            while (iss >> description)
                square.push_back(description);
        }

        // process queries
        string query;
        getline(cin, s);
        istringstream iss2(s);
        while (iss2 >> query) {
            cout << query;

            char conn = query[query.length() - 1];
            query = query.substr(0, query.length() - 1);
            int num = atoi(query.c_str());
            int r = (num-1) / w;
            int c = (num-1) % w;

            assert(r == 0 || r == h-1 || c == 0 || c == w-1);
            while (true) {
                // follow wire in current square
                VS &square = board[r][c];
                char nconn = '~';
                for (size_t i = 0; i < square.size(); ++i) {
                    if (square[i][0] == conn) {
                        nconn = square[i][1];
                    } else if (square[i][1] == conn) {
                        nconn = square[i][0];
                    }
                }
                assert(nconn != '~');
                conn = nconn;

                // go to next square
                int nr = r + dr[conn - 'A'];
                int nc = c + dc[conn - 'A'];
                nconn = mapping[conn - 'A'];
                
                if (nr < 0 || nr >= h || nc < 0 || nc >= w) break;
                r = nr;
                c = nc;
                conn = nconn;
            }
            
            cout << " is connected to " << (r*w+c)+1 << conn << endl;
        }

        // skip blank line
        getline(cin, s);
    }
    return 0;
}
