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
		using namespace rapidxml;

		std::ifstream t("report.xml");
		std::string text((std::istreambuf_iterator<char>(t)),
			std::istreambuf_iterator<char>());
		char* text_arr = &text[0];

		std::cout << "\n\n" << text << "\n\n";


		xml_document<> doc;
		doc.parse<0>(&text[0]);
		
		std::cout << "\n\n" << doc.first_node()->name()<<"\n";

		std::cout << "Name of my first node is: " << doc.first_node()->name() << "\n";

		//TODO how much tests
		//testsuites - count tests, timestamp 
		//testsuite - name, failed, disabled, skipped, errors, time
		//loop by count test:
		////name, result, time, CHECK CHILD NODE _SKIPPED_
		xml_node<>* node = doc.first_node("testsuites")->first_node("testsuite");

		std::cout << "\n1\n"<<node->first_node()->name();

		std::cout << "Node testsuites has value " << node->value() << "\n";
		for (xml_attribute<>* attr = node->first_attribute();
			attr; attr = attr->next_attribute())
		{
			std::cout << "Node testsuites has attribute " << attr->name() << " ";
			std::cout << "with value " << attr->value() << "\n";
		}

		std::cout << "\n111\n";
	}
}