/*!
 * \file directory_checker_thread.cpp
 * \brief file for the definition of the class "DirectoryCheckerThread"
 * \author doga
 * \date 2024-3-6
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

#include "directory_checker_thread.h"
#include "directory_checker.h"

#include <QObject>
#include <QString>
#include <QThread>

DirectoryCheckerThread::DirectoryCheckerThread(const QString & path, QObject * parent)
    : QThread{parent}
    , m_path(path)
    , m_checker(nullptr)
{}

DirectoryCheckerThread::~DirectoryCheckerThread()
{
    if (m_checker) {
        m_checker->deleteLater();
    }
}

void DirectoryCheckerThread::run()
{
    if (m_checker.isNull()) {
        m_checker = new DirectoryChecker(m_path);
    }
    if (m_checker) {
        connect(m_checker, & DirectoryChecker::directoryChecked, this, & DirectoryCheckerThread::onDirectoryChecked, Qt::UniqueConnection);

        // Exécuter la fonction de vérification du répertoire dans ce thread
        m_checker->checkMounting();
    }
}

void DirectoryCheckerThread::onDirectoryChecked(bool isMounted)
{
    // Émettre le résultat après la vérification
    emit mountingStateChecked(isMounted);
    // Terminer ce thread d'exécution
    quit();
}
