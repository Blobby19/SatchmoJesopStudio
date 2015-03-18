<?php   
    
    /**
     * Fonction : de connexion à la base de données
     * 
     * @return la connexion
     */
    function connect(){
        $host_db = "localhost"; // nom de votre serveur
        $user_db = "root"; // nom d'utilisateur de connexion à  votre bdd
        $password_db = ""; // mot de passe de connexion à  votre bdd
        $bdd_db = "satchmosql"; // nom de votre bdd
        
        $connect_db = mysql_connect($host_db,$user_db,$password_db);
        mysql_select_db($bdd_db,$connect_db);
        
        return $connect_db;
    }
    
    /**
     * Fonction : de fermeture de la connexion à la base de données
     * 
     * @global type $connect_db
     */
    function close()
    {
        global $connect_db;
	mysql_close($connect_db);
    }
    
    /**
     * Fonction : d'information
     * 
     * @param type $type
     * @param type $varDbl
     */
    function msgInfos($var)
    {
        echo('
            <div class="alert alert-info">
                <button type="button" class="close" data-dismiss="alert">&times;</button>
                <strong>Informations : </strong><br/>'.$var.'
            </div>
            ');
    }
    
    /**
     * Fonction : message d'information de doublon
     * 
     * @param type $type : onglet, theme, image
     * @param type $error : variable en doublon
     */
    function msgInfosDbl($type, $varDbl)
    {
        echo('
            <div class="alert alert-info">
                <button type="button" class="close" data-dismiss="alert">&times;</button>
                <strong>Erreur doublons : </strong><br/>Les '.$type.' doivent contenir des noms différents : '.$varDbl.' existe déjà!
            </div>
            ');
    }
    
    /**
     * Fonction : message d'erreur SQL
     * 
     * @param type $error : erreur SQL
     */
    function msgErrorSQL($error)
    {
        echo('
            <div class="alert alert-error">
                <button type="button" class="close" data-dismiss="alert">&times;</button>
                <strong>ERROR SQL : </strong><br/>'.$error.'
            </div>
            ');
    }
    
    /**
     * Fonction : message d'erreur SQL
     * 
     * @param type $error : erreur SQL
     */
    function msgErrorDel($error)
    {
        echo('
            <div class="alert alert-error">
                <button type="button" class="close" data-dismiss="alert">&times;</button>
                <strong>Erreur de suppression : </strong><br/>'.$error.'
            </div>
            ');
    }
	
    /**
     * Fonction : message d'erreur SQL
     * 
     * @param type $error : erreur SQL
     */
    function msgError($error)
    {
        echo('
            <div class="alert alert-error">
                <button type="button" class="close" data-dismiss="alert">&times;</button>
                <strong>Erreur : </strong><br/>'.$error.'
            </div>
            ');
    }
    
    /**
     * Fonction : message d'erreur SQL
     * 
     * @param type $error : erreur SQL
     */
    function msgValidate($message)
    {
        echo('
            <div class="alert alert-success">
                <button type="button" class="close" data-dismiss="alert">&times;</button>
                '.$message.'
            </div>
            ');
    }
	
    /**
     * Fonction : : retourne un theme existant aleatoire
     * 
     * @return int
     */
    function themeAleatoire()
    {
        $sqlRqt='SELECT theme_grp_id 
                  FROM image 
                  GROUP BY theme_grp_id 
                  ORDER BY RAND() LIMIT 1;';
        
        $result = mysql_query($sqlRqt, connect()) OR die(msgErrorSQL("themeAleatoire() : ".mysql_error()));
        
        $data='';
        
        if (mysql_num_rows($result)>0)
        {
            $data = mysql_result($result, 0, 'theme_grp_id');
        }
        return $data;
    }
	
    /**
     * Fonction :s return count theme by onglet
     * 
     * @return type
     */
    function countThemeByOnglet()
    {
        $sqlRequestCnt= ('SELECT onglet_name, (CASE WHEN thm.theme_order IS NULL THEN 0 ELSE COUNT(ong.onglet_name) END) AS nber 

                            FROM onglet AS ong 
                            LEFT OUTER JOIN theme AS thm ON (ong.onglet_order=thm.onglet_id) 
                            WHERE ong.visible = 1 
                            GROUP BY onglet_name 
                            ORDER BY id_ordre, theme_order');


        // create request
        $requeteCnt = mysql_query( $sqlRequestCnt, connect() ) or die(msgErrorSQL("countThemeByOnglet() : ".mysql_error()));

        
        while($result = mysql_fetch_array($requeteCnt))
        {
            $tabCnt[$result['onglet_name']]=$result['nber'];
        }
        
        if (empty($tabCnt))
        {
            $tabCnt['']=0;
        }
        
        return $tabCnt;
    }
	
    /**
     * Fonction : determine si c est le thème choisit
     * 
     * @param type $grpId
     * @return type
     */
    function isMyTheme($grpId)
    {
        $onglet_select='';
        $sqlrequest2 = ('SELECT onglet_name
                            FROM theme AS thm
                            INNER JOIN onglet AS ong ON (ong.onglet_order=thm.onglet_id)
                            WHERE thm.theme_order='.onlyInteger($grpId));
        
        $requete = mysql_query($sqlrequest2, connect())or die(msgErrorSQL("isMyTheme() : ".mysql_error()));
        
         	

        while($result2=  mysql_fetch_object($requete))
        {
            $onglet_select=$result2->onglet_name;
        }
        
        return $onglet_select;
    }
    
    /**
     * Fonction : affichage des themes
     *      
     */
    function viewTab($grpId)
    {
        $tabCnt= countThemeByOnglet();
                
        // sql request
        $sqlRequest = ('SELECT onglet_name, theme_title, theme_path, theme_order 
                          FROM onglet AS ong 
                          LEFT OUTER JOIN theme AS thm ON (ong.onglet_order=thm.onglet_id) 
                          WHERE ong.visible = 1
                          ORDER BY id_ordre, theme_order');
                    
        // create request
        $requete = mysql_query( $sqlRequest, connect() ) or die(msgErrorSQL("viewTab() : ".mysql_error()));
        
        if (mysql_num_rows($requete)>0)
        {
            // title of mana

            $title_name="onglet_name";
            $theme_title="theme_title";
            $theme_grp_id="theme_order";

            // initialise variable
            $title=$theme=$link=$linkEnd="";
            $isOnlyTheme=false;

            $onglet_select = isMyTheme($grpId);

            // find tab
            while($result = mysql_fetch_array( $requete ))
            {
                if ($tabCnt[$result[$title_name]]==1)
                {
                    $isOnlyTheme=true;
                }

                // affiche le titre des onglets
                if ((empty($title) || strcmp($title, $result[$title_name]) != 0) && $tabCnt[$result[$title_name]]!=0)
                {
                    $title = $result[$title_name];

                    if($onglet_select!=$title)
                    {
                        $h1Title='<h1 id='.$title.' class="myH1">';
                    }
                    else
                    {
                        $h1Title='<h1 id='.$title.' class="myH1 clicked">';
                    }

                    if ($isOnlyTheme)
                    {
                        $link='<a class="myA" href="./accueil.php?satchmojesopstudio='.$result[$theme_grp_id].'" raff_img>';
                        $linkEnd='</a>';

                        if($onglet_select!=$title)
                        {
                            $h1Title='<h1 id='.$title.' class="myH1">';
                        }
                        else
                        {    
                            $h1Title='<h1 id='.$title.' class="myH1 clicked">';
                        }
                    }
                    else
                    {
                         $link=$linkEnd="";
                    }
                    echo('<dt>'.$link.$h1Title.$title.'</h1>'.$linkEnd."</dt>\n");
                }

                // affiche les themes de la gallerie
                if ((empty($theme) || strcmp($theme, $result[$theme_title]) != 0)  && $tabCnt[$result[$title_name]]!=0)
                {
                    $theme = $result[$theme_title];
                    if (!$isOnlyTheme)
                    {
                        echo('<dd class="myDd"><a class="myA" href="./accueil.php?satchmojesopstudio='.$result[$theme_grp_id].'" raff_img><h2 class="myH2">'.$theme."</h2></a></dd>\n");
                    }
                }
                $isOnlyTheme=false;
            }
        }
    }
    
    /**
     * Fonction : affichage des onglets 
     *
     * @return $tab_onglet : la table contenant les onglets pour l'affichage
     */
    function getOnglets()
    {
        $requete=mysql_query('SELECT ong.*,thm.theme_order,(CASE WHEN thm.theme_order IS NULL THEN 0 ELSE COUNT(ong.onglet_name) END) AS number 
                               FROM onglet ong
                               LEFT OUTER JOIN theme thm ON (ong.onglet_order=thm.onglet_id)
                               GROUP BY onglet_name
                               ORDER BY id_ordre;') OR die(msgErrorSQL("getOnglets() : ".mysql_error()));
        
	while($result=  mysql_fetch_object($requete))
        {
            echo('
                <tr>
                    <td><a class="test" href="./administration.php?page=onglets&name='.$result->onglet_name.'&idOng='.$result->onglet_id.'&ongOrd='.$result->id_ordre.'">'.$result->onglet_name.'</a></td>
                    <td><span class="badge badge-info">'.$result->id_ordre.'</span></td>
                    <td>'.$result->number.'</td>    
                    <td><a href="administration.php?page=onglets&id='.$result->id_ordre.'&name='.$result->onglet_name.'" title="Supprimer"><i class="icon-remove-sign"></i></a></td>
                </tr>
            ');
        }
        
        if (mysql_num_rows($requete) == 0)
        {
           echo('
                <tr>
                    <td colspan=3 >No Records</td>
                </tr>
                '); 
        }
        
    }

    /**
     * Fonction : affichage des thèmes
     * 
     */
    function getThemes()
    {
        $sql_request_theme=('SELECT theme_id, theme_title, theme_path , image_path, tm.onglet_id, ong.onglet_name
                              FROM theme tm 
                              LEFT OUTER JOIN onglet ong ON (ong.onglet_order = tm.onglet_id)
                              LEFT OUTER JOIN image img ON (tm.theme_order = img.theme_grp_id)
                              GROUP BY tm.theme_title;');
        
        $count=0;
        $slash="/";
        $requete = mysql_query($sql_request_theme) OR die(msgErrorSQL("getThemes() : ".mysql_error()));
        
        while($result=  mysql_fetch_object($requete))
        {
            $path_theme = $result->theme_path;
            $img_theme = $result->image_path;
            
            if(empty($img_theme))
            {
                $path_theme = "./img";
                $img_theme = "cray1.jpeg";
            }
            $path_img="../".$path_theme.$slash.$img_theme;
           
            if($count%3 == 0)
            {
                if($count != 0) 
                    echo('</div>');
                if($count != count($result)) 
                    echo('<div class="row-fluid">');
            }
            
            echo('
                <div height="100px" width="100px" class="span3 gallery">
                    <h6>
                        <a class="test" href="./administration.php?page=themes&idTheme='.$result->theme_id.'&themeName='.$result->theme_title.'&idOng='.$result->onglet_id.'">'.$result->theme_title.'</a> 
                        <a href="administration.php?page=themes&id='.$result->theme_id.'&name='.$result->theme_title.'" title="Supprimer"><i class="icon-remove-sign"></i></a><br>
                        <i class="icon-share-alt"></i> '.$result->onglet_name.'
                    </h6>
                    <img  src="'.$path_img.'"/>
                </div>
                ');
             $count++;
        }
        
        if (mysql_num_rows($requete) == 0)
        {
           echo('
                <tr>
                    <td>No Records</td>
                </tr>
                '); 
        }
    }

    /**
     * Fonction : affichage des images.
     * 
     */
    function getImages($themeTitle="")
    {
        $whereClause='';
        if(!empty($themeTitle))
        {
            $whereClause='WHERE tm.theme_title="'.onlyCaracters($themeTitle).'"';
        }
        
        $reqImg= ('SELECT image_id, theme_title, image_name, img.comment, date_creation 
                    FROM image img 
                    JOIN theme tm ON (img.theme_grp_id = tm.theme_order) '.
                    $whereClause
                    .' ORDER BY theme_grp_id');
        
        $requete=  mysql_query($reqImg) OR die(msgErrorSQL("getImages() : ".mysql_error()));
        while($result=  mysql_fetch_object($requete))
        {
            echo('
                <tr>
                    <td><a class="test" href="./administration.php?page=images&idImg='.$result->image_id.'&name='.$result->image_name.'&comment='.$result->comment.'">'.$result->image_name.'</a></td>
                    <td>'.$result->theme_title.'</td>
                    <td>'.$result->comment.'</td>
                    <td>'.date("d/m/Y", strtotime($result->date_creation)).'</td>
                    <td><a href="administration.php?page=images&id='.$result->image_id.'&name='.$result->image_name.'" title="Supprimer"><i class="icon-remove-sign"></i></a></td>
                  </tr>'
                 );
        }
		
	if (mysql_num_rows($requete) == 0)
        {
           echo('
                <tr>
                    <td colspan=4 >No Records</td>
                </tr>
                '); 
        }
    }
    
    /**
     * Fonction : retourne les informations situées en bas à gauche du site
     * 
     */
    function getInfo()
    {
        $requete = mysql_query('SELECT * FROM info ORDER BY odre_address DESC LIMIT 1;') OR die(msgErrorSQL("getInfo() : ".mysql_error()));

        while($result=  mysql_fetch_object($requete))
        {
            echo (
                $result->adresse.'<br/>'.
                $result->code_postal." ".$result->ville.'<br/>'.
                $result->pays.'<br/>'.
                $result->indicatif." ".$result->telephone
                 );
        }
        
        if (mysql_num_rows($requete) == 0)
        {
           echo('
                <tr>
                    <td colspan=4 >No Records</td>
                </tr>
                '); 
        }
    }
    
    /**
     * Fonction : recuperer l'adresse mail
     * 
     */
    function getAdresseMail()
    {
        $fp = fopen ($_SERVER["DOCUMENT_ROOT"]."/php/email.conf", "r+");  
        $contenu_du_fichier = fgets ($fp, 255);
        fclose ($fp);  
        echo '<a href="mailto:'.$contenu_du_fichier.'">'.$contenu_du_fichier.'</a>';
    }
    
    /**
     * Fonction : recuperer le pdf
     * 
     */
    function getPdf()
    {
        echo '<a href="pdf/BOOK IMAGES_SJS_spring_2013.pdf" target="_blank">pdf portfolio</a>';
    }
    
    /**
     *  Fonction : Créer une table des informations
     */
    function getInfoAdmin()
    {
        $requete = mysql_query('SELECT * FROM info;') OR die(msgErrorSQL("getInfo() : ".mysql_error()));
        while($result=mysql_fetch_object($requete))
        {
            echo(
                '<tr>
                    <td><span class="badge badge-info">'.$result->odre_address."</span></td>
                    <td>".$result->adresse."</td>
                    <td>".$result->code_postal."</td>
                    <td>".$result->ville."</td>
                    <td>".$result->pays."</td>
                    <td>".$result->telephone."</td>
                    <td>".$result->indicatif."</td>".
                    '<td><a href="administration.php?page=admin&idInfo='.$result->id_info.'" title="Supprimer"><i class="icon-remove-sign"></i></a></td>    
                </tr>'
                );
        }
        if (mysql_num_rows($requete) == 0)
        {
           echo('
                <tr>
                    <td colspan=6 >No Records</td>
                </tr>
                '); 
        }
        
    }
    
    /**
     * Fonction : ajout onglet dans la table
     * 
     * @param type $nameOnglet : nom de l'onglet à ajouter
     */ 
    function addOnglet($nameOnglet)
    {
        $nameOnglet= onlyCaracters($nameOnglet);
        if(isExistInTable('onglet', 'onglet_name', $nameOnglet) != 0)
        {
            msgInfosDbl("onglets",$nameOnglet);
            return;
        }
        
        $idOnglet = getMaxOnglet()+1;
        
        $str = sprintf("INSERT INTO onglet (onglet_order, id_ordre, onglet_name) VALUES ('%s', '%s', '%s');",$idOnglet ,$idOnglet, $nameOnglet);
        mysql_query($str) OR die(msgErrorSQL("addOnglet() : ".mysql_error()));
          
    }
  
    /**
     * Fonction : ajout de thème dans la table
     * 
     * @param type $nameTheme : nom du thème
     * @param type $onglet : l'onglet auquel le thème va appartenir
     */
    function addTheme($nameTheme, $onglet)
    {   
	$nameTheme = onlyCaracters($nameTheme);
        $onglet = onlyCaracters($onglet);
        if(isExistInTable('theme', 'theme_title', $nameTheme) != 0)
        {
            msgInfosDbl("themes",$nameTheme);
            return;
        }
        
        $pathFile = "uploads/".$nameTheme;
        $ongletId = getIdOnglet($onglet);
        $themeId = getThemeMaxOrder()+1;
        $sqlInsert = sprintf("INSERT INTO theme (theme_order, onglet_id, theme_title, theme_path) VALUES ('%s', '%s', '%s', '%s');", $themeId, $ongletId, $nameTheme, $pathFile);
        
        mysql_query($sqlInsert) OR die(msgErrorSQL("addTheme() : ".mysql_error()));
        @mkdir ("../".$pathFile,0777,true);
    }
    
    /**
     * Fonction : ajout d'image dans la table
     * 
     * @param type $nameImage
     * @param type $pathImage
     * @param type $author
     * @param type $dateCrea
     * @param type $comment
     * @param type $visible
     * @param type $groupeImage
     */
    function addImage($nameImage,$pathImage,$author,$dateCrea,$comment,$visible,$groupeTheme='')
    {   
		$nameImage= onlyCaracters($nameImage);
        $pathImage= onlyCaracters($pathImage);
        $author= onlyCaracters($author);
        $dateCrea= onlyCaracters($dateCrea);
        $comment= onlyCaracters($comment);        
        $visible= onlyCaracters($visible);
        $groupeTheme= onlyCaracters($groupeTheme);
        if(isExistInTable('image', 'image_name', $nameImage) != 0)
        {
            msgInfosDbl("images",$nameImage);
            exit;
        }
        
        $str=  sprintf("INSERT INTO image (theme_grp_id, image_name, image_path, author, date_creation, comment, visible)
                            VALUES ('%s', '%s', '%s', '%s', '%s', '%s', '%s');",
                $groupeTheme,$nameImage,$pathImage,$author,$dateCrea,$comment,onlyInteger($visible));
        
		mysql_query($str) OR die(msgErrorSQL("addImage() : ".mysql_error()));
        
    }
    
    /**
     * Fonction : recuperer l'adresse mail
     * 
     */
    function addAdresseMail($adresse)
    {
        $file = $_SERVER["DOCUMENT_ROOT"]."/php/email.conf";  
        if (!empty($adresse))
        {
            file_put_contents($file, $adresse, LOCK_EX);
        }
    }
    
    /**
     * Fonction : Permet d'ajouter des informations 
     * 
     * @param type $adresse
     * @param type $code_postal
     * @param type $ville
     * @param type $pays
     * @param type $telephone
     * @param type $indicatif
     * @return type
     */
    function updInfo($adresse,$code_postal,$ville,$pays,$telephone,$indicatif)
    {
        if(isExistInTable('info', 'adresse', $adresse) != 0)
        {
            msgInfosDbl("adresses",$adresse." - ".$ville);
            return;
        }
        
        $sqlOrd='SELECT odre_address FROM info ORDER BY odre_address DESC LIMIT 1';
       $result= mysql_query($sqlOrd) or die(msgErrorSQL("updInfo() : ".mysql_error()));
        
        if (mysql_num_rows($result)>0)
        {
            $ordre = mysql_result($result, 0, 'odre_address');
        }
        $ordre += 1;
        $str=  sprintf("INSERT INTO info (adresse, code_postal, ville, pays,telephone, indicatif, odre_address) VALUES ('%s','%s','%s','%s','%s','%s','%s')",$adresse,$code_postal,$ville,$pays,$telephone,$indicatif,$ordre);
        
        mysql_query($str) or die(msgErrorSQL("updInfo() : ".mysql_error()));
    }
    
    function updAboutMe($aboutMe)
    {
      $fp = fopen ("../aboutMe.txt", "w"); 
      fputs ($fp, $aboutMe); 
      fclose ($fp);  
      msgInfos("les informations ont été mise à jour !");
      
    }
    
    /**
     * Function supprimer onglet et les thèmes et images liés
     * 
     * @param type $idOnglet
     * @param type $nameOnglet
     */
    function delOnglet($idOnglet, $nameOnglet)
    {
	$nameOnglet=  onlyCaracters($nameOnglet);
		
	if(countField('onglet','onglet_order',$idOnglet,'onglet_name',$nameOnglet) == 1)
        {
            $sql_request_ong=('SELECT theme_path FROM theme WHERE onglet_id='.onlyInteger($idOnglet).' ;');
            $requete = mysql_query($sql_request_ong) OR die(msgErrorSQL("delOnglet() : ".mysql_error()));
            
            $isAllDlt = false;
            $haveTheme= false;
            while($result=  mysql_fetch_object($requete))
            {
                $haveTheme = true;
                $path = "../".$result->theme_path;
             
                $successDel = rm($path);
                if ($successDel)
                {
                    $sql_rqst_dlt_img ='DELETE FROM image WHERE theme_grp_id IN (SELECT theme_order FROM theme WHERE onglet_id='.onlyInteger($idOnglet).')';
                    mysql_query($sql_rqst_dlt_img) OR die(msgErrorSQL("delOnglet() del image : ".mysql_error()));

                    $sql_rqst_dlt_thm ='DELETE FROM theme WHERE onglet_id='.onlyInteger($idOnglet);
                    mysql_query($sql_rqst_dlt_thm) OR die(msgErrorSQL("delOnglet() del theme : ".mysql_error()));
                    $isAllDlt = true;
                }
                else
                {
                    $isAllDlt = false;
                    msgErrorDel('delOnglet');            
                }
            }
            
            if ($isAllDlt || !$haveTheme)
            {
                $sql_rqst_dlt_thm ='DELETE FROM onglet WHERE onglet_order='.onlyInteger($idOnglet);
                mysql_query($sql_rqst_dlt_thm) OR die(msgErrorSQL("delOnglet() del onglet : ".mysql_error()));
            }
        }   
        else
        {
            msgErrorDel('delOnglet');
        }
    }
    
    /**
     * Function suppression de themes
     * 
     * @param type $idTheme
     * @param type $nameTheme
     */
    function delTheme($idTheme, $nameTheme)
    {
        $nameTheme= onlyCaracters($nameTheme);
	
        if(countField('theme','theme_id',onlyInteger($idTheme),'theme_title',$nameTheme) == 1)
        {
            $sql_request_thm=('SELECT theme_path FROM theme WHERE theme_id='.onlyInteger($idTheme).' LIMIT 1;');
            $requete = mysql_query($sql_request_thm) OR die(msgErrorSQL("delTheme() : ".mysql_error()));
        
            while($result=  mysql_fetch_object($requete))
            {
               $path = "../".$result->theme_path;
            } 

            $successDel = rm($path);
            if ($successDel)
            {
                $sql_rqst_dlt_img ='DELETE FROM image WHERE theme_grp_id IN (SELECT theme_order  FROM theme WHERE theme_id='.onlyInteger($idTheme).')';
                mysql_query($sql_rqst_dlt_img) OR die(msgErrorSQL("delTheme() del image : ".mysql_error()));
                 
                $sql_rqst_dlt_thm ='DELETE FROM theme WHERE theme_id='.onlyInteger($idTheme);
                mysql_query($sql_rqst_dlt_thm) OR die(msgErrorSQL("delTheme() del theme : ".mysql_error()));
            }
            else
            {
                msgErrorDel('delTheme');            
            }
        } 
        else
        {
            msgErrorDel('delTheme');
        }
    }
    
    /**
     * Function supprimer une image avec l'id et le nom
     * 
     * @param type $idImage
     * @param type $nameImage
     */
    function delImage($idImage, $nameImage)
    {
	$nameImage=  onlyCaracters($nameImage);

        if(countField('image','image_id',onlyInteger($idImage),'image_name',$nameImage) == 1)
        {
            $count=0;
            $sqlPathImg='SELECT theme_path, image_path FROM image img JOIN theme tm ON (img.theme_grp_id = tm.theme_order) WHERE image_id='.onlyInteger($idImage).' AND image_name="'.$nameImage.'" LIMIT 1';
            $requete = mysql_query($sqlPathImg) OR die(msgErrorSQL("delImage() : ".mysql_error()));

            while($result=  mysql_fetch_object($requete))
            {
                $tab_onglet[$count] = array($result->theme_path, $result->image_path);  
                $count++;
            }
           
            if(empty($tab_onglet))
            {
                die(msgErrorSQL("Problème de suppression de photo!"));
                return;
            }
            
            $path="../".$tab_onglet[0][0]."/".$tab_onglet[0][1];
           
            
            $successDel = rm($path);
            if($successDel)
            {
                $sqlDelImg='DELETE FROM `image` WHERE (`image_id`='.onlyInteger($idImage).') LIMIT 1';
                mysql_query($sqlDelImg) OR die(msgErrorSQL("delImage() : ".mysql_error()));
                msgValidate('La photo a bien été supprimé !');
            }
            else
            {
                msgErrorDel('La photo n\'a pu être supprimé, veuillez réesayer de nouveau. Si ce problème persiste, contactez l\'administrateur du serveur! ');
            }
        }
        else
        {
            msgErrorDel('Il n\'existe pas de photo à supprimer !');
        }
    }
    
    /**
     * 
     * @param type $idInfos
     */
    function delInfos($idInfos)
    {
        $idInfos= onlyInteger($idInfos);

        if(isExistInTable('info', 'id_info', $idInfos) == 0)
        {
            msgInfos("Cette adresse a déjà été supprimé !");
            return;
        }
        
        $sqlDelInfo='DELETE FROM `info` WHERE (`id_info`='.$idInfos.') LIMIT 1';
        mysql_query($sqlDelInfo) OR die(msgErrorSQL("delInfos() : ".mysql_error()));
        msgValidate('L\'adresse a bien été supprimé !');
    }
	
    /**
     * Fonction : update onglet name, ou ordre theme
     *
     * @param type $idOng
     * @param type $ongletNameAff
     * @param type $ordreAff
     */
    function updOnglet($idOng, $ongletNameAff, $ordreAff, $ordreOld)
    {   
        $idOng= onlyInteger($idOng);
        $ordreOld= onlyInteger($ordreOld);
        $ongletNameAff= onlyCaracters($ongletNameAff);
        $ordreAff= onlyInteger($ordreAff);
        
        $field=$fieldName=$fieldOrd='';
        $messageInfo= "L'upload a bien été effectué !";
        
        if(!empty($ongletNameAff))
        {
            $fieldName= "onglet_name='".$ongletNameAff."' ";
            $field= $fieldName;
        }
        
        if(!empty($ordreAff))
        {
            // change id order if exist
            changeIfExist($ordreAff, $ordreOld);
            
            $fieldOrd= "id_ordre=".$ordreAff;
            $field= $fieldOrd;
        }
        
        if(!empty($ongletNameAff) && !empty($ordreAff))
        {
            $field= $fieldName.', '.$fieldOrd;
        }
        
        if(!empty($field) && !empty($idOng))
        {
            $rqt= 'UPDATE onglet SET '.$field.' WHERE onglet_id='.$idOng.' LIMIT 1;';
            mysql_query($rqt) OR die(msgErrorSQL("updOnglet() : ".mysql_error()));
            
            msgValidate($messageInfo);
            return;
        }
        
        msgInfos("Aucune modifications n'a été faite !");
    }
    
    /**
     * 
     * @param type $ordreAff
     */
    function changeIfExist($ordreAff, $ordreOld)
    {
        $req= 'SELECT onglet_id FROM onglet WHERE id_ordre='.$ordreAff.' LIMIT 1;';
        $result = mysql_query($req, connect()) OR die(msgErrorSQL("changeIfExist() : ".mysql_error()));
                
        if (mysql_num_rows($result)>0)
        {
            $idChange = mysql_result($result, 0, 'onglet_id');
            $rqtChg= 'UPDATE onglet SET id_ordre='.$ordreOld.' WHERE onglet_id='.$idChange.' LIMIT 1;';

            mysql_query($rqtChg) OR die(msgErrorSQL("changeIfExist() : ".mysql_error()));
        }
    }
    
    /**
     * Fonction : update onglet name, ou theme onglet
     * 
     * @param type $idTheme
     * @param type $themeName
     * @param type $themeOnglet
     */
    function updTheme($idTheme, $themeName, $themeOnglet)
    {
        $idTheme= onlyInteger($idTheme);
        $themeName= onlyCaracters($themeName);
        $themeOnglet= onlyCaracters($themeOnglet);

        $field=$fieldName=$fieldOnglet=$rqt='';
        $dirPosition= $_SERVER["DOCUMENT_ROOT"]."/uploads/";
        $messageInfo="L'upload a bien été effectué !";
        
        if(!empty($themeName))
        {
            $fieldName= "theme_title='".$themeName."', theme_path='uploads/".$themeName."' ";
            $field= $fieldName;
        }
        
        if(!empty($themeOnglet))
        {
            $newIdOnglet= getIdOngletByName($themeOnglet);
            $oldIdOnglet= getOngletId($idTheme);
                    
            if($newIdOnglet != $oldIdOnglet)
            {
                $fieldOnglet= "onglet_id=".$newIdOnglet;
                $field= $fieldOnglet;
            }
        }

        if (!empty($fieldName) && !empty($fieldOnglet))
        {
            $field= $fieldName.', '.$fieldOnglet;
        }  
       
        if(!empty($field) && !empty($idTheme))
        {
            if (!empty($themeName))
            {
                renameFilder($dirPosition.getOngletTheName($idTheme), $dirPosition.$themeName);
            }
            
            $rqt='UPDATE theme SET '.$field.' WHERE theme_id='.$idTheme.' LIMIT 1;';
            mysql_query($rqt) OR die(msgErrorSQL("updTheme() : ".mysql_error()));
            
            msgValidate($messageInfo);
            return;
        }
        msgInfos("Aucune modifications n'a été faite !");
    }
    
    /**
     * Fonction : : udpate les photos
     * 
     * @param type $idImage
     * @param type $nameImage
     * @param type $commentImage
     */
    function updImage($idImage, $nameImage, $commentImage)
    {
        $nameImage= onlyCaracters($nameImage);
        $commentImage= onlyCaracters($commentImage);
        
        if(!empty($nameImage))
        {
            $fieldName="image_name='".$nameImage."' ";
            $field=$fieldName;
        }
        
        if(!empty($commentImage))
        {
            $fieldComment="comment='".$commentImage."' ";
            $field=$fieldComment;
        }
        
        if (!empty($nameImage) && !empty($commentImage))
        {
            $field=$fieldName.', '.$fieldComment;
        }  
       
        if(!empty($field) && !empty($idImage))
        {
            $rqt='UPDATE image SET '.$field.' WHERE image_id='.$idImage.' LIMIT 1;';
            mysql_query($rqt) OR die(msgErrorSQL("updImage() : ".mysql_error()));
           
            msgValidate("L'upload a bien été effectué !");
            return;
        }
        
        msgInfos("Aucune modifications n'a été faite !");
    }
    
    /**
     * Fonfction : remoner un fichier
     * 
     * @param type $oldName
     * @param type $newName
     */
    function renameFilder($oldName, $newName)
    {
        $oldName= onlyCaracters($oldName);
        $newName= onlyCaracters($newName);
        
        rename($oldName, $newName);
    }
    
    /**
     * Fonction : recuperer l'id par le nom
     * 
     * @param type $themeOnglet
     * @return type
     */
    function getIdOngletByName($themeOnglet)
    {
        $themeOnglet= onlyCaracters($themeOnglet);
        $sqlRqt='SELECT onglet_order FROM onglet WHERE onglet_name="'.$themeOnglet.'" LIMIT 1;';

        $idThemeOnglet=-1;
        $result = mysql_query($sqlRqt, connect()) OR die(msgErrorSQL("getIdOngletByName() : ".mysql_error()));
        if (mysql_num_rows($result)>0)
        {
            $idThemeOnglet = mysql_result($result, 0, 'onglet_order');
        }
        
        return $idThemeOnglet;
    }
    
    /**
     * Fonction : récupération des données existantes
     * 
     * @param type $idTheme
     * @return type
     */
    function getOngletId($idTheme)
    {
        $idTheme= onlyInteger($idTheme);
        
        $sqlRqt= 'SELECT onglet_id FROM theme t WHERE t.theme_id='.$idTheme.' LIMIT 1;';
        $onglet_id=-1;
        
        $result = mysql_query($sqlRqt, connect()) OR die(msgErrorSQL("getOngletId() : ".mysql_error()));
        if (mysql_num_rows($result)>0)
        {
            $onglet_id = mysql_result($result, 0, 'onglet_id');
        }
        
        return $onglet_id;
    }
    
    /**
     * Fonction : récupération des données existantes
     * 
     * @param type $idTheme
     * @return type
     */
    function getOngletTheName($idTheme)
    {
        $idTheme= onlyInteger($idTheme);
        
        $sqlRqt= 'SELECT theme_title FROM theme t WHERE t.theme_id='.$idTheme.' LIMIT 1;';
        $onglet_name='';
        
        $result = mysql_query($sqlRqt, connect()) OR die(msgErrorSQL("getOngletTheName() : ".mysql_error()));
        if (mysql_num_rows($result)>0)
        {
            $onglet_name = mysql_result($result, 0, 'theme_title');
        }
        
        return $onglet_name;
    }
    
    /**
     * Fonction : affichage des images par theme
     * 
     * @global type $sql_request_img
     * @param type $theme_grp_id
     * @return type
     */
    function showTheme($theme_grp_id)
    {       
        
        $sql_request_img=('SELECT img.*, thm.theme_path
                            FROM image img JOIN theme thm ON (img.theme_grp_id=thm.theme_order)
                            WHERE theme_grp_id=');
        
        $rqst_slq=$sql_request_img.onlyInteger($theme_grp_id);
        $requete = mysql_query($rqst_slq) OR die(msgErrorSQL("showTheme() : ".mysql_error()));

        $count=1;

	$tab_image[$count]=array('', '', '', '');
        while($result=  mysql_fetch_object($requete))
        {
           $pathImg=$result->theme_path."/".$result->image_path;
           $tab_image[$count] = array($result->image_name,$pathImg, $result->author, $result->date_creation, $result->comment);  
           $count++;
        }
        
        return $tab_image;
    }
    
    function showAboutMe()
    {
            $fp = fopen ("aboutMe.txt", "r");  
            $contenu_du_fichier = fgets ($fp);  
            fclose ($fp);  
            echo $contenu_du_fichier;  
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
    function countField($table, $field1, $valField1, $field2, $valField2)
    {
	$table=onlyCaracters($table);
        $field1=  onlyCaracters($field1);
        $valField1=  onlyCaracters($valField1);
        $field2=  onlyCaracters($field2);
        $valField2=  onlyCaracters($valField2);
        $reqSelOnglet = 'SELECT * FROM '.$table.' WHERE '.$field1.'='.$valField1.' AND '.$field2.'="'.$valField2.'"';
        
        $requete=  mysql_query($reqSelOnglet) OR die(msgErrorSQL("countField() : ".mysql_error()));
        return mysql_num_rows($requete);
    }
    
    /**
     * Fonction : retourne le dernier id d'onglet ajouté
     * 
     * @return type
     */
    function getMaxOnglet()
    {
        $rqtOrd = mysql_query("SELECT onglet_order FROM onglet ORDER BY onglet_order DESC LIMIT 1") OR die(msgErrorSQL("getMaxOnglet() : ".mysql_error()));
        while($result=mysql_fetch_object($rqtOrd)){
            return $result->onglet_order;
        }
    }
    
   /**
    * Fonction : recupere id onglet
    * 
    * @param type $ongletTitle
    * @return type
    */ 
    function getIdOnglet($ongletTitle='')
    {
	$ongletTitle=  onlyCaracters($ongletTitle);

        $requete = mysql_query('SELECT onglet_order FROM onglet WHERE onglet_name="'.$ongletTitle.'" LIMIT 1') OR die(msgErrorSQL("getIdOnglet() : ".mysql_error()));
        while($result=mysql_fetch_object($requete))
        {
            return $result->onglet_order;
        }
    }    
    
    /**
     * Fonction : verifie s'il existe dans la table 
     * 
     * @param type $table
     * @param type $field
     * @param type $value
     *
     * @return type : le nombre de ligne présent 
     */
    function isExistInTable($table, $field, $value)
    {
	$table= onlyCaracters($table);
        $field= onlyCaracters($field);
        $value= onlyCaracters($value);  
        $reqCont= sprintf("SELECT * FROM ".$table." WHERE (".$field."='%s')", $value);
        
        $rqt = mysql_query($reqCont) OR die(msgErrorSQL("isExistInTable() : ".mysql_error()));
        $rqtDbl = mysql_num_rows($rqt);
        return ($rqtDbl);
    }
     
    /**
     * Fonction : retourne le nom du thème 
     * 
     */
    function getThemeName($idThm='')
    {
        $orderBy='theme_order;';
        if (!empty($idThm))
        {
            $idThm=  onlyInteger($idThm);
            $orderBy= 'FIND_IN_SET (theme_order, '.$idThm.') DESC;'; 
        }
        
        $requete = mysql_query('SELECT theme_title FROM theme ORDER BY '.$orderBy) OR die(msgErrorSQL("getThemeName() : ".mysql_error()));
       
        while($result=mysql_fetch_object($requete))
        {
            echo '<option>'.$result->theme_title.'</option>';
        }
    }
    
    /**
     * Fonction : retourne le nom du thème 
     * 
     */
    function getOngletName($idOng='')
    {
        $orderBy='onglet_order;';
        
        if (!empty($idOng))
        {
            $idOng=  onlyInteger($idOng);
            $orderBy= 'FIND_IN_SET (onglet_order, '.$idOng.') DESC;'; 
        }
        
        $requete = mysql_query('SELECT onglet_name FROM onglet ORDER BY '.$orderBy) OR die(msgErrorSQL("getOngletName() : ".mysql_error()));
        while($result=mysql_fetch_object($requete))
        {
            echo '<option>'.$result->onglet_name.'</option>';
        }
    }
    
    /**
     * Fonction : retourne l'id du à partir du nom du thème 
     * 
     * @param type $themeTitle : nom du thème
     */
    function getIdTheme($themeTitle='')
    {
		$themeTitle=  onlyCaracters($themeTitle);
		
		$requete = mysql_query('SELECT theme_order FROM theme WHERE theme_title="'.$themeTitle.'" LIMIT 1') OR die(msgErrorSQL("getIdTheme() : ".mysql_error()));
        while($result=mysql_fetch_object($requete))
        {
            return $result->theme_order;
        }
    }
    
    /**
     * Fonction : retourne le dernier id du thème ajouté
     * 
     * @return type
     */
    function getThemeMaxOrder()
    {
        $requete = mysql_query('SELECT theme_order FROM theme ORDER BY theme_order DESC LIMIT 1') OR die(msgErrorSQL("getThemeMaxOrder() : ".mysql_error()));
        while($result=mysql_fetch_object($requete))
        {
            return $result->theme_order;
        }
    }
    
    /**
     * Fonction : 
     * 
     * @param type $number
     * @return type
     */
    function onlyInteger($number)
    {
        $checkVar=-1;
	$number=htmlspecialchars($number);
		
	if(is_numeric($number))
        {
            $checkVar=$number;
        }
        return $checkVar;
    }


    



    /**
     * Fonction : protège des insertions sql
     * 
     * @param type $car
     * @return type
     */
    function onlyCaracters($car)
    {
        // $car1 = htmlspecialchars($car);
        // $car2 = strtr($car1, 'ÀÁÂÃÄÅÇÈÉÊËÌÍÎÏÒÓÔÕÖÙÚÛÜÝàáâãäåçèéêëìíîïðòóôõöùúûüýÿ-;*<>/', 'AAAAAACEEEEIIIIOOOOOUUUUYaaaaaaceeeeiiiioooooouuuuyy&&&&&&');
        // return  preg_replace('/([^.a-z0-9]+)/i', '-', $car2);
		return $car;
    }
        
    /**
     *  Fonction : rm() permet d'effacer un dossier, un fichier ou plusieurs fichiers
     * 
     * Cette fonction permet de passer en paramètre un fichier (fichier.html),
     * un ensemble de fichiers (*.jpg) ou un tableau de fichiers (tableau)
     *
     * @param type $fichier_ou_dossier
     * @return boolean
     */
    function rm($fichier_ou_dossier)
    {
        if (is_string($fichier_ou_dossier))
        {
            if (is_file($fichier_ou_dossier))
            {
                return unlink($fichier_ou_dossier);
            }
            else if (is_dir($fichier_ou_dossier))
            {
                $suppr_fichier = rm("$fichier_ou_dossier/*");
                if (!$suppr_fichier)
                {
                    return false;
                }
                return rmdir($fichier_ou_dossier);
            }
            else 
            { 
                $fichiers_masque = glob($fichier_ou_dossier);
                if ($fichiers_masque === false)
                {
                    return false;
                }
            
                $rslt = array_map('rm', $fichiers_masque);
                if (in_array(false, $rslt))
                {
                    return false;
                }
            }
        }
        else if (is_array($fichier_ou_dossier)) 
        {
            $rslt = array_map('rm', $fichier_ou_dossier);
            if (in_array(false, $rslt)) 
            {
                return false;
            }
        }
        else 
        {
            return false;
        }
        return true;
    }

?>

<script src="../js/jQuery.js"></script>
<script src="../js/bootstrap.js"></script>
<script src="../js/bootstrap-modal.js"></script>
<script src="../js/bootstrap-alert.js"></script>
<script src="../js/bootstrap-transition.js"></script>
