#!/usr/bin/python3

# This script install OpLInk system (the server and one client)
# It's useful for testing Oplink

import install_functs as pf
import projects_dirs

# demonstrator version's is 0.0.0 for launcher and bundles !

# OpLink's dirs
#==============
root_install_dir = projects_dirs.build_dir + '/bin'
pf.create_pf_root_dir(root_install_dir)

# PlugFrame's lib
#================
pf_lib = projects_dirs.build_dir + '/plugframe/core-lib/libplugframe-core-qt5-1.0.0.so'
pf.install_pf_lib(root_install_dir,pf_lib)

# OpLink's libs
#==============
# for backend & frontend bundles
ol_lib = projects_dirs.build_dir + '/applications/oplink/core-lib/liboplink-core-qt5-0.0.0.so'
pf.install_pf_lib(root_install_dir,ol_lib)

# for backend bundles only
ol_backend_lib = projects_dirs.build_dir + '/applications/oplink/core-backend-lib/liboplink-core-backend-qt5-0.0.0.so'
pf.install_pf_lib(root_install_dir,ol_backend_lib)

#=====================
#
# Background's bundles
#
#=====================

backend_install_dir = root_install_dir + '/oplink_backend'
pf.create_pf_dirs(backend_install_dir)

# framework
#----------
pf_framework = projects_dirs.build_dir + '/plugframe/bundles/framework/plugin/libframework-qt5-1.0.0.so'
pf.install_pf_bundle(backend_install_dir,'framework',pf_framework)

# logger
#-------
pf_logger = projects_dirs.build_dir + '/plugframe/bundles/logger/plugin/liblogger-qt5-1.0.0.so'
ol_logger_ini = projects_dirs.conf_dir + '/oplink_backend_log.ini'
pf.install_pf_bundle(backend_install_dir,'logger',pf_logger)
pf.install_bundle_conf_file(backend_install_dir,'logger',ol_logger_ini, 'log.ini')

# display
#--------
pf_display = projects_dirs.build_dir + '/plugframe/bundles/display/plugin/libdisplay-qt5-1.0.0.so'
pf.install_pf_bundle(backend_install_dir,'display',pf_display)

# console
#--------
ol_console = projects_dirs.build_dir + '/applications/oplink/backend-bundles/console/plugin/liboplinkB-console-qt5-0.0.0.so'
pf.install_pf_bundle(backend_install_dir,'console',ol_console)

# users
#------
pf_users = projects_dirs.build_dir + '/plugframe/bundles/users/plugin/libusers-qt5-1.0.0.so'
ol_users_ini = projects_dirs.conf_dir + '/oplink_backend_users.ini'
ol_user_profil_xml = projects_dirs.conf_dir + '/oplink_backend_user_remotemonitoring.xml'
pf.install_pf_bundle(backend_install_dir,'users',pf_users)
pf.install_bundle_conf_file(backend_install_dir,'users',ol_users_ini,'users.ini')
# naming rule : <profil>-remotemonitoring.xml
pf.install_bundle_conf_file(backend_install_dir,'users',ol_user_profil_xml,'user-remotemonitoring.xml')

# engine
#-------
ol_engine = projects_dirs.build_dir + '/applications/oplink/backend-bundles/engine/plugin/liboplinkB-engine-qt5-0.0.0.so'
pf.install_pf_bundle(backend_install_dir,'engine',ol_engine)

# enoceaninfrastructure
#----------------------
ol_enoceaninfrastructure = projects_dirs.build_dir + '/applications/oplink/backend-bundles/enoceaninfrastructure/plugin/liboplinkB-enoceaninfrastructure-qt5-0.0.0.so'
ol_enoceaninfrastructure_xml = projects_dirs.conf_dir + '/oplink_backend_infrastructure_enocean.xml'
pf.install_pf_bundle(backend_install_dir,'enoceaninfrastructure',ol_enoceaninfrastructure)
pf.install_bundle_conf_file(backend_install_dir,'enoceaninfrastructure',ol_enoceaninfrastructure_xml,'infrastructure-enocean.xml')

# heatingmanagerset
#------------------
ol_heatingmanagerset = projects_dirs.build_dir + '/applications/oplink/backend-bundles/heatingmanagerset/plugin/liboplinkB-heatingmanagerset-qt5-0.0.0.so'
# This bundle can load multiple heating manager conf files !
ol_heatingmanagerset_xml = projects_dirs.conf_dir + '/oplink_backend_pwt_heatingmanager1.xml'
pf.install_pf_bundle(backend_install_dir,'heatingmanagerset',ol_heatingmanagerset)
pf.install_bundle_conf_file(backend_install_dir,'heatingmanagerset',ol_heatingmanagerset_xml,'oplink_pwt_heatingmanager1.xml')

