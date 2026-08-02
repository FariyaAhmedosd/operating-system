#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// প্রসেসের তথ্য রাখার জন্য স্ট্রাকচার
struct Process {
    int id, at, bt, priority, ct, tat, wt, remaining_bt;
};

// ১. Priority (Non-Preemptive) অ্যালগরিদম
void priorityNonPreemptive(vector<Process> p, int n) {
    int currentTime = 0, completed = 0;
    vector<bool> is_done(n, false);

    cout << "\nGantt Chart: ";

    while (completed < n) {
        int idx = -1;
        int min_prio = INT_MAX;

        // যে প্রসেসগুলো চলে এসেছে সেগুলোর মধ্যে সবচেয়ে কম Priority কোনটা চেক করা
        for (int i = 0; i < n; i++) {
            if (p[i].at <= currentTime && !is_done[i] && p[i].priority < min_prio) {
                min_prio = p[i].priority;
                idx = i;
            }
        }

        if (idx != -1) {
            cout << "| P" << p[idx].id << " (" << currentTime << "-";
            currentTime += p[idx].bt;
            p[idx].ct = currentTime;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            is_done[idx] = true;
            completed++;
            cout << currentTime << ") ";
        } else {
            currentTime++; // CPU Idle থাকলে সময় ১ বাড়িয়ে দেওয়া
        }
    }
    cout << "|\n";

    // রেজাল্ট প্রিন্ট
    float totalWT = 0, totalTAT = 0;
    cout << "\nPID\tAT\tBT\tPrio\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << p[i].id << "\t" << p[i].at << "\t" << p[i].bt << "\t"
             << p[i].priority << "\t" << p[i].ct << "\t" << p[i].tat << "\t" << p[i].wt << endl;
        totalWT += p[i].wt;
        totalTAT += p[i].tat;
    }
    cout << "\nAverage Waiting Time: " << totalWT / n;
    cout << "\nAverage Turnaround Time: " << totalTAT / n << endl;
}

// ২. Preemptive Logic (Priority Preemptive ও SRTF উভয়ের জন্য)
void preemptiveScheduling(vector<Process> p, int n, bool isPriority) {
    int currentTime = 0, completed = 0;
    vector<bool> is_done(n, false);

    cout << "\nGantt Chart: ";

    while (completed < n) {
        int idx = -1;
        int min_val = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= currentTime && !is_done[i]) {
                // isPriority true হলে Priority চেক করবে, false হলে Remaining Burst Time চেক করবে
                int current_val = isPriority ? p[i].priority : p[i].remaining_bt;
                if (current_val < min_val) {
                    min_val = current_val;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            cout << "| P" << p[idx].id << " (" << currentTime << "-";
            p[idx].remaining_bt--;
            currentTime++;
            cout << currentTime << ") ";

            if (p[idx].remaining_bt == 0) {
                p[idx].ct = currentTime;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
                is_done[idx] = true;
                completed++;
            }
        } else {
            currentTime++;
        }
    }
    cout << "|\n";

    // রেজাল্ট প্রিন্ট
    float totalWT = 0, totalTAT = 0;
    cout << "\nPID\tAT\tBT\tPrio\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << p[i].id << "\t" << p[i].at << "\t" << p[i].bt << "\t"
             << p[i].priority << "\t" << p[i].ct << "\t" << p[i].tat << "\t" << p[i].wt << endl;
        totalWT += p[i].wt;
        totalTAT += p[i].tat;
    }
    cout << "\nAverage Waiting Time: " << totalWT / n;
    cout << "\nAverage Turnaround Time: " << totalTAT / n << endl;
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
    vector<Process> main_p(n);

    for (int i = 0; i < n; i++) {
        main_p[i].id = i + 1;
        cout << "P" << main_p[i].id << " [Arrival, Burst, Priority]: ";
        cin >> main_p[i].at >> main_p[i].bt >> main_p[i].priority;
        main_p[i].remaining_bt = main_p[i].bt;
    }

    while (true) {
        int choice;
        cout << "\n--- CPU Scheduling Menu ---\n";
        cout << "1. Priority (Non-Preemptive)\n";
        cout << "2. Priority (Preemptive)\n";
        cout << "3. SRTF (Preemptive SJF)\n";
        cout << "4. Exit\nSelection: ";
        cin >> choice;

        if (choice == 4) break;

        if (choice == 1) {
            priorityNonPreemptive(main_p, n);
        } else if (choice == 2) {
            preemptiveScheduling(main_p, n, true);  // true = Priority
        } else if (choice == 3) {
            preemptiveScheduling(main_p, n, false); // false = SRTF
        }
    }

    return 0;
}
