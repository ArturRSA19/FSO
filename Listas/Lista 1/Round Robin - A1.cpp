#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Process {
    int process_id;
    int burst_time;
    int remaining_time;
};

void roundRobinScheduling(vector<Process> &processes, int time_quantum) {
    int total_remaining = processes.size();
    int current_time = 0;
    queue<int> processQueue; // Fila para guardar os índices dos processos a serem executados

    for (int i = 0; i < processes.size(); i++) {
        processQueue.push(i); // Adiciona os índices dos processos à fila
    }

    while (total_remaining > 0) {
        int index = processQueue.front(); // Pega o próximo processo a ser executado
        processQueue.pop();

        if (processes[index].remaining_time > 0) {
            int execute_time = min(time_quantum, processes[index].remaining_time); // Determina o tempo de execução
            current_time += execute_time;
            processes[index].remaining_time -= execute_time;

            if (processes[index].remaining_time <= 0) {
                processes[index].remaining_time = 0;
                cout << processes[index].process_id << " (" << current_time << ")" << endl;
                total_remaining--;
            } else {
                processQueue.push(index); // Adiciona de volta à fila se ainda não terminou
            }
        }
    }
}

int main() {
    int N, time_quantum;
    cin >> N;
    cin >> time_quantum;

    vector<Process> processes;

    for (int i = 0; i < N; i++) {
        int pid, exec_time_sec;
        cin >> pid >> exec_time_sec;

        Process new_process = {pid, exec_time_sec * 1000, exec_time_sec * 1000}; // Convertendo segundos para milissegundos
        processes.push_back(new_process);
    }

    roundRobinScheduling(processes, time_quantum);

    return 0;
}