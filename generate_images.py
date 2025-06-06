import matplotlib.pyplot as plt
import numpy as np
import os

os.makedirs('images', exist_ok=True)



#(multiply.png)
fig, ax = plt.subplots(figsize=(6, 6))
matrix = np.random.rand(4, 4)
cax = ax.matshow(matrix, cmap='viridis')

for i in range(4):
    for j in range(4):
        ax.text(j, i, f'{matrix[i,j]:.2f}', ha='center', va='center', color='w')

plt.colorbar(cax)
plt.title('Matrix Multiplication Example', pad=20)
plt.savefig('images/multiply.png', bbox_inches='tight', dpi=300)
plt.close()

#(performance.png)
sizes = [100, 500, 1000, 2000]
ge_times = [0.1, 5.2, 42.1, 336.8]
cg_times = [0.05, 1.8, 14.3, 112.5]

plt.figure(figsize=(8, 5))
plt.plot(sizes, ge_times, 'r-', label='Gaussian Elimination')
plt.plot(sizes, cg_times, 'b--', label='Conjugate Gradient')
plt.xscale('log')
plt.yscale('log')
plt.xlabel('Matrix Size (n x n)')
plt.ylabel('Time (ms)')
plt.title('Solver Performance Comparison')
plt.legend()
plt.grid(True, which="both", ls="-")
plt.savefig('images/performance.png', bbox_inches='tight', dpi=300)
plt.close()

print("Generated to /images")