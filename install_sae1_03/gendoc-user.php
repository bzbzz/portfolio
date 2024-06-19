<?php
$fichier_md = file('DOC_UTILISATEUR.md');
//print_r($fichier_md);
?>

<!DOCTYPE html>
<html lang="fr">

<head>
    <title>Document</title>
</head>

<body>
    <main>

        <!--TITRE -->

        <?php
        foreach ($fichier_md as $line) {
            //H1
            if (str_starts_with($line, '# ')) {
                $line = ltrim($line, '# ');
                echo "<h1>$line</h1> \n";

            }
            //H2
            if (str_starts_with($line, '## ')) {
                $line = ltrim($line, '## ');
                echo "<h2>$line</h2> \n";

            }
            //H3
            if (str_starts_with($line, '### ')) {
                $line = ltrim($line, '### ');
                echo "<h3>$line</h3> \n";


            }
            //H4
            if (str_starts_with($line, '#### ')) {
                $line = ltrim($line, '#### ');
                echo "<h4>$line</h4> \n";

            }

        }

        ?>

        <!--LISTE -->
        <ul>

            <?php
            foreach ($fichier_md as $line) {
                if (str_starts_with($line, '- ')) {
                    $line = ltrim($line, '-');
                    echo "<li>$line</li> \n";

                }

            }

            ?>

        </ul>

        <!--TEXT -->
        <?php

        //GRAS
        $ligne = -1;
        foreach ($fichier_md as $key => $line) {
            if (str_starts_with($line, '**')) {
                $line = trim($line);
                if (str_ends_with($line, '**')) {
                    $line = trim($line, '**');
                    echo "<strong>$line</strong> \n";

                    $ligne = $key;
                }
            }
        }

        //ITALIQUE
        foreach ($fichier_md as $key => $line) {

            if (str_starts_with($line, '*') && ($ligne != $key)) {
                $line = trim($line);
                if (str_ends_with($line, '*')) {
                    $line = trim($line, '*');
                    echo "<em>$line</em> \n";

                }
            }
        }

        ?>
        <!--TEXT -->
        <?php

        //SURBRILLANCE MARCHE PAS , CA PRENDS PAS LES CODE AUI EST DANS LE BAS
        
        foreach ($fichier_md as $line) {

            if (str_starts_with($line, '`')) {
                $line = trim($line);
                if (str_ends_with($line, '`')) {
                    $line = trim($line, '`');
                    echo "<mark>$line</mark> \n";

                }

            }
        }

        // UNE TABULATION (NEST  PAS DEMANDER DANS LE SUJET)
        foreach ($fichier_md as $line) {

            if (str_starts_with($line, '  ')) {
                $line = ltrim($line, '  ');
                echo "<pre>$line</pre> \n"; #marche pas
        

            }

            //BARRE (NEST  PAS DEMANDER DANS LE SUJET)
        
            if (str_starts_with($line, '~~')) {
                $line = trim($line, );
                if (str_ends_with($line, '~~')) {
                    $line = trim($line, '~~');
                    echo "<strike>$line</strike> \n";

                }

            }

        }
        ?>

        <!--EXPOSANT (NEST  PAS DEMANDER DANS LE SUJET)-->
        <?php

        foreach ($fichier_md as $line) {
            if (str_starts_with($line, '<sup>')) {
                echo "$line\n";

            }

        }

        ?>

        <ol>
            <!--BLOCK (NEST  PAS DEMANDER DANS LE SUJET)-->
            <?php

            foreach ($fichier_md as $line) {

                if (str_starts_with($line, '>')) {
                    $line = ltrim($line, '> ');
                    echo "<blockquote> $line </blockquote> ";

                    if (str_starts_with($line, '> >')) // MARCHE PAS IF FAUT UTILISER LE REGEX 
                    {
                        $line = ltrim($line, '> >');
                        echo "<ul> $line </ul> ";
                        if (str_starts_with($line, '\*')) {
                            $line = trim($line, '\*');
                            echo "* $line * ";

                        }

                    }
                }
            }

            ?>

        </ol>

        <!--TABLEAU-->
        <!--URL-->
        <!--TOUS LES TEXTES SANS LES CHAR SPECIAL , LES TEXTES NORALEMENT AVEC DES : EN FIN                       -->


    </main>


</body>

</html>