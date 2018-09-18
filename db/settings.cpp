#include "settings.h"

Settings::Settings(const QString &name) :
    QSettings(name + ".ini", QSettings::IniFormat)
{}
Settings::~Settings()
{
    QMutexLocker mL(&mutex);
    flushCache();
}

void Settings::flush()
{
    QMutexLocker mL(&mutex);
    flushCache();
    sync();
}

void Settings::init(const QString &key, const QVariant &val)
{
    QMutexLocker mL(&mutex);
    if (!cache.contains(key) && !QSettings::contains(key))
        cache[key] = val;
    toRemove.remove(key);
}
bool Settings::contains(const QString &key) const
{
    QMutexLocker mL(&mutex);
    if (cache.contains(key))
        return true;
    if (toRemove.contains(key))
        return false;
    return QSettings::contains(key);
}
void Settings::set(const QString &key, const QVariant &val)
{
    QMutexLocker mL(&mutex);
    toRemove.remove(key);
    cache[key] = val;
}
void Settings::remove(const QString &key)
{
    QMutexLocker mL(&mutex);
    toRemove.insert(key);
    cache.remove(key);
}

QVariant Settings::get(const QString &key, const QVariant &def) const
{
    QMutexLocker mL(&mutex);
    auto it = cache.find(key);
    if (it != cache.end())
        return it.value();
    if (toRemove.contains(key))
        return def;
    return QSettings::value(key, def);
}

void Settings::flushCache()
{
    for (const QString &key : toRemove)
        QSettings::remove(key);
    toRemove.clear();

    for (auto it = cache.constBegin(), end_it = cache.constEnd(); it != end_it; ++it)
        QSettings::setValue(it.key(), it.value());
    cache.clear();
}
