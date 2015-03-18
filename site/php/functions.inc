<?php   
    
     /**
     * Fonction de connexion à la base de données
     * 
     * @return la connexion
     */
    function connect(){
        $host_db = "db461625891.db.1and1.com"; // nom de votre serveur
        $user_db = "dbo461625891"; // nom d'utilisateur de connexion à  votre bdd
        $password_db = "satchmo80"; // mot de passe de connexion à  votre bdd
        $bdd_db = "db461625891"; // nom de votre bdd
        
        $connect_db = mysql_connect($host_db,$user_db,$password_db);
        mysql_select_db($bdd_db,$connect_db);
        
        return $connect_db;
    }
    
    /**
     * Fonction de fermeture de la connexion à la base de données
     * 
     * @global type $connect_db
     */
    function close(){
        global $connect_db;
	mysql_close($connect_db);
    }
    
    /**
     * Fonction d'information
     * 
     * @param type $type
     * @param type $varDbl
     */
    function msgInfos($var){
        echo('
            <div class="alert alert-info">
                <button type="button" class="close" data-dismiss="alert">&times;</button>
                <strong>Informations : </strong><br/>'.$var.'
            </div>
            ');
    }
    
    
    /**
     * Fonction message d'information de doublon
     * 
     * @param type $type : onglet, theme, image
     * @param type $error : variable en doublon
     */
    function msgInfosDbl($type, $varDbl){
        echo('
            <div class="alert alert-info">
                <button type="button" class="close" data-dismiss="alert">&times;</button>
                <strong>Erreur doublons : </strong><br/>Les '.$type.' doivent contenir des noms différents : '.$varDbl.' existe déjà!
            </div>
            ');
    }
    
    /**
     * Fonction message d'erreur SQL
     * 
     * @param type $error : erreur SQL
     */
    function msgErrorSQL($error){
        echo('
            <div class="alert alert-error">
                <button type="button" class="close" data-dismiss="alert">&times;</button>
                <strong>ERROR SQL : </strong><br/>'.$error.'
            </div>
            ');
    }
    
    /**
     * Fonction message d'erreur SQL
     * 
     * @param type $error : erreur SQL
     */
    function msgErrorDel($error){
        echo('
            <div class="alert alert-error">
                <button type="button" class="close" data-dismiss="alert">&times;</button>
                <strong>Erreur de suppression : </strong><br/>'.$error.'
            </div>
            ');
    }
    
    
    /**
     * Fonction message d'erreur SQL
     * 
     * @param type $error : erreur SQL
     */
    function msgValidate($message){
        echo('
            <div class="alert alert-success">
                <button type="button" class="close" data-dismiss="alert">&times;</button>
                '.$message.'
            </div>
            ');
    }
    
   /**
     * Fonction affichage des themes
     *      
     */
    function viewTab(){
        // sql request
        $sql_request = ('SELECT onglet_name, theme_title, theme_path, theme_grp_id, image_name, image_path 
                          FROM onglet AS ong 
                          LEFT OUTER JOIN theme AS thm ON (ong.onglet_order=thm.onglet_id) 
                          LEFT OUTER JOIN image AS img ON (img.theme_grp_id=thm.theme_order) 
                          WHERE ong.visible = 1
                          ORDER BY onglet_order, theme_order');

        // create request
        $requete = mysql_query( $sql_request, connect() ) or die(msgErrorSQL("viewTab() : ".mysql_error()));

        // title of mana
        $title_name="onglet_name";
        $theme_title="theme_title";
        $theme_grp_id="theme_grp_id";

        // initialise variable
        $title="";
        $theme="";
        $count=1;

        // find tab
        while($result = mysql_fetch_array( $requete ))
        {
            // affiche le titre des onglets
            if (empty($title) || strcmp($title, $result[$title_name]) != 0 ){
                $title = $result[$title_name];
                echo('<dt><h1 class="myH1">'.$title."</h1></dt>\n");
            }

            // affiche les themes de la gallerie
            if (empty($theme) || strcmp($theme, $result[$theme_title]) != 0 ){
                $theme = $result[$theme_title];
                echo('<dd class="myDd"><a class="myA" href="./accueil.php?satchmojesopstudio='.$result[$theme_grp_id].'" raff_img><h2 class="myH2">'.$theme."</h2></a></dd>\n");
            }
            $count++;
        }
    }
    
    
    /**
     * Fonction affichage des onglets 
     *
     * @return $tab_onglet : la table contenant les onglets pour l'affichage
     */
    function getOnglets(){
        $requete=mysql_query('SELECT * FROM onglet') OR die(msgErrorSQL("getOnglets() : ".mysql_error()));
        $count=1;
        while($result=  mysql_fetch_object($requete)){
            $tab_onglet[$count] = array($result->onglet_id, $result->onglet_name, $result->onglet_order, $result->visible);  
            $count++;
        }
        return $tab_onglet;
    }

    /**
     * Fonction affichage des thèmes
     * 
     */
    function getThemes(){
        $sql_request_theme=('SELECT theme_id, theme_title, theme_path , image_path 
                              FROM theme tm 
                              LEFT OUTER JOIN image img ON (tm.theme_order = img.theme_grp_id)
                              GROUP BY tm.theme_title');
        
        $count=0;
        $slash="/";
        $requete = mysql_query($sql_request_theme) OR die(msgErrorSQL("getThemes() : ".mysql_error()));
        
        while($result=  mysql_fetch_object($requete)){
            $path_theme = $result->theme_path;
            $img_theme = $result->image_path;
            
            if(empty($img_theme)){
                $path_theme = "./img";
                $img_theme = "cray1.jpeg";
            }
            $path_img="../".$path_theme.$slash.$img_theme;
           
            if($count%3 == 0){
                if($count != 0) 
                    echo('</div>');
                if($count != count($result)) 
                    echo('<div class="row-fluid">');
            }
            echo('<div height="100px" width="100px" class="span3 gallery">
                    <h6>'.$result->theme_title.' <a href="administration.php?page=themes&id='.$result->theme_id.'&name='.$result->theme_title.'" title="Supprimer"><i class="icon-remove-sign"></i></a></td></h6>
                    <img  src="'.$path_img.'"/>
                        
                  </div>');
         $count++;
        }
    }

    /**
     * Fonction affichage des images.
     * 
     */
    function getImages(){
        $reqImg= ('SELECT image_id, theme_title, image_name, img.comment, date_creation 
                    FROM image img 
                    JOIN theme tm ON (img.theme_grp_id = tm.theme_order) 
                    ORDER BY theme_grp_id');
        
        $requete=  mysql_query($reqImg) OR die(msgErrorSQL("getImages() : ".mysql_error()));
        while($result=  mysql_fetch_object($requete)){
            echo('
                <tr>
                    <td>'.$result->image_name.'</td>
                    <td>'.$result->theme_title.'</td>
                    <td>'.$result->comment.'</td>
                    <td>'.date("d/m/Y", strtotime($result->date_creation)).'</td>
                    <td><a href="administration.php?page=images&id='.$result->image_id.'&name='.$result->image_name.'" title="Supprimer"><i class="icon-remove-sign"></i></a></td>
                  </tr>'
                 );
        }
    }
    
    /**
     * Fonction ajout onglet dans la table
     * 
     * @param type $nameOnglet : nom de l'onglet à ajouter
     */ 
    function addOnglet($nameOnglet){
        if(isExistInTable('onglet', 'onglet_name', $nameOnglet) != 0){
            msgInfosDbl("onglets",$nameOnglet);
            return;
        }
        
        $idOnglet = getMaxOnglet()+1;
        
        $str = sprintf("INSERT INTO db461625891.onglet (onglet_order, onglet_name) VALUES ('%s', '%s');", $idOnglet, $nameOnglet);
        mysql_query($str) OR die(msgErrorSQL("addOnglet() : ".mysql_error()));
          
    }
    
     /**
     * Fonction ajout de thème dans la table
     * 
     * @param type $nameTheme : nom du thème
     * @param type $onglet : l'onglet auquel le thème va appartenir
     */
    function addTheme($nameTheme, $onglet){
        
        if(isExistInTable('theme', 'theme_title', $nameTheme) != 0){
            msgInfosDbl("themes",$nameTheme);
            return;
        }
        
        $pathFile = "uploads/".$nameTheme;
        $ongletId = getIdOnglet($onglet);
        $themeId = getThemeMaxOrder()+1;
        $sqlInsert = sprintf("INSERT INTO db461625891.theme (theme_order, onglet_id, theme_title, theme_path) VALUES ('%s', '%s', '%s', '%s');", $themeId, $ongletId, $nameTheme, $pathFile);
        
        mysql_query($sqlInsert) OR die(msgErrorSQL("addTheme() : ".mysql_error()));
        @mkdir ("../".$pathFile,0777,true);
    }
    
    /**
     * Fonction ajout d'image dans la table
     * 
     * @param type $nameImage
     * @param type $pathImage
     * @param type $author
     * @param type $dateCrea
     * @param type $comment
     * @param type $visible
     * @param type $groupeImage
     */
    function addImage($nameImage,$pathImage,$author,$dateCrea,$comment,$visible,$groupeTheme=''){
        
        if(isExistInTable('image', 'image_name', $nameImage) != 0){
            msgInfosDbl("images",$nameImage);
            exit;
        }
        
        $str=  sprintf("INSERT INTO `db461625891`.`image` (`theme_grp_id`, `image_name`, `image_path`, `author`, `date_creation`, `comment`, `visible`)
                            VALUES ('%s', '%s', '%s', '%s', '%s', '%s', '%s');",
                $groupeTheme,$nameImage,$pathImage,$author,$dateCrea,$comment,$visible);
        
        
        mysql_query($str) OR die(msgErrorSQL("addImage() : ".mysql_error()));
        
    }
    
    /**
     * Function supprimer onglet et les thèmes et images liés
     * 
     * @param type $idOnglet
     * @param type $nameOnglet
     */
    function delOnglet($idOnglet, $nameOnglet){
        msgInfos('Pas encore implémenté !');
    }
    
    /**
     * Function suppression theme
     * 
     * @param type $idTheme
     * @param type $nameTheme
     */
    function delTheme($idTheme, $nameTheme){
        if(countField('theme','theme_id',$idTheme,'theme_title',$nameTheme) == 1){
            
            $sqlDelImg='SELECT * FROM theme tm JOIN image img ON (tm.theme_order=img.theme_grp_id) WHERE theme_id='.$idTheme; 
            $reqDelImg= mysql_query($sqlDelImg) OR die(msgErrorSQL("delTheme(img) : ".mysql_error()));
            while($result=  mysql_fetch_object($reqDelImg)){
                delImage($result->image_id, $result->image_name);
            }
            
            $sqlDelThm='DELETE FROM `theme` WHERE (`theme_id`='.$idTheme.') LIMIT 1';
            mysql_query($sqlDelThm) OR die(msgErrorSQL("delTheme(thm) : ".mysql_error()));
            
            $pathDir='../uploads/'.$nameTheme;
            rmdir($pathDir);
        }
    }
    
    /**
     * Function supprimer une image avec l'id et le nom
     * 
     * @param type $idImage
     * @param type $nameImage
     */
    function delImage($idImage, $nameImage){
        if(countField('image','image_id',$idImage,'image_name',$nameImage) == 1){
            $count=0;
            $sqlPathImg='SELECT theme_path, image_path FROM image img JOIN theme tm ON (img.theme_grp_id = tm.theme_order) WHERE image_id='.$idImage.' AND image_name="'.$nameImage.'" LIMIT 1';
            $requete = mysql_query($sqlPathImg) OR die(msgErrorSQL("delImage() : ".mysql_error()));

            while($result=  mysql_fetch_object($requete)){
                $tab_onglet[$count] = array($result->theme_path, $result->image_path);  
                $count++;
            }
           
            if(empty($tab_onglet)){
                die(msgErrorSQL("problème de suppression d'image!"));
                return;
            }
            
            $path="../".$tab_onglet[0][0]."/".$tab_onglet[0][1];
            $sqlDelImg='DELETE FROM `image` WHERE (`image_id`='.$idImage.') LIMIT 1';
   
            mysql_query($sqlDelImg) OR die(msgErrorSQL("delImage() : ".mysql_error()));
            
            unlink($path);
            msgValidate('L\'image a bien été supprimé !');
        }
        else{
            msgErrorDel('delImage', 'test');
        }
    }
    
    /**
     * Fonction affichage des images par theme
     * 
     * @global type $sql_request_img
     * @param type $theme_grp_id
     * @return type
     */
    function showTheme($theme_grp_id){       
        
        $sql_request_img=('SELECT img.*, thm.theme_path
                            FROM image img JOIN theme thm ON (img.theme_grp_id=thm.theme_order)
                            WHERE theme_grp_id=');
        
        $rqst_slq=$sql_request_img.$theme_grp_id;
        $requete = mysql_query($rqst_slq) OR die(msgErrorSQL("showTheme() : ".mysql_error()));
        
        $count=1;
        while($result=  mysql_fetch_object($requete)){
           $pathImg=$result->theme_path."/".$result->image_path;
           $tab_image[$count] = array($result->image_name,$pathImg, $result->author, $result->date_creation, $result->comment);  
           $count++;
        }
        
        return $tab_image;
    }
    
    /**
     * Function compte les champs présent en table 
     * 
     * @param type $table
     * @param type $field1
     * @param type $valField1
     * @param type $field2
     * @param type $valField2
     * @return type
     */
    function countField($table, $field1, $valField1, $field2, $valField2){
        $reqSelOnglet = 'SELECT * FROM '.$table.' WHERE '.$field1.'='.$valField1.' AND '.$field2.'="'.$valField2.'"';
        $requete=  mysql_query($reqSelOnglet) OR die(msgErrorSQL("countField() : ".mysql_error()));
        return mysql_num_rows($requete);
    }
    
    /**
     * Fonction retourne le dernier id d'onglet ajouté
     * 
     * @return type
     */
    function getMaxOnglet(){
        $rqtOrd = mysql_query("SELECT onglet_order FROM onglet ORDER BY onglet_order DESC LIMIT 1") OR die(msgErrorSQL("getMaxOnglet() : ".mysql_error()));
        while($result=mysql_fetch_object($rqtOrd)){
            return $result->onglet_order;
        }
    }
    
   /**
    * Fonction recupere id onglet
    * 
    * @param type $ongletTitle
    * @return type
    */ 
    function getIdOnglet($ongletTitle=''){
        $requete = mysql_query('SELECT onglet_order FROM onglet WHERE onglet_name="'.$ongletTitle.'" LIMIT 1') OR die(msgErrorSQL("getIdOnglet() : ".mysql_error()));
        while($result=mysql_fetch_object($requete)){
            return $result->onglet_order;
        }
    }    
    
    /**
     * Fonction verifie s'il existe dans la table 
     * 
     * @param type $table
     * @param type $field
     * @param type $value
     *
     * @return type : le nombre de ligne présent 
     */
    function isExistInTable($table, $field, $value){
        $reqCont= sprintf("SELECT * FROM ".$table." WHERE (".$field."='%s')", $value);
        $rqt = mysql_query($reqCont) OR die(msgErrorSQL("isExistInTable() : ".mysql_error()));
        $rqtDbl = mysql_num_rows($rqt);
        return ($rqtDbl);
    }
     
    
    /**
     * Fonction retourne le nom du thème 
     * 
     */
    function getThemeName(){
        $requete = mysql_query('SELECT theme_title FROM theme ORDER BY theme_order') OR die(msgErrorSQL("getThemeName() : ".mysql_error()));
        while($result=mysql_fetch_object($requete)){
            echo '<option>'.$result->theme_title.'</option>';
        }
    }
    
    /**
     * Fonction retourne l'id du à partir du nom du thème 
     * 
     * @param type $themeTitle : nom du thème
     */
    function getIdTheme($themeTitle=''){
        $requete = mysql_query('SELECT theme_order FROM theme WHERE theme_title="'.$themeTitle.'" LIMIT 1') OR die(msgErrorSQL("getIdTheme() : ".mysql_error()));
        while($result=mysql_fetch_object($requete)){
            return $result->theme_order;
        }
    }
    
    /**
     * Fonction retourne le nom de l'onglet 
     */
    function getOngletName(){
        $requete = mysql_query('SELECT onglet_name FROM onglet ORDER BY onglet_order') OR die(msgErrorSQL("getOngletName() : ".mysql_error()));
        while($result=mysql_fetch_object($requete)){
            echo '<option>'.$result->onglet_name.'</option>';
        }
    }
    
    /**
     * Fonction retourne le dernier id du thème ajouté
     * 
     * @return type
     */
    function getThemeMaxOrder(){
        $requete = mysql_query('SELECT theme_order FROM theme ORDER BY theme_order DESC LIMIT 1') OR die(msgErrorSQL("getThemeMaxOrder() : ".mysql_error()));
        while($result=mysql_fetch_object($requete)){
            return $result->theme_order;
        }
    }

?>

<script src="../js/jQuery.js"></script>
<script src="../js/bootstrap.js"></script>
<script src="../js/bootstrap-modal.js"></script>
<script src="../js/bootstrap-alert.js"></script>
<script src="../js/bootstrap-transition.js"></script>
