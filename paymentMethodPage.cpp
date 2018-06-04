#include "paymentMethodPage.hpp"

PaymentMethodPage::PaymentMethodPage(DbHandler &newDb, QWidget *parent) : QWidget(parent), db(newDb)
{
}

PaymentMethodPage::~PaymentMethodPage()
{
}

void PaymentMethodPage::setLayoutWindow()
{
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(getHead());
    mainLayout->addWidget(getList());
    mainLayout->addWidget(getBottom());
    setLayout(mainLayout);
}

void    PaymentMethodPage::setMessage(const status_t status, const QString message)
{
    this->LabMessage->setText(message);
    this->LabMessage->setFont(QFont("Times", 15, QFont::Bold));
    switch (status) {
        case SUCCESS:
            this->LabMessage->setStyleSheet("QLabel { color : green; }");
            break;
        case FAIL:
            this->LabMessage->setStyleSheet("QLabel { color : red; }");
            break;
        case INFORMATION:
            this->LabMessage->setStyleSheet("QLabel { color : blue; }");
            break;
        default:
            break;
    }
}

void PaymentMethodPage::cleanItem()
{
    this->Li_ID->setText("");
    this->Li_name->setText("");
}

//setAttibutes

void   PaymentMethodPage::setGroupBoxAttributes(QGroupBox* groupBox, const QString name = "")
{
    groupBox->setObjectName(name);
    this->setStyleSheet("QGroupBox {background-color: white; border-style: outset; border-width: 2px; border-color: beige; font: bold 14px;border: 2px solid pink; }");
    groupBox->setTitle("");
}

void    PaymentMethodPage::setButtonAttributes(QPushButton* button, const QString toolTip = "")
{
   button->setToolTip(toolTip);
   button->setFont(QFont("Times", 18, QFont::Bold));
   button->setStyleSheet("QPushButton {background-color: white; border-width: 1px; border-color: grey; font: bold 14px; padding: 25px; }");
}

void    PaymentMethodPage::setLabelAttributes(QLabel* label)
{
    label->setFont(QFont("Times", 14, QFont::Bold));
}

void    PaymentMethodPage::setLineAttributes(QLineEdit *line)
{
     line =NULL;
}

//Frames

QGroupBox* PaymentMethodPage::getHead()
{
    QGroupBox *groupBox = new QGroupBox(tr("PaymentH"));
    this->setGroupBoxAttributes(groupBox, "Base_unitH");
    QHBoxLayout *Layout = new QHBoxLayout(groupBox);

    this->But_return = new QPushButton("Return");
    this->setButtonAttributes(But_return, "Return to menu");
    connect(But_return, SIGNAL(clicked()), this, SLOT(emitLoadMAIN_PAGE()));
    Layout->addWidget(But_return);

    this->But_add = new QPushButton("Add");
    this->setButtonAttributes(But_add, "Add new base unit");
    connect(But_add, SIGNAL(clicked()), this, SLOT(addItem()));
    Layout->addWidget(But_add);

    this->but_delete = new QPushButton("Delete");
    this->setButtonAttributes(but_delete, "Delete selected base unit");
    connect(but_delete, SIGNAL(clicked()), this, SLOT(deleteItem()));
    Layout->addWidget(but_delete);

    groupBox->setLayout(Layout);
    return (groupBox);
}

QGroupBox* PaymentMethodPage::getList()
{
    QGroupBox *groupBox = new QGroupBox(tr("PaymentL"));
    this->setGroupBoxAttributes(groupBox, "PaymentL");
    QVBoxLayout *Layout = new QVBoxLayout(groupBox);

    this->label = new QLabel(tr("Payment method"));
    label->setFont(QFont("Times", 20, QFont::Bold));
    Layout->addWidget(label);

    //The list
    this->modele = new QStandardItemModel(0, 2);
    QStringList lst;
    lst << "Id" << "Name payment method";
    this->modele->setHorizontalHeaderLabels(lst);
    this->db.getPaymentMethod(this->modele);
    this->table = new QTableView;
    table->setModel(modele);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(table->selectionModel(), SIGNAL(selectionChanged(const QItemSelection&, const QItemSelection&)), this, SLOT(rowSelected(const QItemSelection&, const QItemSelection&)));
    Layout->addWidget(table);

    this->LabMessage = new QLabel();
    Layout->addWidget(LabMessage);

    groupBox->setLayout(Layout);
    return (groupBox);
}

