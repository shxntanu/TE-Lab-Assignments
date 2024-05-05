#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Job {
  int processing_time;
  int profit;
  int deadline;
};

bool compareJobs(const Job& job1, const Job& job2) {
  return job1.deadline < job2.deadline; // Sort in ascending order of deadlines
}

pair<int, vector<Job>> greedyJobScheduling(vector<Job>& jobs) {
  // Sort jobs by deadline
  sort(jobs.begin(), jobs.end(), compareJobs);

  int current_time = 0;
  vector<Job> scheduled_jobs;
  int total_profit = 0;

  // Iterate through sorted jobs
  for (Job& job : jobs) {
    if (current_time + job.processing_time <= job.deadline) {
      // Schedule the job if it doesn't violate the deadline
      current_time += job.processing_time;
      scheduled_jobs.push_back(job);
      total_profit += job.profit;
    }
  }

  return make_pair(total_profit, scheduled_jobs); // Return profit and scheduled jobs
}

int main() {
  vector<Job> jobs = {{5, 20, 2}, {2, 10, 1}, {3, 15, 3}};

  pair<int, vector<Job>> result = greedyJobScheduling(jobs);

  cout << "Total profit earned: " << result.first << endl;
  cout << "Scheduled jobs: \n";
  for (Job& job : result.second) {
    cout << "Processing time: " << job.processing_time << ", Profit: " << job.profit << ", Deadline: " << job.deadline << endl;
  }

  return 0;
}
