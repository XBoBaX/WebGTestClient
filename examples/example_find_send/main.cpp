#include "../libs/WebGTestClient.h"

using namespace webdriver;

int main()
{
	WebDriver browser = Start(Chrome());
	browser.Navigate("https://duckduckgo.org");
	Element elem = browser.FindElement(ByCss("input[name=q]"));
	elem.SendKeys("sha512 helloworld");
	elem.Submit();
	getchar();

	return 0;
}