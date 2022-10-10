# MieGame_C_Core
## 简介
这是一个以C++实现的MieGame对象，可以实现放牌，拿牌等操作。
很简单，注释也写的很明确
/*********************
 * 羊了个羊 游戏设计 mie.cpp
 *      1.有 n 种牌 
 *      2.每 z 张相同的牌可以被抵消
 *      3.共有 N = kz (k属于正整数) 张牌
 *      4.选中格有 F 格，满了即被消除
 *      5.牌被分为 亮牌（可选） 暗牌（不可选）
 *      6.每张牌都有唯一编号 1 - N 
 *      7.从1号牌开始放牌，大号周围 x 距离内，小号牌为暗牌 牌的大小为 2x
 *      8.所有牌都被消除即为游戏胜利
 *      9.牌的存储形式为 ( x,y,t,a ) [位置与类型与亮暗]
 *      10.没有被消除的牌被标记为1，被消除的牌被标记为0，以bitmap的形式存储
 * 
**********************/
