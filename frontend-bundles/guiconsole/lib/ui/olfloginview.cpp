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


#include "olfloginview.h"
#include "ui_loginview.h"

using namespace elekdom::oplink::frontend::guiconsole;

OlfLoginView::OlfLoginView(QWidget *parent):
    OlfConsoleView{"",parent},
    ui(new Ui::loginView)
{
    ui->setupUi(this);

    // UI connections
    connect(ui->identifier, SIGNAL(editingFinished()), SLOT(onIdentifierEditingFinish()));
    connect(ui->password, SIGNAL(editingFinished()), SLOT(onPasswordEditingFinish()));
    connect(ui->siginButton, SIGNAL(pressed()), SLOT(onSigninButtonPressed()));
}

OlfLoginView::~OlfLoginView()
{

}

void OlfLoginView::enableLogin()
{
    ui->identifier->setEnabled(true);
    ui->identifier->clear();
    ui->identifier->setFocus();
    ui->password->setEnabled(false);
    ui->password->clear();
    ui->siginButton->setText(tr("Sign in"));
}

void OlfLoginView::lockLogin()
{
    ui->identifier->clear();
    ui->identifier->setEnabled(false);
    ui->password->clear();
    ui->password->setEnabled(false);
    ui->siginButton->setEnabled(false);
}

void OlfLoginView::loginSuccess()
{
    ui->identifier->setEnabled(false);
    ui->password->clear();
    ui->password->setEnabled(false);
    ui->siginButton->setText(tr("Sign out"));
}

void OlfLoginView::reset()
{
    ui->identifier->clear();
    ui->password->clear();
}

void OlfLoginView::onIdentifierEditingFinish()
{
    if (ui->identifier->text().isEmpty() == false)
    {
        ui->password->setEnabled(true);
        ui->password->setFocus();
    }
}

void OlfLoginView::onPasswordEditingFinish()
{
    if (ui->password->text().isEmpty() == false)
    {
        ui->siginButton->setEnabled(true);
        ui->siginButton->setFocus();
    }
}

void OlfLoginView::onSigninButtonPressed()
{
    emit sigin(ui->identifier->text(), ui->password->text());
}
