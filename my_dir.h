/*!
 * \file my_dir.h
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
#ifndef MY_DIR_H
#define MY_DIR_H

#include <QObject>
#include <QFileSystemWatcher>
#include <QTimer>
#include <QTime>

class MyDir : public QObject
{
    Q_OBJECT
public:
    explicit    MyDir                   (const QString & path, QObject * parent = nullptr);

private slots:
    void        sltwatcherDirChanged    (const QString & path);
    void        sltTimeout              ();

private:
    QString             m_path;
    QTimer              m_timer;
    QFileSystemWatcher  m_watcher;
    quint32             m_iter;
    QTime               m_time;
};

#endif // MY_DIR_H
