from PIL import Image
import numpy as np
import matplotlib.pyplot as plt

# Load image
img = Image.open(r'C:\Users\Admin\LSHADE\lab.png')
width, height = img.size
print(f"Width: {width}, Height: {height}")
# Read positions from pos.txt
positions = []
targets = []
# Read positions from pos.txt and pos1.txt
with open(r'C:\Users\Admin\LSHADE\pos.txt', 'r', encoding='utf-8') as f:
    for line in f:
        if "Clicked at (" in line:
            # Extract x, y from "Clicked at (x, y)"
            part = line.split("Clicked at (")[1].split(")")[0]
            x, y = map(int, part.split(','))
            positions.append((x, y))
with open(r'C:\Users\Admin\LSHADE\pos1.txt', 'r', encoding='utf-8') as f:
    for line in f:
        if "Clicked at (" in line:
            # Extract x, y from "Clicked at (x, y)"
            part = line.split("Clicked at (")[1].split(")")[0]
            x, y = map(int, part.split(','))
            targets.append((x, y))
# Plot image
plt.figure(figsize=(12, 12))
plt.imshow(img)
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
for i, (x, y) in enumerate(positions):
    plt.plot(x, y, 'ro', markersize=1)
    # circle = plt.Circle((x, y), 100, color='blue', fill=False, linewidth=1)
    # ax.add_patch(circle)
    # # Draw number
    plt.text(x, y, str(i), color='black', fontsize=8, ha='center', va='center')
plt.tight_layout()
plt.show()


# Write to test_realworld.inp
with open('data/test_realworld.inp', 'w', encoding='utf-8') as f:
    f.write('90\n')
    f.write('100\n')
    f.write('900,467\n')
    f.write(f'{len(targets)}\n')
    f.write(f'{len(positions)}\n')
    # Write targets: (x, y, a) with a = 1 for each target
    for (x, y) in targets:
        u = np.random.randint(1, 3)
        f.write(f'{x},{y},{u}\n')
    # Write sensors: (x, y)
    for (x, y) in positions:
        f.write(f'{x},{y}\n')