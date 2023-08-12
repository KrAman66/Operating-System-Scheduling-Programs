#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int tempBT;
    int burstTime;
    int priority;
    int completionTime;
    int waitingTime;
    int turnaroundTime;
    bool executed;

    Process(int id, int arrivalTime, int burstTime, int priority)
        : id(id), arrivalTime(arrivalTime), burstTime(burstTime),
          tempBT(burstTime), priority(priority),
          completionTime(0), waitingTime(0), turnaroundTime(0),
          executed(false)
    {}
};

bool sortByArrival(const Process& p1, const Process& p2) {
    return p1.arrivalTime < p2.arrivalTime;
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes;

    cout << "Enter Arrival, Burst, Priority: " << endl;
    for (int i = 0; i < n; i++) {
        cout << "For process " << (i + 1) << ":" << endl;

        int arrivalTime, burstTime, priority;
        cin >> arrivalTime >> burstTime >> priority;

        Process process(i + 1, arrivalTime, burstTime, priority);
        processes.push_back(process);
    }

    // Sort processes based on arrival time
    sort(processes.begin(), processes.end(), sortByArrival);

    int currentTime = 0;
    int completedProcesses = 0;

    while (completedProcesses < n) {
        int highestPriority = INT_MAX;
        int selectedProcessIndex = -1;

        for (int i = 0; i < n; i++) {
            Process& process = processes[i];

            if (!process.executed && process.arrivalTime <= currentTime && process.priority < highestPriority) {
                highestPriority = process.priority;
                selectedProcessIndex = i;
            }
        }

        if (selectedProcessIndex == -1) {
            currentTime++;
            continue;
        }

        Process& selectedProcess = processes[selectedProcessIndex];
        selectedProcess.executed = true;

        selectedProcess.completionTime = currentTime + selectedProcess.burstTime;

        selectedProcess.turnaroundTime = selectedProcess.completionTime - selectedProcess.arrivalTime;
        selectedProcess.waitingTime = selectedProcess.turnaroundTime - selectedProcess.tempBT;

        currentTime = selectedProcess.completionTime;
        completedProcesses++;
    }

    int AverageWaitingTime = 0, AverageTurnaroundTime = 0;
    for (const Process& p : processes) {
        AverageTurnaroundTime += p.turnaroundTime;
        AverageWaitingTime += p.waitingTime;
    }

    cout << "\nProcess\t\tArrival\t\tBurst\t\tpriority\tCompletion\t\tWaiting\t\tTurnaround" << endl;
    cout << "------------------------------------------------------------------------" << endl;
    for (const Process& process : processes) {
        cout << process.id << "\t\t" << process.arrivalTime << "\t\t" << process.tempBT << "\t\t" << process.priority << "\t\t" << process.completionTime << "\t\t\t" << process.waitingTime <<
            "\t\t\t" << process.turnaroundTime << endl;
    }

    float T_ATAT = AverageTurnaroundTime / static_cast<float>(n);
    cout << "Average Waiting time: " << AverageWaitingTime / static_cast<float>(n) << endl;
    cout << "Average Turnaround Time: " << T_ATAT << endl;
    cout << "Throughput Time: " << T_ATAT / static_cast<float>(n) << endl;

    return 0;
}


// #include <iostream>
// #include <vector>
// #include <algorithm>
// #include <climits>

// using namespace std;

// struct Process {
//     int id;
//     int arrivalTime;
//     int tempBT;
//     int burstTime;
//     int priority;
//     int startTime;
//     int completionTime;
//     int waitingTime;
//     int turnaroundTime;
//     bool executed;

//     Process(int id, int arrivalTime, int burstTime, int priority)
//         : id(id), arrivalTime(arrivalTime), burstTime(burstTime),
//           tempBT(burstTime), priority(priority), startTime(0),
//           completionTime(0), waitingTime(0), turnaroundTime(0),
//           executed(false)
//     {}
// };

// bool sortByArrival(const Process& p1, const Process& p2) {
//     return p1.arrivalTime < p2.arrivalTime;
// }

// int main() {
//     int n;
//     cout << "Enter the number of processes: ";
//     cin >> n;

//     vector<Process> processes;

//     cout << "Enter Arrival, Burst, Priority: " << endl;
//     for (int i = 0; i < n; i++) {
//         cout << "For process " << (i + 1) << ":" << endl;

//         int arrivalTime, burstTime, priority;
//         cin >> arrivalTime >> burstTime >> priority;

//         Process process(i + 1, arrivalTime, burstTime, priority);
//         processes.push_back(process);
//     }

//     // Sort processes based on arrival time
//     sort(processes.begin(), processes.end(), sortByArrival);

//     int currentTime = 0;
//     int completedProcesses = 0;

//     while (completedProcesses < n) {
//         int highestPriority = INT_MAX;
//         int selectedProcessIndex = -1;

//         for (int i = 0; i < n; i++) {
//             Process& process = processes[i];

