#!/usr/bin/env python
# -*- coding: utf-8 -*-
import enchant
d = enchant.request_dict("fr_FR")
#x= "en organisation le savent — lk est d'une extrême banalité. Des person fait bonjour hello"
x="eu l’occasion d‘évo"

#1.deliminate the ordinair errors, there are two kinds of ord err: 1,we have to delete it 2,we have to replace it
# for the first kind we delete them first
#2.for the second kind of err, we can correct them before check it by enchant!
#2.check the word
#4.replace the the word to abbreviation

#this the first kind of err, we have to delete them first
error_ens={''}

file = open("error_1")
while 1:
    line = file.readline()
    if str(line)!='':
        error_ens.add(str(line).strip())
    if not line:
        break



replace_dic={'bonjour':'bg'}
file = open("replace")
while 1:
    line1 = file.readline()
    if not line1:
        break
    if str(line1).strip()!='':
        line2 = file.readline()
        replace_dic[line1.strip()]=line2

y=x.split(' ')


li=[]
for i in y:
    if i in error_ens:
        y.remove(i)
    elif not d.check(i):
        i=d.suggest(i)[0]
    if i in replace_dic:
        i=replace_dic[i]
    li.append(i)
print(li)
