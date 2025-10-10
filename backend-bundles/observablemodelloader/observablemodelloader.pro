TEMPLATE    = subdirs

SUBDIRS	    = lib \
              plugin

plugin.depends = lib

OTHER_FILES += \
    bundle.ver \
    conf/observable-models.xml \
    conf/observable-models_homeautomation_example.xml
