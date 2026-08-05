#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

// ======= PARAGRAPH 1: Process Structure =======
// প্রসেসের প্রয়োজনীয় প্রপার্টিগুলো রাখার জন্য স্ট্রাকচার
   struct Process {
    int id;           // Process ID
    int at;           // Arrival Time
    int bt;           // Burst Time
    int ct;           // Completion Time
    int tat;          // Turnaround Time
    int wt;           // Waiting Time
    int remaining_bt; // Round Robin এর জন্য প্রয়োজনীয়
};

// ======= PARAGRAPH 2: Sorting Function =======
// Arrival Time অনুযায়ী সাজানোর জন্য হেল্পার ফাংশন
bool compareAT(Process a, Process b) {
    return a.at < b.at;
}

// ======= PARAGRAPH 3: Result Table & Average Printing =======
// ফলাফল প্রিন্ট এবং Average Calculating ফাংশন
void printResult(vector<Process>& p, int n) {
    float totalWT = 0, totalTAT = 0;

    cout << "\n\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    cout << "-------------------------------------\n";
    for (int i = 0; i < n; i++) {
        cout << p[i].id << "\t" << p[i].at << "\t" << p[i].bt << "\t"
             << p[i].ct << "\t" << p[i].tat << "\t" << p[i].wt << endl;

        totalWT += p[i].wt;
        totalTAT += p[i].tat;
    }

    cout << "\nAverage Waiting Time: " << totalWT / n;
    cout << "\nAverage Turnaround Time: " << totalTAT / n << endl;
}

// ======= PARAGRAPH 4: Main Function Template =======
int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);

    // ইনপুট নেওয়ার লুপ
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        cout << "P" << p[i].id << " Arrival & Burst Time: ";
        cin >> p[i].at >> p[i].bt;
        p[i].remaining_bt = p[i].bt; // RR এর জন্য ইনিশিয়ালাইজেশন
    }

    // ----------------------------------------------------
    //  এখানে নির্দিষ্ট অ্যালগরিদমের লজিক বসবে (নিচে দেখুন)
    // ----------------------------------------------------
// --- Round Robin Logic Starts ---
    int tq;
    cout << "Enter Time Quantum: ";
    cin >> tq;

    sort(p.begin(), p.end(), compareAT); // Arrival Time দিয়ে সর্ট

    queue<int> q;
    vector<bool> in_queue(n, false);
    int currentTime = 0, completed = 0;

    // শুরুতেই যারা চলে এসেছে তাদের কিউতে পুশ করা
    for (int i = 0; i < n; i++) {
        if (p[i].at <= currentTime) {
            q.push(i);
            in_queue[i] = true;
        }
    }

    cout << "\nGantt Chart: ";
    while (completed < n) {
        if (!q.empty()) {
            int idx = q.front();
            q.pop();

            // Time Quantum অনুযায়ী কতটুকু চলবে তা নির্ধারণ
            int slice = min(p[idx].remaining_bt, tq);
            cout << "| P" << p[idx].id << " (" << currentTime << "-";

            p[idx].remaining_bt -= slice;
            currentTime += slice;
            cout << currentTime << ") ";

            // রান করার মাঝে নতুন আসা প্রসেসগুলোকে কিউতে যুক্ত করা
            for (int j = 0; j < n; j++) {
                if (p[j].at <= currentTime && p[j].remaining_bt > 0 && !in_queue[j]) {
                    q.push(j);
                    in_queue[j] = true;
                }
            }

            // যদি বর্তমান প্রসেসের কাজ বাকি থাকে, তবে শেষে আবার পুশ করা
            if (p[idx].remaining_bt > 0) {
                q.push(idx);
            } else {
                p[idx].ct = currentTime;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
                completed++;
            }
        } else { // Queue খালি থাকলে CPU IDLE
            cout << "| IDLE (" << currentTime << "-" << currentTime + 1 << ") ";
            currentTime++;
            for (int j = 0; j < n; j++) {
                if (p[j].at <= currentTime && p[j].remaining_bt > 0 && !in_queue[j]) {
                    q.push(j);
                    in_queue[j] = true;
                }
            }
        }
    }
    cout << "|";
    // --- Round Robin Logic Ends ---
    // ফলাফল প্রিন্ট
    printResult(p, n);

    return 0;
}
