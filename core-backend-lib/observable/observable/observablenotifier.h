// Copyright (C) 2025 ELEKDOM Christophe Mars c.mars@elekdom.fr
// 
// This file is part of OpLink.
// 
// OpLink is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// OpLink is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with PlugFrame. If not, see <https://www.gnu.org/licenses/>.
//


#ifndef OBSERVABLENOTIFIER_H
#define OBSERVABLENOTIFIER_H

#include <QObject>
#include "observablesubscriber.h"
#include "observable/observablenames.h"

namespace elekdom
{
namespace oplink
{
namespace core
{
namespace observable
{

class ObservableNotifier : public QObject
{
    Q_OBJECT

public:
    ObservableNotifier(QObject *parent = nullptr);
    ~ObservableNotifier() override;

signals:

    void stateChange(const elekdom::oplink::core::observable::ObservableName& observableName,
                     const elekdom::oplink::core::observable::PropertyName& propertyName,
                     QVariant propertyValue);

public:
    bool subscribe(ObservableSubscriber *subscriber);
    bool unsubscribe(ObservableSubscriber *subscriber);
    void notifyPropertyValueChange(const ObservableName& observableName,
                                   const PropertyName& propertyName,
                                   QVariant propertyValue);
};

}//namespace observable
}//namespace core
}//namespace oplink
}//namespace elekdom

#endif // OBSERVABLENOTIFIER_H
