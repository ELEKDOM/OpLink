// Copyright (C) 2026 ELEKDOM Christophe Mars c.mars@elekdom.fr
// 
// This file is part of PlugFrame.
// 
// PlugFrame is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// PlugFrame is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with PlugFrame. If not, see <https://www.gnu.org/licenses/>.
//
#ifndef OBSERVABLEPUBLISHER_H
#define OBSERVABLEPUBLISHER_H

#include "abstract_publisher/publisher.h"
#include "service-int/loginserviceinterface.h"
#include "service-int/observableserviceinterface.h"

class ObservablePublisher : public plugframe::Publisher
{
public:
    ObservablePublisher();
    ~ObservablePublisher() override;

public:
    plugframe::LoginServiceInterface *loginService();
    oplink::ObservableServiceInterface *observableService();

protected:
    plugframe::BundleFactory* createFactory() override;
    PF_qtServiceInterface_DECL
};

#endif // OBSERVABLEPUBLISHER_H
