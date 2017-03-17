"""
Bar chart demo with pairs of bars grouped for easy comparison.
"""
import numpy as np
import matplotlib.pyplot as plt
max_yticks = 6
yloc = plt.MaxNLocator(max_yticks)
fig =  plt.subplots(figsize=(120,15))
ax = plt.subplot()

n_groups = 25

data_miss = []
target_miss = open("../D20_result/d20_miss.txt")


for line in target_miss:
    a = [float(x) for x in line.strip().split()]
    data_miss.append(a)

full_miss = data_miss[0]
noover_miss = data_miss[1]
our_miss = data_miss[2]


index = np.arange(n_groups)
bar_width = 0.2

opacity = 1


xticks_2 = 0.2+index + bar_width*1.5
xticks_minor_2 = np.arange(n_groups-1)+1
xlbls_2 = ['D1','D2','D3','D4','D5','D6','D7','D8','D9','D10','D11','D12','D13','D14','D15','D16','D17','D18','D19','D20','D21','D22','D23','D24','D25']

##############################################
#newax.set_frame_on(True)
#newax.patch.set_visible(False)
#newax.set_xticks(xticks)
#newax.set_xticklabels(xlbls)
#newax.set_xticks(xticks_minor,minor = True)
#newax.xaxis.set_ticks_position('bottom')
#newax.xaxis.set_label_position('bottom')
#newax.spines['bottom'].set_position(('outward', 40))
#newax.grid(b=True,which = 'minor',linestyle ='--')

t1 = ax.bar(0.2+index, full_miss, bar_width,
                 alpha=opacity,
                 color='y',edgecolor = 'w',
                 label='Full share')

t2 = ax.bar(0.2+index + bar_width, noover_miss, bar_width,
                 alpha=opacity,
                 color='k',edgecolor = 'w',
                 label='Non-overlap')

t3 = ax.bar(0.2+index + 2*bar_width, our_miss, bar_width,
                 alpha=opacity,
                 color='r',edgecolor = 'w',
                 label='CAPS')

ax.axis([0,25,5,25])
#newax.axis([0,25,5,30])
#ax.set_xlabel('Group ID',size=60)
#newax.set_xlabel('The number of benchmarks')
#ax.set_ylabel('Average MPKI',size=60)
ax.set_xticks(xticks_2)
plt.yticks(size = 100)
ax.set_xticklabels(xlbls_2,size=100)
#ax.set_xticks(xticks_minor_2,minor = True)
#ax.tick_params( axis='x', direction='out',length = 18,which ='minor' )
#newax.tick_params( axis='x', direction='in',length = 40,which ='minor' )
#newax.tick_params( axis='x', direction='in',length = 0,which ='major' )
ax.legend(loc='upper center',fontsize=95,bbox_to_anchor=((0.5, 1.09)),
          fancybox=True, shadow=True, ncol=3)
plt.tight_layout()
plt.savefig('d20_miss.pdf')
plt.close()
##############################################
#newax.set_frame_on(True)
#newax.patch.set_visible(False)
#newax.set_xticks(xticks)
#newax.set_xticklabels(xlbls)
#newax.set_xticks(xticks_minor,minor = True)
#newax.xaxis.set_ticks_position('bottom')
#newax.xaxis.set_label_position('bottom')
#newax.spines['bottom'].set_position(('outward', 40))
#newax.grid(b=True,which = 'minor',linestyle ='--')
yloc = plt.MaxNLocator(max_yticks)
fig =  plt.subplots(figsize=(120,15))
ax = plt.subplot()

n_groups = 25

data_ipc = []

target_ipc = open("../D20_result/d20_ipc.txt")

for line in target_ipc:
    a = [float(x) for x in line.strip().split()]
    data_ipc.append(a)

full_ipc = data_ipc[0]
noover_ipc = data_ipc[1]
our_ipc = data_ipc[2]

index = np.arange(n_groups)
bar_width = 0.2

opacity = 1


xticks_2 = 0.2+index + bar_width*1.5
xticks_minor_2 = np.arange(n_groups-1)+1
xlbls_2 = ['D1','D2','D3','D4','D5','D6','D7','D8','D9','D10','D11','D12','D13','D14','D15','D16','D17','D18','D19','D20','D21','D22','D23','D24','D25']

t1 = ax.bar(0.2+index, full_ipc, bar_width,
                 alpha=opacity,
                 color='y',edgecolor = 'w',
                 label='Full share')

t2 = ax.bar(0.2+index + bar_width, noover_ipc, bar_width,
                 alpha=opacity,
                 color='k',edgecolor = 'w',
                 label='Non-overlap')

t3 = ax.bar(0.2+index + 2*bar_width, our_ipc, bar_width,
                 alpha=opacity,
                 color='r',edgecolor = 'w',
                 label='CAPS')

