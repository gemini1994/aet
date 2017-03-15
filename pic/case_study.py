import numpy as np
import matplotlib.pyplot as plt

plt.figure(figsize=(30,15))
ax = plt.subplot();


ax.broken_barh([(20, 800)], (3, 0.2), facecolors='k',edgecolor = 'w',label ='IPC')
ax.broken_barh([(60, 760)], (3.2, 0.2), facecolors='r',edgecolor = 'w',label='Weighted Slowdown')

ax.broken_barh([(100, 400)], (3.9, 0.2), facecolors='k',edgecolor = 'w')
ax.broken_barh([(20, 400)], (4.1, 0.2), facecolors='r',edgecolor = 'w')

ax.broken_barh([(260, 240)], (4.8, 0.2), facecolors='k',edgecolor = 'w')
ax.broken_barh([(100, 240)], (5, 0.2), facecolors='r',edgecolor = 'w')

ax.broken_barh([(300, 160)], (5.7, 0.2), facecolors='k',edgecolor = 'w')
ax.broken_barh([(100, 40)], (5.9, 0.2), facecolors='r',edgecolor = 'w')

ax.broken_barh([(340, 80)], (6.6, 0.2), facecolors='k',edgecolor = 'w')
ax.broken_barh([(260, 40)], (6.8, 0.2), facecolors='r',edgecolor = 'w')

ax.broken_barh([(340, 80)], (7.5, 0.2), facecolors='k',edgecolor = 'w')
ax.broken_barh([(140, 160)], (7.7, 0.2), facecolors='r',edgecolor = 'w')

ax.broken_barh([(260, 40)], (8.4, 0.2), facecolors='k',edgecolor = 'w')
ax.broken_barh([(140, 40)], (8.6, 0.2), facecolors='r',edgecolor = 'w')

ax.broken_barh([(260, 40)], (9.3, 0.2), facecolors='k',edgecolor = 'w')
ax.broken_barh([(140, 40)], (9.5, 0.2), facecolors='r',edgecolor = 'w')

ax.broken_barh([(300, 40)], (10.2, 0.2), facecolors='k',edgecolor = 'w')
ax.broken_barh([(60, 160)], (10.4, 0.2), facecolors='r',edgecolor = 'w')

ax.broken_barh([(460, 40)], (11.1, 0.2), facecolors='k',edgecolor = 'w')
ax.broken_barh([(100, 120)], (11.3, 0.2), facecolors='r',edgecolor = 'w')

ax.set_ylim(2.3, 12)
ax.set_xlim(0, 840)
ax.set_xlabel('scheme',size = 35)

ax.set_xticks([40,80,120,160,200,240,280,320,360,400,440,480,520,560,600,640,680,720,760,800]);
ax.set_xticklabels([ 'w1', 'w2', 'w3', 'w4','w5','w6','w7','w8','w9','w10','w11','w12','w13','w14','w15','w16','w17','w18','w19','w20'],size=30)
ax.set_yticks([3.2,4.1,5,5.9,6.8,7.7,8.6,9.5,10.4,11.3])
ax.set_yticklabels(['omnetpp','cactusADM','lbm','bwaves','zeusmp','GemsFDTD','libquantum','milc','gobmk','sjeng'],size=30)
ax.set_xticks([20,60,100,140,180,220,260,300,340,380,420,460,500,540,580,620,660,700,740,780],minor = True)
ax.tick_params(axis='x',length=0)

ax.grid(axis='x',linestyle='-.',which = 'minor')
plt.legend(loc = 'upper right',fontsize = 35)
plt.tight_layout()
plt.savefig('case_study.pdf')
plt.show()
