#include "core/configmanager.h"
#include <QFile>
#include <QDir>
#include <QDateTime>
#include <QStandardPaths>
#include <QSaveFile>

ConfigManager::ConfigManager() {}

QString ConfigManager::configPath()
{
    return QDir::homePath() +
           "/.var/app/org.vinegarhq.Sober/config/sober/config.json";
}

QString ConfigManager::profilePath()
{
    return QDir::homePath() + "/.config/SudoStrap/profile.json";
}

bool ConfigManager::saveProfile()
{
    QJsonObject root;
    QJsonObject ff;
    
    for (auto it = m_flags.begin(); it != m_flags.end(); ++it) {
        const QString &v = it.value();
        if (v == "true" || v == "false") {
            ff[it.key()] = (v == "true");
        } else {
            bool ok = false;
            double num = v.toDouble(&ok);
            if (ok && !v.contains('.') && !v.contains('e')) {
                ff[it.key()] = static_cast<int>(num);
            } else if (ok) {
                ff[it.key()] = num;
            } else {
                ff[it.key()] = v;
            }
        }
    }
    root["fflags"] = ff;
    root["use_opengl"] = m_useOpenGL;
    
    QDir().mkpath(QFileInfo(profilePath()).absolutePath());
    QFile f(profilePath());
    if (!f.open(QFile::WriteOnly | QFile::Truncate)) return false;
    f.write(QJsonDocument(root).toJson(QJsonDocument::Indented));
    f.close();
    return true;
}

bool ConfigManager::loadProfile()
{
    QFile f(profilePath());
    if (!f.exists()) return false;
    if (!f.open(QFile::ReadOnly)) return false;
    
    QJsonDocument doc = QJsonDocument::fromJson(f.readAll());
    f.close();
    
    QJsonObject root = doc.object();
    if (!root.contains("fflags")) return false;
    
    m_flags.clear();
    if (root.contains("use_opengl")) m_useOpenGL = root["use_opengl"].toBool();
    
    QJsonObject ff = root["fflags"].toObject();
    for (auto it = ff.begin(); it != ff.end(); ++it) {
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

QString ConfigManager::backupDir()
{
    QString dir = QDir::homePath() + "/.config/SudoStrap/backups";
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

    QByteArray data = f.readAll();
    f.close();

    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(data, &err);
    if (err.error != QJsonParseError::NoError) {
        m_lastError = "Invalid JSON: " + err.errorString();
        return false;
    }

    QJsonObject root = doc.object();

    // Read use_opengl
    if (root.contains("use_opengl")) {
        m_useOpenGL = root["use_opengl"].toBool();
    }

    // Read fflags
    if (root.contains("fflags") && root["fflags"].isObject()) {
        QJsonObject ff = root["fflags"].toObject();
        for (auto it = ff.begin(); it != ff.end(); ++it) {
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
    if (configExists()) {
        QFile rf(configPath());
        if (rf.open(QFile::ReadOnly)) {
            QJsonDocument existing = QJsonDocument::fromJson(rf.readAll());
            if (existing.isObject()) root = existing.object();
            rf.close();
        }
    }

    // Update use_opengl
    root["use_opengl"] = m_useOpenGL;

    // Build fflags object — MERGE with existing (don't replace!)
    QJsonObject ff;
    
    // 1. احتفظ بالفلاغات الموجودة (من Sober أو إعدادات سابقة)
    if (root.contains("fflags") && root["fflags"].isObject()) {
        ff = root["fflags"].toObject();
    }
    
    // 2. حدّث/أضف فلاغاتنا فوقها
    for (auto it = m_flags.begin(); it != m_flags.end(); ++it) {
        const QString &v = it.value();
        if (v == "true" || v == "false") {
            ff[it.key()] = (v == "true");
        } else {
            bool ok = false;
            double num = v.toDouble(&ok);
            if (ok && !v.contains('.') && !v.contains('e') && !v.contains('E')) {
                ff[it.key()] = static_cast<int>(num);
            } else if (ok) {
                ff[it.key()] = num;
            } else {
                ff[it.key()] = v;
            }
        }
    }
    root["fflags"] = ff;

    // Write atomically (QSaveFile handles temp + rename)
    QSaveFile sf(configPath());
    if (!sf.open(QFile::WriteOnly)) {
        m_lastError = "Could not open file for write";
        return false;
    }
    sf.write(QJsonDocument(root).toJson(QJsonDocument::Indented));
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
    return m_flags.value(key, QString());
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
