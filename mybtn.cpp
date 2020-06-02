#include "mybtn.h"
#include <QPainter>
#include <QtDebug>

myBtn::myBtn(QWidget *parent) : QWidget(parent),btnWidth(100),btnHight(40)
{
    //初始化按钮类里面的 成员变量
    press = false;
    btnStyle = 1;
    mText = "anniy ";
    mTextColor = Qt::black;
    mImageName = "~/Qt/btn_custom/btn2_normal.png";
    resize(btnWidth,btnHight);

}

myBtn::~myBtn()
{

}

   //成员函数部分
   //重绘按钮
   void myBtn::paintEvent(QPaintEvent *event)
   {
    QPainter painter(this);
    //设置抗锯齿
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);
    //关于按键的绘制 增加了两种选择  一种单纯的背景色  另一种 绘制图片
    //需要增加一个类型选择标志  进行选择

    //增加一个枚举类型 进行选择
    if(btnStyle == 1){ //这部分处理的是 按键类型的选择
        drawImage(&painter);//填充图片
    }else{
        qDebug() << "color";
        drawBackColor(&painter);//填充背景图
    }
      drawText(&painter);
   }

   //修改控件尺寸的大小 借鉴阿拉丁的处理

    //鼠标的按下 和松开的事件进行重写
   void myBtn::mousePressEvent(QMouseEvent *event)
   {
       press = true;//这个变量 在 我们这里存在的意义是什么呢
       emit pressed();
       repaint();

   }

   void myBtn::mouseReleaseEvent(QMouseEvent *event)
   {
       press = false;
       emit released();
       repaint();
   }

   //参数指针 改称引用会不会好一点

   void myBtn::drawBackColor(QPainter* painter)
   {
        QPen pen;
        pen.setWidth(2);
        pen.setColor(Qt::black);
        pen.setStyle(Qt::SolidLine);
        pen.setCapStyle(Qt::FlatCap);
        pen.setJoinStyle(Qt::BevelJoin);
        painter->setPen(pen);

       QBrush brush;
       //问题是 按键按下之后 没有进行切换
        brush.setStyle(Qt::SolidPattern);//刷子渲染的模式要进行设置
       if(press){
           brush.setColor(mPressedColor);
       }else{
           brush.setColor(mNormalColor);
           qDebug() << "normal";
       }
       painter->setBrush(brush);
       qDebug() << "w" << width() << "h" << height();
       QRect rect(0,0,width(),height());
       painter->drawRect(rect);
   }

   //简单的绘图  更改为 九宫格 绘图
   //将背景色 设置成白色
   void myBtn::drawImage(QPainter*painter)
   {

       QString fileName;

       QPixmap pixmap;
       if(press){
            fileName = "/home/rabbitchenc/Qt/btn_custom/btn2_normal.png";
       }else{
            fileName = "/home/rabbitchenc/Qt/btn_custom/btn2_pressed.png";
       }

       pixmap = QPixmap(fileName);

       int pixWidth = pixmap.width();
       int pixHeight = pixmap.height();
       pixmap = *ninePatch(fileName,pixWidth/3,pixHeight/3, width(),height());
       pixmap = generatePixmap(pixmap,width(),height());
       painter->drawPixmap(0,0,width(),height(),pixmap);

   }


   /*
   **  功能             : 九宫格图处理
   **  picName          : 图片名字
   **  iHorzSplit       : 四个角上格子的宽度
   **  iVertSplit       : 四个角上格子的高度
   **  DstWidth         : 整个图片缩放的宽度
   **  DstWidth         : 整个图片缩放的高度
   **  返回值           : 处理完成的图片
   */


    QPixmap* myBtn::ninePatch(QString picName,int iHorzSplit,int iVertSplit, int DstWidth, int DstHeight)
    {
        QPixmap * pix = new QPixmap(picName);
        int pixWidth = pix->width();
        int pixHeight = pix->height();

        //将原图分割成九部分
        QPixmap pix_1 = pix->copy(0,0,iHorzSplit,iVertSplit);
        QPixmap pix_2 = pix->copy(iHorzSplit, 0, pixWidth-iHorzSplit*2, iVertSplit);
        QPixmap pix_3 = pix->copy(pixWidth-iHorzSplit, 0, iHorzSplit, iVertSplit);

        QPixmap pix_4 = pix->copy(0, iVertSplit, iHorzSplit, pixHeight-iVertSplit*2);
        QPixmap pix_5 = pix->copy(iHorzSplit, iVertSplit, pixWidth-iHorzSplit*2, pixHeight-iVertSplit*2);
        QPixmap pix_6 = pix->copy(pixWidth-iHorzSplit, iVertSplit, iHorzSplit, pixHeight-iVertSplit*2);

        QPixmap pix_7 = pix->copy(0, pixHeight-iVertSplit, iHorzSplit, iVertSplit);
        QPixmap pix_8 = pix->copy(iHorzSplit, pixHeight-iVertSplit, pixWidth-iHorzSplit*2, pixWidth - iHorzSplit*2);
        QPixmap pix_9 = pix->copy(pixWidth-iHorzSplit, pixHeight-iVertSplit, iHorzSplit, iVertSplit);

        //2 4 5 6 8 图 进行缩放
        pix_2 = pix_2.scaled(DstWidth-iHorzSplit*2,iVertSplit, Qt::IgnoreAspectRatio);//保持高度拉宽
        pix_4 = pix_4.scaled(iHorzSplit, DstHeight-iVertSplit*2, Qt::IgnoreAspectRatio);//保持宽度拉高
        pix_5 = pix_5.scaled(DstWidth-iHorzSplit*2,DstHeight-iVertSplit*2, Qt::IgnoreAspectRatio);//宽高都缩放
        pix_6 = pix_6.scaled(iHorzSplit, DstHeight-iVertSplit*2, Qt::IgnoreAspectRatio);//保持宽度拉高
        pix_8 = pix_8.scaled(DstWidth-iHorzSplit*2, iVertSplit);//保持高度拉宽


        QPixmap* resultImag = new QPixmap(DstWidth,DstHeight);
        QPainter*respainter = new QPainter(resultImag);
        if(!resultImag->isNull()){
            respainter->drawPixmap(0,0,pix_1);
            respainter->drawPixmap(iHorzSplit,0,pix_2);
            respainter->drawPixmap(DstWidth-iHorzSplit,0,pix_3);
            respainter->drawPixmap(0, iVertSplit, pix_4);
            respainter->drawPixmap(iHorzSplit, iVertSplit, pix_5);
            respainter->drawPixmap(DstWidth-iHorzSplit, iVertSplit, pix_6);

            respainter->drawPixmap(0, DstHeight-iVertSplit, pix_7);
            respainter->drawPixmap(iHorzSplit, DstHeight-iVertSplit, pix_8);
            respainter->drawPixmap(DstWidth-iHorzSplit, DstHeight-iVertSplit, pix_9);
            respainter->end();
        }
        return  resultImag;
    }



    //增加一个对 图片 圆角处理的函数  不知道 是否有用
    /**
       * 圆角图片
       * src 原图片
       * radius 图片半径
       */

    QPixmap myBtn::generatePixmap(const QPixmap &src, const int w,const int h) {

           // 无效图片不处理
           if (src.isNull()) {
               return src;
           }

           // 压缩图片
           QPixmap pixmap = QPixmap(src);

           QPixmap dest(w, h);
           dest.fill(Qt::transparent);
           QPainter painter(&dest);
           // 抗锯齿 + 平滑边缘处理
           painter.setRenderHints(QPainter::Antialiasing, true);
           painter.setRenderHints(QPainter::SmoothPixmapTransform, true);
           // 裁剪为圆角
           QPainterPath path;
           path.addRect(0, 0, w, h);
           painter.setClipPath(path);
           painter.drawPixmap(0, 0, w, h, pixmap);

           return dest;
       }

    //在按钮上添加文本
    void myBtn::drawText(QPainter *painter)
    {

            painter->setPen(mTextColor);
            painter->drawText(QPoint(width()/2,0),"hello");

    }

   void myBtn::setTextColor(QColor textColor)
   {
        mTextColor = textColor;
        update();
   }
   void myBtn::setText(QString textStr)
   {
        mText = textStr;
        update();
   }
   void myBtn::setImage(QString imageStr)
   {
       mImageName = imageStr;
       update();
   }








