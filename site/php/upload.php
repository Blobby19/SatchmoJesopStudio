<!--
To change this template, choose Tools | Templates
and open the template in the editor.
-->
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>Administration</title>
        <link rel="stylesheet" media="screen" type="text/css" href="../css/bootstrap.css">
        <link rel="stylesheet" media="screen" type="text/css" href="../css/own.css">
    </head>
    <body>
        <script src="http://code.jquery.com/jquery.js"></script>
        <script src="js/bootstrap.min.js"></script>
        <script src="js/RGraph.common.core.js"></script>
        <script src="js/RGraph.radar.js"></script>
        <div class="navbar navbar-inverse navbar-static-top">
            <div class="navbar-inner">
                <div class="container">
                    <a class="brand" href="../index.php">SatchmoJesopStudios</a>
                    <div class="nav-collapse collapse">
                        <ul class="nav">
                            <li class="active"><a href="./administration.php">Administration</a></li>
                        </ul>
                    </div>
                </div>
            </div>
        </div>
        <div class="container" style="margin-top: 20px;">
            <div class="row">
                <div class="span3 sidebar">
                    <div class="sidenav">
                        <ul class="nav nav-list">
                            <li><a href="./administration.php?page=onglets">Gestion des Onglets</a></li>
                            <li><a href="./administration.php?page=themes">Gestion des Thèmes</a></li>
                            <li><a href="./administration.php?page=images">Gestion des Images</a></li>
                        </ul>
                    </div>
                </div>
                <div class="span9">
                    <?php
                    //On appelle la BDD
                    include("functions.inc"); 
                    connect();

                    //Informations sur l'image
                    $dossier = '../uploads/'.$_POST['theme'].'/';
                    $fichier = basename($_FILES['userfile']['name']);

                    $extensions = array(0=>'.png', 1=>'.gif', 2=>'.jpg', 3=>'.jpeg');
                    $extension = strrchr($_FILES['userfile']['name'], '.'); 

                    $themeId = intval(getIdTheme($_POST['theme']));
                    
                    //Si l'extension n'est pas dans le tableau
                    if(!in_array($extension, $extensions)) {
                        $erreur = 'Vous devez uploader un fichier de type png, gif, jpg, jpeg, txt ou doc...';
                    }
                    else {
                        $ext = array_search($extension, $extensions);
                        echo $ext;
                    }

                    //On change le nom du fichier si demandé...
                    if(isset($_POST) && (!empty($_POST['nom_fichier']))){
                        $nom=$_POST['nom_fichier'];
                        $fichier=$nom.$extensions[$ext];
                    }

                    //S'il n'y a pas d'erreur, on upload
                    if(!isset($erreur)) {
                        //On formate le nom du fichier ici...
                        $fichier = strtr($fichier, 'ÀÁÂÃÄÅÇÈÉÊËÌÍÎÏÒÓÔÕÖÙÚÛÜÝàáâãäåçèéêëìíîïðòóôõöùúûüýÿ', 'AAAAAACEEEEIIIIOOOOOUUUUYaaaaaaceeeeiiiioooooouuuuyy');
                        $fichier = preg_replace('/([^.a-z0-9]+)/i', '-', $fichier);
                        
                        //Si la fonction renvoie TRUE, c'est que ça a fonctionné...
                        if(move_uploaded_file($_FILES['userfile']['tmp_name'], $dossier . $fichier)) {
                            addImage($nom, $fichier, 'd', date("y-m-d",time()), $_POST['commentaire'], 1, $themeId);
                            
                            echo 'Upload effectué avec succès !';
			echo "<script language='Javascript'>document.location='http://www.satchmojesopstudio.com/php/administration.php?page=images'</script>"; //Utilisation d'un script JS, header désactivé sur serveur 1&1.
                            header('location: http://www.satchmojesopstudio.com/php/administration.php?page=images');
                        }
                        else {
                            echo('
                            <div class="alert alert-error">
                                Echec de l\'upload !
                            </div>
                            ');
                        }
                    }
                    else {
                        echo('
                            <div class="alert alert-info">
                               <b>Erreur d\'upload :</b> <br/>
                                '.$erreur.'
                            </div>
                            ');
                    }

                    ?>
                </div>
            </div>
        </div>
    </body>
</html>
