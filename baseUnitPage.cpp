#include "baseUnitPage.hpp"

BaseUnitPage::BaseUnitPage(DbHandler &newDb, QWidget *parent) : QWidget(parent), db(newDb)
{
}

BaseUnitPage::~BaseUnitPage()
{
}

void BaseUnitPage::setLayoutWindow()
{
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(getHead());
    mainLayout->addWidget(getList());
    mainLayout->addWidget(getBottom());
    setLayout(mainLayout);
}

void    BaseUnitPage::setMessage(const status_t status, const QString message)
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

void BaseUnitPage::cleanItem()
{
    this->Li_ID->setText("");
    this->Li_name->setText("");
    this->Li_mult->setValue(0);
}

//setAttibutes

void   BaseUnitPage::setGroupBoxAttributes(QGroupBox* groupBox, const QString name = "")
{
    groupBox->setObjectName(name);
    this->setStyleSheet("QGroupBox {background-color: white; border-style: outset; border-width: 2px; border-color: beige; font: bold 14px;border: 2px solid pink; }");
    groupBox->setTitle("");
}

void    BaseUnitPage::setButtonAttributes(QPushButton* button, const QString toolTip = "")
{
   button->setToolTip(toolTip);
   button->setFont(QFont("Times", 18, QFont::Bold));
   button->setStyleSheet("QPushButton {background-color: white; border-width: 1px; border-color: grey; font: bold 14px; padding: 25px; }");
}

void    BaseUnitPage::setLabelAttributes(QLabel* label)
{
    label->setFont(QFont("Times", 14, QFont::Bold));
}

void    BaseUnitPage::setLineAttributes(QLineEdit *line)
{

}

//Frames

QGroupBox* BaseUnitPage::getHead()
{
    QGroupBox *groupBox = new QGroupBox(tr("Base_unitH"));
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

QGroupBox* BaseUnitPage::getList()
{
    QGroupBox *groupBox = new QGroupBox(tr("Base_unitL"));
    this->setGroupBoxAttributes(groupBox, "Base_unitL");
    QVBoxLayout *Layout = new QVBoxLayout(groupBox);

    this->label = new QLabel(tr("Base unit"));
    label->setFont(QFont("Times", 20, QFont::Bold));
    Layout->addWidget(label);

    //The list
    this->modele = new QStandardItemModel(0, 3);
    QStringList lst;
    lst << "Id" << "Name base unit" << "Mult. base unit";
    this->modele->setHorizontalHeaderLabels(lst);
    this->db.getBaseUnit(this->modele);
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

QGroupBox* BaseUnitPage::getBottom()
{
    QGroupBox *groupBox = new QGroupBox(tr("Base_unitB"));
    this->setGroupBoxAttributes(groupBox, "Base_unitB");
    QGridLayout *Layout = new QGridLayout(groupBox);

    this->La_ID = new QLabel(tr("ID base units"));
    this->Li_ID = new QLineEdit;
    this->La_name = new QLabel(tr("Name of base unit"));
    this->Li_name = new QLineEdit;
    this->La_mult = new QLabel(tr("Base unit multiplicator"));
    this->Li_mult = new QDoubleSpinBox;
    this->setLabelAttributes(this->La_name);
    this->setLabelAttributes(this->La_mult);
    this->setLabelAttributes(this->La_ID);
    this->Li_ID->setReadOnly(true);
    this->Li_ID->setStyleSheet("background: grey");
    this->Li_mult->setDecimals(2);
    this->Li_mult->setMaximum(1000000);

    this->But_valid = new QPushButton("Valid");
    this->setButtonAttributes(But_valid, "Valid modifications");
    connect(But_valid, SIGNAL(clicked()), this, SLOT(validItem()));

    Layout->addWidget(La_name, 0, 0);
    Layout->addWidget(Li_name, 0, 1);
    Layout->addWidget(La_mult, 1, 0);
    Layout->addWidget(Li_mult, 1, 1);
    Layout->addWidget(La_ID, 2, 0);
    Layout->addWidget(Li_ID, 2, 1);
    Layout->addWidget(But_valid, 3, 0, 3, 2);

    groupBox->setLayout(Layout);
    return (groupBox);
}

//SLOTS
void BaseUnitPage::rowSelected(const QItemSelection& selectionUp, const QItemSelection& selectionDown)
{
    (void)selectionUp;
    (void)selectionDown;

    QItemSelectionModel *select = table->selectionModel();
    this->Li_ID->setText(select->selectedRows(0).value(0).data().toString());
    this->Li_name->setText(select->selectedRows(1).value(0).data().toString());
    this->Li_mult->setValue(select->selectedRows(2).value(0).data().toDouble());
}

void BaseUnitPage::addItem()
{
    this->setMessage(SUCCESS, "Please insert a new base unit");
    this->cleanItem();
}

void BaseUnitPage::deleteItem()
{
    if (this->Li_ID->text().toStdString() != "")
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "deleted", "Do you want to delete the base unit '" + this->Li_name->text() + "'?",
                                        QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            if (this->db.deleteBaseUnit(this->Li_ID->text().toInt()))
            {
                this->setMessage(SUCCESS, "base unit deleted");
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
    this->db.getBaseUnit(this->modele);
    this->cleanItem();
}

void BaseUnitPage::validItem()
{
    //Add or modify new type article
    if (this->Li_ID->text().toStdString() == "")
    {
        if (this->Li_name->text().toStdString() != "")
        {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "add", "Do you want to add the new base unit '" + this->Li_name->text() + "'?",
                                            QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                if (this->db.addBaseUnit(this->Li_name->text(), (double)this->Li_mult->value()))
                {
                    this->setMessage(SUCCESS, "new base unit added");
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
            reply = QMessageBox::question(this, "update", "Do you want to update the base unit '" + this->Li_name->text() + "'?",
                                            QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                if (this->db.updateBaseUnit(this->Li_ID->text().toInt(), this->Li_name->text(), this->Li_mult->value()))
                {
                    this->setMessage(SUCCESS, "Base unit modified");
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
    this->db.getBaseUnit(this->modele);
    this->cleanItem();
}

void BaseUnitPage::emitLoadMAIN_PAGE()
{
   emit loadPageParent(Tools_LDDS::MAIN_PAGE);
}
