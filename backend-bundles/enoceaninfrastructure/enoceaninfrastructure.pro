TEMPLATE    = subdirs

SUBDIRS	    = lib \
              plugin

plugin.depends = lib

OTHER_FILES += \
    bundle.ver \
    conf/infrastructure-enocean.xml \
    conf/infrastructure-enocean_example.xml

