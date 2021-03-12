#include "Type.h"

int LEVEL_OF_BASIC_TYPE(int TYPE){
	if (TYPE < 10){
		return 0;
	}
	else if (TYPE < 999)
	{
		return LEVEL_OF_POINTER(TYPE);
	}
	else{
		return LEVEL_OF_ARRAY(TYPE);
	}
}

int IS_UNKNOWN(int TYPE) {
	if (TYPE < 10){
		return (TYPE == TYPE_UNKNOWN) ? true : false;
	}
	else if (TYPE < 999)
	{
		return (TYPE % 100 == TYPE_UNKNOWN) ? true : false;
	}
	else{
		return (TYPE % 1000 == TYPE_UNKNOWN) ? true : false;
	}
}

//返回一个表达式的基础类型 如char** p1 (p1++)这个表达式的类型为char**
int TYPE_OF_EXPR(int TYPE) {
	int result = 0;
	if (TYPE < TYPE_REXPR) {
		if (TYPE < 10) {
			result = TYPE - 5;
		}
		else {
			return TYPE_POINTER(TYPE_OF_POINTER_EXPR(TYPE), LEVEL_OF_POINTER_EXPR(TYPE));
		}
	}
	else
	{
		if (TYPE < 5000) {
			return TYPE_ARRAY(TYPE_OF_ARRAY_EXPR(TYPE), LEVEL_OF_ARRAY_EXPR(TYPE));
		}
		else if (TYPE < 10000)
		{
			return TYPE / 1000 - 5;
		}
		else if (TYPE < 100000){
			return TYPE_POINTER(TYPE_OF_POINTER_EXPR(TYPE), LEVEL_OF_POINTER_EXPR(TYPE));
		}
		else {
			return TYPE_ARRAY(TYPE_OF_ARRAY_EXPR(TYPE), LEVEL_OF_ARRAY_EXPR(TYPE));
		}
	}
	return result;
}

//表达式的层数（数组或指针）
int LEVEL_OF_EXPR_TYPE(int EXPR){
	int TYPE = TYPE_OF_EXPR(EXPR);
	return LEVEL_OF_BASIC_TYPE(TYPE);
}

//判断能否隐式转换
int CAN_CONVERT_HIDDEN(int TYPE1, int TYPE2){
	int result = 0;
	int type1 = TYPE_OF_EXPR(TYPE1);
	int type2 = TYPE_OF_EXPR(TYPE2);
	if ((type1 > 0 && type1 < 10 && type2 > 0 && type2 < 10) || type1 == type2) {
		result = 1;
	}
	return result;
}

//判断能否强制转换
int CAN_CONVERT_FORCE(int TYPE1, int TYPE2){
	int result = 0;
	int type1 = TYPE_OF_EXPR(TYPE1);
	int type2 = TYPE_OF_EXPR(TYPE2);
	if ((type1 > 0 && type1 < TYPE_REXPR && type2 > 0 && type2 < TYPE_REXPR) || type1 == type2) {
		result = 1;
	}
	return result;
}

//根据一个表达式生成另一个左值表达式
int MAKE_LEXPR(int EXPR) {
	int result = -1;
	int TYPE = TYPE_OF_EXPR(EXPR);
	if (TYPE < 10) {
		result = MAKE_BASIC_TYPE_LEXPR(TYPE);
	}
	else if (TYPE < TYPE_REXPR) {
		result = TYPE_LEXPR_POINTER(TYPE_OF_POINTER(TYPE), LEVEL_OF_POINTER(TYPE));
	}
	return result;
}

//根据一个表达式生成另一个右值表达式
int MAKE_REXPR(int EXPR) {
	int result = -1;
	int TYPE = TYPE_OF_EXPR(EXPR);
	if (TYPE < 10) {
		result = MAKE_BASIC_TYPE_REXPR(TYPE);
	}
	else if (TYPE < TYPE_REXPR) {
		result = TYPE_REXPR_POINTER(TYPE_OF_POINTER(TYPE), LEVEL_OF_POINTER(TYPE));
	}
	else if (TYPE > TYPE_REXPR) {
		result = TYPE_REXPR_ARRAY(TYPE_OF_ARRAY(TYPE), LEVEL_OF_ARRAY(TYPE));
	}
	return result;
}

//能否赋值
int CAN_ASSIGH(int LEFT, int RIGHT) {
	int result = 0;
	if (CAN_ASSIGN_TO(LEFT)) {
		if (CAN_CONVERT_HIDDEN(LEFT, RIGHT) || TYPE_OF_EXPR(LEFT) == TYPE_OF_EXPR(RIGHT)) {
			result = 1;
		}
	}
	// 仅仅为了数组的初始化列表
	else {
		if (TYPE_OF_EXPR(RIGHT) > TYPE_REXPR && LEVEL_OF_ARRAY(TYPE_OF_EXPR(RIGHT)) == 1 && TYPE_OF_EXPR(LEFT) > TYPE_REXPR){
			return 1;
		}
	}
	return result;
}

int FIND_MAX_TYPE(int TYPE1, int TYPE2) {
	if (CAN_CONVERT_HIDDEN(TYPE1, TYPE2)) {
		return (TYPE1 > TYPE2) ? TYPE1 : TYPE2;
	}
	return -1;
}


