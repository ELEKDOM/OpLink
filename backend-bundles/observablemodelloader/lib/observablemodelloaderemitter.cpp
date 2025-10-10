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


#include "logger/pflog.h"
#include "event/event.h"
#include "event/mandatorypropertiesmodelloadingevent.h"
#include "event/specificpropertiesmodelloadingevent.h"
#include "event/processorsmodelloadingevent.h"
#include "event/observablemodelsloadingevent.h"
#include "observablemodelloaderemitter.h"
#include "observablemodelloaderfactory.h"

using namespace elekdom::oplink::observablemodelloader::bundle;

ObservableModelLoaderEmitter::ObservableModelLoaderEmitter(Bundle& bundle, QObject *parent):
    BundleEmitter{bundle,parent}
{

}

ObservableModelLoaderEmitter::~ObservableModelLoaderEmitter()
{

}

void ObservableModelLoaderEmitter::startLoadingEventLoop()
{
    pfDebug3(getLogBundleName()) << "->ObservableModelLoaderEmitter::startLoadingEventLoop";

    // Create the event
    factory::ObservableModelLoaderFactory& myFactory = dynamic_cast<factory::ObservableModelLoaderFactory&>(getFactory());
    plugframe::core::event::QspEvent evt{myFactory.createMandatoryPropertiesModelLoadingEvent(1)};

    // Post the event
    pfDebug4(getLogBundleName()) << "emit MandatoryPropertiesModelLoadingEvent 1";
    emit pfEvent(evt);

    pfDebug3(getLogBundleName()) << "<-ObservableModelLoaderEmitter::startLoadingEventLoop";
}

void ObservableModelLoaderEmitter::mandatoryPropertiesModelEventLoop(unsigned short cpt)
{
    pfDebug3(getLogBundleName()) << "->ObservableModelLoaderEmitter::mandatoryPropertiesModelEventLoop, " << cpt;

    factory::ObservableModelLoaderFactory& myFactory = dynamic_cast<factory::ObservableModelLoaderFactory&>(getFactory());
    plugframe::core::event::QspEvent evt{myFactory.createMandatoryPropertiesModelLoadingEvent(cpt)};

    // Post the event
    pfDebug4(getLogBundleName()) << "emit MandatoryPropertiesModelLoadingEvent, " << cpt;
    emit pfEvent(evt);

    pfDebug3(getLogBundleName()) << "<-ObservableModelLoaderEmitter::mandatoryPropertiesModelEventLoop";
}

void ObservableModelLoaderEmitter::specificPropertiesModelEventLoop(unsigned short cpt)
{
    pfDebug3(getLogBundleName()) << "->ObservableModelLoaderEmitter::specificPropertiesModelEventLoop, " << cpt;

    factory::ObservableModelLoaderFactory& myFactory = dynamic_cast<factory::ObservableModelLoaderFactory&>(getFactory());
    plugframe::core::event::QspEvent evt{myFactory.createSpecificPropertiesModelLoadingEvent(cpt)};

    // Post the event
    pfDebug4(getLogBundleName()) << "emit SpecificPropertiesModelLoadingEvent, " << cpt;
    emit pfEvent(evt);

    pfDebug3(getLogBundleName()) << "<-ObservableModelLoaderEmitter::specificPropertiesModelEventLoop";
}

void ObservableModelLoaderEmitter::processorModelEventLoop(unsigned short cpt)
{
    pfDebug3(getLogBundleName()) << "->ObservableModelLoaderEmitter::processorModelEventLoop, " << cpt;

    factory::ObservableModelLoaderFactory& myFactory = dynamic_cast<factory::ObservableModelLoaderFactory&>(getFactory());
    plugframe::core::event::QspEvent evt{myFactory.createProcessorsModelLoadingEvent(cpt)};

    // Post the event
    pfDebug4(getLogBundleName()) << "emit ProcessorsModelLoadingEvent, " << cpt;
    emit pfEvent(evt);

    pfDebug3(getLogBundleName()) << "<-ObservableModelLoaderEmitter::processorModelEventLoop";
}

void ObservableModelLoaderEmitter::observableModelsEventLoop(unsigned short cpt)
{
    pfDebug3(getLogBundleName()) << "->ObservableModelLoaderEmitter::observableModelsEventLoop, " << cpt;

    factory::ObservableModelLoaderFactory& myFactory = dynamic_cast<factory::ObservableModelLoaderFactory&>(getFactory());
    plugframe::core::event::QspEvent evt{myFactory.createObservableModelsLoadingEvent(cpt)};

    // Post the event
    pfDebug4(getLogBundleName()) << "emit ObservableModelsLoadingEvent, " << cpt;
    emit pfEvent(evt);

    pfDebug3(getLogBundleName()) << "->ObservableModelLoaderEmitter::observableModelsEventLoop";
}
