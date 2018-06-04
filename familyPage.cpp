#include "familyPage.hpp"

FamilyPage::FamilyPage(DbHandler &newDb, QWidget *parent) : QWidget(parent), db(newDb)
{
}

FamilyPage::~FamilyPage()
{
}

void FamilyPage::setLayoutWindow()
{
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(getHead());
    mainLayout->addWidget(getList());
    mainLayout->addWidget(getBottom());
    setLayout(mainLayout);
}

void    FamilyPage::setMessage(const status_t status, const QString message)
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

void FamilyPage::cleanItem()
{
    this->Li_ID->setText("");
    this->Li_name->setText("");
}

//setAttibutes

void   FamilyPage::setGroupBoxAttributes(QGroupBox* groupBox, const QString name = "")
{
    groupBox->setObjectName(name);
    this->setStyleSheet("QGroupBox {background-color: white; border-style: outset; border-width: 2px; border-color: beige; font: bold 14px;border: 2px solid pink; }");
    groupBox->setTitle("");
}

void    FamilyPage::setButtonAttributes(QPushButton* button, const QString toolTip = "")
{
   button->setToolTip(toolTip);
   button->setFont(QFont("Times", 18, QFont::Bold));
   button->setStyleSheet("QPushButton {background-color: white; border-width: 1px; border-color: grey; font: bold 14px; padding: 25px; }");
}

void    FamilyPage::setLabelAttributes(QLabel* label)
{
    label->setFont(QFont("Times", 14, QFont::Bold));
}

void    FamilyPage::setLineAttributes(QLineEdit *line)
{
    line = NULL;
}

//Frames

QGroupBox* FamilyPage::getHead()
{
    QGroupBox *groupBox = new QGroupBox(tr("Family"));
    this->setGroupBoxAttributes(groupBox, "Family");

    QHBoxLayout *Layout = new QHBoxLayout(groupBox);

    this->But_return = new QPushButton("Return");
    this->setButtonAttributes(But_return, "Return to menu");
    connect(But_return, SIGNAL(clicked()), this, SLOT(emitLoadMAIN_PAGE()));
    Layout->addWidget(But_return);

    this->But_add = new QPushButton("Add");
    this->setButtonAttributes(But_add, "Add new family");
    connect(But_add, SIGNAL(clicked()), this, SLOT(addFamily()));
    Layout->addWidget(But_add);

    this->but_delete = new QPushButton("Delete");
    this->setButtonAttributes(but_delete, "Delete selected family");
    connect(but_delete, SIGNAL(clicked()), this, SLOT(deleteFamily()));
    Layout->addWidget(but_delete);

    groupBox->setLayout(Layout);
    return (groupBox);
}

QGroupBox* FamilyPage::getList()
{
    QGroupBox *groupBox = new QGroupBox(tr("Family"));
    this->setGroupBoxAttributes(groupBox, "Family");
    QVBoxLayout *Layout = new QVBoxLayout(groupBox);

    this->label = new QLabel(tr("Family article"));
    label->setFont(QFont("Times", 20, QFont::Bold));
    Layout->addWidget(label);

    //The list
    this->modele = new QStandardItemModel(0, 2);
    QStringList lst;
    lst << "Id" << "Family";
    this->modele->setHorizontalHeaderLabels(lst);
    this->db.getFamily(this->modele);
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

QGroupBox* FamilyPage::getBottom()
{
    QGroupBox *groupBox = new QGroupBox(tr("Family"));
    this->setGroupBoxAttributes(groupBox, "Family");
    QGridLayout *Layout = new QGridLayout(groupBox);

    this->La_name = new QLabel(tr("Nom de la famille d'article"));
    this->Li_name = new QLineEdit;
    this->La_ID = new QLabel(tr("ID famille article"));
    this->Li_ID = new QLineEdit;
    this->setLabelAttributes(this->La_name);
    this->setLabelAttributes(this->La_ID);
    this->Li_ID->setReadOnly(true);
    this->Li_ID->setStyleSheet("background: grey");

    this->But_valid = new QPushButton("Valid");
    this->setButtonAttributes(But_valid, "Valid modifications");
    connect(But_valid, SIGNAL(clicked()), this, SLOT(validFamily()));

    Layout->addWidget(La_name, 0, 0);
    Layout->addWidget(Li_name, 0, 1);
    Layout->addWidget(La_ID, 1, 0);
    Layout->addWidget(Li_ID, 1, 1);
    Layout->addWidget(But_valid, 2, 0, 2, 2);

    groupBox->setLayout(Layout);
    return (groupBox);
}

//SLOTS
void FamilyPage::rowSelected(const QItemSelection& selectionUp, const QItemSelection& selectionDown)
{
    (void)selectionUp;
    (void)selectionDown;

    QItemSelectionModel *select = table->selectionModel();
    this->Li_ID->setText(select->selectedRows(0).value(0).data().toString());
    this->Li_name->setText(select->selectedRows(1).value(0).data().toString());

}

void FamilyPage::addFamily()
{
    this->setMessage(SUCCESS, "Please insert new family");
     this->cleanItem();
}

void FamilyPage::deleteFamily()
{
    if (this->Li_ID->text().toStdString() != "")
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "deleted", "Do you want to delete the family '" + this->Li_name->text() + "'?",
                                        QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            if (this->db.deleteFamily(this->Li_ID->text().toInt()))
            {
                this->setMessage(SUCCESS, "family deleted");
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
    this->db.getFamily(this->modele);
     this->cleanItem();
}

void FamilyPage::validFamily()
{
    //Add or modify new family
    if (this->Li_ID->text().toStdString() == "")
    {
        if (this->Li_name->text().toStdString() != "")
        {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "add", "Do you want to add the new family '" + this->Li_name->text() + "'?",
                                            QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                if (this->db.addFamily(this->Li_name->text()))
                {
                    this->setMessage(SUCCESS, "new family added");
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
            reply = QMessageBox::question(this, "update", "Do you want to update the family '" + this->Li_name->text() + "'?",
                                            QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                if (this->db.updateFamily(this->Li_ID->text().toInt(), this->Li_name->text()))
                {
                    this->setMessage(SUCCESS, "family modified");
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
    this->db.getFamily(this->modele);
     this->cleanItem();
}

void FamilyPage::emitLoadMAIN_PAGE()
{
   emit loadPageParent(Tools_LDDS::MAIN_PAGE);
}
