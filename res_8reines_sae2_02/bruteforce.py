from itertools import permutations
import time

start_time = time.time()

def possible(echiquier):
    # Double boucle pour analyser les colonnes et les diagonales
    for i in range(len(echiquier)):
        for j in range(i+1, len(echiquier)):
            if echiquier[i] == echiquier[j]:
                return False
            if abs(i - j) == abs(echiquier[i] - echiquier[j]):
                return False
    return True

def brutef(n):
    solu = 0
    # permutations() génère toutes les arrangements possibles de 0 à n-1
    for perm in permutations(range(n)):
        # Vérifie si la permutation est une solution valide
        if possible(perm):
            solu += 1
    return solu

print("Nombre de solutions : ", brutef(10))
print("%s secondes" % (time.time() - start_time))
