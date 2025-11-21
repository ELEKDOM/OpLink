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

#include <QSharedPointer>
#include <QObject>
#include "observablesubscriber.h"
#include "observable/observablenames.h"

namespace oplink
{
class ObservableNotifier : public QObject
{
    Q_OBJECT

public:
    ObservableNotifier(QObject *parent = nullptr);
    ~ObservableNotifier() override;

signals:

    void stateChange(oplink::ObservableName observableName,
                     oplink::PropertyName propertyName,
                     QVariant propertyValue);

public:
    bool subscribe(ObservableSubscriber *subscriber);
    bool unsubscribe(ObservableSubscriber *subscriber);
    void notifyPropertyValueChange(ObservableName observableName,
                                   PropertyName propertyName,
                                   QVariant propertyValue);
};
using QspObservableNotifier = QSharedPointer<ObservableNotifier>;
}//namespace oplink
#endif // OBSERVABLENOTIFIER_H
