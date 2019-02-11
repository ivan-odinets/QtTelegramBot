#ifndef CALLBACKQUERY_H
#define CALLBACKQUERY_H

#include <QDebug>
#include <QString>
#include <QJsonObject>

#include "message.h"
#include "user.h"

namespace Telegram {

class CallbackQuery
{
public:
    CallbackQuery() {}
    CallbackQuery(const QJsonObject& callback);

    QString	id;
    User from;
    Message	message;
    QString inline_message_id;
    QString chat_instance;
    QString data;
    QString game_short_name;
};

inline QDebug operator<< (QDebug dbg, const CallbackQuery& callback)
{
    dbg.nospace() << qUtf8Printable(QString("Telegram::CallbackQuery(id=%1; from.id=%2; data=%3)")
                                    .arg(callback.id)
                                    .arg(callback.from.id)
                                    .arg(callback.data));

    return dbg.maybeSpace();
}

}

#endif // CALLBACKQUERY_H
