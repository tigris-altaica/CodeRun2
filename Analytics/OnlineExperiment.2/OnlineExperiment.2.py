n = int(input())
p = float(input())
q = 1 - p

pH = {0: 1}
pT = {0: 1}

for i in range(2, n + 1):
    pHnew = {}
    pTnew = {}

    for k in range(-(i - 1), i):
        pHnew[k] = (pT.get(k, 0) * q) + (pH.get(k - 1, 0) * p)
        pTnew[k] = (pT.get(k, 0) * q) + (pH.get(k + 1, 0) * p)

    pH = pHnew
    pT = pTnew

vals = list(pH.keys())
probs = [(pH[k] * p + pT[k] * q) for k in vals]

probA = 0
probB = 0
probDraw = 0

for score, prob in zip(vals, probs):
    if score < 0:
        probA += prob
    elif score > 0:
        probB += prob
    else:
        probDraw += prob


print(probA, probDraw, probB)