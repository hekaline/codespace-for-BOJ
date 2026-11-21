#include <bits/stdc++.h>

using namespace std;

int n;

// dp[i][j][0]: 가로, [1]: 대각선, [2]: 세로
long long dp[32][32][3] = { 0 };
bool is_wall[32][32];

bool IsValid(int i, int j) 
{ return 0 <= i && i < n && 0 <= j && j < n; }

bool IsEnterable(int i, int j)
{ return IsValid(i, j) && !is_wall[i][j]; }

int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    dp[0][1][0] = 1;

    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int space_state;
            std::cin >> space_state;

            is_wall[i][j] = space_state;
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (!IsEnterable(i, j)) continue;

            // 왼쪽에서 여기로 진입 가능 시, 이전 위치에서 대각선 또는 가로였을 것
            if (IsEnterable(i, j - 1)) {
                dp[i][j][0] += dp[i][j - 1][0] + dp[i][j - 1][1];
            }
            // 위에서 여기로 진입 가능 시, 이전 위치에서 대각선 또는 세로였을 것
            if (IsEnterable(i - 1, j)) {
                dp[i][j][2] += dp[i - 1][j][1] + dp[i - 1][j][2];
            }
            // 왼쪽 위에서 여기로 진입 가능 시, 이전 위치에서 가로, 대각선 또는 세로였을 것
            if (IsEnterable(i - 1, j - 1) &&
                IsEnterable(i - 1, j) &&
                IsEnterable(i, j - 1)) {
                dp[i][j][1] += 
                    dp[i - 1][j - 1][0] +
                    dp[i - 1][j - 1][1] +
                    dp[i - 1][j - 1][2];
            }
        }
    }

    std::cout << dp[n - 1][n - 1][0] + dp[n - 1][n - 1][1] + dp[n - 1][n - 1][2];
}

// 아 젠장 dp구나