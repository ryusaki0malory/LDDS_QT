#include "parameterPage.hpp"

ParameterPage::ParameterPage(DbHandler &newDb, QWidget *parent) : QWidget(parent), db(newDb)
{

}

ParameterPage::~ParameterPage()
{

}

void ParameterPage::setLayoutWindow()
{
    QVBoxLayout *mainLayout = new QVBoxLayout();
    this->createFrameParameters();
    mainLayout->addWidget(this->parameterGroupBox);
    setLayout(mainLayout);
}

//setAttibutes

void   ParameterPage:: setGroupBoxAttributes()
{
    this->setStyleSheet("QGroupBox {background-color: white; border-style: outset; border-width: 2px; border-color: beige; font: bold 14px;border: 2px solid white; border-bottom: 2px solid pink; }");
}

void    ParameterPage::setButtonAttributes(QPushButton* button, const QString toolTip = "")
{
   button->setToolTip(toolTip);
   button->setFont(QFont("Times", 18, QFont::Bold));
   button->setStyleSheet("QPushButton {background-color: white; border-width: 1px; border-color: grey; font: bold 14px;padding: 25px; }");
}

//Frames

void ParameterPage::createFrameParameters()
{
    this->parameterGroupBox = new QGroupBox(tr("Parameter"));
    QVBoxLayout *LayoutParameters = new QVBoxLayout(parameterGroupBox);

    QPushButton *But_return = new QPushButton("Return");
    this->setButtonAttributes(But_return, "Return to menu");
    connect(But_return, SIGNAL(clicked()), this, SLOT(emitLoadMAIN_PAGE()));
    LayoutParameters->addWidget(But_return);

    QPushButton *First_Init = new QPushButton("First initialisation");
    this->setButtonAttributes(First_Init,"First initialisation of the application");
    connect(First_Init, SIGNAL(clicked()), this, SLOT(firstInit()));
    LayoutParameters->addWidget(First_Init);

    QPushButton *Change_Logo = new QPushButton("Logo");
    this->setButtonAttributes(Change_Logo,"Change the logo of main page");
    connect(Change_Logo, SIGNAL(clicked()), this, SLOT(changeLogo()));
    LayoutParameters->addWidget(Change_Logo);

    QPushButton *Change_Color = new QPushButton("Color");
    this->setButtonAttributes(Change_Color,"Change the colors of the application");
    connect(Change_Color, SIGNAL(clicked()), this, SLOT(changeColor()));
    LayoutParameters->addWidget(Change_Color);

    this->parameterGroupBox->setLayout(LayoutParameters);

}

//SLOTS
void ParameterPage::emitLoadMAIN_PAGE()
{
   emit loadPageParent(Tools_LDDS::MAIN_PAGE);
}

void ParameterPage::firstInit()
{
    QMessageBox message;
    std::fstream file;

    file.open("LDDS.ini");

    if (!file.is_open()) //File has not been created!
    {
            qDebug() << "LDDS.ini not found. Creating...";
            file.open("LDDS.ini", std::ios::out|std::ios::in|std::ios::trunc);
            if (!file.is_open())
            {
                qDebug() << "Error creating file LDDS.ini !" ;
                file.close(); //Is this necessary since the is_open() returns false?
            }
            file << "//FTP onnection\n";
            file << "SERVEUR=\n";
            file << "PORT=\n";
            file << "//BDD informations\n";
            file << "BDD_PATH=/Users/ryusaki0malory/Desktop/LDDS_BDD/\n";
            file << "BDD_VER=0.1.1\n";
            file << "BDD_LAST_UPDATE=20180101\n";
            file << "//APPLICATION\n";
            file << "VER_APP=1.0\n";
            message.setText("First init ok, please restart the application!");
            message.exec();
    }
        else //File already exists, meaning it has a number in it
        {
            message.setText("LDDS.init already exist!");
            message.exec();
        }
        file.close();


}

void ParameterPage::changeLogo()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Choose new logo"),"", tr("Images (*.png *.jpg *.jpeg *.bmp *.gif)"));

    if (QString::compare(filename, QString()) != 0)
    {
        QImage image;
        bool valid = image.load(filename);
        if (valid)
        {
            QPixmap pixmapTempo;
            pixmapTempo = pixmapTempo.fromImage(image);
            QByteArray bArray;
            QImage imageTempo(pixmapTempo.toImage());
            QBuffer buffer(&bArray);
            buffer.open(QIODevice::WriteOnly);
            imageTempo.save(&buffer, "PNG");
            QString IDParameter("");
            if ((IDParameter = this->db.parameterExist()) == "")
            {
                if (this->db.addParameter(bArray))
                {

                }
            }
            else
            {
                if (this->db.updateParameter(IDParameter, bArray))
                {

                 }
            }
        }

    }
}

void ParameterPage::changeColor()
{

}
