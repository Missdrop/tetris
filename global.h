/* 全局变量声明头文件 */

#ifndef _EXTERN_H_INCLUDED
#define _EXTERN_H_INCLUDED

//备注：使用char类型目的为节省内存

extern char tetrisField[22][12];   //场地(标准的10*20大小),，0为空白，1为存在方块，边缘为1被打印为墙

/*
|---------------------------|
|         |        |        |
| (-1,-1) | (-1,0) | (-1,1) |
|         |        |        |
|------------------------------------|
|         |        |        |        |      方块参考坐标系（除I）
| ( 0,-1) | ( 0,0) | ( 0,1) | ( 0,2) |      (0,0)为方块中心
|         |        |        |        |
|------------------------------------|
|         |        |        |
| ( 1,-1) | ( 1,0) | ( 1,1) |
|         |        |        |
----------------------------|
*/

extern const struct blockShape{                              //方块形状结构（储存为相对坐标）
    char blockshape[4 /* 四种方块朝向 */][4 /*四个方块坐标 */][2 /* X,Y坐标 */];
} blockT, blockS, blockZ, blockL, blockJ, blockO, blockI;

extern const char blockMovement[3 /*三个方向 */][2 /*x，y坐标*/]; //方块移动表

extern const char wallKickData[4 /*四个初始方向 */][2 /*两个旋转方向*/][4 /*四次踢墙测试*/][2 /*x，y坐标*/]; // J, L, S, T, Z踢墙表

extern const char wallKickDataI[4 /*四个初始方向*/][2 /*两个旋转方向*/][4 /*四次踢墙测试*/][2 /*x，y坐标*/]; // I方块踢墙表

extern struct tetroMinoState {                         //当前方块数据（结构）
    char type;                              //方块种类
    char location[2];                       //方块位置坐标
    char direction;                         //方块朝向（四种朝向:0,1(R),3(L),2(180)）
} previewBlock;

extern int score;                   //分数

extern int facing[4];               //方向

#endif
