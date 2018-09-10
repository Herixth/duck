# -*- coding = 'utf-8'
# __author__ = 'hx'
# __date__   = 2018/7/9
# python2 

from urllib2 import *
from bs4 import BeautifulSoup
from re import *

urls = ['xkcd.com/1883/', 'xkcd.com/1884/']
head = 'https://www.'

patt = r'src=".+?\.(jpg|png)" title="(.+?)"'

def get_html(url):
    return urlopen(head + url).read()

def print_html(html):
    print html

def get_pictitle(html, url):
    pics = findall(patt, html)
    #soup = BeautifulSoup(html, 'html.parser')
    print '---- web: ' + url + '----'
    #print soup.select('title')
    for pic in pics:
        print 'title: ' + pic[1]

if __name__ == '__main__':
    for url in urls:
        html = get_html(url)
        #print_html(html)
        get_pictitle(html, url)
    pass


