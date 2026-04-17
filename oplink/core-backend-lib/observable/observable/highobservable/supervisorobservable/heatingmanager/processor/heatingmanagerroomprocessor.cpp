#include "heatingmanagerroomprocessor.h"
#include "command/command-names.h"
#include "observable/propertyid.h"
#include "observable/observable/highobservable/supervisorobservable/heatingmanager/heatingmanager.h"
#include "logger/pflog.h"

oplink::HeatingManagerRoomProcessor::HeatingManagerRoomProcessor(Observable &observable):
    HeatingManagerCmdProcessor{observable,CommandNames::ROOM}
{

}

oplink::HeatingManagerRoomProcessor::~HeatingManagerRoomProcessor()
{

}

void oplink::HeatingManagerRoomProcessor::process(QspCommand order)
{
    PropertyName roomTarget{order->property()};
    QVariant val{order->value()};
    QString valStr{val.toString()};
    QString roomName{PropertyId::extractGroupPrefix(roomTarget)};
    QString target{PropertyId::extractPropertyName(roomTarget)};

    if (manager().isActivated())
    {
        if (PropertyId::P_SETPOINT == target)
        {
            manager().setRoomSetpoint(roomName,valStr);
            pfInfo3(observable().logChannel()) << QObject::tr("Gestionnaire de Chauffage : %1 consigne positionnée à %2 pour la pièce %3").arg(order->observable(),valStr,roomName);
        }
        else
        {
            pfWarning1(observable().logChannel()) << QObject::tr("Gestionnaire de Chauffage : la commande %1 ne s'applique pas sur la propriété %2 d'une pièce").arg(order->name(),target);
        }
    }
}