ax.axis([0,25,10,18])
#newax.axis([0,25,4,18])
#ax.set_xlabel('Group ID',size=60)
#newax.set_xlabel('The number of benchmarks')
#ax.set_ylabel('IPC',size=60)
ax.yaxis.set_major_locator(yloc)
ax.set_xticks(xticks_2)
plt.yticks(size = 100)
ax.set_xticklabels(xlbls_2,size=100)
ax.legend(loc='upper center',fontsize=95,bbox_to_anchor=((0.5, 1.09)),
          fancybox=True, shadow=True, ncol=3)
plt.tight_layout()
plt.savefig('d20_ipc.pdf')
plt.close()
#ax.set_xticks(xticks_minor_2,minor = True)
#ax.tick_params( axis='x', direction='out',length = 18,which ='minor' )
#newax.tick_params( axis='x', direction='in',length = 40,which ='minor' )
#newax.tick_params( axis='x', direction='in',length = 0,which ='major' )
##############################################
#newax.set_frame_on(True)
#newax.patch.set_visible(False)
#newax.set_xticks(xticks)
#newax.set_xticklabels(xlbls)
#newax.set_xticks(xticks_minor,minor = True)
#newax.xaxis.set_ticks_position('bottom')
#newax.xaxis.set_label_position('bottom')
#newax.spines['bottom'].set_position(('outward', 40))
#newax.grid(b=True,which = 'minor',linestyle ='--')
yloc = plt.MaxNLocator(max_yticks)
fig =  plt.subplots(figsize=(120,15))
ax = plt.subplot()

n_groups = 25

data_ws = []

target_ws = open("../D20_result/d20_ws.txt")

for line in target_ws:
    a = [float(x) for x in line.strip().split()]
    data_ws.append(a)

full_ws = data_ws[0]
noover_ws = data_ws[1]
our_ws = data_ws[2]

index = np.arange(n_groups)
bar_width = 0.2

opacity = 1


xticks_2 = 0.2+index + bar_width*1.5
xticks_minor_2 = np.arange(n_groups-1)+1
xlbls_2 = ['D1','D2','D3','D4','D5','D6','D7','D8','D9','D10','D11','D12','D13','D14','D15','D16','D17','D18','D19','D20','D21','D22','D23','D24','D25']

t1 = ax.bar(0.2+index, full_ws, bar_width,
                 alpha=opacity,
                 color='y',edgecolor = 'w',
                 label='Full share')

t2 = ax.bar(0.2+index + bar_width, noover_ws, bar_width,
                 alpha=opacity,
                 color='k',edgecolor = 'w',
                 label='Non-overlap')

t3 = ax.bar(0.2+index + 2*bar_width, our_ws, bar_width,
                 alpha=opacity,
                 color='r',edgecolor = 'w',
                 label='CAPS')

ax.axis([0,25,1,1.7])
#newax.axis([0,25,1,1.9])
#ax.set_xlabel('Group ID',size=60)
#newax.set_xlabel('The number of benchmarks')
#ax.set_ylabel('Average Weighted Slowdown',size=60)
ax.set_xticks(xticks_2)
plt.yticks(size = 100)
ax.set_xticklabels(xlbls_2,size=100)
ax.legend(loc='upper center',fontsize=95,bbox_to_anchor=((0.5, 1.09)),
          fancybox=True, shadow=True, ncol=3)
plt.tight_layout()
plt.savefig('d20_ws.pdf')
plt.close()
#ax.set_xticks(xticks_minor_2,minor = True)
#ax.tick_params( axis='x', direction='out',length = 18,which ='minor' )
#newax.tick_params( axis='x', direction='in',length = 40,which ='minor' )
#newax.tick_params( axis='x', direction='in',length = 0,which ='major' )
##############################################
#newax.set_frame_on(True)
#newax.patch.set_visible(False)
#newax.set_xticks(xticks)
#newax.set_xticklabels(xlbls)
#newax.set_xticks(xticks_minor,minor = True)
#newax.xaxis.set_ticks_position('bottom')
#newax.xaxis.set_label_position('bottom')
#newax.spines['bottom'].set_position(('outward', 40))
#newax.grid(b=True,which = 'minor',linestyle ='--')
yloc = plt.MaxNLocator(max_yticks)
fig =  plt.subplots(figsize=(120,15))
ax = plt.subplot()

n_groups = 25

data_ms = []

target_ms = open("../D20_result/d20_ms.txt")

for line in target_ms:
    a = [float(x) for x in line.strip().split()]
    data_ms.append(a)

full_ms = data_ms[0]
noover_ms = data_ms[1]
our_ms = data_ms[2]

