-- phpMyAdmin SQL Dump
-- version 3.3.10
-- http://www.phpmyadmin.net
--
-- Host: db.zut.edu.pl
-- Generation Time: May 13, 2026 at 10:55 AM
-- Server version: 1.0.339
-- PHP Version: 5.4.16

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `kp15319`
--

-- --------------------------------------------------------

--
-- Table structure for table `jeziora`
--

CREATE TABLE IF NOT EXISTS `jeziora` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `idKraina` int(11) NOT NULL,
  `nazwa` varchar(25) NOT NULL,
  `glebokosc` int(11) NOT NULL,
  `powierzchnia` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `idKraina` (`idKraina`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci AUTO_INCREMENT=6 ;

--
-- Dumping data for table `jeziora`
--

INSERT INTO `jeziora` (`id`, `idKraina`, `nazwa`, `glebokosc`, `powierzchnia`) VALUES
(1, 1, 'Śniardwy', 23, 22),
(2, 1, 'Mamry', 44, 10),
(3, 1, 'Niegocin', 39, 4),
(4, 2, 'Hańcza', 108, 1),
(5, 3, 'Morskie Oko', 51, 1);

-- --------------------------------------------------------

--
-- Table structure for table `kraina`
--

CREATE TABLE IF NOT EXISTS `kraina` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `nazwa` varchar(30) NOT NULL,
  `typ` enum('pobrzeza','pojezierze','nizina','wyzyna','kotlina podgorska','gory') NOT NULL,
  `powierzchnia` int(11) NOT NULL,
  `wysokosc` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci AUTO_INCREMENT=6 ;

--
-- Dumping data for table `kraina`
--

INSERT INTO `kraina` (`id`, `nazwa`, `typ`, `powierzchnia`, `wysokosc`) VALUES
(1, 'Mazury', 'pojezierze', 10000, 300),
(2, 'Podhale', 'gory', 800, 900),
(3, 'Bieszczady', 'gory', 1700, 1346),
(4, 'Kotlina Sandomierska', 'kotlina podgorska', 15000, 220),
(5, 'Wyżyna Krakowsko-Częstochowska', 'wyzyna', 2600, 450);

-- --------------------------------------------------------

--
-- Table structure for table `pasmaGorskie`
--

CREATE TABLE IF NOT EXISTS `pasmaGorskie` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `idKraina` int(11) NOT NULL,
  `nazwa` varchar(25) NOT NULL,
  `najwyzszySzczyt` int(11) NOT NULL,
  `powierzchnia` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `idKraina` (`idKraina`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci AUTO_INCREMENT=6 ;

--
-- Dumping data for table `pasmaGorskie`
--

INSERT INTO `pasmaGorskie` (`id`, `idKraina`, `nazwa`, `najwyzszySzczyt`, `powierzchnia`) VALUES
(1, 1, 'Tatry', 2499, 19),
(2, 2, 'Karkonosze', 1603, 40),
(3, 3, 'Bieszczady', 1346, 50),
(4, 4, 'Beskid Śląski', 1257, 20),
(5, 5, 'Pieniny', 1050, 6);

-- --------------------------------------------------------

--
-- Table structure for table `rzekaKraina`
--

CREATE TABLE IF NOT EXISTS `rzekaKraina` (
  `idRzeka` int(11) NOT NULL,
  `idKraina` int(11) NOT NULL,
  PRIMARY KEY (`idRzeka`,`idKraina`),
  KEY `idKraina` (`idKraina`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;

--
-- Dumping data for table `rzekaKraina`
--

INSERT INTO `rzekaKraina` (`idRzeka`, `idKraina`) VALUES
(1, 2),
(1, 4),
(1, 5),
(2, 1),
(3, 5),
(4, 4),
(5, 3),
(5, 4);

-- --------------------------------------------------------

--
-- Table structure for table `rzeki`
--

CREATE TABLE IF NOT EXISTS `rzeki` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `nazwa` varchar(30) NOT NULL,
  `dlugosc` int(11) NOT NULL,
  `maksSzerokosc` int(11) NOT NULL,
  `predkoscNurtu` int(11) NOT NULL,
  `przeplyw` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci AUTO_INCREMENT=6 ;

--
-- Dumping data for table `rzeki`
--

INSERT INTO `rzeki` (`id`, `nazwa`, `dlugosc`, `maksSzerokosc`, `predkoscNurtu`, `przeplyw`) VALUES
(1, 'Wisła', 1047, 1000, 6, 1080),
(2, 'Odra', 854, 500, 5, 574),
(3, 'Warta', 808, 200, 4, 220),
(4, 'Bug', 772, 150, 3, 158),
(5, 'San', 457, 120, 7, 126);

-- --------------------------------------------------------

--
-- Table structure for table `stolice`
--

CREATE TABLE IF NOT EXISTS `stolice` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `nazwa` varchar(25) NOT NULL,
  `powierzchnia` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci AUTO_INCREMENT=11 ;

--
-- Dumping data for table `stolice`
--

INSERT INTO `stolice` (`id`, `nazwa`, `powierzchnia`) VALUES
(1, 'Szczecin', 22892),
(2, 'Kraków', 15183),
(3, 'Warszawa', 35558),
(4, 'Rzeszów', 17846),
(5, 'Olsztyn', 24173);

-- --------------------------------------------------------

--
-- Table structure for table `wojewodztwo`
--

CREATE TABLE IF NOT EXISTS `wojewodztwo` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `nazwa` varchar(25) NOT NULL,
  `powierzchnia` int(11) NOT NULL,
  `liczbaLudności` int(11) NOT NULL,
  `sredniaWysokosc` int(11) NOT NULL,
  `idStolica` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `idStolica` (`idStolica`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci AUTO_INCREMENT=6 ;

--
-- Dumping data for table `wojewodztwo`
--

INSERT INTO `wojewodztwo` (`id`, `nazwa`, `powierzchnia`, `liczbaLudności`, `sredniaWysokosc`, `idStolica`) VALUES
(1, 'Zachodniopomorskie', 22892, 1690000, 50, 1),
(2, 'Małopolskie', 15183, 3400000, 400, 2),
(3, 'Mazowieckie', 35558, 5500000, 150, 3),
(4, 'Podkarpackie', 17846, 2100000, 300, 4),
(5, 'Warmińsko-Mazurskie', 24173, 1400000, 150, 5);

-- --------------------------------------------------------

--
-- Table structure for table `wojewodztwoKraina`
--

CREATE TABLE IF NOT EXISTS `wojewodztwoKraina` (
  `idWojewodztwo` int(11) NOT NULL,
  `idKraina` int(11) NOT NULL,
  PRIMARY KEY (`idWojewodztwo`,`idKraina`),
  KEY `idKraina` (`idKraina`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;

--
-- Dumping data for table `wojewodztwoKraina`
--

INSERT INTO `wojewodztwoKraina` (`idWojewodztwo`, `idKraina`) VALUES
(1, 1),
(2, 2),
(2, 5),
(3, 4),
(4, 3),
(4, 4),
(5, 1);

--
-- Constraints for dumped tables
--

--
-- Constraints for table `jeziora`
--
ALTER TABLE `jeziora`
  ADD CONSTRAINT `jeziora_ibfk_1` FOREIGN KEY (`idKraina`) REFERENCES `kraina` (`id`);

--
-- Constraints for table `pasmaGorskie`
--
ALTER TABLE `pasmaGorskie`
  ADD CONSTRAINT `pasmaGorskie_ibfk_1` FOREIGN KEY (`idKraina`) REFERENCES `kraina` (`id`);

--
-- Constraints for table `rzekaKraina`
--
ALTER TABLE `rzekaKraina`
  ADD CONSTRAINT `rzekaKraina_ibfk_1` FOREIGN KEY (`idRzeka`) REFERENCES `rzeki` (`id`),
  ADD CONSTRAINT `rzekaKraina_ibfk_2` FOREIGN KEY (`idKraina`) REFERENCES `kraina` (`id`);

--
-- Constraints for table `wojewodztwo`
--
ALTER TABLE `wojewodztwo`
  ADD CONSTRAINT `wojewodztwo_ibfk_1` FOREIGN KEY (`idStolica`) REFERENCES `stolice` (`id`);

--
-- Constraints for table `wojewodztwoKraina`
--
ALTER TABLE `wojewodztwoKraina`
  ADD CONSTRAINT `wojewodztwoKraina_ibfk_1` FOREIGN KEY (`idWojewodztwo`) REFERENCES `wojewodztwo` (`id`),
  ADD CONSTRAINT `wojewodztwoKraina_ibfk_2` FOREIGN KEY (`idKraina`) REFERENCES `kraina` (`id`);
