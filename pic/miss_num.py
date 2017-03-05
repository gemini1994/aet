"""
Bar chart demo with pairs of bars grouped for easy comparison.
"""
import numpy as np
import matplotlib.pyplot as plt


n_groups = 5

full = (85930.503608,241119.370014,328890.573427,345684.220963,389572.347411)
noover = (97052.772263,233983.301449,295947.512126,291415.800283,372827.967787)
our = (83194.427746,144651.145743,275739.734104,169939.576720,329741.911765)

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


plt.xlabel('Number of workload')
plt.ylabel('Times(K/s)')
plt.title('Metric: miss num')
plt.xticks(0.2+index + bar_width*1.5, ('4', '6', '8', '10', '12'))
#plt.legend()
plt.legend(loc='upper left')

plt.tight_layout()
plt.show()
