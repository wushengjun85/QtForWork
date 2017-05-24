#include "widget.h"
#include "ui_widget.h"
#include<QPainter>
#include<QPaintEvent>
#include<QDebug>
#include<QTime>
#include<QTimer>
#include<QtSql>
#include <QKeyEvent>
#include <QTextCodec>

#include"hwlib/libshm.h"

//故障码清除标志
bool flagGzmclear = false;
unsigned char clearItem;

QString trd;

int focuseflag;
uchar valueprogressbar;

//有光标移动的菜单选项
uchar LCClearMenuRow = 0;
uchar LCSwitchmatchineRow = 0;
uchar LCMachineModeMenu = 0;
uchar LCEngineSwitchMenu = 0;
bool LCBoolMachineModenu = true;


//2017.5.4  割台设置
int LCGetaiSetup = 1;
uint GeFuWidth = 3140;
uchar Zaihexishu = 5;
uchar Autospeed = 80;
//

//2017.4.7 add
uchar LCBiaoDingRow = 0;
uchar LCPiPeixingBiaoDing = 0;


uchar LCZhujiFault = 0;
uchar LCEngineFault = 0;
//2017.5.9
uint shoubingoffset = 200;
uint langanoffset = 100;


//2017.4.8
//标定 标志判断
uchar FlagShouBing = 0;
uchar FlagXingzouBeng = 0;
uchar FlagAoBanjianxi = 0;

//2017.5.24
uchar FlagShouBingBDFinish = 0;
uchar FlagXingzouBengBDFinish = 0;
uchar FlagAoBanjianxiBDFinish = 0;


//蜂鸣器状态标志
uchar flagbeep = 1;


//焦距焦点获取
bool f1;
bool f2;
bool f3;
bool f4;


//2017.4.6
//
//主离合
unsigned char zlh = 80;
QString strzlh = QString("%1").arg(zlh);
//卸粮离合
unsigned char xllh = 80;
QString strxllh = QString("%1").arg(xllh);
//过桥离合
unsigned char gqlh = 80;
QString strgqlh = QString("%1").arg(gqlh);

//滚筒
unsigned char gtzs = 10;
QString strgtzs = QString("%1").arg(gtzs);
//风机
unsigned char fjzs = 10;
QString strfjzs = QString("%1").arg(fjzs);
//搅龙
unsigned char jlzs = 10;
QString strjlzs = QString("%1").arg(jlzs);
//过桥
unsigned char gqzs = 10;
QString strgqzs = QString("%1").arg(gqzs);


//过渡变量 //临时变量

int tempzlh;
int tempxllh;
int tempgqlh;
int tempgtzs;
int tempfjzs;
int tempjlzs;
int tempgqzs;

//标志变量
bool FaZhiReadOK = true;
//bool FlagFaZhirecover = false;

//3秒内无变化函数
int ShoubingShijizhi;
int ShoubingTempShijizhi;
int XingzhoubengShijizhi;
int XingzhoubengTempShijizhi;
int AobanjianxiShijizhi;
int AobanjianxiTempShijizhi;

//2017.5.23
int shoubingzuixiao;
int shoubingzuida;
int shoubingzhongjian;

int xingzhouzuixiao;
int xingzhouzuida;
int xingzhouzhongjian;


bool FlagNext = false;
uchar ThreeOut;

//2017.4.28
bool tempflagShoubing = false;


//2017.5.16 处理小数点后2位进位问题
unsigned int shunshiyouhaoInt;
float shunshiyouhaoFloat;

long long xiaoshijiLongLong;
double    xiaoshijiDouble;



/*******************************************************************************************************************/
//2017.1.14 wsj
//uchar flagFrame;
//界面选择标志
enum uiFlag
{                                   /*对应stacked 页面页数*/
    xingZouWidget = 0, //行走主工作界面   0
    UserMenu,   //用户菜单               1
    MainMenu,  //主菜单                  2
    ClearMenu,      //清零菜单           3
    SystemMenu, //系统设置菜单            4
    SwitchMachineMenu,//机型选择菜单      5
    MachineModeMenu,//整机型号           6
    HelpMenu,      //帮助菜单            7
    DiagnosisMenu,//故障查询菜单          8
    EngineSwitchMenu,//发动机选择         9
    VideoSetupMenu,   //视频设置         10
    PipeixingbiaodingMenu,//匹配性标定    11
    FazhibiaodingMenu,    //阀值标定       12
    EngineFault,         //发动机故障查询   13
    ZhujiFault,           //主机故障查询    14
    JiQiXinXi,        //机器信息           15
    BiaoDing,          //标定菜单           16
    Shaomiao,              //扫码查询        17
    Getai              //割台参数设置        18
};
uiFlag flagwidget;

//从setup 界面返回上一级界面标志
struct flagSwitch
{
    uchar flagwidget;
    uchar flagwork;
};
flagSwitch flagswitch;

enum matchion
{
    YZB_3A_B = 0,
    YZT_10,
    YZB_4_5_7_8,
    //
    //2017.4.2
    JZ_3600,
    YZBT_5,
    YZT_5,
    S3000
};
matchion flagmatchion;


//发动机厂家选择
enum CJ
{
    YuCai = 0,
    WeiCai,
    XiCai,
    HangFa,
    DongfangHong
};
CJ CJSwitch = YuCai;

//unsigned int cjnum = 0;

/**************************/
//摄像头开始标志位
uchar flagvedio = 1;

enum flagvedioChange
{
    AV2 = 0,
    AV3
};
flagvedioChange flagcurrentvideo = AV2;
uchar flagyihuovideo;
uchar flagdbvideoCurrent;

uchar flagzhuqueren;//主屏确认标志

//设置超时标志
bool flagtimeout = false;
bool flagaction = false;
uchar flagtimeoutnum = 0;

/***************************************************************************************************/
//指针旋转变量
static float floatnu1 = 0;
float floatnu2 = 0.0;

int nu4;
uchar nu3;
float floatnu3;

uint nu2;
uint nu1;

int num = 0;
int numtmp = 0;

/***************************************************************************************************/

/*******************************************************************************************************************/

//故障码显示和油量状态显示
char AddSum[12][100] = {"0"};
//存储油量状态和通信故障状态
char YouAndTongxinArray[2][100] = {""};
char lengthYX;//存储油量状态和通信故障状态 的长度

char *p1 = "通信故障";
char *p2 = "油量开路";
char *p3 = "油量短路";
char *p4 = "油量异常";

 int flagjuzhongnum = 0;

 //故障码
 unsigned int i = 0;

 /**************************************************************************************************************/
 //挂到档返回时不显示故障码 变量设置
 //
 bool flagdaoche = false;
 unsigned char numdaoche = 0;


/*******************************************************************************************************************/

/*******************************************************************************************************************/

long long xiaoshiJi_m;//分钟
double xiaoshiJi_h;//小时
float fadongzhuansu; //发动机转速


//uchar flagadd = 1;//转速方向标志位
uchar flagaddnum = 1;//转速方向标志位
uchar flagnum;
uchar flagDelay;//延时标志
uchar DelayCount;//延时六秒


uchar DelayYLcounter;//油量延时10秒响一次
uchar Delagbeepoff;//关之前延时
uchar flagbeepzero = 0;
//uchar flagYs;//延时2秒 防止一上电出现 蜂鸣器一直响。

uint matchine[5] = {0}; //保存风机，复托器，升运器，等转速 的百分比
int ruby[3] = {0};
//频率量
ushort  shengyunqi =7;    //升运器
ushort  futuoqi =9;       //复脱器
ushort  zhouliuguntong=55;//轴流滚筒
ushort tuoliguntong=8;//脱粒滚筒转速

//米计 里程
//

double MIJILICHENG[3] = {0}; //米计 里程 状态标志
uint clearflag;//清零标志
uint  clearSave;//存储清零标志
uchar clearCount;

uint mijisum;//米计和， 用于显示
double licheng;//里程
int lichengsum;//里程和，用于显示


//水温 机油压力,电压数据
int NumSW;
float JYYL;
float DCDY;//电池电压

float YLBFB;//油量百分比

//闪烁标志
//

//2017.5.18
//
uchar shanshuoLiangshun;//洒粮损失闪烁
/*****************************************/

uchar shanshuoSW;//水温闪烁
uchar shanshuoJYYL;//机油压力闪烁
uchar shanshuoYL;//油量闪烁
uchar shanshuoYZYS;//油中有水
uchar shanshuoYYYW;//液压油温

uchar shanshuoLM;//粮满
uchar shanshuoSS;//手刹

uchar shangshuoChongdian;//充电

uchar shanshuoTXGZ;//通信故障

uchar shanshuozlzs;//轴流滚筒转速
uchar shanshuoftqzs;//复托器转速
uchar shanshuosyqzs;//升运器转速



uchar flagMijLic = 0;//米计里程切换标志

uchar j=0;
uchar jflag = 0;
uint mm=0;
uchar jjjflag = 0;
unsigned char  mybufflag[15] = {0};
unsigned char  myindex[15] = {0};

/**************************/

uchar Led = 0;
/**************************************************************************************************************/
uint bjd[4] = {0};
//uint kaku_tlgt = 88;
//uint kaku_syq = 77;
bool flag_bjd = true;


bool flagjiajia = true;
int startflag = 0;

int  tuoliguntong_zs = 80; //脱离滚筒转速  //轴流滚筒
int fenliguntong_zs = 80;//分离滚筒
int fj_zs = 80;//风机
int ftq_zs = 80;//复脱器
int syq_zs = 80; //升运器
int qsq_zs = 80; //切碎器
int gq_zs = 80;//过桥转速



int kaku_tlgt;//脱离滚筒转速   //轴流滚筒
int kaku_flgt;//分离滚筒
int kaku_fj;//风机
int kaku_ftq;//复脱器
int kaku_syq;//升运器

int kaku_gqzs;//过桥转速


int ka_tlgt;//脱离滚筒转速
int ka_flgt;//分离滚筒
int ka_fj;//风机
int ka_ftq;//复脱器
int ka_syq;//升运器
int ka_qsq;//切碎器
int ka_gqzs;//过桥转速

/**************************************************************************************************************/

////时间设置 变量
QString  Datesetup;
bool timeSetOK = false; //时间设置完毕标志
QString DateTimeSetup;


QString dateBuffer;
QString timeBuffer;
QDateTime MyDatetimeSetup;


//发动机故障码
long long spnItem[10];
unsigned char fmiItem[10];
QString gzmItem[10];
unsigned char un = 0;

//遍历fdjgz表
unsigned int fdjgzcount;

//主机故障码
unsigned char zjgzun = 0;
unsigned char IdItem[10];
QString zjMsItem[10];



//
//发动机厂家，机器型号，语言选择
//
unsigned int ConfigArray[3] = {0};
unsigned int ReadConfigArry[3] = {0};


//2017.5.21 闪烁
unsigned char shanshuoGunTong = 0;
unsigned char shanshuoShengyun = 0;
unsigned char shanshuoguoqiao = 0;
unsigned char shanshuofengji = 0;
//unsigned char shanshuoLiangchangman2 = 0;


/**************************************************************************************************************/

/**************************************************************************************************************/

RAM_CAN_sData cantest;
RAM_CAN_sData_ECU ecutest;


BiaoDingDataRsp biaoding;
/*******************************************************************************************************************/

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    setWindowFlags(windowFlags()|Qt::FramelessWindowHint|Qt::WindowTitleHint); //删除 最小化、最大化、关闭按钮

    #ifdef CAMERAFLAG
        //can 初始化
        Can_Ram_init();
        //摄像头初始化
        m_camerobj.Init(ui->label,NULL,HWE_PRODUCT_800X480_XINYAN);

    #endif

    timer_Main = new QTimer(this);   //声明一个定时器
    timer_Timeout = new QTimer(this);

    timer_xiaoshiji = new QTimer(); //声明小时计定时器
    timer_shanhua = new QTimer();
    timer_Licheng = new QTimer();//里程
    timergzm = new QTimer();//故障码
    timergzmTihuan = new QTimer();//故障码替换

    ThreeSecondNoChangeTimer = new QTimer();//3秒内无边化 定时器
    connect(ThreeSecondNoChangeTimer, SIGNAL(timeout()), this, SLOT(NoChangeFun()));  //连接信号槽，定时器超时触发窗体更新
    ThreeSecondNoChangeTimer->start(1000);


    connect(timer_Main, SIGNAL(timeout()), this, SLOT(update()));  //连接信号槽，定时器超时触发窗体更新
    connect(timer_Timeout,SIGNAL(timeout()),this,SLOT(timeoutfun()));
    connect(timergzm, SIGNAL(timeout()), this, SLOT(gzmslottest()));  //连接信号槽，定时器超时触发窗体更新
    connect(timer_Licheng,SIGNAL(timeout()),this,SLOT(Licheng()));//里程
    connect(timer_xiaoshiji,SIGNAL(timeout()),this,SLOT(xiaoshiji()));//小时计
    connect(timer_shanhua, SIGNAL(timeout()), this, SLOT(shanhua()));  //连接信号槽，定时器超时触发窗体更新


    //故障码替换
   connect(timergzmTihuan, SIGNAL(timeout()), this, SLOT(gzmTihuanslot()));  //连接信号槽，定时器超时触发窗体更新

    timer_Main->start(30);   //启动定时器
    //设置超时判断
    timer_Timeout->start(1000);

    timer_xiaoshiji->start(1000);//小时计
    timer_Licheng->start(1000);//里程
    timergzm->start(1000);//故障码//3000
    timer_shanhua->start(30);


    //滚动播放 很有用
   // m_timer = new QTimer(this);
   // connect(m_timer,  SIGNAL(timeout()),  this,  SLOT(myscroll()));
   //m_timer->start(300);


    timergzmTihuan->start(1000);//故障码替换显示  显示 “ ” 空//3s

    //过滤器安装
    ui->label_2->installEventFilter(this);
    ui->label_5->installEventFilter(this);

    ui->label_2->setAttribute(Qt::WA_PaintOutsidePaintEvent,true);
    ui->label_5->setAttribute(Qt::WA_PaintOutsidePaintEvent,true);


   /*************************************************************************************************/
    //2017.4.6
    //过滤器安装
    ui->lineEdit_23->installEventFilter(this);
    ui->lineEdit_24->installEventFilter(this);
    ui->lineEdit_25->installEventFilter(this);
    ui->lineEdit_26->installEventFilter(this);
    ui->lineEdit_27->installEventFilter(this);
    ui->lineEdit_28->installEventFilter(this);
    ui->lineEdit_29->installEventFilter(this);
    ui->lineEdit_30->installEventFilter(this);


    //2017.5.4
    ui->lineEdit_3->installEventFilter(this);
    ui->lineEdit_4->installEventFilter(this);
    ui->lineEdit_5->installEventFilter(this);
    ui->lineEdit_6->installEventFilter(this);

    ui->lineEdit_7->installEventFilter(this);


    //2017.4.22    //读取阀值设定数据库
    #if 0

     if(FaZhiReadOK)
     {
      //static unsigned char nn = 1;
      QTextCodec::setCodecForTr(QTextCodec::codecForLocale());//汉字显示
      QSqlDatabase db;
      if(QSqlDatabase::contains("qt_sql_default_connection"))
        db = QSqlDatabase::database("qt_sql_default_connection");
      else
        db = QSqlDatabase::addDatabase("QSQLITE");

     db.setDatabaseName("jy.db");
     if (!db.open())
     {
         qDebug()<<"open database failed ---"<<db.lastError().text()<<endl;
     }
     QSqlQuery query;
     #if 0
     bool ok = query.exec("create table FaZhiBingBD(ZLH INTEGER,XLLH INTEGER,GQLH INTEGER,LmdGTZS INTEGER,LmdFengJi INTEGER,LmdJiaoLong INTEGER,LmdGuoQiao INTEGER)");
     if (ok)
     {
         qDebug()<<"ceate table partition success"<<endl;
     }
     else
     {
         qDebug()<<"ceate table partition failed"<<endl;
     }
     #endif

#if 0
     //query.prepare("INSERT INTO FaZhiBingBD(ZLH, XLLH, GQLH,LmdGTZS,LmdFengJi,LmdJiaoLong,LmdGuoQiao) VALUES (:ZLH, :XLLH, :GQLH, :LmdGQZS, :LmdFengJi, :LmdJiaoLong, :LmdGuoQiao)");
     query.prepare("update FaZhiBingBD set ZLH = :ZLH,XLLH = :XLLH,GQLH = :GQLH,LmdGQZS = :LmdGQZS,LmdFengJi = :LmdFengJi,LmdJiaoLong = :LmdJiaoLong,LmdGuoQiao = :LmdGuoQiao");//where

     query.bindValue(":ZLH",10);
     query.bindValue(":XLLH", 11);
     query.bindValue(":GQLH", 12);
     query.bindValue(":LmdGTZS", 13);
     query.bindValue(":LmdFengJi", 14);
     query.bindValue(":LmdJiaoLong", 15);
     query.bindValue(":LmdGuoQiao", 16);
     query.exec();
#endif

    query.exec("select ZLH, XLLH, GQLH,LmdGTZS,LmdFengJi,LmdJiaoLong,LmdGuoQiao from FaZhiBingBD");
    while (query.next())
    {

      qDebug()<<"id("<<query.value(0).toInt()<<")  name:"<<query.value(1).toString()<<"  age:"<<query.value(2).toInt();
      tempzlh = query.value(0).toInt();
      tempxllh = query.value(1).toInt();
      tempgqlh = query.value(2).toInt();
      tempgtzs = query.value(3).toInt();
      tempfjzs = query.value(4).toInt();
      tempjlzs = query.value(5).toInt();
      tempgqzs = query.value(6).toInt();


    }
    query.exec(QObject::tr("drop FaZhiBingBD"));

    zlh  = tempzlh;
    xllh = tempxllh;
    gqlh = tempgqlh;
    gtzs = tempgtzs;
    fjzs = tempfjzs;
    jlzs = tempjlzs;
    gqzs = tempgqzs;

    //FaZhiReadOK = false;
}
    #endif

     //2017.5.2
     //2017.5.2 add wsj
     SendReqCmdToController(GUI_CMD_CFG_REQ_ALL,0);
     GetRspDataFromController(&biaoding);
#if 0

     //
     zlh = biaoding.m_ZhangJinLi_And_Sensitivity[BD_DATA_ZhuLiHeZhangJinLi];
     xllh = biaoding.m_ZhangJinLi_And_Sensitivity[BD_DATA_XieLiangLiHeZhangJinLi];
     gqlh = biaoding.m_ZhangJinLi_And_Sensitivity[BD_DATA_GuoQiaoLiHeZhangJinLi];
     gtzs = biaoding.m_ZhangJinLi_And_Sensitivity[BD_DATA_GunTongZhuanSuLinMinDu];
     fjzs = biaoding.m_ZhangJinLi_And_Sensitivity[BD_DATA_FengJiZhuanSuLinMinDu];
     jlzs = biaoding.m_ZhangJinLi_And_Sensitivity[BD_DATA_JiaoLongZhuanSuLinMinDu];
     gqzs = biaoding.m_ZhangJinLi_And_Sensitivity[BD_DATA_GuoQiaoZhuanSuLinMinDu];

     qDebug()<<"FAZHIBIAODING..............................."<<endl;
     qDebug()<<"zlh = "<<zlh;
     qDebug()<<"xllh = "<<xllh;
     qDebug()<<"gqlh = "<<gqlh;
     qDebug()<<"gtzs = "<<gtzs;
     qDebug()<<"fjzs = "<<fjzs;
     qDebug()<<"jlzs = "<<jlzs;
     qDebug()<<"gqzs = "<<gqzs;

#endif


    //2017.4.6
    //
    //主离合
    //int zlh = 80;
    QString strzlh = QString("%1").arg(zlh);
    //卸粮离合
    //int xllh = 80;
    QString strxllh = QString("%1").arg(xllh);
    //过桥离合
    //int gqlh = 80;
    QString strgqlh = QString("%1").arg(gqlh);

    //滚筒
    //int gtzs = 80;
    QString strgtzs = QString("%1").arg(gtzs);
    //风机
    //int fjzs = 80;
    QString strfjzs = QString("%1").arg(fjzs);
    //搅龙
    //int jlzs = 80;
    QString strjlzs = QString("%1").arg(jlzs);
    //过桥
    //int gqzs = 80;
    QString strgqzs = QString("%1").arg(gqzs);

    ui->lineEdit_23->setText(strzlh);
    ui->lineEdit_24->setText(strgtzs);
    ui->lineEdit_25->setText(strxllh);
    ui->lineEdit_26->setText(strfjzs);
    ui->lineEdit_27->setText(strgqlh);
    ui->lineEdit_28->setText(strjlzs);
    ui->lineEdit_29->setText(strgqzs);

/**********************************************************************************************/



/**********************************************************************************************/

    //2017.4.7
    //过滤器安装

    /*设置中文显示编码，否则为乱码*/
    QTextCodec::setCodecForCStrings( QTextCodec::codecForName("utf8"));

    ui->listWidget_6->installEventFilter(this);

    //标定选择
    QListWidgetItem * BiaoItem1 = new QListWidgetItem;
    QListWidgetItem * BiaoItem2 = new QListWidgetItem;
    QListWidgetItem * BiaoItem3 = new QListWidgetItem;

    BiaoItem1->setSizeHint(QSize(30, 52));  //每次改变Item的高度
    BiaoItem1->setText("匹配性标定");//

    BiaoItem2->setSizeHint(QSize(30, 52));  //每次改变Item的高度
    BiaoItem2->setText("阀值标定");//

    //2017.5.4
    BiaoItem3->setSizeHint(QSize(30, 52));  //每次改变Item的高度
    BiaoItem3->setText("收割参数设定");//

    ui->listWidget_6->insertItem(0,BiaoItem1);
    ui->listWidget_6->insertItem(1,BiaoItem2);
    ui->listWidget_6->insertItem(2,BiaoItem3);

/**************************************************************/

    //过滤器安装
    ui->lineEdit->installEventFilter(this);
    ui->lineEdit_2->installEventFilter(this);
    ui->dateTimeEdit->installEventFilter(this);
    ui->progressBar->installEventFilter(this);

    ui->listWidget->installEventFilter(this);
    ui->listWidget_2->installEventFilter(this);
    ui->listWidget_3->installEventFilter(this);
    ui->listWidget_4->installEventFilter(this);
    ui->listWidget_5->installEventFilter(this);


    //2017.5.4
    ui->listWidget_7->installEventFilter(this);
    //

    ui->tableWidget->installEventFilter(this);
    ui->tableWidget_2->installEventFilter(this);



    ui->progressBar->setRange(0,100);
    ui->progressBar->setValue(0);

//    ui->lineEdit->setAutoFillBackground(true);
//    ui->lineEdit->setFocusPolicy(Qt::StrongFocus);


//    /*设置中文显示编码，否则为乱码*/
//    QTextCodec::setCodecForCStrings( QTextCodec::codecForName( "utf8"));
    //清零 里程 米计
    QListWidgetItem * pItem1 = new QListWidgetItem;
    QListWidgetItem * pItem2 = new QListWidgetItem;
    QListWidgetItem * pItem3 = new QListWidgetItem;

    pItem1->setSizeHint(QSize(40, 43));  //每次改变Item的高度
    pItem1->setText("单次里程清零");//

    pItem2->setSizeHint(QSize(40, 43));  //每次改变Item的高度
    pItem2->setText("单次计数器清零");//

    pItem3->setSizeHint(QSize(40, 43));  //每次改变Item的高度
    pItem3->setText("单次计时器清零");//

    ui->listWidget->insertItem(0,pItem1);
    ui->listWidget->insertItem(1,pItem2);
    ui->listWidget->insertItem(2,pItem3);


    //机型选择
    QListWidgetItem * AItem1 = new QListWidgetItem;
    QListWidgetItem * AItem2 = new QListWidgetItem;
    //QListWidgetItem * pItem3 = new QListWidgetItem;

    AItem1->setSizeHint(QSize(30, 34));  //每次改变Item的高度
    AItem1->setText("整机型号");//

    AItem2->setSizeHint(QSize(30, 34));  //每次改变Item的高度
    AItem2->setText("发动机品牌");//

    ui->listWidget_2->insertItem(0,AItem1);
    ui->listWidget_2->insertItem(1,AItem2);

    //整机型号选择
    //机型选择
    QListWidgetItem * SItem1 = new QListWidgetItem;
    QListWidgetItem * SItem2 = new QListWidgetItem;
    QListWidgetItem * SItem3 = new QListWidgetItem;
    QListWidgetItem * SItem4 = new QListWidgetItem;
    QListWidgetItem * SItem5 = new QListWidgetItem;
    QListWidgetItem * SItem6 = new QListWidgetItem;

    //QListWidgetItem * pItem3 = new QListWidgetItem;

    SItem1->setSizeHint(QSize(30, 37));  //每次改变Item的高度
    SItem1->setText("4YZT-10");//

    SItem2->setSizeHint(QSize(30, 37));  //每次改变Item的高度
    SItem2->setText("4YZB-4/5/7/8");//

    SItem3->setSizeHint(QSize(30, 37));  //每次改变Item的高度
    SItem3->setText("4YZB-3A/B");//


    SItem4->setSizeHint(QSize(30, 37));  //每次改变Item的高度
    SItem4->setText("4JZ-3600");//

    SItem5->setSizeHint(QSize(30, 37));  //每次改变Item的高度
    SItem5->setText("4QZ-2200/2200A");//

    SItem6->setSizeHint(QSize(30, 37));  //每次改变Item的高度
    SItem6->setText("4YZB-6/4(560)");//


    ui->listWidget_3->insertItem(0,SItem1);
    ui->listWidget_3->insertItem(1,SItem2);
    ui->listWidget_3->insertItem(2,SItem3);
    ui->listWidget_3->insertItem(3,SItem4);
    ui->listWidget_3->insertItem(4,SItem5);
    ui->listWidget_3->insertItem(5,SItem6);


    //2017.5.15
    //整机型号选择
    //机型选择
    QListWidgetItem * TItem111 = new QListWidgetItem;
    QListWidgetItem * TItem222 = new QListWidgetItem;
    QListWidgetItem * TItem333 = new QListWidgetItem;
    QListWidgetItem * TItem444 = new QListWidgetItem;
    QListWidgetItem * TItem555 = new QListWidgetItem;
    QListWidgetItem * TItem666 = new QListWidgetItem;
    QListWidgetItem * TItem777 = new QListWidgetItem;
    QListWidgetItem * TItem888 = new QListWidgetItem;

    //QListWidgetItem * pItem3 = new QListWidgetItem;

    TItem111->setSizeHint(QSize(30, 28));  //每次改变Item的高度
    TItem111->setText("玉米");//

    TItem222->setSizeHint(QSize(30, 28));  //每次改变Item的高度
    TItem222->setText("小麦");//

    TItem333->setSizeHint(QSize(30, 28));  //每次改变Item的高度
    TItem333->setText("水稻");//


    TItem444->setSizeHint(QSize(30, 28));  //每次改变Item的高度
    TItem444->setText("大豆");//

    TItem555->setSizeHint(QSize(30, 28));  //每次改变Item的高度
    TItem555->setText("油菜籽");//

    TItem666->setSizeHint(QSize(30, 28));  //每次改变Item的高度
    TItem666->setText("大麦");//

    TItem777->setSizeHint(QSize(30, 28));  //每次改变Item的高度
    TItem777->setText("燕麦");//

    TItem888->setSizeHint(QSize(30, 28));  //每次改变Item的高度
    TItem888->setText("黑麦");//


    ui->listWidget_7->insertItem(0,TItem111);
    ui->listWidget_7->insertItem(1,TItem222);
    ui->listWidget_7->insertItem(2,TItem333);
    ui->listWidget_7->insertItem(3,TItem444);
    ui->listWidget_7->insertItem(4,TItem555);
    ui->listWidget_7->insertItem(5,TItem666);
    ui->listWidget_7->insertItem(6,TItem777);
    ui->listWidget_7->insertItem(7,TItem888);


    //整机型号选择
    //机型选择
    QListWidgetItem * TItem1 = new QListWidgetItem;
    QListWidgetItem * TItem2 = new QListWidgetItem;
    QListWidgetItem * TItem3 = new QListWidgetItem;
    QListWidgetItem * TItem4 = new QListWidgetItem;
    QListWidgetItem * TItem5 = new QListWidgetItem;
    QListWidgetItem * TItem6 = new QListWidgetItem;

    //QListWidgetItem * pItem3 = new QListWidgetItem;

    TItem1->setSizeHint(QSize(30, 37));  //每次改变Item的高度
    TItem1->setText("4YZBT-5");//

    TItem2->setSizeHint(QSize(30, 37));  //每次改变Item的高度
    TItem2->setText("4YZT-5");//

    TItem3->setSizeHint(QSize(30, 37));  //每次改变Item的高度
    TItem3->setText("4YZT-7/4LZ-8");//


    TItem4->setSizeHint(QSize(30, 37));  //每次改变Item的高度
    TItem4->setText("4QZ-3000/3000A");//

    TItem5->setSizeHint(QSize(30, 37));  //每次改变Item的高度
    TItem5->setText("4YZB-4A/B");//

    TItem6->setSizeHint(QSize(30, 37));  //每次改变Item的高度
    TItem6->setText("4YZ-3");//


    ui->listWidget_4->insertItem(0,TItem1);
    ui->listWidget_4->insertItem(1,TItem2);
    ui->listWidget_4->insertItem(2,TItem3);
    ui->listWidget_4->insertItem(3,TItem4);
    ui->listWidget_4->insertItem(4,TItem5);
    ui->listWidget_4->insertItem(5,TItem6);


    //
    //整机型号选择
    //机型选择
    QListWidgetItem * UItem1 = new QListWidgetItem;
    QListWidgetItem * UItem2 = new QListWidgetItem;
    QListWidgetItem * UItem3 = new QListWidgetItem;
    QListWidgetItem * UItem4 = new QListWidgetItem;
    QListWidgetItem * UItem5 = new QListWidgetItem;


    //QListWidgetItem * pItem3 = new QListWidgetItem;

    UItem1->setSizeHint(QSize(30, 42));  //每次改变Item的高度
    UItem1->setText("玉柴");//

    UItem2->setSizeHint(QSize(30, 42));  //每次改变Item的高度
    UItem2->setText("潍柴");//

    UItem3->setSizeHint(QSize(30, 42));  //每次改变Item的高度
    UItem3->setText("锡柴");//


    UItem4->setSizeHint(QSize(30, 42));  //每次改变Item的高度
    UItem4->setText("行发");//

    UItem5->setSizeHint(QSize(30, 42));  //每次改变Item的高度
    UItem5->setText("东方红");//


    ui->listWidget_5->insertItem(0,UItem1);
    ui->listWidget_5->insertItem(1,UItem2);
    ui->listWidget_5->insertItem(2,UItem3);
    ui->listWidget_5->insertItem(3,UItem4);
    ui->listWidget_5->insertItem(4,UItem5);




    //tablewidget
   // ui->tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setColumnWidth(1,198);

//    QTableWidgetItem *item0, *item1;
//    item0 = new QTableWidgetItem;
//    item1 = new QTableWidgetItem;

//    QString txt = QString("%1").arg(6);
//    item0->setText(txt);

//    QString txt2 = QString("%1").arg(9);
//    item1->setText(txt2);

//    ui->tableWidget->setItem(0,0,item0);
//    ui->tableWidget->setItem(1,0,item1);

        ui->tableWidget_2->setColumnWidth(1,60);
        ui->tableWidget_2->setColumnWidth(2,249);


        //2017.4.6
        ui->tableWidget_3->setColumnWidth(0,70);
        ui->tableWidget_3->setColumnWidth(1,74);
        ui->tableWidget_3->setColumnWidth(2,74);
        ui->tableWidget_3->setColumnWidth(3,79);
        ui->tableWidget_3->setColumnWidth(4,79);
        ui->tableWidget_3->setColumnWidth(5,70);

        ui->tableWidget_3->setRowHeight(0,43);
        ui->tableWidget_3->setRowHeight(1,43);
        ui->tableWidget_3->setRowHeight(2,43);

        //2017.4.8
        //匹配性标定
        ui->tableWidget_3->installEventFilter(this);
}


Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *)
{

    //can 接收
    Can_Ram_Get(&cantest,&ecutest);


    QPainter painter(this);
    #if 1
    QPixmap pix;
    //图片选择
    switch(flagwidget)
    {
        case xingZouWidget:

         //机型选择
        switch(flagmatchion)
        {
            case YZT_10:
            pix.load("./img/jiemian/YZT_10.bmp");
            ui->label_5->setStyleSheet("border-image: url(:/new/prefix1/img/icon/shuiwen.png);");

            break;
            case YZB_3A_B:
            pix.load("./img/jiemian/YZB_3A_B.bmp");
            ui->label_5->setStyleSheet("border-image: url(:/new/prefix1/img/icon/jiyouyali.png);");
            break;

            case YZB_4_5_7_8:
            pix.load("./img/jiemian/4YZB_4_5_7_8.bmp");
            //切换到YZBHaishan界面小表盘
            ui->label_5->setStyleSheet("border-image: url(:/new/prefix1/img/icon/jiyouyali.png);");
            break;

            //2017.4.2 add

            case JZ_3600:
            pix.load("./img/jiemian/JZ_3600.bmp");
            ui->label_5->setStyleSheet("border-image: url(:/new/prefix1/img/icon/shuiwen.png);");
            break;

            case YZBT_5:
            pix.load("./img/jiemian/YZBT_5.bmp");
            //切换到YZBHaishan界面小表盘
            ui->label_5->setStyleSheet("border-image: url(:/new/prefix1/img/icon/jiyouyali.png);");
            break;

            case YZT_5:
            pix.load("./img/jiemian/YZT_5.bmp");
            ui->label_5->setStyleSheet("border-image: url(:/new/prefix1/img/icon/shuiwen.png);");
            break;

            case S3000:
            pix.load("./img/jiemian/S3000.bmp");
            ui->label_5->setStyleSheet("border-image: url(:/new/prefix1/img/icon/jiyouyali.png);");
            break;

            default:
            break;
        }
        break;
        case SystemMenu:
        pix.load("./img/jiemian/SystemMenu.bmp");
        break;
        case MainMenu:
        pix.load("./img/jiemian/MainMenu.bmp");
        break;
        case UserMenu:
        pix.load("./img/jiemian/UserMenu.bmp");
        break;

        case MachineModeMenu:
        pix.load("./img/jiemian/machineswitch.bmp");
        break;

        case ClearMenu:
        pix.load("./img/jiemian/ClearMenu.bmp");
        break;

        case HelpMenu:
        pix.load("./img/jiemian/HelpMenu.bmp");
        break;

        case DiagnosisMenu:
        pix.load("./img/jiemian/DiagnosisMenu.bmp");
        break;

        case SwitchMachineMenu:
        pix.load("./img/jiemian/SwitchMachineMenu.bmp");
        break;

        case EngineSwitchMenu:
        pix.load("./img/jiemian/EngineSwitchMenu.bmp");
        break;

        case VideoSetupMenu:
        pix.load("./img/jiemian/VideoSetupMenu.bmp");
        break;

        case PipeixingbiaodingMenu:
        pix.load("./img/jiemian/PipeixingbiaodingMenu.bmp");
        break;


        case FazhibiaodingMenu:
        pix.load("./img/jiemian/FazhibiaodingMenu.bmp");
        break;

        case EngineFault:
        pix.load("./img/jiemian/EngineFault.bmp");
        break;

        case ZhujiFault:
        pix.load("./img/jiemian/ZhujiFault.bmp");
        break;

        case JiQiXinXi:
        pix.load("./img/jiemian/JiQiXinXi.bmp");
        break;

        case BiaoDing:
        pix.load("./img/jiemian/BiaoDing.bmp");
        break;

        case Shaomiao:
        pix.load("./img/jiemian/Shaomiao.bmp");
        break;

        //2017.5.4
        case Getai:
        pix.load("./img/jiemian/Getai.bmp");//Getai
        break;

        default:
        break;
    }
    painter.drawPixmap(0,0,800,480,pix);

#endif

    /**************************************************************************************************************/
    //2017.1.18
    //摄像头 监控画面
#ifdef CAMERAFLAG


#if 1
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());//汉字显示
    QSqlDatabase db;
    if(QSqlDatabase::contains("qt_sql_default_connection"))
      db = QSqlDatabase::database("qt_sql_default_connection");
    else
      db = QSqlDatabase::addDatabase("QSQLITE");

   db.setDatabaseName("jy.db");
   if (!db.open())
   {
       qDebug()<<"open database failed ---"<<db.lastError().text()<<endl;
   }
   QSqlQuery query;
   #if 0
   bool ok = query.exec("create table otherflag(item1 INTEGER,item2 INTEGER,item3 INTEGER)");
   if (ok)
   {
       qDebug()<<"ceate table partition success"<<endl;
   }
   else
   {
       qDebug()<<"ceate table partition failed"<<endl;
   }
   #endif

   //query.prepare("INSERT INTO otherflag(item1, item2, item3) VALUES (:item1, :item2, :item3)");
