#include "WebPage.hpp"
#include "WebPageContainer.hpp"

#include <iostream>
#include <string>
#include <memory>
#include <vector>
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
		HomePage(const std::string& internalPath) :
			WebPage(internalPath)
		{

		}

		~HomePage() = default;
		

		void render() override
		{
			this->addNew<Wt::WText>("<br>Home page</br>");

			page1 = this->addNew<Wt::WPushButton>("Page 1");
			page1->setLink(Wt::WLink(Wt::LinkType::InternalPath, "/page1"));

			page2 = this->addNew<Wt::WPushButton>("Page 2");
			page2->setLink(Wt::WLink(Wt::LinkType::InternalPath, "/page2"));
		}
		
		
	private:
		Wt::WPushButton* page1 = nullptr;
		Wt::WPushButton* page2 = nullptr;
};


class Page1 : public WebPage
{
	public:
		Page1(const std::string& internalPath) :
			WebPage(internalPath)
		{
			
		}

		~Page1() = default;


		void render() override
		{
			this->addNew<Wt::WText>("<br>Page 1</br>");

			back = this->addNew<Wt::WPushButton>("Home page");
			back->setLink(Wt::WLink(Wt::LinkType::InternalPath, "/"));

			page2 = this->addNew<Wt::WPushButton>("Page 2");
			page2->setLink(Wt::WLink(Wt::LinkType::InternalPath, "/page2"));
		}
		
		
	private:
		Wt::WPushButton* back = nullptr;
		Wt::WPushButton* page2 = nullptr;
};



class Page2 : public WebPage
{
	public:
		Page2(const std::string& internalPath) :
			WebPage(internalPath)
		{
			
		}

		~Page2() = default;


		void render() override
		{
			this->addNew<Wt::WText>("<br>Page 2</br>");

			back = this->addNew<Wt::WPushButton>("Home page");
			back->setLink(Wt::WLink(Wt::LinkType::InternalPath, "/"));

			page1 = this->addNew<Wt::WPushButton>("Page 1");
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

		static App* instance();
		WebPageContainer* wpc();
		const WebPageContainer* wpc() const;


    private:
        void render();
        void run();
        
        
    private:
    	WebPageContainer wpc_;
};



App::App(const Wt::WEnvironment& env) :
	Wt::WApplication(env)
{
    this->render();
    this->run();
}


App* App::instance() {
	return dynamic_cast<App*>(Wt::WApplication::instance());
}


WebPageContainer* App::wpc() {
	return &wpc_;
}


const WebPageContainer* App::wpc() const {
	return &wpc_;
}


void App::render()
{
	wpc_.setRenderContainer(root());

	wpc_.addPage(std::make_unique<HomePage>("/"));
	wpc_.addPage(std::make_unique<Page1>("/page1"));
	wpc_.addPage(std::make_unique<Page2>("/page2"));
	
	wpc_.redirect(this->internalPath());
}



void App::run()
{
	this->internalPathChanged().connect([this]()
	{
		wpc_.redirect(this->internalPath());
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
