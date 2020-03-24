import matplotlib.pyplot as plt
import numpy as np
import csv

# ---------------------------------------------------

optimization_log_name_1 = 'optimization_logS15.csv'
optimization_log_name_2 = 'optimization_logM15.csv'
fig_name = 'Convergence.png'
# fig_name = 'Reduction.png'
plot_label_1 = 'MultiLoad-SingleAnalysis (r=1.5)'
plot_label_2 = 'MultiLoad-MultiAnalysis (r=1.5)'
plot_title = 'Response\nConvergence Graph'
# plot_title = 'Response Reduction (%)\nConvergence Graph'

# ---------------------------------------------------

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
# plt.ylabel('Response Reduction %')
plt.xticks(np.arange(0, 21, step=1))
plt.title(plot_title)
plt.legend()
plt.show()
plt.savefig(fig_name)