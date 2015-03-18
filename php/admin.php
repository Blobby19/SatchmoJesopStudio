<?php
    include ('functions.inc');
    connect();
    
    if(isset($_POST))
    {
        if((!empty($_POST['adresse']) && (!empty($_POST['code_postal']) 
            && (!empty($_POST['ville']) && (!empty($_POST['pays'])
            && (!empty($_POST['telephone']) && (!empty($_POST['indicatif']))))))))
        {   
        updInfo($_POST['adresse'], $_POST['code_postal'], $_POST['ville'], $_POST['pays']
                , $_POST['telephone'], $_POST['indicatif']);
        }
        
        if((!empty($_POST['aboutMeText']))){
            updAboutMe($_POST['aboutMeText']);
        }
        
        if ((!empty($_POST['email'])))
        {
           addAdresseMail($_POST['email']); 
        }
       
    }    
        
    if(isset($_GET) && (!empty($_GET['idInfo'])))
    {
        delInfos($_GET['idInfo']);
    }    
    
?>
<script type="text/javascript" src="../js/tinymce/tinymce.min.js"></script>
<script type="text/javascript">
tinymce.init({
    selector: "textarea#aboutMeText",
    theme: "modern",
    width: 500,
    height: 300,
    plugins: [
         "advlist autolink link image lists charmap print preview hr anchor pagebreak spellchecker",
         "searchreplace wordcount visualblocks visualchars code fullscreen insertdatetime media nonbreaking",
         "save table contextmenu directionality emoticons template paste textcolor"
   ],
   content_css: "css/content.css",
   toolbar: "insertfile undo redo | styleselect | bold italic | alignleft aligncenter alignright alignjustify | bullist numlist outdent indent | l      ink image | print preview media fullpage | forecolor backcolor emoticons", 
   style_formats: [
        {title: 'Bold text', inline: 'b'},
        {title: 'Red text', inline: 'span', styles: {color: '#ff0000'}},
        {title: 'Red header', block: 'h1', styles: {color: '#ff0000'}},
        {title: 'Example 1', inline: 'span', classes: 'example1'},
        {title: 'Example 2', inline: 'span', classes: 'example2'},
        {title: 'Table styles'},
        {title: 'Table row 1', selector: 'tr', classes: 'tablerow1'}
    ]
 }); 
</script>
<div class="row">
    <div class="span9">
        <h2>Administration du Site</h2><hr>
        <div class="container-fluid">
            <h4 class="text-info">Modification des informations</h4>
            <i class="icon-plus-sign"></i><a align="right" href="#" class="animated btn btn-link" onclick="fctAddAdr()"> Ajout d'adresse</a><br>
            <i class="icon-envelope"></i><a align="right" href="#" class="animated  btn btn-link" onclick="fctUpdEmail()"> Modifier email</a><br>
            <i class="icon-refresh"></i><a align="right" href="#" class="animated btn btn-link" onclick="fctUpdPdf()"> Update le PDF</a><br>
			<i class="icon-refresh"></i><a align="right" href="#" class="animated btn btn-link" onclick="fctUpdAbout()"> Update le aboutMe</a><br><br>
			
            <h4 class="text-info">Données présentes</h4>
            <hr>
            <h5>Adresses : </h5>
            <table class="table table-striped">
                <thead>
                    <tr>
                        <th> </th>
                        <th>Adresse</th>
                        <th>CP</th>
                        <th>Ville</th>
                        <th>Pays</th>
                        <th>Téléphone</th>
                        <th>Indicatif</th>
                        <th> </th>
                    </tr>
                </thead>
                <tbody>
                    <?php getInfoAdmin(); ?>
                </tbody>
            </table>
            <h5>Email : </h5>
            <i class="icon-envelope"></i> : <?php getAdresseMail()?><br><br>
            <h5>Pdf : </h5>
            <i class="icon-picture"></i> : <?php getPdf()?><br><br>
            <hr>
            
        </div>
    </div>
    <div class="span9 offset1" id="updPdf" style="display:none">
        <h4 class="text-info">> Update pdf: </h4>
        <form class="form-inline" method="post" action="uploadpdf.php" enctype="multipart/form-data">
            <input type="file" name="userfile"/>
            <button type="submit" class="btn btn-primary">Enregistrer...</button>
       </form>  
    </div>
    <div class="span9 offset1" id="updEmail" style="display:none">
        <h4 class="text-info">> Modifier eMail: </h4>
        <form class="form-horizontal" method="post" action="./administration.php?page=admin">
            <div class="control-group">
                <div class="controls">
                    <div class="input-prepend">
                        <span class="add-on"><i class="icon-envelope"></i></span>
                        <input class="span2"  placeholder="email@example.com" id="inputIcon" type="email" required name="email">
                        <button type="submit" class="btn btn-primary">Modifier</button>
                    </div>
                </div>
            </div>
        </form>
    </div>
    <div class="span9 offset1" id="aboutMe" style="display: none">
        <h4 class="text-info">>Update AboutMe: </h4>
        <form class="form-horizontal" method="post" action="./administration.php?page=admin">
            <textarea id="aboutMeText" name="aboutMeText" placeholder="Texte"></textarea><br>
            <button type="submit" class="btn btn-primary">Valider</button>
        </form>
    </div>
    <div class="span9 offset1" id="addAdr" style="display:none">
        <h4 class="text-info">> Ajout d'adresse: </h4>
        <form class="form-horizontal" method="post" action="./administration.php?page=admin">
            <input type="text" name="adresse" placeholder="Adresse :"/><br><br>
            <input type="text" name="code_postal" placeholder="Code Postal :"/><br><br>
            <input type="text" name="ville" placeholder="Ville :"/><br><br>
            <input type="text" name="pays" placeholder="Pays :"/><br><br>
            <div class="input-prepend">
                <input style="width: 43px;" type="tel" name="indicatif" placeholder="+33"/>
                <input type="tel" style="width: 150px;" name="telephone" placeholder="Téléphone :"/>
            </div><br><br>
            <button type="submit" class="btn btn-primary">Valider</button>
        </form>
    </div>
    
</div>

<script type="text/javascript">
    function fctUpdAbout(){
        document.getElementById("aboutMe").style.display="block";
        document.getElementById("addAdr").style.display="none";
        document.getElementById("updPdf").style.display="none";
        document.getElementById("updEmail").style.display="none";
    }
    
    function fctAddAdr(){
        document.getElementById("addAdr").style.display="block";
        document.getElementById("updPdf").style.display="none";
        document.getElementById("updEmail").style.display="none";
        document.getElementById("aboutMe").style.display="none";
    }
    
    function fctUpdPdf(){
        document.getElementById("updPdf").style.display="block";
        document.getElementById("addAdr").style.display="none";
        document.getElementById("updEmail").style.display="none";
        document.getElementById("aboutMe").style.display="none";
    }
    
    function fctUpdEmail(){
        document.getElementById("updEmail").style.display="block";
        document.getElementById("updPdf").style.display="none";
        document.getElementById("addAdr").style.display="none";
        document.getElementById("aboutMe").style.display="none";
    }
</script>
