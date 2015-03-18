
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01//EN" "http://www.w3.org/TR/html40/strict.dtd">
<script src="http://ajax.googleapis.com/ajax/libs/jquery/1.4.2/jquery.min.js"></script>
<script src="http://ajax.googleapis.com/ajax/libs/jqueryui/1.8.2/jquery-ui.min.js"></script>
<script src="js/jquery-1.7.2.min.js"></script>
<script src="js/lightbox.js"></script>
    
<link href="css/lightbox.css" rel="stylesheet" />
<script>
jQuery(document).ready(function() {
    jQuery('.expander').hide();
    jQuery('.trigger').click(function() {
        jQuery(this).next('.expander').slideToggle();
    });
});
</script>

<html>
    <head>
        <meta name="robots" content="noindex, nofollow">
        <title>Satchmo Jesop Studio</title>
        <meta name="description" content="Satchmo Jesop Studio: Architectural renderings ,Photography, project communication, teaching">
        <meta name="keywords" content="Satchmo, Jesop, Studio, Architectural, renderings, Photography, project communication, teaching photo, photographe, photographie, BILD, Carnets, dessin, drafts, architecture, exposition, musée, papier, pliage,coffret, newyork, paris, geneve, lausanne, epfl, ecole d'architecture, edition, livre, album, rendu">
        <meta http-equiv="Content-type" content="text/html; charset=UTF-8">
	    <meta name="viewport" content="width=device-width, target-densitydpi=device-dpi"/>
		<link rel="icon" type="image/gif" href="images/favicon/satchmo.gif">
        <link rel="stylesheet" media="screen" type="text/css" href="css/satchmo.css" />
		
        <?php
            include './php/functions.inc';
            $grpId= themeAleatoire();
            
            if(isset($_GET) && (!empty($_GET['satchmojesopstudio']))){
                $grpId=$_GET['satchmojesopstudio'];
            }
        ?>
    </head>
    <body>
        <div id="global">
            
            <div id="leftcol">
                <script type="text/javascript">
                    $(document).ready(function() {
                        // Au chargement, on cache tous les dd
                        $('dl dd').hide();
                        // Au clic
                        $('dl dt').css('cursor', 'pointer').click( function() {
                            // On ajoute la classe "visible" aux dd associés au dt cliqué, s'ils sont déjà visibles
                            if ($(this).nextUntil('dt').is('dd:visible'))
                                $(this).nextUntil('dt').addClass('visible');

                            // On cache tous les dd
                            $('dl dd').slideUp();

                            // On ferme les dd associés au dt cliqué ayant la classe "visible" (ils étaient ouvert dans les cache)
                            if ($(this).nextUntil('dt').is('dd.visible'))
                                $(this).nextUntil('dt').removeClass('visible').slideUp();
                            // On ouvre les dd associés au dt cliqué qui étaient fermés
                                else
                            $(this).nextUntil('dt').slideDown();
                        });
                    });
                </script>
                <div id="menu">
                    <dl>
                    <?php 
                        if((empty($_GET['satchmojesopstudio'])) || $_GET['satchmojesopstudio']!='aboutme')
                        {?>
                            <dt>
                                <a class="myA" href="./accueil.php?satchmojesopstudio=aboutme">
                                    <h1 id="ABOUTME" class="myH1">ABOUT ME</h1>
                                </a>
                            </dt>
                        <?php
                        }
                        else
                        {?>
                            <dt>
                                <a class="myA" href="./accueil.php?satchmojesopstudio=aboutme">
                                    <h1 id="ABOUTME" class="myH1 clicked">ABOUT ME</h1>
                                </a>
                            </dt>
                        <?php 
                        }
                        viewTab($grpId);
                        ?>
                    </dl> 
                </div>

                <div id="profil">
					<table width="280" height="250" border="0" cellpadding="0">
						<tr>
							<td width="40">&nbsp;</td>
							<td valign="bottom">
								<div id="logo" class="trigger"><a><img src="images/satchmojesopstudio-small.jpg" alt="satchmo jesop studio" border="0"></a></div>
								<div id="info" class="expander">
									<?php getPdf()?><br><br>
									<?php getInfo();?><br>
									<?php getAdresseMail()?><br><br>
									<a href="https://www.facebook.com/pages/Satchmo-Jesop-Studio/121633198027001"><img src="images/facebook-satchmo-jesop.jpg" width="15" alt="satchmo jesop studio photo" border="0"></a>
								</div>
							</td>
						</tr>
					</table>
				</div>
            </div>
            
            <!--Fin de la colonne de gauche -->
            
            <div id="righttcol">
                <div id="container">
                <?php
                    if((empty($_GET['satchmojesopstudio'])) || $_GET['satchmojesopstudio']!='aboutme'){
                            ?>
                        <!--<img height="460" width="700" src="images/test-image.jpeg">-->
                        <div id="myCarousel"  class="carousel slide">
                            <!-- Carousel items -->
                            <div class="carousel-inner" height="460" width="700"> 
                                <?php
                                  include './php/show_images.php';
                                  $visible =  showDynTheme($grpId);
                                ?>   
                            </div>
                             <!-- Carousel nav -->
                             <?php
                             echo('
                                <a class="carousel-control left" href="#myCarousel" data-slide="prev" style="'.$visible.'">&lsaquo;</a>
                                <a class="carousel-control right" href="#myCarousel" data-slide="next" style="'.$visible.'">&rsaquo;</a>
                                ');
                            ?>
                        </div>
                        <?php }
                             else{
                                include './php/show_images.php';
                                showAboutMe();
                            }
                            
                        ?>
                </div>
            </div>
            <div id="footer">
				<table width="980" border="0" cellpadding="0">
					<tr>
						<td height="30" align="left">
							<h3 class="myH3">satchmojesopstudio.com ©MMXIII </h3>
						</td>
						<td width="10"></td>
					</tr>
				</table>
			</div>
        </div>
        <script type="text/javascript">
            $(function() {
                $('#logo > li').hover(
                    function () {
                        var $this = $(this);
                        $('a',$this).stop(true,true).animate({
                            'bottom':'-15px'
                            }, 300);
                        $('i',$this).stop(true,true).animate({
                            'top':'-10px'
                            }, 400);
                    },
                    function () {
                        var $this = $(this);
                        $('a',$this).stop(true,true).animate({
                            'bottom':'-95px'
                            }, 300);
                        $('i',$this).stop(true,true).animate({
                            'top':'50px'
                            }, 400);
                    }
                );
            });
        </script>
        <script src="js/jQuery.js"></script>
        <script src="js/bootstrap.js"></script>
        <script src="js/bootstrap-modal.js"></script>
        <script src="js/bootstrap-alert.js"></script>
        <script src="js/bootstrap-transition.js"></script>
        <script src="js/bootstrap-carousel.js"></script>

        <script type="text/javascript">
            !function ($) {
              $(function(){
                // carousel demo
                $('.carousel').carousel()
              })
            }(window.jQuery)
        </script>
    </body>
</html>