from struct import *
import png
import os

file_name = "heightmap_0"
height_map_file = open(file_name + ".bin", mode="rb")
height_map_data = height_map_file.read()
file_size = os.path.getsize(file_name + ".bin")

min_z = 99999999
max_z = -99999999

z_positions = []

heightmap_dimensions_offset = 8
offset = 0

height_map_dimensions = unpack("ii", height_map_data[:heightmap_dimensions_offset])

for i in range(0, int(file_size/12)):
    position = unpack("fff", height_map_data[heightmap_dimensions_offset + offset : heightmap_dimensions_offset + offset + 12])
    offset += 12
    if (position[0] == 0 and position[1] == 0 and position[2] == 0):
        z_positions.append(z_positions[-1])
        continue
    else:
        z_positions.append(position[2])
    
    if (position[2] < min_z):
        min_z = position[2]
    if (position[2] > max_z):
        max_z = position[2];

z_values = []
for position in z_positions:
    z_value = int((position - min_z)/(max_z - min_z) * (65536-1))
    z_values.append(z_value)

counter = 0
img = []
for y in range(0, height_map_dimensions[0]):
    row = []
    for x in range(0, height_map_dimensions[1]):
        row.append(z_values[counter])
        counter += 1
    img.append(row)
with open(file_name + ".png", 'wb') as f:
    w = png.Writer(height_map_dimensions[1], height_map_dimensions[0], greyscale=True, bitdepth=16)
    w.write(f, img)