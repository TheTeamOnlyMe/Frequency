//#include "tablemodel.h"
//
//TableModel::TableModel(QObject *parent)
//	: QAbstractTableModel(parent)
//{
//
//}
//
//TableModel::~TableModel()
//{
//
//}
////更新数据\主要用于更新数据，刷新界面
//void TableModel::updataData(const QModelIndex &parent,QList<FrequencyDataRecord> recordList)
//{
//
//}
////行数
//int TableModel::rowCount(const QModelIndex &parent) const
//{
//	return 0;
//}
////列数
//int TableModel::columnCount(const QModelIndex &parent)const
//{
//	return 0;
//}
////用来显示数据，根据角色（颜色、文本、对齐方式、选中状态等）判断需要显示的内容。
//QVariant  TableModel::data(const QModelIndex &index, int role) const
//{
//	return QVariant();
//}
////用来设置数据，根据角色（颜色、文本、对齐方式、选中状态等）判断需要设置的内容。
//bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
//{
//	if (!index.isValid())
//		return false;
//
//	int nColumn = index.column();
//	/*FrequencyDataRecord record = m_recordList.at(index.row());
//	switch (role)
//	{
//	case Qt::DisplayRole:
//	{
//		if (nColumn == File_PATH_COLUMN)
//		{
//			record.strFilePath = value.toString();
//
//			m_recordList.replace(index.row(), record);
//			emit dataChanged(index, index);
//			return true;
//		}
//	}
//	case Qt::CheckStateRole:
//	case Qt::UserRole:
//	{
//		if (nColumn == CHECK_BOX_COLUMN)
//		{
//			record.bChecked = value.toBool();
//
//			m_recordList.replace(index.row(), record);
//			emit dataChanged(index, index);
//			return true;
//		}
//	}
//	default:
//		return false;
//	}*/
//	return false;
//}
////用来显示水平/垂直表头的数据
//QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
//{
//	return QVariant();
//}
////用来设置单元格的标志（可用、可选中、可复选等）
//Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
//{
//	if (!index.isValid())
//		return QAbstractItemModel::flags(index);
//
//	Qt::ItemFlags flags = Qt::ItemIsEnabled | Qt::ItemIsSelectable;
//
//	return flags;
//}