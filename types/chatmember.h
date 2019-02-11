#ifndef CHATMEMBER_H
#define CHATMEMBER_H

#include "user.h"

namespace Telegram {

class ChatMember
{
public:
    ChatMember() : userRights(0x00) {}
    ChatMember(const QJsonObject& object);

    enum AccessRights {
        CanBeEdited           = 0b0000000000000001,
        CanChangeInfo         = 0b0000000000000010,
        CanPostMessages       = 0b0000000000000100,
        CanEditMessages       = 0b0000000000001000,
        CanDeleteMessages     = 0b0000000000010000,
        CanInviteUsers        = 0b0000000000100000,
        CanRestrictMembers    = 0b0000000001000000,
        CanPinMessages        = 0b0000000010000000,
        CanPromoteMembers     = 0b0000000100000000,
        CanSendMessages       = 0b0000001000000000,
        CanSendMediaMessages  = 0b0000010000000000,
        CanSendOtherMessages  = 0b0000100000000000,
        CanAddWebPagePreviews = 0b0001000000000000
    };

    enum Status {
        Creator,Administrator,Member,Restricted,Left,Kicked
    };

    User user;
    QString status;

    quint16 userRights;
};

}

#endif // CHATMEMBER_H
