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

#include "directory_checker_thread.h"

#include <QFileSystemWatcher>
#include <QObject>
#include <QString>
#include <QTimer>

MyDir::MyDir(const QString & path, QObject * parent)
    : QObject{parent}
    , m_path(path)
    , m_timer(this)
    , m_watcher(this)
    , m_checker(nullptr)
    , m_isMounted(false)
{
    // Définir l'interval de surveillance du dossier
    m_timer.setInterval(5000);
    m_timer.setSingleShot(true);
    QObject::connect(& m_timer, & QTimer::timeout, this, & MyDir::sltCheckDirectoryMounted);

    // Connecter le signal directoryChanged du FileSystemWatcher
    QObject::connect(& m_watcher, & QFileSystemWatcher::directoryChanged, this, & MyDir::sltwatcherDirChanged);

    sltCheckDirectoryMounted();
}

MyDir::~MyDir()
{
    if (m_checker) {
        m_checker->deleteLater();
    }
}

void MyDir::sltwatcherDirChanged(const QString & path)
{
    sltCheckDirectoryMounted();
}

void MyDir::sltCheckDirectoryMounted()
{
    if (m_checker.isNull()) {
        m_checker = new DirectoryCheckerThread(m_path);
        if (m_checker) {
            QObject::connect(m_checker, & DirectoryCheckerThread::mountingStateChecked, this, & MyDir::setIsMounted, Qt::UniqueConnection);
        }
    }
    if (m_checker) {
        m_checker->start();

        // Démarrer un timer pour vérifier si la tâche est terminée dans un délai donné : 100 ms
        QTimer::singleShot(100, this, & MyDir::sltCheckTaskCompletion);
    }
    // démarre le timer pour la prochaine scruptation
    m_timer.start();
}

void MyDir::sltCheckTaskCompletion()
{
    // Vérifier si la tâche asynchrone est terminée
    if (m_checker && (! m_checker->isFinished())) {
        m_checker->terminate(); // Annuler la tâche asynchrone en cours
        setIsMounted(false);
    }
}

void MyDir::setIsMounted(bool isMounted)
{
    if (m_isMounted == isMounted)
        return;
    m_isMounted = isMounted;
    emit directoryMountingChanged(m_isMounted);
    if (m_isMounted) {
        // Ajouter le point de montage à surveiller
        if (! m_watcher.directories().contains(m_path)) {
            m_watcher.addPath(m_path);
        }
    }
}
