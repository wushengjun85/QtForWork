#ifndef _LIB_SHM_H_
#define _LIB_SHM_H_

#ifdef __cplusplus
extern "C"{
#endif

#define	u8 unsigned char
#define	u16 unsigned short
#define	u32 unsigned int
#define RAM_CAN_fData                   "RAM_CAN_fData"         // CAN�����ڴ��ļ�
#define RAM_CAN_ECU_fData               "RAM_CAN_ECU_fData"         // CANECU�����ڴ��ļ�

#define CAN_LOCK                        1024+1               // CAN������
/************************************************/
/* CAN �м�����ݴ���ṹ */
/************************************************/
//����������ID
typedef enum{
	yuchai,
	weichai
}Fdj_Cj_Id;

typedef struct
{
	int cnt;//����SPN����
	int if_data;//�Ƿ�������
	int spn[10];
	int fmi[10];
	int ifch[10];
	char chgzm[10][100];//���Ĺ�����
}CAN_SPN;

typedef struct
{
	unsigned char  can_no;
	u8 flagTXCS;//ͨ�ų�ʱ��־
	//ָʾ��־:0,1
	//������ ���� 
	u8 flagLeft;  //��ת
	u8 flagBattery;//��ƿָʾ�� ���ָʾ��
	u8 flagWidthlamp; //ʾ���
	u8 flagYG; //Զ���
	//u8 flagSW; //ˮ��
	u8 flagJG; //�����
	u8 flagJY; //����
	u8 flagLCM; //������
	u8 flagLCM_seven; //������70
	u8 flagGL; //����
	u8 flagKL; //������
	u8 flagSS;//��ɲ
	u8 flagFDJYR; //������Ԥ��
	u8 flagPark;//ͣ��
	u8 flagFDJGZ; //����������
	u8 flagRight; //��ת
	u8 flagDC;//�����ź�
	u8 sta_view;//�л�������ʷ��¼
	u8 flagYYYDS;//Һѹ�Ͷ���
	u8 flagYYMainSK;//Һѹ������ɿ�
	u8 flagYYMainZJ;//Һѹ������Ž�
	u8 flagBHLdown;//�κ��ֽ���
	u8 flagBHLup;//�κ�����
	u8 flagGTup;//��̨��
	u8 flagGTdown;//��̨��
	u8 flagfastspeed;//�����ź�
	u8 flagXLTclose;//ж��Ͳ�ر�
	u8 flagXLTopen;//ж��Ͳ��
	u8 flagYSFL;//��ˮ����
	//u8 flagCD;//���ָʾ

	//���������
	u8 flagBHLdownDCF;//�κ��ֽ��͵�ŷ�
	u8 flagBHLupDCF;//�κ�������ŷ�
	u8 flagYYMainSKDCF;//Һѹ������ɿ���ŷ�
	u8 flagYYMainZJDCF;//Һѹ������Ž���ŷ�
	u8 flagGTupDCF;//��̨��
	u8 flagGTdownDCF;//��̨��
	u8 flagXLTcloseDCF;//ж��Ͳ�ر�
	u8 flagXLTopenDCF;//ж��Ͳ��
	u8 flagSCDCF;//ɲ����ŷ�
	u8 flagDCPower;//������Դ
	u8 flagYLDCF;//������ŷ�
	u8 flagmijiclr;//�׼�����
	u8 flagKD;//�յ���ʾ
	u16 speed;
	//ָʾ��ֵ
	int VolYL; //����
	int StaYL;//��������״̬
	int VolYeyayouwen;//Һѹ����
	int MIJI;//�׼�
	int SaLiangLV;//������ʧ��
	int GeChaheight;//���߶�
	int FTspeed;//����ת��
	int SYspeed;//����ת��
	int ZLspeed;//����ת��
	int HourSpeed;//ʱ��
	int VOLV;//��ص�ѹ
	int VolMIJISUM;//���׼�
	int VolLICHENG;//���
	int VolMCL;//Ķ����
	int VolGTweith;//��̨���
	int VolShiWen;//����
} RAM_CAN_sData;

typedef struct
{
	unsigned char  can_no;
	u8 fdj_id;//����������ID
	u8 flagFDJYR_ECU; //������Ԥ��ECU
	u8 flagECU;//ecu
	u8 flagFDJGZ_ECU; //����������ECU
	u8 flagYSFL_ECU;//��ˮ����ECU

	//ָʾ��ֵ
	int VolSW;//ˮ��
	int VolYL; //����
	int VolJYWD;//�����¶�
	int VolJYYL;//����ѹ��
	int FDJ_speed;//������ת��
	int VolYH;//�ͺ�
	
	//SPN����
	CAN_SPN spn_can;
} RAM_CAN_sData_ECU;



void Can_Ram_init();
void Can_Ram_Get(RAM_CAN_sData * RAM_CAN,RAM_CAN_sData_ECU * RAM_CAN_ECU);
void Can_Ram_Set(RAM_CAN_sData * RAM_CAN,RAM_CAN_sData_ECU * RAM_CAN_ECU);
void Can_set_spn_flag(int flag);
void Can_set_Fdj_id(int id);//���÷���������ID������SPN���Ĳ�ѯ
void Can_set_mijiclr_flag(int flag);
void Can_set_MCL_flag(int chanliang);
void Can_set_GTweith_flag(int weith);

//�ӹ����ڴ���
void lockshm();
//�⹲���ڴ���
void unlockshm();
void Set_IO_H(int gpion);
void Set_IO_L(int gpion);
//int beep_Init();
//�򿪷�����
void beep_on();

//�رշ�����
void beep_off();
//�򿪷�����,����
void beep_on_Bit();

//����ͷ�л���V1
void cam_to_V1();
//����ͷ�л���V2
void cam_to_V2();
//����ͷ�л���V3
void cam_to_V3();
//�ź��л���ARM
void sig_to_arm();
//�򿪷�����,����
//void beep_on_S_short();

//�򿪷�����,����
//void beep_on_S_long();

#ifdef __cplusplus
}
#endif 

#endif
