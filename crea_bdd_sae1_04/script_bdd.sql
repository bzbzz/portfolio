drop schema if exists BDD cascade;
create schema BDD;
set schema 'BDD';

CREATE TABLE Activites(
 lib_activites string(50) primary key
);

CREATE TABLE Parcours(
 code_p varchar(20) primary key,
 libelle_parcours varchar(10),
 nbre_groupe_TP_P int NOT NULL,
 nbre_groupe_TD_P int NOT NULL
);

CREATE TABLE Competences(
 lib_competences varchar(10) primary key
);

CREATE TABLE Niveau(
 numero_N int NOTNULL primary key
);

CREATE TABLE Semesetre(
 numero_sem varchar(3) primary key
);

CREATE TABLE UE(
 code_UE varchar(5) primary key
);

CREATE TABLE SAE(
 code_SAE varchar(10) primary key, 
 lib_SAE varchar(50),
 nb_h_TD_enc int NOT NULL,
 nb_h_TP_projet_autonomie int NOT NULL
);

CREATE TABLE Ressources(
 code_R varchar(5) primary key,
 lib_R varchar(50),
 nb_h_CM_PN int NOT NULL,
 nb_h_TD_PN int NOT NULL,
 nb_h_TP_PN int NOT NULL,
);

-- faut utiliser des innerjoin avec comprend R
CREATE TABLE comprend_R(
 nb_h_TD_C int primary key,
 nb_h_TP_C int primary key
);

