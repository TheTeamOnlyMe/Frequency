#include "checkboxdelegate.h"

CheckBoxDelegate::CheckBoxDelegate(QObject *parent)
	: QStyledItemDelegate(parent)
{

}

CheckBoxDelegate::~CheckBoxDelegate()
{

}
void CheckBoxDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	QStyleOptionViewItem viewOption(option);
	initStyleOption(&viewOption, index);
	if (option.state.testFlag(QStyle::State_HasFocus))
		viewOption.state = viewOption.state ^ QStyle::State_HasFocus;

	QStyledItemDelegate::paint(painter, viewOption, index);

	if (index.column() == CHECK_BOX_COLUMN)
	{
		bool data = index.model()->data(index, Qt::UserRole).toBool();

		QStyleOptionButton checkBoxStyle;
		checkBoxStyle.state = data ? QStyle::State_On : QStyle::State_Off;
		checkBoxStyle.state |= QStyle::State_Enabled;
		checkBoxStyle.iconSize = QSize(20, 20);
		checkBoxStyle.rect = option.rect;

		QCheckBox checkBox;
		checkBoxStyle.iconSize = QSize(20, 20);
		checkBoxStyle.rect = option.rect;
		//QApplication::style()->drawPrimitive(QStyle::PE_IndicatorCheckBox, &checkBoxStyle, painter, &checkBox);
	}
}
//用来设置数据，响应鼠标事件，判断当前选中状态，互相切换。
bool CheckBoxDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
	QRect decorationRect = option.rect;

	QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
	if (event->type() == QEvent::MouseButtonPress && decorationRect.contains(mouseEvent->pos()))
	{
		if (index.column() == CHECK_BOX_COLUMN)
		{
			bool data = model->data(index, Qt::UserRole).toBool();
			model->setData(index, !data, Qt::UserRole);
		}
	}

	return QStyledItemDelegate::editorEvent(event, model, option, index);
}