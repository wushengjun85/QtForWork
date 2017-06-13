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
/****************************************************/
//2017/4/1 wangxw add,���ڽ�����ʾ���õ��Ͻṹ��,
//���ڽṹ�������޸�,Ϊ�˼��ݽ����Ͻṹ��,�ض���ú���������;
#define JINYEE_EXT		1 	

/****************************************************/

#define RetIf(c)				if (c) return
#define RetValueIf(c, value)	if (c) return (value)
#define DoIf(c, a)				if (c) {a;}
#define JumpIf(c, lable)		if (c) goto lable
#define BreakIf(c)				if (c) break
#define ContinueIf(c)			if (c) continue
#define Max(x, y)	((x) >= (y) ? (x) : (y))
#define Min(x, y)	((x) >= (y) ? (y) : (x))

enum XINYAN_MACHINE_MODEL
{
	XY_MODEL_4YZT_5,								/* 4YZT-5 */
	XY_MODEL_4YZT_10,								/* 4YZT-10 */
	XY_MODEL_4YZT_8,								/* 4YZT-8 */
	XY_MODEL_4YZB_4_5_7_8,						/* 4YZB-4/5/7/8 */
	XY_MODEL_4YZB_3A,								/* 4YZB-3A */
	XY_MODEL_4YZB_4B,								/* 4YZB-4B */
	XY_MODEL_4YZBT_5_8,							/* 4YZBT-5/8 */
	XY_MODEL_4YZ_3_12V,							/* 4YZ-3(12V) */
	XY_MODEL_4QZ_2200_2600,						/* 4QZ-2200/2600 */
	XY_MODEL_4QZ_S3000,							/* 4QZ-S3000 */
	XY_MODEL_3JA_3600,							/* 3JA-3600	*/
	XY_MODEL_4MGS_300,							/* 4MGS-300 */
	XY_MODEL_BUTT									/* end */
};

enum VIDEO_INPUT_CHANNEL_EN
{
	VI_CHN_1,
	VI_CHN_2,
	VI_CHN_3,
	VI_CHN_BUTT
};


typedef struct{
		XINYAN_MACHINE_MODEL m_Model;
}XY_MachineInfo;


typedef struct
{
	int m_iSPN;				//������spn��
	int m_iFMI;				//������fmi��
}ECU_ErrCode;			

typedef struct {
    int	m_iErrType;		//0:ͼ���쳣���ϡ�1:���������ϡ�2:������·����
    int	m_iTime;		//����ʱ��
   union
	{
		int   	m_iErrNo;		//���Ϻ�
		ECU_ErrCode 	m_stEcuErrCode;	//������������
   	} ;
    char   m_strErrMsg[128];	 //������Ϣ
} Info_SYS_ERR;


enum LAMP_BIT_TYPE
{
	LAMP_BIT_ZhiLiHuiShou,			/*	����������	*/
	LAMP_BIT_LiangCangMan,			/*	������		*/
	LAMP_BIT_LiangTongBaiChu,		/*	��Ͳ�ڳ�	*/
	LAMP_BIT_XieLiangZhong,			/*	ж����		*/
	LAMP_BIT_ShangShaiKaiKou,		/*	��ɸ����	*/
	LAMP_BIT_XiaShaiKaiKou,			/*	��ɸ����	*/
	LAMP_BIT_YeYaLvQing,			/*	Һѹ����	*/
	LAMP_BIT_YeYaYouYa,				/*	Һѹ��ѹ	*/
	LAMP_BIT_CaoXiangXianZhi,		/* 	��������	*/
	LAMP_BIT_BUTT
};

