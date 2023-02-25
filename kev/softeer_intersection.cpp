#include <iostream>
#include <queue>
#include <vector>
#include <array>
#include <algorithm>
#include <limits.h>

using namespace std;

// A -> D
// B -> A
// C -> B
// D -> C

void init();

// 4개의 priority queue를 사용한다
// 시간 t를 증가시키며 iteration을 수행한다
// 입력으로 주어지는 (t, w) 튜플은 유일하다
// 입력은 차가 도로에 진입한 시각 순으로 주어진다
void solve();

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    init();

    solve();

    return 0;
}

struct Car
{
    int t;   // what time
    char w;  // where
    int idx; // 입력으로 주어진 순서
};

int N;
vector<Car> cars;
vector<int> answer;

void init()
{

    cin >> N;

    cars.resize(N);
    answer.resize(N);

    int idx = 0;
    for (auto &car : cars)
    {
        cin >> car.t >> car.w;
        car.idx = idx++;
    }
}

bool is_all_car_passed(const array<queue<Car>, 4>& roads)
{
    for (const auto &road : roads)
    {
        if (!road.empty())
            return false;
    }
    return true;
}

bool is_deadlock_occured(const array<queue<Car>, 4>& roads)
{

    bool is_some_roads_empty = false;
    for (const auto &road : roads)
    {
        is_some_roads_empty |= road.empty();
    }

    if (is_some_roads_empty)
        return false;

    // 모든 도로에 차가 있다.
    int prev_car_t = roads[0].front().t;
    for (int i = 1; i < roads.size(); ++i)
    {
        int cur_car_t = roads[i].front().t;
        if (prev_car_t == cur_car_t)
        {
            prev_car_t = cur_car_t;
            continue;
        }

        return false;
    }

    return true;
}

void solve()
{

    // 몇시에 어느 도로에 차가 들어왔다
    array<queue<Car>, 4> roads;

    for (const auto &car : cars)
    {
        int idx = car.w - 'A';
        roads[idx].push(car);
    }

    // for t = 0, all roads empty?, deadlock?
    // 특정 시점 t에 모든 도로에 자동차가 대기 중이라면 deadlock
    int timer = 0;
    bool deadlock = false;

    while (!is_all_car_passed(roads) 
    && !(deadlock = is_deadlock_occured(roads)))
    {
        int fastforward_to = INT_MAX;
        for(const auto& road: roads){

            if(road.empty()) continue;
            const Car& car = road.front();
            fastforward_to = min(car.t, fastforward_to);
        }
        timer = fastforward_to;

        // 오른쪽 도로를 본다
        // 차가 있냐? 있으면 못 가
        array<bool, 4> can_pass = {false, };
        for (int i = 0; i < 4; ++i)
        {
            
            queue<Car>& road = roads[i];

            if(road.empty() || road.front().t > timer) continue;
            
            queue<Car>& right_road = roads[(4 + i - 1) % 4];
            can_pass[i] = right_road.empty() 
                        || right_road.front().t > timer; // 도착을 안해있다
        }

        for(int i = 0; i < 4; ++i){

            if(roads[i].empty())
                continue;

            Car& car = roads[i].front();
            if(!can_pass[i]) {
                if(car.t <= timer) car.t = timer + 1;
                continue;
            }
            
            answer[car.idx] = timer;
            roads[i].pop(); // A 도로에서 뺀다
            
            if(roads[i].empty()) continue;
            
            Car& next = roads[i].front();
            next.t = next.t <= timer 
            ? timer + 1 
            : next.t;
        }
    }

    if (deadlock)
    {
        for(auto& road: roads){
            while(!road.empty()){
                answer[road.front().idx] = -1;
                road.pop();
            }
        }
    }

    for (const auto &e : answer)
    {
        cout << e << '\n';
    }
}