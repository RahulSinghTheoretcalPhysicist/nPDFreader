#pragma once

#include <QWidget>
#include <QString>

class DocumentCanvas final : public QWidget
{
    Q_OBJECT

public:
    explicit DocumentCanvas(QWidget *parent = nullptr);

    void setOpenedFile(const QString &filePath);
    void clearDocument();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QString m_filePath;
};
