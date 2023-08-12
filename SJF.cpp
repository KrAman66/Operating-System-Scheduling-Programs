#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    string name;
    int arrivalTime;
    int burstTime;

    Process(const string& name, int arrivalTime, int burstTime)
        : name(name), arrivalTime(arrivalTime), burstTime(burstTime) {}
};

struct ArrivalComparator {
    bool operator()(const Process& p1, const Process& p2) {
        return p1.arrivalTime <= p2.arrivalTime;
    }
};

struct BurstComparator {
    bool operator()(const Process& p1, const Process& p2) {
        return p1.burstTime < p2.burstTime;
    }
};

void calculate(const string& name, int at, int bt, int& currentTime, int& totalWaitingTime, int& totalTurnaroundTime) {
    int st = currentTime;
    int ct = st + bt;
    currentTime = currentTime + bt;

    int tat = ct - at;
    int wt = tat - bt;

    totalWaitingTime += wt;
    totalTurnaroundTime += tat;

    cout << name << "\t\t" << at << "\t\t" << bt << "\t\t" << st << "\t\t\t" << ct << "\t\t\t" << tat << "\t\t\t" << wt << endl;
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes;

    cout << "Enter process Arrival & Burst time:\n";
    for (int i = 0; i < n; i++) {
        cout << "For Process " << i << ":" << endl;
        int arrivalTime, burstTime;
        cin >> arrivalTime >> burstTime;

        processes.emplace_back("P" + to_string(i), arrivalTime, burstTime);
    }

    sort(processes.begin(), processes.end(), ArrivalComparator());

    cout << "PID\t\tArrival\t\tBurst\t\tStarting\t\tCompleition\t\tTurnAround\t\tWaiting" << endl;
    int currentTime = 0;
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;

    calculate(processes[0].name, processes[0].arrivalTime, processes[0].burstTime, currentTime, totalWaitingTime, totalTurnaroundTime);

    processes.erase(processes.begin());

    vector<Process> temp;

    while (!processes.empty() || !temp.empty()) {
        if (!processes.empty()) {
            for (int i = 0; i < processes.size(); i++) {
                if (processes[i].arrivalTime <= currentTime) {
                    temp.push_back(processes[i]);
                    processes.erase(processes.begin() + i);
                    i--;
                }
            }
        }

        if (!processes.empty()) {
            for (int i = 0; i < processes.size(); i++) {
                if (processes[i].arrivalTime <= currentTime) {
                    temp.push_back(processes[i]);
                    processes.erase(processes.begin() + i);
                    i--;
                }
            }
        }

        sort(temp.begin(), temp.end(), BurstComparator());

        calculate(temp[0].name, temp[0].arrivalTime, temp[0].burstTime, currentTime, totalWaitingTime, totalTurnaroundTime);

        temp.erase(temp.begin());
    }

    double averageWaitingTime = static_cast<double>(totalWaitingTime) / n;
    double averageTurnaroundTime= static_cast<double>(totalTurnaroundTime) / n;
    cout << "\nAverage Waiting Time: " << averageWaitingTime << endl;
    cout << "Average Turnaround Time: " << averageTurnaroundTime << endl;
    cout << "Throughput Time: " << averageTurnaroundTime/n << endl;
return 0;
}