<?php
    include 'functions.inc';
    connect();
    $modifier='display:none';
    
    if(isset($_POST) || isset($_GET))
    {
        if(!empty($_POST['name']))
        {
            addOnglet($_POST['name']);
        }
        
        if( ((!empty($_POST['idOng'])) &&  (!empty($_POST['ordreOld']))) && ((!empty($_POST['ongletNameAff'])) || (!empty($_POST['ordreAff']))))
        {
            updOnglet($_POST['idOng'], $_POST['ongletNameAff'], $_POST['ordreAff'], $_POST['ordreOld']);
        }
    
        if((!empty($_GET['id'])) && (!empty($_GET['name'])))
        {
            delOnglet($_GET['id'], $_GET['name']);
        }
        
        if((!empty($_GET['name'])) && (!empty($_GET['idOng'])) && (!empty($_GET['ongOrd'])))
        {
            $name= $_GET['name'];
            $idOng= $_GET['idOng'];
            $ongOrd= $_GET['ongOrd'];
            
            $modifier='display:block';
        }
    }
?>
    
<div class="row">   
    <div class="span9">
        <h2>Gestion des Onglets</h2>
	<i class="icon-plus-sign"></i><a align="right" href="#" class="animated btn btn-link" onclick="fctAddOng()"> Ajouter un Onglet</a><hr>

        <table class="table table-hover">
            <!-- Table des Onglets -->
            <thead> <!-- Caption des Colonnes -->
                <tr>
                    <th>Nom des onglets</th>
                    <th>Ordre d'affichage</th>
                    <th>Nombre de thème</th>
                </tr>
            </thead>
                        
            <tbody> <!-- Table des Onglets -->
                <?php getOnglets(); ?>
            </tbody>
        </table>
    </div>

	<div  class="span4 offset1"id="addOnglet" style="display:none">
        <h4 class="text-info">> Ajouter Onglet</h4>
        <form class="form-horizontal" method="post" action="administration.php?page=onglets">
            <div class="input-prepend">
                <input type="text" name="name" placeholder="Nom de l'onglet"/>
                <button type="submit" class="btn btn-primary">Enregistrer</button>
            </div>
        </form>
    </div>
        
    <div class="span4 offset1" id="infoOnglet" style="<?php echo $modifier?>">
        <h4 class="text-info">> Information Onglet</h4>
        <form class="form-horizontal" method="post" action="administration.php?page=onglets">
            <div class="span5">
                <label for="aff_onglet">Nom onglet :</label><input id="aff_onglet" type="text" name="ongletNameAff" placeholder="<?php echo $name?>"/><br/>
                <label for="aff_ordre">Ordre d'affichage :</label><input id="aff_ordre" type="number" name="ordreAff" placeholder="<?php echo $ongOrd?>"/><br/>
                <input type="hidden" name="ordreOld" value="<?php echo $ongOrd?>">
                <input type="hidden" name="idOng" value="<?php echo $idOng?>">
                <button type="submit" class="btn btn-primary">Modifier</button>
            </div>
        </form>
    </div>
    
</div>

<script type="text/javascript">
    function fctAddOng(){
        document.getElementById("addOnglet").style.display="block";
        document.getElementById("infoOnglet").style.display="none";
    }
</script>


