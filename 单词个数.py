
from re import split

__MAX = 10000

file_name = 'test_in.txt'

file = open(file_name, 'r')

record = {}
for line in file:
	arr = split('[ ,.\n]', line)
	for ele in arr:
		if ele == '':
			continue
		if ele in record:
			record[ele] += 1
		else:
			record[ele] = 1

for ele in record.keys():
	print (ele, ' to ', record[ele])

print ('\nsorting')

record = sorted(record.items(), key = lambda items : items[1])

print (record)

for ele in record:
	print (ele[0], ' to ', ele[1])