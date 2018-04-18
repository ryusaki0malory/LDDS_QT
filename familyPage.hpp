#ifndef FAMILY_HPP
#define FAMILY_HPP

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include "tools.hpp"

class FamilyPage : public QWidget
{
    Q_OBJECT
private:
    QLayout* getLayoutWindow(QWidget *view);

public:
    explicit FamilyPage(QWidget *parent = nullptr);

signals:
    void loadPageParent(const Tools_LDDS::windowsName_t);

public slots:
    void emitLoadMAIN_PAGE();
};

#endif // FAMILY_HPP
