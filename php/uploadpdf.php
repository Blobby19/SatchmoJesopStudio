<!DOCTYPE html>
<html>
    <?php
        $stlOng="navSelect";
        $include="onglets.php";
        $stlThm=$stlImg=$stlAdm="";
        if(isset($_GET['page']))
        {
            $stlOng=$include="";
            if($_GET['page']=='onglets')
            {
                $stlOng="navSelect";
                $include='onglets.php';
            }
            elseif($_GET['page']=='themes')
            {
                $stlThm="navSelect";
                $include='themes.php';
            }
            elseif($_GET['page']=='images')
            {
                $stlImg="navSelect";
                $include='images.php';
            }
            elseif($_GET['page']=='admin')
            {
                $stlAdm="navSelect";
                $include='admin.php';
            }
       }
    ?>
	
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
                    <a class="brand" href="../index.php">satchmo jesop studio</a>
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
                            <li><a class="<?php echo $stlOng;?>" href="./administration.php?page=onglets">Gestion des Onglets</a></li>
                            <li><a class="<?php echo $stlThm;?>" href="./administration.php?page=themes">Gestion des Thèmes</a></li>
                            <li><a class="<?php echo $stlImg;?>" href="./administration.php?page=images">Gestion des Images</a></li>
                            <li><a class="<?php echo $stlAdm;?>" href="./administration.php?page=admin">Administration du site</a></li>
                        </ul>
                    </div>
                </div>
                <div class="span9">
                    <?php
                    //On appelle la BDD
                    include("functions.inc"); 
                    //connect();
                    $dossier='../pdf/';
                    $fichier=  basename($_FILES['userfile']['name']);
                    
                    $extensions = array(0=>'.pdf');
                    $extension = strrchr(strtolower($_FILES['userfile']['name']), '.'); 

                    //$themeId = intval(getIdTheme($_POST['theme']));
                    
                    //Si l'extension n'est pas dans le tableau
                    if(empty($_FILES['userfile']['name']) || !in_array($extension, $extensions)) 
                    {
                        $erreur = 'Vous devez uploader un fichier de type pdf !';
                    }
                    else 
                    {
                        $ext = array_search($extension, $extensions);
                    }

                    //S'il n'y a pas d'erreur, on upload
                    if(empty($erreur)) 
                    {
                        $nom=str_replace($extensions[$ext], '', $_FILES['userfile']['name']);
                        $fichier='pdf-accueil.pdf';
                        
                        //On formate le nom du fichier ici...
                        $fichier = strtr($fichier, 'ÀÁÂÃÄÅÇÈÉÊËÌÍÎÏÒÓÔÕÖÙÚÛÜÝàáâãäåçèéêëìíîïðòóôõöùúûüýÿ', 'AAAAAACEEEEIIIIOOOOOUUUUYaaaaaaceeeeiiiioooooouuuuyy');
                        $fichier = preg_replace('/([^.a-z0-9]+)/i', '-', $fichier);
                       
                        //Si la fonction renvoie TRUE, c'est que ça a fonctionné...
                        if(!empty($nom) && move_uploaded_file($_FILES['userfile']['tmp_name'], $dossier . $fichier)) 
                        {
                            msgInfos('PDF ajouté !');
                        }
                        else 
                        {
                            msgError('Echec de l\'upload !');	
                        }
                    }
                    else 
                    {
                        msgError('Echec de l\'upload : '.$erreur.' !');
                    }

                    ?>
                </div>
            </div>
        </div>
    </body>
	<script>
        function changeCss(theme)
        {
            document.getElementById(theme).class="navSelect";
        }
    </script>
</html>