//             if (!process.executed && process.arrivalTime <= currentTime && process.priority < highestPriority) {
//                 highestPriority = process.priority;
//                 selectedProcessIndex = i;
//             }
//         }

//         if (selectedProcessIndex == -1) {
//             currentTime++;
//             continue;
//         }

//         Process& selectedProcess = processes[selectedProcessIndex];
//         selectedProcess.executed = true;
//         selectedProcess.startTime = currentTime;

//         // Calculate completion time
//         selectedProcess.completionTime = currentTime + 1;

//         selectedProcess.turnaroundTime = selectedProcess.completionTime - selectedProcess.arrivalTime;
//         selectedProcess.waitingTime = selectedProcess.turnaroundTime - selectedProcess.tempBT;

//         currentTime++;

//         if (selectedProcess.burstTime > 1) {
//             selectedProcess.burstTime--;
//             selectedProcess.executed = false;
//         } else {
//             completedProcesses++;
//         }
//     }

//     int AverageWaitingTime = 0, AverageTurnaroundTime = 0;
//     for (const Process& p : processes) {
//         AverageTurnaroundTime += p.turnaroundTime;
//         AverageWaitingTime += p.waitingTime;
//     }

//     cout << "\nProcess\t\tArrival\t\tBurst\t\tpriority\tStart\t\tCompletion\t\tWaiting\t\tTurnaround" << endl;
//     cout << "--------------------------------------------------------------------------------------------------------------" << endl;
//     for (const Process& process : processes) {
//         cout << process.id << "\t\t" << process.arrivalTime << "\t\t" << process.tempBT << "\t\t" << process.priority << "\t\t" << process.startTime << "\t\t" << process.completionTime << "\t\t\t" << process.waitingTime <<
//             "\t\t\t" << process.turnaroundTime << endl;
//     }
    
//     float T_ATAT = AverageTurnaroundTime / static_cast<float>(n);
//     cout << "Average Waiting time: " << AverageWaitingTime / static_cast<float>(n) << endl;
//     cout << "Average Turnaround Time: " << T_ATAT << endl;
//     cout << "Throughput Time: " << T_ATAT / static_cast<float>(n) << endl;

//     return 0;
// }


// #include <iostream>
// #include <vector>
// #include <algorithm>
// #include <climits>

// using namespace std;

// struct Process {
//     int id;
//     int arrivalTime;
//     int tempBT;
//     int burstTime;
//     int priority;
//     int startTime;
//     int completionTime;
//     int waitingTime;
//     int turnaroundTime;
//     bool executed;

//     Process(int id, int arrivalTime, int burstTime, int priority)
//         : id(id), arrivalTime(arrivalTime), burstTime(burstTime),
//           tempBT(burstTime), priority(priority), startTime(0),
//           completionTime(0), waitingTime(0), turnaroundTime(0),
//           executed(false)
//     {}
// };

// bool sortByArrival(const Process& p1, const Process& p2) {
//     return p1.arrivalTime < p2.arrivalTime;
// }

// int main() {
//     int n;
//     cout << "Enter the number of processes: ";
//     cin >> n;

//     vector<Process> processes;

//     cout << "Enter Arrival, Burst, Priority: " << endl;
//     for (int i = 0; i < n; i++) {
//         cout << "For process " << (i + 1) << ":" << endl;

//         int arrivalTime, burstTime, priority;
//         cin >> arrivalTime >> burstTime >> priority;

//         Process process(i + 1, arrivalTime, burstTime, priority);
//         processes.push_back(process);
//     }

//     // Sort processes based on arrival time
//     sort(processes.begin(), processes.end(), sortByArrival);

//     int currentTime = 0;
//     int completedProcesses = 0;

//     while (completedProcesses < n) {
//         int highestPriority = INT_MAX;
//         int selectedProcessIndex = -1;

//         for (int i = 0; i < n; i++) {
//             Process& process = processes[i];

//             if (!process.executed && process.arrivalTime <= currentTime && process.priority < highestPriority) {
//                 highestPriority = process.priority;
//                 selectedProcessIndex = i;
//             }
//         }

//         if (selectedProcessIndex == -1) {
//             currentTime++;
//             continue;
//         }

//         Process& selectedProcess = processes[selectedProcessIndex];
//         selectedProcess.executed = true;
//         selectedProcess.completionTime = currentTime + 1;

//         selectedProcess.turnaroundTime = selectedProcess.completionTime - selectedProcess.arrivalTime;
//         selectedProcess.waitingTime = selectedProcess.turnaroundTime - selectedProcess.tempBT;

//         currentTime++;

//         if (selectedProcess.burstTime > 1) {
//             selectedProcess.burstTime--;
//             selectedProcess.executed = false;
//         } else {
//             completedProcesses++;
//         }
//     }

//     int AverageWaitingTime = 0, AverageTurnaroundTime = 0;
//     for (const Process& p : processes) {
//         AverageTurnaroundTime += p.turnaroundTime;
//         AverageWaitingTime += p.waitingTime;
//     }

