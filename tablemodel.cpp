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
////��������\��Ҫ���ڸ������ݣ�ˢ�½���
//void TableModel::updataData(const QModelIndex &parent,QList<FrequencyDataRecord> recordList)
//{
//
//}
////����
//int TableModel::rowCount(const QModelIndex &parent) const
//{
//	return 0;
//}
////����
//int TableModel::columnCount(const QModelIndex &parent)const
//{
//	return 0;
//}
////������ʾ���ݣ����ݽ�ɫ����ɫ���ı������뷽ʽ��ѡ��״̬�ȣ��ж���Ҫ��ʾ�����ݡ�
//QVariant  TableModel::data(const QModelIndex &index, int role) const
//{
//	return QVariant();
//}
////�����������ݣ����ݽ�ɫ����ɫ���ı������뷽ʽ��ѡ��״̬�ȣ��ж���Ҫ���õ����ݡ�
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
////������ʾˮƽ/��ֱ��ͷ������
//QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
//{
//	return QVariant();
//}
////�������õ�Ԫ��ı�־�����á���ѡ�С��ɸ�ѡ�ȣ�
//Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
//{
//	if (!index.isValid())
//		return QAbstractItemModel::flags(index);
//
//	Qt::ItemFlags flags = Qt::ItemIsEnabled | Qt::ItemIsSelectable;
//
//	return flags;
//}