#ifndef MENU_H
#define MENU_H
#include <QPushButton>
#include <QVBoxLayout>
#include <QComboBox>
#include <QVector>
#include <QPair>
#include <QMap>


class TMenu
{
public:
    TMenu(QWidget* parent);
    QVBoxLayout* GetMainLayout();
    QPushButton* GetJsonButton();
    QPushButton* GetGraphButton();
    QPushButton* GetResultsButton();
    void UpdateComboBox(QVector<QPair<int, QString>> graphList);
    ~TMenu();
private:
private:
    QPushButton* GraphButton_;
    QPushButton* JsonButton_;
    QPushButton* ResultsButton_;
    QComboBox* ComboBox_;

    QVBoxLayout* MainLayout_;
    QWidget* Parent_;
    QMap<QString, int> Graph2ID_;
};

#endif // MENU_H
