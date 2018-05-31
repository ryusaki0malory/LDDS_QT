#include "typeArticlesPage.hpp"

TypeArticlesPage::TypeArticlesPage(DbHandler &newDb, QWidget *parent) : QWidget(parent), db(newDb)
{
}

TypeArticlesPage::~TypeArticlesPage()
{
}

void TypeArticlesPage::setLayoutWindow()
{
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(getHead());
    mainLayout->addWidget(getList());
    mainLayout->addWidget(getBottom());
    setLayout(mainLayout);
}

void    TypeArticlesPage::setMessage(const status_t status, const QString message)
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

void TypeArticlesPage::cleanItem()
{
    this->Li_ID->setText("");
    this->Li_name->setText("");
    this->Li_baseUnit->setCurrentIndex(-1);
    this->Li_qte->setValue(0);
}

void    TypeArticlesPage::loadQComboBox()
{
    QMap <QString, QString> map;
    this->db.getBaseUnit(map);
    for(QMap <QString, QString>::iterator it=map.begin() ; it!=map.end() ; ++it)
    {
        this->Li_baseUnit->addItem(it.value(), it.key());
    }
}

//setAttibutes

void   TypeArticlesPage::setGroupBoxAttributes(QGroupBox* groupBox, const QString name = "")
{
    groupBox->setObjectName(name);
    this->setStyleSheet("QGroupBox {background-color: white; border-style: outset; border-width: 2px; border-color: beige; font: bold 14px;border: 2px solid pink; }");
    groupBox->setTitle("");
}

void    TypeArticlesPage::setButtonAttributes(QPushButton* button, const QString toolTip = "")
{
   button->setToolTip(toolTip);
   button->setFont(QFont("Times", 18, QFont::Bold));
   button->setStyleSheet("QPushButton {background-color: white; border-width: 1px; border-color: grey; font: bold 14px; padding: 25px; }");
}

void    TypeArticlesPage::setLabelAttributes(QLabel* label)
{
    label->setFont(QFont("Times", 14, QFont::Bold));
}

void    TypeArticlesPage::setLineAttributes(QLineEdit *line)
{

}

//Frames

QGroupBox* TypeArticlesPage::getHead()
{
    QGroupBox *groupBox = new QGroupBox(tr("TypeArticleH"));
    this->setGroupBoxAttributes(groupBox, "TypeArticleH");
    QHBoxLayout *Layout = new QHBoxLayout(groupBox);

    this->But_return = new QPushButton("Return");
    this->setButtonAttributes(But_return, "Return to menu");
    connect(But_return, SIGNAL(clicked()), this, SLOT(emitLoadMAIN_PAGE()));
    Layout->addWidget(But_return);

    this->But_add = new QPushButton("Add");
    this->setButtonAttributes(But_add, "Add new type article d");
    connect(But_add, SIGNAL(clicked()), this, SLOT(addItem()));
    Layout->addWidget(But_add);

    this->but_delete = new QPushButton("Delete");
    this->setButtonAttributes(but_delete, "Delete selected type article");
    connect(but_delete, SIGNAL(clicked()), this, SLOT(deleteItem()));
    Layout->addWidget(but_delete);

    groupBox->setLayout(Layout);
    return (groupBox);
}

QGroupBox* TypeArticlesPage::getList()
{
    QGroupBox *groupBox = new QGroupBox(tr("TypeArticleL"));
    this->setGroupBoxAttributes(groupBox, "TypeArticleL");
    QVBoxLayout *Layout = new QVBoxLayout(groupBox);

    this->label = new QLabel(tr("Type article"));
    label->setFont(QFont("Times", 20, QFont::Bold));
    Layout->addWidget(label);

    //The list
    this->modele = new QStandardItemModel(0, 5);
    QStringList lst;
    lst << "Id" << "Name type article" << "Quantity unit" << "Base unit" << "IdBaseUnit";
    this->modele->setHorizontalHeaderLabels(lst);
    this->db.getTypeArticle(this->modele);
    this->table = new QTableView;
    table->setModel(modele);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setColumnHidden(4, true);
    connect(table->selectionModel(), SIGNAL(selectionChanged(const QItemSelection&, const QItemSelection&)), this, SLOT(rowSelected(const QItemSelection&, const QItemSelection&)));
    Layout->addWidget(table);

    this->LabMessage = new QLabel();
    Layout->addWidget(LabMessage);

    groupBox->setLayout(Layout);
    return (groupBox);
}