#if 0
   query.prepare("update otherflag set item1 = :item1,item2 = :item2,item3 = :item3");//where

   query.bindValue(":item1",0);
   query.bindValue(":item2", 11);
   query.bindValue(":item3", 66);

   query.exec();
#endif

 query.exec("select item1, item2, item3 from otherflag");//
 while (query.next())
 {
    //qDebug()<<"item1("<<query.value(0).toInt()<<")  item2:"<<query.value(1).toString()<<"  item2:"<<query.value(2).toInt();
    flagdbvideoCurrent = query.value(0).toInt();
    //qDebug()<<""<<endl;
 }

  //query.exec(QObject::tr("drop otherflag"));

#endif

    #if 1
        if(flagwidget == xingZouWidget)
        {
            //if(flagcurrentvideo == AV2)
            if(flagdbvideoCurrent == 0)
            {
                //qDebug()<<"xingZouWidget ............AV2........";
                m_camerobj.Jobs_Monitor(CAMERA_AV_2);      /*作业监控*///CAMERA_AV_3
            }
            //else if(flagcurrentvideo == AV3)
            else if(flagdbvideoCurrent == 1)
            {
                 //qDebug()<<"xingZouWidget ............AV3........";
                m_camerobj.Jobs_Monitor(CAMERA_AV_3);      /*作业监控*///
            }
        }
        //add 2017.3.27
        else if(flagwidget == VideoSetupMenu)
        {
            //if(flagcurrentvideo == AV2)
            if(flagdbvideoCurrent == 0)
            {
                 //qDebug()<<"VideoSetupMenu ............AV2........";
                m_camerobj.Jobs_Monitor(CAMERA_AV_2);      /*作业监控*///CAMERA_AV_3
            }
            //else if(flagcurrentvideo == AV3)
            else if(flagdbvideoCurrent == 1)
            {
                 //qDebug()<<"VideoSetupMenu ............AV3........";
                m_camerobj.Jobs_Monitor(CAMERA_AV_3);      /*作业监控*///
            }
        }
    #endif
#endif

    /**************************************************************************************************************/
