#pragma once
#ifndef _TYPE_H_
#define _TYPE_H_

// TYPE

//�������� ����֪��Ӧ��������
#define TYPE_OTHER -999

//������� ò��ûʲô����
#define TYPE_STMT -100

//Ҳ��֪���÷�����
#define TYPE_EXPR -2

//������ ��֪��������
#define TYPE_VOID -1

//��ֵ���ʽ
#define TYPE_LEXPR 0

//��������
#define TYPE_CHAR 1
#define TYPE_INT 2
#define TYPE_FLOAT 3
#define TYPE_DOUBLE 4

//��������������ʱ��
#define TYPE_UNKNOWN 5
//ָ�����ͣ��������ͣ� ָ��ά�ȣ�
#define TYPE_POINTER(TYPE, LEVEL) (TYPE * 100 + LEVEL)

//��ֵϸ���ı��ʽ
#define TYPE_LEXPR_CHAR 6
#define TYPE_LEXPR_INT 7
#define TYPE_LEXPR_FLOAT 8
#define TYPE_LEXPR_DOUBLE 9
#define TYPE_LEXPR_POINTER(TYPE, LEVEL) ((TYPE + 5) * 100 + LEVEL)
// #define TYPE_REXPR_ARRAY(TYPE, LEVEL) ((TYPE + 5) * 100 + LEVEL)

//��ֵ���ʽ
#define TYPE_REXPR 999

//���飨�������Ӧ�þ�����ֵ��û������ֱ�Ӹ�ֵ��
#define TYPE_ARRAY(TYPE, LEVEL) (TYPE * 1000 + LEVEL)

//��ֵϸ���ı��ʽ
#define TYPE_REXPR_CHAR 6000
#define TYPE_REXPR_INT 7000
#define TYPE_REXPR_FLOAT 8000
#define TYPE_REXPR_DOUBLE 9000
#define TYPE_REXPR_POINTER(TYPE, LEVEL) ((TYPE + 5) * 10000 + LEVEL)
#define TYPE_REXPR_ARRAY(TYPE, LEVEL) ((TYPE + 5) * 100000 + LEVEL)


//FUNCTION

//�ж�һ�����ʽ�������ܷ񱻸�ֵ
#define CAN_ASSIGN_TO(TYPE)((TYPE >= TYPE_LEXPR && TYPE < TYPE_REXPR)?1:0)

// #define CAN_CONVERT_HIDDEN(TYPE1, TYPE2)((TYPE1 >= 0 && TYPE1 < 10 && TYPE2 >= 0 && TYPE2 < 10 )?1:0)

// #define CAN_CONVERT_FORCE(TYPE1, TYPE2)((TYPE1 >= 0 && TYPE1 <= 999 && TYPE2 >= 0 && TYPE2 <= 999 )?1:0)

//����һ��ָ��Ĳ��� ��char **p1 ��������char* ָ��
#define LEVEL_OF_POINTER(TYPE)((TYPE>100)?TYPE%100:0)

//��������Ĳ���
#define LEVEL_OF_ARRAY(TYPE)((TYPE>1000)?TYPE%1000:0)

//����ָ������� ��char* p2����char
#define TYPE_OF_POINTER(TYPE)((TYPE>100)?TYPE/100:TYPE)

//�������������
#define TYPE_OF_ARRAY(TYPE)((TYPE>1000)?TYPE/1000:TYPE)

//����ָ����ʽ�Ĳ��� �������p1, (p1++)������ʽ�����;���char** ����Ϊ2
#define LEVEL_OF_POINTER_EXPR(TYPE)(TYPE%100)

//����ָ����ʽ�Ĳ��� �������p1, (p1++)������ʽ��������char** �����������char
#define TYPE_OF_POINTER_EXPR(TYPE)((TYPE<=999)?TYPE/100-5:TYPE/10000-5)

//ͬ��
#define LEVEL_OF_ARRAY_EXPR(TYPE)(TYPE%100)

//ͬ��
#define TYPE_OF_ARRAY_EXPR(TYPE)(TYPE/100000-5)

//������һЩ�ķ�������char **p1 (p1[1])������ʽ�����;ͱ����char* ����������ش���һ��char*������
#define SUB_LEVEL_OF_POINTER_EXPR(TYPE) ((TYPE%100>1)?TYPE-1:((TYPE>=999)?TYPE/10000:TYPE/100))

