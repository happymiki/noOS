typedef unsigned int bool;

/* ��һ�ַ������궨�� */
#define CopyMMC4_3toMem(z,a,b,c,d)(((bool(*)(int, unsigned int,unsigned short, unsigned int*, bool))(*((unsigned int
*)0xD0037F9C)))(a,b,c,d))

/* �ڶ��ַ������ú���ָ�뷽ʽ���� */
typedef (bool(*pCopySDMMC2Mem)(int, unsigned int, unsigned short, unsigned int*, bool);

/* ʵ��ʹ�� */
pCopySDMMC2Mem p1 = (pCopySDMMC2Mem)0xD0037F98;

/* ��һ�ֵ��÷��� */
p1(x,x,x,x,x);
/* �ڶ��ֵ��÷��� */
(*p1)(x,x,x,x,x);










