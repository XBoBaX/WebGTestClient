#include "reportdriver.h"

namespace reportS
{
	void ReportDriver::StartRegister(std::string testCaseName, std::string typeTest, int countReq)
	{
		SqliteDriver SQLdr;
		SQLdr.InsertData(testCaseName, typeTest, countReq);
	}

	void ReportDriver::ParseResult()
	{
		std::ifstream t("report.xml");
		std::string text((std::istreambuf_iterator<char>(t)),
			std::istreambuf_iterator<char>());
		char* text_arr = &text[0];

		std::cout << "\n\n" << text << "\n\n";


		xml_document<> doc;
		doc.parse<0>(&text[0]);

		std::cout << "Name of my first node is: " << doc.first_node()->name() << "\n";

		//TODO how much tests
		//loop by count test:
		////name, result, time, CHECK CHILD NODE _SKIPPED_
		
		//Testsites
		xml_node<>* nodeTestsuites = doc.first_node(nameNode[0]);
		SetTestsuites(nodeTestsuites);

		//Testsite
		xml_node<>* nodeTestsite = nodeTestsuites->first_node(nameNode[1]);


		//TestCase
		xml_node<>* nodeTestCase = nodeTestsite->first_node(nameNode[2]);
		std::cout << "\n"<<nodeTestCase;
		SetTescaeLoop(nodeTestCase);

		/*
		//Get attr testsite
		for (xml_attribute<>* attr = nodeTestsite->first_attribute();
			attr; attr = attr->next_attribute())
		{
			std::cout << "testsuites has attribute " << attr->name() << " ";
			std::cout << "with value " << attr->value() << "\n";
		}

		xml_node<>* nodeTestCase = nodeTestsuites->first_node(nameNode[2]);


		std::cout << "\n111\n";*/
	}

	void ReportDriver::SetTescaeLoop(const xml_node<>* nodeTestCase) const
	{
		SetTestcase(1, nodeTestCase);
		for (int i = 0; i < countTest-1; i++)
		{
			nodeTestCase = nodeTestCase->next_sibling();
			SetTestcase(i+2, nodeTestCase);
		}
	}

	// Parse xml node "Testcase", save result in sqliteDriver
	void ReportDriver::SetTestcase(int idTest, const xml_node<> *nodeTestCase) const
	{
		std::cout << "\n" << idTest<<"\n";
		std::string nameTest = nodeTestCase->first_attribute("name")->value();
		std::string className = nodeTestCase->first_attribute("classname")->value();
		std::string result = nodeTestCase->first_attribute("result")->value();
		std::string timestamp = nodeTestCase->first_attribute("timestamp")->value();
		float timeMs = std::stof(nodeTestCase->first_attribute("time")->value());

		std::string note {""};
		
		const xml_node<>* child = nodeTestCase->first_node();
		if (child != 0)
		{
			note = child->name();
		}


		SqliteDriver SQLDriver;
		SQLDriver.InserReportDataTestcase(nameTest, className, result, timestamp, note, timeMs, idTest);
	}
	
	// Parse xml node "Testsuites", save result to this object (class)
	void ReportDriver::SetTestsuites(const xml_node<> *nodeTestsites)
	{
		countTest = atoi(nodeTestsites->first_attribute("tests")->value());
		totalTimeStamp = nodeTestsites->first_attribute("timestamp")->value();
	}
}