import matplotlib.pyplot as plt

# Hardcoded values from perf CSVs

threads = [1, 2, 4, 8]

execution_time = [359.42, 332.71, 312.24, 332.78]

context_switches = [0, 0, 0, 0]

cpu_cycles = [0, 0, 0, 0]   # VM does not support hardware CPU cycle counters

# Graph 1
plt.figure(figsize=(6,4))
plt.plot(threads, execution_time, marker='o', linewidth=2)
plt.title("Thread Count vs Execution Time")
plt.xlabel("Thread Count")
plt.ylabel("Execution Time (ms)")
plt.grid(True)
plt.savefig("execution_time.png")
plt.close()

# Graph 2
plt.figure(figsize=(6,4))
plt.plot(threads, context_switches, marker='o', linewidth=2)
plt.title("Thread Count vs Context Switches")
plt.xlabel("Thread Count")
plt.ylabel("Context Switches")
plt.grid(True)
plt.savefig("context_switches.png")
plt.close()

# Graph 3
plt.figure(figsize=(6,4))
plt.plot(threads, cpu_cycles, marker='o', linewidth=2)
plt.title("Thread Count vs CPU Cycles")
plt.xlabel("Thread Count")
plt.ylabel("CPU Cycles")
plt.grid(True)
plt.savefig("cpu_cycles.png")
plt.close()

print("All graphs generated successfully.")
