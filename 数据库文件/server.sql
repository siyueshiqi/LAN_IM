-- MySQL dump 10.13  Distrib 5.5.34, for debian-linux-gnu (i686)
--
-- Host: localhost    Database: serverIMDB
-- ------------------------------------------------------
-- Server version	5.5.34-0ubuntu0.12.04.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `DateCounter`
--

DROP TABLE IF EXISTS `DateCounter`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `DateCounter` (
  `date` date NOT NULL,
  `userTimes` int(11) NOT NULL,
  `flockTimes` int(11) NOT NULL,
  `discussionTimes` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='utf8_general_ci';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `DateCounter`
--

LOCK TABLES `DateCounter` WRITE;
/*!40000 ALTER TABLE `DateCounter` DISABLE KEYS */;
INSERT INTO `DateCounter` VALUES ('2014-05-07',4,4,0),('2014-05-08',0,0,4),('2014-05-09',0,1,17),('2014-05-10',0,6,11),('2014-05-11',0,1,3),('2014-05-13',0,1,0),('2014-05-17',1,1,1),('2014-05-18',0,3,1),('2014-05-24',0,2,0);
/*!40000 ALTER TABLE `DateCounter` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `DiscussionInformation`
--

DROP TABLE IF EXISTS `DiscussionInformation`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `DiscussionInformation` (
  `discussionID` varchar(15) NOT NULL,
  `creatorID` varchar(15) NOT NULL,
  `createDate` date NOT NULL,
  `discussionName` varchar(50) NOT NULL,
  `theme` varchar(100) NOT NULL,
  PRIMARY KEY (`discussionID`),
  KEY `UserInformation_DiscussionInformation_creatorID` (`creatorID`),
  CONSTRAINT `UserInformation_DiscussionInformation_creatorID` FOREIGN KEY (`creatorID`) REFERENCES `UserInformation` (`userID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='utf8_general_ci';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `DiscussionInformation`
--

LOCK TABLES `DiscussionInformation` WRITE;
/*!40000 ALTER TABLE `DiscussionInformation` DISABLE KEYS */;
INSERT INTO `DiscussionInformation` VALUES ('2014051121','2014050702','2014-05-11','dddd','ddd'),('2014051123','2014050703','2014-05-11','apple的IM讨论组','没有主题'),('2014051721','2014051701','2014-05-17','haa的IM讨论组','没有主题'),('2014051821','2014051701','2014-05-18','haa的IM讨论组','没有主题');
/*!40000 ALTER TABLE `DiscussionInformation` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `FlockInformation`
--

DROP TABLE IF EXISTS `FlockInformation`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `FlockInformation` (
  `flockID` varchar(15) NOT NULL,
  `creatorID` varchar(15) NOT NULL,
  `createDate` date NOT NULL,
  `flockName` varchar(50) NOT NULL,
  `theme` varchar(100) NOT NULL,
  PRIMARY KEY (`flockID`),
  KEY `UserInformation_FlockInformation_creatorID` (`creatorID`),
  CONSTRAINT `UserInformation_FlockInformation_creatorID` FOREIGN KEY (`creatorID`) REFERENCES `UserInformation` (`userID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='utf8_general_ci';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `FlockInformation`
--

LOCK TABLES `FlockInformation` WRITE;
/*!40000 ALTER TABLE `FlockInformation` DISABLE KEYS */;
INSERT INTO `FlockInformation` VALUES ('2014051111','2014050702','2014-05-11','sdfsdfsd','sdfsd'),('2014051311','2014050701','2014-05-13','yun的IM群','没有主题'),('2014051711','2014051701','2014-05-17','haa的IM群','没有主题'),('2014051811','2014050704','2014-05-18','mick的IM群','没有主题'),('2014051812','2014051701','2014-05-18','haafgf的IM群','没有主题'),('2014051813','2014050701','2014-05-18','雨舒意的IM群','没有主题'),('2014052411','2014050703','2014-05-24','apple的IM群','没有主题'),('2014052412','2014050702','2014-05-24','dd','没有主题');
/*!40000 ALTER TABLE `FlockInformation` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `FlockSpace`
--

DROP TABLE IF EXISTS `FlockSpace`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `FlockSpace` (
  `flockSpaceNum` int(11) NOT NULL AUTO_INCREMENT,
  `flockID` varchar(15) NOT NULL,
  `fileType` varchar(20) NOT NULL,
  `filePath` varchar(50) NOT NULL,
  `fileName` varchar(50) NOT NULL,
  `fileInformation` varchar(100) DEFAULT NULL,
  `senderID` varchar(15) NOT NULL,
  `downloadTimes` int(11) NOT NULL,
  PRIMARY KEY (`flockSpaceNum`),
  KEY `FlockInformation_FlockSpace_flockID` (`flockID`),
  KEY `UserInformation_FlockSpace_senderID` (`senderID`),
  CONSTRAINT `FlockInformation_FlockSpace_flockID` FOREIGN KEY (`flockID`) REFERENCES `FlockInformation` (`flockID`),
  CONSTRAINT `UserInformation_FlockSpace_senderID` FOREIGN KEY (`senderID`) REFERENCES `UserInformation` (`userID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `FlockSpace`
--

LOCK TABLES `FlockSpace` WRITE;
/*!40000 ALTER TABLE `FlockSpace` DISABLE KEYS */;
/*!40000 ALTER TABLE `FlockSpace` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `HistoryMessage`
--

DROP TABLE IF EXISTS `HistoryMessage`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `HistoryMessage` (
  `messageID` int(11) NOT NULL AUTO_INCREMENT,
  `senderID` varchar(15) NOT NULL,
  `receiverID` varchar(15) NOT NULL,
  `content` varchar(1000) NOT NULL DEFAULT '',
  `dateTime` datetime NOT NULL,
  PRIMARY KEY (`messageID`),
  KEY `UserInformation_HistoryMessage_senderID` (`senderID`),
  KEY `UserInformation_HistoryMessage_receiverID` (`receiverID`),
  CONSTRAINT `UserInformation_HistoryMessage_receiverID` FOREIGN KEY (`receiverID`) REFERENCES `UserInformation` (`userID`),
  CONSTRAINT `UserInformation_HistoryMessage_senderID` FOREIGN KEY (`senderID`) REFERENCES `UserInformation` (`userID`)
) ENGINE=InnoDB AUTO_INCREMENT=374 DEFAULT CHARSET=utf8 COMMENT='utf8_general_ci';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `HistoryMessage`
--

LOCK TABLES `HistoryMessage` WRITE;
/*!40000 ALTER TABLE `HistoryMessage` DISABLE KEYS */;
INSERT INTO `HistoryMessage` VALUES (202,'2014050702','2014050701','erer','2014-05-21 22:24:22'),(203,'2014050702','2014050701','rtrtrtrtrtrtrrt','2014-05-21 22:24:30'),(204,'2014050701','2014050702','hgjghjgh','2014-05-21 22:33:59'),(205,'2014050701','2014050702','ghjgh','2014-05-21 22:34:10'),(206,'2014050701','2014050702','sdfds','2014-05-21 22:35:20'),(207,'2014050701','2014050702','sdfdsfsd','2014-05-21 22:35:36'),(208,'2014050702','2014050701','.m,','2014-05-21 22:36:33'),(209,'2014050702','2014050703','m,.m,','2014-05-21 22:36:48'),(210,'2014050702','2014050701','ghjfg','2014-05-21 22:37:15'),(211,'2014050702','2014050701','ghjgh','2014-05-21 22:37:16'),(212,'2014050702','2014050701','ghjghghjghghjghj','2014-05-21 22:37:33'),(213,'2014050702','2014050701','ghjghjghghjgh','2014-05-21 22:37:39'),(214,'2014050702','2014050701','ghjgh','2014-05-21 22:37:45'),(215,'2014050702','2014050701','dfgdf','2014-05-21 22:52:42'),(216,'2014050701','2014050702','dsfg','2014-05-21 23:07:01'),(217,'2014050701','2014050702','dsfgsdfgsd','2014-05-21 23:07:02'),(218,'2014050701','2014050702','sdfgdsf','2014-05-21 23:07:03'),(219,'2014050702','2014050701','sdfgsdf','2014-05-21 23:07:13'),(220,'2014050702','2014050701','dsfgdsf','2014-05-21 23:07:14'),(221,'2014050702','2014050701','dsfgdsf','2014-05-21 23:07:15'),(222,'2014050702','2014050701','sdfgdfs','2014-05-21 23:07:16'),(223,'2014050702','2014050701','1111111111','2014-05-21 23:16:16'),(224,'2014050702','2014050701','11111111111111','2014-05-21 23:16:19'),(225,'2014050701','2014050702','222222222222','2014-05-21 23:16:20'),(226,'2014050701','2014050702','333333333333','2014-05-21 23:16:22'),(227,'2014050702','2014050701','444444444444','2014-05-21 23:16:24'),(228,'2014050701','2014050702','555555555555','2014-05-21 23:16:26'),(229,'2014050702','2014050701','66666666666','2014-05-21 23:16:28'),(230,'2014050702','2014050701','dfgfd','2014-05-21 23:19:19'),(231,'2014050702','2014050701','ghg','2014-05-21 23:19:32'),(232,'2014050703','2014050701','fghfghfg','2014-05-21 23:21:05'),(233,'2014050703','2014050701','fghfg','2014-05-21 23:21:06'),(234,'2014050703','2014050701','dfgdfgdfdfgdfgdf','2014-05-21 23:22:45'),(235,'2014050703','2014050701','我    2014-05-21 23:21:05: ','2014-05-21 23:22:57'),(236,'2014050702','2014050701','asdas','2014-05-21 23:25:23'),(237,'2014050702','2014050701','asdas','2014-05-21 23:25:29'),(239,'2014050701','2014050702','csdsdfsdsdfsd','2014-05-22 00:30:47'),(240,'2014050701','2014050702','sdfsdfsd','2014-05-22 00:30:48'),(241,'2014050701','2014050702','asdfsda','2014-05-22 00:30:49'),(242,'2014050701','2014050702','asdfsd','2014-05-22 00:30:50'),(243,'2014050701','2014050702','sdafsad','2014-05-22 00:30:51'),(244,'2014050701','2014050702','sdfsda','2014-05-22 00:30:52'),(245,'2014050701','2014050702','dsfgds','2014-05-22 00:32:49'),(246,'2014050701','2014050702','qqqqqqq','2014-05-22 00:59:25'),(247,'2014050702','2014050701','tyuyt','2014-05-24 08:50:10'),(248,'2014050701','2014050703','asdfsad','2014-05-24 15:20:57'),(249,'2014050703','2014050701','sadfas','2014-05-24 15:21:00'),(250,'2014050701','2014050703','dfgfd','2014-05-24 15:21:50'),(251,'2014050702','2014050701','dsfds','2014-05-24 15:22:26'),(252,'2014050702','2014050701','sdfsd','2014-05-24 15:22:29'),(253,'2014050702','2014050701','fgfgf','2014-05-24 16:38:50'),(254,'2014050702','2014050701','fghg','2014-05-24 16:43:52'),(255,'2014050702','2014050701','gfhfg','2014-05-24 16:43:54'),(256,'2014050702','2014050701','gfhfg','2014-05-24 16:43:56'),(257,'2014050702','2014050701','fghfg','2014-05-24 16:43:57'),(258,'2014050701','2014050702','fghfg','2014-05-24 16:44:25'),(259,'2014050701','2014050702','hh','2014-05-24 16:44:32'),(260,'2014050701','2014050702','dfgdfgdf','2014-05-24 16:46:25'),(261,'2014050701','2014050702','dgdfgdf','2014-05-24 16:46:26'),(262,'2014050701','2014050702','dfgdfgdf','2014-05-24 16:46:27'),(263,'2014050702','2014050701','dfgdf','2014-05-24 16:46:34'),(264,'2014050702','2014050701','dfgdf','2014-05-24 16:46:35'),(265,'2014050702','2014050701','dfgdfdfgdf','2014-05-24 16:46:42'),(266,'2014050702','2014050701','sdfds','2014-05-24 16:47:10'),(267,'2014050702','2014050701','sdfds','2014-05-24 16:47:11'),(268,'2014050702','2014050701','sdfsd','2014-05-24 16:47:13'),(269,'2014050701','2014050702','dsfsd','2014-05-24 17:06:42'),(270,'2014050701','2014050702','sdfds','2014-05-24 17:06:45'),(271,'2014050702','2014050701','sdfsd','2014-05-24 17:06:52'),(272,'2014050701','2014050702','sdfds','2014-05-24 17:07:02'),(273,'2014050702','2014050701','sdfsd','2014-05-24 17:07:03'),(274,'2014050701','2014050702','sdfsd','2014-05-24 17:07:11'),(275,'2014050702','2014050701','dsfds','2014-05-24 17:07:15'),(276,'2014050701','2014050702','sdfsd','2014-05-24 17:07:16'),(277,'2014050701','2014050702','sdfsd','2014-05-24 17:07:18'),(278,'2014050701','2014050702','sdfds','2014-05-24 17:07:21'),(279,'2014050701','2014050702','sdfds','2014-05-24 17:07:25'),(280,'2014050701','2014050702','sdfsd','2014-05-24 17:07:26'),(281,'2014050701','2014050702','1','2014-05-24 17:07:29'),(282,'2014050701','2014050702','2','2014-05-24 17:07:30'),(283,'2014050701','2014050702','3','2014-05-24 17:07:33'),(284,'2014050701','2014050702','4','2014-05-24 17:07:34'),(285,'2014050701','2014050702','5','2014-05-24 17:07:35'),(286,'2014050702','2014050701','ghfg','2014-05-24 17:18:59'),(287,'2014050702','2014050701','gfhfg','2014-05-24 17:19:01'),(288,'2014050701','2014050702','dfds','2014-05-24 17:19:33'),(289,'2014050702','2014050701','dsfsdf','2014-05-24 17:20:29'),(290,'2014050702','2014050701','dsfsd','2014-05-24 17:23:18'),(291,'2014050702','2014050701','sdfds','2014-05-24 17:23:20'),(292,'2014050702','2014050701','sdfsd','2014-05-24 17:23:21'),(293,'2014050702','2014050701','sdfsd','2014-05-24 17:23:24'),(294,'2014050702','2014050701','fghfg','2014-05-24 17:25:57'),(295,'2014050702','2014050701','fghfg','2014-05-24 17:25:58'),(296,'2014050701','2014050702','gfhfg','2014-05-24 17:26:04'),(297,'2014050701','2014050702','fghfg','2014-05-24 17:26:05'),(298,'2014050702','2014050701','asdfsd','2014-05-24 20:18:13'),(299,'2014050702','2014050701','fsadfas','2014-05-24 20:18:22'),(300,'2014050702','2014050701','dsafs','2014-05-24 20:18:24'),(301,'2014050701','2014050702','asdfsd','2014-05-24 20:21:19'),(302,'2014050702','2014050701','sdfds','2014-05-24 20:23:01'),(303,'2014050702','2014050701','sdfsd','2014-05-24 20:23:03'),(304,'2014050702','2014050701','dsfds','2014-05-24 20:27:26'),(305,'2014050702','2014050701','sdfsd','2014-05-24 20:27:28'),(306,'2014050701','2014050702','ghg','2014-05-24 21:12:59'),(307,'2014050701','2014050702','rthyrt','2014-05-24 21:13:57'),(308,'2014050701','2014050702','rtyrt','2014-05-24 21:13:59'),(309,'2014050703','2014050701','sdfds','2014-05-24 21:14:28'),(310,'2014050703','2014050702','dsfds','2014-05-24 21:14:39'),(311,'2014050701','2014050702','ghgf','2014-05-24 21:15:14'),(312,'2014050701','2014050702','ghjgh','2014-05-24 21:15:29'),(313,'2014050703','2014050702','jj','2014-05-24 21:15:36'),(314,'2014050701','2014050702','hjkjh','2014-05-24 21:15:58'),(315,'2014050703','2014050702','hjkhj','2014-05-24 21:16:03'),(316,'2014050701','2014050702','dfgdf','2014-05-24 21:19:29'),(317,'2014050703','2014050702','dfgdf','2014-05-24 21:19:39'),(318,'2014050702','2014050703','sdfds','2014-05-24 21:21:03'),(319,'2014050702','2014050703','sdfds','2014-05-24 21:21:05'),(320,'2014050701','2014050703','sdfsd','2014-05-24 21:21:13'),(321,'2014050701','2014050703','sdfsd','2014-05-24 21:21:14'),(322,'2014050702','2014050703','dfgdf','2014-05-24 21:22:51'),(323,'2014050701','2014050703','fdgdf','2014-05-24 21:22:54'),(324,'2014050701','2014050703','dfgdf','2014-05-24 21:23:04'),(325,'2014050702','2014050703','dfgdf','2014-05-24 21:23:05'),(326,'2014050702','2014050703','dfgdf','2014-05-24 21:23:07'),(327,'2014050702','2014050703','sdfds','2014-05-24 21:54:41'),(328,'2014050702','2014050701','dsfds','2014-05-24 22:09:20'),(329,'2014050702','2014050701','sdfsd','2014-05-24 22:11:33'),(330,'2014050702','2014050701','sdfsd','2014-05-24 22:11:35'),(331,'2014050703','2014050701','sdfds','2014-05-24 22:25:02'),(332,'2014050703','2014050701','sdfsd','2014-05-24 22:25:04'),(333,'2014050702','2014050701','sdfsdasfasdasdfasd','2014-05-24 22:25:59'),(334,'2014050702','2014050701','dfgdf','2014-05-24 22:31:08'),(335,'2014050702','2014050701','dfgdf','2014-05-24 22:31:10'),(336,'2014050703','2014050701','dfgdf','2014-05-24 22:31:11'),(337,'2014050703','2014050701','dfgdf','2014-05-24 22:31:12'),(338,'2014050702','2014050703','dfgdf','2014-05-24 22:31:17'),(339,'2014050701','2014050702','dfgdf','2014-05-24 22:31:30'),(340,'2014050701','2014050702','dfgdf','2014-05-24 22:31:31'),(341,'2014050701','2014050702','dfgd','2014-05-24 22:31:32'),(342,'2014050701','2014050702','dfgdf','2014-05-24 22:31:35'),(343,'2014050703','2014050702','dfgdf','2014-05-24 22:31:45'),(344,'2014050703','2014050702','dfgdf','2014-05-24 22:31:46'),(345,'2014050702','2014050703','dfd','2014-05-24 22:32:24'),(346,'2014050702','2014050701','fff','2014-05-24 22:32:28'),(347,'2014050702','2014050701','hgjgh','2014-05-24 22:33:17'),(348,'2014050701','2014050703','sdfds','2014-05-24 22:46:35'),(349,'2014050702','2014050703','dfds','2014-05-24 22:46:40'),(350,'2014050702','2014050701','sdfsd','2014-05-24 22:52:38'),(351,'2014050702','2014050701','sdfsdfs','2014-05-24 22:52:55'),(352,'2014050702','2014050701','sdfds','2014-05-24 22:52:59'),(353,'2014050701','2014050702','sdfsd','2014-05-24 23:00:32'),(354,'2014050701','2014050702','sdfds','2014-05-24 23:00:34'),(355,'2014050703','2014050701','sdfsda','2014-05-24 23:00:41'),(356,'2014050703','2014050701','sdfas','2014-05-24 23:00:42'),(357,'2014050703','2014050702','dfgdf','2014-05-24 23:03:10'),(358,'2014050702','2014050703','ggg','2014-05-24 23:12:15'),(359,'2014050701','2014050703','hh','2014-05-24 23:12:26'),(360,'2014050703','2014050701','asdfasd','2014-05-24 23:16:10'),(361,'2014050703','2014050701','sdfas','2014-05-24 23:16:11'),(362,'2014050703','2014050702','sdaf','2014-05-24 23:16:16'),(363,'2014050703','2014050702','asdfas','2014-05-24 23:16:17'),(364,'2014050703','2014050702','sdfasd','2014-05-24 23:16:21'),(365,'2014050702','2014050703','sadfas','2014-05-24 23:16:24'),(366,'2014050702','2014050703','sadfas','2014-05-24 23:16:27'),(367,'2014050702','2014050703','asdfas','2014-05-24 23:16:31'),(368,'2014050702','2014050703','asdfas','2014-05-24 23:16:32'),(369,'2014050703','2014050702','sdfds','2014-05-24 23:19:32'),(370,'2014050703','2014050702','sdfsd','2014-05-24 23:19:38'),(371,'2014050703','2014050702','dfgdf','2014-05-24 23:19:53'),(372,'2014050703','2014050702','dfgdf','2014-05-24 23:19:57'),(373,'2014050703','2014050702','dfgdf','2014-05-24 23:20:03');
/*!40000 ALTER TABLE `HistoryMessage` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Mail`
--

DROP TABLE IF EXISTS `Mail`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Mail` (
  `mailID` int(11) NOT NULL AUTO_INCREMENT,
  `senderID` varchar(15) NOT NULL,
  `senderAddress` varchar(20) NOT NULL,
  `receiverID` varchar(15) NOT NULL,
  `receiverAddress` varchar(20) NOT NULL,
  `theme` varchar(50) NOT NULL,
  `content` varchar(5000) NOT NULL,
  `time` datetime NOT NULL,
  `status` int(2) NOT NULL DEFAULT '0',
  `receiverStatus` int(2) NOT NULL DEFAULT '0',
  `senderStatus` int(2) NOT NULL DEFAULT '0',
  PRIMARY KEY (`mailID`),
  KEY `UserInformation_Mail_senderID` (`senderID`),
  KEY `UserInformation_Mail_receiverID` (`receiverID`),
  CONSTRAINT `UserInformation_Mail_receiverID` FOREIGN KEY (`receiverID`) REFERENCES `UserInformation` (`userID`),
  CONSTRAINT `UserInformation_Mail_senderID` FOREIGN KEY (`senderID`) REFERENCES `UserInformation` (`userID`)
) ENGINE=InnoDB AUTO_INCREMENT=31 DEFAULT CHARSET=utf8 COMMENT='utf8_general_ci';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Mail`
--

LOCK TABLES `Mail` WRITE;
/*!40000 ALTER TABLE `Mail` DISABLE KEYS */;
INSERT INTO `Mail` VALUES (1,'2014050701','@im.com','2014050702','@im.com','bakset','hey, let\'s paly lol next week.','2014-05-16 12:45:25',1,0,1),(2,'2014050702','@im.com','2014050701','@im.com','java','hey, let\'s paly lol next week.','2014-05-03 11:25:25',0,0,0),(3,'2014050701','@im.com','2014050703','@im.com','c++','hey, let\'s paly lol next week.','2014-05-13 11:45:25',1,0,1),(4,'2014050702','@im.com','2014050701','@im.com','wimer','hey, let\'s paly lol next week.','2014-05-11 12:04:25',1,0,0),(5,'2014050702','@im.com','2014050701','@im.com','lol-mid','hey, let\'s paly lol next week.','2014-05-14 12:45:25',1,0,1),(6,'2014050702','@im.com','2014050703','@im.com','game-dota','hey, let\'s paly lol next week.','2014-05-10 04:45:25',1,0,0),(7,'2014050703','@im.com','2014050701','@im.com','sport','hey, let\'s paly lol next week.','2014-05-10 12:45:25',0,0,0),(8,'2014050703','@im.com','2014050702','@im.com','game','hey, let\'s paly lol next week.','2014-05-13 12:45:25',0,0,0),(9,'2014050702','@im.com','2014050701','@im.com','book','hey, let\'s paly lol next week.','2014-05-11 12:45:25',0,0,0),(10,'2014050701','@im.com','2014050702','@im.com','game','hey, let\'s paly lol next week.','2014-05-10 12:45:25',0,0,0),(12,'2014050703','@im.com','2014050702','@im.com','vn','hey, let\'s paly lol next week.','2014-05-10 12:45:25',0,0,0),(13,'2014050704','@im.com','2014050702','@im.com','hanbing','hey, let\'s paly lol next week.','2014-05-10 12:45:25',0,0,0),(14,'2014050704','@im.com','2014050702','@im.com','game','hey, let\'s paly lol next week.','2014-05-10 12:45:25',0,0,0),(15,'2014050704','@im.com','2014050702','@im.com','game','hey, let\'s paly lol next week.','2014-05-10 12:45:25',0,0,0),(16,'2014050704','@im.com','2014050702','@im.com','game','hey, let\'s paly lol next week.','2014-05-10 12:45:25',0,0,0),(17,'2014050704','@im.com','2014050702','@im.com','game','hey, let\'s paly lol next week.','2014-05-10 12:45:25',0,0,0),(18,'2014050704','@im.com','2014050702','@im.com','game','hey, let\'s paly lol next week.','2014-05-10 12:45:25',0,0,0),(19,'2014050704','@im.com','2014050702','@im.com','game','hey, let\'s paly lol next week.','2014-05-10 12:45:25',0,0,0),(20,'2014050704','@im.com','2014050702','@im.com','game','hey, let\'s paly lol next week.','2014-05-15 12:45:25',0,0,0),(21,'2014050704','@im.com','2014050702','@im.com','game','hey, let\'s paly lol next week.','2014-05-10 12:45:25',0,0,0),(22,'2014050704','@im.com','2014050702','@im.com','game','hey, let\'s paly lol next week.','2014-05-11 12:45:25',0,0,0),(23,'2014050704','@im.com','2014050702','@im.com','game','hey, let\'s paly lol next week.','2014-05-13 12:45:25',0,0,0),(24,'2014050704','@im.com','2014050702','@im.com','game','hey, let\'s paly lol next week.','2014-05-12 12:45:25',0,0,0),(25,'2014050704','@im.com','2014050702','@im.com','game','hey, let\'s paly lol next week.','2014-05-10 12:45:25',0,0,0),(26,'2014050704','@im.com','2014050702','@im.com','game','hey, let\'s paly lol next week.','2014-05-11 12:45:25',0,0,0),(27,'2014050704','@im.com','2014050702','@im.com','game','hey, let\'s paly lol next week.','2014-05-10 12:45:25',0,0,0),(28,'2014050703','@im.com','2014050701','@im.com','game','hey, let\'s paly lol next week.','2014-05-10 12:45:25',0,0,0),(29,'2014050703','@im.com','2014050704','@im.com','game','hey, let\'s paly lol next week.','2014-05-10 12:45:25',1,0,0),(30,'2014050703','@im.com','2014050704','@im.com','game','qwerrtyuhjjd','2014-05-10 12:45:25',1,0,0);
/*!40000 ALTER TABLE `Mail` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `OfflineMessage`
--

DROP TABLE IF EXISTS `OfflineMessage`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `OfflineMessage` (
  `messageID` int(11) NOT NULL AUTO_INCREMENT,
  `kind` int(11) NOT NULL,
  `senderID` varchar(15) NOT NULL,
  `receiverID` varchar(15) NOT NULL,
  `content` varchar(1000) NOT NULL DEFAULT '',
  PRIMARY KEY (`messageID`),
  KEY `UserInformation_OfflineMessage_senderID` (`senderID`),
  KEY `UserInformation_OfflineMessage_receiverID` (`receiverID`),
  CONSTRAINT `UserInformation_OfflineMessage_receiverID` FOREIGN KEY (`receiverID`) REFERENCES `UserInformation` (`userID`),
  CONSTRAINT `UserInformation_OfflineMessage_senderID` FOREIGN KEY (`senderID`) REFERENCES `UserInformation` (`userID`)
) ENGINE=InnoDB AUTO_INCREMENT=99 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `OfflineMessage`
--

LOCK TABLES `OfflineMessage` WRITE;
/*!40000 ALTER TABLE `OfflineMessage` DISABLE KEYS */;
INSERT INTO `OfflineMessage` VALUES (90,81,'2014050701','2014050702','<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\np, li { white-space: pre-wrap; }\n</style></head><body style=\" font-family:\'Ubuntu\'; font-size:11pt; font-weight:400; font-style:normal;\">\n<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">csdsdfsdsdfsd</p></body></html>'),(91,81,'2014050701','2014050702','<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\np, li { white-space: pre-wrap; }\n</style></head><body style=\" font-family:\'Ubuntu\'; font-size:11pt; font-weight:400; font-style:normal;\">\n<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">sdfsdfsd</p></body></html>'),(92,81,'2014050701','2014050702','<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\np, li { white-space: pre-wrap; }\n</style></head><body style=\" font-family:\'Ubuntu\'; font-size:11pt; font-weight:400; font-style:normal;\">\n<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">asdfsda</p></body></html>'),(93,81,'2014050701','2014050702','<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\np, li { white-space: pre-wrap; }\n</style></head><body style=\" font-family:\'Ubuntu\'; font-size:11pt; font-weight:400; font-style:normal;\">\n<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">asdfsd</p></body></html>'),(94,81,'2014050701','2014050702','<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\np, li { white-space: pre-wrap; }\n</style></head><body style=\" font-family:\'Ubuntu\'; font-size:11pt; font-weight:400; font-style:normal;\">\n<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">sdafsad</p></body></html>'),(95,81,'2014050701','2014050702','<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\np, li { white-space: pre-wrap; }\n</style></head><body style=\" font-family:\'Ubuntu\'; font-size:11pt; font-weight:400; font-style:normal;\">\n<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">sdfsda</p></body></html>'),(96,81,'2014050701','2014050702','<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\np, li { white-space: pre-wrap; }\n</style></head><body style=\" font-family:\'Ubuntu\'; font-size:11pt; font-weight:400; font-style:normal;\">\n<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">dsfgds</p></body></html>'),(97,81,'2014050703','2014050701','<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\np, li { white-space: pre-wrap; }\n</style></head><body style=\" font-family:\'Ubuntu\'; font-size:11pt; font-weight:400; font-style:normal;\">\n<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">asdfasd</p></body></html>'),(98,81,'2014050703','2014050701','<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\np, li { white-space: pre-wrap; }\n</style></head><body style=\" font-family:\'Ubuntu\'; font-size:11pt; font-weight:400; font-style:normal;\">\n<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">sdfas</p></body></html>');
/*!40000 ALTER TABLE `OfflineMessage` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `UserDiscussions`
--

DROP TABLE IF EXISTS `UserDiscussions`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `UserDiscussions` (
  `userDiscussionNum` int(11) NOT NULL AUTO_INCREMENT,
  `discussionID` varchar(15) NOT NULL,
  `userID` varchar(15) NOT NULL,
  `status` int(3) NOT NULL,
  `joinDate` datetime NOT NULL,
  PRIMARY KEY (`userDiscussionNum`),
  KEY `DiscussionInformation_UserDiscussions_discussionID` (`discussionID`),
  KEY `UserInformation_UserDiscussions_userID` (`userID`),
  CONSTRAINT `DiscussionInformation_UserDiscussions_discussionID` FOREIGN KEY (`discussionID`) REFERENCES `DiscussionInformation` (`discussionID`) ON DELETE CASCADE,
  CONSTRAINT `UserInformation_UserDiscussions_userID` FOREIGN KEY (`userID`) REFERENCES `UserInformation` (`userID`) ON DELETE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=146 DEFAULT CHARSET=utf8 COMMENT='utf8_general_ci';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `UserDiscussions`
--

LOCK TABLES `UserDiscussions` WRITE;
/*!40000 ALTER TABLE `UserDiscussions` DISABLE KEYS */;
INSERT INTO `UserDiscussions` VALUES (130,'2014051121','2014050702',0,'2014-05-11 18:49:57'),(132,'2014051123','2014050703',0,'2014-05-11 18:50:06'),(137,'2014051121','2014050703',1,'2014-05-11 18:52:01'),(139,'2014051121','2014050701',1,'2014-05-13 16:47:24'),(140,'2014051721','2014051701',0,'2014-05-17 21:32:37'),(141,'2014051721','2014050702',1,'2014-05-17 21:32:53'),(142,'2014051821','2014051701',0,'2014-05-18 21:03:58'),(143,'2014051821','2014050701',1,'2014-05-18 21:04:06'),(144,'2014051821','2014050704',1,'2014-05-18 21:04:15'),(145,'2014051721','2014050704',1,'2014-05-18 21:04:36');
/*!40000 ALTER TABLE `UserDiscussions` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `UserFlocks`
--

DROP TABLE IF EXISTS `UserFlocks`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `UserFlocks` (
  `userFlockNum` int(11) NOT NULL AUTO_INCREMENT,
  `flockID` varchar(15) NOT NULL,
  `userID` varchar(15) NOT NULL,
  `remark` varchar(20) DEFAULT NULL,
  `status` int(3) NOT NULL,
  `joinDate` datetime NOT NULL,
  PRIMARY KEY (`userFlockNum`),
  KEY `FlockInformation_UserFlocks_flockID` (`flockID`),
  KEY `UserInformation_UserFlocks_userID` (`userID`),
  CONSTRAINT `FlockInformation_UserFlocks_flockID` FOREIGN KEY (`flockID`) REFERENCES `FlockInformation` (`flockID`) ON DELETE CASCADE,
  CONSTRAINT `UserInformation_UserFlocks_userID` FOREIGN KEY (`userID`) REFERENCES `UserInformation` (`userID`) ON DELETE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=140 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `UserFlocks`
--

LOCK TABLES `UserFlocks` WRITE;
/*!40000 ALTER TABLE `UserFlocks` DISABLE KEYS */;
INSERT INTO `UserFlocks` VALUES (125,'2014051111','2014050702',NULL,0,'2014-05-11 18:43:47'),(126,'2014051111','2014050701',NULL,2,'2014-05-11 18:44:15'),(127,'2014051311','2014050701','ghghg',0,'2014-05-13 14:32:41'),(128,'2014051311','2014050702',NULL,2,'2014-05-13 14:55:21'),(129,'2014051711','2014051701',NULL,0,'2014-05-17 21:32:11'),(130,'2014051711','2014050702',NULL,2,'2014-05-17 21:32:21'),(131,'2014051711','2014050704',NULL,2,'2014-05-18 21:02:44'),(132,'2014051811','2014050704',NULL,0,'2014-05-18 21:03:00'),(133,'2014051811','2014051701',NULL,2,'2014-05-18 21:03:36'),(134,'2014051812','2014051701',NULL,0,'2014-05-18 21:45:01'),(135,'2014051813','2014050701',NULL,0,'2014-05-18 21:45:06'),(136,'2014052411','2014050703',NULL,0,'2014-05-24 11:17:28'),(137,'2014052412','2014050702','dfgfd',0,'2014-05-24 21:54:59'),(138,'2014052412','2014050703','gfhgf',2,'2014-05-24 21:55:12'),(139,'2014052412','2014050701',NULL,2,'2014-05-24 22:25:34');
/*!40000 ALTER TABLE `UserFlocks` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `UserFriends`
--

DROP TABLE IF EXISTS `UserFriends`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `UserFriends` (
  `friendNum` int(11) NOT NULL AUTO_INCREMENT,
  `userID` varchar(15) NOT NULL,
  `friendID` varchar(15) NOT NULL,
  `groupName` varchar(50) NOT NULL,
  `remarkName` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`friendNum`),
  KEY `UserInformation_UserFriends_user` (`userID`),
  KEY `UserInformation_UserFriends_friend` (`friendID`),
  CONSTRAINT `UserInformation_UserFriends_friend` FOREIGN KEY (`friendID`) REFERENCES `UserInformation` (`userID`),
  CONSTRAINT `UserInformation_UserFriends_user` FOREIGN KEY (`userID`) REFERENCES `UserInformation` (`userID`)
) ENGINE=InnoDB AUTO_INCREMENT=165 DEFAULT CHARSET=utf8 COMMENT='utf8_general_ci';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `UserFriends`
--

LOCK TABLES `UserFriends` WRITE;
/*!40000 ALTER TABLE `UserFriends` DISABLE KEYS */;
INSERT INTO `UserFriends` VALUES (137,'2014050703','2014050702','rtyrt',NULL),(138,'2014050702','2014050703','new group',NULL),(147,'2014050703','2014050701','rtyrt',NULL),(148,'2014050701','2014050703','核心项目组',NULL),(149,'2014050701','2014050704','家人',NULL),(150,'2014050704','2014050701','New Friends',NULL),(153,'2014050704','2014050702','New Friends',NULL),(154,'2014050702','2014050704','new group',NULL),(155,'2014050703','2014051701','rtyrt','qq'),(156,'2014051701','2014050703','New Friends',NULL),(157,'2014051701','2014050702','new group',NULL),(158,'2014050702','2014051701','new group',NULL),(159,'2014050701','2014051701','朋友',NULL),(160,'2014051701','2014050701','jkljk','ijjj'),(161,'2014050704','2014051701','New Friends',NULL),(162,'2014051701','2014050704','New Friends',NULL),(163,'2014050701','2014050702','家人',NULL),(164,'2014050702','2014050701','new group',NULL);
/*!40000 ALTER TABLE `UserFriends` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `UserGroup`
--

DROP TABLE IF EXISTS `UserGroup`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `UserGroup` (
  `groupNum` int(11) NOT NULL AUTO_INCREMENT,
  `userID` varchar(15) NOT NULL,
  `groupName` varchar(20) NOT NULL,
  PRIMARY KEY (`groupNum`),
  KEY `UserInformation_UserGroup` (`userID`),
  CONSTRAINT `UserInformation_UserGroup` FOREIGN KEY (`userID`) REFERENCES `UserInformation` (`userID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `UserGroup`
--

LOCK TABLES `UserGroup` WRITE;
/*!40000 ALTER TABLE `UserGroup` DISABLE KEYS */;
/*!40000 ALTER TABLE `UserGroup` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `UserInformation`
--

DROP TABLE IF EXISTS `UserInformation`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `UserInformation` (
  `userID` varchar(15) NOT NULL,
  `head` int(11) NOT NULL DEFAULT '1',
  `nickname` varchar(20) NOT NULL,
  `password` varchar(10) NOT NULL,
  `sex` varchar(2) NOT NULL,
  `birthday` date NOT NULL,
  `question` varchar(50) NOT NULL,
  `answer` varchar(50) NOT NULL,
  `name` varchar(50) DEFAULT NULL,
  `phone` varchar(12) DEFAULT NULL,
  `address` varchar(50) DEFAULT NULL,
  `regDate` datetime NOT NULL,
  `status` int(3) NOT NULL DEFAULT '5',
  PRIMARY KEY (`userID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='utf8_general_ci';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `UserInformation`
--

LOCK TABLES `UserInformation` WRITE;
/*!40000 ALTER TABLE `UserInformation` DISABLE KEYS */;
INSERT INTO `UserInformation` VALUES ('2014050701',66,'雨舒意',';89>?<','男','2014-05-15','1','2','付行知','18767122710','zjut-西十三','2014-05-07 23:11:28',5),('2014050702',1,'云敛容',';89>?<','男','2014-05-15','1','2','2','2','2','2014-05-07 23:11:42',5),('2014050703',49,'apple',';89>?<','男','2012-03-02','1','2','流','1305674','dashfk-zjut','2014-05-07 23:11:48',5),('2014050704',20,'mick',';89>?<','女','1995-06-15','dfg','hg','fhd','123','ghjkh','2014-05-07 23:12:48',5),('2014051701',43,'haafgf',';89>?<','女','2014-05-18','11','11','11','11','11','2014-05-17 21:29:43',5);
/*!40000 ALTER TABLE `UserInformation` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2014-05-26 10:21:55
