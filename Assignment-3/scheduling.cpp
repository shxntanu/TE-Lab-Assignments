#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>

using namespace std;

class Job {
public:
    string id;
    int deadline;
    int profit;

    Job(string id, int deadline, int profit) : id(id), deadline(deadline), profit(profit) {}

    // Optional comparison operator overloading for cleaner sorting (C++11 or later)
    bool operator<(const Job& other) const { return profit > other.profit; }
};

class Schedule {
private:
    vector<Job> jobs;

public:
    void input() {
        int numJobs;
        cout << "Enter the number of jobs: ";
        cin >> numJobs;

        jobs.resize(numJobs);

        for (int i = 0; i < numJobs; ++i) {
            cout << "Enter job " << (i + 1) << " details:\n";
            cout << "  ID: ";
            cin >> jobs[i].id;
            cout << "  Deadline: ";
            cin >> jobs[i].deadline;
            cout << "  Profit: ";
            cin >> jobs[i].profit;
        }
    }

    void order() {
        sort(jobs.begin(), jobs.end()); // Use vector sorting functionality

        vector<bool> slots(max_element(jobs.begin(), jobs.end(), [](const Job& j1, const Job& j2) {
            return j1.deadline < j2.deadline;
        })->deadline + 1, false); // Ensure enough slots for any deadline

        vector<string> jobSequence;
        for (const Job& job : jobs) {
            for (int slot = job.deadline - 1; slot >= 0; --slot) {
                if (!slots[slot]) {
                    jobSequence.push_back(job.id);
                    slots[slot] = true;
                    break;
                }
            }
        }

        cout << "Job Scheduling using greedy search approach:\n";
        for (const string& jobId : jobSequence) {
            cout << jobId << " ";
        }
        cout << endl;
    }

    void display() {
        cout << "ID" << setw(10) << "Deadline" << setw(10) << "Profit\n";
        for (const Job& job : jobs) {
            cout << job.id << "\t" << job.deadline << "\t" << job.profit << endl;
        }
    }
};

int main() {
    Schedule schedule;
    cout << "INPUT:\n";
    schedule.input();
    cout << "Entered jobs are as follows:\n";
    schedule.display();
    schedule.order();
    return 0;
}
