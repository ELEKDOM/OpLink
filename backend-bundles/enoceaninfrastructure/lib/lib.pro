QT -= gui
QT += serialport xml

TEMPLATE = lib
CONFIG  += staticlib

BUNDLE_VERSION = $$cat(../bundle.ver)
TARGET = oplinkB-enoceaninfrastructure-qt6-$${BUNDLE_VERSION}

SOURCES +=  \
            area/enoceandevicearea.cpp \
            area/enoceanoperatingdevicearea.cpp \
            area/enoceansetupdevicearea.cpp \
            commandprocessor/D2/d201measurementenergyquery.cpp \
            commandprocessor/D2/d201measurementpowerquery.cpp \
            commandprocessor/D2/d201pilotwiremodequery.cpp \
            commandprocessor/D2/d201setoutput.cpp \
            commandprocessor/D2/d201setpilotwiremode.cpp \
            commandprocessor/D2/d201statusquery.cpp \
            device/a50401eep.cpp \
            device/a504eep.cpp \
            device/a5eep.cpp \
            device/d2010ceep.cpp \
            device/d2010eeep.cpp \
            device/d50001eep.cpp \
            device/d500eep.cpp \
            device/d5eep.cpp \
            loader/enoceanconfreader.cpp \
            loader/enoceaninfrastructureloader.cpp \
            loader/enoceaninfrastructureoperatingloader.cpp \
            loader/enoceandevicebuilder.cpp \
            loader/enoceandeviceprocessorbuilder.cpp \
            loader/enoceanoperatingdeviceprocessorbuilder.cpp \
            loader/enoceangatewayargs.cpp \
            loader/enoceantcpgatewayargs.cpp \
            loader/enoceanusbgatewayargs.cpp \
            gateway/enoceangateway.cpp \
            gateway/gatewayport.cpp \
            gateway/usbgatewayport.cpp \
            gateway/enoceangatewaymode.cpp \
            gateway/enoceanoperatinggateway.cpp \
            gateway/esp3packetreceiver.cpp \
            gateway/esp3packetserialreceiver.cpp \
            gateway/esp3serialreceiverstate.cpp \
            gateway/waitfordata.cpp \
            gateway/waitfordatacrc.cpp \
            gateway/waitforheader.cpp \
            gateway/waitforheadercrc.cpp \
            gateway/waitforsyncbyte.cpp \
            gateway/esp3packettransmitter.cpp \
            gateway/responsehandler.cpp \
            device/enoceanequipmentprofile.cpp \
            device/d20112eep.cpp \
            device/d201eep.cpp \
            device/d2eep.cpp \
            device/f60101eep.cpp \
            device/f601eep.cpp \
            device/f60201eep.cpp \
            device/f602eep.cpp \
            device/f6eep.cpp \
            commandprocessor/enoceancommandprocessor.cpp \
            commandprocessor/D2/d2commandprocessor.cpp \
            commandprocessor/D2/d201commandprocessor.cpp \
            enoceaninfrastructure.cpp \
            packet/esp3crc8.cpp \
            packet/esp3packet.cpp \
            packet/format/esp3packetformat.cpp \
            packet/format/receivedformat/eeptelegram/a504telegramformat.cpp \
            packet/format/receivedformat/eeptelegram/a5telegramformat.cpp \
            packet/format/receivedformat/eeptelegram/d500telegramformat.cpp \
            packet/format/receivedformat/eeptelegram/d5telegramformat.cpp \
            packet/format/receivedformat/esp3receivedpacketformat.cpp \
            packet/format/receivedformat/eeptelegram/eeptelegramformat.cpp \
            packet/format/receivedformat/eeptelegram/d2telegramformat.cpp \
            packet/format/receivedformat/eeptelegram/d201telegramformat.cpp \
            packet/format/receivedformat/eeptelegram/f6telegramformat.cpp \
            packet/format/receivedformat/eeptelegram/f601telegramformat.cpp \
            packet/format/receivedformat/eeptelegram/f602telegramformat.cpp \
            packet/format/receivedformat/response/responseformat.cpp \
            packet/format/receivedformat/response/eepcommandresponseformat.cpp \
            packet/format/receivedformat/response/commoncommandresponse/commoncommandresponseformat.cpp \
            packet/format/receivedformat/response/commoncommandresponse/readidbaseresponseformat.cpp \
            packet/format/sentformat/eepcommandformat/D2/d201cmd6format.cpp \
            packet/format/sentformat/eepcommandformat/D2/d201cmd8format.cpp \
            packet/format/sentformat/eepcommandformat/D2/d201cmd9format.cpp \
            packet/format/sentformat/esp3sentpacketformat.cpp \
            packet/format/sentformat/commoncommand/commoncommandformat.cpp \
            packet/format/sentformat/commoncommand/readidbaseformat.cpp \
            packet/format/sentformat/eepcommandformat/eepcommandformat.cpp \
            packet/format/sentformat/eepcommandformat/D2/d2commandformat.cpp \
            packet/format/sentformat/eepcommandformat/D2/d201commandformat.cpp \
            packet/format/sentformat/eepcommandformat/D2/d201cmd1format.cpp \
            packet/format/sentformat/eepcommandformat/D2/d201cmd3format.cpp

