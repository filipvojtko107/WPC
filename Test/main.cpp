#include "WebPage.hpp"
#include "WebPageContainer.hpp"

#include <iostream>
#include <string>
#include <memory>
#include <exception>

#include <Wt/WApplication.h>
#include <Wt/WEnvironment.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WString.h>
#include <Wt/WLink.h>



class HomePage : public WebPage
{
	public:
		HomePage(const std::string& internalPath)
			: WebPage(internalPath)
		{

		}

		virtual ~HomePage() = default;


		void render(Wt::WContainerWidget& content) override
		{
			content.addNew<Wt::WText>("<br>Home page</br>");

			page1 = content.addNew<Wt::WPushButton>("Page 1");
			page1->setLink(Wt::WLink(Wt::LinkType::InternalPath, "/page1"));

			page2 = content.addNew<Wt::WPushButton>("Page 2");
			page2->setLink(Wt::WLink(Wt::LinkType::InternalPath, "/page2"));
		}
		
		
	private:
		Wt::WPushButton* page1 = nullptr;
		Wt::WPushButton* page2 = nullptr;
};


class Page1 : public WebPage
{
	public:
		Page1(const std::string& internalPath)
			: WebPage(internalPath)
		{
			
		}

		virtual ~Page1() = default;


		void render(Wt::WContainerWidget& content) override
		{
			content.addNew<Wt::WText>("<br>Page 1</br>");

			back = content.addNew<Wt::WPushButton>("Home page");
			back->setLink(Wt::WLink(Wt::LinkType::InternalPath, "/"));

			page2 = content.addNew<Wt::WPushButton>("Page 2");
			page2->setLink(Wt::WLink(Wt::LinkType::InternalPath, "/page2"));
		}
		
		
	private:
		Wt::WPushButton* back = nullptr;
		Wt::WPushButton* page2 = nullptr;
};



class Page2 : public WebPage
{
	public:
		Page2(const std::string& internalPath)
			: WebPage(internalPath)
		{
			
		}

		virtual ~Page2() = default;


		void render(Wt::WContainerWidget& content) override
		{
			content.addNew<Wt::WText>("<br>Page 2</br>");

			back = content.addNew<Wt::WPushButton>("Home page");
			back->setLink(Wt::WLink(Wt::LinkType::InternalPath, "/"));

			page1 = content.addNew<Wt::WPushButton>("Page 1");
			page1->setLink(Wt::WLink(Wt::LinkType::InternalPath, "/page1"));
		}

		
	private:
		Wt::WPushButton* back = nullptr;
		Wt::WPushButton* page1 = nullptr;
};


class App : public Wt::WApplication
{
    public:
    	App() = default;
        App(const Wt::WEnvironment& env);
        virtual ~App() = default;


    private:
        void render();
        void run();


    private:
    	std::unique_ptr<WebPageContainer> cont;
};



App::App(const Wt::WEnvironment& env)
    : Wt::WApplication(env)
{
    this->render();
    this->run();
}


void App::render()
{
	cont = std::make_unique<WebPageContainer>(root());

	cont->addPage<HomePage>("/");
	cont->addPage<Page1>("/page1");
	cont->addPage<Page2>("/page2");
}



void App::run()
{
	cont->renderPage("/");

	this->internalPathChanged().connect([this](void)
	{
		std::vector<std::unique_ptr<WebPage>>* pages = cont->getPages();

		for (std::unique_ptr<WebPage>& page : *pages)
		{
			if (page->getInternalPath() == this->internalPath())
			{
				cont->clearPage(); 
				cont->renderPage(*page);
				break;
			}
		}
	});
}



int main(int argc, char** argv)
{
	try
	{
		return Wt::WRun(argc, argv, [](const Wt::WEnvironment& env) 
		{
			return std::make_unique<App>(env);
		});
	}
	
	catch (const std::exception& err)
	{
		std::cerr << err.what() << std::endl;
		return EXIT_FAILURE;
	}
	
	
	return EXIT_SUCCESS;
}
