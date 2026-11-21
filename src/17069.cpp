#include <bits/stdc++.h>

using PII = std::pair<int, int>;

// [horizontal, diagonal, vertical]
std::vector<std::vector<std::vector<int>>> method_cnt;
std::vector<std::vector<std::bitset<1>>> is_wall;

int n;

inline void GetInput()
{
    std::cin >> n;
    is_wall.resize(n);
    method_cnt.resize(n);

    for (int i = 0; i < n; ++i) {
        is_wall[i].resize(n);
        method_cnt[i].resize(n);
        for (int j = 0; j < n; ++j) {
            method_cnt[i][j].resize(3);
            int space_state;
            std::cin >> space_state;

            is_wall[i][j] = static_cast<std::bitset<1>>(
                space_state);
        }
    }
}

bool IsValid(int i, int j)
{
    return 0 <= i && i < n && 0 <= j && j < n;
}

bool IsEnterable(int i, int j)
{
    return IsValid(i, j) && is_wall[i][j] == false;
}

int main() 
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    

    GetInput();
    method_cnt[0][1][0] = 1;

    std::queue<std::pair<PII, PII>> q; // <dest, from>
    q.push({{0, 1}, {0, 0}});

    std::pair<int, int> offsets[] = {{-1, 0}, {0, -1}, {-1, -1}};
    while (!q.empty()) {
        // 현 좌표 가져오기
        auto [dest, from] = q.front(); q.pop();
        auto [curr_y, curr_x] = dest;
        auto [prev_y, prev_x] = from;

        // 유효한지, 벽인지 확인
        if (!IsEnterable(curr_y, curr_x)) continue;

        // 전 위치에서 정보 가져오기
        int idx;
        {
            bool is_horizontal = curr_x != prev_x;
            bool is_vertical = curr_y != prev_y;
            bool is_diagonal = is_horizontal && is_vertical;

            
            if (is_diagonal) idx = 1;
            else if (is_horizontal) idx = 0;
            else idx = 2;
        }

        method_cnt[curr_y][curr_x][idx] += 
            method_cnt[prev_y][prev_x][idx];

        for (auto const&[oy, ox] : offsets) {
            int next_y = curr_y - oy;
            int next_x = curr_x - ox;

            if (!IsEnterable(next_y, next_x)) continue;

            bool is_diagonal = oy == ox;
            if (is_diagonal) {
                if (!IsEnterable(curr_y, next_x) ||
                    !IsEnterable(next_y, curr_x)) continue;
            }

            q.push({{next_y, next_x}, dest});
        }
    }

    long long ans {0};
    for (int i = 0; i < 3; ++i)
        ans += method_cnt[n - 1][n - 1][i];

    std::cout << ans;
}

// 문제 해석하기
// -- 파이프의 끝 상태 (위치, 각도)만 알면 된다. 
//   -- 문제에서 "꼭 빈칸이어야 하는 곳"을 유의
//   -- 각도에는 총 세 가지가 있다 (0도, 45도, 90도)
//   -- 이를 따로 보관해야 다음 밀기 동작들을 예측 및 수행할 수 있다.
//   -- 
// -- 그래프 문제