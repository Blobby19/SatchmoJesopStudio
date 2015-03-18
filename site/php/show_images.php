<!--<link rel="stylesheet" media="screen" type="text/css" href="css/main.css" />-->
<link rel="stylesheet" media="screen" type="text/css" href="css/bootstrap.css"/>
<?php

function showDynTheme($grpId)
{
    $tab_img = showTheme($grpId);
    
    echo('<div class="item active"><img height="460" width="700" src="'.$tab_img[1][1].'"/></div>');
    $count= 2;
    while ($count <= count($tab_img)){           
        echo('<div class="item"><img height="460" width="700" src="'.$tab_img[$count][1].'"/></div>');
        $count++;
    }
    $visible = 'display:visible;';
    if ($count == 2)
    {
        $visible ='display:none;';
    }
    
    return $visible;
} 


?>
