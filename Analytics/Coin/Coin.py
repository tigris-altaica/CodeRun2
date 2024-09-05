import random


def flip_coin():
    outcome = random.random()  # Генерируем случайное число между 0 и 1
    if outcome < 0.9:  # Вероятность 90% для орла
        return 'H'
    else:
        return 'T'


def do_experiment():
    num_heads_in_row = 0
    num_series = 0

    while num_series < 15:
        toss = flip_coin()

        if toss == 'H':
            num_heads_in_row += 1
        else:
            if num_heads_in_row != 0:
                num_series += 1
            num_heads_in_row = 0

        if num_heads_in_row > 25:
            return True

    return False


num_repeats = 10000000
num_successes = 0

for i in range(num_repeats):
    num_successes += do_experiment()

print(num_successes / num_repeats)
