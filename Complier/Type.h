#pragma once
#ifndef _TYPE_H_
#define _TYPE_H_

// TYPE

//其他类型 并不知道应该在哪用
#define TYPE_OTHER -999

//语句类型 貌似没什么作用
#define TYPE_STMT -100

//也不知道该放在哪
#define TYPE_EXPR -2

//空类型 不知道在哪用
#define TYPE_VOID -1

//左值表达式
#define TYPE_LEXPR 0

//基础类型
#define TYPE_CHAR 1
#define TYPE_INT 2
#define TYPE_FLOAT 3
#define TYPE_DOUBLE 4

//仅仅用在声明的时候
#define TYPE_UNKNOWN 5
//指针类型（基础类型， 指针维度）
#define TYPE_POINTER(TYPE, LEVEL) (TYPE * 100 + LEVEL)

//左值细化的表达式
#define TYPE_LEXPR_CHAR 6
#define TYPE_LEXPR_INT 7
#define TYPE_LEXPR_FLOAT 8
#define TYPE_LEXPR_DOUBLE 9
#define TYPE_LEXPR_POINTER(TYPE, LEVEL) ((TYPE + 5) * 100 + LEVEL)
// #define TYPE_REXPR_ARRAY(TYPE, LEVEL) ((TYPE + 5) * 100 + LEVEL)

//右值表达式
#define TYPE_REXPR 999

//数组（这个东西应该就是右值，没法做到直接赋值）
#define TYPE_ARRAY(TYPE, LEVEL) (TYPE * 1000 + LEVEL)

//右值细化的表达式
#define TYPE_REXPR_CHAR 6000
#define TYPE_REXPR_INT 7000
#define TYPE_REXPR_FLOAT 8000
#define TYPE_REXPR_DOUBLE 9000
#define TYPE_REXPR_POINTER(TYPE, LEVEL) ((TYPE + 5) * 10000 + LEVEL)
#define TYPE_REXPR_ARRAY(TYPE, LEVEL) ((TYPE + 5) * 100000 + LEVEL)


//FUNCTION

//判断一个表达式的类型能否被赋值
#define CAN_ASSIGN_TO(TYPE)((TYPE >= TYPE_LEXPR && TYPE < TYPE_REXPR)?1:0)

// #define CAN_CONVERT_HIDDEN(TYPE1, TYPE2)((TYPE1 >= 0 && TYPE1 < 10 && TYPE2 >= 0 && TYPE2 < 10 )?1:0)

// #define CAN_CONVERT_FORCE(TYPE1, TYPE2)((TYPE1 >= 0 && TYPE1 <= 999 && TYPE2 >= 0 && TYPE2 <= 999 )?1:0)

//返回一个指针的层数 如char **p1 就是两层char* 指针
#define LEVEL_OF_POINTER(TYPE)((TYPE>100)?TYPE%100:0)

//返回数组的层数
#define LEVEL_OF_ARRAY(TYPE)((TYPE>1000)?TYPE%1000:0)

//返回指针的类型 如char* p2返回char
#define TYPE_OF_POINTER(TYPE)((TYPE>100)?TYPE/100:TYPE)

//返回数组的类型
#define TYPE_OF_ARRAY(TYPE)((TYPE>1000)?TYPE/1000:TYPE)

//返回指针表达式的层数 如上面的p1, (p1++)这个表达式的类型就是char** 层数为2
#define LEVEL_OF_POINTER_EXPR(TYPE)(TYPE%100)

//返回指针表达式的层数 如上面的p1, (p1++)这个表达式的类型是char** 这个函数返回char
#define TYPE_OF_POINTER_EXPR(TYPE)((TYPE<=999)?TYPE/100-5:TYPE/10000-5)

//同上
#define LEVEL_OF_ARRAY_EXPR(TYPE)(TYPE%100)

//同上
#define TYPE_OF_ARRAY_EXPR(TYPE)(TYPE/100000-5)

//当遇到一些文法，比如char **p1 (p1[1])这个表达式的类型就变成了char* 这个函数返回代表一层char*的类型
#define SUB_LEVEL_OF_POINTER_EXPR(TYPE) ((TYPE%100>1)?TYPE-1:((TYPE>=999)?TYPE/10000:TYPE/100))

