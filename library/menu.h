#ifndef MENU_H
#define MENU_H
#include <QPushButton>
#include <QVBoxLayout>
#include <QComboBox>
#include <QVector>
#include <QPair>
#include <QMap>


class TMenu : public QObject
{
    Q_OBJECT
public:
    TMenu(QWidget* parent);
    QVBoxLayout* GetMainLayout();
    QPushButton* GetJsonButton();
    QPushButton* GetGraphButton();
    QPushButton* GetResultsButton();
    QPushButton* GetCreateButton();
    void UpdateComboBox(QVector<QPair<int, QString>> graphList);
    ~TMenu();
private slots:
    void UpdateCurrentInComboBox(QString graphName);
signals:
    void UpdateCurrentGraphID(int);
private:
    QPushButton* GraphButton_;
    QPushButton* JsonButton_;
    QPushButton* ResultsButton_;
    QPushButton* CreateButton_;
    QComboBox* ComboBox_;

    QVBoxLayout* MainLayout_;
    QWidget* Parent_;
    QMap<QString, int> Graph2ID_;
    static const int WIDTH = 100;
};

#endif // MENU_H
