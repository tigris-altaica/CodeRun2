import itertools
import smallestenclosingcircle


def read_datasets_from_file(filename):
    data = []
    with open(filename, "r") as file:
        for _ in range(10):
            sublist_temp = list(map(float, file.readline().split()))
            sublist = [(sublist_temp[i], sublist_temp[i + 1]) for i in range(0, 36 * 2, 2)]
            data.append(sublist)
    return data


def process_set(points_set):
    min_radius = 1337
    for points_subset in itertools.combinations(points_set, 6):
        center_x, center_y, radius = smallestenclosingcircle.make_circle(list(points_subset))
        min_radius = min(radius, min_radius)
    return min_radius


points_sets = read_datasets_from_file('data.txt')

for set in points_sets:
    radius = process_set(set)
    print(radius)
