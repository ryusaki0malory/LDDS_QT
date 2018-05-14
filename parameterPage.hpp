#ifndef PARAMETERPAGE_HPP
#define PARAMETERPAGE_HPP

#include <QWidget>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QFileDialog>
#include <QGridLayout>
#include <QPushButton>
#include <QMessageBox>
#include "tools.hpp"
#include "dbhandler.hpp"

class ParameterPage : public QWidget
{
    Q_OBJECT
public:
    explicit ParameterPage(DbHandler &newDb, QWidget *parent = nullptr);
    ~ParameterPage();
    void setLayoutWindow();

private:
    void setButtonAttributes(QPushButton* button, const QString toolTip);
    void setGroupBoxAttributes();
    void createFrameParameters();

    QPushButton *But_return;
    QPushButton *First_Init;
    QPushButton *Change_Logo;
    QGroupBox *parameterGroupBox;
    DbHandler &db;

signals:
    void loadPageParent(const Tools_LDDS::windowsName_t);

public slots:
    void emitLoadMAIN_PAGE();
    void firstInit();
    void changeLogo();
};

#endif // PARAMETERPAGE_HPP
