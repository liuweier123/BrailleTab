#!/usr/bin/env python
#coding=utf-8
from enchant.tokenize import get_tokenizer
tknzr = get_tokenizer("en_US")
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
print [w for w in tknzr(x)]