QGroupBox* TypeArticlesPage::getBottom()
{
    QGroupBox *groupBox = new QGroupBox(tr("TypeArticleB"));
    this->setGroupBoxAttributes(groupBox, "TypeArticleB");
    QGridLayout *Layout = new QGridLayout(groupBox);

    this->La_ID = new QLabel(tr("ID type article"));
    this->Li_ID = new QLineEdit;
    this->La_name = new QLabel(tr("Name of type article"));
    this->Li_name = new QLineEdit;
    this->La_qte = new QLabel(tr("Quantity unit"));
    this->Li_qte = new QDoubleSpinBox;
    this->La_baseUnit = new QLabel(tr("Base unit"));
    this->Li_baseUnit = new QComboBox;
    this->loadQComboBox();
    this->setLabelAttributes(this->La_ID);
    this->setLabelAttributes(this->La_name);
    this->setLabelAttributes(this->La_qte);
    this->setLabelAttributes(this->La_baseUnit);
    this->Li_ID->setReadOnly(true);
    this->Li_ID->setStyleSheet("background: grey");
    this->Li_qte->setDecimals(2);
    this->Li_qte->setMaximum(1000000);

    this->But_valid = new QPushButton("Valid");
    this->setButtonAttributes(But_valid, "Valid modifications");
    connect(But_valid, SIGNAL(clicked()), this, SLOT(validItem()));


    Layout->addWidget(La_name, 0, 0);
    Layout->addWidget(Li_name, 0, 1);
    Layout->addWidget(La_qte, 1, 0);
    Layout->addWidget(Li_qte, 1, 1);
    Layout->addWidget(La_baseUnit, 2, 0);
    Layout->addWidget(Li_baseUnit, 2, 1);
    Layout->addWidget(La_ID, 3, 0);
    Layout->addWidget(Li_ID, 3, 1);
    Layout->addWidget(But_valid, 4, 0, 4, 2);
    groupBox->setLayout(Layout);
    return (groupBox);
}

//SLOTS
void TypeArticlesPage::rowSelected(const QItemSelection& selectionUp, const QItemSelection& selectionDown)
{
    (void)selectionUp;
    (void)selectionDown;

    QItemSelectionModel *select = table->selectionModel();
    this->Li_ID->setText(select->selectedRows(0).value(0).data().toString());
    this->Li_name->setText(select->selectedRows(1).value(0).data().toString());
    this->Li_qte->setValue(select->selectedRows(2).value(0).data().toDouble());
    this->Li_baseUnit->setCurrentIndex(Li_baseUnit->findData(select->selectedRows(4).value(0).data().toString()));
    ;
}

void TypeArticlesPage::addItem()
{
    this->setMessage(SUCCESS, "Please insert a new base unit");
    this->cleanItem();
}

void TypeArticlesPage::deleteItem()
{
    if (this->Li_ID->text().toStdString() != "")
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "deleted", "Do you want to delete the type article '" + this->Li_name->text() + "'?",
                                        QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            if (this->db.deleteTypeArticle(this->Li_ID->text().toInt()))
            {
                this->setMessage(SUCCESS, "Type article deleted");
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
    this->db.getTypeArticle(this->modele);
    this->cleanItem();
}

void TypeArticlesPage::validItem()
{
    //Add or modify new type article
    if (this->Li_ID->text().toStdString() == "")
    {
        if (this->Li_name->text().toStdString() != "")
        {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "add", "Do you want to add the new type article '" + this->Li_name->text() + "'?",
                                            QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                if (this->db.addTypeArticle(this->Li_name->text(), this->Li_qte->value(), this->Li_baseUnit->itemData(this->Li_baseUnit->currentIndex()).toInt()))
                {
                    this->setMessage(SUCCESS, "new type article added");
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
            reply = QMessageBox::question(this, "update", "Do you want to update the type article '" + this->Li_name->text() + "'?",
                                            QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                if (this->db.updateTypeArticle(this->Li_ID->text().toInt(), this->Li_name->text(),  this->Li_qte->value(), this->Li_baseUnit->itemData(this->Li_baseUnit->currentIndex()).toInt()))
                {
                    this->setMessage(SUCCESS, "Type article modified");
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
    this->db.getTypeArticle(this->modele);
    this->cleanItem();
}

void TypeArticlesPage::emitLoadMAIN_PAGE()
{
   emit loadPageParent(Tools_LDDS::MAIN_PAGE);
}
