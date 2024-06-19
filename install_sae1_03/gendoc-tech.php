#!/usr/bin/php
<!DOCTYPE html>
<html lang="fr">
<head>
<title>Document</title>
<style>
     body
     {
          background-color: antiquewhite;
          font-family: Courier, monospace;
          font-size: 1.3em;
     }

     article
     {
          background-color: bisque;
          margin-left: 200px;
          margin-right: 200px;
          padding: 0 25px 20px ;
          border-top-right-radius: 25px;
          border-top-left-radius:25px ;
     }

     .titreh1
     {
          color: black;
          font-size: 3em;
     }

     .p
     {
          text-align: center;
          font-weight: bold;
          margin-left: 200px;
          margin-right: 200px;
          font-size: 1.5em;
     }

     h1
     {
          text-align: center;
          color: red;
          font-variant: small-caps;
          font-size: 1.6em;
     }

</style>
</head>
    <body>
        <main>
<?php
$nomFic = 'src1.c';
$fichier = file($nomFic);
// Commentaires
// En-tête
$entete = false;
$comEntete = '';
// Defines
$define = false;
$nomDefine = '';
$valDefine = '';
$comDefine = '';
// Structures
$struct = false;
$titreStruct = false;
$debStruct = 0;
// Globales
$varGlob = '';
$typeGlob = '';
$comGlob = '';
$estGlob = false;

if (str_contains($fichier[0], "/**"))
{
     $entete = true;
     echo '<h1 class="titreh1">'.$nomFic.'</h1>';
     foreach ($fichier as $cle => $ligne)
     {
          // EN-TETE
          if ($entete && str_starts_with($ligne, '* '))
          {
               $ligne = ltrim($ligne, '* ');
               $comEntete .= $ligne;
               //print($ligne);
          }
          elseif ($entete && str_contains($ligne, "*/"))
          {
               $entete = false;
               echo '<p class="p">'.$comEntete.'</p>';
          }
          // DEFINES
          if(str_starts_with($ligne, '#define '))
          {
               if ($define == false)
               {
                    echo '<h1>DEFINES</h1>';
               }
               $define = true;
               // NOM
               $nomDefine = ltrim($ligne, '#define ');
               preg_match('/^[a-zA-Z]+/', $nomDefine, $nomDefine);
               // VALEUR
               $valDefine = ltrim($ligne, '#define ');
               $valDefine = ltrim($valDefine, $nomDefine[0].' ');
               preg_match('/^.+? /', $valDefine, $valDefine);
               // COMMENTAIRE
               $comDefine = ltrim($ligne, '#define ');
               preg_match('/\/\*.*\*\//', $comDefine, $comDefine);
               $comDefine = ltrim($comDefine[0], '/** ');
               $comDefine = rtrim($comDefine, ' */');
               echo '<p>Nom : '.$nomDefine[0].' | Valeur : '.$valDefine[0].'| '.$comDefine.'</p>';             
          }
          // STRUCTURES
          // Si on rentre dans une structure
          if(str_starts_with($ligne, 'typedef struct'))
          {
               $struct = true;
               $debStruct = $cle;
               if ($titreStruct == false)
               {
                    echo '<h1>STRUCTURES</h1>';
                    $titreStruct = true;
               }
          }
          // Si on sort de la structure
          if(str_contains($ligne, '}') && $struct == true)
          {
               $struct = false;
               fonctionStructure($debStruct, $cle);
          }
          // Variables globales
          if((str_starts_with($ligne, 'int ') || str_starts_with($ligne, 'bool ') || str_starts_with($ligne, 'char ') || str_starts_with($ligne, 'float ') || str_starts_with($ligne, 'double ')) && str_contains($ligne, ';'))
          {
               if($estGlob == false)
               {
                    echo '<h1>VARIABLES GLOBALES</h1>';
                    $estGlob = true;
               }
               preg_match('/[a-zA-Z]+ /', $ligne, $typeGlob);
               $varGlob = ltrim($ligne, $typeGlob[0]);
               preg_match('/^[a-zA-Z]+/', $varGlob, $varGlob);
               $comGlob = ltrim($ligne, $typeGlob[0]);
               preg_match('/\/\*.*\*\//', $comGlob, $comGlob);
               $comGlob = ltrim($comGlob[0], '/** ');
               $comGlob = rtrim($comGlob, ' */');
               echo '<p> Type : '.$typeGlob[0].' | Nom : '.$varGlob[0].' | '.$comGlob.'</p>';
          }
     }
}
else
{
     print("Erreur. Aucune en-tête présente dans le fichier source.\n");
}

// fonction qui récupère les attributs d'une structure
function fonctionStructure($debStruct, $cle)
{
     global $fichier;
     // Nom
     $nomStruct = '';
     preg_match('/}\s+[a-zA-Z,_]+/', $fichier[$cle], $nomStruct);
     preg_match('/[a-zA-Z,_]+/', $fichier[$cle], $nomStruct);
     // Commentaire
     $comStruct = '';
     preg_match('/\/\*.*\*\//', $fichier[$cle], $comStruct);
     $comStruct = ltrim($comStruct[0], '/** ');
     $comStruct = rtrim($comStruct, ' */');
     echo '<p>'.$nomStruct[0].' | '.$comStruct.'</p>';
     echo '<h2> Attributs : </h2>';
     // Attributs
     for ($i = $debStruct+1; $i < $cle; $i++)
     {
          $attribut = '';
          $com = '';
          if (str_contains($fichier[$i], '/**'))
          {
               preg_match('/\s+[a-zA-Z,_]+\s+[a-zA-Z,_]+/', $fichier[$i], $attribut);
               // regex pour match le commentaire de l'attribut
               preg_match('/\/\*.*\*\//', $fichier[$i], $com);
               $com = ltrim($com[0], '/** ');
               $com = rtrim($com, ' */');
               echo '<p>'.$attribut[0].' : '.$com.'</p>';
          }
     }
}

?>