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
//	//��������\��Ҫ���ڸ������ݣ�ˢ�½���
//	void updataData(const QModelIndex &index,QList<FrequencyDataRecord> recordList);
//	//����
//	int rowCount(const QModelIndex &parent) const;
//	//����
//	int columnCount(const QModelIndex &parent)const;	
//	//������ʾ���ݣ����ݽ�ɫ����ɫ���ı������뷽ʽ��ѡ��״̬�ȣ��ж���Ҫ��ʾ�����ݡ�
//	QVariant  data(const QModelIndex &index, int role) const;
//	//�����������ݣ����ݽ�ɫ����ɫ���ı������뷽ʽ��ѡ��״̬�ȣ��ж���Ҫ���õ����ݡ�
//	bool setData(const QModelIndex &index,const QVariant &value,int role);
//	//������ʾˮƽ/��ֱ��ͷ������
//	QVariant headerData(int section, Qt::Orientation orientation, int role) const;
//	//�������õ�Ԫ��ı�־�����á���ѡ�С��ɸ�ѡ�ȣ�
//	Qt::ItemFlags flags(const QModelIndex &index) const;
//private:
//	
//};
//
//#endif // TABLEMODEL_H
