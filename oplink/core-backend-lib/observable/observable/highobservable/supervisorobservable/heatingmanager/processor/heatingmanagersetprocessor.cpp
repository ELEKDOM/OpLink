#include "heatingmanagersetprocessor.h"
#include "command/command-names.h"
#include "observable/propertyid.h"
#include "observable/observable/highobservable/supervisorobservable/heatingmanager/heatingmanager.h"
#include "logger/pflog.h"

oplink::HeatingManagerSetProcessor::HeatingManagerSetProcessor(Observable &observable):
    HeatingManagerCmdProcessor{observable,CommandNames::SET}
{

}

oplink::HeatingManagerSetProcessor::~HeatingManagerSetProcessor()
{

}

///
/// \brief oplink::HeatingManagerSetProcessor::process
/// The `set` command allows the change of three properties of a heatingManager
/// run > 'on' or 'off'
/// setpoint > setpoint value
/// tmode > 'ondemand' or 'planned' (only for highobservable with scheduler)
/// planning > string containing the XML definition of the scheduler (only for highobservable with scheduler)
/// \param order
///
void oplink::HeatingManagerSetProcessor::process(QspCommand order)
{
    PropertyName target{order->property()};
    QVariant val{order->value()};
    QString valStr{val.toString()};

    if (PropertyId::P_RUNNING == target)
    {
        if (CommandArgs::ON == valStr)
        {
            manager().setOn();
            pfInfo3(observable().logChannel()) << QObject::tr("Gestionnaire de Chauffage : %1 démarré").arg(order->observable());
        }
        else if (CommandArgs::OFF == valStr)
        {
            manager().setOff();
            pfInfo3(observable().logChannel()) << QObject::tr("Gestionnaire de Chauffage : %1 stoppé").arg(order->observable());
        }
        else
        {
            pfWarning1(observable().logChannel()) << QObject::tr("Gestionnaire de Chauffage : %1 valeur non autorisée pour une commande %2 %3").arg(valStr,order->name(),target);
        }
    }
    else if (manager().isActivated())
    {
        if (PropertyId::P_SETPOINT == target)
        {
            manager().setSetpoint(valStr);
            pfInfo3(observable().logChannel()) << QObject::tr("Gestionnaire de Chauffage : %1 consigne positionnée à %2").arg(order->observable(),valStr);
        }
        else if (PropertyId::P_TRIGGER_MODE == target)
        {
            if (manager().hasPlannedMode())
            {
                if (CommandArgs::TRIGGER_MODE_ONDEMAND == valStr)
                {
                    manager().setOnDemand();
                    pfInfo3(observable().logChannel()) << QObject::tr("Gestionnaire de Chauffage : %1 en mode 'manuel'").arg(order->observable());
                }
                else if (CommandArgs::TRIGGER_MODE_PLANNED == valStr)
                {
                    manager().setPlanned();
                    pfInfo3(observable().logChannel()) << QObject::tr("Gestionnaire de Chauffage : %1 en mode 'planifié'").arg(order->observable());
                }
                else
                {
                    pfWarning1(observable().logChannel()) << QObject::tr("Gestionnaire de Chauffage : %1 valeur non autorisée pour une commande %2 %3").arg(valStr,order->name(),target);
                }
            }
            else
            {
                pfWarning1(observable().logChannel()) << QObject::tr("La commande %1 %2 ne peut s'appliquer que sur des gestionnaire de chauffage avec planificateur").arg(order->name(),target);
            }
        }
        else if (PropertyId::P_SCHEDULER_XML_DEF == target)
        {
            if (manager().hasPlannedMode())
            {
                manager().setSchedulerXmlDef(valStr);
            }
            else
            {
                pfWarning1(observable().logChannel()) << QObject::tr("La commande %1 %2 ne peut s'appliquer que sur des gestionnaire de chauffage avec planificateur").arg(order->name(),target);
            }
        }
        else
        {
            pfWarning1(observable().logChannel()) << QObject::tr("Gestionnaire de Chauffage : la commande %1 ne s'applique pas sur la propriété %2").arg(order->name(),target);
        }
    }//else if (manager().isActivated())
}
