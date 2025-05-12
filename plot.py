import matplotlib.pyplot as plt                      

qbi = r'C:\Users\Admin\LSHADE\result\qbi.txt'

with open(qbi, 'r') as f:
    data = f.readlines()
def frange(start, stop, step):
    while start < stop:
        yield start
        start += step
# Chỉ lấy các giá trị của Generation chia hết cho 50
values = []
generations = []
for i in range(len(data)):
    data[i] = data[i].replace(f"Generation {i}: ", '')
    if i % 30 == 0:  # Chỉ lấy các dòng chia hết cho 50
        try:
            value = round(float(data[i].strip()), 6)
            values.append(value)
            generations.append(i)  # Lưu lại chỉ số Generation
        except ValueError:
            print(f"Skipping invalid data at line {i}: {data[i]}")

# Vẽ biểu đồ
plt.plot(generations, values, marker='o', linestyle='-', color='b', label='QBI Value', markersize=4)
plt.xlabel('Generation')
plt.ylabel('QBI')
# plt.title('Data Plot (Generations divisible by 50)')
plt.ylim(0.88, 0.98)  # Giới hạn trục y từ 0.88 đến 1
plt.yticks([round(i, 2) for i in list(frange(0.88, 0.99, 0.01))])  # Tạo khoảng cách 0.01 trên trục y

plt.legend()
plt.grid(True)
plt.show()