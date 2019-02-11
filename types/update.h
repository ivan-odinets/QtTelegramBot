#ifndef UPDATE_H
#define UPDATE_H

#include <QDebug>
#include <QJsonObject>
#include "callbackquery.h"
#include "message.h"

namespace Telegram {

class Update
{
public:
    //enum Type {Message,CallbackQuery};
    Update() {}
    Update(const QJsonObject& update);

    quint32 id;
    Message message;
    CallbackQuery callback;
};

inline QDebug operator<< (QDebug dbg, const Update &update)
{
    dbg.nospace() << qUtf8Printable(QString("Telegram::Update(id=%1; message=%2)")
                                    .arg(update.id)
                                    .arg("Message(" + QString::number(update.message.id) + ")"));

    return dbg.maybeSpace();
}

}

#endif // UPDATE_H
