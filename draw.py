import matplotlib.pyplot as plt       
import matplotlib.patches as patches
from PIL import Image
import numpy as np
import re
data_path = r'C:\Users\Admin\LSHADE\data\test_realworld.inp'
img = Image.open(r'C:\Users\Admin\LSHADE\lab.png')
# plt.title("Sensor & Target Visualization")

with open(data_path, 'r') as f:
    lines = [line.strip() for line in f.readlines()]
    
result_path = r'C:\Users\Admin\LSHADE\result\result_realworld.out0'
with open(result_path, 'r', encoding='utf-8') as f:
    result_text = f.read()
# Extract Activation vector
active_match = re.search(r'Activation vector:\s*\[([^\]]+)\]', result_text)
if active_match:
    active = [int(x.strip()) for x in active_match.group(1).split(',')]
else:
    raise ValueError("Activation vector not found in result_realworld.out0")

# Extract Sensor angle
angle_match = re.search(r'Sensor angle:\s*\[([^\]]+)\]', result_text)
if angle_match:
    angles = [float(x.strip()) for x in angle_match.group(1).split(',')]
else:
    raise ValueError("Sensor angle not found in result_realworld.out0")
sensor_angle = float(lines[0])
sensor_radius = float(lines[1])
field_width, field_height = map(float, lines[2].split(','))
num_targets = int(lines[3])
num_sensors = int(lines[4])


targets = []
for i in range(5, 5 + num_targets):
    x, y, _ = map(float, lines[i].split(','))
    targets.append((x, y))


# Đọc tọa độ sensor
sensors = []
for i in range(5 + num_targets, 5 + num_targets + num_sensors):
    x, y = map(float, lines[i].split(','))
    sensors.append((x, y))
    
plt.figure(figsize=(12, 12))
# plt.imshow(img)
plt.axis('off')
ax = plt.gca()

# ...existing code...



# fig, ax = plt.subplots(figsize=(10, 10))
# ax.set_xlim(0, width)
# ax.set_ylim(0, height)
# ax.set_aspect('equal')

# Vẽ target (ngôi sao đỏ)
for (x, y) in targets:
    ax.plot(x, y, marker='*', color='red', markersize=12)
# Draw points and numbers
for (i,(x, y)) in enumerate(sensors):
    # ax.plot(x, y, 'ko', markersize=3)  # chấm đen
    if (active[i]):
        ax.plot(x, y, 'ko', markersize=3)
        circle = patches.Circle((x, y), sensor_radius, color='skyblue', alpha=0.3)
        ax.add_patch(circle)
        center_deg = np.degrees(angles[i])
        theta1 = center_deg- sensor_angle / 2
        theta2 = center_deg + sensor_angle / 2
        wedge = patches.Wedge((x, y), sensor_radius, theta1, theta2, facecolor='blue', alpha=0.3)
        ax.add_patch(wedge)
    else:
        ax.plot(x, y, 'ko', markersize=3)
plt.imshow(img)

plt.title("Sensor & Target Visualization")

plt.tight_layout()
plt.show()