enum GZ_BIT_TYPE
{
	GZ_BIT_ZHUJI,			/* �������� */
	GZ_BIT_FENGJI, 			/* ������� */
	GZ_BIT_LIANGCANGGAI, 	/* ���ָǹ��� */
	GZ_BIT_GUNTONG, 		/* ��Ͳ���� */
	GZ_BIT_SHENGYUNQI, 		/* һ����������,�������� */
	GZ_BIT_SHENGYUNQI_2, 		/* ������������*/
	GZ_BIT_SHENGYUNQI_3, 		/* ������������*/
	GZ_BIT_GUOQIAO, 		/* ���Ź��� */
	GZ_BIT_SHACHEZHIDONG, 	/* ɲ���ƶ����� */
	GZ_BIT_SHACHEPANMOSUN, 	/* ɲ����ĥ��*/
	GZ_BIT_GETAI,				/* ��̨��������*/
	GZ_BIT_DAOLUN,				/* ���ֶ�������*/
	GZ_BIT_BUTT
};

#define SET_GZ_BIT(x,index)	( x |= 1 << index )			/* ���� ���� bit λ */
#define CLR_GZ_BIT(x,index)	( x &= ~(1 << index) )		/* ��� ���� bit λ */
#define CHK_GZ_BIT(x,index)	( x & (1 << index) )			/* ��� ���� bit λ */

#define SET_BIT(x,index)	SET_GZ_BIT(x,index)
#define CLR_BIT(x,index)	CLR_GZ_BIT(x,index)
#define CHK_BIT(x,index)	CHK_GZ_BIT(x,index)

#define Bit(S, Bits, Value) ( (Value==1) ? (S|(1<<Bits)) : (S&(~(1<<Bits))) )


#define MAX_SPEED_TYPE_NUM		20
enum SPEED_TYPE_EN
{
	SPEED_GUOQIAO,			/* ����ת�� */
	SPEED_JIAOLONG,			/* ����ת�� */
	SPEED_GUNTONG,			/* ��Ͳת�� */
	SPEED_FENGJI,				/* ���ת�� */
	SPEED_GETAI,				/* ��̨ת�� */	
	SPEED_JUPAN,				/* ����ת�� */
	SPEED_XINGZOU,				/* ʱ��/����ת�� */
	SPEED_SHENGYUNQI,			/* ������ת�� */
	SPEED_BACHA,				/* �β�ת�� */
	SPEED_BAHELUN,			/* �κ���ת�� */
	SPEED_BOPIJI,				/* ��Ƥ��ת�� */
	SPEED_SANREFENGSHAN,		/* ɢ�ȷ���ת�� */
	SPEED_PIN1,				/* ת��1 */
	SPEED_PIN4,				/* ת��4 */
	SPEED_PIN7,				/* ת��7 */
	SPEED_PIN17,				/* ת��17 */
	SPEED_BUTT		
};

enum
{	
	DID0_D0,			//������(������)���������1���ֽ�
	DID0_D1,			//������(������)��2���ֽ�
	DID0_D2,			//������(������)��3���ֽ�
	DID0_D3,			//������(������)��4���ֽ�
	DID0_D4,			//������(������)��5���ֽ�
	DID0_D5,			//������(������)��6���ֽ�
	DID0_D6,			//������(������)��7���ֽ�
	DID0_D7,			//������(������)��8���ֽ�
	DID0_BUTT,			//ĩβ
};
enum DI_BIT_TYPE_EN
{
	DI_BIT_GunTongSpeed_Up=6,					//��Ͳת�ٵ�������-��202-D1-B6
	DI_BIT_GunTongSpeed_Down=7,				//��Ͳת�ٵ�������-��202-D1-B7
};

