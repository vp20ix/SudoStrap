#include "core/configmanager.h"
#include <QFile>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QSaveFile>

namespace {

const QString &homeDirectory()
{
    static const QString path = QDir::homePath();
    return path;
}

const QString &soberConfigPath()
{
    static const QString path = homeDirectory() + QStringLiteral("/.var/app/org.vinegarhq.Sober/config/sober/config.json");
    return path;
}

const QString &sudostrapConfigDirectory()
{
    static const QString path = homeDirectory() + QStringLiteral("/.config/SudoStrap");
    return path;
}

const QString &sudostrapProfilePath()
{
    static const QString path = sudostrapConfigDirectory() + QStringLiteral("/profile.json");
    return path;
}

const QString &sudostrapBackupDirectory()
{
    static const QString path = sudostrapConfigDirectory() + QStringLiteral("/backups");
    return path;
}

QJsonValue jsonValueForFlag(const QString &value)
{
    if (value == QLatin1String("true")) return true;
    if (value == QLatin1String("false")) return false;

    bool ok = false;
    const double number = value.toDouble(&ok);
    if (!ok) return value;

    if (!value.contains(QLatin1Char('.')) &&
        !value.contains(QLatin1Char('e')) &&
        !value.contains(QLatin1Char('E'))) {
        return static_cast<int>(number);
    }
    return number;
}

} // namespace

const QString &ConfigManager::configPath()
{
    return soberConfigPath();
}

const QString &ConfigManager::profilePath()
{
    return sudostrapProfilePath();
}

bool ConfigManager::saveProfile()
{
    m_lastError.clear();

    QJsonObject root;
    QJsonObject ff;

    for (auto it = m_flags.cbegin(), end = m_flags.cend(); it != end; ++it) {
        ff.insert(it.key(), jsonValueForFlag(it.value()));
    }

    root.insert(QStringLiteral("fflags"), ff);
    root.insert(QStringLiteral("use_opengl"), m_useOpenGL);

    if (!QDir().mkpath(sudostrapConfigDirectory())) {
        m_lastError = QStringLiteral("Could not create profile directory");
        return false;
    }

    QSaveFile file(profilePath());
    if (!file.open(QFile::WriteOnly)) {
        m_lastError = QStringLiteral("Could not open profile for write");
        return false;
    }

    const QByteArray json = QJsonDocument(root).toJson(QJsonDocument::Compact);
    if (file.write(json) != json.size()) {
        m_lastError = QStringLiteral("Could not write profile");
        file.cancelWriting();
        return false;
    }
    if (!file.commit()) {
        m_lastError = QStringLiteral("Could not commit profile");
        return false;
    }

    return true;
}

bool ConfigManager::loadProfile()
{
    QFile f(profilePath());
    if (!f.exists()) return false;
    if (!f.open(QFile::ReadOnly)) return false;
    
    const QJsonDocument doc = QJsonDocument::fromJson(f.readAll());
    f.close();
    
    const QJsonObject root = doc.object();
    const QJsonValue flagsValue = root.value(QStringLiteral("fflags"));
    if (!flagsValue.isObject()) return false;
    
    m_flags.clear();
    const QJsonValue openGLValue = root.value(QStringLiteral("use_opengl"));
    if (!openGLValue.isUndefined()) m_useOpenGL = openGLValue.toBool();
    
    const QJsonObject ff = flagsValue.toObject();
    for (auto it = ff.constBegin(), end = ff.constEnd(); it != end; ++it) {
        QString val;
        if (it.value().isString()) val = it.value().toString();
        else if (it.value().isBool()) val = it.value().toBool() ? "true" : "false";
        else if (it.value().isDouble()) val = QString::number(it.value().toDouble(), 'g', 15);
        m_flags[it.key()] = val;
    }
    return true;
}

bool ConfigManager::restoreFromProfile()
{
    if (!loadProfile()) {
        m_lastError = "No profile found";
        return false;
    }
    return save();
}

const QString &ConfigManager::backupDir()
{
    const QString &dir = sudostrapBackupDirectory();
    QDir().mkpath(dir);
    return dir;
}

bool ConfigManager::configExists() const
{
    return QFile::exists(configPath());
}

