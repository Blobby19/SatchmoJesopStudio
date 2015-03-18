<?php
    include 'functions.inc';
    connect();
    
    if(isset($_GET) && (!empty($_GET['id'])) && (!empty($_GET['name']))){
        delImage($_GET['id'], $_GET['name']);
    }
?>



<div class="row">
    <div class="span7">
        <h2>Gestion des Images</h2><hr>
        <table class="table table-striped">
            <thead>
                <tr>
                    <th>Nom</th>
                    <th>Groupe</th>
                    <th>Commentaire</th>
                    <th>Création</th>
                </tr>
            </thead>
            <tbody>
                <?php getImages();?>
            </tbody>
        </table>
    </div>
    <div class="span2">
        <h4 class="text-info">Ajouter Image</h4>
        <form method="post" action="upload.php" enctype="multipart/form-data" onSubmit="valider_formulaire(this)">     
            <input type="hidden" name="MAX_FILE_SIZE" value="2097152"/>     
            <input type="file" name="userfile"/>
            <input id="nameFileId" type="text" name="nom_fichier" placeholder="Nom du fichier"/>
            <textarea name="commentaire" placeholder="Commentaire"></textarea>
            <select id="themeId" name="theme" class="">
                <?php getThemeName();?>              
            </select>

            <input type="submit" class="btn btn-primary" value="Envoyer le fichier"/>    
        </form>
    </div>
</div>

<script language='JavaScript'>
    
    

</script>
