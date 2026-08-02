#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Process {
    int id, at, bt, ct, tat, wt, remaining_bt;
};

// Arrival Time অনুযায়ী সাজানোর জন্য
bool compareAT(Process a, Process b) {
    return a.at < b.at;
}

void printTable(vector<Process> p, int n) {
    float totalWT = 0, totalTAT = 0;
    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << p[i].id << "\t" << p[i].at << "\t" << p[i].bt << "\t"
             << p[i].ct << "\t" << p[i].tat << "\t" << p[i].wt << endl;
        totalWT += p[i].wt;
        totalTAT += p[i].tat;
    }
    cout << "\nAverage Waiting Time: " << totalWT / n;
    cout << "\nAverage Turnaround Time: " << totalTAT / n;
    cout << "\nThroughput: " << (float)n / p[n-1].ct << " processes/unit\n";
}

int main() {
    int n;
    cout << "Enter number of processes: "; cin >> n;
    vector<Process> main_p(n);

    for (int i = 0; i < n; i++) {
        main_p[i].id = i + 1;
        cout << "P" << main_p[i].id << " Arrival & Burst: ";
        cin >> main_p[i].at >> main_p[i].bt;
    }

    while (true) {
        vector<Process> p = main_p; // মেইন ডাটা কপি করা হচ্ছে
        for(int i=0; i<n; i++) p[i].remaining_bt = p[i].bt;

        sort(p.begin(), p.end(), compareAT);

        int choice;
        cout << "\n--- CPU Scheduling Menu ---\n1. FCFS\n2. SJF (Non-Preemptive)\n3. Round Robin\n4. Exit\nSelection: ";
        cin >> choice;

        if (choice == 4) break;

        int currentTime = 0;
        cout << "\nGantt Chart: ";

        if (choice == 1) { // FCFS Logic
            for (int i = 0; i < n; i++) {
                if (currentTime < p[i].at) {
                    cout << "| IDLE (" << currentTime << "-" << p[i].at << ") ";
                    currentTime = p[i].at;
                }
                cout << "| P" << p[i].id << " (" << currentTime << "-";
                p[i].ct = currentTime + p[i].bt;
                cout << p[i].ct << ") ";
                p[i].tat = p[i].ct - p[i].at;
                p[i].wt = p[i].tat - p[i].bt;
                currentTime = p[i].ct;
            }
            cout << "|";
            printTable(p, n);
        }
        else if (choice == 2) { // SJF Logic
            int completed = 0;
            vector<bool> is_done(n, false);
            while (completed != n) {
                int idx = -1, min_bt = 9999;
                for (int i = 0; i < n; i++) {
                    if (p[i].at <= currentTime && !is_done[i] && p[i].bt < min_bt) {
                        min_bt = p[i].bt;
                        idx = i;
                    }
                }
                if (idx != -1) {
                    cout << "| P" << p[idx].id << " (" << currentTime << "-";
                    p[idx].ct = currentTime + p[idx].bt;
                    cout << p[idx].ct << ") ";
                    p[idx].tat = p[idx].ct - p[idx].at;
                    p[idx].wt = p[idx].tat - p[idx].bt;
                    currentTime = p[idx].ct;
                    is_done[idx] = true;
                    completed++;
                } else {
                    cout << "| IDLE ";
                    currentTime++;
                }
            }
            cout << "|";
            printTable(p, n);
        }
        else if (choice == 3) { // Round Robin Logic
            int tq; cout << "Enter Time Quantum: "; cin >> tq;
            queue<int> q;
            vector<bool> in_queue(n, false);
            int completed = 0;

            // শুরুর প্রসেস কিউতে অ্যাড করা
            int i = 0;
            while(i < n && p[i].at <= currentTime) {
                q.push(i); in_queue[i] = true; i++;
            }

            while (completed != n) {
                if (!q.empty()) {
                    int idx = q.front(); q.pop();
                    cout << "| P" << p[idx].id << " (" << currentTime << "-";

                    int move = min(p[idx].remaining_bt, tq);
                    p[idx].remaining_bt -= move;
                    currentTime += move;
                    cout << currentTime << ") ";

                    // নতুন প্রসেস যারা এই সময়ে এসেছে তাদের অ্যাড করা
                    for (int j = 0; j < n; j++) {
                        if (p[j].at <= currentTime && p[j].remaining_bt > 0 && !in_queue[j]) {
                            q.push(j); in_queue[j] = true;
                        }
                    }

                    if (p[idx].remaining_bt > 0) q.push(idx);
                    else {
                        p[idx].ct = currentTime;
                        p[idx].tat = p[idx].ct - p[idx].at;
                        p[idx].wt = p[idx].tat - p[idx].bt;
                        completed++;
                    }
                } else {
                    cout << "| IDLE ";
                    currentTime++;
                    for (int j = 0; j < n; j++) {
                        if (p[j].at <= currentTime && p[j].remaining_bt > 0 && !in_queue[j]) {
                            q.push(j); in_queue[j] = true;
                        }
                    }
                }
            }
            cout << "|";
            printTable(p, n);
        }
    }
    return 0;
}
