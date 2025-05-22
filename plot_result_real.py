import json 
import matplotlib.pyplot as plt
with open(r'C:\Users\Admin\LSHADE\result\qbi.txt', 'r') as f:
    data = f.readlines()
def extract_values(data, step=50):
    values = []
    generations = []
    for i in range(len(data)):
        data[i] = data[i].replace(f"Generation {i}: ", '')
        if i % step == 0:
            try:
                value = round(float(data[i].strip()), 6)
                values.append(value)
                generations.append(i)
            except ValueError:
                print(f"Skipping invalid data at line {i}: {data[i]}")
    return generations, values
generations1, values1 = extract_values(data)
plt.plot(generations1, values1, marker='o', markersize=3, color = 'green', label='H = 10')
plt.xlabel('Generation')
plt.ylabel('QBI')
plt.ylim(0.68, 0.8)

plt.legend()
plt.grid(True)
plt.show()
