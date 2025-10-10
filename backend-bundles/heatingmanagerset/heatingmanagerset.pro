#! [0]
TEMPLATE    = subdirs

SUBDIRS	    = lib \
              plugin

plugin.depends = lib

OTHER_FILES += \
    bundle.ver \
    conf/pw-heatingmanager.xml \
    conf/pwt-heatingmanager.xml \
    conf/pwt-heatingmanager_example.xml

