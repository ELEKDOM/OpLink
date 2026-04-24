#ifndef BUTTONCMDNAME_H
#define BUTTONCMDNAME_H

#include <QString>

class ButtonCmdName
{
public:

    static QString on() {return QStringLiteral("on");}
    static QString off() {return QStringLiteral("off");}
    static QString power() {return QStringLiteral("power");}
    static QString energy() {return QStringLiteral("energy");}
    static QString comfort() {return QStringLiteral("comfort");}
    static QString comfort1() {return QStringLiteral("comfort1");}
    static QString comfort2() {return QStringLiteral("comfort2");}
    static QString eco() {return QStringLiteral("eco");}
    static QString nofrost() {return QStringLiteral("nofrost");}

    // for heating manager
    static QString managerOnOff() {return QStringLiteral("manageronoff");}
    static QString managerOn() {return QStringLiteral("manageron");}
    static QString managerOff() {return QStringLiteral("manageroff");}
    static QString triggerPlannedMode() {return QStringLiteral("triggerplannedmode");}
    static QString plannedMode() {return QStringLiteral("plannedmode");}
    static QString onDemandMode() {return QStringLiteral("ondemandmode");}
};

#endif // BUTTONCMDNAME_H
