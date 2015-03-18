<?php
    include 'functions.inc';
    connect();
    
    if(isset($_POST) && ((!empty($_POST['nameAdd'])) && (!empty($_POST['ongletAdd'])))){
        addTheme($_POST['nameAdd'], $_POST['ongletAdd']);
    }
    
    if(isset($_GET) && ((!empty($_GET['id'])) && (!empty($_GET['name'])))){
        delTheme($_GET['id'], $_GET['name']);
    }
    
//    <td><a href="administration.php?page=images&id='.$result->image_id.'&name='.$result->image_name.'" title="Supprimer"><i class="icon-remove-sign"></i></a></td>
?>

<div class="row">
    <div class="span9">
       <h2>Gestion des Themes</h2><a align="right" href="#" class="btn btn-link" onclick="fctAddTheme()" >Ajouter un thème </a><hr>
        
        <div class="container-fluid">
            <?php getThemes(); ?>
        </div>
    </div>

    <div id="addTheme" style="visibility:hidden">
        <h4>Ajouter Onglets</h4>
        <form class="form-horizontal" method="post" action="administration.php?page=themes">
            <input type="text" name="nameAdd" placeholder="Nom du thème"/>
            <select id="ongletId" name="ongletAdd" class="">
                <?php getOngletName();?>              
            </select>
            <button type="submit" class="btn btn-primary">Enregistrer</button>
        </form>
    </div>
</div>

<script type="text/javascript">
    function fctAddTheme(){
        document.getElementById("addTheme").style.visibility="visible";
    }
</script>
