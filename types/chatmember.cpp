#include "types/chatmember.h"

namespace Telegram {

ChatMember::ChatMember(const QJsonObject& object)
    : userRights(0b0000000000000000)
{
    user = User(object.value("user").toObject());
    status = object.value("status").toString();

    //Administrators only
    if (object.value("can_be_edited").toBool())
        userRights |= CanBeEdited;

    if (object.value("can_change_info").toBool())
        userRights |= CanChangeInfo;
    if (object.value("can_post_messages").toBool())
        userRights |= CanPostMessages;
    if (object.value("can_edit_messages").toBool())
        userRights |= CanEditMessages;
    if (object.value("can_delete_messages").toBool())
        userRights |= CanDeleteMessages;
    if (object.value("can_invite_users").toBool())
        userRights |= CanInviteUsers;
    if (object.value("can_restrict_members").toBool())
        userRights |= CanRestrictMembers;
    if (object.value("can_pin_messages").toBool())
        userRights |= CanPinMessages;
    if (object.value("can_promote_members").toBool())
        userRights |= CanPromoteMembers;

    //Restricted only
    if (object.value("can_send_messages").toBool())
        userRights |= CanSendMessages;
    if (object.value("can_send_media_messages").toBool())
        userRights |= CanSendMediaMessages;
    if (object.value("can_send_other_messages").toBool())
        userRights |= CanSendOtherMessages;
    if (object.value("can_add_web_page_previews").toBool())
        userRights |= CanAddWebPagePreviews;
}

}
