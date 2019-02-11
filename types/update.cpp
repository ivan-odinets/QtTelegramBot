#include "update.h"

using namespace Telegram;

Update::Update(const QJsonObject& update)
{
    id = update.value("update_id").toInt();
    if (update.contains("callback_query"))
        callback = CallbackQuery(update.value("callback_query").toObject());
    else if (update.contains("message"))
        message = Message(update.value("message").toObject());
}
