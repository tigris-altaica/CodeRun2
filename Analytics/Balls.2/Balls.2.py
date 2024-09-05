from functools import cache
from math import gcd, factorial


def reduce_gcd(num, denum):
    div = gcd(num, denum)
    num //= div
    denum //= div
    return num, denum

@cache
def pochhammer(a, n):
    result = 1
    for i in range(n):
        result *= (a + i)
    return result

n, x, y = int(input()), int(input()), int(input())

num = pochhammer(1 + x, n) * pochhammer(1 + y, n) - factorial(n) * pochhammer(1 + x + y, n)
denum = pochhammer(1 + x, n) * pochhammer(1 + y, n)

num, denum = reduce_gcd(num, denum)

print(num, denum)
