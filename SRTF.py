class Process:
    def __init__(self, id, burst, arrival):
        self.id = id
        self.burst = burst
        self.arrival = arrival

def waitingTime(processes, n, wt):
    remainingTime = [0] * n

    for i in range(n):
        remainingTime[i] = processes[i].burst

    currentTime = 0
    completedTasks = 0
    shortestTask = 0
    minBurst = float('inf')
    finishTime = 0
    taskActive = False

    while completedTasks != n:
        for j in range(n):
            if (
                processes[j].arrival <= currentTime
                and processes[j].burst < minBurst
                and remainingTime[j] > 0
            ):
                shortestTask = j
                minBurst = processes[j].burst
                taskActive = True

        if not taskActive:
            currentTime += 1
            continue

        remainingTime[shortestTask] -= 1
        minBurst = remainingTime[shortestTask]

        if minBurst == 0:
            minBurst = float('inf')

        if remainingTime[shortestTask] == 0:
            completedTasks += 1
            finishTime = currentTime + 1
            taskActive = False
            wt[shortestTask] = (
                finishTime - processes[shortestTask].arrival - processes[shortestTask].burst
            )
            if wt[shortestTask] < 0:
                wt[shortestTask] = 0

        currentTime += 1

if __name__ == "__main__":
    proc = [
        Process(1, 6, 2),
        Process(2, 2, 5),
        Process(3, 8, 1),
        Process(4, 3, 0),
        Process(5, 4, 4),
    ]
    n = len(proc)
    wt = [0] * n
    waitingTime(proc, n, wt)
    for i in range(n):
        print(wt[i])