bool ConfigManager::load()
{
    m_flags.clear();
    m_lastError.clear();

    QFile f(configPath());
    if (!f.exists()) {
        m_lastError = "config.json not found (Sober may not be installed)";
        return false;
    }

    if (!f.open(QFile::ReadOnly)) {
        m_lastError = "Could not open config.json";
        return false;
    }

    QJsonParseError err;
    const QJsonDocument doc = QJsonDocument::fromJson(f.readAll(), &err);
    f.close();
    if (err.error != QJsonParseError::NoError) {
        m_lastError = "Invalid JSON: " + err.errorString();
        return false;
    }

    const QJsonObject root = doc.object();

    // Read use_opengl
    const QJsonValue openGLValue = root.value(QStringLiteral("use_opengl"));
    if (!openGLValue.isUndefined()) m_useOpenGL = openGLValue.toBool();

    // Read fflags
    const QJsonValue flagsValue = root.value(QStringLiteral("fflags"));
    if (flagsValue.isObject()) {
        const QJsonObject ff = flagsValue.toObject();
        for (auto it = ff.constBegin(), end = ff.constEnd(); it != end; ++it) {
            QString val;
            if (it.value().isString())       val = it.value().toString();
            else if (it.value().isBool())    val = it.value().toBool() ? "true" : "false";
            else if (it.value().isDouble())  val = QString::number(it.value().toDouble(), 'g', 15);
            else if (it.value().isNull())    val = "null";
            else                             val = "?";
            m_flags[it.key()] = val;
        }
    }

    return true;
}

bool ConfigManager::save()
{
    m_lastError.clear();

    QJsonObject root;

    // Preserve existing file content
    {
        QFile existingFile(configPath());
        if (existingFile.open(QFile::ReadOnly)) {
            const QJsonDocument existing = QJsonDocument::fromJson(existingFile.readAll());
            if (existing.isObject()) root = existing.object();
        }
    }

    // Update use_opengl
    root.insert(QStringLiteral("use_opengl"), m_useOpenGL);

    // Build fflags object — MERGE with existing (don't replace!)
    QJsonObject ff;
    
    // 1. احتفظ بالفلاغات الموجودة (من Sober أو إعدادات سابقة)
    const QJsonValue existingFlags = root.value(QStringLiteral("fflags"));
    if (existingFlags.isObject()) {
        ff = existingFlags.toObject();
    }
    
    // 2. حدّث/أضف فلاغاتنا فوقها
    for (auto it = m_flags.cbegin(), end = m_flags.cend(); it != end; ++it) {
        ff.insert(it.key(), jsonValueForFlag(it.value()));
    }
    root.insert(QStringLiteral("fflags"), ff);

    // Write atomically (QSaveFile handles temp + rename)
    QSaveFile sf(configPath());
    if (!sf.open(QFile::WriteOnly)) {
        m_lastError = "Could not open file for write";
        return false;
    }
    const QByteArray json = QJsonDocument(root).toJson(QJsonDocument::Compact);
    if (sf.write(json) != json.size()) {
        m_lastError = "Could not write file";
        sf.cancelWriting();
        return false;
    }
    if (!sf.commit()) {
        m_lastError = "Could not commit file";
        return false;
    }

    return true;
}


void ConfigManager::setFlag(const QString &key, const QString &value)
{
    m_flags[key] = value;
}

void ConfigManager::removeFlag(const QString &key)
{
    m_flags.remove(key);
}

QString ConfigManager::getFlag(const QString &key) const
{
    const auto it = m_flags.constFind(key);
    return it == m_flags.cend() ? QString() : it.value();
}

void ConfigManager::clearFlags()
{
    m_flags.clear();
}

void ConfigManager::applyLowEndPreset()
{
    clearFlags();
    m_flags["DFIntTaskSchedulerTargetFps"] = "60";
    m_flags["DFIntCSGLevelOfDetailSwitchingDistance"] = "0";
    m_flags["DFIntDebugFRMQualityLevelOverride"] = "1";
    m_flags["DFIntTextureQualityOverride"] = "0";
    m_flags["FIntFRMMaxGrassDistance"] = "0";
}

void ConfigManager::applyBalancedPreset()
{
    clearFlags();
    m_flags["DFIntTaskSchedulerTargetFps"] = "240";
    m_flags["DFIntCSGLevelOfDetailSwitchingDistance"] = "500";
    m_flags["DFIntDebugFRMQualityLevelOverride"] = "10";
    m_flags["DFIntTextureQualityOverride"] = "2";
    m_flags["FIntFRMMaxGrassDistance"] = "500";
}

void ConfigManager::applyHighEndPreset()
{
    clearFlags();
    m_flags["DFIntTaskSchedulerTargetFps"] = "9999";
    m_flags["DFIntCSGLevelOfDetailSwitchingDistance"] = "1000";
    m_flags["DFIntDebugFRMQualityLevelOverride"] = "21";
    m_flags["DFIntTextureQualityOverride"] = "3";
    m_flags["FIntFRMMaxGrassDistance"] = "1000";
}
