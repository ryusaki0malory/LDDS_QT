#include "customerPage.hpp"

CustomerPage::CustomerPage(DbHandler &newDb, QWidget *parent) : QWidget(parent), db(newDb)
{
}

CustomerPage::~CustomerPage()
{
}

void CustomerPage::setLayoutWindow()
{
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(getHead());
    mainLayout->addWidget(getList());
    mainLayout->addWidget(getBottom());
    setLayout(mainLayout);
}

void    CustomerPage::setMessage(const status_t status, const QString message)
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

void CustomerPage::cleanItem()
{
    this->Li_ID->setText("");
    this->Li_first_name->setText("");
    this->Li_last_name->setText("");
    this->Li_address->setText("");
    this->Li_postal_code->setText("");
    this->Li_city->setText("");
    this->Li_comment->setText("");
    this->Li_phone->setText("");
    this->Li_mail->setText("");
}

//setAttibutes

void   CustomerPage::setGroupBoxAttributes(QGroupBox* groupBox, const QString name = "")
{
    groupBox->setObjectName(name);
    this->setStyleSheet("QGroupBox {background-color: white; border-style: outset; border-width: 2px; border-color: beige; font: bold 14px;border: 2px solid pink; }");
    groupBox->setTitle("");
}

void    CustomerPage::setButtonAttributes(QPushButton* button, const QString toolTip = "")
{
   button->setToolTip(toolTip);
   button->setFont(QFont("Times", 18, QFont::Bold));
   button->setStyleSheet("QPushButton {background-color: white; border-width: 1px; border-color: grey; font: bold 14px; padding: 25px; }");
}

//Frames

