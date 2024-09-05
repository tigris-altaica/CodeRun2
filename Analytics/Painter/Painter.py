import csv
import matplotlib.pyplot as plt
import math


def euclidean_distance(point1, point2):
    x1, y1 = point1
    x2, y2 = point2
    distance = math.sqrt((x2 - x1)**2 + (y2 - y1)**2)
    return distance

# Считываем координаты точек из CSV файла
x_coords = []
y_coords = []

i = 0
with open('path.csv', 'r') as file:
    reader = csv.reader(file)
    for row in reader:
        if i in {7, 27, 20, 21, 22, 45, 73}:
            i += 1
            continue
        x_coords.append(float(row[0]))
        y_coords.append(float(row[1]))
        i += 1


# Рисуем точки на плоскости
for i, (x, y) in enumerate(zip(x_coords, y_coords)):
    plt.scatter(x, y)
    plt.text(x, y, str(i), fontsize=8, ha='center', va='bottom')

distance = 0
# Соединяем точки линиями
for i in range(len(x_coords) - 1):
    distance += euclidean_distance((x_coords[i], y_coords[i]), (x_coords[i + 1], y_coords[i + 1]))
    plt.plot([x_coords[i], x_coords[i+1]], [y_coords[i], y_coords[i+1]], 'ro-')


print(distance / 1000)

plt.show()