QGroupBox* PaymentMethodPage::getBottom()
{
    QGroupBox *groupBox = new QGroupBox(tr("PaymentB"));
    this->setGroupBoxAttributes(groupBox, "PaymentB");
    QGridLayout *Layout = new QGridLayout(groupBox);

    this->La_ID = new QLabel(tr("ID payment method"));
    this->Li_ID = new QLineEdit;
    this->La_name = new QLabel(tr("Name of payment method"));
    this->Li_name = new QLineEdit;
    this->setLabelAttributes(this->La_name);
    this->setLabelAttributes(this->La_ID);
    this->Li_ID->setReadOnly(true);
    this->Li_ID->setStyleSheet("background: grey");

    this->But_valid = new QPushButton("Valid");
    this->setButtonAttributes(But_valid, "Valid modifications");
    connect(But_valid, SIGNAL(clicked()), this, SLOT(validItem()));

    Layout->addWidget(La_name, 0, 0);
    Layout->addWidget(Li_name, 0, 1);
    Layout->addWidget(La_ID, 1, 0);
    Layout->addWidget(Li_ID, 1, 1);
    Layout->addWidget(But_valid, 2, 0, 2, 2);

    groupBox->setLayout(Layout);
    return (groupBox);
}

//SLOTS
void PaymentMethodPage::rowSelected(const QItemSelection& selectionUp, const QItemSelection& selectionDown)
{
    (void)selectionUp;
    (void)selectionDown;

    QItemSelectionModel *select = table->selectionModel();
    this->Li_ID->setText(select->selectedRows(0).value(0).data().toString());
    this->Li_name->setText(select->selectedRows(1).value(0).data().toString());
}

void PaymentMethodPage::addItem()
{
    this->setMessage(SUCCESS, "Please insert a new payment method");
    this->cleanItem();
}

void PaymentMethodPage::deleteItem()
{
    if (this->Li_ID->text().toStdString() != "")
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "deleted", "Do you want to delete the payment method '" + this->Li_name->text() + "'?",
                                        QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            if (this->db.deletePaymentMethod(this->Li_ID->text().toInt()))
            {
                this->setMessage(SUCCESS, "payment method deleted");
            }
            else
            {
                this->setMessage(FAIL, "Error occured");
            }
          } else {
            this->setMessage(FAIL, "");
          }
    }
    //actualise
    this->modele->setRowCount(0);
    this->db.getPaymentMethod(this->modele);
    this->cleanItem();
}

void PaymentMethodPage::validItem()
{
    //Add or modify new payment method
    if (this->Li_ID->text().toStdString() == "")
    {
        if (this->Li_name->text().toStdString() != "")
        {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "add", "Do you want to add the new payment method '" + this->Li_name->text() + "'?",
                                            QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                if (this->db.addPaymentMethod(this->Li_name->text()))
                {
                    this->setMessage(SUCCESS, "new payment method added");
                }
                else
                {
                    this->setMessage(FAIL, "Error occured");
                }
             }
             else
             {
                this->setMessage(FAIL, "");
             }
        }
    }
    else
    {
        if (this->Li_name->text().toStdString() != "")
        {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "update", "Do you want to update the payment method '" + this->Li_name->text() + "'?",
                                            QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                if (this->db.updatePaymentMethod(this->Li_ID->text().toInt(), this->Li_name->text()))
                {
                    this->setMessage(SUCCESS, "Payment method modified");
                }
                else
                {
                    this->setMessage(FAIL, "Error occured");
                }
            }
            else
            {
                this->setMessage(FAIL, "");
            }
        }
    }
    //actualise
    this->modele->setRowCount(0);
    this->db.getPaymentMethod(this->modele);
    this->cleanItem();
}

void PaymentMethodPage::emitLoadMAIN_PAGE()
{
   emit loadPageParent(Tools_LDDS::MAIN_PAGE);
}

