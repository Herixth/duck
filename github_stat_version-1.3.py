# -*- coding: UTF-8 -*-
# __author__ = 'hx'
# pyinstaller --console --onefile --icon=pic.ico url_test.py
# version-1.3
from urllib import request
import codecs
import re
import string
from tkinter import *
from tkinter import ttk
import ctypes
import sys
import webbrowser
from tkinter.scrolledtext import ScrolledText
import time

#控制cmd窗口显示 param->True/False
def Hid_or_show(param):
	whnd = ctypes.windll.kernel32.GetConsoleWindow()
	ctypes.windll.user32.ShowWindow(whnd, param)
	ctypes.windll.kernel32.CloseHandle(whnd)

class Interface:
	def __init__(self):
		pass

	def show(self):
		file_type_list = []
		def on_click():
			__notice_lab.place(x = 620, y = 418)
			__notice_lab.update()
			time.sleep(0.1)
			confir.update()
			scroll.config(state = 'normal')
			scroll.delete(0.0, END)
			scroll.update()
			_stat_scroll.config(state = 'normal')
			_stat_scroll.delete(0.0, END)
			_stat_scroll.update()
			__file_type = []
			for inc in range(len(vector)):
				if vector[inc] != 0:
					__file_type.append(file_type[inc][0])
			__user = __user_text.get()
			__save_path = __save_path_text.get()
			if __save_path.find('(') != -1:
				__save_path = './'
			if len(__user.strip()) != 0:
				Web_spider(__user.strip(), __save_path.strip() + '/', __file_type, scroll, _stat_scroll)
			__notice_lab.place_forget()
			__notice_lab.update()
			scroll.config(state = 'disabled')
			scroll.update()
			_stat_scroll.config(state = 'disabled')
			_stat_scroll.update()
		def on_click_quit():
			sys.exit(0)
			root.quit()
			pass
		pass #画布 分割线
		canvas = Canvas(root, width = 900, height = 500, bg = '#cfcaca')
		canvas.create_rectangle(540, 0, 545, 500, outline = 'white', fill = 'white')
		canvas.pack()
		pass #copyright
		__copyright_lab = Label(root, text = "Copyright © 2018 HX.All Rights Reserved.", font = ('Consolas', 8), fg = '#494949', bg = '#cfcaca')
		__copyright_lab.place(x = 608, y = 460)
		pass #文本01
		__user_lab = Label(root, text = "github用户名：", font = ('新宋体', 14), fg = '#494949', bg = '#cfcaca')
		__user_lab.place(x = 50, y = 30)
		__user_text = StringVar()
		__user_win = Entry(root,textvariable=__user_text,borderwidth=3,width=20,font=('Consolas',13),fg='#494949',background='#fbf3bb',insertwidth=1,relief='flat')
		__user_text.set('')
		__user_win.place(x = 50, y = 64)
		pass #文本02
		__save_path_lab = Label(root, text = "result保存地址：", font = ('新宋体', 14), fg = '#494949', bg = '#cfcaca')
		__save_path_lab.place(x = 50, y = 123)
		__save_path_text = StringVar()
		__save_path_win = Entry(root,textvariable=__save_path_text,borderwidth=3,width=20,font=('Consolas',13),fg = '#494949',background='#fbf3bb',insertwidth=1,relief='flat')
		__save_path_text.set("(默认路径为当前目录)")
		__save_path_win.place(x = 50, y = 156)
		pass #文本 stat
		__stat_lab = Label(root, text = "统计结果：", font = ('新宋体', 14), fg = '#494949', bg = '#cfcaca')
		__stat_lab.place(x = 50, y = 220)
		pass #notice
		__notice_lab = Label(root, text = "正在处理数据,请等待大约15s...", font = ('Melon', 12), fg = 'red', bg = '#cfcaca')
		__notice_lab.place_forget()
		pass #复合选项
		file_type = [('.cpp', '1'), ('.c', '2'), ('.h', '3'), ('.py', '4'), ('.txt', '5')]
		file_type_choice = Label(root, text = "搜索文件种类:", font = ('新宋体', 14), fg = '#494949', bg = '#cfcaca')
		file_type_choice.place(x = 350, y = 30)

		vector = []
		for type_, val in file_type:
			vector.append(IntVar())
			check = Checkbutton(root,text=type_,font=('Melon',12),variable=vector[int(val)-1],fg='#494949',selectcolor='#f3f3b2',bg='#cfcaca',activebackground='#cfcaca',activeforeground='#494949')
			check.select()
			check.place(x=350,y=30+27*int(val))
		pass #按钮01 02
		confir = Button(root,text="确认",command=on_click,font=('Consolas',18,'bold'),borderwidth=3,fg='#f0f0f0',bg='#6dea58',relief=RAISED,bd=2,activebackground='#6dea58',activeforeground='#f0f0f0')
		confir.place(x=120,y=420)
		exits = Button(root,text="退出",command=on_click_quit,font=('Consolas',18,'bold'),borderwidth=3,fg='#f0f0f0',bg='#ff0000',relief=RAISED,bd=2,activebackground='#ff0000',activeforeground='#f0f0f0')
		exits.place(x=330,y=420)
		pass #显示界面
		frame = Frame(height = 400, width = 350,bg = '#cfcaca')
		Label(frame, text = '搜索结果:', fg = '#494949',bg = '#cfcaca', font = ('新宋体', 14)).pack()
		frame.place(x = 578, y = 30)
		pass
		scroll = ScrolledText(root, width = 35, height = 21, font = ('新宋体', 12))
		scroll.config(state = 'disabled')
		scroll.place(x = 578, y = 64)
		_stat_scroll = ScrolledText(root, width = 52, height = 8.5, font = ('新宋体', 12))
		_stat_scroll.place(x = 50, y = 255)
		pass
