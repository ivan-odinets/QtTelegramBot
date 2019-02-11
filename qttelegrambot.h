#ifndef QTTELEGRAMBOT_H
#define QTTELEGRAMBOT_H

#include <QObject>
#include <QLoggingCategory>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QHttpPart>
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QMimeDatabase>
#include <QTimer>

#include "networking.h"
#include "types/chat.h"
#include "types/update.h"
#include "types/user.h"
#include "types/file.h"
#include "types/message.h"
#include "types/chatmember.h"
#include "types/callbackquery.h"
#include "types/reply/genericreply.h"
#include "types/reply/inlinekeyboardmarkup.h"
#include "types/reply/replykeyboardmarkup.h"
#include "types/reply/replykeyboardhide.h"
#include "types/reply/forcereply.h"

namespace Telegram {

typedef QList<QList<PhotoSize> > UserProfilePhotos;

class Bot : public QObject
{
    Q_OBJECT
public:
    /**
     * Bot constructor
     * @param token
     * @param updates - enable automatic update polling
     * @param updateInterval - interval between update polls in msec
     * @param pollingTimeout - timeout in sec
     * @param parent
     */
    explicit Bot(const QString& token, bool updates = false, quint32 updateInterval = 1000, quint32 pollingTimeout = 0, QObject *parent = 0);
    ~Bot();

    enum ChatAction { Typing, UploadingPhoto, RecordingVideo, UploadingVideo, RecordingAudio, UploadingAudio, UploadingDocument, FindingLocation };

    /**
     * Returns basic information about the bot in form of a `User` object.
     * @return User Object
     * @see https://core.telegram.org/bots/api#getme
     */
    User getMe();

    /**
     * Use this method to get up to date information about the chat.
     * @param chatId
     * @return Chat Object
     * @see https://core.telegram.org/bots/api#getchat
     */
    Chat getChat(const QVariant& chatId);

    /**
     * Use this method to get information about a member of a chat.
     * @param chatId
     * @param userId
     * @return ChatMember Object
     * @see https://core.telegram.org/bots/api#getchatmember
     */
    ChatMember getChatMember(const QVariant& chatId,qint32 userId);

    /**
     * Send text message.
     * @param chatId - Unique identifier for the message recipient or @channelname
     * @param text - Text of the message to be sent
     * @param markdown - Use markdown in message display (only Telegram for Android supports this)
     * @param disableWebPagePreview - Disables link previews for links in this message
     * @param replyToMessageId - If the message is a reply, ID of the original message
     * @param replyMarkup - Additional interface options
     * @return success
     * @see https://core.telegram.org/bots/api#sendmessage
     */
    bool sendMessage(const QVariant& chatId, const QString& text, bool markdown = false, bool disableWebPagePreview = false, qint32 replyToMessageId = -1, const GenericReply &replyMarkup = GenericReply());

    /**
     * Forward messages of any kind.
     * @param chatId - Unique identifier for the message recipient or @channelname
     * @param fromChatId - Unique identifier for the chat where the original message was sent
     * @param messageId - Unique message identifier
     * @return success
     * @see https://core.telegram.org/bots/api#forwardmessage
     */
    bool forwardMessage(const QVariant& chatId, quint32 fromChatId, quint32 messageId);

    /**
     * Delete messages.
     * @param chatId - Unique identifier for the message recipient or @channelname
     * @param messageId - Unique message identifier
     * @return success
     * @see https://core.telegram.org/bots/api#deletemessage
     */
    bool deleteMessage(const QVariant& chatId,quint32 id);

    /**
     * Send a photo
     * @param chatId - Unique identifier for the message recipient or @channelname
     * @param file - A file to send
     * @param caption - Photo caption
     * @param replyToMessageId - If the message is a reply, ID of the original message
     * @param replyMarkup - Additional interface options
     * @return success
     * @see https://core.telegram.org/bots/api#sendphoto
     */
    bool sendPhoto(const QVariant& chatId, QFile *file, const QString& caption = QString(), qint32 replyToMessageId = -1, const GenericReply &replyMarkup = GenericReply());

    /**
     * Send a photo
     * @param chatId - Unique identifier for the message recipient or @channelname
     * @param fileId - Telegram file_id of already sent photo
     * @param caption - Photo caption
     * @param replyToMessageId - If the message is a reply, ID of the original message
     * @param replyMarkup - Additional interface options
     * @return success
     * @see https://core.telegram.org/bots/api#sendphoto
     */
    bool sendPhoto(const QVariant& chatId, const QString& fileId, const QString& caption = QString(), qint32 replyToMessageId = -1, const GenericReply &replyMarkup = GenericReply());

    /**
     * Send audio
     * @param chatId - Unique identifier for the message recipient or @channelname
     * @param file - A file to send
     * @param duration - Duration of the audio in seconds
     * @param performer - Performer of the audio
     * @param title - Track name of the audio
     * @param replyToMessageId - If the message is a reply, ID of the original message
     * @param replyMarkup - Additional interface options
     * @return success
     * @see https://core.telegram.org/bots/api#sendaudio
     */
    bool sendAudio(const QVariant& chatId, QFile *file, qint64 duration = -1, const QString& performer = QString(), const QString& title = QString(), qint32 replyToMessageId = -1, const GenericReply &replyMarkup = GenericReply());

    /**
     * Send audio
     * @param chatId - Unique identifier for the message recipient or @channelname
     * @param fileId - Telegram file_id of already sent audio
     * @param duration - Duration of the audio in seconds
     * @param performer - Performer of the audio
     * @param title - Track name of the audio
     * @param replyToMessageId - If the message is a reply, ID of the original message
     * @param replyMarkup - Additional interface options
     * @return success
     * @see https://core.telegram.org/bots/api#sendaudio
     */
    bool sendAudio(const QVariant& chatId, const QString& fileId, qint64 duration = -1, const QString& performer = QString(), const QString& title = QString(), qint32 replyToMessageId = -1, const GenericReply &replyMarkup = GenericReply());

    /**
     * Send a document
     * @param chatId - Unique identifier for the message recipient or @channelname
     * @param file - A file to send
     * @param replyToMessageId - If the message is a reply, ID of the original message
     * @param replyMarkup - Additional interface options
     * @return success
     * @see https://core.telegram.org/bots/api#senddocument
     */
    bool sendDocument(const QVariant& chatId, QFile *file, qint32 replyToMessageId = -1, const GenericReply &replyMarkup = GenericReply());


    /**
     * Send a document
     * @param chatId - Unique identifier for the message recipient or @channelname
     * @param fileId - Telegram file_id of already sent photo
     * @param replyToMessageId - If the message is a reply, ID of the original message
     * @param replyMarkup - Additional interface options
     * @return success
     * @see https://core.telegram.org/bots/api#senddocument
     */
    bool sendDocument(const QVariant& chatId, const QString& fileId, qint32 replyToMessageId = -1, const GenericReply &replyMarkup = GenericReply());

    /**
     * Send a sticker
     * @param chatId - Unique identifier for the message recipient or @channelname
     * @param file - A file to send
     * @param replyToMessageId - If the message is a reply, ID of the original message
     * @param replyMarkup - Additional interface options
     * @return success
     * @see https://core.telegram.org/bots/api#sendsticker
     */
    bool sendSticker(const QVariant& chatId, QFile *file, qint32 replyToMessageId = -1, const GenericReply &replyMarkup = GenericReply());

    /**
     * Send a sticker
     * @param chatId - Unique identifier for the message recipient or @channelname
     * @param fileId - Telegram file_id of already sent photo
     * @param replyToMessageId - If the message is a reply, ID of the original message
     * @param replyMarkup - Additional interface options
     * @return success
     * @see https://core.telegram.org/bots/api#sendsticker
     */
    bool sendSticker(const QVariant& chatId, const QString& fileId, qint32 replyToMessageId = -1, const GenericReply &replyMarkup = GenericReply());

    /**
     * Send a video
     * @param chatId - Unique identifier for the message recipient or @channelname
     * @param fileId - Telegram file_id of already sent photo
     * @param duration - Duration of sent video in seconds
     * @param caption - Video caption
     * @param replyToMessageId - If the message is a reply, ID of the original message
     * @param replyMarkup - Additional interface options
     * @return success
     * @see https://core.telegram.org/bots/api#sendvideo
     */
    bool sendVideo(const QVariant& chatId, QFile *file, qint64 duration = -1, const QString& caption = QString(), qint32 replyToMessageId = -1, const GenericReply &replyMarkup = GenericReply());

    /**
     * Send a video
     * @param chatId - Unique identifier for the message recipient or @channelname
     * @param fileId - Telegram file_id of already sent photo
     * @param duration - Duration of sent video in seconds
     * @param caption - Video caption
     * @param replyToMessageId - If the message is a reply, ID of the original message
     * @param replyMarkup - Additional interface options
     * @return success
     * @see https://core.telegram.org/bots/api#sendvideo
     */
    bool sendVideo(const QVariant& chatId, const QString& fileId, qint64 duration = -1, const QString& caption = QString(), qint32 replyToMessageId = -1, const GenericReply &replyMarkup = GenericReply());

    /**
     * Send a voice
     * @param chatId - Unique identifier for the message recipient or @channelname
     * @param fileId - Telegram file_id of already sent photo
     * @param duration - Duration of sent audio in seconds
     * @param replyToMessageId - If the message is a reply, ID of the original message
     * @param replyMarkup - Additional interface options
     * @return success
     * @see https://core.telegram.org/bots/api#sendvoice
     */
    bool sendVoice(const QVariant& chatId, QFile *file, qint64 duration = -1, qint32 replyToMessageId = -1, const GenericReply &replyMarkup = GenericReply());

    /**
     * Send a voice
     * @param chatId - Unique identifier for the message recipient or @channelname
     * @param fileId - Telegram file_id of already sent photo
     * @param duration - Duration of sent audio in seconds
     * @param replyToMessageId - If the message is a reply, ID of the original message
     * @param replyMarkup - Additional interface options
     * @return success
     * @see https://core.telegram.org/bots/api#sendvoice
     */
    bool sendVoice(const QVariant& chatId, const QString& fileId, qint64 duration = -1, qint32 replyToMessageId = -1, const GenericReply &replyMarkup = GenericReply());

    /**
     * Send a location
     * @param chatId - Unique identifier for the message recipient or @channelname
     * @param latitude - latitude of the location
     * @param longitude - longitude of the location
     * @param replyToMessageId - If the message is a reply, ID of the original message
     * @param replyMarkup - Additional interface options
     * @return success
     * @see https://core.telegram.org/bots/api#sendlocation
     */
    bool sendLocation(const QVariant& chatId, float latitude, float longitude, qint32 replyToMessageId = -1, const GenericReply &replyMarkup = GenericReply());

    /**
     * Use this method when you need to tell the user that something is happening on the bot's side.
     * @param chatId - Unique identifier for the message recipient or @channelname
     * @param action - Type of action to broadcast
     * @return success
     * @see https://core.telegram.org/bots/api#sendchataction
     */
    bool sendChatAction(const QVariant& chatId, ChatAction action);

    /**
     * Use this method to get a list of profile pictures for a user.
     * @param userId - Unique identifier of the target user
     * @param offset - Sequential number of the first photo to be returned.
     * @param limit - Limits the number of photos to be retrieved. Values between 1—100 are accepted. Defaults to 100.
     * @return UserProfilePhotos list
     * @see Use this method to get a list of profile pictures for a user.
     */
    UserProfilePhotos getUserProfilePhotos(quint32 userId, qint16 offset =  -1, qint8 limit = -1);

    /**
     * Use this method to receive incoming updates using long polling
     * @param timeout - Timeout in seconds for long polling.
     * @param limit - Limits the number of updates to be retrieved.
     * @param offset - Identifier of the first update to be returned.
     * @return List of Update objects
     * @see https://core.telegram.org/bots/api#getupdates
     */
    QList<Update> getUpdates(quint32 timeout, quint32 limit, quint32 offset);

    /**
     * @param callback_query_id - Unique identifier for the query to be answered
     * @param text - Text of the notification. If not specified, nothing will be shown to the user, 0-200 characters
     * @param show_alert - If true, an alert will be shown by the client instead of a notification at the top of the chat screen. Defaults to false.
     * @param url - URL that will be opened by the user's client. If you have created a Game and accepted the conditions via @Botfather, specify the URL that opens your game – note that this will only work if the query comes from a callback_game button.
     * @param cache_time	Integer	Optional	The maximum amount of time in seconds that the result of the callback query may be cached client-side. Telegram apps will support caching starting in version 3.14. Defaults to 0.
     * @return success
     * @see https://core.telegram.org/bots/api#answercallbackquery
     */
    bool answerCallbackQuery(const QString& callbackQueryId,const QString& text = QString(),bool showAlert = false, const QString& url = QString(),qint32 cahceTime = 0);

    /**
     * Use this method to specify a url and receive incoming updates via an outgoing webhook.
     * @param url - HTTPS url to send updates to. Use an empty string to remove webhook integration
     * @param certificate - Upload your public key certificate so that the root certificate in use can be checked.
     * @return success
     * @see https://core.telegram.org/bots/api#setwebhook
     */
    bool setWebhook(const QString& url, QFile *certificate);

    /**
     * Use this method to get basic info about a file and prepare it for downloading.
     * @param fileId - File identifier to get info about
     * @return File object
     * @see https://core.telegram.org/bots/api#getfile
     */
    File getFile(const QString& fileId);

    /**
     * Use this method to set restrictions for user in supergroup.
     *
     * @param chat_id - Unique identifier for the target chat or username of the target supergroup (in the format @supergroupusername)
     * @param user_id - Unique identifier of the target user
     * @param until_date - Date when restrictions will be lifted for the user, unix time. If user is restricted for more than 366 days or less than 30 seconds from the current time, they are considered to be restricted forever
     * @param can_send_messages - Pass True, if the user can send text messages, contacts, locations and venues
     * @param can_send_media_messages - Pass True, if the user can send audios, documents, photos, videos, video notes and voice notes, implies can_send_messages
     * @param can_send_other_messages - Pass True, if the user can send animations, games, stickers and use inline bots, implies can_send_media_messages
     * @param can_add_web_page_previews - Pass True, if the user may add web page previews to their messages, implies can_send_media_messages
     * @return true on success
     * @see https://core.telegram.org/bots/api#restrictchatmember
     */
    bool restrictChatMember(const QVariant& chatId, const QVariant& userId, qint32 untilDate, bool canSendMessages = false, bool can_send_media_messages = false,bool can_send_other_messages = false,bool can_add_web_page_previews = false);

    /**
     * Use this method to kick a user from a group, a supergroup or a channel.
     * @param chat_id - Unique identifier for the target chat or username of the target supergroup (in the format @supergroupusername).
     * @param user_id - Unique identifier of the target user.
     * @param until_date - Date when the user will be unbanned, unix time. If user is banned for more than 366 days or less than 30 seconds from the current time they are considered to be banned forever.
     * @return true on success
     * @see https://core.telegram.org/bots/api#kickchatmember
     */
    bool kickChatMember(const QVariant& chatId,const QVariant& userId,quint32 untilDate);

    /**
     */
    bool unbanChatMember(qint64 chatId,qint32 userId);

private:
    Networking *m_net;

    bool _sendPayload(const QVariant& chatId, QFile *filePayload, ParameterList params, qint32 replyToMessageId, const GenericReply &replyMarkup, const QString& payloadField, const QString& endpoint);
    bool _sendPayload(const QVariant& chatId, const QString& textPayload, ParameterList params, qint32 replyToMessageId, const GenericReply &replyMarkup, const QString& payloadField, const QString& endpoint);

    QJsonObject jsonObjectFromByteArray(const QByteArray& json);
    QJsonArray jsonArrayFromByteArray(const QByteArray& json);
    bool responseOk(const QByteArray& json);

    void internalGetUpdates();
    QTimer *m_internalUpdateTimer;
    quint32 m_updateInterval;
    quint32 m_updateOffset;
    quint32 m_pollingTimeout;



signals:
    void message(Telegram::Message message);
    void callbackQuery(Telegram::CallbackQuery callback);
};

}

#endif // QTTELEGRAMBOT_H
