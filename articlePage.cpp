#include "articlePage.hpp"

ArticlePage::ArticlePage(DbHandler &newDb, QWidget *parent) : QWidget(parent), db(newDb)
{
}

ArticlePage::~ArticlePage()
{
}

void ArticlePage::setLayoutWindow()
{
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(getHead());
    mainLayout->addWidget(getList());
    mainLayout->addWidget(getBottom());
    setLayout(mainLayout);
}

void    ArticlePage::setMessage(const status_t status, const QString message)
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

void ArticlePage::cleanItem()
{
    this->Li_ID->setText("");
    this->Li_name->setText("");
    this->Li_comment->setText("");
    this->Li_prix->setValue(0);
    this->Li_qte->setValue(0);
    this->Li_family->setCurrentIndex(-1);
    this->Li_retailer->setCurrentIndex(-1);
    this->Li_type->setCurrentIndex(-1);
    //this->Li_image->setCurrentIndex(-1);
}

void    ArticlePage::loadQComboBox()
{
    QMap <QString, QString> mapFamily;
    this->db.getFamily(mapFamily);
    for(QMap <QString, QString>::iterator it=mapFamily.begin() ; it!=mapFamily.end() ; ++it)
    {
        this->Li_family->addItem(it.value(), it.key());
    }

    QMap <QString, QString> mapRetailer;
    this->db.getRetailler(mapRetailer);
    for(QMap <QString, QString>::iterator it=mapRetailer.begin() ; it!=mapRetailer.end() ; ++it)
    {
        this->Li_retailer->addItem(it.value(), it.key());
    }

    QMap <QString, QString> maType;
    this->db.getTypeArticle(maType);
    for(QMap <QString, QString>::iterator it=maType.begin() ; it!=maType.end() ; ++it)
    {
        this->Li_type->addItem(it.value(), it.key());
    }
}
void ArticlePage::chooseImage()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Choose new image"),"", tr("Images (*.png *.jpg *.jpeg *.bmp *.gif)"));

    if (QString::compare(filename, QString()) != 0)
    {
        QImage image;
        bool valid = image.load(filename);

        if (valid)
        {
            image = image.scaledToWidth(this->Li_image->width(), Qt::SmoothTransformation);
            this->Li_image->setPixmap(QPixmap::fromImage(image));
        }
    }
}
//setAttibutes

void   ArticlePage::setGroupBoxAttributes(QGroupBox* groupBox, const QString name = "")
{
    groupBox->setObjectName(name);
    this->setStyleSheet("QGroupBox {background-color: white; border-style: outset; border-width: 2px; border-color: beige; font: bold 14px;border: 2px solid pink; }");
    groupBox->setTitle("");
}

void    ArticlePage::setButtonAttributes(QPushButton* button, const QString toolTip = "")
{
   button->setToolTip(toolTip);
   button->setFont(QFont("Times", 18, QFont::Bold));
   button->setStyleSheet("QPushButton {background-color: white; border-width: 1px; border-color: grey; font: bold 14px; padding: 25px; }");
}

void    ArticlePage::setLabelAttributes(QLabel* label)
{
    label->setFont(QFont("Times", 14, QFont::Bold));
}

void    ArticlePage::setLineAttributes(QLineEdit *line)
{

}

//Frames

QGroupBox* ArticlePage::getHead()
{
    QGroupBox *groupBox = new QGroupBox(tr("ArticleH"));
    this->setGroupBoxAttributes(groupBox, "ArticleH");
    QHBoxLayout *Layout = new QHBoxLayout(groupBox);

    this->But_return = new QPushButton("Return");
    this->setButtonAttributes(But_return, "Return to menu");
    connect(But_return, SIGNAL(clicked()), this, SLOT(emitLoadMAIN_PAGE()));
    Layout->addWidget(But_return);

    this->But_add = new QPushButton("Add");
    this->setButtonAttributes(But_add, "Add new article");
    connect(But_add, SIGNAL(clicked()), this, SLOT(addItem()));
    Layout->addWidget(But_add);

    this->but_delete = new QPushButton("Delete");
    this->setButtonAttributes(but_delete, "Delete selected article");
    connect(but_delete, SIGNAL(clicked()), this, SLOT(deleteItem()));
    Layout->addWidget(but_delete);

    groupBox->setLayout(Layout);
    return (groupBox);
}