enum GUI_CMD_CFG_REQ_TYPE_EN
{
	GUI_CMD_CFG_REQ_ALL,						/* �����ȡ���б궨����*/
	GUI_CMD_CFG_REQ_XinZouJuBing_Data,			/* ���߾�� �궨����*/
	GUI_CMD_CFG_REQ_XinZouJuBing_Offset=4,		/* ���߾���м�λ��ƫ���� */
	GUI_CMD_CFG_REQ_XinZouLaGan_Data=11,		/* �������˱궨���� */
	GUI_CMD_CFG_REQ_XinZouLaGan_Offset=14,		/* ���������м�λ��ƫ���� */
	GUI_CMD_CFG_REQ_AoBanJianXi_Minimum=21,		/* �����϶��Сֵ */
	GUI_CMD_CFG_REQ_AoBanJianXi_Maximum=22,	/* �����϶���ֵ */
	GUI_CMD_CFG_REQ_ZhuLiHeZhangJinLi=31,		/* ������Ž���	 */
	GUI_CMD_CFG_REQ_XieLiangLiHeZhangJinLi,		/* ж������Ž��� */
	GUI_CMD_CFG_REQ_GuoQiaoLiHeZhangJinLi,		/* ��������Ž��� */
	GUI_CMD_CFG_REQ_GunTongZhuanSuLinMinDu,	/* ��Ͳת�������� */
	GUI_CMD_CFG_REQ_FengJiZhuanSuLinMinDu,		/* ���ת�������� */
	GUI_CMD_CFG_REQ_JiaoLongZhuanSuLinMinDu,	/* ����ת�������� */
	GUI_CMD_CFG_REQ_GuoQiaoZhuanSuLinMinDu,		/* ����ת�������� */
	GUI_CMD_CFG_REQ_GeFuKuanDu,					/* ������	*/
	GUI_CMD_CFG_REQ_ZaiHeXiShu,					/* �غ�ϵ��	*/
	GUI_CMD_CFG_REQ_TiaoSuXiShu,					/* ����ϵ��	*/
	GUI_CMD_CFG_REQ_GuWuZhongLei,				/* ��������	*/
	GUI_CMD_CFG_REQ_DefaultRestore_XinZouJuBing=231,	/* �����ֱ����б궨ֵ�ָ���Ĭ��ֵ */
	GUI_CMD_CFG_REQ_DefaultRestore_XinZouLaGan=232,	/* �����������б궨ֵ�ָ���Ĭ��ֵ */
	GUI_CMD_CFG_REQ_DefaultRestore_AoBanJianXi=233,	/* �����϶���б궨ֵ�ָ���Ĭ��ֵ */
};

typedef struct
{
	unsigned char m_ucCmdHead1;	//������0x11
	unsigned char m_ucCmdHead2;	//������0x22
	unsigned char m_ucCmdHead3;	//������0x33
	unsigned char m_ucIdentifier;		//�궨��ʶ��
	unsigned char m_ucData[4];	//����
} BiaoDingCmdDataProtocol;

typedef struct
{
	
   BiaoDingCmdDataProtocol 	m_BDCmdData;
}BiaoDingDataReq;

enum BIAO_DING_DATA_TYPE_EN
{
	BD_DATA_ZhuLiHeZhangJinLi,			/* ������Ž���	 */
	BD_DATA_XieLiangLiHeZhangJinLi,	/* ж������Ž��� */
	BD_DATA_GuoQiaoLiHeZhangJinLi,		/* ��������Ž��� */
	BD_DATA_GunTongZhuanSuLinMinDu,	/* ��Ͳת�������� */
	BD_DATA_FengJiZhuanSuLinMinDu,	/* ���ת�������� */
	BD_DATA_JiaoLongZhuanSuLinMinDu,	/* ����ת�������� */
	BD_DATA_GuoQiaoZhuanSuLinMinDu,	/* ����ת�������� */
	BD_DATA_ShengYunQiLinMinDu,		/* ������ת�������� */
	BD_DATA_BUTT
};

enum BIAO_DING_VALUE_TYPE_EN
{
	BD_VALUE_RealValue,
	BD_VALUE_Minimum,
	BD_VALUE_Median,
	BD_VALUE_Maximum,
	BD_VALUE_Offset,
	BD_VALUE_BUTT
};

enum GRAIN_TYPE_EN
{
		GT_YuMi,			/* ����*/
		GT_XiaoMai,			/* С��*/
		GT_ShuiDao,			/* ˮ��*/
		GT_DaDou,			/* ��*/
		GT_YouZiCai,		/* ���Ѳ�*/
		GT_DaMai,			/* ����*/
		GT_YanMai,			/* ����*/
		GT_HeiMai,			/* ����*/
		GT_BUTT,			/* ĩβ*/
};

