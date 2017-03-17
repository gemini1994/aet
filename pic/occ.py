"""
Bar chart demo with pairs of bars grouped for easy comparison.
"""
import numpy as np
import matplotlib.pyplot as plt

fig, ax = plt.subplots(figsize=(40,20))
#newax = ax.twiny()
#fig.subplots_adjust(top=0.5)

n_groups = 10
#plt.figure(figsize=(30,10))

data = []
target = open("./occ.txt")
for line in target:
    a = [float(x) for x in line.strip().split()]
    data.append(a)

ipc = data[0]
fs = data[1]
full = data[2]

index = np.arange(n_groups)
bar_width = 0.2

opacity = 1

#xticks = [2.5,7.5,12.5,17.5,22.5]
#xticks_minor = [0, 5, 10, 15, 20,25]
#xlbls = ['4','6','8','10','12']

xticks_2 = 0.2+index + bar_width*1.5
xticks_minor_2 = np.arange(24)+1
#xlbls_2 = ['20%', '40%', '50%', '60%', '80%','20%', '40%', '50%', '60%', '80%','20%', '40%', '50%', '60%', '80%','20%', '40%', '50%', '60%', '80%','20%', '40%', '50%', '60%', '80%']
#xlbls_2 = ['Q1', 'Q2', 'Q3', 'Q4', 'Q5','H1', 'H2', 'H3', 'H4', 'H5','O1', 'O2', 'O3', 'O4', 'O5','T1', 'T2', 'T3', 'T4', 'T5','P1', 'P2', 'P3', 'P4', 'P5']
xlbls_2 = ['bzip2', 'gcc', 'mcf', 'cactus', 'tonto', 'bwaves', 'zeusmp', 'leslie3d','GemsFDTD','libquantum']
#ax.set_xticks( xticks_minor, minor=True )
#newax.set_frame_on(True)
#newax.patch.set_visible(False)
#newax.set_xticks(xticks)
#newax.set_xticklabels(xlbls)
#newax.set_xticks(xticks_minor,minor = True)
#ax.set_xticks(xticks_minor,minor = True)
#ax.grid(b=True,which = 'minor',linestyle ='--')
#newax.xaxis.set_ticks_position('bottom')
#newax.xaxis.set_label_position('bottom')
#newax.spines['bottom'].set_position(('outward', 40))
#newax.grid(b=True,which = 'minor',linestyle ='--')
##newax.tick_params( axis='x', which='minor', direction='out' )

#error_config = {'ecolor': '0.3'}

t1 = ax.bar(0.2+index, full, bar_width,
                 alpha=opacity,
                 color='c',edgecolor = 'w',
                 label='Full share')

t2 = ax.bar(0.2+index + bar_width, ipc, bar_width,
                 alpha=opacity,
                 color='k',edgecolor = 'w',
                 label='Throughput')

t3 = ax.bar(0.2+index + 2*bar_width, fs, bar_width,
                 alpha=opacity,
                 color='m',edgecolor = 'w',
                 label='Fair slowdown')

ax.axis([0,10,0,30000])
#newax.axis([0,25,5,30])
#ax.set_xlabel('Core Count',size = 80)
#newax.set_xlabel('The number of benchmarks')
ax.set_ylabel('Occupancy (KB)',size = 80)
#plt.title('Metric: miss num')
ax.set_xticks(xticks_2)
ax.set_xticklabels(xlbls_2,size = 75,rotation = 50)
#ax.set_xticks(xticks_minor_2,minor = True)
#ax.tick_params( axis='x', direction='out',length = 18,which ='minor' )
#newax.tick_params( axis='x', direction='in',length = 40,which ='minor' )
#plt.legend()
plt.legend(loc='upper center',fontsize=75,bbox_to_anchor=(0.5, 1.07),
          fancybox=True, shadow=True, ncol=3)
plt.yticks(size = 75)
plt.tight_layout()
plt.savefig('occ.pdf')
#plt.show()
