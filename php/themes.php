<?php
    include 'functions.inc';
    connect();
    $modifier='display:none';
    $idTheme=$idOng=$thmName=$grp=$thmOnglet='';
      
    if(isset($_POST) && ((!empty($_POST['nameAdd'])) && (!empty($_POST['ongletAdd']))))
    {
        addTheme($_POST['nameAdd'], $_POST['ongletAdd']);
    }
    
    if(isset($_GET))
    {
        if ((!empty($_GET['id'])) && (!empty($_GET['name'])))
        {
            delTheme($_GET['id'], $_GET['name']);
        }
    
        if ((!empty($_GET['idTheme'])) && (!empty($_GET['themeName'])) && (!empty($_GET['idOng'])))
        {
            $modifier='visibility:visible';
            
            $idTheme= $_GET['idTheme'];
            $thmName= $_GET['themeName'];
            $idOng= $_GET['idOng'];
        }
        
        if ((!empty($_GET['oldIdTheme'])) && ((!empty($_GET['newThemeName'])) || (!empty($_GET['newThemeOnglet']))))
        {
            updTheme(($_GET['oldIdTheme']), ($_GET['newThemeName']), ($_GET['newThemeOnglet']));
        }
    }

?>

<div class="row">
    <div class="span9">
       <h2>Gestion des Themes</h2>
        <i class="icon-plus-sign"></i><a align="right" href="#" class="animated btn btn-link" onclick="fctAddTheme()"> Ajouter un thème </a><hr>
 
        <div class="container-fluid">
            <?php getThemes(); ?>
        </div>
    </div>

    <div class="span9 offset1" id="addTheme" style="display:none">
        <h4 class="text-info">> Ajouter Onglets</h4>
        <form class="form-horizontal" method="post" action="administration.php?page=themes">
            <input type="text" name="nameAdd" placeholder="Nom du thème"/>
            <select id="ongletId" name="ongletAdd" class="">
                <?php getOngletName();?>              
            </select>
            <button type="submit" class="btn btn-primary">Enregistrer</button>
        </form>
    </div>
    <div class="span9 offset1" id="infoTheme" style="<?php echo $modifier?>">
        <h4 class="text-info">> Modifier informations Thème</h4>
        <form class="form-horizontal" method="get" action="administration.php?page=images">
            <div class="span10">
                <label for="aff_photo">Nom thème :</label><input id="aff_theme" type="text" name="newThemeName" placeholder="<?php echo $thmName?>"/><br/>
                <label for="aff_cmnt">Onglet :</label><select id="aff_onglet" name="newThemeOnglet" ><?php getOngletName($idOng);?></select><br/>
                
                <input type="hidden" name="oldIdTheme" value="<?php echo $idTheme?>">
                <button type="submit" name="page" value="themes" class="btn btn-primary">Modifier</button>
            </div>
        </form>
    </div>
</div>

<script type="text/javascript">
    function fctAddTheme(){
        document.getElementById("addTheme").style.display="block";
        document.getElementById("infoTheme").style.display="none";
    }
    
</script>
