from math import gcd


def reduce_gcd(num, denum):
    div = gcd(num, denum)
    num //= div
    denum //= div
    return num, denum


n = int(input())

num = n * (n + 7)
denum = 2 * (n + 1) * (n + 6)
num, denum = reduce_gcd(num, denum)

print(num, denum)
