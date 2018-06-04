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

void    CustomerPage::setLabelAttributes(QLabel* label)
{
    label->setFont(QFont("Times", 14, QFont::Bold));
}

void    CustomerPage::setLineAttributes(QLineEdit *line)
{
     line =NULL;
}

void    CustomerPage::setLineAttributes(QTextEdit *line)
{
     line =NULL;
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

    this->label = new QLabel(tr("Customer"));
    label->setFont(QFont("Times", 20, QFont::Bold));
    Layout->addWidget(label);

    //The list
    this->modele = new QStandardItemModel(0, 9);
    QStringList lst;
    lst << "Id" << "Last name" << "First name" << "Address" << "Postal code" << "City" << "Comment" << "Phone" << "Mail";
    this->modele->setHorizontalHeaderLabels(lst);
    //this->db.getCustomer(this->modele);
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
    QGridLayout *Layout = new QGridLayout(groupBox);

    this->La_ID = new QLabel(tr("ID customer"));
    this->Li_ID = new QLineEdit;
    this->La_first_name = new QLabel(tr("First name"));
    this->Li_first_name = new QLineEdit;
    this->La_last_name = new QLabel(tr("Last name"));
    this->Li_last_name = new QLineEdit;
    this->La_address = new QLabel(tr("Address"));
    this->Li_address = new QLineEdit;
    this->La_postal_code = new QLabel(tr("Postal code"));
    this->Li_postal_code = new QLineEdit;
    this->La_city = new QLabel(tr("City"));
    this->Li_city = new QLineEdit;
    this->La_comment = new QLabel(tr("Comment"));
    this->Li_comment = new QTextEdit;
    this->La_phone = new QLabel(tr("Phone"));
    this->Li_phone = new QLineEdit;
    this->La_mail = new QLabel(tr("Mail"));
    this->Li_mail = new QLineEdit;
    this->Li_ID->setReadOnly(true);
    this->Li_ID->setStyleSheet("background: grey");

    this->But_valid = new QPushButton("Valid");
    this->setButtonAttributes(But_valid, "Valid modifications");
    connect(But_valid, SIGNAL(clicked()), this, SLOT(validItem()));

    Layout->addWidget(La_first_name, 0, 0);
    Layout->addWidget(Li_first_name, 0, 1);
    Layout->addWidget(La_last_name, 0, 2);
    Layout->addWidget(Li_last_name, 0, 3);
    Layout->addWidget(La_address, 1, 0);
    Layout->addWidget(Li_address, 1, 1);
    Layout->addWidget(La_postal_code, 1, 2);
    Layout->addWidget(Li_postal_code, 1, 3);
    Layout->addWidget(La_city, 2, 0);
    Layout->addWidget(Li_city, 2, 1);
    Layout->addWidget(La_phone, 2, 2);
    Layout->addWidget(Li_phone, 2, 3);
    Layout->addWidget(La_mail, 3, 0);
    Layout->addWidget(Li_mail, 3, 1);
    Layout->addWidget(La_ID, 3, 2);
    Layout->addWidget(Li_ID, 3, 3);
    Layout->addWidget(La_comment, 4, 0);
    Layout->addWidget(Li_comment, 4, 1);
    Layout->addWidget(But_valid, 5, 0, 5, 3);

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
//            if (this->db.deleteCustomer(this->Li_ID->text().toInt()))
//            {
//                this->setMessage(SUCCESS, "Customer deleted");
//            }
//            else
//            {
//                this->setMessage(FAIL, "Error occured");
//            }
          } else {
            this->setMessage(FAIL, "");
          }
    }
    //actualise
    this->modele->setRowCount(0);
    //this->db.getCustomer(this->modele);
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
//            if (reply == QMessageBox::Yes) {
//                if (this->db.addCustomer(Li_first_name->text(), Li_last_name->text(), Li_address->text(), Li_postal_code->text(), Li_city->text(), Li_comment->toPlainText(), Li_phone->text(), Li_mail->text(), 0 ))
//                {
//                    this->setMessage(SUCCESS, "Customer added");
//                }
//                else
//                {
//                    this->setMessage(FAIL, "Error occured");
//                }
//             }
//             else
//             {
//                this->setMessage(FAIL, "");
//             }
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
//                if (this->db.updateCustomer(this->Li_ID->text().toInt(), Li_first_name->text(), Li_last_name->text(), Li_address->text(), Li_postal_code->text(), Li_city->text(), Li_comment->toPlainText(), Li_phone->text(), Li_mail->text(), 0))
//                {
//                    this->setMessage(SUCCESS, "Customer modified");
//                }
//                else
//                {
//                    this->setMessage(FAIL, "Error occured");
//                }
            }
            else
            {
                this->setMessage(FAIL, "");
            }
        }
    }
    //actualise
    this->modele->setRowCount(0);
    //this->db.getCustomer(this->modele);
    this->cleanItem();
}

void CustomerPage::emitLoadMAIN_PAGE()
{
   emit loadPageParent(Tools_LDDS::MAIN_PAGE);
}