#if 1
        if(flagwidget == xingZouWidget)
           {

            /*******************************************************************************************************/
            //
            //
            //2017.3.11
            //读数据库

                //语言选择 发动机厂家 机器型号
                //

            #if 1
                QTextCodec::setCodecForTr(QTextCodec::codecForLocale());//汉字显示
                QSqlDatabase db;
                if(QSqlDatabase::contains("qt_sql_default_connection"))
                  db = QSqlDatabase::database("qt_sql_default_connection");
                else
                  db = QSqlDatabase::addDatabase("QSQLITE");

               db.setDatabaseName("jy.db");
               if (!db.open())
               {
                   qDebug()<<"open database failed ---"<<db.lastError().text()<<endl;
               }
               QSqlQuery query;

             query.exec("select cjswitch, engineswitch, langswitch from config");
             while (query.next())
             {
                ConfigArray[0] = query.value(0).toInt();
                ConfigArray[1] = query.value(1).toInt();
                ConfigArray[2] = query.value(2).toInt();
                //qDebug()<<"ConfigArray(0)"<<query.value(0).toInt()<<"ConfigArray[1]:"<<query.value(1).toString()<<"ConfigArray[2]:"<<query.value(2).toInt();

             }

              query.exec(QObject::tr("drop config"));

            #endif

            switch(ConfigArray[1])
            {
                case 0:
                flagmatchion = YZB_3A_B;
                ui->label_19->setText("4YZB-3A/B  4YZB-4A/B");
                break;
                case 1:
                flagmatchion = YZT_10;
                ui->label_19->setText("4YZT-10");
                break;
                case 2:
                flagmatchion = YZB_4_5_7_8;
                ui->label_19->setText("4YZB-4/5/7/8");
                break;

                case 3:
                flagmatchion = JZ_3600;
                ui->label_19->setText("4JZ-3600");
                break;

                case 4:
                flagmatchion = YZBT_5;

                ui->label_19->setText("4YZT-5/8");
                break;

                case 5:
                flagmatchion = YZT_5;
                ui->label_19->setText("4YZT-5");
                break;


                case 6:
                flagmatchion = S3000;
                ui->label_19->setText("S3000/S3000A");
                break;

                default:
                break;
            }

             //机型选择
            if(flagmatchion == YZT_10)
            {
               //int side = qMin(width(), height());  //绘制的范围(宽、高中最小值)

               painter.setRenderHint(QPainter::Antialiasing);//绘制的图像反锯齿
               //painter.translate(width() / 2, height() / 2);//重新定位坐标起始点，把坐标原点放到窗体的中央

               //painter.translate(405, 184);//重新定位坐标起始点，把坐标原点放到窗体的中央
                painter.translate(210, 363);//重新定位坐标起始点，把坐标原点放到窗体的中央
               //painter.scale(side / 400.0, side / 300.0);//设定画布的边界,用窗体宽高的最小值来计算时钟的大小，防止窗体拉伸导致的时钟变形以及显示不全

               //下面两个数组用来定义表针的两个顶点，以便后面的填充
               static const QPoint hourHand[4] = {
                   QPoint(8, 0),
                   QPoint(-8,0),
                   QPoint(-1.5, -160),
                   QPoint(1.5, -160)
               };
               static const QPoint minuteHand[4] = {
                   QPoint(4, 0),
                   QPoint(-4, 0),
                   QPoint(-1, -55),
                   QPoint(1, -55)
               };

               //油压

               painter.setPen(Qt::NoPen);//填充时针，不需要边线所以NoPen
               painter.setBrush(Qt::red);
               painter.setRenderHint(QPainter::Antialiasing, true);
               painter.save();
               painter.rotate(-114.5);
               painter.rotate(228*floatnu3);//floatnu1

               painter.drawConvexPolygon(minuteHand, 4);  //填充分针部分
               painter.restore();

               /***********************************************/
               //2016.6.25   画白圈
               painter.setBrush(Qt::black); //画上中心原点/home/vmuser/qtworkplace/chanpin/img2 darkGray
               painter.save();
               painter.drawEllipse(QPoint(0,0),13,13);
               painter.restore();

               //画白圈
               /***********************************************/

               painter.setBrush(Qt::darkGray);//画上中心原点/home/vmuser/qtworkplace/chanpin/img2
               painter.save();
               painter.drawEllipse(QPoint(0,0),10,10);
               painter.restore();


               //风机转速
               painter.translate(377,1);//重新定位坐标起始点，把坐标原点放到窗体的中央
               //painter.scale(side / 400.0, side / 300.0);

               painter.setPen(Qt::NoPen);
               painter.setBrush(Qt::red);
               painter.setRenderHint(QPainter::Antialiasing, true);
               painter.save();

               //painter.rotate(6.0 *time.second());  //设旋转(角度 = 6° * (分钟 + 秒 / 60))
               painter.rotate(-114.5);
               //painter.rotate(8*nu3);
               painter.rotate(7.6*nu1);//



               //painter.rotate(4.0 );  //设旋转(角度 = 6° * (分钟 + 秒 / 60))*shisu
               //内测用
               /****************************************************************************/
               //qDebug()<<"time: "<<time.second()<<endl;

               /****************************************************************************/

               painter.drawConvexPolygon(minuteHand, 4);  //填充分针部分
               painter.setRenderHint(QPainter::Antialiasing, true);
               painter.restore();

               /***********************************************/
               //2016.6.25   画白圈
               painter.setBrush(Qt::black); //画上中心原点/home/vmuser/qtworkplace/chanpin/img2
               painter.save();
               painter.drawEllipse(QPoint(0,0),13,13);
               painter.restore();

               //画白圈
               /***********************************************/


               painter.setBrush(Qt::darkGray);
               painter.save();//画上中心原点
               painter.drawEllipse(QPoint(0,0),10,10);
               painter.restore();

               //KM/H
               painter.translate(-187,-35);//重新定位坐标起始点，把坐标原点放到窗体的中央
               //painter.scale(side / 400.0, side / 300.0);

               painter.setPen(Qt::NoPen);
               painter.setBrush(Qt::red);
               painter.setRenderHint(QPainter::Antialiasing, true);
               painter.save();

               //painter.rotate(6.0 *time.second());  //设旋转(角度 = 6° * (分钟 + 秒 / 60))
               painter.rotate(-114);
               painter.rotate(7.6*nu3);//



               //painter.rotate(4.0 );  //设旋转(角度 = 6° * (分钟 + 秒 / 60))*shisu
               //内测用
               /****************************************************************************/
               //qDebug()<<"time: "<<time.second()<<endl;

               /****************************************************************************/

               painter.drawConvexPolygon(minuteHand, 4);  //填充分针部分
               painter.setRenderHint(QPainter::Antialiasing, true);
               painter.restore();

               /***********************************************/
               //2016.6.25   画白圈
               painter.setBrush(Qt::black); //画上中心原点/home/vmuser/qtworkplace/chanpin/img2
               painter.save();
               painter.drawEllipse(QPoint(0,0),13,13);
               painter.restore();

               //画白圈
               /***********************************************/


               painter.setBrush(Qt::darkGray);
               painter.save();//画上中心原点
               painter.drawEllipse(QPoint(0,0),10,10);
               painter.restore();

               //处理图片闪烁
               painter.translate(-390,-226);//平移到左边角

               //喂入
               QPainter paintShanshuo_W(this);
               QPixmap pixShanshuo_W;
//               pixShanshuo_W.load("./img/weiruliang/09.png");//07.jpg
//               paintShanshuo_W.drawPixmap(10,110,28,121,pixShanshuo_W);

               //qDebug()<<"cantest.WeiRu_Vol: "<<cantest.WeiRu_Vol<<endl;
               switch(cantest.WeiRu_Vol)
               {
                   case 1:
                   pixShanshuo_W.load("./img/weiruliang/10.png");//07.jpg
                   paintShanshuo_W.drawPixmap(10,110,28,121,pixShanshuo_W);
                   break;
                   case 2:
                   pixShanshuo_W.load("./img/weiruliang/09.png");//07.jpg
                   paintShanshuo_W.drawPixmap(10,110,28,121,pixShanshuo_W);
                   break;

                   case 3:
                   pixShanshuo_W.load("./img/weiruliang/08.png");//07.jpg
                   paintShanshuo_W.drawPixmap(10,110,28,121,pixShanshuo_W);
                   break;

                   case 4:
                   pixShanshuo_W.load("./img/weiruliang/07.png");//07.jpg
                   paintShanshuo_W.drawPixmap(10,110,28,121,pixShanshuo_W);
                   break;

                   case 5:
                   pixShanshuo_W.load("./img/weiruliang/06.png");//07.jpg
                   paintShanshuo_W.drawPixmap(10,110,28,121,pixShanshuo_W);
                   break;

                   case 6:
                   pixShanshuo_W.load("./img/weiruliang/05.png");//07.jpg
                   paintShanshuo_W.drawPixmap(10,110,28,121,pixShanshuo_W);
                   break;

                   case 7:
                   pixShanshuo_W.load("./img/weiruliang/04.png");//07.jpg
                   paintShanshuo_W.drawPixmap(10,110,28,121,pixShanshuo_W);
                   break;

                   case 8:
                   pixShanshuo_W.load("./img/weiruliang/03.png");//07.jpg
                   paintShanshuo_W.drawPixmap(10,110,28,121,pixShanshuo_W);
                   break;

                   case 9:
                   pixShanshuo_W.load("./img/weiruliang/02.png");//07.jpg
                   paintShanshuo_W.drawPixmap(10,110,28,121,pixShanshuo_W);
                   break;

                   case 10:
                   pixShanshuo_W.load("./img/weiruliang/01.png");//07.jpg
                   paintShanshuo_W.drawPixmap(10,110,28,121,pixShanshuo_W);
                   break;

               }




               //粮损
//               pixShanshuo_W.load("./img/liangshun/06.png");//07.jpg
//               paintShanshuo_W.drawPixmap(760,110,27,120,pixShanshuo_W);

               switch(cantest.SaLiangLV)
               {
                   case 1:
                   pixShanshuo_W.load("./img/liangshun/06.png");//07.jpg
                   paintShanshuo_W.drawPixmap(760,110,27,120,pixShanshuo_W);
                   break;

                   case 2:
                   pixShanshuo_W.load("./img/liangshun/05.png");//07.jpg
                   paintShanshuo_W.drawPixmap(760,110,27,120,pixShanshuo_W);
                   break;

                   case 3:
                   pixShanshuo_W.load("./img/liangshun/04.png");//07.jpg
                   paintShanshuo_W.drawPixmap(760,110,27,120,pixShanshuo_W);
                   break;

                   case 4:
                   pixShanshuo_W.load("./img/liangshun/03.png");//07.jpg
                   paintShanshuo_W.drawPixmap(760,110,27,120,pixShanshuo_W);
                   break;

                   case 5:
                   pixShanshuo_W.load("./img/liangshun/02.png");//07.jpg
                   paintShanshuo_W.drawPixmap(760,110,27,120,pixShanshuo_W);
                   break;

                   case 6:
                   pixShanshuo_W.load("./img/liangshun/01.png");//07.jpg
                   paintShanshuo_W.drawPixmap(760,110,27,120,pixShanshuo_W);
                   break;

               }

               //油量
//               pixShanshuo_W.load("./img/ranyou/07.png");//07.jpg
//               paintShanshuo_W.drawPixmap(10,275,27,118,pixShanshuo_W);

               switch(cantest.VolYL)
               {
                case 1:
                pixShanshuo_W.load("./img/ranyou/08.png");//07.jpg
                 paintShanshuo_W.drawPixmap(10,275,27,118,pixShanshuo_W);
                break;
               case 2:
               pixShanshuo_W.load("./img/ranyou/07.png");//07.jpg
                paintShanshuo_W.drawPixmap(10,275,27,118,pixShanshuo_W);
               break;
               case 3:
               pixShanshuo_W.load("./img/ranyou/06.png");//07.jpg
                paintShanshuo_W.drawPixmap(10,275,27,118,pixShanshuo_W);
               break;
               case 4:
               pixShanshuo_W.load("./img/ranyou/05.png");//07.jpg
                paintShanshuo_W.drawPixmap(10,275,27,118,pixShanshuo_W);
               break;
               case 5:
               pixShanshuo_W.load("./img/ranyou/04.png");//07.jpg
                paintShanshuo_W.drawPixmap(10,275,27,118,pixShanshuo_W);
               break;
               case 6:
               pixShanshuo_W.load("./img/ranyou/03.png");//07.jpg
                paintShanshuo_W.drawPixmap(10,275,27,118,pixShanshuo_W);
               break;
               case 7:
               pixShanshuo_W.load("./img/ranyou/02.png");//07.jpg
                paintShanshuo_W.drawPixmap(10,275,27,118,pixShanshuo_W);
               break;
               case 8:
               pixShanshuo_W.load("./img/ranyou/01.png");//07.jpg
                paintShanshuo_W.drawPixmap(10,275,27,118,pixShanshuo_W);
               break;

               }


               //凹槽
//               pixShanshuo_W.load("./img/aocao/05.png");//07.jpg
//               paintShanshuo_W.drawPixmap(760,275,28,119,pixShanshuo_W);

               switch(cantest.m_AoBanJianXi)
               {
                    case 1:
                    pixShanshuo_W.load("./img/aocao/05.png");//07.jpg
                    paintShanshuo_W.drawPixmap(760,275,28,119,pixShanshuo_W);

                    break;
                   case 2:
                   pixShanshuo_W.load("./img/aocao/04.png");//07.jpg
                   paintShanshuo_W.drawPixmap(760,275,28,119,pixShanshuo_W);

                   break;
                   case 3:
                   pixShanshuo_W.load("./img/aocao/03.png");//07.jpg
                   paintShanshuo_W.drawPixmap(760,275,28,119,pixShanshuo_W);

                   break;
                   case 4:
                   pixShanshuo_W.load("./img/aocao/02.png");//07.jpg
                   paintShanshuo_W.drawPixmap(760,275,28,119,pixShanshuo_W);

                   break;
                   case 5:
                   pixShanshuo_W.load("./img/aocao/01.png");//07.jpg
                   paintShanshuo_W.drawPixmap(760,275,28,119,pixShanshuo_W);

                   break;
               }



           //报警灯

          QPainter paintdeng(this);
          QPixmap pixdeng;
          //左转灯
          if(cantest.flagLeft)
          {
              pixdeng.load("./img/dengshan/01.png");//
              paintdeng.drawPixmap(5,415,49,55,pixdeng);//正上方位置显示的图标
          }
          //发动机故障
          if(ecutest.flagFDJGZ_ECU)
          {
              pixdeng.load("./img/dengshan/14.png");//
              paintdeng.drawPixmap(73,435,36,23,pixdeng);//正上方位置显示的图标
          }
          //充电指示灯
          if(cantest.flagBattery)
          {
              pixdeng.load("./img/dengshan/17.png");//
              paintdeng.drawPixmap(118,434,34,24,pixdeng);//正上方位置显示的图标
          }
          //水温
          if(shanshuoSW)
          {
              pixdeng.load("./img/dengshan/09.png");//
              paintdeng.drawPixmap(161,432,31,28,pixdeng);//正上方位置显示的图标
          }
          //油压
          if(shanshuoJYYL)
          {
              pixdeng.load("./img/dengshan/12.png");//
              paintdeng.drawPixmap(200,436,39,20,pixdeng);//正上方位置显示的图标
          }
          //油量
          if(shanshuoYL)
          {
              pixdeng.load("./img/dengshan/10.png");//
              paintdeng.drawPixmap(248,430,24,28,pixdeng);//正上方位置显示的图标
          }
          //手刹
          if(cantest.flagSS)
          {
              pixdeng.load("./img/dengshan/13.png");//
              paintdeng.drawPixmap(278,433,37,29,pixdeng);//正上方位置显示的图标
          }
          //远光
          if(cantest.flagYG)
          {
              pixdeng.load("./img/dengshan/02.png");//
              paintdeng.drawPixmap(322,434,38,23,pixdeng);//正上方位置显示的图标
          }
          //示宽灯
          if(cantest.flagWidthlamp)
          {
              pixdeng.load("./img/dengshan/04.png");//
              paintdeng.drawPixmap(367,434,43,24,pixdeng);//正上方位置显示的图标
          }
          //近光灯
          if(cantest.flagJG)
          {
              pixdeng.load("./img/dengshan/03.png");//
              paintdeng.drawPixmap(418,433,37,27,pixdeng);//正上方位置显示的图标
          }
          //发动机预热灯
          if(ecutest.flagFDJYR_ECU)
          {
              pixdeng.load("./img/dengshan/11.png");//
              paintdeng.drawPixmap(463,434,37,23,pixdeng);//正上方位置显示的图标
          }
          //籽粒回收满
           if(CHK_GZ_BIT(cantest.m_extLampBitFlag,LAMP_BIT_ZhiLiHuiShou))
          {
              pixdeng.load("./img/dengshan/15.png");//
              paintdeng.drawPixmap(509,430,32,32,pixdeng);//正上方位置显示的图标
          }
          //粮仓满
          if(CHK_GZ_BIT(cantest.m_extLampBitFlag,LAMP_BIT_LiangCangMan))
          {
              pixdeng.load("./img/dengshan/08.png");//
              paintdeng.drawPixmap(550,435,29,20,pixdeng);//正上方位置显示的图标
          }
          //燃油进水指示灯
          if(shanshuoYZYS)
          {
              pixdeng.load("./img/dengshan/07.png");//
              paintdeng.drawPixmap(586,432,24,28,pixdeng);//正上方位置显示的图标
          }
          //液压油压力
          if(CHK_GZ_BIT(cantest.m_extLampBitFlag,LAMP_BIT_YeYaYouYa))
          {
              pixdeng.load("./img/dengshan/99.png");//
              paintdeng.drawPixmap(616,432,15,28,pixdeng);//正上方位置显示的图标
          }
          //空滤灯
          if(cantest.flagKL)
          {
              pixdeng.load("./img/dengshan/05.png");//
              paintdeng.drawPixmap(640,430,32,32,pixdeng);//正上方位置显示的图标
          }
          //主机故障灯
          if(CHK_GZ_BIT(cantest.m_GZBitFlag,GZ_BIT_ZHUJI))
          {
              pixdeng.load("./img/dengshan/06.png");//
              paintdeng.drawPixmap(680,430,44,29,pixdeng);//正上方位置显示的图标
          }
          //右转灯
          if(cantest.flagRight)
          {
              pixdeng.load("./img/dengshan/18.png");//
              paintdeng.drawPixmap(740,415,49,55,pixdeng);//正上方位置显示的图标
          }



          //主界面中央灯区
          //粮筒摆出
          if(CHK_GZ_BIT(cantest.m_extLampBitFlag,LAMP_BIT_LiangTongBaiChu))
          {
              pixdeng.load("./img/zhujiemianicon/01.png");//
              paintdeng.drawPixmap(255,266,30,19,pixdeng);//正上方位置显示的图标
          }
          //过桥故障
          if(CHK_GZ_BIT(cantest.m_GZBitFlag,GZ_BIT_GUOQIAO))
          {
              pixdeng.load("./img/zhujiemianicon/02.png");//
              paintdeng.drawPixmap(307,258,32,29,pixdeng);//正上方位置显示的图标
          }
          //风机故障
          if(CHK_GZ_BIT(cantest.m_GZBitFlag,GZ_BIT_FENGJI))
          {
              pixdeng.load("./img/zhujiemianicon/03.png");//
              paintdeng.drawPixmap(273,281,31,32,pixdeng);//正上方位置显示的图标
          }

          //滚筒故障
          if(CHK_GZ_BIT(cantest.m_GZBitFlag,GZ_BIT_GUNTONG))
          {
              pixdeng.load("./img/zhujiemianicon/04.png");//
              paintdeng.drawPixmap(288,322,31,28,pixdeng);//正上方位置显示的图标
          }
          //刹车盘磨损
           if(CHK_GZ_BIT(cantest.m_GZBitFlag,GZ_BIT_SHACHEPANMOSUN))
          {
              pixdeng.load("./img/zhujiemianicon/05.png");//
              paintdeng.drawPixmap(294,355,30,24,pixdeng);//正上方位置显示的图标
          }
          //升运器故障
          if(CHK_GZ_BIT(cantest.m_GZBitFlag,GZ_BIT_SHENGYUNQI))
          {
              pixdeng.load("./img/zhujiemianicon/06.png");//
              paintdeng.drawPixmap(463,258,31,25,pixdeng);//正上方位置显示的图标
          }

          //卸粮中
         if(CHK_GZ_BIT(cantest.m_extLampBitFlag,LAMP_BIT_XieLiangZhong))
          {
              pixdeng.load("./img/zhujiemianicon/07.png");//
              paintdeng.drawPixmap(513,260,34,24,pixdeng);//正上方位置显示的图标
          }
          //粮仓盖
          if(CHK_GZ_BIT(cantest.m_GZBitFlag,GZ_BIT_LIANGCANGGAI))
          {
              pixdeng.load("./img/zhujiemianicon/08.png");//
              paintdeng.drawPixmap(499,292,27,23,pixdeng);//正上方位置显示的图标
          }
          //液压滤清
          if(CHK_GZ_BIT(cantest.m_extLampBitFlag,LAMP_BIT_YeYaLvQing))
          {
              pixdeng.load("./img/zhujiemianicon/09.png");//
              paintdeng.drawPixmap(490,319,16,28,pixdeng);//正上方位置显示的图标
          }
          //刹车制动故障
          if(CHK_GZ_BIT(cantest.m_GZBitFlag,GZ_BIT_SHACHEZHIDONG))
          {
              pixdeng.load("./img/zhujiemianicon/10.png");//
              paintdeng.drawPixmap(475,355,31,24,pixdeng);//正上方位置显示的图标
          }

         }//end of if(flagmatchion == YZT_10)
         else if(flagmatchion == YZB_3A_B)
         {
                //int side = qMin(width(), height());  //绘制的范围(宽、高中最小值)

                painter.setRenderHint(QPainter::Antialiasing);//绘制的图像反锯齿
                //painter.translate(width() / 2, height() / 2);//重新定位坐标起始点，把坐标原点放到窗体的中央

                //painter.translate(405, 184);//重新定位坐标起始点，把坐标原点放到窗体的中央
                 painter.translate(210, 363);//重新定位坐标起始点，把坐标原点放到窗体的中央
                //painter.scale(side / 400.0, side / 300.0);//设定画布的边界,用窗体宽高的最小值来计算时钟的大小，防止窗体拉伸导致的时钟变形以及显示不全

                //下面两个数组用来定义表针的两个顶点，以便后面的填充
                static const QPoint hourHand[4] = {
                    QPoint(8, 0),
                    QPoint(-8,0),
                    QPoint(-1.5, -160),
                    QPoint(1.5, -160)
                };
                static const QPoint minuteHand[4] = {
                    QPoint(4, 0),
                    QPoint(-4, 0),
                    QPoint(-1, -55),
                    QPoint(1, -55)
                };

                //油压

                painter.setPen(Qt::NoPen);//填充时针，不需要边线所以NoPen
                painter.setBrush(Qt::red);
                painter.setRenderHint(QPainter::Antialiasing, true);
                painter.save();
                //painter.rotate(6.0 *time.second());  //设旋转(角度 = 6° * (分钟 + 秒 / 60))
                 painter.rotate(-114.5);
                //painter.rotate(6.0 *numtmp);  //设置旋转(6° * 秒)
                //painter.rotate(numtmp++);  //设置旋转(6° * 秒)
                //painter.rotate(4.0 );//*shisu

                //painter.rotate(8*nu1);//floatnu2
                painter.rotate(228*floatnu3);//floatnu1

                painter.drawConvexPolygon(minuteHand, 4);  //填充分针部分
                painter.restore();

                /***********************************************/
                //2016.6.25   画白圈
                painter.setBrush(Qt::black); //画上中心原点/home/vmuser/qtworkplace/chanpin/img2
                painter.save();
                painter.drawEllipse(QPoint(0,0),13,13);
                painter.restore();

                //画白圈
                /***********************************************/

                painter.setBrush(Qt::darkGray);//画上中心原点/home/vmuser/qtworkplace/chanpin/img2
                painter.save();
                painter.drawEllipse(QPoint(0,0),10,10);
                painter.restore();


                //油量
                painter.translate(377,1);//重新定位坐标起始点，把坐标原点放到窗体的中央
                //painter.scale(side / 400.0, side / 300.0);

                painter.setPen(Qt::NoPen);
                painter.setBrush(Qt::red);
                painter.setRenderHint(QPainter::Antialiasing, true);
                painter.save();

                //painter.rotate(6.0 *time.second());  //设旋转(角度 = 6° * (分钟 + 秒 / 60))
                 painter.rotate(-114);
                //painter.rotate(8*nu3);
                painter.rotate(7.6*nu1);//



                //painter.rotate(4.0 );  //设旋转(角度 = 6° * (分钟 + 秒 / 60))*shisu
                //内测用
                /****************************************************************************/
                //qDebug()<<"time: "<<time.second()<<endl;

                /****************************************************************************/

                painter.drawConvexPolygon(minuteHand, 4);  //填充分针部分
                painter.setRenderHint(QPainter::Antialiasing, true);
                painter.restore();

                /***********************************************/
                //2016.6.25   画白圈
                painter.setBrush(Qt::black); //画上中心原点/home/vmuser/qtworkplace/chanpin/img2
                painter.save();
                painter.drawEllipse(QPoint(0,0),13,13);
                painter.restore();

                //画白圈
                /***********************************************/


                painter.setBrush(Qt::darkGray);
                painter.save();//画上中心原点
                painter.drawEllipse(QPoint(0,0),10,10);
                painter.restore();

                //KM/H
                painter.translate(-187,-35);//重新定位坐标起始点，把坐标原点放到窗体的中央
                //painter.scale(side / 400.0, side / 300.0);

                painter.setPen(Qt::NoPen);
                painter.setBrush(Qt::red);
                painter.setRenderHint(QPainter::Antialiasing, true);
                painter.save();

                //painter.rotate(6.0 *time.second());  //设旋转(角度 = 6° * (分钟 + 秒 / 60))
                 painter.rotate(-114);
                //painter.rotate(8*nu3);
                painter.rotate(7.6*nu3);//



                //painter.rotate(4.0 );  //设旋转(角度 = 6° * (分钟 + 秒 / 60))*shisu
                //内测用
                /****************************************************************************/
                //qDebug()<<"time: "<<time.second()<<endl;

                /****************************************************************************/

                painter.drawConvexPolygon(minuteHand, 4);  //填充分针部分
                painter.setRenderHint(QPainter::Antialiasing, true);
                painter.restore();

                /***********************************************/
                //2016.6.25   画白圈
                painter.setBrush(Qt::black); //画上中心原点/home/vmuser/qtworkplace/chanpin/img2
                painter.save();
                painter.drawEllipse(QPoint(0,0),13,13);
                painter.restore();

                //画白圈
                /***********************************************/


                painter.setBrush(Qt::darkGray);
                painter.save();//画上中心原点
                painter.drawEllipse(QPoint(0,0),10,10);
                painter.restore();

                //处理图片闪烁
                painter.translate(-390,-226);//平移到左边角


            //报警灯
           QPainter paintdeng(this);
           QPixmap pixdeng;

#if 1
           //左转灯
           if(cantest.flagLeft)
           {
               pixdeng.load("./img/dengshan/01.png");//
               paintdeng.drawPixmap(5,415,49,55,pixdeng);//正上方位置显示的图标
           }
           //发动机故障
           if(ecutest.flagFDJGZ_ECU)
           {
               pixdeng.load("./img/dengshan/14.png");//
               paintdeng.drawPixmap(73,435,36,23,pixdeng);//正上方位置显示的图标
           }
           //充电指示灯
           if(cantest.flagBattery)
           {
               pixdeng.load("./img/dengshan/17.png");//
               paintdeng.drawPixmap(118,434,34,24,pixdeng);//正上方位置显示的图标
           }

           //手刹
           if(cantest.flagSS)
           {
               pixdeng.load("./img/dengshan/13.png");//
               paintdeng.drawPixmap(278,433,37,29,pixdeng);//正上方位置显示的图标
           }
           //远光
           if(cantest.flagYG)
           {
               pixdeng.load("./img/dengshan/02.png");//
               paintdeng.drawPixmap(322,434,38,23,pixdeng);//正上方位置显示的图标
           }
           //示宽灯
           if(cantest.flagWidthlamp)
           {
               pixdeng.load("./img/dengshan/04.png");//
               paintdeng.drawPixmap(367,434,43,24,pixdeng);//正上方位置显示的图标
           }
           //近光灯
           if(cantest.flagJG)
           {
               pixdeng.load("./img/dengshan/03.png");//
               paintdeng.drawPixmap(418,433,37,27,pixdeng);//正上方位置显示的图标
           }
           //发动机预热灯
           if(ecutest.flagFDJYR_ECU)
           {
               pixdeng.load("./img/dengshan/11.png");//
               paintdeng.drawPixmap(463,434,37,23,pixdeng);//正上方位置显示的图标
           }
//           //量满
//           if(1)
//           {
//               pixdeng.load("./img/dengshan/15.png");//
//               paintdeng.drawPixmap(509,430,32,32,pixdeng);//正上方位置显示的图标
//           }
//           //粮仓满
//           if(1)
//           {
//               pixdeng.load("./img/dengshan/08.png");//
//               paintdeng.drawPixmap(550,435,29,20,pixdeng);//正上方位置显示的图标
//           }
           //燃油进水指示灯
           if(0)
           {
               pixdeng.load("./img/dengshan/07.png");//
               paintdeng.drawPixmap(586,432,24,28,pixdeng);//正上方位置显示的图标
           }
           //液压油压力
           if(CHK_GZ_BIT(cantest.m_extLampBitFlag,LAMP_BIT_YeYaYouYa))
           {
               pixdeng.load("./img/dengshan/99.png");//
               paintdeng.drawPixmap(616,432,15,28,pixdeng);//正上方位置显示的图标
           }
           //空滤灯
           if(cantest.flagKL)
           {
               pixdeng.load("./img/dengshan/05.png");//
               paintdeng.drawPixmap(510,430,32,32,pixdeng);//正上方位置显示的图标
           }
           //草箱限制
          if(CHK_GZ_BIT(cantest.m_extLampBitFlag,LAMP_BIT_CaoXiangXianZhi))
           {
               pixdeng.load("./img/dengshan/19.png");//
               paintdeng.drawPixmap(643,431,34,26,pixdeng);//正上方位置显示的图标
           }
           //右转灯
           if(cantest.flagRight)
           {
               pixdeng.load("./img/dengshan/18.png");//
               paintdeng.drawPixmap(740,415,49,55,pixdeng);//正上方位置显示的图标
           }

           //闪烁控制
           if(shanshuoSW)//水温 0~120度  95度以上报警。
           {
               pixdeng.load("./img/dengshan/09.png");//
               paintdeng.drawPixmap(161,432,31,28,pixdeng);//正上方位置显示的图标
           }

           if(shanshuoJYYL) //机油  油压报警 0～1 MPa,在0.1 MPa 以下为报警区。
           {
               pixdeng.load("./img/dengshan/12.png");//
               paintdeng.drawPixmap(200,436,39,20,pixdeng);//正上方位置显示的图标
           }

           if (shanshuoYL)//油量
           {
               pixdeng.load("./img/dengshan/10.png");//
               paintdeng.drawPixmap(248,430,24,28,pixdeng);//正上方位置显示的图标
           }

           //油中右水  油水分离  需要闪烁
           if(shanshuoYZYS)
           {
               pixdeng.load("./img/dengshan/07.png");//
               paintdeng.drawPixmap(586,432,24,28,pixdeng);//正上方位置显示的图标
           }

           //液压油温
           if(shanshuoYYYW)//液压油温  cantest.VolYeyayouwen
           {

           }
#endif


         }//end of if(flagmatchion == YZT_3)

            else if(flagmatchion == YZB_4_5_7_8)
            {
                   //int side = qMin(width(), height());  //绘制的范围(宽、高中最小值)

                   painter.setRenderHint(QPainter::Antialiasing);//绘制的图像反锯齿
                   //painter.translate(width() / 2, height() / 2);//重新定位坐标起始点，把坐标原点放到窗体的中央

                   //painter.translate(405, 184);//重新定位坐标起始点，把坐标原点放到窗体的中央
                    painter.translate(210, 363);//重新定位坐标起始点，把坐标原点放到窗体的中央
                   //painter.scale(side / 400.0, side / 300.0);//设定画布的边界,用窗体宽高的最小值来计算时钟的大小，防止窗体拉伸导致的时钟变形以及显示不全

                   //下面两个数组用来定义表针的两个顶点，以便后面的填充
                   static const QPoint hourHand[4] = {
                       QPoint(8, 0),
                       QPoint(-8,0),
                       QPoint(-1.5, -160),
                       QPoint(1.5, -160)
                   };
                   static const QPoint minuteHand[4] = {
                       QPoint(4, 0),
                       QPoint(-4, 0),
                       QPoint(-1, -55),
                       QPoint(1, -55)
                   };

                   //油压
                   painter.setPen(Qt::NoPen);//填充时针，不需要边线所以NoPen
                   painter.setBrush(Qt::red);
                   painter.setRenderHint(QPainter::Antialiasing, true);
                   painter.save();
                   //painter.rotate(6.0 *time.second());  //设旋转(角度 = 6° * (分钟 + 秒 / 60))
                    painter.rotate(-114.5);
                   //painter.rotate(6.0 *numtmp);  //设置旋转(6° * 秒)
                   //painter.rotate(numtmp++);  //设置旋转(6° * 秒)
                   //painter.rotate(4.0 );//*shisu

                   //painter.rotate(8*nu1);//floatnu2
                   painter.rotate(228*floatnu3);//floatnu1

                   painter.drawConvexPolygon(minuteHand, 4);  //填充分针部分
                   painter.restore();

                   /***********************************************/
                   //2016.6.25   画白圈
                   painter.setBrush(Qt::black); //画上中心原点/home/vmuser/qtworkplace/chanpin/img2
                   painter.save();
                   painter.drawEllipse(QPoint(0,0),13,13);
                   painter.restore();

                   //画白圈
                   /***********************************************/

                   painter.setBrush(Qt::darkGray);//画上中心原点/home/vmuser/qtworkplace/chanpin/img2
                   painter.save();
                   painter.drawEllipse(QPoint(0,0),10,10);
                   painter.restore();


                   //油量
                   painter.translate(377,1);//重新定位坐标起始点，把坐标原点放到窗体的中央
                   //painter.scale(side / 400.0, side / 300.0);

                   painter.setPen(Qt::NoPen);
                   painter.setBrush(Qt::red);
                   painter.setRenderHint(QPainter::Antialiasing, true);
                   painter.save();

                   //painter.rotate(6.0 *time.second());  //设旋转(角度 = 6° * (分钟 + 秒 / 60))
                    painter.rotate(-114.5);
                   //painter.rotate(8*nu3);
                   painter.rotate(7.6*nu1);//



                   //painter.rotate(4.0 );  //设旋转(角度 = 6° * (分钟 + 秒 / 60))*shisu
                   //内测用
                   /****************************************************************************/
                   //qDebug()<<"time: "<<time.second()<<endl;

                   /****************************************************************************/

                   painter.drawConvexPolygon(minuteHand, 4);  //填充分针部分
                   painter.setRenderHint(QPainter::Antialiasing, true);
                   painter.restore();

                   /***********************************************/
                   //2016.6.25   画白圈
                   painter.setBrush(Qt::black); //画上中心原点/home/vmuser/qtworkplace/chanpin/img2
                   painter.save();
                   painter.drawEllipse(QPoint(0,0),13,13);
                   painter.restore();

                   //画白圈
                   /***********************************************/


                   painter.setBrush(Qt::darkGray);
                   painter.save();//画上中心原点
                   painter.drawEllipse(QPoint(0,0),10,10);
                   painter.restore();

                   //KM/H
                   painter.translate(-187,-35);//重新定位坐标起始点，把坐标原点放到窗体的中央
                   //painter.scale(side / 400.0, side / 300.0);

                   painter.setPen(Qt::NoPen);
                   painter.setBrush(Qt::red);
                   painter.setRenderHint(QPainter::Antialiasing, true);
                   painter.save();

                   //painter.rotate(6.0 *time.second());  //设旋转(角度 = 6° * (分钟 + 秒 / 60))
                   painter.rotate(-114);
                   //painter.rotate(8*nu3);
                   painter.rotate(7.6*nu3);//



                   //painter.rotate(4.0 );  //设旋转(角度 = 6° * (分钟 + 秒 / 60))*shisu
                   //内测用
                   /****************************************************************************/
                   //qDebug()<<"time: "<<time.second()<<endl;

                   /****************************************************************************/

                   painter.drawConvexPolygon(minuteHand, 4);  //填充分针部分
                   painter.setRenderHint(QPainter::Antialiasing, true);
                   painter.restore();

                   /***********************************************/
                   //2016.6.25   画白圈
                   painter.setBrush(Qt::black); //画上中心原点/home/vmuser/qtworkplace/chanpin/img2
                   painter.save();
                   painter.drawEllipse(QPoint(0,0),13,13);
                   painter.restore();

                   //画白圈
                   /***********************************************/


                   painter.setBrush(Qt::darkGray);
                   painter.save();//画上中心原点
                   painter.drawEllipse(QPoint(0,0),10,10);
                   painter.restore();

                   //处理图片闪烁
                   painter.translate(-390,-226);//平移到左边角


               //报警灯
              QPainter paintdeng(this);
              QPixmap pixdeng;
#if 1
           //左转灯
           if(cantest.flagLeft)
           {
               pixdeng.load("./img/dengshan/01.png");//
               paintdeng.drawPixmap(5,415,49,55,pixdeng);//正上方位置显示的图标
           }
           //发动机故障
           if(ecutest.flagFDJGZ_ECU)
           {
               pixdeng.load("./img/dengshan/14.png");//
               paintdeng.drawPixmap(73,435,36,23,pixdeng);//正上方位置显示的图标
           }
           //充电指示灯
           if(cantest.flagBattery)
           {
               pixdeng.load("./img/dengshan/17.png");//
               paintdeng.drawPixmap(118,434,34,24,pixdeng);//正上方位置显示的图标
           }

           //手刹
           if(cantest.flagSS)
           {
               pixdeng.load("./img/dengshan/13.png");//
               paintdeng.drawPixmap(278,433,37,29,pixdeng);//正上方位置显示的图标
           }
           //远光
           if(cantest.flagYG)
           {
               pixdeng.load("./img/dengshan/02.png");//
               paintdeng.drawPixmap(322,434,38,23,pixdeng);//正上方位置显示的图标
           }
           //示宽灯
           if(cantest.flagWidthlamp)
           {
               pixdeng.load("./img/dengshan/04.png");//
               paintdeng.drawPixmap(367,434,43,24,pixdeng);//正上方位置显示的图标
           }
           //近光灯
           if(cantest.flagJG)
           {
               pixdeng.load("./img/dengshan/03.png");//
               paintdeng.drawPixmap(418,433,37,27,pixdeng);//正上方位置显示的图标
           }
           //发动机预热灯
           if(ecutest.flagFDJYR_ECU)
           {
               pixdeng.load("./img/dengshan/11.png");//
               paintdeng.drawPixmap(463,434,37,23,pixdeng);//正上方位置显示的图标
           }
           //籽粒满仓
           if(CHK_GZ_BIT(cantest.m_extLampBitFlag,LAMP_BIT_ZhiLiHuiShou))
           {
               pixdeng.load("./img/dengshan/15.png");//
               paintdeng.drawPixmap(509,430,32,32,pixdeng);//正上方位置显示的图标
           }
//           //粮仓满
//           if(1)
//           {
//               pixdeng.load("./img/dengshan/08.png");//
//               paintdeng.drawPixmap(550,435,29,20,pixdeng);//正上方位置显示的图标
//           }
           //燃油进水指示灯
           if(shanshuoYZYS)
           {
               pixdeng.load("./img/dengshan/07.png");//
               paintdeng.drawPixmap(586,432,24,28,pixdeng);//正上方位置显示的图标
           }
           //液压油压力
           if(CHK_GZ_BIT(cantest.m_extLampBitFlag,LAMP_BIT_YeYaYouYa))
           {
               pixdeng.load("./img/dengshan/99.png");//
               paintdeng.drawPixmap(616,432,15,28,pixdeng);//正上方位置显示的图标
           }
           //空滤灯
           if(cantest.flagKL)
           {
               pixdeng.load("./img/dengshan/05.png");//
               paintdeng.drawPixmap(510,430,32,32,pixdeng);//正上方位置显示的图标
           }
           //草箱限制
           if(CHK_GZ_BIT(cantest.m_extLampBitFlag,LAMP_BIT_CaoXiangXianZhi))
           {
               pixdeng.load("./img/dengshan/19.png");//
               paintdeng.drawPixmap(643,431,34,26,pixdeng);//正上方位置显示的图标
           }
           //右转灯
           if(cantest.flagRight)
           {
               pixdeng.load("./img/dengshan/18.png");//
               paintdeng.drawPixmap(740,415,49,55,pixdeng);//正上方位置显示的图标
           }

           //闪烁控制
           if(shanshuoSW)//水温 0~120度  95度以上报警。
           {
               pixdeng.load("./img/dengshan/09.png");//
               paintdeng.drawPixmap(161,432,31,28,pixdeng);//正上方位置显示的图标
           }

           if(shanshuoJYYL) //机油  油压报警 0～1 MPa,在0.1 MPa 以下为报警区。
           {
               pixdeng.load("./img/dengshan/12.png");//
               paintdeng.drawPixmap(200,436,39,20,pixdeng);//正上方位置显示的图标
           }

           if (shanshuoYL)//油量
           {
               pixdeng.load("./img/dengshan/10.png");//
               paintdeng.drawPixmap(248,430,24,28,pixdeng);//正上方位置显示的图标
           }

           //油中右水  油水分离  需要闪烁
           if(shanshuoYZYS)
           {
               pixdeng.load("./img/dengshan/07.png");//
               paintdeng.drawPixmap(586,432,24,28,pixdeng);//正上方位置显示的图标
           }

           //液压油温
           if(shanshuoYYYW)//液压油温  cantest.VolYeyayouwen
           {

           }
#endif
         }//end of if(flagmatchion == YZB_4_5_7_8)


            //
            //2017.4.2  辣椒机器
            else if(flagmatchion == JZ_3600)
            {
                   //int side = qMin(width(), height());  //绘制的范围(宽、高中最小值)

                   painter.setRenderHint(QPainter::Antialiasing);//绘制的图像反锯齿
                   //painter.translate(width() / 2, height() / 2);//重新定位坐标起始点，把坐标原点放到窗体的中央

                   //painter.translate(405, 184);//重新定位坐标起始点，把坐标原点放到窗体的中央
                    painter.translate(210, 363);//重新定位坐标起始点，把坐标原点放到窗体的中央
                   //painter.scale(side / 400.0, side / 300.0);//设定画布的边界,用窗体宽高的最小值来计算时钟的大小，防止窗体拉伸导致的时钟变形以及显示不全

                   //下面两个数组用来定义表针的两个顶点，以便后面的填充
                   static const QPoint hourHand[4] = {
                       QPoint(8, 0),
                       QPoint(-8,0),
                       QPoint(-1.5, -160),
                       QPoint(1.5, -160)
                   };
                   static const QPoint minuteHand[4] = {
                       QPoint(4, 0),
                       QPoint(-4, 0),
                       QPoint(-1, -55),
                       QPoint(1, -55)
                   };

                   //油压

                   painter.setPen(Qt::NoPen);//填充时针，不需要边线所以NoPen
                   painter.setBrush(Qt::red);
                   painter.setRenderHint(QPainter::Antialiasing, true);
                   painter.save();
                   //painter.rotate(6.0 *time.second());  //设旋转(角度 = 6° * (分钟 + 秒 / 60))
                   painter.rotate(-114.5);
                   painter.rotate(228*floatnu3);//floatnu1

                   painter.drawConvexPolygon(minuteHand, 4);  //填充分针部分
                   painter.restore();

                   /***********************************************/
                   //2016.6.25   画白圈
                   painter.setBrush(Qt::green); //画上中心原点/home/vmuser/qtworkplace/chanpin/img2
                   painter.save();
                   painter.drawEllipse(QPoint(0,0),13,13);
                   painter.restore();

                   //画白圈
                   /***********************************************/

                   painter.setBrush(Qt::darkGray);//画上中心原点/home/vmuser/qtworkplace/chanpin/img2
                   painter.save();
                   painter.drawEllipse(QPoint(0,0),10,10);
                   painter.restore();


                   //油量
                   painter.translate(380,3);//重新定位坐标起始点，把坐标原点放到窗体的中央
                   //painter.scale(side / 400.0, side / 300.0);

                   painter.setPen(Qt::NoPen);
                   painter.setBrush(Qt::red);
                   painter.setRenderHint(QPainter::Antialiasing, true);
                   painter.save();

                   painter.rotate(-114.5);
                   painter.rotate(28.2*nu1);//
                   //painter.rotate(7.6*nu1);//
                   //qDebug()<<"nu1 =======================================   "<<nu1<<endl;

                   //painter.rotate(4.0 );  //设旋转(角度 = 6° * (分钟 + 秒 / 60))*shisu
                   //内测用
                   /****************************************************************************/
                   //qDebug()<<"time: "<<time.second()<<endl;

                   /****************************************************************************/

                   painter.drawConvexPolygon(minuteHand, 4);  //填充分针部分
                   painter.setRenderHint(QPainter::Antialiasing, true);
                   painter.restore();

                   /***********************************************/
                   //2016.6.25   画白圈
                   painter.setBrush(Qt::green); //画上中心原点/home/vmuser/qtworkplace/chanpin/img2
                   painter.save();
                   painter.drawEllipse(QPoint(0,0),13,13);
                   painter.restore();

                   //画白圈
                   /***********************************************/


                   painter.setBrush(Qt::darkGray);
                   painter.save();//画上中心原点
                   painter.drawEllipse(QPoint(0,0),10,10);
                   painter.restore();

                   //KM/H
                   painter.translate(-190,-36);//重新定位坐标起始点，把坐标原点放到窗体的中央
                   //painter.scale(side / 400.0, side / 300.0);

                   painter.setPen(Qt::NoPen);
                   painter.setBrush(Qt::red);
                   painter.setRenderHint(QPainter::Antialiasing, true);
                   painter.save();

                   //painter.rotate(6.0 *time.second());  //设旋转(角度 = 6° * (分钟 + 秒 / 60))
                   painter.rotate(-114);
                   //painter.rotate(8*nu3);
                   painter.rotate(7.6*nu3);//



                   //painter.rotate(4.0 );  //设旋转(角度 = 6° * (分钟 + 秒 / 60))*shisu
                   //内测用
                   /****************************************************************************/
                   //qDebug()<<"time: "<<time.second()<<endl;

                   /****************************************************************************/

                   painter.drawConvexPolygon(minuteHand, 4);  //填充分针部分
                   painter.setRenderHint(QPainter::Antialiasing, true);
                   painter.restore();

                   /***********************************************/
                   //2016.6.25   画白圈
                   painter.setBrush(Qt::green); //画上中心原点/home/vmuser/qtworkplace/chanpin/img2
                   painter.save();
                   painter.drawEllipse(QPoint(0,0),13,13);
                   painter.restore();

                   //画白圈
                   /***********************************************/


                   painter.setBrush(Qt::darkGray);
                   painter.save();//画上中心原点
                   painter.drawEllipse(QPoint(0,0),10,10);
                   painter.restore();

                   //处理图片闪烁
                   painter.translate(-390,-226);//平移到左边角


               //报警灯
              QPainter paintdeng(this);
              QPixmap pixdeng;
              //左转灯
              if(cantest.flagLeft)
              {
                  pixdeng.load("./img/dengshan/01.png");//
                  paintdeng.drawPixmap(5,415,49,55,pixdeng);//正上方位置显示的图标
              }
              //发动机故障
              if(ecutest.flagFDJGZ_ECU)
              {
                  pixdeng.load("./img/dengshan/14.png");//
                  paintdeng.drawPixmap(73,435,36,23,pixdeng);//正上方位置显示的图标
              }
              //充电指示灯
              if(cantest.flagBattery)
              {
                  pixdeng.load("./img/dengshan/17.png");//
                  paintdeng.drawPixmap(118,434,34,24,pixdeng);//正上方位置显示的图标
              }

              //手刹
              if(cantest.flagSS)
              {
                  pixdeng.load("./img/dengshan/13.png");//
                  paintdeng.drawPixmap(278,433,37,29,pixdeng);//正上方位置显示的图标
              }
              //远光
              if(cantest.flagYG)
              {
                  pixdeng.load("./img/dengshan/02.png");//
                  paintdeng.drawPixmap(322,434,38,23,pixdeng);//正上方位置显示的图标
              }
              //示宽灯
              if(cantest.flagWidthlamp)
              {
                  pixdeng.load("./img/dengshan/04.png");//
                  paintdeng.drawPixmap(367,434,43,24,pixdeng);//正上方位置显示的图标
              }
              //近光灯
              if(cantest.flagJG)
              {
                  pixdeng.load("./img/dengshan/03.png");//
                  paintdeng.drawPixmap(418,433,37,27,pixdeng);//正上方位置显示的图标
              }
              //发动机预热灯
              if(ecutest.flagFDJYR_ECU)
              {
                  pixdeng.load("./img/dengshan/11.png");//
                  paintdeng.drawPixmap(463,434,37,23,pixdeng);//正上方位置显示的图标
              }
//              //量满
//              if(1)
//              {
//                  pixdeng.load("./img/dengshan/15.png");//
//                  paintdeng.drawPixmap(509,430,32,32,pixdeng);//正上方位置显示的图标
//              }
   //           //粮仓满
   //           if(1)
   //           {
   //               pixdeng.load("./img/dengshan/08.png");//
   //               paintdeng.drawPixmap(550,435,29,20,pixdeng);//正上方位置显示的图标
   //           }
              //燃油进水指示灯
              if(shanshuoYZYS)
              {
                  pixdeng.load("./img/dengshan/07.png");//
                  paintdeng.drawPixmap(586,432,24,28,pixdeng);//正上方位置显示的图标
              }
              //液压油压力
              if(CHK_GZ_BIT(cantest.m_extLampBitFlag,LAMP_BIT_YeYaYouYa))
              {
                  pixdeng.load("./img/dengshan/99.png");//
                  paintdeng.drawPixmap(616,432,15,28,pixdeng);//正上方位置显示的图标
              }
   //           //空滤灯
   //           if(1)
   //           {
   //               pixdeng.load("./img/dengshan/05.png");//
   //               paintdeng.drawPixmap(640,430,32,32,pixdeng);//正上方位置显示的图标
   //           }
//              //草箱限制
//              if(1)
//              {
//                  pixdeng.load("./img/dengshan/19.png");//
//                  paintdeng.drawPixmap(643,431,34,26,pixdeng);//正上方位置显示的图标
//              }

              //刹车自动故障
              if(CHK_GZ_BIT(cantest.m_GZBitFlag,GZ_BIT_SHACHEZHIDONG))
              {
                  pixdeng.load("./img/zhujiemianicon/10.png");//
                  paintdeng.drawPixmap(643,434,31,24,pixdeng);//正上方位置显示的图标
              }

              //右转灯
              if(cantest.flagRight)
              {
                  pixdeng.load("./img/dengshan/18.png");//
                  paintdeng.drawPixmap(740,415,49,55,pixdeng);//正上方位置显示的图标
              }


              //闪烁控制
               if(shanshuoSW)//水温 0~120度  95度以上报警。
               {
                   pixdeng.load("./img/dengshan/09.png");//
                   paintdeng.drawPixmap(161,432,31,28,pixdeng);//正上方位置显示的图标
               }

               if(shanshuoJYYL) //机油  油压报警 0～1 MPa,在0.1 MPa 以下为报警区。
               {
                   pixdeng.load("./img/dengshan/12.png");//
                   paintdeng.drawPixmap(200,436,39,20,pixdeng);//正上方位置显示的图标
               }

               if (shanshuoYL)//油量
               {
                   pixdeng.load("./img/dengshan/10.png");//
                   paintdeng.drawPixmap(248,430,24,28,pixdeng);//正上方位置显示的图标
               }
               //2017.5.15 当油量为1时，蜂鸣器响一声，油量指示灯常亮
               if(cantest.VolYL == 1)//油量
               {
                   pixdeng.load("./img/dengshan/10.png");//
                   paintdeng.drawPixmap(248,430,24,28,pixdeng);//正上方位置显示的图标
               }

               //油中右水  油水分离  需要闪烁
               if(shanshuoYZYS)
               {
                   pixdeng.load("./img/dengshan/07.png");//
                   paintdeng.drawPixmap(586,432,24,28,pixdeng);//正上方位置显示的图标
               }

               //液压油温
               if(shanshuoYYYW)//液压油温  cantest.VolYeyayouwen
               {

               }

              //显示油量，机油压力，小时计 等要显示的值
              //
              //机油压力
              //ui->label_7->setText("jiyouyali");


            }//end of if(flagmatchion == YZB_4_5_7_8)


            else if(flagmatchion == YZBT_5)
            {
                   //int side = qMin(width(), height());  //绘制的范围(宽、高中最小值)

                   painter.setRenderHint(QPainter::Antialiasing);//绘制的图像反锯齿
                   //painter.translate(width() / 2, height() / 2);//重新定位坐标起始点，把坐标原点放到窗体的中央

                   //painter.translate(405, 184);//重新定位坐标起始点，把坐标原点放到窗体的中央
                    painter.translate(210, 363);//重新定位坐标起始点，把坐标原点放到窗体的中央
                   //painter.scale(side / 400.0, side / 300.0);//设定画布的边界,用窗体宽高的最小值来计算时钟的大小，防止窗体拉伸导致的时钟变形以及显示不全

                   //下面两个数组用来定义表针的两个顶点，以便后面的填充
                   static const QPoint hourHand[4] = {
                       QPoint(8, 0),
                       QPoint(-8,0),
                       QPoint(-1.5, -160),
                       QPoint(1.5, -160)
                   };
                   static const QPoint minuteHand[4] = {
                       QPoint(4, 0),
                       QPoint(-4, 0),
                       QPoint(-1, -55),
                       QPoint(1, -55)
                   };

                   //机油压力

                   painter.setPen(Qt::NoPen);//填充时针，不需要边线所以NoPen
                   painter.setBrush(Qt::red);
                   painter.setRenderHint(QPainter::Antialiasing, true);
                   painter.save();
                   //painter.rotate(6.0 *time.second());  //设旋转(角度 = 6° * (分钟 + 秒 / 60))
                   painter.rotate(-114.5);
                   painter.rotate(228*floatnu3);//floatnu1

                   painter.drawConvexPolygon(minuteHand, 4);  //填充分针部分
                   painter.restore();

                   /***********************************************/
                   //2016.6.25   画白圈
                   painter.setBrush(Qt::darkGray); //画上中心原点/home/vmuser/qtworkplace/chanpin/img2
                   painter.save();
                   painter.drawEllipse(QPoint(0,0),13,13);
                   painter.restore();

                   //画白圈
                   /***********************************************/

                   painter.setBrush(Qt::black);//画上中心原点/home/vmuser/qtworkplace/chanpin/img2
                   painter.save();
                   painter.drawEllipse(QPoint(0,0),10,10);
                   painter.restore();


                   //油量
                   painter.translate(380,3);//重新定位坐标起始点，把坐标原点放到窗体的中央
                   //painter.scale(side / 400.0, side / 300.0);

                   painter.setPen(Qt::NoPen);
                   painter.setBrush(Qt::red);
                   painter.setRenderHint(QPainter::Antialiasing, true);
                   painter.save();

                   //painter.rotate(6.0 *time.second());  //设旋转(角度 = 6° * (分钟 + 秒 / 60))
                   painter.rotate(-114.5);
                   //painter.rotate(8*nu3);
                   painter.rotate(7.6*nu1);//



                   //painter.rotate(4.0 );  //设旋转(角度 = 6° * (分钟 + 秒 / 60))*shisu
                   //内测用
                   /****************************************************************************/
                   //qDebug()<<"time: "<<time.second()<<endl;

                   /****************************************************************************/

                   painter.drawConvexPolygon(minuteHand, 4);  //填充分针部分
                   painter.setRenderHint(QPainter::Antialiasing, true);
                   painter.restore();

                   /***********************************************/
                   //2016.6.25   画白圈
                   painter.setBrush(Qt::darkGray); //画上中心原点/home/vmuser/qtworkplace/chanpin/img2
                   painter.save();
                   painter.drawEllipse(QPoint(0,0),13,13);
                   painter.restore();

                   //画白圈
                   /***********************************************/


                   painter.setBrush(Qt::black);
                   painter.save();//画上中心原点
                   painter.drawEllipse(QPoint(0,0),10,10);
                   painter.restore();

                   //KM/H
                   painter.translate(-190,-36);//重新定位坐标起始点，把坐标原点放到窗体的中央
                   //painter.scale(side / 400.0, side / 300.0);

                   painter.setPen(Qt::NoPen);
                   painter.setBrush(Qt::red);
                   painter.setRenderHint(QPainter::Antialiasing, true);
                   painter.save();

                   //painter.rotate(6.0 *time.second());  //设旋转(角度 = 6° * (分钟 + 秒 / 60))
                   painter.rotate(-114);
                   //painter.rotate(8*nu3);
                   painter.rotate(7.6*floatnu3);//


                   //painter.rotate(4.0 );  //设旋转(角度 = 6° * (分钟 + 秒 / 60))*shisu
                   //内测用
                   /****************************************************************************/
                   //qDebug()<<"time: "<<time.second()<<endl;

                   /****************************************************************************/

                   painter.drawConvexPolygon(minuteHand, 4);  //填充分针部分
                   painter.setRenderHint(QPainter::Antialiasing, true);
                   painter.restore();

                   /***********************************************/
                   //2016.6.25   画白圈
                   painter.setBrush(Qt::darkGray); //画上中心原点/home/vmuser/qtworkplace/chanpin/img2
                   painter.save();
                   painter.drawEllipse(QPoint(0,0),13,13);
                   painter.restore();

                   //画白圈
                   /***********************************************/


                   painter.setBrush(Qt::black);
                   painter.save();//画上中心原点
                   painter.drawEllipse(QPoint(0,0),10,10);
                   painter.restore();

                   //处理图片闪烁
                   painter.translate(-390,-226);//平移到左边角


               //报警灯
              QPainter paintdeng(this);
              QPixmap pixdeng;
              //左转灯
              if(cantest.flagLeft)
              {
                  pixdeng.load("./img/dengshan/01.png");//
                  paintdeng.drawPixmap(5,415,49,55,pixdeng);//正上方位置显示的图标
              }
              //发动机故障
              if(ecutest.flagFDJGZ_ECU)
              {
                  pixdeng.load("./img/dengshan/14.png");//
                  paintdeng.drawPixmap(73,435,36,23,pixdeng);//正上方位置显示的图标
              }
              //充电指示灯
              if(cantest.flagBattery)
              {
                  pixdeng.load("./img/dengshan/17.png");//
                  paintdeng.drawPixmap(118,434,34,24,pixdeng);//正上方位置显示的图标
              }

              //手刹
              if(cantest.flagSS)
              {
                  pixdeng.load("./img/dengshan/13.png");//
                  paintdeng.drawPixmap(278,433,37,29,pixdeng);//正上方位置显示的图标
              }
              //远光
              if(cantest.flagYG)
              {
                  pixdeng.load("./img/dengshan/02.png");//
                  paintdeng.drawPixmap(322,434,38,23,pixdeng);//正上方位置显示的图标
              }
              //示宽灯
              if(cantest.flagWidthlamp)
              {
                  pixdeng.load("./img/dengshan/04.png");//
                  paintdeng.drawPixmap(367,434,43,24,pixdeng);//正上方位置显示的图标
              }
              //近光灯
              if(cantest.flagJG)
              {
                  pixdeng.load("./img/dengshan/03.png");//
                  paintdeng.drawPixmap(418,433,37,27,pixdeng);//正上方位置显示的图标
              }
              //发动机预热灯
              if(ecutest.flagFDJYR_ECU)
              {
                  pixdeng.load("./img/dengshan/11.png");//
                  paintdeng.drawPixmap(463,434,37,23,pixdeng);//正上方位置显示的图标
              }
              //籽粒满仓
               if(CHK_GZ_BIT(cantest.m_extLampBitFlag,LAMP_BIT_ZhiLiHuiShou))
              {
                  pixdeng.load("./img/dengshan/15.png");//
                  paintdeng.drawPixmap(509,430,32,32,pixdeng);//正上方位置显示的图标
              }
              //粮仓满
              if(CHK_GZ_BIT(cantest.m_extLampBitFlag,LAMP_BIT_LiangCangMan))
              {
                  pixdeng.load("./img/dengshan/08.png");//
                  paintdeng.drawPixmap(550,435,29,20,pixdeng);//正上方位置显示的图标
              }
              //燃油进水指示灯
              if(shanshuoYZYS)
              {
                  pixdeng.load("./img/dengshan/07.png");//
                  paintdeng.drawPixmap(586,432,24,28,pixdeng);//正上方位置显示的图标
              }

              //液压滤清
              if(CHK_GZ_BIT(cantest.m_extLampBitFlag,LAMP_BIT_YeYaLvQing))
              {
                  pixdeng.load("./img/zhujiemianicon/09.png");//
                  //paintdeng.drawPixmap(586,432,12,28,pixdeng);//正上方位置显示的图标
                  paintdeng.drawPixmap(616,432,16,28,pixdeng);//正上方位置显示的图标
              }


//              //液压油压力
//              if(1)
//              {
//                  pixdeng.load("./img/dengshan/99.png");//
//                  paintdeng.drawPixmap(616,432,15,28,pixdeng);//正上方位置显示的图标
//              }
   //           //空滤灯
   //           if(1)
   //           {
   //               pixdeng.load("./img/dengshan/05.png");//
   //               paintdeng.drawPixmap(640,430,32,32,pixdeng);//正上方位置显示的图标
   //           }
//              //草箱限制
//              if(0)
//              {
//                  pixdeng.load("./img/dengshan/19.png");//
//                  paintdeng.drawPixmap(643,431,34,26,pixdeng);//正上方位置显示的图标
//              }
              //右转灯
              if(cantest.flagRight)
              {
                  pixdeng.load("./img/dengshan/18.png");//
                  paintdeng.drawPixmap(740,415,49,55,pixdeng);//正上方位置显示的图标
              }


              //闪烁控制
               if(shanshuoSW)//水温 0~120度  95度以上报警。
               {
                   pixdeng.load("./img/dengshan/09.png");//
                   paintdeng.drawPixmap(161,432,31,28,pixdeng);//正上方位置显示的图标
               }

               if(shanshuoJYYL) //机油  油压报警 0～1 MPa,在0.1 MPa 以下为报警区。
               {
                   pixdeng.load("./img/dengshan/12.png");//
                   paintdeng.drawPixmap(200,436,39,20,pixdeng);//正上方位置显示的图标
               }

               if (shanshuoYL)//油量
               {
                   pixdeng.load("./img/dengshan/10.png");//
                   paintdeng.drawPixmap(248,430,24,28,pixdeng);//正上方位置显示的图标
               }

               //油中右水  油水分离  需要闪烁
               if(shanshuoYZYS)
               {
                   pixdeng.load("./img/dengshan/07.png");//
                   paintdeng.drawPixmap(586,432,24,28,pixdeng);//正上方位置显示的图标
               }

               //液压油温
               if(shanshuoYYYW)//液压油温  cantest.VolYeyayouwen
               {

               }

              //显示油量，机油压力，小时计 等要显示的值
              //
              //机油压力
              //ui->label_7->setText("jiyouyali");


            }//end of if(flagmatchion == YZBT_5)


            //
            //2017.5.6 东北测试机型
            else if(flagmatchion == YZT_5)
            {
                //int side = qMin(width(), height());  //绘制的范围(宽、高中最小值)

                painter.setRenderHint(QPainter::Antialiasing);//绘制的图像反锯齿
                //painter.translate(width() / 2, height() / 2);//重新定位坐标起始点，把坐标原点放到窗体的中央

                //painter.translate(405, 184);//重新定位坐标起始点，把坐标原点放到窗体的中央
                 painter.translate(210, 363);//重新定位坐标起始点，把坐标原点放到窗体的中央
                //painter.scale(side / 400.0, side / 300.0);//设定画布的边界,用窗体宽高的最小值来计算时钟的大小，防止窗体拉伸导致的时钟变形以及显示不全

                //下面两个数组用来定义表针的两个顶点，以便后面的填充
                static const QPoint hourHand[4] = {
                    QPoint(8, 0),
                    QPoint(-8,0),
                    QPoint(-1.5, -160),
                    QPoint(1.5, -160)
                };
                static const QPoint minuteHand[4] = {
                    QPoint(4, 0),
                    QPoint(-4, 0),
                    QPoint(-1, -55),
                    QPoint(1, -55)
                };

                //机油压力

                painter.setPen(Qt::NoPen);//填充时针，不需要边线所以NoPen
                painter.setBrush(Qt::red);
                painter.setRenderHint(QPainter::Antialiasing, true);
                painter.save();
                painter.rotate(-114.5);
                painter.rotate(228*floatnu3);//floatnu1

                painter.drawConvexPolygon(minuteHand, 4);  //填充分针部分
                painter.restore();

                /***********************************************/
                //2016.6.25   画白圈
                painter.setBrush(Qt::green); //画上中心原点/home/vmuser/qtworkplace/chanpin/img2
                painter.save();
                painter.drawEllipse(QPoint(0,0),13,13);
                painter.restore();

                //画白圈
                /***********************************************/

                painter.setBrush(Qt::darkGray);//画上中心原点/home/vmuser/qtworkplace/chanpin/img2
                painter.save();
                painter.drawEllipse(QPoint(0,0),10,10);
                painter.restore();


                //滚筒转速
                painter.translate(377,1);//重新定位坐标起始点，把坐标原点放到窗体的中央

                painter.setPen(Qt::NoPen);
                painter.setBrush(Qt::red);
                painter.setRenderHint(QPainter::Antialiasing, true);
                painter.save();

                //painter.rotate(6.0 *time.second());  //设旋转(角度 = 6° * (分钟 + 秒 / 60))
                painter.rotate(-114.5);
                painter.rotate(7.6*nu1);//
               // painter.rotate(8*floatnu1);//



                //painter.rotate(4.0 );  //设旋转(角度 = 6° * (分钟 + 秒 / 60))*shisu
                //内测用
                /****************************************************************************/
                //qDebug()<<"time: "<<time.second()<<endl;

                /****************************************************************************/

                painter.drawConvexPolygon(minuteHand, 4);  //填充分针部分
                painter.setRenderHint(QPainter::Antialiasing, true);
                painter.restore();

                /***********************************************/
                //2016.6.25   画白圈
                painter.setBrush(Qt::green); //画上中心原点/home/vmuser/qtworkplace/chanpin/img2
                painter.save();
                painter.drawEllipse(QPoint(0,0),13,13);
                painter.restore();

                //画白圈
                /***********************************************/


                painter.setBrush(Qt::darkGray);
                painter.save();//画上中心原点
                painter.drawEllipse(QPoint(0,0),10,10);
                painter.restore();

                //KM/H
                painter.translate(-190,-36);//重新定位坐标起始点，把坐标原点放到窗体的中央
                //painter.scale(side / 400.0, side / 300.0);

                painter.setPen(Qt::NoPen);
                painter.setBrush(Qt::red);
                painter.setRenderHint(QPainter::Antialiasing, true);
                painter.save();

                painter.rotate(-114);
                //painter.rotate(8*nu3);
                painter.rotate(7.6*nu3);//


                //painter.rotate(4.0 );  //设旋转(角度 = 6° * (分钟 + 秒 / 60))*shisu
                //内测用
                /****************************************************************************/
                //qDebug()<<"time: "<<time.second()<<endl;

                /****************************************************************************/

                painter.drawConvexPolygon(minuteHand, 4);  //填充分针部分
                painter.setRenderHint(QPainter::Antialiasing, true);
                painter.restore();

                /***********************************************/
                //2016.6.25   画白圈
                painter.setBrush(Qt::green); //画上中心原点/home/vmuser/qtworkplace/chanpin/img2
                painter.save();
                painter.drawEllipse(QPoint(0,0),13,13);
                painter.restore();

                //画白圈
                /***********************************************/


                painter.setBrush(Qt::darkGray);
                painter.save();//画上中心原点
                painter.drawEllipse(QPoint(0,0),10,10);
                painter.restore();

                //处理图片闪烁
                painter.translate(-390,-226);//平移到左边角

//                //喂入
//                QPainter paintShanshuo_W(this);
//                QPixmap pixShanshuo_W;
//                pixShanshuo_W.load("./img/weiruliang/09.png");//07.jpg
//                paintShanshuo_W.drawPixmap(10,110,28,121,pixShanshuo_W);

//                //粮损
//                pixShanshuo_W.load("./img/liangshun/06.png");//07.jpg
//                paintShanshuo_W.drawPixmap(760,110,27,120,pixShanshuo_W);

//                //油量
//                pixShanshuo_W.load("./img/ranyou/07.png");//07.jpg
//                paintShanshuo_W.drawPixmap(10,275,27,118,pixShanshuo_W);

//                //凹槽
//                pixShanshuo_W.load("./img/aocao/05.png");//07.jpg
//                paintShanshuo_W.drawPixmap(760,275,28,119,pixShanshuo_W);

                //喂入
                QPainter paintShanshuo_W(this);
                QPixmap pixShanshuo_W;
 //               pixShanshuo_W.load("./img/weiruliang/09.png");//07.jpg
 //               paintShanshuo_W.drawPixmap(10,110,28,121,pixShanshuo_W);

                switch(cantest.WeiRu_Vol)
                {
                    case 1:
                    pixShanshuo_W.load("./img/weiruliang/10.png");//07.jpg
                    paintShanshuo_W.drawPixmap(10,110,28,121,pixShanshuo_W);
                    break;

                    case 2:
                    pixShanshuo_W.load("./img/weiruliang/09.png");//07.jpg
                    paintShanshuo_W.drawPixmap(10,110,28,121,pixShanshuo_W);
                    break;

                    case 3:
                    pixShanshuo_W.load("./img/weiruliang/08.png");//07.jpg
                    paintShanshuo_W.drawPixmap(10,110,28,121,pixShanshuo_W);

                    break;

                    case 4:
                    pixShanshuo_W.load("./img/weiruliang/07.png");//07.jpg
                    paintShanshuo_W.drawPixmap(10,110,28,121,pixShanshuo_W);

                    break;

                    case 5:
                    pixShanshuo_W.load("./img/weiruliang/06.png");//07.jpg
                    paintShanshuo_W.drawPixmap(10,110,28,121,pixShanshuo_W);

                    break;

                    case 6:
                    pixShanshuo_W.load("./img/weiruliang/05.png");//07.jpg
                    paintShanshuo_W.drawPixmap(10,110,28,121,pixShanshuo_W);

                    break;

                    case 7:
                    pixShanshuo_W.load("./img/weiruliang/04.png");//07.jpg
                    paintShanshuo_W.drawPixmap(10,110,28,121,pixShanshuo_W);

                    break;

                    case 8:
                    pixShanshuo_W.load("./img/weiruliang/03.png");//07.jpg
                    paintShanshuo_W.drawPixmap(10,110,28,121,pixShanshuo_W);

                    break;

                    case 9:
                    pixShanshuo_W.load("./img/weiruliang/02.png");//07.jpg
                    paintShanshuo_W.drawPixmap(10,110,28,121,pixShanshuo_W);

                    break;

                    case 10:
                    pixShanshuo_W.load("./img/weiruliang/01.png");//07.jpg
                    paintShanshuo_W.drawPixmap(10,110,28,121,pixShanshuo_W);
                    break;

                }

                //粮损
 //               pixShanshuo_W.load("./img/liangshun/06.png");//07.jpg
 //               paintShanshuo_W.drawPixmap(760,110,27,120,pixShanshuo_W);

                switch(cantest.SaLiangLV)
                {
                    case 1:
                    pixShanshuo_W.load("./img/liangshun/06.png");//07.jpg
                    paintShanshuo_W.drawPixmap(760,110,27,120,pixShanshuo_W);
                    break;

                    case 2:
                    pixShanshuo_W.load("./img/liangshun/05.png");//07.jpg
                    paintShanshuo_W.drawPixmap(760,110,27,120,pixShanshuo_W);
                    break;

                    case 3:
                    pixShanshuo_W.load("./img/liangshun/04.png");//07.jpg
                    paintShanshuo_W.drawPixmap(760,110,27,120,pixShanshuo_W);
                    break;

                    case 4:
                    pixShanshuo_W.load("./img/liangshun/03.png");//07.jpg
                    paintShanshuo_W.drawPixmap(760,110,27,120,pixShanshuo_W);
                    break;

                    case 5:
                    pixShanshuo_W.load("./img/liangshun/02.png");//07.jpg
                    paintShanshuo_W.drawPixmap(760,110,27,120,pixShanshuo_W);
                    break;

                    case 6:
                    pixShanshuo_W.load("./img/liangshun/01.png");//07.jpg
                    paintShanshuo_W.drawPixmap(760,110,27,120,pixShanshuo_W);
                    break;


                }


                //油量
 //               pixShanshuo_W.load("./img/ranyou/07.png");//07.jpg
 //               paintShanshuo_W.drawPixmap(10,275,27,118,pixShanshuo_W);

                switch(cantest.VolYL)
                {
                 case 1:
                 pixShanshuo_W.load("./img/ranyou/08.png");//07.jpg
                 paintShanshuo_W.drawPixmap(10,275,27,118,pixShanshuo_W);

                 break;
                case 2:
                pixShanshuo_W.load("./img/ranyou/07.png");//07.jpg
                paintShanshuo_W.drawPixmap(10,275,27,118,pixShanshuo_W);

                break;
                case 3:
                pixShanshuo_W.load("./img/ranyou/06.png");//07.jpg
                paintShanshuo_W.drawPixmap(10,275,27,118,pixShanshuo_W);

                break;
                case 4:
                pixShanshuo_W.load("./img/ranyou/05.png");//07.jpg
                paintShanshuo_W.drawPixmap(10,275,27,118,pixShanshuo_W);

                break;
                case 5:
                pixShanshuo_W.load("./img/ranyou/04.png");//07.jpg
                paintShanshuo_W.drawPixmap(10,275,27,118,pixShanshuo_W);

                break;
                case 6:
                pixShanshuo_W.load("./img/ranyou/03.png");//07.jpg
                paintShanshuo_W.drawPixmap(10,275,27,118,pixShanshuo_W);

                break;
                case 7:
                pixShanshuo_W.load("./img/ranyou/02.png");//07.jpg
                paintShanshuo_W.drawPixmap(10,275,27,118,pixShanshuo_W);
                break;

                case 8:
                pixShanshuo_W.load("./img/ranyou/01.png");//07.jpg
                paintShanshuo_W.drawPixmap(10,275,27,118,pixShanshuo_W);
                break;
                }

                //凹槽
 //               pixShanshuo_W.load("./img/aocao/05.png");//07.jpg
 //               paintShanshuo_W.drawPixmap(760,275,28,119,pixShanshuo_W);

                switch(cantest.m_AoBanJianXi)
                {
                     case 1:
                     pixShanshuo_W.load("./img/aocao/05.png");//07.jpg
                     paintShanshuo_W.drawPixmap(760,275,28,119,pixShanshuo_W);
                     break;
                    case 2:
                    pixShanshuo_W.load("./img/aocao/04.png");//07.jpg
                    paintShanshuo_W.drawPixmap(760,275,28,119,pixShanshuo_W);
                    break;
                    case 3:
                    pixShanshuo_W.load("./img/aocao/03.png");//07.jpg
                    paintShanshuo_W.drawPixmap(760,275,28,119,pixShanshuo_W);
                    break;
                    case 4:
                    pixShanshuo_W.load("./img/aocao/02.png");//07.jpg
                    paintShanshuo_W.drawPixmap(760,275,28,119,pixShanshuo_W);
                    break;
                    case 5:
                    pixShanshuo_W.load("./img/aocao/01.png");//07.jpg
                    paintShanshuo_W.drawPixmap(760,275,28,119,pixShanshuo_W);
                    break;
                }

            //报警灯

           QPainter paintdeng(this);
           QPixmap pixdeng;

           //左转灯
           if(cantest.flagLeft)
           {
               pixdeng.load("./img/dengshan/01.png");//
               paintdeng.drawPixmap(5,415,49,55,pixdeng);//正上方位置显示的图标
           }
           //发动机故障
           if(ecutest.flagFDJGZ_ECU)
           {
               pixdeng.load("./img/dengshan/14.png");//
               paintdeng.drawPixmap(73,435,36,23,pixdeng);//正上方位置显示的图标
           }
           //充电指示灯
           if(cantest.flagBattery)
           {
               pixdeng.load("./img/dengshan/17.png");//
               paintdeng.drawPixmap(118,434,34,24,pixdeng);//正上方位置显示的图标
           }
           //闪烁

           //远光
           if(cantest.flagYG != 0)
           {
               pixdeng.load("./img/dengshan/02.png");//
               paintdeng.drawPixmap(322,434,38,23,pixdeng);//正上方位置显示的图标
           }
           //示宽灯
           if(cantest.flagWidthlamp)
           {
               pixdeng.load("./img/dengshan/04.png");//
               paintdeng.drawPixmap(367,434,43,24,pixdeng);//正上方位置显示的图标
           }
           //近光灯
           if(cantest.flagJG != 0)
           {
               pixdeng.load("./img/dengshan/03.png");//
               paintdeng.drawPixmap(418,433,37,27,pixdeng);//正上方位置显示的图标
           }
           //发动机预热灯
           if(ecutest.flagFDJYR_ECU)
           {
               pixdeng.load("./img/dengshan/11.png");//
               paintdeng.drawPixmap(463,434,37,23,pixdeng);//正上方位置显示的图标
           }
           //籽粒回收满
           //shanshuoLM
           //if(CHK_GZ_BIT(cantest.m_extLampBitFlag,LAMP_BIT_ZhiLiHuiShou))
           if(shanshuoLM)
           {
               pixdeng.load("./img/dengshan/15.png");//
               paintdeng.drawPixmap(509,430,32,32,pixdeng);//正上方位置显示的图标
           }
           //量仓满
           if(CHK_GZ_BIT(cantest.m_extLampBitFlag,LAMP_BIT_LiangCangMan))
           {
               pixdeng.load("./img/dengshan/08.png");//
               paintdeng.drawPixmap(550,435,29,20,pixdeng);//正上方位置显示的图标
           }
           //燃油进水指示灯
           if(shanshuoYZYS)
           {
               pixdeng.load("./img/dengshan/07.png");//
               paintdeng.drawPixmap(586,432,24,28,pixdeng);//正上方位置显示的图标
           }
           //液压油压力
           if(CHK_GZ_BIT(cantest.m_extLampBitFlag,LAMP_BIT_YeYaYouYa))
           {
               pixdeng.load("./img/dengshan/99.png");//
               paintdeng.drawPixmap(619,432,15,28,pixdeng);//正上方位置显示的图标
           }
           //空滤灯
           if(cantest.flagKL)
           {
               pixdeng.load("./img/dengshan/05.png");//
               paintdeng.drawPixmap(640,430,32,32,pixdeng);//正上方位置显示的图标
           }
           //主机故障灯
           if(CHK_GZ_BIT(cantest.m_GZBitFlag,GZ_BIT_ZHUJI))
           {
               pixdeng.load("./img/dengshan/06.png");//
               paintdeng.drawPixmap(680,430,44,29,pixdeng);//正上方位置显示的图标
           }
           //右转灯
           if(cantest.flagRight)
           {
               pixdeng.load("./img/dengshan/18.png");//
               paintdeng.drawPixmap(740,415,49,55,pixdeng);//正上方位置显示的图标
           }


#if 0

           //主界面中央灯区
           //粮筒摆出
           if(CHK_GZ_BIT(cantest.m_extLampBitFlag,LAMP_BIT_LiangTongBaiChu))
           {
               pixdeng.load("./img/zhujiemianicon/01.png");//
               paintdeng.drawPixmap(255,266,30,19,pixdeng);//正上方位置显示的图标
           }
           //过桥故障
           if(CHK_GZ_BIT(cantest.m_GZBitFlag,GZ_BIT_GUOQIAO))
           {
               pixdeng.load("./img/zhujiemianicon/02.png");//
               paintdeng.drawPixmap(307,258,32,29,pixdeng);//正上方位置显示的图标
           }
           //风机故障
           if(CHK_GZ_BIT(cantest.m_GZBitFlag,GZ_BIT_FENGJI))
           {
               pixdeng.load("./img/zhujiemianicon/03.png");//
               paintdeng.drawPixmap(273,281,31,32,pixdeng);//正上方位置显示的图标
           }

           //滚筒故障
           if(CHK_GZ_BIT(cantest.m_GZBitFlag,GZ_BIT_GUNTONG))
           {
               pixdeng.load("./img/zhujiemianicon/04.png");//
               paintdeng.drawPixmap(288,322,31,28,pixdeng);//正上方位置显示的图标
           }
           //刹车盘磨损
            if(CHK_GZ_BIT(cantest.m_GZBitFlag,GZ_BIT_SHACHEPANMOSUN))
           {
               pixdeng.load("./img/zhujiemianicon/05.png");//
               paintdeng.drawPixmap(294,355,30,24,pixdeng);//正上方位置显示的图标
           }
           //升运器故障
           if(CHK_GZ_BIT(cantest.m_GZBitFlag,GZ_BIT_SHENGYUNQI))
           {
               pixdeng.load("./img/zhujiemianicon/06.png");//
               paintdeng.drawPixmap(463,258,31,25,pixdeng);//正上方位置显示的图标
           }

           //卸粮中
           if(CHK_GZ_BIT(cantest.m_extLampBitFlag,LAMP_BIT_XieLiangZhong))
           {
               pixdeng.load("./img/zhujiemianicon/07.png");//
               paintdeng.drawPixmap(513,260,34,24,pixdeng);//正上方位置显示的图标
           }
           //粮仓盖
           if(CHK_GZ_BIT(cantest.m_GZBitFlag,GZ_BIT_LIANGCANGGAI))
           {
               pixdeng.load("./img/zhujiemianicon/08.png");//
               paintdeng.drawPixmap(499,292,27,23,pixdeng);//正上方位置显示的图标
           }
           //液压滤清
           if(CHK_GZ_BIT(cantest.m_extLampBitFlag,LAMP_BIT_YeYaLvQing))
           {
               pixdeng.load("./img/zhujiemianicon/09.png");//
               paintdeng.drawPixmap(490,319,16,28,pixdeng);//正上方位置显示的图标
           }
           //刹车制动故障
           if(CHK_GZ_BIT(cantest.m_GZBitFlag,GZ_BIT_SHACHEZHIDONG))
           {
               pixdeng.load("./img/zhujiemianicon/10.png");//
               paintdeng.drawPixmap(475,355,31,24,pixdeng);//正上方位置显示的图标
           }

#endif
           //2017.5.21 闪烁


           //主界面中央灯区
           //粮筒摆出
           if(CHK_GZ_BIT(cantest.m_extLampBitFlag,LAMP_BIT_LiangTongBaiChu))
           {
               pixdeng.load("./img/zhujiemianicon/01.png");//
               paintdeng.drawPixmap(255,266,30,19,pixdeng);//正上方位置显示的图标
           }
           //过桥故障

           if(shanshuoguoqiao)
           {
               pixdeng.load("./img/zhujiemianicon/02.png");//
               paintdeng.drawPixmap(307,258,32,29,pixdeng);//正上方位置显示的图标
           }
           //风机故障

           if(shanshuofengji)
           {
               pixdeng.load("./img/zhujiemianicon/03.png");//
               paintdeng.drawPixmap(273,281,31,32,pixdeng);//正上方位置显示的图标
           }

           //滚筒故障

           if(shanshuoGunTong)
           {
               pixdeng.load("./img/zhujiemianicon/04.png");//
               paintdeng.drawPixmap(288,322,31,28,pixdeng);//正上方位置显示的图标
           }
           //刹车盘磨损
            if(CHK_GZ_BIT(cantest.m_GZBitFlag,GZ_BIT_SHACHEPANMOSUN))
           {
               pixdeng.load("./img/zhujiemianicon/05.png");//
               paintdeng.drawPixmap(294,355,30,24,pixdeng);//正上方位置显示的图标
           }
           //升运器故障

           if(shanshuoShengyun)
           {
               pixdeng.load("./img/zhujiemianicon/06.png");//
               paintdeng.drawPixmap(463,258,31,25,pixdeng);//正上方位置显示的图标
           }

           //卸粮中
           if(CHK_GZ_BIT(cantest.m_extLampBitFlag,LAMP_BIT_XieLiangZhong))
           {
               pixdeng.load("./img/zhujiemianicon/07.png");//
               paintdeng.drawPixmap(513,260,34,24,pixdeng);//正上方位置显示的图标
           }
           //粮仓盖

           if(CHK_GZ_BIT(cantest.m_GZBitFlag,GZ_BIT_LIANGCANGGAI))
           {
               pixdeng.load("./img/zhujiemianicon/08.png");//
               paintdeng.drawPixmap(499,292,27,23,pixdeng);//正上方位置显示的图标
           }
           //液压滤清
           if(CHK_GZ_BIT(cantest.m_extLampBitFlag,LAMP_BIT_YeYaLvQing))
           {
               pixdeng.load("./img/zhujiemianicon/09.png");//
               paintdeng.drawPixmap(490,319,16,28,pixdeng);//正上方位置显示的图标
           }
           //刹车制动故障
           if(CHK_GZ_BIT(cantest.m_GZBitFlag,GZ_BIT_SHACHEZHIDONG))
           {
               pixdeng.load("./img/zhujiemianicon/10.png");//
               paintdeng.drawPixmap(475,355,31,24,pixdeng);//正上方位置显示的图标
           }



           //闪烁控制

           //手刹
           if(shanshuoSS)
           {
               pixdeng.load("./img/dengshan/13.png");//
               paintdeng.drawPixmap(278,433,37,29,pixdeng);//正上方位置显示的图标
           }
            if(shanshuoSW)//水温 0~120度  95度以上报警。
            {
                pixdeng.load("./img/dengshan/09.png");//
                paintdeng.drawPixmap(161,432,31,28,pixdeng);//正上方位置显示的图标
            }

            if(shanshuoJYYL) //机油  油压报警 0～1 MPa,在0.1 MPa 以下为报警区。
            {
                pixdeng.load("./img/dengshan/12.png");//
                paintdeng.drawPixmap(200,436,39,20,pixdeng);//正上方位置显示的图标
            }

            if (shanshuoYL)//油量
            {
                pixdeng.load("./img/dengshan/10.png");//
                paintdeng.drawPixmap(248,430,24,28,pixdeng);//正上方位置显示的图标
            }

            //2017.5.15 当油量为1时，蜂鸣器响一声，油量指示灯常亮
            if(cantest.VolYL == 1)//油量
            {
                pixdeng.load("./img/dengshan/10.png");//
                paintdeng.drawPixmap(248,430,24,28,pixdeng);//正上方位置显示的图标
            }

            //油中右水  油水分离  需要闪烁
            if(shanshuoYZYS)
            {
                pixdeng.load("./img/dengshan/07.png");//
                paintdeng.drawPixmap(586,432,24,28,pixdeng);//正上方位置显示的图标
            }


            //2017.5.18
            //粮食损失
            if(shanshuoLiangshun)
            {
                pixdeng.load("./img/dengshan/t1.png");//
                paintdeng.drawPixmap(757,77,31,28,pixdeng);//正上方位置显示的图标
            }

            //2017.5.24
            //充电指示灯  //闪烁

            if(shangshuoChongdian)
            {
                pixdeng.load("./img/dengshan/17.png");//
                paintdeng.drawPixmap(118,434,34,24,pixdeng);//正上方位置显示的图标
            }


            //液压油温
            if(shanshuoYYYW)//液压油温  cantest.VolYeyayouwen
            {

            }


            }//end of if(flagmatchion == YZB_4_5_7_8)

            else if(flagmatchion == S3000)
            {
                   //int side = qMin(width(), height());  //绘制的范围(宽、高中最小值)

                   painter.setRenderHint(QPainter::Antialiasing);//绘制的图像反锯齿
                   //painter.translate(width() / 2, height() / 2);//重新定位坐标起始点，把坐标原点放到窗体的中央

                   //painter.translate(405, 184);//重新定位坐标起始点，把坐标原点放到窗体的中央
                    painter.translate(210, 363);//重新定位坐标起始点，把坐标原点放到窗体的中央
                   //painter.scale(side / 400.0, side / 300.0);//设定画布的边界,用窗体宽高的最小值来计算时钟的大小，防止窗体拉伸导致的时钟变形以及显示不全

                   //下面两个数组用来定义表针的两个顶点，以便后面的填充
                   static const QPoint hourHand[4] = {
                       QPoint(8, 0),
                       QPoint(-8,0),
                       QPoint(-1.5, -160),
                       QPoint(1.5, -160)
                   };
                   static const QPoint minuteHand[4] = {
                       QPoint(4, 0),
                       QPoint(-4, 0),
                       QPoint(-1, -55),
                       QPoint(1, -55)
                   };

                   //机油压力

                   painter.setPen(Qt::NoPen);//填充时针，不需要边线所以NoPen
                   painter.setBrush(Qt::red);
                   painter.setRenderHint(QPainter::Antialiasing, true);
                   painter.save();
                   //painter.rotate(6.0 *time.second());  //设旋转(角度 = 6° * (分钟 + 秒 / 60))
                   painter.rotate(-114.5);
                   //painter.rotate(6.0 *numtmp);  //设置旋转(6° * 秒)
                   //painter.rotate(numtmp++);  //设置旋转(6° * 秒)
                   //painter.rotate(4.0 );//*shisu

                   //painter.rotate(8*nu1);//floatnu2
                   painter.rotate(228*floatnu3);//floatnu1

                   painter.drawConvexPolygon(minuteHand, 4);  //填充分针部分
                   painter.restore();

                   /***********************************************/
                   //2016.6.25   画白圈
                   painter.setBrush(Qt::darkGray); //画上中心原点/home/vmuser/qtworkplace/chanpin/img2
                   painter.save();
                   painter.drawEllipse(QPoint(0,0),13,13);
                   painter.restore();

                   //画白圈
                   /***********************************************/

                   painter.setBrush(Qt::black);//画上中心原点/home/vmuser/qtworkplace/chanpin/img2
                   painter.save();
                   painter.drawEllipse(QPoint(0,0),10,10);
                   painter.restore();


                   //油量
                   painter.translate(380,3);//重新定位坐标起始点，把坐标原点放到窗体的中央
                   //painter.scale(side / 400.0, side / 300.0);

                   painter.setPen(Qt::NoPen);
                   painter.setBrush(Qt::red);
                   painter.setRenderHint(QPainter::Antialiasing, true);
                   painter.save();

                   //painter.rotate(6.0 *time.second());  //设旋转(角度 = 6° * (分钟 + 秒 / 60))
                   painter.rotate(-114.5);
                   //painter.rotate(8*nu3);
                   painter.rotate(7.6*nu1);//



                   //painter.rotate(4.0 );  //设旋转(角度 = 6° * (分钟 + 秒 / 60))*shisu
                   //内测用
                   /****************************************************************************/
                   //qDebug()<<"time: "<<time.second()<<endl;

                   /****************************************************************************/

                   painter.drawConvexPolygon(minuteHand, 4);  //填充分针部分
                   painter.setRenderHint(QPainter::Antialiasing, true);
                   painter.restore();

                   /***********************************************/
                   //2016.6.25   画白圈
                   painter.setBrush(Qt::darkGray); //画上中心原点/home/vmuser/qtworkplace/chanpin/img2
                   painter.save();
                   painter.drawEllipse(QPoint(0,0),13,13);
                   painter.restore();

                   //画白圈
                   /***********************************************/


                   painter.setBrush(Qt::black);
                   painter.save();//画上中心原点
                   painter.drawEllipse(QPoint(0,0),10,10);
                   painter.restore();

                   //KM/H
                   painter.translate(-190,-36);//重新定位坐标起始点，把坐标原点放到窗体的中央
                   //painter.scale(side / 400.0, side / 300.0);

                   painter.setPen(Qt::NoPen);
                   painter.setBrush(Qt::red);
                   painter.setRenderHint(QPainter::Antialiasing, true);
                   painter.save();

                   //painter.rotate(6.0 *time.second());  //设旋转(角度 = 6° * (分钟 + 秒 / 60))
                   painter.rotate(-114);
                   //painter.rotate(8*nu3);
                   painter.rotate(7.6*nu3);//



                   //painter.rotate(4.0 );  //设旋转(角度 = 6° * (分钟 + 秒 / 60))*shisu
                   //内测用
                   /****************************************************************************/
                   //qDebug()<<"time: "<<time.second()<<endl;

                   /****************************************************************************/

                   painter.drawConvexPolygon(minuteHand, 4);  //填充分针部分
                   painter.setRenderHint(QPainter::Antialiasing, true);
                   painter.restore();

                   /***********************************************/
                   //2016.6.25   画白圈
                   painter.setBrush(Qt::darkGray); //画上中心原点/home/vmuser/qtworkplace/chanpin/img2
                   painter.save();
                   painter.drawEllipse(QPoint(0,0),13,13);
                   painter.restore();

                   //画白圈
                   /***********************************************/


                   painter.setBrush(Qt::black);
                   painter.save();//画上中心原点
                   painter.drawEllipse(QPoint(0,0),10,10);
                   painter.restore();

                   //处理图片闪烁
                   painter.translate(-390,-226);//平移到左边角

               //报警灯
              QPainter paintdeng(this);
              QPixmap pixdeng;
              //左转灯
              if(cantest.flagLeft)
              {
                  pixdeng.load("./img/dengshan/01.png");//
                  paintdeng.drawPixmap(5,415,49,55,pixdeng);//正上方位置显示的图标
              }
              //发动机故障
              if(ecutest.flagFDJGZ_ECU)
              {
                  pixdeng.load("./img/dengshan/14.png");//
                  paintdeng.drawPixmap(73,435,36,23,pixdeng);//正上方位置显示的图标
              }
              //充电指示灯
              if(cantest.flagBattery)
              {
                  pixdeng.load("./img/dengshan/17.png");//
                  paintdeng.drawPixmap(118,434,34,24,pixdeng);//正上方位置显示的图标
              }

              //手刹
              if(cantest.flagSS)
              {
                  pixdeng.load("./img/dengshan/13.png");//
                  paintdeng.drawPixmap(278,433,37,29,pixdeng);//正上方位置显示的图标
              }
              //远光
              if(cantest.flagYG)
              {
                  pixdeng.load("./img/dengshan/02.png");//
                  paintdeng.drawPixmap(322,434,38,23,pixdeng);//正上方位置显示的图标
              }
              //示宽灯
              if(cantest.flagWidthlamp)
              {
                  pixdeng.load("./img/dengshan/04.png");//
                  paintdeng.drawPixmap(367,434,43,24,pixdeng);//正上方位置显示的图标
              }
              //近光灯
              if(cantest.flagJG)
              {
                  pixdeng.load("./img/dengshan/03.png");//
                  paintdeng.drawPixmap(418,433,37,27,pixdeng);//正上方位置显示的图标
              }
              //发动机预热灯
              if(ecutest.flagFDJYR_ECU)
              {
                  pixdeng.load("./img/dengshan/11.png");//
                  paintdeng.drawPixmap(463,434,37,23,pixdeng);//正上方位置显示的图标
              }
//              //量满
//              if(1)
//              {
//                  pixdeng.load("./img/dengshan/15.png");//
//                  paintdeng.drawPixmap(509,430,32,32,pixdeng);//正上方位置显示的图标
//              }
   //           //粮仓满
   //           if(1)
   //           {
   //               pixdeng.load("./img/dengshan/08.png");//
   //               paintdeng.drawPixmap(550,435,29,20,pixdeng);//正上方位置显示的图标
   //           }
              //燃油进水指示灯
              if(shanshuoYZYS)
              {
                  pixdeng.load("./img/dengshan/07.png");//
                  paintdeng.drawPixmap(586,432,24,28,pixdeng);//正上方位置显示的图标
              }
              //液压油压力
              if(CHK_GZ_BIT(cantest.m_extLampBitFlag,LAMP_BIT_YeYaYouYa))
              {
                  pixdeng.load("./img/dengshan/99.png");//
                  paintdeng.drawPixmap(616,432,15,28,pixdeng);//正上方位置显示的图标
              }
   //           //空滤灯
   //           if(1)
   //           {
   //               pixdeng.load("./img/dengshan/05.png");//
   //               paintdeng.drawPixmap(640,430,32,32,pixdeng);//正上方位置显示的图标
   //           }
//              //草箱限制
//              if(1)
//              {
//                  pixdeng.load("./img/dengshan/19.png");//
//                  paintdeng.drawPixmap(643,431,34,26,pixdeng);//正上方位置显示的图标
//              }

              //刹车自动故障
               if(CHK_GZ_BIT(cantest.m_GZBitFlag,GZ_BIT_SHACHEZHIDONG))
              {
                  pixdeng.load("./img/zhujiemianicon/10.png");//
                  paintdeng.drawPixmap(643,434,31,24,pixdeng);//正上方位置显示的图标
              }

              //右转灯
              if(cantest.flagRight)
              {
                  pixdeng.load("./img/dengshan/18.png");//
                  paintdeng.drawPixmap(740,415,49,55,pixdeng);//正上方位置显示的图标
              }


              //闪烁控制
               if(shanshuoSW)//水温 0~120度  95度以上报警。
               {
                   pixdeng.load("./img/dengshan/09.png");//
                   paintdeng.drawPixmap(161,432,31,28,pixdeng);//正上方位置显示的图标
               }

               if(shanshuoJYYL) //机油  油压报警 0～1 MPa,在0.1 MPa 以下为报警区。
               {
                   pixdeng.load("./img/dengshan/12.png");//
                   paintdeng.drawPixmap(200,436,39,20,pixdeng);//正上方位置显示的图标
               }

               if (shanshuoYL)//油量
               {
                   pixdeng.load("./img/dengshan/10.png");//
                   paintdeng.drawPixmap(248,430,24,28,pixdeng);//正上方位置显示的图标
               }

               //油中右水  油水分离  需要闪烁
               if(shanshuoYZYS)
               {
                   pixdeng.load("./img/dengshan/07.png");//
                   paintdeng.drawPixmap(586,432,24,28,pixdeng);//正上方位置显示的图标
               }

               //液压油温
               if(shanshuoYYYW)//液压油温  cantest.VolYeyayouwen
               {

               }


              //显示油量，机油压力，小时计 等要显示的值
              //
              //机油压力
             // ui->label_7->setText("jiyouyali");


            }//end of if(flagmatchion == YZB_4_5_7_8)


        }//end of if(flagwidget == xingZouWidget)

        //油温，发动机转速，小时计，KM/H，油量


        //电池电压
        DCDY =cantest.VOLV;
        DCDY /= 10;
        //label_11 he label_14 处理
        if((flagmatchion == YZT_10)||(flagmatchion == YZT_5)||(flagmatchion == JZ_3600))
        {
            ui->label_14->setText(QString::number(DCDY,'f',1));//系统电压
            ui->label_11->setText(QString::number(cantest.m_Speed[SPEED_FENGJI]));//风机转速
            if(flagmatchion != JZ_3600)
            {
                ui->label_21->setText(QString::number(cantest.m_Speed[SPEED_GUNTONG]));//滚筒转速
            }
            else
            {
                ui->label_21->setText("");//滚筒转速
            }
        }
        else
        {
            ui->label_11->setText(QString::number(DCDY,'f',1));//风机转速
            ui->label_14->setText("");//系统电压
            ui->label_21->setText("");//滚筒转速
        }


        //机油压力
