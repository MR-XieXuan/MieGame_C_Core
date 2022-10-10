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
#ifndef _MIE_H_
#define _MIE_H_

#include <stdio.h>

#define POKERTYPE_AMOUNT     6
#define POKER_REMOVE_NUM     3
#define POKER_SIZE           10
#define MIEGAME_POKERAMOUNT_MAX 504    

typedef unsigned char uint8_t ;

class MieGame {
    public :
        // 放置一张牌
        uint8_t place_a_poker(int x, int y, uint8_t type);
        // 拿走一张牌
        uint8_t takeaway_a_poker(int number);   // 通过编号拿走
        uint8_t takeaway_a_poker(int x, int y); // 通过位置拿走
        // 更新亮暗状态 
        void refresh_poker_a();
        // 获取亮暗状态 
        uint8_t get_poker_a(int n);
        uint8_t get_poker_x(int n);
        uint8_t get_poker_y(int n);
        uint8_t get_poker_t(int n);

    private:
        int amount = 0; // 牌的总数
        uint8_t pokerBitmap[63] = {0}; // 最多容纳 504 张牌
        int pokerPosition[504][4] = {0}; // [牌号][位置x，位置y，类型t,亮暗a]
        char Get_bit( uint8_t * st , char num ){
            return ( st[(int)(num/8)] & (0x01 << (num % 8) ) ) > 0 ? 1 : 0 ;
        }
        void Set_bit( uint8_t * st , char num ){
            st[(int)(num/8)] |= (0x01 << (num % 8) ) ;
        }
        void Res_bit( uint8_t * st , char num ){
            st[(int)(num/8)] &= ~(0x01 << (num % 8) ) ;
        }

};

uint8_t MieGame :: place_a_poker(int x, int y, uint8_t type){
    // 放置一张牌
    //判断是否可以放的下了
    if( amount + 1 <= MIEGAME_POKERAMOUNT_MAX ){
        // 放的下
        //printf("总数加1\n");
        amount ++ ; // 总数加1
        //printf("Srtbit\n");
        Set_bit(pokerBitmap,amount-1);
        pokerPosition[amount-1][0] = x ;
        pokerPosition[amount-1][1] = y ;
        pokerPosition[amount-1][2] = type ;
        pokerPosition[amount-1][3] = 1 ;
        // 更新其他牌的亮暗状态
        //printf("刷新牌堆\n");
        //refresh_poker_a();
        //printf("返回牌数\n");
        return amount ; 
    } else {
        // 放不下
        return 0 ;
    }

}

uint8_t MieGame :: takeaway_a_poker(int x, int y){
    // 通过位置拿走一张牌
    for( int i = amount-1 ; i >= 0 ; i--  ){
        // 遍历牌堆
        if( Get_bit(pokerBitmap,i) ){
            // 如果这张牌没有被拿走 继续执行
        } else { 
            /* 这张牌已经被拿走了 */ 
            continue;
        }
        if( pokerPosition[i][0] >= x - POKER_SIZE/2 && pokerPosition[i][0] <= x + POKER_SIZE/2   ){
            // 检查x是否达标 
        } else { 
            /* x 未达标 */
            continue; 
        } 
        if( pokerPosition[i][1] >= y - POKER_SIZE/2 && pokerPosition[i][1] <= y + POKER_SIZE/2 ){
            // 检查y是否达标 继续执行
        } else { 
            /* y 未达标 */ 
            continue;
        }
        if( pokerPosition[i][3] == 1 ){
            // 检查这张牌是不是亮牌
        } else { 
            /* 这张牌是暗牌 */ 
            continue;
        }
        // 移除这张牌，并返回牌的类型
        Res_bit(pokerBitmap, i);
        return pokerPosition[i][2];
    }
}

void MieGame :: refresh_poker_a(){
    for( int i = amount - 1 ; i >= 0 ; i-- ){
        // 从大遍历所有牌
        //printf("遍历牌 i : %d \n", i);
        if( Get_bit(pokerBitmap, i) ){
            // 检查这张牌是否已经被拿走
            // 没有被拿走则继续执行
            //printf("没有被拿走 %d \n", i);
        } else { continue; }
        for ( int j = i - 1 ; j >= 0 ; j-- ){
            // 检查底下的牌是否有被这张牌压住的，被压住的标记为黑牌
            //printf("检查牌 j : %d \n", j);
            if( pokerPosition[i][0] + POKER_SIZE > pokerPosition[j][0] && pokerPosition[i][0] - POKER_SIZE < pokerPosition[j][0] ){
                // 检查 x 方向是否被压
                // x 方向被压 
                pokerPosition[j][3] = 0 ; 
                continue;
            } else {
                // x 方向没有被压 
                //printf("没有被压 x \n");
            }
            if( pokerPosition[i][1] + POKER_SIZE > pokerPosition[j][1] && pokerPosition[i][1] - POKER_SIZE < pokerPosition[j][1] ){
                // 检查 y 方向是否被压
                // y 方向被压
                pokerPosition[j][3] = 0 ; 
                continue;
            } else {
                // y 方向没有被压 
                //printf("没有被压 y \n");
                
            }
        }
    }
}

uint8_t MieGame :: get_poker_a(int n){
    return pokerPosition[n-1][3] ;
}

uint8_t MieGame :: get_poker_x(int n){
    return pokerPosition[n-1][0] ;
}

uint8_t MieGame :: get_poker_y(int n){
    return pokerPosition[n-1][1] ;
}

uint8_t MieGame :: get_poker_t(int n){
    return pokerPosition[n-1][2] ;
}

#endif
