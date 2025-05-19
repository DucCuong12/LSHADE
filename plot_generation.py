import matplotlib.pyplot as plt                      

qbi1 = r'C:\Users\Admin\LSHADE\result\qbi.txt'
qbi2 = r'C:\Users\Admin\LSHADE\result_batch_6\qbi.txt'
qbi3 = r'C:\Users\Admin\LSHADE\result_14_gen\qbi.txt'

with open(qbi1, 'r') as f:
    data1 = f.readlines()
with open(qbi2, 'r') as f:
    data2 = f.readlines()
with open(qbi3, 'r') as f:
    data3 = f.readlines()

def frange(start, stop, step):
    while start < stop:
        yield start
        start += step

# Chỉ lấy các giá trị của Generation chia hết cho 50
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

generations1, values1 = extract_values(data1)
generations2, values2 = extract_values(data2)
generations3, values3 = extract_values(data3)

plt.plot(generations1, values1, marker='o', markersize=3, color = 'green', label='H = 10')
plt.plot(generations2, values2, marker='s', markersize=3, color = 'red', label='H = 8')
plt.plot(generations3, values3, marker='^', markersize=3, color = 'blue', label='H = 6')

plt.xlabel('Generation')
plt.ylabel('QBI')
plt.ylim(0.84, 0.96)
plt.xlim(-50, 1000)
plt.title('Value of H')

plt.legend()
plt.grid(True)
plt.show()