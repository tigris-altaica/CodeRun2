from math import inf, factorial


def clamp(n, min_n, max_n=inf):
    return max(min(max_n, n), min_n)


def combinations(n, k):
    return factorial(n) // (factorial(k) * factorial(n - k))


def bin_distr_prob(n, p, i):
    return (p ** i) * ((1 - p) ** (n - i)) * combinations(n, i)


def exp_one_day(n, p, f):
    return sum([f(i) * bin_distr_prob(n, p, i) for i in range(n + 1)])


def expired_expectation(n, k, t, p):
    return (t - 1) * exp_one_day(n, p, lambda x: clamp(k - x, 0, n)) + exp_one_day(n, p, lambda x: clamp(k - x, 0))


def main():
    n, k, t = map(int, input().split())
    p = float(input())

    print(expired_expectation(n, k, t, p))


if __name__ == '__main__':
    main()
