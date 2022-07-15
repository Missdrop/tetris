#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "functions.h"
#include "global.h"

int main (void)
{
    char *previewBag = malloc(sizeof(char)*7);
    bagseven(previewBag);                                               //初始化第一包序列

    for (unsigned char blockCount = 0; blockCount < 7; blockCount++)    //Bag7序列循环
    {
        previewBlock.type = *(previewBag + blockCount);                 //替换当前方块至下一方块
        previewBlock.location[1] = 3, previewBlock.location[2] = 7;     //初始化方块位置
        previewBlock.direction = 0;                                     //初始化方块朝向
        if (spawn(tetrisField, previewBlock.type)){                     //生成一个块
            int input;
            while(input = getch())                                      //获取键盘操作
            {
                if(movement(tetrisField, previewBlock.type, input))     //移动（内置打印场地）并判断是否触底，触底则break（新生成一块）
                    break;
                if (rotation(tetrisField, previewBlock.type, input))    //旋转（内置打印场地）旋转成功则continue，接受后续操作
                    continue;
                    while (clear(tetrisField, &score));                 //循环直至完全消行
                printfield(tetrisField);                                //打印完整消行后场地
            }
        }
        else break;                                                     //无法生成方块则说明游戏失败
        if (blockCount == 7) {                                          //判断本包是否用完
            bagseven(previewBag);                                       //一包用完后重新生成一包
            blockCount = 0;                                             //重置包内方块数
        }
    }
    gameover(score);                                                    //游戏结束，展示分数

    free(previewBag);
    system("pause");
    return 0;
}
