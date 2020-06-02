#ifndef MYBTN_H
#define MYBTN_H

#include <QWidget>
#include <QColor>

class myBtn : public QWidget
{
    Q_OBJECT
public:
    explicit myBtn(QWidget *parent = nullptr);
    ~myBtn();
signals:

    void pressed();
    void released();

public slots:

    void setTextColor(QColor textColor);
    void setText(QString textStr);
    void setImage(QString imageStr);



protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void drawBackColor(QPainter* painter);
    void drawText(QPainter *painter);
    void drawImage(QPainter*painter);
    QPixmap* ninePatch(QString picName,int iHorzSplit,int iVertSplit, int DstWidth, int DstHeight);
    QPixmap generatePixmap(const QPixmap &src, const int w,const int h);

private:
    bool press;

    //按键颜色  文本颜色 （这里将他设置成 默认的颜色值）
    QColor mPressedColor = Qt::yellow;
    QColor mNormalColor = Qt::green;
    QColor mTextColor = Qt::black;

    //文本内容  添加图片的名字
    QString mText;
    QString mImageName;



    int btnWidth;
    int btnHight;
    int btnStyle;



signals:

};

#endif // MYBTN_H
