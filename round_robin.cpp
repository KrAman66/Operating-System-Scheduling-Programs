#include <iostream>

int main() {
    int NOP, sum = 0, count = 0, y, quant, wt = 0, tat = 0;
    float avg_wt, avg_tat;

    std::cout << "Total number of processes in the system: ";
    std::cin >> NOP;
    y = NOP;

    int at[NOP], bt[NOP], temp[NOP];
    int i; 
    for ( i = 0; i < NOP; i++) {
        std::cout << "\nEnter the Arrival and Burst time of Process[" << i + 1 << "]:\n";
        std::cout << "Arrival time: ";
        std::cin >> at[i];
        std::cout << "Burst time: ";
        std::cin >> bt[i];
        temp[i] = bt[i];
    }

    std::cout << "Enter the Time Quantum for the process: ";
    std::cin >> quant;

    std::cout << "\nProcess No \t\t Burst Time \t\t Turnaround Time \t\t Waiting Time\n";
    for (sum = 0, i = 0; y != 0 ;) {
        if (temp[i] <= quant && temp[i] > 0) {
            sum = sum + temp[i];
            temp[i] = 0;
            count = 1;
        } else if (temp[i] > 0) {
            temp[i] = temp[i] - quant;
            sum = sum + quant;
        }
        if (temp[i] == 0 && count == 1) {
            y--;
            std::cout << "Process No[" << i + 1 << "]\t\t\t" << bt[i] << "\t\t\t" << sum - at[i] << "\t\t\t\t" << sum - at[i] - bt[i] << "\n";
            wt = wt + sum - at[i] - bt[i];
            tat = tat + sum - at[i];
            count = 0;
        }
        if (i == NOP - 1) {
            i = 0;
        } else if (at[i + 1] <= sum) {
            i++;
        } else {
            i = 0;
        }
    }

    avg_wt = static_cast<float>(wt) / NOP;
    avg_tat = static_cast<float>(tat) / NOP;

    std::cout << "\nAverage Turn Around Time: " << avg_tat << "\n";
    std::cout << "Average Waiting Time: " << avg_wt << "\n";
    std::cout << "Throughput Time: " << avg_wt/NOP << "\n";

  return 0;
}