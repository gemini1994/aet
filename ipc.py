"""
Bar chart demo with pairs of bars grouped for easy comparison.
"""
import numpy as np
import matplotlib.pyplot as plt


n_groups = 5

full = (6.146879,6.711444,10.852056,11.021006,11.534335)
noover = (6.385691,6.658086,10.74476,11.198763,12.066918)
our = (6.476272,6.892457,11.594437,11.438567,12.336773)

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

plt.axis([0,5,4,13])
plt.xlabel('Number of workload')
plt.ylabel('Value')
plt.title('Metric: IPC')
plt.xticks(0.2+index + bar_width*1.5, ('4', '6', '8', '10', '12'))
#plt.legend()
plt.legend(loc='upper left')

plt.tight_layout()
plt.show()
