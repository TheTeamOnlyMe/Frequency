#ifndef CHECKBOXDELEGATE_H
#define CHECKBOXDELEGATE_H

#include <QStyledItemDelegate>
#include <QEvent>
#include <QMouseEvent>
#include <QCheckBox>
#define CHECK_BOX_COLUMN 0 
class CheckBoxDelegate : public QStyledItemDelegate
{
	Q_OBJECT

public:
	CheckBoxDelegate(QObject *parent);
	~CheckBoxDelegate();
	//用来设置表格样式，绘制复选框-状态、大小、显示区域等。
	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
	//用来设置数据，响应鼠标事件，判断当前选中状态，互相切换。
	bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);
private:
	
};

#endif // CHECKBOXDELEGATE_H
