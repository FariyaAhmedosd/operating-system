#include <iostream>
using namespace std;

int main() {
    int m, n;
    cout << "Enter number of Blocks: ";
    cin >> m;
    int blockSize[m];

    cout << "Enter size of each Block:\n";
    for (int i = 0; i < m; i++) {
        cout << "Block " << i + 1 << ": ";
        cin >> blockSize[i];
    }

    cout << "\nEnter number of Processes: ";
    cin >> n;
    int processSize[n];
    int allocation[n];

    cout << "Enter size of each Process:\n";
    for (int i = 0; i < n; i++)
    {
        cout << "Process " << i + 1 << ": ";
        cin >> processSize[i];
        allocation[i] = -1;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }
    cout << "\nFirst Fit Allocation:\n";
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
