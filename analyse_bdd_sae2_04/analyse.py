import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression

# Fonction pour centrer et réduire une matrice

def Centreduire(T):
     T = np.array(T, dtype=np.float64)
     (n, p) = T.shape
     res = np.zeros((n, p))
     TMoy = np.mean(T, axis=0)
     TEcart = np.std(T, axis=0)
     for j in range(p):
         res[:, j] = (T[:, j] - TMoy[j]) / TEcart[j]
     return res

# Fonction pour calculer la taille des noms de départements

def lenDep(depAr):
    tailleAr = []
    for i in depAr:
        tailleAr.append(len(i))
    return tailleAr

# Fonction pour séparer les noms de départements entre voyelles et consonnes

def sepVoyCons(DepAr):
    voyelles = ['A', 'E', 'I', 'O', 'U', 'Y']
    cons = ['B', 'C', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'M', 'N', 'P', 'Q', 'R', 'S', 'T', 'V', 'W', 'X', 'Z']
    depVoy = []
    depCons = []
    for i in DepAr:
        if i[0] in voyelles:
            depVoy.append(i)
        else:
            depCons.append(i)
    return depVoy, depCons

""" Import et formatage des données """
# Lecture du fichier Colleges.csv
CollegesDF = pd.read_csv("Colleges.csv")

# Suppression des lignes contenant des valeurs manquantes et conversion en array
CollegesDF = CollegesDF.dropna()
CollegesAr = CollegesDF.to_numpy()

# Centrage et réduction des données
CollegesAr0 = CollegesAr[:, 1:]
CollegesAr0_CR = Centreduire(CollegesAr0)

# Extraction des colonnes
EleveDifAr = CollegesAr0[:,2]
TotalEleveAr = CollegesAr0[:,3]

# Extraction des noms de départements et calcul de leur taille
nomDepAr = CollegesAr[:,0]
tailleDepAr = lenDep(nomDepAr)

""" Exploration des données avec les matrices de covariance """

Dif6emeAr = CollegesAr0[:,6]
Dif5emeAr = CollegesAr0[:,9]
Dif4emeAr = CollegesAr0[:,12]
Dif3emeAr = CollegesAr0[:,15]

DonneesAr = np.array([tailleDepAr, Dif6emeAr, Dif5emeAr, Dif4emeAr, Dif3emeAr]).T
DonneesAr = Centreduire(DonneesAr)
# On force le typage en array de float64
DonneesAr = np.array(DonneesAr, dtype=np.float64)
MatriceCo = np.cov(DonneesAr, rowvar=False, bias=True)

""" Calcul de la régression linéaire """
# Créer le modèle de régression linéaire
model = LinearRegression()

# Regroupement des variables explicatives
Y = np.array([Dif6emeAr, Dif5emeAr, Dif4emeAr, Dif3emeAr]).T
# On doit reshape tailleDepAr par soucis algorithmique
tailleDepAr = np.array(tailleDepAr).reshape(-1, 1)
# On utilise des données centrées et réduites
tailleDepAr = Centreduire(tailleDepAr)
Y = Centreduire(Y)
# Entraîner le modèle
model.fit(tailleDepAr, Y)

# Afficher les coefficients
print("Coefficients (a0, a1, ...): ", model.coef_)
print("Intercept (a0): ", model.intercept_)

""" Calcul du coefficient de corrélation multiple """

# Prédictions
Y_pred = model.predict(tailleDepAr)

# Calcul du coefficient de corrélation multiple
ss_total = np.sum((Y - np.mean(Y))**2)
ss_residual = np.sum((Y - Y_pred)**2)
r_squared = 1 - (ss_residual / ss_total)

print("Coefficient de corrélation multiple (R²) : ", r_squared)

""" Analyse des sous-groupes de noms de départements """
# nomDepVoy, nomDepCons = sepVoyCons(nomDepAr)
# tailleVoy = lenDep(nomDepVoy)
# tailleCons = lenDep(nomDepCons)
# print(np.mean(tailleVoy), np.var(tailleVoy))
# print(np.mean(tailleCons), np.var(tailleCons))
# print(np.mean(tailleDepAr), np.var(tailleDepAr))

""" Diagramme batons de la taille des noms de départements """
# print(np.min(tailleDepAr), np.max(tailleDepAr))
# inter = np.arange(3, 22, 1)
# plt.hist(tailleDepAr, bins=inter, rwidth=0.7)
# plt.xticks(np.arange(3, 21, 1))
# plt.title("Taille des noms de départements")
# plt.show()

""" Diagramme batons du nombre total d'élèves par département """
# print(np.min(TotalEleveAr), np.max(TotalEleveAr))
# inter = np.arange(14000, 600000, 25000)
# plt.hist(TotalEleveAr, bins=inter, rwidth=0.7) 
# plt.xticks(np.arange(10000, 600000, 50000))
# plt.title("Nombre total d'élèves par département")
# plt.show()

""" Diagramme batons du nombre d'élèves en difficulté par département """
# print(np.min(EleveDifAr), np.max(EleveDifAr))
# inter = np.arange(500, 22000, 1000)
# plt.hist(EleveDifAr, bins=inter, rwidth=0.7)  # Création de l'histogramme
# plt.xticks(np.arange(500, 22000, 1500))
# plt.title("Nombre d'élèves en difficulté par département")
# plt.show()