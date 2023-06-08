def calculator(n):
    if n == 0:
        return 1
    elif n % 2 == 1:
        return calculator(n - 1) * 2
    else:
        return calculator(n // 2) ** 2


print(calculator(4))