QGroupBox* ArticlePage::getList()
{
    QGroupBox *groupBox = new QGroupBox(tr("ArticleL"));
    this->setGroupBoxAttributes(groupBox, "ArticleL");
    QVBoxLayout *Layout = new QVBoxLayout(groupBox);

    this->label = new QLabel(tr("Article"));
    label->setFont(QFont("Times", 20, QFont::Bold));
    Layout->addWidget(label);

    //The list
    this->modele = new QStandardItemModel(0, 12);
    QStringList lst;
    lst << "Id" << "Name article" << "Qte. article" << "Family" << "IdFamily" << "Price article" << "Retailer" << "IDRetailler" << "Type" << " IDType" << "Comment" << "Image";
    this->modele->setHorizontalHeaderLabels(lst);
    this->db.getArticle(this->modele);
    this->table = new QTableView;
    table->setModel(modele);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->horizontalHeader()->setSectionResizeMode(11, QHeaderView::Stretch);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setColumnHidden(4, true);
    table->setColumnHidden(7, true);
    table->setColumnHidden(9, true);
    connect(table->selectionModel(), SIGNAL(selectionChanged(const QItemSelection&, const QItemSelection&)), this, SLOT(rowSelected(const QItemSelection&, const QItemSelection&)));
    Layout->addWidget(table);

    this->LabMessage = new QLabel();
    Layout->addWidget(LabMessage);

    groupBox->setLayout(Layout);
    return (groupBox);
}

QGroupBox* ArticlePage::getBottom()
{
    QGroupBox *groupBox = new QGroupBox(tr("ArticleB"));
    this->setGroupBoxAttributes(groupBox, "ArticleB");
    QGridLayout *Layout = new QGridLayout(groupBox);

    this->La_ID = new QLabel(tr("ID Article"));
    this->Li_ID = new QLineEdit;
    this->La_name = new QLabel(tr("Name article"));
    this->Li_name = new QLineEdit;
    this->La_comment = new QLabel(tr("Comment article"));
    this->Li_comment = new QTextEdit;
    this->La_prix = new QLabel(tr("Prix article"));
    this->Li_prix = new QDoubleSpinBox;
    this->La_qte = new QLabel(tr("Qte article"));
    this->Li_qte = new QDoubleSpinBox;
    this->La_family = new QLabel(tr("Family article"));
    this->Li_family = new QComboBox;
    this->La_retailer = new QLabel(tr("Retailer article"));
    this->Li_retailer = new QComboBox;
    this->La_type = new QLabel(tr("Type article"));
    this->Li_type = new QComboBox;
    this->La_image = new QPushButton(tr("Image article"));
    this->Li_image = new QLabel;
    connect(La_image, SIGNAL(clicked()), this, SLOT(chooseImage()));
    this->loadQComboBox();
    this->setLabelAttributes(this->La_name);
    this->setLabelAttributes(this->La_ID);
    this->setLabelAttributes(this->La_name);
    this->setLabelAttributes(this->La_comment);
    this->setLabelAttributes(this->La_prix);
    this->setLabelAttributes(this->La_qte);
    this->setLabelAttributes(this->La_family);
    this->setLabelAttributes(this->La_retailer);
    this->setLabelAttributes(this->La_type);
    this->setButtonAttributes(this->La_image, "Change image article");
    this->Li_ID->setReadOnly(true);
    this->Li_ID->setStyleSheet("background: grey");
    this->Li_prix->setDecimals(2);
    this->Li_prix->setMaximum(1000000);

//    QString path = this->db.getPathLogo();
//    if (QString::compare(path,QString()) != 0)
//    {
//        QImage image;
//        bool valid = image.load(path);

//        if (valid)
//        {
//            //image = image.scaledToWidth(this->_logo->width(), Qt::SmoothTransformation);
//            this->Li_image->setPixmap(QPixmap::fromImage(image));
//        }
//    }

    this->But_valid = new QPushButton("Valid");
    this->setButtonAttributes(But_valid, "Valid modifications");
    connect(But_valid, SIGNAL(clicked()), this, SLOT(validItem()));

    Layout->addWidget(La_name, 0, 0);
    Layout->addWidget(Li_name, 0, 1);
    Layout->addWidget(La_ID, 0, 2);
    Layout->addWidget(Li_ID, 0, 3);
    Layout->addWidget(La_prix, 1, 0);
    Layout->addWidget(Li_prix, 1, 1);
    Layout->addWidget(La_qte, 2, 0);
    Layout->addWidget(Li_qte, 2, 1);
    Layout->addWidget(La_family, 3, 0);
    Layout->addWidget(Li_family, 3, 1);
    Layout->addWidget(La_retailer, 4, 0);
    Layout->addWidget(Li_retailer, 4, 1);
    Layout->addWidget(La_type, 5, 0);
    Layout->addWidget(Li_type, 5, 1);
    Layout->addWidget(La_image, 1, 2, 1, 3);
    Layout->addWidget(Li_image, 2, 2, 5, 3);
    Layout->addWidget(La_comment, 6, 0);
    Layout->addWidget(Li_comment, 7, 0, 7, 2);
    Layout->addWidget(But_valid, 7, 2, 7, 4);

    groupBox->setLayout(Layout);
    return (groupBox);
}

