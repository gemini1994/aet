"""
Bar chart demo with pairs of bars grouped for easy comparison.
"""
import numpy as np
import matplotlib.pyplot as plt


n_groups = 5

full = (1.415037,1.302205,1.335026,1.537177,1.817994)
noover = (1.216415,1.294208,1.333964,1.474165,1.759627)
our = (1.209769,1.290039,1.253458,1.470854,1.753704)

#fig, ax = plt.subplots()

index = np.arange(n_groups)
bar_width = 0.2

opacity = 0.4
#error_config = {'ecolor': '0.3'}

rects1 = plt.bar(0.2+index, full, bar_width,
                 alpha=opacity,
                 color='b',
                 label='full share')

rects2 = plt.bar(0.2+index + bar_width, noover, bar_width,
                 alpha=opacity,
                 color='r',
                 label='best non-overlap')

rects3 = plt.bar(0.2+index + 2*bar_width, our, bar_width,
                 alpha=opacity,
                 color='y',
                 label='our algorithm')

plt.axis([0,5,1,2])
plt.xlabel('Number of workload')
plt.ylabel('Value')
plt.title('Metric: weighted slowdown')
plt.xticks(0.2+index + bar_width*1.5, ('4', '6', '8', '10', '12'))
#plt.legend()
plt.legend(loc='upper left')

plt.tight_layout()
plt.show()
