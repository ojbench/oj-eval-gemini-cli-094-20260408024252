#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int m, n;
    if (!(cin >> m >> n)) return 0;

    vector<vector<int>> compressed(m, vector<int>(n));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> compressed[i][j];
        }
    }

    int out_m = 3 * m;
    int out_n = 3 * n;
    vector<vector<int>> restored(out_m, vector<int>(out_n));

    for (int r = 0; r < out_m; ++r) {
        for (int c = 0; c < out_n; ++c) {
            if (r % 3 == 1 && c % 3 == 1) {
                restored[r][c] = compressed[r / 3][c / 3];
            } else {
                int a_count = 0;
                int b_count = 0;
                int a_sum = 0;
                int b_sum = 0;

                int start_i = max(0, r / 3 - 1);
                int end_i = min(m - 1, r / 3 + 1);
                int start_j = max(0, c / 3 - 1);
                int end_j = min(n - 1, c / 3 + 1);

                for (int i = start_i; i <= end_i; ++i) {
                    for (int j = start_j; j <= end_j; ++j) {
                        int cr = 3 * i + 1;
                        int cc = 3 * j + 1;
                        int dist = abs(r - cr) + abs(c - cc);
                        if (dist == 1) {
                            a_sum += compressed[i][j];
                            a_count++;
                        } else if (dist == 2) {
                            b_sum += compressed[i][j];
                            b_count++;
                        }
                    }
                }

                if (a_count > 0 && b_count == 0) {
                    restored[r][c] = floor((double)a_sum / a_count);
                } else if (a_count == 0 && b_count > 0) {
                    restored[r][c] = floor((double)b_sum / b_count);
                } else if (a_count > 0 && b_count > 0) {
                    double a_avg = (double)a_sum / a_count;
                    double b_avg = (double)b_sum / b_count;
                    restored[r][c] = floor(a_avg * 0.8 + b_avg * 0.2);
                }
            }
        }
    }

    for (int r = 0; r < out_m; ++r) {
        for (int c = 0; c < out_n; ++c) {
            cout << restored[r][c] << (c == out_n - 1 ? "" : " ");
        }
        cout << "\n";
    }

    return 0;
}
