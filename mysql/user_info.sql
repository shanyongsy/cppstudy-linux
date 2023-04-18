/*
 Navicat MySQL Data Transfer

 Source Server         : 10.41.4.108
 Source Server Type    : MySQL
 Source Server Version : 80023
 Source Host           : 10.41.4.108:3306
 Source Schema         : fs_fee

 Target Server Type    : MySQL
 Target Server Version : 80023
 File Encoding         : 65001

 Date: 28/01/2023 17:45:32
*/

SET NAMES gbk;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for user_info
-- ----------------------------
DROP TABLE IF EXISTS `user_info`;
CREATE TABLE `user_info`  (
  `id` bigint(0) NOT NULL AUTO_INCREMENT,
  `name` varchar(50) CHARACTER SET gbk COLLATE gbk_bin NOT NULL DEFAULT '',
  `account` varchar(50) CHARACTER SET gbk COLLATE gbk_bin NOT NULL DEFAULT '',
  `info` blob NOT NULL,
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `uq_name`(`name`) USING BTREE,
  INDEX `idx_account`(`account`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 1 CHARACTER SET = gbk COLLATE = gbk_bin ROW_FORMAT = Dynamic;

SET FOREIGN_KEY_CHECKS = 1;