# observablemodelloader
#---------------
ol_modelloader = projects_dirs.build_dir + '/applications/oplink/backend-bundles/observablemodelloader/plugin/liboplinkB-observablemodelloader-qt5-0.0.0.so'
ol_modelloader_xml = projects_dirs.conf_dir + '/oplink_backend_observable_models.xml'
pf.install_pf_bundle(backend_install_dir,'observablemodelloader',ol_modelloader)
pf.install_bundle_conf_file(backend_install_dir,'observablemodelloader',ol_modelloader_xml,'observable-models.xml')

# observablemodelregister
#------------------------
ol_observablemodelregister = projects_dirs.build_dir + '/applications/oplink/backend-bundles/observablemodelregister/plugin/liboplinkB-observablemodelregister-qt5-0.0.0.so'
pf.install_pf_bundle(backend_install_dir,'observablemodelregister',ol_observablemodelregister)

# tcpbackend (replace remoteobject)
#-----------
ol_tcpbackend = projects_dirs.build_dir + '/applications/oplink/backend-bundles/tcpbackend/plugin/liboplinkB-tcpbackend-qt5-0.0.0.so'
ol_tcpbackend_ini = projects_dirs.conf_dir + '/oplink_backend_ip.ini'
pf.install_pf_bundle(backend_install_dir,'tcpbackend',ol_tcpbackend)
pf.install_bundle_conf_file(backend_install_dir,'tcpbackend',ol_tcpbackend_ini,'listenAddr.ini')

#=================================
#
# Background launcher's properties
#
#==================================
ol_launcher_backend_properties_ini = projects_dirs.conf_dir + '/oplink_backend_properties.ini'
pf.install_pf_lauching_properties(backend_install_dir,pf.CONF,ol_launcher_backend_properties_ini,'properties.ini')


#======================
#
# GuiFrontend's bundles
#
#======================

guifrontend_install_dir = root_install_dir + '/oplink_guifrontend'
pf.create_pf_dirs(guifrontend_install_dir)

# framework
#----------
pf_framework = projects_dirs.build_dir + '/plugframe/bundles/framework/plugin/libframework-qt5-1.0.0.so'
pf.install_pf_bundle(guifrontend_install_dir,'framework',pf_framework)

# logger
#-------
pf_logger = projects_dirs.build_dir + '/plugframe/bundles/logger/plugin/liblogger-qt5-1.0.0.so'
ol_logger_ini = projects_dirs.conf_dir + '/oplink_frontend_gui_log.ini'
pf.install_pf_bundle(guifrontend_install_dir,'logger',pf_logger)
pf.install_bundle_conf_file(guifrontend_install_dir,'logger',ol_logger_ini, 'log.ini')

# GUIdisplay
#--------
pf_guidisplay = projects_dirs.build_dir + '/plugframe/bundles/guidisplay/plugin/libguidisplay-qt5-1.0.0.so'
pf.install_pf_bundle(guifrontend_install_dir,'guidisplay',pf_guidisplay)

# OpLink GuiConsole
#------------------
ol_guiconsole = projects_dirs.build_dir + '/applications/oplink/frontend-bundles/guiconsole/plugin/liboplinkF-guiconsole-qt5-0.0.0.so'
pf.install_pf_bundle(guifrontend_install_dir,'guiconsole',ol_guiconsole)
ol_guiconsole_ini = projects_dirs.conf_dir + '/oplink_frontend_guiconsole.ini'
pf.install_bundle_conf_file(guifrontend_install_dir,'guiconsole',ol_guiconsole_ini, 'guiconsole.ini')

# tcpfrontend
#-----------
ol_tcpfrontend = projects_dirs.build_dir + '/applications/oplink/frontend-bundles/tcpfrontend/plugin/liboplinkF-tcpfrontend-qt5-0.0.0.so'
pf.install_pf_bundle(guifrontend_install_dir,'tcpfrontend',ol_tcpfrontend)

# GUI Frontend launcher's properties
#===================================
properties_ini = projects_dirs.conf_dir + '/oplink_frontend_gui_properties.ini'
stylesheet_qss = projects_dirs.conf_dir + '/oplink_frontend_gui_elekdom.qss'
pf.install_pf_lauching_properties(guifrontend_install_dir,pf.CONF,properties_ini,'properties.ini')
pf.install_pf_lauching_properties(guifrontend_install_dir,pf.CONF,stylesheet_qss,'elekdom.qss')
