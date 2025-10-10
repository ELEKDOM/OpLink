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


#ifndef OLFCONSOLEPLUGIN_H
#define OLFCONSOLEPLUGIN_H

#include "plugin/plugin.h"

namespace elekdom
{
namespace oplink
{
namespace frontend
{
namespace guiconsole
{
namespace plugin
{

class OlfConsolePlugin : public plugframe::core::plugin::Plugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "elekdom.oplink.frontend.guiconsole.plugin" FILE "../oplinkF-guiconsolebundle.json")
    Q_INTERFACES(elekdom::plugframe::core::plugin::BundleInterface)

private:
    // m_ServiceImpl;

public:
    OlfConsolePlugin();
    ~OlfConsolePlugin() override;

protected: // PLugin
    plugframe::core::bundle::Bundle4PluginInterface *createImplementation() override;
    PF_bindServicesImplementations_DECL
};

} //namespace plugin
} //namespace guiconsole
} //namespace frontend
} //namespace oplink
} //namespace elekdom

#endif // OLFCONSOLEPLUGIN_H
