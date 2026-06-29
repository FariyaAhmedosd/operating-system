#include<bits/stdc++.h>
using namespace std;

int n, m;
int alloc[10][10], maxR[10][10], need[10][10], avail[10];

void isSafe()
{
    int work[10];
    bool finish[10] = {false};
    int safeSeq[10];
    int count = 0;

    // Copy available resources to work array
    for(int i = 0; i < m; i++)
        work[i] = avail[i];

    while(count < n)
    {
        bool found = false;

        for(int i = 0; i < n; i++)
        {
            if(!finish[i])
            {
                bool ok = true;

                // Check if all needed resources are available
                for(int j = 0; j < m; j++)
                {
                    if(need[i][j] > work[j])
                    {
                        ok = false;
                        break;
                    }
                }

                if(ok)
                {
                    // Release allocated resources
                    for(int j = 0; j < m; j++)
                        work[j] += alloc[i][j];

                    safeSeq[count] = i;
                    count++;
                    finish[i] = true;
                    found = true;
                }
            }
        }

        if(!found)
            break;
    }

    if(count == n)
    {
        cout << "\nSystem is in SAFE State.\n";
        cout << "Safe Sequence: ";

        for(int i = 0; i < n; i++)
        {
            cout << "P" << safeSeq[i];
            if(i != n - 1)
                cout << " -> ";
        }
        cout << endl;
    }
    else
    {
        cout << "\nSystem is NOT in SAFE State.\n";
    }
}

int main()
{
    cout << "Enter Number of Processes: ";
    cin >> n;

    cout << "Enter Number of Resources: ";
    cin >> m;

    cout << "\nEnter Allocation Matrix:\n";
    for(int i = 0; i < n; i++)
    {
        cout << "P" << i << ": ";
        for(int j = 0; j < m; j++)
            cin >> alloc[i][j];
    }

    cout << "\nEnter Max need:\n";
    for(int i = 0; i < n; i++)
    {
        cout << "P" << i << ": ";
        for(int j = 0; j < m; j++)
            cin >> maxR[i][j];
    }

    cout << "\nEnter Available Resources:\n";
    for(int i = 0; i < m; i++)
        cin >> avail[i];

    cout << "\nNeed Matrix:\n";
    for(int i = 0; i < n; i++)
    {
        cout << "P" << i << ": ";
        for(int j = 0; j < m; j++)
        {
            need[i][j] = maxR[i][j] - alloc[i][j];
            cout << need[i][j] << " ";
        }
        cout << endl;
    }

    isSafe();

    return 0;
}
