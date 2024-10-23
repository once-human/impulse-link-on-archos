#include "notification_model.h"
#include <libnotify/notify.h>

void displayNotification(const std::string &message) {
    notify_init("Impulse Link");
    NotifyNotification* n = notify_notification_new("Notification", message.c_str(), nullptr);
    notify_notification_show(n, nullptr);
    g_object_unref(G_OBJECT(n));
}
