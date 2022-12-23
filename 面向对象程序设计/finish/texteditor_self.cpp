#include "texteditor_self.h"
#include "ui_texteditor_self.h"
#include <QMessageBox>
#include <QPushButton>
#include <QFileDialog>
#include <QTextStream>
#include <QColorDialog>
#include <QFontDialog>
#include <cstring>
#include <QTimer>
#include <QShortcut>
#include<QWidget>
#include<QMenuBar>
#include<QAction>
#include<QToolBar>
#include<QList>
#include<QDebug>
#include<QKeySequence>

#include <QTextBlock>
#include <QTextDocument>
#include <QTextFragment>
#include <QFile>
#include <QFileInfo>
#include <QDataStream>
#include <QIODevice>
#include <QDesktopServices>
#include <QFileDialog>
#include <QTextEdit>
#include <QTimer>
#include <QShortcut>
#include <QStringList>
#include <QLineEdit>
#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QPalette>
#include <QClipboard>
#include <QCloseEvent>

Texteditor_self::Texteditor_self(QWidget *parent):QMainWindow(parent),ui(new Ui::Texteditor_self)
{
    pin = 0; //初始化锁
    ui->setupUi(this);
    Test = tr("新建");
    newFile = true;
    // 初始化窗口标题为文件名
    setWindowTitle(Test + tr(" - TextEditor_self"));
    UI_init();
    connect(ui->textEdit, SIGNAL(textChanged()), this, SLOT(on_textEdit_textChanged()));//textchange的信号到压入tempstack的槽
    createActions();
    createToolBars();
}

void Texteditor_self::UI_init(){
    QMenuBar *mBar = menuBar();
    QMenu *pFile = mBar->addMenu("File");
    pFile->addAction("New",this,SLOT(newWindow()),tr("ctrl+n"));
    pFile->addAction("Open",this,SLOT(LoadFile()),tr("ctrl+o"));
    pFile->addAction("Save",this,SLOT(SaveFile()),tr("ctrl+s"));
    pFile->addAction("Save as",this,SLOT(SaveasFile()),tr("ctrl+shift+s"));

    QMenu *eFile = mBar->addMenu("Edit");
    eFile->addAction("Undo",this,SLOT(Undo()),tr("ctrl+u"));
    eFile->addAction("Redo",this,SLOT(Redo()),tr("ctrl+r"));
    eFile->addAction("Search/Repalce",this,SLOT(searchText()),tr("ctrl+f"));
    eFile->addAction("Delete",this,SLOT(on_action_triggered()),tr("Del"));
    eFile->addAction("Cut",this,SLOT(on_actionCut_triggered()),tr("ctrl+x"));
    eFile->addAction("Copy",this,SLOT(on_fu()),tr("ctrl+c"));
    eFile->addAction("Paste",this,SLOT(on_tie()),tr("ctrl+v"));
    eFile->addAction("Insert",this,SLOT(on_actionInsert_triggered()),tr("ctrl+i"));

    QMenu *fFile = mBar->addMenu("Format");
    fFile->addAction("Left",this,SLOT(TextLeft()));
    fFile->addAction("Right",this,SLOT(TextRight()));
    fFile->addAction("Center",this,SLOT(TextCenter()));
    fFile->addAction("Justify",this,SLOT(TextJustify()));
    fFile->addAction("Font",this,SLOT(TextFont()));
    fFile->addAction("Color",this,SLOT(TextColor()));


    m_contextMenu = new QMenu;
    m_contextMenu->addAction("Undo",this,SLOT(Undo()));
    m_contextMenu->addAction("Redo",this,SLOT(Redo()));
    m_contextMenu->addAction("Delete",this,SLOT(on_actionDel_triggered()));
    m_contextMenu->addAction("Cut",this,SLOT(on_actionCut_triggered()));
    m_contextMenu->addAction("Copy",this,SLOT(on_fu()));
    m_contextMenu->addAction("Paste",this,SLOT(on_tie()));
    m_contextMenu->addAction("Insert",this,SLOT(on_actionInsert_triggered()));

    setCentralWidget(ui->textEdit);
}


void Texteditor_self::mousePressEvent(QMouseEvent *event)
{
    //确保右键点击，然后跳出菜单.
    if (event->button() == Qt::RightButton)
    {
        //在鼠标右击的地方弹出菜单
        m_contextMenu->exec(event->globalPos());
    }

    event->accept();
}

