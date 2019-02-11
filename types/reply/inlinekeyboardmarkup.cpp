#include "types/reply/inlinekeyboardmarkup.h"

namespace Telegram {

QJsonObject InlineKeyboardButton::toJsonObject() const
{
    QJsonObject object;
    object.insert("text", text);
    if (!url.isEmpty())
        object.insert("url", url);
    if (!callback_data.isEmpty())
        object.insert("callback_data", callback_data);
    if (!switch_inline_query.isEmpty())
        object.insert("switch_inline_query", switch_inline_query);
    if (!switch_inline_query_current_chat.isEmpty())
        object.insert("switch_inline_query_current_chat", switch_inline_query_current_chat);

    return object;
}

void InlineKeyboardMarkup::addButton(const InlineKeyboardButton& button)
{
    InlineKeyboardButtonRow row;
    row.append(button);
    m_buttons.append(row);
}

void InlineKeyboardMarkup::addButton(const InlineKeyboardButton& button, int row, int column)
{
    int rows = m_buttons.count();
    if (row >= rows) {//Insert new row
        InlineKeyboardButtonRow newRow;
        newRow.append(button);
        m_buttons.append(newRow);
        return;
    } else {
        int columns = m_buttons.at(row).count();
        if (column >= columns) {
            m_buttons[row].append(button);
        } else {
            m_buttons[row].insert(column,button);
        }
    }
}

QString InlineKeyboardMarkup::serialize() const
{
    QJsonObject o = QJsonObject();

    QJsonArray rows;
    for (auto row : m_buttons) {
        QJsonArray rowJson;
        for (auto item : row)
            rowJson.push_back(item.toJsonObject());
        rows.push_back(rowJson);
    }

    o["inline_keyboard"] = rows;

    return serializeJson(o);
}

}
