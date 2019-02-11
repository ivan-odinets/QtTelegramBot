#include "callbackquery.h"

namespace Telegram {

CallbackQuery::CallbackQuery(const QJsonObject& callback)
{
    id = callback.value("id").toString();
    from = User(callback.value("from").toObject());

    if (callback.contains("message"))
        message = Message(callback.value("message").toObject());
    if (callback.contains("inline_message_id"))
        inline_message_id = callback.value("inline_message_id").toString();
    chat_instance = callback.value("chat_instance").toString();
    if (callback.contains("data"))
        data = callback.value("data").toString();
    if (callback.contains("game_short_name"))
        game_short_name = callback.value("game_short_name").toString();
}

}