//        JYYL = ecutest.VolJYYL;
//        JYYL = JYYL/1000;
//        ui->label_10->setText(QString::number(JYYL,'f',2));//机油压力

//        //机油温度
//        ui->label_7->setText(QString::number(ecutest.VolJYWD));

        //总里程
        //显示 里程
        lichengsum = cantest.VolLICHENG;
        lichengsum /= 10;
        ui->label_9->setText(QString::number(lichengsum));//里程

//        //发动机转速
//        if(ecutest.FDJ_speed > 3000)
//        {
//           ui->label_6->setText(QString::number(3000));// r/min
//        }
//        else
//        {
//            ui->label_6->setText(QString::number(ecutest.FDJ_speed));// r/min
//        }

        //2017.4.17 瞬时油耗

        shunshiyouhaoInt = ecutest.m_InsFuelVal*10;
        shunshiyouhaoFloat = shunshiyouhaoInt;
        shunshiyouhaoFloat = shunshiyouhaoFloat / 10;

        ui->label_6->setText(QString::number(shunshiyouhaoFloat,'f',1));
        //qDebug()<<"ecutest.m_InsFuelVal ========================  "<<ecutest.m_InsFuelVal<<endl;

        //KM/H
        float floatworknu4 = (cantest.HourSpeed);///100
        //floatworknu4 /= 10;
        if(floatworknu4 > 30)
        {
            floatworknu4 = 30;
        }

        //单次里程 和 总里程
        ui->label_8->setText(QString::number(cantest.MIJI));// 单次里程floatworknu4,'f',1
        ui->label_9->setText(QString::number(cantest.VolMIJISUM));//总里程

        //        //油量
        //        YLBFB = cantest.VolYL;
        //        YLBFB *= 12.5;

        //        if(YLBFB > 100)
        //        {
        //             ui->label_11->setText(QString::number(100));
        //        }
        //        else
        //        {
        //             ui->label_11->setText(QString::number(YLBFB));
        //        }


        //2017.4.15

        //处理label_20
        if(flagmatchion == YZT_10) //过桥转速
        {
            ui->label_20->setText(QString::number(cantest.m_Speed[SPEED_GUOQIAO]));
            ui->label_10->setText(QString::number(cantest.m_Speed[SPEED_JIAOLONG]));//处理label_10 搅龙转速
        }
        else if(flagmatchion == YZT_5)//主力合工作时间
        {
            ui->label_20->setText(QString::number(cantest.m_ZhuLiHeWorkTime));
            ui->label_10->setText(QString::number(cantest.m_Speed[SPEED_SHENGYUNQI]));//处理label_10 升运器转速
        }
        else if(flagmatchion == JZ_3600)//割台转速
        {
           ui->label_10->setText(QString::number(cantest.m_Speed[SPEED_GETAI]));
           ui->label_20->setText(" ");
        }
        else //工作时间
        {
#if 0
            xiaoshijiLongLong = ecutest.m_EcuWorkTime;
            xiaoshijiLongLong *= 10;
            xiaoshijiDouble = xiaoshijiLongLong;
            xiaoshijiDouble /= 10;
#endif

            ui->label_10->setText(QString::number(xiaoshijiDouble,'f',1));
            ui->label_20->setText(" ");
        }

        //处理label_6 瞬时油耗
        //ui->label_6->setText(QString::number());


/*************************************************************************************************************/
     /*设置系统时间*/
    if(timeSetOK == true)
    {
        //日期
        QString str1 = """";
        str1 += "date -s ";
        str1 += dateBuffer;
        str1 += """";
        system(str1.toLatin1().data());

        //时间
        QString str2 = """";
        str2 += "date -s ";
        //str2 += DateTimeSetup.mid(11,9);
        str2 += timeBuffer;

        str2 += """";
        system(str2.toLatin1().data());
        system("hwclock -w");
        timeSetOK = false;

    }
/*****************************************************************************************************************/

/*****************************************************************************************************************/
//处理 Label 数据
//
//
//日期 时间 处理
    //控件显示
    //显示时间 。2017.1.14
    QString timeStr1= QTime::currentTime().toString();     //绘制当前的时间
    QString dateStr1 = QDate::currentDate().toString("yyyy-MM-dd");//dddd
    QString dddd = QDate::currentDate().toString("dddd");//

    ui->label_3->setText(dateStr1);
    ui->label_13->setText(timeStr1);

    //qDebug()<<"dddd == "<<dddd<<endl;

    //arm 板子汉化
    if(dddd == "Monday")
    {
        ui->label_12->setText("星期一");
    }
    else if(dddd == "Tuesday")
    {
        ui->label_12->setText("星期二");
    }
    else if(dddd == "Wednesday")
    {
        ui->label_12->setText("星期三");
    }
    else if(dddd == "Thursday")
    {
        ui->label_12->setText("星期四");
    }
    else if(dddd == "Friday")
    {
        ui->label_12->setText("星期五");
    }
    else if(dddd == "Saturday")
    {
        ui->label_12->setText("星期六");
    }
    else if(dddd == "Sunday")
    {
        ui->label_12->setText("星期日");
    }

/***************************************************************************************************************/


