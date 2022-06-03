import pylab
from sys import argv


def draw_graph(position, name, x_label, y_label, x_data, y_data, color, dotType):
    pylab.subplot(*position)
    pylab.plot(x_data, y_data, linestyle='-', marker=dotType, color=color)
    pylab.title(name)
    pylab.xlabel(x_label)
    pylab.ylabel(y_label)
    pylab.grid(True)

#def draw_graph(position, name, x_label, y_label, xEx_data, yEx_data, xMod_data, yMod_data):
##    pylab.subplot(*position)
#    pylab.plot(xMod_data, yMod_data, linestyle='-', marker='o', color='red')
##    pylab.plot(xEx_data, yEx_data, linestyle='-', marker='o', color='green')
#    pylab.title(name)
#    pylab.xlabel(x_label)
#    pylab.ylabel(y_label)
#    pylab.grid(True)

def graph_cartesian(graph_name, args, file_model, file_base):
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

    for line in file_base:
        data = line.strip().split()
        ex_time.append(float(data[0]))
        ex_x.append(float(data[1]))
        ex_y.append(float(data[2]))
        ex_z.append(float(data[3]))
    
    if args["jpl_needed"]:
        file_jpl = open("../debug/convert_result.txt", "r")
        orbit_x = []
        orbit_y = []
        orbit_z = []
        orbit_time = []
        for line in file_jpl:
            data = line.strip().split()
            orbit_time.append(float(data[0]))
            orbit_x.append(float(data[1]))
            orbit_y.append(float(data[2]))
            orbit_z.append(float(data[3]))
        draw_graph((3, 1, 1), f"X ({graph_name})", "Time", "X", orbit_time, orbit_x, "yellow", "")
        draw_graph((3, 1, 2), f"Y ({graph_name})", "Time", "Y", orbit_time, orbit_y, "yellow", "")
        draw_graph((3, 1, 3), f"Z ({graph_name})", "Time", "Z", orbit_time, orbit_z, "yellow", "")
        file_jpl.close()

    if args["full_orbit_needed"]:
        file_full = open("../debug/orbit.txt", "r")
        full_x = []
        full_y = []
        full_z = []
        full_time = []
        for line in file_full:
            data = line.strip().split()
            full_time.append(float(data[0]))
            full_x.append(float(data[1]))
            full_y.append(float(data[2]))
            full_z.append(float(data[3]))
        draw_graph((3, 1, 1), f"X ({graph_name})", "Time", "X", full_time, full_x, "pink", "")
        draw_graph((3, 1, 2), f"Y ({graph_name})", "Time", "Y", full_time, full_y, "pink", "")
        draw_graph((3, 1, 3), f"Z ({graph_name})", "Time", "Z", full_time, full_z, "pink", "")
        file_full.close()

    if args["earth_orbit_needed"]:
        earth_jpl = open("../debug/earth_for_graph.txt", "r")
        earth_x = []
        earth_y = []
        earth_z = []
        earth_time = []
        for line in earth_jpl:
            data = line.strip().split()
            earth_time.append(float(data[0]))
            earth_x.append(float(data[1]))
            earth_y.append(float(data[2]))
            earth_z.append(float(data[3]))
        draw_graph((3, 1, 1), f"X ({graph_name})", "Time", "X", earth_time, earth_x, "blue", "")
        draw_graph((3, 1, 2), f"Y ({graph_name})", "Time", "Y", earth_time, earth_y, "blue", "")
        draw_graph((3, 1, 3), f"Z ({graph_name})", "Time", "Z", earth_time, earth_z, "blue", "")
        earth_jpl.close()
    
    draw_graph((3, 1, 1), f"X ({graph_name})", "Time", "X", ex_time, ex_x, "green", "o")
    draw_graph((3, 1, 1), f"X ({graph_name})", "Time", "X", model_time, model_x, "red", "o")
    draw_graph((3, 1, 2), f"Y ({graph_name})", "Time", "Y", ex_time, ex_y, "green", "o")
    draw_graph((3, 1, 2), f"Y ({graph_name})", "Time", "Y", model_time, model_y, "red", "o")
    draw_graph((3, 1, 3), f"Z ({graph_name})", "Time", "Z", ex_time, ex_z, "green", "o")
    draw_graph((3, 1, 3), f"Z ({graph_name})", "Time", "Z", model_time, model_z, "red", "o")


def graph_cel(graph_name, args, file_model, file_base):
    model_time = []
    model_long = []
    model_lat = []

    ex_time = []
    ex_long = []
    ex_lat = []

    for line in file_model:
        data = line.strip().split()
        model_time.append(float(data[0]))
        model_long.append(float(data[1]))
        model_lat.append(float(data[2]))
    
    for line in file_base:
        data = line.strip().split()
        ex_time.append(float(data[0]))
        ex_long.append(float(data[1]))
        ex_lat.append(float(data[2]))
    
    draw_graph((2, 1, 1), f"RA ({graph_name})", "Time", "RA", ex_time, ex_long, "green", "o")
    draw_graph((2, 1, 1), f"RA ({graph_name})", "Time", "RA", model_time, model_long, "red", "o")
    draw_graph((2, 1, 2), f"DEC ({graph_name})", "Time", "DEC", ex_time, ex_lat, "green", "o")
    draw_graph((2, 1, 2), f"DEC ({graph_name})", "Time", "DEC", model_time, model_lat, "red", "o")

def make_graph(type, graph_name, args, model_file, base_file):
    file_model = open(model_file, "r")
    file_base = open(base_file, "r")
    if type == "dec":
        graph_cartesian(graph_name, args, file_model, file_base)
    else:
        graph_cel(graph_name, args, file_model, file_base)
    pylab.show() 
    file_model.close()
    file_base.close()




jpl_needed = False
earth_orbit_needed = False
full_orbit_needed = False

if len(argv) > 1:
    args = {"jpl_needed": False, "earth_orbit_needed": False, "full_orbit_needed": False}
    if "bary" in argv:
        if "earth" in argv:
            args["earth_orbit_needed"] = True
        if "full" in argv:
            args["full_orbit_needed"] = True
        graph_name = "bary"
        make_graph("dec", graph_name, args, "../data/model_bary.txt", "graph_bary_equatorial.txt")
    elif "geo" in argv:
        graph_name = "geo"
        if "jpl" in argv:
            args["jpl_needed"] = True
        make_graph("dec", graph_name, args, "../data/model_geo.txt", "graph_geo_equatorial.txt")
    elif "sph" in argv:
        graph_name = "celestial"
        make_graph("sph", graph_name, args, "../data/spherical_model.txt", "../data/spherical_base.txt")
    else:
        print("Неопознанный аргумент")
else:
    print("Не задан тип графика")     


#if len(argv) > 1 and "bary" in argv:
#    if "earth" in argv:
#        earth_orbit_needed = True
#    if "full" in argv:
#        full_orbit_needed = True
#    graph_name = "bary"
#    file_model = open("../data/model_bary.txt", "r")
#    file_example = open("graph_bary_equatorial.txt", "r")
#else:
#    if "jpl" in argv:
#        jpl_needed = True
#    graph_name = "geo"
#    file_model = open("../data/model_geo.txt", "r")
#    file_example = open("graph_geo_equatorial.txt", "r")

