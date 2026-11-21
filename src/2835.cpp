#include <bits/stdc++.h>

constexpr int DAY_IN_SEC = 86400;
constexpr int TREE_SIZE = DAY_IN_SEC * 4 + 1;
int n;

struct Node {
    int start, end; // 단위는 초
    long long sec; // [start, end] 동안 시청된 초
} tree[TREE_SIZE];

inline void FastIO()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
}

void update_range(int start, int end, int left, int right, int node)
{
    if (left <= start && end <= right) {
        
    }
}

void update_range(int start, int end)
{ update_range(start, end, 0, DAY_IN_SEC, 1); }

void Input()
{
    std::cin >> n;
    std::string line;

    for (int i = 0; i < n; ++i) {
        std::cin >> line;

        int h = std::stoi(line.substr(0, 2));
        int m = std::stoi(line.substr(3, 2));
        int s = std::stoi(line.substr(6, 2));
        int beginning_time = h * 60 * 60 + m * 60 + s;

        h = std::stoi(line.substr(11, 2));
        m = std::stoi(line.substr(14, 2));
        s = std::stoi(line.substr(17, 2));
        int finishing_time = h * 60 * 60 + m * 60 + s;
    }
}

int main() 
{
    FastIO();
    Input();
}

// grinding scores!! (lazyprop)

// 86400초 동안 TV 보는 인구 수 조사
// 트리는 다음을 포함해야 함:
// - 노드가 가리키는 시간 내 범위 동안 시청한 총 시간
//    - 예로 들어 노드가 1시부터 2시까지를 가리킬 때
//      1:00:00부터 1:00:01까지 시청했으면 2초 추가
//        - 즉 범위는 [시작 시간, 종료 시간]으로 닫힌 구간임

// 예상 트리 크기: 86400 * 4 * 8(sizeof(long long)) bytes ≈ 2.7648mb
// 메모리 걱정은 안 해도 될 듯

// 예제 입력 1:
// 5명의 시청 기록 입력
// 0초부터 1초 = 2s
// 1초부터 3초 = 3s
// 0초부터 2초 = 3s
// 5초부터 9초 = 5s
// 6초부터 6초 = 1s

// 예제 입력 1의 첫 번째 출력
// 0초부터 3초동안 인기도: 인구수 = 3명, 시간 = 8초. 
// 즉, 2를 출력.