/* 全局函数定义文件 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "global.h"

/* 文件内部局部函数声明 */

static const struct blockShape *block_hashmap(const char);
/*-----------------------------------------------------------------
输入值：当前方块（char值）
目标：查找该方块并返回该包含方块形状结构的指针
返回值：对应方块形状结构指针
-----------------------------------------------------------------*/

static bool wallkick(char (*memfield)[12], const char block, const char direction, const char rotateto);
/*-----------------------------------------------------------------
输入值：当前场地（数组指针），当前方块，方块朝向（前），旋转方向
目标：检测四次踢墙，成功则更改场地，返回false，四次都失败则返回true
返回值：一个bool值（作为if条件，true则进行说明踢墙失败，continue主循环，false则说明踢墙成功，继续消行检测）
-------------------------------------------------------------------*/

/* 局部函数定义 */

const struct blockShape *block_hashmap(const char block)
{
    switch (block){
        case 'S': return &blockS;
        case 'Z': return &blockZ;
        case 'J': return &blockJ;
        case 'L': return &blockL;
        case 'T': return &blockT;
        case 'I': return &blockI;
        case 'O': return &blockO;
    }
}


bool wallkick(char (*memfield)[12], const char block, const char direction, char rotateto)
{
    unsigned char memDirection = (direction + rotateto) % 4;
    switch (rotateto)
    {
        case -1:
            rotateto = 0;
            break;
        case 1:
            rotateto = 1;
            break;
    }
    const char (*wallKickDict)[2][4][2];
    if (block == 'I')
        wallKickDict = wallKickData;
    else
        wallKickDict = wallKickDataI;
    for (unsigned char wallKickCount = 0; wallKickCount < 4; wallKickCount++)
    {
        bool isSuccess = true;
        for (unsigned char i = 0; i < 4; i++)
        {
            unsigned char delta_x = block_hashmap(block)->blockshape[memDirection][i][0]
                                    + wallKickDict[direction][rotateto][wallKickCount][0];
            unsigned char delta_y = block_hashmap(block)->blockshape[memDirection][i][1]
                                    + wallKickDict[direction][rotateto][wallKickCount][1];
            if (memfield[previewBlock.location[0] + delta_x][previewBlock.location[1] + delta_y])
            {
                isSuccess = false;
                break;
            }
        }
        if (isSuccess)
        {
            previewBlock.location[0] += wallKickDict[direction][rotateto][wallKickCount][0];
            previewBlock.location[1] += wallKickDict[direction][rotateto][wallKickCount][1];
            for (unsigned char i = 0; i < 4; i++)
            {
                memfield[previewBlock.location[0]+block_hashmap(block)->blockshape[memDirection][i][0]]
                        [previewBlock.location[1]+block_hashmap(block)->blockshape[memDirection][i][1]] += 1;
            }
            return false;
        }
    }
    return true;
}

/* 全局函数定义 */

void bagseven(char *previewBag)         //已知bug：第一块必为Z
{
    srand((unsigned int)time(NULL));                                    //时间作为随机种子
    char bag[7] = {'Z', 'S', 'L', 'J', 'T', 'I', 'O'};                  //初始化临时包
    for (unsigned char random, i = 0; i < 7; random = rand() % 7)       //随机项数i
    {
        if (bag[random])                                                //检测临时包的i项是否为0
        {
            *(previewBag + i) = bag[random];                            //给包第i项赋值
            bag[random] = 0;                                            //将临时包第i项设为0
            ++i;
        }
    }
}


void printfield(char (*field)[12])
{
    system("cls");
    for (unsigned char x = 0; x < 22; x++)
        for (unsigned char y = 0; y < 12; y++)
        {
            if (x == 21)
            {
                printf("--");
                continue;
            }
            if (y == 0 || y == 11)
            {
                printf("|");
                if (y == 11)
                    printf("\n");
                continue;
            }
            if (field[x][y] == 1)
                printf("[]");
            else
                printf("  ");
        }
}


bool spawn(char (*field)[12], const char block)
{
    for (char i = 0; i < 4; i++)                                    //备注：该函数无需使用缓存场地检测
    {
        unsigned char delta_x = block_hashmap(block)->blockshape[0][i][0];  //方块距离中心偏移X距离
        unsigned char delta_y = block_hashmap(block)->blockshape[0][i][1];  //方块距离中心偏移Y距离
        if((field[3 + delta_x][7 + delta_y] += 1) > 1)                      //判断是否成功生成方块
            return false;                                                   //生成失败则返回false
    }
    printfield(field);                                                      //打印场地
    return true;                                                            //成功生成则返回true
}


