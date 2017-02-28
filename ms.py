"""
Bar chart demo with pairs of bars grouped for easy comparison.
"""
import numpy as np
import matplotlib.pyplot as plt


n_groups = 5

full = (2.162500,2.049812,2.213502,3.641645,3.792985)
noover = (1.537049,1.591737,2.027160,2.689738,3.384776)
our = (1.536712,1.677283,1.827634,2.401375,2.984929)

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

plt.axis([0,5,1,4])
plt.xlabel('Number of workload')
plt.ylabel('Value')
plt.title('Metric: Max weighted slowdown')
plt.xticks(0.2+index + bar_width*1.5, ('4', '6', '8', '10', '12'))
#plt.legend()
plt.legend(loc='upper left')

plt.tight_layout()
plt.show()
