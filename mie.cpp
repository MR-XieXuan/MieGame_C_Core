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
 *      9.牌的存储形式为 ( x,y,t,a ) [位置与类型与亮暗] t != 0 
 *      10.没有被消除的牌被标记为1，被消除的牌被标记为0，以bitmap的形式存储
 * 
**********************/

#include <stdio.h>
#include "mie.h"
#include "graphics.h"

void put_poker(int x , int y , int type);

int main(){
    MieGame game;
    initgraph(640, 480);
    // 添加卡牌
    game.place_a_poker(20,20,0);
    game.place_a_poker(20,25,0);
    game.place_a_poker(50,20,0);
    game.place_a_poker(50,25,0);
    game.place_a_poker(80,20,0);
    game.place_a_poker(80,25,0);
    game.place_a_poker(20,50,0);
    game.place_a_poker(20,55,0);
    game.place_a_poker(50,50,0);
    game.place_a_poker(50,55,0);
    game.place_a_poker(80,50,0);
    game.place_a_poker(80,55,0);
    game.place_a_poker(20,80,0);
    game.place_a_poker(20,85,0);
    game.place_a_poker(50,80,0);
    game.place_a_poker(50,85,0);
    game.place_a_poker(80,80,0);
    game.place_a_poker(80,85,0);
    game.refresh_poker_a();
    // 绘制卡片
    for( int i = 1 ; i <= 18 ; i++ ){
        put_poker(game.get_poker_x(i),game.get_poker_y(i),0);
        printf("(%d,%d)",game.get_poker_x(i),game.get_poker_y(i));
        //circle(game.get_poker_x(i),game.get_poker_y(i),5);
    }
    while(1);
}

void put_poker(int x , int y , int type){
    uint8_t bom = 4;
    color_t color = EGERGB(255,255,255);
	setfillcolor(color);
	bar((x-5)*bom,(y+5)*bom,(x+5)*bom,(y-5)*bom);
	setfillcolor(GREEN);
	rectangle((x-5)*bom,(y+5)*bom,(x+5)*bom,(y-5)*bom);
}

void getaway_poker(int x, int y){
	
}
