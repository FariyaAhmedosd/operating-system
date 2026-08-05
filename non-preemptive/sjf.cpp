#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
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
// Arrival Time অনুযায়ী সাজানোর জন্য হেল্পার ফাংশন
bool compareAT(Process a, Process b) {
    return a.at < b.at;
}
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
int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);

    // ইনপুট নেওয়ার লুপ
    for (int i = 0; i < n; i++)
    {
        p[i].id = i + 1;
        cout << "P" << p[i].id << " Arrival & Burst Time: ";
        cin >> p[i].at >> p[i].bt;
        p[i].remaining_bt = p[i].bt; // RR এর জন্য ইনিশিয়ালাইজেশন
    }
// --- SJF Logic Starts ---
    vector<bool> is_done(n, false);
    int currentTime = 0, completed = 0;

    cout << "\nGantt Chart: ";
    while (completed < n) {
        int idx = -1;
        int min_bt = 1e9; // প্রসেস খোঁজার জন্য বড় মান

        // বর্তমান সময়ে এসেছে এমন প্রসেসের মধ্যে সর্বনিম্ন BT খুঁজে বের করা
        for (int i = 0; i < n; i++) {
            if (p[i].at <= currentTime && !is_done[i] && p[i].bt < min_bt) {
                min_bt = p[i].bt;
                idx = i;
            }
        }

        if (idx != -1) { // প্রসেস পাওয়া গেলে
            p[idx].ct = currentTime + p[idx].bt;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;

            cout << "| P" << p[idx].id << " (" << currentTime << "-" << p[idx].ct << ") ";
            currentTime = p[idx].ct;
            is_done[idx] = true;
            completed++;
        } else { // প্রসেস না পাওয়া গেলে CPU IDLE থাকবে
            cout << "| IDLE (" << currentTime << "-" << currentTime + 1 << ") ";
            currentTime++;
        }
    }
    cout << "|";
    // --- SJF Logic Ends ---
    // ফলাফল প্রিন্ট
    printResult(p, n);

    return 0;
}
