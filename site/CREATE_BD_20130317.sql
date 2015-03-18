# --------------------------------------------------------
# Host:                         db461625891.db.1and1.com
# Database:                     db461625891
# Server version:               5.5.24-log
# Server OS:                    Win64
# HeidiSQL version:             5.0.0.3272
# Date/time:                    2013-03-17 04:02:18
# --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
# Dumping database structure for satchmosql
CREATE DATABASE IF NOT EXISTS `db461625891` /*!40100 DEFAULT CHARACTER SET latin1 */;
USE `db461625891`;


# Dumping structure for table satchmosql.image
DROP TABLE IF EXISTS `image`;
CREATE TABLE IF NOT EXISTS `image` (
  `image_id` int(100) unsigned NOT NULL AUTO_INCREMENT,
  `theme_grp_id` int(100) unsigned DEFAULT NULL COMMENT 'link onglet',
  `image_name` varchar(500) COLLATE utf8_bin NOT NULL COMMENT 'image name',
  `image_path` varchar(500) COLLATE utf8_bin NOT NULL COMMENT 'path name',
  `author` varchar(500) COLLATE utf8_bin NOT NULL,
  `date_creation` date NOT NULL COMMENT 'date',
  `comment` varchar(50) COLLATE utf8_bin NOT NULL COMMENT 'path comment',
  `visible` tinyint(1) unsigned zerofill NOT NULL DEFAULT '1',
  PRIMARY KEY (`image_id`),
  KEY `FK_image_multionglet` (`theme_grp_id`),
  CONSTRAINT `FK_image_theme` FOREIGN KEY (`theme_grp_id`) REFERENCES `theme` (`theme_order`)
) ENGINE=InnoDB AUTO_INCREMENT=50 DEFAULT CHARSET=utf8 COLLATE=utf8_bin COMMENT='contient le liens vers les differentes images, ainsi que les path et leurs onglets\r\n';

# Dumping data for table satchmosql.image: 7 rows
DELETE FROM `image`;
/*!40000 ALTER TABLE `image` DISABLE KEYS */;
INSERT INTO `image` (`image_id`, `theme_grp_id`, `image_name`, `image_path`, `author`, `date_creation`, `comment`, `visible`) VALUES (1, 2, 'free run 1', 'free run 1.jpg', '', '2013-02-16', '', 1), (2, 2, 'free run 2', 'free run 2.jpg', '', '2013-03-16', '', 1), (3, 3, 'detente1', 'detente1.jpg', '', '2013-03-06', '', 1), (4, 3, 'detente2', 'detente2.jpg', '', '2013-01-16', '', 1), (5, 3, 'detente3', 'detente3.jpg', '', '2013-03-16', '', 1), (6, 1, 'happy_2', 'happy_2.jpg', '', '2013-03-14', '', 1);
/*!40000 ALTER TABLE `image` ENABLE KEYS */;


# Dumping structure for table satchmosql.onglet
DROP TABLE IF EXISTS `onglet`;
CREATE TABLE IF NOT EXISTS `onglet` (
  `onglet_id` int(10) NOT NULL AUTO_INCREMENT,
  `onglet_order` int(100) unsigned NOT NULL,
  `onglet_name` varchar(500) NOT NULL,
  `visible` tinyint(2) DEFAULT '1',
  PRIMARY KEY (`onglet_id`),
  UNIQUE KEY `onglet_id` (`onglet_id`),
  UNIQUE KEY `onglet_order` (`onglet_order`)
) ENGINE=InnoDB AUTO_INCREMENT=11 DEFAULT CHARSET=latin1;

# Dumping data for table satchmosql.onglet: 6 rows
DELETE FROM `onglet`;
/*!40000 ALTER TABLE `onglet` DISABLE KEYS */;
INSERT INTO `onglet` (`onglet_id`, `onglet_order`, `onglet_name`, `visible`) VALUES (1, 1, 'RENDERINGS', 1), (2, 2, 'PHOTOS', 1), (3, 3, 'GALLERY', 1), (4, 4, 'GOODIES', 1), (5, 5, 'TEACHING', 1), (6, 6, 'LARGESCALE', 1);
/*!40000 ALTER TABLE `onglet` ENABLE KEYS */;


# Dumping structure for table satchmosql.theme
DROP TABLE IF EXISTS `theme`;
CREATE TABLE IF NOT EXISTS `theme` (
  `theme_id` int(100) unsigned NOT NULL AUTO_INCREMENT COMMENT 'cle primaire tab',
  `theme_order` int(100) unsigned NOT NULL,
  `onglet_id` int(100) unsigned NOT NULL,
  `theme_title` varchar(500) COLLATE utf8_bin NOT NULL COMMENT 'nom du title de l onglet',
  `theme_href` varchar(500) COLLATE utf8_bin NOT NULL COMMENT 'reference de l onglet',
  `theme_path` varchar(50) COLLATE utf8_bin DEFAULT '#' COMMENT 'path image',
  `comment` varchar(500) COLLATE utf8_bin NOT NULL,
  `visible` tinyint(1) unsigned DEFAULT '1',
  PRIMARY KEY (`theme_id`),
  UNIQUE KEY `onglet_grp_id` (`theme_order`),
  KEY `onglet_id` (`onglet_id`),
  CONSTRAINT `FK_theme_onglet` FOREIGN KEY (`onglet_id`) REFERENCES `onglet` (`onglet_order`)
) ENGINE=InnoDB AUTO_INCREMENT=46 DEFAULT CHARSET=utf8 COLLATE=utf8_bin COMMENT='table contenant les differents onglets dynamique du site';

# Dumping data for table satchmosql.theme: 5 rows
DELETE FROM `theme`;
/*!40000 ALTER TABLE `theme` DISABLE KEYS */;
INSERT INTO `theme` (`theme_id`, `theme_order`, `onglet_id`, `theme_title`, `theme_href`, `theme_path`, `comment`, `visible`) VALUES (1, 1, 1, 'Photos vacance', '', 'uploads/Photos vacance', '', 1), (2, 3, 1, 'Photos cool', '', 'uploads/Photos cool', '', 1), (18, 2, 1, 'Free Run', '', 'uploads/Free Run', '', 1);
/*!40000 ALTER TABLE `theme` ENABLE KEYS */;
/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
