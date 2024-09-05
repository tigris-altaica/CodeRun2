def count_primes(n):
    if n < 2:
        return 0  # Нет простых чисел меньше 2

    # Создаем список для хранения информации о простых числах
    primes = [True] * (n + 1)
    p = 2
    while (p * p <= n):
        # Если primes[p] не изменился, то это простое число
        if (primes[p] == True):
            # Обновляем все кратные p как составные
            for i in range(p * p, n + 1, p):
                primes[i] = False
        p += 1

    # Считаем количество простых чисел
    prime_count = sum(1 for p in range(2, n + 1) if primes[p])

    return prime_count


def main():
    all_numbers = int(input())
    primes = count_primes(all_numbers)
    print("{:.2f}".format(primes / all_numbers))


if __name__ == '__main__':
    main()