-- phpMyAdmin SQL Dump
-- version 3.3.10
-- http://www.phpmyadmin.net
--
-- Host: db.zut.edu.pl
-- Generation Time: May 11, 2026 at 10:56 AM
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
-- Table structure for table `kraina`
--

CREATE TABLE IF NOT EXISTS `kraina` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `nazwa` varchar(30) CHARACTER SET utf8 COLLATE utf8_polish_ci NOT NULL,
  `typ` ENUM('pobrzeza', 'pojezierze', 'nizina', 'wyzyna', 'kotlina podgorska', 'gory') NOT NULL,
  `powierzchnia` int(11) NOT NULL,
  `wysokosc` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;

--
-- Dumping data for table `kraina`
--

INSERT INTO `kraina` (`nazwa`, `typ`, `powierzchnia`, `wysokosc`) VALUES
('Mazury', 'pojezierze', 10000, 300),
('Podhale', 'gory', 800, 900),
('Bieszczady', 'gory', 1700, 1346),
('Kotlina Sandomierska', 'kotlina podgorska', 15000, 220),
('Wyżyna Krakowsko-Częstochowska', 'wyzyna', 2600, 450);

-- --------------------------------------------------------

--
-- Table structure for table `jeziora`
--

CREATE TABLE IF NOT EXISTS `jeziora` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `idKraina` int(11) NOT NULL,
  `nazwa` varchar(25) CHARACTER SET utf8 COLLATE utf8_polish_ci NOT NULL,
  `glebokosc` int(11) NOT NULL,
  `powierzchnia` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  FOREIGN KEY (`idKraina`) REFERENCES `kraina`(`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;

--
-- Dumping data for table `jeziora`
--
INSERT INTO `jeziora` (`nazwa`, `idKraina`, `glebokosc`, `powierzchnia`) VALUES
('Śniardwy', 1, 23, 22),
('Mamry', 1, 44, 10),
('Niegocin', 1, 39, 4),
('Hańcza', 2, 108, 1),
('Morskie Oko', 3, 51, 1);


-- --------------------------------------------------------

--
-- Table structure for table `pasmaGorskie`
--

CREATE TABLE IF NOT EXISTS `pasmaGorskie` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `idKraina` int(11) NOT NULL,
  `nazwa` varchar(25) CHARACTER SET utf8 COLLATE utf8_polish_ci NOT NULL,
  `najwyzszySzczyt` int(11) NOT NULL,
  `powierzchnia` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  FOREIGN KEY (`idKraina`) REFERENCES `kraina`(`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;

--
-- Dumping data for table `pasmaGorskie`
--
INSERT INTO `pasmaGorskie` (`nazwa`, `idKraina`, `najwyzszySzczyt`, `powierzchnia`) VALUES
('Tatry', 1, 2499, 19),
('Karkonosze', 2, 1603, 40),
('Bieszczady', 3, 1346, 50),
('Beskid Śląski', 4, 1257, 20),
('Pieniny', 5, 1050, 6);

-- --------------------------------------------------------

--
-- Table structure for table `wojewodztwo`
--

CREATE TABLE IF NOT EXISTS `wojewodztwo` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `nazwa` varchar(25) CHARACTER SET utf8 COLLATE utf8_polish_ci NOT NULL,
  `powierzchnia` int(11) NOT NULL,
  `liczbaLudności` int(11) NOT NULL,
  `sredniaWysokosc` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;

--
-- Dumping data for table `wojewodztwo`
--

INSERT INTO `wojewodztwo` (`nazwa`, `powierzchnia`, `liczbaLudności`, `sredniaWysokosc`) VALUES
('Zachodniopomorskie', 22892, 1690000, 50),
('Małopolskie', 15183, 3400000, 400),
('Mazowieckie', 35558, 5500000, 150),
('Podkarpackie', 17846, 2100000, 300),
('Warmińsko-Mazurskie', 24173, 1400000, 150);

-- --------------------------------------------------------

--
-- Table structure for table `rzeki`
--

CREATE TABLE IF NOT EXISTS `rzeki` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `nazwa` varchar(30) CHARACTER SET utf8 COLLATE utf8_polish_ci NOT NULL,
  `dlugosc` int(11) NOT NULL,
  `szerokosc` int(11) NOT NULL,
  `predkoscNurtu` int(11) NOT NULL,
  `przeplyw` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;

--
-- Dumping data for table `rzeki`
--

INSERT INTO `rzeki` (`nazwa`, `dlugosc`, `szerokosc`, `predkoscNurtu`, `przeplyw`) VALUES
('Wisła', 1047, 1000, 6, 1080),
('Odra', 854, 500, 5, 574),
('Warta', 808, 200, 4, 220),
('Bug', 772, 150, 3, 158),
('San', 457, 120, 7, 126);

-- --------------------------------------------------------

--
-- Table structure for table `wojewodztwoKraina`
--

CREATE TABLE IF NOT EXISTS `wojewodztwoKraina` (
  `idWojewodztwo` int(11) NOT NULL,
  `idKraina` int(11) NOT NULL,
  PRIMARY KEY (`idWojewodztwo`,`idKraina`),
  FOREIGN KEY (`idWojewodztwo`) REFERENCES `wojewodztwo`(`id`),
  FOREIGN KEY (`idKraina`) REFERENCES `kraina`(`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;

--
-- Dumping data for table `wojewodztwoKraina`
--

-- --------------------------------------------------------

--
-- Table structure for table `rzekaKraina`
--

CREATE TABLE IF NOT EXISTS `rzekaKraina` (
  `idRzeka` int(11) NOT NULL,
  `idKraina` int(11) NOT NULL,
  PRIMARY KEY (`idRzeka`,`idKraina`),
  FOREIGN KEY (`idRzeka`) REFERENCES `rzeki`(`id`),
  FOREIGN KEY (`idKraina`) REFERENCES `kraina`(`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;

--
-- Dumping data for table `rzekaKraina`
--

--
-- Constraints for dumped tables
--
