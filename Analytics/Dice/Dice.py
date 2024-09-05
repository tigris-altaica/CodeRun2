from math import isclose
import numpy as np

p1 = 1 / 6
p2 = 2 / 6
p3 = 3 / 6

transition_matrix = np.array([[p2 + p3, p1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
                              [p3, p1, p2, 0, 0, 0, 0, 0, 0, 0, 0, 0],
                              [p2, p1, 0, p3, 0, 0, 0, 0, 0, 0, 0, 0],
                              [p2 + p3, 0, 0, 0, p1, 0, 0, 0, 0, 0, 0, 0],
                              [p3, p1, 0, 0, 0, p2, 0, 0, 0, 0, 0, 0],
                              [p2, 0, 0, p3, 0, 0, p1, 0, 0, 0, 0, 0],
                              [p3, p1, 0, 0, 0, 0, 0, p2, 0, 0, 0, 0],
                              [p2, p1, 0, 0, 0, 0, 0, 0, p3, 0, 0, 0],
                              [p2 + p3, 0, 0, 0, 0, 0, 0, 0, 0, p1, 0, 0],
                              [p3, p1, 0, 0, 0, 0, 0, 0, 0, 0, p2, 0],
                              [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
                              [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1]])

num_repeats = 10
transition_matrix_power = np.linalg.matrix_power(transition_matrix, num_repeats)
math_exp = 0.0
prev_math_exp = -1.0

while not isclose(math_exp, prev_math_exp, abs_tol=1e-11, rel_tol=0):
    prev_math_exp = math_exp
    math_exp += num_repeats * transition_matrix_power[0][10]
    transition_matrix_power = transition_matrix_power @ transition_matrix
    num_repeats += 1

print(math_exp)