
# def get_population(country):
# 	return country[2]

# get_population = lambda country : country[2]

countries = []
file = open("countries_zh.csv", "r")

arr = []
for line in file:
	line = line.strip()
	arr  = line.split(";")
	name = arr[1]
	capt = arr[3]
	popu = int(arr[4])
	countries.append( (name, capt, popu) )

countries.sort(key = lambda country : country[2])

for country in countries:
	for tuplp_ in country:
		print(tuplp_, end = ' ')
	print (end = '\n')

#复合函数
def quadratic(a, b, c):
	return lambda x : a * x * x + b * x + c

f = quadratic(1, -1, 2)

print ('f(2) = ', f(2))

