#ifndef JSON_EDIT_H
#define JSON_EDIT_H

#include <QObject>
#include <QTextEdit>

class TJsonEdit : public QObject
{
    Q_OBJECT
public:
    explicit TJsonEdit(QObject *parent = nullptr);
    QTextEdit* GetJsonEdit();
    void UpdateGraph(QMap<QString, QVector<QString>> graph);
    ~TJsonEdit();
signals:

public slots:
private:
    QTextEdit* JsonEdit_;

};

#endif // JSON_EDIT_H
