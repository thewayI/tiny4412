#ifndef COMMANDLIST_H
#define COMMANDLIST_H

#include <QSettings>
#include <QMessageBox>
#include <QProcess>
#include "QString"
#include "commandList.h"
#include "posix_qextserialport.h"
typedef struct cmd_list
{
    unsigned char cmdNo;
    QString cmdInfo;
    unsigned int respCharCnt;

}S_CMD_LIST;

typedef struct unit_change{
    unsigned char code;
    QString unitInfo;
}S_UNIT_CHANGE;

//command list define
#if 1
#define CMD_GET_PRESSURE_READING    0  //#*?
#define CMD_SET_ADDR                1  //#*A n
#define CMD_GET_TURNDOWN            2  //#*B?
#define CMD_GET_CALIBRATION_DATE    3  //#*DC?
#define CMD_SET_CALIBRATION_DATE    4  //#*DC nnnnnn
#define CMD_GET_FLITER              5  //#*FL?
#define CMD_SET_FLITER              6  //#*FL nn
#define CMD_GET_FS_ACCURACY         7  //#*FS?
#define CMD_GET_ID                  8  //#*ID?
#define CMD_GET_MODE                9  //#*M?
#define CMD_SET_MODE                10 //#*M Y
#define CMD_DISABLE_PASSWD          11 //#*PW
#define CMD_GET_MINIMUM             12 //#*R-?
#define CMD_GET_MAXIMUM             13 //#*R+?
#define CMD_SAVE_ALL_DATA           14 //#*SAVE
#define CMD_GET_CORRECTION_MULTIPLIER 15 //#*SC?
#define CMD_LOAD_CORRECTION_MULTIPLIER 16 //#*SC
#define CMD_SWITCH_CAL              17 //#*SW
#define CMD_GET_CAL_TYPE            18 //#*T?
#define CMD_GET_UNIT_CODE           19 //#*U?
#define CMD_GET_ZERO_CORRECTION     20 //#*ZC?
#define CMD_SET_ZERO_CORRECTION     21 //#*ZC
#define CMD_GET_VOLTAGE_UPPER       22 //#*V+?
#define CMD_GET_VOLTAGE_LOWER       23 //#*V-?
#define CMD_GET_VSC                 24 //#*VSC?
#define CMD_SET_VSC                 25 //#*VSC
#define CMD_GET_VZC                 26 //#*VZC?
#define CMD_SET_VZC                 27 //#*VZC

#define RESP_HEADER_LEN             2  //addr + sp
#define RESP_TAIL_LEN               2  //<cr><lf>
#define RESP_READY_LEN              1  //R

//#*?
#define RESP_PRESSURE_LEN           9  //pressure read
//#*B?
#define RESP_TURNDOWN_NUM_LEN       2  //B<sp>
#define RESP_TURNDOWN_RESUT_LEN     1  //NUM
//#*DC?
#define RESP_CALIBRATION_DATE_LEN   3  //DC<sp>
#define RESP_CALIBRATION_DATE_RESULT_LEN 6 //date
//#*FL?
//#define RESP_