//     cout << "\nProcess\t\tArrival\t\tBurst\t\tpriority\tCompletion\t\tWaiting\t\tTurnaround" << endl;
//     cout << "--------------------------------------------------------------------------------------------------------------" << endl;
//     for (const Process& process : processes) {
//         cout << process.id << "\t\t" << process.arrivalTime << "\t\t" << process.tempBT << "\t\t" <<process.priority <<"\t\t" << process.completionTime << "\t\t\t" << process.waitingTime <<
//             "\t\t\t" << process.turnaroundTime << endl;
//     }
//      float T_ATAT = AverageTurnaroundTime / n;
//     cout << "Average Waiting time: " << AverageWaitingTime << endl;
//     cout << "Average Turnaround Time: " << AverageTurnaroundTime << endl;
//     cout << "Throughput Time: " << T_ATAT / n;

//     return 0;
// }



// #include <iostream>
// #include <vector>
// #include <algorithm>
// #include <climits>

// using namespace std;

// struct Process {
//     int id;
//     int arrivalTime;
//     int tempBT;
//     int burstTime;
//     int priority;
//     int startTime;
//     int completionTime;
//     int waitingTime;
//     int turnaroundTime;
//     bool executed;
//     int tempst;
//     Process(int id, int arrivalTime, int burstTime, int priority)
//         : id(id), arrivalTime(arrivalTime), burstTime(burstTime),
//           tempBT(burstTime), priority(priority), startTime(0),
//           completionTime(0), waitingTime(0), turnaroundTime(0),
//           executed(false)
//     {}
// };

// bool sortByStartTime(const Process& p1, const Process& p2) {
//     return p1.startTime < p2.startTime;
// }

// int main() {
//     int n;
//     cout << "Enter the number of processes: ";
//     cin >> n;

//     vector<Process> processes;

//     cout << "Enter Arrival, Burst, Priority: " << endl;
//     for (int i = 0; i < n; i++) {
//         cout << "For process " << (i + 1) << ":" << endl;

//         int arrivalTime, burstTime, priority;
//         cin >> arrivalTime >> burstTime >> priority;

//         Process process(i + 1, arrivalTime, burstTime, priority);
//         processes.push_back(process);
//     }

//     // Sort processes based on arrival time
//     sort(processes.begin(), processes.end(),
//          [](const Process& p1, const Process& p2) {
//              return p1.arrivalTime < p2.arrivalTime;
//          });

//     int currentTime = 0;
//     int completedProcesses = 0;

//     while (completedProcesses < n) {
//         int highestPriority = INT_MAX;
//         int selectedProcessIndex = -1;

//         for (int i = 0; i < n; i++) {
//             Process& process = processes[i];

//             if (!process.executed && process.arrivalTime <= currentTime && process.priority < highestPriority) {
//                 highestPriority = process.priority;
//                 selectedProcessIndex = i;
//             }
//         }

//         if (selectedProcessIndex == -1) {
//             currentTime++;
//             continue;
//         }

//         Process& selectedProcess = processes[selectedProcessIndex];
//         selectedProcess.executed = true;
//         selectedProcess.startTime = currentTime;
//         selectedProcess.tempst = currentTime; // Store the temporary start time

//         selectedProcess.completionTime = currentTime + 1;

//         selectedProcess.turnaroundTime = selectedProcess.completionTime - selectedProcess.arrivalTime;
//         selectedProcess.waitingTime = selectedProcess.turnaroundTime - selectedProcess.tempBT;

//         currentTime++;

//         if (selectedProcess.burstTime > 1) {
//             selectedProcess.burstTime--;
//             selectedProcess.executed = false;
//         } else {
//             completedProcesses++;
//         }
//     }

//     sort(processes.begin(), processes.end(), sortByStartTime);

//     float AverageWaitingTime = 0.0, AverageTurnaroundTime = 0.0;
//     for (const Process& p : processes) {
//         AverageTurnaroundTime += p.turnaroundTime;
//         AverageWaitingTime += p.waitingTime;
//     }

//     cout << "\nProcess\t\tArrival\t\tBurst\t\tPriority\t\tStart\t\tCompletion\t\tWaiting\t\tTurnaround" << endl;
//     cout << "----------------------------------------------------------------------------------------------" << endl;
//     for (const Process& process : processes) {
//         cout << process.id << "\t\t" << process.arrivalTime << "\t\t" << process.tempBT << "\t\t"<<process.priority<<"\t\t" <<
//             process.tempst << "\t\t" << process.completionTime << "\t\t\t" << process.waitingTime <<
//             "\t\t\t" << process.turnaroundTime << endl;
//     }
//     float T_ATAT = AverageTurnaroundTime / n;
//     cout << "Average Waiting time: " << AverageWaitingTime / n << endl;
//     cout << "Average Turnaround Time: " << T_ATAT << endl;
//     cout << "Throughput Time: " << T_ATAT / n << endl;

//     return 0;
// }


