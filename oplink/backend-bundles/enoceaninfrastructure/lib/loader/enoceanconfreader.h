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

#ifndef ENOCEANCONFREADER_H
#define ENOCEANCONFREADER_H

#include "abstract_infrastructure/loading/infrastructureconfreader.h"

class EnoceanConfReader : public oplink::InfrastructureConfReader
{
protected:
    inline QString usbStickNode() { return QStringLiteral("usb-stick"); }
    inline QString baudrateAttribute() { return QStringLiteral("baudrate"); }
    inline QString databitsAttribute() { return QStringLiteral("databits"); }
    inline QString stopbitsAttribute() { return QStringLiteral("stopbits"); }
    inline QString parityAttribute() { return QStringLiteral("parity"); }
    inline QString devAttribute() { return QStringLiteral("dev"); }
    inline QString tcpStickNode() { return QStringLiteral("tcp-stick"); }
    inline QString addressAttribute() { return QStringLiteral("address"); }
    inline QString portAttribute() { return QStringLiteral("port"); }

public:
    EnoceanConfReader(const QString& logChannel,
                      oplink::InfrastructureStore& store,
                      plugframe::WorkerSignal *wSignal,
                      const plugframe::QspWorkerArgs& args,
                      QObject *parent = nullptr);
    ~EnoceanConfReader() override;

protected:
    void extractDataFromGateway(oplink::LoadingError& err) override;
};
#endif // ENOCEANCONFREADER_H