/***************************************************************************************************************/
                             if(flagwidget == PipeixingbiaodingMenu)
                   //if(1)
                              {

                                  //SendReqCmdToController(GUI_CMD_CFG_REQ_XinZouLaGan_Data,langanoffset);
                                  //qDebug()<<"uuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuxxxxxxxxxxxxxxxxxxxxxx"<<endl;
                                 /****************************添加最小值，最大值，中间值，偏移量*******************************************************/
                                 //2017.4.26
                                     //ui->tableWidget_3->setItem(0,0,new QTableWidgetItem("99"));
#if 0
                                 ui->tableWidget_3->setItem(0,1,new QTableWidgetItem(QString::number(biaoding.m_XinZouJubing[BD_VALUE_RealValue])));
                                 ui->tableWidget_3->setItem(0,2,new QTableWidgetItem(QString::number(biaoding.m_XinZouJubing[BD_VALUE_Maximum])));
                                 ui->tableWidget_3->setItem(0,3,new QTableWidgetItem(QString::number(biaoding.m_XinZouJubing[BD_VALUE_Median])));
                                 ui->tableWidget_3->setItem(0,4,new QTableWidgetItem(QString::number(biaoding.m_XinZouJubing[BD_VALUE_Minimum])));
                                 ui->tableWidget_3->setItem(0,5,new QTableWidgetItem(QString::number(shoubingoffset)));


                                 //ui->tableWidget_3->setItem(1,0,new QTableWidgetItem(10));
                                 ui->tableWidget_3->setItem(1,1,new QTableWidgetItem(QString::number(biaoding.m_XinZouLaGan[BD_VALUE_RealValue])));
                                 ui->tableWidget_3->setItem(1,2,new QTableWidgetItem(QString::number(biaoding.m_XinZouLaGan[BD_VALUE_Maximum])));
                                 ui->tableWidget_3->setItem(1,3,new QTableWidgetItem(QString::number(biaoding.m_XinZouLaGan[BD_VALUE_Median])));
                                 ui->tableWidget_3->setItem(1,4,new QTableWidgetItem(QString::number(biaoding.m_XinZouLaGan[BD_VALUE_Minimum])));
                                 ui->tableWidget_3->setItem(1,5,new QTableWidgetItem(QString::number(langanoffset)));

                                 //ui->tableWidget_3->setItem(2,0,new QTableWidgetItem(10));
                                 ui->tableWidget_3->setItem(2,1,new QTableWidgetItem(QString::number(biaoding.m_AoBanJianXi[BD_VALUE_RealValue])));
                                 ui->tableWidget_3->setItem(2,2,new QTableWidgetItem(QString::number(biaoding.m_AoBanJianXi[BD_VALUE_Maximum])));
                                 //ui->tableWidget_3->setItem(2,3,new QTableWidgetItem(QString::number(biaoding.m_AoBanJianXi[BD_VALUE_Maximum])));
                                 ui->tableWidget_3->setItem(2,4,new QTableWidgetItem(QString::number(biaoding.m_AoBanJianXi[BD_VALUE_Minimum])));
                                 //ui->tableWidget_3->setItem(2,5,new QTableWidgetItem(" "));//QString::number(biaoding.m_AoBanJianXi[BD_VALUE_Offset]
#endif
#if 1
                                 ui->tableWidget_3->setItem(0,1,new QTableWidgetItem(QString::number(ShoubingShijizhi)));
                                 ui->tableWidget_3->setItem(0,2,new QTableWidgetItem(QString::number(shoubingzuida)));
                                 ui->tableWidget_3->setItem(0,3,new QTableWidgetItem(QString::number(shoubingzhongjian)));
                                 ui->tableWidget_3->setItem(0,4,new QTableWidgetItem(QString::number(shoubingzuixiao)));
                                 ui->tableWidget_3->setItem(0,5,new QTableWidgetItem(QString::number(shoubingoffset)));


                                 //ui->tableWidget_3->setItem(1,0,new QTableWidgetItem(10));
                                 ui->tableWidget_3->setItem(1,1,new QTableWidgetItem(QString::number(XingzhoubengShijizhi)));
                                 ui->tableWidget_3->setItem(1,2,new QTableWidgetItem(QString::number(xingzhouzuida)));
                                 ui->tableWidget_3->setItem(1,3,new QTableWidgetItem(QString::number(xingzhouzhongjian)));
                                 ui->tableWidget_3->setItem(1,4,new QTableWidgetItem(QString::number(xingzhouzuixiao)));
                                 ui->tableWidget_3->setItem(1,5,new QTableWidgetItem(QString::number(langanoffset)));

                                 //ui->tableWidget_3->setItem(2,0,new QTableWidgetItem(10));
                                 ui->tableWidget_3->setItem(2,1,new QTableWidgetItem(QString::number(biaoding.m_AoBanJianXi[BD_VALUE_RealValue])));
                                 ui->tableWidget_3->setItem(2,2,new QTableWidgetItem(QString::number(biaoding.m_AoBanJianXi[BD_VALUE_Maximum])));
                                 //ui->tableWidget_3->setItem(2,3,new QTableWidgetItem(QString::number(biaoding.m_AoBanJianXi[BD_VALUE_Maximum])));
                                 ui->tableWidget_3->setItem(2,4,new QTableWidgetItem(QString::number(biaoding.m_AoBanJianXi[BD_VALUE_Minimum])));
                                 //ui->tableWidget_3->setItem(2,5,new QTableWidgetItem(" "));//QString::number(biaoding.m_AoBanJianXi[BD_VALUE_Offset]
#endif

                                 /***************************************************************************************************************/

/***************************************************************************************************************/
     if((LCPiPeixingBiaoDing == 1)&&(FlagShouBing ==0))
     {
         ui->label_17->setText("请按F5开始标定手柄");
     }
     else if((LCPiPeixingBiaoDing == 1)&&(FlagShouBing ==1))
     {
         ui->label_17->setText("请推动手柄到最大位置等待");         
         SendReqCmdToController(GUI_CMD_CFG_REQ_XinZouJuBing_Data,0);
         GetRspDataFromController(&biaoding);
     }

     //2017.4.28
     else if((LCPiPeixingBiaoDing ==1)&&(FlagShouBing ==2))
     {
         ui->label_17->setText("请推动手柄到最小位置等待");
         SendReqCmdToController(GUI_CMD_CFG_REQ_XinZouJuBing_Data,0);
         GetRspDataFromController(&biaoding);

         qDebug()<<"jddddddddddddddddddddddddddddddddddddddddddddddddddddd ====  "<<LCPiPeixingBiaoDing<<endl;
     }
     else if((LCPiPeixingBiaoDing ==1)&&(FlagShouBing ==3))
     {
        ui->label_17->setText("手柄标定完成");

        //2017.5.24
        //FlagShouBing = 0;
     }
     //

     else if((LCPiPeixingBiaoDing == 2)&&(FlagXingzouBeng ==0))
     {
         ui->label_17->setText("按F5键开始标定行走泵杆");

     }
     else if((LCPiPeixingBiaoDing == 2)&&(FlagXingzouBeng ==1))
     {
          ui->label_17->setText("行走泵校准中");
          //拉杆
          SendReqCmdToController(GUI_CMD_CFG_REQ_XinZouLaGan_Data,0);
          GetRspDataFromController(&biaoding);

     }
     else if((LCPiPeixingBiaoDing == 2)&&(FlagXingzouBeng ==2))
     {
         ui->label_17->setText("行走泵校准中");
         //拉杆
         SendReqCmdToController(GUI_CMD_CFG_REQ_XinZouLaGan_Data,0);
         GetRspDataFromController(&biaoding);

     }
     else if((LCPiPeixingBiaoDing == 2)&&(FlagXingzouBeng ==3))
     {
          ui->label_17->setText("行走泵校准完成");
          //2017.5.24
          //FlagXingzouBeng = 0;
     }

     else if((LCPiPeixingBiaoDing == 3)&&(FlagAoBanjianxi ==0))
     {
         ui->label_17->setText("按F5键开始标定凹板间隙");
     }
     else if((LCPiPeixingBiaoDing == 3)&&(FlagAoBanjianxi ==1))
     {
         ui->label_17->setText("请按住凹板间隙增大调整开关并等待");
     }
     else if((LCPiPeixingBiaoDing == 3)&&(FlagAoBanjianxi ==2))
     {
         ui->label_17->setText("请按住凹板间隙减少开关并等待");
     }
     else if((LCPiPeixingBiaoDing == 3)&&(FlagAoBanjianxi ==3))
     {
         ui->label_17->setText("凹板间隙标定完成");

         //FlagAoBanjianxi =3;
     }




    //偏移量
    else if((LCPiPeixingBiaoDing == 4)||(LCPiPeixingBiaoDing == 5))
    {
       ui->label_17->setText(" ");
    }

}

/**************************************************************************************************/


        if(flagwidget == SystemMenu)
        {

        }

#endif

/*************************************************************************************************************/
//
//
//2017.3.6
//
        //计算 存储油量状态和通信故障状态 的长度
        if((ecutest.flagECU == 0)&&(cantest.StaYL != 0))
        {
            lengthYX = 1;
        }
        else if((ecutest.flagECU == 1)&&(cantest.StaYL != 0))
        {
            lengthYX = 2;
        }
        else if((ecutest.flagECU == 1)&&(cantest.StaYL == 0))
        {
            lengthYX = 1;
        }
        if((ecutest.flagECU == 0)&&(cantest.StaYL == 0))
        {
            lengthYX = 0;
        }

        //油量状态位 0 正常，通信没有故障 为0.
        //通信故障判断


        // qDebug()<<"cantest.StaYL == "<<cantest.StaYL<<endl;

        //只显示故障码
        if((ecutest.flagECU == 0)&&(cantest.StaYL == 0))
        {
            memcpy(AddSum[0],ecutest.spn_can.chgzm[0],(ecutest.spn_can.cnt)*sizeof(ecutest.spn_can.chgzm[0]));

        }

        //油量开路
        else if((ecutest.flagECU == 0)&&(cantest.StaYL == 1))
        {
            memcpy(YouAndTongxinArray[0],p2,sizeof(YouAndTongxinArray[0]));
            memcpy(AddSum[0],ecutest.spn_can.chgzm[0],(ecutest.spn_can.cnt)*sizeof(ecutest.spn_can.chgzm[0]));
            memcpy(AddSum[ecutest.spn_can.cnt],YouAndTongxinArray[0],lengthYX*sizeof(YouAndTongxinArray[0]));
        }
        //油量短路
        else if((ecutest.flagECU == 0)&&(cantest.StaYL == 2))
        {
           memcpy(YouAndTongxinArray[0],p3,sizeof(YouAndTongxinArray[0]));
            memcpy(AddSum[0],ecutest.spn_can.chgzm[0],(ecutest.spn_can.cnt)*sizeof(ecutest.spn_can.chgzm[0]));
            memcpy(AddSum[ecutest.spn_can.cnt],YouAndTongxinArray[0],lengthYX*sizeof(YouAndTongxinArray[0]));
        }
        //油量异常
        else if((ecutest.flagECU == 0)&&(cantest.StaYL == 3))
        {
            memcpy(YouAndTongxinArray[0],p4,sizeof(YouAndTongxinArray[0]));
            memcpy(AddSum[0],ecutest.spn_can.chgzm[0],(ecutest.spn_can.cnt)*sizeof(ecutest.spn_can.chgzm[0]));
            memcpy(AddSum[ecutest.spn_can.cnt],YouAndTongxinArray[0],lengthYX*sizeof(YouAndTongxinArray[0]));
        }
        //剧中显示 油量和通讯故障
        else if((ecutest.flagECU == 1)&&(cantest.StaYL == 0))
        {
            memcpy(YouAndTongxinArray[0],p1,sizeof(YouAndTongxinArray[0]));
        }
        else if((ecutest.flagECU == 1)&&(cantest.StaYL != 0))
        {
            memcpy(YouAndTongxinArray[0],p1,sizeof(YouAndTongxinArray[0]));
            switch(cantest.StaYL)
            {
                case 1:
                memcpy(YouAndTongxinArray[1],p2,sizeof(YouAndTongxinArray[0]));
                break;

                case 2:
                    memcpy(YouAndTongxinArray[1],p3,sizeof(YouAndTongxinArray[0]));
                    break;
                case 3:
                    memcpy(YouAndTongxinArray[1],p4,sizeof(YouAndTongxinArray[0]));
                    break;
                default:
                    break;
            }

        }


/*************************************************************************************************************/

//从数据库读出机型
/***************************************************************************************************************************************************/
//读取数据库信息
//
#if 0
                QTextCodec::setCodecForTr(QTextCodec::codecForLocale());//汉字显示
                QSqlDatabase db;
                if(QSqlDatabase::contains("qt_sql_default_connection"))
                  db = QSqlDatabase::database("qt_sql_default_connection");
                else
                  db = QSqlDatabase::addDatabase("QSQLITE");

               db.setDatabaseName("jy.db");
               if (!db.open())
               {
                   qDebug()<<"open database failed ---"<<db.lastError().text()<<"/n";
               }
               QSqlQuery query;
#endif

            #if 0
               bool ok = query.exec("create table myjy10(id INTEGER,name varchar,age INTEGER)");
               if (ok)
               {
                   qDebug()<<"ceate table partition success"<<endl;
               }
               else
               {
                   qDebug()<<"ceate table partition failed"<<endl;
               }
            #endif
                    //query.prepare("INSERT INTO myjy10 (id, name, age) VALUES (:id, :name, :age)");

                    uchar flagi = 0;
                    query.exec("select cjswitch, engineswitch, langswitch from config");
                    while (query.next())
                    {
                        ReadConfigArry[flagi++] = query.value(0).toInt();
                    }
                    if (flagi >=3)
                    {
                        flagi = 0;
                    }

                    if(ReadConfigArry[0]==YuCai)
                    {
                       Can_set_Fdj_id(0);//设置发动机厂家ID，用于SPN中文查询

                       ui->label_18->setText("玉柴");
                    }
                    else if(ReadConfigArry[0]==WeiCai)
                    {
                        Can_set_Fdj_id(1);//设置发动机厂家ID，用于SPN中文查询
                        ui->label_18->setText("潍柴");
                    }
                    else if(ReadConfigArry[0] == XiCai)
                    {
                        Can_set_Fdj_id(2);//设置发动机厂家ID，用于SPN中文查询

                        ui->label_18->setText("锡柴");
                    }
                    else if(ReadConfigArry[0]==HangFa)
                    {
                        Can_set_Fdj_id(3);//设置发动机厂家ID，用于SPN中文查询
                        ui->label_18->setText("杭发");
                    }
                    else if(ReadConfigArry[0] == DongfangHong)
                    {
                        Can_set_Fdj_id(4);//设置发动机厂家ID，用于SPN中文查询
                        ui->label_18->setText("东方红");
                    }


            #if 0
                    i = 0;
                    for (i = 0; i < 4; i++)
                        {
                            qDebug()<<"matchine % bi "<<matchine[i]<<endl;
                        }
                    i = 0;
            #endif

            query.exec(QObject::tr("drop config"));

/****************************************************************************************************/

//发动机故障查询

#if 1
            static unsigned char nn = 1;
            #if 0
            QTextCodec::setCodecForTr(QTextCodec::codecForLocale());//汉字显示
            QSqlDatabase db;
            if(QSqlDatabase::contains("qt_sql_default_connection"))
              db = QSqlDatabase::database("qt_sql_default_connection");
            else
              db = QSqlDatabase::addDatabase("QSQLITE");

           db.setDatabaseName("jy.db");
           if (!db.open())
           {
               qDebug()<<"open database failed ---"<<db.lastError().text()<<endl;
           }
           QSqlQuery query;
            #endif

//           qDebug()<<"flagGzmclear == "<<flagGzmclear<<endl;
//           qDebug()<<"ecutest.spn_can.cnt == "<<ecutest.spn_can.cnt<<endl;

           if((flagGzmclear == true)&&((ecutest.spn_can.cnt >0)&&(ecutest.spn_can.if_data == 1)))
           {
               //qDebug()<<"insett insert insert........................................... "<<endl;
               trd = QString("select * from fdjgz where spn = %1 and fmi = %2").arg(ecutest.spn_can.spn[un]).arg(ecutest.spn_can.fmi[un]);//.arg(spnnum)
               query.exec(trd);
               if(!query.next())
               {
                    query.prepare("INSERT INTO fdjgz (spn, fmi, gzms) VALUES (:spn, :fmi, :gzms)");
                    query.bindValue(":spn",ecutest.spn_can.spn[un]);
                    query.bindValue(":fmi",ecutest.spn_can.fmi[un]);
                    query.bindValue(":gzms", ecutest.spn_can.chgzm[un]);
                    query.exec();
               }
               else
               {
                   //qDebug()<<"!query.next().................. "<<endl;

               }

                flagGzmclear = false;
           }
           else  if(flagGzmclear == false)
           {
               //query.prepare("update fdjgz set fmi = :fmi,gzms = :gzms,spn = :spn");//

               //qDebug()<<"ecutest.spn_can.if_data == "<<ecutest.spn_can.if_data<<endl;

               //qDebug()<<"ecutest.spn_can.spn[un] == "<<ecutest.spn_can.spn[un]<<"ecutest.spn_can.fmi[un]"<<ecutest.spn_can.fmi[un]<<endl;


               //query.exec("select * from fdjgz where spn = ecutest.spn_can.spn[un] and fmi = ecutest.spn_can.fmi[un]");

               trd = QString("select * from fdjgz where spn = %1 and fmi = %2").arg(ecutest.spn_can.spn[un]).arg(ecutest.spn_can.fmi[un]);//.arg(spnnum)
               query.exec(trd);//exec spn,fmi,gzms"select * from fdjgz where spn = %1".arg(4);               if(!query.next())
               if(!query.next())
               {
                    //qDebug()<<"cha zhao cha zhao"<<endl;
                    query.prepare("INSERT INTO fdjgz (spn, fmi, gzms) VALUES (:spn, :fmi, :gzms)");
                    query.bindValue(":spn",ecutest.spn_can.spn[un]);
                    query.bindValue(":fmi",ecutest.spn_can.fmi[un]);
                    query.bindValue(":gzms", ecutest.spn_can.chgzm[un]);
                    query.exec();
               }
               else
               {
                   //qDebug()<<"select select select"<<endl;
                   query.exec("select spn, fmi, gzms from fdjgz");
                   while (query.next())//指向下一条记录
                   {
                       spnItem[fdjgzcount] = query.value(0).toInt();
                       fmiItem[fdjgzcount] = query.value(1).toInt();
                       gzmItem[fdjgzcount] = query.value(2).toString();

                       if(flagGzmclear == false)
                       {
                           ui->tableWidget_2->setItem(fdjgzcount,0,new QTableWidgetItem(QString::number(spnItem[fdjgzcount])));
                           ui->tableWidget_2->setItem(fdjgzcount,1,new QTableWidgetItem(QString::number(fmiItem[fdjgzcount])));
                           ui->tableWidget_2->setItem(fdjgzcount,2,new QTableWidgetItem(gzmItem[fdjgzcount]));//(QString::fromUtf8(AddSum[fdjgzcount]))
                       }
                       fdjgzcount++;
                   }
                   fdjgzcount = 0;

               }

           }
#endif

            un++;
            if(un>=10)
            {
                un = 0;
            }

          query.exec(QObject::tr("drop fdjgz"));

/****************************************************************************************************/
/****************************************************************************************************/
//主机故障查询
#if 0
          query.prepare("update zjgz set id = :id,name = :name");//,age = :age

          query.bindValue(":id", 1);
          query.bindValue(":name","");//QObject::tr("%1").arg(66666)

          query.exec();

          query.bindValue(":id",2);
          query.bindValue(":name", "");//QObject::tr("%1").arg(99999)
          query.exec();


        query.exec("select id, name, age from zjgz");
        while (query.next())
        {

           //qDebug()<<"id*******"<<query.value(0).toInt()<<"*************** name:"<<query.value(1).toString()<<"  age:"<<query.value(2).toInt();
           IdItem[zjgzun] = query.value(0).toInt();
           zjMsItem[zjgzun] = query.value(1).toString();

           ui->tableWidget->setItem(zjgzun,0,new QTableWidgetItem(QString::number(IdItem[zjgzun])));
           ui->tableWidget->setItem(zjgzun,1,new QTableWidgetItem(zjMsItem[zjgzun]));

           zjgzun++;
//           if(zjgzun>=10)
//           {
//               zjgzun = 0;
//           }
        }
        zjgzun = 0;

         query.exec(QObject::tr("drop zjgz"));
#endif

/****************************************************************************************************/
}


