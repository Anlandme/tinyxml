#include <stdio.h>
#include "tinyxml.h"
#include <iostream>
#include <cstring>

using namespace std;

/*
	TiXmlDocument���ĵ��࣬������������xml�ļ�
	TiXmlDeclaration�������࣬����ʾ�ļ�����������
	TiXmlComment��ע���࣬����ʾ�ļ���ע�Ͳ���
	TiXmlElement��Ԫ���࣬�����ļ�����Ҫ���֣�����֧��Ƕ�׽ṹ��һ��ʹ�����ֽṹ������Ĵ洢��Ϣ�������԰�����������ı���
	TiXmlAttribute/TiXmlAttributeSet��Ԫ�����ԣ���һ��Ƕ����Ԫ���У����ڼ�¼��Ԫ�ص�һЩ����
	TiXmlText���ı�������Ƕ����ĳ��Ԫ���ڲ�
*/
//����xml�ļ�

int writeXmlFile()
{
	TiXmlDocument *writeDoc = new TiXmlDocument; //xml�ĵ�ָ��
	
	//�ĵ���ʽ����
	TiXmlDeclaration *decl = new TiXmlDeclaration("1.0", "UTF-8", "yes");
	writeDoc->LinkEndChild(decl); //д���ĵ�

	int n = 3;	//���ڵ����

	TiXmlElement *RootElement = new TiXmlElement("Info");//��Ԫ��
	RootElement->SetAttribute("num", n); //����
	writeDoc->LinkEndChild(RootElement);
	
	for(int i=0; i<n; i++)//n�����ڵ�
	{
		TiXmlElement *StuElement = new TiXmlElement("Stu");//Stu
		
		//��������
		StuElement->SetAttribute("class","A");
		if(2 == i)
		{
				StuElement->SetAttribute("class","B");
		}
		
		StuElement->SetAttribute("id",i+1);
		StuElement->SetAttribute("flag", (i+1)*10);
		RootElement->LinkEndChild(StuElement);//���ڵ�д���ĵ�
	
		//����
		TiXmlElement *nameElement = new TiXmlElement("name");
		StuElement->LinkEndChild(nameElement);

		TiXmlText *nameContent = new TiXmlText("mike");
		nameElement->LinkEndChild(nameContent);
		
		//����
		TiXmlElement *scoreElement = new TiXmlElement("score");
		StuElement->LinkEndChild(scoreElement);

		TiXmlText *scoreContent = new TiXmlText("88");
		scoreElement->LinkEndChild(scoreContent);
		
		//����
		TiXmlElement *cityElement = new TiXmlElement("city");
		StuElement->LinkEndChild(cityElement);

		TiXmlText *cityContent = new TiXmlText("Shenzhen");
		cityElement->LinkEndChild(cityContent);
		
	}
	
	writeDoc->SaveFile("stu_info.xml");
	delete writeDoc;
	
	return 1;
}

//����xml�ļ�
int readXmlFile()
{
	TiXmlDocument mydoc("stu_info.xml");//xml�ĵ�����
	bool loadOk=mydoc.LoadFile();//�����ĵ�
	if(!loadOk)
	{
		cout<<"could not load the test file.Error:"<<mydoc.ErrorDesc()<<endl;
		exit(1);
	}

	TiXmlElement *RootElement=mydoc.RootElement();	//��Ԫ��, Info
	cout<< "[root name]" << RootElement->Value() <<"\n";
	
	TiXmlElement *pEle=RootElement;

	//�����ý��
	for(TiXmlElement *StuElement = pEle->FirstChildElement();//��һ����Ԫ��
		StuElement != NULL;
		StuElement = StuElement->NextSiblingElement())//��һ���ֵ�Ԫ��
	{
		// StuElement->Value() �ڵ�����
		cout<< StuElement->Value() <<" ";
		TiXmlAttribute *pAttr=StuElement->FirstAttribute();//��һ������
		
		while( NULL != pAttr) //�����������
		{
			cout<<pAttr->Name()<<":"<<pAttr->Value()<<" ";
			pAttr=pAttr->Next();
		}
		cout<<endl;
		
		//�����Ԫ�ص�ֵ
		for(TiXmlElement *sonElement=StuElement->FirstChildElement();
		sonElement;
		sonElement=sonElement->NextSiblingElement())
		{
			cout<<sonElement->FirstChild()->Value()<<endl;
		}
	}
	
	return 1;
}

int main(int argc, char *argv[])
{
	writeXmlFile();
	
	printf("\nafter write\n");
	
	readXmlFile();

	return 0;
}
