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

#include "lightingwidgetview.h"
#include "ui_lightingwidgetview.h"

LightingWidgetView::LightingWidgetView(QWidget *parent):
    MonitoredObservableWidgetListView{parent},
    ui(new Ui::lightingWidgetView)
{
    ui->setupUi(this);

    connect(ui->onCmd, SIGNAL(pressed()), SLOT(onOnCmd()));
    connect(ui->offCmd, SIGNAL(pressed()), SLOT(onOffCmd()));
}

LightingWidgetView::~LightingWidgetView()
{
    delete ui;
}

void LightingWidgetView::setTitle(const QString &title)
{
    ui->lightName->setText(title);
}

void LightingWidgetView::setImg(const QPixmap &img, const QString &propertyName)
{
    Q_UNUSED(propertyName)
    ui->state->setPixmap(img);
}

void LightingWidgetView::enableCmdButton(bool enable, const QString &cmdName)
{

    if (cmdName == ButtonName::on())
    {
        ui->onCmd->setEnabled(enable);
    }
    else if (cmdName == ButtonName::off())
    {
        ui->offCmd->setEnabled(enable);
    }
}

void LightingWidgetView::onOnCmd()
{
    emit cmdButtonClicked(ButtonName::on());
}

void LightingWidgetView::onOffCmd()
{
    emit cmdButtonClicked(ButtonName::off());
}
