#include <iostream>
#include <vector>

using namespace std;

int max_value; // 最大价值
vector<int> best_solution; // 最佳解
vector<int> current_solution; // 当前解
vector<int> weight; // 物品重量
vector<int> value; // 物品价值

// 检查当前解是否是最优解
void check_solution() {
    int current_value = 0;
    for (int i = 0; i < current_solution.size(); i++) {
        if (current_solution[i] == 1) {
            current_value += value[i];
        }
    }
    if (current_value > max_value) {
        max_value = current_value;
        best_solution = current_solution;
    }
}

// 回溯搜索
void backtrack(int i, int remaining_capacity) {
    if (i == weight.size()) {
        check_solution();
        return;
    }
    if (weight[i] <= remaining_capacity) {
        current_solution[i] = 1;
        backtrack(i + 1, remaining_capacity - weight[i]);
    }
    current_solution[i] = 0;
    backtrack(i + 1, remaining_capacity);
}

int main() {
    int n, capacity;
    cin >> n >> capacity;

    // 读入物品重量和价值
    weight.resize(n);
    value.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> weight[i] >> value[i];
    }

    // 初始化
    max_value = 0;
    current_solution.resize(n);
    best_solution.resize(n);

    // 回溯搜索
    backtrack(0, capacity);

    // 输出最大价值和最佳解
    cout << "Max value: " << max_value << endl;
    cout << "Best solution: ";
    for (int i = 0; i < best_solution.size(); i++) {
        cout << best_solution[i] << " ";
    }
    cout << endl;

    return 0;
}