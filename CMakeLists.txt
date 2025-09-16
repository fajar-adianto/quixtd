cmake_minimum_required(VERSION 3.16)

project(QuixTd VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(QT_QML_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR})
set(QT_QML_GENERATE_QMLLS_INI ON)

# Don't forget to append path to tdlib in CMAKE_PREFIX_PATH!
#   Add: list(APPEND CMAKE_PREFIX_PATH "C:/path/to/tdlib")
list(APPEND CMAKE_PREFIX_PATH "C:/Users/mfaja/Documents/cpp_lib/td-1.8.54/td")
find_package(Td 1.8.54 REQUIRED)

find_package(Qt6 6.2 COMPONENTS Core Qml Quick Concurrent Positioning Multimedia Widgets REQUIRED)

qt_policy(SET QTP0001 NEW)
qt_policy(SET QTP0004 NEW)
qt_policy(SET QTP0005 NEW)

qt_add_library(QuixTd STATIC)
qt_add_qml_module(QuixTd
    URI QuixTd
    VERSION 1.0
    QML_FILES QxTdControls.qml
    SOURCES qxtd.cpp qxtd.h
SOURCES
    cpp/auth/requests/qtdauthcoderesponse.cpp cpp/auth/requests/qtdauthcoderesponse.h
    cpp/auth/requests/qtdauthdeleteaccountresponse.cpp cpp/auth/requests/qtdauthdeleteaccountresponse.h
    cpp/auth/requests/qtdauthencryptionkeyresponse.cpp cpp/auth/requests/qtdauthencryptionkeyresponse.h
    cpp/auth/requests/qtdauthlogoutresponse.cpp cpp/auth/requests/qtdauthlogoutresponse.h
    cpp/auth/requests/qtdauthparametersresponse.cpp cpp/auth/requests/qtdauthparametersresponse.h
    cpp/auth/requests/qtdauthpasswordresponse.cpp cpp/auth/requests/qtdauthpasswordresponse.h
    cpp/auth/requests/qtdauthphonenumberresponse.cpp cpp/auth/requests/qtdauthphonenumberresponse.h
    cpp/auth/requests/qtdauthregistrationresponse.cpp cpp/auth/requests/qtdauthregistrationresponse.h
    cpp/auth/requests/qtdauthresendcoderequest.cpp cpp/auth/requests/qtdauthresendcoderequest.h
    cpp/auth/qtdauthcode.cpp cpp/auth/qtdauthcode.h
    cpp/auth/qtdauthmanager.cpp cpp/auth/qtdauthmanager.h
    cpp/auth/qtdauthparams.cpp cpp/auth/qtdauthparams.h
    cpp/auth/qtdauthstate.cpp cpp/auth/qtdauthstate.h
    cpp/auth/qtdauthstatefactory.cpp cpp/auth/qtdauthstatefactory.h
    cpp/call/qtdcalldiscardreason.cpp cpp/call/qtdcalldiscardreason.h
    cpp/chat/requests/qtdchatreportreason.cpp cpp/chat/requests/qtdchatreportreason.h
    cpp/chat/requests/qtdcheckchatinvitelinkrequest.cpp cpp/chat/requests/qtdcheckchatinvitelinkrequest.h
    cpp/chat/requests/qtdclosechatrequest.cpp cpp/chat/requests/qtdclosechatrequest.h
    cpp/chat/requests/qtdclosesecretchatrequest.cpp cpp/chat/requests/qtdclosesecretchatrequest.h
    cpp/chat/requests/qtdcreatenewsecretchatrequest.cpp cpp/chat/requests/qtdcreatenewsecretchatrequest.h
    cpp/chat/requests/qtdcreateprivatechatrequest.cpp cpp/chat/requests/qtdcreateprivatechatrequest.h
    cpp/chat/requests/qtddeletechathistoryrequest.cpp cpp/chat/requests/qtddeletechathistoryrequest.h
    cpp/chat/requests/qtdforwardmessagesrequest.cpp cpp/chat/requests/qtdforwardmessagesrequest.h
    cpp/chat/requests/qtdgetbasicgrouprequest.cpp cpp/chat/requests/qtdgetbasicgrouprequest.h
    cpp/chat/requests/qtdgetchatrequest.cpp cpp/chat/requests/qtdgetchatrequest.h
    cpp/chat/requests/qtdgetchatsrequest.cpp cpp/chat/requests/qtdgetchatsrequest.h
    cpp/chat/requests/qtdgetsecretchatrequest.cpp cpp/chat/requests/qtdgetsecretchatrequest.h
    cpp/chat/requests/qtdgetsupergroupfullinforequest.cpp cpp/chat/requests/qtdgetsupergroupfullinforequest.h
    cpp/chat/requests/qtdgetsupergrouprequest.cpp cpp/chat/requests/qtdgetsupergrouprequest.h
    cpp/chat/requests/qtdjoinchatbyinvitelinkrequest.cpp cpp/chat/requests/qtdjoinchatbyinvitelinkrequest.h
    cpp/chat/requests/qtdjoinchatrequest.cpp cpp/chat/requests/qtdjoinchatrequest.h
    cpp/chat/requests/qtdleavechatrequest.cpp cpp/chat/requests/qtdleavechatrequest.h
    cpp/chat/requests/qtdloadchatsrequest.cpp cpp/chat/requests/qtdloadchatsrequest.h
    cpp/chat/requests/qtdopenchatrequest.cpp cpp/chat/requests/qtdopenchatrequest.h
    cpp/chat/requests/qtdreportchatrequest.cpp cpp/chat/requests/qtdreportchatrequest.h
    cpp/chat/requests/qtdsearchchatmessagesrequest.cpp cpp/chat/requests/qtdsearchchatmessagesrequest.h
    cpp/chat/requests/qtdsearchpublicchatrequest.cpp cpp/chat/requests/qtdsearchpublicchatrequest.h
    cpp/chat/requests/qtdsendchatactionrequest.cpp cpp/chat/requests/qtdsendchatactionrequest.h
    cpp/chat/requests/qtdsetchatdraftrequest.cpp cpp/chat/requests/qtdsetchatdraftrequest.h
    cpp/chat/requests/qtdsetchatmessagettlrequest.cpp cpp/chat/requests/qtdsetchatmessagettlrequest.h
    cpp/chat/requests/qtdsetchatnotificationsettings.cpp cpp/chat/requests/qtdsetchatnotificationsettings.h
    cpp/chat/requests/qtdsetchattitlerequest.cpp cpp/chat/requests/qtdsetchattitlerequest.h
    cpp/chat/requests/qtdsetpinnedchatsrequest.cpp cpp/chat/requests/qtdsetpinnedchatsrequest.h
    cpp/chat/qtdbasicgroupchat.cpp cpp/chat/qtdbasicgroupchat.h
    cpp/chat/qtdchat.cpp cpp/chat/qtdchat.h
    cpp/chat/qtdchataction.cpp cpp/chat/qtdchataction.h
    cpp/chat/qtdchatactionbar.cpp cpp/chat/qtdchatactionbar.h
    cpp/chat/qtdchatactionfactory.cpp cpp/chat/qtdchatactionfactory.h
    cpp/chat/qtdchatadministratorrights.cpp cpp/chat/qtdchatadministratorrights.h
    cpp/chat/qtdchatinvitelinkinfo.cpp cpp/chat/qtdchatinvitelinkinfo.h
    cpp/chat/qtdchatlist.cpp cpp/chat/qtdchatlist.h
    cpp/chat/qtdchatlistmodel.cpp cpp/chat/qtdchatlistmodel.h
    cpp/chat/qtdchatlistsortfiltermodel.cpp cpp/chat/qtdchatlistsortfiltermodel.h
    cpp/chat/qtdchatmember.cpp cpp/chat/qtdchatmember.h
    cpp/chat/qtdchatmemberstatus.cpp cpp/chat/qtdchatmemberstatus.h
    cpp/chat/qtdchatpermissions.cpp cpp/chat/qtdchatpermissions.h
    cpp/chat/qtdchatposition.cpp cpp/chat/qtdchatposition.h
    cpp/chat/qtdchattype.cpp cpp/chat/qtdchattype.h
    cpp/chat/qtdchattypefactory.cpp cpp/chat/qtdchattypefactory.h
    cpp/chat/qtdsecretchat.cpp cpp/chat/qtdsecretchat.h
    cpp/chat/qtdsecretchatstate.cpp cpp/chat/qtdsecretchatstate.h
    cpp/chat/qtdsupergroupchat.cpp cpp/chat/qtdsupergroupchat.h
    cpp/client/requests/qtdcloserequest.cpp cpp/client/requests/qtdcloserequest.h
    cpp/client/qtdclient.cpp cpp/client/qtdclient.h
    cpp/client/qtdhandle.cpp cpp/client/qtdhandle.h
    cpp/client/qtdthread.cpp cpp/client/qtdthread.h
    cpp/common/qabstractint64id.cpp cpp/common/qabstractint64id.h
    cpp/common/qx_td_object.cpp cpp/common/qx_td_object.h
    cpp/common/qtdhelpers.cpp cpp/common/qtdhelpers.h
    cpp/common/qtdint.cpp cpp/common/qtdint.h
    cpp/common/qtdrequest.cpp cpp/common/qtdrequest.h
    cpp/common/qtdresponse.cpp cpp/common/qtdresponse.h
    cpp/connections/qtdconnectionmanager.cpp cpp/connections/qtdconnectionmanager.h
    cpp/connections/qtdconnectionstate.cpp cpp/connections/qtdconnectionstate.h
    cpp/connections/qtdconnectionstatefactory.cpp cpp/connections/qtdconnectionstatefactory.h
    cpp/files/sticker/qtdstickerformat.cpp cpp/files/sticker/qtdstickerformat.h
    cpp/files/sticker/qtdstickertype.cpp cpp/files/sticker/qtdstickertype.h
    cpp/files/qtdanimation.cpp cpp/files/qtdanimation.h
    cpp/files/qtdaudio.cpp cpp/files/qtdaudio.h
    cpp/files/qtddocument.cpp cpp/files/qtddocument.h
    cpp/files/qtddownloadfilerequest.cpp cpp/files/qtddownloadfilerequest.h
    cpp/files/qtdfile.cpp cpp/files/qtdfile.h
    cpp/files/qtdlocalfile.cpp cpp/files/qtdlocalfile.h
    cpp/files/qtdminithumbnail.cpp cpp/files/qtdminithumbnail.h
    cpp/files/qtdphoto.cpp cpp/files/qtdphoto.h
    cpp/files/qtdphotos.cpp cpp/files/qtdphotos.h
    cpp/files/qtdphotosize.cpp cpp/files/qtdphotosize.h
    cpp/files/qtdremotefile.cpp cpp/files/qtdremotefile.h
    cpp/files/qtdsticker.cpp cpp/files/qtdsticker.h
    cpp/files/qtdthumbnail.cpp cpp/files/qtdthumbnail.h
    cpp/files/qtdthumbnailformat.cpp cpp/files/qtdthumbnailformat.h
    cpp/files/qtdvideo.cpp cpp/files/qtdvideo.h
    cpp/files/qtdvideonote.cpp cpp/files/qtdvideonote.h
    cpp/files/qtdvoicenote.cpp cpp/files/qtdvoicenote.h
    cpp/messages/content/qtdformattedtext.cpp cpp/messages/content/qtdformattedtext.h
    cpp/messages/content/qtdlocation.cpp cpp/messages/content/qtdlocation.h
    cpp/messages/content/qtdmessageanimation.cpp cpp/messages/content/qtdmessageanimation.h
    cpp/messages/content/qtdmessageaudio.cpp cpp/messages/content/qtdmessageaudio.h
    cpp/messages/content/qtdmessagebasicgroupchatcreate.cpp cpp/messages/content/qtdmessagebasicgroupchatcreate.h
    cpp/messages/content/qtdmessagecall.cpp cpp/messages/content/qtdmessagecall.h
    cpp/messages/content/qtdmessagechataddmembers.cpp cpp/messages/content/qtdmessagechataddmembers.h
    cpp/messages/content/qtdmessagechatchangephoto.cpp cpp/messages/content/qtdmessagechatchangephoto.h
    cpp/messages/content/qtdmessagechatchangetitle.cpp cpp/messages/content/qtdmessagechatchangetitle.h
    cpp/messages/content/qtdmessagechatdeletemember.cpp cpp/messages/content/qtdmessagechatdeletemember.h
    cpp/messages/content/qtdmessagechatdeletephoto.cpp cpp/messages/content/qtdmessagechatdeletephoto.h
    cpp/messages/content/qtdmessagechatjoinbylink.cpp cpp/messages/content/qtdmessagechatjoinbylink.h
    cpp/messages/content/qtdmessagechatsetmessageautodeletetime.cpp cpp/messages/content/qtdmessagechatsetmessageautodeletetime.h
    cpp/messages/content/qtdmessagechatupgradefrom.cpp cpp/messages/content/qtdmessagechatupgradefrom.h
    cpp/messages/content/qtdmessagechatupgradeto.cpp cpp/messages/content/qtdmessagechatupgradeto.h
    cpp/messages/content/qtdmessagecontact.cpp cpp/messages/content/qtdmessagecontact.h
    cpp/messages/content/qtdmessagecontactregistered.cpp cpp/messages/content/qtdmessagecontactregistered.h
    cpp/messages/content/qtdmessagecustomserviceaction.cpp cpp/messages/content/qtdmessagecustomserviceaction.h
    cpp/messages/content/qtdmessagedate.cpp cpp/messages/content/qtdmessagedate.h
    cpp/messages/content/qtdmessagedocument.cpp cpp/messages/content/qtdmessagedocument.h
    cpp/messages/content/qtdmessagelocation.cpp cpp/messages/content/qtdmessagelocation.h
    cpp/messages/content/qtdmessagephoto.cpp cpp/messages/content/qtdmessagephoto.h
    cpp/messages/content/qtdmessagepinmessage.cpp cpp/messages/content/qtdmessagepinmessage.h
    cpp/messages/content/qtdmessagepoll.cpp cpp/messages/content/qtdmessagepoll.h
    cpp/messages/content/qtdmessagescreenshottaken.cpp cpp/messages/content/qtdmessagescreenshottaken.h
    cpp/messages/content/qtdmessagesticker.cpp cpp/messages/content/qtdmessagesticker.h
    cpp/messages/content/qtdmessagesupergroupchatcreate.cpp cpp/messages/content/qtdmessagesupergroupchatcreate.h
    cpp/messages/content/qtdmessagetext.cpp cpp/messages/content/qtdmessagetext.h
    cpp/messages/content/qtdmessageunreadlabel.cpp cpp/messages/content/qtdmessageunreadlabel.h
    cpp/messages/content/qtdmessageunsupported.cpp cpp/messages/content/qtdmessageunsupported.h
    cpp/messages/content/qtdmessagevideo.cpp cpp/messages/content/qtdmessagevideo.h
    cpp/messages/content/qtdmessagevideonote.cpp cpp/messages/content/qtdmessagevideonote.h
    cpp/messages/content/qtdmessagevoicenote.cpp cpp/messages/content/qtdmessagevoicenote.h
    cpp/messages/content/qtdpoll.cpp cpp/messages/content/qtdpoll.h
    cpp/messages/content/qtdpolloption.cpp cpp/messages/content/qtdpolloption.h
    cpp/messages/content/qtdpolltype.cpp cpp/messages/content/qtdpolltype.h
    cpp/messages/content/qtdtextentity.cpp cpp/messages/content/qtdtextentity.h
    cpp/messages/content/qtdtextentitytype.cpp cpp/messages/content/qtdtextentitytype.h
    cpp/messages/content/qtdwebpage.cpp cpp/messages/content/qtdwebpage.h
    cpp/messages/forwardinfo/qtdmessageforwardinfo.cpp cpp/messages/forwardinfo/qtdmessageforwardinfo.h
    cpp/messages/forwardinfo/qtdmessageforwardorigin.cpp cpp/messages/forwardinfo/qtdmessageforwardorigin.h
    cpp/messages/forwardinfo/qtdmessageforwardoriginfactory.cpp cpp/messages/forwardinfo/qtdmessageforwardoriginfactory.h
    cpp/messages/replymarkup/qtdkeyboardbutton.cpp cpp/messages/replymarkup/qtdkeyboardbutton.h
    cpp/messages/replymarkup/qtdkeyboardbuttontype.cpp cpp/messages/replymarkup/qtdkeyboardbuttontype.h
    cpp/messages/replymarkup/qtdreplymarkup.cpp cpp/messages/replymarkup/qtdreplymarkup.h
    cpp/messages/requests/content/imessageattachmentcontent.h cpp/messages/requests/content/imessagecaptioncontent.h
    cpp/messages/requests/content/qtdinputmessageaudio.cpp cpp/messages/requests/content/qtdinputmessageaudio.h
    cpp/messages/requests/content/qtdinputmessagecontact.cpp cpp/messages/requests/content/qtdinputmessagecontact.h
    cpp/messages/requests/content/qtdinputmessagedocument.cpp cpp/messages/requests/content/qtdinputmessagedocument.h
    cpp/messages/requests/content/qtdinputmessagelocation.cpp cpp/messages/requests/content/qtdinputmessagelocation.h
    cpp/messages/requests/content/qtdinputmessagephoto.cpp cpp/messages/requests/content/qtdinputmessagephoto.h
    cpp/messages/requests/content/qtdinputmessagesticker.cpp cpp/messages/requests/content/qtdinputmessagesticker.h
    cpp/messages/requests/content/qtdinputmessagetext.cpp cpp/messages/requests/content/qtdinputmessagetext.h
    cpp/messages/requests/content/qtdinputmessagevideo.cpp cpp/messages/requests/content/qtdinputmessagevideo.h
    cpp/messages/requests/content/qtdinputmessagevoicenote.cpp cpp/messages/requests/content/qtdinputmessagevoicenote.h
    cpp/messages/requests/content/qtdinputthumbnail.cpp cpp/messages/requests/content/qtdinputthumbnail.h
    cpp/messages/requests/qtddeletemessagesrequest.cpp cpp/messages/requests/qtddeletemessagesrequest.h
    cpp/messages/requests/qtdeditmessagecaptionrequest.cpp cpp/messages/requests/qtdeditmessagecaptionrequest.h
    cpp/messages/requests/qtdeditmessagetextrequest.cpp cpp/messages/requests/qtdeditmessagetextrequest.h
    cpp/messages/requests/qtdgetchathistoryrequest.cpp cpp/messages/requests/qtdgetchathistoryrequest.h
    cpp/messages/requests/qtdgetmessagelinkrequest.cpp cpp/messages/requests/qtdgetmessagelinkrequest.h
    cpp/messages/requests/qtdgetmessagerequest.cpp cpp/messages/requests/qtdgetmessagerequest.h
    cpp/messages/requests/qtdinputmessagecontent.cpp cpp/messages/requests/qtdinputmessagecontent.h
    cpp/messages/requests/qtdinputmessagecontentattachmentcaption.cpp cpp/messages/requests/qtdinputmessagecontentattachmentcaption.h
    cpp/messages/requests/qtdinputmessagecontentfactory.cpp cpp/messages/requests/qtdinputmessagecontentfactory.h
    cpp/messages/requests/qtdmessagesendoptions.cpp cpp/messages/requests/qtdmessagesendoptions.h
    cpp/messages/requests/qtdopenmessagecontentrequest.cpp cpp/messages/requests/qtdopenmessagecontentrequest.h
    cpp/messages/requests/qtdsendmessagealbumrequest.cpp cpp/messages/requests/qtdsendmessagealbumrequest.h
    cpp/messages/requests/qtdsendmessagerequest.cpp cpp/messages/requests/qtdsendmessagerequest.h
    cpp/messages/requests/qtdsetpollanswerrequest.cpp cpp/messages/requests/qtdsetpollanswerrequest.h
    cpp/messages/requests/qtdtogglemessagesenderisblockedrequest.cpp cpp/messages/requests/qtdtogglemessagesenderisblockedrequest.h
    cpp/messages/requests/qtdviewmessagesrequest.cpp cpp/messages/requests/qtdviewmessagesrequest.h
    cpp/messages/qtdchatstate.cpp cpp/messages/qtdchatstate.h
    cpp/messages/qtddraftmessage.cpp cpp/messages/qtddraftmessage.h
    cpp/messages/qtdmessage.cpp cpp/messages/qtdmessage.h
    cpp/messages/qtdmessagecontent.cpp cpp/messages/qtdmessagecontent.h
    cpp/messages/qtdmessagecontentfactory.cpp cpp/messages/qtdmessagecontentfactory.h
    cpp/messages/qtdmessageinteractioninfo.cpp cpp/messages/qtdmessageinteractioninfo.h
    cpp/messages/qtdmessagelink.cpp cpp/messages/qtdmessagelink.h
    cpp/messages/qtdmessagelistmodel.cpp cpp/messages/qtdmessagelistmodel.h
    cpp/messages/qtdmessageschedulingstate.cpp cpp/messages/qtdmessageschedulingstate.h
    cpp/messages/qtdmessagesender.cpp cpp/messages/qtdmessagesender.h
    cpp/messages/qtdmessagesenderchat.cpp cpp/messages/qtdmessagesenderchat.h
    cpp/messages/qtdmessagesenderuser.cpp cpp/messages/qtdmessagesenderuser.h
    cpp/messages/qtdmessagesendingstate.cpp cpp/messages/qtdmessagesendingstate.h
    cpp/models/QmlObjectListModel.cpp cpp/models/QmlObjectListModel.h
    cpp/models/QmlVariantListModel.cpp cpp/models/QmlVariantListModel.h
    cpp/network/requests/qtdsetnetworktype.cpp cpp/network/requests/qtdsetnetworktype.h
    cpp/network/qtdnetworktype.cpp cpp/network/qtdnetworktype.h
    cpp/notifications/qtdenablenotifications.cpp cpp/notifications/qtdenablenotifications.h
    cpp/notifications/qtdnotificationsettings.cpp cpp/notifications/qtdnotificationsettings.h
    cpp/notifications/qtdregisterdevicerequest.cpp cpp/notifications/qtdregisterdevicerequest.h
    cpp/quick/contacts.cpp cpp/quick/contacts.h
    cpp/quick/plugin.cpp cpp/quick/plugin.h
    cpp/quick/users.cpp cpp/quick/users.h
    cpp/settings/requests/qtdaddproxyrequest.cpp cpp/settings/requests/qtdaddproxyrequest.h
    cpp/settings/requests/qtddisableproxyrequest.cpp cpp/settings/requests/qtddisableproxyrequest.h
    cpp/settings/requests/qtdeditproxyrequest.cpp cpp/settings/requests/qtdeditproxyrequest.h
    cpp/settings/requests/qtdenableproxyrequest.cpp cpp/settings/requests/qtdenableproxyrequest.h
    cpp/settings/requests/qtdgetproxiesrequest.cpp cpp/settings/requests/qtdgetproxiesrequest.h
    cpp/settings/requests/qtdpingproxyrequest.cpp cpp/settings/requests/qtdpingproxyrequest.h
    cpp/settings/requests/qtdremoveproxyrequest.cpp cpp/settings/requests/qtdremoveproxyrequest.h
    cpp/settings/qtdproxy.cpp cpp/settings/qtdproxy.h
    cpp/settings/qtdproxytype.cpp cpp/settings/qtdproxytype.h
    cpp/settings/qtdsettings.cpp cpp/settings/qtdsettings.h
    cpp/stickers/qtdstickerset.cpp cpp/stickers/qtdstickerset.h
    cpp/stickers/qtdstickersets.cpp cpp/stickers/qtdstickersets.h
    cpp/user/requests/qtdblockuserrequest.cpp cpp/user/requests/qtdblockuserrequest.h
    cpp/user/requests/qtdgetcontactsrequest.cpp cpp/user/requests/qtdgetcontactsrequest.h
    cpp/user/requests/qtdgetuserfullinforequest.cpp cpp/user/requests/qtdgetuserfullinforequest.h
    cpp/user/requests/qtdgetuserrequest.cpp cpp/user/requests/qtdgetuserrequest.h
    cpp/user/requests/qtdimportcontactsrequest.cpp cpp/user/requests/qtdimportcontactsrequest.h
    cpp/user/requests/qtdremovecontactsrequest.cpp cpp/user/requests/qtdremovecontactsrequest.h
    cpp/user/requests/qtdsearchuserbyphonenumberrequest.cpp cpp/user/requests/qtdsearchuserbyphonenumberrequest.h
    cpp/user/qtdcontact.cpp cpp/user/qtdcontact.h
    cpp/user/qtdemojistatus.cpp cpp/user/qtdemojistatus.h
    cpp/user/qtdprofilephoto.cpp cpp/user/qtdprofilephoto.h
    cpp/user/qtduser.cpp cpp/user/qtduser.h
    cpp/user/qtduserfullinfo.cpp cpp/user/qtduserfullinfo.h
    cpp/user/qtdusernames.cpp cpp/user/qtdusernames.h
    cpp/user/qtdusers.cpp cpp/user/qtdusers.h
    cpp/user/qtduserstatus.cpp cpp/user/qtduserstatus.h
    cpp/user/qtduserstatusfactory.cpp cpp/user/qtduserstatusfactory.h
    cpp/user/qtdusertype.cpp cpp/user/qtdusertype.h
    cpp/utils/asyncfuture.h cpp/utils/await.h
    cpp/utils/debug.h cpp/utils/i18n.h
    cpp/utils/qtdmediatools.cpp cpp/utils/qtdmediatools.h
    cpp/utils/qtdtextformatter.cpp cpp/utils/qtdtextformatter.h
    cpp/auxdb/auxdb.cpp cpp/auxdb/auxdb.h
    cpp/auxdb/avatarmaptable.cpp cpp/auxdb/avatarmaptable.h
    cpp/auxdb/postal-client.cpp cpp/auxdb/postal-client.h
RESOURCES
    cpp/utils/tlparser.py
)

set_target_properties(QuixTd PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_compile_definitions(QuixTd
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(QuixTd
    PRIVATE Qt6::Core Qt6::Quick Qt6::Widgets Qt6::Qml Qt6::Concurrent Qt6::Positioning Qt6::Multimedia
    PUBLIC Td::tdjson Td::tdapi
)

target_include_directories(QuixTd PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Internal include directory.
include_directories(cpp)
