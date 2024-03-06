/*!
 * \file directory_checker_thread.h
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

#ifndef DIRECTORY_CHECKER_THREAD_H
#define DIRECTORY_CHECKER_THREAD_H

#include <QObject>
#include <QPointer>
#include <QString>
#include <QThread>

class DirectoryChecker;

class DirectoryCheckerThread : public QThread
{
    Q_OBJECT
public:
    explicit    DirectoryCheckerThread  (const QString & path, QObject * parent = nullptr);
    virtual     ~DirectoryCheckerThread ();

    void        run                     () Q_DECL_OVERRIDE;

signals:
    void        mountingStateChecked    (bool isMounted);

private slots:
    void        onDirectoryChecked      (bool isMounted);

private:
    QString                     m_path;
    QPointer<DirectoryChecker>  m_checker;
};

#endif // DIRECTORY_CHECKER_THREAD_H