QGroupBox* CustomerPage::getHead()
{
    QGroupBox *groupBox = new QGroupBox(tr("CustomerH"));
    this->setGroupBoxAttributes(groupBox, "CustomerH");
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

QGroupBox* CustomerPage::getList()
{
    QGroupBox *groupBox = new QGroupBox(tr("CustomerL"));
    this->setGroupBoxAttributes(groupBox, "CustomerL");
    QVBoxLayout *Layout = new QVBoxLayout(groupBox);

    this->label = new QLabel(tr("Payment method"));
    label->setFont(QFont("Times", 20, QFont::Bold));
    Layout->addWidget(label);

    //The list
    this->modele = new QStandardItemModel(0, 9);
    QStringList lst;
    lst << "Id" << "Last name" << "First name" << "Address" << "Postal code" << "City" << "Comment" << "Phone" << "Mail";
    this->modele->setHorizontalHeaderLabels(lst);
    this->db.getCustomer(this->modele);
    this->table = new QTableView;
    table->setModel(modele);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->horizontalHeader()->setSectionResizeMode(8, QHeaderView::Stretch);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(table->selectionModel(), SIGNAL(selectionChanged(const QItemSelection&, const QItemSelection&)), this, SLOT(rowSelected(const QItemSelection&, const QItemSelection&)));
    Layout->addWidget(table);

    this->LabMessage = new QLabel();
    Layout->addWidget(LabMessage);

    groupBox->setLayout(Layout);
    return (groupBox);
}

QGroupBox* CustomerPage::getBottom()
{
    QGroupBox *groupBox = new QGroupBox(tr("CustomerB"));
    this->setGroupBoxAttributes(groupBox, "CustomerB");
    QHBoxLayout *Layout = new QHBoxLayout(groupBox);

    this->Li_ID = new QLineEdit;
    this->Li_first_name = new QLineEdit;
    this->Li_last_name = new QLineEdit;
    this->Li_address = new QLineEdit;
    this->Li_postal_code = new QLineEdit;
    this->Li_city = new QLineEdit;
    this->Li_comment = new QLineEdit;
    this->Li_phone = new QLineEdit;
    this->Li_mail = new QLineEdit;
    this->Li_ID->setReadOnly(true);
    this->Li_ID->setStyleSheet("background: grey");
    QFormLayout *formLayout = new QFormLayout();
    formLayout->addRow(tr("&First name"), Li_first_name);
    formLayout->addRow(tr("&Last name"), Li_last_name);
    formLayout->addRow(tr("&Address"), Li_address);
    formLayout->addRow(tr("&Postal code"), Li_postal_code);
    formLayout->addRow(tr("&City"), Li_city);
    formLayout->addRow(tr("&Comment"), Li_comment);
    formLayout->addRow(tr("&Phone"), Li_phone);
    formLayout->addRow(tr("&Mail"), Li_mail);
    formLayout->addRow(tr("ID customer"), Li_ID);
    Layout->addLayout(formLayout);

    this->But_valid = new QPushButton("Valid");
    this->setButtonAttributes(But_valid, "Valid modifications");
    connect(But_valid, SIGNAL(clicked()), this, SLOT(validItem()));
    Layout->addWidget(But_valid);

    groupBox->setLayout(Layout);
    return (groupBox);
}

//SLOTS
void CustomerPage::rowSelected(const QItemSelection& selectionUp, const QItemSelection& selectionDown)
{
    (void)selectionUp;
    (void)selectionDown;

    QItemSelectionModel *select = table->selectionModel();
    this->Li_ID->setText(select->selectedRows(0).value(0).data().toString());
    this->Li_first_name->setText(select->selectedRows(1).value(0).data().toString());
    this->Li_last_name->setText(select->selectedRows(2).value(0).data().toString());
    this->Li_address->setText(select->selectedRows(3).value(0).data().toString());
    this->Li_postal_code->setText(select->selectedRows(4).value(0).data().toString());
    this->Li_city->setText(select->selectedRows(5).value(0).data().toString());
    this->Li_comment->setText(select->selectedRows(6).value(0).data().toString());
    this->Li_phone->setText(select->selectedRows(7).value(0).data().toString());
    this->Li_mail->setText(select->selectedRows(8).value(0).data().toString());
}

void CustomerPage::addItem()
{
    this->setMessage(SUCCESS, "Please insert a new customer");
    this->cleanItem();
}

void CustomerPage::deleteItem()
{
    if (this->Li_ID->text().toStdString() != "")
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "deleted", "Do you want to delete the customer '" + this->Li_last_name->text() + "'?",
                                        QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            if (this->db.deleteCustomer(this->Li_ID->text().toInt()))
            {
                this->setMessage(SUCCESS, "Customer deleted");
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
    this->db.getCustomer(this->modele);
    this->cleanItem();
}

void CustomerPage::validItem()
{
    //Add or modify customer method
    if (this->Li_ID->text().toStdString() == "")
    {
        if (this->Li_last_name->text().toStdString() != "")
        {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "add", "Do you want to add the new customer '" + this->Li_last_name->text() + "'?",
                                            QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                if (this->db.addCustomer(Li_first_name->text(), Li_last_name->text(), Li_address->text(), Li_postal_code->text(), Li_city->text(), Li_comment->text(), Li_phone->text(), Li_mail->text(), 0 ))
                {
                    this->setMessage(SUCCESS, "Customer added");
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
        if (this->Li_last_name->text().toStdString() != "")
        {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "update", "Do you want to update the customer '" + this->Li_last_name->text() + "'?",
                                            QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                if (this->db.updateCustomer(this->Li_ID->text().toInt(), Li_first_name->text(), Li_last_name->text(), Li_address->text(), Li_postal_code->text(), Li_city->text(), Li_comment->text(), Li_phone->text(), Li_mail->text(), 0))
                {
                    this->setMessage(SUCCESS, "Customer modified");
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
    this->db.getCustomer(this->modele);
    this->cleanItem();
}

void CustomerPage::emitLoadMAIN_PAGE()
{
   emit loadPageParent(Tools_LDDS::MAIN_PAGE);
}