//按键事件
void Widget::keyPressEvent(QKeyEvent *e)
{
    switch (e->key())
    {

    case Qt::Key_F1:

         switch(flagwidget)
         {
            case xingZouWidget:
              flagwidget = MainMenu;
              ui->stackedWidget->setCurrentIndex(2);
              break;

             case MainMenu:
                 flagwidget = HelpMenu;
                 ui->stackedWidget->setCurrentIndex(7);
                 break;

         case UserMenu:
             flagwidget = MainMenu;
             ui->stackedWidget->setCurrentIndex(2);
             break;

         case ClearMenu:
             flagwidget = MainMenu;
             ui->stackedWidget->setCurrentIndex(2);
             break;

         case SystemMenu:
             flagwidget = MainMenu;
             ui->stackedWidget->setCurrentIndex(2);
             break;

         case SwitchMachineMenu:
             flagwidget = MainMenu;
             ui->stackedWidget->setCurrentIndex(2);
             break;

         case MachineModeMenu:
             flagwidget = MainMenu;
             ui->stackedWidget->setCurrentIndex(2);
             break;

         case EngineSwitchMenu:
             flagwidget = MainMenu;
             ui->stackedWidget->setCurrentIndex(2);
             break;

         case ZhujiFault:
             flagwidget = MainMenu;
             ui->stackedWidget->setCurrentIndex(2);
             break;

         case EngineFault:
             flagwidget = MainMenu;
             ui->stackedWidget->setCurrentIndex(2);
             break;


        case HelpMenu:
             flagwidget = Shaomiao;
             ui->stackedWidget->setCurrentIndex(17);
             break;

             //标定菜单
        case BiaoDing:
             flagwidget = MainMenu;
             ui->stackedWidget->setCurrentIndex(2);
             break;

             //阀值标定
        case FazhibiaodingMenu:
             flagwidget = MainMenu;
             ui->stackedWidget->setCurrentIndex(2);
             break;

             //匹配性标定
        case PipeixingbiaodingMenu:
             flagwidget = MainMenu;
             ui->stackedWidget->setCurrentIndex(2);
             break;

         case Getai:
         flagwidget = MainMenu;
         ui->stackedWidget->setCurrentIndex(2);
         break;

             default:
                 break;

         }

         break;

    case Qt::Key_F2:

         switch(flagwidget)
         {

         //2017.5.22
           case xingZouWidget:
           flagwidget = MainMenu;
           ui->stackedWidget->setCurrentIndex(2);
           break;

            case MainMenu:
             flagwidget = SystemMenu;
             ui->stackedWidget->setCurrentIndex(4);
             break;

             case SystemMenu:
              flagwidget = UserMenu;
              ui->stackedWidget->setCurrentIndex(1);
              ui->lineEdit->setFocus();
              //设置时间时显示当前时间
              ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());

              break;

         case HelpMenu:
             flagwidget = MainMenu;
             ui->stackedWidget->setCurrentIndex(2);
             break;

         case DiagnosisMenu:
             flagwidget = MainMenu;
             ui->stackedWidget->setCurrentIndex(2);
             break;


         case VideoSetupMenu:
             flagwidget = MainMenu;
             ui->stackedWidget->setCurrentIndex(2);

#ifdef CAMERAFLAG

//m_camerobj.SetVideoOuputLabel(ui->label_16,NULL);   //设置视频输出LABEL对象
//m_camerobj.Jobs_Monitor_Stop();      /*停止作业监控*/
#endif

             break;

             default:
                 break;
         }

         break;

    case Qt::Key_F3:

         flagvedio = 1;
         switch(flagwidget)
         {
             //2017.5.22
               case xingZouWidget:
               flagwidget = MainMenu;
               ui->stackedWidget->setCurrentIndex(2);
               break;

             case MainMenu:
              flagwidget = DiagnosisMenu;
              ui->stackedWidget->setCurrentIndex(8);
              break;

             case DiagnosisMenu:
              flagwidget = ZhujiFault;
              ui->stackedWidget->setCurrentIndex(14);
              ui->tableWidget->setFocus();
              break;

              //进入视频界面
             case SystemMenu:
              flagwidget = VideoSetupMenu;
              ui->stackedWidget->setCurrentIndex(10);

//              if(flagyihuovideo == 1)
//              {
//                  flagcurrentvideo = AV3;
//                  m_camerobj.SetVideoOuputLabel(ui->label_16,NULL);
//              }
//              else
//              {
//                  flagcurrentvideo = AV2;
//                  m_camerobj.SetVideoOuputLabel(ui->label_16,NULL);
//              }
              m_camerobj.SetVideoOuputLabel(ui->label_16,NULL);

              break;

             case HelpMenu:     //维修保养
             flagwidget = Shaomiao;
             ui->stackedWidget->setCurrentIndex(17);
             break;

             default:
             break;
         }
         break;


    case Qt::Key_F4:
        switch(flagwidget)
        {
        //2017.5.22
          case xingZouWidget:
          flagwidget = MainMenu;
          ui->stackedWidget->setCurrentIndex(2);
          break;

            case MainMenu:
             flagwidget = ClearMenu;
             ui->stackedWidget->setCurrentIndex(3);
             ui->listWidget->setFocus();
             break;

            case SystemMenu:
            flagwidget = SwitchMachineMenu;
            ui->stackedWidget->setCurrentIndex(5);
            ui->listWidget_2->setFocus();
            break;

            case DiagnosisMenu:
            flagwidget = EngineFault;
            ui->stackedWidget->setCurrentIndex(13);
            ui->tableWidget_2->setFocus();
            break;

            case HelpMenu:
            flagwidget = EngineFault;
            ui->stackedWidget->setCurrentIndex(13);
            ui->tableWidget_2->setFocus();
            break;


            case VideoSetupMenu://视频切换
            {

                flagyihuovideo ^= 1;
                if(flagyihuovideo == 1)
                {
                    //flagcurrentvideo = AV3;
                    flagdbvideoCurrent = 1;
                    m_camerobj.SetVideoOuputLabel(ui->label_16,NULL);
                }
                else
                {
                    //flagcurrentvideo = AV2;
                    flagdbvideoCurrent = 0;
                    m_camerobj.SetVideoOuputLabel(ui->label_16,NULL);
                }

                //更新数据库
                #if 1
                QTextCodec::setCodecForTr(QTextCodec::codecForLocale());//汉字显示
                QSqlDatabase db;
                if(QSqlDatabase::contains("qt_sql_default_connection"))
                db = QSqlDatabase::database("qt_sql_default_connection");
                else
                db = QSqlDatabase::addDatabase("QSQLITE");

                db.setDatabaseName("jy.db");
                if (!db.open())
                {
                qDebug()<<"open database failed ---"<<db.lastError().text()<<endl;
                }
                QSqlQuery query;

                //query.prepare("INSERT INTO otherflag(item1, item2, item3) VALUES (:item1, :item2, :item3)");

                query.prepare("update otherflag set item1 = :item1,item2 = :item2,item3 = :item3");//where

                query.bindValue(":item1",flagdbvideoCurrent);
                query.bindValue(":item2", 11);
                query.bindValue(":item3", 66);

                query.exec();

                #endif
            }
            break;


            default:
            break;
        }
        break;

    case Qt::Key_F5:
        switch(flagwidget)
        {
        //2017.5.23
        case ClearMenu:
        {
            //单次里程清零// 米计清零
            if(clearflag == 1)
            {
                //给控制器发送指令
                Cfg_sSingMileageClear();	/*	单次里程/米计清零 */
            }
        }
//        flagwidget = MainMenu;
//        ui->stackedWidget->setCurrentIndex(2);
        break;


            //2017.5.22
              case xingZouWidget:
              flagwidget = MainMenu;
              ui->stackedWidget->setCurrentIndex(2);
              break;

            case MainMenu:  //静音
            flagbeep ^= 1;
            if(flagbeep)
            {
                ui->pushButton_2->setStyleSheet("QPushButton{border-image:url(./img/jiemian/labayes.png);background-repeat: background-xy;background-position: center;background-attachment: fixed;background-clip: padding}");
            }
            else
            {
                ui->pushButton_2->setStyleSheet("QPushButton{border-image:url(./img/jiemian/labano.png);background-repeat: background-xy;background-position: center;background-attachment: fixed;background-clip: padding}");
            }
             break;

             case SwitchMachineMenu: //机型选择菜单
                if(LCSwitchmatchineRow == 1)//整机型号
                {
                  flagwidget = MachineModeMenu;
                  ui->stackedWidget->setCurrentIndex(6);
                }
                else if(LCSwitchmatchineRow == 2) //发动机品牌
                {
                    flagwidget = EngineSwitchMenu;
                    ui->stackedWidget->setCurrentIndex(9);
                }
              break;

                //机器型号
            case MachineModeMenu:
            {

                if((LCMachineModeMenu == 1)&&(LCBoolMachineModenu == true))
                 {
                     flagmatchion = YZT_10;
                 }
                 else if((LCMachineModeMenu == 2)&&(LCBoolMachineModenu == true))
                 {
                     flagmatchion = YZB_4_5_7_8;
                 }
                 else if((LCMachineModeMenu == 3)&&(LCBoolMachineModenu == true))
                 {
                     flagmatchion = YZB_3A_B;
                 }

                //
                //2017.4.2
                else if((LCMachineModeMenu == 4)&&(LCBoolMachineModenu == true))
                {
                    flagmatchion = JZ_3600;
                }
                //
                //ui->listwidget4
                else if((LCMachineModeMenu == 1)&&(LCBoolMachineModenu == false))
                {
                    flagmatchion = YZBT_5;
                    qDebug()<<"Hao hao xue xi ... tian tian .. . xiang shang ....."<<endl;
                }
                else if((LCMachineModeMenu == 2)&&(LCBoolMachineModenu == false))
                {
                    flagmatchion = YZT_5;
                }
                else if((LCMachineModeMenu == 3)&&(LCBoolMachineModenu == false))
                {
                    flagmatchion = S3000;
                }

                qDebug()<<"LCMachineModeMenuLCMachineModeMenuLCMachineModeMenu ======"<<LCMachineModeMenu<<endl;

                //存储数据
                //

                QTextCodec::setCodecForTr(QTextCodec::codecForLocale());//汉字显示
                QSqlDatabase db;
                if(QSqlDatabase::contains("qt_sql_default_connection"))
                  db = QSqlDatabase::database("qt_sql_default_connection");
                else
                  db = QSqlDatabase::addDatabase("QSQLITE");

               db.setDatabaseName("jy.db");
               if (!db.open())
               {
                   qDebug()<<"open database failed ---"<<db.lastError().text()<<endl;
               }
               QSqlQuery query;
               query.prepare("update config set engineswitch = :engineswitch");//cjswitch = :cjswitch,,langswitch = :langswitch
               //query.bindValue(":cjswitch",77);
               query.bindValue(":engineswitch", flagmatchion);
              // query.bindValue(":langswitch", 55);
               query.exec();

             query.exec("select cjswitch, engineswitch, langswitch from config");
             while (query.next())
             {
                //qDebug()<<"matchine.......  ==  "<<query.value(0).toInt()<<endl;
             }


             //2017.5.6  暂时先这样给下边传数据
             SetXinYanMachineModel(	XY_MODEL_4YZT_5);

             query.exec(QObject::tr("drop config"));

          }
         break;


            //发动机厂家
            case EngineSwitchMenu:
            {
                if(LCEngineSwitchMenu == 1)
                {
                    CJSwitch = YuCai;
                    //cjnum = 0;
                }
                else if(LCEngineSwitchMenu == 2)
                {
                    CJSwitch = WeiCai;
                    //cjnum = 1;

                }
                else if(LCEngineSwitchMenu == 3)
                {
                    CJSwitch = XiCai;
                    //cjnum = 2;
                }
                else if(LCEngineSwitchMenu == 4)
                {
                    CJSwitch = HangFa;
                    //cjnum = 3;
                }
                else if(LCEngineSwitchMenu == 5)
                {
                    CJSwitch = DongfangHong;
                    //cjnum = 4;
                }
                //存储数据
                //
                QTextCodec::setCodecForTr(QTextCodec::codecForLocale());//汉字显示
                QSqlDatabase db;
                if(QSqlDatabase::contains("qt_sql_default_connection"))
                  db = QSqlDatabase::database("qt_sql_default_connection");
                else
                  db = QSqlDatabase::addDatabase("QSQLITE");

               db.setDatabaseName("jy.db");
               if (!db.open())
               {
                   qDebug()<<"open database failed ---"<<db.lastError().text()<<endl;
               }
               QSqlQuery query;
               query.prepare("update config set cjswitch = :cjswitch");//,engineswitch = :engineswitch,langswitch = :langswitch
               query.bindValue(":cjswitch",CJSwitch);//cjnum
               //query.bindValue(":engineswitch", flagmatchion);
              // query.bindValue(":langswitch", 55);
               query.exec();

             query.exec("select cjswitch, engineswitch, langswitch from config");
             while (query.next())
             {
                qDebug()<<"888888888888888888888888   matchine.......  ==  "<<query.value(0).toInt()<<endl;
             }

             //2017.5.6 设置发动机厂家ID，用于SPN中文查询
             Can_set_Fdj_id(CJSwitch);//设置发动机厂家ID，用于SPN中文查询

             query.exec(QObject::tr("drop config"));
            }
            break;

            //故障码清除
            //清空数据库列表 故障码列表
            case DiagnosisMenu:
            {
                flagGzmclear = true;

                //存储数据
                //
                QTextCodec::setCodecForTr(QTextCodec::codecForLocale());//汉字显示
                QSqlDatabase db;
                if(QSqlDatabase::contains("qt_sql_default_connection"))
                  db = QSqlDatabase::database("qt_sql_default_connection");
                else
                  db = QSqlDatabase::addDatabase("QSQLITE");

               db.setDatabaseName("jy.db");
               if (!db.open())
               {
                   qDebug()<<"open database failed ---"<<db.lastError().text()<<endl;
               }
               QSqlQuery query;
               query.prepare("delete from fdjgz");//
               query.exec();
               qDebug()<<"kdddddddddddddddddddddddddddddddddddddddddddddddddddddd"<<endl;
               query.exec(QObject::tr("drop fdjgz"));



//               ui->tableWidget_2->setItem(un,0,new QTableWidgetItem(""));
//               ui->tableWidget_2->setItem(un,1,new QTableWidgetItem(""));
//               ui->tableWidget_2->setItem(un,2,new QTableWidgetItem(""));


               for(clearItem = 0; clearItem<10;clearItem++)
               {
                   ui->tableWidget_2->setItem(clearItem,0,new QTableWidgetItem(""));
                   ui->tableWidget_2->setItem(clearItem,1,new QTableWidgetItem(""));
                   ui->tableWidget_2->setItem(clearItem,2,new QTableWidgetItem(""));
               }
               if(clearItem>=10)
               {
                   clearItem = 0;
               }
            }
            break;

            //2017.4.7
            //系统标定
            case SystemMenu:
            {
                flagwidget = BiaoDing;
                ui->stackedWidget->setCurrentIndex(16);
                ui->listWidget_6->setFocus();
            }
            break;

            //xitongbiaoding 确认
            case BiaoDing:
            if(LCBiaoDingRow == 1)//匹配性标定
            {
              flagwidget = PipeixingbiaodingMenu;
              ui->stackedWidget->setCurrentIndex(11);

              //2017.5.23
              //2017.5.23
              BiaoDingInit();	/* 进入标定初始化界面	*/

              //2017.5.17
//              shoubingoffset = biaoding.m_XinZouJubing[BD_VALUE_Offset];
//              langanoffset =   biaoding.m_XinZouJubing[BD_VALUE_Offset];
            }
            else if(LCBiaoDingRow == 2) //阀值标定
            {
                flagwidget = FazhibiaodingMenu;
                ui->stackedWidget->setCurrentIndex(12);

                //2017.4.22   //更新阀值设定数据库

                  QTextCodec::setCodecForTr(QTextCodec::codecForLocale());//汉字显示
                  QSqlDatabase db;
                  if(QSqlDatabase::contains("qt_sql_default_connection"))
                    db = QSqlDatabase::database("qt_sql_default_connection");
                  else
                    db = QSqlDatabase::addDatabase("QSQLITE");

                 db.setDatabaseName("jy.db");
                 if (!db.open())
                 {
                     qDebug()<<"open database failed ---"<<db.lastError().text()<<endl;
                 }
                 QSqlQuery query;


            #if 0
                 //query.prepare("INSERT INTO FaZhiBingBD(ZLH, XLLH, GQLH,LmdGTZS,LmdFengJi,LmdJiaoLong,LmdGuoQiao) VALUES (:ZLH, :XLLH, :GQLH, :LmdGQZS, :LmdFengJi, :LmdJiaoLong, :LmdGuoQiao)");
                 query.prepare("update FaZhiBingBD set ZLH = :ZLH,XLLH = :XLLH,GQLH = :GQLH,LmdGTZS = :LmdGQZS,LmdFengJi = :LmdFengJi,LmdJiaoLong = :LmdJiaoLong,LmdGuoQiao = :LmdGuoQiao");//where

                 query.bindValue(":ZLH",zlh);
                 query.bindValue(":XLLH", xllh);
                 query.bindValue(":GQLH", gqlh);
                 query.bindValue(":LmdGTZS", gtzs);
                 query.bindValue(":LmdFengJi", fjzs);
                 query.bindValue(":LmdJiaoLong", jlzs);
                 query.bindValue(":LmdGuoQiao", gqzs);
                 query.exec();

            #endif


//                 //2017.5.2  向控制器 发送数据
//                 SendReqCmdToController(GUI_CMD_CFG_REQ_ZhuLiHeZhangJinLi,zlh);
//                 SendReqCmdToController(GUI_CMD_CFG_REQ_XieLiangLiHeZhangJinLi,xllh);
//                 SendReqCmdToController(GUI_CMD_CFG_REQ_GuoQiaoLiHeZhangJinLi,gqlh);
//                 SendReqCmdToController(GUI_CMD_CFG_REQ_GunTongZhuanSuLinMinDu,gtzs);
//                 SendReqCmdToController(GUI_CMD_CFG_REQ_FengJiZhuanSuLinMinDu,fjzs);
//                 SendReqCmdToController(GUI_CMD_CFG_REQ_JiaoLongZhuanSuLinMinDu,jlzs);
//                 SendReqCmdToController(GUI_CMD_CFG_REQ_GuoQiaoZhuanSuLinMinDu,gqzs);



                 #if 1
                query.exec("select ZLH, XLLH, GQLH,LmdGTZS,LmdFengJi,LmdJiaoLong,LmdGuoQiao from FaZhiBingBD");
                while (query.next())
                {

                  qDebug()<<"id("<<query.value(0).toInt()<<")  name:"<<query.value(1).toString()<<"  age:"<<query.value(2).toInt();
                  zlh = query.value(0).toInt();
                  xllh = query.value(1).toInt();
                  gqlh = query.value(2).toInt();
                  gtzs = query.value(3).toInt();
                  fjzs = query.value(4).toInt();
                  jlzs = query.value(5).toInt();
                  gqzs = query.value(6).toInt();
                }
                #endif
                query.exec(QObject::tr("drop FaZhiBingBD"));

            }

            //2017.5.4
            else if(LCBiaoDingRow == 3) //割台设定
            {
                qDebug()<<"GETATI)))))))))))))))))))))))))))))))))))))))))))))))";
                flagwidget = Getai;
                ui->stackedWidget->setCurrentIndex(18);

                //2017.5.4
                ui->listWidget_7->setFocus();
                //2017.5.9

//                GeFuWidth = biaoding.m_GeFuKuanDu;
//                Zaihexishu = biaoding.m_ZaiKeXiShu;
//                Autospeed = biaoding.m_TiaoSuXiShu;
//                LCGetaiSetup = biaoding.m_GuWuZhongLei;


                ui->lineEdit_3->setText(QString::number(GeFuWidth));
                ui->lineEdit_4->setText(QString::number(Zaihexishu));
                ui->lineEdit_5->setText(QString::number(Autospeed));


                //2017.5.24
                //割台参数读取
              #if 1
                    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());//汉字显示
                    QSqlDatabase db;
                    if(QSqlDatabase::contains("qt_sql_default_connection"))
                      db = QSqlDatabase::database("qt_sql_default_connection");
                    else
                      db = QSqlDatabase::addDatabase("QSQLITE");

                   db.setDatabaseName("jy.db");
                   if (!db.open())
                   {
                       qDebug()<<"open database failed ---"<<db.lastError().text()<<endl;
                   }
                   QSqlQuery query;

                 query.exec("select GuWuSwitch, GeFuWidth, ZaiHeXishu,ChangeSpeed from GeTaiBD");
                 while (query.next())
                 {

                    LCGetaiSetup = query.value(0).toInt();
                    GeFuWidth = query.value(1).toInt();
                    Zaihexishu = query.value(2).toInt();
                    Autospeed = query.value(3).toInt();

                    qDebug()<<"id("<<query.value(0).toInt()<<")  name:"<<query.value(1).toString()<<"  age:"<<query.value(2).toInt();

                 }
                  query.exec(QObject::tr("drop GuWuSwitch"));

              #endif


            }
          break;

            /*********************************************************/
            //确定键
            case UserMenu:
                timeSetOK = true;
                break;
            /*********************************************************/


            case VideoSetupMenu://设为主屏幕
            {
                if(flagyihuovideo == 1)
                {
                    //flagcurrentvideo = AV3;
                    flagdbvideoCurrent = 1;
                    m_camerobj.SetVideoOuputLabel(ui->label,NULL);
                }
                else
                {
                    //flagcurrentvideo = AV2;
                    flagdbvideoCurrent = 0;
                    m_camerobj.SetVideoOuputLabel(ui->label,NULL);
                }
                flagzhuqueren = 1;
            }
            break;

/**************************************************************************************************/
        case PipeixingbiaodingMenu:
           {
                if((LCPiPeixingBiaoDing == 1)&&(FlagShouBing ==0))
                {
                    FlagShouBing = 1;
                    //ui->label_16->setText("请推动手柄到最大位置等待");
                    FlagXingzouBeng = 0;
                    FlagAoBanjianxi = 0;

                    //2017.5.18 向控制器 发送数据
                    SendReqCmdToController(GUI_CMD_CFG_REQ_XinZouJuBing_Data,0);
                    GetRspDataFromController(&biaoding);

                }
                else if((LCPiPeixingBiaoDing == 2)&&(FlagXingzouBeng ==0))
                {
                    FlagXingzouBeng = 1;
                    //ui->label_16->setText("请推动手柄到最大位置等待");
                     FlagShouBing = 0;
                      FlagAoBanjianxi = 0;
                      //2017.5.18 向控制器 发送数据
                      SendReqCmdToController(GUI_CMD_CFG_REQ_XinZouLaGan_Data,0);
                      GetRspDataFromController(&biaoding);

                }
                else if((LCPiPeixingBiaoDing == 3)&&(FlagAoBanjianxi ==0))
                {
                    FlagAoBanjianxi = 1;
                    //ui->label_16->setText("请按住凹板间隙增大调整开关并等待");
                     FlagShouBing = 0;
                     FlagXingzouBeng = 0;
                }

                //2017.5.18 向控制器 发送数据
                SendReqCmdToController(GUI_CMD_CFG_REQ_XinZouJuBing_Offset,shoubingoffset);
                SendReqCmdToController(GUI_CMD_CFG_REQ_XinZouLaGan_Offset,langanoffset);
           }
            break;



/**************************************************************************************************/

/**************************************************************************************************/
//阀值标定
           case FazhibiaodingMenu:
            {
            //2017.4.22   //更新阀值设定数据库
            #if 1
             if(FaZhiReadOK)
             {
              QTextCodec::setCodecForTr(QTextCodec::codecForLocale());//汉字显示
              QSqlDatabase db;
              if(QSqlDatabase::contains("qt_sql_default_connection"))
                db = QSqlDatabase::database("qt_sql_default_connection");
              else
                db = QSqlDatabase::addDatabase("QSQLITE");

             db.setDatabaseName("jy.db");
             if (!db.open())
             {
                 qDebug()<<"open database failed ---"<<db.lastError().text()<<endl;
             }
             QSqlQuery query;
             #if 0
             bool ok = query.exec("create table FaZhiBingBD(ZLH INTEGER,XLLH INTEGER,GQLH INTEGER,LmdGTZS INTEGER,LmdFengJi INTEGER,LmdJiaoLong INTEGER,LmdGuoQiao INTEGER)");
             if (ok)
             {
                 qDebug()<<"ceate table partition success"<<endl;
             }
             else
             {
                 qDebug()<<"ceate table partition failed"<<endl;
             }
             #endif

        #if 1
             //query.prepare("INSERT INTO FaZhiBingBD(ZLH, XLLH, GQLH,LmdGTZS,LmdFengJi,LmdJiaoLong,LmdGuoQiao) VALUES (:ZLH, :XLLH, :GQLH, :LmdGQZS, :LmdFengJi, :LmdJiaoLong, :LmdGuoQiao)");
             query.prepare("update FaZhiBingBD set ZLH = :ZLH,XLLH = :XLLH,GQLH = :GQLH,LmdGTZS = :LmdGQZS,LmdFengJi = :LmdFengJi,LmdJiaoLong = :LmdJiaoLong,LmdGuoQiao = :LmdGuoQiao");//where

             query.bindValue(":ZLH",zlh);
             query.bindValue(":XLLH", xllh);
             query.bindValue(":GQLH", gqlh);
             query.bindValue(":LmdGTZS", gtzs);
             query.bindValue(":LmdFengJi", fjzs);
             query.bindValue(":LmdJiaoLong", jlzs);
             query.bindValue(":LmdGuoQiao", gqzs);
             query.exec();

        #endif


             //2017.5.2  向控制器 发送数据
             SendReqCmdToController(GUI_CMD_CFG_REQ_ZhuLiHeZhangJinLi,zlh);
             SendReqCmdToController(GUI_CMD_CFG_REQ_XieLiangLiHeZhangJinLi,xllh);
             SendReqCmdToController(GUI_CMD_CFG_REQ_GuoQiaoLiHeZhangJinLi,gqlh);
             SendReqCmdToController(GUI_CMD_CFG_REQ_GunTongZhuanSuLinMinDu,gtzs);
             SendReqCmdToController(GUI_CMD_CFG_REQ_FengJiZhuanSuLinMinDu,fjzs);
             SendReqCmdToController(GUI_CMD_CFG_REQ_JiaoLongZhuanSuLinMinDu,jlzs);
             SendReqCmdToController(GUI_CMD_CFG_REQ_GuoQiaoZhuanSuLinMinDu,gqzs);



             #if 0
            query.exec("select ZLH, XLLH, GQLH,LmdGTZS,LmdFengJi,LmdJiaoLong,LmdGuoQiao from FaZhiBingBD");
            while (query.next())
            {

              qDebug()<<"id("<<query.value(0).toInt()<<")  name:"<<query.value(1).toString()<<"  age:"<<query.value(2).toInt();
              tempzlh = query.value(0).toInt();
              tempxllh = query.value(1).toInt();
              tempgqlh = query.value(2).toInt();
              tempgtzs = query.value(3).toInt();
              tempfjzs = query.value(4).toInt();
              tempjlzs = query.value(5).toInt();
              tempgqzs = query.value(6).toInt();


            }
            #endif
            query.exec(QObject::tr("drop FaZhiBingBD"));

        }
            #endif
            }
            break;


/**************************************************************************************************/
/**************************************************************************************************/

                            case Getai:
                            {
                            //2017.5.5 割台参数设置
                            #if 1
                            QTextCodec::setCodecForTr(QTextCodec::codecForLocale());//汉字显示
                            QSqlDatabase db;
                            if(QSqlDatabase::contains("qt_sql_default_connection"))
                              db = QSqlDatabase::database("qt_sql_default_connection");
                            else
                              db = QSqlDatabase::addDatabase("QSQLITE");

                           db.setDatabaseName("jy.db");
                           if (!db.open())
                           {
                               qDebug()<<"open database failed ---"<<db.lastError().text()<<endl;
                           }
                           QSqlQuery query;
                           #if 0
                           bool ok = query.exec("create table GeTaiBD(GuWuSwitch INTEGER,GeFuWidth INTEGER,ZaiHeXishu INTEGER,ChangeSpeed INTEGER)");
                           if (ok)
                           {
                               qDebug()<<"ceate table partition success"<<endl;
                           }
                           else
                           {
                               qDebug()<<"ceate table partition failed"<<endl;
                           }
                           #endif

                           //query.prepare("INSERT INTO GeTaiBD(GuWuSwitch, GeFuWidth, ZaiHeXishu,ChangeSpeed) VALUES (:GuWuSwitch, :GeFuWidth,:ZaiHeXishu, :ChangeSpeed)");
                           query.prepare("update GeTaiBD set GuWuSwitch = :GuWuSwitch,GeFuWidth = :GeFuWidth,ZaiHeXishu = :ZaiHeXishu,ChangeSpeed = :ChangeSpeed");//where

//                           query.bindValue(":GuWuSwitch",1);
//                           query.bindValue(":GeFuWidth", 3140);
//                           query.bindValue(":ZaiHeXishu", 5);
//                           query.bindValue(":ChangeSpeed", 80);
//                           query.exec();

                              query.bindValue(":GuWuSwitch",LCGetaiSetup);
                              query.bindValue(":GeFuWidth", GeFuWidth);
                              query.bindValue(":ZaiHeXishu", Zaihexishu);
                              query.bindValue(":ChangeSpeed", Autospeed);
                              query.exec();


                         query.exec("select GuWuSwitch, GeFuWidth, ZaiHeXishu,ChangeSpeed from GeTaiBD");
                         while (query.next())
                         {
                            qDebug()<<"id("<<query.value(0).toInt()<<")  name:"<<query.value(1).toString()<<"  age:"<<query.value(2).toInt();
                         }
                          query.exec(QObject::tr("drop GuWuSwitch"));

                      #endif

                            //2017.5.2  向控制器 发送数据
                            SendReqCmdToController(GUI_CMD_CFG_REQ_GuWuZhongLei,LCGetaiSetup);
                            SendReqCmdToController(GUI_CMD_CFG_REQ_GeFuKuanDu,GeFuWidth);
                            SendReqCmdToController(GUI_CMD_CFG_REQ_ZaiHeXiShu,Zaihexishu);
                            SendReqCmdToController(GUI_CMD_CFG_REQ_TiaoSuXiShu,Autospeed);

                          }
                          break;
/**************************************************************************************************/

            //2017.4.10
            case HelpMenu:
            flagwidget = JiQiXinXi;
            ui->stackedWidget->setCurrentIndex(15);
            break;


            default:
            break;
        }
        break;

    case Qt::Key_F6:
        switch(flagwidget)
        {

        //2017.5.22
          case xingZouWidget:
          flagwidget = MainMenu;
          ui->stackedWidget->setCurrentIndex(2);
          break;

            case MainMenu://确认键 返回到行走工作界面
             flagwidget = xingZouWidget;
             ui->stackedWidget->setCurrentIndex(0);
             break;

            case UserMenu:
             flagwidget = SystemMenu;
             ui->stackedWidget->setCurrentIndex(4);
             break;

             case SwitchMachineMenu:
              flagwidget = SystemMenu;
              ui->stackedWidget->setCurrentIndex(4);
              break;

            case SystemMenu:
             flagwidget = MainMenu;
             ui->stackedWidget->setCurrentIndex(2);
             break;

            case EngineSwitchMenu:
                flagwidget =  SwitchMachineMenu;
                ui->stackedWidget->setCurrentIndex(5);
                break;

            case MachineModeMenu:
                flagwidget = SwitchMachineMenu;
                ui->stackedWidget->setCurrentIndex(5);
            break;

        case ZhujiFault:
            flagwidget = DiagnosisMenu;
            ui->stackedWidget->setCurrentIndex(8);
            break;

            case EngineFault:
            flagwidget = DiagnosisMenu;
            ui->stackedWidget->setCurrentIndex(8);
            break;

            //视频界面返回到系统设置界面

            case VideoSetupMenu://设为主屏幕
            {
                flagwidget = SystemMenu;
                ui->stackedWidget->setCurrentIndex(4);
                if(flagyihuovideo == 1)
                {
                    //flagcurrentvideo = AV3;
                    flagdbvideoCurrent = 1;
                    m_camerobj.SetVideoOuputLabel(ui->label,NULL);
                }
                else
                {
                    //flagcurrentvideo = AV2;
                    flagdbvideoCurrent = 0;
                    m_camerobj.SetVideoOuputLabel(ui->label,NULL);
                }
            }
            break;

            case DiagnosisMenu:
            flagwidget = MainMenu;
            ui->stackedWidget->setCurrentIndex(2);
            break;

            case ClearMenu:
            flagwidget = MainMenu;
            ui->stackedWidget->setCurrentIndex(2);
            break;

//            case PipeixingbiaodingMenu:
//            flagwidget = SystemMenu;
//            ui->stackedWidget->setCurrentIndex(4);
//            break;


            case HelpMenu:
            flagwidget = MainMenu;
            ui->stackedWidget->setCurrentIndex(2);
            break;

            case Shaomiao:     //返回上一级菜单
            flagwidget = HelpMenu;
            ui->stackedWidget->setCurrentIndex(7);
            break;

            case FazhibiaodingMenu:     //返回上一级菜单
            flagwidget = BiaoDing;//系统标定
            ui->stackedWidget->setCurrentIndex(16);
            break;

            case BiaoDing:     //返回上一级菜单
            flagwidget = SystemMenu;//系统标定
            ui->stackedWidget->setCurrentIndex(4);
            break;

            case PipeixingbiaodingMenu:     //返回上一级菜单
            flagwidget = BiaoDing;//
            ui->stackedWidget->setCurrentIndex(16);

            //2017.5.23
            BiaoDingExit();	/* 退出标定界面 */
            break;

            //2017.4.10
            case JiQiXinXi:
            flagwidget = HelpMenu;
            ui->stackedWidget->setCurrentIndex(7);
            break;

            //2017.5.4
            case Getai:
            flagwidget = BiaoDing;
            ui->stackedWidget->setCurrentIndex(16);
            break;

            default:
            break;
        }
        break;

    }
    flagaction = true;
}

