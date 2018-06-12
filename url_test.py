# -*- coding: UTF-8 -*-
from urllib import request
import codecs

def saveFile(data):
	__path = './url_code.dat'
	file = codecs.open(__path, 'w', 'utf8')
	file.writelines(data)
	# for line in data:
	# 	line.decode(__codeing)
	# 	file.write(line)
	file.close()

if __name__ == '__main__':
	__web_path = 'https://blog.csdn.net/c406495762/article/details/58716886'
	__codeing  = 'utf-8'   #charset
	response = request.urlopen(__web_path)
	html = response.read()
	html = html.decode(__codeing)
	print (html)
	print ('********************************************************************')
	print (type(response))
	print ('********************************************************************')
	print (response.geturl())
	print ('********************************************************************')
	print (response.info())
	print ('********************************************************************')
	print (response.getcode())

	saveFile(html)