bool movement(char (*field)[12], const char block, const char direction)
{
    unsigned char moveto;                                           //移动方向
    switch (direction)                                              //检测并赋值移动方向
    {
        case 'a': moveto = 1; break;
        case 'd': moveto = 2; break;
        case 's': moveto = 3; break;
        default: return false;                                      //不匹配则返回false，进行后续（旋转）操作检测
    }
    char (*memfield)[12] = (char(*)[12]) malloc(sizeof(field));     //为缓存场地分配内存
    memcpy(memfield, field, sizeof(field));                         //拷贝场地至缓存场地
    for (char i = 0; i < 4; i++)                                    //在缓存场地中去除原来方块
    {
        unsigned char delta_x = block_hashmap(block)->blockshape[previewBlock.direction][i][0]; //方块距离中心偏移X距离
        unsigned char delta_y = block_hashmap(block)->blockshape[previewBlock.direction][i][1]; //方块距离中心偏移Y距离
        memfield[previewBlock.location[0] + delta_x][previewBlock.location[1] + delta_y] -= 1;  //去除原来方块
    }
    for (char i = 0; i < 4; i++)                                    //在缓存场地中移动方块并测试是否成功
    {
        unsigned char delta_x = block_hashmap(block)->blockshape[previewBlock.direction][i][0]; //方块距离中心偏移X距离
        unsigned char delta_y = block_hashmap(block)->blockshape[previewBlock.direction][i][1]; //方块距离中心偏移Y距离
        if((memfield[previewBlock.location[0] + delta_x + blockMovement[moveto][0]]             //增加移动后方块
                    [previewBlock.location[1] + delta_y + blockMovement[moveto][1]] += 1) > 1)  //判断移动是否成功
        {
            free(memfield);
            if (moveto == 3)                                        //判断是否触底
                return true;                                        //触底则返回true并退出函数
            return false;                                           //撞墙则退出false函数
        }
    }
    memcpy(field, memfield, sizeof(field));                         //拷贝缓存场地至场地
    previewBlock.location[0] += blockMovement[moveto][0];           //记录新的方块坐标
    previewBlock.location[1] += blockMovement[moveto][1];
    free(memfield);
    printfield(field);
    return false;                                                   //成功移动，返回false
}


bool rotation(char (*field)[12], const char block, const char direction)
{
    if (block == 'O')
        return true;                                                //不处理O方块，返回true（O：我不要面子的吗）
    char rotateto;                                                  //旋转方向
    switch (direction)                                              //检测并赋值旋转方向
    {
        case 'q': rotateto = -1; break;
        case 'e': rotateto = 1; break;
        default: return true;                                       //不匹配则返回true，进行后续（下一轮循环）检测
    }
    char memDirection = (previewBlock.direction + rotateto) % 4;
    char (*memfield)[12] = (char(*)[12]) malloc(sizeof(field));     //为缓存场地分配内存
    memcpy(memfield, field, sizeof(field));                         //拷贝场地至缓存场地
    for (char i = 0; i < 4; i++)                                    //在缓存场地中去除原来方块
    {
        unsigned char delta_x = block_hashmap(block)->blockshape[previewBlock.direction][i][0]; //方块距离中心偏移X距离
        unsigned char delta_y = block_hashmap(block)->blockshape[previewBlock.direction][i][1]; //方块距离中心偏移Y距离
        memfield[previewBlock.location[0] + delta_x][previewBlock.location[1] + delta_y] -= 1;  //去除原来方块
    }
    for (int i = 0; i < 4; i++)                                     //在缓存场地中旋转方块并测试是否成功
    {
        unsigned char delta_x = block_hashmap(block)->blockshape[memDirection][i][0];           //方块距离中心偏移X距离
        unsigned char delta_y = block_hashmap(block)->blockshape[memDirection][i][1];           //方块距离中心偏移Y距离
        if (memfield[previewBlock.location[0] + delta_x][previewBlock.location[1] + delta_y])
        {
            if (wallkick(memfield, block, previewBlock.direction, rotateto))
            {
                free(memfield);
                return true;
            }
            break;
        }
    }
    previewBlock.direction = memDirection;
    memcpy(field, memfield, sizeof(field));                     //拷贝缓存场地至场地
    free(memfield);
    printfield(field);
    return false;
}


bool clear(char (*field)[12], int *score)
{
    for (unsigned char x = 0; x < 21; x++)
    {
        char lineSum = 0;
        for (unsigned char y = 0; y < 11; y++)
        {
            lineSum += field[x][y];
        }
        if (lineSum == 10)
        {
            for (unsigned char y1 = 0; y1 < 11; y1++)
                field[x][y1] -= 1;
            for (unsigned char x2 = x; x2 < 20; x2++)
            {
                for (unsigned char y2 = 0; y2 < 11; y2++)
                {
                    field[x2][y2] = field[x2 + 1][y2];
                }
            }
            for (unsigned char y3 = 0; y3 < 11; y3++)
                field[21][y3] = 0;
            *score += 514;
        }
    }
}


void gameover(int score)
{
    system("cls");
    puts("Game Over");
    printf("Your score id %d\n", score);
}
