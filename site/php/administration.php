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
                            <li><a href="./administration.php?page=onglets">Gestion des Onglets</a></li>
                            <li><a href="./administration.php?page=themes">Gestion des Thèmes</a></li>
                            <li><a href="./administration.php?page=images">Gestion des Images</a></li>
                        </ul>
                    </div>
                </div>
                <div class="span9">
                    <?php
                        if(isset($_GET['page']))
                            if($_GET['page']=='onglets')
                                include 'onglets.php';
                            elseif($_GET['page']=='images')
                                include 'images.php';
                            elseif($_GET['page']=='themes')
                                include 'themes.php';
                    ?>
                </div>
                
                
            </div>
        </div>
    </body>
</html>
