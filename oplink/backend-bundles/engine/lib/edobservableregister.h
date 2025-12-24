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


#ifndef EDOBSERVABLEREGISTER_H
#define EDOBSERVABLEREGISTER_H

#include <QHash>
#include "pluginpattern/smfbundleimplementation.h"
#include "edobservableregisterservice.h"
#include "edobservablelookupservice.h"
#include "observable/edobservable.h"

using namespace smf::core;

namespace edserver
{

class EdObservableRegister: public pluginpattern::SmfBundleImplementation
{

    friend EdObservableRegisterService;
    friend EdObservableLookupService;

public:
    EdObservableRegister(pluginpattern::SmfPlugin& bundle);
    virtual ~EdObservableRegister();

protected: // for class EdObservableRegisterService;
    bool addObservable(QspEdObservable observable);

protected: // for class EdObservableLookupService;
    QspEdObservable lookupObservable(const EdObservableName& name);

private: // implementation's attributs
    QHash<const EdObservableName&, QspEdObservable> m_observables;
};

using QspEdObservableRegister = QSharedPointer<EdObservableRegister>;

}//namespace edserver

#endif // EDOBSERVABLEREGISTER_H
