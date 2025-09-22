cmake_minimum_required(VERSION 3.16)

project(QuixTd VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(QT_QML_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR})
set(QT_QML_GENERATE_QMLLS_INI ON)

# Don't forget to append path to tdlib in CMAKE_PREFIX_PATH!
#   Add: list(APPEND CMAKE_PREFIX_PATH "C:/path/to/tdlib")
list(APPEND CMAKE_PREFIX_PATH "C:/Users/mfaja/Documents/cpp_lib/td-1.8.54/td")
find_package(Td 1.8.54 REQUIRED)

find_package(Qt6 6.2 REQUIRED COMPONENTS Core Qml Sql Quick Concurrent Positioning Multimedia Widgets DBus)

# Qt6 QML policies (recommended)
qt_policy(SET QTP0001 NEW)
qt_policy(SET QTP0004 NEW)
qt_policy(SET QTP0005 NEW)

include(FetchContent)
FetchContent_Declare(
    asyncfuture
    GIT_REPOSITORY "https://github.com/vpicaver/asyncfuture.git"
    GIT_TAG master
)
FetchContent_MakeAvailable(asyncfuture)

# Create the library as a QML plugin
qt_add_library(QuixTd STATIC)

qt_add_qml_module(QuixTd
    URI QuixTd
    VERSION 1.0
SOURCES
    cpp/auth/requests/qx_td_auth_code_response.cpp cpp/auth/requests/qx_td_auth_code_response.h
    cpp/auth/requests/qx_td_auth_delete_account_response.cpp cpp/auth/requests/qx_td_auth_delete_account_response.h
    cpp/auth/requests/qx_td_auth_encryption_key_response.cpp cpp/auth/requests/qx_td_auth_encryption_key_response.h
    cpp/auth/requests/qx_td_auth_logout_response.cpp cpp/auth/requests/qx_td_auth_logout_response.h
    cpp/auth/requests/qx_td_auth_parameters_response.cpp cpp/auth/requests/qx_td_auth_parameters_response.h
    cpp/auth/requests/qx_td_auth_password_response.cpp cpp/auth/requests/qx_td_auth_password_response.h
    cpp/auth/requests/qx_td_auth_phone_number_response.cpp cpp/auth/requests/qx_td_auth_phone_number_response.h
    cpp/auth/requests/qx_td_auth_registration_response.cpp cpp/auth/requests/qx_td_auth_registration_response.h
    cpp/auth/requests/qx_td_auth_resend_code_request.cpp cpp/auth/requests/qx_td_auth_resend_code_request.h
    cpp/auth/qx_td_auth_code.cpp cpp/auth/qx_td_auth_code.h
    cpp/auth/qx_td_auth_manager.cpp cpp/auth/qx_td_auth_manager.h
    cpp/auth/qx_td_auth_params.cpp cpp/auth/qx_td_auth_params.h
    cpp/auth/qx_td_auth_state.cpp cpp/auth/qx_td_auth_state.h
    cpp/auth/qx_td_auth_state_factory.cpp cpp/auth/qx_td_auth_state_factory.h
    cpp/call/qx_td_call_discard_reason.cpp cpp/call/qx_td_call_discard_reason.h
    cpp/chat/requests/qx_td_chat_report_reason.cpp cpp/chat/requests/qx_td_chat_report_reason.h
    cpp/chat/requests/qx_td_check_chat_invite_link_request.cpp cpp/chat/requests/qx_td_check_chat_invite_link_request.h
    cpp/chat/requests/qx_td_close_chat_request.cpp cpp/chat/requests/qx_td_close_chat_request.h
    cpp/chat/requests/qx_td_close_secret_chat_request.cpp cpp/chat/requests/qx_td_close_secret_chat_request.h
    cpp/chat/requests/qx_td_create_new_secret_chat_request.cpp cpp/chat/requests/qx_td_create_new_secret_chat_request.h
    cpp/chat/requests/qx_td_create_private_chat_request.cpp cpp/chat/requests/qx_td_create_private_chat_request.h
    cpp/chat/requests/qx_td_delete_chat_history_request.cpp cpp/chat/requests/qx_td_delete_chat_history_request.h
    cpp/chat/requests/qx_td_forward_messages_request.cpp cpp/chat/requests/qx_td_forward_messages_request.h
    cpp/chat/requests/qx_td_get_basic_group_request.cpp cpp/chat/requests/qx_td_get_basic_group_request.h
    cpp/chat/requests/qx_td_get_chat_request.cpp cpp/chat/requests/qx_td_get_chat_request.h
    cpp/chat/requests/qx_td_get_chats_request.cpp cpp/chat/requests/qx_td_get_chats_request.h
    cpp/chat/requests/qx_td_get_secret_chat_request.cpp cpp/chat/requests/qx_td_get_secret_chat_request.h
    cpp/chat/requests/qx_td_get_super_group_full_info_request.cpp cpp/chat/requests/qx_td_get_super_group_full_info_request.h
    cpp/chat/requests/qx_td_get_super_group_request.cpp cpp/chat/requests/qx_td_get_super_group_request.h
    cpp/chat/requests/qx_td_join_chat_by_invite_link_request.cpp cpp/chat/requests/qx_td_join_chat_by_invite_link_request.h
    cpp/chat/requests/qx_td_join_chat_request.cpp cpp/chat/requests/qx_td_join_chat_request.h
    cpp/chat/requests/qx_td_leave_chat_request.cpp cpp/chat/requests/qx_td_leave_chat_request.h
    cpp/chat/requests/qx_td_load_chats_request.cpp cpp/chat/requests/qx_td_load_chats_request.h
    cpp/chat/requests/qx_td_open_chat_request.cpp cpp/chat/requests/qx_td_open_chat_request.h
    cpp/chat/requests/qx_td_report_chat_request.cpp cpp/chat/requests/qx_td_report_chat_request.h
    cpp/chat/requests/qx_td_search_chat_messages_request.cpp cpp/chat/requests/qx_td_search_chat_messages_request.h
    cpp/chat/requests/qx_td_search_public_chat_request.cpp cpp/chat/requests/qx_td_search_public_chat_request.h
    cpp/chat/requests/qx_td_send_chat_action_request.cpp cpp/chat/requests/qx_td_send_chat_action_request.h
    cpp/chat/requests/qx_td_set_chat_draft_request.cpp cpp/chat/requests/qx_td_set_chat_draft_request.h
    cpp/chat/requests/qx_td_set_chat_message_ttl_request.cpp cpp/chat/requests/qx_td_set_chat_message_ttl_request.h
    cpp/chat/requests/qx_td_set_chat_notification_settings.cpp cpp/chat/requests/qx_td_set_chat_notification_settings.h
    cpp/chat/requests/qx_td_set_chat_title_request.cpp cpp/chat/requests/qx_td_set_chat_title_request.h
    cpp/chat/requests/qx_td_set_pinned_chats_request.cpp cpp/chat/requests/qx_td_set_pinned_chats_request.h
    cpp/chat/qx_td_basic_group_chat.cpp cpp/chat/qx_td_basic_group_chat.h
    cpp/chat/qx_td_chat.cpp cpp/chat/qx_td_chat.h
    cpp/chat/qx_td_chat_action.cpp cpp/chat/qx_td_chat_action.h
    cpp/chat/qx_td_chat_action_bar.cpp cpp/chat/qx_td_chat_action_bar.h
    cpp/chat/qx_td_chat_action_factory.cpp cpp/chat/qx_td_chat_action_factory.h
    cpp/chat/qx_td_chat_administrator_rights.cpp cpp/chat/qx_td_chat_administrator_rights.h
    cpp/chat/qx_td_chat_invite_link_info.cpp cpp/chat/qx_td_chat_invite_link_info.h
    cpp/chat/qx_td_chat_list.cpp cpp/chat/qx_td_chat_list.h
    cpp/chat/qx_td_chat_list_model.cpp cpp/chat/qx_td_chat_list_model.h
    cpp/chat/qx_td_chat_list_sort_filter_model.cpp cpp/chat/qx_td_chat_list_sort_filter_model.h
    cpp/chat/qx_td_chat_member.cpp cpp/chat/qx_td_chat_member.h
    cpp/chat/qx_td_chat_member_status.cpp cpp/chat/qx_td_chat_member_status.h
    cpp/chat/qx_td_chat_permissions.cpp cpp/chat/qx_td_chat_permissions.h
    cpp/chat/qx_td_chat_position.cpp cpp/chat/qx_td_chat_position.h
    cpp/chat/qx_td_chat_type.cpp cpp/chat/qx_td_chat_type.h
    cpp/chat/qx_td_chat_type_factory.cpp cpp/chat/qx_td_chat_type_factory.h
    cpp/chat/qx_td_secret_chat.cpp cpp/chat/qx_td_secret_chat.h
    cpp/chat/qx_td_secret_chat_state.cpp cpp/chat/qx_td_secret_chat_state.h
    cpp/chat/qx_td_super_group_chat.cpp cpp/chat/qx_td_super_group_chat.h
    cpp/client/requests/qx_td_close_request.cpp cpp/client/requests/qx_td_close_request.h
    cpp/client/qx_td_client.cpp cpp/client/qx_td_client.h
    cpp/client/qx_td_handle.cpp cpp/client/qx_td_handle.h
    cpp/client/qx_td_thread.cpp cpp/client/qx_td_thread.h
    cpp/common/qx_abstract_int64_id.cpp cpp/common/qx_abstract_int64_id.h
    cpp/common/qx_td_object.cpp cpp/common/qx_td_object.h
    cpp/common/qx_td_helpers.cpp cpp/common/qx_td_helpers.h
    cpp/common/qx_td_int.cpp cpp/common/qx_td_int.h
    cpp/common/qx_td_request.cpp cpp/common/qx_td_request.h
    cpp/common/qx_td_response.cpp cpp/common/qx_td_response.h
    cpp/connections/qx_td_connection_manager.cpp cpp/connections/qx_td_connection_manager.h
    cpp/connections/qx_td_connection_state.cpp cpp/connections/qx_td_connection_state.h
    cpp/connections/qx_td_connection_state_factory.cpp cpp/connections/qx_td_connection_state_factory.h
    cpp/files/sticker/qx_td_sticker_format.cpp cpp/files/sticker/qx_td_sticker_format.h
    cpp/files/sticker/qx_td_sticker_type.cpp cpp/files/sticker/qx_td_sticker_type.h
    cpp/files/qx_td_animation.cpp cpp/files/qx_td_animation.h
    cpp/files/qx_td_audio.cpp cpp/files/qx_td_audio.h
    cpp/files/qx_td_document.cpp cpp/files/qx_td_document.h
    cpp/files/qx_td_download_file_request.cpp cpp/files/qx_td_download_file_request.h
    cpp/files/qx_td_file.cpp cpp/files/qx_td_file.h
    cpp/files/qx_td_local_file.cpp cpp/files/qx_td_local_file.h
    cpp/files/qx_td_mini_thumbnail.cpp cpp/files/qx_td_mini_thumbnail.h
    cpp/files/qx_td_photo.cpp cpp/files/qx_td_photo.h
    cpp/files/qx_td_photos.cpp cpp/files/qx_td_photos.h
    cpp/files/qx_td_photo_size.cpp cpp/files/qx_td_photo_size.h
    cpp/files/qx_td_remote_file.cpp cpp/files/qx_td_remote_file.h
    cpp/files/qx_td_sticker.cpp cpp/files/qx_td_sticker.h
    cpp/files/qx_td_thumbnail.cpp cpp/files/qx_td_thumbnail.h
    cpp/files/qx_td_thumbnail_format.cpp cpp/files/qx_td_thumbnail_format.h
    cpp/files/qx_td_video.cpp cpp/files/qx_td_video.h
    cpp/files/qx_td_video_note.cpp cpp/files/qx_td_video_note.h
    cpp/files/qx_td_voice_note.cpp cpp/files/qx_td_voice_note.h
    cpp/messages/content/qx_td_formatted_text.cpp cpp/messages/content/qx_td_formatted_text.h
    cpp/messages/content/qx_td_location.cpp cpp/messages/content/qx_td_location.h
    cpp/messages/content/qx_td_message_animation.cpp cpp/messages/content/qx_td_message_animation.h
    cpp/messages/content/qx_td_message_audio.cpp cpp/messages/content/qx_td_message_audio.h
    cpp/messages/content/qx_td_message_basic_group_chat_create.cpp cpp/messages/content/qx_td_message_basic_group_chat_create.h
    cpp/messages/content/qx_td_message_call.cpp cpp/messages/content/qx_td_message_call.h
    cpp/messages/content/qx_td_message_chat_add_members.cpp cpp/messages/content/qx_td_message_chat_add_members.h
    cpp/messages/content/qx_td_message_chat_change_photo.cpp cpp/messages/content/qx_td_message_chat_change_photo.h
    cpp/messages/content/qx_td_message_chat_change_title.cpp cpp/messages/content/qx_td_message_chat_change_title.h
    cpp/messages/content/qx_td_message_chat_delete_member.cpp cpp/messages/content/qx_td_message_chat_delete_member.h
    cpp/messages/content/qx_td_message_chat_delete_photo.cpp cpp/messages/content/qx_td_message_chat_delete_photo.h
    cpp/messages/content/qx_td_message_chat_join_by_link.cpp cpp/messages/content/qx_td_message_chat_join_by_link.h
    cpp/messages/content/qx_td_message_chat_set_message_auto_delete_time.cpp cpp/messages/content/qx_td_message_chat_set_message_auto_delete_time.h
    cpp/messages/content/qx_td_message_chat_upgrade_from.cpp cpp/messages/content/qx_td_message_chat_upgrade_from.h
    cpp/messages/content/qx_td_message_chat_upgrade_to.cpp cpp/messages/content/qx_td_message_chat_upgrade_to.h
    cpp/messages/content/qx_td_message_contact.cpp cpp/messages/content/qx_td_message_contact.h
    cpp/messages/content/qx_td_message_contact_registered.cpp cpp/messages/content/qx_td_message_contact_registered.h
    cpp/messages/content/qx_td_message_custom_service_action.cpp cpp/messages/content/qx_td_message_custom_service_action.h
    cpp/messages/content/qx_td_message_date.cpp cpp/messages/content/qx_td_message_date.h
    cpp/messages/content/qx_td_message_document.cpp cpp/messages/content/qx_td_message_document.h
    cpp/messages/content/qx_td_message_location.cpp cpp/messages/content/qx_td_message_location.h
    cpp/messages/content/qx_td_message_photo.cpp cpp/messages/content/qx_td_message_photo.h
    cpp/messages/content/qx_td_message_pin_message.cpp cpp/messages/content/qx_td_message_pin_message.h
    cpp/messages/content/qx_td_message_poll.cpp cpp/messages/content/qx_td_message_poll.h
    cpp/messages/content/qx_td_message_screenshot_taken.cpp cpp/messages/content/qx_td_message_screenshot_taken.h
    cpp/messages/content/qx_td_message_sticker.cpp cpp/messages/content/qx_td_message_sticker.h
    cpp/messages/content/qx_td_message_super_group_chat_create.cpp cpp/messages/content/qx_td_message_super_group_chat_create.h
    cpp/messages/content/qx_td_message_text.cpp cpp/messages/content/qx_td_message_text.h
    cpp/messages/content/qx_td_message_unread_label.cpp cpp/messages/content/qx_td_message_unread_label.h
    cpp/messages/content/qx_td_message_unsupported.cpp cpp/messages/content/qx_td_message_unsupported.h
    cpp/messages/content/qx_td_message_video.cpp cpp/messages/content/qx_td_message_video.h
    cpp/messages/content/qx_td_message_video_note.cpp cpp/messages/content/qx_td_message_video_note.h
    cpp/messages/content/qx_td_message_voice_note.cpp cpp/messages/content/qx_td_message_voice_note.h
    cpp/messages/content/qx_td_poll.cpp cpp/messages/content/qx_td_poll.h
    cpp/messages/content/qx_td_poll_option.cpp cpp/messages/content/qx_td_poll_option.h
    cpp/messages/content/qx_td_poll_type.cpp cpp/messages/content/qx_td_poll_type.h
    cpp/messages/content/qx_td_text_entity.cpp cpp/messages/content/qx_td_text_entity.h
    cpp/messages/content/qx_td_text_entity_type.cpp cpp/messages/content/qx_td_text_entity_type.h
    cpp/messages/content/qx_td_web_page.cpp cpp/messages/content/qx_td_web_page.h
    cpp/messages/forwardinfo/qx_td_message_forward_info.cpp cpp/messages/forwardinfo/qx_td_message_forward_info.h
    cpp/messages/forwardinfo/qx_td_message_forward_origin.cpp cpp/messages/forwardinfo/qx_td_message_forward_origin.h
    cpp/messages/forwardinfo/qx_td_message_forward_origin_factory.cpp cpp/messages/forwardinfo/qx_td_message_forward_origin_factory.h
    cpp/messages/replymarkup/qx_td_keyboard_button.cpp cpp/messages/replymarkup/qx_td_keyboard_button.h
    cpp/messages/replymarkup/qx_td_keyboard_button_type.cpp cpp/messages/replymarkup/qx_td_keyboard_button_type.h
    cpp/messages/replymarkup/qx_td_reply_markup.cpp cpp/messages/replymarkup/qx_td_reply_markup.h
    cpp/messages/requests/content/imessageattachmentcontent.h cpp/messages/requests/content/imessagecaptioncontent.h
    cpp/messages/requests/content/qx_td_input_message_audio.cpp cpp/messages/requests/content/qx_td_input_message_audio.h
    cpp/messages/requests/content/qx_td_input_message_contact.cpp cpp/messages/requests/content/qx_td_input_message_contact.h
    cpp/messages/requests/content/qx_td_input_message_document.cpp cpp/messages/requests/content/qx_td_input_message_document.h
    cpp/messages/requests/content/qx_td_input_message_location.cpp cpp/messages/requests/content/qx_td_input_message_location.h
    cpp/messages/requests/content/qx_td_input_message_photo.cpp cpp/messages/requests/content/qx_td_input_message_photo.h
    cpp/messages/requests/content/qx_td_input_message_sticker.cpp cpp/messages/requests/content/qx_td_input_message_sticker.h
    cpp/messages/requests/content/qx_td_input_message_text.cpp cpp/messages/requests/content/qx_td_input_message_text.h
    cpp/messages/requests/content/qx_td_input_message_video.cpp cpp/messages/requests/content/qx_td_input_message_video.h
    cpp/messages/requests/content/qx_td_input_message_voice_note.cpp cpp/messages/requests/content/qx_td_input_message_voice_note.h
    cpp/messages/requests/content/qx_td_input_thumbnail.cpp cpp/messages/requests/content/qx_td_input_thumbnail.h
    cpp/messages/requests/qx_td_delete_messages_request.cpp cpp/messages/requests/qx_td_delete_messages_request.h
    cpp/messages/requests/qx_td_edit_message_caption_request.cpp cpp/messages/requests/qx_td_edit_message_caption_request.h
    cpp/messages/requests/qx_td_edit_message_text_request.cpp cpp/messages/requests/qx_td_edit_message_text_request.h
    cpp/messages/requests/qx_td_get_chat_history_request.cpp cpp/messages/requests/qx_td_get_chat_history_request.h
    cpp/messages/requests/qx_td_get_message_link_request.cpp cpp/messages/requests/qx_td_get_message_link_request.h
    cpp/messages/requests/qx_td_get_message_request.cpp cpp/messages/requests/qx_td_get_message_request.h
    cpp/messages/requests/qx_td_input_message_content.cpp cpp/messages/requests/qx_td_input_message_content.h
    cpp/messages/requests/qx_td_input_message_content_attachment_caption.cpp cpp/messages/requests/qx_td_input_message_content_attachment_caption.h
    cpp/messages/requests/qx_td_input_message_content_factory.cpp cpp/messages/requests/qx_td_input_message_content_factory.h
    cpp/messages/requests/qx_td_message_send_options.cpp cpp/messages/requests/qx_td_message_send_options.h
    cpp/messages/requests/qx_td_open_message_content_request.cpp cpp/messages/requests/qx_td_open_message_content_request.h
    cpp/messages/requests/qx_td_send_message_album_request.cpp cpp/messages/requests/qx_td_send_message_album_request.h
    cpp/messages/requests/qx_td_send_message_request.cpp cpp/messages/requests/qx_td_send_message_request.h
    cpp/messages/requests/qx_td_set_poll_answer_request.cpp cpp/messages/requests/qx_td_set_poll_answer_request.h
    cpp/messages/requests/qx_td_toggle_message_sender_is_blocked_request.cpp cpp/messages/requests/qx_td_toggle_message_sender_is_blocked_request.h
    cpp/messages/requests/qx_td_view_messages_request.cpp cpp/messages/requests/qx_td_view_messages_request.h
    cpp/messages/qx_td_chat_state.cpp cpp/messages/qx_td_chat_state.h
    cpp/messages/qx_td_draft_message.cpp cpp/messages/qx_td_draft_message.h
    cpp/messages/qx_td_message.cpp cpp/messages/qx_td_message.h
    cpp/messages/qx_td_message_content.cpp cpp/messages/qx_td_message_content.h
    cpp/messages/qx_td_message_content_factory.cpp cpp/messages/qx_td_message_content_factory.h
    cpp/messages/qx_td_message_interaction_info.cpp cpp/messages/qx_td_message_interaction_info.h
    cpp/messages/qx_td_message_link.cpp cpp/messages/qx_td_message_link.h
    cpp/messages/qx_td_message_list_model.cpp cpp/messages/qx_td_message_list_model.h
    cpp/messages/qx_td_message_scheduling_state.cpp cpp/messages/qx_td_message_scheduling_state.h
    cpp/messages/qx_td_message_sender.cpp cpp/messages/qx_td_message_sender.h
    cpp/messages/qx_td_message_sender_chat.cpp cpp/messages/qx_td_message_sender_chat.h
    cpp/messages/qx_td_message_sender_user.cpp cpp/messages/qx_td_message_sender_user.h
    cpp/messages/qx_td_message_sending_state.cpp cpp/messages/qx_td_message_sending_state.h
    cpp/models/qx_td_object_list_model.cpp cpp/models/qx_td_object_list_model.h
    cpp/models/qx_td_variant_list_model.cpp cpp/models/qx_td_variant_list_model.h
    cpp/network/requests/qx_td_set_network_type.cpp cpp/network/requests/qx_td_set_network_type.h
    cpp/network/qx_td_network_type.cpp cpp/network/qx_td_network_type.h
    cpp/notifications/qx_td_enable_notifications.cpp cpp/notifications/qx_td_enable_notifications.h
    cpp/notifications/qx_td_notification_settings.cpp cpp/notifications/qx_td_notification_settings.h
    cpp/notifications/qx_td_register_device_request.cpp cpp/notifications/qx_td_register_device_request.h
    cpp/quick/qx_contacts.cpp cpp/quick/qx_contacts.h
    cpp/quick/plugin_reference.cpp cpp/quick/plugin_reference.h
    cpp/quick/qx_users.cpp cpp/quick/qx_users.h
    cpp/settings/requests/qx_td_add_proxy_request.cpp cpp/settings/requests/qx_td_add_proxy_request.h
    cpp/settings/requests/qx_td_disable_proxy_request.cpp cpp/settings/requests/qx_td_disable_proxy_request.h
    cpp/settings/requests/qx_td_edit_proxy_request.cpp cpp/settings/requests/qx_td_edit_proxy_request.h
    cpp/settings/requests/qx_td_enable_proxy_request.cpp cpp/settings/requests/qx_td_enable_proxy_request.h
    cpp/settings/requests/qx_td_get_proxies_request.cpp cpp/settings/requests/qx_td_get_proxies_request.h
    cpp/settings/requests/qx_td_ping_proxy_request.cpp cpp/settings/requests/qx_td_ping_proxy_request.h
    cpp/settings/requests/qx_td_remove_proxy_request.cpp cpp/settings/requests/qx_td_remove_proxy_request.h
    cpp/settings/qx_td_proxy.cpp cpp/settings/qx_td_proxy.h
    cpp/settings/qx_td_proxy_type.cpp cpp/settings/qx_td_proxy_type.h
    cpp/settings/qx_td_settings.cpp cpp/settings/qx_td_settings.h
    cpp/stickers/qx_td_sticker_set.cpp cpp/stickers/qx_td_sticker_set.h
    cpp/stickers/qx_td_sticker_sets.cpp cpp/stickers/qx_td_sticker_sets.h
    cpp/user/requests/qx_td_block_user_request.cpp cpp/user/requests/qx_td_block_user_request.h
    cpp/user/requests/qx_td_get_contacts_request.cpp cpp/user/requests/qx_td_get_contacts_request.h
    cpp/user/requests/qx_td_get_user_full_info_request.cpp cpp/user/requests/qx_td_get_user_full_info_request.h
    cpp/user/requests/qx_td_get_user_request.cpp cpp/user/requests/qx_td_get_user_request.h
    cpp/user/requests/qx_td_import_contacts_request.cpp cpp/user/requests/qx_td_import_contacts_request.h
    cpp/user/requests/qx_td_remove_contacts_request.cpp cpp/user/requests/qx_td_remove_contacts_request.h
    cpp/user/requests/qx_td_search_user_by_phone_number_request.cpp cpp/user/requests/qx_td_search_user_by_phone_number_request.h
    cpp/user/qx_td_contact.cpp cpp/user/qx_td_contact.h
    cpp/user/qx_td_emoji_status.cpp cpp/user/qx_td_emoji_status.h
    cpp/user/qx_td_profile_photo.cpp cpp/user/qx_td_profile_photo.h
    cpp/user/qx_td_user.cpp cpp/user/qx_td_user.h
    cpp/user/qx_td_user_full_info.cpp cpp/user/qx_td_user_full_info.h
    cpp/user/qx_td_usernames.cpp cpp/user/qx_td_usernames.h
    cpp/user/qx_td_users.cpp cpp/user/qx_td_users.h
    cpp/user/qx_td_user_status.cpp cpp/user/qx_td_user_status.h
    cpp/user/qx_td_user_status_factory.cpp cpp/user/qx_td_user_status_factory.h
    cpp/user/qx_td_user_type.cpp cpp/user/qx_td_user_type.h
    cpp/utils/qx_td_await.h
    cpp/utils/debug.h cpp/utils/qx_td_translate_tools.h
    cpp/utils/qx_td_media_tools.cpp cpp/utils/qx_td_media_tools.h
    cpp/utils/qx_td_text_formatter.cpp cpp/utils/qx_td_text_formatter.h
    cpp/auxdb/auxdb.cpp cpp/auxdb/auxdb.h
    cpp/auxdb/avatarmaptable.cpp cpp/auxdb/avatarmaptable.h
    cpp/auxdb/postal-client.cpp cpp/auxdb/postal-client.h
RESOURCES
    cpp/utils/tlparser.py
)

set_target_properties(QuixTd PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER quixtd
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_compile_definitions(QuixTd
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

# Link dependencies
target_link_libraries(QuixTd
    PRIVATE
        Qt6::Concurrent
        Qt6::Core
        Qt6::DBus
        Qt6::Multimedia
        Qt6::Positioning
        Qt6::Qml
        Qt6::Quick
        Qt6::Sql
        Qt6::Widgets
        Td::tdjson
        Td::tdapi
        asyncfuture
)

# Public headers (if other projects will use them)
target_include_directories(QuixTd PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/cpp)

# Internal include directory.
include_directories(cpp)
include_directories(cpp/auth)
include_directories(cpp/call)
include_directories(cpp/chat)
include_directories(cpp/client)
include_directories(cpp/common)
include_directories(cpp/connections)
include_directories(cpp/files)
include_directories(cpp/messages)
include_directories(cpp/messages/content)
include_directories(cpp/models)
include_directories(cpp/network)
include_directories(cpp/notifications)
include_directories(cpp/quick)
include_directories(cpp/settings)
include_directories(cpp/stickers)
include_directories(cpp/user)
include_directories(cpp/utils)
