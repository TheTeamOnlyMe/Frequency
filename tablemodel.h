//#ifndef TABLEMODEL_H
//#define TABLEMODEL_H
//
//#include <QAbstractTableModel>
//#include "DataBaseTool.h"
//class TableModel : public QAbstractTableModel
//{
//	Q_OBJECT
//
//public:
//	TableModel(QObject *parent);
//	~TableModel();
//	//更新数据\主要用于更新数据，刷新界面
//	void updataData(const QModelIndex &index,QList<FrequencyDataRecord> recordList);
//	//行数
//	int rowCount(const QModelIndex &parent) const;
//	//列数
//	int columnCount(const QModelIndex &parent)const;	
//	//用来显示数据，根据角色（颜色、文本、对齐方式、选中状态等）判断需要显示的内容。
//	QVariant  data(const QModelIndex &index, int role) const;
//	//用来设置数据，根据角色（颜色、文本、对齐方式、选中状态等）判断需要设置的内容。
//	bool setData(const QModelIndex &index,const QVariant &value,int role);
//	//用来显示水平/垂直表头的数据
//	QVariant headerData(int section, Qt::Orientation orientation, int role) const;
//	//用来设置单元格的标志（可用、可选中、可复选等）
//	Qt::ItemFlags flags(const QModelIndex &index) const;
//private:
//	
//};
//
//#endif // TABLEMODEL_H
