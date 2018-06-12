
#read

__MAX = 10000

file_name = 'test_in.txt'

file = open(file_name, 'r')

# content = file.read()

while True:
	lines = file.readlines(__MAX)
	if not lines:
		break
	else:
		for line in lines:
			print (line.strip())

file.close()

#writ

file_name = 'test_out.txt'

file = open(file_name, 'a')

lines = ['1111', '2222']

line = '\n'.join(lines)

file.writelines(lines)
file.write(line)

file.close()

from re import split

str_ = '111@222#444@3333'

arr = split('[@#]', str_)

print (arr)

