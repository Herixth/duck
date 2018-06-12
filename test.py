from urllib import request

if __name__ == "__main__":
	response = request.urlopen('http://www.4399.com/flash/18012.htm')
	html = response.readlines(10000)
	print (html)
	