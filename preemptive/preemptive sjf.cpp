
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

struct Process {
    int id, at, bt, remaining_bt, ct, tat, wt;
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        cout << "P" << p[i].id << " [Arrival, Burst]: ";
        cin >> p[i].at >> p[i].bt;
        p[i].remaining_bt = p[i].bt;
    }

    int currentTime = 0, completed = 0;
    vector<bool> isDone(n, false);

    cout << "\nGantt Chart: ";

    while (completed < n) {
        int idx = -1;
        int minRemainingBt = INT_MAX;

        // যেই প্রসেসের remaining_bt সবচেয়ে কম, সেটা খুঁজে নেওয়া
        for (int i = 0; i < n; i++) {
            if (p[i].at <= currentTime && !isDone[i] && p[i].remaining_bt < minRemainingBt) {
                minRemainingBt = p[i].remaining_bt;
                idx = i;
            }
        }

        if (idx != -1) {
            p[idx].remaining_bt--;
            cout << "| P" << p[idx].id << " (" << currentTime << "-" << currentTime + 1 << ") ";
            currentTime++;

            if (p[idx].remaining_bt == 0) {
                p[idx].ct = currentTime;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
                isDone[idx] = true;
                completed++;
            }
        } else {
            currentTime++;
        }
    }
    cout << "|\n";

    // টেবিল প্রিন্ট
    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    float totalWT = 0, totalTAT = 0;
    for (int i = 0; i < n; i++) {
        cout << p[i].id << "\t" << p[i].at << "\t" << p[i].bt << "\t"
             << p[i].ct << "\t" << p[i].tat << "\t" << p[i].wt << endl;
        totalWT += p[i].wt;
        totalTAT += p[i].tat;
    }

    cout << "\nAverage Waiting Time: " << totalWT / n;
    cout << "\nAverage Turnaround Time: " << totalTAT / n << endl;

    return 0;
}
