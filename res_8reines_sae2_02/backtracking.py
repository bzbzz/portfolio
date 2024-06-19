import time

start_time = time.time()

def possible (N, choix, col, lig):
	""" Renvoie true si une dame peut etre mise dans la case (lig, col)"""
	if col <= 1: return True # si c'est la premiere colonne
	coll = 1
	# on verifie si la dame peut etre mise dans la case en se baladant dans la liste choix
	# qui contient les lignes ou les dames sont deja mises
	for lastlig in choix:
		if lastlig == lig: return False
		if col + lig == lastlig + coll: return False
		if col >= lig and coll >= lastlig and col - lig == coll - lastlig: return False
		if col <= lig and coll <= lastlig and lig - col == lastlig - coll: return False
		coll = coll + 1
	return True	

def backtrack(N, choix=[], col=1, num=0):
	""" Retourne le nombre de solutions """
	if col == N+1: # si on a atteint la derniere colonne
		return 1
	for lig in range(1, N+1): # on parcourt les lignes
		if possible (N, choix, col, lig): # si on peut mettre une dame dans la case
			choix.append (lig)
			num = num + backtrack(N , choix, col + 1) # on continue avec la colonne suivante de manière récursive
			choix.pop ()
	return num

print("Nombre de solutions : ", backtrack(10))
print("%s secondes" % (time.time() - start_time))
