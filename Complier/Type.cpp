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

//����һ�����ʽ�Ļ������� ��char** p1 (p1++)������ʽ������Ϊchar**
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

//���ʽ�Ĳ����������ָ�룩
int LEVEL_OF_EXPR_TYPE(int EXPR){
	int TYPE = TYPE_OF_EXPR(EXPR);
	return LEVEL_OF_BASIC_TYPE(TYPE);
}

//�ж��ܷ���ʽת��
int CAN_CONVERT_HIDDEN(int TYPE1, int TYPE2){
	int result = 0;
	int type1 = TYPE_OF_EXPR(TYPE1);
	int type2 = TYPE_OF_EXPR(TYPE2);
	if ((type1 > 0 && type1 < 10 && type2 > 0 && type2 < 10) || type1 == type2) {
		result = 1;
	}
	return result;
}

//�ж��ܷ�ǿ��ת��
int CAN_CONVERT_FORCE(int TYPE1, int TYPE2){
	int result = 0;
	int type1 = TYPE_OF_EXPR(TYPE1);
	int type2 = TYPE_OF_EXPR(TYPE2);
	if ((type1 > 0 && type1 < TYPE_REXPR && type2 > 0 && type2 < TYPE_REXPR) || type1 == type2) {
		result = 1;
	}
	return result;
}

//����һ�����ʽ������һ����ֵ���ʽ
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

//����һ�����ʽ������һ����ֵ���ʽ
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

//�ܷ�ֵ
int CAN_ASSIGH(int LEFT, int RIGHT) {
	int result = 0;
	if (CAN_ASSIGN_TO(LEFT)) {
		if (CAN_CONVERT_HIDDEN(LEFT, RIGHT) || TYPE_OF_EXPR(LEFT) == TYPE_OF_EXPR(RIGHT)) {
			result = 1;
		}
	}
	// ����Ϊ������ĳ�ʼ���б�
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


//�ܹ�λ���㣨�ж��ǲ���char ���� int��
int CAN_BIT(int TYPE) {
	int type = TYPE_OF_EXPR(TYPE);
	if (type == TYPE_CHAR || type == TYPE_INT) {
		return 1;
	}
	else {
		return 0;
	}
}

//����δ֪���͵ı��ʽ
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


//����һ�����ʽ������һ����ֵ���ʽ
int MAKE_LEXPR_BY_TYPE(int TYPE) {
	int result = -1;
	if (TYPE < 10) {
		result = MAKE_BASIC_TYPE_LEXPR(TYPE);
	}
	else if (TYPE < TYPE_REXPR) {
		result = TYPE_LEXPR_POINTER(TYPE_OF_POINTER(TYPE), LEVEL_OF_POINTER(TYPE));
	}
	//������ ����Ϊ��������ʽ���������֧
	else if (TYPE > TYPE_REXPR) {
		result = TYPE_REXPR_ARRAY(TYPE_OF_ARRAY(TYPE), LEVEL_OF_ARRAY(TYPE));
	}
	return result;
}

//����һ��TYPE������һ����ֵ���ʽ
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

//�ж�����type�����ֵ
int MAX_TYPE(int TYPE1, int TYPE2) {
	return (TYPE1 > TYPE2) ? TYPE1 : TYPE2;
}

//���������ܲ��ܼӼ�
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

//���������ܲ��ܳ˳�
int CAN_MUL_OR_DEV(int TYPE1, int TYPE2) {
	if (IS_BASIC(TYPE1) && IS_BASIC(TYPE2)) {
		return 1;
	}
	return 0;
}

//���������ܲ���ȡģ��λ����
int CAN_MOD_OR_BIT(int TYPE1, int TYPE2) {
	if (IS_INT(TYPE1) && IS_INT(TYPE2)) {
		return 1;
	}
	return 0;
}

//�Ӽ��õ���������
int MAKE_TYPE_BY_ADD_OR_PLUS(int TYPE1, int TYPE2) {
	if (CAN_ADD_OR_PLUS(TYPE1, TYPE2)) {
		return  MAX_TYPE(TYPE1, TYPE2);
	}
	return -1;
}

//�˳��õ���������
int MAKE_TYPE_BY_MUL_OR_DEV(int TYPE1, int TYPE2) {
	if (CAN_MUL_OR_DEV(TYPE1, TYPE2)) {
		return  MAX_TYPE(TYPE1, TYPE2);
	}
	return -1;
}

//ȡģ�õ���������
int MAKE_TYPE_BY_MOD_OR_BIT(int TYPE1, int TYPE2) {
	if (CAN_MOD_OR_BIT(TYPE1, TYPE2)) {
		return  MAX_TYPE(TYPE1, TYPE2);
	}
	return -1;
}

//�߼�����õ���������
int MAKE_TYPE_BY_LOGIC(int TYPE1, int TYPE2) {
	return TYPE_CHAR;
}

//��������õ���������
int MAKE_TYPE_BY_COMMA(int TYPE1, int TYPE2) {
	return TYPE2;
}

//��ֵ����õ���������
int MAKE_TYPE_BY_ASSIGN(int TYPE1, int TYPE2) {
	if (CAN_ASSIGH(MAKE_LEXPR_BY_TYPE(TYPE1), MAKE_REXPR_BY_TYPE(TYPE2))) {
		return TYPE1;
	}
	return -1;
}

//*�õ���������
int MAKE_TYPE_BY_STAR(int TYPE) {
	if (IS_POINTER(TYPE)){
		return ((TYPE - 1) % 100 == 0) ? TYPE_OF_POINTER(TYPE) : TYPE - 1;
	}
	return -1;
}

//&�õ���������
int MAKE_TYPE_BY_AND(int TYPE) {
	if (IS_POINTER(TYPE)){
		return TYPE + 1;
	}
	else if(IS_BASIC(TYPE)){
		return TYPE_POINTER(TYPE, 1);
	}
	return -1;
}