#Python script to plot data from CSCI 311 project 1
#pyinstaller -F plotData.py

import numpy as np
import matplotlib.pyplot as plt
import argparse

if __name__=='__main__':
  parser = argparse.ArgumentParser(description='Plot Sorting Algorithm Run Time Data')
  parser.add_argument('--data', type=str, required=True,
                      help='The file holding the run time data to be plotted')
  parser.add_argument('--case', type=str, required=True,
                      help='Best, Worst, or Average')
  parser.add_argument('--save', type=str, default='', required=False,
                      help='Save the resulting figure with this file name')
  args = parser.parse_args()

  if not (args.case in ['Best', 'Worst', 'Average']):
    print('--case must be one of Best, Worst, or Average')
    exit(0)
  
  if args.save == '': args.save = args.case+'_case_figure'
  print('Saving figures as '+args.save+'.png and '+'log_'+args.save+'.png')

  #{algorithm} -> {size} -> [times]
  times = {'Bubble Sort':{}, 'Insertion Sort':{}, 'Selection Sort':{}, 'Quicksort':{}}
  with open(args.data, 'r') as f:
    for line in f:
      l = line.strip().split(',')
      func = ''
      if l[0][0].lower()[0]=='b': func = 'Bubble Sort'
      elif l[0][0].lower()=='i': func = 'Insertion Sort'
      elif l[0][0].lower()=='s': func = 'Selection Sort'
      elif l[0][0].lower()=='q': func = 'Quicksort'
      else:
        print('Unrecognized sorting algorithm '+l[0])

      times[func][int(l[1])] = times[func].get(int(l[1]), []) + [float(l[2])]

  for s in times:
    X = sorted(times[s].keys())
    Y = [np.mean(times[s][x]) for x in X]
    E = [np.std(times[s][x]) for x in X]
    plt.errorbar(X, Y, yerr=E, capsize=5, alpha=0.5, label=s)
  plt.title(args.case+' Case Run Times')
  plt.xlabel('Size')
  plt.ylabel('Time (sec)')
  plt.legend(loc='upper left')
  plt.savefig(args.save+'.png', bbox_inches='tight')
  plt.clf()

  plt.yscale('log')
  for s in times:
    X = sorted(times[s].keys())
    Y = [np.mean(times[s][x]) for x in X]
    E = [np.std(times[s][x]) for x in X]
    plt.errorbar(X, Y, yerr=E, capsize=5, alpha=0.5, label=s)
  plt.title(args.case+' Case Run Times (log scale)')
  plt.xlabel('Size')
  plt.ylabel('Time (sec)')
  plt.legend(loc='upper left')
  plt.savefig('log_'+args.save+'.png', bbox_inches='tight')
  plt.clf()
