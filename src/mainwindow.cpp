//
// Created by 13223 on 2023/12/5.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "headers/mainwindow.h"
#include "QFileDialog"
#include "QMessageBox"
#include "forms/ui_MainWindow.h"
#include "headers/HaffManTree.h"
#include <fstream>
#include <iostream>
MainWindow::MainWindow(QWidget *parent) : QWidget(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    connect(ui->browse_Button, SIGNAL(clicked()), this, SLOT(ClickButton_browse()));
    connect(ui->compression_Button, SIGNAL(clicked()), this, SLOT(ClickButton_compression()));
    connect(ui->decode_browse_Button, SIGNAL(clicked()), this, SLOT(ClickButton_browse_decode()));
    connect(ui->decompression_Button, SIGNAL(clicked()), this, SLOT(ClickButton_decompression()));
}

void MainWindow::ClickButton_decompression() {
    int leafLen;
    int *w = new int[300]();
    int *re = new int[300]();
    std::fstream fs(this->filePath.toStdString(), std::ios::binary | std::ios::in);

    if (!fs.is_open()) {
        QMessageBox::critical(nullptr, "失败!", "文件打开失败！");
    } else {
        // 读取文件内容

        fs >> leafLen;

        for (int i = 0; i < leafLen; i++) {
            fs >> re[i] >> w[re[i]];
        }
        std::string code;
        fs >> code;
        ui->text_before->setText(QString::fromStdString(code));
        fs.close();
        // 构建哈夫曼树
        HaffManTree tree(w, re, leafLen);
        // 获取哈夫曼编码
        std::string *codeArr = tree.getCodeArr();
        // 解码
        std::string res;
        Node *p = tree.getRoot();
        for (char i: code) {
            if (i == '0') {
                p = p->getL();
            } else {
                p = p->getR();
            }
            if (p->getCode() != -1) {
                res += (char) p->getCode();
                p = tree.getRoot();
            }
        }
        ui->text_after->setText(QString::fromStdString(res));
        std::string fileName = extractFileName(this->filePath.toStdString());
        std::string outPath = "E:/File-Compression-System/decompression/" + fileName;
        std::cout << outPath << std::endl;
        std::fstream out(outPath, std::ios::binary | std::ios::out);
        if (!out.is_open()) {
            QMessageBox::critical(nullptr, "失败!", "文件打开失败！");
        } else {
            // 写入文件内容
            out << res;
            out.close();
            QMessageBox::information(nullptr, "成功!", "文件解压成功！");
        }
    }
}
void MainWindow::ClickButton_browse_decode() {
    this->filePath = QFileDialog::getOpenFileName(this, "选择一个文本本文件", "E:/File-Compression-System", "Text Files (*.txt)");
    ui->decode_file_display->setText(this->filePath);
}


void MainWindow::ClickButton_browse() {
    this->filePath = QFileDialog::getOpenFileName(this, "选择一个文本本文件", "E:/File-Compression-System", "Text Files (*.txt)");
    ui->file_display->setText(this->filePath);
}

void MainWindow::ClickButton_compression() {
    std::fstream fs(this->filePath.toStdString(), std::ios::binary | std::ios::in);
    if (!fs.is_open()) {
        QMessageBox::critical(nullptr, "失败!", "文件打开失败！");
    } else {
        // 统计文件中出现的字符次数 计算出字符的权值
        std::string tmp;
        char tt;
        int *w = new int[300]();
        int *re = new int[300]();
        int leafLen = 0;
        while (fs.get(tt)) {
            tmp += tt;
            unsigned int code = (int) (unsigned char) tt;
            if (!w[code]) re[leafLen++] = int(code);
            w[code]++;
        }//有些字符的ascll码大于128所以要用unsigned来存储
        fs.close();
        QString ttt = QString::fromStdString(tmp);
        ui->text_before->setText(ttt);
        for (int i = 0; i < leafLen; i++) {
            std::cout << re[i] << " " << w[re[i]] << std::endl;
        }
        //        QMessageBox::information(nullptr, "成功!", ttt);
        // 构建哈夫曼树
        HaffManTree tree(w, re, leafLen);
        // 获取哈夫曼编码
        std::string *code = tree.getCodeArr();
        std::string res;
        for (char i: tmp) {
            res += code[(int) (unsigned char) i];
        }
        ui->text_after->setText(QString::fromStdString(res));
        //        QMessageBox::information(nullptr, "成功!", QString::fromStdString(res));
        std::string fileName = extractFileName(this->filePath.toStdString());
        std::string outPath = "E:/File-Compression-System/compression/" + fileName;
        std::cout << outPath << std::endl;
        std::fstream out(outPath, std::ios::binary | std::ios::out);
        if (!out.is_open()) {
            QMessageBox::critical(nullptr, "失败!", "文件打开失败！");
        } else {
            // 写入文件内容
            out << leafLen << ' ';
            for (int i = 0; i < leafLen; i++) {
                out << re[i] << ' ' << w[re[i]] << ' ';
            }
            out << res;
            out.close();
            QMessageBox::information(nullptr, "成功!", "文件压缩成功！");
        }
    }
}

MainWindow::~MainWindow() {
    delete ui;
}

std::string MainWindow::extractFileName(const std::string &filePath) {
    // 查找最后一个斜杠的位置
    size_t lastSlash = filePath.find_last_of("/\\");
    // 截取文件名部分
    std::string fileName = filePath.substr(lastSlash + 1);
    return fileName;
}