HEADERS +=  \
            area/enoceandevicearea.h \
            area/enoceanoperatingdevicearea.h \
            area/enoceansetupdevicearea.h \
            commandprocessor/D2/d201measurementenergyquery.h \
            commandprocessor/D2/d201measurementpowerquery.h \
            commandprocessor/D2/d201pilotwiremodequery.h \
            commandprocessor/D2/d201setoutput.h \
            commandprocessor/D2/d201setpilotwiremode.h \
            commandprocessor/D2/d201statusquery.h \
            device/a50401eep.h \
            device/a504eep.h \
            device/a5eep.h \
            device/d2010ceep.h \
            device/d2010eeep.h \
            device/d50001eep.h \
            device/d500eep.h \
            device/d5eep.h \
            enoceaninfrastructure_forward.h \
            enoceaninfrastructurelogchannel.h \
            loader/enoceanconfreader.h \
            loader/enoceaninfrastructureloader.h \
            loader/enoceaninfrastructureoperatingloader.h \
            loader/enoceandevicebuilder.h \
            loader/enoceandeviceprocessorbuilder.h \
            loader/enoceanoperatingdeviceprocessorbuilder.h \
            loader/enoceangatewayargs.h \
            loader/enoceantcpgatewayargs.h \
            loader/enoceanusbgatewayargs.h \
            gateway/enoceangateway.h \
            gateway/gatewayport.h \
            gateway/usbgatewayport.h \
            gateway/enoceangatewaymode.h \
            gateway/enoceanoperatinggateway.h \
            gateway/esp3packetreceiver.h \
            gateway/esp3packetserialreceiver.h \
            gateway/esp3serialreceiverstate.h \
            gateway/waitfordata.h \
            gateway/waitfordatacrc.h \
            gateway/waitforheader.h \
            gateway/waitforheadercrc.h \
            gateway/waitforsyncbyte.h \
            gateway/esp3packettransmitter.h \
            gateway/responsehandler.h \
            device/enoceanequipmentprofile.h \
            device/d20112eep.h \
            device/d201eep.h \
            device/d2eep.h \
            device/f60101eep.h \
            device/f601eep.h \
            device/f60201eep.h \
            device/f602eep.h \
            device/f6eep.h \
            commandprocessor/enoceancommandprocessor.h \
            commandprocessor/D2/d2commandprocessor.h \
            commandprocessor/D2/d201commandprocessor.h \
            enoceaninfrastructure.h \
            packet/esp3crc8.h \
            packet/esp3packet.h \
            packet/format/esp3packetformat.h \
            packet/format/receivedformat/eeptelegram/a504telegramformat.h \
            packet/format/receivedformat/eeptelegram/a5telegramformat.h \
            packet/format/receivedformat/eeptelegram/d500telegramformat.h \
            packet/format/receivedformat/eeptelegram/d5telegramformat.h \
            packet/format/receivedformat/esp3receivedpacketformat.h \
            packet/format/receivedformat/eeptelegram/eeptelegramformat.h \
            packet/format/receivedformat/eeptelegram/d2telegramformat.h \
            packet/format/receivedformat/eeptelegram/d201telegramformat.h \
            packet/format/receivedformat/eeptelegram/f6telegramformat.h \
            packet/format/receivedformat/eeptelegram/f601telegramformat.h \
            packet/format/receivedformat/eeptelegram/f602telegramformat.h \
            packet/format/receivedformat/response/responseformat.h \
            packet/format/receivedformat/response/eepcommandresponseformat.h \
            packet/format/receivedformat/response/commoncommandresponse/commoncommandresponseformat.h \
            packet/format/receivedformat/response/commoncommandresponse/readidbaseresponseformat.h \
            packet/format/sentformat/eepcommandformat/D2/d201cmd6format.h \
            packet/format/sentformat/eepcommandformat/D2/d201cmd8format.h \
            packet/format/sentformat/eepcommandformat/D2/d201cmd9format.h \
            packet/format/sentformat/esp3sentpacketformat.h \
            packet/format/sentformat/commoncommand/commoncommandformat.h \
            packet/format/sentformat/commoncommand/readidbaseformat.h \
            packet/format/sentformat/eepcommandformat/eepcommandformat.h \
            packet/format/sentformat/eepcommandformat/D2/d2commandformat.h \
            packet/format/sentformat/eepcommandformat/D2/d201commandformat.h \
            packet/format/sentformat/eepcommandformat/D2/d201cmd1format.h \
            packet/format/sentformat/eepcommandformat/D2/d201cmd3format.h

INCLUDEPATH += \
            ../plugin \
            ../../../core-backend-lib \
            ../../../core-lib \
            ../../../../../plugframe/core-lib

CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT

