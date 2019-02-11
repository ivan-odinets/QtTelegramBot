#ifndef INLINEKEYBOARDMARKUP_H
#define INLINEKEYBOARDMARKUP_H

#include <QList>
#include <QString>

#include "genericreply.h"

namespace Telegram {

class InlineKeyboardButton
{
public:
    InlineKeyboardButton(QString text, QString url = QString(), QString callback_data = QString(), QString switch_inline_query = QString(), QString switch_inline_query_current_chat = QString())
        : text(text),
          url(url),
          callback_data(callback_data),
          switch_inline_query(switch_inline_query),
          switch_inline_query_current_chat(switch_inline_query_current_chat)
    {}
    /**
     * @text - Label text on the button
     */
    QString text;

    /**
     * @url - Optional. HTTP url to be opened when button is pressed
     */
    QString url;

    /**
     * @callback_data - Optional. Data to be sent in a callback query to the bot when button is pressed, 1-64 bytes
     */
    QString callback_data;

    /**
     * @switch_inline_query - Optional. If set, pressing the button will prompt the user to select one of their chats, open that chat and insert the bot‘s username and the specified inline query in the input field.
     * Can be empty, in which case just the bot’s username will be inserted.
     */
    QString switch_inline_query;

    /**
     * @switch_inline_query_current_chat - Optional. If set, pressing the button will insert the bot‘s username and the specified inline query in the current chat's input field.
     * Can be empty, in which case only the bot’s username will be inserted.
     */
    QString switch_inline_query_current_chat;

    QJsonObject toJsonObject() const;
};

typedef QList<InlineKeyboardButton> InlineKeyboardButtonRow;

class InlineKeyboardMarkup : public GenericReply
{
public:
    InlineKeyboardMarkup()
        : GenericReply(false) {}

    void addButton(const InlineKeyboardButton& button);
    void addButton(const InlineKeyboardButton& button,int row, int column);
    void addButtonRow(const InlineKeyboardButtonRow& row)
        { m_buttons.append(row); }

    virtual QString serialize() const;

private:
    QList<InlineKeyboardButtonRow> m_buttons;
};

}

#endif // INLINEKEYBOARDMARKUP_H
