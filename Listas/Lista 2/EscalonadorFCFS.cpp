#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Process {
    int id;
    vector<int> instructions;
    int index = 0; // Current instruction index
};

int main() {
    int N;
    cin >> N;
    
    vector<int> instructionCount(N);
    for (int i = 0; i < N; ++i) {
        cin >> instructionCount[i];
    }
    
    queue<Process> processQueue;
    for (int i = 0; i < N; ++i) {
        Process p;
        p.id = i + 1;
        p.instructions.resize(instructionCount[i]);
        for (int j = 0; j < instructionCount[i]; ++j) {
            cin >> p.instructions[j];
        }
        processQueue.push(p);
    }

    int currentTime = 0;
    vector<pair<int, int>> completionTimes;

    while (!processQueue.empty()) {
        Process p = processQueue.front();
        processQueue.pop();

        while (p.index < p.instructions.size()) {
            if (p.instructions[p.index] == 0) {
                currentTime += 10;
                ++p.index;
            } else {
                p.instructions[p.index] = 0; // Turn blocking instruction to non-blocking
                processQueue.push(p);
                break;
            }
        }

        if (p.index == p.instructions.size()) {
            completionTimes.push_back({p.id, currentTime});
        }
    }

    for (const auto& ct : completionTimes) {
        cout << ct.first << " (" << ct.second << ")\n";
    }

    return 0;
}
