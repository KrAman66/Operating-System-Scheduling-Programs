#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int main() {
    int headPosition, totalRequests;

    cout << "Enter the current head position: ";
    cin >> headPosition;

    cout << "Enter the total number of disk requests: ";
    cin >> totalRequests;

    int* requests = new int[totalRequests];

    cout << "Enter the disk request positions:\n";
    for (int i = 0; i < totalRequests; i++) {
        cout << "Request " << (i + 1) << ": ";
        cin >> requests[i];
    }

    // Calculate the total head movement and build the seek sequence
    int totalHeadMovement = 0;
    vector<int> seekSequence;

    // Process each request in the order of arrival
    for (int i = 0; i < totalRequests; i++) {
        // Calculate the absolute difference between head position and current request
        int headMovement = abs(requests[i] - headPosition);

        // Update the head position
        headPosition = requests[i];

        // Accumulate the head movement
        totalHeadMovement += headMovement;

        // Add the current request position to the seek sequence
        seekSequence.push_back(requests[i]);
    }

    cout << "\nTotal head movement: " << totalHeadMovement << endl;

    // Display the seek sequence
    cout << "Seek Sequence: ";
    for (int i = 0; i < seekSequence.size(); i++) {
        cout << seekSequence[i];
        if (i != seekSequence.size() - 1) {
            cout << " -> ";
        }
    }
    cout << endl;
    cout<<"Throughput:"<<(float)totalRequests/totalHeadMovement;
    
    // Deallocate the dynamically allocated memory
    delete[] requests;

    return 0;
}