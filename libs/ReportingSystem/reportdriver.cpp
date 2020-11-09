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

		xml_document<> doc;
		doc.parse<0>(&text[0]);
		
		//Testsites
		xml_node<>* nodeTestsuites = doc.first_node(nameNode[0]);
		SetTestsuites(nodeTestsuites);

		//Testsite
		xml_node<>* nodeTestsite = nodeTestsuites->first_node(nameNode[1]);


		//TestCase
		xml_node<>* nodeTestCase = nodeTestsite->first_node(nameNode[2]);
		std::cout << "\n"<<nodeTestCase;
		SetTescaeLoop(nodeTestCase);
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
			result = note;
		}

		SqliteDriver SQLDriver;
		SQLDriver.InserReportDataTestcase(nameTest, className, result, totalTimeStamp, note, timeMs, idTest);
	}
	
	// Parse xml node "Testsuites", save result to this object (class)
	void ReportDriver::SetTestsuites(const xml_node<> *nodeTestsites)
	{
		countTest = atoi(nodeTestsites->first_attribute("tests")->value());
		totalTimeStamp = nodeTestsites->first_attribute("timestamp")->value();
	}

	void ReportDriver::CreateReport() 
	{

		SqliteDriver SQLdr;
		SQLdr.GetListTimeStamp();
		auto copyArrayTime = SQLdr.arrayTime;
		
		std::string selectOp{""};
		int i{1};
		selectOp += "<option value=\"0\">Selected period</option>\n";
	
		for (auto timeItter : copyArrayTime)
		{
			std::string nameFile = "test_report_" + timeItter + ".html";
			nameFile = ReplaceAll(nameFile, "-", "");
			nameFile = ReplaceAll(nameFile, ":", "");
			selectOp += "<option value=\"" + nameFile + "\">" + timeItter + "</option>\n";
		}
		

		std::string str_graph{ "" };
		int masBF[]{ 4,5,7,7,9,11,11,12,12,12,12,12,12,12,12,12,12,12,12,12 };
		int masSW[]{ 0,0,1,2,2,3,5,9,9,9,9,9,9,9,9,9,9,9,9,9 };
		int ij = 0;
		for (std::string count : copyArrayTime)
		{
			str_graph += "['" + count + "', " + std::to_string(masBF[ij]) + ", " + std::to_string(masSW[ij++]) + "],";
		}

		std::cout << str_graph;

		
		

		SQLdr.GetFromCollections("TESTCASE");
		auto copSecTest = SQLdr.arrayTime;

		SQLdr.GetFromCollections("TYPETEST");
		auto copSecType = SQLdr.arrayTime;

		SQLdr.GetFromCollections("COUNTREQ");
		auto copSecReq = SQLdr.arrayTime;


		i = 0;
		for (auto timeItter : copyArrayTime)
		{

			std::ifstream t("../../../test_Pattern.html");
			std::string text((std::istreambuf_iterator<char>(t)),
				std::istreambuf_iterator<char>());

			std::string str_timeDA = timeItter.substr(0,10);
			std::string str_timeTI = timeItter.substr(12,7);
			
			SQLdr.GetData("TIMEMS", timeItter);
			auto copyTimeMS = SQLdr.arrayTime;
			
			int sumTimeMS{0};
			for (std::string element : copyTimeMS) 
			{
				sumTimeMS += stoi(element);
			}
			std::string str_timeMS = "(" + std::to_string(sumTimeMS) + " ms)";

			SQLdr.GetData("RESULT", timeItter);
			auto copyResult = SQLdr.arrayTime;
			
			int completedCNT{ 0 }, skippedCNT{ 0 }, errorsCNT{ 0 }, failursCNT{ 0 }, disabledCNT{ 0 };
			for (std::string elem : copyResult)
			{
				if (elem == "completed") completedCNT++;
				else if (elem == "skipped") skippedCNT++;
				else if (elem == "errors") errorsCNT++;
				else if (elem == "failures") failursCNT++;
				else if (elem == "disabled") disabledCNT++;
			}


			SQLdr.GetData("NAMETEST", timeItter);
			auto copyName = SQLdr.arrayTime;
			SQLdr.GetData("CLASSNAME", timeItter);
			auto copyClass = SQLdr.arrayTime;
			SQLdr.GetData("IDTEST", timeItter);
			auto copyID = SQLdr.arrayTime;

			std::string str_row{ "" };
			int j = 0;
			for (std::string elem : copyResult)
			{
				str_row += "['" + copyName[j] + "', '" + copyClass[j] + "', '" + copyResult[j] + "', " + copyTimeMS[j] + ", " + copyID[j] + "],";
				j++;
			}

			

			

			text = ReplaceAll(text, "I1_000", selectOp);
			text = ReplaceAll(text, "I1_001", str_timeDA);
			text = ReplaceAll(text, "I1_002", str_timeTI);
			text = ReplaceAll(text, "I1_003", str_timeMS);
			text = ReplaceAll(text, "I1_004", std::to_string(copyTimeMS.size()));
			text = ReplaceAll(text, "I1_005", std::to_string(completedCNT));
			text = ReplaceAll(text, "I1_006", std::to_string(skippedCNT));
			text = ReplaceAll(text, "I1_007", std::to_string(errorsCNT));
			text = ReplaceAll(text, "I1_008", std::to_string(failursCNT));
			text = ReplaceAll(text, "I1_009", std::to_string(disabledCNT));
			text = ReplaceAll(text, "I1_010", std::to_string(completedCNT));
			text = ReplaceAll(text, "I1_011", std::to_string(skippedCNT + errorsCNT + failursCNT +  disabledCNT));
			text = ReplaceAll(text, "I1_012", str_row);
			text = ReplaceAll(text, "I1_013", str_graph);
			//text = ReplaceAll(text, "I1_014", str_graph);

			//std::ofstream out("test_report_" + SQLdr.arrayTime[0] + ".html");
			std::string nameFile = "test_report_" + timeItter + ".html";
			nameFile = ReplaceAll(nameFile, "-", "");
			nameFile = ReplaceAll(nameFile, ":", "");
			std::ofstream out(nameFile);

			out << text;
			out.close();

			std::cout << timeItter<<" "<<nameFile;	
		}

	}

	std::string ReportDriver::ReplaceAll(const std::string& inputStr, const std::string& src, const std::string& dst)
	{
		std::tr1::regex rx(src.c_str());
		return std::tr1::regex_replace(inputStr, rx, dst);
	}
}