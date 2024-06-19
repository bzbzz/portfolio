#!/usr/bin/bash

#------------------Creation du volume-----------------#

docker volume create sae103

# docker image pull clock //à la main
# docker image pull sae103-php  //à la main
# docker image pull sae103-html2pdf   //à la main

docker container run --name sae103-forever -d -v sae103:/work clock

#-----------------------------------------------------------------------------------------------------#

#--------------pour lancer le bash et le droit qu'il faut donner----------#

#chmod u+x docker.bash
#./docker.bash

#-----------------------------------------------------------------------------------------------------#

#------------pour mettre les fichiers dans le work-----------------#

docker container cp md_php.php sae103-forever:/work/
#CHANGER LE NOM DE LA PHP SI BESOIN



docker container cp extraction_c.php sae103-forever:/work/ 
docker container cp gendoc-tech.php sae103-forever:/work/ 
docker container cp php_vers_html.php sae103-forever:/work/
#CHANGER LE NOM DE LA PHP SI BESOIN



docker container cp src1.c sae103-forever:/work/
docker container cp src2.c sae103-forever:/work/
docker container cp src3.c sae103-forever:/work/
docker container cp DOC_UTILISATEUR.md sae103-forever:/work/
docker container cp DOC_UTILISATEUR.html sae103-forever:/work/
docker container cp DOC_TECHNIQUE.html sae103-forever:/work/


#AJOUTE LES FICHIER SI BESOIN AVEC DES MEME IDEE

#-------------------------------------------------------------------------------------------------------#

# -------Pour mettre les RÉSULTATS envoyer par les fichier---------------------------------------------#


                #-------------------- ça envoie conversion de php à html------------#

                docker container run -v sae103:/work  sae103-php php -f  /work/gendoc-tech.php  /work/doc-tech-1.0.0.html



                #--------------------ça envoie conversion de html à pdf------------#


                docker container run -v sae103:/work  sae103-html2pdf html2pdf  /work/doc-tech-1.0.0.html /work/doc-tech-1.0.0.pdf


                #--------------ça envoie conversion de MD à HTML------------------#

                #change le nom (on a pas encore cree)

                docker container run -v sae103:/work  sae103-php php -f  /work/gendoc-user.php  /work/doc-user-1.0.0.html


#-----------------------------------------------------------------------------------------------------#

#-----------------------Fin-----------------------#

docker container stop sae103-forever
docker volume rm sae103