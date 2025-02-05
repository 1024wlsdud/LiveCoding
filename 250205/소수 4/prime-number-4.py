input(a, b)
count = 0
numbers = [True] * (a+1) 
for i in range(2, n+1):
    if numbers[i]:
        count += 1
        if count == b:
            return i
    for j in range(i * 2, a+1, i):
        if 