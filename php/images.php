<?php
    include 'functions.inc';
    connect();
    $themeSearch='';
    $modifier='display:none';
    $idImg=$name=$grp=$comment='';
    
    if(isset($_POST) || isset($_GET))
    {
        if ((!empty($_GET['id'])) && (!empty($_GET['name'])))
        {
            delImage($_GET['id'], $_GET['name']);
        }
        
        if ((!empty($_GET['idImg'])) && ((!empty($_GET['name'])) || (!empty($_GET['comment']))))
        {
            $idImg = ($_GET['idImg']);
            $name = ($_GET['name']);
            $comment = ($_GET['comment']);

            $modifier='display:block';
        }
        
        if ((!empty($_GET['idImage'])) && ((!empty($_GET['photoName'])) || (!empty($_GET['photoCmt']))))
        {
            updImage(($_GET['idImage']), ($_GET['photoName']), ($_GET['photoCmt']));
        }
        
        if(!empty($_POST['theme']))
        {
            $themeSearch = ($_POST['theme']);
        }
    }
    
     
?>

<div class="row">
    <div class="span9">
        <h2>Gestion des Photos</h2>
	<i class="icon-plus-sign"></i><a align="right" href="#" class="animated btn btn-link" onclick="fctAddImg()"> Ajouter une Photo</a>
	
        <hr>
        <table class="table table-striped">
            <div>
                <form class="form-horizontal" method="post" action="administration.php?page=images" enctype="multipart/form-data">
                    <select id="themeId" name="theme" >
                        <?php getThemeName();?>              
                    </select>
                    <input type="image" value="images" name="page" src="../images/search.png" title="Search by themes" />
                </form>    
              <a href="administration.php?page=images" title="Reset search"><i class="icon-remove-sign"></i></a>
            </div> 
            <thead>
                <tr>
                    <th>Nom</th>
                    <th>Groupe</th>
                    <th>Commentaire</th>
                    <th>Création</th>
                </tr>
            </thead>
            <tbody>
                <?php getImages($themeSearch);?>
            </tbody>
        </table>
    </div>
	<div class="span9 offset1" id="addTheme" style="display:none">
        <h4 class="text-info">> Ajouter Photos</h4>
        <form method="post" action="upload.php" enctype="multipart/form-data">     
            <input type="hidden" name="MAX_FILE_SIZE" value="2097152"/>     
            <input type="file" name="userfile"/><br>
            <input id="nameFileId" type="text" name="nom_fichier" placeholder="Nom du fichier"/><br>
            <textarea name="commentaire" placeholder="Commentaire"></textarea><br>
            <select id="themeId" name="theme" class="">
                <?php getThemeName();?>              
            </select>
			<br/>
            <input type="submit" class="btn btn-primary" value="Envoyer le fichier"/>    
        </form>
    </div>
    <div class="span9 offset1" id="infoImage" style="<?php echo $modifier?>">
        <h4 class="text-info">> Modifier informations Photos</h4>
        <form class="form-horizontal" method="get" action="administration.php?page=images">
            <div class="span10">
                <label for="aff_photo">Nom photo :</label><input id="aff_photo" type="text" name="photoName" placeholder="<?php echo $name?>"/><br>
                <label for="aff_cmnt">Commentaire :</label><input id="aff_cmnt" type="text" name="photoCmt" placeholder="<?php echo $comment?>"/><br>
                <input type="hidden" name="idImage" value="<?php echo $idImg?>">
                <label><button type="submit" name="page" value="images" class="btn">Modifier</button></label>
            </div>
        </form>
    </div>
</div>

<script type="text/javascript">
    function fctAddImg(){
        document.getElementById("addTheme").style.display="block";
        document.getElementById("infoImage").style.display="none";
    }
    
</script>