void Texteditor_self::createActions() {
    newAct = new QAction ( QIcon ( ":/images/rsc/new.png" ), tr ( "&New" ), this );
    newAct->setShortcuts ( QKeySequence::New );
    newAct->setStatusTip ( tr ( "Create a new file" ) );
    connect ( newAct, SIGNAL ( triggered() ), this, SLOT ( newWindow() ) );
    open = new QAction ( QIcon ( ":/images/rsc/open.png" ), tr ( "&Open" ), this );
    open->setStatusTip ( tr ( "Open a new file" ) );
    connect ( open, SIGNAL ( triggered() ), this, SLOT ( LoadFile() ) );
    Save = new QAction ( QIcon ( ":/images/rsc/save.png" ), tr ( "&Save" ), this );
    Save->setStatusTip ( tr ( "Save a new file" ) );
    connect ( Save, SIGNAL ( triggered() ), this, SLOT ( SaveFile() ) );
    saveAs = new QAction ( QIcon ( ":/images/rsc/saveas.png" ),tr ( "&SaveAs" ), this );
    saveAs->setShortcuts ( QKeySequence::SaveAs );
    saveAs->setStatusTip ( tr ( "Save as a new file" ) );
    connect ( saveAs, SIGNAL ( triggered() ), this, SLOT ( test() ) );
    cut = new QAction ( QIcon ( ":/images/rsc/cut.png" ), tr ( "&Cut" ), this );
    cut->setShortcuts ( QKeySequence::Cut );
    cut->setStatusTip ( tr ( "Cut" ) );
    connect( cut, SIGNAL ( triggered() ), this, SLOT ( on_actionCut_triggered() ) );
    copy = new QAction ( QIcon ( ":/images/rsc/copy.png" ), tr ( "&Copy" ), this );
    copy->setShortcuts ( QKeySequence::Copy );
    copy->setStatusTip ( tr ( "Copy" ) );
    connect( copy, SIGNAL ( triggered() ), this, SLOT ( on_fu() ) );
    paste = new QAction ( QIcon ( ":/images/rsc/paste.png" ), tr ( "&Paste" ), this );
    paste->setShortcuts ( QKeySequence::Paste );
    paste->setStatusTip ( tr ( "Paste" ) );
    connect( paste, SIGNAL ( triggered() ), this, SLOT ( on_tie() ) );
    find = new QAction ( QIcon ( ":/images/rsc/find.png" ), tr ( "&Search/Replace" ), this );
    find->setStatusTip ( tr ( "Search/Replace" ) );
    connect( find, SIGNAL ( triggered() ), this, SLOT ( searchText() ) );
    undo = new QAction ( QIcon ( ":/images/rsc/undo.png" ), tr ( "&Undo" ), this );
    undo->setShortcuts ( QKeySequence::Undo );
    undo->setStatusTip ( tr ( "Undo" ) );
    connect( undo, SIGNAL ( triggered() ), this, SLOT ( Undo() ) );
    redo = new QAction ( QIcon ( ":/images/rsc/redo.png" ), tr ( "&Redo" ), this );
    redo->setShortcuts ( QKeySequence::Redo );
    redo->setStatusTip ( tr ( "Redo" ) );
    connect( redo, SIGNAL ( triggered() ), this, SLOT ( Redo() ) );
    left = new QAction ( QIcon ( ":/images/rsc/left.png" ), tr ( "&Left" ), this );
    left->setStatusTip ( tr ( "Left" ) );
    connect( redo, SIGNAL ( triggered() ), this, SLOT ( TextLeft() ) );
    right = new QAction ( QIcon ( ":/images/rsc/right.png" ), tr ( "&Left" ), this );
    right->setStatusTip ( tr ( "Left" ) );
    connect( right, SIGNAL ( triggered() ), this, SLOT ( TextRight() ) );
    middle = new QAction ( QIcon ( ":/images/rsc/middle.png" ), tr ( "&Center" ), this );
    middle->setStatusTip ( tr ( "Center" ) );
    connect( middle, SIGNAL ( triggered() ), this, SLOT ( TextCenter() ) );
    just = new QAction ( QIcon ( ":/images/rsc/just.png" ), tr ( "&Just" ), this );
    just->setStatusTip ( tr ( "Center" ) );
    connect( just, SIGNAL ( triggered() ), this, SLOT ( TextJustify() ) );
    font = new QAction ( QIcon ( ":/images/rsc/font.png" ), tr ( "&Font" ), this );
    font->setStatusTip ( tr ( "Font" ) );
    connect( font, SIGNAL ( triggered() ), this, SLOT ( TextFont() ) );
    color = new QAction ( QIcon ( ":/images/rsc/color.png" ), tr ( "&Color" ), this );
    color->setStatusTip ( tr ( "Color" ) );
    connect( color, SIGNAL ( triggered() ), this, SLOT ( TextColor() ) );
    insert = new QAction ( QIcon ( ":/images/rsc/insert.png" ), tr ( "&Insert" ), this );
    insert->setStatusTip ( tr ( "Insert" ) );
    connect( insert, SIGNAL ( triggered() ), this, SLOT ( on_actionInsert_triggered() ) );
}