//SLOTS
void ArticlePage::rowSelected(const QItemSelection& selectionUp, const QItemSelection& selectionDown)
{
    (void)selectionUp;
    (void)selectionDown;

    QItemSelectionModel *select = table->selectionModel();
    this->Li_ID->setText(select->selectedRows(0).value(0).data().toString());
    this->Li_name->setText(select->selectedRows(1).value(0).data().toString());
    this->Li_qte->setValue(select->selectedRows(2).value(0).data().toDouble());
    this->Li_family->setCurrentIndex(Li_family->findData(select->selectedRows(4).value(0).data().toString()));
    this->Li_prix->setValue(select->selectedRows(5).value(0).data().toDouble());
    this->Li_retailer->setCurrentIndex(Li_retailer->findData(select->selectedRows(7).value(0).data().toString()));
    this->Li_type->setCurrentIndex(Li_type->findData(select->selectedRows(9).value(0).data().toString()));
    this->Li_comment->setText(select->selectedRows(10).value(0).data().toString());
    //this->Li_image->setPixmap(select->selectedRows(11).value(0).data<QPixmap>());
}

void ArticlePage::addItem()
{
    this->setMessage(SUCCESS, "Please insert a new article");
    this->cleanItem();
}

void ArticlePage::deleteItem()
{
    if (this->Li_ID->text().toStdString() != "")
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "deleted", "Do you want to delete the article '" + this->Li_name->text() + "'?",
                                        QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            if (this->db.deleteArticle(this->Li_ID->text().toInt()))
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
    this->db.getArticle(this->modele);
    this->cleanItem();
}

void ArticlePage::validItem()
{
    //Add or modify new type article
    if (this->Li_ID->text().toStdString() == "")
    {
        if (this->Li_name->text().toStdString() != "")
        {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "add", "Do you want to add the new article '" + this->Li_name->text() + "'?",
                                            QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                const QPixmap *pixmapTempo = this->Li_image->pixmap();
                QByteArray bArray;
                if (pixmapTempo)
                {
                    QImage imageTempo(pixmapTempo->toImage());
                    QBuffer buffer(&bArray);
                    buffer.open(QIODevice::WriteOnly);
                    imageTempo.save(&buffer, "PNG");

                }
                if (this->db.addArticle(this->Li_name->text(), (double)this->Li_prix->value(), (double)this->Li_qte->value(),
                                         this->Li_family->itemData(this->Li_family->currentIndex()).toInt(),
                                          this->Li_retailer->itemData(this->Li_retailer->currentIndex()).toInt(),
                                           this->Li_type->itemData(this->Li_type->currentIndex()).toInt(),
                                            this->Li_comment->toPlainText(), bArray))
                {
                    this->setMessage(SUCCESS, "new article added");
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
            reply = QMessageBox::question(this, "update", "Do you want to update the article '" + this->Li_name->text() + "'?",
                                            QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::Yes) {
//                if (this->db.updateArticle(this->Li_ID->text().toInt(), this->Li_name->text(), this->Li_mult->value()))
//                {
//                    this->setMessage(SUCCESS, "Base unit modified");
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
    this->db.getArticle(this->modele);
    this->cleanItem();
}

void ArticlePage::emitLoadMAIN_PAGE()
{
   emit loadPageParent(Tools_LDDS::MAIN_PAGE);
}
