#include "commandList.h"

S_CMD_LIST gCommandListTbl[CMD_SUPPORT_COUNT] = {
    {CMD_GET_PRESSURE_READING      , QString("#*?"),    10},
    {CMD_SET_ADDR                  , QString("#*A"),     1},
    {CMD_GET_TURNDOWN              , QString("#*B?"),    5},
    {CMD_GET_CALIBRATION_DATE      , QString("#*DC?"),  11},
    {CMD_SET_CALIBRATION_DATE      , QString("#*DC"),    1},
    {CMD_GET_FLITER                , QString("#*FL?"),   7},
    {CMD_SET_FLITER                , QString("#*FL"),    1},
    {CMD_GET_FS_ACCURACY           , QString("#*FS?"),  10},
    {CMD_GET_ID                    , QString("#*ID?"),  39},
    {CMD_GET_MODE                  , QString("#*M?"),    5},
    {CMD_SET_MODE                  , QString("#*M"),     1},
    {CMD_DISABLE_PASSWD            , QString("#*PW"),    1},
    {CMD_GET_MINIMUM               , QString("#*R-?"),  14},
    {CMD_GET_MAXIMUM               , QString("#*R+?"),  14},
    {CMD_SAVE_ALL_DATA             , QString("#*SAVE"),  1},
    {CMD_GET_CORRECTION_MULTIPLIER , QString("#*SC?"),   8},
    {CMD_LOAD_CORRECTION_MULTIPLIER, QString("#*SC"),    1},
    {CMD_SWITCH_CAL                , QString("#*SW"),    1},
    {CMD_GET_CAL_TYPE              , QString("#*T?"),    5},
    {CMD_GET_UNIT_CODE             , QString("#*U?"),    3},
    {CMD_GET_ZERO_CORRECTION       , QString("#*ZC?"),  13},
    {CMD_SET_ZERO_CORRECTION       , QString("#*ZC"),    1},
    {CMD_GET_VOLTAGE_UPPER         , QString("#*V+?"),   6},
    {CMD_GET_VOLTAGE_LOWER         , QString("#*V-?"),   6},
    {CMD_GET_VSC                   , QString("#*VSC?"),  7},
    {CMD_SET_VSC                   , QString("#*VSC"),   1},
    {CMD_GET_VZC                   , QString("#*VZC?"),  8},
    {CMD_SET_VZC                   , QString("#*VZC"),   1}
};

S_UNIT_CHANGE gUnitChange[] = {
    {1, QString("psi")},
    {2, QString("inHg@0°C")},
    {3, QString("inHg@60°F")},
    {4, QString("inH2O@4°C")},
    {5, QString("inH2O@20°C")},
    {6, QString("inH2O@60°F")},
    {7, QString("ftH2O@4°C")},
    {8, QString("ftH2O@20°C")},
    {9, QString("ftH2O@60°F")},
    {10,QString("mtorr (@0°C)")},
    {11,QString("inSW @ 0°C ")},
    {12,QString("ftSW @ 0°C")},
    {13,QString("atm")},
    {14,QString("Bars")},
    {15,QString("mBars")},
    {16,QString("mmH2O@4°C")},
    {17,QString("cmH2O@4°C")},
    {18,QString("mH2O@4°C")},
    {19,QString("mmHg@0°C")},
    {20,QString("cmHg@0°C")},
    {21,QString("Torr")},
    {22,QString("Kpa")},
    {23,QString("Pa")},
    {24,QString("Dynes/cm2")},
    {25,QString("g/cm2")},
    {26,QString("kg/cm2")},
    {27,QString("mSW @ 0°C")},
    {28,QString("oz/in2")},
    {29,QString("psf")},
    {30,QString("tsf")},
    {31,QString("% Full Scale")},
    {32,QString("microns Hg @ 0°C")},
    {33,QString("tsi")},
    {35,QString("HPa")},
    {36,QString("MPa")},
};

QString getCommandString(unsigned char cmdIdx)
{
    if(gCommandListTbl[cmdIdx].cmdNo == cmdIdx)
        return gCommandListTbl[cmdIdx].cmdInfo;
    else
        return QString("");
}

unsigned int getResponseCharCnt(unsigned char cmdIdx)
{
    if(gCommandListTbl[cmdIdx].cmdNo == cmdIdx)
        return gCommandListTbl[cmdIdx].respCharCnt;
    else
        return 0;
}

void sendSerialCommand(Posix_QextSerialPort *pSerial, unsigned char index, QString *result)
{
    QString str;
    u_int32_t timeout = 0;
    if(pSerial != NULL)
    {
        str = getCommandString((unsigned char)(index));
        //str.append("\n");
        pSerial->write(str.toAscii());

        QByteArray temp = pSerial->readAll();

        timeout = 0;
        while(1)
        {
            if(pSerial->bytesAvailable() >= getResponseCharCnt((unsigned char)(index)))
            {
                temp = pSerial->readAll();
                break;
            }
#if 0
            else
            {
                timeout++;
            }
            if(timeout >= RECV_RESP_TIMEOUT)
            {
                break;
            }
#endif
        }
        *result = QString(temp);
    }
}

void sendSerialCommandArg(Posix_QextSerialPort *pSerial, unsigned char index, QString arg, QString *result)
{
    QString str;
    u_int32_t timeout = 0;
    str = getCommandString((unsigned char)(index));
    str.append(arg);
    //str.append("\n");
    if(pSerial != NULL)
    {
        pSerial->write(str.toAscii());

        QByteArray temp = pSerial->readAll();

        timeout = 0;
        while(1)
        {
            if(pSerial->bytesAvailable() >= getResponseCharCnt((unsigned char)(index)))
            {
                temp = pSerial->readAll();
                break;
            }
#if 0
            else
            {
                timeout++;
            }
            if(timeout >= RECV_RESP_TIMEOUT)
            {
                break;
            }
#endif
        }
        *result = QString(temp);
    }
}


//cpt6100 address default is "1", use set
