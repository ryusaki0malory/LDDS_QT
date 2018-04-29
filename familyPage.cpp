#include "familyPage.hpp"

FamilyPage::FamilyPage(QWidget *parent) : QWidget(parent)
{
    this->db = new DbManager();
    setLayoutWindow(parent);
}

FamilyPage::~FamilyPage()
{
    if (this->db != NULL)
    {
        delete(this->db);
    }
}

void FamilyPage::setLayoutWindow(QWidget *parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(parent);
    mainLayout->addWidget(getFrameHead());
    mainLayout->addWidget(getFrameList());
    mainLayout->addWidget(getFrameBottom());

    setLayout(mainLayout);
}

//setAttibutes
void   FamilyPage::setFrameAttributes(QFrame* frame, const QString name = "")
{
    frame->setObjectName(name);
    frame->setStyleSheet("#"+name+" { border: 1px solid blue; }");
    frame->setFrameShape(QFrame::StyledPanel);
}

void    FamilyPage::setButtonAttributes(QPushButton* button, const QString toolTip = "")
{
   button->setToolTip(toolTip);
   button->setFont(QFont("Times", 18, QFont::Bold));
}
//Frames
QFrame* FamilyPage::getFrameBottom()
{
    QFrame *frameBottom = new QFrame(this);
    this->setFrameAttributes(frameBottom, "Products");
    QHBoxLayout *LayoutBottom = new QHBoxLayout(frameBottom);

    this->Li_name = new QLineEdit;
    this->Li_ID = new QLineEdit;
    this->Li_ID->setReadOnly(true);
    QFormLayout *formLayout = new QFormLayout(frameBottom);
    formLayout->addRow(tr("&Nom de la famille d'article"), Li_name);
    formLayout->addRow(tr("ID famille article"), Li_ID);
    LayoutBottom->addLayout(formLayout);

    this->But_valid = new QPushButton("Valid", frameBottom);
    this->setButtonAttributes(But_valid, "Valid modifications");
    connect(But_valid, SIGNAL(clicked()), this, SLOT(validFamily()));
    LayoutBottom->addWidget(But_valid);

    this->But_cancel = new QPushButton("Cancel", frameBottom);
    this->setButtonAttributes(But_cancel, "Cancel modifications");
    connect(But_cancel, SIGNAL(clicked()), this, SLOT(cancelFamily()));
    LayoutBottom->addWidget(But_cancel);

    frameBottom->setLayout(LayoutBottom);
    return (frameBottom);
}

QFrame* FamilyPage::getFrameList()
{
    QFrame *frameList = new QFrame(this);
    this->setFrameAttributes(frameList, "Products");
    QVBoxLayout *LayoutList = new QVBoxLayout(frameList);

    this->label = new QLabel(tr("Famille article"));
    label->setFont(QFont("Times", 20, QFont::Bold));
    LayoutList->addWidget(label);

    //The list
    this->modeleFamily = new QStandardItemModel(0, 2);
    QStringList lst;
    lst << "Id" << "Family";
    this->modeleFamily->setHorizontalHeaderLabels(lst);
    this->db->getFamily(this->modeleFamily);
    this->table = new QTableView;
    table->setModel(modeleFamily);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(table->selectionModel(), SIGNAL(selectionChanged(const QItemSelection&, const QItemSelection&)), this, SLOT(rowSelected(const QItemSelection&, const QItemSelection&)));
    LayoutList->addWidget(table);

    this->LabMessage = new QLabel();
    LayoutList->addWidget(LabMessage);

    frameList->setLayout(LayoutList);
    return (frameList);
}

QFrame* FamilyPage::getFrameHead()
{
    QFrame *frameHead = new QFrame(this);
    this->setFrameAttributes(frameHead, "Products");
    QHBoxLayout *LayoutHead = new QHBoxLayout(frameHead);

    this->But_return = new QPushButton("Return", frameHead);
    this->setButtonAttributes(But_return, "Return to menu");
    connect(But_return, SIGNAL(clicked()), this, SLOT(emitLoadMAIN_PAGE()));
    LayoutHead->addWidget(But_return);

    this->But_add = new QPushButton("Add", frameHead);
    this->setButtonAttributes(But_add, "Add new family");
    connect(But_add, SIGNAL(clicked()), this, SLOT(addFamily()));
    LayoutHead->addWidget(But_add);

    this->but_delete = new QPushButton("Delete", frameHead);
    this->setButtonAttributes(but_delete, "Delete selected family");
    connect(but_delete, SIGNAL(clicked()), this, SLOT(deleteFamily()));
    LayoutHead->addWidget(but_delete);

    frameHead->setLayout(LayoutHead);
    return (frameHead);
}

//SLOTS
void FamilyPage::rowSelected(const QItemSelection& selectionUp, const QItemSelection& selectionDown)
{

    QModelIndexList indexes = table->selectionModel()->selection().indexes();
    //QMessageBox::information(this,"", QString::number(indexes.at(0).row()));

    QItemSelectionModel *select = table->selectionModel();
    this->Li_ID->setText(select->selectedRows(0).value(0).data().toString());
    this->Li_name->setText(select->selectedRows(1).value(0).data().toString());

}

void FamilyPage::addFamily()
{
    this->LabMessage->setText("Please insert new family");
    this->LabMessage->setFont(QFont("Times", 15, QFont::Bold));
    this->LabMessage->setStyleSheet("QLabel { color : green; }");

    this->Li_ID->setText("");
    this->Li_name->setText("");
}

void FamilyPage::deleteFamily()
{

}

void FamilyPage::validFamily()
{
    //Add or modify new family
    if (this->Li_ID->text().toStdString() == "")
    {
        if (this->Li_name->text().toStdString() != "")
        {
            this->db->addFamily(this->Li_name->text());
        }
    }
    else
    {
        if (this->Li_name->text().toStdString() != "")
        {
            this->db->modifyFamily(this->Li_ID->text(), this->Li_name->text());
        }
    }
    //actualise
    this->modeleFamily->setRowCount(0);
    this->db->getFamily(this->modeleFamily);
}

void FamilyPage::cancelFamily()
{

}

void FamilyPage::emitLoadMAIN_PAGE()
{
   emit loadPageParent(Tools_LDDS::MAIN_PAGE);
}
