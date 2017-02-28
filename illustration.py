import numpy as np
import matplotlib.pyplot as plt


n_groups = 2

over = (0.415268,0.967625)
noover = (0.421380,0.912704)
full = (0.347465,0.954963)

#fig, ax = plt.subplots()

index = np.arange(n_groups)
bar_width = 0.2

index_2 = (40,80,120,160);
opacity = 0.4
ax = plt.subplot(1,2,1);

ax.broken_barh([(20, 160)], (26, 1), facecolors='g')
ax.broken_barh([(20, 160)], (24, 1), facecolors='y')

ax.broken_barh([(20, 80)], (18, 1), facecolors='g')
ax.broken_barh([(100, 80)], (16, 1), facecolors='y')

ax.broken_barh([(20, 120)], (10, 1), facecolors='g')
ax.broken_barh([(60, 120)], (8, 1), facecolors='y')

ax.set_ylim(5, 30)
ax.set_xlim(0, 200)
ax.set_xlabel('scheme')
ax.set_yticks([8.5,10.5,16.5,18.5,24.5,26.5])
ax.set_yticklabels(['omnetpp', 'lbm','omnetpp','lbm','omnetpp','lbm'])
ax.set_xticks([20,60,100,140,180]);


ax.set_xticklabels(['w0', 'w1', 'w2', 'w3', 'w4'])
ax.grid(axis='x',linestyle='-.')
#plt.xticks(index_2, ('w1','w2','w3','w4'))
ax.annotate('full-contention', (62, 22),fontsize=14)
ax.annotate('non-overlap', (62, 14),fontsize=14)
ax.annotate('overlap', (72, 6),fontsize=14)

plt.subplot(1,2,2);
rects1 = plt.bar(0.3+index, full, bar_width,
                 alpha=opacity,
                 color='blue',
                 label='full-contention')

rects2 = plt.bar(0.3+index+bar_width, noover, bar_width,
                 alpha=0.4,
                 color='red',
                 label='non-overlap')

rects3 = plt.bar(0.3+index+bar_width*2, over, bar_width,
                 alpha=0.4,
                 color='yellow',
                 label='overlap')


plt.axis([0,2,0.3,1])
plt.xlabel('Illustration of omnetpp and lbm')
plt.ylabel('IPC')
plt.xticks(0.2+index + bar_width*1.5, ('omnetpp', 'lbm'))
#plt.legend()
plt.legend(loc='upper left')

plt.tight_layout()
plt.show()
