

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for administrator
-- ----------------------------
DROP TABLE IF EXISTS `administrator`;
CREATE TABLE `administrator`  (
  `admin_username` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `admin_password` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `admin_name` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `admin_sex` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `admin_tel` char(11) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  PRIMARY KEY (`admin_username`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Compact;

-- ----------------------------
-- Records of administrator
-- ----------------------------
INSERT INTO `administrator` VALUES ('admin', 'admin', 'admin', '男', '119');

-- ----------------------------
-- Table structure for musicdb
-- ----------------------------
DROP TABLE IF EXISTS `musicdb`;
CREATE TABLE `musicdb`  (
  `music_id` varchar(63) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `music_name` varchar(63) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
	`music_singer` varchar(63) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
	`music_lyricist` varchar(63) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
	`music_composer` varchar(63) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
	`record` varchar(63) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `record_company` varchar(63) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `music_category` varchar(63) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `filename` varchar(63) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL,
  `path` varchar(63) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL,
  `music_description` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `music_price` double(10, 0) NOT NULL,
  `music_inventory` int(11) NOT NULL,
  `music_heat` int(11) NOT NULL,
  PRIMARY KEY (`music_id`) USING BTREE,
  INDEX `musicdb_ibfk_1`(`music_category`) USING BTREE,
  CONSTRAINT `musicdb_ibfk_1` FOREIGN KEY (`music_category`) REFERENCES `category` (`category_id`) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Compact;

-- ----------------------------
-- Records of musicdb
-- ----------------------------
INSERT INTO `musicdb` VALUES ('2c086867-bcac-4d8a-b060-dc74ed5b3f3b', '海阔天空', 'Beyond', '黄家驹', '黄家驹', '乐与怒', '华纳', '摇滚', 'csapp.jpg', 'music', '1993', 100, 4, 1);

-- ----------------------------
-- Table structure for category
-- ----------------------------
DROP TABLE IF EXISTS `category`;
CREATE TABLE `category`  (
  `category_id` varchar(63) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `category_name` varchar(63) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `category_description` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  PRIMARY KEY (`category_id`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Compact;

-- ----------------------------
-- Records of category
-- ----------------------------
INSERT INTO `category` VALUES ('143c60c6-e608-46cc-b846-620d0404f958', '摇滚', 'rock and roll');

-- ----------------------------
-- Table structure for favorite
-- ----------------------------
DROP TABLE IF EXISTS `favorite`;
CREATE TABLE `favorite`  (
  `favorite_id` varchar(63) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `user_id` varchar(63) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL,
  `music_id` varchar(63) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL,
  PRIMARY KEY (`favorite_id`) USING BTREE,
  INDEX `user_id`(`user_id`) USING BTREE,
  INDEX `music_id`(`music_id`) USING BTREE,
  CONSTRAINT `favorite_ibfk_1` FOREIGN KEY (`user_id`) REFERENCES `user` (`user_id`) ON DELETE RESTRICT ON UPDATE RESTRICT,
  CONSTRAINT `favorite_ibfk_2` FOREIGN KEY (`music_id`) REFERENCES `musicdb` (`music_id`) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Compact;

-- ----------------------------
-- Records of favorite
-- ----------------------------
-- INSERT INTO `favorite` VALUES ('fab61d2d-b8f2-4d1d-89d1-8979844a2740', 'd4d4e886-a1a9-450c-a227-63cf663cd341', '2c086867-bcac-4d8a-b060-dc74ed5b3f3b');

-- ----------------------------
-- Table structure for orderitems
-- ----------------------------
DROP TABLE IF EXISTS `orderitems`;
CREATE TABLE `orderitems`  (
  `orderitem_id` varchar(63) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `quantity` int(11) DEFAULT NULL,
  `price` double DEFAULT NULL,
  `music_id` varchar(63) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL,
  `order_id` varchar(63) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL,
  PRIMARY KEY (`orderitem_id`) USING BTREE,
  INDEX `music_id_fk`(`music_id`) USING BTREE,
  INDEX `order_id_fk`(`order_id`) USING BTREE,
  CONSTRAINT `music_id_fk` FOREIGN KEY (`music_id`) REFERENCES `musicdb` (`music_id`) ON DELETE RESTRICT ON UPDATE RESTRICT,
  CONSTRAINT `order_id_fk` FOREIGN KEY (`order_id`) REFERENCES `orders` (`order_id`) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Compact;

-- ----------------------------
-- Records of orderitems
-- ----------------------------
-- INSERT INTO `orderitems` VALUES ('202105095520400219828300', 2, 200, '2c086867-bcac-4d8a-b060-dc74ed5b3f3b', '202105095520400219357300');

-- ----------------------------
-- Table structure for orders
-- ----------------------------
DROP TABLE IF EXISTS `orders`;
CREATE TABLE `orders`  (
  `order_id` varchar(63) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `quantity` int(11) DEFAULT NULL,
  `money` double DEFAULT NULL,
  `time` varchar(100) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL,
  `status` int(11) DEFAULT NULL,
  `user_id` varchar(63) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL,
  PRIMARY KEY (`order_id`) USING BTREE,
  INDEX `user_Id_fk`(`user_id`) USING BTREE,
  CONSTRAINT `user_Id_fk` FOREIGN KEY (`user_id`) REFERENCES `user` (`user_id`) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Compact;

-- ----------------------------
-- Records of orders
-- ----------------------------
-- INSERT INTO `orders` VALUES ('202105095520400219357300', 2, 200, '2021-05-09 16:55:15', 0, 'd4d4e886-a1a9-450c-a227-63cf663cd341');

-- ----------------------------
-- Table structure for user
-- ----------------------------
DROP TABLE IF EXISTS `user`;
CREATE TABLE `user`  (
  `user_id` varchar(63) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `user_username` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `user_password` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `user_name` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `user_sex` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL,
  `user_tel` char(11) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL,
  `user_address` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL,
  PRIMARY KEY (`user_id`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Compact;

-- ----------------------------
-- Records of user
-- ----------------------------
-- INSERT INTO `user` VALUES ('d4d4e886-a1a9-450c-a227-63cf663cd341', 'HaC', '123', 'C哥', NULL, '', '');

SET FOREIGN_KEY_CHECKS = 1;