//ͬ��
#define SUB_LEVEL_OF_ARRAY_EXPR(TYPE) ((TYPE%100>1)?TYPE-1:TYPE/100000)

//���ݻ�����������һ��������ֵ���ʽ����
#define MAKE_BASIC_TYPE_LEXPR(TYPE) (TYPE+5)

//���ݻ�����������һ��������ֵ���ʽ����
#define MAKE_BASIC_TYPE_REXPR(TYPE) ((TYPE+5)*1000)

//������ֵ���ʽ�Ļ�������
#define TYPE_OF_BASIC_LEXOR(TYPE) (TYPE-5)

//������ֵ���ʽ�Ļ�������
#define TYPE_OF_BASIC_REXOR(TYPE) (TYPE/1000)

//�ж�һ�������ǲ���ָ��
#define IS_POINTER(TYPE) ((TYPE > 100 && TYPE <= 600)? 1:0)

//�ж�һ�������ǲ�������
#define IS_ARRAY(TYPE) ((TYPE > 1000 && TYPE <= 6000)? 1:0)

//�ж�һ�������ǲ��ǻ�������
#define IS_BASIC(TYPE) ((TYPE < 5 && TYPE > 0)? 1:0)

//�ж�һ�������ǲ���INT ���� CHAR
#define IS_INT(TYPE) ((TYPE < 3 && TYPE > 0)? 1:0)

int LEVEL_OF_BASIC_TYPE(int TYPE);

int IS_UNKNOWN(int TYPE);

//����һ�����ʽ�Ļ������� ��char** p1 (p1++)������ʽ������Ϊchar**
int TYPE_OF_EXPR(int TYPE);

//���ʽ�Ĳ����������ָ�룩
int LEVEL_OF_EXPR_TYPE(int EXPR);

//�ж��ܷ���ʽת��
int CAN_CONVERT_HIDDEN(int TYPE1, int TYPE2);

//�ж��ܷ�ǿ��ת��
int CAN_CONVERT_FORCE(int TYPE1, int TYPE2);

//����һ�����ʽ������һ����ֵ���ʽ
int MAKE_LEXPR(int EXPR);

//����һ�����ʽ������һ����ֵ���ʽ
int MAKE_REXPR(int EXPR);

//�ܷ�ֵ
int CAN_ASSIGH(int LEFT, int RIGHT);

int FIND_MAX_TYPE(int TYPE1, int TYPE2);


//�ܹ�λ���㣨�ж��ǲ���char ���� int��
int CAN_BIT(int TYPE);

//����δ֪���͵ı��ʽ
int MAKE_TYPE_BY_UNKNOWN(int TYPE, int UNKNOWN);


//����һ�����ʽ������һ����ֵ���ʽ
int MAKE_LEXPR_BY_TYPE(int TYPE);

//����һ��TYPE������һ����ֵ���ʽ
int MAKE_REXPR_BY_TYPE(int TYPE);

//�ж�����type�����ֵ
int MAX_TYPE(int TYPE1, int TYPE2);

//���������ܲ��ܼӼ�
int CAN_ADD_OR_PLUS(int TYPE1, int TYPE2);

//���������ܲ��ܳ˳�
int CAN_MUL_OR_DEV(int TYPE1, int TYPE2);

//���������ܲ���ȡģ��λ����
int CAN_MOD_OR_BIT(int TYPE1, int TYPE2);

//�Ӽ��õ���������
int MAKE_TYPE_BY_ADD_OR_PLUS(int TYPE1, int TYPE2);

//�˳��õ���������
int MAKE_TYPE_BY_MUL_OR_DEV(int TYPE1, int TYPE2);

//ȡģ�õ���������
int MAKE_TYPE_BY_MOD_OR_BIT(int TYPE1, int TYPE2);

//�߼�����õ���������
int MAKE_TYPE_BY_LOGIC(int TYPE1, int TYPE2);

//��������õ���������
int MAKE_TYPE_BY_COMMA(int TYPE1, int TYPE2);

//��ֵ����õ���������
int MAKE_TYPE_BY_ASSIGN(int TYPE1, int TYPE2);

//*�õ���������
int MAKE_TYPE_BY_STAR(int TYPE);

//&�õ���������
int MAKE_TYPE_BY_AND(int TYPE);
#endif