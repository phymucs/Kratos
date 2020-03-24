import matplotlib.pyplot as plt
import csv

# ---------------------------------------------------

optimization_log_name_1 = 'optimization_log_S.csv'
optimization_log_name_2 = 'optimization_log_M.csv'
fig_name = 'Convergence.png'
plot_label_1 = 'MultiLoad-SingleAnalysis'
plot_label_2 = 'MultiLoad-MultiAnalysis'
plot_title = 'Response\nConvergence Graph'

# ---------------------------------------------------

x = []
y = []
with open(optimization_log_name_1, 'r') as csvfile:
    reader = csv.reader(csvfile, delimiter=',')
    lineN = 0
    x = []
    y = []
    z = []
    for line in reader:
        lineN += 1
        if lineN != 1:
            x.append(int(line[0]))
            y.append(float(line[1]))
            z.append(float(line[2]))

plt.plot(x,y, 'b8-', linewidth=2, markersize=6.5, label= plot_label_1)
# plt.plot(x,z, 'b8-', linewidth=2, markersize=6.5, label= plot_label_1)

with open(optimization_log_name_2, 'r') as csvfile:
    reader = csv.reader(csvfile, delimiter=',')
    lineN = 0
    x = []
    y = []
    z = []
    for line in reader:
        lineN += 1
        if lineN != 1:
            x.append(int(line[0]))
            y.append(float(line[1]))
            z.append(float(line[2]))

plt.plot(x,y, 'r*--', linewidth=2, markersize=6, label= plot_label_2)
# plt.plot(x,z, 'r*--', linewidth=2, markersize=6, label= plot_label_2)

plt.xlabel('Iterations')
plt.ylabel('Response Value')
plt.title(plot_title)
plt.legend()
plt.show()
plt.savefig(fig_name)