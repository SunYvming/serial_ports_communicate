#include "mycombobox.h"
#include <QComboBox>

MyComboBox::MyComboBox(QWidget *parent):QComboBox(parent)
{

}

void MyComboBox::mousePressEvent(QMouseEvent *event)
{
  if(event->button() == Qt::LeftButton)
  {
      emit clicked();
  }
  QComboBox::mousePressEvent(event);
}
