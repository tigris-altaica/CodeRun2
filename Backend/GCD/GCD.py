from functools import reduce
import operator
from math import gcd


def main():
    n = int(input())
    a = reduce(operator.mul, map(int, input().split()))
    m = int(input())
    b = reduce(operator.mul, map(int, input().split()))

    d = gcd(a, b)

    print(str(d)[-9:])


if __name__ == '__main__':
    main()