bool Widget::eventFilter(QObject *watched, QEvent *event)
{

    //主界面选择
    if((watched == ui->label_2 && (event->type() == QEvent::Paint)))//||(watched == ui->label_5 && event->type() == QEvent::Paint))
    {
        magicTime();
    }
    else if((watched == ui->label_5 && (event->type() == QEvent::Paint)))
    {
        fun2();
    }
    //时间设置 语言选择 屏幕亮度调节
    else if((watched == ui->lineEdit)||(watched == ui->lineEdit_2)||(watched == ui->dateTimeEdit)||(watched == ui->progressBar))
    {
        if(event->type() == QEvent::KeyPress)
        {
            QKeyEvent *key_event = static_cast < QKeyEvent *>(event); //将事件转化为键盘事件
            {
                if(key_event->key() == Qt::Key_F2)//下键
                {
                    bool f1 = ui->lineEdit->hasFocus();
                    bool f2 = ui->lineEdit_2->hasFocus();
                    bool f3 = ui->dateTimeEdit->hasFocus();
                    bool f4 = ui->progressBar->hasFocus();

                    if(f1)
                    {
                    focusNextChild();
                    ui->lineEdit_2->setFocus();
                    }
                    if(f2)
                    {
                        focusNextChild();
                        ui->dateTimeEdit->setFocus();
                    }
                    if(f3)
                    {
                        focuseflag = ui->dateTimeEdit->currentSectionIndex();
                        ui->dateTimeEdit->setCurrentSectionIndex(++focuseflag);
                        ui->dateTimeEdit->setFocus();
                        qDebug()<<"focuseflag == "<<focuseflag<<endl;
                        if(focuseflag>=6)
                        {
                            focusNextChild();
                            ui->progressBar->setFocus();
                        }
                    }
                    if(f4)
                    {
                        focusNextChild();
                        ui->lineEdit->setFocus();
                    }

                    flagaction = true;
                    return true;
                }
                else if (key_event->key() == Qt::Key_F4)
                {
                    bool ff3 = ui->dateTimeEdit->hasFocus();
                    bool ff4 = ui->progressBar->hasFocus();
                    if(ff3)
                    ui->dateTimeEdit->stepBy(1);
                    else if (ff4)
                        ui->progressBar->setValue(++valueprogressbar);

                    flagaction = true;
                    return true;
                }
                else if (key_event->key() == Qt::Key_F3)
                {
                    bool ff3 = ui->dateTimeEdit->hasFocus();
                    bool ff4 = ui->progressBar->hasFocus();
                    if(ff3)
                    ui->dateTimeEdit->stepBy(-1);
                    else if (ff4)
                        ui->progressBar->setValue(--valueprogressbar);

                    flagaction = true;
                    return true;
                }

            }
        }
    } //clearmenu F2键过滤
    //米计清零设置
    else if(watched == ui->listWidget)
    {
        if(event->type() == QEvent::KeyPress)
        {
            QKeyEvent *key_event = static_cast < QKeyEvent *>(event); //将事件转化为键盘事件
            {
                if(key_event->key() == Qt::Key_F2)//下键
                {
                    if(LCClearMenuRow>2)
                    {
                        LCClearMenuRow = 0;
                        ui->listWidget->item(2)->setBackgroundColor(Qt::transparent);
                        ui->listWidget->item(2)->setTextColor(Qt::black);
                    }

                    ui->listWidget->item(LCClearMenuRow)->setBackgroundColor(Qt::blue);
                    ui->listWidget->item(LCClearMenuRow)->setTextColor(Qt::red);

                    if(LCClearMenuRow == 1)
                    {
                        ui->listWidget->item(0)->setBackgroundColor(Qt::transparent);
                        ui->listWidget->item(0)->setTextColor(Qt::black);
                    }
                    else if(LCClearMenuRow == 2)
                    {

                        ui->listWidget->item(1)->setBackgroundColor(Qt::transparent);
                        ui->listWidget->item(1)->setTextColor(Qt::black);
                        ui->listWidget->item(0)->setBackgroundColor(Qt::transparent);
                        ui->listWidget->item(0)->setTextColor(Qt::black);
                    }

                    flagaction = true;
                    LCClearMenuRow++;

                }

            }
        }
    }// end of else if(watched == ui->listWidget)
    //机型选择
    else if(watched == ui->listWidget_2)
    {
        if(event->type() == QEvent::KeyPress)
        {
            QKeyEvent *key_event = static_cast < QKeyEvent *>(event); //将事件转化为键盘事件
            {
                if(key_event->key() == Qt::Key_F2)//下键
                {
                    if(LCSwitchmatchineRow>1)
                    {
                        LCSwitchmatchineRow = 0;
                        ui->listWidget_2->item(1)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_2->item(1)->setTextColor(Qt::black);
                    }

                    ui->listWidget_2->item(LCSwitchmatchineRow)->setBackgroundColor(Qt::blue);
                    ui->listWidget_2->item(LCSwitchmatchineRow)->setTextColor(Qt::red);

                    if(LCSwitchmatchineRow == 1)
                    {
                        ui->listWidget_2->item(0)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_2->item(0)->setTextColor(Qt::black);
                    }

                    flagaction = true;
                    LCSwitchmatchineRow++;
                }

            }
        }
    }//end of else if(watched == ui->listWidget_2)

    //机器型号选择
    //机器型号选择
    else if(watched == ui->listWidget_3)
    {
        if(event->type() == QEvent::KeyPress)
        {
            QKeyEvent *key_event = static_cast < QKeyEvent *>(event); //将事件转化为键盘事件
            {
                if(key_event->key() == Qt::Key_F2)//下键
                {
                    LCBoolMachineModenu = true;

                    if(LCMachineModeMenu>5)
                    {
                        LCMachineModeMenu = 0;
                        ui->listWidget_3->item(5)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_3->item(5)->setTextColor(Qt::black);

                        ui->listWidget_4->setFocus();
                        ui->listWidget_4->item(LCMachineModeMenu)->setBackgroundColor(Qt::blue);
                        ui->listWidget_4->item(LCMachineModeMenu)->setTextColor(Qt::red);
                        LCBoolMachineModenu = false;
                    }

                    else
                    {
                        ui->listWidget_3->item(LCMachineModeMenu)->setBackgroundColor(Qt::blue);
                        ui->listWidget_3->item(LCMachineModeMenu)->setTextColor(Qt::red);
                    }

                    if(LCMachineModeMenu == 1)
                    {
                        ui->listWidget_3->item(0)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_3->item(0)->setTextColor(Qt::black);
                    }
                    if(LCMachineModeMenu == 2)
                    {
                        ui->listWidget_3->item(0)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_3->item(0)->setTextColor(Qt::black);
                        ui->listWidget_3->item(1)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_3->item(1)->setTextColor(Qt::black);
                    }
                    if(LCMachineModeMenu == 3)
                    {
                        ui->listWidget_3->item(0)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_3->item(0)->setTextColor(Qt::black);
                        ui->listWidget_3->item(1)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_3->item(1)->setTextColor(Qt::black);
                        ui->listWidget_3->item(2)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_3->item(2)->setTextColor(Qt::black);
                    }

                    if(LCMachineModeMenu == 4)
                    {
                        ui->listWidget_3->item(0)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_3->item(0)->setTextColor(Qt::black);
                        ui->listWidget_3->item(1)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_3->item(1)->setTextColor(Qt::black);
                        ui->listWidget_3->item(2)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_3->item(2)->setTextColor(Qt::black);
                        ui->listWidget_3->item(3)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_3->item(3)->setTextColor(Qt::black);
                    }
                    if(LCMachineModeMenu == 5)
                    {
                        ui->listWidget_3->item(0)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_3->item(0)->setTextColor(Qt::black);
                        ui->listWidget_3->item(1)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_3->item(1)->setTextColor(Qt::black);
                        ui->listWidget_3->item(2)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_3->item(2)->setTextColor(Qt::black);
                        ui->listWidget_3->item(3)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_3->item(3)->setTextColor(Qt::black);
                        ui->listWidget_3->item(4)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_3->item(4)->setTextColor(Qt::black);
                    }
                    flagaction = true;
                    LCMachineModeMenu++;

                }
            }
        }
    }//end of else if(watched == ui->listWidget_3)

    //机器型号选择
    else if(watched == ui->listWidget_4)
    {
        if(event->type() == QEvent::KeyPress)
        {
            QKeyEvent *key_event = static_cast < QKeyEvent *>(event); //将事件转化为键盘事件
            {
                if(key_event->key() == Qt::Key_F2)//下键
                {
                    if(LCMachineModeMenu>5)
                    {

                        LCMachineModeMenu = 0;
                        ui->listWidget_4->item(5)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_4->item(5)->setTextColor(Qt::black);

                        ui->listWidget_3->setFocus();
                        ui->listWidget_3->item(0)->setBackgroundColor(Qt::blue);
                        ui->listWidget_3->item(0)->setTextColor(Qt::red);
                        LCBoolMachineModenu = true;
                    }
                    else
                    {
                        ui->listWidget_4->item(LCMachineModeMenu)->setBackgroundColor(Qt::blue);
                        ui->listWidget_4->item(LCMachineModeMenu)->setTextColor(Qt::red);
                    }



                    if(LCMachineModeMenu == 1)
                    {
                        ui->listWidget_4->item(0)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_4->item(0)->setTextColor(Qt::black);
                    }
                    if(LCMachineModeMenu == 2)
                    {
                        ui->listWidget_4->item(0)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_4->item(0)->setTextColor(Qt::black);
                        ui->listWidget_4->item(1)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_4->item(1)->setTextColor(Qt::black);
                    }
                    if(LCMachineModeMenu == 3)
                    {
                        ui->listWidget_4->item(0)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_4->item(0)->setTextColor(Qt::black);
                        ui->listWidget_4->item(1)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_4->item(1)->setTextColor(Qt::black);
                        ui->listWidget_4->item(2)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_4->item(2)->setTextColor(Qt::black);
                    }

                    if(LCMachineModeMenu == 4)
                    {
                        ui->listWidget_4->item(0)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_4->item(0)->setTextColor(Qt::black);
                        ui->listWidget_4->item(1)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_4->item(1)->setTextColor(Qt::black);
                        ui->listWidget_4->item(2)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_4->item(2)->setTextColor(Qt::black);
                        ui->listWidget_4->item(3)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_4->item(3)->setTextColor(Qt::black);
                    }
                    if(LCMachineModeMenu == 5)
                    {
                        ui->listWidget_4->item(0)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_4->item(0)->setTextColor(Qt::black);
                        ui->listWidget_4->item(1)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_4->item(1)->setTextColor(Qt::black);
                        ui->listWidget_4->item(2)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_4->item(2)->setTextColor(Qt::black);
                        ui->listWidget_4->item(3)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_4->item(3)->setTextColor(Qt::black);
                        ui->listWidget_4->item(4)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_4->item(4)->setTextColor(Qt::black);
                    }
                    flagaction = true;
                    LCMachineModeMenu++;
                }
            }
        }
    }//end of else if(watched == ui->listWidget_4)

    //机型选择
    else if(watched == ui->listWidget_5)
    {
        if(event->type() == QEvent::KeyPress)
        {
            QKeyEvent *key_event = static_cast < QKeyEvent *>(event); //将事件转化为键盘事件
            {
                if(key_event->key() == Qt::Key_F2)//下键
                {
                    if(LCEngineSwitchMenu>4)
                    {
                        LCEngineSwitchMenu = 0;
                        ui->listWidget_5->item(4)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_5->item(4)->setTextColor(Qt::black);
                    }

                    ui->listWidget_5->item(LCEngineSwitchMenu)->setBackgroundColor(Qt::blue);
                    ui->listWidget_5->item(LCEngineSwitchMenu)->setTextColor(Qt::red);

                    if(LCEngineSwitchMenu == 1)
                    {
                        ui->listWidget_5->item(0)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_5->item(0)->setTextColor(Qt::black);
                    }
                    if(LCEngineSwitchMenu == 2)
                    {
                        ui->listWidget_5->item(0)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_5->item(0)->setTextColor(Qt::black);
                        ui->listWidget_5->item(1)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_5->item(1)->setTextColor(Qt::black);
                    }
                    if(LCEngineSwitchMenu == 3)
                    {
                        ui->listWidget_5->item(0)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_5->item(0)->setTextColor(Qt::black);
                        ui->listWidget_5->item(1)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_5->item(1)->setTextColor(Qt::black);
                        ui->listWidget_5->item(2)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_5->item(2)->setTextColor(Qt::black);
                    }

                    if(LCEngineSwitchMenu == 4)
                    {
                        ui->listWidget_5->item(0)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_5->item(0)->setTextColor(Qt::black);
                        ui->listWidget_5->item(1)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_5->item(1)->setTextColor(Qt::black);
                        ui->listWidget_5->item(2)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_5->item(2)->setTextColor(Qt::black);
                        ui->listWidget_5->item(3)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_5->item(3)->setTextColor(Qt::black);
                    }

                    flagaction = true;
                    LCEngineSwitchMenu++;
                }

            }
        }
    }//end of else if(watched == ui->listWidget_2)

    //主机故障查询
    else if(watched == ui->tableWidget)
    {
        if(event->type() == QEvent::KeyPress)
        {
            QKeyEvent *key_event = static_cast < QKeyEvent *>(event); //将事件转化为键盘事件
            {
                if(key_event->key() == Qt::Key_F2)//下键
                {

                    if(LCZhujiFault>=10)
                    {
                        LCZhujiFault = 0;
                       // ui->tableWidget->setStyleSheet("background-color:red;");//selection-
                        ui->tableWidget->hasFocus();
                        ui->tableWidget->setCurrentCell(LCZhujiFault,0);
                        ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

                    }
                    else
                    {
                        ui->tableWidget->setCurrentCell(LCZhujiFault,0);
                        ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
                    }

                    flagaction = true;
                    LCZhujiFault++;

                }
                //向下键
                else if (key_event->key() == Qt::Key_F3)
                {
                    LCZhujiFault--;
                    if(LCZhujiFault <= 0)
                    {
                        LCZhujiFault = 0;
                    }
                    ui->tableWidget->setCurrentCell(LCZhujiFault,0);
                    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
                    flagaction = true;
                    return true;
                }//向上键
                else if (key_event->key() == Qt::Key_F4)
                {
                    LCZhujiFault++;

                    if(LCZhujiFault >= 10)
                    {
                        LCZhujiFault = 0;
                    }

                    ui->tableWidget->setCurrentCell(LCZhujiFault,0);
                    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
                    flagaction = true;
                    return true;
                }

            }
        }
    }//end of  else if(watched == ui->tableWidget)

    //发动机故障查询
    else if(watched == ui->tableWidget_2)
    {
        if(event->type() == QEvent::KeyPress)
        {
            QKeyEvent *key_event = static_cast < QKeyEvent *>(event); //将事件转化为键盘事件
            {
                if(key_event->key() == Qt::Key_F2)//下键
                {

                    if(LCEngineFault>=10)
                    {
                        LCEngineFault = 0;
                       // ui->tableWidget->setStyleSheet("background-color:red;");//selection-
                        ui->tableWidget_2->hasFocus();
                        ui->tableWidget_2->setCurrentCell(LCEngineFault,0);
                        ui->tableWidget_2->setSelectionBehavior(QAbstractItemView::SelectRows);

                    }
                    else
                    {
                        ui->tableWidget_2->setCurrentCell(LCEngineFault,0);
                        ui->tableWidget_2->setSelectionBehavior(QAbstractItemView::SelectRows);
                    }

                    flagaction = true;
                    LCEngineFault++;

                }
                //向下键
                else if (key_event->key() == Qt::Key_F3)
                {
                    LCEngineFault--;
                    if(LCEngineFault <= 0)
                    {
                        LCEngineFault = 0;
                    }
                    ui->tableWidget_2->setCurrentCell(LCEngineFault,0);
                    ui->tableWidget_2->setSelectionBehavior(QAbstractItemView::SelectRows);
                    flagaction = true;
                    return true;
                }//向上键
                else if (key_event->key() == Qt::Key_F4)
                {
                    LCEngineFault++;

                    if(LCEngineFault >= 10)
                    {
                        LCEngineFault = 0;
                    }

                    ui->tableWidget_2->setCurrentCell(LCEngineFault,0);
                    ui->tableWidget_2->setSelectionBehavior(QAbstractItemView::SelectRows);
                    flagaction = true;
                    return true;
                }

            }
        }
    }//end of  else if(watched == ui->tableWidget_2)



    //2017.4.6
    //阀值标定
    else if((watched == ui->lineEdit_23)||(watched ==ui->lineEdit_24)||(watched == ui->lineEdit_25)||(watched == ui->lineEdit_26)||(watched == ui->lineEdit_27)||(watched == ui->lineEdit_28)||(watched == ui->lineEdit_29)||(watched == ui->lineEdit_30))
    {
        if(event->type() == QEvent::KeyPress)
        {
            QKeyEvent *key_event = static_cast < QKeyEvent *>(event); //将事件转化为键盘事件
            {
                if(key_event->key() == Qt::Key_F2)//下键
                {
                    bool m1 = ui->lineEdit_23->hasFocus();
                    bool m2 = ui->lineEdit_24->hasFocus();
                    bool m3 = ui->lineEdit_25->hasFocus();
                    bool m4 = ui->lineEdit_26->hasFocus();
                    bool m5 = ui->lineEdit_27->hasFocus();
                    bool m6 = ui->lineEdit_28->hasFocus();
                    bool m7 = ui->lineEdit_29->hasFocus();
                    bool m8 = ui->lineEdit_30->hasFocus();

                    if(m1)
                    {
                    focusNextChild();
                    ui->lineEdit_24->setFocus();
                    ui->lineEdit_24->hasFocus();

                    QPalette p1=QPalette();
                    p1.setColor(QPalette::Base,Qt::blue);
                    ui->lineEdit_24->setPalette(p1);

                    QPalette p2=QPalette();
                    p2.setColor(QPalette::Base,Qt::white);
                    ui->lineEdit_23->setPalette(p2);

                    }
                    if(m2)
                    {
                        focusNextChild();
                        ui->lineEdit_25->setFocus();
                        ui->lineEdit_25->hasFocus();

                        QPalette p1=QPalette();
                        p1.setColor(QPalette::Base,Qt::blue);
                        ui->lineEdit_25->setPalette(p1);

                        QPalette p2=QPalette();
                        p2.setColor(QPalette::Base,Qt::white);
                        ui->lineEdit_24->setPalette(p2);

                    }
                    if(m3)
                    {
                        focusNextChild();
                        ui->lineEdit_26->setFocus();
                        ui->lineEdit_26->hasFocus();

                        QPalette p1=QPalette();
                        p1.setColor(QPalette::Base,Qt::blue);
                        ui->lineEdit_26->setPalette(p1);

                        QPalette p2=QPalette();
                        p2.setColor(QPalette::Base,Qt::white);
                        ui->lineEdit_25->setPalette(p2);

                    }
                    if(m4)
                    {
                        focusNextChild();
                        ui->lineEdit_27->setFocus();
                        ui->lineEdit_27->hasFocus();

                        QPalette p1=QPalette();
                        p1.setColor(QPalette::Base,Qt::blue);
                        ui->lineEdit_27->setPalette(p1);

                        QPalette p2=QPalette();
                        p2.setColor(QPalette::Base,Qt::white);
                        ui->lineEdit_26->setPalette(p2);

                    }
                    if(m5)
                    {
                        focusNextChild();
                        ui->lineEdit_28->setFocus();
                        ui->lineEdit_28->hasFocus();

                        QPalette p1=QPalette();
                        p1.setColor(QPalette::Base,Qt::blue);
                        ui->lineEdit_28->setPalette(p1);

                        QPalette p2=QPalette();
                        p2.setColor(QPalette::Base,Qt::white);
                        ui->lineEdit_27->setPalette(p2);

                    }
                    if(m6)
                    {
                        focusNextChild();
                        ui->lineEdit_29->setFocus();
                        ui->lineEdit_29->hasFocus();

                        QPalette p1=QPalette();
                        p1.setColor(QPalette::Base,Qt::blue);
                        ui->lineEdit_29->setPalette(p1);

                        QPalette p2=QPalette();
                        p2.setColor(QPalette::Base,Qt::white);
                        ui->lineEdit_28->setPalette(p2);

                    }
                    if(m7)
                    {
                        focusNextChild();
                        ui->lineEdit_30->setFocus();
                        ui->lineEdit_30->hasFocus();

                        QPalette p1=QPalette();
                        p1.setColor(QPalette::Base,Qt::blue);
                        ui->lineEdit_30->setPalette(p1);

                        QPalette p2=QPalette();
                        p2.setColor(QPalette::Base,Qt::white);
                        ui->lineEdit_29->setPalette(p2);

                    }
                    if(m8)
                    {
                        focusNextChild();
                        ui->lineEdit_23->setFocus();
                        ui->lineEdit_23->hasFocus();

                        QPalette p1=QPalette();
                        p1.setColor(QPalette::Base,Qt::blue);
                        ui->lineEdit_23->setPalette(p1);

                        QPalette p2=QPalette();
                        p2.setColor(QPalette::Base,Qt::white);
                        ui->lineEdit_30->setPalette(p2);


                    }

                    flagaction = true;
                    return true;
                }
                else if (key_event->key() == Qt::Key_F4)
                {


                    bool mm1 = ui->lineEdit_23->hasFocus();
                    bool mm2 = ui->lineEdit_24->hasFocus();
                    bool mm3 = ui->lineEdit_25->hasFocus();
                    bool mm4 = ui->lineEdit_26->hasFocus();
                    bool mm5 = ui->lineEdit_27->hasFocus();
                    bool mm6 = ui->lineEdit_28->hasFocus();
                    bool mm7 = ui->lineEdit_29->hasFocus();
                    bool mm8 = ui->lineEdit_30->hasFocus();


                    if(mm1)
                    {
                        zlh++;
                        QString strzlh = QString("%1").arg(zlh);
                        ui->lineEdit_23->setText(strzlh);
                    }
                    if(mm2)
                    {
                        gtzs++;
                        QString strgtzs = QString("%1").arg(gtzs);
                        ui->lineEdit_24->setText(strgtzs);
                    }
                    if(mm3)
                    {
                        xllh++;
                        QString strxllh = QString("%1").arg(xllh);
                        ui->lineEdit_25->setText(strxllh);
                    }
                    if(mm4)
                    {
                        fjzs++;
                        QString strfjzs = QString("%1").arg(fjzs);
                        ui->lineEdit_26->setText(strfjzs);
                    }
                    if(mm5)
                    {
                        gqlh++;
                        QString strgqlh = QString("%1").arg(gqlh);
                        ui->lineEdit_27->setText(strgqlh);
                    }
                    if(mm6)
                    {
                        jlzs++;
                        QString strjlzs = QString("%1").arg(jlzs);
                        ui->lineEdit_28->setText(strjlzs);
                    }
                    if(mm7)
                    {
                        gqzs++;
                        QString strgqzs = QString("%1").arg(gqzs);
                        ui->lineEdit_29->setText(strgqzs);
                    }

                    flagaction = true;
                    return true;
                }
                else if (key_event->key() == Qt::Key_F3)
                {
                    bool mm1 = ui->lineEdit_23->hasFocus();
                    bool mm2 = ui->lineEdit_24->hasFocus();
                    bool mm3 = ui->lineEdit_25->hasFocus();
                    bool mm4 = ui->lineEdit_26->hasFocus();
                    bool mm5 = ui->lineEdit_27->hasFocus();
                    bool mm6 = ui->lineEdit_28->hasFocus();
                    bool mm7 = ui->lineEdit_29->hasFocus();
                    bool mm8 = ui->lineEdit_30->hasFocus();


                    if(mm1)
                    {
                        zlh--;
                        QString strzlh = QString("%1").arg(zlh);
                        ui->lineEdit_23->setText(strzlh);
                    }
                    if(mm2)
                    {
                        gtzs--;
                        QString strgtzs = QString("%1").arg(gtzs);
                        ui->lineEdit_24->setText(strgtzs);
                    }
                    if(mm3)
                    {
                        xllh--;
                        QString strxllh = QString("%1").arg(xllh);
                        ui->lineEdit_25->setText(strxllh);
                    }
                    if(mm4)
                    {
                        fjzs--;
                        QString strfjzs = QString("%1").arg(fjzs);
                        ui->lineEdit_26->setText(strfjzs);
                    }
                    if(mm5)
                    {
                        gqlh--;
                        QString strgqlh = QString("%1").arg(gqlh);
                        ui->lineEdit_27->setText(strgqlh);
                    }
                    if(mm6)
                    {
                        jlzs--;
                        QString strjlzs = QString("%1").arg(jlzs);
                        ui->lineEdit_28->setText(strjlzs);
                    }
                    if(mm7)
                    {
                        gqzs--;
                        QString strgqzs = QString("%1").arg(gqzs);
                        ui->lineEdit_29->setText(strgqzs);
                    }

                    flagaction = true;
                    return true;
                }

                else if ((key_event->key() == Qt::Key_F5)&&(watched == ui->lineEdit_30))
                {
                    bool mm8 = ui->lineEdit_30->hasFocus();
                    if(mm8)
                    {
                        qDebug()<<"kddddddddddddddddddddddddddddddddddddddddddddddddd"<<endl;
                    }


                    zlh  = 80;
                    xllh = 80;
                    gqlh = 80;
                    gtzs = 10;
                    fjzs = 10;
                    jlzs = 10;
                    gqzs = 10;

                    //2017.4.22    //更新阀值设定数据库

                      QTextCodec::setCodecForTr(QTextCodec::codecForLocale());//汉字显示
                      QSqlDatabase db;
                      if(QSqlDatabase::contains("qt_sql_default_connection"))
                        db = QSqlDatabase::database("qt_sql_default_connection");
                      else
                        db = QSqlDatabase::addDatabase("QSQLITE");

                     db.setDatabaseName("jy.db");
                     if (!db.open())
                     {
                         qDebug()<<"open database failed ---"<<db.lastError().text()<<endl;
                     }
                     QSqlQuery query;

                     query.prepare("update FaZhiBingBD set ZLH = :ZLH,XLLH = :XLLH,GQLH = :GQLH,LmdGTZS = :LmdGQZS,LmdFengJi = :LmdFengJi,LmdJiaoLong = :LmdJiaoLong,LmdGuoQiao = :LmdGuoQiao");//where
                     query.bindValue(":ZLH",zlh);
                     query.bindValue(":XLLH", xllh);
                     query.bindValue(":GQLH", gqlh);
                     query.bindValue(":LmdGTZS", gtzs);
                     query.bindValue(":LmdFengJi", fjzs);
                     query.bindValue(":LmdJiaoLong", jlzs);
                     query.bindValue(":LmdGuoQiao", gqzs);
                     query.exec();

                    query.exec(QObject::tr("drop FaZhiBingBD"));

                    ui->lineEdit_23->setText("80");
                    ui->lineEdit_24->setText("10");
                    ui->lineEdit_25->setText("80");
                    ui->lineEdit_26->setText("10");
                    ui->lineEdit_27->setText("80");
                    ui->lineEdit_28->setText("10");
                    ui->lineEdit_29->setText("10");

                    //2017.5.23
                    //发送给控制器器

                    flagaction = true;
                    return true;
                }

            }
        }
    } //clearmenu F2键过滤


    //标定菜单
    else if(watched == ui->listWidget_6)
    {
        if(event->type() == QEvent::KeyPress)
        {
            QKeyEvent *key_event = static_cast < QKeyEvent *>(event); //将事件转化为键盘事件
            {
                if(key_event->key() == Qt::Key_F2)//下键
                {
                    qDebug()<<"Biaodingcaidan"<<endl;
                   if(LCBiaoDingRow>2)
                   {
                       LCBiaoDingRow = 0;
                       ui->listWidget_6->item(2)->setBackgroundColor(Qt::transparent);
                       ui->listWidget_6->item(2)->setTextColor(Qt::black);
                   }

                   ui->listWidget_6->item(LCBiaoDingRow)->setBackgroundColor(Qt::blue);
                   ui->listWidget_6->item(LCBiaoDingRow)->setTextColor(Qt::red);

                   if(LCBiaoDingRow == 1)
                   {
                       ui->listWidget_6->item(0)->setBackgroundColor(Qt::transparent);
                       ui->listWidget_6->item(0)->setTextColor(Qt::black);
                   }
                   if(LCBiaoDingRow == 2)
                   {
                       ui->listWidget_6->item(1)->setBackgroundColor(Qt::transparent);
                       ui->listWidget_6->item(1)->setTextColor(Qt::black);
                   }

                    flagaction = true;
                    LCBiaoDingRow++;
                    return true;
                }

            }
        }
    }//end of else if(watched == ui->listWidget_6)


    //2017.5.5 从新开始新的交互体验
    else if((watched == ui->listWidget_7)||(watched == ui->lineEdit_3)||(watched == ui->lineEdit_4)||(watched == ui->lineEdit_5)||(watched == ui->lineEdit_6))
    {
        if(event->type() == QEvent::KeyPress)
        {
            QKeyEvent *key_event = static_cast < QKeyEvent *>(event); //将事件转化为键盘事件
            {
                bool ff1 = ui->listWidget_7->hasFocus();
                bool ff2 = ui->lineEdit_3->hasFocus();
                bool ff3 = ui->lineEdit_4->hasFocus();
                bool ff4 = ui->lineEdit_5->hasFocus();
                bool ff5 = ui->lineEdit_6->hasFocus();

                if(ff1)
                {
                    ui->listWidget_7->item(LCGetaiSetup)->setBackgroundColor(Qt::yellow);
                    ui->listWidget_7->item(LCGetaiSetup)->setTextColor(Qt::red);
                }

                if(key_event->key() == Qt::Key_F2)//下键
                {

                    if(ff1)
                    {
                        focusNextChild();
                        ui->lineEdit_3->hasFocus();
                    }
                    if(ff2)
                    {
                        focusNextChild();
                        ui->lineEdit_4->hasFocus();

                    }
                    if(ff3)
                    {
                        focusNextChild();
                        ui->lineEdit_5->hasFocus();
                    }
                    if(ff4)
                    {
                        focusNextChild();
                        ui->lineEdit_6->hasFocus();
                    }
                    if(ff5)
                    {
                        focusNextChild();
                        ui->listWidget_7->hasFocus();
                    }

                    flagaction = true;
                }

                else if (key_event->key() == Qt::Key_F3)
                {
                    if(ff1)
                    {
                      LCGetaiSetup--;
                      if(LCGetaiSetup <=0)
                      {
                          LCGetaiSetup = 0;
                      }
                      ui->listWidget_7->item(LCGetaiSetup)->setBackgroundColor(Qt::yellow);
                      ui->listWidget_7->item(LCGetaiSetup)->setTextColor(Qt::red);
                      ui->listWidget_7->item(LCGetaiSetup+1)->setBackgroundColor(Qt::transparent);
                      ui->listWidget_7->item(LCGetaiSetup+1)->setTextColor(Qt::black);
                    }

                    if(ff2)
                    {
                        GeFuWidth--;
                        QString strGeFuWidth = QString("%1").arg(GeFuWidth);
                        ui->lineEdit_3->setText(strGeFuWidth);
                    }
                    if(ff3)
                    {
                         Zaihexishu--;
                        QString strZaihexishu = QString("%1").arg(Zaihexishu);
                        ui->lineEdit_4->setText(strZaihexishu);
                    }
                    if(ff4)
                    {
                        Autospeed--;
                        QString strAutospeed = QString("%1").arg(Autospeed);
                        ui->lineEdit_5->setText(strAutospeed);
                    }
                    flagaction = true;
                   return true;
                }
                else if (key_event->key() == Qt::Key_F4)
                {
                    if(ff1)
                    {
                        LCGetaiSetup++;
                        if(LCGetaiSetup >=7)
                        {
                            LCGetaiSetup = 7;
                        }
                        ui->listWidget_7->item(LCGetaiSetup)->setBackgroundColor(Qt::yellow);
                        ui->listWidget_7->item(LCGetaiSetup)->setTextColor(Qt::red);
                        ui->listWidget_7->item(LCGetaiSetup-1)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_7->item(LCGetaiSetup-1)->setTextColor(Qt::black);
                    }
                    if(ff2)
                    {
                        GeFuWidth++;
                        QString strGeFuWidth = QString("%1").arg(GeFuWidth);
                        ui->lineEdit_3->setText(strGeFuWidth);
                    }
                    if(ff3)
                    {
                         Zaihexishu++;
                        QString strZaihexishu = QString("%1").arg(Zaihexishu);
                        ui->lineEdit_4->setText(strZaihexishu);
                    }
                    if(ff4)
                    {
                        Autospeed++;
                        QString strAutospeed = QString("%1").arg(Autospeed);
                        ui->lineEdit_5->setText(strAutospeed);
                    }
                    flagaction = true;
                    return true;
                }
                else if ((key_event->key() == Qt::Key_F5)&&(watched == ui->lineEdit_6))
                {
                    //2017.5.5 割台数据库添加
                    //割台参数设置
                  #if 1
                        QTextCodec::setCodecForTr(QTextCodec::codecForLocale());//汉字显示
                        QSqlDatabase db;
                        if(QSqlDatabase::contains("qt_sql_default_connection"))
                          db = QSqlDatabase::database("qt_sql_default_connection");
                        else
                          db = QSqlDatabase::addDatabase("QSQLITE");

                       db.setDatabaseName("jy.db");
                       if (!db.open())
                       {
                           qDebug()<<"open database failed ---"<<db.lastError().text()<<endl;
                       }
                       QSqlQuery query;
                       #if 0
                       bool ok = query.exec("create table GeTaiBD(GuWuSwitch INTEGER,GeFuWidth INTEGER,ZaiHeXishu INTEGER,ChangeSpeed INTEGER)");
                       if (ok)
                       {
                           qDebug()<<"ceate table partition success"<<endl;
                       }
                       else
                       {
                           qDebug()<<"ceate table partition failed"<<endl;
                       }
                       #endif

                       //query.prepare("INSERT INTO GeTaiBD(GuWuSwitch, GeFuWidth, ZaiHeXishu,ChangeSpeed) VALUES (:GuWuSwitch, :GeFuWidth,:ZaiHeXishu, :ChangeSpeed)");
                       query.prepare("update GeTaiBD set GuWuSwitch = :GuWuSwitch,GeFuWidth = :GeFuWidth,ZaiHeXishu = :ZaiHeXishu,ChangeSpeed = :ChangeSpeed");//where

                       query.bindValue(":GuWuSwitch",1);
                       query.bindValue(":GeFuWidth", 11);
                       query.bindValue(":ZaiHeXishu", 66);
                       query.bindValue(":ChangeSpeed", 77);
                       query.exec();

                     query.exec("select GuWuSwitch, GeFuWidth, ZaiHeXishu,ChangeSpeed from GeTaiBD");
                     while (query.next())
                     {

                        qDebug()<<"id("<<query.value(0).toInt()<<")  name:"<<query.value(1).toString()<<"  age:"<<query.value(2).toInt();

                     }
                      query.exec(QObject::tr("drop GuWuSwitch"));

                  #endif

                    ui->lineEdit_3->setText("3140");
                    ui->lineEdit_4->setText("5");
                    ui->lineEdit_5->setText("80");

                    ui->listWidget_7->item(LCGetaiSetup)->setBackgroundColor(Qt::transparent);
                    ui->listWidget_7->item(LCGetaiSetup)->setTextColor(Qt::black);
                    LCGetaiSetup = 1;

                    ui->listWidget_7->item(LCGetaiSetup)->setBackgroundColor(Qt::yellow);
                    ui->listWidget_7->item(LCGetaiSetup)->setTextColor(Qt::red);

                    flagaction = true;
                    return true;
                }

            }
        }
    }


    //匹配性标定
    else if((watched == ui->tableWidget_3)||(watched == ui->lineEdit_7))//
    {
        if(event->type() == QEvent::KeyPress)
        {
            QKeyEvent *key_event = static_cast < QKeyEvent *>(event); //将事件转化为键盘事件
            {
                if(key_event->key() == Qt::Key_F2)//下键
                {

                    bool mm1 = ui->tableWidget_3->hasFocus();
                    bool mm2 = ui->lineEdit_7->hasFocus();
                    if(mm1)
                    {
#if 1
                    if(LCPiPeixingBiaoDing>=6)
                    {
                        LCPiPeixingBiaoDing = 0;
                       // ui->tableWidget->setStyleSheet("background-color:red;");//selection-
                        ui->tableWidget_3->hasFocus();

                        #if 0
                        ui->tableWidget_3->setCurrentCell(LCPiPeixingBiaoDing,0);
                        ui->tableWidget_3->setSelectionBehavior(QAbstractItemView::SelectItems);
                        #endif

                        ui->tableWidget_3->setCurrentCell(LCPiPeixingBiaoDing,0);
                        ui->tableWidget_3->setSelectionBehavior(QAbstractItemView::SelectItems);

                    }
                    else
                    {
                        if(LCPiPeixingBiaoDing>=3)
                        {
                                ui->tableWidget_3->setCurrentCell(LCPiPeixingBiaoDing-3,5);
                                ui->tableWidget_3->setSelectionBehavior(QAbstractItemView::SelectItems);//SelectRows
                                if(LCPiPeixingBiaoDing == 5)
                                {
                                    focusNextChild();
                                    ui->lineEdit_7->setFocus();
                                }
                        }
                        else
                        {
                            //qDebug()<<"k666666666666666666666666666kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk"<<endl;

                            ui->tableWidget_3->setCurrentCell(LCPiPeixingBiaoDing,0);
                            ui->tableWidget_3->setSelectionBehavior(QAbstractItemView::SelectItems);//SelectRows
                            //ui->tableWidget_3->hasFocus();
                        }

                    }
//                    flagaction = true;
                    LCPiPeixingBiaoDing++;
#endif
                    }
                    if(mm2)
                    {
                        LCPiPeixingBiaoDing = 0;
                        focusNextChild();
                        ui->tableWidget_3->hasFocus();
                        ui->tableWidget_3->setCurrentCell(LCPiPeixingBiaoDing,0);
                        ui->tableWidget_3->setSelectionBehavior(QAbstractItemView::SelectItems);//SelectRows
                        LCPiPeixingBiaoDing++;
                    }

                    flagaction = true;
                    return true;
                }

                //向下键
                else if (key_event->key() == Qt::Key_F3)
                {

                    /********************2017.4.27************************************/
                    if(LCPiPeixingBiaoDing==4)
                    {
                         shoubingoffset--;
                    }
                    else if(LCPiPeixingBiaoDing==5)
                    {
                        langanoffset--;
                    }

                    /*****************************************************************/

                    flagaction = true;
                    return true;
                }//向上键
                else if (key_event->key() == Qt::Key_F4)
                {

                    /********************2017.4.27************************************/
                    if(LCPiPeixingBiaoDing==4)
                    {
                         shoubingoffset++;
                    }
                    else if(LCPiPeixingBiaoDing==5)
                    {
                        langanoffset++;
                    }

                    /*****************************************************************/

                    qDebug()<<"LCPiPeixingBiaoDing: "<<LCPiPeixingBiaoDing<<endl;

                    flagaction = true;
                    return true;
                }
                else if ((key_event->key() == Qt::Key_F5)&&(watched == ui->lineEdit_7))
                {

                    //2017.5.21

                    //恢復默認值
                    SendReqCmdToController(GUI_CMD_CFG_REQ_DefaultRestore_XinZouJuBing,0);
                    SendReqCmdToController(GUI_CMD_CFG_REQ_DefaultRestore_XinZouLaGan,0);
                    GetRspDataFromController(&biaoding);

                    shoubingoffset = 200;
                    langanoffset = 100;

                    //2017.4.28    //更新匹配性标定设定数据库

                    //手柄标定数据库创建

                        //static unsigned char nn = 1;
                        QTextCodec::setCodecForTr(QTextCodec::codecForLocale());//汉字显示
                        QSqlDatabase db;
                        if(QSqlDatabase::contains("qt_sql_default_connection"))
                          db = QSqlDatabase::database("qt_sql_default_connection");
                        else
                          db = QSqlDatabase::addDatabase("QSQLITE");

                       db.setDatabaseName("jy.db");
                       if (!db.open())
                       {
                           qDebug()<<"open database failed ---"<<db.lastError().text()<<endl;
                       }
                       QSqlQuery query;
                       #if 0
                       bool ok = query.exec("create table ShouBingBD(TrueValue INTEGER,SmallValue INTEGER,MiddleValue INTEGER,BigValue INTEGER,OffSetValue INTEGER)");
                       if (ok)
                       {
                           qDebug()<<"ceate table partition success"<<endl;
                       }
                       else
                       {
                           qDebug()<<"ceate table partition failed"<<endl;
                       }
                       #endif

                       //query.prepare("INSERT INTO ShouBingBD(TrueValue, SmallValue, MiddleValue,BigValue,OffSetValue) VALUES (:TrueValue, :SmallValue,:MiddleValue, :BigValue,:OffSetValue)");
                       query.prepare("update ShouBingBD set TrueValue = :TrueValue,SmallValue = :SmallValue,MiddleValue = :MiddleValue,BigValue = :BigValue,OffSetValue = :OffSetValue");//where

                       query.bindValue(":TrueValue",66);
                       query.bindValue(":SmallValue", 66);
                       query.bindValue(":MiddleValue", 66);
                       query.bindValue(":BigValue", 66);
                       query.bindValue(":OffSetValue", 66);
                       query.exec();


                       query.bindValue(":TrueValue",66);
                       query.bindValue(":SmallValue", 66);
                       //query.bindValue(":MiddleValue", 66);
                       query.bindValue(":BigValue", 66);
                       //query.bindValue(":OffSetValue", 66);
                       query.exec();

                     query.exec("select TrueValue, SmallValue,MiddleValue,BigValue,OffSetValue from ShouBingBDS");
                     while (query.next())
                     {

                        qDebug()<<"id("<<query.value(0).toInt()<<")  name:"<<query.value(1).toString()<<"  age:"<<query.value(2).toInt();

                     }

                      query.exec(QObject::tr("drop ShouBingBDS"));

                    /****************************添加最小值，最大值，中间值，偏移量*******************************************************/
                    //2017.4.26
#if 0
                        //ui->tableWidget_3->setItem(0,0,new QTableWidgetItem("99"));
                        ui->tableWidget_3->setItem(0,1,new QTableWidgetItem("99"));
                        ui->tableWidget_3->setItem(0,2,new QTableWidgetItem("99"));
                        ui->tableWidget_3->setItem(0,3,new QTableWidgetItem("99"));
                        ui->tableWidget_3->setItem(0,4,new QTableWidgetItem("99"));
                        ui->tableWidget_3->setItem(0,5,new QTableWidgetItem("99"));


                        //ui->tableWidget_3->setItem(1,0,new QTableWidgetItem(10));
                        ui->tableWidget_3->setItem(1,1,new QTableWidgetItem("99"));
                        ui->tableWidget_3->setItem(1,2,new QTableWidgetItem("99"));
                        ui->tableWidget_3->setItem(1,3,new QTableWidgetItem("99"));
                        ui->tableWidget_3->setItem(1,4,new QTableWidgetItem("99"));
                        ui->tableWidget_3->setItem(1,5,new QTableWidgetItem("99"));

                        //ui->tableWidget_3->setItem(2,0,new QTableWidgetItem(10));
                        ui->tableWidget_3->setItem(2,1,new QTableWidgetItem("99"));
                        ui->tableWidget_3->setItem(2,2,new QTableWidgetItem("99"));
                        //ui->tableWidget_3->setItem(2,3,new QTableWidgetItem("99"));
                        ui->tableWidget_3->setItem(2,4,new QTableWidgetItem("99"));
                        //ui->tableWidget_3->setItem(2,5,new QTableWidgetItem("99"));
#endif
                    /***************************************************************************************************************/

                }
            }
        }
    }//end of  else if(watched == ui->tableWidget_3)


    return QWidget::eventFilter(watched,event);
}

//绘制label_5 上的指针
void Widget::fun2()
{
#if 1
               QPainter painterlabel5(ui->label_5);
               //km/h
               painterlabel5.translate(102, 102);//重新定位坐标起始点，把坐标原点放到窗体的中央
               //painter.scale(side / 400.0, side / 300.0);

               static const QPoint hourHand[4] = {
                   QPoint(8, 0),
                   QPoint(-8,0),
                   QPoint(-1.5, -80),
                   QPoint(1.5, -80)
               };

               painterlabel5.setPen(Qt::NoPen);
               painterlabel5.setBrush(Qt::red);
               painterlabel5.setRenderHint(QPainter::Antialiasing, true);
               painterlabel5.save();

               //painter.rotate(6.0 *time.second());  //设旋转(角度 = 6° * (分钟 + 秒 / 60))
               painterlabel5.rotate(-114);
               painterlabel5.rotate(2.85*floatnu2);



               //painter.rotate(4.0 );  //设旋转(角度 = 6° * (分钟 + 秒 / 60))*shisu
               //内测用
               /****************************************************************************/
               //qDebug()<<"time: "<<time.second()<<endl;

               /****************************************************************************/

               painterlabel5.drawConvexPolygon(hourHand, 4);  //填充分针部分
               painterlabel5.setRenderHint(QPainter::Antialiasing, true);
               painterlabel5.restore();

               /***********************************************/
               //2016.6.25   画白圈
               painterlabel5.setBrush(Qt::green); //画上中心原点/home/vmuser/qtworkplace/chanpin/img2
               painterlabel5.save();
               painterlabel5.drawEllipse(QPoint(0,0),18,18);
               painterlabel5.restore();

               //画白圈
               /***********************************************/


               painterlabel5.setBrush(Qt::darkGray);
               painterlabel5.save();//画上中心原点
               painterlabel5.drawEllipse(QPoint(0,0),15,15);
               painterlabel5.restore();

               //chuli pupian shansuo
              // painter.translate(-405,-432);//平移到左上角
#endif
}

//绘制label_2 上的指针
void Widget::magicTime()
{
    QPainter painterlabel2(ui->label_2);

#if 1

        if(flagwidget == xingZouWidget)
           {

               //int side = qMin(width(), height());  //绘制的范围(宽、高中最小值)

               painterlabel2.setRenderHint(QPainter::Antialiasing);//绘制的图像反锯齿
               //painter.translate(width() / 2, height() / 2);//重新定位坐标起始点，把坐标原点放到窗体的中央

               //painter.translate(405, 184);//重新定位坐标起始点，把坐标原点放到窗体的中央
                painterlabel2.translate(103, 102);//重新定位坐标起始点，把坐标原点放到窗体的中央
               //painter.scale(side / 400.0, side / 300.0);//设定画布的边界,用窗体宽高的最小值来计算时钟的大小，防止窗体拉伸导致的时钟变形以及显示不全

               //下面两个数组用来定义表针的两个顶点，以便后面的填充
               static const QPoint hourHand[4] = {
                   QPoint(8, 0),
                   QPoint(-8,0),
                   QPoint(-1.5, -80),
                   QPoint(1.5, -80)
               };
               static const QPoint minuteHand[4] = {
                   QPoint(4, 0),
                   QPoint(-4, 0),
                   QPoint(-1, -80),
                   QPoint(1, -80)
               };

               //R/MIN

               painterlabel2.setPen(Qt::NoPen);//填充时针，不需要边线所以NoPen
               painterlabel2.setBrush(Qt::red);
               painterlabel2.setRenderHint(QPainter::Antialiasing, true);
               painterlabel2.save();
               //painter.rotate(6.0 *time.second());  //设旋转(角度 = 6° * (分钟 + 秒 / 60))
               painterlabel2.rotate(-114);

               painterlabel2.rotate(7.6*floatnu1);//floatnu1  *floatnu1

               painterlabel2.drawConvexPolygon(hourHand, 4);  //填充分针部分
               painterlabel2.restore();

               /***********************************************/
               //2016.6.25   画白圈
               painterlabel2.setBrush(Qt::green); //画上中心原点/home/vmuser/qtworkplace/chanpin/img2
               painterlabel2.save();
               painterlabel2.drawEllipse(QPoint(0,0),18,18);
               painterlabel2.restore();

               //画白圈
               /***********************************************/

               painterlabel2.setBrush(Qt::darkGray);//画上中心原点/home/vmuser/qtworkplace/chanpin/img2
               painterlabel2.save();
               painterlabel2.drawEllipse(QPoint(0,0),15,15);
               painterlabel2.restore();

           }
#endif
}

//暂时测试用到 加加时指针会转动
//void Widget::on_pushButton_clicked()
//{
//    floatnu1++;
//}

//listwidget 光标移动触发事件
void Widget::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
#if 0
    if(current== NULL)return;
    if(previous!= NULL)
    {
        previous->setBackgroundColor(Qt::transparent);
        previous->setTextColor(Qt::black);
    }
    current->setBackgroundColor(Qt::red);
    current->setTextColor(Qt::blue);
#endif
}


//超时判断 在没有任何按键按下时计数器开始计数
void Widget::timeoutfun()
{
    //2017.5.22
    if(flagwidget != PipeixingbiaodingMenu)
    {

#if 1
        if(flagaction)
        {
            flagtimeoutnum = 0;
            flagaction = false;
            //qDebug()<<"flagtimeoutnum = "<<flagtimeoutnum<<endl;
        }
        else
        {
            flagtimeoutnum++;
            //qDebug()<<"flagtimeoutnum false .......... = "<<flagtimeoutnum<<endl;
            if(flagtimeoutnum == 15)
            {
                flagtimeout = true;
            }

        }

    if(flagtimeout)
    {
        if(flagyihuovideo == 1)
        {
            //flagcurrentvideo = AV3;
            flagdbvideoCurrent = 1;
            m_camerobj.SetVideoOuputLabel(ui->label,NULL);
        }
        else
        {
            //flagcurrentvideo = AV2;
            flagdbvideoCurrent = 0;
            m_camerobj.SetVideoOuputLabel(ui->label,NULL);
        }

        flagwidget = xingZouWidget;
        ui->stackedWidget->setCurrentIndex(0);
        flagtimeout = false;
        flagtimeoutnum = 0;
    }
    //qDebug()<<"timeout"<<endl;
#endif

    }
    else
    {
        flagtimeoutnum = 0;
        flagaction = false;
    }
}


/******************************************************************************************************/
//信号槽
//

#if 0
//故障码
uchar i = 0;
void Widget::gzmslottest()//故障码显示
{
     qDebug()<<"mm ++ == "<<mm++<<endl;
     if (mm>=6)//312
     {
         mm = 0;
     }
}
#endif


