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
	//�������ñ����ʽ�����Ƹ�ѡ��-״̬����С����ʾ����ȡ�
	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
	//�����������ݣ���Ӧ����¼����жϵ�ǰѡ��״̬�������л���
	bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);
private:
	
};

#endif // CHECKBOXDELEGATE_H
