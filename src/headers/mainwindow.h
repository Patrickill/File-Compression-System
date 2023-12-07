//
// Created by 13223 on 2023/12/5.
//

#ifndef FILE_COMPRESSION_SYSTEM_MAINWINDOW_H
#define FILE_COMPRESSION_SYSTEM_MAINWINDOW_H

#include "Node.h"
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QWidget {
    Q_OBJECT

public:
    std::string extractFileName(const std::string &filePath);
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
public slots:
    void ClickButton_browse();
    void ClickButton_compression();
    void ClickButton_decompression();
    void ClickButton_browse_decode();

private:
    Ui::MainWindow *ui;
    QString filePath;
    Node *root;
};


#endif//FILE_COMPRESSION_SYSTEM_MAINWINDOW_H