void Texteditor_self::createToolBars()
{
    ui->mainToolBar->addAction ( open );
    ui->mainToolBar->addAction ( newAct );
    ui->mainToolBar->addAction ( Save );
    ui->mainToolBar->addAction ( saveAs );
    editToolBar = addToolBar ( tr ( "Edit" ) );
    editToolBar->addAction ( cut );
    editToolBar->addAction ( copy );
    editToolBar->addAction ( paste );
    editToolBar->addAction ( insert );
    editToolBar->addAction ( find );
    editToolBar->addAction ( undo );
    editToolBar->addAction ( redo );
    fmtToolBar = addToolBar ( tr ( "Format" ) );
    fmtToolBar->addAction( left );
    fmtToolBar->addAction( right );
    fmtToolBar->addAction( middle );
    fmtToolBar->addAction( just );
    fmtToolBar->addAction( font );
    fmtToolBar->addAction( color );
}

Texteditor_self::~Texteditor_self()
{
    delete ui;
}

void Texteditor_self::SaveFile(){
    if ( newFile==true ){ // 新文件需要给一个路径和名字
        save();
    }
    else{// 老文件直接保存就行
        save(Test);
    }
}

void Texteditor_self::SaveasFile(){
    save();
}

void Texteditor_self::TextRight(){//右对齐
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextBlockFormat textBlockFormat = cursor.blockFormat();
    textBlockFormat.setAlignment(Qt::AlignRight);
    cursor.mergeBlockFormat(textBlockFormat);
    ui->textEdit->setTextCursor(cursor);
}
void Texteditor_self::TextLeft(){//左对齐
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextBlockFormat textBlockFormat = cursor.blockFormat();
    textBlockFormat.setAlignment(Qt::AlignLeft);
    cursor.mergeBlockFormat(textBlockFormat);
    ui->textEdit->setTextCursor(cursor);
}
void Texteditor_self::TextCenter(){//居中对齐
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextBlockFormat textBlockFormat = cursor.blockFormat();
    textBlockFormat.setAlignment(Qt::AlignCenter);
    cursor.mergeBlockFormat(textBlockFormat);
    ui->textEdit->setTextCursor(cursor);
}

void Texteditor_self::TextJustify(){//两端对齐
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextBlockFormat textBlockFormat = cursor.blockFormat();
    textBlockFormat.setAlignment(Qt::AlignJustify);
    cursor.mergeBlockFormat(textBlockFormat);
    ui->textEdit->setTextCursor(cursor);
}

void Texteditor_self::newWindow(){
    if ( ui->textEdit->document()->isModified() ){
        // 自定义一个警告对话框
        QMessageBox box;
        box.setWindowTitle(tr("警告"));
        box.setIcon(QMessageBox::Warning);
        box.setText(tr(" 尚未保存，是否保存？"));
        QPushButton *yesBtn = box.addButton(tr("是(&Y)"),QMessageBox::YesRole);

        QPushButton *noBtn = box.addButton(tr("否(&N)"), QMessageBox::NoRole);
        QPushButton *cancelBtn = box.addButton(tr("取消"),QMessageBox::RejectRole);
        box.exec();

        if (box.clickedButton() == yesBtn)
            save();
        else if (box.clickedButton() == cancelBtn){
            //
        }
        else if (box.clickedButton() == noBtn){
            pin = 0; //初始化锁
            Test = tr("新建");
            newFile = true;
            // 初始化窗口标题为文件名
            setWindowTitle(Test + tr(" - TextEditor_self"));
            ui->textEdit->clear();
        }
    }
}