////故障码
//uchar i = 0;
void Widget::gzmslottest()//故障码显示
{

//    qDebug()<<"QString::fromUtf8(ecutest.spn_can.chgzm[i])  ===   "<<QString::fromUtf8(ecutest.spn_can.chgzm[i])<<endl;
//    qDebug()<<"ecutest.spn_can.if_data  ==  "<<ecutest.spn_can.if_data<<endl;
//    qDebug()<<"ecutest.spn_can.cnt ==  "<<ecutest.spn_can.cnt<<endl;

/*************************************************************************************************************/
//
//
//2017.3.6
//

#if 0
    //故障码显示和油量状态显示
    char AddSum[12][100] = {"0"};
    //存储油量状态和通信故障状态
    char YouAndTongxinArray[2][100] = {"0"};
    char lengthYX;//存储油量状态和通信故障状态 的长度

    char *p1 = "通信故障";
    char *p2 = "油量开路";
    char *p3 = "油量短路";
    char *p4 = "油量异常";


    //计算 存储油量状态和通信故障状态 的长度
    if((ecutest.flagECU == 0)&&(cantest.StaYL != 0))
    {
        lengthYX = 1;
    }
    else if((ecutest.flagECU == 1)&&(cantest.StaYL != 0))
    {
        lengthYX = 2;
    }
    else if((ecutest.flagECU == 1)&&(cantest.StaYL == 0))
    {
        lengthYX = 1;
    }


    //油量状态位 0 正常，通信没有故障 为0.
    //通信故障判断

    //只显示故障码
    if((ecutest.flagECU == 0)&&(cantest.StaYL == 0))
    {
        memcpy(AddSum[0],ecutest.spn_can.chgzm[0],(ecutest.spn_can.cnt)*sizeof(ecutest.spn_can.chgzm[0]));
    }

    //油量开路
    else if((ecutest.flagECU == 0)&&(cantest.StaYL == 1))
    {
        YouAndTongxinArray[0][0] = *p2;
        memcpy(AddSum[0],ecutest.spn_can.chgzm[0],(ecutest.spn_can.cnt)*sizeof(ecutest.spn_can.chgzm[0]));
        memcpy(AddSum[ecutest.spn_can.cnt],YouAndTongxinArray[0],lengthYX*sizeof(YouAndTongxinArray[0]));


    }
    //油量短路
    else if((ecutest.flagECU == 0)&&(cantest.StaYL == 2))
    {
        YouAndTongxinArray[0][0] = *p3;
        memcpy(AddSum[0],ecutest.spn_can.chgzm[0],(ecutest.spn_can.cnt)*sizeof(ecutest.spn_can.chgzm[0]));
        memcpy(AddSum[ecutest.spn_can.cnt],YouAndTongxinArray[0],lengthYX*sizeof(YouAndTongxinArray[0]));
    }
    //油量异常
    else if((ecutest.flagECU == 0)&&(cantest.StaYL == 3))
    {
        YouAndTongxinArray[0][0] = *p4;
        memcpy(AddSum[0],ecutest.spn_can.chgzm[0],(ecutest.spn_can.cnt)*sizeof(ecutest.spn_can.chgzm[0]));
        memcpy(AddSum[ecutest.spn_can.cnt],YouAndTongxinArray[0],lengthYX*sizeof(YouAndTongxinArray[0]));
    }


#endif


/*************************************************************************************************************/
    QString stringzuhe = QString("spn: %1  fmi: %2").arg(QString::number(ecutest.spn_can.spn[i])).arg(QString::number(ecutest.spn_can.fmi[i]));

    //if((ecutest.spn_can.if_data == 1)&&(i < (ecutest.spn_can.cnt+1)))//是否有数据 0和1  1表示有数据
   if((ecutest.spn_can.if_data == 1)&&(i < (ecutest.spn_can.cnt+lengthYX)))//是否有数据 0和1  1表示有数据
    {
            if(flagwidget == xingZouWidget)
            {

                //qDebug()<<"after can_spn_obj.ifch[i]  ============   "<<can_spn_obj.ifch[i]<<endl;
                if(ecutest.spn_can.ifch[i] == 1)//有对应的中文故障码
                {

                    if(cantest.flagDC)
                    {
                        ui->label_2->setText("");
                    }
                    else
                    {
                        if(flagdaoche == false)
                        {
                            ui->label_4->setText(QString::fromUtf8(AddSum[i]));
                            //qDebug()<<"flagdaoche AAAA.....?????? == "<<numdaoche<<endl;
                        }
                        else if((flagdaoche == true)&&(numdaoche == 2))
                        {
                            ui->label_4->setText("");
                            flagdaoche = false;
                            //qDebug()<<"Kongkong AAAA.....?????? == "<<numdaoche<<endl;

                        }


                    }
                    //ui->label_2->setText(QString::fromUtf8(AddSum[i]));
                    //qDebug()<<"中文故障码  ============   "<<QString::fromUtf8(AddSum[i])<<endl;


                }
                else if(ecutest.spn_can.ifch[i] == 0) // 没有对应的故障码显示 spn fmi 对应的值
                {

                     //qDebug()<<"spn   fmi ========   "<<ecutest.spn_can.spn[i]<<"..........."<<ecutest.spn_can.fmi[i]<<"i ==  "<<i<<endl;
                    if((ecutest.spn_can.cnt == 1)&&(lengthYX == 1))
                    {
                        if(i != 0)
                         {
                             //ui->label_2->setText(QString::fromUtf8(AddSum[i]));
                             if(cantest.flagDC)
                             {
                                 ui->label_4->setText("");
                             }
                             else
                             {
                                 //ui->label_2->setText(QString::fromUtf8(AddSum[i]));
                                 if(flagdaoche == false)
                                 {
                                     ui->label_4->setText(QString::fromUtf8(AddSum[i]));
                                     //qDebug()<<"flagdaoche BBBBB.....?????? == "<<numdaoche<<endl;
                                 }
                                 else  if((flagdaoche == true)&&(numdaoche == 2))
                                 {
                                     ui->label_4->setText("");
                                     flagdaoche = false;
                                     //qDebug()<<"Kongkong BBBBB.....?????? == "<<numdaoche<<endl;
                                 }

                             }
                         }
                         else
                         {
                             //ui->label_2->setText(QString("spn: %1  fmi: %2").arg(QString::number(ecutest.spn_can.spn[i])).arg(QString::number(ecutest.spn_can.fmi[i])));
                             if(cantest.flagDC)
                             {
                                 ui->label_4->setText("");
                             }
                             else
                             {
                                 //ui->label_2->setText(QString("spn: %1  fmi: %2").arg(QString::number(ecutest.spn_can.spn[i])).arg(QString::number(ecutest.spn_can.fmi[i])));
                                 if(flagdaoche == false)
                                 {
                                     //ui->label_4->setText(QString::fromUtf8(AddSum[i]));
                                     ui->label_4->setText(QString("spn: %1  fmi: %2").arg(QString::number(ecutest.spn_can.spn[i])).arg(QString::number(ecutest.spn_can.fmi[i])));

                                     //qDebug()<<"flagdaoche CCCCCC.....?????? == "<<numdaoche<<endl;
                                 }
                                 else if((flagdaoche == true)&&(numdaoche == 2))
                                 {
                                     ui->label_4->setText("");
                                     flagdaoche = false;
                                     //qDebug()<<"Kongkong CCCCCCCCCCCc.....?????? == "<<numdaoche<<endl;
                                 }

                             }
                         }
                    }
                    else
                    {
                        if(i == ecutest.spn_can.cnt)
                        {
                           //ui->label_2->setText(QString::fromUtf8(AddSum[i]));
                           if(cantest.flagDC)
                           {
                               ui->label_4->setText("");
                           }
                           else
                           {
                               //ui->label_2->setText(QString::fromUtf8(AddSum[i]));
                               if(flagdaoche == false)
                               {
                                   ui->label_4->setText(QString::fromUtf8(AddSum[i]));
                                   //qDebug()<<"flagdaoche DDDDDDDDD.....?????? == "<<numdaoche<<endl;
                               }
                               else if((flagdaoche == true)&&(numdaoche == 2))
                               {
                                   ui->label_4->setText("");
                                   flagdaoche = false;
                                   //qDebug()<<"Kongkong DDDDDDDDDD.....?????? == "<<numdaoche<<endl;
                               }

                           }

                        }
                        else
                        {
                            //ui->label_2->setText(QString("spn: %1  fmi: %2").arg(QString::number(ecutest.spn_can.spn[i])).arg(QString::number(ecutest.spn_can.fmi[i])));
                            if(cantest.flagDC)
                            {
                                ui->label_4->setText("");
                            }
                            else
                            {
                                //ui->label_2->setText(QString("spn: %1  fmi: %2").arg(QString::number(ecutest.spn_can.spn[i])).arg(QString::number(ecutest.spn_can.fmi[i])));
                                if(flagdaoche == false)
                                {
                                    //ui->label_4->setText(QString::fromUtf8(AddSum[i]));
                                    ui->label_4->setText(QString("spn: %1  fmi: %2").arg(QString::number(ecutest.spn_can.spn[i])).arg(QString::number(ecutest.spn_can.fmi[i])));

                                    //qDebug()<<"flagdaoche EEEEEEEEEE.....?????? == "<<numdaoche<<endl;
                                }
                                else if((flagdaoche == true)&&(numdaoche == 2))
                                {
                                    ui->label_4->setText("");
                                    flagdaoche = false;
                                    //qDebug()<<"Kongkong EEEEEEEEEE.....?????? == "<<numdaoche<<endl;
                                }


                            }
                        }
                    }


                }
            }

            i++;

                timergzm->stop();
                timergzmTihuan->start(3000);//3000


            ecutest.spn_can.if_data = 0;
    }
    else if((ecutest.spn_can.if_data == 0)||(i >= (ecutest.spn_can.cnt+lengthYX)))//是否有数据 0和1  1表示有数据
    {
        //1
       if(i>=(ecutest.spn_can.cnt+lengthYX))
       {
            i = 0;
            memset(AddSum,0,1200);

             ui->label_15->setText("");

       }
       else
       {
           //  通信故障 和 油量开路轮流显示

          #if 1

                  //通信故障
                  if((ecutest.spn_can.if_data == 0))//是否有数据 1表示有数据
                  {
                     // qDebug()<<"QString::fromUtf8(YouAndTongxinArray[flagjuzhongnum]) == "<<QString::fromUtf8(YouAndTongxinArray[flagjuzhongnum])<<endl;

                     if(flagjuzhongnum < lengthYX)
                     {

                      //ui->label_17->setText(QString::fromUtf8(YouAndTongxinArray[flagjuzhongnum]));

                      if(cantest.flagDC)
                      {
                          ui->label_4->setText("");
                          ui->label_15->setText("");
                      }
                      else
                      {
                           //ui->label_17->setText(QString::fromUtf8(YouAndTongxinArray[flagjuzhongnum]));
                          if(flagdaoche == false)
                          {
                              ui->label_15->setText(QString::fromUtf8(YouAndTongxinArray[flagjuzhongnum]));
                              //qDebug()<<"flagdaoche FFFFFFFFFFFF.....?????? == "<<numdaoche<<endl;
                          }
                          else if((flagdaoche == true)&&(numdaoche == 2))
                           {
                               ui->label_15->setText("");
                               flagdaoche = false;
                                //qDebug()<<"Kongkong FFFFFFFFFFFFFF.....?????? == "<<numdaoche<<endl;
                           }

                      }


                      flagjuzhongnum++;

                      timergzm->stop();
                      timergzmTihuan->start(3000);//2000
                     }
                     else
                     {
                       flagjuzhongnum = 0;
                       //ui->label_17->setText(" ");
                       memset(YouAndTongxinArray,0,200);
                     }
                  }
//                  else if((ecutest.spn_can.if_data == 1))//是否有数据 1表示有数据
//                  {
//                    qDebug()<<"8888888888888888889999999999999 == "<<QString::fromUtf8(YouAndTongxinArray[flagjuzhongnum])<<endl;
//                    ui->label_17->setText(" ");
//                  }

          #endif
       }

    }
}

//闪烁 平滑转动
//平滑转动
void Widget::shanhua()//闪烁和平滑转动
{

#if 1
    //油量 和 滚筒转速

    if((flagmatchion == YZT_10)||(flagmatchion == YZT_5)) //滚筒转速
    {
        nu2 = cantest.m_Speed[SPEED_GUNTONG];
        nu2 /= 100;
        nu2 *= 2;

        if(nu2 > 30)//3000 转
        {
            nu2 = 30;
        }

        if(nu1 < nu2)//
        {
            nu1++;
        }
        else if(nu1 > nu2)//
        {
            nu1--;
        }
    }
    else  //燃油量
    {
        nu2 = cantest.VolYL;
        //qDebug()<<"cantest.VolYL ===============..................+++++++++++++ =    "<<cantest.VolYL<<endl;

        if(nu2 > 8)
        {
            nu2 = 8;
        }

        if(nu1 < nu2)//cantest.FDJ_speed
        {
            nu1++;
        }
        else if(nu1 > nu2)//cantest.FDJ_speed
        {
            nu1--;
        }
    }


    //水温

    //qDebug()<<"1    ecutest.VolSW ----------------------    === "<<ecutest.VolSW<<endl;
    //floatnu2 = (ecutest.VolSW)/10;
    floatnu2 = ecutest.VolSW;


    if(floatnu2 >=120)
    {
        floatnu2 = 80;
    }
    else if((floatnu2 >=40)&&(floatnu2 <120))
    {
        floatnu2 -= 40;
    }
    else if(floatnu2 < 40)
    {
        floatnu2 = 0;
    }


    //转速
    floatnu1 = ecutest.FDJ_speed;
    floatnu1 = floatnu1/100;
    if(floatnu1 >30)
    {
        floatnu1 = 30;
    }


    //机油压力
    JYYL = ecutest.VolJYYL;
    JYYL = JYYL/1000;
    //ui->label_2->setText(QString::number(JYYL,'f',2));

    floatnu3 = JYYL;

    //qDebug()<<"floatnu3........................ =============   "<<floatnu3<<endl;
//    floatnu3 *= 10;

    if(floatnu3 >1)
    {
        floatnu3 = 1;
    }


    //zan 时不用
    nu4 = cantest.HourSpeed;
    if(nu4>30)
    {
        nu4 = 30;
    }
    if(nu4<0)
    {
        nu4 = 0;
    }
    if(nu3 < nu4)//cantest.FDJ_speed
    {
        nu3++;
        //qDebug()<<"3++"<<cantest.FDJ_speed<<endl;
    }
    else if(nu3 > nu4)//cantest.FDJ_speed
    {
        nu3--;

        //qDebug()<<"4------"<<cantest.FDJ_speed<<endl;
    }


    if(flagaddnum)
    {
        //闪烁控制

        if(ecutest.flagECU == 0)
        {
            if(ecutest.VolSW > 100)//水温
            {
                shanshuoSW = 1;
            }

            if(JYYL < 0.08)//机油
            {
                shanshuoJYYL = 1;
            }

            if(cantest.VolYL < 1)//油量
            {
                shanshuoYL = 1;
            }
        }


//        if(cantest.flagTXCS == 0)//cantest.flagTXCS == 1 mcu  故障
//        {
//            if(cantest.VolYL <= 1)//油量
//            {
//                shanshuoYL = 1;
//            }
//        }

        //油中有水
        if(ecutest.flagYSFL_ECU == 1)//油中有水
        {
            shanshuoYZYS = 1;
        }

        //液压油温
        if(cantest.VolYeyayouwen > 90)
        {
            shanshuoYYYW = 1;
        }

        //手刹
        if(cantest.flagSS)
        {
            shanshuoSS = 1;
        }
        //籽粒回收满
        //if(cantest.flagLCM)
        if(CHK_GZ_BIT(cantest.m_extLampBitFlag,LAMP_BIT_ZhiLiHuiShou))
        {
            shanshuoLM = 1;
        }

        //2017.5.18

        if(cantest.SaLiangLV >= 5)
        {
            shanshuoLiangshun = 1;
        }

        //2017.5.22
        //主界面中央灯区

        //过桥故障

        if(CHK_GZ_BIT(cantest.m_GZBitFlag,GZ_BIT_GUOQIAO))
        {
            shanshuoguoqiao = 1;
        }
        //风机故障

        if(CHK_GZ_BIT(cantest.m_GZBitFlag,GZ_BIT_FENGJI))
        {
            shanshuofengji = 1;
        }

        //滚筒故障

        if(CHK_GZ_BIT(cantest.m_GZBitFlag,GZ_BIT_GUNTONG))
        {
            shanshuoGunTong = 1;
        }

        //升运器故障

        if(CHK_GZ_BIT(cantest.m_GZBitFlag,GZ_BIT_SHENGYUNQI))
        {
            shanshuoShengyun = 1;
        }

//        //卸粮中
//        if(CHK_GZ_BIT(cantest.m_extLampBitFlag,LAMP_BIT_XieLiangZhong))
//        {
//            shanshuoLiangchangman2 = 1;
//        }
//        //粮仓盖

//        if(CHK_GZ_BIT(cantest.m_GZBitFlag,GZ_BIT_LIANGCANGGAI))
//        {
//            shanshuoLiangchangman2 = 1;
//        }

        //2017.5.24
        //充电指示灯
        if(cantest.flagBattery == 2)
        {
            shangshuoChongdian = 1;
        }



        //闪烁算法 核心
        flagnum++;
        if(flagnum>15)//30
        {
            flagaddnum = 0;
        }
    }
    else
    {
        shanshuoSW = 0;//水温
        shanshuoJYYL = 0;//机油
        shanshuoYL = 0;//油量
        shanshuoYZYS = 0;// 油中有水

        shanshuoSS = 0;//手刹
        shanshuoLM = 0;//粮满

        //2017.5.18
        shanshuoLiangshun = 0;

        //2017.5.22
        shanshuoGunTong = 0;
        shanshuoShengyun = 0;
        shanshuoguoqiao = 0;
        shanshuofengji = 0;
        //shanshuoLiangchangman2 = 0;


        flagnum--;
        if(flagnum==0)
        {
            flagaddnum = 1;
        }
    }
#endif
}


#if 1
//里程 蜂鸣器
void Widget::Licheng()//里程
{
#if 1

        //if((ecutest.flagECU == 0)&&(ecutest.FDJ_speed>350))


    if(flagwidget == xingZouWidget)
    {

        if((ecutest.flagECU == 0))
        {
            if(((shanshuoSW == 1)||(shanshuoJYYL ==1)||(shanshuoLM == 1)||(shanshuoLiangshun == 1)||(shanshuoGunTong == 1)||(shanshuoShengyun == 1)||(shanshuoguoqiao == 1)||(shanshuofengji == 1)||(shanshuoSS == 1)||(shangshuoChongdian == 1)||(shanshuoYL == 1))&&(ecutest.FDJ_speed>350))//||shanshuoYL||shanshuozlzs||shanshuoftqzs||shanshuosyqzs
            {
                if(flagbeep)
                {
                    beep_on();
                    //qDebug()<<"beef on 00000000000000000000000000000000000000000000000000000000   ======   "<<ecutest.flagECU<<endl;

                }
               // qDebug()<<"beef on 00000000000000000000000000000000000000000000000000000000   ======   "<<ecutest.flagECU<<endl;
//                qDebug()<<"beef on shanshuoJYYL  ==                  ff         == "<<shanshuoJYYL<<endl;

            }
            else if((shanshuoSW != 1)||(shanshuoJYYL !=1)||(shanshuoLM != 1)||(shanshuoLiangshun != 1)||(shanshuoGunTong != 1)||(shanshuoShengyun != 1)||(shanshuoguoqiao != 1)||(shanshuofengji != 1)||(shanshuoSS != 1)||(shangshuoChongdian != 1)||(shanshuoYL != 1))
            {
                if(flagbeepzero == 0)
                {
                    beep_off();
                    //qDebug()<<"beef off 999999999999999999999999999999999999999999999999999999999"<<endl;

                }
               // qDebug()<<"beef off 999999999999999999999999999999999999999999999999999999999"<<endl;
//                //qDebug()<<"shanshuoYL  == "<<shanshuoYL<<endl;
            }
        }
        else if (ecutest.flagECU == 1)//||(ecutest.FDJ_speed < 350))
        {
            beep_off();
        }
#endif

////////////////////////////////////////////////////////////////////////////////////
//发动机转速达到 350时 蜂鸣器报警 。
#if 1

#if 1
       if((ecutest.flagECU == 0))//&&(ecutest.FDJ_speed>350)
        {
                if((shanshuoYL == 1))
                {
                    DelayYLcounter++;
                    if(DelayYLcounter == 60)//60
                    {
                        if(flagbeep)
                        {
                            beep_on();
                            flagbeepzero = 1;
                        }
                        //qDebug()<<"DelayYLcounter  988888888888888888888888888888888888888888888888888== "<<DelayYLcounter<<endl;
                        DelayYLcounter = 0;
                    }
                }
                else if((shanshuoYL != 1)&&(flagbeepzero == 1))
                {
                    Delagbeepoff++;
                    if(Delagbeepoff == 1)
                    {
                    beep_off();
                    flagbeepzero = 0;

                    }
                    //qDebug()<<"offfffffffffffff  == "<<DelayYLcounter<<endl;
                     Delagbeepoff = 0;
                }
        }
#endif

    }//endoff if((flagwidget == xingZouWidget)||(flagwidget == workWidget))
    else
    {
        beep_off();
    }
#endif


}
#endif



//里程 槽函数
//里程 槽函数

#if 0
void Widget::Licheng()//里程
{
        static unsigned char nn = 1;
        QTextCodec::setCodecForTr(QTextCodec::codecForLocale());//汉字显示
        QSqlDatabase db;
        if(QSqlDatabase::contains("qt_sql_default_connection"))
          db = QSqlDatabase::database("qt_sql_default_connection");
        else
          db = QSqlDatabase::addDatabase("QSQLITE");

       db.setDatabaseName("jy.db");
       if (!db.open())
       {
           qDebug()<<"open database failed ---"<<db.lastError().text()<<endl;
       }
       QSqlQuery query;
       #if 0
       bool ok = query.exec("create table fdjgz(spn INTEGER,fmi INTEGER,gzms varchar)");
       if (ok)
       {
           qDebug()<<"ceate table partition success"<<endl;
       }
       else
       {
           qDebug()<<"ceate table partition failed"<<endl;
       }
       #endif

       //query.prepare("INSERT INTO fdjgz (spn, fmi, gzms) VALUES (:spn, :fmi, :gzms)");

       //query.prepare("update fdjgz set fmi = :fmi,gzms = :gzms where spn = :spn ");//
       query.prepare("UPDATE fdjgz SET fmi = :fmi,gzms = :gzms where spn = :spn ");//
       //query.prepare("UPDATE fdjgz SET fmi = :fmi where spn = :spn ");//,gzms = :gzms
       query.bindValue(":spn",66);
       query.bindValue(":fmi", 888);
       query.bindValue(":gzms", QObject::tr("%1").arg(555));

       query.exec();

       query.bindValue(":spn",77);
       query.bindValue(":fmi", 77);
       query.bindValue(":gzms", QObject::tr("%1").arg(77));

       query.exec();


     query.exec("select spn, fmi, gzms from fdjgz");
     while (query.next())
     {

        qDebug()<<"id("<<query.value(0).toInt()<<")  name:"<<query.value(1).toString()<<"  age:"<<query.value(2).toInt();
        spnItem[un] = query.value(0).toInt();
        fmiItem[un] = query.value(1).toInt();
        gzmItem[un] = query.value(2).toString();

        ui->tableWidget->setItem(un,0,new QTableWidgetItem(QString::number(spnItem[un])));
        //ui->tableWidget->setItem(un,1,new QTableWidgetItem(QString::number(fmiItem[un])));
        ui->tableWidget->setItem(un,1,new QTableWidgetItem(gzmItem[un]));

        un++;
        if(un>=10)
        {
            un = 0;
        }
     }

      query.exec(QObject::tr("drop fdjgz"));
}
#endif

#if 0
void Widget::Licheng()//里程
{
    //static unsigned char nn = 1;  otheritem
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());//汉字显示
    QSqlDatabase db;
    if(QSqlDatabase::contains("qt_sql_default_connection"))
      db = QSqlDatabase::database("qt_sql_default_connection");
    else
      db = QSqlDatabase::addDatabase("QSQLITE");

   db.setDatabaseName("jy.db");
   if (!db.open())
   {
       qDebug()<<"open database failed ---"<<db.lastError().text()<<endl;
   }
   QSqlQuery query;
   #if 1
   bool ok = query.exec("create table otherflag(item1 INTEGER,item2 INTEGER,item3 INTEGER)");
   if (ok)
   {
       qDebug()<<"ceate table partition success"<<endl;
   }
   else
   {
       qDebug()<<"ceate table partition failed"<<endl;
   }
   #endif

   query.prepare("INSERT INTO otherflag(item1, item2, item3) VALUES (:item1, :item2, :item3)");
   //query.prepare("update config set cjswitch = :cjswitch,engineswitch = :engineswitch,langswitch = :langswitch");//where

   query.bindValue(":item1",22);
   query.bindValue(":item2", 11);
   query.bindValue(":item3", 66);

   query.exec();


 query.exec("select item1, item2, item3 from otherflag");
 while (query.next())
 {
    qDebug()<<"item1("<<query.value(0).toInt()<<")  item2:"<<query.value(1).toString()<<"  item2:"<<query.value(2).toInt();
 }

  query.exec(QObject::tr("drop config"));

}
#endif

//里程 槽函数
 #if 0
void Widget::Licheng()//语言，发动机厂家，机器型号
{

        static unsigned char nn = 1;
        QTextCodec::setCodecForTr(QTextCodec::codecForLocale());//汉字显示
        QSqlDatabase db;
        if(QSqlDatabase::contains("qt_sql_default_connection"))
          db = QSqlDatabase::database("qt_sql_default_connection");
        else
          db = QSqlDatabase::addDatabase("QSQLITE");

       db.setDatabaseName("jy.db");
       if (!db.open())
       {
           qDebug()<<"open database failed ---"<<db.lastError().text()<<endl;
       }
       QSqlQuery query;
       #if 0
       bool ok = query.exec("create table config(cjswitch INTEGER,engineswitch INTEGER,langswitch INTEGER)");
       if (ok)
       {
           qDebug()<<"ceate table partition success"<<endl;
       }
       else
       {
           qDebug()<<"ceate table partition failed"<<endl;
       }
       #endif

       //query.prepare("INSERT INTO config(cjswitch, engineswitch, langswitch) VALUES (:cjswitch, :engineswitch, :langswitch)");
       query.prepare("update config set cjswitch = :cjswitch,engineswitch = :engineswitch,langswitch = :langswitch");//where

       query.bindValue(":cjswitch",22);
       query.bindValue(":engineswitch", 11);
       query.bindValue(":langswitch", 66);

       query.exec();


     query.exec("select cjswitch, engineswitch, langswitch from config");
     while (query.next())
     {

        qDebug()<<"id("<<query.value(0).toInt()<<")  name:"<<query.value(1).toString()<<"  age:"<<query.value(2).toInt();
        spnItem[un] = query.value(0).toInt();
        fmiItem[un] = query.value(1).toInt();
        gzmItem[un] = query.value(2).toString();

        ui->tableWidget->setItem(un,0,new QTableWidgetItem(QString::number(spnItem[un])));
        //ui->tableWidget->setItem(un,1,new QTableWidgetItem(QString::number(fmiItem[un])));
        ui->tableWidget->setItem(un,1,new QTableWidgetItem(gzmItem[un]));

        un++;
        if(un>=10)
        {
            un = 0;
        }
     }

      query.exec(QObject::tr("drop config"));


}
 #endif





//小时计 槽函数
void Widget::xiaoshiji()//小时计
{

#if 0
    //2017.5.15 因新研股份辣椒机读取小时计是从ECU 内部读取，暂时先这样。
    if((flagmatchion == YZT_10)||(flagmatchion == YZT_5)||(flagmatchion == JZ_3600))
    {
        xiaoshijiLongLong = ecutest.m_EcuWorkTime;
        xiaoshijiLongLong *= 10;
        xiaoshijiDouble = xiaoshijiLongLong;
        xiaoshijiDouble /= 10;
         ui->label_7->setText(QString::number(xiaoshijiDouble,'f',1));
    }
    else
    {
         //机油温度
         ui->label_7->setText(QString::number(ecutest.VolJYWD));

    }
#endif

#if 1
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());//汉字显示
    QSqlDatabase db;
    if(QSqlDatabase::contains("qt_sql_default_connection"))
      db = QSqlDatabase::database("qt_sql_default_connection");
    else
      db = QSqlDatabase::addDatabase("QSQLITE");


   //QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
   db.setDatabaseName("jy.db");
   if (!db.open())
   {
       qDebug()<<"open database failed ---"<<db.lastError().text()<<"/n";
   }
   QSqlQuery query;
   #if 0
   bool ok = query.exec("create table xsj(id INTEGER,name varchar,age INTEGER)");
   if (ok)
   {
       qDebug()<<"ceate table partition success"<<endl;
   }
   else
   {
       qDebug()<<"ceate table partition failed"<<endl;
   }
   #endif

   query.exec("select id, name, age from xsj");
   while (query.next())
   {

     // qDebug()<<"id("<<query.value(0).toInt()<<")  name:"<<query.value(1).toString()<<"  age:"<<query.value(2).toInt();
     //xiaoshiJi_m = query.value(2).toInt();

       xiaoshiJi_m = query.value(2).toLongLong();

   }



   if(ecutest.FDJ_speed>350)
    {
         xiaoshiJi_m++;
    }

    /*测试*/
   //xiaoshiJi_m++;
   xiaoshiJi_h = (xiaoshiJi_m/3600)*1000 + ((xiaoshiJi_m%3600)*1000)/3600;
   xiaoshiJi_h /= 1000;

   if((flagmatchion == YZT_10)||(flagmatchion == YZT_5)||(flagmatchion == JZ_3600))
   {
        ui->label_7->setText(QString::number(xiaoshiJi_h,'f',1));
        //qDebug()<<"1111111111111111111111111111111111111111"<<endl;
   }
   else
   {
        //ui->label_10->setText(QString::number(xiaoshiJi_h,'f',1));

        //机油温度
        ui->label_7->setText(QString::number(ecutest.VolJYWD));

   }

   query.prepare("update xsj set age = :age where id = :id");

   //query.prepare(update_sql);
   query.bindValue(":id",1);
  // query.bindValue(":name", QObject::tr("小时计"));
   query.bindValue(":age", xiaoshiJi_m);
   query.exec();

 query.exec("select id, name, age from xsj");
 while (query.next())
 {

    //qDebug()<<"id("<<query.value(0).toInt()<<")  name:"<<query.value(1).toString()<<"  age:"<<query.value(2).toInt();
 }
 query.exec(QObject::tr("drop xsj"));

#endif

#if 0
  if(ecutest.FDJ_speed>350)
   {
        xiaoshiJi_m++;
   }
    xiaoshiJi_h = (xiaoshiJi_m/3600)*1000 + ((xiaoshiJi_m%3600)*1000)/3600;
    xiaoshiJi_h /= 1000;

    if(flagwidget == xingZouWidget)
    {
        ui->label_33->setText(QString::number(xiaoshiJi_h,'f',1));
    }
    else if(flagwidget == workWidget)
    {
        ui->label_7->setText(QString::number(xiaoshiJi_h,'f',1));
    }
          //query.prepare("INSERT INTO xsj (id, name, age) VALUES (:id, :name, :age)");

          query.prepare("update xsj set age = :age where id = :id");

          //query.prepare(update_sql);
          query.bindValue(":id",1);
         // query.bindValue(":name", QObject::tr("小时计"));
          query.bindValue(":age", xiaoshiJi_m);
          query.exec();

        query.exec("select id, name, age from xsj");
        while (query.next())
        {

           //qDebug()<<"id("<<query.value(0).toInt()<<")  name:"<<query.value(1).toString()<<"  age:"<<query.value(2).toInt();
        }

        query.exec(QObject::tr("drop xsj"));

/*******************************************************************/

        if((cantest.ZLspeed != 0)||(cantest.FTspeed != 0) ||(cantest.SYspeed != 0))
        {
            DelayCount++;
            if(DelayCount == 7)
            {
                flagDelay = 1;
            }
        }
        else if((cantest.ZLspeed == 0)&&(cantest.FTspeed == 0)&&(cantest.SYspeed == 0))
        {
            flagDelay = 0;
            DelayCount = 0;
           // qDebug()<<"delay ........                        ...................."<<endl;

        }

#endif
}

//故障码索引

uint Widget::GuzhangmaIndex(long spn, uchar fmi)
{

}

//
uint Widget::GuzhangmaYucaiIndex(long spn, uchar fmi)
{

}

void Widget::myscroll()
{
    //QString 数组
    QString CeshiZM[7] = {"空调压缩机开路","空调压缩机对电源短路","空调压缩机对地短路"};//{,"空气质量流量传感器电压超上限"};
    static int nPos = 0;
    //if (nPos > m_scrollCaptionStr.length())
    if (nPos > CeshiZM[mm].length())
    {
        nPos = 0;
    }
    nPos++;
    ui->label_4->setText(CeshiZM[mm].mid(nPos));
}

//时间设置
void Widget::on_dateTimeEdit_dateTimeChanged(const QDateTime &date)
{
    MyDatetimeSetup =date;// QDateTime::currentDateTime();
    dateBuffer = MyDatetimeSetup.toString("yyyy-MM-dd ");//
    timeBuffer = MyDatetimeSetup.toString("hh:mm:ss");
}

void Widget::gzmTihuanslot()
{
    ui->label_4->setText("");
    ui->label_15->setText("");
    timergzmTihuan->stop();
    timergzm->start();//3000

}


//3秒内无边化函数
void Widget::NoChangeFun()
{
    //2017.5.18
    //ShoubingShijizhi =

//    //手柄
//    SendReqCmdToController(GUI_CMD_CFG_REQ_XinZouJuBing_Data,0);
//    GetRspDataFromController(&biaoding);

//    //拉杆
    //SendReqCmdToController(GUI_CMD_CFG_REQ_XinZouLaGan_Data,0);
//    GetRspDataFromController(&biaoding);


    ShoubingShijizhi = biaoding.m_XinZouJubing[BD_VALUE_RealValue];
    XingzhoubengShijizhi = biaoding.m_XinZouLaGan[BD_VALUE_RealValue];
    AobanjianxiShijizhi = biaoding.m_AoBanJianXi[BD_VALUE_RealValue];



     shoubingzuixiao =  biaoding.m_XinZouJubing[BD_VALUE_Minimum];
     shoubingzuida = biaoding.m_XinZouJubing[BD_VALUE_Maximum];
     shoubingzhongjian = biaoding.m_XinZouJubing[BD_VALUE_Median];

     xingzhouzuixiao =  biaoding.m_XinZouLaGan[BD_VALUE_Minimum];
     xingzhouzuida = biaoding.m_XinZouLaGan[BD_VALUE_Maximum];
     xingzhouzhongjian = biaoding.m_XinZouLaGan[BD_VALUE_Median];


//    qDebug()<<"ShoubingShijizhi == "<<ShoubingShijizhi<<endl;
//    qDebug()<<"XingzhoubengShijizhi == "<<XingzhoubengShijizhi<<endl;
//    qDebug()<<"AobanjianxiShijizhi == "<<AobanjianxiShijizhi<<endl;


    if(LCPiPeixingBiaoDing == 1)
    {
        FlagAoBanjianxi = 0;

        if((FlagNext == false)&&(FlagShouBing ==1))
        {
            if(ShoubingTempShijizhi == ShoubingShijizhi)
            {
                ThreeOut++;
            }
            else
            {
                ShoubingTempShijizhi = ShoubingShijizhi;
                ThreeOut = 0;
            }
        }
        if(ThreeOut == 3)
        {
            //qDebug()<<"ppppppppppppppppppppppppppppppppppppppppp = "<<LCPiPeixingBiaoDing<<endl;
            //ui->label_16->setText("请推动手柄到最小位置");

            FlagShouBing = 2;
            FlagNext = true;
            ThreeOut = 0;
        }
        else
        {
            //ui->label_16->setText("请推动手柄到最大位置");
        }

        //标定完成
        if((FlagNext == true)&&(FlagShouBing ==2))
        {
            if(ShoubingTempShijizhi == ShoubingShijizhi)
            {
                ThreeOut++;
            }
            else
            {
                ShoubingTempShijizhi = ShoubingShijizhi;
                ThreeOut = 0;
            }
        }
        if(ThreeOut == 3)
        {
            //ui->label_16->setText("手柄标定完成");

            FlagShouBing = 3;
            FlagNext = false;
            ThreeOut = 0;
        }
        //手柄标定完成
        else if(FlagShouBing == 3)
        {
            FlagShouBingBDFinish++;
            if(FlagShouBingBDFinish == 6)
            {
                FlagShouBing =  0;
                FlagShouBingBDFinish = 0;
            }
        }
    }
    else if(LCPiPeixingBiaoDing == 2)//行走泵标定
    {
        //2017.5.24
        FlagShouBing = 0;


        if((FlagNext == false)&&(FlagXingzouBeng == 1))
        {
            if(XingzhoubengTempShijizhi == XingzhoubengShijizhi)
            {
                ThreeOut++;
            }
            else
            {
                XingzhoubengTempShijizhi = XingzhoubengShijizhi;
                ThreeOut = 0;
            }
        }
        if(ThreeOut == 3)
        {
            ui->label_16->setText("行走泵校准中");

            FlagXingzouBeng = 2;
            FlagNext = true;
            ThreeOut = 0;
        }
        else
        {
            //ui->label_16->setText("行走泵校准中");
        }

        //标定完成
        if((FlagNext == true)&&(FlagXingzouBeng == 2))
        {
            if(XingzhoubengTempShijizhi == XingzhoubengShijizhi)
            {
                ThreeOut++;
            }
            else
            {
                XingzhoubengTempShijizhi = XingzhoubengShijizhi;
                ThreeOut = 0;
            }
        }
        if(ThreeOut == 3)
        {
            ui->label_16->setText("行走泵标定完成");

            FlagXingzouBeng = 3;
            FlagNext = false;
            ThreeOut = 0;
        }
        //行走泵标定完成
        else if(FlagXingzouBeng == 3)
        {
            FlagXingzouBengBDFinish++;
            if(FlagXingzouBengBDFinish == 6)
            {
                FlagXingzouBeng =  0;
                FlagXingzouBengBDFinish = 0;
            }
        }
    }
    else if(LCPiPeixingBiaoDing == 3)//凹板间隙
    {

        FlagXingzouBeng = 0;

        if((FlagNext == false)&&(FlagAoBanjianxi == 1))
        {
            if(AobanjianxiTempShijizhi == AobanjianxiShijizhi)
            {
                ThreeOut++;
            }
            else
            {
                AobanjianxiTempShijizhi = AobanjianxiShijizhi;
                ThreeOut = 0;
            }
        }
        if(ThreeOut == 3)
        {
            //ui->label_16->setText("请推动手柄到最小位置");

            FlagAoBanjianxi = 2;
            FlagNext = true;
            ThreeOut = 0;
        }
        else
        {
            //ui->label_16->setText("请推动手柄到最大位置");
        }

        //凹板间隙标定完成
        if((FlagNext == true)&&(FlagAoBanjianxi == 2))
        {
            if(AobanjianxiTempShijizhi == AobanjianxiShijizhi)
            {
                ThreeOut++;
            }
            else
            {
                AobanjianxiTempShijizhi = AobanjianxiShijizhi;
                ThreeOut = 0;
            }
        }
        if(ThreeOut == 3)
        {
           // ui->label_16->setText("凹板间隙标定完成");

            FlagAoBanjianxi = 3;
            FlagNext = false;
            ThreeOut = 0;
        }
        //凹板间隙标定完成
        else if(FlagAoBanjianxi == 3)
        {
            FlagAoBanjianxiBDFinish++;
            if(FlagAoBanjianxiBDFinish == 6)
            {
                FlagAoBanjianxi =  0;
                FlagAoBanjianxiBDFinish = 0;
            }
        }
    }
}