#define MAX_BD_VALUE_NUM		BD_VALUE_BUTT
typedef struct 
{
	BiaoDingCmdDataProtocol 	m_BDCmdData;
	int m_XinZouJubing[MAX_BD_VALUE_NUM];
	int m_XinZouLaGan[MAX_BD_VALUE_NUM];	
	int m_AoBanJianXi[MAX_BD_VALUE_NUM];
	int m_ZhangJinLi_And_Sensitivity[BD_DATA_BUTT];
	int m_GeFuKuanDu;		/* ������*/
	int m_ZaiKeXiShu;		/* �غ�ϵ��*/
	int m_TiaoSuXiShu;		/* ����ϵ�� */
	int m_GuWuZhongLei;		/* �������� */
}BiaoDingDataRsp;


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
#if JINYEE_EXT	
	int ifch[10];
	char chgzm[10][100];//���Ĺ�����
#endif	
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
#if JINYEE_EXT	
	u8 sta_view;//�л�������ʷ��¼
	u8 flagYYYDS;//Һѹ�Ͷ���
#endif	
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
	u8 flagXLTcloseDCF;//ж��Ͳ�رյ�ŷ�
	u8 flagXLTopenDCF;//ж��Ͳ�򿪵�ŷ�
	u8 flagSCDCF;//ɲ����ŷ�
	u8 flagDCPower;//������Դ
	u8 flagYLDCF;//������ŷ�
	u8 flagmijiclr;//�׼�����
	u8 flagKD;//�յ���ʾ
	u16 speed;
	//ָʾ��ֵ
	int VolYL; //����
#if JINYEE_EXT	
	int StaYL;//��������״̬0�������� 1����· 2�����· 3�����쳣
