import random

def first_fit(programSize: int, memory: list, currentPointer: int) -> int:
    for i in range(len(memory)):
        if not memory[i][2] and memory[i][0] >= programSize:
            updateList = list(memory[i])
            updateList[0] = updateList[0] - programSize
            updateList[1] = programSize
            updateList[2] = True
            memory[i] = tuple(updateList)
            currentPointer = i
            return i
    return -1

def next_fit(programSize: int, memory: list, currentPointer: int) -> int:
    for i in range(currentPointer, len(memory)):
        if not memory[i][2] and memory[i][0] >= programSize:
            updateList = list(memory[i])
            updateList[0] = updateList[0] - programSize
            updateList[1] = programSize
            updateList[2] = True
            memory[i] = tuple(updateList)
            currentPointer = i
            return i
    for i in range(0, currentPointer):
        if not memory[i][2] and memory[i][0] >= programSize:
            updateList = list(memory[i])
            updateList[0] = updateList[0] - programSize
            updateList[1] = programSize
            updateList[2] = True
            memory[i] = tuple(updateList)
            currentPointer = i
            return i
    return -1

def best_fit(programSize: int, memory: list, currentPointer: int) -> int:
    minimumVal, min = 10000, -1
    for i in range(len(memory)):
        if not memory[i][2] and memory[i][0] >= programSize and memory[i][0] - programSize <= minimumVal:
            minimumVal = memory[i][0] - programSize
            min = i
    if min != -1:
        updateList = list(memory[min])
        updateList[0] = updateList[0] - programSize
        updateList[1] = programSize
        updateList[2] = True
        memory[min] = tuple(updateList)
        currentPointer = min
    return min

def worst_fit(programSize: int, memory: list, currentPointer: int) -> int:
    maximumVal, max = 0, -1
    for i in range(len(memory)):
        if not memory[i][2] and memory[i][0] >= programSize and memory[i][0] - programSize > maximumVal:
            maximumVal = memory[i][0] - programSize
            max = i
    if max != -1:
        updateList = list(memory[max])
        updateList[0] = updateList[0] - programSize
        updateList[1] = programSize
        updateList[2] = True
        memory[max] = tuple(updateList)
        currentPointer = max
    return max

if __name__ == '__main__':

    n = random.randint(5,15)
    memory = [(int(round(random.random(), 3) * 1000), 0, False) for _ in range(n)]
    programs = [int(round(random.random(), 3) * 1000) for _ in range(5)]
    currentPtr = 0

    for program in programs:

        pos = 0
        print("Free       Consumed    isOccupied?")
        for (free, consumed, isOccupied) in memory:
            print("{:<14}{:<11}{}".format(free, consumed, isOccupied))

        print(f"\nThe current program has size {program}, how do you want to fit it?: ")
        choice = int(input("""1. Best Fit
2. Worst Fit
3. First Fit
4. Next Fit: \n"""))
        
        if choice == 1:
            pos = best_fit(program, memory, currentPtr)
        elif choice == 2:
            pos = worst_fit(program, memory, currentPtr)
        elif choice == 3:
            pos = first_fit(program, memory, currentPtr)
        elif choice == 4:
            pos = next_fit(program, memory, currentPtr)

        if pos == -1:
            print("Not Enough Memory")
        else:
            print(f"Program inserted at position: {pos}")
        

