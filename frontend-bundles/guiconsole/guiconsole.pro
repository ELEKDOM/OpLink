TEMPLATE    = subdirs

SUBDIRS	    = lib \
              plugin

plugin.depends = lib

OTHER_FILES += \
    conf/guiconsole.ini \
    bundle.ver
