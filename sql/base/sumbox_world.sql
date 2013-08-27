-- phpMyAdmin SQL Dump
-- version 3.5.2.2
-- http://www.phpmyadmin.net
--
-- Client: localhost
-- Généré le: Mar 27 Août 2013 à 15:21
-- Version du serveur: 5.5.27
-- Version de PHP: 5.4.7

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Base de données: `sumbox_world`
--

-- --------------------------------------------------------

--
-- Structure de la table `breed_start_infos`
--

CREATE TABLE IF NOT EXISTS `race_start_infos` (
  `race` tinyint(2) unsigned NOT NULL,
  `map_id` smallint(5) unsigned NOT NULL,
  `cell_id` smallint(3) unsigned NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Contenu de la table `breed_start_infos`
--

INSERT INTO `breed_start_infos` (`race`, `map_id`, `cell_id`) VALUES
(1, 7554, 255),
(2, 7554, 255),
(3, 7554, 255),
(4, 7554, 255),
(5, 7554, 255),
(6, 7554, 255),
(7, 7554, 255),
(8, 7554, 255),
(9, 7554, 255),
(10, 7554, 255),
(11, 7554, 255),
(12, 7554, 255);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