void Texteditor_self::save(){
    // 获取文本信息
    QString file_name;
    file_name = QFileDialog::getSaveFileName(this,tr("Save files"),"./",tr("Binary files(*.bin)"));
    QString strHtml = ui->textEdit->document()->toHtml();
    QFile file(file_name);
    if ( file.open(QFile::WriteOnly) ){
        QDataStream out(&file);
        out<<strHtml;
        file.close();

        Test = file_name;
        QStringList tmp = Test.split(QRegExp("/"));
        int i=tmp.count();
        QString str = tmp[i-1];
        setWindowTitle(str + tr(" - TextEditor_self"));
        newFile = false;
    }
    else{
        QMessageBox msgBox;
        msgBox.setText("fail to save file!");
        msgBox.exec();
    }
}

void Texteditor_self::save(QString file_name)
{
    QString strHtml = ui->textEdit->document()->toHtml();
    QFile file(file_name);
    if ( file.open(QFile::WriteOnly) ){
        QDataStream out(&file);
        out<<strHtml;
        file.close();

        Test = file_name;
        QStringList tmp = Test.split(QRegExp("/"));
        int i=tmp.count();
        QString str = tmp[i-1];
        setWindowTitle(str + tr(" - TextEditor_self"));
        newFile = false;
    }
    else{
        QMessageBox msgBox;
        msgBox.setText("fail to save file!");
        msgBox.exec();
    }
}

void Texteditor_self::LoadFile(){
    // ui->textEdit->append("Hello World!");
    initstack();//打开时初始化undostack

    QString file_name;
    file_name = QFileDialog::getOpenFileName(this,"open file","./","Binary files(*.bin)");
    QFile file(file_name);

    if (file.open(QIODevice::ReadOnly)){
        QDataStream in(&file);

        QString strHtml;
        in>>strHtml;
        file.close();
        ui->textEdit->clear();
        ui->textEdit->setText(strHtml);

        Test = file_name;
        QStringList tmp = Test.split(QRegExp("/"));
        int i=tmp.count();
        QString str = tmp[i-1];
        setWindowTitle(str + tr(" - TextEditor_self"));
        newFile = false;
        temp.push(strHtml);
    }else{
        QMessageBox msgBox;
        msgBox.setText("fail to load file!");
        msgBox.exec();
    }
}

void Texteditor_self::closeEvent(QCloseEvent *event)
{
    if ( ui->textEdit->document()->isModified() ){
        // 自定义一个警告对话框
        QMessageBox box;
        box.setWindowTitle(tr("警告"));
        box.setIcon(QMessageBox::Warning);
        box.setText(tr(" 尚未保存，是否保存？"));
        QPushButton *yesBtn = box.addButton(tr("是(&Y)"),QMessageBox::YesRole);

        QPushButton *exit = box.addButton(tr("否(&N)"), QMessageBox::NoRole);
        QPushButton *cancelBut = box.addButton(tr("取消"),QMessageBox::RejectRole);
        box.exec();

        if (box.clickedButton() == yesBtn){
            save();
            event->accept();
            return ;
        }
        else if (box.clickedButton() == cancelBut){
            event->ignore();
            return ;
        }
        else if (box.clickedButton() == exit){
            event->accept();
        }
    }
    // event->ignore();
}

void Texteditor_self::Undo(){
    if (!temp.isEmpty()){//新增限制条件
    pin++; //加锁
    store.push(temp.pop());
    store.push(temp.pop());//当前栈加入store中以供redo调用
    ui->textEdit->setText(temp.top());//显示上一个内容
    //store.push(ui->textEdit->toPlainText());//上一个内容压入store
    ui->textEdit->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
    pin--; //解锁
    }
}

void Texteditor_self::Redo(){
    if (!store.isEmpty()){//新增限制条件
    pin++;
    temp.push(store.pop());
    temp.push(store.pop());
    ui->textEdit->setText(temp.top());
    //temp.push(ui->textEdit->toPlainText());
    ui->textEdit->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
    pin--;
    }
}