#endif	
	int VolYeyayouwen;//Һѹ����
	int MIJI;//�׼ơ��������
	int SaLiangLV;//������ʧ��
	int GeChaheight;//���߶�
	int FTspeed;//����ת��
	int SYspeed;//����ת��
	int ZLspeed;//����ת��
	int HourSpeed;//ʱ��
	int VOLV;//��ص�ѹ
	int VolMIJISUM;//���׼ơ������
	int VolLICHENG;//���
	int VolMCL;//Ķ����
	int VolGTweith;//��̨���
	int VolShiWen;//����

	//���йɷ���Ӳ���
	u8 TJQ_type;//�ƽ����ֱ��ź�����
	int TJQ_Vol;//�ƽ����ֱ��ź�
	u8 XZB_type;//���߱��Ƹ��ź�����
	int XZB_Vol;//���߱��ź�
	int XZ_Speed_Sensor;//�����ٶȴ�����

	u8 PLT_OnOff_type;//����Ͳ�����ź�����
	int PLT_OnOff_Vol;//����Ͳ���ص�λ���ź�
	u8 PLT_Rotate_type;//����Ͳ��ת��λ���ź�����
	int PLT_Rotate_Vol;//����Ͳ��ת��λ���ź�
	int GT_Speed_sensor;//��̨ת���źŴ�����

	u8 GT_Turn_type;//��̨ת�����ź�����
	int GT_Turn_Vol;//��̨ת�����ź�
	u8 YYY_Press_type;//Һѹ��ѹ���������ź�����
	int YYY_Press_Vol;//Һѹ��ѹ���������ź�
	int GunTong_Speed_Sensor;//��Ͳת�ٴ������ź�

	u8 Guwu_damage;//����������
	u8 Guwu_water;//���ﺬˮ��
	int Guwu_Chanliang_Vol;//����Ķ����
	int GT_hight;//��̨�߶�
	int JuPan_Speed;//����ת��

	int Up_Trans1_Speed;//һ����ת��
	int Up_Trans2_Speed;//������ת��
	int Up_Trans3_Speed;//������ת��
	int BaHe_Speed;//�κ���ת��

	u8 DaoLiao_Pad_type;//���ϰ��λ���ź�����
	int DaoLiao_Pad_Vol;//���ϰ��λ���ź�
	u8 Ao_Pad_type;//����λ�õ�λ���ź�����
	int Ao_Pad_Vol;//����λ�õ�λ���ź�
	int BaoPi_Speed_Sensor;//��Ƥ��ת���źŴ�����

	int Grass_Length;//��������
	int Grass_Weight;//��������
	int Grass_Single_Count;//�������μ���
	int BoCha_Speed;//����ת��

	int Fan_Speed;//���ת���ź�
	int Guwu_lose2;//������ʧ2
	int Guwu_lose1;//������ʧ1
	int Fuel_remaind;//ȼ������

	u8 HandPark_motor_type;//��ɲ��������������ź�����
	int HandPark_motor_Vol;//��ɲ��������������ź�
	int ZaYu_jiao_Vol;//��������������ź�
	int GuoQiao_Speed;//����ת���ź�

	u8 Clean_Fan_type;//�����������������ź�����
	int Clean_Fan_Vol;//�����������������ź�
	int DaoLun_Speed;//����ת��
	int SY_Fan_Speed;//ɢ�ȷ���ת��
	int WeiRu_Vol;//ι����
	int m_GZBitFlag;	/* ���ڱ�Ǹ��ֹ��ϵ� bit λ ,�ο� enum GZ_BIT_TYPE */
	int m_Speed[MAX_SPEED_TYPE_NUM];		/* ���� ��¼������ �������ĸ��������ٶ� */
	int m_extLampBitFlag;					/* ���пͻ���չָʾ�Ʊ��, �ο� LAMP_BIT_TYPE */
	double m_ZhuLiHeWorkTime;				/*	����Ϲ���ʱ��	*/
	int m_AoBanJianXi;						/*	�����϶	*/
	u8 m_DI[DID0_BUTT];						/*	������/����������*/
	u8 m_DO[DID0_BUTT];						/*  ������/��������� */
} RAM_CAN_sData;

typedef struct
{
	unsigned char  can_no;
#if JINYEE_EXT	
	u8 fdj_id;//����������ID
#endif	
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
#if JINYEE_EXT	
	float m_FuelVal;			/* �ͺ�ֵ INSTANT FUEL value */
	float m_InsFuelVal;		/* ˲���ͺ�ֵ INSTANT FUEL value */
	double m_EcuWorkTime;	/* ����������( ����) ʱ��*/
#endif	
	
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
int SendReqCmdToController(GUI_CMD_CFG_REQ_TYPE_EN enReqCmd,unsigned char ucData);
int GetRspDataFromController(BiaoDingDataRsp *_ptRsp);
void SetXinYanMachineModel(XINYAN_MACHINE_MODEL _enModel);
int GetXinYanMachineModel(void);
int GuiTransportInit();
int BiaoDingInit();	/* ����궨��ʼ������	*/
int BiaoDingExit();	/* �˳��궨���� */
int Cfg_sSingMileageClear();	/*	�������/�׼����� */
int Cfg_sVideoInputChn(VIDEO_INPUT_CHANNEL_EN _enViChn);	/* ����Ԥ����Ƶͨ��*/

/**********************************************************************
������:		GetHostSystemErrorInfo()
��	��:		��ȡepower ϵͳ������Ϣ
�Ρ���:	[in,out]		_ptErrorInfo    ������Ϣ�ṹ��
			[in ]			_iLen:		������Ϣ�ṹ�峤��(  С��MAX_ERROR_INFO_NUM )
����ֵ:	
		����0 :����ʵ�ʹ�����Ϣ��Ŀ
		����0 :ʵ�ʹ�����Ϣ��ĿΪ��
		����-1:��������
**********************************************************************/

int GetHostSystemErrorInfo(Info_SYS_ERR *_ptErrorInfo,int _iLen);


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
