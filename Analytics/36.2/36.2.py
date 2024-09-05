import itertools


def read_datasets_from_file(filename):
    data = []
    with open(filename, "r") as file:
        for _ in range(10):
            sublist_temp = list(map(float, file.readline().split()))
            sublist = [(sublist_temp[i], sublist_temp[i + 1]) for i in range(0, 36 * 2, 2)]
            data.append(sublist)
    return data

def min_square(points):
    xDiff = max(points, key=lambda p: p[0])[0] - min(points, key=lambda p: p[0])[0]
    yDiff = max(points, key=lambda p: p[1])[1] - min(points, key=lambda p: p[1])[1]
    return max(xDiff, yDiff) / 2

def process_set(points_set):
    min_radius = 1337
    for points_subset in itertools.combinations(points_set, 6):
        radius = min_square(list(points_subset))
        min_radius = min(radius, min_radius)
    return min_radius


points_sets = read_datasets_from_file('data.txt')

for set in points_sets:
    radius = process_set(set)
    print(radius)
