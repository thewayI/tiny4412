#include "commandList.h"

S_CMD_LIST gCommandListTbl[CMD_SUPPORT_COUNT] = {
    {CMD_GET_PRESSURE_READING      , QString("#*?")},
    {CMD_SET_ADDR                  , QString("#*A")},
    {CMD_GET_TURNDOWN              , QString("#*B?")},
    {CMD_GET_CALIBRATION_DATE      , QString("#*DC?")},
    {CMD_SET_CALIBRATION_DATE      , QString("#*DC")},
    {CMD_GET_FLITER                , QString("#*FL?")},
    {CMD_SET_FLITER                , QString("#*FL")},
    {CMD_GET_FS_ACCURACY           , QString("#*FS?")},
    {CMD_GET_ID                    , QString("#*ID?")},
    {CMD_GET_MODE                  , QString("#*M?")},
    {CMD_SET_MODE                  , QString("#*M")},
    {CMD_DISABLE_PASSWD            , QString("#*PW")},
    {CMD_GET_MINIMUM               , QString("#*R-?")},
    {CMD_GET_MAXIMUM               , QString("#*R+?")},
    {CMD_SAVE_ALL_DATA             , QString("#*SAVE")},
    {CMD_GET_CORRECTION_MULTIPLIER , QString("#*SC?")},
    {CMD_LOAD_CORRECTION_MULTIPLIER, QString("#*SC")},
    {CMD_SWITCH_CAL                , QString("#*SW")},
    {CMD_GET_CAL_TYPE              , QString("#*T?")},
    {CMD_GET_UNIT_CODE             , QString("#*U?")},
    {CMD_GET_ZERO_CORRECTION       , QString("#*ZC?")},
    {CMD_SET_ZERO_CORRECTION       , QString("#*ZC")},
    {CMD_GET_VOLTAGE_UPPER         , QString("#*V+?")},
    {CMD_GET_VOLTAGE_LOWER         , QString("#*V-?")},
    {CMD_GET_VSC                   , QString("#*VSC?")},
    {CMD_SET_VSC                   , QString("#*VSC")},
    {CMD_GET_VZC                   , QString("#*VZC?")},
    {CMD_SET_VZC                   , QString("#*VZC")}
};

QString getCommandString(unsigned char cmdIdx)
{
    if(gCommandListTbl[cmdIdx].cmdNo == cmdIdx)
        return gCommandListTbl[cmdIdx].cmdInfo;
    else
        return QString("");
}

void sendSerialCommand(Posix_QextSerialPort *pSerial, unsigned char index, QString *result)
{
    QString str;
    if(pSerial != NULL)
    {
        str = getCommandString((unsigned char)(index));
        str.append("\n");
        pSerial->write(str.toAscii());

        QByteArray temp = pSerial->readAll();

#if 0
        while(temp.size() == 0)
        {
            temp = pSerial->readAll();
        }
#endif
        *result = QString(temp);
    }
}

void sendSerialCommandArg(Posix_QextSerialPort *pSerial, unsigned char index, QString arg, QString *result)
{
    QString str;
    str = getCommandString((unsigned char)(index));
    str.append(arg);
    str.append("\n");
    if(pSerial != NULL)
    {
        pSerial->write(str.toAscii());

        QByteArray temp = pSerial->readAll();

#if 0
        while(temp.size() == 0)
        {
            temp = pSerial->readAll();
        }
#endif
        *result = QString(temp);
    }
}


//cpt6100 address default is "1", use set
