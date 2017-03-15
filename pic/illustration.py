import numpy as np
import matplotlib.pyplot as plt


n_groups = 3

#over = (0.415268,0.967625)
#noover = (0.421380,0.912704)
#full = (0.347465,0.954963)
omnetpp = (0.347465,0.415268,0.421380)
lbm = (0.954963,0.912704,0.967625)

#fig, ax = plt.subplots()
plt.figure(figsize=(15,8))
index = np.arange(n_groups)
bar_width = 0.2

index_2 = (40,80,120,160);
opacity = 0.9
ax = plt.subplot(1,2,1);

ax.broken_barh([(20, 160)], (21, 1), facecolors='K',edgecolor = 'w',label = 'omnetpp')
ax.broken_barh([(20, 160)], (23, 1), facecolors='R',edgecolor = 'w',label = 'lbm')

ax.broken_barh([(100, 80)], (15, 1), facecolors='K',edgecolor = 'w')
ax.broken_barh([(20, 80)], (17, 1), facecolors='R',edgecolor = 'w')

ax.broken_barh([(60, 120)], (9, 1), facecolors='K',edgecolor = 'w')
ax.broken_barh([(20, 120)], (11, 1), facecolors='R',edgecolor = 'w')


ax.set_ylim(5, 30)
ax.set_xlim(0, 200)
#ax.set_xlabel('Scheme',size = 25)
#ax.set_yticks([8.5,10.5,16.5,18.5,24.5,26.5])
#ax.set_yticklabels(['omnetpp', 'lbm','omnetpp','lbm','omnetpp','lbm'])
ax.set_xticks([40,80,120,160]);
ax.set_xticklabels([ 'Way1', 'Way2', 'Way3', 'Way4'],size=20)
ax.set_yticklabels([])
ax.set_xticks([20,60,100,140,180],minor = True)
ax.tick_params(axis='both',length=0)

ax.grid(axis='x',linestyle='-.',which = 'minor')
#plt.xticks(index_2, ('w1','w2','w3','w4'))
ax.annotate('Full-share:', (21, 25),fontsize=20)
ax.annotate('Non-overlap:', (21, 19),fontsize=20)
ax.annotate('Overlap:', (21, 13),fontsize=20)
plt.legend(loc='upper left',fontsize = 20)

plt.subplot(1,2,2);
#rects1 = plt.bar(0.3+index, full, bar_width,
#                 alpha=opacity,
#                 color='blue',
#                 label='full-contention')

#rects2 = plt.bar(0.3+index+bar_width, noover, bar_width,
#                 alpha=0.4,
#                 color='red',
#                 label='non-overlap')

#rects3 = plt.bar(0.3+index+bar_width*2, over, bar_width,
#                 alpha=0.4,
#                 color='yellow',
#                 label='overlap')
p1 = plt.bar(0.3+index*0.5, lbm, bar_width,
            alpha=opacity,
            color='k',
            label='omnetpp',
            edgecolor = 'w')
p2 = plt.bar(0.3+index*0.5, omnetpp, bar_width,bottom=lbm,
            alpha=opacity,
            color='r',
            edgecolor = 'w',
            label='lbm')
plt.axis([0.15,1.65,0.8,1.5])
#plt.xlabel('Illustration of omnetpp and lbm',size = 25)
plt.ylabel('IPC',size = 25)
plt.yticks(size = 20)
plt.xticks(0.3+index*0.5 + bar_width*0.5, ('Full-share', 'Non-overlap','Overlap'),size = 20)
#plt.legend()
plt.legend(loc='upper left',fontsize = 20)

plt.tight_layout()
plt.savefig('illus.pdf')
plt.show()
