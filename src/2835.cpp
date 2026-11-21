#include <bits/stdc++.h>

constexpr int DAY_IN_SEC = 86400;
constexpr int TREE_SIZE = DAY_IN_SEC * 4 + 1;
int n;

struct Node {
    int start, end; // 단위는 초
    long long sum; // [start, end] 동안 시청된 초의 합
    long long lazy; // 업데이트 미뤄진 인구 수
} tree[TREE_SIZE];

inline void FastIO()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
}

void update_lazy(int start, int end, int node)
{
    tree[node].sum += (end - start + 1) * tree[node].lazy;
    
    if (start != end) {
        int left_child = node * 2;
        int right_child = node * 2 + 1;
        
        tree[left_child].lazy += tree[node].lazy;
        tree[right_child].lazy += tree[node].lazy;
    }

    tree[node].lazy = 0;
}

long long query(int start, int end, int left, int right, int node)
{
    if (start > end) return 0;
    update_lazy(start, end, node);

    // 완벽히 벗어남
    if (right < start || end < left) {
        return 0;
    }

    // 완벽히 겹침
    if (left <= start && end <= right) {
        return tree[node].sum;
    }

    // 일부가 겹침
    int mid = (start + end) / 2;
    return query(start, mid, left, right, node * 2) + 
        query(mid + 1, end, left, right, node * 2 + 1);
}

long long query(int left, int right)
{ return query(0, DAY_IN_SEC - 1, left, right, 1); }

void update_range(int start, int end, int left, int right, int node)
{
    if (start > end) return;
    update_lazy(start, end, node);

    // 완벽히 벗어남
    if (right < start || end < left) {
        return;
    }

    // 완벽히 겹침
    if (left <= start && end <= right) {
        tree[node].lazy += 1;
        update_lazy(left, right, node);
        return;
    }

    // 일부가 겹침
    int mid = (start + end) / 2;

    // left child
    update_range(start, mid, left, right, node * 2);

    // right child
    update_range(mid + 1, end, left, right, node * 2 + 1);
}

void update_range(int left, int right)
{ update_range(0, DAY_IN_SEC - 1, left, right, 1); }

std::pair<int, int> ParseLine(std::string const &line)
{
    int h = std::stoi(line.substr(0, 2));
    int m = std::stoi(line.substr(3, 2));
    int s = std::stoi(line.substr(6, 2));
    int beginning_time = h * 60 * 60 + m * 60 + s;

    h = std::stoi(line.substr(11, 2));
    m = std::stoi(line.substr(14, 2));
    s = std::stoi(line.substr(17, 2));
    int finishing_time = h * 60 * 60 + m * 60 + s;

    return { beginning_time, finishing_time };
}

void Input()
{
    // UPDATE
    std::cin >> n;
    std::cin.ignore();
    std::string line;

    for (int i = 0; i < n; ++i) {
        std::getline(std::cin, line);
        auto const [s, e] = ParseLine(line);

        if (s <= e) {
            update_range(s, e);
        } else {
            // 자정 넘겨서 시청
            update_range(s, DAY_IN_SEC - 1);
            update_range(0, e);
        }
    } // END OF UPDATE

    // QUERY
    int m;
    std::cin >> m;
    std::cin.ignore();

    for (int i = 0; i < m; ++i) {
        std::getline(std::cin, line);
        auto const [s, e] = ParseLine(line);

        long double ans;
        if (s <= e) ans = static_cast<long double>(query(s, e)) / (e - s + 1);
        else ans = (static_cast<long double>(query(s, DAY_IN_SEC - 1)) + static_cast<long double>(query(0, e))) / static_cast<long double>(e - s + 1);
        std::cout << ans << '\n';
    }
    
    // END OF QUERY
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