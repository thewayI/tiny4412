#include "commandList.h"

S_CMD_LIST gCommandListTbl[CMD_SUPPORT_COUNT] = {
    {CMD_GET_PRESSURE_READING      , QString("#*?"),    10},
    {CMD_SET_ADDR                  , QString("#*A"),     1},
    {CMD_GET_TURNDOWN              , QString("#*B?"),    7},
    {CMD_GET_CALIBRATION_DATE      , QString("#*DC?"),  13},
    {CMD_SET_CALIBRATION_DATE      , QString("#*DC"),    1},
    {CMD_GET_FLITER                , QString("#*FL?"),   9},
    {CMD_SET_FLITER                , QString("#*FL"),    1},
    {CMD_GET_FS_ACCURACY           , QString("#*FS?"),  10},
    {CMD_GET_ID                    , QString("#*ID?"),  40},
    {CMD_GET_MODE                  , QString("#*M?"),    5},
    {CMD_SET_MODE                  , QString("#*M"),     1},
    {CMD_DISABLE_PASSWD            , QString("#*CALU\n"),    1},
    {CMD_GET_MINIMUM               , QString("#*R-?"),  14},
    {CMD_GET_MAXIMUM               , QString("#*R+?"),  14},
    {CMD_SAVE_ALL_DATA             , QString("#*SAVE\n"),  1},
    {CMD_GET_CORRECTION_MULTIPLIER , QString("#*SC?"),   14},
    {CMD_LOAD_CORRECTION_MULTIPLIER, QString("#*SC"),    1},
    {CMD_SWITCH_CAL                , QString("#*SW\n1\r"),    1},
    {CMD_GET_CAL_TYPE              , QString("#*T?"),    5},
    {CMD_GET_UNIT_CODE             , QString("#*U?"),    5},
    {CMD_GET_ZERO_CORRECTION       , QString("#*ZC?"),  13},
    {CMD_SET_ZERO_CORRECTION       , QString("#*ZC"),    1},
    //{CMD_GET_VOLTAGE_UPPER         , QString("#*V+?"),   6},
    //{CMD_GET_VOLTAGE_LOWER         , QString("#*V-?"),   6},
    //{CMD_GET_VSC                   , QString("#*VSC?"),  7},
    //{CMD_SET_VSC                   , QString("#*VSC"),   1},
    //{CMD_GET_VZC                   , QString("#*VZC?"),  8},
    //{CMD_SET_VZC                   , QString("#*VZC"),   1}
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
    u_int32_t loop = 0;
    for(loop = 0; loop < 40; loop++)
    {
        if(gCommandListTbl[loop].cmdNo == cmdIdx)
            return gCommandListTbl[loop].cmdInfo;
    }
    return QString("");
}

unsigned int getResponseCharCnt(unsigned char cmdIdx)
{
    u_int32_t loop = 0;
    for(loop = 0; loop < 40; loop++)
    {
        if(gCommandListTbl[loop].cmdNo == cmdIdx)
            return gCommandListTbl[loop].respCharCnt;
    }
    return 0;
}
#define __DEBUG__

QString sendSerialMessage(Posix_QextSerialPort *pSerial, QString cmd)
{
    QString str;
    QString strTemp = QString("");
    u_int32_t timeout = 0;
    QByteArray temp;

    if(pSerial != NULL)
    {
        pSerial->write(cmd.toAscii());

        str = QString("");
        timeout = 0;
        while(1)
        {
            if(strTemp.right(2) != QString("\r\n"))
            {
                temp = pSerial->readAll();
                str = QString(temp);
                strTemp.append(str);

                if((strTemp.left(1) == strTemp.right(1)) && (strTemp.left(1) == QString("R")))
                {
                    break;
                }
            }
            else
            {
                break;
            }

            timeout++;

            if(timeout >= RECV_RESP_TIMEOUT)
            {
                break;
            }
        }
    }

    return strTemp;
}


void sendSerialCommand(Posix_QextSerialPort *pSerial, unsigned char index, QString *result)
{
    QString str;
    QString strTemp = QString("");
    u_int32_t timeout = 0;
    (*result) = QString("");
    if(pSerial != NULL)
    {
        str = getCommandString((unsigned char)(index));
        if(str.size() != 0)
        {
            str.append("\r");
            pSerial->write(str.toAscii());
#ifdef __DEBUG__
            if(index != CMD_GET_PRESSURE_READING)
                qDebug("%s", qPrintable( str ));
#endif
            QByteArray temp;
            str = QString("");
            timeout = 0;
            while(1)
            {
#if 0
                if(pSerial->bytesAvailable() >= getResponseCharCnt((unsigned char)(index)))
                {
                    temp = pSerial->readAll();
                    break;
                }
#endif
                if(strTemp.right(2) != QString("\r\n"))
                {
                    temp = pSerial->readAll();
                    str = QString(temp);
#ifdef __DEBUG__
                    if(index != CMD_GET_PRESSURE_READING)
                        if(str.size() != 0)
                            qDebug("%s", qPrintable( str ));
#endif
                    strTemp.append(str);

                    if((strTemp.left(1) == strTemp.right(1)) && (strTemp.left(1) == QString("R")))
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }

#if 1
                timeout++;

                if(timeout >= RECV_RESP_TIMEOUT)
                {
                    break;
                }
#endif
            }
            *result = strTemp;
        }
        else
        {
            *result = QString("");
        }
    }
    else
    {
        *result = QString("");
    }
}

void sendSerialCommandArg(Posix_QextSerialPort *pSerial, unsigned char index, QString arg, QString *result)
{
    QString str;
    QString strTemp = QString("");
    u_int32_t timeout = 0;

    if(pSerial != NULL)
    {
        str = getCommandString((unsigned char)(index));
        if(str.size() != 0)
        {
            if(index != CMD_SWITCH_CAL)
            {
                str.append(QString(" "));
                str.append(arg);
                str.append("\r");
            }
            else
            {
                str.append(QString("\r"));
                str.append(arg);
                str.append("\n");
            }
            pSerial->write(str.toAscii());
#ifdef __DEBUG__
            if(index != CMD_GET_PRESSURE_READING)
                qDebug("%s", qPrintable( str ));
#endif
            QByteArray temp;

            timeout = 0;
            while(1)
            {
#if 0
                if(pSerial->bytesAvailable() >= getResponseCharCnt((unsigned char)(index)))
                {
                    temp = pSerial->readAll();
                    break;
                }
#else
                if(strTemp.right(2) != QString("\r\n"))
                {
                    temp = pSerial->readAll();
                    str = QString(temp);
#ifdef __DEBUG__
                    if(index != CMD_GET_PRESSURE_READING)
                        if(str.size() != 0)
                            qDebug("%s", qPrintable( str ));
#endif
                    strTemp.append(str);
                    if((strTemp.left(1) == strTemp.right(1)) && (strTemp.left(1) == QString("R")))
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
#endif

                timeout++;

                if(timeout >= RECV_RESP_TIMEOUT)
                {
                    break;
                }

            }
            *result = strTemp;
        }
    }
    else
    {
        *result = QString("");
    }
}
