#!/usr/bin/env python
#coding=utf-8
import enchant
from enchant.checker import SpellChecker
from enchant.tokenize import EmailFilter, URLFilter
x= """
qui est simple pour toutes les autres. Lorsqu‘elle le fait remarquer,
on lui rétorque que c‘est le système qui veut ça. .. « La bureaucratie
universitaire est si lourde », dit-elle avec ironie, en ajoutant: « Son
poids n’est pas le même pour tout le monde.»

QUELQUES aerouns

La situation de Joëlle — tous ceux qui ont eu l’occasion d‘évoluer
en organisation le savent — est d'une extrême banalité. Des person—
nes qui se trouvent mises sur la touche, sans avoir jamais démÉriuâ
et ayant même, en tendance, une implication plutôt plus élevée
que la moyenne, tout le monde en a rencontré, La fréquence de ces
situations banalise—t-elle leur violence? Le discours qui consiste à
s‘accommoder de ce constat est bien connu: « C‘est un peu injuste
bien sûr, mais la justice, n‘est-elle pas une utopie romantique? Et
puis, si toutes ses collègues ayant moins d’ancienneté ont réussi à
connaître une promotion, c’est quand même un signe. . . Il n’y a pas
de fumée sans feu ! » Le propos pourrait être prolongé car joelle,
tout le monde la connaît: elle est la, dans ce bureau de l‘université ;
ici, dans une caisse d’allocations familiales ; ailleurs, dans un secré-
"""

#这个暂时好像没有什么卵用
d = enchant.DictWithPWL("fr_FR","mywords.txt")


chkr = SpellChecker("fr_FR",filters=[EmailFilter,URLFilter])
chkr.replace_always('lll','kl')
chkr.replace_always('mo','more')

#we can ignore the word in the txt
file = open("mywords.txt")
while 1:
    line = file.readline()
    if str(line)!='':
        chkr.ignore_always(str(line).strip())
    if not line:
        break

#we can ignore the word in the txt
file = open("replaceword.txt")
while 1:
    line1 = file.readline()
    print('line1',str(line1).strip())
    if not line1:
        break
    line2 = file.readline()
    print('line2',line2)
    if str(line1)!='':
        chkr.replace_always(str(line1).strip(),str(line2).strip())


chkr.set_text("icaiyu@gmail.com bonj")
for err in chkr:
    err.replace(err.suggest(err.word)[0])
print chkr.get_text()
