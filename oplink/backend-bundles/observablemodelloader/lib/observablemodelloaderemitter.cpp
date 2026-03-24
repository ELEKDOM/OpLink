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
#include "observablemodelloaderemitter.h"
#include "observablemodelloaderfactory.h"

ObservableModelLoaderEmitter::ObservableModelLoaderEmitter(plugframe::Bundle& bundle, QObject *parent):
    BundleEmitter{bundle,parent}
{

}

ObservableModelLoaderEmitter::~ObservableModelLoaderEmitter()
{

}

void ObservableModelLoaderEmitter::startLoadingEventLoop()
{
    pfDebug3(getLogBundleName()) << "->ObservableModelLoaderEmitter::startLoadingEventLoop";

    // Create the first event
    ObservableModelLoaderFactory& myFactory = dynamic_cast<ObservableModelLoaderFactory&>(getFactory());
    plugframe::QspEvent evt{myFactory.createSpecificPropertiesModelLoadingEvent(1)};

    // Post the event
    pfDebug4(getLogBundleName()) << "emit First event, SpecificPropertiesModelLoadingEvent 1";
    emit pfEvent(evt);

    pfDebug3(getLogBundleName()) << "<-ObservableModelLoaderEmitter::startLoadingEventLoop";
}

void ObservableModelLoaderEmitter::specificPropertiesModelEventLoop(unsigned short cpt)
{
    pfDebug3(getLogBundleName()) << "->ObservableModelLoaderEmitter::specificPropertiesModelEventLoop, " << cpt;

    ObservableModelLoaderFactory& myFactory = dynamic_cast<ObservableModelLoaderFactory&>(getFactory());
    plugframe::QspEvent evt{myFactory.createSpecificPropertiesModelLoadingEvent(cpt)};

    // Post the event
    pfDebug4(getLogBundleName()) << "emit SpecificPropertiesModelLoadingEvent, " << cpt;
    emit pfEvent(evt);

    pfDebug3(getLogBundleName()) << "<-ObservableModelLoaderEmitter::specificPropertiesModelEventLoop";
}

void ObservableModelLoaderEmitter::processorModelEventLoop(unsigned short cpt)
{
    pfDebug3(getLogBundleName()) << "->ObservableModelLoaderEmitter::processorModelEventLoop, " << cpt;

    ObservableModelLoaderFactory& myFactory = dynamic_cast<ObservableModelLoaderFactory&>(getFactory());
    plugframe::QspEvent evt{myFactory.createProcessorsModelLoadingEvent(cpt)};

    // Post the event
    pfDebug4(getLogBundleName()) << "emit ProcessorsModelLoadingEvent, " << cpt;
    emit pfEvent(evt);

    pfDebug3(getLogBundleName()) << "<-ObservableModelLoaderEmitter::processorModelEventLoop";
}

void ObservableModelLoaderEmitter::observableModelsEventLoop(unsigned short cpt)
{
    pfDebug3(getLogBundleName()) << "->ObservableModelLoaderEmitter::observableModelsEventLoop, " << cpt;

    ObservableModelLoaderFactory& myFactory = dynamic_cast<ObservableModelLoaderFactory&>(getFactory());
    plugframe::QspEvent evt{myFactory.createObservableModelsLoadingEvent(cpt)};

    // Post the event
    pfDebug4(getLogBundleName()) << "emit ObservableModelsLoadingEvent, " << cpt;
    emit pfEvent(evt);

    pfDebug3(getLogBundleName()) << "->ObservableModelLoaderEmitter::observableModelsEventLoop";
}
