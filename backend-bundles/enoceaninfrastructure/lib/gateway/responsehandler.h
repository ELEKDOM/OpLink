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

#ifndef RESPONSEHANDLER_H
#define RESPONSEHANDLER_H

#include <QObject>
#include "enoceaninfrastructure_forward.h"

class ResponseHandler : public QObject
{
    Q_OBJECT

public:
    ResponseHandler(QObject *parent = nullptr);
    virtual ~ResponseHandler();

signals:
    void responseProcessed(bool resendPacket);

public:
    virtual void visit(EepCommandResponseFormat& response) = 0;
    virtual void visit(CommonCommandResponseFormat& response) = 0;
    virtual void visit(ReadIdBaseResponseFormat& response) = 0;
};

#endif // RESPONSEHANDLER_H
