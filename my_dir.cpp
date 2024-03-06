/*!
 * \file my_dir.cpp
 * \brief file for the definition of the class "MyDir"
 * \author doga
 * \date 2024-3-5
 *
 * \details
 *
 * \copyright
 ****************************************************************************
 *        Ce logiciel est la propriete de DOGA®.
 *         -------------------------------------
 *
 *    Il ne peut etre reproduit ni communique en totalite ou partie sans
 *    son autorisation ecrite.
 *
 ****************************************************************************
 *        This software is the property of DOGA®.
 *         -------------------------------------
 *
 *    It cannot be reproduced nor disclosed entirely or partially without
 *    a written agreement.
 *
 ****************************************************************************
 */
#include "my_dir.h"

#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QFileSystemWatcher>
#include <QObject>
#include <QStorageInfo>
#include <QTimer>

MyDir::MyDir(const QString & path, QObject * parent)
    : QObject{parent}
    , m_path(path)
    , m_timer(this)
    , m_watcher(this)
    , m_iter(0)
    , m_time()
{
    // Ajouter le point de montage à surveiller
    m_watcher.addPath(m_path);
    qDebug() << "Surveillance du dossier" << m_path << "en cours...";

    m_timer.setInterval(5000);
    m_timer.setSingleShot(false);
    QObject::connect(& m_timer, & QTimer::timeout, this, & MyDir::sltTimeout);
    m_timer.start();

    // Connecter le signal directoryChanged à une fonction lambda
    QObject::connect(& m_watcher, & QFileSystemWatcher::directoryChanged, this, & MyDir::sltwatcherDirChanged);
}

void MyDir::sltwatcherDirChanged(const QString &path) {
    qDebug() << "Le contenu du dossier" << path << "a changé.";
}

void MyDir::sltTimeout() {
    QTime time = QTime::currentTime();
    qDebug() << "Le statut du dossier" << m_path << "est :" << m_iter++ << "," << m_time.msecsTo(time) << "ms";
    QFileInfo fi(m_path);
    if (fi.exists()) {
        qDebug() << "  - exists";
        if (fi.isDir()) {
            qDebug() << "  - isDir";
            qDebug() << "  - size:" << fi.size();
            QDir dir(m_path);
            QStringList content = dir.entryList(QDir::NoDotAndDotDot | QDir::Files | QDir::Dirs, QDir::Name);
            if (content.isEmpty()) {
                qDebug() << "  - empty";
            } else {
                qDebug() << "  - content:" << content.join(", ");
            }

            QStorageInfo storage(dir);
            storage.refresh();
            if (storage.isValid()) {
                qDebug() << "  - storage valid";
                if (storage.isReady()) {
                    qDebug() << "  - storage ready";
                    qDebug() << "  - storage rootPath =" << storage.rootPath();
                    QString canonicalPath(dir.canonicalPath());
                    qDebug() << "  - canonical path   =" << canonicalPath;
                    if (QDir(canonicalPath).exists()) {
                        qDebug() << "  - canonical path exists";
                    } else {
                        qDebug() << "  - canonical path NOT EXISTS";
                    }
                }
            }
        }
    } else {
        qDebug() << "  - NOT EXISTS";
    }
    m_time = time;
    qDebug() << " Done in" << time.msecsTo(QTime::currentTime()) << "ms";
}