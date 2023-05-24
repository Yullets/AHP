#ifndef ICOMMAND_H
#define ICOMMAND_H

#include <QObject>

class ICommand : public QObject
{
    Q_OBJECT
public:
    explicit ICommand(QObject *parent = nullptr);

signals:

};

#endif // ICOMMAND_H