def getsubWeb(__source, __user, __codeing):
	__web_path_list = []
	response = request.urlopen(__source + __user)
	html = response.read()
	html = html.decode(__codeing)
	contain = re.split('[<>"]', html)
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

def find_type(__file_type, sentence):
	if (sentence.find('"') == -1):
		for _type in __file_type:
			if (sentence.find(_type) != -1) and len(sentence.strip()) != 0:
				return _type
	return False

def getList(data, __file_type, web_to_num):
	record = []
	contain = re.split('[<>]', data)
	for sentence in contain:
		type__ = find_type(__file_type, sentence)
		if type__ != False:
			record.append(sentence)
			web_to_num[type__] += 1
	return record

def saveFile_result(__web_path_list, record_list, save_path):
	__path = save_path + 'result.dat'
	file = codecs.open(__path, 'w', 'utf8')
	num = 0
	for record in record_list:
		num += len(record)
		file.write('网址: ' + __web_path_list[record_list.index(record)] + '    .cpp: ' + str(len(record)) + '\n')
		file.write('list:\n')
		for item in record:
			file.write('--> ' + item + '\n\n')
	file.write('总数: ' + str(num) + '\n')
	file.close()

def Set_text(text, record, repository):
	text.insert(END, '_________________________\n>>> 库: ' + repository + '\nlist:\n')
	for line in record:
			time.sleep(0.1)
			text.update()
			text.insert(END, '-> ' + line +'\n')
			text.see(END)
			text.update()
	if len(record) == 0:
		text.insert(END, '->  没有目标文件\n')
	time.sleep(0.1)
	text.insert(END, '\n>>>_____计: ' + str(len(record)) + ' 份\n')
	text.see(END)
	text.update()
	pass

def Set_stat_text(repository_list, stat_text, every_detail, total):
	stat_text.insert(END, '>>> 总计:\n    |-> 目标文件总数: %d\n    |-> 库数目: %d\n' % (total, len(repository_list)))
	for repository_ in repository_list:
		stat_text.insert(END, '    |   |-> %s\n' % (repository_))
	stat_text.insert(END, '>>> 按文件类型统计:\n')
	file_num = len(every_detail[0])
	stat_text.insert(END, '    | 文件类型:       数目:   \n')
	for type_ in every_detail[0]:
		nums = 0
		type_t = type_
		for inc in range(6 - len(type_)):
			type_t += ' '
		for inc in range(len(every_detail)):
			nums += every_detail[inc][type_]
		stat_text.insert(END, '    |-> %s         %d\n' % (type_t, nums))
	stat_text.insert(END, '>>> 按库统计:\n')
	for num_ in range(len(repository_list)):
		stat_text.insert(END, '    |-> 库: %s\n' % repository_list[num_])
		stat_text.insert(END, '    |        |-> 文件类型:       数目:   \n')
		for type_ in every_detail[num_]:
			type_t = type_
			for inc in range(12 - len(type_)):
				type_t += ' '
			stat_text.insert(END, '    |        |->  %s    %d\n' % (type_t, every_detail[num_][type_]))

def Web_spider(__user, __save_path, __file_type, text, stat_text):

	if len(__save_path) == 1:
		__save_path = './'
	__codeing  = 'utf-8'   #charset
	__source = 'https://github.com/'
	__web_path_list = list(getsubWeb(__source, __user, __codeing))
	pass
	record_list = []
	every_detail = []
	repository_list = []
	total = 0
	for __web_path in __web_path_list:
		web_to_num = {}
		for __type in __file_type:
			web_to_num[__type] = 0
		response = request.urlopen(__web_path)
		html = response.read()
		html = html.decode(__codeing)
		newrecord = getList(html, __file_type, web_to_num)
		record_list.append(newrecord)
		every_detail.append(web_to_num)
		total += len(newrecord)
		Set_text(text, newrecord, __web_path.split(__user + '/')[1])
		repository_list.append(__web_path.split(__user + '/')[1])
	text.insert(END, '\n______________<END>________________\n')
	Set_stat_text(repository_list, stat_text, every_detail, total)
	saveFile_result(__web_path_list, record_list, __save_path)

#GUI
Hid_or_show(False)
if_click = False
root = Tk()
root.title("github提交文件统计工具")
root.geometry('900x500')                 #是x 不是*
root.resizable(width=False, height=False)

display = Interface()
display.show()

#webbrowser.open('http://www.fishc.com')
root.mainloop()