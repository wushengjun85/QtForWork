#ifndef _LIB_SHM_H_
#define _LIB_SHM_H_

#ifdef __cplusplus
extern "C"{
#endif

#define	u8 unsigned char
#define	u16 unsigned short
#define	u32 unsigned int
#define RAM_CAN_fData                   "RAM_CAN_fData"         // CAN共享内存文件
#define RAM_CAN_ECU_fData               "RAM_CAN_ECU_fData"         // CANECU共享内存文件

#define CAN_LOCK                        1024+1               // CAN共享锁
/****************************************************/
//2017/4/1 wangxw add,由于金亿显示器用的老结构体,
//后期结构体有所修改,为了兼容金亿老结构体,特定义该宏用于区分;
#define JINYEE_EXT		1
/****************************************************/
enum LAMP_BIT_TYPE
{
	LAMP_BIT_ZhiLiHuiShou,			/*	籽粒回收	*/
	LAMP_BIT_LiangCangMan,			/*	粮仓满		*/
	LAMP_BIT_LiangTongBaiChu,		/*	粮筒摆出	*/
	LAMP_BIT_XieLiangZhong,			/*	卸粮中		*/
	LAMP_BIT_ShangShaiKaiKou,		/*	上筛开口	*/
	LAMP_BIT_XiaShaiKaiKou,			/*	下筛开口	*/
	LAMP_BIT_YeYaLvQing,			/*	液压滤清	*/
	LAMP_BIT_YeYaYouYa,				/*	液压油压	*/
	LAMP_BIT_CaoXiangXianZhi,		/* 	草箱限制	*/
	LAMP_BIT_BUTT
};

enum GZ_BIT_TYPE
{
	GZ_BIT_ZHUJI,			/* 主机故障 */
	GZ_BIT_FENGJI, 			/* 风机故障 */
	GZ_BIT_LIANGCANGGAI, 	/* 粮仓盖故障 */
	GZ_BIT_GUNTONG, 		/* 滚筒故障 */
	GZ_BIT_SHENGYUNQI, 		/* 升运器故障 */
	GZ_BIT_GUOQIAO, 		/* 过桥故障 */
	GZ_BIT_SHACHEZHIDONG, 	/* 刹车制动故障 */
	GZ_BIT_SHACHEPANMOSUN, 	/* 刹车盘磨损 */
	GZ_BIT_BUTT
};

#define SET_GZ_BIT(x,index)	( x |= 1 < index )			/* 设置 故障 bit 位 */
#define CLR_GZ_BIT(x,index)	( x &= ~(1 < index) )		/* 清除 故障 bit 位 */
#define CHK_GZ_BIT(x,index)	( x & (1 < index) )			/* 检测 故障 bit 位 */


#define MAX_SPEED_TYPE_NUM		15
enum SPEED_TYPE_EN
{
	SPEED_GUOQIAO,			/* 过桥转速 */
	SPEED_JIAOLONG,			/* 绞龙转速 */
	SPEED_GUNTONG,			/* 滚筒转速 */
	SPEED_FENGJI,			/* 风机转速 */
	SPEED_GETAI,			/* 割台转速 */	
	SPEED_JUPAN,			/* 锯盘转速 */
	SPEED_XINGZOU,			/* 时速/行走转速 */
	SPEED_BUTT		
};

/************************************************/
/* CAN 中间层数据传输结构 */
/************************************************/
//发动机厂家ID
typedef enum{
	yuchai,
	weichai
}Fdj_Cj_Id;

typedef struct
{
	int cnt;//接收SPN包书
	int if_data;//是否有数据
	int spn[10];
	int fmi[10];
#if JINYEE_EXT	
	int ifch[10];
	char chgzm[10][100];//中文故障码
#endif	
}CAN_SPN;

typedef struct
{
	unsigned char  can_no;
	u8 flagTXCS;//通信超时标志
	//指示标志:0,1
	//开关量 输入 
	u8 flagLeft;  //左转
	u8 flagBattery;//电瓶指示灯 充电指示灯
	u8 flagWidthlamp; //示宽灯
	u8 flagYG; //远光灯
	//u8 flagSW; //水温
	u8 flagJG; //近光灯
	u8 flagJY; //机油
	u8 flagLCM; //粮仓满
	u8 flagLCM_seven; //粮仓满70
	u8 flagGL; //过滤
	u8 flagKL; //空气滤
	u8 flagSS;//手刹
	u8 flagFDJYR; //发动机预热
	u8 flagPark;//停车
	u8 flagFDJGZ; //发动机故障
	u8 flagRight; //右转
	u8 flagDC;//倒车信号
#if JINYEE_EXT	
	u8 sta_view;//切换界面历史记录
	u8 flagYYYDS;//液压油堵塞
#endif	
	u8 flagYYMainSK;//液压主离合松开
	u8 flagYYMainZJ;//液压主离合张紧
	u8 flagBHLdown;//拔禾轮降低
	u8 flagBHLup;//拔河轮升
	u8 flagGTup;//割台升
	u8 flagGTdown;//割台降
	u8 flagfastspeed;//高速信号
	u8 flagXLTclose;//卸粮筒关闭
	u8 flagXLTopen;//卸粮筒打开
	u8 flagYSFL;//油水分离
	//u8 flagCD;//充电指示

	//开关量输出
	u8 flagBHLdownDCF;//拔禾轮降低电磁阀
	u8 flagBHLupDCF;//拔河轮升电磁阀
	u8 flagYYMainSKDCF;//液压主离合松开电磁阀
	u8 flagYYMainZJDCF;//液压主离合张紧电磁阀
	u8 flagGTupDCF;//割台升
	u8 flagGTdownDCF;//割台降
	u8 flagXLTcloseDCF;//卸粮筒关闭电磁阀
	u8 flagXLTopenDCF;//卸粮筒打开电磁阀
	u8 flagSCDCF;//刹车电磁阀
	u8 flagDCPower;//倒车电源
	u8 flagYLDCF;//溢流电磁阀
	u8 flagmijiclr;//米计清零
	u8 flagKD;//空挡标示
	u16 speed;
	//指示数值
	int VolYL; //油量
#if JINYEE_EXT	
	int StaYL;//油量故障状态
#endif	
	int VolYeyayouwen;//液压油温
	int MIJI;//米计
	int SaLiangLV;//撒粮损失率
	int GeChaheight;//割茬高度
	int FTspeed;//复脱转速
	int SYspeed;//升运转速
	int ZLspeed;//轴流转速
	int HourSpeed;//时速
	int VOLV;//电池电压
	int VolMIJISUM;//总米计
	int VolLICHENG;//里程
	int VolMCL;//亩产量
	int VolGTweith;//割台宽度
	int VolShiWen;//室温

	//新研股份添加部分
	u8 TJQ_type;//推进器手柄信号类型
	int TJQ_Vol;//推进器手柄信号
	u8 XZB_type;//行走泵推杆信号类型
	int XZB_Vol;//行走泵信号
	int XZ_Speed_Sensor;//行走速度传感器

	u8 PLT_OnOff_type;//抛料筒开关信号类型
	int PLT_OnOff_Vol;//抛料筒开关电位计信号
	u8 PLT_Rotate_type;//抛料筒旋转电位计信号类型
	int PLT_Rotate_Vol;//抛料筒旋转电位计信号
	int GT_Speed_sensor;//割台转速信号传感器

	u8 GT_Turn_type;//割台转向电机信号类型
	int GT_Turn_Vol;//割台转向电机信号
	u8 YYY_Press_type;//液压油压力传感器信号类型
	int YYY_Press_Vol;//液压油压力传感器信号
	int GunTong_Speed_Sensor;//滚筒转速传感器信号

	u8 Guwu_damage;//谷物破损率
	u8 Guwu_water;//谷物含水率
	int Guwu_Chanliang_Vol;//谷物亩产量
	int GT_hight;//割台高度
	int JuPan_Speed;//锯盘转速

	int Up_Trans1_Speed;//一升运转速
	int Up_Trans2_Speed;//二升运转速
	int Up_Trans3_Speed;//三升运转速
	int BaHe_Speed;//拔禾轮转速

	u8 DaoLiao_Pad_type;//导料板电位计信号类型
	int DaoLiao_Pad_Vol;//导料板电位计信号
	u8 Ao_Pad_type;//凹板位置电位计信号类型
	int Ao_Pad_Vol;//凹板位置电位计信号
	int BaoPi_Speed_Sensor;//薄皮机转速信号传感器

	int Grass_Length;//草捆长度
	int Grass_Weight;//草捆重量
	int Grass_Single_Count;//草捆单次计数
	int BoCha_Speed;//拨叉转速

	int Fan_Speed;//风机转速信号
	int Guwu_lose2;//谷物损失2
	int Guwu_lose1;//谷物损失1
	int Fuel_remaind;//燃油余量

	u8 HandPark_motor_type;//手刹电机电流传感器信号类型
	int HandPark_motor_Vol;//手刹电机电流传感器信号
	int ZaYu_jiao_Vol;//杂余绞龙传感器信号
	int GuoQiao_Speed;//过桥转速信号

	u8 Clean_Fan_type;//清洁风机驱动电机电流信号类型
	int Clean_Fan_Vol;//清洁风机驱动电机电流信号
	int DaoLun_Speed;//刀轮转速
	int SY_Fan_Speed;//散热风扇转速
	int WeiRu_Vol;//喂入量
	int m_GZBitFlag;	/* 用于标记各种故障的 bit 位 ,参考 enum GZ_BIT_TYPE */
	int m_Speed[MAX_SPEED_TYPE_NUM];		/* 用于 记录控制器 发过来的各个部件速度 */
	int m_extLampBitFlag;					/* 新研客户扩展指示灯标记, 参考 LAMP_BIT_TYPE */
	int m_ZhuLiHeWorkTime;					/*	主离合工作时间	*/
	int m_AoBanJianXi;						/*	凹板间隙	*/
} RAM_CAN_sData;

typedef struct
{
	unsigned char  can_no;
#if JINYEE_EXT	
	u8 fdj_id;//发动机厂家ID
#endif	
	u8 flagFDJYR_ECU; //发动机预热ECU
	u8 flagECU;//ecu
	u8 flagFDJGZ_ECU; //发动机故障ECU
	u8 flagYSFL_ECU;//油水分离ECU

	//指示数值
	int VolSW;//水温
	int VolYL; //油量
	int VolJYWD;//机油温度
	int VolJYYL;//机油压力
	int FDJ_speed;//发动机转速
#if JINYEE_EXT	
	int VolYH;//油耗
#endif	
	
	//SPN故障
	CAN_SPN spn_can;
} RAM_CAN_sData_ECU;



void Can_Ram_init();
void Can_Ram_Get(RAM_CAN_sData * RAM_CAN,RAM_CAN_sData_ECU * RAM_CAN_ECU);
void Can_Ram_Set(RAM_CAN_sData * RAM_CAN,RAM_CAN_sData_ECU * RAM_CAN_ECU);
void Can_set_spn_flag(int flag);
void Can_set_Fdj_id(int id);//设置发动机厂家ID，用于SPN中文查询
void Can_set_mijiclr_flag(int flag);
void Can_set_MCL_flag(int chanliang);
void Can_set_GTweith_flag(int weith);

//加共享内存锁
void lockshm();
//解共享内存锁
void unlockshm();
void Set_IO_H(int gpion);
void Set_IO_L(int gpion);
//int beep_Init();
//打开蜂鸣器
void beep_on();

//关闭蜂鸣器
void beep_off();
//打开蜂鸣器,短响
void beep_on_Bit();

//摄像头切换到V1
void cam_to_V1();
//摄像头切换到V2
void cam_to_V2();
//摄像头切换到V3
void cam_to_V3();
//信号切换到ARM
void sig_to_arm();
//打开蜂鸣器,长闪
//void beep_on_S_short();

//打开蜂鸣器,短闪
//void beep_on_S_long();

#ifdef __cplusplus
}
#endif 

#endif
