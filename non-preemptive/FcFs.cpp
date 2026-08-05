#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// ======= PARAGRAPH 1: Process Structure =======
struct Process {
    int id;           // Process ID
    int at;           // Arrival Time
    int bt;           // Burst Time
    int ct;           // Completion Time
    int tat;          // Turnaround Time
    int wt;           // Waiting Time
    int remaining_bt; // Round Robin এর জন্য প্রয়োজনীয়
};

// =======  Sorting Function =======
// Arrival Time অনুযায়ী সাজানোর জন্য হেল্পার ফাংশন
bool compareAT(Process a, Process b) {
    return a.at < b.at;
}
//==== Result Table & Average Printing =======
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
// --- FCFS Logic Starts ---
   sort(p.begin(), p.end(), compareAT);

    int currentTime = 0;
    float totalWT = 0, totalTAT = 0;

    cout << "\nGantt Chart: ";
    for (int i = 0; i < n; i++) {
        if (currentTime < p[i].at) {
            cout << "| IDLE (" << currentTime << "-" << p[i].at << ") ";
            currentTime = p[i].at;
        }

        p[i].ct = currentTime + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        cout << "| P" << p[i].id << " (" << currentTime << "-" << p[i].ct << ") ";
        currentTime = p[i].ct;

        totalWT += p[i].wt;
        totalTAT += p[i].tat;
    }
    cout << "|\n";
    // --- FCFS Logic Ends ---
      printResult(p, n);
    return 0;
}



























/*
while (true) {
        cout << "\n===============================";
        cout << "\n--- CPU Scheduling Menu ---";
        cout << "\n1. FCFS";
        cout << "\n2. SJF (Non-Preemptive)";
        cout << "\n3. Round Robin";
        cout << "\n4. Exit";
        cout << "\nSelect Choice (1-4): ";

        int choice;
        cin >> choice;

        if (choice == 4) {
            cout << "Exiting Program...\n";
            break;
        }

        switch (choice) {
            case 1:
                runFCFS(main_p, n);
                break;
            case 2:
                runSJF(main_p, n);
                break;
            case 3:
                runRoundRobin(main_p, n);
                break;
            default:
                cout << "Invalid Option! Please select between 1 and 4.\n";
        }
    }

*/


