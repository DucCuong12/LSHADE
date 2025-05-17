from PIL import Image
import numpy as np
import matplotlib.pyplot as plt

# Load image
img = Image.open(r'C:\Users\Admin\LSHADE\lab.png')
width, height = img.size
print(f"Width: {width}, Height: {height}")
# Read positions from pos.txt
positions = []
with open(r'C:\Users\Admin\LSHADE\pos.txt', 'r', encoding='utf-8') as f:
    for line in f:
        if "Clicked at (" in line:
            # Extract x, y from "Clicked at (x, y)"
            part = line.split("Clicked at (")[1].split(")")[0]
            x, y = map(int, part.split(','))
            positions.append((x, y))

# Plot image
plt.figure(figsize=(12, 12))
plt.imshow(img)
plt.axis('off')
ax = plt.gca()
print(positions)

# Draw points and numbers
for i, (x, y) in enumerate(positions):
    plt.plot(x, y, 'ro', markersize=1)
    circle = plt.Circle((x, y), 100, color='blue', fill=False, linewidth=1)
    ax.add_patch(circle)
    # Draw number
    plt.text(x, y, str(i), color='black', fontsize=8, ha='center', va='center')
plt.tight_layout()
plt.show()