void Texteditor_self::on_textEdit_textChanged(){//每次文本更改时更新堆栈
    if (pin==0){
        //temp.push(ui->textEdit->toPlainText());
        QString strHtml = ui->textEdit->document()->toHtml();
        temp.push(strHtml);
    }
    //if (temp.size()>3){
    //    QVBoxLayout *layout =new QVBoxLayout();
            //ui->scrollArea->setLayout(layout);
            //ui->scrollArea->setWidgetResizable(true);
    //        QTextEdit *edit1 = new QTextEdit("hello world");
    //        edit1->setSizePolicy(QSizePolicy::QSizePolicy::Preferred,QSizePolicy::Preferred);
            //layout->addWidget(edit1);
    //}
}


void Texteditor_self::initstack() //栈初始化
{
    temp.clear();
    store.clear();
}

void Texteditor_self::searchText(){
    findDlg = new QDialog(this);
    findDlg->setWindowTitle("Search And Replace");
    findLineEdit = new QLineEdit(findDlg);
    replaceLineEdit = new QLineEdit(findDlg);

    QPushButton *btn = new QPushButton(tr("Next"), findDlg);
    QPushButton *btn1 = new QPushButton(tr("Replace This"), findDlg);
    QPushButton *btn2 = new QPushButton(tr("Replace All"), findDlg);
    QVBoxLayout *layout = new QVBoxLayout(findDlg);

    layout->addWidget(findLineEdit);
    layout->addWidget(replaceLineEdit);
    layout->addWidget(btn);
    layout->addWidget(btn1);
    layout->addWidget(btn2);
    connect(btn, &QPushButton::clicked, this, &Texteditor_self::showFindText);
    connect(btn1,&QPushButton::clicked, this, &Texteditor_self::replaceThisText);
    connect(btn2,&QPushButton::clicked, this, &Texteditor_self::replaceAllText);
    SearchTextNum=0;
    findDlg->show();
}

void Texteditor_self::showFindText(){
    static QString pre;
    QString searchContent = findLineEdit->text();
    if (searchContent!=pre){
        SearchTextNum=0;qDebug()<<"Clear num already.";
    }
    pre = searchContent;
    QString content = ui->textEdit->toPlainText();
    static int precount;
    int count = content.count(searchContent);
    if (precount!=count){
        SearchTextNum=0;qDebug()<<"Clear num in count part.";
    }
    qDebug()<<"Count is "<<count;
    precount=count;
    if (!ui->textEdit->find(searchContent, QTextDocument::FindCaseSensitively))
    {
        ui->textEdit->moveCursor(QTextCursor::Start);
    }
    else{
        QPalette palette = ui->textEdit->palette();
        palette.setColor(QPalette::Highlight,palette.color(QPalette::Active,QPalette::Highlight));
        ui->textEdit->setPalette(palette);
        SearchTextNum = (++SearchTextNum)%(1+count);
        if (SearchTextNum==0)
            SearchTextNum++;
        qDebug()<<"num is "<<SearchTextNum;
    }
}

void Texteditor_self::replaceThisText(){

    QString searchContent = findLineEdit->text();
    // QString content = ui->textEdit->toPlainText();
    QString content = ui->textEdit->document()->toHtml();
    QString replaceContent = replaceLineEdit->text();

    int tmp=0;
    for (int i=0;i<=SearchTextNum-1;i++){
        tmp = content.indexOf(searchContent, searchContent.length()+tmp);
        qDebug()<<"Current tmp is:"<<tmp;
    }

    int bpos=tmp;
    if (bpos!=-1){
        QString conString=content.left(bpos);
        conString.append(replaceContent);
        conString.append(content.right(content.length()-bpos-searchContent.length()));

        ui->textEdit->clear();
        ui->textEdit->setText(conString);
    }
    ui->textEdit->moveCursor(QTextCursor::Start);
}

void Texteditor_self::replaceAllText(){

    QString searchContent = findLineEdit->text();
    QString content = ui->textEdit->document()->toHtml();
    QString replaceContent = replaceLineEdit->text();

    content.replace(searchContent, replaceContent);
    ui->textEdit->clear();
    ui->textEdit->setText(content);
}

//delete cursor
void Texteditor_self::on_actionDel_triggered()
{
    QTextCursor cursor=ui->textEdit->textCursor();//得到当前text的光标
       if(cursor.hasSelection())//如果有选中，则取消，以免受受影响
           cursor.clearSelection();
       cursor.deletePreviousChar();//删除前一个字符
       ui->textEdit->setTextCursor(cursor);//让光标移到删除后的位置
}

