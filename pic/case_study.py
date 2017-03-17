import numpy as np
import matplotlib.pyplot as plt

plt.figure(figsize=(50,30))
ax = plt.subplot();


ax.broken_barh([(460, 360)], (3, 0.2), facecolors='k',edgecolor = 'w',label ='Throughput')
ax.broken_barh([(180, 480)], (3.2, 0.2), facecolors='y',edgecolor = 'w',label='Fair slowdown')

ax.broken_barh([(20, 800)], (3.9, 0.2), facecolors='k',edgecolor = 'w')
ax.broken_barh([(500, 320)], (4.1, 0.2), facecolors='y',edgecolor = 'w')

ax.broken_barh([(260, 320)], (4.8, 0.2), facecolors='k',edgecolor = 'w')
ax.broken_barh([(20, 280)], (5, 0.2), facecolors='y',edgecolor = 'w')

ax.broken_barh([(140, 560)], (5.7, 0.2), facecolors='k',edgecolor = 'w')
ax.broken_barh([(60, 480)], (5.9, 0.2), facecolors='y',edgecolor = 'w')

ax.broken_barh([(220, 440)], (6.6, 0.2), facecolors='k',edgecolor = 'w')
ax.broken_barh([(500, 80)], (6.8, 0.2), facecolors='y',edgecolor = 'w')

ax.broken_barh([(460, 80)], (7.5, 0.2), facecolors='k',edgecolor = 'w')
ax.broken_barh([(700, 80)], (7.7, 0.2), facecolors='y',edgecolor = 'w')

ax.broken_barh([(540, 80)], (8.4, 0.2), facecolors='k',edgecolor = 'w')
ax.broken_barh([(340, 40)], (8.6, 0.2), facecolors='y',edgecolor = 'w')

ax.broken_barh([(500, 160)], (9.3, 0.2), facecolors='k',edgecolor = 'w')
ax.broken_barh([(620, 160)], (9.5, 0.2), facecolors='y',edgecolor = 'w')

ax.broken_barh([(460, 160)], (10.2, 0.2), facecolors='k',edgecolor = 'w')
ax.broken_barh([(300, 80)], (10.4, 0.2), facecolors='y',edgecolor = 'w')

ax.broken_barh([(540, 40)], (11.1, 0.2), facecolors='k',edgecolor = 'w')
ax.broken_barh([(740, 40)], (11.3, 0.2), facecolors='y',edgecolor = 'w')

ax.set_ylim(2.3, 12)
ax.set_xlim(0, 840)
ax.set_xlabel('Cache way',size = 80)

ax.set_xticks([40,80,120,160,200,240,280,320,360,400,440,480,520,560,600,640,680,720,760,800]);
ax.set_xticklabels([ '1', '2', '3', '4','5','6','7','8','9','10','11','12','13','14','15','16','17','18','19','20'],size=70)
ax.set_yticks([3.2,4.1,5,5.9,6.8,7.7,8.6,9.5,10.4,11.3])
ax.set_yticklabels(['bzip2', 'gcc', 'mcf', 'cactus', 'tonto', 'bwaves', 'zeusmp', 'leslie3d','GemsFDTD','libquantum'],size=70)
ax.set_xticks([20,60,100,140,180,220,260,300,340,380,420,460,500,540,580,620,660,700,740,780,820],minor = True)
ax.tick_params(axis='x',length=0)

ax.grid(axis='x',linestyle='-.',which = 'minor')
plt.legend(loc = 'upper left',fontsize = 80)
plt.tight_layout()
plt.savefig('case_study.pdf')
plt.show()
