"""
Bar chart demo with pairs of bars grouped for easy comparison.
"""
import numpy as np
import matplotlib.pyplot as plt

fig,ax1= plt.subplots(figsize=(40,20))

ax2 = ax1.twinx()
#fig.subplots_adjust(bottom=0.20)

n_groups = 2
n_groups2 = 3
group = 5
data = []
target = open("./avg_analysis.txt")
for line in target:
    a = [float(x) for x in line.strip().split()]
    data.append(a)
#plt.yticks(size = 20)
full1 = data[0][0:2]
noover1 = data[1][0:2]
our1 = data[2][0:2]

full2 = data[0][2:5]
noover2 = data[1][2:5]
our2 = data[2][2:5]

index = np.arange(n_groups)
index2 = np.arange(n_groups2)
index_sum =  np.arange(group)
bar_width = 0.2

opacity = 1

xticks_1 = 0.2+index_sum + bar_width*1.5
#xticks_2 = 2+0.2+index2 + bar_width*1.5

xlbls_1 = ['Average MPKI','Throughput','Average slowdown','Fair slowdown','Max slowdown']
xlbls_2 = ['Weighted slowdown','Max slowdown','Fair slowdown']
t1 = ax1.bar(0.2+index, full1, bar_width,
                 alpha=opacity,
                 color='y',edgecolor = 'w',
                 label='Full share')

t2 = ax1.bar(0.2+index + bar_width, noover1, bar_width,
                 alpha=opacity,
                 color='k',edgecolor = 'w',
                 label='Non-overlap')

t3 = ax1.bar(0.2+index + 2*bar_width, our1, bar_width,
                 alpha=opacity,
                 color='r',edgecolor = 'w',
                 label='CAPS')

t4 = ax2.bar(0.2+index2+2, full2, bar_width,
                 alpha=opacity,
                 color='y',edgecolor = 'w',
                 label='Full share')

t5 = ax2.bar(0.2+index2+2 + bar_width, noover2, bar_width,
                 alpha=opacity,
                 color='k',edgecolor = 'w',
                 label='Non-overlap')

t6 = ax2.bar(0.2+index2+2 + 2*bar_width, our2, bar_width,
                 alpha=opacity,
                 color='r',edgecolor = 'w',
                 label='CAPS')

ax1.axis([0,5,11,16])
ax2.axis([0,5,1,2.5])
ax1.set_xlabel('Metrics',size =75)
#ax1.set_ylabel('MPKI/IPC',size = 70)
#ax1.set_yticklabels([4,6,8,10,12,14,16,18,20],size = 20)
#ax1.set_yticks(size = 20)
#ax2.set_yticks(size = 20)
#ax2.set_ylabel('Slowdown',size = 70)
ax1.set_xticks(xticks_1)
ax1.set_xticks([2],minor=True)
ax1.set_xticklabels(xlbls_1,size = 60)
#ax2.set_xticks(xticks_2)
#ax2.set_xticklabels(xlbls_2,size = 10)
#ax2.set_yticklabels(size = 20)
ax1.grid(b=True,which = 'minor',linestyle ='--',color = 'k',linewidth = 20)
#ax1.legend(loc='upper left',fontsize = '20')
ax1.set_yticks([11,12,13,14,15,16])
ax1.set_yticklabels(['11','12','13','14','15','16'],size = 65)
ax2.set_yticks([1,1.2,1.4,1.6,1.8,2.0,2.2,2.4])
ax2.set_yticklabels(['1','1.2','1.4','1.6','1.8','2.0','2.2','2.4'],size =65)
plt.legend(loc='upper center',fontsize=70,bbox_to_anchor=(0.5, 1.05),
          fancybox=True, shadow=True, ncol=3)
#plt.yticks(size = 20)

plt.tight_layout()
plt.savefig('avg_analysis.pdf')
plt.show()
