import matplotlib.pyplot as plt
import numpy as np
import csv

# ---------------------------------------------------

# optimization_log_name_1 = 'optimization_logS075.csv'
# optimization_log_name_2 = 'optimization_logS15.csv'
# optimization_log_name_3 = 'optimization_logS30.csv'
# optimization_log_name_4 = 'optimization_logS60.csv'
optimization_log_name_1 = 'optimization_logM075.csv'
optimization_log_name_2 = 'optimization_logM15.csv'
optimization_log_name_3 = 'optimization_logM30.csv'
optimization_log_name_4 = 'optimization_logM60.csv'
# fig_name = 'Radius_Convergence_Single.png'
fig_name = 'Radius_Reduction_Multi.png'
plot_label_1 = 'r=0.75'
plot_label_2 = 'r=1.5'
plot_label_3 = 'r=3.0'
plot_label_4 = 'r=6.0'
# plot_title = 'Response\nConvergence Graph'
# plot_title = 'Response Reduction (%)\nMultiLoad - Single Analysis Graph'
plot_title = 'Response Reduction (%)\nMultiLoad - Multi Analysis Graph'

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

# plt.plot(x,y, 'b8-', linewidth=2, markersize=5, label= plot_label_1)
plt.plot(x,z, 'b8-', linewidth=2, markersize=5, label= plot_label_1)

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

# plt.plot(x,y, 'r*--', linewidth=2, markersize=6, label= plot_label_2)
plt.plot(x,z, 'r*--', linewidth=2, markersize=6, label= plot_label_2)

with open(optimization_log_name_3, 'r') as csvfile:
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

# plt.plot(x,y, 'b8-', linewidth=2, markersize=6.5, label= plot_label_3)
plt.plot(x,z, 'gD-.', linewidth=2, markersize=6.5, label= plot_label_3)

with open(optimization_log_name_4, 'r') as csvfile:
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

# plt.plot(x,y, 'r*--', linewidth=2, markersize=6, label= plot_label_4)
plt.plot(x,z, 'P:', linewidth=2, markersize=6, label= plot_label_4)

plt.xlabel('Iterations')
# plt.ylabel('Response Value')
plt.ylabel('Response Reduction %')
plt.xticks(np.arange(0, 21, step=1))
plt.title(plot_title)
plt.legend()
plt.show()
plt.savefig(fig_name)