//insert
void Texteditor_self::on_actionInsert_triggered(){
    QString file_name;
    file_name = QFileDialog::getOpenFileName(this,"open file","./","Binary files(*.bin)");
    QFile file(file_name);

    if (file.open(QIODevice::ReadOnly)){
        QDataStream in(&file);

        QString strHtml;
        in>>strHtml;
        file.close();

        QTextCursor cursor=ui->textEdit->textCursor();//得到当前text的光标
        int index =  cursor.position();

        qDebug() << index;
        QString content = ui->textEdit->document()->toHtml();
        qDebug() << content<<endl;

        QString tmp;
        QString plaintxt = ui->textEdit->document()->toPlainText();
        QString prechar = plaintxt.left(index);
        prechar = prechar.right(1);
        qDebug()<<prechar;

        int totalnum = plaintxt.count(prechar);
        int precharnum = plaintxt.left(index).count(prechar);
        qDebug()<<totalnum<<"|"<<precharnum<<endl;

        int insertindex;
        for (int i=0;i<=precharnum-1;i++){
            insertindex  = content.indexOf(prechar, prechar.length()+insertindex);
        }

        while ( QString::compare(content.left(insertindex).right(3),"/p>")!=0 ){
            insertindex++;
        }
        qDebug()<<"Current insertindex is:"<<insertindex;

        tmp = content.left(insertindex);
        int start = strHtml.indexOf("<p");
        int end = strHtml.lastIndexOf("/p>");

        strHtml = strHtml.mid(start,end);
        strHtml = strHtml.left(strHtml.length()-14);
        // strHtml = strHtml.left(start);

        qDebug()<<"start is"<<start<<"| end is"<<end<<endl;
        qDebug() << strHtml<<endl;

        tmp.append(strHtml);
        tmp.append(content.right(content.length()-insertindex));
        ui->textEdit->clear();
        ui->textEdit->setText(tmp);

        // cursor.insertText(strHtml);
        // conString.append(content.right(content.length()-bpos-searchContent.length()));
        //cursor.setText(strHtml);
        //ui->textEdit->clear();
        //ui->textEdit->setText(strHtml);

        //        Test = file_name;
//        QStringList tmp = Test.split(QRegExp("/"));
//        int i=tmp.count();
//        QString str = tmp[i-1];
//        setWindowTitle(str + tr(" - TextEditor_self"));
//        newFile = false;

        temp.push(strHtml);
    }else{
        QMessageBox msgBox;
        msgBox.setText("fail to insert!");
        msgBox.exec();
    }

}

void Texteditor_self::on_actionCut_triggered(){
   ui->textEdit->cut();

}

//del select all
void Texteditor_self::on_action_triggered()
{
    QTextCursor cursor=ui->textEdit->textCursor();//得到当前text的光标
    if(cursor.hasSelection()){
          cursor.deleteChar();
    }else{
        QTextCursor cursor=ui->textEdit->textCursor();//得到当前text的光标
              if(cursor.hasSelection())//如果有选中，则取消，以免受受影响
                  cursor.clearSelection();
              cursor.deletePreviousChar();//删除前一个字符
              ui->textEdit->setTextCursor(cursor);//让
    }
}

void Texteditor_self::on_fu()
{
 ui->textEdit->copy();

}

void Texteditor_self::on_tie()
{
     ui->textEdit->paste();
}


void Texteditor_self:: ChangeFormat(const QTextCharFormat &mod)//让改变格式的操作作用于被选取的区域，如果当前没有被选取的区域则使操作作用于光标所在处的字符
{
    QTextCursor cursor =ui->textEdit->textCursor();
    if ( !cursor.hasSelection() )//判断是否有被选取区域，如果有返回true，否则返回false
           cursor.select( QTextCursor::WordUnderCursor ); //无被选取区域时，相当于选择光标目前所在处字符（WordUnderCursor）

    cursor.mergeCharFormat( mod );
    ui->textEdit->mergeCurrentCharFormat( mod );
}


void Texteditor_self::TextColor()
{
    QColor color = QColorDialog::getColor(Qt::black, this);//调用颜色操作框
    if ( color.isValid() )
    {
         QTextCharFormat mod;
         mod.setForeground( color );
         ChangeFormat( mod );
    }
}

void Texteditor_self::TextFont()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok);//调用字体操作框
    if(ok){
        QTextCharFormat mod;
        mod.setFont( font );
        ChangeFormat( mod );
    }
}