#else
#define CMD_OUTPUT_FORMAT           0  //#*?
#define CMD_CHAN_A_READING_PRESSURE 1  //#*A?
#define CMD_CHAN_A_RATE             2  //#*AR?
#define CMD_ACQUIRE                 3  //#*Acquire?
#define CMD_SET_ADDRESS             4  //#*Address
#define CMD_GET_ADDRESS             5  //#*Address?
#define CMD_SET_ASSET_TAG           6  //#*Asset_tag
#define CMD_GET_ASSET_TAG           7  //#*Asset_tag?
#define CMD_CHAN_B_READING_PRESSURE 8  //#*B?
#define CMD_CHAN_B_RATE             9  //#*BR?
#define CMD_BARO                    10 //#*Baro?
#define CMD_CHAN_C_READING_PRESSURE 11 //#*C?
#define CMD_CHAN_C_RATE             12 //#*CR?
#define CMD_CALCULATE_AS_FOUNT_LINEARITY 13 //#*Calculate_as_found_linearity
#define CMD_SET_CALDISABLE          14 //#*CaldisableYES/#*CaldisableNO
#define CMD_GET_CALDISABLE          15 //#*Caldisable?
#define CMD_CERR                    16 //#*Cerr
#define CMD_SET_CHAN                17 //#*ChanA/#*ChanB/#*ChanC/#*ChanD
#define CMD_GET_CHAN                18 //#*Chan?
#define CMD_SET_CHAN_FUNC           19 //#*Chanfunc...
#define CMD_GET_CHAN_FUNC           20 //#*Chanfunc<n>
#define CMD_GET_CMD                 21 //#*CmdsetMensor/#*CmdsetSCPI
#define CMD_GET_CMD                 22 //#*Cmdset?
#define CMD_CHAN_D_READING_PRESSURE 23 //#*D?
#define CMD_CHAN_D_RATE             24 //#*DR?
#define CMD_DEFAULT                 25 //#*Default
#define CMD_SET_DELTAFUNC           26 //#*Deltafunc
#define CMD_GET_DELTAFUNC           27 //#*Deltafunc?
#define CMD_SET_DHCP                28 //#*DHCP
#define CMD_GET_DHCP                29 //#*DHCP?
#define CMD_SET_DOC                 30 //#*DOC
#define CMD_GET_DOC                 31 //#*DOC?
#define CMD_GET_DOM                 32 //#*DOM?
#define CMD_GET_ERROR               33 //#*Error?
#define CMD_SET_FILTER              34 //#*Filter
#define CMD_GET_FILTER              35 //#*Filter?
#define CMD_SET_GASDENSITY          36 //#*Gasdensity
#define CMD_GET_GASDENSITY          37 //#*Gasdensity?
#define CMD_SET_GASTEMP             38 //#*Gastemp
#define CMD_GET_GASTEMP             39 //#*Gastemp?
#define CMD_SET_GATEWAY             40 //#*Gateway
#define CMD_GET_GATEWAY             41 //#*Gateway?
#define CMD_SET_HEIGHT              42 //#*Height
#define CMD_GET_GEIGHT              43 //#*Height?
#define CMD_GET_LD                  44 //#*ld?
#define CMD_SET_IP                  45 //#*IP
#define CMD_GET_IP                  46 //#*IP?
#define CMD_KEYLOCK                 47 //#*KeylockYES/#*KeylockNO
#define CMD_GET_LIST                48 //#*List?
#define CMD_GET_LISTCAL             49 //#*Listcal?
#define CMD_GET_LISTRANGE           50 //#*Listrange?
#define CMD_SET_LOCALGRAVITY        51 //#*Localgravity
#define CMD_GET_LOCALGRAVITY        52 //#*Localgravity?
#define CMD_SET_NETMASK             53 //#*Netmask
#define CMD_GET_NETMASK             54 //#*Netmask?
#define CMD_SET_OUTFORM             55 //#*Outform
#define CMD_GET_OUTFORM             56 //#*Outform?
#define CMD_GET_PEAKMAX             57 //#*Peakmax?
#define CMD_GET_PEALMIN             58 //#*Peakmin?
#define CMD_PEAK_RESET              59 //#*Peakreset
#define CMD_SET_PORT                60 //#*Port
#define CMD_GET_PORT                61 //#*Port?
#define CMD_SET_PTYPE               62 //#*Ptype
#define CMD_GET_PTYPE               63 //#*Ptype?
#define CMD_GET_RANGEMAX            64 //#*RangeMax?
#define CMD_GET_RANGEMIN            65 //#*RangeMin?
#define CMD_GET_RATE                66 //#*Rate?
#define CMD_GET_RDECPT              67 //#*Rdecpt?
#endif

#define CMD_SUPPORT_COUNT           30
#define RECV_RESP_TIMEOUT           30000

#define CHAN_A_PEAK_CHECK           (0x1 << 0)
#define CHAN_A_RATE_CHECK           (0x1 << 1)
#define CHAN_A_ADJUST_ZERO_PEAK     (0x1 << 2)
#define CHAN_A_PRESSURE_PEAK        (0x1 << 3)
#define CHAN_B_PEAK_CHECK           (0x1 << 4)
#define CHAN_B_RATE_CHECK           (0x1 << 5)
#define CHAN_B_ADJUST_ZERO_PEAK     (0x1 << 6)
#define CHAN_B_PRESSURE_PEAK        (0x1 << 7)

extern u_int32_t g32styleMode;
extern bool      g8ConnectFlag;
extern u_int8_t  g8checkSts;
extern u_int8_t g8Accuracy;
extern u_int8_t g8ConfigStyle;

extern S_UNIT_CHANGE gUnitChange[40];
extern S_CMD_LIST gCommandListTbl[CMD_SUPPORT_COUNT];
extern QString getCommandString(unsigned char cmdIdx);
extern unsigned int getResponseCharCnt(unsigned char cmdIdx);
extern QString sendSerialMessage(Posix_QextSerialPort *pSerial, QString cmd);
extern void sendSerialCommand(Posix_QextSerialPort *pSerial, unsigned char index, QString *result);
extern void sendSerialCommandArg(Posix_QextSerialPort *pSerial, unsigned char index, QString arg, QString *result);
#endif // COMMANDLIST_H

