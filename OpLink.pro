#! [0]
TEMPLATE    = subdirs

SUBDIRS	    = \
    core-lib \
    core-backend-lib \
    backend-bundles \
    backend-launcher \
    frontend-bundles \
    frontend-launcher
    #core-backend-lib-tests

core-backend-lib.depends = core-lib
backend-bundles.depends = core-backend-lib
backend-launcher.depends = backend-bundles
frontend-bundles.depends = core-lib
frontend-launcher.depends = frontend-bundles

OTHER_FILES += \
    README.md
OTHER_FILES += \
    scripts/install_oplink.py
