<!--<link rel="stylesheet" media="screen" type="text/css" href="css/main.css" />-->
<link rel="stylesheet" media="screen" type="text/css" href="css/bootstrap.css"/>
<link rel="stylesheet"media="screen" type="text/css" href="css/swipebox.css">
<?php

/**
 * Function show dynamique theme
 * 
 * @param type $grpId
 * @return string
 */
function showDynTheme($grpId)
{

    $visible = 'display:none;';

    if(is_numeric($grpId))
    {
        $tab_img = showTheme($grpId);

        echo('<div class="item active">
                <a href="'.$tab_img[1][1].'" class="swipebox" title="'.$tab_img[1][4].'">
                    <img height="460" width="700" src="'.$tab_img[1][1].'"/>
                </a>        
                <div align="right" id="legende" >'.$tab_img[1][4].'</div>
               </div>'
            );
        $count= 2;
        while ($count <= count($tab_img))
        {           
            echo('<div class="item" >
                    <a href="'.$tab_img[$count][1].'" class="swipebox" title="'.$tab_img[1][4].'">
                        <img height="460" width="700" src="'.$tab_img[$count][1].'"/>
                    </a>  
                    <div align="right" id="legende">'.$tab_img[$count][4].'</div>
                  </div>'
                );
            $count++;
        }
       
        // si plusieurs images
        if ($count > 2)
        {
            $visible ='display:visible;';
        }
        
    }

    return $visible;
} 


?>
<script src="js/jquery-1.9.0.min.js"></script>
<script src="js/ios-orientationchange-fix.js"></script>

<script src="js/jquery.swipebox.min.js"></script>
<script type="text/javascript">
        jQuery(function($) {
                $(".swipebox").swipebox();
        });
</script>