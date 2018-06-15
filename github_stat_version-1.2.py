# -*- coding: UTF-8 -*-
# __author__ = 'hx'
# pyinstaller --console --onefile --icon=pic.ico url_test.py
# version-1.2
from urllib import request
import codecs
import re
import string
from tkinter import *


def getsubWeb(__source, __user, __codeing):
	__web_path_list = []
	response = request.urlopen(__source + __user)
	html = response.read()
	html = html.decode(__codeing)
	contain = re.split('[<> "]', html)
	for sentence in contain:
		if sentence.find(__user + '/') == 1 and sentence.count('/') < 4:
			__web_path_list.append(__source + sentence.strip('/'))
	return set(__web_path_list)


def saveFile_html(data, __save_path):
	__path = __save_path + 'html_code.dat'
	file = codecs.open(__path, 'a', 'utf8')
	file.writelines(data)
	file.write('---------------------end------------------------')
	file.close()

def getList(data):
	record = []
	contain = re.split('[<> ]', data)
	for sentence in contain:
		if sentence.find('.cpp') != -1 and sentence.find('"') == -1:
			record.append(sentence)
	return record

def saveFile_result(__web_path_list, record_list, save_path):
	__path = save_path + 'result.dat'
	file = codecs.open(__path, 'w', 'utf8')
	num = 0
	for record in record_list:
		num += len(record)
		print ('\n------------------------------------------------------------------------------')
		print ('searching: ' + __web_path_list[record_list.index(record)] + '    .cpp: ' + str(len(record)) + '\n')
		print ('list:')
		file.write('网址: ' + __web_path_list[record_list.index(record)] + '    .cpp: ' + str(len(record)) + '\n')
		file.write('list:\n')
		for item in record:
			print ('--> ' + item + '\n')
			file.write('--> ' + item + '\n\n')
	print ('总数: ' + str(num))
	print ('\n已生成:\n--> result.dat: 存放显示结果\n--> html_code.dat: 存放网页源代码')
	file.write('总数: ' + str(num) + '\n')
	file.close()


def Web_spider(__user, __save_path):
	print ('用户名: ' + __user + '\n')
	print ('保存路径: ' + __save_path[:-1] + '\n')

	if len(__save_path) == 1:
		__save_path = './'
	__codeing  = 'utf-8'   #charset
	__source = 'https://github.com/'
	__web_path_list = list(getsubWeb(__source, __user, __codeing))
	pass
	record_list = []
	for __web_path in __web_path_list:
		response = request.urlopen(__web_path)
		html = response.read()
		html = html.decode(__codeing)

		#saveFile_html(html, __save_path)
		record_list.append(getList(html))

	saveFile_result(__web_path_list, record_list, __save_path)

#GUI

root = Tk()
root.title("github提交cpp统计工具")
root.geometry('600x400')                 #是x 不是*


__user_lab = Label(root, text = "github用户名：", font = ('Consolas', 18))
__user_lab.pack()  #这里的side可以赋值为LEFT  RTGHT TOP  BOTTOM
__user_text = StringVar()
__user_win = Entry(root, textvariable = __user_text)
__user_text.set(" ")
__user_win.pack()


__save_path_lab = Label(root, text = "result保存地址：", font = ('Consolas', 18))
__save_path_lab.pack()  #这里的side可以赋值为LEFT  RTGHT TOP  BOTTOM
__save_path_text = StringVar()
__save_path_lab = Entry(root, textvariable = __save_path_text)
__save_path_text.set("./")
__save_path_lab.pack()


def on_click():
    __user = __user_text.get()
    __save_path = __save_path_text.get()
    root.destroy()
    Web_spider(__user.strip(), __save_path.strip() + '/')

Button(root, text = "确认", command = on_click, font = ('Consolas', 18)).pack()

root.mainloop()

