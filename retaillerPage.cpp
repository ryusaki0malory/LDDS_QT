#include "retaillerPage.hpp"

RetaillerPage::RetaillerPage(DbHandler &newDb, QWidget *parent) : QWidget(parent), db(newDb)
{
}

RetaillerPage::~RetaillerPage()
{
}

void RetaillerPage::setLayoutWindow()
{
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(getHead());
    mainLayout->addWidget(getList());
    mainLayout->addWidget(getBottom());
    setLayout(mainLayout);
}

void    RetaillerPage::setMessage(const status_t status, const QString message)
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

void RetaillerPage::cleanItem()
{
    this->Li_ID->setText("");
    this->Li_name->setText("");
    this->Li_comment->setText("");
}

//setAttibutes

void   RetaillerPage::setGroupBoxAttributes(QGroupBox* groupBox, const QString name = "")
{
    groupBox->setObjectName(name);
    this->setStyleSheet("QGroupBox {background-color: white; border-style: outset; border-width: 2px; border-color: beige; font: bold 14px;border: 2px solid pink; }");
    groupBox->setTitle("");
}

void    RetaillerPage::setButtonAttributes(QPushButton* button, const QString toolTip = "")
{
   button->setToolTip(toolTip);
   button->setFont(QFont("Times", 18, QFont::Bold));
   button->setStyleSheet("QPushButton {background-color: white; border-width: 1px; border-color: grey; font: bold 14px; padding: 25px; }");
}

//Frames

QGroupBox* RetaillerPage::getHead()
{
    QGroupBox *groupBox = new QGroupBox(tr("RetaillerB"));
    this->setGroupBoxAttributes(groupBox, "RetaillerB");
    QHBoxLayout *Layout = new QHBoxLayout(groupBox);

    this->But_return = new QPushButton("Return");
    this->setButtonAttributes(But_return, "Return to menu");
    connect(But_return, SIGNAL(clicked()), this, SLOT(emitLoadMAIN_PAGE()));
    Layout->addWidget(But_return);

    this->But_add = new QPushButton("Add");
    this->setButtonAttributes(But_add, "Add new retailler");
    connect(But_add, SIGNAL(clicked()), this, SLOT(addItem()));
    Layout->addWidget(But_add);

    this->but_delete = new QPushButton("Delete");
    this->setButtonAttributes(but_delete, "Delete selected retailler");
    connect(but_delete, SIGNAL(clicked()), this, SLOT(deleteItem()));
    Layout->addWidget(but_delete);

    groupBox->setLayout(Layout);
    return (groupBox);
}

QGroupBox* RetaillerPage::getList()
{
    QGroupBox *groupBox = new QGroupBox(tr("RetaillerL"));
    this->setGroupBoxAttributes(groupBox, "RetaillerL");
    QVBoxLayout *Layout = new QVBoxLayout(groupBox);

    this->label = new QLabel(tr("Retailler"));
    label->setFont(QFont("Times", 20, QFont::Bold));
    Layout->addWidget(label);

    //The list
    this->modele = new QStandardItemModel(0, 3);
    QStringList lst;
    lst << "Id" << "Retailler" << "Comment";
    this->modele->setHorizontalHeaderLabels(lst);
    this->db.getRetailler(this->modele);
    this->table = new QTableView;
    table->setModel(modele);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(table->selectionModel(), SIGNAL(selectionChanged(const QItemSelection&, const QItemSelection&)), this, SLOT(rowSelected(const QItemSelection&, const QItemSelection&)));
    Layout->addWidget(table);

    this->LabMessage = new QLabel();
    Layout->addWidget(LabMessage);

    groupBox->setLayout(Layout);
    return (groupBox);
}

QGroupBox* RetaillerPage::getBottom()
{
    QGroupBox *groupBox = new QGroupBox(tr("RetaillerB"));
    this->setGroupBoxAttributes(groupBox, "RetaillerB");
    QHBoxLayout *Layout = new QHBoxLayout(groupBox);

    this->Li_name = new QLineEdit;
    this->Li_comment = new QTextEdit;
    this->Li_ID = new QLineEdit;
    this->Li_ID->setReadOnly(true);
    this->Li_ID->setStyleSheet("background: grey");
    QFormLayout *formLayout = new QFormLayout();
    formLayout->addRow(tr("&Name of retailler"), Li_name);
    formLayout->addRow(tr("&Comment retailler"), Li_comment);
    formLayout->addRow(tr("ID retailler"), Li_ID);
    Layout->addLayout(formLayout);

    this->But_valid = new QPushButton("Valid");
    this->setButtonAttributes(But_valid, "Valid modifications");
    connect(But_valid, SIGNAL(clicked()), this, SLOT(validItem()));
    Layout->addWidget(But_valid);

     groupBox->setLayout(Layout);
    return (groupBox);
}

//SLOTS
void RetaillerPage::rowSelected(const QItemSelection& selectionUp, const QItemSelection& selectionDown)
{
    (void)selectionUp;
    (void)selectionDown;
    //QMessageBox::information(this,"", QString::number(indexes.at(0).row()));

    QItemSelectionModel *select = table->selectionModel();
    this->Li_ID->setText(select->selectedRows(0).value(0).data().toString());
    this->Li_name->setText(select->selectedRows(1).value(0).data().toString());
    this->Li_comment->setText(select->selectedRows(2).value(0).data().toString());

}

void RetaillerPage::addItem()
{
    this->setMessage(SUCCESS, "Please insert new retailler");
    this->cleanItem();
}

void RetaillerPage::deleteItem()
{
    if (this->Li_ID->text().toStdString() != "")
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "deleted", "Do you want to delete the retailler '" + this->Li_name->text() + "'?",
                                        QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            if (this->db.deleteRetailler(this->Li_ID->text().toInt()))
            {
                this->setMessage(SUCCESS, "retailler deleted");
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
    this->db.getRetailler(this->modele);
    this->cleanItem();
}

void RetaillerPage::validItem()
{
    //Add or modify new Retailler
    if (this->Li_ID->text().toStdString() == "")
    {
        if (this->Li_name->text().toStdString() != "")
        {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "add", "Do you want to add the new retailler '" + this->Li_name->text() + "'?",
                                            QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                if (this->db.addRetailler(this->Li_name->text(), this->Li_comment->toPlainText()))
                {
                    this->setMessage(SUCCESS, "new retailler added");
                }
                else
                {
                    this->setMessage(FAIL, "Error occured");
                }
              } else {
                this->setMessage(FAIL, "");
              }
        }
    }
    else
    {
        if (this->Li_name->text().toStdString() != "")
        {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "update", "Do you want to update the retailler '" + this->Li_name->text() + "'?",
                                            QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                if (this->db.updateRetailler(this->Li_ID->text().toInt(), this->Li_name->text(), this->Li_comment->toPlainText()))
                {
                    this->setMessage(SUCCESS, "Retailler modified");
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
    this->db.getRetailler(this->modele);
    this->cleanItem();
}

void RetaillerPage::emitLoadMAIN_PAGE()
{
   emit loadPageParent(Tools_LDDS::MAIN_PAGE);
}
