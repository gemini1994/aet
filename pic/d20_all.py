"""
Bar chart demo with pairs of bars grouped for easy comparison.
"""
import numpy as np
import matplotlib.pyplot as plt
max_yticks = 6
yloc = plt.MaxNLocator(max_yticks)
fig =  plt.subplots(figsize=(50,30))
ax = plt.subplot(5,1,1)
ax_ipc = plt.subplot(5,1,2)
ax_ws = plt.subplot(5,1,3)
ax_ms = plt.subplot(5,1,4)
ax_fs = plt.subplot(5,1,5)

#newax = ax.twiny()
#newax_ipc = ax_ipc.twiny()
#newax_ws = ax_ws.twiny()
#newax_ms = ax_ms.twiny()
#newax_fs = ax_fs.twiny()
#fig.subplots_adjust(bottom=0.20)

n_groups = 25
#plt.figure(figsize=(30,10))

data_miss = []
data_ipc = []
data_ws = []
data_ms = []
data_fs = []

target_miss = open("../D20_result/d20_miss.txt")
target_ipc = open("../D20_result/d20_ipc.txt")
target_ws = open("../D20_result/d20_ws.txt")
target_ms = open("../D20_result/d20_ms.txt")
target_fs = open("../D20_result/d20_fs.txt")

for line in target_miss:
    a = [float(x) for x in line.strip().split()]
    data_miss.append(a)
for line in target_ipc:
    a = [float(x) for x in line.strip().split()]
    data_ipc.append(a)
for line in target_ws:
    a = [float(x) for x in line.strip().split()]
    data_ws.append(a)
for line in target_ms:
    a = [float(x) for x in line.strip().split()]
    data_ms.append(a)
for line in target_fs:
    a = [float(x) for x in line.strip().split()]
    data_fs.append(a)

full_miss = data_miss[0]
noover_miss = data_miss[1]
our_miss = data_miss[2]

full_ipc = data_ipc[0]
noover_ipc = data_ipc[1]
our_ipc = data_ipc[2]

full_ws = data_ws[0]
noover_ws = data_ws[1]
our_ws = data_ws[2]

full_ms = data_ms[0]
noover_ms = data_ms[1]
our_ms = data_ms[2]

full_fs = data_fs[0]
noover_fs = data_fs[1]
our_fs = data_fs[2]

index = np.arange(n_groups)
bar_width = 0.2

opacity = 1

#xticks = [2.5,7.5,12.5,17.5,22.5]
#xticks_minor = [0, 5, 10, 15, 20,25]
#xlbls = ['4','6','8','10','12']

xticks_2 = 0.2+index + bar_width*1.5
xticks_minor_2 = np.arange(n_groups-1)+1
xlbls_2 = ['D1','D2','D3','D4','D5','D6','D7','D8','D9','D10','D11','D12','D13','D14','D15','D16','D17','D18','D19','D20','D21','D22','D23','D24','D25']
#ax.set_xticks( xticks_minor, minor=True )
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
                 label='full share')

t2 = ax.bar(0.2+index + bar_width, noover_miss, bar_width,
                 alpha=opacity,
                 color='k',edgecolor = 'w',
                 label='best non-overlap')

t3 = ax.bar(0.2+index + 2*bar_width, our_miss, bar_width,
                 alpha=opacity,
                 color='r',edgecolor = 'w',
                 label='our algorithm')

ax.axis([0,25,5,30])
#newax.axis([0,25,5,30])
ax.set_xlabel('Group ID')
#newax.set_xlabel('The number of benchmarks')
ax.set_ylabel('Average MPKI')
ax.set_xticks(xticks_2)
ax.set_xticklabels(xlbls_2)
#ax.set_xticks(xticks_minor_2,minor = True)
#ax.tick_params( axis='x', direction='out',length = 18,which ='minor' )
#newax.tick_params( axis='x', direction='in',length = 40,which ='minor' )
#newax.tick_params( axis='x', direction='in',length = 0,which ='major' )
ax.legend(loc='upper center',fontsize='large',bbox_to_anchor=(0.5, 1.05),
          fancybox=True, shadow=True, ncol=3)
##############################################
#newax_ipc.set_frame_on(True)
#newax_ipc.patch.set_visible(False)
#newax_ipc.set_xticks(xticks)
#newax_ipc.set_xticklabels(xlbls)
#newax_ipc.set_xticks(xticks_minor,minor = True)
#newax_ipc.xaxis.set_ticks_position('bottom')
#newax_ipc.xaxis.set_label_position('bottom')
#newax_ipc.spines['bottom'].set_position(('outward', 40))
#newax_ipc.grid(b=True,which = 'minor',linestyle ='--')

t1 = ax_ipc.bar(0.2+index, full_ipc, bar_width,
                 alpha=opacity,
                 color='y',edgecolor = 'w',
                 label='full share')

t2 = ax_ipc.bar(0.2+index + bar_width, noover_ipc, bar_width,
                 alpha=opacity,
                 color='k',edgecolor = 'w',
                 label='best non-overlap')

t3 = ax_ipc.bar(0.2+index + 2*bar_width, our_ipc, bar_width,
                 alpha=opacity,
                 color='r',edgecolor = 'w',
                 label='our algorithm')