//同上
#define SUB_LEVEL_OF_ARRAY_EXPR(TYPE) ((TYPE%100>1)?TYPE-1:TYPE/100000)

//根据基础类型制造一个基础左值表达式类型
#define MAKE_BASIC_TYPE_LEXPR(TYPE) (TYPE+5)

//根据基础类型制造一个基础右值表达式类型
#define MAKE_BASIC_TYPE_REXPR(TYPE) ((TYPE+5)*1000)

//基础左值表达式的基础类型
#define TYPE_OF_BASIC_LEXOR(TYPE) (TYPE-5)

//基础右值表达式的基础类型
#define TYPE_OF_BASIC_REXOR(TYPE) (TYPE/1000)

//判断一个类型是不是指针
#define IS_POINTER(TYPE) ((TYPE > 100 && TYPE <= 600)? 1:0)

//判断一个类型是不是数组
#define IS_ARRAY(TYPE) ((TYPE > 1000 && TYPE <= 6000)? 1:0)

//判断一个类型是不是基础类型
#define IS_BASIC(TYPE) ((TYPE < 5 && TYPE > 0)? 1:0)

//判断一个类型是不是INT 或者 CHAR
#define IS_INT(TYPE) ((TYPE < 3 && TYPE > 0)? 1:0)

int LEVEL_OF_BASIC_TYPE(int TYPE);

int IS_UNKNOWN(int TYPE);

//返回一个表达式的基础类型 如char** p1 (p1++)这个表达式的类型为char**
int TYPE_OF_EXPR(int TYPE);

//表达式的层数（数组或指针）
int LEVEL_OF_EXPR_TYPE(int EXPR);

//判断能否隐式转换
int CAN_CONVERT_HIDDEN(int TYPE1, int TYPE2);

//判断能否强制转换
int CAN_CONVERT_FORCE(int TYPE1, int TYPE2);

//根据一个表达式生成另一个左值表达式
int MAKE_LEXPR(int EXPR);

//根据一个表达式生成另一个右值表达式
int MAKE_REXPR(int EXPR);

//能否赋值
int CAN_ASSIGH(int LEFT, int RIGHT);

int FIND_MAX_TYPE(int TYPE1, int TYPE2);


//能够位运算（判断是不是char 或者 int）
int CAN_BIT(int TYPE);

//制作未知类型的表达式
int MAKE_TYPE_BY_UNKNOWN(int TYPE, int UNKNOWN);


//根据一个表达式生成另一个左值表达式
int MAKE_LEXPR_BY_TYPE(int TYPE);

//根据一个TYPE生成另一个右值表达式
int MAKE_REXPR_BY_TYPE(int TYPE);

//判断两个type的最大值
int MAX_TYPE(int TYPE1, int TYPE2);

//两个变量能不能加减
int CAN_ADD_OR_PLUS(int TYPE1, int TYPE2);

//两个变量能不能乘除
int CAN_MUL_OR_DEV(int TYPE1, int TYPE2);

//两个变量能不能取模或位运算
int CAN_MOD_OR_BIT(int TYPE1, int TYPE2);

//加减得到的新类型
int MAKE_TYPE_BY_ADD_OR_PLUS(int TYPE1, int TYPE2);

//乘除得到的新类型
int MAKE_TYPE_BY_MUL_OR_DEV(int TYPE1, int TYPE2);

//取模得到的新类型
int MAKE_TYPE_BY_MOD_OR_BIT(int TYPE1, int TYPE2);

//逻辑运算得到的新类型
int MAKE_TYPE_BY_LOGIC(int TYPE1, int TYPE2);

//逗号运算得到的新类型
int MAKE_TYPE_BY_COMMA(int TYPE1, int TYPE2);

//赋值运算得到的新类型
int MAKE_TYPE_BY_ASSIGN(int TYPE1, int TYPE2);

//*得到的新类型
int MAKE_TYPE_BY_STAR(int TYPE);

//&得到的新类型
int MAKE_TYPE_BY_AND(int TYPE);
#endif