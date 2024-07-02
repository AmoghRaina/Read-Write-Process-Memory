    #include "mainwindow.h"
    #include "./ui_mainwindow.h"
    #include <windows.h>
    #include <QTimer>
    #include <QDebug>
    #include <tlhelp32.h>

    using namespace std;
    MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow)
    {
        ui->setupUi(this);

        ui->lineEdit_changevalue->setEnabled(false);
        ui->lineEdit_changevalue->setStyleSheet("QLineEdit:disabled { background-color: rgb(42, 42, 42); color: #aaaaaa; }");
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_2->setStyleSheet("QPushButton:disabled { background-color: rgb(42, 42, 42); color: #aaaaaa; }");
        ui->lineEdit->setEnabled(false);
        ui->lineEdit->setStyleSheet("QLineEdit:disabled { background-color: rgb(42, 42, 42); color: #aaaaaa; }");

        connect(ui->pushButton,&QPushButton::clicked,this,&MainWindow::read);
        connect(ui->pushButton_2,&QPushButton::clicked,this,&MainWindow::check);
        connect(ui->comboBox,QOverload<int>::of(&QComboBox::currentIndexChanged),this,&MainWindow::theme);

    }

    MainWindow::~MainWindow()
    {
        delete ui;
    }
    void MainWindow::read(){
        const wchar_t* app = ui->lineEdit_2->text().toStdWString().c_str();;

        processid = 0;
        HANDLE hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);
        PROCESSENTRY32 proent;
        proent.dwSize = sizeof(proent);
        bool found = false;
        if (Process32First(hsnap, &proent)) {
            do {
                if (!_wcsicmp(proent.szExeFile,app)) {
                    processid = proent.th32ProcessID;
                    // QString text2 = QString::fromWCharArray(app);


                    ui->label_name->setText(ui->lineEdit_2->text());
                    // ui->label_name->setStyleSheet("color:green;background-color:rgb(45, 11, 47)");
                    ui->label_name->setPalette(createColorPalette(Qt::green));

                    ui->label_idle_2->setText("attached");
                    // ui->label_idle_2->setStyleSheet("color:green;background-color: rgb(45, 11, 47)");
                    ui->label_idle_2->setPalette(createColorPalette(Qt::green));

                    ui->lineEdit->setEnabled(true);
                    found =true;
                    break;

                }



            } while (Process32Next(hsnap, &proent));
            if (found==false){
                ui->label_name->setPalette(createColorPalette(Qt::red));
                ui->label_name->setText("NotFound");
                // ui->label_name->setStyleSheet("color:red;background-color:rgb(45, 11, 47)");

                ui->label_idle_2->setText("Idle");
                // ui->label_idle->setStyleSheet("color:white;background-color: rgb(45, 11, 47)");
                ui->label_idle_2->setPalette(createColorPalette(Qt::white));

                ui->label_idle->setText("Idle");
                // ui->label_idle_2->setStyleSheet("color:white;background-color: rgb(45, 11, 47)");
                ui->label_idle->setPalette(createColorPalette(Qt::white));

                ui->lineEdit->setEnabled(false);
                ui->lineEdit->setText("");
                ui->lineEdit_changevalue->setEnabled(false);
                ui->pushButton_2->setEnabled(false);
            }


        }

        process = OpenProcess(PROCESS_ALL_ACCESS,NULL,processid);
        QString text1 = QString::number(processid);
        ui->label_processid->setText(text1);
        offsetsinput = ui->lineEdit->text();
        offsets =strtoull(offsetsinput.toStdString().c_str(), nullptr, 0); // ---> conversion from string to dword64

        DWORD temp = 0;
        if( ui->label_idle_2->text()=="attached"&&ui->lineEdit->text()!=""){
        if(ReadProcessMemory(process, (LPCVOID*)offsets, &temp, sizeof(temp), 0)){
             // ui->label_idle->setStyleSheet("color:green;background-color: rgb(45, 11, 47)");
            ui->label_idle->setPalette(createColorPalette(Qt::green));

            ui->label_idle->setText("Success reading memory");
        }
        else{
            DWORD geterror = GetLastError();
            QString error = QString::number(geterror);
            if(error!="0"){
            // ui->label_idle->setStyleSheet("color:red;background-color: rgb(45, 11, 47)");
                ui->label_idle->setPalette(createColorPalette(Qt::red));

            ui->label_idle->setText(error);
            }
            else{
                // ui->label_idle->setStyleSheet("color:red;background-color: rgb(45, 11, 47)");
                ui->label_idle->setPalette(createColorPalette(Qt::red));

                ui->label_idle->setText("error reading memory");
            }
        }
        }
        QString text = QString::number(temp);
        ui->label_currentvalue->setText(text);
        if(!(processid==0)&&ui->label_currentvalue->text()!="0"){
            ui->lineEdit_changevalue->setEnabled(true);
            ui->pushButton_2->setEnabled(true);

        }
        else{
            ui->lineEdit_changevalue->setEnabled(false);
            ui->lineEdit_changevalue->setText("");
            ui->pushButton_2->setEnabled(false);

        }

    }
    void MainWindow::check(){

        QString storing = ui->lineEdit_changevalue->text();
        int change = storing.toInt();
        bool success=false;
        if(WriteProcessMemory(process,(LPCVOID*)offsets,&change,sizeof(change),0)){
            // ui->label_idle->setStyleSheet("color:green;background-color: rgb(45, 11, 47)");
            ui->label_idle->setPalette(createColorPalette(Qt::green));

            ui->label_idle->setText("Success writing to memory");
            success=true;


        }
        else{

            DWORD geterror = GetLastError();
            if (geterror != ERROR_SUCCESS)
            {
                QString error = QString::number(geterror);
                // ui->label_idle->setStyleSheet("color:red;background-color: rgb(45, 11, 47)");
                ui->label_idle->setPalette(createColorPalette(Qt::red));

                ui->label_idle->setText("Error: " + error);
            }
            else
            {
                // ui->label_idle->setStyleSheet("color:red;background-color: rgb(45, 11, 47)");
                ui->label_idle->setPalette(createColorPalette(Qt::red));

                ui->label_idle->setText("Unknown fault");
            }

        }
        if(success){
        QTimer::singleShot(2000, this,[this](){
        read();
        });
    }
    }

    void MainWindow::theme(int index){
        if (index == 1) {
            this->setStyleSheet("background-color: rgb(5, 5, 5)");//----->theme darkest
            ui->label_2->setStyleSheet("background-color: rgb(12, 12, 12);border-radius:15px");//----->outerline dark
            ui->c_2->setStyleSheet("background-color: rgb(12, 12, 12);border-radius:15px");//------>made by



            ui->label->setStyleSheet("background-color: rgb(20, 20, 20);border-radius:15px");//----->outerline light
            ui->lineEdit->setStyleSheet("background-color: rgb(20, 20, 20);border-radius:15px"); //-----> placeholder text
            ui->lineEdit_2->setStyleSheet("background-color: rgb(20, 20, 20);border-radius:15px");//-----> placeholder text
            ui->lineEdit_changevalue->setStyleSheet("background-color: rgb(20, 20, 20);border-radius:15px");//-----> placeholder text
            ui->label_9->setStyleSheet("background-color:rgb(20,20,20)");
            ui->comboBox->setStyleSheet("background-color:rgb(20,20,20)");


            ui->label_3->setStyleSheet("background-color: rgb(25, 25, 25);border-radius:15px");//----->inner label dark+
            ui->label_6->setStyleSheet("background-color: rgb(25, 25, 25);border-radius:15px");//----->inner label2 dark+
            ui->c->setStyleSheet("background-color: rgb(25, 25, 25);border-radius:15px");//----->"current value"
            ui->label_7->setStyleSheet("background-color: rgb(25, 25, 25);border-radius:15px");//----->"processid"
            ui->label_5->setStyleSheet("background-color: rgb(25, 25, 25);border-radius:15px");//----->"Application"
            ui->label_name->setStyleSheet("background-color: rgb(25, 25, 25);border-radius:15px");
            ui->label_processid->setStyleSheet("background-color: rgb(25, 25, 25);border-radius:15px");
            ui->label_idle->setStyleSheet("background-color: rgb(25, 25, 25);border-radius:15px");
            ui->label_idle_2->setStyleSheet("background-color: rgb(25, 25, 25);border-radius:15px");
            ui->textEdit->setStyleSheet("background-color: rgb(25, 25, 25);border-radius:15px");
            ui->label_currentvalue->setStyleSheet("background-color: rgb(25, 25, 25);border-radius:15px");//current value*
            ui->label_4->setStyleSheet("background-color: rgb(25, 25, 25);border-radius:15px");// information text
            ui->label_10->setStyleSheet("background-color: rgb(25, 25, 25);border-radius:15px");// status text


            ui->lineEdit_changevalue->setEnabled(false);
            ui->lineEdit_changevalue->setStyleSheet("QLineEdit:disabled { background-color: rgb(42, 42, 42); color: #aaaaaa; }");
            ui->pushButton_2->setEnabled(false);
            ui->pushButton_2->setStyleSheet("QPushButton:disabled { background-color: rgb(42, 42, 42); color: #aaaaaa; }");
            ui->lineEdit->setEnabled(false);
            ui->lineEdit->setStyleSheet("QLineEdit:disabled { background-color: rgb(42, 42, 42); color: #aaaaaa; }");


        }
        if(index==0){
            this->setStyleSheet("background-color: rgb(58, 14, 61)");//----->theme
            ui->label_2->setStyleSheet("background-color: rgb(56, 4, 65);border-radius:15px");//----->innerline
            ui->c_2->setStyleSheet("background-color: rgb(56, 4, 65);border-radius:15px");//------>made by

            ui->label->setStyleSheet("background-color: rgb(50, 12, 49);border-radius:15px");//----->outerline light
            ui->lineEdit->setStyleSheet("background-color: rgb(50, 12, 49);border-radius:15px"); //-----> placeholder text
            ui->lineEdit_2->setStyleSheet("background-color: rgb(50, 12, 49);border-radius:15px");//-----> placeholder text
            ui->lineEdit_changevalue->setStyleSheet("background-color: rgb(50, 12, 49);border-radius:15px");//-----> placeholder text
            ui->label_9->setStyleSheet("background-color:rgb(50, 12, 49)");
            ui->comboBox->setStyleSheet("background-color:rgb(50, 12, 49)");


            ui->label_3->setStyleSheet("background-color: rgb(45, 11, 47);border-radius:15px");//----->inner label dark+
            ui->label_6->setStyleSheet("background-color: rgb(45, 11, 47);border-radius:15px");//----->inner label2 dark+
            ui->c->setStyleSheet("background-color: rgb(45, 11, 47);border-radius:15px");//----->"current value"
            ui->label_7->setStyleSheet("background-color: rgb(45, 11, 47);border-radius:15px");//----->"processid"
            ui->label_5->setStyleSheet("background-color: rgb(45, 11, 47);border-radius:15px");//----->"Application"

            ui->label_name->setStyleSheet("background-color: rgb(45, 11, 47);border-radius:15px");
            ui->label_processid->setStyleSheet("background-color: rgb(45, 11, 47);border-radius:15px");
            ui->label_idle->setStyleSheet("background-color: rgb(45, 11, 47);border-radius:15px");
            ui->label_idle_2->setStyleSheet("background-color: rgb(45, 11, 47);border-radius:15px");
            ui->textEdit->setStyleSheet("background-color: rgb(45, 11, 47);border-radius:15px");
            ui->label_currentvalue->setStyleSheet("background-color: rgb(45, 11, 47);border-radius:15px");//current value*
            ui->label_4->setStyleSheet("background-color: rgb(45, 11, 47);border-radius:15px");// information text
            ui->label_10->setStyleSheet("background-color: rgb(45, 11, 47);border-radius:15px");// status text



            ui->lineEdit_changevalue->setEnabled(false);
            ui->lineEdit_changevalue->setStyleSheet("QLineEdit:disabled { background-color: rgb(42, 42, 42); color: #aaaaaa; }");
            ui->pushButton_2->setEnabled(false);
            ui->pushButton_2->setStyleSheet("QPushButton:disabled { background-color: rgb(42, 42, 42); color: #aaaaaa; }");
            ui->lineEdit->setEnabled(false);
            ui->lineEdit->setStyleSheet("QLineEdit:disabled { background-color: rgb(42, 42, 42); color: #aaaaaa; }");

        }

    }

    QPalette MainWindow::createColorPalette(const QColor& color) {
        QPalette palette;
        palette.setColor(QPalette::WindowText, color);
        return palette;
    }
