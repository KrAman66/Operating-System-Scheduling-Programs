#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>

using namespace std;

// Function to calculate the absolute difference between two numbers
int absDiff(int a, int b) {
    return abs(a - b);
}

int main() {
    int n, head;

    cout << "Enter the number of requests: ";
    cin >> n;

    if (n <= 0) {
        cout << "Invalid number of requests. Exiting the program." << endl;
        return 0;
    }

    vector<int> arr(n);

    cout << "Enter the request values:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Request " << i + 1 << ": ";
        cin >> arr[i];
    }

    cout << "Enter the initial head position: ";
    cin >> head;

    int totalSeekTime = 0;
    int current = head;

    cout << "Seek Sequence: ";
    for (int i = 0; i < n; i++) {
        int shortestSeekTime = INT_MAX;
        int shortestSeekTimeIndex = -1;

        for (int j = 0; j < n; j++) {
            int diff = absDiff(arr[j], current);

            if (diff < shortestSeekTime) {
                shortestSeekTime = diff;
                shortestSeekTimeIndex = j;
            }
        }

        cout << arr[shortestSeekTimeIndex] << " ";
        totalSeekTime += shortestSeekTime;
        current = arr[shortestSeekTimeIndex];
        arr[shortestSeekTimeIndex] = INT_MAX;
    }

    cout << endl;
    cout << "Total Seek Time: " << totalSeekTime << endl;
    cout<<"Throughput:"<<(float)n/totalSeekTime;
  return 0;
}