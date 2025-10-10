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


#include "grouptowatch.h"
#include "statetowatchlist.h"
#include "grouptowatchalgorithm.h"

using namespace elekdom::oplink::core::observable::monitoring;

GroupToWatch::GroupToWatch(QspMonitoredGroupAlgorithm algo):
    m_algorithm{algo}
{
    m_algorithm->group(this);
}

GroupToWatch::~GroupToWatch()
{

}

void GroupToWatch::addCategory(const QString &categoryName)
{
    if (!m_categories.contains(categoryName))
    {
        QspMonitoredStateList newCat{new StateToWatchList};

        m_categories.insert(categoryName, newCat);
    }
}

bool GroupToWatch::isCategoryEmpty(const QString &categoryName)
{
    bool ret{true};

    if (m_categories.contains(categoryName))
    {
        QspMonitoredStateList cat{m_categories.value(categoryName)};

        ret = cat->isEmpty();
    }

    return ret;
}

void GroupToWatch::addMonitoredState(const QString &categoryName, QspMonitoredState monitoredState)
{
    if (m_categories.contains(categoryName))
    {
        QspMonitoredStateList category{m_categories.value(categoryName)};

        category->append(monitoredState);

        // Add a new input for reverse look up !
        QString obsName{monitoredState->observableName()};
        QString propName{monitoredState->propertyName()};
        QString reverseInput{obsName+propName};
        m_reversLookUp.insert(reverseInput, categoryName);
    }
}

QspMonitoredStateList GroupToWatch::category(const QString &categoryName)
{
    return m_categories.value(categoryName);
}

void GroupToWatch::initAlgorithm(engine::service::ObservableServiceInterface *observableService)
{
    if (!m_algorithm.isNull())
    {
        m_algorithm->initAlgorithm(observableService);
    }
}

GroupToWatchAlgorithm *GroupToWatch::algorithm()
{
    GroupToWatchAlgorithm *ret{nullptr};

    if (!m_algorithm.isNull())
    {
        return m_algorithm.data();
    }
    return ret;
}

QString GroupToWatch::reverseLookUp(const QString &reverseInput)
{
    return m_reversLookUp.value(reverseInput);
}

bool GroupToWatch::allTrue(const QString &categoryName)
{
    QspMonitoredStateList msList{category(categoryName)};

    return msList->allTrue();
}
