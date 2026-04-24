#ifndef HEATINGMANAGERMODELNAMES_H
#define HEATINGMANAGERMODELNAMES_H

#include <QString>
#include "olcore-lib_export.h"

namespace oplink
{
class OLCORE_LIB_EXPORT HeatingManagerModelNames
{
public:
    static QString pilotWireModelName() {return QStringLiteral("heating_manager_pilotwire");}
    static QString pilotWireThermostatModelName() {return QStringLiteral("heating_manager_pilotwire_thermostat");}
};
}//namespace oplink
#endif // HEATINGMANAGERMODELNAMES_H
