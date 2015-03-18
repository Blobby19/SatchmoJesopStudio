<?php
    include 'functions.inc';
    connect();
    
    if(isset($_POST) && (!empty($_POST['name'])) ){
        addOnglet($_POST['name']);
    }
    
    if(isset($_POST) && (!empty($_POST['ongletNameAff'])) ){
        echo "onglet: ".$_POST['ongletNameAff'];
    }
    
    if(isset($_GET) && (!empty($_GET['id'])) && (!empty($_GET['name']))){
        delOnglet($_GET['id'], $_GET['name']);
    }
?>
    
<div class="row">   
    <div class="span7">
        <h2>Gestion des Onglets</h2><hr>
        <table class="table table-hover">
            <!-- Table des Onglets -->
            <thead> <!-- Caption des Colonnes -->
                <tr>
                    <th>Nom des onglets</th>
                    <th>Ordre d'affichage</th>
                </tr>
            </thead>
                        
            <tbody> <!-- Table des Onglets -->
                <?php
               
                $info_onglet = getOnglets();
                  
                $count= 1;
                while ($count <= count($info_onglet)) {
                    echo ('
                        <tr>
                            <td><a class="test" href="#" onclick="raff_onglet(\''.$info_onglet[$count][1].'\', '.$info_onglet[$count][0].');">'.$info_onglet[$count][1].'</a></td>
                            <td><span class="badge badge-info">'.$info_onglet[$count][2].'</span></td>
                            <td><a href="administration.php?page=onglets&id='.$info_onglet[$count][0].'&name='.$info_onglet[$count][1].'" title="Supprimer"><i class="icon-remove-sign"></i></a></td>
                        </tr>'
                    );
                                                   
                    $count++;
                }
                ?>
            </tbody>
        </table>
    </div>

    <div class="span2">
        <h4>Ajouter Onglet</h4>
        <form class="form-horizontal" method="post" action="administration.php?page=onglets">
            <input type="text" name="name" placeholder="Nom de l'onglet"/>
            <br/><br/>
            <button type="submit" class="btn btn-primary">Enregistrer</button>
        </form>
    </div>
        
    <div class="span4" id="infoOnglet" style="visibility:hidden">
        <h4>Information Onglet</h4>
        <form class="form-horizontal" method="post" action="administration.php?page=onglets">
            <div class="control-group">
                <div class="controls">
                    <div class="span10">
                        Nom onglet        : <input id="aff_onglet" type="text" name="ongletNameAff"/>
                        Ordre d'affichage : <input id="aff_ordre" type="text" name="odreAff"/>
                    </div>
                </div>
            </div>
            <div class="span4">
                <div class="control-group">
                    <div class="controls">
                        <button type="submit" class="btn">Modifier</button>
                    </div>
                </div>
            </div>
        </form>
    </div>
    
</div>

<script type="text/javascript">
    function raff_onglet(name, ordre){
        document.getElementById("infoOnglet").style.visibility="visible";
        document.getElementById("aff_onglet").placeholder =name;
        document.getElementById("aff_ordre").placeholder =ordre;
    }
</script>