ax_ipc.axis([0,25,10,18])
#newax_ipc.axis([0,25,4,18])
ax_ipc.set_xlabel('Group ID')
#newax_ipc.set_xlabel('The number of benchmarks')
ax_ipc.set_ylabel('IPC')
ax_ipc.yaxis.set_major_locator(yloc)
ax_ipc.set_xticks(xticks_2)
ax_ipc.set_xticklabels(xlbls_2)
#ax_ipc.set_xticks(xticks_minor_2,minor = True)
#ax_ipc.tick_params( axis='x', direction='out',length = 18,which ='minor' )
#newax_ipc.tick_params( axis='x', direction='in',length = 40,which ='minor' )
#newax_ipc.tick_params( axis='x', direction='in',length = 0,which ='major' )
##############################################
#newax_ws.set_frame_on(True)
#newax_ws.patch.set_visible(False)
#newax_ws.set_xticks(xticks)
#newax_ws.set_xticklabels(xlbls)
#newax_ws.set_xticks(xticks_minor,minor = True)
#newax_ws.xaxis.set_ticks_position('bottom')
#newax_ws.xaxis.set_label_position('bottom')
#newax_ws.spines['bottom'].set_position(('outward', 40))
#newax_ws.grid(b=True,which = 'minor',linestyle ='--')

t1 = ax_ws.bar(0.2+index, full_ws, bar_width,
                 alpha=opacity,
                 color='y',edgecolor = 'w',
                 label='full share')

t2 = ax_ws.bar(0.2+index + bar_width, noover_ws, bar_width,
                 alpha=opacity,
                 color='k',edgecolor = 'w',
                 label='best non-overlap')

t3 = ax_ws.bar(0.2+index + 2*bar_width, our_ws, bar_width,
                 alpha=opacity,
                 color='r',edgecolor = 'w',
                 label='our algorithm')

ax_ws.axis([0,25,1,1.9])
#newax_ws.axis([0,25,1,1.9])
ax_ws.set_xlabel('Group ID')
#newax_ws.set_xlabel('The number of benchmarks')
ax_ws.set_ylabel('Average Weighted Slowdown')
ax_ws.set_xticks(xticks_2)
ax_ws.set_xticklabels(xlbls_2)
#ax_ws.set_xticks(xticks_minor_2,minor = True)
#ax_ws.tick_params( axis='x', direction='out',length = 18,which ='minor' )
#newax_ws.tick_params( axis='x', direction='in',length = 40,which ='minor' )
#newax_ws.tick_params( axis='x', direction='in',length = 0,which ='major' )
##############################################
#newax_ms.set_frame_on(True)
#newax_ms.patch.set_visible(False)
#newax_ms.set_xticks(xticks)
#newax_ms.set_xticklabels(xlbls)
#newax_ms.set_xticks(xticks_minor,minor = True)
#newax_ms.xaxis.set_ticks_position('bottom')
#newax_ms.xaxis.set_label_position('bottom')
#newax_ms.spines['bottom'].set_position(('outward', 40))
#newax_ms.grid(b=True,which = 'minor',linestyle ='--')

t1 = ax_ms.bar(0.2+index, full_ms, bar_width,
                 alpha=opacity,
                 color='y',edgecolor = 'w',
                 label='full share')

t2 = ax_ms.bar(0.2+index + bar_width, noover_ms, bar_width,
                 alpha=opacity,
                 color='k',edgecolor = 'w',
                 label='best non-overlap')

t3 = ax_ms.bar(0.2+index + 2*bar_width, our_ms, bar_width,
                 alpha=opacity,
                 color='r',edgecolor = 'w',
                 label='our algorithm')

ax_ms.axis([0,25,1,4.5])
#newax_ms.axis([0,25,1,4.5])
ax_ms.set_xlabel('Group ID')
#newax_ms.set_xlabel('The number of benchmarks')
ax_ms.set_ylabel('Max Weighted Slowdown')
ax_ms.set_xticks(xticks_2)
ax_ms.set_xticklabels(xlbls_2)
#ax_ms.set_xticks(xticks_minor_2,minor = True)
#ax_ms.tick_params( axis='x', direction='out',length = 18,which ='minor' )
#newax_ms.tick_params( axis='x', direction='in',length = 40,which ='minor' )
#newax_ms.tick_params( axis='x', direction='in',length = 0,which ='major' )
##############################################
#newax_fs.set_frame_on(True)
#newax_fs.patch.set_visible(False)
#newax_fs.set_xticks(xticks)
#newax_fs.set_xticklabels(xlbls)
#newax_fs.set_xticks(xticks_minor,minor = True)
#newax_fs.xaxis.set_ticks_position('bottom')
#newax_fs.xaxis.set_label_position('bottom')
#newax_fs.spines['bottom'].set_position(('outward', 40))
#newax_fs.grid(b=True,which = 'minor',linestyle ='--')

t1 = ax_fs.bar(0.2+index, full_fs, bar_width,
                 alpha=opacity,
                 color='y',edgecolor = 'w',
                 label='full share')

t2 = ax_fs.bar(0.2+index + bar_width, noover_fs, bar_width,
                 alpha=opacity,
                 color='k',edgecolor = 'w',
                 label='best non-overlap')

t3 = ax_fs.bar(0.2+index + 2*bar_width, our_fs, bar_width,
                 alpha=opacity,
                 color='r',edgecolor = 'w',
                 label='our algorithm')

ax_fs.axis([0,25,1,1.9])
#newax_fs.axis([0,25,1,1.9])
ax_fs.set_xlabel('Group ID')
#newax_fs.set_xlabel('The number of benchmarks')
ax_fs.set_ylabel('Fair Weighted Slowdown')
ax_fs.set_xticks(xticks_2)
ax_fs.set_xticklabels(xlbls_2)
#ax_fs.set_xticks(xticks_minor_2,minor = True)
#ax_fs.tick_params( axis='x', direction='out',length = 18,which ='minor' )
#newax_fs.tick_params( axis='x', direction='in',length = 40,which ='minor' )
#newax_fs.tick_params( axis='x', direction='in',length = 0,which ='major' )



plt.tight_layout()
plt.savefig('d20_all.pdf')
ax_ipc.savefig('tmp.pdf')
#plt.show()