//能够位运算（判断是不是char 或者 int）
int CAN_BIT(int TYPE) {
	int type = TYPE_OF_EXPR(TYPE);
	if (type == TYPE_CHAR || type == TYPE_INT) {
		return 1;
	}
	else {
		return 0;
	}
}

//制作未知类型的表达式
int MAKE_TYPE_BY_UNKNOWN(int TYPE, int UNKNOWN) {
	if (IS_POINTER(UNKNOWN)) {
		return TYPE_POINTER(TYPE, LEVEL_OF_POINTER(UNKNOWN));
	}
	else if (IS_ARRAY(UNKNOWN)) {
		return TYPE_ARRAY(TYPE, LEVEL_OF_ARRAY(UNKNOWN));
	}
	else {
		return TYPE;
	}
}


//根据一个表达式生成另一个左值表达式
int MAKE_LEXPR_BY_TYPE(int TYPE) {
	int result = -1;
	if (TYPE < 10) {
		result = MAKE_BASIC_TYPE_LEXPR(TYPE);
	}
	else if (TYPE < TYPE_REXPR) {
		result = TYPE_LEXPR_POINTER(TYPE_OF_POINTER(TYPE), LEVEL_OF_POINTER(TYPE));
	}
	//有问题 仅仅为了数组表达式而到这个分支
	else if (TYPE > TYPE_REXPR) {
		result = TYPE_REXPR_ARRAY(TYPE_OF_ARRAY(TYPE), LEVEL_OF_ARRAY(TYPE));
	}
	return result;
}

//根据一个TYPE生成另一个右值表达式
int MAKE_REXPR_BY_TYPE(int TYPE) {
	int result = -1;
	if (TYPE < 10) {
		result = MAKE_BASIC_TYPE_REXPR(TYPE);
	}
	else if (TYPE < TYPE_REXPR) {
		result = TYPE_REXPR_POINTER(TYPE_OF_POINTER(TYPE), LEVEL_OF_POINTER(TYPE));
	}
	else if (TYPE > TYPE_REXPR) {
		result = TYPE_REXPR_ARRAY(TYPE_OF_ARRAY(TYPE), LEVEL_OF_ARRAY(TYPE));
	}
	return result;
}

//判断两个type的最大值
int MAX_TYPE(int TYPE1, int TYPE2) {
	return (TYPE1 > TYPE2) ? TYPE1 : TYPE2;
}

//两个变量能不能加减
int CAN_ADD_OR_PLUS(int TYPE1, int TYPE2) {
	if (IS_BASIC(TYPE1) && IS_BASIC(TYPE2)) {
		return 1;
	}
	else {
		if ((IS_POINTER(TYPE1) && IS_BASIC(TYPE2)) || (IS_POINTER(TYPE2) && IS_BASIC(TYPE1))){
			return 1;
		}
	}
	return 0;
}

//两个变量能不能乘除
int CAN_MUL_OR_DEV(int TYPE1, int TYPE2) {
	if (IS_BASIC(TYPE1) && IS_BASIC(TYPE2)) {
		return 1;
	}
	return 0;
}

//两个变量能不能取模或位运算
int CAN_MOD_OR_BIT(int TYPE1, int TYPE2) {
	if (IS_INT(TYPE1) && IS_INT(TYPE2)) {
		return 1;
	}
	return 0;
}

//加减得到的新类型
int MAKE_TYPE_BY_ADD_OR_PLUS(int TYPE1, int TYPE2) {
	if (CAN_ADD_OR_PLUS(TYPE1, TYPE2)) {
		return  MAX_TYPE(TYPE1, TYPE2);
	}
	return -1;
}

//乘除得到的新类型
int MAKE_TYPE_BY_MUL_OR_DEV(int TYPE1, int TYPE2) {
	if (CAN_MUL_OR_DEV(TYPE1, TYPE2)) {
		return  MAX_TYPE(TYPE1, TYPE2);
	}
	return -1;
}

//取模得到的新类型
int MAKE_TYPE_BY_MOD_OR_BIT(int TYPE1, int TYPE2) {
	if (CAN_MOD_OR_BIT(TYPE1, TYPE2)) {
		return  MAX_TYPE(TYPE1, TYPE2);
	}
	return -1;
}

//逻辑运算得到的新类型
int MAKE_TYPE_BY_LOGIC(int TYPE1, int TYPE2) {
	return TYPE_CHAR;
}

//逗号运算得到的新类型
int MAKE_TYPE_BY_COMMA(int TYPE1, int TYPE2) {
	return TYPE2;
}

//赋值运算得到的新类型
int MAKE_TYPE_BY_ASSIGN(int TYPE1, int TYPE2) {
	if (CAN_ASSIGH(MAKE_LEXPR_BY_TYPE(TYPE1), MAKE_REXPR_BY_TYPE(TYPE2))) {
		return TYPE1;
	}
	return -1;
}

//*得到的新类型
int MAKE_TYPE_BY_STAR(int TYPE) {
	if (IS_POINTER(TYPE)){
		return ((TYPE - 1) % 100 == 0) ? TYPE_OF_POINTER(TYPE) : TYPE - 1;
	}
	return -1;
}

//&得到的新类型
int MAKE_TYPE_BY_AND(int TYPE) {
	if (IS_POINTER(TYPE)){
		return TYPE + 1;
	}
	else if(IS_BASIC(TYPE)){
		return TYPE_POINTER(TYPE, 1);
	}
	return -1;
}