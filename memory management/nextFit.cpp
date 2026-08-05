#include <iostream>
using namespace std;

int main() {
    int m, n;
    cout << "Enter number of Blocks: ";
    cin >> m;
    int blockSize[m];

    cout << "Enter size of each Block:\n";
    for (int i = 0; i < m; i++)
    {
        cout << "Block " << i + 1 << ": ";
        cin >> blockSize[i];
    }

    cout << "\nEnter number of Processes: ";
    cin >> n;
    int processSize[n];
    int allocation[n];

    cout << "Enter size of each Process:\n";
    for (int i = 0; i < n; i++) {
        cout << "Process " << i + 1 << ": ";
        cin >> processSize[i];
        allocation[i] = -1;
    }
    int lastPos = 0; //last kon position e process dhukse

    for (int i = 0; i < n; i++) {
        int count = 0;
        //all block circular way te ghure dekhbe tai
        while (count < m) {
            int j = (lastPos + count) % m; //last position theke shuru korbe

            if (blockSize[j] >= processSize[i])
                {
                allocation[i] = j;              // block num save
                blockSize[j] -= processSize[i]; // decrease block size
                lastPos = j;
                break;
                }
            count++;
        }
    }
    // output
    cout << "\nNext Fit Allocation:\n";
    cout << "Process No.\tProcess Size\tBlock No.\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << i + 1 << "\t\t" << processSize[i] << "\t\t";
        if (allocation[i] != -1) {
            cout << allocation[i] + 1 << "\n";
        } else {
            cout << "Not Allocated\n";
        }
    }

    return 0;
}
