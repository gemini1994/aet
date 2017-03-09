"""
Bar chart demo with pairs of bars grouped for easy comparison.
"""
import numpy as np
import matplotlib.pyplot as plt

fig, ax = plt.subplots(figsize=(30,10))
newax = ax.twiny()
fig.subplots_adjust(bottom=0.20)

n_groups = 25
#plt.figure(figsize=(30,10))

data = []
target = open("./fs.txt")
for line in target:
    a = [float(x) for x in line.strip().split()]
    data.append(a)

full1 = data[0]
noover1 = data[1]
our1 = data[2]

index = np.arange(n_groups)
bar_width = 0.2

opacity = 0.4

xticks = [2.5,7.5,12.5,17.5,22.5]
xticks_minor = [0, 5, 10, 15, 20,25]
xlbls = ['4','6','8','10','12']

xticks_2 = 0.2+index + bar_width*1.5
xticks_minor_2 = np.arange(24)+1
xlbls_2 = ['20%', '40%', '50%', '60%', '80%','20%', '40%', '50%', '60%', '80%','20%', '40%', '50%', '60%', '80%','20%', '40%', '50%', '60%', '80%','20%', '40%', '50%', '60%', '80%']
#ax.set_xticks( xticks_minor, minor=True )
newax.set_frame_on(True)
newax.patch.set_visible(False)
newax.set_xticks(xticks)
newax.set_xticklabels(xlbls)
newax.set_xticks(xticks_minor,minor = True)
newax.xaxis.set_ticks_position('bottom')
newax.xaxis.set_label_position('bottom')
newax.spines['bottom'].set_position(('outward', 40))
newax.grid(b=True,which = 'minor',linestyle ='--')
#newax.tick_params( axis='x', which='minor', direction='out' )

#error_config = {'ecolor': '0.3'}

ax.bar(0.2+index, full1, bar_width,
                 alpha=opacity,
                 color='b',
                 label='full share')

ax.bar(0.2+index + bar_width, noover1, bar_width,
                 alpha=opacity,
                 color='r',
                 label='best non-overlap')

ax.bar(0.2+index + 2*bar_width, our1, bar_width,
                 alpha=opacity,
                 color='y',
                 label='our algorithm')

ax.axis([0,25,1,1.9])
newax.axis([0,25,1,1.9])
ax.set_xlabel('Percentage of sensitive workload')
newax.set_xlabel('The number of benchmarks')
ax.set_ylabel('Fair Weighted Slowdown')
#plt.title('Metric: miss num')
ax.set_xticks(xticks_2)
ax.set_xticklabels(xlbls_2)
ax.set_xticks(xticks_minor_2,minor = True)
ax.tick_params( axis='x', direction='out',length = 18,which ='minor' )
newax.tick_params( axis='x', direction='in',length = 40,which ='minor' )
#plt.legend()
ax.legend(loc='upper left')

plt.tight_layout()
plt.show()
