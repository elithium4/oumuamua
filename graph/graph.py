import pylab
from sys import argv


def draw_graph(position, name, x_label, y_label, xEx_data, yEx_data, xMod_data, yMod_data):
    pylab.subplot(*position)
    pylab.plot(xMod_data, yMod_data, linestyle='-', marker='o', color='red')
    pylab.plot(xEx_data, yEx_data, linestyle='-', marker='o', color='green')
    pylab.title(name)
    pylab.xlabel(x_label)
    pylab.ylabel(y_label)
    pylab.grid(True)


if len(argv) > 1 and argv[1] == "bary":
    graph_name = "bary"
    file_model = open("../data/model_bary.txt", "r")
    file_example = open("graph_bary_equatorial.txt", "r")
else:
    graph_name = "geo"
    file_model = open("../data/model_geo.txt", "r")
    file_example = open("graph_geo_equatorial.txt", "r")

model_time = []
model_x = []
model_y = []
model_z = []

ex_time = []
ex_x = []
ex_y = []
ex_z = []

for line in file_model:
    data = line.strip().split()
    model_time.append(float(data[0]))
    model_x.append(float(data[1]))
    model_y.append(float(data[2]))
    model_z.append(float(data[3]))

for line in file_example:
    data = line.strip().split()
    ex_time.append(float(data[0]))
    ex_x.append(float(data[1]))
    ex_y.append(float(data[2]))
    ex_z.append(float(data[3]))

file_model.close()
file_example.close()

draw_graph((3, 1, 1), f"X ({graph_name})", "Time", "X", ex_time, ex_x, model_time, model_x)
draw_graph((3, 1, 2), f"Y ({graph_name})", "Time", "Y", ex_time, ex_y, model_time, model_y)
draw_graph((3, 1, 3), f"Z ({graph_name})", "Time", "Z", ex_time, ex_z, model_time, model_z)
pylab.show()