index = np.arange(n_groups)
bar_width = 0.2

opacity = 1


xticks_2 = 0.2+index + bar_width*1.5
xticks_minor_2 = np.arange(n_groups-1)+1
xlbls_2 = ['D1','D2','D3','D4','D5','D6','D7','D8','D9','D10','D11','D12','D13','D14','D15','D16','D17','D18','D19','D20','D21','D22','D23','D24','D25']

t1 = ax.bar(0.2+index, full_ms, bar_width,
                 alpha=opacity,
                 color='y',edgecolor = 'w',
                 label='Full share')

t2 = ax.bar(0.2+index + bar_width, noover_ms, bar_width,
                 alpha=opacity,
                 color='k',edgecolor = 'w',
                 label='Non-overlap')

t3 = ax.bar(0.2+index + 2*bar_width, our_ms, bar_width,
                 alpha=opacity,
                 color='r',edgecolor = 'w',
                 label='CAPS')

ax.axis([0,25,1,4])
#newax.axis([0,25,1,4.5])
#ax.set_xlabel('Group ID',size =60)
#newax.set_xlabel('The number of benchmarks')
#ax.set_ylabel('Max Weighted Slowdown',size=60)
ax.set_xticks(xticks_2)
plt.yticks(size = 100)
ax.set_xticklabels(xlbls_2,size=100)
ax.legend(loc='upper center',fontsize=95,bbox_to_anchor=((0.5, 1.09)),
          fancybox=True, shadow=True, ncol=3)
plt.tight_layout()
plt.savefig('d20_ms.pdf')
plt.close()
#ax.set_xticks(xticks_minor_2,minor = True)
#ax.tick_params( axis='x', direction='out',length = 18,which ='minor' )
#newax.tick_params( axis='x', direction='in',length = 40,which ='minor' )
#newax.tick_params( axis='x', direction='in',length = 0,which ='major' )
##############################################
#newax.set_frame_on(True)
#newax.patch.set_visible(False)
#newax.set_xticks(xticks)
#newax.set_xticklabels(xlbls)
#newax.set_xticks(xticks_minor,minor = True)
#newax.xaxis.set_ticks_position('bottom')
#newax.xaxis.set_label_position('bottom')
#newax.spines['bottom'].set_position(('outward', 40))
#newax.grid(b=True,which = 'minor',linestyle ='--')
yloc = plt.MaxNLocator(max_yticks)
fig =  plt.subplots(figsize=(120,15))
ax = plt.subplot()

n_groups = 25

data_fs = []

target_fs = open("../D20_result/d20_fs.txt")

for line in target_fs:
    a = [float(x) for x in line.strip().split()]
    data_fs.append(a)

full_fs = data_fs[0]
noover_fs = data_fs[1]
our_fs = data_fs[2]

index = np.arange(n_groups)
bar_width = 0.2

opacity = 1


xticks_2 = 0.2+index + bar_width*1.5
xticks_minor_2 = np.arange(n_groups-1)+1
xlbls_2 = ['D1','D2','D3','D4','D5','D6','D7','D8','D9','D10','D11','D12','D13','D14','D15','D16','D17','D18','D19','D20','D21','D22','D23','D24','D25']

t1 = ax.bar(0.2+index, full_fs, bar_width,
                 alpha=opacity,
                 color='y',edgecolor = 'w',
                 label='Full share')

t2 = ax.bar(0.2+index + bar_width, noover_fs, bar_width,
                 alpha=opacity,
                 color='k',edgecolor = 'w',
                 label='Non-overlap')

t3 = ax.bar(0.2+index + 2*bar_width, our_fs, bar_width,
                 alpha=opacity,
                 color='r',edgecolor = 'w',
                 label='CAPS')

ax.axis([0,25,1,1.6])
#newax.axis([0,25,1,1.9])
#ax.set_xlabel('Group ID',size =60)
#newax.set_xlabel('The number of benchmarks')
#ax.set_ylabel('Fair Weighted Slowdown',size =60)
ax.set_xticks(xticks_2)
plt.yticks(size = 100)
ax.set_xticklabels(xlbls_2,size=100)
#ax.set_xticks(xticks_minor_2,minor = True)
#ax.tick_params( axis='x', direction='out',length = 18,which ='minor' )
#newax.tick_params( axis='x', direction='in',length = 40,which ='minor' )
#newax.tick_params( axis='x', direction='in',length = 0,which ='major' )

ax.legend(loc='upper center',fontsize=95,bbox_to_anchor=((0.5, 1.09)),
          fancybox=True, shadow=True, ncol=3)
plt.tight_layout()
plt.savefig('d20_fs.pdf')
plt.close()

#plt.tight_layout()
#plt.savefig('d20_all.pdf')

#plt.show()

