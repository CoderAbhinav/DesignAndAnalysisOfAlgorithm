import random

def generateRandomArray(low:int ,high: int ,count: int):
    res = []
    for i in range(count):
        res.append(random.randint(low, high + 1))
    
    return res

def generateSortedArray(low: int, high: int, count: int):
    res = []
    for i in range(count):
        res.append(random.randint(low, high + 1))
    
    res.sort()

    return res

x = generateRandomArray(0, 50000, 100000)

print(100000)
for n in x:
    print(n, end= '\t')


